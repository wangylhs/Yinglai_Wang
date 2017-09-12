import project4.ILinkedList;

public class LinkedList<E> implements ILinkedList{

	private LinkedNode<E> head;
	
	public Object get(int arg0) throws OrderIndexOutOfBoundsException {
	
		LinkedNode<E> ptr = head;
		
		if(head==null)
		{
			throw new OrderIndexOutOfBoundsException();
		}
		
		for(int i=0; i<arg0; i++)
		{
			if(ptr.next!=null)
			{
				ptr = ptr.next;
			}
			else
			{
				throw new OrderIndexOutOfBoundsException();
			}
		}
		
		return ptr.item;
	}


	public void insert(Object obj, int index)
			throws OrderIndexOutOfBoundsException {
		
		LinkedNode<E> ptr = head;
	
		LinkedNode<E> NewNode = new LinkedNode<E>();
		
				
		if(head==null)
		{
			throw new OrderIndexOutOfBoundsException();
		}
		
		for(int i=0; i<index-1; i++)
		{
			if(ptr.next!=null)
			{
				ptr = ptr.next;
			}
			else
			{
				throw new OrderIndexOutOfBoundsException();
			}
		}
		
		NewNode.next = ptr.next;
		ptr.next = NewNode;
		NewNode.item = (E) obj;
		
	}


	public void insertHead(Object obj) {
		
		LinkedNode<E> NewNode = new LinkedNode<E>();
		NewNode.item = (E) obj;
		
		if(head==null)
		{
			head = NewNode;
		}
		
		else
		{
			NewNode.next = head;
			head = NewNode;
		}
	}


	public void insertTail(Object obj) {
		
		LinkedNode<E> ptr = head;
		LinkedNode<E> NewNode = new LinkedNode<E>();
		NewNode.item = (E) obj;
		
		if(head==null)
		{
			head = NewNode;
			NewNode.next = null;
		}
		else
		{
			while(ptr.next!=null)
			{
				ptr = ptr.next;
			}
		
			ptr.next = NewNode;
			NewNode.next = null;
		}

	}
	public boolean isEmpty() {
		
		if(head==null)
		{
			return true;
		}
		
		return false;
	}

	
	public Object remove(int index) throws OrderIndexOutOfBoundsException {
		
		LinkedNode<E> ptr = head;
		LinkedNode<E> ptr2;
		
		if(head==null)
		{
			throw new OrderIndexOutOfBoundsException();
		}
		
		for(int i=0; i<index-1; i++)
		{
			if(ptr.next!=null)
			{
				ptr = ptr.next;
			}
			else
			{
				throw new OrderIndexOutOfBoundsException();
			}
		}
		
		if(ptr==head)
		{
			head = ptr.next;
			ptr.next = null;
			return ptr.item;
		}
		
		else
		{
			ptr2 = ptr.next;
			ptr.next = ptr.next.next;
			ptr2.next = null;
			return ptr2.item;
		}
	}


	public int size() {
		int size = 1;
		LinkedNode<E> ptr = head;
		
		if(head==null)
		{
			return 0;
		}
		
		while(ptr.next!=null)
		{
			ptr = ptr.next;
			size++;
		}
		
		return size;	
	}
	
	public void print()
	{
		LinkedNode<E> ptr = head;
		
		if(head==null)
		{
			System.out.println("Head IS Null :(");
		}
		
		else
		{
			System.out.println("\n\n----------------------");
			while(ptr!=null)
			{
				System.out.println("Item : " + ptr.item);
				ptr = ptr.next;
			}
		}
	}
	
}
