#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define HASH_SIZE 10

typedef struct order{
	struct order *next;
	struct order *previous;
	long int id;
	char side;
	char symbol[5];
	int quantity;
	double price;
}
order;

order *hashHead[HASH_SIZE];
order *hashTail[HASH_SIZE];


void NewOrder(order **head, order **tail, long int id, char side, char *symbol, int quantity, double price){
	order *p = (order*)malloc(sizeof(order));

	if(*head == NULL){
		p -> next = p -> previous = NULL;
		p -> id = id;
		p -> side = side;
		p -> quantity = quantity;
		strcpy(p->symbol,symbol);
		p -> price = price;
		*head = *tail = p;
	}else{
		p -> next = NULL;
		p -> previous = *tail;
		(*tail) -> next = p;
		*tail = p;
		p -> id = id;
		p -> side = side;
		p -> quantity = quantity;
		strcpy(p->symbol,symbol);
		p -> price = price;
	}
}

void DeleteOrder(order **head, order **tail, order *node){
	if(*head == NULL){
		return;
	}
	order *previous = node -> previous;
	order *next = node -> next;
	free(node);
	if(previous){
		previous -> next = next;
	}else{
		*head = next;
	}
	if(next){
		next -> previous = previous;
	}else{
		*tail = previous;
	}
}

order *GetNext(order *node){
	return node -> next;
}
long int GetID(order *node){
	return node -> id;
}
char GetSide(order *node){
	return node -> side;
}
char *GetSymbol(order *node){
	return node -> symbol;
}
int GetQuantity(order *node){
	return node -> quantity;
}

double GetPrice(order *node){
	return node -> price;
}

order *Search(int id, order **head){
	if(*head == NULL){
		return NULL;
	}
	order *p = *head;
	while(p!=NULL){
		if((p->id)==id){
			return p;
		}else{
			p = p->next;
		}
	}
	return NULL;
}

void DeleteList(order **head, order **tail){
	order *p = *head;
	while(p){
		order *temp = p->next;
		free(p);
		p = temp;
	}
	*head = *tail = NULL;
}

void PrintOrder(FILE *fp, order **head){
	order *node;
	if(*head != NULL){
		for(node = *head; node!=NULL; node = GetNext(node)){
			fprintf(fp, "%ld %c %d %lf\n", GetID(node), GetSide(node), GetQuantity(node), node->price);
		}
	}
}

int getHashIndex(long int id){
	return (id % HASH_SIZE);
}

void printHash(FILE *fp){
	int i;
	for(i=0; i<HASH_SIZE; i++){
		PrintOrder(fp,&hashHead[i]);
	}
}

void NewHashOrder(long int id, char side, char *symbol, int quantity, double price){
	int index = getHashIndex(id);
	NewOrder(&hashHead[index], &hashTail[index], id, side, symbol, quantity, price);
}

void DeleteHashOrder(long int id, order *node){
	int index = getHashIndex(id);
	DeleteOrder(&hashHead[index], &hashTail[index],node);
}

order *SearchHash(long int id){
	int index = getHashIndex(id);
	return Search(id, &hashHead[index]);
}

void DeleteHash(){
	int i;
	for(i=0; i<HASH_SIZE; i++){
		DeleteList(&hashHead[i], &hashTail[i]);
	}
}

int main(int argc, char **argv){

	order *head, *tail;
	head = tail = NULL;

	char msg;
    FILE *fin;
	FILE *fout;
	int i=1;
	int inputFile = 0;
	int outputFile = 0;
	int hashmapFlag = 0;

	while(i<argc){
		if(strcmp(argv[i],"-i")==0){
			fin = fopen(argv[++i],"r");
			inputFile = 1;
		}

		else if(strcmp(argv[i],"-o")==0){
			fout = fopen(argv[++i],"w");
			outputFile = 1;
		}

		else if(strcmp(argv[i],"-h")==0){
			hashmapFlag = 1;
		}
		i++;
	}

	if(!inputFile)
		fin = stdin;

	if(!outputFile)
		fout = stdout;

    while((msg=getc(fin))!=EOF){
        switch (msg) {
            case 'A':{	long int id;
						char side;
						char symbol[5];
						int quantity;
						double price;
                		order *p = (order*)malloc(sizeof(order));
                		fscanf(fin, "%ld %c %s %d %lf",&id,&side,symbol,&quantity,&price);
						if(!hashmapFlag)
							NewOrder(&head, &tail, id, side, symbol, quantity,price);
						else
							NewHashOrder(id, side, symbol, quantity, price);
						break;
					 }

			case 'X':{
               			long int id;
               			char symbol[5];
                		fscanf(fin, "%ld %s", &id, symbol);
                		if(!hashmapFlag){
							order *p = Search(id, &head);
							DeleteOrder(&head, &tail, p);
						}else{
							order *p = SearchHash(id);
							DeleteHashOrder(id, p);
						}
						break;
					 }
			case 'C':{
                		long int id;
                		char symbol[5];
                		int quantity;
						order *p;
                		fscanf(fin, "%ld %s %d", &id, symbol, &quantity);
                		if(!hashmapFlag)
							p = Search(id, &head);
                		else
							p = SearchHash(id);
						p->quantity -= quantity;
						break;
					 }
            case 'T':{
                		long int id;
                		char symbol[5];
                		int quantity;
						order *p;
                		fscanf(fin, "%ld %s %d", &id, symbol, &quantity);
                		if(!hashmapFlag)
							p = Search(id, &head);
                		else
							p = SearchHash(id);
						p->quantity -= quantity;
                		break;
					 }
            case 'R':{
               			long int id;
                		char symbol[5];
                		int quantity;
						double price;
						order *p;
						fscanf(fin, "%ld %s %d %lf", &id, symbol, &quantity, &price);
                		if(!hashmapFlag)
							p = Search(id, &head);
                		else
							p = SearchHash(id);
						p->quantity = quantity;
						p->price = price;
                		break;
					 }
        }


    }

	if(hashmapFlag)
		printHash(fout);
	else
		PrintOrder(fout, &head);
}
