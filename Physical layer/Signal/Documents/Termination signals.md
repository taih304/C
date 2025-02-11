# SIGKILL

Self-terminated a process after printing from ``0`` to ``10``:

```c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>   

int pid;
int number;

int main(){  
    pid = getpid();
    while (1){
        printf("%d\n", number);
        if (number == 10) kill(pid, SIGKILL);
        else number += 1;
    }
}
```
# SIGTSTP and SIGINT

Using ``Ctr+Z`` for ``SIGTSTP`` signal:

```c
void signal_handler(int signal_number){
	char displayed_string[50];
	bzero(displayed_string, 50);
	
	int sz = snprintf(displayed_string, sizeof(displayed_string), "Signal %d is caught\n", signal_number);
	write(STDOUT_FILENO, displayed_string, sz); 
}

int main(){ 
	signal(SIGTSTP, signal_handler);
	while(1);//Start an infinite loop and handle with signal
}
```

Then pressing ``Ctr+Z`` won't stop the process and just cause the program to simply print out the string ``You have entered signal number: 20``. That happen as ``Ctr+Z`` sends the suspend signal on most Linux terminals, so with the signal handler function the program won't stop execution on the terminal.

The same behavior happen with ``Ctr+C`` as ``SIGINT``:

```
//Other operations like above
signal(SIGINT, signal_handler);
//Other operations like above
```
**Result**

```
^CYou have entered signal number: 2
^CYou have entered signal number: 2
^CYou have entered signal number: 2
```
# SIGHUP
Stop a process with SIGHUP via kill command:
```c
int main() {
	while(1) {
        printf("Hello, World !\n");
        sleep(1);
	}
}
```
Run ``./a.out&`` to have process run in the background and get the PID, e.g ``1873788``.

Then run ``kill -HUP 1873788`` to stop this process.

Beside SIGHUP, SIGUSR1 and SIGUSR2 can be used to stop the above infinite process:
```sh
kill -USR1 1873830
```
```sh
kill -USR2 1873867
```
