/*
 * Schach.c
 *
 *  Created on: 24.03.2015
 *      Author: Lüdemann
 */
#include "Schach.h"

void draw_field(void)
{
	for(uint8_t i=0;i<8;i++){
			LCD_GOTO_ADDRESS(i,0);
			if(i==1 || i==3|| i==5 || i==7){
				for(uint8_t j=0;j<64;j++){
					if((j>=0 && j<8) || (j>16 && j<24) || (j>32 && j<40) || (j>48 && j<56)){
						LCD_Data(255);
					}
					else{
						LCD_Data(0);
					}
				}
			}
			else{
				for(uint8_t j=0;j<64;j++){
								if((j>=8 && j<16) || (j>24 && j<32) || (j>40 && j<48) || (j>56 && j<64)){
									LCD_Data(255);
								}
								else{
									LCD_Data(0);
								}
							}
			}
	}
}

void draw_figur(uint8_t fig, uint8_t page, uint8_t pos){
	uint8_t muster[8];

	muster[0]=255;
	muster[7]=255;
	switch (fig)
	{
	case 0: //Pawn
		muster[1]=0b01000000;
		muster[2]=0b01000000;
		muster[3]=0b01111110;
		muster[4]=0b01111110;
		muster[5]=0b01000000;
		muster[6]=0b01000000;
		break;

	case 1: //Night
		muster[1]=0b01000000;
		muster[2]=0b01011100;
		muster[3]=0b01010110;
		muster[4]=0b01110010;
		muster[5]=0b01010010;
		muster[6]=0b01111110;
		break;

	case 2: //Bishop
		muster[1]=0b00000000;
		muster[2]=0b01000000;
		muster[3]=0b01100100;
		muster[4]=0b01011010;
		muster[5]=0b01100100;
		muster[6]=0b01000000;
		break;

	case 3: //Rock
		muster[1]=0b00000000;
		muster[2]=0b01111110;
		muster[3]=0b01111000;
		muster[4]=0b01111110;
		muster[5]=0b01111000;
		muster[6]=0b01111110;
		break;

	case 4: //Queen
		muster[1]=0b00000000;
		muster[2]=0b01000000;
		muster[3]=0b01101110;
		muster[4]=0b01111000;
		muster[5]=0b01101110;
		muster[6]=0b01000000;
		break;

	case 5: //King
		muster[1]=0b00000000;
		muster[2]=0b01000100;
		muster[3]=0b01100100;
		muster[4]=0b01111110;
		muster[5]=0b01100100;
		muster[6]=0b01000100;
		break;
	default:
		muster[1]=255;
		muster[2]=255;
		muster[3]=255;
		muster[4]=255;
		muster[5]=255;
		muster[6]=255;
		break;
	}
	lcd_moveto_xy(page,pos+1);
	//Ausgabe
	for(uint8_t i =0;i<8;i++){
		if(page==0||page==2||page==4||page==6){
			if(pos==8||pos==24||pos==40||pos==56){
				muster[i]-=0b11111111;
				muster[i]&=0b01111110;
				muster[i]+=0b10000001;
			}
		}
		else{
			if(pos==0||pos==16||pos==32||pos==48){
				muster[i]-=0b11111111;
				muster[i]&=0b01111110;
				muster[i]+=0b10000001;
			}
		}
		LCD_Data(muster[i]);
	}

}

void schach(void){
	uint8_t spiel[8][8]=
		{
				{3,1,2,4,5,2,1,3},
				{0,0,0,0,0,0,0,0},
				{8,8,8,8,8,8,8,8},
				{8,8,8,8,8,8,8,8},
				{8,8,8,8,8,8,8,8},
				{8,8,8,8,8,8,8,8},
				{0,0,0,0,0,0,0,0},
				{3,1,2,4,5,2,1,3}
		};

	//draw_field();
	for(uint8_t i=0;i<8;i++){
		for(uint8_t j=0;j<8;j++){
			draw_figur(spiel[i][j],i,j*8);
		}
	}
}
