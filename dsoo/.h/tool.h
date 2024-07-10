
#define ADS1255_INTERFACE_H

#include <stdint.h>

void StartADCConversion(uint8_t mode);
uint8_t ADC_ConversionComplete();
uint32_t ReadADCData(uint8_t channel);
void ProcessADCData();
void SPI_SendCommand(uint8_t command);
uint32_t SPI_ReadData();
uint8_t Hardware_CheckDRDYPin();
float ConvertToVoltage(uint32_t data);
