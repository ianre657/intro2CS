#include<stdio.h>
#include<stdlib.h>
//MAX_PT : 最多能存放的線段數
#define MAX_PT 500000 

typedef struct LineSegment{
	int id ; 
	int top ; 
	int down ;
	struct LineSegment *next ;
	struct LineSegment *prev ;
}LineSegment; 
void insertHead_LS( LineSegment ** Head,int id,int top ,int down );//新增一個node 到 Head 鏈結串列的前端
void deleteSegment( LineSegment ** Head , LineSegment ** seg );// deleteSegment 回傳被刪除Node的 下一個Node位址
void freeList_LS( LineSegment *iter);  //Free 從 iter 後面所有的鏈結串列
void printList_LS( LineSegment *list ); //Print 從 list開始的鏈結串列
//合併Overlap重疊的線段,並從Head中比對並剪除seg線段
void OverlapMerge_Trim( LineSegment **Overlap, LineSegment **Head, LineSegment ** seg);


typedef struct LineRelation{// A link list to record the line it can see 
	int id;
	struct LineRelation * next ;
	struct LineRelation * prev ;
}LineRelation;
void insertHead_LR( LineRelation ** Head, int id );//新增一個node 到 Head 鏈結串列的前端
void freeList_LR( LineRelation *iter );//Free 從 iter 後面所有的鏈結串列

typedef struct Line{
	int id ; 
	int x ; 
	int top ; 
	int down ;
}Line ;//存放線段所有的資訊

int cmp_x( const void * a, const void *b );
int cmp_id_LR( const void *a, const void *b);

//看看該top , down 跟 seg是否有重疊，如果有重疊的話會將重疊部分傳入 Overlap中等待後續合併處理
int Have_overlap( LineSegment **Head, LineSegment * seg, LineSegment **Overlap, int top , int down );


