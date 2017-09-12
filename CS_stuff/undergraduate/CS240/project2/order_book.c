#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define HASH_SIZE (1<<11)

typedef struct order{
	struct order *next;
    struct order *pprev;
    struct order *pnext;
    char side;
	unsigned int id;
	unsigned int quantity;
	double price;
}
order;

order shead, bhead;
order *hashbHead[HASH_SIZE];
FILE *fIq;
const char *psymbol;
order **currentHead;
int n = 1000;

void NewBOrder(order **head, char side, unsigned int id, unsigned int quantity, double price){
	order *p = (order*)malloc(sizeof(order));
    p -> next = *head;
    p -> side = side;
    p -> id = id;
    p -> quantity = quantity;
    p -> price = price;
    *head = p;

    order *ip;
    if (side=='B'){
        ip = &bhead;
        while(ip->pnext && ip->pnext->price > price){
				ip = ip -> pnext;
        }
        p->pprev = ip;
        p->pnext = ip->pnext;
        ip->pnext = p;
        if(p->pnext)
            p->pnext->pprev = p;
    } else { //'S'
        ip = &shead;
        while(ip->pnext && ip->pnext->price < price){
            ip = ip -> pnext;
        }
        p->pprev = ip;
        p->pnext = ip->pnext;
        ip->pnext = p;
        if(p->pnext)
            p->pnext->pprev = p;
    }
}

void DeleteOrder(order **head, order *previous){
	if(*head == NULL){
		return;
	}

    order *node;
    if(previous==NULL){
        node = *head;
        *head = (*head)->next;
    }else{
        node = previous->next;
        order *next = node->next;
        previous->next = next;
    }
    
    order *pprev = node->pprev;
    order *pnext = node->pnext;

    pprev -> pnext = pnext;
    if (pnext) {
        pnext -> pprev = pprev;
    }
    
    free(node);
}

order *GetNext(order *node){
	return node -> next;
}
unsigned int GetID(order *node){
	return node -> id;
}
int GetQuantity(order *node){
	return node -> quantity;
}

double GetPrice(order *node){
	return node -> price;
}

order *Search(int id, order **head, order **previous){
	if(*head == NULL){
		return NULL;
	}
    *previous = NULL;
	order *p = *head;
	while(p!=NULL){
		if((p->id)==id){
			return p;
		}else{
			*previous = p;
			p = p->next;
		}
	}
	return NULL;
}

void DeleteList(order **head){
	order *p = *head;
	while(p){
		order *temp = p->next;
		free(p);
		p = temp;
	}
	*head = NULL;
}

void PrintOrder(FILE *fp, order **head){
	order *node;
	if(*head != NULL){
		for(node = *head; node!=NULL; node = GetNext(node)){
			fprintf(fp, "%u %c %u %lf\n", GetID(node), node -> side, GetQuantity(node), node->price);
		}
	}
}

int getHashIndex(unsigned int id){
    unsigned long int h = id;
    h ^= (h<<19) | (h>>45);
    h ^= (h<<32) | (h>>32);
	return (id % HASH_SIZE);
}

void printHash(FILE *fp){
	int i;
	for(i=0; i<HASH_SIZE; i++){
		PrintOrder(fp, &hashbHead[i]);
	}
}

void printIq()
{
    int i;
    double bprice = 0, sprice = 0;
    if (bhead.pnext) bprice = bhead.pnext->price;
    if (shead.pnext) sprice = shead.pnext->price;
    fprintf(fIq, "%lf %lf\n", sprice, bprice);
}

void NewHashOrder(unsigned int id, char side, unsigned int quantity, double price){
	int index = getHashIndex(id);
    NewBOrder(&hashbHead[index], side, id, quantity, price);
}

order *SearchHash(unsigned int id, order **previous){
	int index = getHashIndex(id);
	order *node = Search(id, &hashbHead[index], previous);
    currentHead = &hashbHead[index];
    return node;
}

void DeleteHash(){
	int i;
	for(i=0; i<HASH_SIZE; i++){
		DeleteList(&hashbHead[i]);
	}
}
int processFlag(char *s){
    return !psymbol || strncmp(s,psymbol,4)==0;
}

