/*
 * umwandeln.c
 *
 *  Created on: 06.11.2016
 *      Author: andre
 */
#include <stdio.h>
#include <stdlib.h>
#include "myError.h"
#include "myTypes.h"

/**
 * Wandelt die Informationen der alten Pixel mit Hilfe der Farbpalette um.
 */
int bmpUmwandeln(BITMAPINFOHEADER bi, RGBQUAD *pPixel, RGBQUAD *pPalette, long counter) {
	RGBTRIPLE *newPalette;
	newPalette = malloc(bi.biHeight * bi.biWidth * sizeof(RGBTRIPLE));
	for (int i = 0; i < counter; i++) {
		/*
			newPalette[i].rgbtBlue = pPalette[pPixel[i]].rgbBlue;
			newPalette[i].rgbtGreen = pPalette[pPixel[i]].rgbGreen;
			newPalette[i].rgbtRed = pPalette[pPixel[i]].rgbRed;
			*/
	}
	//free(pPixel);
	//pPixel = newPalette;
	return OK;
}
