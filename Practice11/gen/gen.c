#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main( int argc, char** argv){
	FILE *fout;
	char *out = "test1.txt";
	if( !(fout=fopen( out,"w"))){
		printf("Can't open %s\n", out );
		exit(0);
	}
	srand(time(NULL));
	int down, top ,x ;
	int max = atoi( argv[1] );
	for( int i = 1; i<= max; i++){
		x = rand()%50 ;
		down = rand()%1000 ;
		top = rand()%200 + down;
		fprintf(fout,"%4d %5d %5d %5d\n", i, x, down , top);
	}
	return 0 ; 
}