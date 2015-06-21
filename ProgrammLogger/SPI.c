/*
 * SPI.c
 *
 *  Created on: 15.05.2014
 *      Author: Wastlhuber
 */

#include "SPI.h"

void LCD_Init()
{
	EnableStartOfFrame(SPI001_Handle0);

	LCD_Command(0b11100010);	//Reset

	LCD_Command(0x40);
	uLCDsleep(10);

	LCD_Command(0xA1);
	uLCDsleep(10);

	LCD_Command(0xC0);
	uLCDsleep(10);

	LCD_Command(0xA6);
	uLCDsleep(200);

	LCD_Command(0xA2);
	uLCDsleep(10);

	LCD_Command(0x2F);
	uLCDsleep(10);

	LCD_Command(0xF8);
	uLCDsleep(10);

	LCD_Command(0x00);
	uLCDsleep(10);

	LCD_Command(0x27);
	uLCDsleep(10);

	LCD_Command(0x81);
	uLCDsleep(10);

	LCD_Command(0x16);
	uLCDsleep(10);

	LCD_Command(0xAC);
	uLCDsleep(10);

	LCD_Command(0x00);
	uLCDsleep(10);

	LCD_Command(0xAF);
	uLCDsleep(10);

	EnableEndOfFrame(SPI001_Handle0);

	LCD_Clear();
}

void LCD_Clear()
{
	EnableStartOfFrame(SPI001_Handle0);
	for(int j = 0;j<8;j++){
		LCD_GOTO_ADDRESS(j,0);
		for(int i=0;i<128;i++){
				LCD_Data(0);
			}
	}
	LCD_GOTO_ADDRESS(0,0);
	EnableEndOfFrame(SPI001_Handle0);
}

void lcd_moveto_xy(uint8_t page, uint8_t column) {
  LCD_GOTO_ADDRESS(page,column);
}

void LCD_Command(uint16_t w_data)
{
	uint16_t tmp;
	uint8_t Status1 = 0;
	uint8_t Status2 = 0;
	uint16_t data;

	IO004_ResetPin(IO004_Handle0);

	SPI001_ClearFlag(&SPI001_Handle0,SPI001_RECV_IND_FLAG);
	SPI001_ClearFlag(&SPI001_Handle0,SPI001_ALT_RECV_IND_FLAG);
	data = w_data;
	SPI001_WriteData(&SPI001_Handle0,&data,SPI001_STANDARD);
	/*wait for dummy to be received*/
	do
	{
	   Status1 = SPI001_GetFlagStatus(&SPI001_Handle0,SPI001_RECV_IND_FLAG);
	   Status2 = SPI001_GetFlagStatus(&SPI001_Handle0,SPI001_ALT_RECV_IND_FLAG);
	}while(!((Status1 == SPI001_SET) || (Status2 == SPI001_SET)));
	SPI001_ReadData(&SPI001_Handle0,&tmp);	// dummy read

	IO004_SetPin(IO004_Handle0);
	IO004_ResetPin(IO004_Handle0);
}

void LCD_Data(uint16_t w_data)
{
	EnableStartOfFrame(SPI001_Handle0);

	uint16_t tmp;
	uint8_t Status1 = 0;
	uint8_t Status2 = 0;
	uint16_t data;

	IO004_SetPin(IO004_Handle0);

	SPI001_ClearFlag(&SPI001_Handle0,SPI001_RECV_IND_FLAG);
	SPI001_ClearFlag(&SPI001_Handle0,SPI001_ALT_RECV_IND_FLAG);
	data = w_data;
	SPI001_WriteData(&SPI001_Handle0,&data,SPI001_STANDARD);
	/*wait for dummy to be received*/
	do
	{
	   Status1 = SPI001_GetFlagStatus(&SPI001_Handle0,SPI001_RECV_IND_FLAG);
	   Status2 = SPI001_GetFlagStatus(&SPI001_Handle0,SPI001_ALT_RECV_IND_FLAG);
	}while(!((Status1 == SPI001_SET) || (Status2 == SPI001_SET)));
	SPI001_ReadData(&SPI001_Handle0,&tmp);	// dummy read

	IO004_ResetPin(IO004_Handle0);
	IO004_SetPin(IO004_Handle0);

	EnableEndOfFrame(SPI001_Handle0);
}

void uLCDsleep(uint16_t usec)
{
	uint32_t i,j;
for(i=0;i<usec/2;i++)
	j++;

}
void msleep(uint16_t msec){
	for(uint32_t i=0;i<msec*10;i++){
		uLCDsleep(1000);
	}
}
