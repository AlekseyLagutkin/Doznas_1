#include "f_init.h"

void key_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef StrA5;
	GPIO_InitTypeDef StrC;
	
	StrA5.GPIO_Mode = GPIO_Mode_Out_PP;   //Светодиод
	StrA5.GPIO_Pin = GPIO_Pin_5;
	StrA5.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &StrA5);
	
	StrC.GPIO_Mode = GPIO_Mode_Out_PP;   //Строки
	StrC.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	StrC.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &StrC);
	
	StrC.GPIO_Mode = GPIO_Mode_IPD;   //Столбцы
	StrC.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	StrC.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &StrC);
}

void tim2_init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitTypeDef StrT2;
	TIM_TimeBaseStructInit(&StrT2);
	StrT2.TIM_Prescaler = PRESCALER - 1;
	StrT2.TIM_Period = PERIOD - 1;
	TIM_TimeBaseInit(TIM2, &StrT2);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);

	/*TIM_OCInitTypeDef StrPWM;
	StrPWM.TIM_Pulse = PERIOD / 2 - 1;
	StrPWM.TIM_OCMode = TIM_OCMode_PWM1;
	StrPWM.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIM2, &StrPWM);*/
	
	
	//TIM2->CCR1 = PERIOD/2 - 1;   //ШИМ
	//TIM2->CCER |= TIM_CCER_CC1E;   //ШИМ
	//TIM2->CCMR1 |= TIM_CCMR1_OC1M;
	
	NVIC_EnableIRQ(TIM2_IRQn);
	//NVIC_SetPriority(TIM2_IRQn, 1);
	
	/*RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;   //Тактирование таймера TIM2
	TIM2->PSC = PRESCALER - 1;
	TIM2->ARR = PERIOD - 1;
	TIM2->CR1 |= TIM_CR1_ARPE;
	TIM2->CR1 |= TIM_CR1_CEN;*/
}

void usart2_init(void)
{
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	GPIO_InitTypeDef StrA2;
	GPIO_InitTypeDef StrA3;
	
	StrA2.GPIO_Mode = GPIO_Mode_AF_PP;
	StrA2.GPIO_Pin = GPIO_Pin_2;
	StrA2.GPIO_Speed = GPIO_Speed_2MHz;
	
	StrA3.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	StrA3.GPIO_Pin = GPIO_Pin_3;
	StrA3.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(GPIOA, &StrA2);
	GPIO_Init(GPIOA, &StrA3);
	
	USART_InitTypeDef StrU;
	
	StrU.USART_BaudRate = 9600;
	StrU.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	StrU.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	StrU.USART_Parity = USART_Parity_No;
	StrU.USART_StopBits = USART_StopBits_1;
	StrU.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART2, &StrU);
	USART_Cmd(USART2, ENABLE);
	
	/*NVIC_InitTypeDef StrN;
	
	StrN.NVIC_IRQChannel = USART2_IRQn;
	StrN.NVIC_IRQChannelCmd = ENABLE;
	StrN.NVIC_IRQChannelPreemptionPriority = 0;
	StrN.NVIC_IRQChannelSubPriority = 0;
	
	NVIC_Init(&StrN);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	NVIC_EnableIRQ(USART2_IRQn);*/
}

void i2c_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	
	GPIO_InitTypeDef StrB;
	
	StrB.GPIO_Speed = GPIO_Speed_2MHz;
	StrB.GPIO_Mode = GPIO_Mode_AF_OD;   //***
	StrB.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	
	GPIO_Init(GPIOB, &StrB);
	
	I2C_InitTypeDef StrI;
	
	I2C_StructInit(&StrI);
	
	StrI.I2C_Mode = I2C_Mode_I2C;
	StrI.I2C_DutyCycle = I2C_DutyCycle_2;
	StrI.I2C_OwnAddress1 = 0x00;
	StrI.I2C_Ack = I2C_Ack_Enable;
	StrI.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	StrI.I2C_ClockSpeed = 100000;   //***

	I2C_Init(I2C1, &StrI);
	
	I2C_Cmd(I2C1, ENABLE);
	
	//I2C1->CR1 |= I2C_CR1_SWRST;
	//I2C1->CR1 &= ~I2C_CR1_SWRST;   //Сброс I2C
	
	//I2C1->OAR2 &= ~I2C_OAR2_ENDUAL;   //Откл режим двойной индексации
	//I2C1->CR1 &= ~I2C_CR1_ENGC;   //Откл широковещательную адресацию
	//I2C1->CR1 |= I2C_CR1_NOSTRETCH;   //Выкл отложенный отклик
	//I2C1->CR1 &= ~I2C_CR1_PE;   //Откл I2C
	
	//uint32_t pclk = 72000000;
	//I2C1->CR2 |= pclk / 1000000;   //Частота
	//I2C1->TRISE |= I2C_TRISE_TRISE;
	//I2C1->CCR |= pclk / (100000 * 2);
	//I2C1->TRISE = (pclk / 1000000) + 1;
	//I2C1->CCR |= I2C_CCR_DUTY;
	//I2C1->CCR |= I2C_CCR_FS;
	//I2C1->CR1 |= I2C_CR1_PE;
}

void i2c_send(uint8_t dev_addr, uint8_t control_req, uint8_t data_req)
{
	uint8_t tx_buf[2];
	
	tx_buf[0] = control_req;
	tx_buf[1] = data_req;
	
	I2C_GenerateSTART(I2C1, ENABLE);
}

void i2c_start(void)   //Отправка старт бита
{
	I2C1->CR1 |= I2C_CR1_START;
	while(!(I2C1->SR1 & I2C_SR1_SB))
	{
	}
	uint32_t temp = I2C1->SR1;   //***
}

