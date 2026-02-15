# SimulateIIC - GPIO模拟I²C通信框架

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Platform: ESP32](https://img.shields.io/badge/Platform-ESP32-green.svg)](https://www.espressif.com/)
[![Language: C](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))

一个轻量级、可移植的GPIO模拟I²C通信框架，支持在不同嵌入式平台之间轻松移植。已在ESP-IDF ESP32环境下通过BMP280传感器驱动测试验证。

## 📋 目录

- [特性](#特性)
- [快速开始](#快速开始)
- [项目结构](#项目结构)
- [API文档](#api文档)
- [移植指南](#移植指南)
- [示例项目](#示例项目)
- [许可证](#许可证)

## ✨ 特性

- **轻量级设计**: 纯C语言实现，无外部依赖
- **高度可移植**: 通过简单的端口层实现跨平台支持
- **完整I²C功能**: 支持标准I²C读写操作
- **错误处理**: 详细的错误返回码
- **易于集成**: 简单的API接口，快速上手
- **多平台支持**: 已在ESP32平台验证，支持其他MCU移植

## 🚀 快速开始

### 1. 克隆项目

```bash
git clone https://github.com/Dreams-Possible/SimulateIIC.git
cd SimulateIIC
```

### 2. 集成到你的项目

将 `simulate_iic/` 目录复制到你的项目中，并配置端口层。

### 3. 基本使用示例

```c
#include "simulate_iic.h"

// 初始化I²C
simulate_iic_init();

// 写入数据到设备
uint8_t data_to_write[] = {0x01, 0x02, 0x03};
uint8_t result = simulate_iic_write_register(0x76, 0x00, data_to_write, 3);

if (result == 0) {
    printf("写入成功\n");
} else {
    printf("写入失败，错误码: %d\n", result);
}

// 从设备读取数据
uint8_t read_buffer[3];
result = simulate_iic_read_register(0x76, 0x00, read_buffer, 3);

if (result == 0) {
    printf("读取成功: %02X %02X %02X\n", 
           read_buffer[0], read_buffer[1], read_buffer[2]);
}
```

## 📁 项目结构

```
SimulateIIC/
├── simulate_iic/                    # 核心框架
│   ├── simulate_iic.h              # 公共API头文件
│   ├── simulate_iic.c              # I²C协议实现
│   ├── simulate_iic_port.h         # 端口层接口定义
│   └── simulate_iic_port.c         # 端口层实现（需平台适配）
├── ESP-IDF ESP32 Port/             # ESP32平台移植示例
│   ├── Base/                       # 基础移植示例
│   └── gpio/                       # GPIO配置示例
├── LICENSE                         # GPL v3许可证
└── README.md                       # 本文档
```

## 📚 API文档

### 初始化函数

```c
/**
 * @brief 初始化模拟I²C总线
 * 
 * 初始化端口层并将SDA和SCL线设置为高电平状态。
 */
void simulate_iic_init(void);
```

### 寄存器写入函数

```c
/**
 * @brief 向I²C设备寄存器写入数据
 * 
 * @param dev_addr 设备地址（7位地址）
 * @param reg_addr 寄存器地址
 * @param data 要写入的数据缓冲区
 * @param len 数据长度
 * @return uint8_t 错误码：
 *                 0 - 成功
 *                 1 - 设备地址ACK错误
 *                 2 - 寄存器地址ACK错误
 *                 3 - 数据ACK错误
 */
uint8_t simulate_iic_write_register(uint8_t dev_addr, uint8_t reg_addr, 
                                   uint8_t* data, uint8_t len);
```

### 寄存器读取函数

```c
/**
 * @brief 从I²C设备寄存器读取数据
 * 
 * @param dev_addr 设备地址（7位地址）
 * @param reg_addr 寄存器地址
 * @param data 读取数据缓冲区
 * @param len 要读取的数据长度
 * @return uint8_t 错误码：
 *                 0 - 成功
 *                 1 - 设备地址ACK错误（写模式）
 *                 2 - 寄存器地址ACK错误
 *                 3 - 设备地址ACK错误（读模式）
 */
uint8_t simulate_iic_read_register(uint8_t dev_addr, uint8_t reg_addr, 
                                  uint8_t* data, uint8_t len);
```

### 端口层接口

```c
/**
 * @brief 初始化GPIO端口
 */
void port_init(void);

/**
 * @brief 设置SCL线电平
 * @param bit 电平值（0-低电平，1-高电平）
 */
void scl_write(uint8_t bit);

/**
 * @brief 设置SDA线电平
 * @param bit 电平值（0-低电平，1-高电平）
 */
void sda_write(uint8_t bit);

/**
 * @brief 读取SDA线电平
 * @return uint8_t 电平值（0-低电平，1-高电平）
 */
uint8_t sda_read(void);
```

## 🔧 移植指南

### 步骤1: 实现端口层

在 `simulate_iic_port.c` 中实现以下函数：

```c
#include "simulate_iic.h"

// 根据你的平台配置GPIO引脚
#define SDA_PIN 21
#define SCL_PIN 22

void port_init() {
    // 初始化SDA和SCL引脚为GPIO模式
    // 配置引脚方向（输入/输出）
}

void scl_write(uint8_t bit) {
    // 设置SCL引脚电平
    // gpio_set_level(SCL_PIN, bit);
}

void sda_write(uint8_t bit) {
    // 设置SDA引脚电平（输出模式）
    // gpio_set_level(SDA_PIN, bit);
}

uint8_t sda_read() {
    // 读取SDA引脚电平（输入模式）
    // return gpio_get_level(SDA_PIN);
}
```

### 步骤2: 配置时序

如果需要调整时序，可以修改 `simulate_iic.c` 中的延时函数或添加适当的延时。

### 步骤3: 集成测试

使用I²C设备（如BMP280传感器）进行功能测试。

## 📖 示例项目

### ESP32平台示例

项目包含完整的ESP-IDF示例项目：

1. **基础示例** (`ESP-IDF ESP32 Port/Base/`)
   - 最小化配置示例
   - 包含CMake构建系统

2. **GPIO配置示例** (`ESP-IDF ESP32 Port/gpio/`)
   - 具体的GPIO引脚配置
   - 可直接运行的示例

## 📄 许可证

本项目采用 **GNU General Public License v3.0** 许可证。详情请参阅 [LICENSE](LICENSE) 文件。

```
Copyright (C) 2023 Dreams-Possible

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
```

---

**SimulateIIC** - 让嵌入式I²C开发更简单！ 🚀