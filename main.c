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

int main() {
	int errno = 0;
	BITMAPFILEHEADER *bfh;
	BITMAPINFOHEADER *bih;
	char *pPixel = NULL;
	RGBQUAD *pPalette = NULL;

	//printf("%d\n", 0x01U);
	errno = readFile("/home/andre/workspace/GSP/bitmap/aufgabe3_bild1.bmp",
			bfh, bih, pPixel, pPalette);
	if (errno == FILE_NOT_FOUND) {
		printf(FILE_NOT_FOUND_TEXT);
		return -1;
	}

	if (errno != OK) {
		printf(MALLOC_FAIL_TEXT);
		return -1;
	}

	printf("Beendet");

	return errno;
}
