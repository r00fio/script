
# Put your stlink folder here so make burn will work.
STLINK=/home/bebe/work/system/arm/stlink

# Put your source files here (or *.c, etc)
SRCS=main.c system_stm32f4xx.c 

# Binaries will be generated with this name (.elf, .bin, .hex, etc)
PROJ_NAME=Axel

# Put your STM32F4 library code directory here
STM_COMMON=/home/bebe/work/tuning/board/f4

# Normally you shouldn't need to change anything below this line!
#######################################################################################

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy


CFLAGS  = -g -O2 -Wall -Tstm32_flash.ld 
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
# CFLAGS += -mfloat-abi=hardfp -mfpu=fpv4-sp-d16
CFLAGS += --specs=rdimon.specs -lm
CFLAGS += -DUSE_STDPERIPH_DRIVER
CFLAGS += -DARM_MATH_CM4
CFLAGS += -DSTM32F4XX
CFLAGS += -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls	
CFLAGS += -I.

# Include files from STM libraries
CFLAGS += -I$(STM_COMMON)/Utilities/STM32F4-Discovery
CFLAGS += -I$(STM_COMMON)/Libraries/cmsis/
CFLAGS += -I$(STM_COMMON)/Libraries/
CFLAGS += -I$(STM_COMMON)/Libraries/cmsis_boot/
CFLAGS += -I$(STM_COMMON)/Libraries/cmsis_boot/startup
CFLAGS += -I$(STM_COMMON)/Libraries/cmsis_lib/include
CFLAGS += -I$(STM_COMMON)/Libraries/cmsis_lib/source
CFLAGS += -I$(STM_COMMON)/LIS302DL
CFLAGS += -I$(STM_COMMON)/CacheLibs/Libraries/CMSIS/Include
# CFLAGS += -I/usr/arm-none-eabi/include

CFLAGS += -I$(STM_COMMON)/ARMCM4/Include
# CFLAGS += -I$(STM_COMMON)/CacheLibs/Libraries/CMSIS/Include
CFLAGS += -I$(STM_COMMON)/ARMCM4/Include
CFLAGS += -I$(STM_COMMON)/ARMCM4/Source
CFLAGS += -I$(STM_COMMON)/ARMCM4/Source/ARM"
CFLAGS += -I$(STM_COMMON)/ARMCM4/Source/GCC"
               

# add startup file to build
SRCS += $(STM_COMMON)/Libraries/cmsis_boot/startup/startup_stm32f4xx.c
SRCS += $(STM_COMMON)/LIS302DL/stm32_ub_lis302dl.c
SRCS += $(STM_COMMON)/LIS302DL/stm32_ub_spi1.c

SRCS += $(STM_COMMON)/Libraries/cmsis_lib/include/stm32f4xx_rcc.h 
SRCS += $(STM_COMMON)/Libraries/cmsis_lib/include/stm32f4xx_gpio.h 
SRCS += $(STM_COMMON)/Libraries/cmsis_lib/include/stm32f4xx_spi.h 
SRCS += $(STM_COMMON)/Libraries/cmsis_lib/include/stm32f4xx_usart.h 
SRCS += $(STM_COMMON)/Libraries/cmsis_lib/include/stm32f4xx_tim.h
SRCS += $(STM_COMMON)/Libraries/cmsis_lib/include/stm32f4xx_syscfg.h
SRCS += $(STM_COMMON)/Libraries/cmsis_lib/include/stm32f4xx_exti.h
SRCS += $(STM_COMMON)/Libraries/cmsis_lib/source/misc.c

SRCS += $(STM_COMMON)/Libraries/cmsis_lib/source/stm32f4xx_rcc.c 
SRCS += $(STM_COMMON)/Libraries/cmsis_lib/source/stm32f4xx_gpio.c
SRCS += $(STM_COMMON)/Libraries/cmsis_lib/source/stm32f4xx_spi.c
SRCS += $(STM_COMMON)/Libraries/cmsis_lib/source/stm32f4xx_usart.c
SRCS += $(STM_COMMON)/Libraries/cmsis_lib/source/stm32f4xx_tim.c
SRCS += $(STM_COMMON)/Libraries/cmsis_lib/source/stm32f4xx_syscfg.c
SRCS += $(STM_COMMON)/Libraries/cmsis_lib/source/stm32f4xx_exti.c
SRCS += $(STM_COMMON)/Libraries/cmsis_lib/include/misc.h


# SRCS += $(STM_COMMON)CacheLibs/Libraries/STM32F4xx_StdPeriph_Driver/inc/
# SRCS += /usr/arm-none-eabi/include/math.h
# SRCS += $(STM_COMMON)/CacheLibs/Libraries/CMSIS/Include/arm_math.h
# 

# SRCS += /usr/include/
# SRCS += /usr/include/x86_64-linux-gnu/bits/predefs.h
# SRCS += $(STM_COMMON)/ARMCM4/Source/system_ARMCM4.c
# SRCS += $(STM_COMMON)/ARMCM4/Include/system_ARMCM4.h
OBJS = $(SRCS:.c=.o)



.PHONY: proj

all: proj

proj: $(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ 
	$(OBJCOPY) -O  ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin 


clean:
	rm -f *.o $(PROJ_NAME).elf $(PROJ_NAME).hex $(PROJ_NAME).bin

# Flash the STM32F4
burn: proj
	$(STLINK)/st-flash write $(PROJ_NAME).bin 0x8000000
