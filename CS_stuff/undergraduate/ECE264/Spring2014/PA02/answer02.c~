#include <stdio.h>
#include "answer02.h"

size_t my_strlen(const  char * str){
	size_t n = 0;
	int i = 0;
	if(str == NULL){
		printf("error -- undefined behavior.\n");
	}else{
		while(str[i] != '\0'){
			i++;
			n++;
		}
	}
	return n;
}

int my_countchar(const char * str, char ch){
	int n = 0;
	int i = 0;
	for(i = 0; i < my_strlen(str); i++){
		if(str[i] == ch){
			n++;
		}
	}
	return n;
}

char * my_strchr(const char * str, int ch){
	if(ch == '\0'){
		return (char*)(str + my_strlen(str));
	}
	while(*str){
		if(*str == ch)
		{
			return (char*)str;
		}
		str++;
	}
	return NULL;
}

char * my_strrchr(const char * str, int ch){
	if(ch == '\0'){
		return (char*)(str + my_strlen(str));
	}
	const char *end = str + my_strlen(str);
	while(end >= str){
		if(*end == ch){
			return (char*)end;	
		}
		end --;
	}
	return NULL;
}


char * my_strstr(const char * haystack, const char * needle){
	if(*needle == '\0'){
		return (char*)haystack;
	}
	while(*haystack != '\0'){
		const char * ch = haystack;
		while(*ch == *needle && *ch != '\0' && *needle != '\0'){
			ch++;
			needle++;		
		}
		if(*needle == '\0'){
			return (char*)haystack;
		}
		haystack++;
	}
	return NULL;
	
}

char * my_strcpy(char * dest, const char * src){
	int len = my_strlen(src);
	int i = 0;	
	for(i = 0; i <= len; i++){
		dest[i] = src[i];	
	}
	return dest;
}

char * my_strcat(char * dest, const char * src){
	my_strcpy((dest + my_strlen((char*)dest)), src);
	return dest;
}

int my_isspace(int ch){
	if(ch == 9 || ch == 10 || ch == 11 || ch == 12 || ch == 13 || ch == 32){
		return 1;	
	}else{
		return 0;	
	}
}

int my_atoi(const char * str){	
	int sign = 1;
	int ret = 0;	
	while( *str != '\0'){
		if(*str == '-'){
			sign = -1;		
		}
		if('0' <= *str && *str <= '9'){
			ret *= 10;
			ret += *str - '0';			
		}
		str++;
	}
	return sign*ret;
	
}


/*int main(int argc, char * * argv){
	//printf("%zd\n",my_strlen("kl;asjudhfkljasgeofp;iuhw;EFCH"));	
	//printf("%zd\n",my_strlen(""));
	//char * str = "Hello ";
	//char buff[50];
	//printf("%s\n", my_strcpy(buff,str));
	//printf("%s\n", my_strcat(str,"World!"));
	printf("%d\n", my_atoi("\n\f\t\v\r 6 white space characters handled correctly."));
	char buffer[50];
  	my_strcpy(buffer, "Hello ");
 	printf("%s\n", my_strcat(buffer, "Zippy!")); // prints "Hello Zippy!"
		
	//return EXIT_SUCCESS;
}
*/
