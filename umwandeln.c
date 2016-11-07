/*
 * umwandeln.c
 *
 *  Created on: 06.11.2016
 *      Author: andre
 */
#include <stdio.h>
#include "myError.h"
#include "myTypes.h"

/**
 * Wandelt die Informationen der alten Pixel mit Hilfe der Farbpalette um.
 */
int bmpUmwandeln(BITMAPINFOHEADER bi, CHAR *pPixel, RGBQUAD *pPalette) {
	RGBTRIPLE *newPalette;
	newPalette = malloc(bi.biHeight * bi.biWidth * sizeof(RGBTRIPLE));
	for (int i = 0; i < bi.biHeight * bi.biHeight; i++) {
			newPalette[i].rgbBlue = pPalette[pPixel[i]].rgbBlue;
			newPalette[i].rgbGreen = pPalette[pPixel[i]].rgbGreen;
			newPalette[i].rgbRed = pPalette[pPixel[i]].rgbRed;
	}
	free(pPixel);
	pPixel = newPalette;
	return OK;
}
