#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

/* for proc_dir_entry and create_proc_entry */
#include <linux/proc_fs.h>

/* For sprintf and snprintf */
#include <linux/string.h>

/* For copy_from_user */
#include <linux/uaccess.h>

static char internal_buffer[256];

int buf_read(char *buf, char **start, off_t offset, int count, int *eof, void *data)
{
	int len;
	len = snprintf(buf, count, "%s", internal_buffer);
	return len;
}

static int buf_write(struct file *file, const char *buf, unsigned long count, void *data)
{
	if(count > 255) /* to avoid overflowwwwwwwwww */ 
		count = 255;

	/* Copies data from user space to kernel space */ 
	copy_from_user(internal_buffer, buf, count);

	/* inserting NULL to end the string */
	internal_buffer[count] = '\0';
	return count;
}

int __init proc_init(void) {
	/* Simple */	
	struct proc_dir_entry *de = create_proc_entry("coding", 0667, 0);

	/* Set pointers to our functions */
	de->read_proc = buf_read; /* reading */ 
	de->write_proc = buf_write; /* writing */ 

	/* We initialize our internal_buffer with some text. */
	sprintf(internal_buffer, "www.coding.com.br");
	return 0 ;
}

void __exit proc_cleanup(void) {

	/* We delete our entry */
	remove_proc_entry("coding", NULL);

}

module_init(proc_init);
module_exit(proc_cleanup);

MODULE_LICENSE("GPL");
