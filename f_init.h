#ifndef __F_INIT_H
#define __F_INIT_H

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include "stm32f10x_dma.h"              // Keil::Device:StdPeriph Drivers:DMA
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI
#include "stm32f10x_i2c.h"              // Keil::Device:StdPeriph Drivers:I2C

//#define EXTI_ON

#define PRESCALER 72
#define PERIOD 1000

#define LED_ON() GPIO_SetBits(GPIOA, GPIO_Pin_5)
#define LED_OFF() GPIO_ResetBits(GPIOA, GPIO_Pin_5)

void key_init(void);
void delay(uint16_t t);
void tim2_init(void);
void usart2_init(void);

void i2c_init(void);
void i2c_send(uint8_t dev_addr, uint8_t control_req, uint8_t data_req);

void i2c_start(void);
void i2c_sendaddress_write(uint8_t address);
void i2c_senddata(uint8_t data);
void i2c_stop(void);
void i2c_registerwrite(uint8_t device_addr, uint8_t reg_addr, uint8_t data_1, uint8_t data_2, uint8_t data_3);

void lcd_init_1(void);
void lcd_init_2(void);

#endif
