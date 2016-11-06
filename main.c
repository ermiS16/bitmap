/*
 * main.c
 *
 *  Created on: 19.10.2016
 *      Author: Eric
 */

#include <stdio.h>
#include "bitmap.h"
#include "myError.h"
#include "myTypes.h"
#include "main.h"


int main(){
	int errno = 0;
	BITMAPFILEHEADER bfh = NULL;
	BITMAPINFOHEADER bih = NULL;
	char *pPixel = NULL;
	RGBQUAD *pPalette = NULL;

	printf("%d\n",0x01U);
	errno = int readFile("Unbenannt.bmp", &bfh, &bih, pPixel, pPalette);
	if (errno == FILE_NOT_FOUND) {
		printf("Datei wurde nicht gefunden! :(");
		return -1;
	}
	printf("Datei wurde geöffnet! :)");
	return errno;
}
