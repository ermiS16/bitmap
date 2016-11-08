/*
 * schreiben.c
 *
 *  Created on: 06.11.2016
 *      Author: andre
 */

#include <stdio.h>
#include "myError.h"
#include "myTypes.h"
#include "schreiben.h"

int writeFile(BITMAPFILEHEADER bf, BITMAPINFOHEADER bi, BYTE *vlaPixel, long counter) {
	FILE *new;
	int pixelCounter = 0;


	new = fopen("testBilder/newFile.bmp", "w+");

	fwrite(&bf.bfType, sizeof(bf.bfType), 1, new);
	fwrite(&bf.bfSize, sizeof(bf.bfSize), 1, new);
	fwrite(&bf.bfReserved1, sizeof(bf.bfReserved1), 1, new);
	fwrite(&bf.bfReserved2, sizeof(bf.bfReserved2), 1, new);
	fwrite(&bf.bfOffBits, sizeof(bf.bfOffBits), 1, new);

	fwrite(&bi.biSize, sizeof(bi.biSize), 1, new);
	fwrite(&bi.biWidth, sizeof(bi.biWidth), 1, new);
	fwrite(&bi.biHeight, sizeof(bi.biHeight), 1, new);
	fwrite(&bi.biPlanes, sizeof(bi.biPlanes), 1, new);
	fwrite(&bi.biBitCount, sizeof(bi.biBitCount), 1, new);
	fwrite(&bi.biCompression, sizeof(bi.biCompression), 1, new);
	fwrite(&bi.biSizeImage, sizeof(bi.biSizeImage), 1, new);
	fwrite(&bi.biXPelsPerMeter, sizeof(bi.biXPelsPerMeter), 1, new);
	fwrite(&bi.biYPelsPerMeter, sizeof(bi.biYPelsPerMeter), 1, new);
	fwrite(&bi.biClrUsed, sizeof(bi.biClrUsed), 1, new);
	fwrite(&bi.biClrImportant, sizeof(bi.biClrImportant), 1, new);

	pixelCounter = bi.biWidth * bi.biHeight;
	for (int i = 0; i < counter; i++) {
		fwrite(vlaPixel, sizeof(int), 1, new);
	}

	printf("Schreiben fertig");
	return OK;
}

