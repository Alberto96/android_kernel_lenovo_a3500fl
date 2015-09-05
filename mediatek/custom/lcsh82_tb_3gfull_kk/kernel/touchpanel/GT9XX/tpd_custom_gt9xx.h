#ifndef TPD_CUSTOM_GT9XX_H__
#define TPD_CUSTOM_GT9XX_H__

#include <linux/hrtimer.h>
#include <linux/string.h>
#include <linux/vmalloc.h>
//#include <linux/io.h>

#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/bitops.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/byteorder/generic.h>
#ifdef CONFIG_HAS_EARLYSUSPEND
#include <linux/earlysuspend.h>
#endif
#include <linux/interrupt.h>
#include <linux/time.h>
#include <linux/rtpm_prio.h>

#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#include <mach/mt_pm_ldo.h>
#include <mach/mt_typedefs.h>
#include <mach/mt_boot.h>
#include <mach/mt_gpio.h>

#include <cust_eint.h>
#include <linux/jiffies.h>

/* Pre-defined definition */

#define TPD_KEY_COUNT   4
#define key_1           60,850              //auto define  
#define key_2           180,850
#define key_3           300,850
#define key_4           420,850

#define TPD_KEYS        {KEY_BACK, KEY_HOME, KEY_MENU, KEY_SEARCH}
#define TPD_KEYS_DIM    {{key_1,50,30},{key_2,50,30},{key_3,50,30},{key_4,50,30}}

#define SWITCH_ON	1
#define SWITCH_OFF	0

struct goodix_ts_data
{
    spinlock_t irq_lock;
    struct i2c_client *client;
    struct input_dev  *input_dev;
    struct hrtimer timer;
    struct work_struct  work;
    struct early_suspend early_suspend;
    s32 irq_is_disable;
    s32 use_irq;
    u16 abs_x_max;
    u16 abs_y_max;
    u8  max_touch_num;
    u8  int_trigger_type;
    u8  green_wake_mode;
    u8  chip_type;
    u8  enter_update;
    u8  gtp_is_suspend;
    u8  gtp_rawdiff_mode;
};

extern u16 show_len;
extern u16 total_len;
extern u8 gtp_rawdiff_mode;

extern s32 gtp_send_cfg(struct i2c_client *client);
extern void gtp_reset_guitar(struct i2c_client *client, s32 ms);
extern void gtp_int_sync(void);
extern u8 gup_init_update_proc(struct i2c_client *client);
extern u8 gup_init_fw_proc(struct i2c_client *client);
extern s32 gtp_i2c_read(struct i2c_client *client, u8 *buf, s32 len);
extern s32 gtp_i2c_write(struct i2c_client *client, u8 *buf, s32 len);
extern int i2c_write_bytes(struct i2c_client *client, u16 addr, u8 *txbuf, int len);
extern int i2c_read_bytes(struct i2c_client *client, u16 addr, u8 *rxbuf, int len);

//***************************PART1:ON/OFF define*******************************
#define GTP_CUSTOM_CFG        0
#define GTP_DRIVER_SEND_CFG   1       //driver send config to TP on intilization (for no config built in TP flash)
#define GTP_HAVE_TOUCH_KEY    0
#define GTP_POWER_CTRL_SLEEP  0       //turn off power on suspend
#define GTP_CHANGE_X2Y        0				//set for se1
#define GTP_ESD_PROTECT       1
#define GTP_CREATE_WR_NODE    1
//#define GTP_CHARGER_DETECT

#define GTP_AUTO_UPDATE       0       // auto updated fw by .bin file yxw modify20130114
#define GTP_HEADER_FW_UPDATE  1       // auto updated fw by gtp_default_FW in gt9xx_firmware.h, function together with GTP_AUTO_UDPATE
#define GTP_AUTO_UPDATE_CFG   0       // auto update config by .cfg file, function together with GTP_AUTO_UPDATE

#define GTP_SUPPORT_I2C_DMA   0       // if gt9xxf, better enable it if hardware platform supported
#define GTP_COMPATIBLE_MODE   0       // compatible with GT9XXF

//#define TPD_PROXIMITY
//#define TPD_HAVE_BUTTON               //report key as coordinate,Vibration feedback
//#define TPD_WARP_X
//#define TPD_WARP_Y

