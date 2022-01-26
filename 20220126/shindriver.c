#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/kdev_t.h>

#include "shindriver.h"


MODULE_LICENSE("GPL");

dev_t shindriver_dev;
u32 shindriver_major = SHINDRIVER_MAJOR;
u32 shindriver_minor = 0;

static int __init shindriver_init(void)
{
	int result;

	printk(KERN_ALERT "[Shindriver] Ready to Init!\n");

	if(shindriver_major){
		shindriver_dev = MKDEV(shindriver_major, shindriver_minor);
		result = register_chrdev_region(shindriver_dev, 0, "shindriver");
	}
	else{
		result = alloc_chrdev_region(&shindriver_dev, shindriver_minor, 0, "shindriver");
		shindriver_major = MAJOR(shindriver_dev);
	}
	
	if(result < 0){
		printk(KERN_WARNING "[Shindriver] Failed to get major : %d\n", shindriver_major);
		goto err;
	}

	printk(KERN_INFO "[Shindriver] Success to get major : %d\n", shindriver_major);

	return 0;
err:
	return result;
}

static void __exit shindriver_exit(void)
{
	printk(KERN_ALERT "[Shindriver] Bye, Driver!\n");
	unregister_chrdev_region(shindriver_dev, 0);
}

module_init(shindriver_init);
module_exit(shindriver_exit);