#include "i2c.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_dma.h"
#include "string.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include "temperature_sensor.h"


  
      uint8_t offset = 0x20;
         uint8_t tempDat[3],j1=0, flag=0;


int main(void)
{
    config_I2C();

    uint16_t temperature=0;
    while(1){
       temperature= get_temperature();

       //delay
       for(int i=0; i<100000;i++);
    }

}

