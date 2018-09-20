#include<stdio.h>
#include<stdlib.h>
#include<time.h>
// track length 
#define LEN 60
int track[LEN] ;
int tortoise , hare;

// tortoise should not sleep during game.
enum { fastPlod=1, slip, slowPlod} tMove_t ; 
int tor_move[]={ 0, 3, -6, 1 };
char tor_move_str[4][10]={ "", "Fast Plod", "Slip", "Slow Plod" };


enum { sleep, bigHop, bigSlip, smallHop, smallSlip } hMove_t ; 
int hare_move[]={ 0, 9, -12, 1, -2};
char hare_move_str[5][10]={ "Sleep", "Big hop", "Big slip", "Small hop", "Small slip" };
int  h_slow_round , h_bigHop_times=0, h_hurt=0 , h_sleep = 0 ; 
float h_speed = 1.0;

enum { river, forest, slide } terrain ;

void print_track();
void generate_terrain();
void hare_status_check();
int main(void){
    int cur_time =0; 
    srand( time(NULL) );
    generate_terrain();
    tMove_t = sleep ;
    hMove_t = sleep ;
    while(1){
        system("clear");
        cur_time ++; 
        hare_status_check();

        tortoise += tor_move[ tMove_t ];
        tortoise = tortoise<0 ? 0 : (tortoise>LEN-1? LEN-1: tortoise);
        hare += hare_move[ hMove_t ]*h_speed; 
        hare = hare <0 ? 0 : ( hare>LEN-1 ? LEN-1: hare); 


        if( cur_time == 1 ) printf("BANG!!! AND THEY'RE OFF!!!!!\n\n\n\n");

        if( cur_time != 1 ) printf(" Tortoise %s\n",tor_move_str[tMove_t ]);
        if( cur_time != 1 ) printf("     Hare %s\n",hare_move_str[hMove_t]);
        if( tortoise==LEN-1 || hare==LEN-1 ){
            if( tortoise == hare ) printf(" It's a tie.\n");
            else{
                printf("%s",tortoise==LEN-1? " TORTOISE WINS!!! YAY!!!\n":"");
                printf("%s",hare    ==LEN-1? " Hare wins. Yuch.\n":"");
            }
        }else if( cur_time != 1){
            printf("%s", tortoise == hare ? " OUCH!!!\n":"\n");
            printf("%s", h_hurt == 1 ?" Hurt!!!\n":"\n");
            if( h_hurt ) h_hurt = 0 ;
        }
        print_track();
        // get enter
        while(getchar()!='\n')
            ;
        if( tortoise == LEN-1 || hare == LEN-1)
            break;
        int r_num;

        // Tortoise  move 
        if( track[ tortoise] == river  ){
            tMove_t = fastPlod;
        }else{
            r_num= rand()%10 +1 ;
            if     ( 1<=r_num && r_num <= 5)  tMove_t = fastPlod;
            else if( 6<=r_num && r_num <= 7)  tMove_t = slip;
            else if( 8<=r_num && r_num <= 10) tMove_t = slowPlod;
        }

        // Hare move 
        if( track[hare] == river ){
            h_slow_round  = 2; 
        }
        if( hare == tortoise && cur_time != 1 ){
            h_hurt = 1;
            h_sleep = 1 ;
            hMove_t =  sleep ;
            //  h_sleep ==1 only when hare got sleep status.
        }else if( (track[hare] == forest  || h_bigHop_times >= 2)&& h_sleep == 0){
            h_sleep = 1; 
            hMove_t = sleep;
        }else{
            if( h_sleep ==1 )
                h_sleep = 0 ;
            r_num = rand()%10 +1 ;
            if     ( 1<=r_num && r_num <= 2)  hMove_t = sleep;
            else if( 3<=r_num && r_num <= 4)  hMove_t = bigHop;
            else if( 5<=r_num && r_num <= 5)  hMove_t = bigSlip;
            else if( 6<=r_num && r_num <= 8)  hMove_t = smallHop;
            else if( 9<=r_num && r_num <= 10) hMove_t = smallSlip;
        }
    }
    return 0 ;
}

