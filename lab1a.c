#include<stdio.h>
#include<stdlib.h>

int main(){
	int n;
	printf("Enter the size of array:\n");
	scanf("%d",&n);
	int *ar;
	ar = (int*)malloc(sizeof(int)*n);
	for(int i=0; i<n; i++){
		printf("Enter the %d element:\n",i);
		scanf("%d",&ar[i]);
	}
	for(int i=n-1; i>=0; i--){
		printf("%d element is: %d\n",i,*(ar+i));
	}
	return 0;
}