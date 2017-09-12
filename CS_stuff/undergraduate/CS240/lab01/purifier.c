#include<stdio.h>

char msg[141];
int c, i, j;
int count=0;

int main()
{
	msg[140]='\0';
	while((c=getchar())!=EOF)
		{
			msg[count]=c;
			if(count==140)
			{
				break;
			}
			count++;
		}
	

	for(i=0;i<count;i++)
	{
		if((msg[i]=='d' && msg[i+1]=='a' && msg[i+2]=='r' && msg[i+3]=='n'))
		{	
			if((i==0) && ((msg[i+4]<'A' || msg[i+4]>'Z') && (msg[i+4]<'a' || msg[i+4]>'z')) )
			{
				msg[i]  ='X';
				msg[i+1]='X';
				msg[i+2]='X';
				msg[i+3]='X';
			}
			else if(((msg[i+4]<'A' || msg[i+4]>'Z') && (msg[i+4]<'a' || msg[i+4]>'z')) &&
			   ((msg[i-1]<'A' || msg[i-1]>'Z') && (msg[i-1]<'a' || msg[i-1]>'z')))
			{
				msg[i]  ='X';
				msg[i+1]='X';
				msg[i+2]='X';
				msg[i+3]='X';
			}

		}
		if((msg[i]=='f' && msg[i+1]=='o' && msg[i+2]=='o' && msg[i+3]=='l'))
		{	
			if((i==0) && ((msg[i+4]<'A' || msg[i+4]>'Z') && (msg[i+4]<'a' || msg[i+4]>'z')) )
			{
				msg[i]  ='X';
				msg[i+1]='X';
				msg[i+2]='X';
				msg[i+3]='X';
			}
			else if(((msg[i+4]<'A' || msg[i+4]>'Z') && (msg[i+4]<'a' || msg[i+4]>'z')) &&
			   ((msg[i-1]<'A' || msg[i-1]>'Z') && (msg[i-1]<'a' || msg[i-1]>'z')))
			{
				msg[i]  ='X';
				msg[i+1]='X';
				msg[i+2]='X';
				msg[i+3]='X';
			}

		}
			if((msg[i]=='h' && msg[i+1]=='e' && msg[i+2]=='l' && msg[i+3]=='l'))
		{	
			if((i==0) && ((msg[i+4]<'A' || msg[i+4]>'Z') && (msg[i+4]<'a' || msg[i+4]>'z')) )
			{
				msg[i]  ='X';
				msg[i+1]='X';
				msg[i+2]='X';
				msg[i+3]='X';
			}
			else if(((msg[i+4]<'A' || msg[i+4]>'Z') && (msg[i+4]<'a' || msg[i+4]>'z')) &&
			   ((msg[i-1]<'A' || msg[i-1]>'Z') && (msg[i-1]<'a' || msg[i-1]>'z')))
			{
				msg[i]  ='X';
				msg[i+1]='X';
				msg[i+2]='X';
				msg[i+3]='X';
			}

		}

	}
	
	for(j=0;j<count;j++)
	{
		printf("%c", msg[j]);
	}
}












/*		if(msg[i]=='f' && msg[i+1]=='o' && msg[i+2]=='o' && msg[i+3]=='l')
        {   
			if((msg[i+4]=='d' && msg[i+5]=='a' && msg[i+6]=='r' && msg[i+7]=='n')||
               (msg[i+4]=='f' && msg[i+5]=='o' && msg[i+6]=='o' && msg[i+7]=='l')||
               (msg[i+4]=='h' && msg[i+5]=='e' && msg[i+6]=='e' && msg[i+7]=='l'))
            {           
                int k;          
                for(k=i;k<i+8;k++)
                {               
                    msg[k]='X';         
                }               
            }
            if((msg[i+4]<'A' || msg[i+4]>'Z' g) && (msg[i+4]<'a' g || msg[i+4]>'z' g))
            {   
                msg[i]  ='X';
                msg[i+1]='X';
                msg[i+2]='X';
                msg[i+3]='X';
            }   
        }
		if(msg[i]=='h' && msg[i+1]=='e' && msg[i+2]=='l' && msg[i+3]=='l')
        {   
			if((msg[i+4]=='d' && msg[i+5]=='a' && msg[i+6]=='r' && msg[i+7]=='n')||
               (msg[i+4]=='f' && msg[i+5]=='o' && msg[i+6]=='o' && msg[i+7]=='l')||
               (msg[i+4]=='h' && msg[i+5]=='e' && msg[i+6]=='e' && msg[i+7]=='l'))
            {           
                int k;          
                for(k=i;k<i+8;k++)
                {               
                    msg[k]='X';         
                }               
            }
            if((msg[i+4]<'A' || msg[i+4]>'Z' g) && (msg[i+4]<'a' g || msg[i+4]>'z' g))
            {   
                msg[i]  ='X';
                msg[i+1]='X';
                msg[i+2]='X';
                msg[i+3]='X';
            }   
        }*/      

