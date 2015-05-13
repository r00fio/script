cmake_minimum_required(VERSION 2.8.4)
project(Axel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    -lm
    gdbcommands
    main.c
    main.h
    Makefile
    stm32_flash.ld
    stm32f4xx_conf.h
    )

SET(CMAKE_SYSTEM_NAME Generic)

# where is the target environment
SET(CMAKE_FIND_ROOT_PATH  /usr/lib/tuning/arm/bin)

# specify the cross compiler
SET(CMAKE_C_COMPILER   arm-none-eabi-gcc )
SET(CMAKE_CXX_COMPILER arm-none-eabi-g++ )
SET(CMAKE_LINKER arm-none-eabi-ld )
set(CMAKE_EXECUTABLE_SUFFIX     ".elf")

set(ARM_FLAGS "-nostdlib -mcpu=cortex-m3 -mthumb -O2")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ARM_FLAGS} -std=c99 -ffunction-sections -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 ${ARM_FLAGS} -ffunction-sections -g")
set(CMAKE_EXE_LINKER_FLAGS "${ARM_FLAGS} -g -nostartfiles -Wl,-Map=${PROJECT_NAME}.map -Wl,--gc-sections -Wl,--library-path=\"${PROJECT_SOURCE_DIR}\" -Wl,-Tstm32_flash.ld  ")

set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET>")
set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET>")

# -------------------------------------------------------------------

add_executable(Axel ${SOURCE_FILES})