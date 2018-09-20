#include <stdio.h>

#define NONE "\033[m"
#define RED "\033[0;32;31m" 
#define DARY_GRAY "\033[1;30m"
int main()
{ 
    int i,m,n,q; 
    int year, month, temp, first_space, feb_days; 
    
    printf("Please input the month and year of the calendar you want to printf.\n");
    printf("Month:");
	scanf("%d",&month);
       
    printf("\nYear:");
    scanf("%d",&year);
    
    
    if(month <= 12 && month >= 1){
    	for(first_space = 1,q = 0; q < (year - 1900); q ++){
    		if(q % 4 == 0 && q % 100 != 0 || q % 400 == 100)
    			first_space = (first_space + 366) % 7;
    		else
    			first_space = (first_space + 365) % 7;
    	}  
     
      //計算2月天數 
    	if(year % 4 == 0 && year % 100 != 0 || year % 400 == 0) 
        	feb_days =29;
    	else
       		feb_days =28;
    
     
    int space[13]={0,first_space,0,0,0,0,0,0,0,0,0,0,0};   
    int days[13]={0,31,feb_days,31,30,31,30,31,31,30,31,30,31}; 
    


    for(i = 1; i < month; i ++)
    	space[i + 1] = (space[i]+days[i]) % 7;

    printf("\n\n %d/%d",month,year); 
    printf("      "RED"Sun"NONE"  Mon  Tue  Wed  Thu  Fri  "RED"Sat"NONE" \n   ");
    printf("        ");
    
    if(month == 1)
		days[i - 1] = 31;
		
    temp = days[i - 1] - space[i] + 1;
    for(m = 1; m <= space[i]; m ++)
        printf(" "DARY_GRAY"%4d"NONE"",temp ++);
              
    for(n = 1; n <= days[i]; n ++){    
        printf(" %4d",n);
          
        if(n % 7 == (7 - space[i]) % 7)
        	printf("\n           ");
    }
    
    for(i = 1;i < month + 1; i ++)
    	space[i+1]=(space[i]+days[i])%7;

    for(m = 1; m <= 7 - space[i]; m ++){
    	if(space[i] == 0){
    		break;
		}
    	printf(" "DARY_GRAY"%4d"NONE"",m);
	}
        
           
    printf("\n");
    } 
     return 0;
     
} 
