/*
 * SDCARD.c
 *
 *  Created on: 28.04.2015
 *      Author: Lüdemann
 */


#include "SDCARD.h"

//oeffnen einer neuen Datei. Der Dateiname wird uebergeben
void fileopen(const char *file){
	ptr =  fopen(file, "a+");
	fseek(ptr,0,SEEK_SET);
}

//schließen einer Datei, dessen dateiname uebergeben wird
void fileclose(const char *file){
	fclose(ptr);
}

//beshreiben einer Datei mit nur einer zeile
//diese sollte Satzendzeichen und Zeilenendzeichen enthalten, sowie bereits Platzhalter wie tabs
void filewrite(const char *data, uint8_t anzahl){

	fwrite(data,sizeof(data),cs,ptr);

}
