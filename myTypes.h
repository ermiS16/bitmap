/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   myTypes.h
 * Author: andre
 *
 * Created on 13. November 2016, 20:55
 */

#ifndef MYTYPES_H
#define MYTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef int8_t CHAR;
typedef int16_t SHORT;
typedef int32_t LONG;
typedef uint32_t DWORD;
typedef int32_t BOOL;
typedef uint8_t BYTE;
typedef uint16_t WORD;


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
        BYTE rgbBlue;
	BYTE rgbGreen;
        BYTE rgbRed;
}__attribute__((__packed__))RGBTRIPLE;

typedef struct pixelPosition {
    WORD xPos;
    WORD yPos;
} PIXEL_POS;

#ifdef __cplusplus
}
#endif

#endif /* MYTYPES_H */

