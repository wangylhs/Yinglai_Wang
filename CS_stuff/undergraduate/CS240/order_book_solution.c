#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************Start Hash Structure Definitions***************************/

/**/
#ifndef HASH_MAP_SIZE
	#define HASH_MAP_SIZE 100
#endif

/* enum for Side*/
typedef enum o_side { BUY, SELL} OrderSide;


/* OrderNode - Node to be inserted in the hash structure */
typedef struct onode {
	int id;
	OrderSide side; 
	int quantity;
	double price;
	struct onode *prev;
	struct onode *next;
} OrderNode;


/******************************************Start Input Definitions******************************/

/* 
 * enum for input type
 * BIN: Input is Binary
 * ASCII: Input is ASCII
 */
typedef enum i_type { BIN, ASCII } InputType;

/* struct to catch input*/
typedef struct order {
	int id;
	OrderSide side;
	int quantity;
    double price;
} Order;

/* 
 * enum to distinguish between both struct types 
 * HMAP: Struct for hashmap
 * LL: Struct for linked list implementation
 */
typedef enum s_type { LL, HMAP } StructType;

//End Binary Definitions


/*********************************Start Function implementations**********************************/

/*
 * proc_scmdline - Processes the command line
 * argc - number of arguments
 * argv - arguments passed to the program command line
 * i_t - capture the input type
 * s_t - hashmap implementation or linked list
 * in - input file
 * out - output file
 */
void proc_cmdline(int argc, char *argv[], InputType *i_t, StructType *s_t, FILE **in, FILE **out) {
	for (int i=1; i < argc; i++) {
		if (!strcmp(argv[i], "-b")) {
			*i_t = BIN;
		} else if (!strcmp(argv[i], "-h")) {
			*s_t = HMAP;
		} else if (!strcmp(argv[i], "-i")) {
			i++;
			if ((*in = fopen(argv[i], "r")) == NULL) {
				fprintf(stderr, "Unabled to open input file named %s\n", argv[i]);
				exit(0);
			}
		} else if (!strcmp(argv[i], "-o")) {
			i++;	
			if ((*out = fopen(argv[i], "w")) == NULL) {
				fprintf(stderr, "Unabled to open output file named %s\n", argv[i]);
				exit(0);
			}
		} else {
			fprintf(stderr, "Unexpected input flag %s\n", argv[i]);
		}
	}	
}


/*******************************Start Linked List implementation***********************************/

/*
 * add_order_LL - add order to linked list
 * head - head of the linked list
 * data - node data
 */
void add_order_LL(OrderNode **head, OrderNode *data) {
	if (*head == NULL) { //Empty list
		*head = (OrderNode*) malloc(sizeof(OrderNode));
		(*head)->id = data->id;
		(*head)->side = data->side;
		(*head)->quantity = data->quantity;
		(*head)->price = data->price;
		(*head)->next = NULL;
		(*head)->prev = NULL;
	} else { //Non Empty list
		OrderNode *tmp;
		tmp = (OrderNode*) malloc(sizeof(OrderNode));
		tmp->id = data->id;
		tmp->side = data->side;
		tmp->quantity = data->quantity;
		tmp->price = data->price;
		tmp->next = *head;
		tmp->prev = NULL;
		(*head)->prev = tmp;
		*head = tmp;	
	}
}

/*
 * cancel_order_LL - cancel order from linked list
 * head - head of the linked list
 * data - node data
 */
void cancel_order_LL(OrderNode **head, OrderNode *data) {
	OrderNode *cur = *head;
	// find the location of the node to cancel
	while (cur != NULL && (cur->id != data->id)) 
		cur = cur->next;

	// delete node after finding its location
	if (cur != NULL) {
		if (cur == *head) { //curr is head, we should assign a new head
			*head = cur->next;
			(*head)->prev = NULL;
		} else { // cur isn't head node
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
		}
		//free the memory location
		free(cur);
	}	
}

/*
 * reduce_quantity_LL - reduce quantity in a linked list
 * head - head of the linked list
 * data - node data
 */
void reduce_quantity_LL(OrderNode *head, OrderNode *data) {
	OrderNode *cur = head;
	
	// find the location of the node to be updated
    while (cur != NULL && (cur->id != data->id)) 
		cur = cur->next;

	// reduce quantity 
    if (cur != NULL) 
		cur->quantity = cur->quantity - data->quantity;
}

/*
 * change_order_LL - change the date of an order
 * head - head of the linked list
 * data - node data
 */
void change_order_LL(OrderNode *head, OrderNode *data) {
	OrderNode *cur = head;
    // find the location of the node to cancel
    while (cur != NULL && (cur->id != data->id))
    	cur = cur->next;
 
    // change order 
    if (cur != NULL) {
	    cur->quantity = data->quantity;
		cur->price = data->price;
	}
}

