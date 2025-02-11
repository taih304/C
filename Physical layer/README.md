# Embedded command
## system()

Run embedded Unix or Windows commands in ``C`` source code

```c
#include <stdlib.h>
int system(const char *command);
```
**Return**
* ``-1``: Error
* Status number of command when success
**Example**:
```c
system("ls"); //Run ls command
```

On Windows, the ``a.exe`` of this file will run normally in Git Bash and will result in error ``command not found`` in Command Prompt.

``system("dir")`` will run properly in [Windows Command prompt](https://github.com/TranPhucVinh/Windows-Batch).

[Use system() to start and kill a background job, which includes while(1) loop](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/Process/Background%20job/Background%20job%20with%20infinite%20loop.md):
* [Kill the infinite background job by signal](Background%20job%20with%20infinite%20loop.md#kill-the-infinite-background-job-by-signal)
* [Run the infinite background job, get its PID then kill it by functions inside in the parent process](Background%20job%20with%20infinite%20loop.md#run-the-infinite-background-job-get-its-pid-then-kills-it-by-functions-inside-in-the-parent-process)
* [Stop background_job by SIGSTOP and continue it by SIGCONT](Process/Background%20job/Background%20job%20with%20infinite%20loop.md#stop-background_job-by-sigstop-and-continue-it-by-sigcont)
## popen() and pclose()
The ``popen()`` function opens a process by creating a pipe, forking, and invoking the shell.

```c
FILE *popen(const char *command, const char *type);
```

The ``command`` argument is a pointer to a null-terminated string containing a shell command line.  This command is passed to ``/bin/sh``, then interpretation, and finally is performed by the shell.

``pclose()`` will close the pipe opened by ``popen()``.

```c
int pclose(FILE *stream);
``` 

``ls`` command

```c
#include <stdio.h>

#define ELEMENT_NUMBERS 1
#define BUFFER_SIZE 100

char buffer[BUFFER_SIZE];


int main(){
    FILE* pipe = popen("ls", "r");
    fread(buffer, BUFFER_SIZE, ELEMENT_NUMBERS, pipe);//Will read ELEMENT_NUMBERS*READ_SIZE from fp
    printf("%s\n", buffer);
    pclose(pipe);
}
```

``rm`` command:

```c
FILE* pipe = popen("rm a.out", "r");
pclose(pipe);
```

# Environment API

## printenv()

Get environment variable with ``printenv()``. ``environ`` is defined as a global variable in the ``Glibc`` source file ``posix/environ.c`` so this program just runs on Unix.

```c
#include <stdio.h>

extern char **environ;
int main(int argc, char *argv[])
{
    int count = 0;

    printf("\n");
    while(environ[count] != NULL)
   {
         printf("[%s] :: ", environ[count]);
         count++;
   }

   return 0;
}
```
## Get variable environment

``char *getenv(const char *name)`` searches for the environment string pointed to by name and returns the associated value to the string.

This run on both Windows and Unix.

```c
#include <stdio.h>
#include <stdlib.h>

int main () {
   printf("PATH : %s\n", getenv("PATH"));
   printf("HOME : %s\n", getenv("HOME"));
   printf("ROOT : %s\n", getenv("ROOT"));

   return(0);
}
```
