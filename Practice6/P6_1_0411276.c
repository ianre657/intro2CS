#include<stdio.h>

// long long int would overflow over   n = 90+ in Fibinacci series sum;   
#define MAX 90

// RECUR_VER  or  ITER_VER 
#define RECUR_VER

#ifdef	RECUR_VER
long long int fibonacci( int i );
#endif

int max_day = 2  ; 
long long int chen[MAX+1] = { [1] = 1, [2] = 1};
long long int chen_sum( int day);

int wu_sum( int day ){ return day* 11200; };
int main(void){
	int day = 0 , n = 0  ;
	int in = 0 ;

	printf("\nHow many data you want to input?"); fflush(stdout);
	scanf("%d", &n );
	for( int i = 1 ; i <= n ; i++ ){
		printf("Input day: ");
		in = scanf("%d",&day);
		if( in == 0 ){
			printf("Invalid input\n"); while( getchar()!='\n' );
		}else{
			if( day <= MAX ){
				long long int c_sum = 0 ;
				int w_sum =0 ;
				c_sum = chen_sum(day); w_sum = wu_sum(day);
				printf("%c\n", c_sum > w_sum ? 'c' : (  c_sum < w_sum ? 'w':'e' )  );
				//printf(" On day %d:\n  TA Chen got %lld,\n  TA Wu   got %-19d  (in total)\n",day,c_sum,w_sum);
			}else
				printf("c\n");
		}
		 fflush(stdout);
	}
	return 0 ;
}

#ifdef	RECUR_VER
long long int fibonacci( int i ){
	if( i == 1 || i == 2 )
		return 1 ;
	else 
		return fibonacci(i-1) + fibonacci(i-2);
}
#endif

long long int chen_sum( int day ){
	long long int sum = 0 ;
	if( day >  max_day ){
		for( int i = max_day+1 ; i <= day; i++ ){
#ifdef ITER_VER 
			chen[i] = chen[i-1] + chen[i-2];
#endif
#ifdef RECUR_VER
			// Use hybird version instead to prevent too much delay
			if( i >= 46 )
				chen[i] = chen[i-1] + chen[i-2];
			else
				chen[i] = fibonacci(i);
#endif
		}
		max_day = day; 
	}
	for( int i = 1; i <= day ; i++ )
		sum += chen[i];
	return sum ; 
}
