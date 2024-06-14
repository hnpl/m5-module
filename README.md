# m5 Kernel Module

This Linux kernel module allows the guest system to send m5ops to
the host system.

Note that the module must be compiled off the linux kernel source
matches the kernel version up to the subsubversion. E.g., the
module compiled with Linux source v6.6.33 must be run with the
kernel version v6.6.33, not with other kernel version, such as
v6.6.34.

## Development

You should use QEMU for developing kernel module. While it is possible
to develop on your own system, a buggy module can bring unstability
to your system rendering the machine unstable. So, it's best to do
the development on a virtual system. The most common way to do it is
via QEMU. This means, this repo should be on your guest system and
not on your host system.

### Building the Disk Image for Development

TODO
