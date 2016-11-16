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
#include "RectangleFinder.h"
#include "RLE8.h"

/**
 * Read a Fileheader out of an opened Bitmap-File
 * @param source    Bitmap-File
 * @return          Fileheader
 */
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
    
    if (fh->bfType != BITMAP_TYPE) {
        errNo = NOT_A_BITMAP;
        return NOT_OK;
    }
    
    return fh;
}

/**
 * Reads the InfoHeader out of an opened Bitmap
 * @param source    Bitmap-File
 * @return          InfoHeader
 */
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
    
    if (ih->biWidth > MAX_WIDTH || ih->biHeight > MAX_HEIGHT) {
        errNo = SIZE_ERROR;
        return NULL;
    }
    
    return ih;
}

/**
 * Read the Colormap out of an opened Bitmap-File
 * @param source        Bitmap-File
 * @param usedColors    Number of used Colors in the Bitmap-File
 * @return              Color-Map
 */
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
        errNo MALLOC_FAIL;
        return NULL;
    }
    
    fread(cm, sizeof(RGBQUAD), usedColors, source);
    
    
    return cm;
}

/**
 * Read the 8Bit Pixel out of an opened Bitmap-File
 * @param source    Bitmap-File
 * @param width     Width of Bitmap-File
 * @param height    Height of Bitmap-File
 * @return          Array with 8Bit Pixels
 */
BYTE* readPixel(FILE *source, int width, int height) {
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
    
    fread(p8B, sizeof(BYTE), (width * height), source);
    
    return p8B;
} 

/**
 * Convert Pixel from 8 Bit to 24 Bit
 * @param width         Width of Bitmap-File
 * @param height        Height of Bitmap-File
 * @param colormap      Colormap
 * @param pixel8Bit     Array with 8 Bit Pixels
 * @return              Array with converted 24Bit Pixels
 */
RGBTRIPLE* convertPixel(int width, int height, RGBQUAD colormap[256], BYTE pixel8Bit[width * height]) {
    RGBTRIPLE *p24B = NULL;
    RGBTRIPLE pixel;
    
    p24B = (RGBTRIPLE*) malloc(sizeof(RGBTRIPLE) * width * height);
    if(NULL == p24B) {
        return MALLOC_FAIL;
    }
    
    for (int i = 0; i < width * height; i++) {
        pixel.rgbBlue = colormap[pixel8Bit[i]].rgbBlue;
        pixel.rgbGreen = colormap[pixel8Bit[i]].rgbGreen;
        pixel.rgbRed = colormap[pixel8Bit[i]].rgbRed;
        p24B[i] = pixel;
    }
    
    return p24B;
}

/**
 * Converts the Fileheader of the Bitmapfile
 * @param fileheader
 * @return 
 */
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

/**
 * Converts the Infoheader of the Bitmapfile
 * @param fileheader
 * @return 
 */
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

/**
 * Writes a new Bitmap-File with converted Datas
 * @param dest          Destination File
 * @param fileheader    Converted Fileheader
 * @param infoheader    Converted Infoheader
 * @param pixel24Bit    Array with 24Bit Pixels 
 * @param width         Width of Bitmap-File
 * @param height        Height og Bitmap-File
 * @return              
 */
int writeFile(FILE *dest, BITMAPFILEHEADER *fileheader, BITMAPINFOHEADER *infoheader, RGBTRIPLE *pixel24Bit, int width, int height) {
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

/**
 * Reads Pixel of 24Bit Bitmap-File
 * @param source    Bitmap-File
 * @param width     Width of Bitmap-File
 * @param height    Heigth of Bitmap-File
 * @return          Array with 24Bit Pixels
 */
RGBTRIPLE* read24BitPixel(FILE *source, int width, int height) {
    RGBTRIPLE *p24B = NULL;
    if (NULL == source) {
        errNo = FILE_NOT_FOUND;
        return NULL;
    }
    
    if (width < 1 || height < 1) {
        errNo = SIZE_ERROR;
        return NULL;
    }
    
    p24B = (BYTE*) malloc(sizeof(BYTE) * width * height);
    if (NULL == p24B) {
        errNo = MALLOC_FAIL;
        return NULL;
    }
    
    fread(p24B, sizeof(RGBTRIPLE), (width * height), source);
    
    return p24B;
} 

/**
 * Opens a BitmapFile
 * @param filename  Name of File
 * @param mode      OpeningMode
 * @return          Pointer of File
 */
FILE* openFile(char *filename, char *mode) {
    FILE *new = NULL;
    
    new = fopen(filename, mode);
    
    if(NULL == new) {
        errNo = FILE_NOT_FOUND;
        return NULL;
    } else {
        printf("File %s opened\n", filename);
    }
    
    return new;
}

/**
 * Closes the File
 * @param file  File to close
 * @return
 */
int closeFile(FILE *file) {
    if (NULL == file) {
        return FILE_NOT_FOUND;
    } 
    
    fclose(file);
    printf("File has been closed\n");
    file = NULL;
    
    return OK;
}
