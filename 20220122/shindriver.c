#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

static int __init shindriver_init(void){
	printk(KERN_ALERT "[Shindriver] Hello Driver!\n");
	return 0;
}

static void __exit shindriver_exit(void) {
	printk(KERN_ALERT "[Shindriver] Bye Driver!\n");
}

module_init(shindriver_init);
module_exit(shindriver_exit);
