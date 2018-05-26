//
//	memory.c
//
//	Routines for dealing with memory management.

//static char rcsid[] = "$Id: memory.c,v 1.1 2000/09/20 01:50:19 elm Exp elm $";

#include "ostraps.h"
#include "dlxos.h"
#include "process.h"
#include "memory.h"
#include "queue.h"

// num_pages = size_of_memory / size_of_one_page
static uint32 freemap[MEM_MAX_PAGES >> 5];
//static uint32 pagestart;
//static int nfreepages;
//static int freemapmax;

//----------------------------------------------------------------------
//
//	This silliness is required because the compiler believes that
//	it can invert a number by subtracting it from zero and subtracting
//	an additional 1.  This works unless you try to negate 0x80000000,
//	which causes an overflow when subtracted from 0.  Simply
//	trying to do an XOR with 0xffffffff results in the same code
//	being emitted.
//
//----------------------------------------------------------------------
static int negativeone = 0xFFFFFFFF;
static inline uint32 invert (uint32 n) {
  return (n ^ negativeone);
}

//----------------------------------------------------------------------
//
//	MemoryGetSize
//
//	Return the total size of memory in the simulator.  This is
//	available by reading a special location.
//
//----------------------------------------------------------------------
int MemoryGetSize() {
  return (*((int *)DLX_MEMSIZE_ADDRESS));
}


//----------------------------------------------------------------------
//
//	MemoryInitModule
//
//	Initialize the memory module of the operating system.
//      Basically just need to setup the freemap for pages, and mark
//      the ones in use by the operating system as "VALID", and mark
//      all the rest as not in use.
//
//----------------------------------------------------------------------
void MemoryModuleInit() {
	int i;
	uint32 os_num_pages = lastosaddress >> MEM_L1FIELD_FIRST_BITNUM;	// last address/4KB
	uint32 os_free_map_size = os_num_pages >> 5;											// size of free map that os occupies
	 																																	// total os pages / 32
	uint32 os_free_map_inuse_bit = os_num_pages & 0x1F;								// os_num_pages % 32
	
	//init freemap
	for(i=0; i<(MEM_MAX_PAGES >> 5); i++){
		freemap[i] = 0xFFFFFFFF;
	}
	//mark the ones used by os
	for(i=0; i<os_free_map_size; i++){
		freemap[i] = 0;			// mark them in use
	}
	//mark the bit on last os page
	freemap[i] = freemap[i] >> os_free_map_inuse_bit;
}


//----------------------------------------------------------------------
//
// MemoryTranslateUserToSystem
//
//	Translate a user address (in the process referenced by pcb)
//	into an OS (physical) address.  Return the physical address.
//
//----------------------------------------------------------------------
uint32 MemoryTranslateUserToSystem (PCB *pcb, uint32 addr) {
	uint32 offset = addr & MEM_ADDRESS_OFFSET_MASK;
	uint32 page_num = addr >> MEM_L1FIELD_FIRST_BITNUM;
	uint32 pte = pcb->pagetable[page_num];
	
	if((pte & MEM_PTE_VALID)==0){
		pcb->currentSavedFrame[PROCESS_STACK_FAULT] = addr;
		if(MemoryPageFaultHandler(pcb) == MEM_FAIL){
			return 0;
		}
	}
	return (pte&MEM_PTE_MASK) | offset;
}


//----------------------------------------------------------------------
//
//	MemoryMoveBetweenSpaces
//
//	Copy data between user and system spaces.  This is done page by
//	page by:
//	* Translating the user address into system space.
//	* Copying all of the data in that page
//	* Repeating until all of the data is copied.
//	A positive direction means the copy goes from system to user
//	space; negative direction means the copy goes from user to system
//	space.
//
//	This routine returns the number of bytes copied.  Note that this
//	may be less than the number requested if there were unmapped pages
//	in the user range.  If this happens, the copy stops at the
//	first unmapped address.
//
//----------------------------------------------------------------------
int MemoryMoveBetweenSpaces (PCB *pcb, unsigned char *system, unsigned char *user, int n, int dir) {
  unsigned char *curUser;         // Holds current physical address representing user-space virtual address
  int		bytesCopied = 0;  // Running counter
  int		bytesToCopy;      // Used to compute number of bytes left in page to be copied

  while (n > 0) {
    // Translate current user page to system address.  If this fails, return
    // the number of bytes copied so far.
    curUser = (unsigned char *)MemoryTranslateUserToSystem (pcb, (uint32)user);

    // If we could not translate address, exit now
    if (curUser == (unsigned char *)0) break;

    // Calculate the number of bytes to copy this time.  If we have more bytes
    // to copy than there are left in the current page, we'll have to just copy to the
    // end of the page and then go through the loop again with the next page.
    // In other words, "bytesToCopy" is the minimum of the bytes left on this page 
    // and the total number of bytes left to copy ("n").

    // First, compute number of bytes left in this page.  This is just
    // the total size of a page minus the current offset part of the physical
    // address.  MEM_PAGESIZE should be the size (in bytes) of 1 page of memory.
    // MEM_ADDRESS_OFFSET_MASK should be the bit mask required to get just the
    // "offset" portion of an address.
    bytesToCopy = MEM_PAGESIZE - ((uint32)curUser & MEM_ADDRESS_OFFSET_MASK);
    
    // Now find minimum of bytes in this page vs. total bytes left to copy
    if (bytesToCopy > n) {
      bytesToCopy = n;
    }

    // Perform the copy.
    if (dir >= 0) {
      bcopy (system, curUser, bytesToCopy);
    } else {
      bcopy (curUser, system, bytesToCopy);
    }

    // Keep track of bytes copied and adjust addresses appropriately.
    n -= bytesToCopy;           // Total number of bytes left to copy
    bytesCopied += bytesToCopy; // Total number of bytes copied thus far
    system += bytesToCopy;      // Current address in system space to copy next bytes from/into
    user += bytesToCopy;        // Current virtual address in user space to copy next bytes from/into
  }
  return (bytesCopied);
}

