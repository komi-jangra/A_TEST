#!/bin/bash 
rm -rf sr.*
 #svn co http://10.100.211.65/system/pfs/PFS/branches/DEV-EIC/products/eic/images
 mkdir sr.`./mkimage -l ramdisk-eic.bin | grep Revision | cut -c 25`.`./mkimage -l ramdisk-eic.bin | grep Revision | cut -c 26`.`./mkimage -l ramdisk-eic.bin | grep Revision | cut -c 27-29`
 cp -a ramdisk-eic.bin kernel-eic.bin sr.*/
 ls -l sr.*
# EIC Repos
