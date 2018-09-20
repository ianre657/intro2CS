#include<stdio.h>
#include<stdlib.h>

typedef struct vline{
	int x ;
	int yt ;//y top
	int yb ;//y bottom
}vline;// vertical line
typedef struct vlineNode{
	vline  vline;
	struct vlineNode * prev;
	struct vlineNode * next;
}vlineNode;

void insertBack_vlNode( vlineNode ** this,const vline * vl );//將node插在後方,this不能是指向LinkList的指標
void insertBack_vlNode( vlineNode ** this,const vline * vl ){
	vlineNode * n = malloc( sizeof(vlineNode) );
	if( !n ){ printf("Can't insertback \n"); exit(0);}
	if( (*this)->next == NULL ){//tail node
		n->prev = *this ;
		n->next = NULL ;
		n->vline = *vl ;
		(*this)->next = n ;
	}else{
		n->prev =  *this ;
		n->next = (*this)->next ;
		n->vline = *vl;
		(*this)->next = n ;
	}
	return ;
}

void insertHead_vlNode( vlineNode ** Head, const vline *vl ) //在前方插入Node, 會順便更新Head node
{
	vlineNode * n = NULL;
	n = malloc( sizeof(vlineNode) );
	if( !n ){ printf("Can't insertback \n"); exit(0);}
	n->prev = NULL ;
	if( *Head == NULL ){
		n->next = NULL ;
		n->vline = *vl;
		*Head = n ;
	}else{
		(*Head)->prev = n ;
		n->next = (*Head);
		n->vline = *vl;
		*Head = n ;
	}
	return;
}

void delete_vlNode( vlineNode **Head, vlineNode ** vline); //刪除後自動將vline變成 原本的vline->next
void delete_vlNode( vlineNode **Head, vlineNode ** vline)
{
	if( *vline == NULL )
		return ;
	
	vlineNode * del = *vline ;
	if( ((*vline)->next)!= NULL )
	{
		if( (*vline)->prev != NULL  ){
			((*vline)->prev)->next = (*vline)->next ;
			((*vline)->next)->prev = (*vline)->prev ;
		}else{// 假設刪除的是HeadNode
			((*vline)->next)->prev = NULL ;
			(*Head) = (*vline)->next ;
		}
		(*vline) = (*vline)->next ;
	}else if(  ((*vline)->prev) != NULL  ){//刪除 tail node
		((*vline)->prev)->next = NULL ;
		(*vline) = NULL ;
	}else{//刪除最後一個Node
		(*vline) = NULL ;
		(*Head) = NULL;
	}
	free( del );
	return ;
}

void freeList_vlineNode( vlineNode *list );
void freeList_vlineNode( vlineNode *list )
{
	vlineNode *del;
	while( list != NULL){
		del = list ;
		list = list->next ;
		free(del);
	}
	return ;
}

typedef struct rect{
	int xl;//left
	int xr;//right
	int yt;//top
	int yb;//bottom
}rect;

typedef struct rectNode{
	rect rect ;
	struct rectNode *next ;
}rectNode;

void insertHead_rec( rectNode** head,int xl, int xr, int yt, int yb );
void insertHead_rec( rectNode** head,int xl, int xr, int yt, int yb )
{
	rectNode *n = malloc( sizeof( rectNode) );
	if( !n ){puts("Can't allocate rectangular Node"); exit(1);};
	n->rect.xl = xl ;
	n->rect.xr = xr ;
	n->rect.yt = yt ;
	n->rect.yb = yb ;
	
	if( *head == NULL  ){
		n->next = NULL ;
		(*head)  = n ;
	}else{
		n->next = *head ;
		(*head) = n ;
	}
	return ;
}

void freeList_rect( rectNode *list );
void freeList_rect( rectNode *list )
{
	rectNode *del;
	while( list != NULL){
		del = list ;
		list = list->next ;
		free(del);
	}
	return ;
}

int cmp_vline( const void *a, const void *b );// 由x小排到大, x 相同者y大在前(假設線段不重疊)
int cmp_vline( const void *a, const void *b )
{//cmp_vline
	vline L1 =  *((vline*)a);
	vline L2 =  *((vline*)b);
	if( L1.x != L2.x )
		return L1.x - L2.x ;
	else
		return L2.yt - L1.yt ;
}

int cmp_rect( const void *a, const void *b );
int cmp_rect( const void *a, const void *b )
{
	rect r1 = *(rect*)a;
	rect r2 = *(rect*)b;
	if( r1.yb != r2.yb )
		return r1.yb - r2.yb ;
	else
		return r1.xl - r2.xl ;
}
int area( rect r ){ return ( r.xr - r.xl )*( r.yt - r.yb ) ; }

