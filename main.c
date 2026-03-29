#include "f_init.h"

uint16_t line;   //Строка
uint16_t col;   //Столбец
uint16_t num;   //Символ
uint16_t tim;   //Счетчик
uint16_t i = 0;
const uint16_t tic = 200;

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		if(i > 0)
		{
		--i;
		}
	}
}

void delay(uint16_t t)
{
	i = t;
	while(i > 0)
	{
	}
}

int main(void)
{
	key_init();
	tim2_init();
	usart2_init();
	i2c_init();
	
	while(1)
	{
		tim = TIM2->CNT;
		if(tim < 250)
		{
			GPIO_Write(GPIOC, 0x1);
		}
		else if(tim >= 250 && tim < 500)
		{
			GPIO_Write(GPIOC, 0x2);
		}
		else if(tim >= 500 && tim < 750)
		{
			GPIO_Write(GPIOC, 0x4);
		}
		else
		{
			GPIO_Write(GPIOC, 0x8);
		}
		
		line = GPIO_ReadOutputData(GPIOC);
		col = GPIO_ReadInputData(GPIOC) & 0xF0;
		num = line | col;
		
		if((col == 16) || (col == 32) || (col == 64) || (col == 128)) 
		{
			USART_SendData(USART2, num);
			LED_ON();
			delay(tic);
			if(num == 0x81)
			{
				lcd_init_2();   //Настройка интерфейса
			}
			if(num == 0x82)
			{
				i2c_registerwrite(0x27, 0x0C, 0x08, 0x2C, 0x28);   //2 - Установка курсора в начало первой строки
			}
			if(num == 0x84)
			{
				i2c_registerwrite(0x27, 0x1C, 0x18, 0x4C, 0x48);   //5 - Сдвиг курсора вправо
			}
			if(num == 0x88)
			{
				i2c_registerwrite(0x27, 0x8C, 0x88, 0x0C, 0x08);   //8 - запись адреса DRAM
			}
			if(num == 0x11)
			{
				i2c_registerwrite(0x27, 0x3D, 0x39, 0x2D, 0x29);   //10 - запись кода символа
			}
		}
		else
		{
			LED_OFF();
		}
	}
}
