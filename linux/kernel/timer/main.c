#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
    int fd;

    fd = open("/dev/dev_scl0", O_RDWR);
    if(fd < 0)
    {
        perror("Failed to open /dev/dev_scl0!\n");
        return EXIT_FAILURE;
    }

    sleep(5);

    return EXIT_SUCCESS;
}
