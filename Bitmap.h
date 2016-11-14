/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bitmap.h
 * Author: andre
 *
 * Created on 13. November 2016, 22:39
 */

#ifndef BITMAP_H
#define BITMAP_H

#ifdef __cplusplus
extern "C" {
#endif

BITMAPFILEHEADER* readFileHeader(FILE *source);

BITMAPINFOHEADER* readInfoHeader(FILE *source);

RGBQUAD* readColormap(FILE *source, int usedColors);

BYTE* readPixel(FILE *source, int width, int height);

RGBTRIPLE* convertPixel(int width, int height, RGBQUAD *colormap, BYTE *pixel8Bit);

BITMAPFILEHEADER* convertFileHeader(BITMAPFILEHEADER *fileheader);

BITMAPINFOHEADER* convertInfoHeader(BITMAPINFOHEADER *infoheader);

int writeFile(FILE *dest, BITMAPFILEHEADER *fileheader, BITMAPINFOHEADER *infoheader, RGBTRIPLE *pixel24Bit, int width, int height);

FILE* openFile(char *filename, char *mode);

int closeFile(FILE *file);


#ifdef __cplusplus
}
#endif

#endif /* BITMAP_H */

