#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
int main(void)
{
    char input;
    int flag;//1:the input character is not a digit
    int count;//the number of input digits
    int i,j,e;
    while(1)
    {
        char c[256]={0};//input character,garbage
        char in[256]={0};//input digits
        system("clear");
        flag=0,count=0,i=0,j=0,e=0;
        printf("Please input one integer: ");
        while((input=getchar())!='\n')
        {
	        e=1;
            if(isdigit(input)&&flag==0)
            {
                in[i++]=input;
                count++;
            }
            else
            {
                flag=1;
                c[j++]=input;
                if(count==0)
                {
                   printf("Your input does not begin with a numerical character.\n");
                   while(getchar()!='\n')
                   {}
                   break;
                }
            }
        }
        if(flag==0&&e!=0)
        {
            printf("The input integer is %s. \nYour input is correct.\n",in);
        }
        else if(flag!=0&&count!=0)
        {
            printf("The input integer is %s. \n",in);
            printf("Although we got one integer from your input. your input contains non-numerical characters.\n");
            printf("The garbage in your input is \"%s\".\n",c);
        }
        printf("Press any key to continue!\n");
        scanf("%*[^\n]s");getchar();
        //getchar();
    }
    return 0;
}


