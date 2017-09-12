nclude<stdio.h>
  extern int isAlpha(char);
  testIsAlpha() {
     if(isAlpha(’a’)==0) printf("Error a is alpha\n");
     if(isAlpha(’Z’)==0) printf("Error Z is alpha\n");
     // more cases ...
}
  int main(){
    testIsAlpha();
    // add other tests here
}
