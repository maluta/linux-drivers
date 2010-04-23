#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sysctl.h>
#include <linux/spinlock.h>
#include <linux/delay.h>

static int thread3(void *unused) {

	int count3 = 0;
	while (count3 < 1000) {
		msleep(100);
		printk("Thread 3: %d\n", count3++); 
	} 
	return 0; 
} 


static int thread2(void *unused) {
	
	int count2 = 0;
	while (count2 < 1000) {
		msleep(10);
		printk("Thread 2: %d\n", count2++); 
	} 
	return 0;
}

static int __init threads_init(void)
{
	int count1 = 0;
	int ret1, ret2;

	ret1 = kernel_thread(thread2, NULL, CLONE_FS | CLONE_FILES | CLONE_SIGHAND | SIGCHLD );
	ret2 = kernel_thread(thread3, NULL, CLONE_FS | CLONE_FILES | CLONE_SIGHAND | SIGCHLD );

	printk("--tm: module init\n");	
	printk("--tm: spawning thread 1 ret=%d\n", ret1);	
	printk("--tm: spawning thread 2 ret=%d\n", ret2);	
    
	while (count1 < 1000) {
		msleep(10); 
		printk("Thread 1: %d\n", count1++); 
     	}


    return 0;
}
 
static void __exit threads_exit(void)
{
    printk("--tm: module removed\n");	
}

module_init(threads_init);
module_exit(threads_exit);

MODULE_AUTHOR("Tiago Maluta <maluta@unifei.edu.br");
MODULE_DESCRIPTION("initial");
MODULE_LICENSE("GPL");

