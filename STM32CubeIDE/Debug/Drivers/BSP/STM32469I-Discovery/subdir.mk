################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/jbawi/Desktop/Final\ Project/STM32CubeIDE/LCD_DSI_CmdMode_SingleBuffer/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.c \
C:/Users/jbawi/Desktop/Final\ Project/STM32CubeIDE/LCD_DSI_CmdMode_SingleBuffer/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_lcd.c \
C:/Users/jbawi/Desktop/Final\ Project/STM32CubeIDE/LCD_DSI_CmdMode_SingleBuffer/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_qspi.c \
C:/Users/jbawi/Desktop/Final\ Project/STM32CubeIDE/LCD_DSI_CmdMode_SingleBuffer/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.c 

OBJS += \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.o \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_lcd.o \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_qspi.o \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.o 

C_DEPS += \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.d \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_lcd.d \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_qspi.d \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.o: C:/Users/jbawi/Desktop/Final\ Project/STM32CubeIDE/LCD_DSI_CmdMode_SingleBuffer/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.c Drivers/BSP/STM32469I-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_STM32469I_DISCO_REVC -DSTM32F469xx -DUSE_HAL_DRIVER -c -I../../Inc -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/BSP/STM32469I-Discovery -I../../Drivers/BSP/Components/Common -I../../Utilities/Log -I../../Utilities/Fonts -I../../Utilities/CPU -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_lcd.o: C:/Users/jbawi/Desktop/Final\ Project/STM32CubeIDE/LCD_DSI_CmdMode_SingleBuffer/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_lcd.c Drivers/BSP/STM32469I-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_STM32469I_DISCO_REVC -DSTM32F469xx -DUSE_HAL_DRIVER -c -I../../Inc -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/BSP/STM32469I-Discovery -I../../Drivers/BSP/Components/Common -I../../Utilities/Log -I../../Utilities/Fonts -I../../Utilities/CPU -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_lcd.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_qspi.o: C:/Users/jbawi/Desktop/Final\ Project/STM32CubeIDE/LCD_DSI_CmdMode_SingleBuffer/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_qspi.c Drivers/BSP/STM32469I-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_STM32469I_DISCO_REVC -DSTM32F469xx -DUSE_HAL_DRIVER -c -I../../Inc -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/BSP/STM32469I-Discovery -I../../Drivers/BSP/Components/Common -I../../Utilities/Log -I../../Utilities/Fonts -I../../Utilities/CPU -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_qspi.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.o: C:/Users/jbawi/Desktop/Final\ Project/STM32CubeIDE/LCD_DSI_CmdMode_SingleBuffer/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.c Drivers/BSP/STM32469I-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_STM32469I_DISCO_REVC -DSTM32F469xx -DUSE_HAL_DRIVER -c -I../../Inc -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/BSP/STM32469I-Discovery -I../../Drivers/BSP/Components/Common -I../../Utilities/Log -I../../Utilities/Fonts -I../../Utilities/CPU -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32469I-2d-Discovery

clean-Drivers-2f-BSP-2f-STM32469I-2d-Discovery:
	-$(RM) ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.cyclo ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.d ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.o ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.su ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_lcd.cyclo ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_lcd.d ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_lcd.o ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_lcd.su ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_qspi.cyclo ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_qspi.d ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_qspi.o ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_qspi.su ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.cyclo ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.d ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.o ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32469I-2d-Discovery

