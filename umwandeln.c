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
int bmpUmwandeln(BITMAPINFOHEADER bi, char *pPixel, RGBQUAD *pPalette) {
	RGBTRIPLE newPalette = malloc(bi.biHeight * bi.biWidth * sizeof(RGBTRIPLE));
	for (int i = 0; i < bi.biHeight; i++) {
		for (int j = 0; j < bi.biWidth; j++) {
			newPalette[i][j].rgbBlue = pPalette[pPixel[i][j]].rgbBlue;
			newPalette[i][j].rgbGreen = pPalette[pPixel[i][j]].rgbGreen;
			newPalette[i][j].rgbRed = pPalette[pPixel[i][j]].rgbRed;
		}
	}

	return OK;
}
