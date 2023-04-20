#include<stdio.h>
#include<stdlib.h>

int min(int *n1,int *n2, int *n3){

	if(*n1<=*n2 && *n1<=*n3){
		return *n1;
	}
	else if(*n2<=*n1 && *n2<=*n3){
		return *n2;
	}
	else{
		return *n3;
	}
}

int max(int *n1,int *n2, int *n3){
	if(*n1>=*n2 && *n1>=*n3){
		return *n1;
	}
	else if(*n2>=*n1 && *n2>=*n3){
		return *n2;
	}
	else{
		return *n3;
	}
}

int prod (int (*min)(), int (*max)(), int *n1, int *n2, int *n3){
	int ret= min(n1,n2,n3);
	int ret2= max(n1,n2,n3);
	return ret*ret2;
}

int main(){
	int num1 = (rand() % (100 - 0 + 1)) + 0;
	int num2 = (rand() % (100 - 0 + 1)) + 0;
	int num3 = (rand() % (100 - 0 + 1)) + 0;
	printf("Numbers are: %d %d %d\n", num1,num2,num3);
	int final= prod (min, max, &num1, &num2, &num3);
	printf("Product of return values is: %d\n", final);
	return 0;
}