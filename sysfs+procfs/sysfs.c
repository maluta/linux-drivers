#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

/* for sysfs class creation */
#include <linux/platform_device.h>

static struct class *sysfs_class;

int __init sysfs_init(void) {
	
	sysfs_class = class_create(THIS_MODULE, "sysfs" );
	return 0 ;
}

void __exit sysfs_cleanup(void) {

	/* We delete our entry */
	class_destroy(sysfs_class);
}

module_init(sysfs_init);
module_exit(sysfs_cleanup);

MODULE_LICENSE("GPL");
