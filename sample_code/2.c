#include<stdio.h>
#include<ctype.h>
int main()
{
  while(1){
    char input=0;
    printf("Please input Y/N/y/n:\n");
    while(isalnum(input)==0){
      scanf("%c",&input);
    }
    if(isdigit(input))
      printf("Your input is a number character. Please input y or n but not a number character.\n");
    else if(isalpha(input)){
      if(tolower(input)=='y'||tolower(input)=='n'){
        printf("Correct!\n");
        break;
      }
      else 
        printf("Your input is alphabet,but we want Y/N/y/n.\n");
    }
  }
  return 0;
}

