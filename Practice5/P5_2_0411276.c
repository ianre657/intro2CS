#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define MAX_NO 200000

void my_intBubble( int *array, size_t length, int(*isbigger)(int , int ) );
int my_binarySearch( int *array, size_t length, int search  );
int increse( int a, int b){ return a > b ? 1 : 0; } ;
int decrese( int a, int b){ return a < b ? 1 : 0 ; } ;

int main(void){
    int num_array[MAX_NO]; 
	FILE *in; 
	srand( time(NULL) ); 
	printf("Please select the way to read a set of integers.\n"
			" <1> random numbers ; <2> read integers from a file.\n > "); fflush(stdout);
	int gen_mode = 0, totalNo = 0 ;
	char filename[100]; 
	scanf("%d", &gen_mode );
	
	if( gen_mode == 1 ){
		printf("How many number of integers do you want to input?\n > ");fflush(stdout);
		scanf("%d", &totalNo);
		while( getchar() != '\n')
			;
		for( int i = 0 ; i < totalNo ; i++){
			num_array[i] = rand() % 10000 ; 
		}
		printf("%d random integers have been generated.\n", totalNo);fflush(stdout);

	}else if( gen_mode == 2 ){
		printf("Please specify the filename you want to open and read\n > ");fflush(stdout);
		scanf("%s", filename );
		while( getchar() != '\n')
			;
		if( (in = fopen( filename, "r")) == NULL  ){
			printf("Cannot open %s\n", filename);fflush(stdout); return 0  ; 
		}	
		fscanf(in , "%d", &totalNo );
		for( int i = 0 ; i < totalNo ; i++)
			fscanf( in , "%d", &num_array[i] );
		printf("All integers in file %s have been read.", filename);fflush(stdout);

	}
	int incre = 0 , decre = 0 , incre_array[MAX_NO];
	while(1){
		printf("\nSpecify the operation you want to do.\n"
				" i: print integers in increasing order.\n d: print integers in decreasing order.\n"
				" b: perform a binary search.\n q: Quit the program.\n" " > ");fflush(stdout);
		char bfr[3];
		fgets( bfr, 3, stdin ) ;
		if( bfr[ strlen(bfr) -1 ] == '\n'){
			bfr[ strlen(bfr) -1 ] = '\0' ; 
		}else{
			while( getchar() != '\n' )
				;
			printf("Input error!\n"); continue ; 
		}
		if( strlen(bfr) == 0 ){ printf("Input error!\n"); continue ; }

		if( incre == 0 ){	
			incre = 1;
			my_intBubble( num_array, totalNo, increse );

			for( int i = 0 ; i <totalNo ; i++)
				incre_array[i] = num_array[i];
		}

		int quit = 0 , key = 0, search = 0 ;
		FILE *incsort, *decsort;
		switch( bfr[0] ){
			case 'i':
				if( (incsort = fopen("IncSort.txt", "w") )== NULL  )
					printf("Cannot open IncSort.\n");
				for(int i = 0 ; i < totalNo ; i++)
					fprintf( incsort, "%4d\n", incre_array[i]);
					fflush(incsort);
				break;

			case 'd':
				if( decre == 0 ){
					my_intBubble( num_array, totalNo, decrese ); decre = 1;
				}
				if( (decsort = fopen("DecSort.txt", "w") )== NULL  )
					printf("Cannot open DecSort.\n");
				for(int i = 0 ; i < totalNo ; i++)
					fprintf( decsort, "%4d\n", num_array[i]);
					fflush(decsort);
				break;

			case 'b':
				printf("Input an integer for search : ");
				scanf("%d", &search);
				while( getchar() != '\n')
					;
				key = my_binarySearch( incre_array, totalNo, search );
				if( key == -1 )
					printf("The number %d is not in the integer list\n", search);
				else 
					printf("The number %d is in array[%d]", search, key);
				break;
			case 'q': 
				quit = 1 ; break;
			default:
				printf("Input error!\n"); break;
		}
		if( quit )
			break; 
		
	}
	



	printf("\n");
	return 0 ; 
}
int my_binarySearch( int *array, size_t length, int search  ){
	//assuming in increasing order. 
	int low=0, high=length-1;
	while( low <= high ){
		int mid = (low + high)/2; 
		if( array[mid] == search )
			return mid; 
		else if ( array[mid] > search )
			high = mid -1 ;
		else if ( array[mid] < search )
			low = mid + 1 ;
	}
	return -1;
}

void my_intBubble( int *array, size_t length, int(*isbigger)(int, int) ){
	int tmp ; 
	for( int i = 0 ; i < length  -1   ; i++){
		for ( int j = 0  ; j < length -1 -i  ; j++ ){
			if( (*isbigger)( array[j], array[j+1]) ){
				tmp  = array[j];
				array[j] = array[j+1];
				array[j+1] =tmp ; 
			}
		}
	}

	return ;
}
