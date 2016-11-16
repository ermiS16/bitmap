/*
 * RLE8.c
 *
 *  Created on: 14.11.2016
 *      Author: Eric
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

#define MARKER_END_OF_LINE "End of Line\n"
#define MARKER_END_OF_FILE "End of File\n"
#define PIXEL_MAX 255
//#define COUNT_MAX 255

int error = 0;

BYTE* rleDecompress(FILE *source, int width, int height){
	BYTE static *newPixel = NULL;
	int count = 0;
	BYTE pixel = NULL;
        BYTE absoluteMode = NULL;
	int xOffset = 0;
	int yOffset = 0;
        int endOfFile = 1;
        int pixelCount = 0;

	newPixel = (BYTE*) malloc(sizeof(BYTE) * width * height);

	while(!feof(source)){
		error = fread(&count, sizeof(BYTE), 1, source);
		if(count < 1){
                    error = fread(&pixel, sizeof(BYTE), 1, source);
                    switch(pixel){
                    case 0:	
                        break;
                                    
                    case 1:	
                        endOfFile = 0;
                        break;
                                    
                    case 2:	
                        fread(&xOffset, sizeof(BYTE), 1, source);
                        fread(&yOffset, sizeof(BYTE), 1, source);
                        fseek(source,(xOffset*yOffset),SEEK_SET);
                        break;
                                    
                    default:
                        if(count < 0 || count > 255){
                            errNo = CANT_COMPRESS;
                            return NULL;
                        
                        }else{
                            for (int i = 0; i < pixel; i++) {
                                fread(&absoluteMode, sizeof(BYTE), 1, source);
                                if (pixelCount < (height * width)) {
                                    newPixel[pixelCount] = absoluteMode;
                                    pixelCount++;
                                } else {
                                    errNo = PIXEL_OUT_OF_BOUNDS;
                                    return NULL;
                                }
                            }
                            if((pixel % 2) != 0) {
                                fread(&absoluteMode, sizeof(BYTE), 1, source);
                            }
                        }
                    }
		} else {
                    fread(&pixel, sizeof(BYTE), 1, source);
                    for (int i = pixelCount; i < (count + pixelCount); i++) {
                        if (i < height * width) {
                            newPixel[i] = pixel;
                        } else {
                            errNo = PIXEL_OUT_OF_BOUNDS;
                            return NULL;
                        }
                    }
                    pixelCount += count;
		}
	}
	return newPixel;
}