void print_track(){
    if( tortoise < 25 && hare < 25 ){
        for(int i=0 ; i < 25 ; i++)
            printf("%3d", i+1);
        printf("\n");
        for(int i=0 ; i < 25 ; i++){
            switch( track[i] ){
                case river:  printf("  R");break;
                case forest: printf("  F");break;
                case slide:  printf("  S");break;
            }
        } printf("\n");

        for(int i = 0; i < 25 ; i++){
            if( tortoise == i ) printf("  T");
            else printf("   ");
        } printf("\n");
        for(int i = 0; i < 25 ; i++){
            if( hare == i ) printf("  H");
            else printf("   ");
        } printf("\n");
    }else{
        int min = tortoise < hare ? tortoise : hare;   
        int max = tortoise > hare ? tortoise : hare;
        int i=0 , p = 0 ;
        for( i = min ; i <= max ; i++ ){
            printf("%3d", i+1);
            p++;
            if( p >= 25 ) break;
        } printf("\n"); p = 0 ;
        for(int i=min ; i <= max ; i++){
            switch( track[i] ){
                case river:  printf("  R");break;
                case forest: printf("  F");break;
                case slide:  printf("  S");break;
            }
            p++;
            if( p >= 25 ) break;
        } printf("\n"); p=0;

        for(i = min; i <= max ; i++){
            if( tortoise == i ) printf("  T");
            else printf("   ");
            p++;
            if( p >= 25 ) break;
        } printf("\n");  p=0;
        for(i = min; i <= max ; i++){
            if( hare == i ) printf("  H");
            else printf("   ");
            p++;
            if( p >= 25 ) break;
        } 
        printf("\n");p=0;
        //second line 
        if( i < max ){
            printf("=========================\n\n");
            min = i+1 ;
            for( i = min ; i <= max ; i++ ){
                printf("%3d", i+1);
                p++;              
                if( p >= 25 ) break;
            } printf("\n"); p = 0 ;
            for(int i=min ; i <= max ; i++){
                switch( track[i] ){
                    case river:  printf("  R");break;
                    case forest: printf("  F");break;
                    case slide:  printf("  S");break;
                }
                p++;              
                if( p >= 25 ) break;
            } printf("\n"); p=0; 

            for(i = min; i <= max ; i++){
                if( tortoise == i ) printf("  T");
                else printf("   ");
                p++;
                if( p >= 25 ) break;
            } printf("\n");  p=0;
            for(i = min; i <= max ; i++){
                if( hare == i ) printf("  H");
                else printf("   ");
                p++;
                if( p >= 25 ) break;
            } printf("\n"); p=0;
        }
        //Thied line 
        if( i < max ){
            printf("=========================\n\n");
            min = i+1 ;
            for( i = min ; i <= max ; i++ ){
                printf("%3d", i+1);
                p++;              
                if( p >= 25 ) break;
            } printf("\n"); p = 0 ;
            for(int i=min ; i <= max ; i++){
                switch( track[i] ){
                    case river:  printf("  R");break;
                    case forest: printf("  F");break;
                    case slide:  printf("  S");break;
                }
                p++;              
                if( p >= 25 ) break;
            } printf("\n"); p=0; 

            for(i = min; i <= max ; i++){
                if( tortoise == i ) printf("  T");
                else printf("   ");
                p++;
                if( p >= 25 ) break;
            } printf("\n");  p=0;
            for(i = min; i <= max ; i++){
                if( hare == i ) printf("  H");
                else printf("   ");
                p++;
                if( p >= 25 ) break;
            } printf("\n"); p=0;
        }

    }
    return ;
}

void generate_terrain(){
    int r_num ;
    for( int i=0 ; i< LEN ; i++ ){
        r_num = rand()%10 +1 ;
        if     ( 1<=r_num && r_num <= 2)  track[i]=river;
        else if( 3<=r_num && r_num <= 4)  track[i]=forest;
        else if( 5<=r_num && r_num <= 10) track[i]=slide;
    }
    return ;
}
void hare_status_check(){
    if( hMove_t == bigHop ) h_bigHop_times++;
    else h_bigHop_times = 0 ;

    if( h_slow_round > 0 ){
        h_speed = 0.5;
        h_slow_round-- ;
    }else{
        h_speed = 1.0;
    }

    return ;
}