int main( int argc, char** argv){
	FILE *fin, *fout ;
	if( !( fin  = fopen( argv[1], "r") ) ){ printf("Can't open %s\n", argv[1]); exit(1);}
	if( !( fout = fopen( "0411276_ans.txt", "w") ) ){ printf("Can't open %s\n","output.txt"); exit(1);}
	
	int total_pt = 0 ;
	fscanf(fin," %d ", &total_pt);
	vline *up, *down ;
	if( !( up = calloc( total_pt/2 , sizeof(vline) ) ) ){ printf("Can't allocate space for up\n"); exit(1);}
	if( !( down = calloc( total_pt/2, sizeof(vline) ) ) ){ printf("Can't allocate space for down\n"); exit(1);}
	
	int total_up = 0 , total_down = 0 ;
	int x , y ;
	int last_x=0, last_y=0;
	int first_x=0 , first_y = 0 ;
	int n = 0 ;
	while( n != total_pt )
	{
		fscanf(fin," %d %d ", &x,&y);
		if( n != 0 )
		{
			if( y != last_y )
			{
				if( y > last_y )
				{
					up[total_up].x = x ;
					up[total_up].yt = y ;
					up[total_up].yb = last_y ;
					total_up++;
				}else{
					down[total_down].x = x ;
					down[total_down].yt = last_y;
					down[total_down].yb = y;
					total_down ++ ;
				}
			}
		}else{
			first_x =  x ;
			first_y =  y;
		}
		last_x = x ;
		last_y = y ;
		n += 1 ;
	}
	if( n == total_pt && last_x == first_x )
	{
		if( first_y > last_y )
		{
			up[total_up].x = last_x ;
			up[total_up].yt = first_y ;
			up[total_up].yb = last_y ;
			total_up++;
		}else if( first_y == last_y){
			printf("firsty = last y , impossible\n");exit(0);
		}else{
			down[total_down].x = last_x ;
			down[total_down].yt = last_y;
			down[total_down].yb = first_y;
			total_down ++ ;
		}
	}

	up = realloc( up,  total_up * sizeof(vline)  );
	down = realloc( down, total_down *  sizeof(vline));
	qsort( up, total_up, sizeof(up[0]), cmp_vline);
	qsort( down, total_down, sizeof(down[0]), cmp_vline);



	vlineNode *up_vlNode   = NULL ;
	vlineNode *down_vlNode = NULL ;
	//將vline轉成 Link list儲存起來,方便接下來運算
	for( int i = total_up-1 ; i >= 0; i--){
		insertHead_vlNode( &up_vlNode, &up[i] );
	}
	for( int i = total_down-1 ; i >= 0; i--){
		insertHead_vlNode( &down_vlNode, &down[i] );
	}
	
	//if(total_up!= 0 )free(up);
	//if(total_down!= 0 )free(down);
	free(up);
	free(down);
	
	rectNode *rectList = NULL ;
	int iter_update = 0 ; //刪除iterD node 會更新 iterD, 需要用flag註記有無更新過
	for( vlineNode *iterD = down_vlNode; iterD != NULL;  )
	{
		for( vlineNode *iterU = up_vlNode; iterU != NULL ; iterU = iterU->next )
		{
			//不重疊
			if( iterD->vline.x >= iterU->vline.x ||iterD->vline.yt <= iterU->vline.yb || iterD->vline.yb >= iterU->vline.yt  ){
				
				
				
				continue;
				
				//完全重疊
			}else if( iterD->vline.yt <= iterU->vline.yt && iterD->vline.yb >= iterU->vline.yb){
				insertHead_rec( &rectList, iterD->vline.x, iterU->vline.x, iterD->vline.yt, iterD->vline.yb );
				delete_vlNode( &down_vlNode, &iterD );
				iter_update = 1 ;
				break;
				
				//上半部重疊
			}else if ( iterD->vline.yt <=  iterU->vline.yt && iterD->vline.yb < iterU->vline.yb ){
				insertHead_rec( &rectList, iterD->vline.x, iterU->vline.x, iterD->vline.yt, iterU->vline.yb );
				iterD->vline.yt = iterU->vline.yb ;
				
				//下半部重疊
			}else if( iterD->vline.yb < iterU->vline.yt && iterD->vline.yb >= iterU->vline.yb ){
				insertHead_rec( &rectList, iterD->vline.x, iterU->vline.x, iterU->vline.yt, iterD->vline.yb );
				iterD->vline.yb = iterU->vline.yt;
				// 中間重疊
			}else if ( iterD->vline.yt > iterU->vline.yt && iterD->vline.yb < iterU->vline.yb){
				vline new ;
				new.x = iterD->vline.x;
				new.yt = iterD->vline.yt ;
				new.yb = iterU->vline.yt ;
				
				insertBack_vlNode( &iterD, &new);
				insertHead_rec( &rectList, iterD->vline.x, iterU->vline.x, iterU->vline.yt, iterU->vline.yb );
				iterD->vline.yt = iterU->vline.yb ;
			}else{
				printf("This case should not happen\n");
				exit(1);
			}
		}
		if( !iter_update ){
			iterD = iterD->next ;
		}else{
			iter_update = 0 ;
		}
	}
	
	freeList_vlineNode( up_vlNode );
	freeList_vlineNode( down_vlNode );
	
	int total_rect = 0  ;
	for( rectNode *iter = rectList; iter!= NULL ; iter = iter->next ){
		total_rect++;
	}
	
	rect *r = malloc( sizeof(rect) * total_rect);
	if( !r ){ puts("Can't allocate rect array\n"); exit(1);}
	
	rectNode *iter = rectList ;
	for( int i = 0 ; i < total_rect; i++ , iter= iter->next){
		r[i] = iter->rect ;
	}
	freeList_rect( rectList);
	qsort(  r, total_rect, sizeof(rect), cmp_rect );
	
	
	//printf("total rect = %d\n",total_rect);
	
	int total_area = 0 ;

	//第一個元素是r[0]
	for( int i = 0 ; i< total_rect ; i++){
		fprintf(fout,"%d %d\n",i, area(r[i]));
	}
	
	total_area = 0 ;

	free(r);
	fclose( fin);
	fclose( fout);
	return 0 ;
}