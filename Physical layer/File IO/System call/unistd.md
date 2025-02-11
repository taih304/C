# read()

```c
ssize_t read(int fd, void *buf, size_t count);
```

Read up to ``count`` bytes from file descriptor ``fd`` into the buffer``buf``. ``read()`` returns the number of bytes actually read. If no further bytes could be read (i.e., end-of-file was encountered), ``read()`` returns 0.

# write()

Writes up to ``count`` bytes from the buffer starting at ``buf`` to the file referred to by the file descriptor ``fd``.

```c
ssize_t write(int fd, const void *buf, size_t count);
```

Write a string to screen

```c
char displayedString[] = "Hello, World !";
write(STDOUT_FILENO, displayedString, sizeof(displayedString));
write(STDOUT_FILENO, "Display string", 14);
```

This function can be used to write string to a file: ``./a.out > temp.txt``

By using ``/dev/tty``:

```c
char displayedString[] = "Hello, World ! a new string";
int fileDescriptor = open("/dev/tty", O_WRONLY);//Write only
write(fileDescriptor, displayedString, sizeof(displayedString));
```

To append to write with ``O_APPEND``:

```c
fd = open("test.md", O_WRONLY | O_APPEND);//Flag O_APPEND must OR with O_WRONLY. If using only O_APPEND, file can't be written
```

# close()

Close a file descriptor, so that it no longer refers to any file and may be reused. 

```c
int close(int fd);
```
# unlink()

Deletes a name (with ``pathname``) from the filesystem

```c
int unlink(const char *pathname);
```

* ``0``: success
* ``-1``: error

```c
#define FILE_NAME 		"delete.txt"

int main(int argc, char *argv[])  {
	if (unlink(FILE_NAME) == -1) printf("Unable to remove file");
}
```

# lseek()

```c
off_t lseek(int fildes, off_t offset, int whence);
```

Reposition read/write file ``offset``

| whence | Description|
| ------- |:------:|
|SEEK_SET | The offset is set to offset bytes|
|SEEK_CUR|The offset is set to its current location plus offset bytes|
|SEEK_END|The offset is set to the size of the file plus offset bytes|

**Return**: Upon successful completion, ``lseek()`` returns the resulting offset location as measured in bytes from the beginning of the file. On error, the value (``off_t``) -1 is returned and ``errno`` is set to indicate the error.

Implementations of ``whence``:
* ``SEEK_SET``: [Read a file from a specific index](File%20operations.md#open-a-file-to-read)
* ``SEEK_END``: [Read the whole file into a char pointer without knowing its type (char *read_file(char *filename))](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/stdio/basic_file_operations.c)

# pread() and pwrite()

``pread()``: Returns number of bytes read, 0 on EOF, or –1 on error

```c
ssize_t pread(int fd , void * buf , size_t count , off_t offset );
```
``pwrite()``: Returns number of bytes written, or –1 on error

```c
ssize_t pwrite(int fd , const void * buf , size_t count , off_t offset );
```

As ``pread()`` and ``pwrite()`` work with ``lseek()``, they doesn't operate with ``/dev/tty``.

# truncate() and ftruncate()

The ``truncate()`` and ``ftruncate()`` system calls set the size of a file to the value specified by length.

```c
int truncate(const char * pathname , off_t length );
int ftruncate(int fd , off_t length );
```

If the file is longer than ``length``, the excess data is lost. If the file is currently shorter than length, it is extended by padding with a sequence of null bytes or a hole.

# dup() and dup2()

The ``dup()`` system call creates a copy of a file descriptor.

* It uses the lowest-numbered unused descriptor for the new descriptor.
* If the copy is successfully created, then the original and copy file descriptors may be used interchangeably.
* They both refer to the same open file description and thus share file offset and file status flags.

**Examples**

* ``dup_write_number_to_file.c``: Write number from ``1`` to ``100`` to a file using a file descriptor created by ``dup()``

Print out number from ``1`` to ``100`` in terminal (``STDOUT_FILENO``) using a file descriptor created by ``dup()``:

```c
int copy_fd = dup(STDOUT_FILENO);

while(number < 100){
    sprintf(write_buffer, "%d\n", number);
    write(STDOUT_FILENO, write_buffer, strlen(write_buffer));      
    number += 1;
    sprintf(write_buffer, "%d\n", number);
    write(copy_fd, write_buffer, strlen(write_buffer));
    number += 1;
} 
```

The ``dup2()`` system call is similar to ``dup()`` but the basic difference between them is that instead of using the lowest-numbered unused file descriptor, it uses the descriptor number specified by the user.

```c
int dup2(int oldfd, int newfd);
```

If ``newfd`` was previously opened, it is silently closed before being reused.

This program write the content in ``printf()`` to a file instead of ``STDOUT_FILENO``:

```c
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
  
int main()
{
    int fd = open("test.txt",O_WRONLY | O_APPEND);
    dup2(fd, STDOUT_FILENO);          
    printf("Write to test.txt\n");  
    return 0;
}
```
