/* keyboard-dump.c
 * 
 * This is a "notify chain" example that dumps keyboard on kernel message
 *
 *	(C) Copyright 2010, Tiago Maluta
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/notifier.h>
#include <linux/module.h>
#include <linux/keyboard.h>

static int debug = 1;

#define dbg(fmt, arg...)						\
	do {								\
		if (debug)						\
			printk (KERN_DEBUG "%s: %s: " fmt "\n",		\
				"test" , __FUNCTION__ , ## arg);	\
	} while (0)



int keyboard_event_handler(struct notifier_block *self, 
                         unsigned long val, 
			 void *data) 
{

	struct keyboard_notifier_param *param = data; 

	unsigned int value = param->value;
	
	if ((!param->down) && (value > 0xf000)) 
		printk("%c", KVAL(param->value));
	
	return NOTIFY_DONE ;
}

static struct notifier_block keyboard_notifier = {
	.notifier_call = keyboard_event_handler,
};

static int __init keyboard_init(void) 
{

	register_keyboard_notifier(&keyboard_notifier);
	
	dbg();

	return 0;
}

static void __exit keyboard_exit(void)
{
	unregister_keyboard_notifier(&keyboard_notifier);
	dbg(); 
}

module_init(keyboard_init);
module_exit(keyboard_exit);

MODULE_LICENSE("GPL");
