/*
 * Main.c
 *
 *  Created on: 20.04.2015
 *      Author: Lüdemann
 */

#include "header.h"

//Variablen
RTC001_TimeHandle current_time;

//menuefuehrung
uint8_t pos=0, pmax=4;
uint8_t zeigerpos[4]={0,65,0,65};
uint8_t zeigerposs[4]={2,2,4,4};
uint8_t folie=0;

//Messung
_Bool echo=false;
_Bool Messunglaeuft = false;
uint8_t einzelmessung=0;
char dateiname[20];
char ausgabe[10];
uint8_t Bytes;

//PWM einstelungen und millisekunden Timer
long tempfreierspeicher=32;
uint16_t weiterfreierspeicher=16;
uint16_t LEDfreq=10;
uint16_t msec[2]={0,0};
uint8_t blau=0;
uint8_t intensianzeige=0;
uint16_t frequenz=100;
unsigned long Sekundenmessung=0;

//Variablen fuer den ADC
ADC001_ResultHandleType Result;
uint16_t ADCTemperatur=0, ADCDruck=0, ADCEcho=0, ADCAbsorb=0;
uint16_t Echoergeb=0;

//Variablen zur Auswertung
float Temperatur=0;
float Druck=0;
float Intensitaet[3];
float Tiefe=0;
uint32_t Druckoffset=1001;
uint32_t Luftdruck=1024;

//Echolot
uint8_t counter=0;
unsigned int nanosec=0;
uint16_t schwingungen[echoconst];
_Bool aufnahmeecho=false;
_Bool ganzephase=false;
float zeit = 0;
float weg = 0;

//GPS
_Bool gpsfertig=false;
uint8_t gpsdata[80];
float latitude=0;
float longitude=0;
uint16_t genauigkeit=0;
//float geschwindigkeit[3];

void tempaus(void){
	char put[12]="Core-Temp:";
	uint32_t tempera=0;
	char temperacor[5];
	TMPS001_StartMeasurement();
	while(TMPS001_GetStatus() != TMPS001_READY){}
	tempera=TMPS001_ReadTemp();
	lcd_moveto_xy(6,0);
	for(uint8_t i=0;i<(sizeof(put)/cs);i++){
		draw_ASCI(put[i]);
	}
	temperacor[0]='0'+tempera/1000;
	temperacor[1]='0'+tempera%1000/100;
	temperacor[2]='0'+tempera%1000%100/10;
	temperacor[3]='0'+tempera%1000%100%10;
	for(uint8_t i=1; i<4;i++){
		draw_ASCI(temperacor[i]);
	}
	draw_ASCI('°');
	draw_ASCI('C');
}

#include <math.h>
float PTTemp(uint16_t ADCw){
	float spann = ((ADCw*3.3/ADCMAX)/(1.0+99.5/9.99));
	float wider = (R1*spann/(3.3-spann))-widoffset;
	float ergeb = (A-sqrt(A*A+4*B*(1-wider/R0)))/(2*B);
//	float ergeb = -A/(2.0*B);
//		ergeb -= sqrt((A*A)/(4.0*B*B)-(1.0/B)+(wider/(R0*B)));
//	float ergeb = -A/(2.0*B);
//	ergeb -= sqrt((A*A)/(4.0*B*B)-(1.0/B)+((R1*((ADCw*3.3/ADCMAX)/(1.0+99.5/9.99))/(3.3-((ADCw*3.3/ADCMAX)/(1.0+99.5/9.99))))/(R0*B)));
	return ergeb;
}

float intensi(uint16_t ADCw){
	return ((ADCw*3.3/ADCMAX)/(1.0+99.6/9.96));
}

float druckwert(uint16_t ADCw){
	float spann = (ADCw*3.3/ADCMAX);
	return (spann*Druckoffset);
}
//#include <arm_math.h>
#include "analoguhr.h"
_Bool schoneran = false;
uint8_t schoner=0;