int total_point; 
int main(int argc , char ** argv){
	FILE *fin, *ans ;
	//FILE *fout;
	//fout = fopen("out.txt","w"); 
	if( !( fin = fopen( argv[1], "r")  )){printf("Can't open %s\n", argv[1]);exit(1);}
	if( !( ans = fopen("vLine.out","w"))){printf("Can't open vLine.out\n");  exit(1);}

	Line * line = malloc( MAX_PT * sizeof(Line));
	int top, down, id ,x;
	int i = 0 ;  
	for(i = 0 ; i < MAX_PT && fscanf(fin, " %d %d %d %d ", &id, &x, &down, &top ) != EOF; i++){
		line[i].id = id ;
		line[i].x = x ;
		line[i].top = top;
		line[i].down = down ;  
		if( i == MAX_PT -1  ){
			printf( "Reach the maximun storage!\n");
			exit(0);
		}
	}
	total_point = i ; 
	line = realloc( line , total_point * sizeof(Line) ) ;
	qsort( line,  total_point, sizeof(Line), cmp_x );
	//Print all line 
	/*for( i = 0 ; i < total_point ; i++){
		fprintf(fout,"id: %5d, x:%5d, top:%5d, down:%5d \n", line[i].id, line[i].x, line[i].top, line[i].down );
	}fflush( fout );*/

	LineSegment *Activelist =NULL  ;
	LineSegment *Overlap = NULL ; 
	LineRelation **rtable =NULL;// Ralation Table 是一個 Array of LinkList, 用來紀錄該線段看得到誰
	
	rtable = malloc( (total_point+1) * sizeof( LineRelation * ));//rtable[0]捨棄不用
	for( i = 0 ; i <= total_point ; i++ ){rtable[i] = NULL;}
	if( ! rtable ){ printf("Can't allocate rtable\n"); exit(0);} 

	int same_low=0, same_high=0 ;
	i = total_point -1 ; 
	while(1){
		if( i < 0 )//Same_high ~ Same_low: x 值相同的所有線段 
			break ; 
		same_high = i ; 
		if( i !=  0 ){
			for(int j = i-1 ; j>=0 ; j--){
				if( line[j].x != line[same_high].x ){
					same_low = j + 1;
					break;
				}
				if( j == 0 ){
					same_low = 0 ;break;
				}
			}
		}else{
		  same_low = 0 ;
		}
		//針對Activelist 中的線段, 由Same_high~Same_low中的所有線段判斷看不看得到
		for( LineSegment *iter = Activelist ; iter!= NULL ; ){
			for( int j = same_high ; j >= same_low; j-- ){
				if( Have_overlap( &Activelist, iter , &Overlap , line[j].top, line[j].down ) ){
					insertHead_LR( &(rtable[line[j].id]), iter->id );//rs : relation table 
				}
			}
			//overlap 結算
			if( Overlap != NULL ){
				OverlapMerge_Trim( &Overlap, &Activelist , &iter );//如果有重疊的話 iter 會自動更新成iter->next 
			}else{
				iter = iter->next ;
			}
			freeList_LS( Overlap );
			Overlap = NULL ; 

		}
		//將samehigh ~ samelow 的線段放入active list
		for( int j = same_high ; j >= same_low ; j--){
			insertHead_LS( &Activelist , line[j].id, line[j].top, line[j].down);
		}	

		i = same_low -1 ;
	}
	//算完之後將 relation table 中的東西放到array中 排序後輸出
	for( i = 1 ; i <= total_point ; i++){
		fprintf(ans,"%d", i );
		int size = 0 ;//計算該linklist 長度
		for( LineRelation *iter = rtable[i] ; iter != NULL ; iter = iter->next ){
			size ++ ; 
		}
		int *rela = malloc( size * sizeof(int) ); 
		int r_iter = 0 ;
		for( LineRelation *iter = rtable[i] ; iter != NULL ; iter = iter->next,r_iter++ ){
			rela[r_iter] = iter->id ;
		}

		qsort( rela, size, sizeof(int), cmp_id_LR );
		int last = 0;
		for( r_iter = 0 ; r_iter < size ; r_iter++ ){
			if( last != rela[r_iter]){
				fprintf(ans," %d", rela[r_iter]);
			}
			last = rela[r_iter] ; 
		}

		freeList_LR( rtable[i]) ;
		free(rela);
		fprintf(ans,"\n");
	}

	//結束
	freeList_LS( Overlap );
	freeList_LS( Activelist);
	free(rtable);
	//fclose( fout);
	fclose( fin );
   return 0 ; 
}
void insertHead_LR( LineRelation ** Head, int id ){	
	//printf("Want to insert %d\n", id);
	LineRelation *n = malloc( sizeof(LineRelation) );
	n->id = id ; 
	n->prev = NULL ;
	if(  (*Head) == NULL ){
		n->next = NULL ; 
	}else{
		n->next = (*Head) ; 
		(*Head)->prev = n;
	}
	(*Head) = n ;
	return ;
}
void freeList_LR( LineRelation *iter ){
	LineRelation *next = NULL ; 
	while( iter != NULL ){
		next = iter->next ; 
		free( iter );
		iter = next ;
	}
	return ; 
}
void insertHead_LS( LineSegment ** Head,int id,int top ,int down ){
	LineSegment * n = malloc( sizeof(LineSegment) ) ;
	if( !n ){
		printf("Can't create new node\n");
		exit(0);
	}

	n->id = id ;
	n->top = top;
	n->down = down;
	n->prev= NULL;

	if( *Head == NULL ){//empty list
		n->next = NULL ;
	}else{
		n->next = *Head;
		(*Head)->prev = n ;
	}
	(*Head) = n;	//printf("create id = %d \n", (*Head)->id);
	return ; 
}
void deleteSegment( LineSegment ** Head , LineSegment ** seg ){
	if( *Head == NULL || *seg == NULL )
		return ; 
	LineSegment * del = NULL ; 
	if( (*seg)->prev ==  NULL ){//delete the (*Head) node 
		if( (*seg)->next != NULL){	
			((*seg)->next)->prev = NULL ; 
			(*Head) = (*Head)->next ; 
		}else{ //delete the list with one node
			(*Head) = NULL ; 
		}
		del = (*seg);
		(*seg) = (*seg)->next;
		free( del );
		return;
	}else if( (*seg)->next == NULL ){// delete the tail
		((*seg)->prev)->next = NULL ;
		del = (*seg);
		(*seg) = (*seg)->next;
		free( del );
		return;
	}else{ // delete the middle one 
		((*seg)->prev)->next = (*seg)->next ;
		((*seg)->next)->prev = (*seg)->prev ;
		del = (*seg);
		(*seg) = (*seg)->next;
		free( del );
		return;
	}
	return ;
}
void freeList_LS( LineSegment *iter){
	LineSegment *next; 
	while( iter != NULL ){
		next = iter->next ; 
		free( iter );
		iter = next ;
	}
	return ; 
}
void printList_LS( LineSegment *list ){
	while( list!= NULL ){
		printf("id : %d, top : %d, down : %d\n", list->id, list->top, list->down );
		list = list->next ;
	}
	printf("\n");
	return ;
}
void OverlapMerge_Trim( LineSegment **Overlap, LineSegment **Head, LineSegment ** seg ){
	if( *Overlap == NULL )
		return ;
	LineSegment *iter = *Overlap;
	LineSegment *cur = (*Overlap)->next ; 
	//先排序後再合併  
	int total = 0 ;
	for( iter = *Overlap ; iter != NULL ; iter = iter->next ){
		total++;
	}
	Line *array = malloc( total * sizeof(Line) );
	if( !array ){ printf("Overlap_merge : run out of space!!\n"); exit(0);} 
	int i = 0 ;
	for( iter = *Overlap ; iter != NULL ; iter = iter->next , i++ ){
		array[i].id = iter->id ;
		array[i].top = iter->top ;
		array[i].down = iter->down;
		array[i].x = 0; // 利用cmp_x在x相同時比top的特點
	}
	// 要注意  array 屬於Line type ,  而其他都是LineSegment type 
	qsort( array, total, sizeof(Line), cmp_x );
	for( i = 0 , iter = *Overlap ; i < total ; i++, iter = iter->next ){
		iter->id = array[i].id;
		iter->top = array[i].top;
		iter->down = array[i].down;
		//iter->x = array[i].x ;
	}
	//After Sorting, Start to merge the overlaping line in the "Overlap" list 
	for( iter = *Overlap ; iter != NULL ; iter = iter->next ){
		for( cur = iter->next ; cur!= NULL ;){
			if( iter->top >= cur->down && iter->down <= cur->down ){
				iter->top = cur->top;
				iter->down = iter->down < cur->down ? iter-> down : cur->down ;
				deleteSegment( Overlap ,&cur );//deleteSegment會將cur自動變成 cur->next 
			}else{
				cur = cur->next;
			}
		}
	}

	//輸出看看
	/*
	printf("準備剪除線段\n");
	for( iter = *Overlap ; iter != NULL ; iter = iter->next){
		printf(" id :%d, top: %d, down : %d\n", iter->id, iter->top, iter->down );
	}*/
	//準備好剪除, 備註： Overlap 的範圍不會超過該線段
	for( iter = *Overlap ; iter != NULL ; iter = iter->next){
		//下半部重疊
		if(  (*seg)->down == iter->down  ){
			if(  iter->top == (*seg)->top ){
				deleteSegment( Head, seg );//整個線段都被蓋掉
				//照理來說如果整個線段會被刪除的話,Overlap中只會有一個Node 
				free(array);
				return ; 
			}else{
				(*seg)->down = iter->top;
			}
		//中間部分重疊	 ,留下來的那段都是上半段(排序是依top值由小到大)
		}else if( (*seg)->down < iter->down && (*seg)->top > iter->top ){
			insertHead_LS( Head, (*seg)->id, iter->down, (*seg)->down );
			(*seg)->down = iter->top ; 
		//上半部重疊  
		}else{
			(*seg)->top = iter->down ; 
		}
	}
	(*seg) = (*seg)->next ;// 因為沒有 deleteSegment輔助 ,要自行更新 seg成 seg->next避免重複運算
	free(array);
}
int Have_overlap( LineSegment **Head, LineSegment * seg, LineSegment **Overlap, int top , int down ){	
	if( seg == NULL || *Head == NULL )
		return 0 ;
	if( top >= seg->top && down <= seg->down ){
		// cover the  all of the line 
		// remove this point and return 1 ;
		insertHead_LS(Overlap, seg->id, seg->top, seg->down);// inset into the overlap list
		return 1; 
	}else if( top >= seg->top && down < seg->top ){
		// overlaping the up-side part of the line 
		insertHead_LS(Overlap, seg->id, seg->top, down );
		return 1 ;
	}else if( top > seg->down && down <=  seg->down ){
		// overlaping the down-side partof the line 
		insertHead_LS(Overlap, seg->id, top, seg->down );
		return 1 ;
	}else if(  top < seg->top &&  down > seg->down ){
		// overlaping the sub-part of the  segment 
		insertHead_LS(Overlap, seg->id, top, down);
		return 1; 
	}else 
		return 0 ; 
}
int cmp_x( const void * a, const void *b ){
	Line L1 = *((Line *)a);
	Line L2 = *((Line *)b);
	if( L1.x != L2.x ){
		return L1.x - L2.x;
	}else
		return  L1.top - L2.top ;
}
int cmp_id_LR( const void *a, const void *b){
	int id1 = *((int*)a ); 
	int id2 = *((int*)b ); 
	return id1 - id2 ; 
} 
