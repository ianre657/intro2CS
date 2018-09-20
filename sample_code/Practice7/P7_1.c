#include <stdio.h>
#include <stdlib.h>

int route_x[1000];
int route_y[1000];
int route_index;
int path_x[1000];
int path_y[1000];
int path_cnt[1000];
int path_index;
int ans_array[1000];
int ans_index;
int ans_step;

//record point in stack
void push_path(int x,int y){
    path_x[++path_index] = x;
    path_y[path_index] = y;
}

//pop out point from stack
void pop_path(){
    if(path_index >= 0) path_index--;
}

void snap_shot(int t_x, int t_y){
    int i;
    ans_index = -1;
    if(t_x - path_x[path_index] == -1) 
		ans_array[++ans_index] = 0;
    else if(t_x - path_x[path_index] == 1) 
		ans_array[++ans_index] = 1;
    else if(t_y - path_y[path_index] == 1) 
		ans_array[++ans_index] = 2;
    else if(t_y - path_y[path_index] == -1) 
		ans_array[++ans_index] = 3;
		
    for (i = path_index - 1; i >= 0; i--) {
        if(path_x[i + 1] - path_x[i] == -1) 
			ans_array[++ans_index] = 0;
        else if(path_x[i + 1] - path_x[i] == 1) 
			ans_array[++ans_index] = 1;
        else if(path_y[i + 1] - path_y[i] == 1) 
			ans_array[++ans_index] = 2;
        else if(path_y[i + 1] - path_y[i] == -1) 
			ans_array[++ans_index] = 3;
    }
    ans_step = path_index + 1;
}

int visit_loop(int s_x, int s_y, int* MAZE, int width, int height){
    int i, j, maze_num, step = 0;
    int step1 = 0, cur_x = s_x, cur_y = s_y;
    int move_x[4] = {0, 0, 1, -1};
    int move_y[4] = {1, -1, 0, 0};
    path_index = -1;
    ans_step = 1000;
    for (i = 0; i < 1000; i++) {
        path_x[i] = path_y[i] = -1;
        path_cnt[i] = ans_array[i] = 0;
    }
    while (1) {
    	
		//Meet can walk point or need try point
        if(MAZE[width*cur_x+cur_y] == 0 || (path_x[path_index] == cur_x && path_y[path_index] == cur_y)){
        	
            if((path_x[path_index] != cur_x || path_y[path_index] != cur_y) || path_cnt[0] == 0 ){
                MAZE[width * cur_x + cur_y] = 2;//2:walked
                push_path(cur_x, cur_y);
            }
            
            if(path_cnt[path_index] < 4){
            	//every set just can move 1 step
                cur_x += move_x[path_cnt[path_index]];
                cur_y += move_y[path_cnt[path_index]];
                
                path_cnt[path_index]++;
            }
            
            else{
                if(cur_x == s_x && cur_y == s_y) 
					return 0;
                MAZE[width * cur_x + cur_y] = 0;
                path_cnt[path_index] = 0;
                pop_path();
                cur_x = path_x[path_index];
                cur_y = path_y[path_index];
            }
        }
        
        //Meet obstacle
        else if(MAZE[width * cur_x + cur_y] == 1){
            cur_x = path_x[path_index];
            cur_y = path_y[path_index];
        }
        
        //Meet target
        else if(MAZE[width * cur_x + cur_y] == 8){

            if(path_index + 1 < ans_step) {
                snap_shot(cur_x, cur_y);
            }
            cur_x = path_x[path_index];
            cur_y = path_y[path_index];
            //return 0;
        }
        //Meet walked point
        else if(MAZE[width * cur_x + cur_y] == 2){
            cur_x = path_x[path_index];
            cur_y = path_y[path_index];
        }
    }
    
    return -1;
}

int main(int argc, const char * argv[]) {

    FILE *out, *in;
    char garbage = '\0';
    char file_name[1000];
    route_index = -1;
    int i, j, len = 0, t_x, t_y, s_x, s_y, b_x, b_y, block_cnt, MAX_R, MAX_C;
    printf("Please enter the file name:");
    scanf("%s",file_name);
    if ((in = fopen(file_name,"r")) == NULL)
    {
        printf("Cannot open file \"in\"!\n");
        return 0;
    }
    //printf("flag1\n");
    fscanf(in, "%d %d", &MAX_C, &MAX_R);
    fscanf(in, "%c", &garbage);
    int grid[MAX_R + 2][MAX_C + 2];
    for(i = 0; i < MAX_R + 2; i ++) 
		for(j = 0; j < MAX_C + 2; j++) {
        	if(i == 0 || j == 0 || i == MAX_R+1 || j == MAX_C+1){
            	grid[i][j] = 1;//set bounded
        	}
        	else grid[i][j] = 0;
    }

    fscanf(in, "%d %d", &s_x,&s_y);
    fscanf(in, "%d %d", &t_x,&t_y);

    fscanf(in, "%c", &garbage);
    grid[t_y + 1][t_x + 1] = 8;
    fscanf(in,"%d",&block_cnt);
    fscanf(in,"%c",&garbage);
    for (i = 0; i < block_cnt; i++) {
        fscanf(in,"%d %d", &b_x,&b_y);
        fscanf(in,"%c", &garbage);
        grid[b_y+1][b_x+1]=1;
    }

    fclose(in);

    if ((out = fopen("path.txt","w")) == NULL)
    {
        printf("Cannot open file!\n");
        return 0;
    }

    visit_loop(s_y + 1, s_x + 1, *grid, MAX_C + 2, MAX_R + 2);
    
    fprintf(out,"%d\n",ans_step);
    for (i = 0; i <= ans_index; i++) {
        fprintf(out,"%d ",ans_array[i]);
    }
    fprintf(out,"\n");
    fclose(out);
    return 0;
}
