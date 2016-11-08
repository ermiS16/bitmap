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
#include "einlesen.h"

int main() {
	int errNo = 0;
	BITMAPFILEHEADER *bfh = NULL;;
	BITMAPINFOHEADER *bih = NULL;
	char *pPixel = NULL;
	RGBQUAD *pPalette = NULL;

	//printf("%d\n", 0x01U);

	errNo = readFile("testBilder/littleBitmap2_8.bmp",
			bfh, bih, pPixel, pPalette);
	if (errNo == FILE_NOT_FOUND) {
		printf(FILE_NOT_FOUND_TEXT);
		return -1;
	}

	if (errNo != OK) {
		printf(MALLOC_FAIL_TEXT);
		return -1;
	}

	printf("Beendet");

	return errNo;
}
