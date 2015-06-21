/*
 * taster.c
 *
 *  Created on: 11.04.2015
 *      Author: kevin
 */

#include "taster.h"

uint8_t taster(IO004_HandleType Handle){
	if(!IO004_ReadPin(Handle)){
		for(uint16_t i=0;i<2000;i++){
			uLCDsleep(1000);
		}
		if(IO004_ReadPin(Handle)){
			for(uint16_t i=0;i<1000;i++){
				uLCDsleep(1000);
			}
			return 1;
		}
	}
	return 0;
}

void init(void){
	DAVE_Init();			// Initialization of DAVE Apps
	LCD_Init();
	ADC001_GenerateLoadEvent(&ADC001_Handle0);
	ADC002_InitializeQueue(&ADC002_Handle0);

	//Grundeinstellung Zeit
	msg_dat[2]='.';
	msg_dat[5]='.';
	msg_uhr[2]=':';
	msg_uhr[5]=':';

}

void uhreinst(uint8_t Stunden, uint8_t Minuten, uint8_t Tage, uint8_t Monat, uint8_t Jahr){
	RTC001_Disable();
	RTC001_TimeHandle SetTime;
	uint8_t posit=0;
	char disp[20];
	_Bool aenderung=true;
	uint8_t stunden=Stunden;
	uint8_t minuten=Minuten;
	uint8_t tag=Tage;
	uint8_t monat=Monat;
	uint16_t jahr=Jahr+2000;

	//Grundanzeige
	lcd_moveto_xy(0,0);
	strcpy(disp,"Uhreinstellungen");
	for(uint8_t i=0;i<(sizeof(disp)/cs);i++){
		draw_ASCI(disp[i]);
	}
	memset(disp,'\0',sizeof(disp));

	lcd_moveto_xy(1,0);
	strcpy(disp,"----------------");
	for(uint8_t i=0;i<(sizeof(disp)/cs);i++){
		draw_ASCI(disp[i]);
	}
	memset(disp,'\0',sizeof(disp));

	//Ausgabe der Zeit, welche einzustellen ist
	disp[2]=':';
	disp[5]=':';
	disp[6]='0';
	disp[7]='0';
	disp[8]=' ';
	disp[11]='.';
	disp[14]='.';
	//anzeiger welche die aktuelle aenderung zu beginn der einstellugen
	//Stunden
	lcd_moveto_xy(4,0);
	draw_ASCI('>');
	//minuten
	lcd_moveto_xy(4,4*7+1);
	draw_ASCI('>');
	//Tage
	lcd_moveto_xy(4,9*7+1);
	draw_ASCI('>');
	//Monate
	lcd_moveto_xy(4,12*7+1);
	draw_ASCI('>');
	//Jahr
	lcd_moveto_xy(4,15*7+1);
	draw_ASCI('²');
	//zeichen aktive
	while(posit<5){
		if(aenderung){
			lcd_moveto_xy(3,0);
			disp[0]='0'+stunden/10;
			disp[1]='0'+stunden%10;
			disp[3]='0'+minuten/10;
			disp[4]='0'+minuten%10;
			disp[9]='0'+tag/10;
			disp[10]='0'+tag%10;
			disp[12]='0'+monat/10;
			disp[13]='0'+monat%10;
			disp[15]='0'+(jahr-2000)/10;
			disp[16]='0'+(jahr-2000)%10;
			for(uint8_t i=0;i<(sizeof(disp)/cs);i++){
				draw_ASCI(disp[i]);
			}
			//memset(ausg,'\0',sizeof(ausg));
			//ruecksetzten
			aenderung=false;
		}
		if(taster(IO004_Handle1)){
			posit++;
			//anzeiger welche die aktuelle aenderung
			//Stunden
			lcd_moveto_xy(4,0);
			draw_ASCI('>');
			//minuten
			lcd_moveto_xy(4,4*7+1);
			draw_ASCI('>');
			//Tage
			lcd_moveto_xy(4,9*7+1);
			draw_ASCI('>');
			//Monate
			lcd_moveto_xy(4,12*7+1);
			draw_ASCI('>');
			//Jahr
			lcd_moveto_xy(4,15*7+1);
			draw_ASCI('>');
			//zeichen aktive
			switch (posit)
			{
			case 0:
				lcd_moveto_xy(4,15*7+1);
				break;
			case 1:
				lcd_moveto_xy(4,12*7+1);
				break;
			case 2:
				lcd_moveto_xy(4,9*7+1);
				break;
			case 3:
				lcd_moveto_xy(4,0);
				break;
			case 4:
				lcd_moveto_xy(4,4*7+1);
				break;
			}
			draw_ASCI('²');
		}
		if(taster(IO004_Handle2)){
			switch (posit)
			{
			case 0:
				jahr++;
				if(jahr>=2031){jahr=2015;}
				break;
			case 1:
				monat++;
				if(monat>=13){monat=1;}
				break;
			case 2:
				tag++;
				if(monat==1||monat==3||monat==5||monat==7||monat==8||monat==10||monat==12){
					if(tag>=32){tag=1;}
				}
				else if(monat==2){
					if(jahr%4==0){
						if(tag>=30){tag=1;}
					}
					else{
						if(tag>=29){tag=1;}
					}
				}
				else{
					if(tag>=31){tag=1;}
				}
				break;
			case 3:
				stunden++;
				if(stunden>=24){stunden=0;}
				break;
			case 4:
				minuten++;
				if(minuten>=60){minuten=0;}
				break;

			}
			aenderung=true;
		}


	}

	//Set Time
	SetTime.Year=jahr;
	SetTime.Month=monat;
	SetTime.Days=tag;
	SetTime.Hours=stunden;
	SetTime.Min=minuten;
	SetTime.Sec=0;
	RTC001_Clock_SetTime(&SetTime);
	RTC001_Enable();

}
