#!/bin/bash

LOCAL_PATH=`pwd -P`

set -e

KERNEL_DIR=$LOCAL_PATH
export TARGET_PRODUCT=lcsh82_tb_3gfull_kk
RAMDISK_DIRECTORY=$LOCAL_PATH/ramdisk/$TARGET_PRODUCT

rm -rf $KERNEL_DIR/out/target/product/$TARGET_PRODUCT/kernel
rm -rf $KERNEL_DIR/out/target/product/$TARGET_PRODUCT/boot.img
$KERNEL_DIR/mediatek/build/tools/mkimage $KERNEL_DIR/out/target/product/lcsh82_tb_3gfull_kk/obj/KERNEL_OBJ/arch/arm/boot/zImage KERNEL > $KERNEL_DIR/out/target/product/$TARGET_PRODUCT/kernel

$LOCAL_PATH/mtk-tools/repack-MTK.pl -boot $KERNEL_DIR/out/target/product/$TARGET_PRODUCT/kernel $RAMDISK_DIRECTORY $KERNEL_DIR/out/target/product/$TARGET_PRODUCT/boot.img
