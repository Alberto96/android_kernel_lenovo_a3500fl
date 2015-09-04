export PATH=/home/AndroidDev/Lenovo/arm-eabi-4.7/bin:$PATH
export CROSS_COMPILE=arm-eabi-
export TARGET_PRODUCT=lcsh82_tb_3gfull_kk
export FLASHABLE_ZIP="./kernel-$TARGET_PRODUCT-`date +"%Y%m%d"`.zip"

./mk -o=TARGET_BUILD_VARIANT=user $TARGET_PRODUCT n k
source /home/AndroidDev/Lenovo/alps/pack_bootimage.sh
