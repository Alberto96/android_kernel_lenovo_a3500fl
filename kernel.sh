#!/bin/bash

LOCAL_PATH=`pwd -P`

export PATH=/opt/arm-eabi-4.7/bin:$PATH
export CROSS_COMPILE=arm-eabi-
export TARGET_PRODUCT=lcsh82_tb_3gfull_kk

./mk -o=TARGET_BUILD_VARIANT=user $TARGET_PRODUCT n k
source $LOCAL_PATH/pack_bootimage.sh
