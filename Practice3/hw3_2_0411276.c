#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

//Different Operating ststem need different system call
#ifdef __linux__
	#define CLEAR() system("clear")
#endif /* linux */

#ifdef _WIN32  /* _WIN32 is defined both in win32 and win64 system */ 
	#define CLEAR() system("cls")
#endif /* WIN32  */

#ifdef __APPLE__
	#define CLEAR() system("clear")
#endif /* Apple */

//define garbage buffer size 
#define GAR_SIZ  30
#define NUM_BFR_SIZ 100

unsigned long myPow10( const int );
int main(void){

	int numArray[ NUM_BFR_SIZ ];
	int i = 0 ; 

	CLEAR();
	while(1){
		printf("Please input one integer :");

		unsigned int nm_read = 0;
		short  input_remain=0  ;
		char ch ;
		for( i=0,nm_read=0 ; i <NUM_BFR_SIZ  ;/* empty*/ ){
			ch = getchar(); 
			if( isdigit(ch) ){
				++nm_read ;
				numArray[i] = atoi( &ch );
				i++;
			}else{
				input_remain=1; break; 
			}
		}
		/* If not begin with numericla number, restart to loop and ask again.*/
		if( nm_read == 0 ){
			/* Clear the keyboard buffer */
			while( getchar() != '\n');
			printf("Your input does not begin with a numerical number.\n");
			printf("Press any key to continue!\n");
			/* Asking for any key with enter*/
			while( getchar() != '\n');
			CLEAR();
			continue; 
		}

		/*	If the program runs after this line,
		 * 	this means user successfully input one number. 
		 */
		unsigned long num;
		for( i=nm_read-1, num=0 ; i>=0; i--){
			num+= numArray[i] * myPow10( nm_read-i-1 );
		}
		printf("The input integer is %lu\n", num);


			// siz 1 make the control in if-else statement more sence.
			// siz 12 is reserved for "...(deleted)"
		char garbage[GAR_SIZ+1+12] ;
		
		garbage[0] = '\0';
		short newLineFd = 0 ;
		i = 0 ;
		while(1){
			if( input_remain == 0  ){
				garbage[i] = getchar();
			}else{
				garbage[i] = ch ;
				input_remain = 0 ;
			}

			if( garbage[i] == '\n'){
				garbage[i] = '\0';
				newLineFd = 1; break; 
			}
			if( i >= GAR_SIZ  && newLineFd == 0 ){
				garbage[i] = '\0';
				char ch ; 
				// Clear garbage remained.
				while( (ch = getchar() ) != '\n')
					; 
				strncat( garbage, "...(deleted)", 12);
				
				break;
			}else
				i++;
		}
		if(  strlen(garbage)==0 ){
			printf("Your input is correct.\n");
		}else{
			printf("Although we got one integer from your input, your input contains  non-numerical characters.\n");
			printf("The garbage in your input is  \"%s\".\n", garbage);
		}
		
		printf("Press any key to continue!\n");
		while( getchar() != '\n' ) 
			;
		CLEAR();
	}

	return 0 ;
}

unsigned long myPow10( const int power ){
	int i; 
	unsigned long nm=1;
	for( i = power; i >0; i--){
		nm *= 10 ;
	}
	return nm;
}
