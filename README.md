# C

## Compile

### Compile code C in sublime text, notepad, gedit,...

follow this link:
[How to Compile and Execute C/C++ Program On Ubuntu using Terminal Gedit, Sublime Text Editor](https://www.youtube.com/watch?v=QU8arxnpfhA)

Shell
```shell
{
"cmd" : ["gcc", "$file_name", "-o", "${file_base_name}", "-lm", "-Wall"],
"selector" : "source.c",
"shell":false,
"working_dir" : "$file_path"
}
```
To run the code: cd to current c workspace:

then type: ./<name of project>

### Compile C++, C on terminal

```shell
g++ -o output_file file.cpp
```
Then
``
./output_file
``

**Reference:** [Sublime text 3 - compile program and run in terminal](https://stackoverflow.com/questions/21196077/sublime-text-3-compile-program-and-run-in-terminal)

Format code: [Sublime Text 2 & 3 AStyle Formatter Plugin](https://packagecontrol.io/packages/SublimeAStyleFormatter)

Ctrl +alt +f
  
## Library

**stdio.h:** standard io

## Data Type

### char

can store character or integer value

`````c
// character
char c;
c = 'a';
printf("Character %c ", c);
`````

`````c
// integer
char c;
c = 8;
printf("Integer %d ", c);
`````

**Notes**

``char c ='ab'`` => Warning "character constant too long for its type"
=> WRONG

So, char in C go only with one word.

#### Print out

```c
char hw[] = "Hello, World!";
	printf("%s ", hw);
```

### float and double

**double** can also be declared as **long float**.

```
float -> %f

double -> %lf
```

### static

**static:** local variable but the value remain unchanged in a function

## BEGINNER

#### scanf

`````c
scanf("%d ", &a);
`````
You have to type value a; then type one more to finish command although the value of **a** is still printed out correctly. To print out the value of **a** just after typing it, delete the space after %d

`````c
scanf("%d", &a);
`````

**Example**

`````c
#include <stdio.h>

void main() {
	int a;
	scanf("%d ", &a);
	printf("%d",a);
}
`````

#### printf

`````c
printf("%d ", a) // int
printf("%s ", a) // string
`````

### COMPARE

| C | JavaScript|
| ------- |:------:|
|int a = 8; | var a = 8;|
| printf("%d ",a)    | console.log(a)    |

**" " and ' '**

* ' ' is for character

* " " is for string

## CHEATSHEAT

#### gets()

**gets()** is used to enter a string

`````c
#include <stdio.h>

int main () {
   char str[50];

   printf("Enter a string : ");
   gets(str);

   printf("You entered: %s", str);

   return(0);
}
`````
**Result**

```
Enter a string : tutorialspoint.com

You entered: tutorialspoint.com
```
