/*
 * seiten.c
 *
 *  Created on: 12.04.2015
 *      Author: kevin
 */

#include "seiten.h"

void willkommen(void){
	char hallo[20]="Wilkommen\0";
	lcd_moveto_xy(1,3*6+1);
	for(uint8_t i=0;i<(sizeof(hallo)/cs);i++){
		draw_ASCI(hallo[i]);
	}
	lcd_moveto_xy(3,3*6+1);
	memset(hallo,'\0',sizeof(hallo));
	strcpy(hallo,"Datenlogger\0");
	for(uint8_t i=0;i<(sizeof(hallo)/cs);i++){
		draw_ASCI(hallo[i]);
	}
	lcd_moveto_xy(4,7*6+1);
	memset(hallo,'\0',sizeof(hallo));
	strcpy(hallo,"V 2.3");
	for(uint8_t i=0;i<(sizeof(hallo)/cs);i++){
		draw_ASCI(hallo[i]);
	}
	msleep(2000);
}

void hauptmenue(void){
	char ausg[10];
	lcd_moveto_xy(0,3*6+1);
	strcpy(ausg,"Hauptmenue");
	for(uint8_t i=0;i<(sizeof(ausg)/cs);i++){
		draw_ASCI(ausg[i]);
	}
	memset(ausg,'\0',sizeof(ausg));

	lcd_moveto_xy(1,3*6+1);
	strcpy(ausg,"----------");
	for(uint8_t i=0;i<(sizeof(ausg)/cs);i++){
		draw_ASCI(ausg[i]);
	}
	memset(ausg,'\0',sizeof(ausg));

	lcd_moveto_xy(2,0);
	strcpy(ausg,"²Logger");
	for(uint8_t i=0;i<(sizeof(ausg)/cs);i++){
		draw_ASCI(ausg[i]);
	}
	memset(ausg,'\0',sizeof(ausg));

	lcd_moveto_xy(2,65);
	strcpy(ausg,">Einst");
	for(uint8_t i=0;i<(sizeof(ausg)/cs);i++){
		draw_ASCI(ausg[i]);
	}
	memset(ausg,'\0',sizeof(ausg));

	lcd_moveto_xy(4,0);
	strcpy(ausg,">Funktio");
	for(uint8_t i=0;i<(sizeof(ausg)/cs);i++){
		draw_ASCI(ausg[i]);
	}
	memset(ausg,'\0',sizeof(ausg));

	lcd_moveto_xy(4,65);
	strcpy(ausg,">Speich");
	for(uint8_t i=0;i<(sizeof(ausg)/cs);i++){
		draw_ASCI(ausg[i]);
	}
	memset(ausg,'\0',sizeof(ausg));
}

void zeiger(uint8_t posit, uint8_t zeigpos[2][4]){
//	char ausg[10];
	uint8_t alt=0;
	switch (posit)
	{
	case 1:
		lcd_moveto_xy(zeigpos[0][posit-1],zeigpos[1][posit-1]);
		draw_ASCI('²');
		alt=posit-2;
		if(alt==255){alt=3;}
		lcd_moveto_xy(zeigpos[0][alt],zeigpos[1][alt]);
		draw_ASCI('>');
		break;
	case 2:
		lcd_moveto_xy(zeigpos[0][posit-1],zeigpos[1][posit-1]);
		draw_ASCI('²');
		alt=posit-2;
		lcd_moveto_xy(zeigpos[0][alt],zeigpos[1][alt]);
		draw_ASCI('>');
		break;
	case 3:
		lcd_moveto_xy(zeigpos[0][posit-1],zeigpos[1][posit-1]);
		draw_ASCI('²');
		alt=posit-2;
		lcd_moveto_xy(zeigpos[0][alt],zeigpos[1][alt]);
		draw_ASCI('>');
		break;
	case 4:
		lcd_moveto_xy(zeigpos[0][posit-1],zeigpos[1][posit-1]);
		alt=posit-2;
		draw_ASCI('²');
		lcd_moveto_xy(zeigpos[0][alt],zeigpos[1][alt]);
		draw_ASCI('>');
		break;
	}
}

void logger(_Bool Messung){
	char ausg[10];
	lcd_moveto_xy(0,3*6+1);
	strcpy(ausg,"Logger");
	for(uint8_t i=0;i<(sizeof(ausg)/cs);i++){
		draw_ASCI(ausg[i]);
	}
	memset(ausg,'\0',sizeof(ausg));

	lcd_moveto_xy(1,3*6+1);
	strcpy(ausg,"------");
	for(uint8_t i=0;i<(sizeof(ausg)/cs);i++){
		draw_ASCI(ausg[i]);
	}
	memset(ausg,'\0',sizeof(ausg));

	lcd_moveto_xy(2,0);
	draw_ASCI('²');
	draw_ASCI(' ');
	if(Messung){
		strcpy(ausg,"stop ");
	}
	else {
		strcpy(ausg,"start");
	}

	for(uint8_t i=0;i<(sizeof(ausg)/cs);i++){
		draw_ASCI(ausg[i]);
	}
	memset(ausg,'\0',sizeof(ausg));

	lcd_moveto_xy(2,65);
	draw_ASCI('>');
	draw_ASCI(' ');

	strcpy(ausg,"Echolot");
	for(uint8_t i=0;i<(sizeof(ausg)/cs);i++){
		draw_ASCI(ausg[i]);
	}
	memset(ausg,'\0',sizeof(ausg));
}

