/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "myError.h"
#include "myTypes.h"
#include "myConsts.h"
#include "Bitmap.h"
#include "RLE8.h"

#define FILEHEADER_TYPE_BITMAP 0x4D42 // Dez: 19778 -> ASCII: BM


BITMAPFILEHEADER* readFileHeader(FILE *source) {
    BITMAPFILEHEADER *fh = NULL;
    if (NULL == source) {
        errNo = FILE_NOT_FOUND;
        return NULL;
    }
    
    fh = (BITMAPFILEHEADER*) malloc(sizeof(BITMAPFILEHEADER));
    if (NULL == fh) {
        errNo = MALLOC_FAIL;
        return NULL;
    }
    
    fread(fh, sizeof(BITMAPFILEHEADER), 1, source);
    
    if(fh->bfType != FILEHEADER_TYPE_BITMAP){
    	errNo = NOT_A_BITMAP;
    	return NULL;
    }

    return fh;
}

BITMAPINFOHEADER* readInfoHeader(FILE *source) {
    BITMAPINFOHEADER *ih = NULL;
    if (NULL == source) {
        errNo = FILE_NOT_FOUND;
        return NULL;
    }
    
    ih = (BITMAPINFOHEADER*) malloc(sizeof(BITMAPINFOHEADER));
    if (NULL == ih) {
        errNo = MALLOC_FAIL;
        return NULL;
    }
    
    fread(ih, sizeof(BITMAPINFOHEADER), 1, source);
    
    return ih;
}

RGBQUAD* readColormap(FILE *source, int usedColors) {
    RGBQUAD *cm = NULL;
    if (NULL == source) {
        errNo = FILE_NOT_FOUND;
        return NULL;
    }
    
    if (usedColors < 1 || usedColors > 256) {
        errNo = COLORMAP_ERROR;
        return NULL;
    }
    
    cm = (RGBQUAD*) malloc(sizeof(RGBQUAD) * usedColors);
    if (NULL == cm) {
        errNo = MALLOC_FAIL;
        return NULL;
    }
    
    fread(cm, sizeof(RGBQUAD), usedColors, source);
    
    
    return cm;
}

BYTE* readPixel(FILE *source, int width, int height, BITMAPINFOHEADER *infoheader) {
    BYTE *p8B = NULL;
    if (NULL == source) {
        errNo = FILE_NOT_FOUND;
        return NULL;
    }
    
    if (width < 1 || height < 1) {
        errNo = SIZE_ERROR;
        return NULL;
    }


    p8B = (BYTE*) malloc(sizeof(BYTE) * width * height);
    if (NULL == p8B) {
        errNo = MALLOC_FAIL;
        return NULL;
    }
    
    if(infoheader->biCompression == 1){
    	p8B = rleDecompress(source, width, height);
    }else{
    	fread(p8B, sizeof(BYTE), (width * height), source);
    }
    return p8B;
} 

RGBTRIPLE* convertPixel( int width, int height, RGBQUAD colormap[256], BYTE pixel8Bit[width * height]) {
    RGBTRIPLE *p24B = NULL;
    RGBTRIPLE pixel;
    
    p24B = (RGBTRIPLE*) malloc(sizeof(RGBTRIPLE) * width * height);
    if(NULL == p24B) {
        return MALLOC_FAIL;
    }
    
    for (int i = 0; i < width * height; i++) {
        pixel.rgbtBlue = colormap[pixel8Bit[i]].rgbBlue;
        pixel.rgbtGreen = colormap[pixel8Bit[i]].rgbGreen;
        pixel.rgbtRed = colormap[pixel8Bit[i]].rgbRed;
        p24B[i] = pixel;
    }
    
    return p24B;
}

BITMAPFILEHEADER* convertFileHeader(BITMAPFILEHEADER *fileheader) {
    BITMAPFILEHEADER *fh = NULL;
   
    fh = (BITMAPFILEHEADER*) malloc(sizeof(BITMAPFILEHEADER));
    if(NULL == fh) {
        return MALLOC_FAIL;
    }
    
    fh->bfType = fileheader->bfType;
    fh->bfSize = fileheader->bfSize;
    fh->bfReserved1 = fileheader->bfReserved1;
    fh->bfReserved2 = fileheader->bfReserved2;
    fh->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
     
    return fh;
}

BITMAPINFOHEADER* convertInfoHeader(BITMAPINFOHEADER *infoheader) {
    BITMAPINFOHEADER *ih;
    
    ih = malloc(sizeof(BITMAPINFOHEADER));
    
    if (NULL == ih) {
        errNo = MALLOC_FAIL;
        return NULL;
    }
    
    ih->biSize = infoheader->biSize;
    ih->biWidth = infoheader->biWidth;
    ih->biHeight = infoheader->biHeight;
    ih->biPlanes = infoheader->biPlanes;
    ih->biBitCount = TYPE_24_BIT;
    ih->biCompression = NO_COMPRESSION;
    ih->biSizeImage = infoheader->biSizeImage;
    ih->biXPelsPerMeter = infoheader->biXPelsPerMeter;
    ih->biYPelsPerMeter = infoheader->biYPelsPerMeter;
    ih->biClrUsed = infoheader->biClrUsed;
    ih->biClrImportant = infoheader->biClrImportant;
    
    return ih;
}

int writeBitmap(FILE *dest, BITMAPFILEHEADER *fileheader, BITMAPINFOHEADER *infoheader, RGBTRIPLE *pixel24Bit, int width, int height) {
    if (NULL == dest) {
        return FILE_NOT_FOUND;
    }
    
    fwrite(fileheader, sizeof(BITMAPFILEHEADER), 1, dest);
    fwrite(infoheader, sizeof(BITMAPINFOHEADER), 1, dest);
    for (int i = 0; i < width * height; i++) {
        fwrite(&pixel24Bit[i], sizeof(RGBTRIPLE), 1, dest);
    }
    
    return OK;
}

FILE* openFile(char *filename, char *mode) {
    FILE *new = NULL;
    
    new = fopen(filename, mode);
    
    if(NULL == new) {
        errNo = FILE_NOT_FOUND;
        return NULL;
    }
    
    return new;
}

int closeFile(FILE *file) {
    if (NULL == file) {
        return FILE_NOT_FOUND;
    }
    
    fclose(file);
    
    return OK;
}
