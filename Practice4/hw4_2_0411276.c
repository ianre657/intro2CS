#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_YEAR 9999
#define BFR_SZ 100

//ANSI code 
	#define NONE "\033[m"
//FONT
	#define F_RED "\033[0;32;31m"
	#define F_DGRAY "\033[90m"
//Back ground
	#define B_BLUE "\033[5;44m" 

char bfr[BFR_SZ];

typedef struct date{
	int y ;
	int m ;
	int d ;
 	int weekday ;
}date;
						       // 0, Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec 
const int days_in_month[2][13]={ {0,  31,  28,  31,  30,  31,  30,  31,  31,  30,  31,  30,  31},
   								 {0,  31,  29,  31,  30,  31,  30,  31,  31,  30,  31,  30,  31} };
const char days_in_week[7][4] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
int weekday_between( const date d1, const date d2 ); // return the weekday between these two date in mod 7(d2-d1 is always positive)
int positive_mod( const int i  , const int n);// return positive mod in order to count backward
int is_leap_year( const int year);// Use Georian calendar model 
int readInt( int * );
void print_day( const int day, const int weekday, int dark_font );
void print_nextLine(void);


int main(void){
	int y,m,d=1;
	int weekday = 0;
	date known = { .y= 2016, .m= 10, .d=15, .weekday=6};// 2016/10/15 is Saturday

	while(1){
		int in_m,in_y;
		printf("Please input the month and year of the calendar you want to print.\nMonth: ");
		in_m = readInt(&m);
		printf("Year: ");
		in_y = readInt(&y);
		if( in_m == -1 || in_y == -1 ||  y <1 || y> MAX_YEAR || m<1 || m>12 )
			printf("Invalid date.\n");
		else
			break;
	}
//	printf("%d %s\n",y, is_leap_year(y)?"is leap yeer":"is not leap year" );
	weekday = known.weekday ; 
	date want ={ .y=y, .m=m , .d = d};
	if( (y < known.y) || ( y==known.y && m< known.m) || ( y== known.y && m== known.m && d <= known.d)  ){
		weekday += positive_mod( -1*weekday_between( want, known),7 );
	}else if( (y > known.y) || ( y==known.y && m > known.m) || ( y== known.y && m== known.m && d > known.d) ){
		weekday += weekday_between( known, want) %7 ;
	}
	weekday %= 7;
 //   printf("weekday : %d\n",weekday );
 //   printf("%d/%d/%d, is %s\n", d,m,y, days_in_week[weekday]);

	printf("%2d/%4d"  F_RED"  Sun" NONE "  Mon  Tue  Wed  Thu  Fri" F_RED"  Sat"NONE,m,y);
	print_nextLine();

	int p_mon  = want.m -1;
	if( want.m ==1 )
		p_mon = 12;

	if( weekday != 0){
		for( int i = 0 ; i < weekday  ; i++ )
			print_day( days_in_month[is_leap_year(want.y)][p_mon]-weekday+i+1,i , 1);
	}
	int wk_now = weekday; 
	for( int i = 1 ; i <= days_in_month[is_leap_year(want.y)][want.m]; i++ ){
		print_day( i, wk_now++ ,0 );
		if( wk_now >=7  ){
			wk_now %= 7 ;
			print_nextLine();
		}
	}
	if( wk_now != 0 ){
		int n_date ; 
		for( int i = wk_now, n_date =1  ; i<= 6 ; i++, n_date++){
			print_day( n_date, i, 1);
		}
	}

	printf("\n");
	return 0 ; 
}
void print_nextLine(void){
	printf("\n       ");
	return ;
}
void print_day( const int day, const int weekday, int dark_font ){
	if( (weekday == 0 || weekday == 6) && dark_font ==1  )
		printf(B_BLUE F_DGRAY "%5d" NONE, day);
	else if( (weekday == 0 || weekday == 6) && dark_font == 0 )
		printf(B_BLUE  "%5d" NONE, day);
	else if( dark_font == 1)
		printf(F_DGRAY  "%5d" NONE, day);
	else 
		printf("%5d",day);
	return ; 
}

int positive_mod( const int i  , const int n){
	int tmp = i%n;
	return tmp >= 0? tmp : tmp+n ;
}
int is_leap_year( const int year){
	return ( ( year%4==0 && year%100!=0)|| year%400 == 0 ) ? 1 : 0 ;
}
int weekday_between( const date d1, const date d2 ){
	int wk_bt=0  ;
	//count backword , include the same day
	if( (d1.y < d2.y) || ( d1.y==d2.y && d1.m< d2.m) || ( d1.y== d2.y && d1.m== d2.m && d1.d <= d2.d)  ){
		if( d1.y < d2.y){
			//day
			wk_bt +=  days_in_month[ is_leap_year(d1.y) ][d1.m] - d1.d  ;
			//mon
			for( int i = d1.m+1 ; i <= 12; i++){
					wk_bt +=  days_in_month[ is_leap_year(d1.y) ][i]  ;
			}
			//year
			for( int i = d1.y+1; i<d2.y;i++){
				if( is_leap_year(i) )
					wk_bt += 2;// 366 mod 7
				else 
					wk_bt += 1;// 365 mod 7 
			}
			wk_bt %= 7;
		}
		//wk_bt have accumulated d2.y 
		if( (d1.y < d2.y) || ( d1.y==d2.y && d1.m < d2.m) ){
			if( d1.y==d2.y && d1.m < d2.m ){
				wk_bt +=  days_in_month [ is_leap_year(d2.y)][d1.m] -  d1.d; 
				for ( int i = d1.m+1 ; i< d2.m ;i++)
					wk_bt += days_in_month[ is_leap_year(d2.y) ][i] ;
			}else{
				for( int i = 1; i < d2.m; i++){
						wk_bt += days_in_month[ is_leap_year(d2.y) ][i] ;
				}
			}
		}
		//"wk_bt" have accumulated to d2.m 
		if( (d1.y < d2.y) || ( d1.y==d2.y && d1.m < d2.m) || ( d1.y== d2.y && d1.m== d2.m && d1.d <= d2.d) ){
			if( d1.y== d2.y && d1.m== d2.m && d1.d <= d2.d )
				wk_bt += d2.d - d1.d; 
			else
				wk_bt += d2.d ; 
		}
	}
	return  wk_bt % 7 ; 
}
int readInt( int *rd_in ){
    int in = 0 ;

	fgets( bfr, BFR_SZ,stdin);
	if( bfr[strlen(bfr)-1] == '\n' ){
		bfr[strlen(bfr)-1] = '\0';
	}else{
		while( getchar() != '\n')
			;
	}
	//printf("bfr=\"%s\"\n",bfr);
	int legal = 1 ,space_head = 1,start_rd = 0,end_rd = 0  ; 
	for( int i = 0 ; bfr[i]!='\0';i++ ){
		// don't allow any character exist
		if( !( isspace( bfr[i]) || isdigit(bfr[i]) ) ){
			legal = 0 ; break;
		}else if( space_head ==1  && isspace( bfr[i]) ){
			continue;
		}else if( end_rd == 1 && !isspace(bfr[i]) ){
			legal = 0 ; break;
		}else if( isdigit(bfr[i]) ){
			if( space_head == 1 ){
				space_head = 0 ;start_rd = 1; in++;
			}
			continue;
		}else if( !isdigit(bfr[i]) && start_rd ==1 ){
			start_rd = 0 ; end_rd = 1 ; continue;
		}

	}
	if( legal == 0 ){
		return  -1 ; 
	}else{
		*rd_in = atoi(bfr);
	}
	return in ; 
}
