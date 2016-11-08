/*
 * input.c
 *
 *  Created on: 04.11.2016
 *      Author: Eric
 */
#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"
#include "myTypes.h"
#include "myError.h"
#include "einlesen.h"
#include "umwandeln.h"
#include "schreiben.h"

int readFile(char* filename, BITMAPFILEHEADER *pbf, BITMAPINFOHEADER *pbi, char *pPixel, RGBQUAD *pPalette) {
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	RGBQUAD paletteEntry;
	FILE *filep;
	RGBQUAD *vlaPalette;
	RGBQUAD *vlaPixel = NULL;
	int usedColors = 0;
	long counter = 0;

	filep = fopen(filename, "r");

	if (filep == NULL) {
		return FILE_NOT_FOUND;
	}

	fread(&bf, sizeof(bf), 1, filep);
	fread(&bi, sizeof(bi), 1, filep);

//	printf("FILEHEADER\n");
//	printf("%d\n", bf.bfType);
//	printf("%d\n", bf.bfSize);
//	printf("%d\n", bf.bfReserved1);
//	printf("%d\n", bf.bfReserved2);
//	printf("%d\n", bf.bfOffBits);
//
//	printf("INFOHEADER\n");
//	printf("%d\n", bi.biSize);
//	printf("%d\n", bi.biWidth);
//	printf("%d\n", bi.biHeight);
//	printf("%d\n", bi.biPlanes);
//	printf("%d\n", bi.biBitCount);
//	printf("%d\n", bi.biCompression);
//	printf("%d\n", bi.biSizeImage);
//	printf("%d\n", bi.biXPelsPerMeter);
//	printf("%d\n", bi.biYPelsPerMeter);
//	printf("%d\n", bi.biClrUsed);
//	printf("%d\n", bi.biClrImportant);


	if (bi.biHeight < 0) {
		bi.biHeight *= -1;
	}

	if (bi.biClrUsed == 0) {
		usedColors = 256;
	} else {
		usedColors = bi.biClrUsed;
	}

	//Speicher fuer die Farb-Palette reservieren
	vlaPalette = malloc(usedColors * sizeof(RGBQUAD));
	if (vlaPalette == NULL) {
		printf("Malloc failed!");
		fclose(filep);
		return MALLOC_FAIL;
	}
	//printf("FARBPALETTE\n");
	//Eintraege der Farb-Palette auf dem Heap ablegen
	for (int i = 0; i < usedColors; i++) {
		fread(&paletteEntry, sizeof(paletteEntry), 1, filep);
		vlaPalette[i] = paletteEntry;
	}

	//Speicher für die Pixel auf dem Heap reservieren
	vlaPixel = malloc(bi.biWidth * bi.biHeight * sizeof(BYTE));

	if (vlaPixel == NULL) {
		printf("Malloc failed!");
		fclose(filep);
		free(vlaPalette);
		return MALLOC_FAIL;
	}

	fseek(filep, bf.bfOffBits, SEEK_SET);
//	printf("Pixel\n");
//	printf("Height: %d Width: %d\n", bi.biHeight,bi.biWidth);
//	Pixel auf dem Heap ablegen
	for(int i = 0; i < (bi.biWidth * bi.biHeight); i++) {
		if(feof(filep)!=0){
			printf("EOF ERREICHT!");
			break;
		} else {
			counter++;
			fread(&vlaPixel[i], sizeof(BYTE), 1, filep);
			printf("i: %d\nRot: %d Gruen: %d Blau: %d\n", i, vlaPixel[i].rgbRed, vlaPixel[i].rgbGreen, vlaPixel[i].rgbBlue);
		}
	}
	printf("COUNTER: %ld\n", counter);
	printf("Pixel fertig");

	if (bi.biCompression == 1) {
		//RLE8-Kodierung

	}
	printf("Umwandeln");
	bmpUmwandeln(bi, vlaPixel, vlaPalette, counter);
	printf("Umwandeln fertig");

//TODO Header ändern

	printf("Schreiben");
	writeFile(bf, bi, vlaPixel, counter);
	printf("Schreiben fertig");

	if (feof(filep)) {
		printf("Dateiende entdeckt");
		fclose(filep);
	} else {
		printf("Dateiende nicht entdeckt!");
		fclose(filep);
	}

	//pPixel = vlaPixel;
	pPalette = vlaPalette;
	return OK;
}