int main(void)
{
//	status_t status=255;		// Declaration of return variable for DAVE3 APIs (toggle comment if required)
	init();
	//Variablen wichtig fuer das einbinden der SD
	FATFS myfsObject;

	RTC001_Disable();	//warten mit dem Einschalten
	TMPS001_Enable();	//einschalten des internen Temperatursensors


	//Hallo ausgabe
	willkommen();
	LCD_Clear();
	//Uhreinstellungen
	uhreinst(9,27,17,6,15);
	LCD_Clear();

	//mounten der SD Karte, diese sollte eingesteckt sein
	mount(0,&myfsObject);

	//Zeichnen des Hauptmenues
	hauptmenue();

	//Hauptschleife
	while(1)
	{
		//Abfrage ob der Positionstaster gedreuckt wurde
		if(taster(IO004_Handle1)){	//Pos
			if(!schoneran){
				uint8_t alt=0;
				pos++;
				if(pos>=pmax){
					pos=0;
				}
				//wechseln der Position des Zeigers
				lcd_moveto_xy(zeigerposs[pos],zeigerpos[pos]);
				draw_ASCI('²');
				alt=pos-1;
				if(alt==255){
					alt=pmax-1;
				}
				lcd_moveto_xy(zeigerposs[alt],zeigerpos[alt]);
				draw_ASCI('>');
			}
		}
		//Abfrage des OK Tasters zum bestetiegen der Eingabe
		if(taster(IO004_Handle2)){ //OK
			schoner=0;
			if(folie==0){
				//folie mit Hauptmenue
				if(pos==0){
					//Logger start pos
					zeigerposs[0]=2;
					zeigerposs[1]=2;
					zeigerposs[2]=3;
					zeigerposs[3]=3;
					zeigerpos[0]=0;
					zeigerpos[1]=65;
					zeigerpos[2]=0;
					zeigerpos[3]=65;
					LCD_Clear();
					logger(Messunglaeuft);
					pmax=2;
					pos=0;
					folie=1;
				}
				else if(pos==1){
					//einstellung pos
					if(!Messunglaeuft){
						zeigerposs[0]=0;
						zeigerposs[1]=1;
						zeigerposs[2]=2;
						zeigerposs[3]=3;
						zeigerposs[4]=4;
						zeigerposs[5]=5;
						zeigerpos[0]=0;
						zeigerpos[1]=0;
						zeigerpos[2]=0;
						zeigerpos[3]=0;
						zeigerpos[4]=0;
						zeigerpos[5]=0;
						LCD_Clear();
						einstellungen(frequenz,LEDfreq,intensianzeige,Luftdruck);
						folie=2;
						pos=0;
						pmax=6;
					}
				}
				else if(pos==2){
					//Funktio pos
					zeigerposs[0]=2;
					zeigerposs[1]=3;
					zeigerposs[2]=4;
					zeigerposs[3]=5;
					zeigerpos[0]=0;
					zeigerpos[1]=0;
					zeigerpos[2]=0;
					zeigerpos[3]=0;
					LCD_Clear();
					funktio();
					folie=3;
					pos=0;
					pmax=4;
				}
				else if(pos==3){
					//Speicher pos
				}
			}
			else if(folie==1){
				//folie mit dem Logger
				if(pos==0){
					//start der datenaufnahme
					//setzen der start variable _Bool start aufnahme
					//start der eigentlichen Aufnahem bei Sekunden interut der RTC um pwm und RTC Synchron zu haben
					if(!Messunglaeuft && !echo){
						memset(dateiname,'\0',sizeof(dateiname));
						sprintf(dateiname,"%02d%02d%02d%02d.dat",current_time.Month,current_time.Days,current_time.Hours,current_time.Min);
						fileopen(dateiname);
						fprintf(ptr,"#Zeit[s]\t\tTemperatur\t\tDruck\t\tAbsorbtion\tohne LED\tBlau\tIR\t\tLatitude\t\tLongitude\t\tMesspunkte: %u/s\tLEDZeit: %u/s\n", frequenz, LEDfreq);
						Messunglaeuft=true;
						Sekundenmessung=(current_time.Hours*60*60+current_time.Min*60+current_time.Sec)*1000;
						PWMSP001_Start(&PWMSP001_Handle0);
						lcd_moveto_xy(2,2*charsize+2);	//wechseln auf die Stopp funktion
						memset(ausgabe,'\0',sizeof(ausgabe));
						strcpy(ausgabe,"stop \0");
						for(uint8_t i=0;i<(sizeof(ausgabe)/cs);i++){
							if(ausgabe[i]!='\0'){
								draw_ASCI(ausgabe[i]);
							}
						}
					}
					else {
						fileclose(dateiname);
						Messunglaeuft=false;
						lcd_moveto_xy(0,18*charsize);
						draw_ASCI(' ');
						IO004_ResetPin(IO004_Handle6);
						blau=0;
						PWMSP001_Stop(&PWMSP001_Handle0);
						IO004_ResetPin(IO004_Handle4);
						IO004_ResetPin(IO004_Handle5);
						lcd_moveto_xy(2,2*charsize+2);	//rueckgang auf die Startfunktion
						memset(ausgabe,'\0',sizeof(ausgabe));
						strcpy(ausgabe,"start\0");
						for(uint8_t i=0;i<(sizeof(ausgabe)/cs);i++){
							if(ausgabe[i]!='\0'){
								draw_ASCI(ausgabe[i]);
							}
						}

					}
				}
				else if(pos==1){
					/*
					if (!echo && !Messunglaeuft){
						//Dauermessung mit dem Echolot
						memset(dateiname,'\0',sizeof(dateiname));
						sprintf(dateiname,"%02d%02d%02d_S.dat",current_time.Month,current_time.Hours,current_time.Min);
						fileopen(dateiname);
						fprintf(ptr,"#Zeit\tWeg\t\tFrequenz: 39700Hz\tAufnahmefrequenz: 0.5MHz\n");
						echo=true;
						PWMSP001_Start(&PWMSP001_Handle2);
						lcd_moveto_xy(0,18*charsize);
						draw_ASCI('°');
						IO004_SetPin(IO004_Handle7);
						counter=0;
						ganzephase=false;
					}
					else if(echo){
						IO004_ResetPin(IO004_Handle7);
						fileclose(dateiname);
						echo=false;
						PWMSP001_Stop(&PWMSP001_Handle1);
						lcd_moveto_xy(0,18*charsize);
						draw_ASCI(' ');
						counter=0;
					}
					*/
				}
			}
			else if(folie==2){
				//folie mit den Einstellungen
				if(pos==0){
					//einstellung der Zeit
					LCD_Clear();
					uhreinst(current_time.Hours,current_time.Min,current_time.Days,current_time.Month,current_time.Year-2000);
					LCD_Clear();
					einstellungen(frequenz,LEDfreq,intensianzeige,Luftdruck);
				}
				else if(pos==1){
					//Einstellung der Messpunkte
					frequenz= frequenz + 10;
					if(frequenz>PWMFREQUENZ){
						frequenz=10;
					}
					lcd_moveto_xy(1,15*charsize);
					ausgabe[0]='0'+(uint16_t)frequenz/1000;
					ausgabe[1]='0'+(uint16_t)frequenz%1000/100;
					ausgabe[2]='0'+(uint16_t)frequenz%1000%100/10;
					ausgabe[3]='0'+(uint16_t)frequenz%1000%100%10;
					for(uint8_t i=0;i<4;i++){
						draw_ASCI(ausgabe[i]);
					}
				}
				else if(pos==2){
					//einstellung der LED Zeit
					LEDfreq++;
					if(LEDfreq>LEDFREQUENZ){
						LEDfreq=1;
					}
					lcd_moveto_xy(2,13*charsize);
					ausgabe[0]='0'+LEDfreq/100;
					ausgabe[1]='0'+LEDfreq%100/10;
					ausgabe[2]='0'+LEDfreq%100%10%10;
					for(uint8_t i=0;i<3;i++){
						draw_ASCI(ausgabe[i]);
					}
				}
				else if(pos==3){
					//Druckoffset einstellen
					//Temporaer aus den EInstellungen genommen, da momentan fest geeicht und hatte bei Einstellen bis jetzt immer Probleme
					Luftdruck++;
					if(Luftdruck==1050){
						Luftdruck=950;
					}
					lcd_moveto_xy(3,11*charsize+4);
					ausgabe[0]='0'+Luftdruck/1000;
					ausgabe[1]='0'+Luftdruck%1000/100;
					ausgabe[2]='0'+Luftdruck%1000%100/10;
					ausgabe[3]='0'+Luftdruck%1000%100%10;
					for(uint8_t i=0;i<4;i++){
						draw_ASCI(ausgabe[i]);
					}
				}
				else if(pos==4){
					//intensitaetsanzeige einstellen
					intensianzeige++;
					if(intensianzeige==3){
						intensianzeige=0;
					}
					lcd_moveto_xy(4,14*charsize);
					ausgabe[0]='0'+intensianzeige;
						draw_ASCI(ausgabe[0]);
				}
				else if(pos==5){
					if(gpsdata[2]!=0){
						RTC001_Disable();
						RTC001_TimeHandle SetTime;
						SetTime.Year=2000+(gpsdata[1]-'0')*10+(gpsdata[2]-'0');
						SetTime.Month=(gpsdata[3]-'0')*10+(gpsdata[4]-'0');
						SetTime.Days=(gpsdata[5]-'0')*10+(gpsdata[6]-'0');
						SetTime.Hours=(gpsdata[7]-'0')*10+(gpsdata[8]-'0')+2;//+2 wegen UTC, kann aber auch anders berechnet werden, wenn gewollt
						SetTime.Min=(gpsdata[9]-'0')*10+(gpsdata[10]-'0');
						SetTime.Sec=(gpsdata[11]-'0')*10+(gpsdata[12]-'0');
						RTC001_Clock_SetTime(&SetTime);
						RTC001_Enable();
					}
				}
			}
			else if(folie==3){
				//Folie mit der Anzeige eines Sensors
				//jeder Sensor ist einzeln anteuerbar
				if(!Messunglaeuft){
					if(pos==0){
						//Messung Temperatur
						if(einzelmessung==0){
							einzelmessung=1;
							lcd_moveto_xy(0,18*charsize);
							draw_ASCI('°');
							memset(dateiname,'\0',sizeof(dateiname));
							sprintf(dateiname,"%02d%02d%02d_T.dat",current_time.Month,current_time.Hours,current_time.Min);
							fileopen(dateiname);
							fprintf(ptr,"#Zeit\t\tTemperatur\t\tLatitude\t\tLongitude\t\tMesspunkte: %u/s\tLEDZeit: %u/s\n", frequenz, LEDfreq);
							Sekundenmessung=(current_time.Hours*60*60+current_time.Min*60+current_time.Sec)*1000;
							PWMSP001_Start(&PWMSP001_Handle0);
						}
						else if(einzelmessung==1){
							einzelmessung=0;
							lcd_moveto_xy(0,18*charsize);
							draw_ASCI(' ');
							IO004_ResetPin(IO004_Handle6);
							fileclose(dateiname);
							PWMSP001_Stop(&PWMSP001_Handle0);
						}
					}
					else if(pos==1){
						//Messung Druck
						if(einzelmessung==0){
							einzelmessung=2;
							lcd_moveto_xy(0,18*charsize);
							draw_ASCI('°');
							memset(dateiname,'\0',sizeof(dateiname));
							sprintf(dateiname,"%02d%02d%02d_D.dat",current_time.Month,current_time.Hours,current_time.Min);
							fileopen(dateiname);
							fprintf(ptr,"#Zeit\t\tDruck\t\tLatitude\t\tLongitude\t\tMesspunkte: %u/s\tLEDZeit: %u/s\n", frequenz, LEDfreq);
							Sekundenmessung=(current_time.Hours*60*60+current_time.Min*60+current_time.Sec)*1000;
							PWMSP001_Start(&PWMSP001_Handle0);
						}
						else if(einzelmessung==2){
							einzelmessung=0;
							lcd_moveto_xy(0,18*charsize);
							draw_ASCI(' ');
							IO004_ResetPin(IO004_Handle6);
							fileclose(dateiname);
							PWMSP001_Stop(&PWMSP001_Handle0);
						}
					}
					else if(pos==2){
						//Messung der Intensität
						if(einzelmessung==0){
							einzelmessung=3;
							lcd_moveto_xy(0,18*charsize);
							draw_ASCI('°');
							memset(dateiname,'\0',sizeof(dateiname));
							sprintf(dateiname,"%02d%02d%02d_I.dat",current_time.Month,current_time.Hours,current_time.Min);
							fileopen(dateiname);
							fprintf(ptr,"#Zeit\t\tIntensitaet\t\tLatitude\t\tLongitude\t\tMesspunkte: %u/s\tLEDZeit: %u/s\n", frequenz, LEDfreq);
							Sekundenmessung=(current_time.Hours*60*60+current_time.Min*60+current_time.Sec)*1000;
							PWMSP001_Start(&PWMSP001_Handle0);
						}
						else if(einzelmessung==3){
							einzelmessung=0;
							lcd_moveto_xy(0,18*charsize);
							draw_ASCI(' ');
							IO004_ResetPin(IO004_Handle6);
							fileclose(dateiname);
							IO004_ResetPin(IO004_Handle4);
							IO004_ResetPin(IO004_Handle5);
							blau=0;
							PWMSP001_Stop(&PWMSP001_Handle0);
						}
					}
					else if(pos==3){
						//Messung der Tiefe mit dem Echolot
						//hier nur die Messung der ganzen Phase, einfuehrung der Variable ganzephase
						/*
						if(einzelmessung==0){
							einzelmessung=4;
							lcd_moveto_xy(0,18*charsize);
							draw_ASCI('°');
							IO004_SetPin(IO004_Handle7);
							PWMSP001_Start(&PWMSP001_Handle2);
							ganzephase=true;
						}*/
/*						else if(einzelmessung==4){
							einzelmessung=0;
							lcd_moveto_xy(0,18*charsize);
							draw_ASCI(' ');
							fileclose(dateiname);
							PWMSP001_Stop(&PWMSP001_Handle0);
						}*/
					}
				}
			}

		}
		if(taster(IO004_Handle3)){ //Return
			//einbau einer Abfrage, ob gerade eine Speicherung laeuft
			if(folie!=0){
				LCD_Clear();
				hauptmenue();
				pmax=4;
				zeigerposs[0]=2;
				zeigerposs[1]=2;
				zeigerposs[2]=4;
				zeigerposs[3]=4;
				zeigerpos[0]=0;
				zeigerpos[1]=65;
				zeigerpos[2]=0;
				zeigerpos[3]=65;
				pos=0;
				folie=0;
				schoneran=false;
				schoner=0;
			}
		}

	}
	TMPS001_Disable(); //ausschalten des internen Temperatursensors
	return 0;
}

