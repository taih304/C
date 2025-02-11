**Error when value defined outside header file**

``header.h``

```c
#include <stdio.h>
int a;
```

``header.c``

```c
#include "head.h"
a = 18;
```

``main.c``

```c
#include "head.h"

main(){
	printf("%d \n", a);
}
```

This give compile error with ``g++``

```
In file included from test.c:9:0:
head.c:5:2: error: ‘a’ does not name a type
  a = 18;
```

Compiling this on ``gcc`` won't give error and just give warning instead then runs properly

```
username@hostname~/C_GCC$ gcc main.c head.c
main.c:3:1: warning: return type defaults to ‘int’ [-Wimplicit-int]
    3 | main(){
      | ^~~~
head.c:3:1: warning: data definition has no type or storage class
    3 | a = 18;
      | ^
head.c:3:1: warning: type defaults to ‘int’ in declaration of ‘a’ [-Wimplicit-int]
username@hostname~/C_GCC$ ./a.out
18
```

### Problem solve with extern

``head.h``

```c
#include <stdio.h>

void helloworld();
extern int value;
```

``head.h`` has declared variable ``value`` by ``extern`` but not define it and allows other ``.c`` files to define it.

``head.c``

```c
#include "head.h"

int value = 16; 

void helloworld(){
	printf("%d\n", value);
}
```

Note that, to use variable ``value`` in ``g++``, it must be ``int value = 16``, not ``value = 16``. Assign ``value = 16`` just gives warning in ``gcc``.

``main.c``

```c
#include "head.h"

int main(){
	helloworld(); //16
}
```

### Multiple use with extern variable

Define variable with extern in 2 functions.

``head.h``

```c
#include <stdio.h>

void func1();
void func2();
extern int value;
```
``head.c``
```c
#include "head.h"

//define variable value in function func1
void func1(){
	int value = 18;
	printf("%d\n", value);
}

//define variable value in function func2
void func2(){
	int value = 19;
	printf("%d\n", value);
}
```
``main.c``
```c
#include "head.h"

int main(){
	func1(); //18
	func2(); //19
}
```

### main.c call variable from other file without library included

``head.h``

```c
#include <stdio.h>

int a;
```

``head.c``

```c
#include "head.h"

int a = 120;
```

``main.c``

```c
//"head.h" is not included
#include <stdio.h>

extern int a;

int main(int argc, char *argv[])
{
   printf("%d", a); //120
   return 0;
}
```
