#include <REGX52.H>
#include "Delay.h"

sbit RCK=P3^5;
sbit SCK=P3^6;
sbit SER=P3^4;

#define MATRTX_LED_PORT			P0

/**
   * @brief  点阵屏初始化
   * @param  无
   * @retval 无
   */		
void MatrixLED_Init()
{
	SCK=0;
	RCK=0;
}

/**
   * @brief  74HC95写入一个字节
   * @param  要写的字节
   * @retval 无
   */		
void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		SER=Byte&(0x80>>i);
		SCK=1;
		SCK=0;
	}
	RCK=1;
	RCK=0;
}
/**
   * @brief  LCD点阵屏显示一列数据
   * @param  Column 选择列，范围0~7，0在最左
   * @param  Data 选择列的数据，高位在最上，1为亮，0为灭
   * @retval
   */		
void MatrixLED_ShowColumn(unsigned char Column,Data)
{
	_74HC595_WriteByte(Data);
	MATRTX_LED_PORT=~(0x80>>Column);
	Delay(1);
	MATRTX_LED_PORT=0xFF;
}