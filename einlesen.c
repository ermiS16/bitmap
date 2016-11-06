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

/**
 * Liest den FileHeader der Bitmap-Datei ein
 */
BITMAPFILEHEADER readBitmapFileHeader(FILE *filep) {
	BITMAPFILEHEADER out;
	memset(&out, 0, sizeof(BITMAPFILEHEADER));

	fread(&out.bfType, sizeof(out.bfType), 1, filep);
	fread(&out.bfSize, sizeof(out.bfSize), 1, filep);
	fread(&out.bfReserved1, sizeof(out.bfReserved1), 1, filep);
	fread(&out.bfReserved2, sizeof(out.bfReserved2), 1, filep);
	fread(&out.bfOffBits, sizeof(out.bfOffBits), 1, filep);

	return out;
}

/**
 * Liest den Info-Header der Bitmap-Datei ein
 */
BITMAPINFOHEADER readBitmapInfoHeader(FILE *filep) {
	BITMAPINFOHEADER out;
	memset(&out, 0, sizeof(BITMAPINFOHEADER));

	fread(&out.biSize, sizeof(out.biSize), 1, filep);
	fread(&out.biWidth, sizeof(out.biWidth), 1, filep);
	fread(&out.biHeight, sizeof(out.biHeight), 1, filep);
	fread(&out.biPlanes, sizeof(out.biPlanes), 1, filep);
	fread(&out.biBitCount, sizeof(out.biBitCount), 1, filep);
	fread(&out.biCompression, sizeof(out.biCompression), 1, filep);
	fread(&out.biSizeImage, sizeof(out.biSizeImage), 1, filep);
	fread(&out.biXPelsPerMeter, sizeof(out.biXPelsPerMeter), 1, filep);
	fread(&out.biYPelsPerMeter, sizeof(out.biYPelsPerMeter), 1, filep);
	fread(&out.biClrUsed, sizeof(out.biClrUsed), 1, filep);
	fread(&out.biClrImportant, sizeof(out.biClrImportant), 1, filep);

	return out;
}

int readFile(char* filename, BITMAPFILEHEADER *pbf, BITMAPINFOHEADER *pbi, char *pPixel, RGBQUAD *pPalette) {
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	RGBQUAD paletteEntry;
	FILE *filep;
	char *vlaPixel;
	RGBQUAD *vlaPalette;

	int pixelCounter = 0;

	filep = fopen(filename, "r");

	if (filep == NULL) {
		return FILE_NOT_FOUND;
	}

	bf = readBitmapFileHeader(filep);
	bi = readBitmapInfoHeader(filep);

	//Speicher fuer die Farb-Palette reservieren
	vlaPalette = malloc(256 * sizeof(RGBQUAD));
	if (vlaPalette == NULL) {
		printf("Malloc failed!");
		fclose(filep);
		return MALLOC_FAIL;
	}

	//Eintraege der Farb-Palette auf dem Heap ablegen
	if (bi.biBitCount == 8) {
		for (int i = 0; i < 256; i++) {
			fread(&paletteEntry.rgbBlue, sizeof(paletteEntry.rgbBlue), 1,
					filep);
			fread(&paletteEntry.rgbGreen, sizeof(paletteEntry.rgbGreen), 1,
					filep);
			fread(&paletteEntry.rgbRed, sizeof(paletteEntry.rgbRed), 1, filep);
			fread(&paletteEntry.rgbReserved, sizeof(paletteEntry.rgbReserved),
					1, filep);
			vlaPalette[i] = paletteEntry;
		}
	}

	if (bi.biCompression == 1) {
		//RLE8-Kodierung
	}

	//Speicher für die Pixel auf dem Heap reservieren
	pixelCounter = bi.biWidth * bi.biHeight;
	vlaPixel = malloc(pixelCounter * sizeof(CHAR));
	if (vlaPixel == NULL) {
		printf("Malloc failed!");
		fclose(filep);
		free(vlaPalette);
		return MALLOC_FAIL;
	}

	//Pixel auf dem Heap ablegen
	for(int i = 0; i < pixelCounter; i++) {
		fread(vlaPixel[i], sizeof(char), 1, filep);
		printf("%d", vlaPixel[i]);
	}

	pbf = bf;
	pbi = bi;
	pPixel = vlaPixel;
	pPalette = vlaPalette;
	return OK;
}
