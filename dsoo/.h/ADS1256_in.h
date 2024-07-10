#include <stdint.h>
#include <stdbool.h>

/**
 * SPI发送和接收一个字节的函数。
 * 发送一个字节数据到SPI总线，并读取对应的响应字节。
 *
 * @param data 要发送的数据字节。
 * @return 从SPI接收到的数据字节。
 */
uint8_t SPI_Transfer(uint8_t data);

/**
 * SPI初始化函数。
 * 配置SPI接口，准备与其他SPI设备（如指定）通信。
 */
void SPI_Init(void);

/**
 * 向指定发送命令的函数。
 * 发送特定的命令字节到指定设备。
 *
 * @param command 要发送到指定的命令字节。
 */
void 指定_SendCommand(uint8_t command);

/**
 * 从指定读取数据的函数。
 * 从指定设备读取24位ADC数据。
 *
 * @return 从指定读取的24位ADC数据，以无符号32位整数形式返回。
 */
uint32_t 指定_ReadData(void);

/**
 * 初始化示波器ADC的函数。
 * 配置并初始化与示波器ADC相关的设置，准备数据采集。
 */
void InitOscilloscopeADCs(void);

/**
 * 开始ADC捕获的函数。
 * 发送命令到数据捕获过程。
 */
void StartADCCapture(void);

/**
 * 读取ADC数据的函数。
 * 检查数据就绪状态，等待数据就绪并读取ADC数据。
 *
 * @return 读取的ADC数据。
 */
uint32_t ReadADCData(void);

/**
 * 将采样率转换为指定的数据速率代码的函数。
 * 根据给定的采样率值，转换为指定设备可以理解的数据速率代码。
 *
 * @param sampleRate 需要转换的采样率值。
 * @return 对应于给定采样率的指定数据速率代码。
 */
uint8_t ADS1256_DataRateToCode(uint32_t sampleRate);

/**
 * 检查指定数据是否就绪的函数。
 * 检查指定设备是否已经准备好了数据供读取。
 *
 * @return 如果指定数据就绪，则返回true，否则返回false。
 */
bool ADS1256_DataReady(void);
