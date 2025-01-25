#include"simulate_iic.h"
#ifdef SIMULATE_IIC_H
#ifndef SIMULATE_IIC_PORT_H
#define SIMULATE_IIC_PORT_H
//inculde
#include<stdint.h>
#include"driver/gpio.h"

//port init
void port_init();
//scl write
void scl_write(uint8_t bit);
//sda write
void sda_write(uint8_t bit);
//sda read
uint8_t sda_read();

#endif//#ifndef SIMULATE_IIC_PORT_H
#endif//#ifdef SIMULATE_IIC_H
