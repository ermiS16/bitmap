/*
 * main.c
 *
 *  Created on: 19.10.2016
 *      Author: Eric
 */

#include <stdio.h>
#include "bitmap.h"
#include "myError.h"
#include "myTypes.h"
#include "main.h"


int main(){
	int errno;
	printf("%d",0x01U);
	errno = readFile("Unbenannt.bmp");
	return errno;
}
