#include<stdio.h>
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"

#include"simulate_iic.h"

void app_main(void)
{
    //simulate iic init
    simulate_iic_init();
    uint8_t dev_addr=0x01;
    uint8_t write_reg_addr=0x02;
    uint8_t read_reg_addr=0x03;
    uint8_t write_data[2]={0};
    uint8_t read_data[2]={0};
    //write to register
    simulate_iic_write_register(dev_addr,write_reg_addr,write_data,2);
    //read from register
    simulate_iic_read_register(dev_addr,read_reg_addr,read_data,2);
}
