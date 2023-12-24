 #include "sppppi.h"
  uint8_t x=0;
 void main()
 {     BEGIN();  // slave mode and pa9 is input
       beginTransaction(LSBFIRST, clock_devider, bits_transfared,SPI_MODE0);
    //  GPIOA_IDR &= ~(1<<9);
        while(!(GPIOA_IDR & (1 << 9))){
               x= SPI_TransmitReceive(8);
               if(x==1)
               {     GPIOA_ODR |=(1 << 0)  ; //pA0 HIGH
                     Delay_ms(3000) ;
                     GPIOA_ODR &=~(1 << 0)  ; //pA0 LOW
                      Delay_ms(3000) ;
               }
          }
 }