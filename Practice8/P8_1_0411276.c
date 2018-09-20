#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int track[25] ;
int tortoise , hare;

// tortoise should not sleep during game.
enum { fastPlod=1, slip, slowPlod} tMove_t ; 
int tor_move[]={ 0, 3, -6, 1 };
char tor_move_str[4][10]={ "", "Fast Plod", "Slip", "Slow Plod" };

enum { sleep, bigHop, bigSlip, smallHop, smallSlip } hMove_t ; 
int hare_move[]={ 0, 9, -12, 1, -2};
char hare_move_str[5][10]={ "Sleep", "Big hop", "Big slip", "Small hop", "Small slip" };

//enum { river, forest, slide } terrain ;

void print_track();
int main(void){
    int cur_time =0; 
    srand( time(NULL) );
    tMove_t = sleep ;
    hMove_t = sleep ;
    while(1){
        system("clear");
        cur_time ++; 
        tortoise += tor_move[ tMove_t ]; tortoise = tortoise<0 ? 0 : (tortoise>24? 24: tortoise);
        hare    += hare_move[ hMove_t ]; hare     = hare    <0 ? 0 : ( hare>24   ? 24: hare); 
        if( cur_time == 1 ) printf("BANG!!! AND THEY'RE OFF!!!!!\n\n\n");

        if( cur_time != 1 ) printf(" Tortoise %s\n",tor_move_str[tMove_t ]);
        if( cur_time != 1 ) printf("     Hare %s\n",hare_move_str[hMove_t]);
        if( tortoise==24 || hare==24 ){
            if( tortoise == hare ) printf(" It's a tie.\n");
            else{
                printf("%s",tortoise==24? " TORTOISE WINS!!! YAY!!!\n":"");
                printf("%s",hare    ==24? " Hare wins. Yuch.\n":"");
            }
        }else if( cur_time != 1){
            printf("%s", tortoise == hare ? " OUCH!!!\n":"\n");
        }
        print_track();
        // get enter
        while(getchar()!='\n')
            ;
        if( tortoise == 24 || hare == 24)
            break;
        int r_num = rand()%10 +1 ;

        if     ( 1<=r_num && r_num <= 5)  tMove_t = fastPlod;
        else if( 6<=r_num && r_num <= 7)  tMove_t = slip;
        else if( 8<=r_num && r_num <= 10) tMove_t = slowPlod;
        r_num = rand()%10 +1 ;
        if     ( 1<=r_num && r_num <= 2)  hMove_t = sleep;
        else if( 3<=r_num && r_num <= 4)  hMove_t = bigHop;
        else if( 5<=r_num && r_num <= 5)  hMove_t = bigSlip; 
        else if( 6<=r_num && r_num <= 8)  hMove_t = smallHop;
        else if( 9<=r_num && r_num <= 10) hMove_t = smallSlip;
    }
    return 0 ;
}

void print_track(){
    for(int i=0 ; i <25 ; i++)
        printf("%3d", i+1);
    printf("\n");
    for(int i = 0; i < 25 ; i++){
        if( tortoise == i ) printf("  T");
        else printf("   ");
    } printf("\n");
    for(int i = 0; i < 25 ; i++){
        if( hare == i ) printf("  H");
        else printf("   ");
    } printf("\n");
    return ;
}
