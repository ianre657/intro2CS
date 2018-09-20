#include <stdio.h>
#include <stdlib.h>
#define N 8

typedef struct Knight
{
    int row,col;
    int d; //direction
    int t;
    int steps;
}KNIGHT;
typedef struct Prior
{
    int key;
    int value;
}PRIOR;

void push(KNIGHT knight);
KNIGHT pop(void);
int inChess(int row,int col);
void knightMove(int row,int col);
void initinal();
void print();
void demo();
int cmp(const void *a,const void *b);

int demonstration=0;
int chess[N][N];
int pathnum[N][N];
int top=0;
KNIGHT stack[N*N];
int colMove[] = {2,1,-1,-2,-2,-1,1,2};//record the eight direction
int rowMove[] = {-1,-2,-2,-1,1,2,2,1};
//int rowMove[8]={1,2,2,1,-1,-2,-2,-1};
//int colMove[8]={2,1,-1,-2,-2,-1,1,2};
int main(void)
{
     int row,col;
     initinal();
     printf("Please input start point coordinate(ex:1 2) or input 'd' to demo(ex:d): ");

     if(scanf("%d %d",&row,&col)!=2)
     {
        char d;
        getchar();
        demo();
     }
     else
     {
        knightMove(row,col);
        printf("------****(%d,%d)****------\n",row,col);
        print();
     }
    return 0;
}
void initinal()
{
     top=0;
     int i,j,k;
     for(i=0;i<N;i++)
     {
         for(j=0;j<N;j++)
         {
             chess[i][j]=0;   //initinal the chessboard;0:covered
             pathnum[i][j]=0;
         }
     }
     for(i=0;i<N;i++)  //compute the all possible direction number of each point
     {
         for(j=0;j<N;j++)
         {
             for(k=0;k<8;k++)
             {
                 if(inChess(i+rowMove[k],j+colMove[k]))
                    pathnum[i][j]++;
             }
         }
     }
}
void push(KNIGHT knight)
{
    stack[top]=knight;
    top++;
}
KNIGHT pop(void)
{
   top--;
   return(stack[top]);
}

int inChess(int row,int col)
{
    if(row>=0&&row<N&col>=0&&col<N)
       return 1;
    else
       return 0;
}
void knightMove(int row,int col)      //start from (row,col)
{
    int i,j,k,w=0;
    int steps = 1,t=0,nRow,nCol,d;
    KNIGHT knight;
    chess[row][col] = steps++;
    while(steps<=N*N)
    {
        if(demonstration==1)
        {
            system("cls");
            printf("----***start at (3,4)***----\n");
            print();
            system("pause");
        }
        PRIOR priority[8]; //priority array
        for(i=0;i<8;i++)
        {
            if(inChess(row+rowMove[i],col+colMove[i]))
                pathnum[row+rowMove[i]][col+colMove[i]]--;
                priority[i].key=i;//direction
            priority[i].value=pathnum[row+rowMove[i]][col+colMove[i]];//pathnum
        }
        qsort(priority,8,sizeof(priority[0]),cmp);
        for(;t<8;t++)
        {
            nRow = row+rowMove[priority[t].key]; //compute next row
            nCol = col+colMove[priority[t].key]; //compute next col
            if(inChess(nRow,nCol)&&chess[nRow][nCol]==0)
            {
                chess[nRow][nCol]=steps;
                knight.row = row;     //record the location of previous step
                knight.col = col;
                knight.d = priority[t].key;
                knight.t=t;
                knight.steps = steps;
                push(knight); //push
                t=0;
                row = nRow;
                col = nCol;
                steps++;
                break;
            }
        }
        if(t==8) //return to previous step
        {
            for(i=0;i<8;i++)
            {
                if(inChess(row+rowMove[i],col+colMove[i]))
                    pathnum[row+rowMove[i]][col+colMove[i]]++;
            }
            knight = pop();//pop
            row = knight.row;
            col = knight.col;
            d = knight.d;
            t = knight.t;
            steps = knight.steps;
            nRow = row + rowMove[d];
            nCol = col + colMove[d];
            chess[nRow][nCol]=0; //return to zero
            t++;
        }
    }
}
int cmp(const void *a,const void *b)
{
    int c=(*(PRIOR *)a).value;
    int d=(*(PRIOR *)b).value;
    if(c<d) return -1;
    else if(c==d) return 0;
    else return 1;
}
void print()
{
    int i,j;
    for(i=-1;i<N;i++)
     {
         for(j=-1;j<N;j++)
         {
             if(i==-1)
             {
                 if(j==-1) printf("   ");
                 else printf("%2d ",j);
             }
             else if(j==-1) printf("%2d ",i);
			 else printf("%2d ", chess[i][j]);

         }
         printf("\n");
     }
}
void demo()
{
    demonstration=1;
    knightMove(3,4);
    printf("\n------***result***-------\n");
    print();
    system("pause");
}
