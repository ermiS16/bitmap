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
<<<<<<< HEAD
#include "myConsts.h"
#include "Bitmap.h"


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
    int usedColors;
    int width;
    int height;
    
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
    
    printf("%d x %d\n", height, width);
    
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
    
    pixel24Bit = convertPixel( width, height, colormap, pixel8Bit);
    
    if (errNo != OK) {
        return errorHandling();
    }
    
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
=======
#include "main.h"
#include "einlesen.h"

int main() {
	int errNo = 0;
	BITMAPFILEHEADER *bfh = NULL;;
	BITMAPINFOHEADER *bih = NULL;
	BYTE *pPixel = NULL;
	RGBQUAD *pPalette = NULL;

	//printf("%d\n", 0x01U);

	errNo = readFile("testBilder/littleBitmap2_8.bmp",
			bfh, bih, pPixel, pPalette);
	if (errNo == FILE_NOT_FOUND) {
		printf(FILE_NOT_FOUND_TEXT);
		return -1;
	}

	if (errNo != OK) {
		printf(MALLOC_FAIL_TEXT);
		return -1;
	}

	printf("Beendet");

	return errNo;
>>>>>>> 079ec1b2f4c856218ed72e8fdb4c9f49560ee4f2
}

