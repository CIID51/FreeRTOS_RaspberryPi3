# FreeRTOS Ported to Raspberry Pi 3

## Howto Build

Type make!
Toolchain : aarch64-none-elf- (/!\ not changed in the Makefile yet !)

## ABOUT FREERTOS PORT

- Raspberry Pi 3 uses the BCM2837 wich has the same base address that the previous one (BCM2836 -> BaseAddress=0x3F000000)

- There was another FreeRTOS_Config.h file which overcame the good one

- The FreeRTOS version has been updated to the last version (9.0.0) to work with the architecture of the Cortex-A53

- It seem that the compiler arm-none-eabi is unable to use some 64bits features. Has been changed for :
gcc-aarch64-linux-gnu (/!\ need to be change for aarch64-none-elf-)

- Assembly deprecated commands have been changed by the armv8 ones

- Some function have been deprecated in FreeRTOS 9 : some v*****() functions can be replaced by x*****()


### TODO:

-find a way to implement the _freertos_vector_table variable (used in portASM.S)

-write the timer functions in the FreeRTOSTimers file

-find out where is the new implementation of vPortYieldProcessor and create it if it does not exist

-check the addresses configuraton in FreeRTOS_config

-check the startup file

### Please refer to:

Raspberry documentation:
	-	https://github.com/raspberrypi/documentation

Porting to 64:
	-	"Porting to ARM 64-bit.pdf" file
	-	http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.den0024a/ch08s02s01.html

## ABOUT UBOOT

- The u-boot need to be compile with the toolchain "aarch64-none-elf-" (available on http://wiki.osdev.org/GCC_Cross-Compiler) to work with the last raspberry firmware and in 64 mode.

- The following options must be set in the config.txt file:
	
	\# ARMv8
	arm_control=0x200

	\# Uart
	enable_uart=1

	\# Kernel name
	kernel=uboot.img	

- Put the compiled u-boot.bin in the boot partition as "uboot.img" and copy all the content of the raspberry boot firmware into the boot partition (a working exemple of boot is available in the "Working_Uboot" directory)

### Please refer to:

U-boot compiling tutorial:
	-	"HOWTO_ubootRasp3.pdf" file

Raspberry boot firmware:
	-	https://github.com/raspberrypi/firmware/tree/master/boot
