/*
 * input.c
 *
 *  Created on: 04.11.2016
 *      Author: Eric
 */
#include <stdio.h>
#include "bitmap.h"
#include "myTypes.h"
#include "myError.h"
#include "einlesen.h"

int readFile(char* filename) {
	FILE *filep = fopen(filename, "r");
	if (filep == NULL) {
		return FILE_NOT_FOUND;
	}

	//TODO
	//Initialisierung eines Structs
	BITMAPFILEHEADER data = {
		.bfType = 1,
		.bfSize = 2,
		.bfReserved1 = 3,
		.bfReserved2 = 4,
		.bfOffBits =  5,
	};

	//Wenn End of File erreicht, schließe Datei
	if (feof(filep)) {
		fclose(filep);
	}
	return OK;
}
