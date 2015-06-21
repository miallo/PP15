/*
 * header.h
 *
 *  Created on: 12.04.2015
 *      Author: kevin
 */

#ifndef HEADER_H_
#define HEADER_H_

//Definitionen
#define true 1
#define false 0
#define charsize 6
#define charhighte 7
#define cs sizeof(char)
#define PWMFREQUENZ 500
#define LEDFREQUENZ 20
#define ADCMAX 4095.0
#define VOLT 3.3
#define widoffset 20.6
#define R0 1000.0
#define R1 19120.0
#define A 3.9083E-3
#define B -5.775E-7
#define SPANNUNG(ADCWERT) (ADCWERT/ADCMAX*VOLT)
#define WiDERST(span) (R1*span/(3.3-span))
//#define TEMPERATUR(Spannung) (R0*(1+A*WiDERST(Spannung/10.0)+B*WiDERST(Spannung/10.0)*WiDERST(Spannung/10.0)))
#define DRUCK(ADCwert,Grundwert) (SPANNUNG(ADCwert)*Grundwert)	//Druck in HPa, nur, wenn der Druck auf genau 1000HPa beeicht ist, ansonsten muss kroigiert werden dazu ist die Eichung da

#define echoconst 250	//Konstante fuer die anzahl der noetigen Aufzeichnungspunkte bei der Echolot Messung
#define echoth 1220		//ADC trigger offset, damit erst ab diesem Wert die Messung ausgeloest wird
#define echozeit 5.0E-6	//zeit, die der Sender braucht um das signal zu senden
#define schallgeschww 1484	//Schallgeschwingiskeit in Wasser
#define aufnahmefrequenz 333E-5	//1/Frequenz (in us) mit der der PWM Interrupt lauft um die Zeit zu berechnen, genaue Zeit bitte genau Ausmessen

#include <XMC4500.h>		//SFR declarations of the selected device
#include <DAVE3.h>			//Declarations from DAVE3 Code Generation (includes SFR declaration)

#include "SPI.h"
#include "ASCI.h"
#include "Schach.h"
#include <stdlib.h>
#include <sys/unistd.h>
#include <string.h>
#include "taster.h"
#include "seiten.h"
#include "SDCARD.h"



#endif /* HEADER_H_ */
