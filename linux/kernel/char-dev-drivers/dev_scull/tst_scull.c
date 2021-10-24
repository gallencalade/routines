#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, const char *argv[])
{
    int fd;
    int n;

    char buf[256] = "Hello World!\n";

    fd = open("/dev/dev_scl0", O_RDWR);
    if(fd < 0)
    {
        perror("Failed to open /dev/dev_scl0!\n");
        return EXIT_FAILURE;
    }

    n = write(fd, buf, strlen(buf));
    if(n < 0)
    {
        perror("Failed to write!\n");
        return -1;
    }

    printf("Write %d bytes.\n", n);

    return EXIT_SUCCESS;
}
