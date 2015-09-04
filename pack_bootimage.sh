#!/bin/bash

set -e

KERNEL_DIR=/home/AndroidDev/Lenovo/alps
export TARGET_PRODUCT=lcsh82_tb_3gfull_kk
RAMDISK_DIRECTORY=/home/AndroidDev/Lenovo/alps/ramdisk/$TARGET_PRODUCT

rm -rf $KERNEL_DIR/out/target/product/$TARGET_PRODUCT/kernel
rm -rf $KERNEL_DIR/out/target/product/$TARGET_PRODUCT/boot.img
$KERNEL_DIR/mediatek/build/tools/mkimage $KERNEL_DIR/out/target/product/lcsh82_tb_3gfull_kk/obj/KERNEL_OBJ/arch/arm/boot/zImage KERNEL > $KERNEL_DIR/out/target/product/$TARGET_PRODUCT/kernel

/home/AndroidDev/Lenovo/alps/mtk-tools/repack-MTK.pl -boot $KERNEL_DIR/out/target/product/$TARGET_PRODUCT/kernel $RAMDISK_DIRECTORY $KERNEL_DIR/out/target/product/$TARGET_PRODUCT/boot.img
