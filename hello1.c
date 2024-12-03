#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include "hello1.h"

MODULE_AUTHOR("Makovetskyi Dmytro <dima.makovetskuy@gmail.com>");
MODULE_DESCRIPTION("Hello1 Module");
MODULE_LICENSE("Dual BSD/GPL");

static LIST_HEAD(hello_list);

void print_hello(uint count)
{
	struct hello_time *ht;
	unsigned int i;

	for (i = 0; i < count; i++) {
		if (i == 4) {
			ht = NULL;
		} else {
			ht = kmalloc(sizeof(*ht), GFP_KERNEL);
		}

		if (!ht) {
			pr_err("Failed to allocate memory for hello_time\n");
			continue;
		}

		ht->time = ktime_get();
		list_add_tail(&ht->list, &hello_list);
		pr_info("Hello, world!\n");
	}
}
EXPORT_SYMBOL(print_hello);

static void __exit hello1_exit(void)
{
	struct hello_time *ht, *tmp;

	list_for_each_entry_safe(ht, tmp, &hello_list, list) {
		pr_info("Time: %lld ns\n", ktime_to_ns(ht->time));
		list_del(&ht->list);
		kfree(ht);
	}
}

module_exit(hello1_exit);