/*
 * proc_mesgs_LL - Process a file into a linked list
 * in_type - Tyoe of input (ASCII Vs Binary)
 * head - head of the linked list
 * in - inputfile
 */
void proc_mesgs_LL(InputType in_type, OrderNode** head, FILE *in) {
	char msg_type; //char to hold the operation type
    char side;     // sell Vs Buy
	OrderNode in_data;

	if (in_type == ASCII) {
        while (fscanf(in, "%c", &msg_type) != EOF) { //While not EOF
            // process data
            switch (msg_type) {
                case 'A':
					fscanf(in, "%d %c SPY %d %lf\n", &(in_data.id), &side, &(in_data.quantity),
							&(in_data.price));
					(side == 'B') ? (in_data.side = BUY) :  (in_data.side = SELL);
                    add_order_LL(head, &in_data);
                break;
                case 'X':
					fscanf(in, "%d SPY\n", &(in_data.id));
                    cancel_order_LL(head, &in_data);
                break;
                case 'T':  //Same as Case 'T'
                case 'C':
					fscanf(in, "%d SPY %d\n", &(in_data.id), &(in_data.quantity));
                    reduce_quantity_LL(*head, &in_data);
                break;
                case 'R':
					fscanf(in, "%d SPY %d %lf\n", &(in_data.id), &(in_data.quantity), &(in_data.price));
                    change_order_LL(*head, &in_data);
                break;
                default: //If we reach here, then we got wrong input
                    fprintf(stderr, "Unknown message type, %c, ignoring message\n", msg_type);
                break;
            }
        }
	} else { //in_type == binary
		fprintf(stderr, "Binary data not handled yet\n");	
	}
}


/*
 * print_orderbook_LL - Print the order book
 * head - head of the linked list
 * out - outputfile
 */
void print_orderbook_LL(OrderNode *head, FILE *out) {
	OrderNode *cur = head;
	while (cur != NULL) { //loop on the list starting from head
		fprintf(out, "%d %c %d %f\n", 
				cur->id, 
				(cur->side == BUY) ? 'B' : 'S', 
				cur->quantity, 
				cur->price);
		cur = cur->next;
	}
}

/*
 * free_LL - free the entire list
 * head - head of the linked list
 */
void free_LL(OrderNode **head) {
	OrderNode *last, *cur = *head;
	while (cur != NULL) { //loop on the list starting from head
		last = cur;
		cur = cur->next;
		//free the node
		free(last);
	}
}

//End Linked List Implementation

/*******************************Start Hashtable implementation***********************************/
/*
 * hash - Hash function
 * order_id - The id to be inserted in the hash
 */
int hash(int order_id) {
	return order_id % HASH_MAP_SIZE;
}

/*
 * init_HM - Initialize the hash structure
 * ob - array of linked list to be used in the hashtable
 */
void init_HM(OrderNode **ob) {
	// initialize array to NULL
	for (int i=0;i < HASH_MAP_SIZE;i++)
		ob[i] = NULL;
}

/*
 * add_order_HM - Add a node to the hashtable
 * oreder_book - array of linked list to be used in the hashtable
 * data - data node to be added to the hash
 */
void add_order_HM(OrderNode **order_book, OrderNode *data) {
	int hash_index = hash(data->id);
	OrderNode *tmp = (OrderNode*) malloc(sizeof(OrderNode));
	//Copy data into the newly allocated using memcpy
	memcpy(tmp, data, sizeof(OrderNode));
	tmp->prev = NULL;
	
	if (order_book[hash_index] == NULL) {// new chain
		tmp->next = NULL;
		order_book[hash_index] = tmp;
	} else { // insert in front of chain 
		tmp->next = order_book[hash_index];
		order_book[hash_index]->prev = tmp;
		order_book[hash_index] = tmp;
	}
}

/*
 * cancel_order_HM - cancel order from Hash
 * oreder_book - array of linked list to be used in the hashtable
 * data - data node to be canceled to the hash
 */
void cancel_order_HM(OrderNode **order_book, OrderNode *data) {
	int hash_index = hash(data->id);
	OrderNode *cur = order_book[hash_index];

	//search for matching id and remove from chain
	while(cur != NULL) {
		if (cur->id != data->id)
			cur = cur->next;
		else { // match found
			// head node
			if (cur == order_book[hash_index]) {
				order_book[hash_index] = cur->next;
				if (order_book[hash_index])
					order_book[hash_index]->prev = NULL;
				free(cur);
			} else { //middle or tail node
				cur->prev->next = cur->next;
				if (cur->next) //if not tail
					cur->next->prev = cur->prev;
				//Free the node
				free(cur);
			}
			cur = NULL;
		}
	}
}

