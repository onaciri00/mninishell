


#include <fcntl.h>
#include<stdio.h>
#include <unistd.h>
int main(int ac, char *av[])
{
    int fd = open(av[1], O_CREAT | O_RDWR | O_APPEND, 0666);
    printf("%d\n",fd);
    close(fd);

}