#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main( int argc, char ** argv ){
    FILE *fout; 
    fout = fopen(argv[1], "w");
    if( ! fout){
        printf("Can't open %s\n", argv[1]);
        return 0 ;
    }
    int a,b ;
    int n = atoi( argv[2] ); 
    srand( time(NULL) ); 
    for( int i =0 ; i < n ; i++ ){
        a = rand() % 10000 ;
        b = (rand() % 100) + a ;
        fprintf(fout,"%d %d\n", a ,b );
    }
    
    
    fclose( fout);
    return 0 ;
}

