#include<spi.h>
/**
 * 发送 SPI 命令到 SPI 控制器。
 * 
 * @param command 要发送的 8 位 SPI 命令。
 */
void SPI_SendCommand(uint8_t command) {
    // SPI_CMD_START_BIT 定义了命令位在寄存器中的起始位。
    // 0xFF 是一个全为 1 的字节，用于清除命令寄存器中的命令部分。
    // 通过左移命令位，然后清除和设置命令寄存器的相应位来发送命令。
    *(volatile uint32_t *)SPI_CONTROL_REGISTER &= ~(0xFF << SPI_CMD_START_BIT); // 清除命令位
    *(volatile uint32_t *)SPI_CONTROL_REGISTER |= (command & 0xFF) << SPI_CMD_START_BIT; // 发送命令
}

/**
 * 从 SPI 控制器读取数据。
 * 
 * @return 从 SPI 数据寄存器读取的 32 位数据。
 */
uint32_t SPI_ReadData() {
    // 循环等待 DRDY 引脚状态变为高，表示 SPI 传输的数据已经准备好。
    while(!Hardware_CheckDRDYPin());
    
    // 从 SPI 数据寄存器读取数据。
    return *(volatile uint32_t *)SPI_DATA_REGISTER;
}

/**
 * 检查 DRDY 引脚的状态，以确定数据是否准备好。
 * 
 * @return 如果 DRDY 引脚状态为高，则返回 1，否则返回 0。
 */
uint8_t Hardware_CheckDRDYPin() {
    // 读取 DRDY 引脚的状态寄存器，应用掩码以隔离 DRDY 引脚的状态。
    // 如果结果不为零，则 DRDY 引脚状态为高。
    return (*(volatile uint32_t *)DRDY_PIN_REGISTER & DRDY_PIN_MASK) ? 1 : 0;
}

/**
 * 将从 ADC 读取的数据转换为电压值。
 * 
 * @param data 从 ADC 获取的原始数据。
 * @return 对应的电压值。
 */
float ConvertToVoltage(uint32_t data) {
    // 将 ADC 数据转换为电压值，使用参考电压和 ADC 分辨率进行计算。
    // 公式为：voltage = (data / ADC_RESOLUTION) * REFERENCE_VOLTAGE
    float voltage = (data * REFERENCE_VOLTAGE) / ADC_RESOLUTION;
    return voltage;
}