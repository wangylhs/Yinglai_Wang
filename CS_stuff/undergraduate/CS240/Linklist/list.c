#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define HASH_SIZE 10;

typedef struct order{
	struct order *next;
	struct order *previews;
	long int id;
	char side;
	char *symbol;
	int quantity;
	double price;
};

void newOrder(order **head, order **tail, long int id, char side, char *symbol, int quantity, double price){
	order *p = (order*)malloc(sizeof(order));

	if(*head == NULL){
		p -> next = p -> previous = NULL;
		p -> id = id;
		p -> side = side;
		p -> symbol = strdup(symbol);
		p -> quantity = quantity;
		p -> price = price;
	}else{
		p -> next = NULL;
		p -> previous = *tail;
		(*tail) -> next = p;
		*tail = p;
		p -> id = id;
		p -> side = side;
		p -> symbol = strdup(symbol);
		p -> quantity = quantity;
		p -> price = price;
	}
}
void deleteOrder(order **head, order **tail, order *node){
	if(*head == NULL)
		return;
	order *previous = node -> previous;
	order *next = node -> next;
	free(node->symbol);
	free(node);
	if(previous!=NULL){
		previous -> next = next;
	}else{
		*head = next;
	}
	if(next!=NULL){
		next -> previous = previous;
	}else{
		*tail = previous;
	}
}
order *searchOrder(order **head, long int id){
	order *p = *head;
	while(p!=NULL){
		if((p->id) == id){
			return p;
		}else{
			return NULL;
		}
	}
	return NULL;
}

void setQuantity(order **head, long int id, int quantity){
	order *p = searchOrder(&head, id);
	p -> quantity = quantity;
}
void setPrice(order **head, long int id, double price){
	order *p = searchOrder(&head, id);
	p -> price = price;
}
void setSide(order **head, long int id, char side){
	order *p = searchOrder(&head, id);
	p -> side = side;
}
void deleteList(order **head, order **tail){
	order *p = *head;
	while(p!=NULL){
		order *temp = p -> next;
		free(p->symbol);
		free(p);
		p = temp;
	}
	*head = *tail = NULL;
}
void printOrder(FILE *filep, order **head){
	order *node;
	if(*head != NULL){
		for(node = *head; node!=NULL; node = node->next){
			fprintf(filep, "%ld %c %d %lf\n", node->id, node->side, node->quantity, node->price);
		}
	}
}
//main-------------------------------------------------------
int main(int argc, char **argv){
	order *head, *tail;
	head = tail = NULL;

	char operation;
	FILE *fin = stdin, *fout = stdout;
	int i;
	int inputFlag = 0, outputFlag = 0, hashFlag = 0;
	for(i=1, i<argc, i++){
		if(strcmp(argv[i],"-i")==0){
			fin = fopen(argv[++i], "r");
			inputFlag = 1;
		}else if(strcmp(argv[i],"-o")==0){
			fout = fopen(argv[++i], "w");
			outputFlag = 1;
		}else if(strcmp(argv[i],"-h")==0){
			hashFlag = 1;
		}
	}
	while((operation=getc(fin))!=EOF){
		switch(operation){
			case 'A':{
				long int id;
				char side;
				char *symbol;
				int quantity;
				double price;
				order *p = (order*)malloc(sizeof(order));
				fscanf(fin, "%ld %c %s %d %lf", &id, &side, symbol, &quantity, &price);
				newOrder(&head, &tail, id, side, symbol, quantity, price);
				break;
			}
			case 'X':{
				long int id;
				char *symbol;
				fscanf(fin, "%ld %s", &id, symbol);
				order *p = searchOrder(&head, id);
				deleteOrder(&head, &tail, p);
				break;
			}
			case 'C':{
				long int id;
				char *symbol;
				int quantity;
				fscanf(fin, "%ld %s %d", &id, symbol, &quantity);
				order *p;
				p = searchOrder(&head, id);
				p -> quantity -= quantity;
				break;
			}
			case 'T':{	
				long int id;
				char *symbol;
				int quantity;
				fscanf(fin, "%ld %s %d", &id, symbol, &quantity);
				order *p;
				p = searchOrder(&head, id);
				p -> quantity -= quanity;
			}
			case 'R':{
				long int id;
				char *symbol;
				int quantity;
				double price;
				fscanf(fin, "%ld %s %d %lf", %id, symbol, &quantity, &price);
				setQuantity(&head, id, quantity);
				setPrice(&head, id, price);
			}
		}
	}
	if(hashFlag){
		
	}else{
		printOrder(fout, &head);
	}
}













