#include"simulate_iic.h"
#ifdef SIMULATE_IIC_H

//config
#define SDA 3//sda pin
#define SCL 2//scl pin

//port init
void port_init();
//scl write
void scl_write(uint8_t bit);
//sda write
void sda_write(uint8_t bit);
//sda read
uint8_t sda_read();

//port init
void port_init()
{
    gpio_config_t config={0};
    //sda
    config.intr_type=GPIO_INTR_DISABLE;
    config.mode=GPIO_MODE_OUTPUT;
    config.pin_bit_mask=(1ULL<<SDA);
    config.pull_down_en=0;
    config.pull_up_en=0;
    gpio_config(&config);
    //scl
    config.intr_type=GPIO_INTR_DISABLE;
    config.mode=GPIO_MODE_OUTPUT;
    config.pin_bit_mask=(1ULL<<SCL);
    config.pull_down_en=0;
    config.pull_up_en=0;
    gpio_config(&config);
    return;
}

//scl write
void scl_write(uint8_t bit)
{
    gpio_set_level(SCL,bit);
    return;
}

//sda write
void sda_write(uint8_t bit)
{
    gpio_config_t config={0};
    config.intr_type=GPIO_INTR_DISABLE;
    config.mode=GPIO_MODE_OUTPUT;
    config.pin_bit_mask=(1ULL<<SDA);
    config.pull_down_en=0;
    config.pull_up_en=0;
    gpio_config(&config);
    gpio_set_level(SDA,bit);
    return;
}

//sda read
uint8_t sda_read()
{
    gpio_config_t config={0};
    config.intr_type=GPIO_INTR_DISABLE;
    config.mode=GPIO_MODE_INPUT;
    config.pin_bit_mask=(1ULL<<SDA);
    config.pull_down_en=0;
    config.pull_up_en=0;
    gpio_config(&config);
    return gpio_get_level(SDA);
}

#endif//#ifdef SIMULATE_IIC_H
