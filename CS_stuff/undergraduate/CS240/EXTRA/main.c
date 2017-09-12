#include<stdio.h>
#include<string.h>
#include<stdlib.h>


struct sea_animal {
  char name[20];
  int age;
  double weight;
  void (*eat)(struct sea_animal*);
  void (*swim)(struct sea_animal*, int);
};

void readline(char c[]) { // read a line of text from stdin to char array c 
  int i=0;
  while((c[i++]=getchar())!='\n');
  c[i-1]='\0';
}
void shark_eat(struct sea_animal* this) {
  this->weight *= 1.01;
  this->weight = (this->weight>2000)?2000:this->weight;
  printf("%s happliy ate %.2f pounds of food. ", this->name, 0.1*(this->weight));
  printf("Its weight is now %.2f pounds.\n", this->weight);
}
void shark_swim(struct sea_animal* this, int hours) {
  double distance = 10*this->age*(1000/this->weight)*hours;
  printf("%s happily swam %.2f miles.\n", this->name, distance);
}
void whale_eat(struct sea_animal* this) {
  this->weight *= 1.05;
  this->weight = (this->weight>400000)?400000:this->weight;
  printf("%s happliy ate %.2f pounds of food. ", this->name, 0.05*(this->weight));
  printf("Its weight is now %.2f pounds.\n", this->weight);
}
void whale_swim(struct sea_animal* this, int hours) {
  double distance = 3*this->age*(200000/this->weight)*hours;
  printf("%s happily swam %.2f miles.\n", this->name, distance);
}

struct sea_animal* whale_new(char* name, int age, double weight) {
  struct sea_animal* new;
  if((new = (struct sea_animal*)malloc(sizeof(struct sea_animal)))==NULL)
    return NULL;
  strcpy(new->name, name);
  new->age = age;
  new->weight = weight;
  new->eat = whale_eat;
  new->swim = whale_swim;
  return new;
}
struct sea_animal* shark_new(char* name, int age, double weight) {
  struct sea_animal* new;
  if((new=(struct sea_animal*)malloc(sizeof(struct sea_animal)))==NULL)
    return NULL;
  strcpy(new->name, name);
  new->age = age;
  new->weight = weight;
  new->eat = shark_eat;
  new->swim = shark_swim;
  return new;
}

int main() {
  struct sea_animal* new;
  char type;
  char name[20];
  int age;
  double weight;
  char ageChar[20];
  char weightChar[20];
  char choice;
  char hour[20];
  
  printf("Create your new pet, whale or shark? (w/s): ");
  readline(&type);
  printf("Pet's name: ");
  readline(name);
  printf("Age: ");
  readline(ageChar);
  age=atoi(ageChar);
  printf("Weight: ");
  readline(weightChar);
  weight=atof(weightChar);

  if(type=='w')
    new=whale_new(name,age,weight);
  else
    new=shark_new(name,age,weight);
  printf("Pet created!");
  while(1){
    printf("\nHave fun with your new pet %s:\n",new->name);
    printf("1. Feed\n2. Walk\n3. Play later\n\nInput: ");
    readline(&choice);
      if(choice=='1')
        (*(new->eat))(new);
      else if(choice=='2'){
        printf("For how many hours?: ");
        readline(hour);
        (*(new->swim))(new, atoi(hour));
      }
      else{
        printf("Quit.\n");
        exit(0);
      }
  }
}



