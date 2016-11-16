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
 * Seeks the green rectangle in the Bitmap
 * @param pixel24Bit    Converted Pixel of the Bitmap
 * @param width         Width of the Bitmap
 * @param height        Height of the Bitmap
 * @param bl            Index of the Pixel in the corner bottom left
 * @param br            Index of the Pixel in the corner bottom right
 * @param ul            Index of the Pixel in the corner upper left
 * @param ur            Index of the Pixel in the corner upper right
 * @return 
 */
int findRectangle(RGBTRIPLE *pixel24Bit, RGBTRIPLE color, int width, int height, int *bl, int *br, int *ul, int *ur) {
    int indexBL = 0;
    int indexBR = 0;
    int indexUL = 0;
    int indexUR = 0;
    
    int counter;
    
    for (int i = 0; i < (width * height) - width; i++) {
        if (pixel24Bit[i].rgbRed == color.rgbRed && pixel24Bit[i].rgbGreen == color.rgbGreen && pixel24Bit[i].rgbBlue == color.rgbBlue) {
            if (pixel24Bit[i+3].rgbRed == color.rgbRed && pixel24Bit[i+3].rgbGreen == color.rgbGreen && pixel24Bit[i+3].rgbBlue == color.rgbBlue) {
                if (indexBL == 0) {
                    indexBL = i;
                    counter = 0;
                    while(!indexUL) {
                        counter++;
                        if ((i + (counter * width)) > (height * width)) {
                            if (pixel24Bit[i+((counter-1)*width)].rgbRed == color.rgbRed && pixel24Bit[i+((counter-1)*width)].rgbGreen == color.rgbGreen && pixel24Bit[i+((counter-1)*width)].rgbBlue == color.rgbBlue) {
                                indexUL = i + ((counter - 1) * width);
                            }
                            break;
                        }
                        if (pixel24Bit[i+(counter*width)].rgbRed != color.rgbRed || pixel24Bit[i+(counter*width)].rgbGreen != color.rgbGreen || pixel24Bit[i+(counter*width)].rgbBlue != color.rgbBlue) {
                            if (indexUL == 0) {
                                indexUL = i + ((counter - 1) * width);
                            }
                        }
                    }
                }
            }
            if (pixel24Bit[i+1].rgbRed != color.rgbRed || pixel24Bit[i+1].rgbGreen != color.rgbGreen || pixel24Bit[i+1].rgbBlue != color.rgbBlue){
                if (indexBR == 0) {
                    indexBR = i;
                    counter = 0;
                    while(!indexUR) {
                        counter++;
                        if ((i + (counter * width)) > (height * width)) {
                            if (pixel24Bit[i+((counter-1)*width)].rgbRed == color.rgbRed && pixel24Bit[i+((counter-1)*width)].rgbGreen == color.rgbGreen && pixel24Bit[i+((counter-1)*width)].rgbBlue == color.rgbBlue) {
                                indexUR = i + ((counter - 1) * width);
                            }
                            break;
                        }
                        if (pixel24Bit[i+(counter*width)].rgbRed != color.rgbRed || pixel24Bit[i+(counter*width)].rgbGreen != color.rgbGreen || pixel24Bit[i+(counter*width)].rgbBlue != color.rgbBlue) {
                            if (indexUR == 0) {
                                indexUR = i + ((counter - 1) * width);
                            }
                        }
                    }
                }   
            }
        }
        if (indexUR > 0) {
            break;
        }
    }
    *ul = indexUL;
    
    if (ur > 0) {
        *ur = indexUR;
    } else {
        errNo = NO_RECTANGLE_FOUND;
        return NOT_OK;
    }
    
    if (bl > 0) {
        *bl = indexBL;
    } else {
        errNo = NO_RECTANGLE_FOUND;
        return NOT_OK;
    }
    
    if (br > 0) {
        *br = indexBR;
    } else {
        errNo = NO_RECTANGLE_FOUND;
        return NOT_OK;
    }
    
    return OK;
}
    
/**
 * Set pixel at index as a blue-colored pixel
 * @param pixel24Bit    24 Bit Pixel of Bitmap
 * @param index         Index of the Pixel, which should be painted blue
 * @return 
 */
int setPixel(RGBTRIPLE *pixel24Bit, int index) {
    RGBTRIPLE pixelBlue;
    pixelBlue.rgbBlue = FULL_COLOR;
    pixelBlue.rgbGreen = NO_COLOR;
    pixelBlue.rgbRed = NO_COLOR;
    
    pixel24Bit[index] = pixelBlue;
    return OK;
}