void secinterrupt(uint32_t CbArg){
//	IO004_TogglePin(IO004_Handle8);
	//sekundeninterupt der RTC mit ausgabe der neuen Zeit
	RTC001_Clock_GetTime(&current_time);

	//umwandeln der neuen Zeit und Datum
	msg_uhr[0]='0'+current_time.Hours/10;
	msg_uhr[1]='0'+current_time.Hours%10;
	msg_uhr[3]='0'+current_time.Min/10;
	msg_uhr[4]='0'+current_time.Min%10;
	msg_uhr[6]='0'+current_time.Sec/10;
	msg_uhr[7]='0'+current_time.Sec%10;

	msg_dat[0]='0'+current_time.Days/10;
	msg_dat[1]='0'+current_time.Days%10;
	msg_dat[3]='0'+current_time.Month/10;
	msg_dat[4]='0'+current_time.Month%10;
	msg_dat[6]='0'+(current_time.Year-2000)/10;
	msg_dat[7]='0'+(current_time.Year-2000)%10;

	//anzeige der Analoguhr

	if(!schoneran){
		//Anzeige der Zeit links unten
		lcd_moveto_xy(7,0);
		for(uint8_t i=0;i<8;i++)
		{
			draw_ASCI(msg_uhr[i]);
		}
		//Anzeige Datum rechts unten neben Zeit
		lcd_moveto_xy(7,10*charsize+1);
		for(uint8_t i=0;i<8;i++)
		{
			draw_ASCI(msg_dat[i]);
		}
		if(folie==0){
			tempaus();
		}
		if(Messunglaeuft){
			lcd_moveto_xy(0,18*charsize);
			draw_ASCI('°');
			if(folie==1){	//ausgabe der Daten
				lcd_moveto_xy(4,0);		//Temperatur in °C
				Bytes = sprintf(ausgabe,"%.02f°C",Temperatur);
				for(uint8_t i=0;i<Bytes;i++){
					draw_ASCI(ausgabe[i]);
				}
				lcd_moveto_xy(4,charsize*9);	//Druck ausgabe in HPa
				Bytes = sprintf(ausgabe,"%.02fHPa",Druck);
				for(uint8_t i=0;i<Bytes;i++){
					draw_ASCI(ausgabe[i]);
				}
				lcd_moveto_xy(6,0);		//Asuageb der Instensität in mV, da eine Umrechnung in sinvolle Einheiten
				Bytes = sprintf(ausgabe,"%.02fmV",Intensitaet[intensianzeige]*1000.0);
				for(uint8_t i=0;i<Bytes;i++){
					draw_ASCI(ausgabe[i]);
				}
				lcd_moveto_xy(6,charsize*9);	//Ausgabe der Tiefe noch in HPa, da noch keine Umrechnung in Meter
				Bytes = sprintf(ausgabe,"%.02fM",Tiefe);
				for(uint8_t i=0;i<Bytes;i++){
					draw_ASCI(ausgabe[i]);
				}
				//Ausgabe der Position

				if(gpsfertig){
					lcd_moveto_xy(3,0);	//Ausgabe von Latitude in Grad
					Bytes = sprintf(ausgabe,"%c: %.02f°",gpsdata[13],latitude);
					for(uint8_t i=0;i<Bytes;i++){
						draw_ASCI(ausgabe[i]);
					}

					lcd_moveto_xy(5,0);	//Ausgabe von Latitude in Grad
					Bytes = sprintf(ausgabe,"%c: %.02f°",gpsdata[21],longitude);
					for(uint8_t i=0;i<Bytes;i++){
						draw_ASCI(ausgabe[i]);
					}

					gpsfertig=false;
				}

			}
		}
		else if(einzelmessung!=0){
			lcd_moveto_xy(0,18*charsize);
			draw_ASCI('°');
			if(einzelmessung==1){
				lcd_moveto_xy(2,11*charsize);	//ausgabe der Temperatur
				Bytes = sprintf(ausgabe,"%.02f°C",Temperatur);
				for(uint8_t i=0;i<Bytes;i++){
					draw_ASCI(ausgabe[i]);
				}
			}
			else if(einzelmessung==2){
				lcd_moveto_xy(3,11*charsize);	//Druck ausgabe in HPa
				Bytes = sprintf(ausgabe,"%.02fHPa",Druck);
				for(uint8_t i=0;i<Bytes;i++){
					draw_ASCI(ausgabe[i]);
				}
			}
			else if(einzelmessung==3){
				lcd_moveto_xy(4,11*charsize);		//Ausgabe der Instensität
				Bytes = sprintf(ausgabe,"%.02fmV",Intensitaet[intensianzeige]*1000.0);
				for(uint8_t i=0;i<Bytes;i++){
					draw_ASCI(ausgabe[i]);
				}
			}
			else if(einzelmessung==4){
				lcd_moveto_xy(4,0);
				Bytes = sprintf(ausgabe,"Tiefe %.02f°C",weg);
			}
		}
		if(Messunglaeuft==false && einzelmessung==0 && folie==0 && echo==false){
			schoner++;
			if(schoner>=60){
				LCD_Clear();
				schoneran=true;
				folie=100;
			}
		}
	}
	else
	{
		analog(current_time.Hours,current_time.Min,current_time.Sec);
		//Anzeige der Zeit links unten
		lcd_moveto_xy(0,64);
		for(uint8_t i=0;i<8;i++)
		{
			draw_ASCI(msg_uhr[i]);
		}
		//Anzeige Datum rechts unten neben Zeit
		lcd_moveto_xy(7,64);
		for(uint8_t i=0;i<8;i++)
		{
			draw_ASCI(msg_dat[i]);
		}
	}
	//ruecksetzen der zeit im Software PWM zum sychronisieren
	msec[0]=0;
	msec[1]=0;

}

