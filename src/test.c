#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main ()
{
	int fd1 = open("fd1", O_CREAT | O_RDWR, 0644);
	write(fd1, "Non", 3);
	printf("fd1 = %d\n", fd1);
	close(fd1);
}
