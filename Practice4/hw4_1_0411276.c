#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define BFR_SZ 100 
	// input size bigger than BFR_SZ would not be accept 
	// even if user input 4-digit numer and lots of whitespaces together 

void rand4( int[4], int[10 ]);
		//1 int[4] : integer array to store random 4-digits without repetition
		//2 int[10]: table to record the digit usage in the int array.
int  readIn( char* , const size_t ,int* , const size_t  );
		// Return number of digits  that have read in , return -1 while keyboard buffer exist illegal input.
		//1 char * : character array to read user input 
		//2 size_t : size of char array 
		//3 int*   : array to store integers
		//4 size_t : size of the integer array
int main(void){

	int hst_table[10], usr_table[10];// Host, User
	int hst4[4], usr4[4];
	int in = 0 ;
	int guess_times = 0 ;
	char bfr[BFR_SZ]; //Buffer, buffer_size 

	srand( time(NULL) );
	// Game
    while(1){
		system("clear");
		guess_times = 0 ;
		for(int i=0;i<10;i++)
			hst_table[i] = usr_table[i] =0;
		rand4( hst4, hst_table );

		
		printf("Please input a 4-digit integer. Four digits must be four different numbers.\n");
		printf("//the answer is %d%d%d%d\n",hst4[0],hst4[1],hst4[2],hst4[3]);
		// Round
		while(1){ 
			for( int i=0 ; i<10; i++)
				usr_table[i]=0;
			printf("Your 4-digit number: ");
			in = readIn( bfr, BFR_SZ, usr4, 4  );
			//printf("in= %d\n",in);
			if( in == -1 || in < 4 ) {
				printf("You have to input a 4-digit number\n");
				printf("Press Enter to continue!\n");
				while( getchar() != '\n')
					;
				continue ;
			}
			printf("Your input number is %d%d%d%d",usr4[0],usr4[1],usr4[2],usr4[3]);
			// different number check
			int same_num = 0 ;
			for(int i=0; i<4 ;i++){
					if(usr_table[ usr4[i] ] == 1 ){
						 same_num = 1; break;
					}else 
						usr_table[ usr4[i] ] = 1 ;
			}
			if( same_num ){
				printf("     Two digits of the input number are the same. Retry again!.\n");
				continue ;
			} 

			//calculate  ?A?B
			int A=0,B=0 ; 
			for( int i=0; i<4 ;i++){
				if( usr4[i]== hst4[i] )
					A++;
				else if( hst_table[ usr4[i] ] ==1 )
					B++;
			}
			printf("     You got %dA %dB\n",A,B);
			guess_times++;

			if( A==4 )
				break;
		}//Round
		
		int again = 0;
		printf("=============================================\n");
		printf("Winning!!!After %d guessing, you got the right number!\n",guess_times);
		while(1){
			printf("Wanna play again? (y/n): ");
			char check[5];
			fgets( check, 5, stdin );
			if( check[ strlen(check)-1 ] !='\n'){
				while( getchar()!='\n')
					;
			}else
				check[ strlen(check)-1 ] = '\0';
			if( strcmp(check,"y")==0 || strcmp(check,"yes")==0 ){
				again = 1 ;  break;
			}else if( strcmp(check,"n")==0 || strcmp(check,"no")==0  ){
				again = 0 ; break;
			}else{
				printf("Please input 'y' or 'n'\n");
			}
		}
		if( again )
			continue;
		else
			break;
	}//game

	return 0 ; 
}
void rand4( int four[4], int table[10]){
	int i =0,j=0,ct=0,rd=0;
    // Generate 4 random numbers
	for( i=0;i<4;/*empty*/){
		rd = rand()%10;
		for(j=0,ct=0;j<i;j++){
			if(table[rd]==1){
				ct=1;break;
			}
		}
		if(ct)
			continue;
		else{
			table[rd]=1; four[i]=rd;
			i++;
		}
	}
	return ;
}

int readIn( char *bfr, const size_t max_len,int *rd_in , const size_t mx_num ){
    int in = 0 ;
	fgets( bfr, max_len,stdin);
	if( bfr[strlen(bfr)-1] == '\n' ){
		bfr[strlen(bfr)-1] = '\0';
	}else{
		while( getchar() != '\n')
			;
	}
	//printf("bfr=\"%s\"\n",bfr);
	int legal = 1 ;
	int j = 0 ;
	for( int i = 0 ; bfr[i]!='\0';i++ ){
		if( isspace( bfr[i]) )
			continue;
		if( !isdigit( bfr[i] ) ){
			legal = 0 ; break ; 
		}else if ( isdigit( bfr[i]) ){
			if( in >= mx_num ){
				legal = 0; break;
			}
			else{
				char ch[2]=""; ch[0] = bfr[i];
				rd_in[j] = atoi( ch );
		   //    printf("rd_in %d = %d\n",j,rd_in[j]);
				in++; j++;
			}
		}
	}
	if( legal == 0 ){
		for( int i =0 ; i < 4 ; i++ )
			rd_in[i] = 0 ;
		in = -1 ; 
	}
	return in ; 
}
