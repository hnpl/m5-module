#!/bin/sh

sudo apt-get update
sudo apt-get upgrade

sudo apt-get install build-essential
# installing the linux kernel headers
sudo apt-get install linux-headers-$(uname -r)
