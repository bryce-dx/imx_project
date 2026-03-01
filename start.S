.text
.global _start

_start:
    /* 进入SVC模式 */
    mrs r0, cpsr
    bic r0, r0, #0x1f       /* 将r0寄存器中的低5位清零，也就是cpsr的M0~M4 */
    orr r0, r0, #0x13       /* r0或上0x13,表示使用SVC模式 */
    msr cpsr_c, r0          /* 将r0 的数据写入到cpsr的控制位中 */
    /* 设置sp指针 */
    ldr sp, =0x80200000     /* 设置栈指针 */
    /* 清BSS段 */
	ldr r0, =__bss_start    /* 加载BSS段起始地址 */
	ldr r1, =__bss_end      /* 加载BSS段结束地址 */
	mov r2, #0
bss_loop:
    cmp r0, r1              /* 比较当前地址和结束地址 */
    bge bss_end             /* 如果r0 >= r1，退出循环 */
    str r2, [r0]            /* 向r0指向的地址写入4字节0 */
    add r0, r0, #4          /* r0指向的地址添加4字节偏移 */
    b bss_loop              /* 无条件跳转到bss_loop继续清bss段*/
bss_end:
    /* 跳转到main函数 */
    bl main
halt:
    wfi                     /* 进入低功耗等待状态，等待中断唤醒 */
	b halt                  /* 防止main返回后程序跑飞 */