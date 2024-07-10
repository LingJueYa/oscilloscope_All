
#include <stdint.h> // 包含对基本数据类型的定义
#define SPI_CONTROL_REGISTER (0x1FFF0220) // SPI 控制寄存器的基地址

// 根据手册中表 10-1，假设的SPI数据寄存器地址
#define SPI_DATA_REGISTER (0x1FFF0224) // 数据寄存器地址


#define DRDY_PIN_REGISTER (0x1FFF0228) // DRDY 引脚状态寄存器地址

// DRDY 引脚状态掩码
#define DRDY_PIN_MASK (0x01)

// 手册中提到了控制寄存器(SPCR)中的位域，但没有提到具体的启动位，这里假设一个
#define SPI_CMD_START_BIT (0x01) //自己定的SPI 命令启动位

// 假设的参考电压和 ADC 分辨率
#define REFERENCE_VOLTAGE (3.3f)
#define ADC_RESOLUTION (1024)

/**
 * 发送 SPI 命令到 SPI 控制器。
 * 
 * @param command 要发送的 8 位 SPI 命令。
 */
void SPI_SendCommand(uint8_t command) {
    *(volatile uint8_t*)SPI_CONTROL_REGISTER = command;
}

/**
 * 从 SPI 控制器读取数据。
 * 
 * @return 从 SPI 数据寄存器读取的 32 位数据。
 */
uint32_t SPI_ReadData() {
    return *(volatile uint32_t*)SPI_DATA_REGISTER;
}

/**
 * 检查 DRDY 引脚的状态，以确定数据是否准备好。
 * 
 * @return 如果 DRDY 引脚状态为高，则返回 1，否则返回 0。
 */
uint8_t Hardware_CheckDRDYPin() {
    return (*(volatile uint8_t*)DRDY_PIN_REGISTER & DRDY_PIN_MASK) ? 1 : 0;
}

/**
 * 将从 ADC 读取的数据转换为电压值。
 * 
 * @param data 从 ADC 获取的原始数据。
 * @return 对应的电压值。
 */
float ConvertToVoltage(uint32_t data) {
    return (float)data * (REFERENCE_VOLTAGE / ADC_RESOLUTION);
}
