/*
 * Here's a sample kernel module showing the use of jprobes to dump
 * the arguments of _do_fork().
 *
 * For more information on theory of operation of jprobes, see
 * Documentation/kprobes.txt
 *
 * Build and insert the kernel module as done in the kprobe example.
 * You will see the trace data in /var/log/messages and on the
 * console whenever _do_fork() is invoked to create a new process.
 * (Some messages may be suppressed if syslogd is configured to
 * eliminate duplicate messages.)
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>

/*
 * Jumper probe for _do_fork.
 * Mirror principle enables access to arguments of the probed routine
 * from the probe handler.
 */

/* Proxy routine having the same arguments as actual _do_fork() routine */
void j_submit_bio(int rm, struct bio *bio)
{
    printk(KERN_ALERT "Get bio\n");
	/*pr_info("jprobe: clone_flags = 0x%lx, stack_start = 0x%lx "
		"stack_size = 0x%lx\n", clone_flags, stack_start, stack_size);*/

	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return;
}

static struct jprobe my_jprobe = {
	.entry			= j_submit_bio,
	.kp = {
		.symbol_name	= "submit_bio",
	},
};

static int __init jprobe_init(void)
{
	int ret;

	ret = register_jprobe(&my_jprobe);
	if (ret < 0) {
		printk(KERN_INFO "register_jprobe failed, returned %d\n", ret);
		return -1;
	}
	printk(KERN_INFO "Planted jprobe at %p, handler addr %p\n",
	       my_jprobe.kp.addr, my_jprobe.entry);
	return 0;
}

static void __exit jprobe_exit(void)
{
	unregister_jprobe(&my_jprobe);
	printk(KERN_INFO "jprobe at %p unregistered\n", my_jprobe.kp.addr);
}

module_init(jprobe_init)
module_exit(jprobe_exit)

MODULE_LICENSE("GPL");
