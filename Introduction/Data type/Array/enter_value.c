#include <stdio.h>

main() {
	int i, n, array[100];
	printf("Enter the number of members: ");
	scanf("%d", &n);
	printf("Enter the value of each member: ");
	for (i = 0; i < n; i++){
		scanf("%d", &array[i]);
	}
	for (i=0; i < n; i++){
		printf("Value of member %d is %d \n", i, array[i]);
	}
}