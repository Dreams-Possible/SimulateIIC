#pragma once

//enable simulate_iic
#if 1
#ifndef SIMULATE_IIC_H
#define SIMULATE_IIC_H
//inculde
#include<stdint.h>
#include"simulate_iic_port.h"

//simulate iic init
void simulate_iic_init();
//write to register
uint8_t simulate_iic_write_register(uint8_t dev_addr,uint8_t reg_addr,uint8_t*data,uint8_t len);
//read from register
uint8_t simulate_iic_read_register(uint8_t dev_addr,uint8_t reg_addr,uint8_t*data,uint8_t len);

#endif//#ifndef SIMULATE_IIC_H
#endif//#if 1
