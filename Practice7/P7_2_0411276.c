#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define START_R 0
#define START_C 0

#define MAX_R 8
#define MAX_C 8
#define MV_TYPE 8 

int grid[MAX_R][MAX_C]  = { {0} };
int path[MAX_R * MAX_C +1]= {0};
const int  horMove[MV_TYPE]= { 2, 1, -1, -2, -2, -1, 1, 2 }  ;// col
const int  verMove[MV_TYPE]= { 1, 2 , 2,  1, -1, -2, -2, -1} ;//row

int len  = 0 ;
int row=MAX_R , col=MAX_C ;
int cur_row= 0 , cur_col= 0  ; 
int next_step=0 ;
int start[2];

int GetNextMove( int );
void print_grid(void);
int main(){
    while(1){
        printf("\n\nPlease input the starting point you want.\n in \"Column Row\" order (0~7)\n > " );
        scanf("%d%d", &start[1] , &start[0]);
        if( start[0] >= 0 && start[0] < MAX_R  && start[0] >= 0 && start[0] < MAX_C )
            break;
        else
            printf("Inappropriate input.\n");
    }
    grid[start[0]][start[1]] = 1 ;// START point
    
    cur_row = start[0]; cur_col = start[1];

    for( int i = 0 ; i < row * col  ; i++ )
        path[i] = -1 ;

    int backing =0 , last_step = 0 , reach_end =0 ;
    int time = 1 ;
    while(len >= 0 ){
        //go ahead
        while(1){
            while( time %10000000 == 0 ){
                time %= 10000000;
                printf("Running...\n\n");
                print_grid();
                break;
            }
            time++;
            // reach end 
            if( len >= MAX_C* MAX_R -1   ){
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
                grid[cur_row][cur_col] = len+1 ;
            }else
                break;
        }
        if( reach_end == 1){
            break ; 
        }
        //backing
        grid[cur_row][cur_col] = 0 ;
        cur_row -= verMove[ path[len-1] ] ;
        cur_col -= horMove[ path[len-1] ] ;
        last_step = path[len-1];
        backing =1 ;
        path[len--] = -1 ;
    }
    printf("%s\n", reach_end == 1 ? "reach the end!!\n":"After go through all possible path,\nIt is impossible to reach to end node" );
    if( reach_end )
        print_grid();
	return 0 ;
}
void print_grid(){
	int r=0 , c=0;
	for( r = row-1; r >= 0 ; r-- ){
		printf("%2d ", r ); 
		for( c = 0; c <= col -1  ; c++){
                    printf(" %2d",grid[r][c] );
		}
		printf("\n");
	}  
	printf("\n   ");
	for( int i = 0 ; i < c  ; i++){
		printf(" %2d", i);
	}
	printf("\n\n\n\n");
	return ; 
}
int GetNextMove( int begin_step ){
    int  r = 0, c = 0 ,legal = 1 , i; 
    if( begin_step >= MV_TYPE )
        return -1 ;
    for( i = begin_step ;i < MV_TYPE ; i++){
        r = cur_row, c = cur_col ; 
        r += verMove[i]; c += horMove[i];
        if( r < 0 || r >= row || c < 0 || c >= col ||  grid[r][c] ==  -2 || grid[r][c] == -1   || grid[r][c] > 0    ){
            legal =0 ; continue ;
        }else{
            legal = 1 ; break;
        }
    }
    return legal == 1 ? i : -1;
}
