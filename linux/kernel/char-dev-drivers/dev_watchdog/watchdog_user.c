#include <fcntl.h>
#include <asm/types.h>
#include <linux/watchdog.h>

int main()
{
    int new_timeout;

    int wfd = open("/dev/watchdog", O_WRONLY);

    new_timeout = 20;
    ioctl(wfd, WDIOC_SETTIMEOUT, &new_timeout);
    while(1)
    {
        process_graphics();
        ioctl(wfd, WDIOC_KEEPALIVE, 0);
        fsync(wfd);
    }
}
