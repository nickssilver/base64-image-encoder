# base64-image-encoder
Base64 image encoder written in C.

## Assumptions

You are building and running this application on a Debian-based Linux machine. Other distros and operating systems may have varied results. 

## Dependencies and prerequisites
Have libcurl package installed. To install:

`$ sudo apt-get install libcurl4-openssl-dev`

Download and extract the libcurl library in the same location where you will clone the github repository

[Download](https://curl.se/download.html)

## Installing the application locally
Clone the repository:

`$ git clone https://github.com/dfcybhzb/base64-image-encoder.git`

In the root directory of the repository, set the `LD_LIBRARY_PATH` environment variable to the current directory:

`$ export LD_LIBRARY_PATH=$(pwd)`

Create the object file:

`$ gcc -c -Wall -Werror -fpic libencode.c`

Create a shared library from the object file:

`$ gcc -shared -o libencode.so libencode.o`

## Running the application locally
Compile the executable:

`$ gcc -L$(pwd) -Wall -o encode main.c -lencode -lcurl`

Move empty file to write into root directory, or create it:

`$ touch filename`

Run the executable with an image link and file name:

`$ ./encode https://www.image.png filename`

 
# base64-image-encoder
