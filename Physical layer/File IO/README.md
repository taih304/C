# Fundamental concepts

File is an instance of an OS object, like process, device, data,...

**File descriptor** is a (usually small) non-negative integer in your application that refers to the file description in the kernel. **File description** is the structure in the kernel that maintains the state of an open file (its current position, blocking/non-blocking, etc.). In Linux kernel, file descripion is [struct file](https://github.com/TranPhucVinh/C/tree/master/Kernel/Character%20device/Character%20device%20operations/Basic%20operations).

# Read entered value from stdin/stream in

Method to read entered value from stdin/stream in with fix bufffer size to store the entered string/value:
* [scanf()](stdio/stdin%20and%20stdout%20API.md#scanf) and [fgets()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/stdio/File%20pointer%20API.md#fgets)
* [read() system call with stdin (STDIN_FILENO) or /dev/tty file descriptor to read the entered string in terminal](System%20call/Device%20file%20operations.md#terminal-operations)
* [gets() (deprecated) to read entered string](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/stdio/stdin%20and%20stdout%20API.md#gets-and-puts), [getchar() to read entered char](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/stdio/stdin%20and%20stdout%20API.md#getchar-putchar)

To read the entered string from stdin/stream in to store into a char pointer by dynamically allocating with [realloc](../Memory/Dynamic%20memory%20allocation/API.md#realloc), check [realloc_string_entered.c](realloc_string_entered.c).
