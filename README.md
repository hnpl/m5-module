# m5 Kernel Module

This Linux kernel module allows the guest system to send m5ops to
the host system.

Note that the module must be compiled off the Linux kernel source
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

### Downloading and Using the Disk Image for Development

#### Downloading

```sh
wget https://cloud-images.ubuntu.com/releases/22.04/release-20240612/ubuntu-22.04-server-cloudimg-arm64.img
qemu-img convert ubuntu-22.04-server-cloudimg-arm64.img -O raw ./ubuntu-22.04-arm64.img
qemu-img resize -f raw ubuntu-22.04-arm64.img +10G
```

#### Before the First Use

You only need to do this step once.

By default, a cloud disk image does not have any user in its record.
To add a new user, you need to supply a cloud-config specifying the
username, permission, and credential.

First, you'll need to create an SSH credential for login.

```sh
ssh-keygen -C "ubuntu@localhost"
ssh-add ~/.ssh/id_rsa
```

Second, you'll need to create a file call `cloud.txt`,

```text
#cloud-config
users:
  - name: ubuntu
    lock_passwd: false
    groups: sudo
    sudo: ['ALL=(ALL) NOPASSWD:ALL']
    shell: /bin/bash
    ssh-authorized-keys:
      - ssh-rsa AAAAJLKFJEWOIJRNJF... <- insert the public key here (e.g., the content of ~/.ssh/id_rsa.pub)
```

After this, you can generate a cloud config to input to QEMU.

```sh
cloud-localds --disk-format qcow2 cloud.img cloud.txt
```

We will use `cloud.img` to input to QEMU.

Finally, you need to flash the bootloader to images.

```sh
dd if=/dev/zero of=flash0.img bs=1M count=64
dd if=/usr/share/qemu-efi-aarch64/QEMU_EFI.fd of=flash0.img conv=notrunc
dd if=/dev/zero of=flash1.img bs=1M count=64
```

#### Starting a QEMU Instance from the Disk Image

Without KVM,

```sh
qemu-system-aarch64 -m 16384 -smp 8 -cpu cortex-a57 -M virt \
    -nographic -pflash flash0.img -pflash flash1.img \
    -drive if=none,file=ubuntu-22.04-arm64.img,id=hd0 -device virtio-blk-device,drive=hd0 \
    -drive if=none,id=cloud,file=cloud.img -device virtio-blk-device,drive=cloud \
    -netdev user,id=user0 -device virtio-net-device,netdev=eth0 \
    -netdev user,id=eth0,hostfwd=tcp::5555-:22
```

With KVM,

```sh
qemu-system-aarch64 -m 16384 -smp 8 -cpu host -M virt -M gic-version=3 --enable-kvm \
    -nographic -pflash flash0.img -pflash flash1.img \
    -drive if=none,file=ubuntu-22.04-arm64.img,id=hd0 -device virtio-blk-device,drive=hd0 \
    -drive if=none,id=cloud,file=cloud.img -device virtio-blk-device,drive=cloud \
    -netdev user,id=user0 -device virtio-net-device,netdev=eth0 \
    -netdev user,id=eth0,hostfwd=tcp::5555-:22
```

After QEMU finished booting Ubuntu, you can login to the guest system using,

```sh
ssh-add ~/.ssh/id_rsa
ssh -p 5555 ubuntu@localhost
```

All steps after this step should be done on the guest machine.

### Downloading the Linux Kernel

You can find the kernel source code here, [kernel.org](https://kernel.org/).

The following command downloads the Linux kernel source code version v6.6.33.

```sh
wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.6.33.tar.xz
tar xf linux-6.6.33.tar.xz
```

The Linux kernel source code should be in the `linux-6.6.33` folder.

