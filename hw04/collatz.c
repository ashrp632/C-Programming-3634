#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv){
  int n,i,arr[100];
  n = atoi(argv[1]);
  if(argc > 2 || n < 0) {
    printf("Not a valid input. Try a single positive integer.\n");
  }
    else {
      printf("%d,", n);
      while(n>1) {
	if (n % 2==0){
	  n = n/2;
	  if(n==1){
	    printf("%d", n);
	  }
	  else{
	    printf("%d,", n);
	  } 
	}
	else{
	  n = n*3+1;
	  printf("%d,", n);
	}
      }
      printf("\n");
      return 0;
    }
}
  
  
