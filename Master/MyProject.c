 #include "spimaster.h"
 uint8_t x=0;
 void main()
 {     BEGIN();
        beginTransaction(LSBFIRST, clock_devider, bits_transfared,SPI_MODE0);
      GPIOA_ODR &= ~(1<<9);
        while(1){
               x= SPI_TransmitReceive(1);
              Delay_ms(1000) ;
          }
 }