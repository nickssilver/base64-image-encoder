# base64-image-encoder
<p align="center">
<img src="https://cdn.shopify.com/s/files/1/0204/4104/products/20180517-20180517-P1260614_600x.jpg?v=1528506358">
</p>
<hr />
Base64 image encoder written in C.
## Repo Description
Base64 is an encoding algorithm that converts any characters, binary data, and even images or sound files into a readable string, which can be saved or transported over the network without data loss. The characters generated from Base64 encoding consist of Latin letters, digits, plus, and slash. Base64 is most commonly used as a 'MIME' (Multipurpose Internet Mail Extensions) transfer encoding for email.

Base64 images are primarily used to embed image data within other formats like HTML, CSS, or JSON. By including image data within an HTML document, the browser doesn't need to make an additional web request to fetch the file, since the image is already embedded in the HTML document. A Base64 representation of an image is larger than a separate image and the string gets very long for large images. You should primarily use Base64 for small images and always test both embedded and external images to see what works best.

Once converted to Base64, encoded image data will look similar to this (shortened for simplicity):
```
iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAMAAABEpIrGAAAABGdBTUEAALGPC/xhBQAAAAFzUkdCAK7OHOkAAAAgY0hSTQAAeiYAAICEAAD6AAAAgOgAAHUwAADqYAAAOpgwnLpRPAAA...
```
The string can be used instead of an URL in the src attribute of the img element in HTML:
```
<img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAALQAAAC0CAYAAAA9zQYyAAAABGdBTUEAALGPC/xhBQAAAAlwSFlzA..." />
```
Or you can insert the string as a background-image in CSS:
```
background-image: url("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAALQAAAC0CAYAAAA9zQYyAAAABGdBTUEAALGPC/xhBQAAAAlwSFlzA...");
```
Other file types like XML and JSON also supports Base64 encoded images. Start by uploading an image file above and play with the different possibilities.

## Assumptions

You are building and running this application on a Debian-based Linux machine. Other distros and operating systems may have varied results. 

## Dependencies and prerequisites
Have libcurl package installed. To install:

`$ sudo apt-get install libcurl4-openssl-dev`

Download and extract the libcurl library in the same location where you will clone the github repository

[Download](https://curl.se/download.html)

## Installing the application locally
Clone the repository:

`$ git clone https://github.com/nickssilver/base64-image-encoder.git`

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