/*
 * reduce_quantity_HM - reduce quantity order from Hash
 * oreder_book - array of linked list to be used in the hashtable
 * data - data node to be canceled to the hash
 */
void  reduce_quantity_HM(OrderNode **order_book, OrderNode *data) {
	int hash_index = hash(data->id);
	OrderNode *cur = order_book[hash_index];

	//search for matching id and remove from chain
	while(cur != NULL) {
		if (cur->id != data->id)
			cur = cur->next;
		else { // match found
			cur->quantity = cur->quantity - data->quantity;
			cur = NULL;
		}
	}
}

/*
 * change_order_HM - change order data from Hash
 * oreder_book - array of linked list to be used in the hashtable
 * data - data node to be canceled to the hash
 */
void change_order_HM(OrderNode **order_book, OrderNode *data) {
	int hash_index = hash(data->id);
	OrderNode *cur = order_book[hash_index];

	//search for matching id and remove from chain
	while(cur != NULL) {
		if (cur->id != data->id)
			cur = cur->next;
		else { // match found
			cur->quantity = data->quantity;
			cur->price = data->price;
			cur = NULL;
		}
	}
}

/*
 * proc_mesgs_HM - Process file for hashmap implementation
 * oreder_book - array of linked list to be used in the hashtable
 * in - inputfile
 */
void proc_mesgs_HM(InputType in_type, OrderNode **order_book, FILE *in) {
	char msg_type;
        char side;
	OrderNode in_data;

	if (in_type == ASCII) {
        while (fscanf(in, "%c", &msg_type) != EOF) {
            // process data
            switch (msg_type) {
            	case 'A':
					fscanf(in, "%d %c SPY %d %lf\n", &(in_data.id), &side, &(in_data.quantity), 
							&(in_data.price));
					(side == 'B') ? (in_data.side = BUY) :  (in_data.side = SELL);
                    add_order_HM(order_book, &in_data);
                break;
                case 'X':
					fscanf(in, "%d SPY\n", &(in_data.id));
                    cancel_order_HM(order_book, &in_data);
                break;
                case 'T': //Same as C
                case 'C':
					fscanf(in, "%d SPY %d\n", &(in_data.id), &(in_data.quantity));
                    reduce_quantity_HM(order_book, &in_data);
                break;
                case 'R':
					fscanf(in, "%d SPY %d %lf\n", &(in_data.id), &(in_data.quantity), 
							&(in_data.price));
                    change_order_HM(order_book, &in_data);
                break;
                default:
                	fprintf(stderr, "Unknown message type, %c, ignoring message\n", msg_type);
                break;
            }
        }
	} else { //in_type == binary
		fprintf(stderr, "Binary data not handled yet\n");	
	}
}

/*
 * print_orderbook_HM - Print orderbook stored in hashtable
 * ob - array of linked list to be used in the hashtable
 * output - outputfile
 */
void print_orderbook_HM(OrderNode **ob, FILE *output) {
    for(int i=0; i < HASH_MAP_SIZE; i++) {
        OrderNode *cur = ob[i];        
        while(cur != NULL) {
			fprintf(output, "%d %c %d %f\n", cur->id, 
					 	(cur->side==BUY) ? 'B':'S',
					 	cur->quantity, cur->price);
        	cur = cur->next;
        }
    }
}

/*
 * free_HM - Free order book stored as a hash
 * ob - array of linked list to be used in the hashtable
 */
void free_HM(OrderNode **ob) {
	for(int i=0; i < HASH_MAP_SIZE; i++) {
		OrderNode *tmp, *cur = ob[i];		
		while(cur != NULL) {
			tmp = cur;
			cur = cur->next;
			free(tmp);
		}
	}
}

//End of hashtable implementation


/**********************************Main Implementation******************************************/
int main(int argc, char *argv[]) {
	char c;
	InputType in_type = ASCII;
	StructType struct_type = LL;
	FILE *input = stdin;
	FILE *output = stdout;

	//Process the commandline
	proc_cmdline(argc, argv, &in_type, &struct_type, &input, &output);

	if ( struct_type == LL ) { //linked list
		OrderNode *order_book = NULL;
		//process input
		proc_mesgs_LL(in_type, &order_book, input);
		//print the order_book
		print_orderbook_LL(order_book, output);
		//free data
		free_LL(&order_book);
	} else { // struct_type == hash map	
	    //create the hash array
		OrderNode *order_book[HASH_MAP_SIZE];
		//initialize the hashtable
		init_HM(order_book);
		//process the input
		proc_mesgs_HM(in_type, order_book, input); 
		//print the order_book
		print_orderbook_HM(order_book, output);
		//free data
		free_HM(order_book);
	}
		
	return 0;
}
