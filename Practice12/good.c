#include<stdio.h>
#include<stdlib.h>
tpyedef struct list{
    int id;
    struct list *next ;
}list;

void insertBack( list ** Head, list ** this){
    list * n = malloc( sizeof(list));

    if( !n ){ printf("Can't crete new node\n"); exit(0);}
    n->next = NULL ; 

    if( *Head == NULL ){
        *Head = n ;
        return ;
    }else if( (*this)->next == NULL ){
        (*this)->next = n;
    }else{
        n->next = (*this)->next ;
        (*this)->next = n;
    }
    return ;
}

void freelist( list * this ){
    list *next ; 
    while( this ){
        next = this->next ;
        free(this);
        this=next;
    }
    return 0 ; 
}
int main(int argc, char ** argv){
    FILE *fin;
    if( fin=fopen(argv[1],"r")  ){printf("Can't open %s\n", argv[1]); exit(0);}
    
    list *edge = NULL;
    
    int id; 
    list *prev 
    while( fscanf(" %d ")!= EOF ){
        for( list *iter = edge ; iter != NULL ;iter=iter->next){
        }
    }
    
    
    
    return 0 ; 
}
