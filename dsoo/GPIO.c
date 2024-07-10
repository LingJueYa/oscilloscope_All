#include<GPIO.h>
#include <stdint.h>
void GPIO_SetPinDirection(uint8_t pin, uint8_t direction) {
    // 设置GPIO引脚方向
    volatile uint64_t *gpio_oen_reg = (uint64_t *)GPIO_OEN_REG;
    if (direction == GPIO_FUNCTION_INPUT) {
        *gpio_oen_reg |= (1ULL << pin); // 设置为输入
    } else { // GPIO_FUNCTION_OUTPUT
        *gpio_oen_reg &= ~(1ULL << pin); // 设置为输出
    }
}

void GPIO_SetPinState(uint8_t pin, uint8_t state) {
    // 设置GPIO引脚输出状态
    volatile uint64_t *gpio_o_reg = (uint64_t *)GPIO_O_REG;
    if (state == GPIO_OUTPUT_HIGH) {
        *gpio_o_reg |= (1ULL << pin); // 设置为高电平
    } else { // GPIO_OUTPUT_LOW
        *gpio_o_reg &= ~(1ULL << pin); // 设置为低电平
    }
}

void GPIO_ReadPinState(uint8_t pin) {
    // 读取GPIO引脚输入状态
    volatile uint64_t *gpio_i_reg = (uint64_t *)GPIO_I_REG;
    uint64_t state = (*gpio_i_reg >> pin) & 0x1;
    // 根据state的值，进行相应的处理
}

void InitGPIOs() {
    // 初始化专用GPIO引脚
    GPIO_SetPinDirection(GPIO00_PIN, GPIO_FUNCTION_OUTPUT);
    GPIO_SetPinDirection(GPIO01_PIN, GPIO_FUNCTION_INPUT);
    GPIO_SetPinDirection(GPIO02_PIN, GPIO_FUNCTION_OUTPUT);
    GPIO_SetPinDirection(GPIO03_PIN, GPIO_FUNCTION_INPUT);

    // 设置专用GPIO引脚的初始状态
    GPIO_SetPinState(GPIO00_PIN, GPIO_OUTPUT_HIGH); // GPIO00设置为高电平
    GPIO_SetPinState(GPIO01_PIN, GPIO_OUTPUT_LOW);  // GPIO01设置为低电平
    // ... 其他GPIO初始化状态

    // 读取GPIO01的输入状态
    GPIO_ReadPinState(GPIO01_PIN);
}