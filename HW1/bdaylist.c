#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Birthday list");
MODULE_AUTHOR("SGG");


struct birthday 
{
   int day;
   int month;
   int year;
   struct list_head list;
};

static LIST_HEAD(birthday_list);

/* This function is called when the module is loaded. */
int birthday_list_init(void)
{
	struct birthday *person;
	int year = 1995;
	int i = 0;
       printk(KERN_INFO "Loading Module\n");

	
	for(i = 0; i < 5; i++){
		person = kmalloc(sizeof(*person), GFP_KERNEL);
   		person->day = (i + 4);
   		person->year = year++;
   		INIT_LIST_HEAD(&person->list);
   		list_add_tail(&person->list, &birthday_list);
	}
	list_for_each_entry(person, &birthday_list, list)
	{
		printk(KERN_INFO "birthday: %d/%d/%d \n", person->month, person->day, person->year);
	}

       return 0;
}

/* This function is called when the module is removed. */
void birthday_list_exit(void) {
	
	struct birthday *ptr;
	struct birthday *next;
	list_for_each_entry_safe(ptr, next, &birthday_list, list)
	{
		list_del(&ptr->list);
		kfree(ptr);
	}
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( birthday_list_init );
module_exit( birthday_list_exit );



