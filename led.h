
#ifndef   __LED_H__
#define   __LED_H__

/* 
 * CCM相关寄存器地址 
 */
#define CCM_CCGR0 			            *((volatile unsigned int *)0X020C4068)
#define CCM_CCGR1 			            *((volatile unsigned int *)0X020C406C)
#define CCM_CCGR2 			            *((volatile unsigned int *)0X020C4070)
#define CCM_CCGR3 			            *((volatile unsigned int *)0X020C4074)
#define CCM_CCGR4 			            *((volatile unsigned int *)0X020C4078)
#define CCM_CCGR5 			            *((volatile unsigned int *)0X020C407C)
#define CCM_CCGR6 			            *((volatile unsigned int *)0X020C4080)

/* 
 * IOMUX相关寄存器地址 
 */
#define SW_MUX_CTL_PAD_SNVS_TAMPER3     *((volatile unsigned int *)0x02290014)
#define SW_PAD_CTL_PAD_SNVS_TAMPER3     *((volatile unsigned int *)0x02290058)

/* 
 * GPIO5相关寄存器地址 
 */
#define GPIO5_DR 			            *((volatile unsigned int *)0x020AC000)
#define GPIO5_GDIR 			            *((volatile unsigned int *)0X020AC004)

/*
 * @description	: 初始化LED引脚，就是把它设置为输出引脚
 * @param 		: 无
 * @return 		: 无
 */
void led_init(void);


/*
 * @description	: 设置LED状态
 * @param - on	: 1-LED点亮, 0-LED熄灭
 * @return 		: 无
 */
void led_ctl(int on);

#endif // __LED_H__

