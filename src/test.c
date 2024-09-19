#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main ()
{
	int fd1 = open("fd1", O_CREAT | O_RDWR, 0644);
	printf("fd1 = %d\n", fd1);
	write(fd1, "heyyyyy", 7);
	close(fd1);

	int fd2 = open("fd1", O_CREAT | O_RDWR, 0644);
	printf("fd2 = %d\n", fd2);
	write(fd2, "\0", 1);
	close(fd2);
}
