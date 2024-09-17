#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main ()
{
	int fd = open("test", O_CREAT);
	int fd2= open("test", O_WRONLY);
	write(fd2, "hello", 5);
	close(fd2);
	printf("fd %d\n", fd);
	printf("fd2 %d\n", fd2);
}
