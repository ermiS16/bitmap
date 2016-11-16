/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RectangleFinder.h
 * Author: andre
 *
 * Created on 14. November 2016, 14:58
 */

#ifndef RECTANGLEFINDER_H
#define RECTANGLEFINDER_H

#ifdef __cplusplus
extern "C" {
#endif

int findRectangle(RGBTRIPLE *pixel24Bit, RGBTRIPLE color, int width, int height, int *bl, int *br, int *ul, int *ur);

int setPixel(RGBTRIPLE *pixel24Bit, int index);

int findFramePoints(RGBTRIPLE *pixel24Bit, int width, int rbl, int rbr, int rul, int rur, int gbl, int gbr, int gul, int gur);

int setFrame(RGBTRIPLE *pixel24Bit, int width, int bl, int br, int ul, int ur);

#ifdef __cplusplus
}
#endif

#endif /* RECTANGLEFINDER_H */

