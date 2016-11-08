/*
 * myTypes.h
 *
 * Benutzt nicht die Standart int-Types,
 * da sonst Fehler bei unterschiedlichen Systemen auftreten koennen
 *
 *  Created on: 05.11.2016
 *      Author: andre
 */

#ifndef BITMAP_MYTYPES_H_
#define BITMAP_MYTYPES_H_

#include <stdint.h>

#ifdef LINUX
typedef __int8_t CHAR;
typedef __int16_t SHORT;
typedef __int32_t LONG;
typedef __uint32_t DWORD;
typedef __int32_t BOOL;
typedef __uint8_t BYTE;
typedef __uint16_t WORD;

#else
typedef int8_t CHAR;
typedef int16_t SHORT;
typedef int32_t LONG;
typedef uint32_t DWORD;
typedef int32_t BOOL;
typedef int8_t BYTE;
typedef uint16_t WORD;

#endif

typedef struct tagBITMAPFILEHEADER {
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
} __attribute__((__packed__))BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
	DWORD biSize;
	LONG biWidth;
	LONG biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG biXPelsPerMeter;
	LONG biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
} __attribute__((__packed__))BITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagRGBQUAD {
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
	BYTE rgbReserved;
}__attribute__((__packed__))RGBQUAD;

typedef struct tagRGBTRIPLE {
	BYTE rgbtBlue;
	BYTE rgbtGreen;
	BYTE rgbtRed;
}__attribute__((__packed__))RGBTRIPLE;

#endif /* BITMAP_MYTYPES_H_ */
