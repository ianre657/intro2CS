#include <stdio.h>
#define MAX_SZ 20000


int coin_calculate(  int );
int main(void){


	int money[MAX_SZ], in = 0  ;
	scanf("%d",&in);
	if( in > MAX_SZ ){ printf("inputs exceed array size!\n"); return 0 ; }

	for( int i = 0 ; i < in ; i++){                                                    
		scanf("%d", &money[i]);
		printf("%d\n", coin_calculate( money[i] ) );
	}


	return 0 ;
}
int coin_calculate( int m ){
	int c1=0, c5=0, c10=0, c50=0 ;                                     
	int remain  = 0 ;
	
	c50 = m / 50 ;
	remain = m - 50 * c50; 
	c10 = remain / 10 ;
	remain = remain - 10 * c10;
	c5 = remain / 5;
	remain = remain - 5 * c5;
	c1 = remain / 1 ;
	
	return c1 + c5 + c10 + c50;
}
