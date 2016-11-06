/*
 * input.h
 *
 *  Created on: 04.11.2016
 *      Author: Eric
 */

#ifndef EINLESEN_H_
#define EINLESEN_H_

#include "myTypes.h"

BITMAPFILEHEADER readBitmapFileHeader (FILE *filep);
BITMAPINFOHEADER readBitmapInfoHeader (FILE *filep);

int readFile(char* filename);

#endif /* EINLESEN_H_ */
