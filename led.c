
#include "led.h"

/*
 * @description	: 初始化LED引脚，就是把它设置为输出引脚
 * @param 		: 无
 * @return 		: 无
 */
void led_init(void)
{
    int temp_value;

    /* 初始化IO复用 */
    temp_value = SW_MUX_CTL_PAD_SNVS_TAMPER3;
    temp_value &= ~(0xf);
    temp_value |= (0x5);
    SW_MUX_CTL_PAD_SNVS_TAMPER3 = temp_value;
	/* 配置GPIO5_IO03的电气属性	
     *bit [16]:0 HYS关闭
     *bit [15:14]: 00 默认下拉
     *bit [13]: 0 kepper功能
     *bit [12]: 1 pull/keeper使能
     *bit [11]: 0 关闭开路输出
     *bit [7:6]: 10 速度100Mhz
     *bit [5:3]: 110 R0/6驱动能力
     *bit [0]: 0 低转换率
     */
    SW_PAD_CTL_PAD_SNVS_TAMPER3 = 0X10B0;
    /* 设置GPIO5_IO03作为输出引脚 */
    GPIO5_GDIR |= (1<<3);
}

/*
 * @description	: 设置LED状态
 * @param - on	: 1-LED点亮, 0-LED熄灭
 * @return 		: 无
 */
void led_ctl(int on)
{
	if (on) {
		/* 设置GPIO5_DR输出低电平
		 * set GPIO5_DR to configure GPIO5_IO03 output 0
		 * GPIO5_DR 0x020AC000 + 0
		 * bit[3] = 0b0
		 */
		GPIO5_DR &= ~(1<<3);
	}
	else  {
		/* 设置GPIO5_IO3输出高电平
		 * set GPIO5_DR to configure GPIO5_IO03 output 1
		 * GPIO5_DR 0x020AC000 + 0
		 * bit[3] = 0b1
		 */ 
		GPIO5_DR |= (1<<3);
	}
}