/*
 * input.h
 *
 *  Created on: 04.11.2016
 *      Author: Eric
 */

#ifndef EINLESEN_H_
#define EINLESEN_H_

#include "myTypes.h"

BITMAPFILEHEADER readBitmapFileHeader(FILE *filep);
BITMAPINFOHEADER readBitmapInfoHeader(FILE *filep);

int readFile(char* filename, BITMAPFILEHEADER *pbf, BITMAPINFOHEADER *pbi,
		char *pPixel, RGBQUAD *pPalette);

#endif /* EINLESEN_H_ */
