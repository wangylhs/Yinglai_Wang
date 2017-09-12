#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include"market.h"
#include<pthread.h>
#define HASH_SIZE (1<<7)
typedef struct order{
	unsigned int id;
	unsigned int quantity;
	struct order *next;
	double price;
}
order;
order *hashbHead[HASH_SIZE];
order *hashsHead[HASH_SIZE];
//global.................
char *psymbol;
order **currentHead;
char currentSide;
int n = 14;
int m = 3;
int count = 0;
int newcount=0;
double bprice;
double sprice;
double *trade;
double *fso;
double *sso;
int tradeN = 0;
int tFlag = 0;
unsigned int cont;
double C;
double L;
double H;
double SSO;
double FSO;
double signal_line;
enum alert_type ACTION;


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
			while(ip->next && ip->next->price > price){
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
			while(ip->next && ip->next->price < price){
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
    //    h ^= (h<<19) | (h>>45);
    //h ^= (h<<32) | (h>>32);
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
    bprice = 0;
    for( i = 0; i < HASH_SIZE; i++) {
        if (hashbHead[i] && hashbHead[i]->price>bprice)
            bprice = hashbHead[i]->price;
    }
    
    sprice = 0;
    for( i = 0; i < HASH_SIZE; i++) {
        if (hashsHead[i] && ( hashsHead[i]->price < sprice || sprice == 0 ) )
            sprice = hashsHead[i]->price;
    }
    //fprintf(fIq, "%lf %lf\n", sprice, bprice);
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
        currentSide = 'B';
        return node;
    } 
    currentHead = &hashsHead[index];
    currentSide = 'S';
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

struct add{
    unsigned int id;
    char side;
    char symbol[4];
    unsigned int quantity;
    double price;
} __attribute__ ((__packed__)) readA;

struct del{
    unsigned int id;
    char symbol[4];
} __attribute__ ((__packed__)) readX;

struct tra{
    unsigned int id;
    char symbol[4];
    unsigned int quantity;
} __attribute__ ((__packed__)) readT;

struct cha{
    unsigned int id;
    char symbol[4];
    unsigned int quantity;
    double price;
} __attribute__ ((__packed__)) readR;

void binaryRead(char ** buff){
    order *previous;
    char *buf=*buff;
    char msg;
    while(cont!=0){
        msg = *buf;
        buf++;
        cont--;
        switch (msg) {
            case 'A':{
                order *p;
                readA = *((struct add*)buf);
                buf += sizeof(struct add);
                cont -= sizeof(struct add);
                if(processFlag(readA.symbol)) {
                    NewHashOrder(readA.id, readA.side, readA.quantity, readA.price);
					count++;
				}
                break;
            }
                
			case 'X':{
                readX = *((struct del*)buf);
                buf += sizeof(struct del);
                cont -= sizeof(struct del);
                if(processFlag(readX.symbol)){
					order *p = SearchHash(readX.id, &previous);
                    DeleteOrder(currentHead, previous);
					count++;
                }
                break;
            }
			case 'C':{
                order *p;
                readT = *((struct tra*)buf);
                buf += sizeof(struct tra);
                cont -= sizeof(struct tra);
                if(processFlag(readT.symbol)){
                    p = SearchHash(readT.id, &previous);
                    p->quantity -= readT.quantity;
                    if(p->quantity <= 0){
                        DeleteOrder(currentHead, previous);
                    }
                    count++;
                }
                break;
            }
			case 'T':{
                order *p;
                
                readT = *((struct tra*)buf);
                buf += sizeof(struct tra);
                cont -= sizeof(struct tra);
                p = SearchHash(readT.id, &previous);
                if(processFlag(readT.symbol)){
                    p->quantity -= readT.quantity;
                    count++;
                    //
                    C = p -> price;
                    int i;
                    double sum = 0;
                    L = C;
                    H = C;
                    for(i=0; i<n; i++){
                        if(trade[i]<L)
                            L = trade[i];
                        if(trade[i]>H)
                            H = trade[i];
                    }
                    FSO = ( (C-L) / (H-L) ) * 100;
                    fso[tradeN%m] = FSO;
                    for(i=0; i<m; i++){
                        sum += fso[i];
                    }
                    SSO = sum/m;
                    sso[tradeN%m] = SSO;
                    sum = 0;
                    for(i=0; i<m; i++){
                        sum += sso[i];
                    }
                    signal_line = sum/m;
                    if ((sso[(tradeN-1)%m] > 80) && (SSO < 80) && (signal_line < SSO) ){
                        ACTION = SELL;
                    }else if ((sso[(tradeN-1)%m] < 20) && (SSO > 20) && (signal_line > SSO) ){
                        ACTION = BUY;
                    }else{
                        ACTION = NO_ACTION;
                        }
                    trade[tradeN%n] = p->price;
                    if(p->quantity <= 0)
                        DeleteOrder(currentHead, previous);
                    tradeN++;
                }
                break;
            }
            case 'R':{
                order *p;
                readR = *((struct cha*)buf);
                buf += sizeof(struct cha);
                cont -= sizeof(struct cha);
                if(processFlag(readR.symbol)){
                    p = SearchHash(readR.id, &previous);
                    if(readR.quantity <= 0){
                        DeleteOrder(currentHead, previous);
                    }else if (p->price == readR.price){
                        p->quantity = readR.quantity;
                    } else {
                        DeleteOrder(currentHead, previous);
                        NewHashOrder(readR.id, currentSide, readR.quantity, readR.price);
                    }
					count++;
                }
                break;
            }
        }
        /*if(count == n){
         newcount++;
         count = 0;
         printIq();
         }*/
    }
}
void killReport(int signum){
	newcount = newcount*n + count;
	if(signum == SIGINT){
		printf("Program killed after processing %d messages for symbol %s.\n", newcount, psymbol);
	}else if(signum == SIGSEGV){
		printf("Program died from a segmentation fault after processing %d messages for symbol %s.\n", newcount, psymbol);
	}
	exit(signum);
}
struct prediction get_prediction(){
    struct prediction p;
    if(tFlag){
        printIq();
        p.SSO = sprice;
        p.signal_line = bprice;
        p.alert = NO_ACTION;
        return p;
    }
    else{
        p.SSO = SSO;
        p.signal_line = signal_line;
        p.alert = ACTION;
        return p;
    }
}


int main(int argc, char **argv){
	signal(SIGINT, killReport);
	signal(SIGSEGV, killReport);
    
    order *head;
	head = NULL;
    FILE *fin; 
	int i=1;
	int inputFile = 0;
    int symbolFlag = 0;
    
    const char *filetype = "r";
	while(i<argc){
		if(strcmp(argv[i],"-i")==0){
			fin = fopen(argv[++i], filetype);
			inputFile = 1;
		}else if(strcmp(argv[i],"-s")==0){
            psymbol = argv[++i];
            symbolFlag = 1;
        }else if(strcmp(argv[i],"-n")==0){
            n = atoi(argv[++i]);
        }else if(strcmp(argv[i],"-m")==0){
            m = atoi(argv[++i]);
        }else if(strcmp(argv[i],"-t")==0){
            tFlag = 1;
        }
		i++;
	}
    if(!inputFile || !symbolFlag){
        printf("Argument missing! Program quit.\n");
        exit(0);
    }
    //inite array
    trade = (double*)malloc(sizeof(double)*n);
    fso = (double*)malloc(sizeof(double)*m);
    sso = (double*)malloc(sizeof(double)*m);
    
    for(i=0; i<n; i++){
        trade[i] = 0;
    }
    for(i=0; i<m; i++){
        fso[i] = 0;
        sso[i] = 0;
    }
    
    init_market(fin, psymbol);
    pthread_t a;
    pthread_create(&a, NULL, market, NULL);
    char *buf;
    while(1){
        buf = get_inputs(&cont);
        if(cont == 0) 
            break;
        binaryRead(&buf);
    }
    
    DeleteHash(hashsHead);
    DeleteHash(hashbHead);
    return 0;
}
