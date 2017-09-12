#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define HASH_SIZE (1<<11)

typedef struct order{
	struct order *next;
	unsigned int id;
	unsigned int quantity;
	double price;
}
order;

order *hashbHead[HASH_SIZE];
order *hashsHead[HASH_SIZE];
FILE *fIq;
const char *psymbol;
order **currentHead;
int n = 1000;

void NewBOrder(order **head, unsigned int id, unsigned int quantity, double price){
	order *p = (order*)malloc(sizeof(order));
	if(*head == NULL){
		p -> next = NULL;
		p -> id = id;
		p -> quantity = quantity;
		p -> price = price;
		*head = p;
	}else{
		order *ip = *head;
		if(ip->price <= price){
			p->next = *head;
			*head = p;
		}else {
			while(ip->next && ip->next->price <= price){
				ip = ip -> next;
			}
			p->next = ip->next;
			ip->next = p;
		}
		p -> id = id;
		p -> quantity = quantity;
		p -> price = price;
	}
}
void NewSOrder(order **head, unsigned int id, unsigned int quantity, double price){
	order *p = (order*)malloc(sizeof(order));
	if(*head == NULL){
		p -> next = NULL;
		p -> id = id;
		p -> quantity = quantity;
		p -> price = price;
		*head = p;
	}else{
		order *ip = *head;
		if(ip->price >= price){
			p->next = *head;
			*head = p;
		}else {
			while(ip->next && ip->next->price >= price){
				ip = ip -> next;
			}
			p->next = ip->next;
			ip->next = p;
		}
		p -> id = id;
		p -> quantity = quantity;
		p -> price = price;
	}
}

void DeleteOrder(order **head, order *previous){
	if(*head == NULL){
		return;
	}
    if(previous==NULL){
        order *next = (*head)->next;
        free(*head);
        *head = next;
    }else{
        order *node = previous->next;
        order *next = node->next;
        free(node);
        previous->next = next;
    }
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

void PrintOrder(FILE *fp, char side,order **head){
	order *node;
	if(*head != NULL){
		for(node = *head; node!=NULL; node = GetNext(node)){
			fprintf(fp, "%u %c %u %lf\n", GetID(node), side, GetQuantity(node), node->price);
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
		PrintOrder(fp, 'B', &hashbHead[i]);
        PrintOrder(fp, 'S', &hashsHead[i]);
	}
}

void printIq()
{
    int i;
    double bprice = 0;
    for( i = 0; i < HASH_SIZE; i++) {
        if (hashbHead[i] && hashbHead[i]->price>bprice)
            bprice = hashbHead[i]->price;
    }
    
    double sprice = 0;
    for( i = 0; i < HASH_SIZE; i++) {
        if (hashsHead[i] && ( hashsHead[i]->price < sprice || sprice == 0 ) )
            sprice = hashsHead[i]->price;
    }
    fprintf(fIq, "%lf %lf\n", sprice, bprice);
}

void NewHashOrder(unsigned int id, char side, unsigned int quantity, double price){
	int index = getHashIndex(id);
    if (side=='B')
        NewBOrder(&hashbHead[index], id, quantity, price);
    else
        NewSOrder(&hashsHead[index], id, quantity, price);

}


order *SearchHash(unsigned int id, order **previous){
	int index = getHashIndex(id);
	order *node = Search(id, &hashbHead[index], previous);
    if (node) {
        currentHead = &hashbHead[index];
        return node;
    } 
    currentHead = &hashsHead[index];
    node =  Search(id, &hashsHead[index], previous);
    return node;
}

void DeleteHash(){
	int i;
	for(i=0; i<HASH_SIZE; i++){
		DeleteList(&hashbHead[i]);
	}
    for(i=0; i<HASH_SIZE; i++){
		DeleteList(&hashsHead[i]);
	}
}
int processFlag(char *s){
    return !psymbol || strncmp(s,psymbol,4)==0;
}

void txtRead(FILE *fin, FILE *fout){
    char msg;
    order *previous;
    int count = 0;
    while((msg=getc(fin))!=EOF){
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
                unsigned int id;
                char symbol[5];
                unsigned int quantity;
                double price;
                order *p;
                fscanf(fin, "%u %s %u %lf", &id, symbol, &quantity, &price);
                if(processFlag(symbol)){
					count++;
                    p = SearchHash(id, &previous);
                    p->quantity = quantity;
                    p->price = price;
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
    while((msg=getc(fin))!=EOF){
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
                    p = SearchHash(readR.id, &previous);
                    p->quantity = readR.quantity;
                    p->price = readR.price;
					count++;
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
