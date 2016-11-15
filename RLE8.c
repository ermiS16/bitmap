/*
 * RLE8.c
 *
 *  Created on: 14.11.2016
 *      Author: Eric
 */

#include <stdio.h>
#include <stdlib.h>
#include "myError.h"
#include "myTypes.h"
#include "RLE8.h"

#define MARKER_END_OF_LINE "End of Line"
#define MARKER_END_OF_FILE "End of File"
#define PIXEL_MAX 255
//#define COUNT_MAX 255

int error = 0;

BYTE* rleDecompress(FILE *source, int width, int height){
	BYTE static *newPixel = NULL;
	BYTE count = 0;
	BYTE *pixel = NULL;
	int xOffset = 0;
	int yOffset = 0;

	newPixel = (BYTE*) malloc(sizeof(BYTE) * width*height);
	pixel = (BYTE*) malloc(sizeof(BYTE) * PIXEL_MAX);
	//count = (BYTE*) malloc(sizeof(BYTE) * COUNT_MAX);

	while(!feof(source)){
		error = fread(&count, sizeof(BYTE), 1, source);
		printf("Count: %d\n", error);

		if(count < 1){
			error = fread(&pixel, sizeof(BYTE), 1, source);
			printf("Marker: %d\n", error);
			switch(*pixel){
				case 0:	printf(MARKER_END_OF_LINE);
						break;
				case 1:	printf(MARKER_END_OF_FILE);
						break;
				case 2:	fread(&xOffset, sizeof(BYTE), 1, source);
						fread(&yOffset, sizeof(BYTE), 1, source);
						fseek(source,(xOffset*yOffset),SEEK_SET);
						break;
				default:
					if(count < 0 || count > 255){
						errNo = CANT_COMPRESS;
						return NULL;
					}else{
						absoluteMode(source, newPixel, pixel);
					}
				}
			}else{
				encodeMode(source, newPixel, count, pixel);
			}
	}
	return newPixel;
}

void encodeMode(FILE *source, BYTE *newPixel, BYTE count, BYTE *pixel){

		error = fread(newPixel, sizeof(BYTE), count, source);
		printf("Pixel: %d\n", error);

}

void absoluteMode(FILE *source, BYTE *newPixel, BYTE *pixel){
	BYTE newCount = sizeof(pixel);
	//BYTE endNull = 0;
	fread(&newCount, sizeof(BYTE), 1, source);
	for(int k=0; k<newCount;k++){
		error = fread(newPixel, sizeof(BYTE),sizeof(newCount), source);
		printf("Pixel: %d\n", error);
	}
	/*
	if(newCount % 2 != 0){
		*newPixel += endNull;
	}
	*/

}
