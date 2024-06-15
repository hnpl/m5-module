#!/bin/sh

isa=$(uname -m)
m5ops_addr=0
if [ $isa = 'aarch64' ] ; then
    m5ops_addr=0x10010000
else
    m5ops_addr=0xFFFF0000
fi

sudo rmmod src/m5-driver.ko
sudo insmod src/m5-driver.ko m5ops_addr=$m5ops_addr
