# Create

For a 2 dimension array with ``row`` and ``column`` on heap memory: Check [Create a 2 dimension int array with malloc() document](../../Physical%20layer/Memory/Dynamic%20memory%20allocation/API.md#create-a-2-dimension-int-array-with-malloc).

## Create a 2 dimension array with row stored on stack memory and column stored on heap memory

```c
#include <stdio.h>
#include <stdlib.h>

#define COLUMN_SZ 3
#define ROW_SZ 2

int main(){
	int *array[COLUMN_SZ];

	for (int column = 0; column < COLUMN_SZ; column++){
		array[column] = (int*) malloc (ROW_SZ * sizeof(int));
	}

	int number = 0;
	for (int row = 0; row < ROW_SZ; row++){
		for (int column = 0; column < COLUMN_SZ; column++){
			array[row][column] = number++; // Assign number to array[row][column] then increase number by 1
		}
	}

    for (int column = 0; column < COLUMN_SZ; column++){
		free(array[column]);
	}
}
```

## Create a char pointer with row stored on stack memory and column stored on heap memory

```c
char *string_array[3] = {"string 1", "string 2", "string 3"};
```

This gives no error in GCC and gives warning in G++:

```
warning: deprecated conversion from string constant to ‘char*’ [-Wwrite-strings]
```

```c
#include <stdio.h>

char *string_array[3] = {"string 1", "string 2", "string 3"};

int main() {
	for (int i=0; i < 3; i++){
		printf("string_array[%i]: %s \n", i, string_array[i]);
	}

	//Get value of index 2
	printf("string_array[2]: %s\n", *(string_array + 2));

	//Get a character inside the string: 
	printf("string_array[2][2]: %c\n", (*(string_array + 2))[2]);
}
```

Dynamically create:

```c
#include <stdio.h>

#define STRING_SIZE	10
#define ARRAY_SIZE	3

char *string_array[ARRAY_SIZE];

int main() {
	for (int i=0; i < ARRAY_SIZE; i++){
		string_array[i] = (int*) malloc(STRING_SIZE * sizeof(int));
		strcpy(string_array[i], "Hello, World");
	}

	for (int i=0; i < ARRAY_SIZE; i++){
		printf("%s\n", string_array[i]);
	}
}
```


Or the value can be simply set:

```c
//Other operations are like above
for (int i=0; i < ARRAY_SIZE; i++){
	string_array[i] = "Hello, World";
}
//Other operations are like above
```
**Unable to get total elements**: There is no built-in functions or specific method in C to get the total member of a char pointer array or [a double pointer](../../Physical%20layer/Memory/Pointer/Pointer%20to%20pointer.md) char.
# 2D array as a function parameter

A 2 dimension array declared by pointer to pointer can be passed into functions:

```c
#include <stdio.h>
#include <stdlib.h>

#define ROW_SIZE 	2
#define COLUMN_SIZE 	3

void intArray(int **array);

int main()
{  
	int **int_array = (int**) malloc(ROW_SIZE * sizeof(int*));

	for (int row = 0; row < ROW_SIZE; row++){
		int_array[row] = (int*) malloc(COLUMN_SIZE * sizeof(int));
	}

	int index = 0;
	for (int row = 0; row < ROW_SIZE; row++){
		for (int column = 0; column < COLUMN_SIZE; column++){
			int_array[row][column] = index;
			index += 1;
		}	
	}

	intArray((int**)int_array);//array[1][2] 5
}

void intArray(int **array){
	printf("array[1][2] %d\n", array[1][2]);
}
```

Char pointer array with row stored on stack memory and column stored on heap memory as function argument:

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRING_SIZE	10
#define ARRAY_SIZE	3

char *string_array[ARRAY_SIZE];
void set_value(char *array[ARRAY_SIZE]);

int main() {
	set_value(string_array);
	for (int i=0; i < ARRAY_SIZE; i++){
		printf("%s\n", string_array[i]);
	}

    //free memory
    for (int i=0; i < ARRAY_SIZE; i++){
		free(string_array[i]);
	}
}

void set_value(char *array[ARRAY_SIZE]){
	for (int i=0; i < ARRAY_SIZE; i++){
        string_array[i] = (char*) malloc(STRING_SIZE * sizeof(char));
        strcpy(string_array[i], "set_value");
	}
}
```
