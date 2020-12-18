#include <stdio.h>
#include "file_handler.h"

void file_read(char *path){
	FILE *fptr;

	fptr = fopen(path, "r");

	fclose(fptr);
}