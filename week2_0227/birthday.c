#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

#define MAX_PERSON 5

MODULE_DESCRIPTION("Birthday_linked_list");
MODULE_LICENSE("GPL");

struct birthday
{
	int day;
	int month;
	int year;
	struct list_head list;
};

static LIST_HEAD(birthday_list);

void Add_birthday(void)
{
	struct birthday *new_person[MAX_PERSON];
	int days[] = {5, 6, 7, 8, 9};
	int months[] = {20, 21, 22, 23, 24};
	int years[] = {1998, 1999, 2000, 2001, 2002};
	int i;
	
	for (i = 0; i < MAX_PERSON; i++)
	{
		new_person[i] = kmalloc(sizeof(struct birthday), GFP_KERNEL);
		new_person[i]->day = days[i];
		new_person[i]->month = months[i];
		new_person[i]->year = years[i];
		INIT_LIST_HEAD(&new_person[i]->list);
		list_add_tail(&new_person[i]->list, &birthday_list);
	}
}

void Traverse_list(void)
{
	struct birthday *ptr;

	list_for_each_entry(ptr, &birthday_list, list)
	{
		printk(KERN_INFO "day: %d | month: %d | year: %d\n", ptr->day, ptr->month, ptr->year);
	}
}

static int birthday_init(void)
{
    printk(KERN_INFO "Birthday Init\n");

	Add_birthday();
	Traverse_list();

    return 0;
}

static void birthday_exit(void)
{
    struct birthday *ptr, *next;

	list_for_each_entry_safe(ptr, next, &birthday_list, list)
	{
		printk(KERN_INFO "Remove | day: %d | month: %d | year: %d\n", ptr->day, ptr->month, ptr->year);
		list_del(&ptr->list);
		kfree(ptr);
	}

	printk(KERN_INFO "Birthday EXIT\n");
}

module_init(birthday_init);
module_exit(birthday_exit);