void speichern(void){

	ADC001_GetResult(&ADC001_Handle0,&Result);
	switch (Result.ChannelNo)
	{
		case 0:
			ADCTemperatur=Result.Result;
			break;
		case 2:
			ADCDruck=Result.Result;
			break;
		case 5:
			ADCAbsorb=Result.Result;
			break;
		default:
			break;
	}

	//anzahl der Messpunkte beachten.
	//der Adc wird jedes Mal ausgelesen, aber es wird nur mit der richtigen Frequenz das ergebnis in die Datei geschrieben
	msec[0]++;
	msec[1]++;

	if(msec[1]>=(PWMFREQUENZ/LEDfreq)){
		blau++;
		switch (blau)
		{
		case 1:
			IO004_TogglePin(IO004_Handle4);	//Blau ein
			break;
		case 2:
			IO004_TogglePin(IO004_Handle4);	//Blau aus
			break;
		case 3:
			IO004_TogglePin(IO004_Handle5);	//IR ein
			break;
		case 4:
			IO004_TogglePin(IO004_Handle5);	//IR aus
			blau=0;
			break;
		default:
			break;
		}

		msec[1]=0;
	}

	if(msec[0]>=(PWMFREQUENZ/frequenz)){
		Sekundenmessung+=PWMFREQUENZ/frequenz;
		IO004_TogglePin(IO004_Handle6);
		if(Messunglaeuft){
			switch (blau) {
				case 1:
					Intensitaet[2]=intensi(ADCAbsorb);
					break;
				case 3:
					Intensitaet[1]=intensi(ADCAbsorb);
					break;
				default:
					Intensitaet[0]=intensi(ADCAbsorb);
					break;
			}
			//schreiben der Logger daten
			Temperatur=PTTemp(ADCTemperatur);
			Druck=druckwert(ADCDruck);
			Tiefe=(Druck-Luftdruck)/100.0;
			fprintf(ptr,"%u\t%u\t%g\t%u\t%g\t%g\t%u\t%g\t%g\t%g\t%g\t%g\n",
												Sekundenmessung,
												ADCTemperatur,
												Temperatur,
												ADCDruck,
												Druck,
												Tiefe,
												ADCAbsorb,
												Intensitaet[0],		//momentan nur Spannung, da Spannung Proportional zur Intensitär Offset wird später betrachtett
												Intensitaet[1],
												Intensitaet[2],
												latitude,
												longitude);
		}
		else if(einzelmessung==1){
			//schreiben der Temperatur
			Temperatur=PTTemp(ADCTemperatur);
			fprintf(ptr,"%u\t%u\t%g\t%g\t%g\n",Sekundenmessung,ADCTemperatur,Temperatur,latitude,longitude);
		}
		else if(einzelmessung==2){
			//Schreiben des Drucks
			Druck=druckwert(ADCDruck);		//DRUCK(ADCDruck,Druckoffset);
			Tiefe=(Druck-Luftdruck)/100.0;		//dummy fuer die Tiefe, die noch nicht implementiert ist
			fprintf(ptr,"%u\t%u\t%g\t%g\t%g\t%g\n",Sekundenmessung,ADCDruck,Druck,Tiefe,latitude,longitude);
		}
		else if(einzelmessung==3){
			//Schreiben der Intensität
			fprintf(ptr,"%u\t%u\t%g\t%g\t%g\t%g\t%g\n",Sekundenmessung,ADCAbsorb,Intensitaet[0],Intensitaet[1],Intensitaet[2],latitude,longitude);
		}
		msec[0]=0;
	}
}

