PREFIX=arm-linux-gnueabihf-
CC=$(PREFIX)gcc
LD=$(PREFIX)ld
AR=$(PREFIX)ar
OBJCOPY=$(PREFIX)objcopy
OBJDUMP=$(PREFIX)objdump

# mkimage工具路径
MKIMAGE_TOOL = ../tool/mkimage
# imximage配置文件路径
MKIMAGE_CFG = ../tool/imximage.cfg.cfgtmp
# 程序入口地址（-e参数的值）
ENTRY_ADDR = 0x87800000

# 编译参数: 1、开启 GCC 内置的绝大多数有用警告; 2、不链接标准库(如libc、libm等, 必选); 3、生成调试信息； 4、禁用栈保护机制
CFLAGS = -Wall -nostdlib -g -fno-stack-protector
# 链接参数：栈区域无执行权限
LDFLAGS = -znoexecstack

all: led.imx

led.imx : start.S led.c main.c
	$(CC) $(CFLAGS) -c -o start.o start.S
	$(CC) $(CFLAGS) -c -o led.o led.c
	$(CC) $(CFLAGS) -c -o main.o main.c

	$(LD) -T imx6ull.lds -g $(LDFLAGS) start.o led.o main.o -o led.elf

	$(OBJCOPY) -O binary -S led.elf led.bin
	$(OBJDUMP) -D -m arm led.elf > led.dis
	$(MKIMAGE_TOOL) -n $(MKIMAGE_CFG) -T imximage -e $(ENTRY_ADDR) -d led.bin led.imx

clean:
	rm -f *.o  led.elf led.dis led.bin led.imx

.PHONY: all clean