#include "temperature_sensor.h"
#include "i2c.h"
#include "string.h"
#define TEMP_SENSOR_ADDR  0x90

uint8_t i2c_dma_ready=0;


 uint16_t get_temperature( ){

    //straight code, 1st bit is sign; from -127...+127 , 1st byte -integer part 2nd fractional
    uint16_t temperature = 0;
    uint8_t intg = 0;
    uint8_t frac = 0;
    uint8_t sign = 0;
    uint8_t temp_buff[2];

    I2C_DMA_Read(TEMP_SENSOR_ADDR);

    //wait untill dma ends
    while(i2c_dma_ready==0);
    i2c_dma_ready=0;
    memcpy(temp_buff, I2C_Rx_Buffer, 2);


    if((temp_buff[0] & 0x80) != 0 ){
            sign = 1;
            uint16_t b = ~((0xE000 | (((temp_buff[0]<<8) +temp_buff[1])>>3))-1);
            intg = b>>4;
            frac = 0x0F & b;
    }else{
            sign=0;
            uint16_t b = ((temp_buff[0]<<8) +temp_buff[1])>>3;
            intg = b>>4;
            frac = (0x0F & b) * 625 / 100;
    }
    temperature = sign<<15 |intg<<8 | frac;

    return temperature;
}

