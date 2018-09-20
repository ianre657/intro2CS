#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define MAX_R 500
#define MAX_C 500

// move type 
#define MV_TYPE 4 
int inverse[]={ 1, 0, 3, 2 };
int grid[MAX_R][MAX_C]  = { {0} };
int path[MAX_R * MAX_C ]= {0};

int best_grid[MAX_R][MAX_C] = { {0} }; 
int best_path[MAX_R * MAX_C ]= {0};
int best_len = MAX_R * MAX_C;

const int  horMove[MV_TYPE]= { 0, 0, -1, 1 }  ;// col
const int  verMove[MV_TYPE]= { 1, -1, 0, 0 } ;//row

int len  = 0 ;
int row=0 , col=0 ;
int cur_row= 0 , cur_col= 0  ; 
int next_step=0 ;
int  start[2], end[2];
//void print_grid( int *[] );
void print_grid( int [MAX_R][MAX_C] );

int GetNextMove( int );
void get_result_best(void);

int main(){
	FILE *fin, *fout; 
	if( (fin = fopen( "route.txt" , "r") ) ==NULL  ){
		printf("Fail to open input.txt!\n"); return 0 ;
	}
	if( (fout = fopen( "path.txt" , "w") ) ==NULL  ){
		printf("Fail to open path.txt!\n"); return 0 ;
	}
	fscanf(fin, "%d%d", &col, &row);
	if( col > MAX_C || col < 1 || row > MAX_R || row < 1  ){
		printf("Illegal size\n");return 0 ;
	}
    for( int i = 0; i< MAX_C* MAX_R ; i++){
        best_path[i] = -1 ;
    }

	fscanf(fin, "%d%d%d%d",&start[1], &start[0], &end[1], &end[0]);
    grid[start[0]][start[1]] = -2 ;// START point
    grid[end[0]][end[1]] = -3 ;// END point

	int ob_r=0, ob_c =0;
	int ob_num;
	fscanf(fin, "%d", &ob_num ) ; 
	for( int i = 0 ; i < ob_num ; i++){
		fscanf(fin, "%d%d",&ob_c,&ob_r );
		grid[ob_r][ob_c] = -1 ;
	}
    
    cur_row = start[0]; cur_col = start[1];
    for( int i = 0 ; i < row * col  ; i++ )
        path[i] = -1 ;

    int backing =0 , last_step = 0 ; 
    int reach_end =0 ;
    while(len >= 0 ){
        //go ahead
        while(1){
            // reach end 
            if( cur_row == end[0] && cur_col == end[1] ){
                if( len < best_len ){
                    get_result_best();
                }
                reach_end = 1 ; break ;
            }else if( backing == 1 ){
                next_step = GetNextMove( last_step+1 );
                backing = 0 ;
            }else
                next_step = GetNextMove( 0 ) ; 

            if( next_step != -1 ){
                path[len++] = next_step ; 
                cur_row += verMove[next_step];
                cur_col += horMove[next_step];
                grid[cur_row][cur_col] = len ;

            }else{
                break;
            }
        }
        //backing
        grid[cur_row][cur_col] = 0 ;
        cur_row -= verMove[ path[len-1] ] ;
        cur_col -= horMove[ path[len-1] ] ;
        last_step = path[len-1];
        backing =1 ;
        path[len--] = -1 ;
    }
    if( reach_end == 0  ){
        printf("It is impossible to reach to end node\n");
    }else{
        printf("\nThis is the shortest path founded,\n data had been write into \"path.txt\"\n"
            " In back-tracing order.\n\n");
        print_grid( best_grid);
        fprintf(fout,"%d\n",best_len);
        for(int i = best_len-1 ; i >= 0  ; i--){
            fprintf(fout,"%d ", inverse[best_path[i]]);
        }
        fprintf(fout,"\n");
    }
    fclose( fin );
    fclose( fout );
	return 0 ;
}

int GetNextMove( int begin_step ){
    int  r = 0, c = 0 ; 
    int legal = 1 ;
    if( begin_step >= MV_TYPE ){
        return -1 ;
    }
    int i =0 ;
    for( i = begin_step ;i < MV_TYPE ; i++){
        r = cur_row, c = cur_col ; 
        r += verMove[i]; c += horMove[i];
        if( r < 0 || r >= row || c < 0 || c >= col ||  grid[r][c] ==  -2 || grid[r][c] == -1   || grid[r][c] > 0    ){
            legal =0 ; continue ;
        }else{
            legal = 1 ; break;
        }
    }
    return legal == 1 ? i : -1 ; 
}
void get_result_best(){
    best_len = len ; 
    for( int i = 0 ; path[i] != -1; i++ ){
        best_path[i] = path[i];
    }
    best_path[len] = -1 ;
    for( int i = 0 ; i < row ; i++){
        for( int j = 0 ; j< col ; j++)
            best_grid[i][j] = grid[i][j];
    }
    return ; 
}
void print_grid( int g[MAX_R][MAX_C] ){
	int r=0 , c=0;
	for( r = row-1; r >= 0 ; r-- ){
		printf("%2d ", r ); 
		for( c = 0; c <= col -1  ; c++){
            switch( g[r][c] ){
                case -1 :
                    printf("  #");break;
                case -2 :
                    printf("  S");break;
                case -3 :
                    printf("  E");break;
                default:
                    printf(" %2d",g[r][c] );break;
            }
		}
		printf("\n");
	}  
	printf("\n   ");
	for( int i = 0 ; i < c  ; i++){
		printf(" %2d", i);
	}
	printf("\n");
	return ; 
}
