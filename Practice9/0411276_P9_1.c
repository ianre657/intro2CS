#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#define MAX_ROW 100000
#define MAX_LEN 100

char article[1000000];
typedef struct{
    int id ;
    char word[MAX_LEN];
    int  times ;
    int  weight; 
}keyword;

keyword token[MAX_ROW];

char sample[MAX_ROW][MAX_LEN];// E-mail file 
unsigned total_appear =0; // Total times token appearing.
unsigned total_key ;
unsigned total_word ; 
unsigned total_sample ;
float  total_weight = 0 ;
float  spam_threshold  = 1.0 ; 




int KeyWordFile_Read( char *keyFile, keyword *key_array );
void get_option(int argc, char** argv);
int cmp_keyword( const void *k1 , const void *k2 );// Decending order according to keyword.times.
int cmp_id( const void *k1 , const void *k2 );// Decending order according to keyword.times.

int cmp_keyword( const void *k1 , const void *k2 ){
    return (  ((keyword*)k2)->times  - ((keyword*)k1)->times );
}
int cmp_id( const void *k1 , const void *k2 ){
    return (  ((keyword*)k1)->id  - ((keyword*)k2)->id );
}

int mode_occur = 0 ;
int mode_checkSpam = 0 ;
void init(void); 
int main( int argc, char ** argv ){
    get_option( argc, argv); 
    char word_c[MAX_LEN], token_c[MAX_LEN];

    for( int i =0 ; i < total_sample ; i++){
        FILE *fin;
        char word[MAX_LEN];
        init();// initialize 
        if( ( fin=fopen( sample[i], "r") ) == NULL ){
            printf("Error opening e-mail  file : %s\n", sample[i] );
            continue; 
        }else{
            int in = 0 ;
            while( (in = fscanf(fin,"%[^ ,.:;?!\'\"()*\r\n]s", word ) )!= EOF ){
                fscanf(fin,"%*[ ,.:;?!\'\"()*\r\n]s");
                if( in ==0 ) 
                    continue ;
                total_word ++ ;
                //printf("   WORD=\"%s\"\n",word);
            int iter = 0 ;
            while(word[iter]){
                word_c[iter] = (word[iter]);
                iter ++ ;
            }
            word_c[iter]='\0';
            //printf("Word = \"%s\"\n", word_c);
            //puts( word_c);
                qsort( (void*)token, total_key-1, sizeof(keyword), cmp_id );
                for(int j=0; j< total_key; j++){
                    iter = 0 ;
                    while(token[j].word[iter]){
                        token_c[iter] = (token[j].word[iter]);
                        iter ++ ;
                    }
                    token_c[iter]='\0';
                    //printf("token = \"%s\"\n", token_c);
                    if( !strcmp( word_c, token_c ) ){
                        token[j].times ++ ;
                        total_appear++ ; 
                    }else if( strstr( word_c, token_c) ){
                        token[j].times ++ ;
                        total_appear++ ; 
                        break;
                    }
                }
            }
            qsort( (void*)token, total_key-1, sizeof(keyword), cmp_keyword);
            //printf("total word %5d\n", total_word ); 

            int  j = 0;
            float weight  =1 ; 
            if( mode_checkSpam ){
                // calculate for total spam weight 
                for( j=0; j<total_key ; j++){
                    if( token[j].times == 0 )
                        break; 
                    weight =  1 ;
                        //weight = ( pow(token[j].times, 1.2) /(float)total_word ) * token[j].weight ;
                        weight = ( token[j].times /(float)total_word ) * token[j].weight ;
                        //printf("%15s weight : %8.4f\n", token[j].word,  weight );
                        total_weight += weight ; 
                        
                }
            }
            /*
            printf("Total appear: %d\n", total_appear); 
            for(int j=0 ; j< total_key; j++){
                printf("  %15s : %4d\n", token[j].word, token[j].times);
            }
            */
            //output
            printf("Email \"%s\" : processing DONE.\n", sample[i]);
            if(mode_occur|| mode_checkSpam){
                printf("****=========================================================================****\n");
                //printf("Statics for \"%s\"\n", sample[i]);
                if( mode_checkSpam ){
                    //printf("   Total weight : %18.8f\n", total_weight );
                    //printf("   Spam thershold :     %12.8f\n", spam_threshold );
                    printf("\"%s\" %3s\n",sample[i], total_weight>= spam_threshold? "Is a Spam email!!": "Is a normal email");
                    printf("\n");    
                }
                if( mode_occur ){
                    printf("   Key Word Occurence :\n");
                    for(int j =0; j<total_key ;j++){
                        //if( token[j].times <=  0 )
                        //    break;
                        //else 
                            printf("  %15s : %4d", token[j].word, token[j].times);
                        if( j%3 == 2 )
                            printf("\n");
                    }
                    printf("\n");
                }
                 printf("\n\n\n");
                

            }
        }   

        fclose(fin);
    }
    return 0; 
}

void get_option(int argc, char** argv){
    int count = 0 ;
    for( int i = 1 ; i < argc; ){
        if( argv[i][0] == '-'){
            switch( argv[i][1] ){
                case 'k':
                        KeyWordFile_Read( argv[i+1], token );                    
                    i += 2  ; 
                    break;
                case 'e':
                    
                    //count = atoi(&argv[i][2]);
                    count = 1; 
                    for( int j = 0 ; j < count ; j++ ){
                        strncpy( sample[total_sample], argv[i+j+1], MAX_LEN);
                        total_sample++;
                        //sample[total_sample++] = argv[i+j+1];
                    }
                    i += count +1 ; 
                    break;
                    
                    /*    
                                    
                    strncpy( sample[total_sample], argv[i+1], MAX_LEN);
                    total_sample++;                    
                    i += 2 ; 
                    break;
                    */
                    
                case 'o':
                    if( !strcmp(argv[i],"-oc")){
                        mode_occur = 1; 
                    }
                    else{
                        printf("Can't not find %s option.\n", argv[i]);
                    }
                    i++;
                    break;
                case 's':
                    if( !strcmp(argv[i],"-spam"))
                        mode_checkSpam = 1; 
                    else
                        printf("Can't not find %s option.\n", argv[i]);
                    i++;
                    break;
                default:
                    printf("do not find %s option.\n", argv[i]);
                    i++;
                    break;
            }
        }else{
            printf("Can't resolve  %s.\n", argv[i]);
            i++;
        }
    }
    return ; 
}

int KeyWordFile_Read( char *keyFile, keyword *key_array ){
    int weight = 0 ; 
    FILE *key_in ;
    if( ( key_in = fopen( keyFile, "r") ) == NULL ){
        printf("Error opening KeyWord file : %s\n", keyFile );
        return -1; 
    }
    unsigned  i = total_key ;
    while(1){
        fscanf(key_in, "%d", &weight );
        if( weight == -999 || i>= MAX_ROW  )
            break ; 
        key_array[i].weight = weight; 
        fscanf(key_in," %s", key_array[i].word);
        //printf("word = \"%s\" \n", key_array[i].word );
        i++; 
    }
    total_key = i ;
    fclose(key_in);
    return 0 ;
}

void init(void){
        total_word = 0 ;
        total_weight = 0 ;
        total_appear = 0 ;
        for(int i =0 ; i< MAX_ROW ; i++){
            token[i].times = 0 ; 
        }
        return ;
}
