// JAApp.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <windows.h>
#include <iostream>
//#define cimg_use_jpeg
//#include "CImg.h"
//using namespace cimg_library;
#include <jpeglib.h>    
#include <jerror.h>
#include <vector>
#include <string.h>

extern "C" int _stdcall MyProc1(DWORD x, DWORD y);

int main() {

	//CImg<unsigned char> img("C:\\Users\\admin\\Documents\\ja\\jpeg-9b\\testimg.jpg");
	//img.display("Image");

	std::vector<int> red;
	std::vector<int> green;
	std::vector<int> blue;

	unsigned char a, r, g, b;
	int width, height;
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	const char * filePath;
	const char * filePathOut;
	filePath = "C:\\Users\\User\\Documents\\studia\\ja\\jpeg-build\\jpeg-6b\\testoutt.jpg";
	filePathOut = "C:\\Users\\User\\Documents\\studia\\ja\\jpeg-build\\jpeg-6b\\testout.jpg";
	FILE * infile;        /* source file */
	JSAMPARRAY pJpegBuffer;       /* Output row buffer */
	int row_stride;       /* physical row width in output buffer */
	if ((infile = fopen(filePath, "rb")) == NULL) {
		fprintf(stderr, "can't open %s\n", filePath);
		return 0;
	}
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, infile);
	(void)jpeg_read_header(&cinfo, TRUE);
	(void)jpeg_start_decompress(&cinfo);
	width = cinfo.output_width;
	height = cinfo.output_height;

	unsigned char * pDummy = new unsigned char[width*height * 4];
	unsigned char * pTest = pDummy;
	if (!pDummy) {
		printf("NO MEM FOR JPEG CONVERT!\n");
		return 0;
	}
	row_stride = width * cinfo.output_components;
	pJpegBuffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr)&cinfo, JPOOL_IMAGE, row_stride, 1);

	while (cinfo.output_scanline < cinfo.output_height) {
		(void)jpeg_read_scanlines(&cinfo, pJpegBuffer, 1);
		for (int x = 0; x < width; x++) {
			a = 0; // alpha value is not supported on jpg
			r = pJpegBuffer[0][cinfo.output_components * x];
			if (cinfo.output_components > 2) {
				g = pJpegBuffer[0][cinfo.output_components * x + 1];
				b = pJpegBuffer[0][cinfo.output_components * x + 2];
			}
			else {
				g = r;
				b = r;
			}
		//	*(pDummy++) = b;
			//*(pDummy++) = g;
			//*(pDummy++) = r;
			*(pDummy++) = a;
			red.push_back(r);
			green.push_back(g);
			blue.push_back(b);
			//std::cout << (int)r << ", ";
			//std::cout << (int)g << ", ";
			//std::cout << (int)b << " /";
		}
	}
	fclose(infile);
	(void)jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	int* aaa = (int*)pTest;

	std::cout << "Height: " << height << ", width: " << width << "\n";
	std::cout << pTest << "\n";




	save_jpg_to_file(filePathOut, width, height);

	int k = 3, w = 4, c = 0;
	c = MyProc1(k, w); // wywo³anie procedury asemblerowej z biblioteki
	std::cout << c << "\n";

	return 0;
}

bool save_jpg_to_file(const char *file_name, int width, int height) {
	struct jpeg_compress_struct cinfo;

	struct jpeg_error_mgr jerr;

	FILE * outfile;
	JSAMPROW row_pointer[1];
	int row;

	JSAMPLE * image_buffer;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);

	if ((outfile = fopen(file_name, "wb")) == NULL) {
		fprintf(stderr, "can't open %s\n", file_name);
		return false;
	}

	jpeg_stdio_dest(&cinfo, outfile);


	cinfo.image_width = width;
	cinfo.image_height = height;
	cinfo.input_components = 3;
	cinfo.in_color_space = JCS_RGB;

	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, 100, TRUE);

	jpeg_start_compress(&cinfo, TRUE);

	unsigned char bytes[3000]; //tutaj wielkosc

	while (cinfo.next_scanline < cinfo.image_height) {
		for (int i = 0; i < width; i += 3){
			

			//tutaj dodaæ moje

			bytes[i] = static_cast<int>(colorData.red() * 255) & 0xff;
			bytes[i + 1] = static_cast<int>(colorData.green() * 255) & 0xff;
			bytes[i + 2] = static_cast<int>(colorData.blue() * 255) & 0xff;
		}
		row_pointer[0] = bytes;
		(void)jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	jpeg_finish_compress(&cinfo);
	fclose(outfile);
	jpeg_destroy_compress(&cinfo);

	std::cout << "Done" << std::endl;

	return true;
}