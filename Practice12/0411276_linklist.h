#ifndef 0411276_LINKLIST 

    #define  0411276_LINKLIST
typedef struct Multi_linklist{
    int id ;
    int n; //The number of childs 
    struct Multi_linklist *next[10];
}Multi_linklist ;

tpyedef struct Node{
    int id;
    struct Node * next ;
}Node;

void insertNode();
void insertHead();
void inserback;
void freelist ;
void deleteNode;
void printList;
void isempty;



#endif
