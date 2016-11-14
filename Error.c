/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include "myError.h"

int errorHandling() {
    switch (errNo) {
        case OK:
            return OK;
                    
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
            
        case MALLOC_FAIL:
            printf(MALLOC_FAIL_TEXT);
            break;
            
        case FILE_NOT_FOUND:
            printf(FILE_NOT_FOUND_TEXT);
            break;
    }
    //clean up
    return NOT_OK;
}
