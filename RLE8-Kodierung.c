///*
// * RLE8-Kodierung.c
// *
// *  Created on: 04.11.2016
// *      Author: Eric
// */
//#include <stdio.h>
//#include "einlesen.h"
//#include "myError.h"
//#include "myTypes.h"
//#include "RLE8-Kodierung.h"
//
//int dekodierung(BITMAPINFOHEADER bi, char *vlaPixel[]) {
//
//	char pixel[1];
//
//	if (bi.biWidth < 0) {
//		bi.biWidth *= -1;
//	}
//	char vlaPixelNew = malloc(bi.biHeight * bi.biWidth * sizeof(char));
//
//	for (int i = 0; i < bi.biHeight; i++) {
//		for (int j = 0; j < bi.biWidth; i++) {
//			switch (vlaPixel[i][j])  {
//				case (0x00):
//					if (vlaPixel[i][j+1] == 0x00) {
//						//TODO Ende der Zeile erreicht
//						break;
//					} else {
//						if (vlaPixel[i][j+1] == 0x01) {
//							//TODO ENDE DER DATEI ERREICHT
//							break;
//						} else {
//							if (vlaPixel[i][j+1] == 0x02) {
//								j += vlaPixel[i][j+2];
//								i += vlaPixel[i][j+3];
//								break;
//							}
//						}
//					}
//					break;
//				case (0x01):
//					vlaPixelNew[i][j] = vlaPixel[i][j];
//					break;
//				default:
//					pixel = vlaPixel[i][j+1];
//					for (int k = 0; k < vlaPixel[i][j]; k++) {
//						vlaPixelNew[i][j+k] = pixel;
//					}
//					break;
//			}
//		}
//	}
//	free(vlaPixel);
//	vlaPixel = vlaPixelNew;
//
//	return OK;
//}
//
