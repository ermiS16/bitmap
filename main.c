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
#include "RectangleFinder.h"


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
    int indexUL;
    int indexUR;
    int indexBL;
    int indexBR;
    
    errNo = OK;
    
    source = openFile("/home/andre/workspace/GSP/bitmap/aufgabe3_bild1.bmp", READ_MODE);
    
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
    
    if (errNo != OK) {
        return errorHandling();
    }
    
    colormap = readColormap(source, usedColors);
    
    if (errNo != OK) {
        return errorHandling();
    }
    
    pixel8Bit = readPixel(source, width, height);
    
    if (errNo != OK) {
        return errorHandling();
    }
    
    errNo = closeFile(source);
    
    if (errNo != OK) {
        return errorHandling();
    }
    
    pixel24Bit = convertPixel(width, height, colormap, pixel8Bit);
    
    if (errNo != OK) {
        return errorHandling();
    }
    
    findRedRectangle(pixel24Bit, width, height, &indexBL, &indexBR, &indexUL, &indexUR);
    setFrame(pixel24Bit, width, indexBL, indexBR, indexUL, indexUR);
    
    findGreenRectangle(pixel24Bit, width, height, &indexBL, &indexBR, &indexUL, &indexUR);
    setFrame(pixel24Bit, width, indexBL, indexBR, indexUL, indexUR);
    
    fileheader = convertFileHeader(fileheader);
    infoheader = convertInfoHeader(infoheader);
    
    if (errNo != OK) {
        return errorHandling();
    }
    
    dest = openFile("/home/andre/workspace/GSP/bitmap/newFile.bmp", WRITE_MODE);
    
    if (errNo != OK) {
        return errorHandling();
    }
    
    errNo = writeFile(dest, fileheader, infoheader, pixel24Bit, width, height);
    
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

