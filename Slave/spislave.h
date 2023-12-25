#include <stdint.h>
#define RCC_BASE_ADDRESS 0x40023800
#define GPIOA_BASE_ADDRESS 0x40020000
#define SPI1_BASE_ADDRESS 0x40013000

#define RCC_AHB1ENR (*((unsigned int *)(RCC_BASE_ADDRESS + 0x30)))
#define RCC_APB2ENR (*((unsigned int *)(RCC_BASE_ADDRESS + 0x44)))

#define GPIOA_MODER (*((unsigned int *)(GPIOA_BASE_ADDRESS + 0x00)))
#define GPIOA_AFRL (*((unsigned int *)(GPIOA_BASE_ADDRESS + 0x20)))
#define GPIOA_OSPEEDR (*((unsigned int *)(GPIOA_BASE_ADDRESS + 0x08)))
#define GPIOA_IDR (*((unsigned int *)(GPIOA_BASE_ADDRESS + 0x10)))    //to  read from pa9
#define GPIOA_ODR (*((unsigned int *)(GPIOA_BASE_ADDRESS + 0x14)))     //to put 1 on pa9
#define SPI1_CR1 (*((unsigned int *)(SPI1_BASE_ADDRESS + 0x00)))
#define SPI1_CR2 (*((unsigned int *)(SPI1_BASE_ADDRESS + 0x04)))
#define SPI1_SR (*((unsigned int *)(SPI1_BASE_ADDRESS + 0x08)))
#define SPI1_DR (*((unsigned int *)(SPI1_BASE_ADDRESS + 0x0C)))

#define SPI_MODE0 0
#define SPI_MODE1 1 // when i call fun i put macros name
#define SPI_MODE2 2
#define SPI_MODE3 3
#define bits_transfared 8 // shift register
#define clock_devider 0   // addnumder from 1 to 7
#define LSBFIRST 0        // Least Significant Bit First
#define MSBFIRST 1        // Most Significant Bit First

void BEGIN(void);
void set_data_mode(int bit_mode, int clock_mode);
void set_clock_divider(int divider);
void setBitOrder(int byteOrder);
void end();
uint8_t SPI_TransmitReceive( uint8_t var);
void beginTransaction(int byteOrder1, int dataMode1, int baudRate1, int clockMode1);
void end_transaction(void);