void einstellungen(uint16_t freq, uint16_t ledfreq, uint8_t intensit, uint32_t luft){
	char ausg[20];
	lcd_moveto_xy(0,0);
	draw_ASCI('²');
	draw_ASCI(' ');

	strcpy(ausg,"Zeit/datum");
	for(uint8_t i=0;i<(sizeof(ausg)/cs);i++){
		draw_ASCI(ausg[i]);
	}
	memset(ausg,'\0',sizeof(ausg));

	lcd_moveto_xy(1,0);
	draw_ASCI('>');
	draw_ASCI(' ');

	strcpy(ausg,"Messpunkte: ");
	for(uint8_t i=0;i<(sizeof(ausg)/cs);i++){
		draw_ASCI(ausg[i]);
	}

	ausg[0]='0'+freq/1000;
	ausg[1]='0'+freq%1000/100;
	ausg[2]='0'+freq%1000%100/10;
	ausg[3]='0'+freq%1000%100%10;
	lcd_moveto_xy(1,15*6);
	for(uint8_t i=0;i<4;i++){
		draw_ASCI(ausg[i]);
	}
	memset(ausg,'\0',sizeof(ausg));

	lcd_moveto_xy(2,0);
	draw_ASCI('>');
	draw_ASCI(' ');

	strcpy(ausg,"LED Zeit: ");
	for(uint8_t i=0;i<(sizeof(ausg)/cs);i++){
		draw_ASCI(ausg[i]);
	}
	ausg[0]='0'+ledfreq/100;
	ausg[1]='0'+ledfreq%100/10;
	ausg[2]='0'+ledfreq%100%10%10;
	lcd_moveto_xy(2,13*6);
	for(uint8_t i=0;i<3;i++){
		draw_ASCI(ausg[i]);
	}
	memset(ausg,'\0',sizeof(ausg));

	lcd_moveto_xy(3,0);
	draw_ASCI('>');
	draw_ASCI(' ');

	strcpy(ausg,"Druck: ");
	for(uint8_t i=0;i<(sizeof(ausg)/cs);i++){
		draw_ASCI(ausg[i]);
	}
	memset(ausg,'\0',sizeof(ausg));

	ausg[0]='0'+luft/1000;
	ausg[1]='0'+luft%1000/100;
	ausg[2]='0'+luft%1000%100/10;
	ausg[3]='0'+luft%1000%100%10;
	lcd_moveto_xy(3,10*7);
	for(uint8_t i=0;i<4;i++){
		draw_ASCI(ausg[i]);
	}

	lcd_moveto_xy(4,0);
	draw_ASCI('>');
	draw_ASCI(' ');

	strcpy(ausg,"Intensi: ");
	for(uint8_t i=0;i<(sizeof(ausg)/cs);i++){
		draw_ASCI(ausg[i]);
	}
	memset(ausg,'\0',sizeof(ausg));

	ausg[0]='0'+intensit;
	lcd_moveto_xy(4,12*7);
	draw_ASCI(ausg[0]);

	//GPS Zeit
	lcd_moveto_xy(5,0);
	draw_ASCI('>');
	draw_ASCI(' ');

	strcpy(ausg,"Zeit aus GPS");
	for(uint8_t i=0;i<(sizeof(ausg)/cs);i++){
		draw_ASCI(ausg[i]);
	}
	memset(ausg,'\0',sizeof(ausg));
}

void funktio(void){
	char ausg[10];
	lcd_moveto_xy(0,3*6+1);
	strcpy(ausg,"Funktio");
	for(uint8_t i=0;i<(sizeof(ausg)/cs);i++){
		draw_ASCI(ausg[i]);
	}
	memset(ausg,'\0',sizeof(ausg));

	lcd_moveto_xy(1,3*6+1);
	strcpy(ausg,"--------");
	for(uint8_t i=0;i<(sizeof(ausg)/cs);i++){
		draw_ASCI(ausg[i]);
	}
	memset(ausg,'\0',sizeof(ausg));

	lcd_moveto_xy(2,0);
	draw_ASCI('²');
	draw_ASCI(' ');

	strcpy(ausg,"Temp: ");
	for(uint8_t i=0;i<(sizeof(ausg)/cs);i++){
		draw_ASCI(ausg[i]);
	}
	memset(ausg,'\0',sizeof(ausg));

	lcd_moveto_xy(3,0);
	draw_ASCI('>');
	draw_ASCI(' ');

	strcpy(ausg,"Druck: ");
	for(uint8_t i=0;i<(sizeof(ausg)/cs);i++){
		draw_ASCI(ausg[i]);
	}
	memset(ausg,'\0',sizeof(ausg));

	lcd_moveto_xy(4,0);
	draw_ASCI('>');
	draw_ASCI(' ');

	strcpy(ausg,"Intesi: ");
	for(uint8_t i=0;i<(sizeof(ausg)/cs);i++){
		draw_ASCI(ausg[i]);
	}
	memset(ausg,'\0',sizeof(ausg));
	lcd_moveto_xy(5,0);
	draw_ASCI('>');
	draw_ASCI(' ');

	strcpy(ausg,"Tiefe: ");
	for(uint8_t i=0;i<(sizeof(ausg)/cs);i++){
		draw_ASCI(ausg[i]);
	}
	memset(ausg,'\0',sizeof(ausg));

}

void SDcard(void){
	lcd_moveto_xy(2,0);
	char aus[20];
	strcpy(aus,"Bitte SDCard einstecken");
	for(uint8_t i=0;i<(sizeof(aus)/cs);i++){
		draw_ASCI(aus[i]);
	}
}