void Echovektor(void){
	nanosec++;		//nanosekundenzaehler
	ADCCH001_GetResult(&ADCCH001_Handle0,&Echoergeb);
	//ADC002 APP zum auslesen eines zweiten Echo Pins, dem 14.13 Pin.
	//mit der neuen Variable muss jetzt gerechnet werden
	//jetzt sollte es moeglich sein, mit groeßerer Freqeunz ausgelesen werden
	//zu beginn testen, ob die Ausgabe der Daten Stimmt, dann Pin verloeten
	/*
	do
	{
		ADC001_GetResult(&ADC001_Handle0,&Result);
	}while(Result.ChannelNo!=7);*/
/*
	if(Echoergeb>echoth && aufnahmeecho!=true){	//uberschreiten der Signalschwelle
		aufnahmeecho=true;
	}

	if(aufnahmeecho && counter<(echoconst-1) && ganzephase==true){	//abfrage was getan werden soll, bzw welche schreiben der Daten in den RAM
		schwingungen[counter]=Echoergeb;
		counter++;
	}

	else if (aufnahmeecho==true && ganzephase!=true){	//nur Messung der Zeit und nicht der ganze Phase
		//speichern der Tiefe
		zeit = (nanosec*0.000000001*2)+echozeit;
		weg = schallgeschww*zeit;
		fprintf(ptr,"%g\t%g\n",zeit, weg);
		fileclose(dateiname);
		PWMSP001_Stop(&PWMSP001_Handle1);
		nanosec=0;
		echo=false;
		lcd_moveto_xy(0,18*charsize);
		draw_ASCI(' ');
		IO004_ResetPin(IO004_Handle7);
		counter=0;
		aufnahmeecho=false;
	}

	if(counter>=(echoconst-1) && ganzephase==true){	//fuer ganze Messung zum beende der Messung
		PWMSP001_Stop(&PWMSP001_Handle1);
		memset(dateiname,'\0',sizeof(dateiname));
		sprintf(dateiname,"%02d%02d%02d_E.dat",current_time.Hours,current_time.Min,current_time.Sec);
		fileopen(dateiname);
		fprintf(ptr,"#Amplitude\tZeit\t\tSchwingungsfrequenz: 39700Hz\t\t Aufnahmefrequenz: 0.5MHz\n");
		for(uint8_t i=0;i<(echoconst-1);i++){
			fprintf(ptr,"%u\t%u\n",schwingungen[i],(nanosec-i*echoconst)*2);
		}
		fileclose(dateiname);
		nanosec=0;
		echo=false;
		lcd_moveto_xy(0,18*charsize);
		draw_ASCI(' ');
		IO004_ResetPin(IO004_Handle7);
		counter=0;
		einzelmessung=0;
		aufnahmeecho=false;
	}
	*/

	if(nanosec>=4000000){	//zum abfangen eines fehlende signales
		PWMSP001_Stop(&PWMSP001_Handle1);
		echo=false;
		lcd_moveto_xy(0,18*charsize);
		draw_ASCI(' ');
		IO004_ResetPin(IO004_Handle7);
		nanosec=0;
		counter=0;
		einzelmessung=0;
		aufnahmeecho=false;
	}
}

