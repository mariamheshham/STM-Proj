#include "spislave.h"
void BEGIN(void)
{
    RCC_APB2ENR |= (1 << 12);        // Enable SPI1 CLock
    //SPI1_CR1 |= (1 << 2);            // Master Mode
    SPI1_CR1 &= ~(1 << 2);            // slave Mode
    SPI1_CR1 |= (1 << 8) | (1 << 9); // SSM=1, SSi=1 -> Software Slave Management    ,to choose any io pin and make i0t ss_pin
    SPI1_CR1 &= ~(1 << 10);          // RXONLY = 0, full-duplex
    SPI1_CR2 = 0;
    RCC_AHB1ENR |= (1 << 0);                                        // Enable GPIOA Clock
    GPIOA_MODER |= (2 << 10) | (2 << 12) | (2 << 14) ;   // Alternate functions for PA5, PA6, PA7
    //GPIOA_MODER |=(1 << 18)  ; //pA9 OUTPUT
    GPIOA_MODER |=(1 << 0)  ; //pA0 OUTPUT
    GPIOA_MODER &= ~(1 << 18) ;//PA9 INPUT
    GPIOA_OSPEEDR |= (3 << 10) | (3 << 12) | (3 << 14) | (3 << 18); // HIGH Speed for PA5, PA6, PA7, PA9
    GPIOA_AFRL = 0;
    GPIOA_AFRL |= (5 << 20) | (5 << 24) | (5 << 28); // AF5(SPI1) for PA5, PA6, PA7
}
void set_data_mode(int bit_mode, int clock_mode)
{
    if (bit_mode == 8)
    {
        SPI1_CR1 &= ~(1 << 11); // DFF=0, 8 bit data
    }
    else if (bit_mode == 16)
    {
        SPI1_CR1 |= (1 << 11); // DFF=1, 16 bit data
    }
    SPI1_CR1 &= ~(3 << 0);        // Clear bits 0 and 1 (CPOL and CPHA) we make oring with0
    SPI1_CR1 |= (clock_mode & 3); // Set bits 0 and 1 based on the provided mode
}
void set_clock_divider(int divider)
{
    SPI1_CR1 &= ~(7 << 3);            // Clear bits 3, 4, and 5 (BR)
    SPI1_CR1 |= ((divider & 7) << 3); // Set bits 3, 4, and 5 based on the provided divider we divide on7to
}
void setBitOrder(int byteOrder)
{
    if (byteOrder == LSBFIRST)
    {
        // Set LSBFIRST in SPI_CR1 register
        SPI1_CR1 &= ~(1 << 7); // Clear bit 7 (MSBFIRST)
    }
    else if (byteOrder == MSBFIRST)
    {
        // Set MSBFIRST in SPI_CR1 register
        SPI1_CR1 |= (1 << 7); // Set bit 7 (MSBFIRST)
    }
    // Add error handling or default case as needed
}
void end()
{
    // Disable SPI by clearing the SPE bit in the control register (CR1)
    SPI1_CR1 &= ~(1 << 6); // SPE bit position for SPI enable
}
 uint8_t SPI_TransmitReceive( uint8_t var)
{
    while (!(SPI1_SR & (1 << 1))) ;           // Wait until transmit buffer is empty
    SPI1_DR = var; // Send data
    while (!((SPI1_SR) & (1 << 1)))  ; // wait for TXE bit to set -> This will indicate that the buffer is empty
    while (((SPI1_SR) & (1 << 7)))
        ; // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication
    while (!(SPI1_SR & (1 << 0)))
        ;           // Wait until receive buffer is not empty
    return SPI1_DR; // Read received data
}

void beginTransaction(int byteOrder1,  int baudRate1,  int dataMode1, int clockMode1)
{
    set_clock_divider(baudRate1);
    setBitOrder(byteOrder1);
    set_data_mode(dataMode1, clockMode1);
}
void end_transaction(void)
{
    while (!((SPI1_SR) & (1 << 0))) ;
    while (!((SPI1_SR) & (1 << 1)));
    while (((SPI1_SR) & (1 << 7)));
    end();
}
