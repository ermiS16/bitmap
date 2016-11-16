/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   myConsts.h
 * Author: andre
 *
 * Created on 13. November 2016, 22:36
 */

#ifndef MYCONSTS_H
#define MYCONSTS_H

#include "myTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

    
#define BITMAP_SOURCE "/home/andre/Dokumente/Technische Informatik/2. Semester/Grundlagen systemnahes Programmieren/Praktikumsaufgaben/Aufgabe3/testBilder/newFile.bmp"
#define BITMAP_DESTINATION "/home/andre/Dokumente/Technische Informatik/2. Semester/Grundlagen systemnahes Programmieren/Praktikumsaufgaben/Aufgabe3/testBilder/newFile.bmp"
#define READ_MODE "r"
#define WRITE_MODE "w+"
    
#define MAX_USED_COLORS 256
#define BITMAP_TYPE 0x4D42
#define TYPE_8_BIT 8
#define TYPE_24_BIT 24
#define NO_COMPRESSION 0
#define COMPRESSION 1
#define MAX_WIDTH 100000
#define MAX_HEIGHT 100000

#define FULL_COLOR 255
#define NO_COLOR 0

    
#ifdef __cplusplus
}
#endif

#endif /* MYCONSTS_H */

