# Handling Modules

## Overview

After compilation, the module is of the file format `*.ko`.

We will use the following commands insert/remove/listing the new module.
Typically, the `sudo` permission is required to use most of these commands.

- `modinfo m5-driver.ko`: information about the module.
- `insmod m5-driver.ko`: insert the module to the kernel.
- `rmmod m5-driver.ko`: remove the module from the inserted modules.
- `lsmod`: list all inserted modules.

## Module Logs

Typically, modules will leave some logs.
You can use `printk` method when writing the kernel module to output some
debugging information.
You will need to include `<linux/printk.h>` to use the `printk` function.
The output can be found by the following command, `dmesg`, or,
`journalctl | grep kernel`.
