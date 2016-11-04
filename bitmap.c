/*
 * bitmap.c
 *
 *  Created on: 04.11.2016
 *      Author: Eric
 */

#include <stdio.h>
#include <bitmap.h>

//typedef char = CHAR
//typedef short = SHORT
//typedef long = LONG
//typedef unsigned long = DWORD
//typedef int = BOOL
//typedef unsigned char = BYTE
//typedef unsigned short = WORD

typedef struct BITMAPFILEHEADER{
	typedef unsigned short bfType;
	typedef unsigned long bfSize;
	typedef unsigned short bfReserved1;
	typedef unsigned short bfReserved2;
	typedef unsigned long bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct BITMAPINFOHEADER{
	typedef unsigned long biSize;
	typedef long biWidth;
	typedef long biheight;
	typedef unsigned short biPlanes;
	typedef unsigned short biBitCount;
	typedef unsigned long biCompression;
	typedef unsigned long biSizeImage;
	typedef long biXPelsPerMeter;
	typedef long biYPelsPerMeter;
	typedef unsigned long biClrUsed;
	typedef unsigned long biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagRGBQuad{
	unsigned char rgbBlue;
	unsigned char rgbGreen;
	unsigned char rgbRed;
	unsigned char rgbReserved;
}RGBQUAD;

typedef struct tagRGBTriple{
	unsigned char rgbBlue;
	unsigned char rgbGreen;
	unsigned char rgbRed;
}RGBTRIPLE;
