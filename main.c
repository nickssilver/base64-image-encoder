#include "header.h"

/**
* main - receives arguments from the command line and calls library functions
* @argc: unused
* @argv: command line argument vector
*/

int main(int argc, char *argv[]) {
	// Initialize variables
	FILE * fd;
	char * binary_image;

	// Save Base 64 encoded version of image binary
	binary_image = base64_encode(argv[1]);
	
	// Open file named in command line argument
	fd = fopen(argv[2], "w+");
	if (!fd) 
		exit(-1);

	// Write Base 64 encoded ASCII to file
	fprintf(fd, "%s", binary_image);

	fclose(fd);	

	return (1);
}