#define GTP_DEBUG_ON          0
#define GTP_DEBUG_ARRAY_ON    0
#define GTP_DEBUG_FUNC_ON     0

#define LCT_ADD_TP_VERSION		// modified by zhangtao 20130930

//***************************PART2:TODO define**********************************
//STEP_1(REQUIRED):Change config table.
/*TODO: puts the config info corresponded to your TP here, the following is just
a sample config, send this config should cause the chip cannot work normally*/
#define CTP_CFG_GROUP1 {\
0x42,0x20,0x03,0x00,0x05,0x05,0x3C,0x48,\
0x01,0x0F,0x1E,0x08,0x50,0x32,0x03,0x05,\
0x00,0x00,0x00,0x00,0x02,0x24,0x04,0x14,\
0x16,0x1E,0x14,0x87,0x27,0xCC,0x7D,0x81,\
0xDA,0x09,0x00,0x00,0x00,0x01,0x02,0x1D,\
0x44,0x21,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x4B,0x96,0x94,0xC5,0x02,\
0x08,0x00,0x00,0x04,0xAA,0x50,0x00,0x9A,\
0x5C,0x00,0x8C,0x6A,0x00,0x81,0x7A,0x00,\
0x79,0x8C,0x00,0x79,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x1B,0x1A,0x19,0x18,0x17,0x16,0x13,0x12,\
0x11,0x10,0x0F,0x0E,0x0D,0x0C,0x09,0x08,\
0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00,\
0xFF,0xFF,0x00,0x00,0x00,0x00,0x24,0x2A,\
0x25,0x29,0x26,0x27,0x28,0x0A,0x0B,0x0C,\
0x09,0x0D,0x08,0x0E,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0xA8,0x01,\
}

#define CTP_CFG_GROUP1_CHARGER {\
}

//TODO puts your group2 config info here,if need.
#define CTP_CFG_GROUP2 {\
    }

//TODO puts your group2 config info here,if need.
#define CTP_CFG_GROUP2_CHARGER {\
    }

//TODO puts your group3 config info here,if need.
#define CTP_CFG_GROUP3 {\
    }

//TODO puts your group3 config info here,if need.
#define CTP_CFG_GROUP3_CHARGER {\
    }

//TODO puts your group4 config info here,if need.
#define CTP_CFG_GROUP4 {\
0x42,0x20,0x03,0x00,0x05,0x05,0x3C,0x48,\
0x01,0x0F,0x1E,0x08,0x50,0x32,0x03,0x05,\
0x00,0x00,0x00,0x00,0x02,0x24,0x04,0x14,\
0x16,0x1E,0x14,0x87,0x27,0xCC,0x7D,0x81,\
0xDA,0x09,0x00,0x00,0x00,0x01,0x02,0x1D,\
0x44,0x21,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x4B,0x96,0x94,0xC5,0x02,\
0x08,0x00,0x00,0x04,0xAA,0x50,0x00,0x9A,\
0x5C,0x00,0x8C,0x6A,0x00,0x81,0x7A,0x00,\
0x79,0x8C,0x00,0x79,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x1B,0x1A,0x19,0x18,0x17,0x16,0x13,0x12,\
0x11,0x10,0x0F,0x0E,0x0D,0x0C,0x09,0x08,\
0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00,\
0xFF,0xFF,0x00,0x00,0x00,0x00,0x24,0x2A,\
0x25,0x29,0x26,0x27,0x28,0x0A,0x0B,0x0C,\
0x09,0x0D,0x08,0x0E,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0xA8,0x01,\
}

//TODO puts your group4 config info here,if need.
#define CTP_CFG_GROUP4_CHARGER {\
    }

//TODO puts your group5 config info here,if need.
#define CTP_CFG_GROUP5 {\
    }

//TODO puts your group5 config info here,if need.
#define CTP_CFG_GROUP5_CHARGER {\
    }

