#include<stdio.h> 

char msg[141]; 
int c;
int count=0;
int i; 

int main(){
	msg[140] = '\0';
	
	while( (c=getchar())!=EOF){
		msg[count]=c;
		if(count == 140){
			break;
		}
		count++;
	}
	
	for(i=count;i>=0;i--){
		if(msg[i]=='@')
		{
			int j = i-1;
			while(	msg[j] >='A' && msg[j] <='Z' ||
				msg[j] >='a' && msg[j] <='z' ||
				msg[j] >='0' && msg[j] <='9') 
			{
				msg[j] = 'X';
				j--;
			}
		}
	}
	
	int k;
	for(k=0;k<count;k++)
	{
		printf("%c", msg[k]);
	}
	
}
