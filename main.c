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
	printf("%d\n",0x01U);
	errno = readFile("Unbenannt.bmp\0");
	if (errno == FILE_NOT_FOUND) {
		printf("Datei wurde nicht gefunden! :(");
		return -1;
	}
	printf("Datei wurde geöffnet! :)");
	return errno;
}