//----------------------------------------------------------------------
//
//	These two routines copy data between user and system spaces.
//	They call a common routine to do the copying; the only difference
//	between the calls is the actual call to do the copying.  Everything
//	else is identical.
//
//----------------------------------------------------------------------
int MemoryCopySystemToUser (PCB *pcb, unsigned char *from,unsigned char *to, int n) {
  return (MemoryMoveBetweenSpaces (pcb, from, to, n, 1));
}

int MemoryCopyUserToSystem (PCB *pcb, unsigned char *from,unsigned char *to, int n) {
  return (MemoryMoveBetweenSpaces (pcb, to, from, n, -1));
}

//---------------------------------------------------------------------
// MemoryPageFaultHandler is called in traps.c whenever a page fault 
// (better known as a "seg fault" occurs.  If the address that was
// being accessed is on the stack, we need to allocate a new page 
// for the stack.  If it is not on the stack, then this is a legitimate
// seg fault and we should kill the process.  Returns MEM_SUCCESS
// on success, and kills the current process on failure.  Note that
// fault_address is the beginning of the page of the virtual address that 
// caused the page fault, i.e. it is the vaddr with the offset zero-ed
// out.
//
// Note: The existing code is incomplete and only for reference. 
// Feel free to edit.
//---------------------------------------------------------------------
int MemoryPageFaultHandler(PCB *pcb) {

  uint32 addr = pcb->currentSavedFrame[PROCESS_STACK_FAULT];
  uint32 ppagenum;
	uint32 vpagenum = addr>>MEM_L1FIELD_FIRST_BITNUM;
	uint32 stackpagenum = pcb->currentSavedFrame[PROCESS_STACK_USER_STACKPOINTER]>>MEM_L1FIELD_FIRST_BITNUM;
  /* // segfault if the faulting address is not part of the stack */
  if (vpagenum < stackpagenum) {
 		dbprintf('m', "addr = %x\nsp = %x\n", addr, pcb->currentSavedFrame[PROCESS_STACK_USER_STACKPOINTER]);
 		//printf("FATAL ERROR (%d): segmentation fault at page address %x\n", findpid(pcb), addr);
  	ProcessKill();
  	return MEM_FAIL;
	}

  ppagenum = MemoryAllocPage();
  pcb->pagetable[vpagenum] = MemorySetupPte(ppagenum);
  dbprintf('m', "Returning from page fault handler\n");
  printf("allocate new page!!\n");
  return MEM_SUCCESS;
}


//---------------------------------------------------------------------
// You may need to implement the following functions and access them from process.c
// Feel free to edit/remove them
//---------------------------------------------------------------------

int MemoryAllocPage(void) {
	int i;
	int index = 31;
	uint32 freemap_mask = 0x80000000; 					//1000 0000 0000 0000 0000 0000 0000 0000
																							// used to go through freemap[i] bit by bit
	int p_page_num;
	// find a index of freemap that is not entirely used
	for(i=0;i<MEM_MAX_PAGES;i++){
		if(freemap[i]!=0) break;
	}
	
	// find bit index of free page
	while((freemap[i]&freemap_mask)==0){
		// page is used, keep shifting 1 toward right
		freemap_mask = freemap_mask>>1;
		index-=1;
	}
	// mark it inuse
	freemap[i] = freemap[i] & invert(0x1<<index);
	p_page_num = i*32+32-index;
  return p_page_num;									// return physical page number
}


uint32 MemorySetupPte (uint32 page) {
	// set PTE and its valid bit
  return (page<<MEM_L1FIELD_FIRST_BITNUM) | 0x1;
}


void MemoryFreePage(uint32 page) {
	uint32 i = page>>5;
	uint32 index = page & 0x1F;
	freemap[i] = freemap[i] | (0x1<<index);
	return;
}

