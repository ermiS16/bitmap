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

<<<<<<< HEAD
#ifndef MYTYPES_H
#define MYTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

=======
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
>>>>>>> 079ec1b2f4c856218ed72e8fdb4c9f49560ee4f2
typedef int8_t CHAR;
typedef int16_t SHORT;
typedef int32_t LONG;
typedef uint32_t DWORD;
typedef int32_t BOOL;
typedef uint8_t BYTE;
typedef uint16_t WORD;

<<<<<<< HEAD
=======
#endif
>>>>>>> 079ec1b2f4c856218ed72e8fdb4c9f49560ee4f2

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
<<<<<<< HEAD
        BYTE rgbRed;	
        BYTE rgbBlue;
	BYTE rgbGreen;
	
=======
	BYTE rgbtBlue;
	BYTE rgbtGreen;
	BYTE rgbtRed;
>>>>>>> 079ec1b2f4c856218ed72e8fdb4c9f49560ee4f2
}__attribute__((__packed__))RGBTRIPLE;


#ifdef __cplusplus
}
#endif

#endif /* MYTYPES_H */

