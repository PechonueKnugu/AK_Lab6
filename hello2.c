#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include "hello1.h"

MODULE_AUTHOR("Makovetskyi Dmytro <dima.makovetskuy@gmail.com>");
MODULE_DESCRIPTION("Hello2 Module");
MODULE_LICENSE("Dual BSD/GPL");

static uint count = 1;
module_param(count, uint, 0444);
MODULE_PARM_DESC(count, "The number of “Hello world!”");

static int __init hello2_init(void)
{
	unsigned int i;

	if (count == 0 || (count >= 5 && count <= 10))
		pr_warn("Warning: Parameter count is 0 or between 5 and 10\n");

	if (count > 10) {
		pr_err("Error: Parameter count is greater than 10\n");
		BUG_ON(1);
	}

	for (i = 0; i < count; i++) {
		print_hello(count);
	}

	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("Exit hello2\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
