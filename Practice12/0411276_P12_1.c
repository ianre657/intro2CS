#include<stdio.h>
#include<stdlib.h>

char *outfile = "task.out" ;
int main(int argc, char ** argv){
    FILE *fin , *fout ;
    if( !(fin=fopen(argv[1],"r") ) ){ printf("Can't open %s\n", argc[1]); exit(1); } 
    if( !(fout=fopen(outfile,"w")) ){ printf("Can't open %s\n", outfile); exit(1); } 

    return 0 ;
}
