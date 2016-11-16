/*
 * RLE8.h
 *
 *  Created on: 14.11.2016
 *      Author: Eric
 */

#ifndef RLE8_H_
#define RLE8_H_

BYTE* rleDecompress(FILE *source, int width, int height);

void encodeMode(FILE *source, BYTE *newPixel, BYTE count, BYTE *pixel);

void absoluteMode(FILE *source, BYTE *newPixel, BYTE *pixel);

#endif /* RLE8_H_ */