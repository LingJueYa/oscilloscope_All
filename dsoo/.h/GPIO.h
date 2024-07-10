#include <stdint.h> // 包含对基本数据类型的定义

// 定义GPIO引脚编号
#define GPIO00_PIN 00
#define GPIO01_PIN 01
#define GPIO02_PIN 02
#define GPIO03_PIN 03

// 定义GPIO功能模式
#define GPIO_FUNCTION_INPUT  0x0
#define GPIO_FUNCTION_OUTPUT 0x1

// 定义GPIO输出电平
#define GPIO_OUTPUT_LOW  0x0
#define GPIO_OUTPUT_HIGH 0x1

// 定义GPIO配置寄存器地址
#define GPIO_OEN_REG   0x1fe00500 // GPIO 输出使能寄存器
#define GPIO_O_REG     0x1fe00510 // GPIO 输出值寄存器
#define GPIO_I_REG     0x1fe00520 // GPIO 输入值寄存器

// 函数原型声明
void GPIO_SetPinDirection(uint8_t pin, uint8_t direction);
void GPIO_SetPinState(uint8_t pin, uint8_t state);
void GPIO_ReadPinState(uint8_t pin);
void InitGPIOs(void);

