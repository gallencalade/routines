/*
 * -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
 *
 *      Filename : dev_scull.c
 *   Description : 
 *
 *       Version : 1.0
 *         CTime : Tue Sep  6 13:53:13 CST 2016
 *      Compiler : gcc
 *        Author : Gallen Escalade
 *        E-mail : 932441619@qq.com
 *
 *      Revision : NONE
 *         MTime : NONE
 *   Description : NONE
 *
 * -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/timer.h>

#define DEV_SCULL_TYPE       'k'
#define DEV_SCULL_CLEAN     _IO(DEV_SCULL_TYPE, 0x10)
#define DEV_SCULL_SETVALUE  _IOR(DEV_SCULL_TYPE, 0x11, int)
#define DEV_SCULL_GETVALUE  _IOW(DEV_SCULL_TYPE, 0x12, int)

#define DEVICE_NAME "dev_scull"
#define DEVICE_NUM  1
#define MAJOR_NUM   252

#define BUFFER_LEN  1024
#define NAME_LEN    16

struct dev_scull{
    unsigned char   scl_buf[BUFFER_LEN];
    unsigned char   scl_name[NAME_LEN];
    unsigned int    scl_size;

    struct cdev cdev;
};

static dev_t dev_num = { 0 };
struct dev_scull *dev_scl;
static struct class *cls_scl;

struct timer_list timer;

static void timer_func(unsigned long data)
{
    printk(KERN_ALERT "Timer ding!\n");
}

static int dev_scull_open(struct inode *inode, struct file *filp)
{
    /* for stream device */
    /* filp->f_mode &= ~(FMODE_LSEEK | FMODE_PREAD | FMODE_PWRITE);
    return 0; */
    
    struct dev_scull *dev_sclp;
    
    init_timer(&timer);
    timer.expires = jiffies + HZ;
    timer.function = &timer_func;
    add_timer(&timer);

    dev_sclp = container_of(inode->i_cdev, struct dev_scull, cdev);
    filp->private_data = dev_sclp;
    
    printk(KERN_ALERT "Success to open dev_scull!\n");
    return 0;
}

static int dev_scull_release(struct inode *inode, struct file *filp)
{
    del_timer_sync(&timer);

    return 0;
}

static struct file_operations dev_scull_ops = {
    .owner  = THIS_MODULE,
    .open   = dev_scull_open,
    .release= dev_scull_release,
};

int __init dev_scull_init(void)
{
    int i = 0, j = 0;
    int ret = -1;
    struct device *device;

    /* the number of device */
    dev_scl = kzalloc(DEVICE_NUM * sizeof(struct dev_scull), GFP_KERNEL);
    if(!dev_scl)
    {
        printk(KERN_ALERT "Failed to alloc device!\n");
        return -ENOMEM;
    }

    /* request allocation of device major/minor number */
    dev_num = MKDEV(MAJOR_NUM, 0);
    ret = register_chrdev_region(dev_num, DEVICE_NUM, DEVICE_NAME);
    if(ret < 0)
    {
        ret = alloc_chrdev_region(&dev_num, 0, DEVICE_NUM, DEVICE_NAME);
        if(ret < 0)
        {
            printk(KERN_ALERT "Failed to register device number!\n");
            goto err_register_chrdev_region;
        }
    }

    /* create device classs, populate sysfs entries */
    cls_scl = class_create(THIS_MODULE, DEVICE_NAME);
    if(IS_ERR(cls_scl))
    {
        ret = PTR_ERR(cls_scl);
        goto err_class_create;
    }

    for(i = 0; i < DEVICE_NUM; ++i)
    {
        /* the name of device */
        sprintf(dev_scl[i].scl_name, "dev_scull%d", i);
        /* connect the file operations with the cdev */
        cdev_init(&dev_scl[i].cdev, &dev_scull_ops);
        /* connect the major/minor number to cdev */
        ret = cdev_add(&dev_scl[i].cdev, MKDEV(MAJOR(dev_num), i), 1);
        if(ret < 0)
        {
            printk(KERN_ALERT "Failed to cdev_add!\n");
            goto err_cdev_add;
        }
        /* send uevents to udev, so it will create /dev nodes */
        device = device_create(cls_scl, NULL, MKDEV(MAJOR(dev_num), i), NULL, "dev_scl%d", i);
        if(IS_ERR(device))
        {
            ret = PTR_ERR(device);
            printk(KERN_ALERT "Failed to device_create!\n");
            goto err_device_create;
        }
    }
    
    printk(KERN_ALERT "Success to register dev_scull to system!\n");
    return 0;

err_device_create:
    for(j = 0; j < i; ++j)
    {
        device_destroy(cls_scl, MKDEV(MAJOR(dev_num), j));
    }

err_cdev_add:
    for(j = 0; j < i; ++j)
    {
        cdev_del(&dev_scl[j].cdev);
    }

err_class_create:
    unregister_chrdev_region(dev_num, DEVICE_NUM);

err_register_chrdev_region:
    kfree(dev_scl);

    return ret;
}

void __exit dev_scull_exit(void)
{
    int i = 0;
    /* destroy device */
    for(i = 0; i < DEVICE_NUM; ++i)
    {
        device_destroy(cls_scl, MKDEV(MAJOR(dev_num), i));
    }
    /* destroy scull class */
    class_destroy(cls_scl);
    /* delete cdev */
    for(i = 0; i < DEVICE_NUM; ++i)
    {
        cdev_del(&dev_scl[i].cdev);
    }
    /* release the major number */
    unregister_chrdev_region(dev_num, DEVICE_NUM);

    return ;
}

module_init(dev_scull_init);
module_exit(dev_scull_exit);

MODULE_LICENSE("GPL");
