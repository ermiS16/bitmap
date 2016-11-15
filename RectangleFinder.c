/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "myConsts.h"
#include "myError.h"
#include "myTypes.h"

#define FULL_COLOR 0xFF
#define NO_COLOR 0x00


int findRedRectangle(RGBTRIPLE *pixel24Bit, int width, int height, int *bl, int *br, int *ul, int *ur) {
    int indexBL = 0;
    int indexBR = 0;
    int indexUL = 0;
    int indexUR = 0;
    
    int counter;
    
    for (int i = 0; i < (width * height); i++) {
        if (pixel24Bit[i].rgbRed == FULL_COLOR && pixel24Bit[i].rgbGreen == NO_COLOR && pixel24Bit[i].rgbBlue == NO_COLOR) {
            if (pixel24Bit[i+5].rgbRed == FULL_COLOR && pixel24Bit[i+5].rgbGreen == NO_COLOR && pixel24Bit[i+5].rgbBlue == NO_COLOR) {
                if (indexBL == 0) {
                    indexBL = i;
                }
                counter = 0;
                while(!indexUL) {
                    counter++;
                    if ((i + (counter * width)) > (height * width)){
                       break;
                    }
                    if (pixel24Bit[i+(counter*width)].rgbRed == FULL_COLOR && pixel24Bit[i+(counter*width)].rgbGreen == FULL_COLOR && pixel24Bit[i+(counter*width)].rgbBlue == FULL_COLOR) {
                        if (indexUL == 0) {
                            indexUL = i + ((counter - 1) * width);
                        }
                    }
                }
            }
            if (pixel24Bit[i+1].rgbRed == FULL_COLOR && pixel24Bit[i+1].rgbGreen == FULL_COLOR && pixel24Bit[i+1].rgbBlue == FULL_COLOR){
                if (indexBR == 0) {
                    indexBR = i;
                }
                counter = 0;
                while(!indexUR) {
                   counter++;
                   if ((i + (counter * width)) > (height * width)){
                       break;
                   }
                   if (pixel24Bit[i+(counter*width)].rgbRed == FULL_COLOR && pixel24Bit[i+(counter*width)].rgbGreen == FULL_COLOR && pixel24Bit[i+(counter*width)].rgbBlue == FULL_COLOR) {
                        if (indexUR == 0) {
                            indexUR = i + ((counter - 1) * width);
                        }
                   }
                }
            }   
        }
    }
    if (ul != 0) {
        *ul = indexUL;
    } else {
        return NO_RECTANGLE_FOUND;
    }
    
    if (ur != 0) {
        *ur = indexUR;
    } else {
        return NO_RECTANGLE_FOUND;
    }
    
    if (bl != 0) {
        *bl = indexBL;
    } else {
        return NO_RECTANGLE_FOUND;
    }
    
    if (br != 0) {
        *br = indexBR;
    } else {
        return NO_RECTANGLE_FOUND;
    }
    
    return OK;
}


int findGreenRectangle(RGBTRIPLE *pixel24Bit, int width, int height, int *bl, int *br, int *ul, int *ur) {
    int indexBL = 0;
    int indexBR = 0;
    int indexUL = 0;
    int indexUR = 0;
    
    int counter;
    
    for (int i = 0; i < (width * height); i++) {
        if (pixel24Bit[i].rgbRed == NO_COLOR && pixel24Bit[i].rgbGreen == FULL_COLOR && pixel24Bit[i].rgbBlue == NO_COLOR) {
            if (pixel24Bit[i+5].rgbRed == NO_COLOR && pixel24Bit[i+5].rgbGreen == FULL_COLOR && pixel24Bit[i+5].rgbBlue == NO_COLOR) {
                if (indexBL == 0) {
                    indexBL = i;
                }
                counter = 0;
                while(!indexUL) {
                    counter++;
                    if ((i + (counter * width)) > (height * width)){
                       break;
                    }
                    if (pixel24Bit[i+(counter*width)].rgbRed == FULL_COLOR && pixel24Bit[i+(counter*width)].rgbGreen == FULL_COLOR && pixel24Bit[i+(counter*width)].rgbBlue == FULL_COLOR) {
                        if (indexUL == 0) {
                            indexUL = i + ((counter - 1) * width);
                        }
                    }
                }
            }
            if (pixel24Bit[i+1].rgbRed == FULL_COLOR && pixel24Bit[i+1].rgbGreen == FULL_COLOR && pixel24Bit[i+1].rgbBlue == FULL_COLOR){
                if (indexBR == 0) {
                    indexBR = i;
                }
                counter = 0;
                while(!indexUR) {
                   counter++;
                   if ((i + (counter * width)) > (height * width)){
                       break;
                   }
                   if (pixel24Bit[i+(counter*width)].rgbRed == FULL_COLOR && pixel24Bit[i+(counter*width)].rgbGreen == FULL_COLOR && pixel24Bit[i+(counter*width)].rgbBlue == FULL_COLOR) {
                        if (indexUR == 0) {
                            indexUR = i + ((counter - 1) * width);
                        }
                   }
                }
            }   
        }
    }
    if (ul != 0) {
        *ul = indexUL;
    } else {
        return NO_RECTANGLE_FOUND;
    }
    
    if (ur != 0) {
        *ur = indexUR;
    } else {
        return NO_RECTANGLE_FOUND;
    }
    
    if (bl != 0) {
        *bl = indexBL;
    } else {
        return NO_RECTANGLE_FOUND;
    }
    
    if (br != 0) {
        *br = indexBR;
    } else {
        return NO_RECTANGLE_FOUND;
    }
    
    return OK;
}
    
int setPixel(RGBTRIPLE *pixel24Bit, int index) {
    RGBTRIPLE pixelBlue;
    pixelBlue.rgbBlue = FULL_COLOR;
    pixelBlue.rgbGreen = NO_COLOR;
    pixelBlue.rgbRed = NO_COLOR;
    pixel24Bit[index] = pixelBlue;
    return OK;
}

int setFrame(RGBTRIPLE *pixel24Bit, int width, int bl, int br, int ul, int ur) {
    for (int i = bl; i <= br; i++) {
        setPixel(pixel24Bit, i);
    }
    for (int i = ul; i <= ur; i++) {
        setPixel(pixel24Bit, i);
    }
    for (int i = bl; i <= ul; i += width) {
        setPixel(pixel24Bit, i);
    }
    for (int i = br; i <= ur; i += width) {
        setPixel(pixel24Bit, i);
    }
    
    return OK;
}
