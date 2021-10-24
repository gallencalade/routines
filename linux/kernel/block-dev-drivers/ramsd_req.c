#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/vmalloc.h>
#include <linux/blkdev.h>
#include <linux/hdreg.h>

#define RAMSD_NAME              "ramsd"
#define RAMSD_MAX_DEVICES       2
#define RAMSD_MAX_PARTITIONS    4
#define RAMSD_SECTORS_SIZE      512
#define RAMSD_SECTORS           16
#define RAMSD_HEADS             4
#define RAMSD_CYLINDERS         256

#define RAMSD_SECTOR_TOTAL      (RAMSD_SECTORS * RAMSD_HEADS * RAMSD_CYLINDERS)
#define RAMSD_SIZE              (RAMSD_SECTORS_SIZE * RAMSD_SECTOR_TOTAL)       // 8MB

typedef struct{
    unsigned char           *data;
    struct request_queue    *queue;
    spinlock_t              lock;
    struct gendisk          *gd;
}RAMSD_DEV;

static char *sdisk[RAMSD_MAX_DEVICES];
static RAMSD_DEV *rdev[RAMSD_MAX_DEVICES];

static dev_t ramsd_major;

static int ramsd_space_init(void)
{
    int i;
    int err = 0;
    for(i = 0; i < RAMSD_MAX_DEVICES; ++i)
    {
        sdisk[i] = vmalloc(RAMSD_SIZE);
        if(!sdisk[i])
        {
            err = -ENOMEM;
            return err;
        }
        memset(sdisk[i], 0, RAMSD_SIZE);
    }

    return err;
}

static void ramsd_space_clean(void)
{
    int i;
    for(i = 0; i < RAMSD_MAX_DEVICES; ++i)
    {
        vfree(sdisk[i]);
    }
}

static int alloc_ramdev(void)
{
    int i;
    for(i = 0; i < RAMSD_MAX_DEVICES; ++i)
    {
        rdev[i] = kzalloc(sizeof(RAMSD_DEV), GFP_KERNEL);
        if(!rdev[i])
            return -ENOMEM;
    }

    return 0;
}

static void clean_ramdev(void)
{
    int i;
    for(i = 0; i < RAMSD_MAX_DEVICES; ++i)
    {
        if(rdev[i])
            kfree(rdev[i]);
    }
}

static int ramsd_open(struct block_device *bdev, fmode_t mode)
{
    return 0;
}

static void ramsd_release(struct gendisk *gd, fmode_t mode)
{
    return ;
}

static int ramsd_ioctl(struct block_device *bdev, fmode_t mode, unsigned int cmd, unsigned long arg)
{
    int err;
    struct hd_geometry geo;

    switch(cmd)
    {
        case HDIO_GETGEO:
            err = !access_ok(VERIFY_WRITE, arg, sizeof(geo));
            if(err)
                return -EFAULT;
            geo.cylinders   = RAMSD_CYLINDERS;
            geo.heads       = RAMSD_HEADS;
            geo.sectors     = RAMSD_SECTORS;
            geo.start       = get_start_sect(bdev);
            if(copy_to_user((void*)arg, &geo, sizeof(geo)))
                return -EFAULT;

            return 0;            
    }
    
    return -ENOTTY;
}

static struct block_device_operations ramsd_fops = {
    .owner      = THIS_MODULE,
    .open       = ramsd_open,
    .release    = ramsd_release,
    .ioctl      = ramsd_ioctl,
};

void ramsd_req_func(struct request_queue *q)
{
    struct request *req;
    RAMSD_DEV *pdev;
    char *pData;
    unsigned long addr, size, start;
    req = blk_fetch_request(q);
    while(req)
    {
        start = blk_rq_pos(req);
        pdev = (RAMSD_DEV*)req->rq_disk->private_data;
        pData = pdev->data;
        addr = (unsigned long)pData + start * RAMSD_SECTORS_SIZE;
        size = blk_rq_cur_bytes(req);
        if(rq_data_dir(req) == READ)
        {
            // memcpy(req->buffer, (char*)addr, size);
        }
        else
        {
            // memcpy((char*)addr, req->buffer, size);
        }
            
        if(!__blk_end_request_cur(req, 0))
            req = blk_fetch_request(q);
    }
}

int ramsd_init(void)
{
    int i;
    ramsd_space_init();
    alloc_ramdev();

    ramsd_major = register_blkdev(0, RAMSD_NAME);

    for(i = 0; i < RAMSD_MAX_DEVICES; ++i)
    {
        rdev[i]->data = sdisk[i];
        rdev[i]->gd = alloc_disk(RAMSD_MAX_PARTITIONS);
        spin_lock_init(&rdev[i]->lock);
        rdev[i]->queue = blk_init_queue(ramsd_req_func, &rdev[i]->lock);
        rdev[i]->gd->major = ramsd_major;
        rdev[i]->gd->first_minor = i * RAMSD_MAX_PARTITIONS;
        rdev[i]->gd->fops = &ramsd_fops;
        rdev[i]->gd->queue = rdev[i]->queue;
        rdev[i]->gd->private_data = rdev[i];
        sprintf(rdev[i]->gd->disk_name, "ramsd%c", 'a'+i);
        set_capacity(rdev[i]->gd, RAMSD_SECTOR_TOTAL);
        add_disk(rdev[i]->gd);
    }

    return 0;
}

void ramsd_exit(void)
{
    int i;
    for(i = 0; i < RAMSD_MAX_DEVICES; ++i)
    {
        del_gendisk(rdev[i]->gd);
        put_disk(rdev[i]->gd);
        blk_cleanup_queue(rdev[i]->queue);
    }
    unregister_blkdev(ramsd_major, RAMSD_NAME);
    clean_ramdev();
    ramsd_space_clean();
}

module_init(ramsd_init);
module_exit(ramsd_exit);

MODULE_LICENSE("GPL");
