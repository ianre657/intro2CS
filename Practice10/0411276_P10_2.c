#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SZ 400000

typedef struct linept{
    int id; 
    int point;
    enum Handside{ left, right } side ;
}LinePoint ;

typedef struct table{
    int left_pos ;
    int right_pos ;
}Table;

typedef struct ActiveList{
    int id ;
    int point ; 
    int next ; 
    int prev; 
    char active ; 
}ActiveList ; 

int cmp_point( const void*a, const void *b){
    LinePoint p1 = *((LinePoint*)a) ;
    LinePoint p2 = *((LinePoint*)b) ;
    if( p1.point != p2.point )
        return p1.point -p2.point;
    else 
        return p1.side - p2.side ;  
}
time_t sort_begin, sort_end , add_begin, add_end ; 

int total_active = 0; 

int main(int argc , char ** argv){
    FILE *fin ;
    if( !( fin= fopen(argv[1],"r" ))  ){
        printf("Can't open %s\n", argv[1]);
        return 0 ; 
    }
    //FILE *fout ;
    //fout = fopen("out.txt", "w"); // Watch the sorting outcome 
    int total_point = 0 ;
    LinePoint * lp = malloc( MAX_SZ * sizeof(LinePoint));
    if( !lp ){
        printf("Can't allocate LinePoint\n");exit(0);
    }
    
	long long total_overlap=0;
	// Only designed for one input file
	int Lpoint, Rpoint ; 
	int i = 0 ;
    while( fscanf( fin , " %d %d ",  &Lpoint, &Rpoint) != EOF){
        lp[2*i].id = i;
        lp[2*i].point=Lpoint ;
        lp[2*i].side = left ;
        lp[2*i+1].id = i ;
        lp[2*i+1].point = Rpoint ; 
        lp[2*i+1].side = right; 
        i ++ ;
	}
    total_point = 2*i ;
    lp = realloc( lp, total_point * sizeof(LinePoint) );

    time( &sort_begin);
    qsort( lp, total_point, sizeof( LinePoint), cmp_point );
    time( &sort_end );


    time( &add_begin );
    // Used table to look up the points left and right point value 
    // use ID as the array key .
    Table *ta = malloc( (total_point/2) *sizeof(Table) );
    for( int i = 0; i < total_point ; i++){
        if( lp[i].side == left )
            ta[ lp[i].id ].left_pos = lp[i].point;
        else  
            ta[ lp[i].id ].right_pos = lp[i].point;
    }

    //Use ActiveList (Array) to acheve better performence 
    ActiveList *ac = calloc(  (total_point/2) , sizeof(ActiveList) );
    total_active = 0 ; 
    int front =0 , back = 0 ;
    // back is always offset by one


    /*for( i = 0; ( i < total_point )  ; i++){
        fprintf(fout," id: %6.6d, point: %6.6d ,%c\n", lp[i].id, lp[i].point, lp[i].side==left?'L':'R');
    }
    fflush(fout);*/
    time ( &add_begin );
    //
    for( i =0 ; i<total_point/2 ; i++ ){
        ac[i].next = i + 1 ;
        if( i != 0 )
            ac[i].prev = i - 1 ;
    }
    back = 0 ;
	for( i = 0 ; i< total_point ; i++ ){

        /*Print all element
        printf("\n\nfront = %5d, back = %5d, total_active =%5d\n", front, back, total_active);
        for( int h = 0 ; h < total_point/2 ; h++ ){
            printf("id : %5d, point : %5d, h= %5d, next= %5d, prev = %5d, active = %1d", ac[h].id, ac[h].point,h, ac[h].next, ac[h].prev, ac[h].active );
            if( h == front ) printf("  Front\n");
            else if ( h== back ) printf("  Back\n");
            else printf("\n");
        }
        // Print all element end
        */
        /*
        if( i% 10000 == 0 )
            printf("processing point :%6.6d\n",i );
        */
        //Go into list to do operation
        if( lp[i].side == left ){
            //there exist at least one active point in the list 
            ac[back].active = 1 ;
            total_active++;
            ac[back].id = lp[i].id ;
            ac[back].point = lp[i].point ;
            back++ ; 
        }else{
            //int through = 0 ;
            for( int j = front; j != back ; j= ac[j].next ){
                if( ac[j].id == lp[i].id ){
                    //remove forom list 
                    if( total_active == 1 ){//only exist one in the list 
                        front = back ;
                    }else if( j == front ){// first one in the list
                        front = ac[j].next ; 
                    }else if( j == back -1 ){// remove the last one 
                        ac[ ac[j].prev ].next = back ; 
                        ac[ j+1 ].prev = ac[j].prev;
                    }else{
                        ac[ ac[j].prev ].next = ac[j].next;
                        ac[ ac[j].next ].prev = ac[j].prev ;
                    }
                    ac[ j ].active = 0 ;
                    total_active -- ;
                    //back ,front check 
                }else{
                    // do overlaping operation 
                    
                    int left =  ta[ lp[i].id ].left_pos ; 
                    if( ac[j].point >= left ){
                        total_overlap += lp[i].point - ac[j].point ;
                    }
                    else 
                        total_overlap += lp[i].point - left ; 
                }
            }
        }
    }
    time( &add_end );
	printf("%lld\n", total_overlap );
    printf("Sorting time : %f second\n", difftime( sort_end, sort_begin));
    printf("Adding  time : %f second\n", difftime( add_end, add_begin ));
    free(lp);
    free(ta);
    free(ac);
	fclose(fin);
	return 0 ;
}
