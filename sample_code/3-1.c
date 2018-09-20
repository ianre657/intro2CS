#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GAR_SZ 10
int main(void)
{
    int num1,num2,i;
    char garbage[GAR_SZ];
    while(1)
    {
        for(i=0;i<GAR_SZ;i++)
            garbage[i]='\0';
        system("clear");
        printf("Please input two numbers: ");
        int legal=scanf("%d %d",&num1,&num2);
        printf("The legal number of inputs are %d.\n",legal);
        if(legal!=2)
        {
            if( getchar() == '\n' )
                printf("#\n");
            printf("We do not receive two integers.\n");
            scanf("%[^\n]s",garbage); //clear the input buffer
            getchar();
            // size of garbage is a problem
            //printf("Size of garbage : %lu\n", strlen(garbage) ); 
            printf("The garbage in keyboard buffer is \"%s\". We just removed them from the buffer.\n",garbage);
        }
        else
        {
            if(scanf("%[^\n]s",garbage)!=0)
            {

                printf("Although we got two integers. You also input some non-numerical characters.\n");
                printf("The garbage in keyboard buffer is \"%s\". We just removed them from the buffer.\n",garbage);
                getchar();
            }
            else
            {
                printf("Your input is completely correct!!!.\n");
                getchar();
            }
        }
        printf("Press any key to continue!\n");
        getchar();
    }
    return 0;
}

