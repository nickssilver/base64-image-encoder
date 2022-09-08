#include "header.h"

/**
* This function adapted from libcurl API tutorial
* https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
*
* callback - curl easy handle function to write GET response to memory instead of stdout
* @data: delivered binary output data of GET request to image URL
* @size: always 1
* @nmemb: size of delivered data
* @userdata: data set by CURLOPT_WRITEDATA option
*
* Return: actual size of delivered data
*/

static size_t callback(void *data, size_t size, size_t nmemb, void *userdata) {
	// Initialize variables
	size_t actual = size * nmemb;
	BufferStruct *buff = (struct BufferStruct *)userdata;

	// Reallocate memory
	char *p = realloc(buff->buffer, buff->size + actual + 1);
	if(!p)
		return (0);
 
	// Assign buff to reallocated memory chunk
	buff->buffer = p;
	memcpy(&(buff->buffer[buff->size]), data, actual);
	buff->size += actual;
	
	// Terminate
	buff->buffer[buff->size] = 0;
 
	// Return size of data
	return (actual);
}
 
/**
* get_image - function to make a curl request to the user specified URL
* @url: user specified URL
*
* Return: memory struct containing:
* 	@buffer: image binary
*	@size: size of binary
*/

BufferStruct get_image(char *url) {
	// Initialize variables and CURL easy handle
	CURL *curl = curl_easy_init();
	CURLcode res;
	
	// Initialize buffer struct
	BufferStruct buff;
	buff.buffer = malloc(1);
	buff.size = 0;

	// Configure CURL easy handle
	curl_easy_setopt(curl, CURLOPT_URL, url);

	// Configure write function
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

	// Configure write location
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&buff);

	// Run blocking file transfer
	res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		printf("Request failed\n");
	}	

	// End CURL easy handle
	curl_easy_cleanup(curl);
	return (buff);
}

/**
* base64_encode - function to encode an image binary into Base 64 ASCII
* @url: user specified URL
*
* Return: Base 64 encoded string
*/

char * base64_encode(char *url) {
	// Initialize variables
	static char base64_encode[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	BufferStruct image_binary = get_image(url);
	char *place, *encoded = NULL;
	int i;
	char * src = image_binary.buffer;

	// Allocate memory for the encoded string
	// 4/3 times the size of the binary file
	encoded = malloc(image_binary.size * 4/3 + 1);
	if (!encoded)
		printf("malloc failed\n");
	
	// Assign pointer to allocated space for encoded string
	place = encoded;

	// Loop through binary data in sets of 3 and assign 4 characters
	for (i = 0; i < image_binary.size - 2; i += 3)
	{
		// For example: src[i] = 11011001
		
		// Shift right 2 (divide by 4 & remove remainder); 11011001 -> 00110110; compare with 0x3F=63; 
		// 00010000 = base64_encode[16] = P
		*place++ = base64_encode[(src[i] >> 2) & 0x3F];

		// Left side of |: Compare with 0x3=3: 11011001 & 00000011 = 00000001;
		// Shift left 4 (multiply by 16); 00000001 -> 00010000;
		// Right side of |: Compare src[i+1] = 11001100 with 0xF0=240=11110000; 11000000
		// Shift right 4 (divide by 16 & remove remainder); 11000000 -> 00000000
		// Compare left and right: 00010000 | 00000000 = 00010000 = 16
		// 00010000 - base64_encode[16] = P
		*place++ = base64_encode[((src[i] & 0x3) << 4) | ((src[i + 1] & 0xF0) >> 4)];

		*place++ = base64_encode[((src[i + 1] & 0xF) << 2) | ((src[i + 2] & 0xC0) >> 6)];
		*place++ = base64_encode[src[i + 2] & 0x3F];
	}
	
	// Account for leftover bits
	if (i < image_binary.size)
	{
		*place++ = base64_encode[(src[i] >> 2) & 0x3F];

		if (i == (image_binary.size - 1))
		{
			*place++ = base64_encode[((src[i] & 0x3) << 4)];
			// Convention for leftover bit
			*place++ = '=';
		}
		else
		{
			*place++ = base64_encode[((src[i] & 0x3) << 4) | ((src[i + 1] & 0xF0) >> 4)];
			*place++ = base64_encode[((src[i + 1] & 0xF) << 2)];
		}
		// Convention for leftover bit
		*place++ = '=';
	}

	// Terminate encoded string
	*place++ = '\0';

	curl_global_cleanup();

	return (encoded);
}
