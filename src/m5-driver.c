#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>

static u64 m5ops_addr = 0x0;

/**
 * Parameters
 */
// Not sure about permission bits.
// The bits are set to be readable/writable from user and group
module_param(m5ops_addr, ullong, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

static int __init init_m5_driver(void)
{
    pr_info("Initializing m5-driver.\n");
    pr_info("m5ops_addr = 0x%llx.\n", m5ops_addr);
    return 0;
}

static void __exit exit_m5_driver(void)
{
    pr_info("Exiting m5-driver.\n");
}

module_init(init_m5_driver);
module_exit(exit_m5_driver);

MODULE_LICENSE("BSD");
