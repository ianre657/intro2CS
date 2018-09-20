#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LEN 400000
typedef struct line{
	long left , right ;
}LinePoint;


long overlap_len(const LinePoint * ,const  LinePoint * );
int cmp_LinePoint( const void * a, const void *b );

LinePoint *pl ; 

time_t improve_begin, improve_end , sort_begin, sort_end ; 
time_t brute_begin, brute_end ; 
int main(int argc , char ** argv){
    int total_point = 0 ; 
	long long total_overlap=0;
	FILE *fin ;
	// Only designed for one input file
	if( !( fin= fopen(argv[1],"r" ))  ){
		printf("Can't open %s\n", argv[1]);
		return 0 ; 
	}
    pl = malloc( MAX_LEN * sizeof(LinePoint));
	int i = 0, left , right ;
	while( fscanf(fin," %d %d", &left , &right ) != EOF){
        pl[i].left = left ; 
        pl[i].right = right;
        i++;
	}
    total_point = i ;
    pl = realloc(pl,  total_point * sizeof( LinePoint));

/////Brute Force begin
    total_overlap = 0 ;
    time( &brute_begin );
    for( i = 0 ; i < total_point  ; i++){
        for( int j = i+1 ; j < total_point ; j++){
            total_overlap += overlap_len( &(pl[i]), &(pl[j]) );
        }
    }
    time( &brute_end );
    printf("%lld\n", total_overlap);
    printf("%f seconds\n", difftime(brute_end ,brute_begin) ) ;

/////Brute Force end

////Sort begin
    time( &sort_begin);
    qsort( pl, total_point, sizeof(LinePoint), cmp_LinePoint);
    time( &sort_end);
    printf("%f seconds\n", difftime(sort_end ,sort_begin) ) ;
////Sort end

//// 1-c begin
    total_overlap = 0 ;
    time(&improve_begin);
    for( i = 0 ; i < total_point-1 ; i++){
        for( int j = i+1 ; j < total_point ; j++){
        if( pl[i].right < pl[j].left )
            break;
        else
            total_overlap += overlap_len( &(pl[i]), &(pl[j]) );
        }
    }
    time( &improve_end );
    printf("%lld\n", total_overlap);
    printf("%f seconds\n", difftime(improve_end ,improve_begin) ) ;
//// 1-c end


	fclose(fin);
	return 0 ;
}

long overlap_len(const LinePoint * a,const  LinePoint * b){
	if( a->left <= b->left && a->right >= b->right )
		return b->right - b->left;
	else if(b->left <= a->left && b->right >= a->right)
		return a->right - a->left;
	else if( a->left <= b->left && a->right >= b->left )
		return a->right - b->left ;
	else if(b->left <= a->left && b->right >= a->left)
		return b->right - a->left ;
	else
		return 0 ;
    
}
int cmp_LinePoint( const void * a, const void *b ){
    LinePoint  p1 = *((LinePoint*)a) ;
    LinePoint  p2 = *((LinePoint*)b) ;
    return p1.left - p2.left ;
}


