/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   myError.h
 * Author: andre
 *
 * Created on 13. November 2016, 20:57
 */

#ifndef MYERROR_H
#define MYERROR_H

#ifdef __cplusplus
extern "C" {
#endif
    
int errNo;

#define OK 1

            
#define NOT_OK -1
#define NOT_OK_TEXT "Unknown Error"
            
#define COLORMAP_ERROR -2
#define COLORMAP_ERROR_TEXT "Wrong size of Colormap"
    
#define NOT_A_BITMAP -3
#define NOT_A_BITMAP_TEXT "File is not a Bitmap"
    
#define SIZE_ERROR -4
#define SIZE_ERROR_TEXT "Wrong size of Bitmap"

#define NO_RECTANGLE_FOUND -5
#define NO_RECTANGLE_FOUND_TEXT "No Rectangle found"

#define MALLOC_FAIL -7
#define MALLOC_FAIL_TEXT "Malloc failed"

#define FILE_NOT_FOUND -8
#define FILE_NOT_FOUND_TEXT "File not found"

#define INFOHEADER_NOT_FOUND -9
#define INFOHEADER_NOT_FOUND_TEXT "Infoheader not found"

#define CANT_COMPRESS -10
#define CANT_COMPRESS_TEXT "Compression failed"

int errorHandling(void);

#ifdef __cplusplus
}
#endif

#endif /* MYERROR_H */