//TODO puts your group6 config info here,if need.
#define CTP_CFG_GROUP6 {\
0x42,0x20,0x03,0x00,0x05,0x0A,0x3D,0x40,\
0x01,0x08,0x1C,0x0A,0x50,0x32,0x03,0x05,\
0x00,0x00,0x00,0x00,0x34,0x11,0x04,0x15,\
0x17,0x19,0x14,0x87,0x27,0xDD,0x46,0x48,\
0xDA,0x09,0x00,0x00,0x00,0x82,0x02,0x1D,\
0x46,0x01,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x26,0x6E,0x88,0xE5,0x03,\
0x06,0x00,0x00,0x04,0x80,0x2A,0x00,0x81,\
0x34,0x00,0x83,0x41,0x00,0x80,0x50,0x00,\
0x80,0x63,0x00,0x7F,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,\
0x08,0x09,0x0C,0x0D,0x0E,0x0F,0x10,0x11,\
0x12,0x13,0x16,0x17,0x18,0x19,0x1A,0x1B,\
0x1C,0x1D,0x00,0x00,0x00,0x00,0x24,0x25,\
0x2A,0x26,0x29,0x27,0x28,0x0A,0x0B,0x09,\
0x0C,0x08,0x0D,0x0E,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0xD2,0x6E,0x5A,0x1E,0x00,0x00,0x00,0x00,\
0x00,0x00,0x28,0x50,0x78,0xDC,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x16,0x01,\
}

//TODO puts your group6 config info here,if need.
#define CTP_CFG_GROUP6_CHARGER {\
    }

//STEP_2(REQUIRED):Change I/O define & I/O operation mode.
#define GTP_RST_PORT    GPIO_CTP_RST_PIN
#define GTP_INT_PORT    GPIO_CTP_EINT_PIN

#define GTP_GPIO_AS_INPUT(pin)          do{\
                                            if(pin == GPIO_CTP_EINT_PIN)\
                                                mt_set_gpio_mode(pin, GPIO_CTP_EINT_PIN_M_GPIO);\
                                            else\
                                                mt_set_gpio_mode(pin, GPIO_CTP_RST_PIN_M_GPIO);\
                                            mt_set_gpio_dir(pin, GPIO_DIR_IN);\
                                            mt_set_gpio_pull_enable(pin, GPIO_PULL_DISABLE);\
                                        }while(0)
#define GTP_GPIO_AS_INT(pin)            do{\
                                            mt_set_gpio_mode(pin, GPIO_CTP_EINT_PIN_M_EINT);\
                                            mt_set_gpio_dir(pin, GPIO_DIR_IN);\
                                            mt_set_gpio_pull_enable(pin, GPIO_PULL_DISABLE);\
                                        }while(0)
#define GTP_GPIO_GET_VALUE(pin)         mt_get_gpio_in(pin)
#define GTP_GPIO_OUTPUT(pin,level)      do{\
                                            if(pin == GPIO_CTP_EINT_PIN)\
                                                mt_set_gpio_mode(pin, GPIO_CTP_EINT_PIN_M_GPIO);\
                                            else\
                                                mt_set_gpio_mode(pin, GPIO_CTP_RST_PIN_M_GPIO);\
                                            mt_set_gpio_dir(pin, GPIO_DIR_OUT);\
                                            mt_set_gpio_out(pin, level);\
                                        }while(0)
#define GTP_GPIO_REQUEST(pin, label)    gpio_request(pin, label)
#define GTP_GPIO_FREE(pin)              gpio_free(pin)
#define GTP_IRQ_TAB                     {IRQ_TYPE_EDGE_RISING, IRQ_TYPE_EDGE_FALLING, IRQ_TYPE_LEVEL_LOW, IRQ_TYPE_LEVEL_HIGH}

//STEP_3(optional):Custom set some config by themself,if need.
#if GTP_CUSTOM_CFG
#define GTP_MAX_HEIGHT   800
#define GTP_MAX_WIDTH    480
#define GTP_INT_TRIGGER  0    //0:Rising 1:Falling
#else
#define GTP_MAX_HEIGHT   1280
#define GTP_MAX_WIDTH    720
#define GTP_INT_TRIGGER  1
#endif
#define GTP_MAX_TOUCH      5
#define GTP_ESD_CHECK_CIRCLE  2000
#define TPD_POWER_SOURCE_CUSTOM	MT6323_POWER_LDO_VGP1
#define VELOCITY_CUSTOM
#define TPD_VELOCITY_CUSTOM_X 15
#define TPD_VELOCITY_CUSTOM_Y 15

//STEP_4(optional):If this project have touch key,Set touch key config.
#if GTP_HAVE_TOUCH_KEY
#define GTP_KEY_TAB	 {KEY_MENU, KEY_HOME, KEY_BACK, KEY_SEND}
#endif

