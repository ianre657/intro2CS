#include<stdio.h>
#include<string.h>
#include<stdlib.h> 
#include<time.h>
#include<ctype.h>

int main(){
	time_t now;
	time(&now);
	srand(time(NULL));
	printf("Now time is %s\n\n",asctime(localtime(&now)));
	int i,j,time,flag,a,b;
	char input[10],ans[4];
	char define;
	while(1){
		
		printf("Please input a 4-digit integer. Four digits must be four different numbers.\n");
		
		ans[0] = rand() % 10;
		while(1){
			ans[1] = rand() % 10;
			if(ans[1] != ans[0])break;
		}
		while(1){
			ans[2] = rand() % 10;
			if(ans[2] != ans[0] && ans[2] != ans[1])break;
		}
		while(1){
			ans[3] = rand() % 10;
			if(ans[3] != ans[0] && ans[3] != ans[1] && ans[3] != ans[2])break;		
		}
		
		for(time = 1;; time ++){
			
			
			printf("Your 4-digit number: ");
			scanf("%s",input);
			
			a = b = flag = 0;
			for(i = 0; i < strlen(input); i ++){
				if(isalpha(input[0])){
					printf("Your input does not begin with a numerical character\n");
					system("pause");
					flag = 1;
					break;
				}
				
				if(strlen(input) != 4){
					printf("You have to input a 4-digit number.\n");
					system("pause");
					flag = 1;
					break;
				}
				
				if(isalpha(input[i])){
					printf("You have to input a 4-digit number.\n");
					system("pause");
					flag = 1;
					break;
				}
			
				for(j = i+1; j < strlen(input); j++){
					if(input[i] == input[j]){
						break;
					}
				}
				if(j != strlen(input)){
					printf("Your input number is %s.         Two digits of the input number are the same. Retry again!\n",input);
					system("pause");
					flag = 1;
				}	
			}
			if(flag == 1)
				continue;
			
			for(i = 0; i < 4; i ++){
				if(ans[i] == input[i] - '0'){
				a++;
				}
			}
		
			for(i = 0 ;i < 4; i ++){
				for(j = 0; j < 4; j++){
					if(j == i)continue;
					if(ans[i] == input[j] - '0'){
						b++;
					}
				}
			}
			printf("Your input number is %s.        You got %dA%dB.\n",input,a,b);
			if(a == 4)
				break;
		}
		
		getchar();
		printf("Congratulations! After %d trials, you got the right number!\nDo you want to play again? (y/n)",time);
		scanf("%c",&define);
		if(define == 'n')
			break;
	}
	return 0;
}
