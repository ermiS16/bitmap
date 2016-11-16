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

int cleanUp(FILE *file, BITMAPFILEHEADER *fileheader, BITMAPINFOHEADER *infoheader, RGBQUAD *colormap, BYTE *pixel8Bit, RGBTRIPLE *pixel24Bit) {
    if (file != NULL) {
        fclose(file);
    }
    if (fileheader != NULL) {
        free(fileheader);
    }
    if (infoheader != NULL) {
        free(infoheader);
    }
    if (colormap != NULL) {
        free(colormap);
    }
    if (pixel8Bit != NULL) {
        free(pixel8Bit);
    }
    if (pixel24Bit != NULL) {
        free(pixel24Bit);
    }
    return NOT_OK;
}

int errorHandling(FILE *file, BITMAPFILEHEADER *fileheader, BITMAPINFOHEADER *infoheader, RGBQUAD *colormap, BYTE *pixel8Bit, RGBTRIPLE *pixel24Bit) {
    printf("-------------------- ERROR --------------------\n");
    printf("**********");
    if (errNo != OK) {
        switch (errNo) {                    
            case NOT_OK:
                printf(NOT_OK_TEXT);
                break;
            
            case COLORMAP_ERROR:
                printf(COLORMAP_ERROR_TEXT);
                break;
            
            case NOT_A_BITMAP:
                printf(NOT_A_BITMAP_TEXT);
                break;
            
            case SIZE_ERROR:
                printf(SIZE_ERROR_TEXT);
                break;
            
            case NO_RECTANGLE_FOUND:
                printf(NO_RECTANGLE_FOUND_TEXT);
                break;
            
            case MALLOC_FAIL:
                printf(MALLOC_FAIL_TEXT);
                break;
            
            case FILE_NOT_FOUND:
                printf(FILE_NOT_FOUND_TEXT);
                break;
            
            case PIXEL_OUT_OF_BOUNDS:
                printf(PIXEL_OUT_OF_BOUNDS_TEXT);
                break;
        
            case WRONG_FRAME_SIZE:
                printf(WRONG_FRAME_SIZE_TEXT);
                break;
        }
    } else {
        printf("Unknown Error");
    }
    printf("**********");
    cleanUp(file, fileheader, infoheader, colormap, pixel8Bit, pixel24Bit);
    fflush(stdout);
    return NOT_OK;
}
