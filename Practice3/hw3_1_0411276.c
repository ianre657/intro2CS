#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
#define GAR_SIZ  10

int main(void){

	int in = 0 ;
	int num[2];
	int i = 0 ; 

	CLEAR();
	while(1){
		printf("Please input two numbers :");
		in = scanf("%d%d", &num[0],&num[1]);
		printf("\nThe legal number of inputs are %d\n",in);
		printf("%s\n", (in==2)? "Your input is completely correct!" : "We do not receive two numbers.");

			// siz 1 make the control in if-else statement more sence.
			// siz 12 is reserved for "...(deleted)"
		char garbage[GAR_SIZ+1+12] ;
		short newLineFd  ;
		
		garbage[0] = '\0';
		newLineFd = 0 ;
		i = 0 ;
		while(1){
			garbage[i] = getchar();
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
		
		if( in==2  && strlen(garbage)!= 0 )
			printf("Although we got two integers. You also input some non-numerical characters.\n");
		if ( strlen(garbage)!= 0 )
			printf("The garbage in input buffer is \"%s\". We just removed them from the buffer.\n", garbage);
		
		printf("Press Enter to continue!"); fflush(stdout);
		scanf("%*[^\n]s"); getchar();

		CLEAR();
	}

	return 0 ;
}
