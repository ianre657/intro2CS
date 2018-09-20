#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int a[],int size);
int binary_search(int b[],int size,int key);
void randomgenerator(int c[],int number);

int main(void)
{
	  FILE *input_file,*inc_file,*dec_file;
      int select_input;
      int number;//record the number of array
      char file_name[128];//record input filename
      int i;
      int data[1000];
      for(int i=0;i<1000;i++)
          data[i]=0;

	  printf("Please select the way to read a set of integers.\n");
	  printf("1: random numbers; 2: read integers from a text file.\n");
	  scanf("%d",&select_input);

	  if(select_input==1)//random number
	  {
	  	printf("How many number of integers do you want to input?\n");
	  	scanf("%d",&number);
	  	randomgenerator(data,number);
	  }
	  else if(select_input==2)
	  {
	  	printf("please specify the filename you want to open and read.\n");
	  	scanf("%s",&file_name);
	  	if((input_file=fopen(file_name,"r"))==NULL)
	  	{
	  		printf("Error opening file!\n");
	  		return 0;
		}
		fscanf(input_file,"%d",&number);
		for(i=0;i<number;i++)
	    {
	        fscanf(input_file,"%d",&data[i]);
		}
		printf("All integers in file %s have been read.\n",file_name);
	  }

	  bubble_sort(data,number);//sort the input number
	  while(getchar()!='\n')
      {}

	  char mode;

	  while(1)
	  {
	  	printf("Specify the operation you want to do.\n");
		printf("i: print integers in increasing order.\n");
		printf("d: print integers in decreasing order.\n");
		printf("b: perform a binay search.\n");
		printf("q: Quit the program.\n");
		scanf("%c",&mode);
		while(getchar()!='\n')
        {}
		switch(mode)
        {
      	    case 'i':
                if((inc_file=fopen("IncSort","w"))==NULL)
      		    {
      			    printf("Error opening file!\n");
      			    return 0;
			    }
			    fprintf(inc_file,"%d\n",number);
			    for(i=0;i<number;i++)
			    {
				    fprintf(inc_file,"%d\n",data[i]);
			    }
			    fclose(inc_file);
			    break;
		    case 'd':
			    if((dec_file=fopen("DecSort","w"))==NULL)
			    {
				    printf("Error opening file!\n");
				    return 0;
			    }
			    fprintf(dec_file,"%d\n",number);
			    for(i=number-1;i>=0;i--)
			    {
				    fprintf(dec_file,"%d\n",data[i]);
			    }
			    fclose(dec_file);
			    break;
		    case 'b':
		        printf("Input an integer for search:");
			    int key,index;
			    scanf("%d",&key);
			    getchar();
				index=binary_search(data,number,key);
			    if(index==-1)
			        printf("The number %d is not in the integer list.\n",key);
			    else
			        printf("The number %d is in array[%d].\n",key,index);
				break;
		    case 'q':
			    return 0;
			    break;
		    default:
			    printf("Input error!\n");
	    }
    }
    return 0;
}

void bubble_sort(int a[],int size)
{
     int temp;
     for(int i=0;i<size-1;i++)
     {
         for(int j=0;j<size-1-i;j++)
         {
             if(a[j]>a[j+1])
             {
                 temp=a[j];
                 a[j]=a[j+1];
                 a[j+1]=temp;
             }
         }
     }
}

int binary_search(int b[],int size,int search)
{
    int low=0;
    int high=size-1;
    while(low<=high)
    {
        int mid = (low + high)/2;

        if(b[mid]==search)
        {
            return mid;
        }
        else if(b[mid]>search)
        {
            high = mid-1;
        }
        else if(b[mid]<search)
        {
            low = mid+1;
        }
    }
    return -1;
}

void randomgenerator(int c[],int number)
{
      time_t now;
      time(&now);
      //printf("Now time is %s.\n",asctime(localtime(&now)));//print the system time
      srand(time(NULL));
      for(int i=0;i<number;i++)
      {
             c[i]=(rand()%10000);
      }
      printf("%d integers have been generated.\n",number);
}

