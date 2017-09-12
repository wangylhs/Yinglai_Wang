#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct sea_animal{
	char name[20];
	int age;
	double weight;
	void (*eat)(struct sea_animal*);
	void (*swim)(struct sea_animal*, int);
};

void readline(char c[]){
	int i=0;
	while((c[i++]=getchar())!='\n');
		c[i-1]='\0';
}

void shark_eat(struct sea_animal *this){
    double food = (this -> weight)*0.1;
	this -> weight += (this -> weight)*0.01;
	if(this -> weight > 2000){
		this -> weight = 2000;
	}
	printf("%s happily ate %.2f pounds of food. Its weight is now %.2f pounds.\n\n", this -> name, food, this -> weight);
}

void whale_eat(struct sea_animal *this){
    double food = (this -> weight)*0.05;
	this -> weight += (this -> weight)*0.05;
	if(this -> weight > 400000){
		this -> weight = 400000;
	}
	printf("%s happily ate %.2f pounds of food. Its weight is now %.2f pounds.\n\n", this -> name, food, this -> weight);
}

void shark_swim(struct sea_animal *this, int time){
	double mile;
	mile = (this -> age)*10*(1000/(this -> weight))*time;
	printf("%s happily swam %.2f miles.\n\n", this -> name, mile);
}

void whale_swim(struct sea_animal *this, int time){
	double mile;
	mile = (this -> age)*3*(200000/(this ->weight))*time;
	printf("%s happily swam %2.f miles.\n\n", this -> name, mile);
}

struct sea_animal* whale_new(char *name, int age, double weight){
	struct sea_animal *whale;
	whale = (struct sea_animal*)malloc(sizeof(struct sea_animal));
	strcpy(whale -> name, name);
	whale -> age = age;
	whale -> weight = weight;
	whale -> eat = whale_eat;
	whale -> swim = whale_swim;
	return whale;
}

struct sea_animal* shark_new(char *name, int age, double weight){
	struct sea_animal *shark;
	shark = (struct sea_animal*)malloc(sizeof(struct sea_animal));
	strcpy(shark -> name, name);
	shark -> age = age;
	shark -> weight = weight;
	shark -> eat = shark_eat;
	shark -> swim = shark_swim;
	return shark;
}

int main(){
	struct sea_animal *p;
	char pet;
	char name[20];
	char inputage[10];
	char inputweight[10];
	char inputtime[10];
	int age;
	double weight;
	char action;
	int time;

	printf("Create your new pet, whale or shark? (w/s): ");
	readline(&pet);
	printf("Pet's name: ");
	readline(name);
	printf("Age: ");
	readline(inputage);
	printf("Weight: ");
	readline(inputweight);
	age = atoi(inputage);
	weight = atof(inputweight);
	if(pet == 'w'){
		p = whale_new(name, age, weight);
	}else if(pet == 's'){
		p = shark_new(name, age, weight);
	}else{
		printf("Pet does not exist!");
	}
	printf("Pet created!\n");
	while(1){
		printf("Have fun with your new pet %s: \n", p -> name);
		printf("1. Feed \n2. Walk \n3. Play later\n");
		printf("\nInput: ");
		readline(&action);
		switch(action){
			case '1':{
				(*(p -> eat))(p);
				break;
			}
			case '2':{
				printf("For how many hours?: ");
				readline(inputtime);
				time = atoi(inputtime);
				(*(p -> swim))(p, time);
                break;
			}
			case '3':{
				printf("Quit. \n");
				exit(0);
			}
		}
	}
}

