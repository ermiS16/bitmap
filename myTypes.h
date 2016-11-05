/*
 * myTypes.h
 *
 * Benutzt nicht die Standart int-Types,
 * da sonst Fheler bei unterschiedlichen Systemen auftreten koennen
 *
 *  Created on: 05.11.2016
 *      Author: andre
 */

#ifndef BITMAP_MYTYPES_H_
#define BITMAP_MYTYPES_H_

typedef __int8_t	CHAR;
typedef __int16_t	SHORT;
typedef __int32_t	LONG;
typedef __uint64_t	DWORD;
typedef __int32_t	BOOL;
typedef __uint8_t	BYTE;
typedef __uint16_t	WORD;

typedef struct tagBITMAPFILEHEADER {
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
} __attribute__((__packed__)) BITMAPFILEHEADER, *PBITMAPFILEHEADER;

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
} __attribute__((__packed__)) BITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagRGBQUAD {
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
	BYTE rgbReserved;
} __attribute__((__packed__)) RGBQUAD;

#endif /* BITMAP_MYTYPES_H_ */
