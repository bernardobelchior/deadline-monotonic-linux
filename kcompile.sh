#!/bin/bash
start=$(date +'%s')
cd linux-4.12.4-cister
sudo make 2>../errors_4.12.4-cister
sudo make modules
sudo make modules_install
sudo make install
cd ..
sudo update-grub2
cat errors_4.12.4-cister
echo "Linux kernel compilation and installation took $(($(date +'%s') - $start)) seconds"
