

#include <stdint.h>

// 硬件平台相关的宏定义
#define SPI_CS_PIN   0
#define SPI_SCLK_PIN  1
#define SPI_DIN_PIN   2
#define SPI_DOUT_PIN  3

#define SAMPLE_RATE  10000  // 采样率，单位 SPS
#define RESOLUTION   24     // 分辨率，ADS1256为24位

// ADS1256命令定义
#define ADS1256_CMD_WAKEUP               0x00
#define ADS1256_CMD_STANDBY              0x01
#define ADS1256_CMD_RESET                0x06
#define ADS1256_CMD_START_CONV_SINGLE    0x08
#define ADS1256_CMD_SELFCAL              0xF0
#define ADS1256_CMD_SELFOCAL             0xF1
#define ADS1256_CMD_SELFGCAL             0xF2
#define ADS1256_CMD_SYSOCAL              0xF3
#define ADS1256_CMD_SYSGCAL              0xF4
/*ADS1256_CMD_WAKEUP: 定义为 0x00，这个命令用于完成同步操作并从待机模式中唤醒设备。
它允许设备从低功耗状态转换到正常工作状态。

ADS1256_CMD_STANDBY: 定义为 0x01，这个命令将设备置于待机模式，这是一种低功耗状态。
待机模式下，设备准备好快速唤醒以进行单次转换或恢复正常操作。

ADS1256_CMD_RESET: 定义为 0x06，这个命令用于重置设备中的所有寄存器到它们初始的默认值。
这通常在设备初始化或需要重置配置时使用。

ADS1256_CMD_START_CONV_SINGLE: 定义为 0x08，此命令用于启动单次转换模式。
这种模式下，设备将执行一次模数转换并返回结果。

ADS1256_CMD_SELFCAL: 定义为 0xF0，这个命令执行自我校准操作，包括偏移和增益校准。
它会更新偏移校准寄存器（OFC）和全量程校准寄存器（FSC）。

ADS1256_CMD_SELFOCAL: 定义为 0xF1，这个命令执行自我偏移校准。
它会更新偏移校准寄存器（OFC）。

ADS1256_CMD_SELFGCAL: 定义为 0xF2，这个命令执行自我增益校准。
它会更新全量程校准寄存器（FSC）。

ADS1256_CMD_SYSOCAL: 定义为 0xF3，这个命令执行系统偏移校准。
与自我校准不同，系统校准需要用户在外部提供校准信号。

ADS1256_CMD_SYSGCAL: 定义为 0xF4，这个命令执行系统增益校准。*/

// ADS1256寄存器地址
#define ADS1256_REG_STATUS               0x00
#define ADS1256_REG_MUX                  0x01
#define ADS1256_REG_ADCON                0x02
#define ADS1256_REG_DRATE                0x03
#define ADS1256_REG_IO                   0x04
#define ADS1256_REG_OFC0                 0x05
#define ADS1256_REG_OFC1                 0x06
#define ADS1256_REG_OFC2                 0x07
#define ADS1256_REG_FSC0                 0x08
#define ADS1256_REG_FSC1                 0x09
#define ADS1256_REG_FSC2                 0x0A
/*ADS1256_REG_STATUS: 地址 0x00，状态寄存器。
这个寄存器包含了设备的状态信息，如数据就绪（DRDY）、缓冲器使能状态、自动校准状态等。

ADS1256_REG_MUX: 地址 0x01，输入多路复用器控制寄存器。

此寄存器用于选择模拟输入通道，确定哪些输入通道连接到ADC进行转换。

ADS1256_REG_ADCON: 地址 0x02，模数转换器控制寄存器。
这个寄存器包含了对ADC进行控制的位，如时钟输出设置、传感器检测电流源设置、PGA增益设置等。

ADS1256_REG_DRATE: 地址 0x03，模数转换数据速率寄存器。
此寄存器用于设置ADC的数据输出速率，即每秒钟采样的次数。

ADS1256_REG_IO: 地址 0x04，通用数字I/O控制寄存器。
此寄存器用于控制和监视设备上的通用数字I/O引脚。

ADS1256_REG_OFC0: 地址 0x05，偏移校准字节0，
这是偏移校准寄存器的一部分，用于存储偏移校准值的最低有效字节。

ADS1256_REG_OFC1: 地址 0x06，偏移校准字节1，
这是偏移校准寄存器的中间字节。

ADS1256_REG_OFC2: 地址 0x07，偏移校准字节2，
这是偏移校准寄存器的最高有效字节。

ADS1256_REG_FSC0: 地址 0x08，全量程校准字节0，
这是全量程校准寄存器的一部分，用于存储全量程校准值的最低有效字节。

ADS1256_REG_FSC1: 地址 0x09，全量程校准字节1，
这是全量程校准寄存器的中间字节。

ADS1256_REG_FSC2: 地址 0x0A，全量程校准字节2，
这是全量程校准寄存器的最高有效字节。*/

// ADS1256配置宏定义
#define ADS1256_PGA_GAIN                0x01
/* "000" 对应的增益是 1，"001" 对应的增益是 2，
以此类推，直到 "111" 对应的增益是 64*/ 
#define ADS1256_SDCS_CURRENT            0x02
/*"
SDCS0 和 SDCS1 位用于设置传感器检测电流源。
00" 表示传感器检测关闭（默认）
"01" 表示传感器检测电流 = 0.5μA
"10" 表示传感器检测电流 = 2μA
"11" 表示传感器检测电流 = 10μA*/

// 函数声明
void SPI_Init(void);
void ADS1256_SendCommand(uint8_t command);
void ADS1256_WriteRegister(uint8_t regAddr, uint8_t *data, uint16_t length);
void ADS1256_ReadRegister(uint8_t regAddr, uint8_t *data, uint16_t length);
uint32_t ADS1256_ReadData(void);
void InitOscilloscopeADCs(void);
void StartADCCapture(void);
uint32_t ReadADCData(void);
bool ADS1256_DataReady(void);

