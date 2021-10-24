#include <linux/miscdevice.h>
#include <linux/watchdog.h>
#include <linux/uaccess.h>
#include <linux/module.h>
#include <linux/fs.h>

#define DEFAULT_WATCHHDOG_TIMEOUT   10
#define TIMEOUT_SHIFT               5
#define WENABLE_SHIFT               3
#define TIMEOUT_BITS                1

unsigned long WD_CONTROL_REGISTER;
unsigned long WD_SERVICE_REGISTER;

static int wdt_open(struct inode *inode, struct file *filp)
{
    WD_CONTROL_REGISTER |= DEFAULT_WATCHHDOG_TIMEOUT << TIMEOUT_SHIFT;
    WD_CONTROL_REGISTER |= 1 << WENABLE_SHIFT;

    return 0;
}

static int wdt_close(struct inode *inode, struct file *filp)
{
#ifndef CONFIG_WATCHDOG_NOWAYOUT
    WD_CONTROL_REGISTER &= -(1 << WENABLE_SHIFT);
#endif
    return 0;
}

static ssize_t wdt_write(struct file *filp, const char *data, size_t len, loff_t *ppose)
{
    WD_SERVICE_REGISTER = 0xABCD;

    return len;
}

long wdt_unlocked_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    int timeout;

    switch(cmd)
    {
        case WDIOC_KEEPALIVE:
            WD_SERVICE_REGISTER = 0xABCD;
            break;
        case WDIOC_SETTIMEOUT:
            copy_from_user(&timeout, (int*)arg, sizeof(int));
            WD_CONTROL_REGISTER = timeout << TIMEOUT_BITS;
            break;
        case WDIOC_GETTIMEOUT:
            break;

        default:
            return -ENOTTY;
    }

    return 0;
}

static struct file_operations wdt_dog = {
    .owner  = THIS_MODULE,
    .open   = wdt_open,
    .release    = wdt_close,
    .write  = wdt_write,
    .unlocked_ioctl = wdt_unlocked_ioctl,
};

static struct miscdevice wdt_dev = {
    .minor  = WATCHDOG_MINOR,
    .name   = "watchdog",
    .fops   = &wdt_dog,
};

int __init wdt_init(void)
{
    misc_register(&wdt_dev);

    return 0;
}


void __exit wdt_exit(void)
{
    misc_deregister(&wdt_dev);

    return ;
}

module_init(wdt_init);
module_exit(wdt_exit);

MODULE_LICENSE("GPL");