void count(void){		//der PWM ist immernoch auf 20hz eingestellt, umstellen auf 39700Hz fuer den Piezo
	counter++;
	if(counter>=20){
		PWMSP001_Stop(&PWMSP001_Handle2);
		PWMSP001_Start(&PWMSP001_Handle1);
		counter=0;
		aufnahmeecho=false;
	}
}

void GPS_KOORD(){
	static uint8_t gpscounter=0;
	UART001_ReadDataBytes(&UART001_Handle0,&gpsdata[gpscounter],1);
	if(gpsdata[gpscounter]=='@' && gpscounter!=0){
		gpscounter=0;
		gpsdata[gpscounter]='@';
	}
	gpscounter+=1;
	if(gpscounter==57){
		gpscounter=0;
		gpsfertig=true;
		if(gpsdata[14]!='_'){
			latitude=	(gpsdata[14]-'0')*10+(gpsdata[15]-'0')+((gpsdata[16]-'0')*10.0+(gpsdata[17]-'0')+(gpsdata[18]-'0')*0.1+(gpsdata[19]-'0')*0.01+(gpsdata[20]-'0')*0.001)/60.0;
			longitude=	(gpsdata[22]-'0')*100+(gpsdata[23]-'0')*10+(gpsdata[24]-'0')+((gpsdata[25]-'0')*10.0+(gpsdata[26]-'0')+(gpsdata[27]-'0')*0.1+(gpsdata[28]-'0')*0.01+(gpsdata[29]-'0')*0.001)/60.0;
			genauigkeit = (gpsdata[31]-'0')*100+(gpsdata[32]-'0')*10+(gpsdata[33]-'0');
		}
		else {
			latitude=0;
			longitude=0;
			genauigkeit=0;
		}
	}
}
