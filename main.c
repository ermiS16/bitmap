/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: andre
 *
 * Created on 13. November 2016, 20:54
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "myError.h"
#include "myTypes.h"
#include "myConsts.h"
#include "Bitmap.h"
#include "RectangleFinder.h"
#include "RLE8.h"


/*
 * 
 */
int main(int argc, char** argv) {
    FILE *source = NULL;
    FILE *dest = NULL;
    BITMAPFILEHEADER *fileheader = NULL;
    BITMAPINFOHEADER *infoheader = NULL;
    RGBQUAD *colormap = NULL;
    BYTE *pixel8Bit = NULL;
    RGBTRIPLE *pixel24Bit = NULL;
    uint32_t offset;
    int usedColors;
    int width;
    int height;
    int indexRUL;
    int indexRUR;
    int indexRBL;
    int indexRBR;
    
    int indexGUL;
    int indexGUR;
    int indexGBL;
    int indexGBR;
    
    RGBTRIPLE red;
    red.rgbBlue = NO_COLOR;
    red.rgbGreen = NO_COLOR;
    red.rgbRed = FULL_COLOR;
    
    RGBTRIPLE green;
    green.rgbBlue = NO_COLOR;
    green.rgbGreen = FULL_COLOR;
    green.rgbRed = NO_COLOR;
    
    errNo = OK;
    
    source = openFile(BITMAP_SOURCE, READ_MODE);
    
    if (errNo != OK) {
        return errorHandling(source, fileheader, infoheader, colormap, pixel8Bit, pixel24Bit);
    }
    
    fileheader = readFileHeader(source);
    
    if (errNo != OK) {
        return errorHandling(source, fileheader, infoheader, colormap, pixel8Bit, pixel24Bit);
    }
    
    infoheader = readInfoHeader(source);
    
    if (errNo != OK) {
        return errorHandling(source, fileheader, infoheader, colormap, pixel8Bit, pixel24Bit);
    }
    if (infoheader->biClrUsed == 0) {
        usedColors = MAX_USED_COLORS;
    } else {
        if (infoheader->biClrUsed > 0 && infoheader->biClrUsed < MAX_USED_COLORS) {
            usedColors = infoheader->biClrUsed;
        } else {
            errNo = COLORMAP_ERROR;
            return errorHandling(source, fileheader, infoheader, colormap, pixel8Bit, pixel24Bit);
        }
    }
    
    height = infoheader->biHeight;
    width = infoheader->biWidth;
    offset = fileheader->bfOffBits;
    
    printf("Size of Bitmap: %d x %d\n", width , height);
    
    if (errNo != OK) {
        return errorHandling(source, fileheader, infoheader, colormap, pixel8Bit, pixel24Bit);
    }
    
    if (infoheader->biBitCount == 8) {
    
        colormap = readColormap(source, usedColors);
    
        if (errNo != OK) {
            return errorHandling(source, fileheader, infoheader, colormap, pixel8Bit, pixel24Bit);
        }
    
        if (infoheader->biCompression == 1) {
            pixel8Bit = rleDecompress(source, width, height);
        } else {
            pixel8Bit = readPixel(source, width, height);
        }
        
        if (errNo != OK) {
            return errorHandling(source, fileheader, infoheader, colormap, pixel8Bit, pixel24Bit);
        }
    
        pixel24Bit = convertPixel(width, height, colormap, pixel8Bit);
    
        if (errNo != OK) {
            return errorHandling(source, fileheader, infoheader, colormap, pixel8Bit, pixel24Bit);
        }
        
        free(pixel8Bit);
        pixel8Bit = NULL;
        free(colormap);
        colormap = NULL;
    } else {
        if (infoheader->biCompression != 0) {
            errNo = CANT_COMPRESS;
            return errorHandling(source, fileheader, infoheader, colormap, pixel8Bit, pixel24Bit);
        }
        pixel24Bit = read24BitPixel(source, width, height);
        
    }
    
    closeFile(source);
    source = NULL;
    
    
    if (errNo != OK) {
        return errorHandling(source, fileheader, infoheader, colormap, pixel8Bit, pixel24Bit);
    }
    
    findRectangle(pixel24Bit, red, width, height, &indexRBL, &indexRBR, &indexRUL, &indexRUR);
    
    if (errNo != OK) {
        return errorHandling(source, fileheader, infoheader, colormap, pixel8Bit, pixel24Bit);
    }
    
    findRectangle(pixel24Bit, green, width, height, &indexGBL, &indexGBR, &indexGUL, &indexGUR);
    
    if (errNo != OK) {
        return errorHandling(source, fileheader, infoheader, colormap, pixel8Bit, pixel24Bit);
    }
    
    findFramePoints(pixel24Bit, width, indexRBL, indexRBR, indexRUL, indexRUR, indexGBL, indexGBR, indexGUL, indexGUR);
    
    if (errNo != OK) {
        return errorHandling(source, fileheader, infoheader, colormap, pixel8Bit, pixel24Bit);
    }
    
    fileheader = convertFileHeader(fileheader);
    infoheader = convertInfoHeader(infoheader);
    
    if (errNo != OK) {
        return errorHandling(source, fileheader, infoheader, colormap, pixel8Bit, pixel24Bit);
    }
    
    
    dest = openFile(BITMAP_DESTINATION, WRITE_MODE);
    
    if (errNo != OK) {
        return errorHandling(dest, fileheader, infoheader, colormap, pixel8Bit, pixel24Bit);
    }
    
    writeFile(dest, fileheader, infoheader, pixel24Bit, width, height);
    
    if (errNo != OK) {
        return errorHandling(dest, fileheader, infoheader, colormap, pixel8Bit, pixel24Bit);
    }
    
    closeFile(dest);
    dest = NULL;
    
    cleanUp(dest, fileheader, infoheader, colormap, pixel8Bit, pixel24Bit);
    
    printf("----->Bitmap successfully converted<-----");
    fflush(stdout);
    return (EXIT_SUCCESS);
}

