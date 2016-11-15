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
#include "myError.h"
#include "myTypes.h"
#include "myConsts.h"
#include "Bitmap.h"
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
    
    errNo = OK;
    
    source = openFile("testBilder/amrandrle.bmp", READ_MODE);
    
    if (errNo != OK) {
        return errorHandling();
    }
    
    fileheader = readFileHeader(source);
    
    if (errNo != OK) {
        return errorHandling();
    }
    
    infoheader = readInfoHeader(source);
    
    if (errNo != OK) {
        return errorHandling();
    }
    if (infoheader->biClrUsed == 0) {
        usedColors = MAX_USED_COLORS;
    } else {
        if (infoheader->biClrUsed > 0 && infoheader->biClrUsed < MAX_USED_COLORS) {
            usedColors = infoheader->biClrUsed;
        } else {
            errNo = COLORMAP_ERROR;
        }
    }
    
    height = infoheader->biHeight;
    width = infoheader->biWidth;
    offset = fileheader->bfOffBits;
    printf("%d x %d\n", height, width);
    
    if (errNo != OK) {
        return errorHandling();
    }
    
    colormap = readColormap(source, usedColors);
    
    if (errNo != OK) {
        return errorHandling();
    }
    
    pixel8Bit = readPixel(source, width, height, infoheader);

    if (errNo != OK) {
        return errorHandling();
    }
    
    errNo = closeFile(source);
    
    if (errNo != OK) {
        return errorHandling();
    }
    
    pixel24Bit = convertPixel( width, height, colormap, pixel8Bit);
    
    if (errNo != OK) {
        return errorHandling();
    }
    
    fileheader = convertFileHeader(fileheader);
    infoheader = convertInfoHeader(infoheader);
    
    if (errNo != OK) {
        return errorHandling();
    }
    
    dest = openFile("testBilder/newFile.bmp", WRITE_MODE);
    
    if (errNo != OK) {
        return errorHandling();
    }
    
    errNo = writeBitmap(dest, fileheader, infoheader, pixel24Bit, width, height);
    
    if (errNo != OK) {
        return errorHandling();
    }
    
    errNo = closeFile(dest);
    
    if (errNo != OK) {
        return errorHandling();
    }
    
    free(fileheader);
    free(infoheader);
    free(colormap);
    free(pixel8Bit);
    free(pixel24Bit);
    
    return (EXIT_SUCCESS);
}

