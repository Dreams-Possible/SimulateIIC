#include"simulate_iic.h"
#ifdef SIMULATE_IIC_H

//start connection
static void start();
//end connection
static void end();
//read ack
static uint8_t read_ack();
//send ack
static void send_ack(uint8_t ack);
//read byte
static int8_t read_byte();
//send byte
static void send_byte(uint8_t byte);
//simulate iic init
void simulate_iic_init();
//write to register
uint8_t simulate_iic_write_register(uint8_t dev_addr,uint8_t reg_addr,uint8_t*data,uint8_t len);
//read from register
uint8_t simulate_iic_read_register(uint8_t dev_addr,uint8_t reg_addr,uint8_t*data,uint8_t len);

//start connection
static void start()
{
	sda_write(1);
	scl_write(1);
	sda_write(0);
	scl_write(0);
}

//end connection
static void end()
{
	sda_write(0);
	scl_write(1);
	sda_write(1);
}

//read ack
static uint8_t read_ack()
{
	sda_write(1);
	scl_write(1);
	uint8_t ack=sda_read();
	scl_write(0);
	return ack;
}

//send ack
static void send_ack(uint8_t ack)
{
	sda_write(ack);
	scl_write(1);
	scl_write(0);
}

//read byte
static int8_t read_byte()
{
    uint8_t byte=0;
    sda_write(1);//释放sda_write
    for(uint8_t f=0;f<8;++f)
	{
		scl_write(1);
		if(sda_read())
		{
			byte|=(0x80>>f);//将16进制数一位一位读入
		}
		scl_write(0);
	}
    return byte;//读取到的数据
}

//send byte
static void send_byte(uint8_t byte)
{
    for(uint8_t a=0;a<8;++a)
    {
    	sda_write(byte&(0x80>>a));//将16进制数一位一位取出来
    	scl_write(1);
    	scl_write(0);
    }
}

//simulate iic init
void simulate_iic_init()
{
	//port init
	port_init();
	sda_write(1);
	scl_write(1);
}

//write to register
uint8_t simulate_iic_write_register(uint8_t dev_addr,uint8_t reg_addr,uint8_t*data,uint8_t len)
{
	start();
	send_byte(dev_addr<<1|0);
	if(read_ack())
	{
		return 1;
	}
	send_byte(reg_addr);
	if(read_ack())
	{
		return 2;
	}
	while(len)
	{
		send_byte(*data);
		if(read_ack())
		{
			return 3;
		}
		--len;
		++data;
	}
	end();
	return 0;
}

//read from register
uint8_t simulate_iic_read_register(uint8_t dev_addr,uint8_t reg_addr,uint8_t*data,uint8_t len)
{
	start();
	send_byte(dev_addr<<1|0);
	if(read_ack())
	{
		return 1;
	}
	send_byte(reg_addr);
	if(read_ack())
	{
		return 2;
	}
	start();
	send_byte(dev_addr<<1|1);
	if(read_ack())
	{
		return 3;
	}
	while(len)
	{
		*data=read_byte();
		if(len==1)
		{
			send_ack(1);
		}else
		{
			send_ack(0);
		}
		--len;
		++data;
	}
	end();
	return 0;
}

#endif//#ifdef SIMULATE_IIC_H