void i2c_sendaddress_write(uint8_t address)   //Отправка адреса устройства
{
	I2C1->DR = address << 1;
	while(!(I2C1->SR1 & I2C_SR1_ADDR))
	{
	}
	uint32_t temp_1 = I2C1->SR1;   //***
	uint32_t temp_2 = I2C1->SR2;   //***
}

void i2c_senddata(uint8_t data)   //Отправка данных
{
	while(!(I2C1->SR1 & I2C_SR1_TXE))
	{
	}
	uint32_t temp_1 = I2C1->SR1;   //***
	I2C1->DR = data;
	while(!(I2C1->SR1 & I2C_SR1_BTF))
	{
	}
}

void i2c_stop(void)   //Отправка STOP-бита
{
	I2C1->CR1 |= I2C_CR1_STOP;
}

void i2c_registerwrite(uint8_t device_addr, uint8_t reg_addr, uint8_t data_1, uint8_t data_2, uint8_t data_3)
{
	i2c_start();
	//delay(10);
	i2c_sendaddress_write(device_addr);
	//delay(10);
	i2c_senddata(reg_addr);
	//delay(10);
	i2c_senddata(data_1);
	//delay(10);
	i2c_senddata(data_2);
	//delay(10);
	i2c_senddata(data_3);
	//delay(10);
	i2c_stop();
}

void lcd_init_1(void)
{
	delay(40);
	i2c_start();
	delay(2);
	i2c_sendaddress_write(0x27);
	delay(2);
	
	i2c_senddata(0x34);   //8 бит
	//delay(2);
	i2c_senddata(0x30);
	//delay(2);
	i2c_senddata(0x04);
	//delay(2);
	i2c_senddata(0x00);
	//delay(2);
	
	i2c_senddata(0x34);
	//delay(2);
	i2c_senddata(0x30);
	//delay(2);
	i2c_senddata(0x04);
	//elay(2);
	i2c_senddata(0x00);
	//delay(2);
	
	i2c_senddata(0x34);
	//delay(2);
	i2c_senddata(0x30);
	//delay(2);
	i2c_senddata(0x04);
	//delay(2);
	i2c_senddata(0x00);
	//delay(2);
	
	i2c_senddata(0x24);   //Установка 4-х бит
	//delay(2);
	i2c_senddata(0x20);
	//delay(2);
	i2c_senddata(0x04);
	//delay(2);
	i2c_senddata(0x00);
	//delay(2);
	
	i2c_senddata(0x24);   //2 строки шрифт 5х8
	//delay(2);
	i2c_senddata(0x20);
	//delay(2);
	i2c_senddata(0x84);
	//delay(2);
	i2c_senddata(0x80);
	//delay(2);
	
	i2c_senddata(0x02);   //D=0 C=0 B=0
	//delay(2);
	i2c_senddata(0x00);
	//delay(2);
	i2c_senddata(0x82);
	//delay(2);
	i2c_senddata(0x80);
	//delay(2);
	
	i2c_senddata(0x02);   //Очистка дисплея
	//delay(2);
	i2c_senddata(0x00);
	//delay(2);
	i2c_senddata(0x12);
	//delay(2);
	i2c_senddata(0x10);
	//delay(2);
	
	i2c_senddata(0x02);   //Направление вывода символов
	//delay(2);
	i2c_senddata(0x00);
	//delay(2);
	i2c_senddata(0x62);
	//delay(2);
	i2c_senddata(0x60);
	//delay(2);
	
	i2c_senddata(0x0C);   //B=1 C=0 D=0
	//delay(2);
	i2c_senddata(0x08);
	//delay(2);
	i2c_senddata(0xCC);
	//delay(2);
	i2c_senddata(0xC8);
	//delay(2);
	
	i2c_stop();
}

void lcd_init_2(void)
{
	i2c_start();
	delay(2);
	i2c_sendaddress_write(0x27);
	delay(2);
	i2c_senddata(0x30);   //8 бит
	delay(5);
	i2c_senddata(0x30);   //8 бит
	delay(5);
	i2c_senddata(0x30);   //8 бит
	delay(5);
	i2c_senddata(0x20);   //4 бит
	delay(2);
	
	i2c_senddata(0x2C);   //6 DL=0 N=1 F=0
	//delay(2);
	i2c_senddata(0x28);
	//delay(2);
	i2c_senddata(0x8C);
	//delay(2);
	i2c_senddata(0x88);
	delay(2);
	
	i2c_senddata(0x0C);   //4 D=0 C=0 B=0
	//delay(2);
	i2c_senddata(0x08);
	//delay(2);
	i2c_senddata(0x8C);
	//delay(2);
	i2c_senddata(0x88);
	delay(2);
	
	i2c_senddata(0x0C);   //1 очистка дисплея
	//delay(2);
	i2c_senddata(0x08);
	//delay(2);
	i2c_senddata(0x1C);
	//delay(2);
	i2c_senddata(0x18);
	delay(2);
	
	i2c_senddata(0x0C);   //3 направление вывода символа
	//delay(2);
	i2c_senddata(0x08);
	//delay(2);
	i2c_senddata(0x6C);
	//delay(2);
	i2c_senddata(0x68);
	delay(2);
	
	i2c_senddata(0x0C);   //1 очистка дисплея
	//delay(2);
	i2c_senddata(0x08);
	//delay(2);
	i2c_senddata(0x1C);
	//delay(2);
	i2c_senddata(0x18);
	delay(2);
	
	i2c_senddata(0x0C);   //4 включение дисплея D=1 C=1 B=0
	//delay(2);
	i2c_senddata(0x08);
	//delay(2);
	i2c_senddata(0xFC);
	//delay(2);
	i2c_senddata(0xF8);
	delay(2);
	i2c_stop();
}