void txtRead(FILE *fin, FILE *fout){
    char msg;
    order *previous;
    int count = 0;
    while(fread(&msg, sizeof(char), 1, fin)==1){
        switch (msg) {
            case 'A':{	
                unsigned int id;
                char side;
                char symbol[5];
                unsigned int quantity;
                double price;
                fscanf(fin, "%u %c %s %u %lf",&id,&side,symbol,&quantity,&price);
                if(processFlag(symbol)) {
					count++;
                    NewHashOrder(id, side, quantity, price);
				}
                break;
            }
                
			case 'X':{
                unsigned int id;
                char symbol[5];
                fscanf(fin, "%u %s", &id, symbol);
                if(processFlag(symbol)){
					count++;
                    order *p = SearchHash(id, &previous);
                    DeleteOrder(currentHead, previous);
                }
                break;
            }
			case 'C':
			case 'T':{
                unsigned int id;
                char symbol[5];
                unsigned int quantity;
                order *p;
                fscanf(fin, "%u %s %u", &id, symbol, &quantity);
                if(processFlag(symbol)){
					count++;
                    p = SearchHash(id, &previous);
                    p->quantity -= quantity;
                    if(p->quantity <= 0)
                        DeleteOrder(currentHead, previous);
                }
                break;
            }
            case 'R':{
                char side;
                unsigned int id;
                char symbol[5];
                unsigned int quantity;
                double price;
                order *p;
                fscanf(fin, "%u %s %u %lf", &id, symbol, &quantity, &price);
                if(processFlag(symbol)){
					count++;
                    p = SearchHash(id, &previous);
                    side = p->side;
                    DeleteOrder(currentHead, previous);
                    NewBOrder(currentHead, side, id, quantity, price);
                }
                break;
            }
        }
        if(count == n){
            count = 0;
            printIq();
        }
    }

}
struct{
    unsigned int id;
    char side;
    char symbol[4];
    unsigned int quantity;
    double price;
} __attribute__ ((__packed__)) readA;

struct{
    unsigned int id;
    char symbol[4];
} __attribute__ ((__packed__)) readX;

struct{
    unsigned int id;
    char symbol[4];
    unsigned int quantity;
} __attribute__ ((__packed__)) readT;

struct{
    unsigned int id;
    char symbol[4];
    unsigned int quantity;
    double price;
} __attribute__ ((__packed__)) readR;

void binaryRead(FILE *fin, FILE *fout){
    char msg;
    order *previous;
    int count = 0;
    while(fread(&msg, sizeof(char), 1, fin)==1){
        switch (msg) {
            case 'A':{	
                order *p = (order*)malloc(sizeof(order));
                fread(&readA, sizeof(readA), 1, fin);
                if(processFlag(readA.symbol)) {
                    NewHashOrder(readA.id, readA.side, readA.quantity, readA.price);
					count++;
				}
                break;
            }
                
			case 'X':{
                fread(&readX, sizeof(readX), 1, fin);
                if(processFlag(readX.symbol)){
                    order *p = SearchHash(readX.id, &previous);
                    DeleteOrder(currentHead, previous);
					count++;
                }
                break;
            }
			case 'C':
			case 'T':{
                order *p;
                fread(&readT, sizeof(readT), 1, fin);
                if(processFlag(readT.symbol)){
                    p = SearchHash(readT.id, &previous);
                    p->quantity -= readT.quantity;
                    if(p->quantity <= 0)
                        DeleteOrder(currentHead, previous);
					count++;
                }
                break;
            }
            case 'R':{
                order *p;
                fread(&readR, sizeof(readR), 1, fin);
                if(processFlag(readR.symbol)){
					count++;
                    p = SearchHash(readR.id, &previous);
                    char side = p->side;
                    DeleteOrder(currentHead, previous);
                    NewBOrder(currentHead, side, readR.id, readR.quantity, readR.price);
                }
                break;
            }
        }
        if(count == n){
            count = 0;
            printIq();
        }
    }
}

int main(int argc, char **argv){
	order *head;
	head = NULL;
    FILE *fin;
	FILE *fout;
	int i=1;
	int inputFile = 0;
	int outputFile = 0;
    const char *filetype = "r";
	while(i<argc){
		if(strcmp(argv[i],"-i")==0){
			fin = fopen(argv[++i], filetype);
			inputFile = 1;
		}else if(strcmp(argv[i],"-o")==0 && i+1 < argc){
			fout = fopen(argv[++i],"w");
			outputFile = 1;
		}else if(strcmp(argv[i],"-b")==0 && i+1 < argc){
            filetype = "rb";
        }else if(strcmp(argv[i],"-s")==0){
            psymbol = argv[++i];
        }else if(strcmp(argv[i],"-n")==0){
            n = atoi(argv[++i]);
        }
		i++;
	}
	if(!inputFile)
		fin = stdin;
	if(!outputFile)
		fout = fopen("ob.txt","w");
    fIq = fopen("iq.txt", "w");
    if(strcmp(filetype,"r")==0){
        txtRead(fin, fout);
    }else{
        binaryRead(fin, fout);
    }
    printHash(fout);
    fclose(fout);
    fclose(fIq);
}
