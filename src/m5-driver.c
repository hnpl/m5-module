#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

static int __init init_m5_driver(void)
{
    pr_info("Hello\n");
    return 0;
}

static void __exit exit_m5_driver(void)
{
    pr_info("Removing module\n");
}

module_init(init_m5_driver);
module_exit(exit_m5_driver);

MODULE_LICENSE("BSD");