//***************************PART3:OTHER define*********************************
#define GTP_DRIVER_VERSION          "V1.0<2012/05/01>"
#define GTP_I2C_NAME                "Goodix-TS"
#if defined(LCT_ADD_TP_VERSION)
#define GT91XX_CONFIG_PROC_FILE     "tp_info"
#else
#define GT91XX_CONFIG_PROC_FILE     "gt9xx_config"
#endif
#define GTP_POLL_TIME               10
#define GTP_ADDR_LENGTH             2
#define GTP_CONFIG_MAX_LENGTH       240
#define FAIL                        0
#define SUCCESS                     1

//Register define
#define GTP_READ_COOR_ADDR          0x814E
#define GTP_REG_SLEEP               0x8040
#define GTP_REG_SENSOR_ID           0x814A
#define GTP_REG_CONFIG_DATA         0x8047
#define GTP_REG_VERSION             0x8140
#define GTP_REG_HW_INFO             0x4220
#define GTP_REG_REFRESH_RATE		0x8056

#define RESOLUTION_LOC              3
#define TRIGGER_LOC                 8


#define MAX_TRANSACTION_LENGTH        8
#define TPD_I2C_NUMBER				0
#define I2C_MASTER_CLOCK              300
#define MAX_I2C_TRANSFER_SIZE         (MAX_TRANSACTION_LENGTH - GTP_ADDR_LENGTH)
#define TPD_MAX_RESET_COUNT           3
#define TPD_CALIBRATION_MATRIX        {962,0,0,0,1600,0,0,0};


#define TPD_RESET_ISSUE_WORKAROUND
#define TPD_HAVE_CALIBRATION
#define TPD_NO_GPIO
#define TPD_RESET_ISSUE_WORKAROUND

#ifdef TPD_WARP_X
#undef TPD_WARP_X
#define TPD_WARP_X(x_max, x) ( x_max - 1 - x )
#else
#define TPD_WARP_X(x_max, x) x
#endif

#ifdef TPD_WARP_Y
#undef TPD_WARP_Y
#define TPD_WARP_Y(y_max, y) ( y_max - 1 - y )
#else
#define TPD_WARP_Y(y_max, y) y
#endif

//Log define
#define GTP_INFO(fmt,arg...)           printk("<<-GTP-INFO->> "fmt"\n",##arg)
#define GTP_ERROR(fmt,arg...)          printk("<<-GTP-ERROR->> "fmt"\n",##arg)
#define GTP_DEBUG(fmt,arg...)          do{\
                                         if(GTP_DEBUG_ON)\
                                         printk("<<-GTP-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                       }while(0)
#define GTP_DEBUG_ARRAY(array, num)    do{\
                                         s32 i;\
                                         u8* a = array;\
                                         if(GTP_DEBUG_ARRAY_ON)\
                                         {\
                                            printk("<<-GTP-DEBUG-ARRAY->>\n");\
                                            for (i = 0; i < (num); i++)\
                                            {\
                                                printk("%02x   ", (a)[i]);\
                                                if ((i + 1 ) %10 == 0)\
                                                {\
                                                    printk("\n");\
                                                }\
                                            }\
                                            printk("\n");\
                                        }\
                                       }while(0)
#define GTP_DEBUG_FUNC()               do{\
                                         if(GTP_DEBUG_FUNC_ON)\
                                         printk("<<-GTP-FUNC->> Func:%s@Line:%d\n",__func__,__LINE__);\
                                       }while(0)
#define GTP_SWAP(x, y)                 do{\
                                         typeof(x) z = x;\
                                         x = y;\
                                         y = z;\
                                       }while (0)

//****************************PART4:UPDATE define*******************************
//Error no
#define ERROR_NO_FILE           2   //ENOENT
#define ERROR_FILE_READ         23  //ENFILE
#define ERROR_FILE_TYPE         21  //EISDIR
#define ERROR_GPIO_REQUEST      4   //EINTR
#define ERROR_I2C_TRANSFER      5   //EIO
#define ERROR_NO_RESPONSE       16  //EBUSY
#define ERROR_TIMEOUT           110 //ETIMEDOUT

//*****************************End of Part III********************************
#endif /* TOUCHPANEL_H__ */
