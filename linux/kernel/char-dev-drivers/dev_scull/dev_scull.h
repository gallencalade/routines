/*
 * -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
 *
 *      Filename : dev_scull.h
 *   Description : 
 *
 *       Version : 1.0
 *         CTime : Tue Sep  6 13:52:52 CST 2016
 *      Compiler : g++
 *        Author : Gallen Escalade
 *        E-mail : 932441619@qq.com
 *
 *      Revision : NONE
 *         MTime : NONE
 *   Description : NONE
 *
 * -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
 */

#ifdef  __DEV_SCULL_H__
#define __DEV_SCULL_H__

#include <linux/cdev.h>

#define BUFFER_LEN  1024
#define NAME_LEN    16

struct dev_scull{
    unsigned char   scl_buf[BUFFER_LEN];
    unsigned char   scl_name[NAME_LEN];
    unsigned int    scl_size;

    struct cdev cdev;
};

int  __init dev_scull_init(void);
void __exit dev_scull_exit(void);

static int dev_scull_open(struct inode *, struct file *);
static int dev_scull_release(struct inode *, struct file *);
static ssize_t dev_scull_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t dev_scull_write(struct file *, char __user *, size_t, loff_t *);
static loff_t dev_scull_llseek(struct file *, loff_t, int);
static int dev_scull_unlocked_ioctl(struct file *, unsigned int, unsigned long);

#endif