/**
 * Seeks the corner points to build a frame, which includes all Rectangles
 * @param pixel24Bit    Convertet Pixel with 24 Bits
 * @param width         Width of the Bitmap
 * @param rbl           Pixel in the bottom left corner of red rectangle
 * @param rbr           Pixel in the bottom right corner of red rectangle
 * @param rul           Pixel in the upper left corner of red rectangle
 * @param rur           Pixel in the upper right corner of red rectangle
 * @param gbl           Pixel in the bottom left corner of green rectangle
 * @param gbr           Pixel in the bottom right corner of green rectangle
 * @param gul           Pixel in the Upper left corner of green rectangle
 * @param gur           Pixel in the upper right corner of green rectangle
 * @return 
 */
int findFramePoints(RGBTRIPLE *pixel24Bit, int width, int rbl, int rbr, int rul, int rur, int gbl, int gbr, int gul, int gur) {
    PIXEL_POS frameUL;
    PIXEL_POS frameUR;
    PIXEL_POS frameBL;
    PIXEL_POS frameBR;
    
    int fbl;
    int fbr;
    int ful;
    int fur;
    
    PIXEL_POS redBL;
    redBL.yPos = rbl / width;
    redBL.xPos = rbl - (redBL.yPos * width);
    
    PIXEL_POS redBR;
    redBR.yPos = rbr / width;
    redBR.xPos = rbr - (redBR.yPos * width);
    
    PIXEL_POS redUL;
    redUL.yPos = rul / width;
    redUL.xPos = rul - (redUL.yPos * width);
    
    PIXEL_POS redUR;
    redUR.yPos = rur / width;
    redUR.xPos = rur - (redUR.yPos * width);
    
    PIXEL_POS greenBL;
    greenBL.yPos = gbl / width;
    greenBL.xPos = gbl - (greenBL.yPos * width);
    
    PIXEL_POS greenBR;
    greenBR.yPos = gbr / width;
    greenBR.xPos = gbr - (greenBR.yPos * width);
    
    PIXEL_POS greenUL;
    greenUL.yPos = gul / width;
    greenUL.xPos = gul - (greenUL.yPos * width);
    
    PIXEL_POS greenUR;
    greenUR.yPos = gur / width;
    greenUR.xPos = gur - (greenUR.yPos * width);
    
    if (redBL.yPos < greenBL.yPos) {
        if (redBL.xPos < greenBL.xPos) {
            frameBL = redBL;
        } else {
            frameBL.xPos = greenBL.xPos;
            frameBL.yPos = redBL.yPos;
        }
    } else {
        if (redBL.xPos > greenBL.xPos) {
            frameBL = greenBL;
        } else {
            frameBL.xPos = redBL.xPos;
            frameBL.yPos = greenBL.yPos;
        }
    }
    
    if (redBR.yPos < greenBR.yPos) {
        if (redBR.xPos > greenBR.xPos) {
            frameBR = redBR;
        } else {
            frameBR.xPos = greenBR.xPos;
            frameBR.yPos = redBR.yPos;
        }
    } else {
        if (redBR.xPos < greenBR.xPos) {
            frameBR = greenBR;
        } else {
            frameBR.xPos = redBR.xPos;
            frameBR.yPos = greenBR.yPos;
        }
    }
    
    if (redUL.yPos > greenUL.yPos) {
        if (redUL.xPos < greenUL.xPos) {
            frameUL = redUL;
        } else {
            frameUL.xPos = greenUL.xPos;
            frameUL.yPos = redUL.yPos;
        }
    } else {
        if (redUL.xPos > greenUL.xPos) {
            frameUL = greenUL;
        } else {
            frameUL.xPos = redUL.xPos;
            frameUL.yPos = greenUL.yPos;
        }
    }
    
    if (redUR.yPos > greenUR.yPos) {
        if (redUR.xPos > greenUR.xPos) {
            frameUR = redUR;
        } else {
            frameUR.xPos = greenUR.xPos;
            frameUR.yPos = redUR.yPos;
        }
    } else {
        if (redUR.xPos < greenUR.xPos) {
            frameUR = greenUR;
        } else {
            frameUR.xPos = redUR.xPos;
            frameUR.yPos = greenUR.yPos;
        }
    }
    
    if (frameUL.yPos == frameUR.yPos && frameBL.yPos == frameBR.yPos && frameUL.xPos == frameBL.xPos && frameUR.xPos == frameBR.xPos) {
        ful = frameUL.xPos + (frameUL.yPos * width);
        fur = frameUR.xPos + (frameUR.yPos * width);
        fbl = frameBL.xPos + (frameBL.yPos * width);
        fbr = frameBR.xPos + (frameBR.yPos * width);
    } else {
        errNo = WRONG_FRAME_SIZE;
    }
    setFrame(pixel24Bit, width, fbl, fbr, ful, fur);
}

/**
 * Paints the blue frame in the Bitmap-File
 * @param pixel24Bit    24 Bit Pixel of the Bitmap
 * @param width         Width of the Bitmap
 * @param bl            Bottom left corner of frame
 * @param br            Bottom right corner of frame
 * @param ul            Upper left corner of frame
 * @param ur            Upper right corner of frame
 * @return 
 */
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
