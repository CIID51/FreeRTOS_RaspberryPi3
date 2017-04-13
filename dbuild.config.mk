#ASFLAGS += -mcpu=cortex-a8
ASFLAGS += -march=armv8-a
#CFLAGS += -mcpu=cortex-a8 -g -Wall -w
CFLAGS += -march=armv8-a -g -Wall -w
#-Wextra

CFLAGS += -I $(BASE)Source/portable/GCC/ARM_CA53_64_BIT/
CFLAGS += -I $(BASE)Source/include/
CFLAGS += -I $(BASE)Demo/Drivers/
CFLAGS += -I $(BASE)Demo/

TOOLCHAIN=aarch64-linux-gnu-
#TOOLCHAIN=arm-none-eabi-
