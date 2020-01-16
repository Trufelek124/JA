#include "stdafx.h"
#include "PictureManager.h"

PictureManager::PictureManager(){
	filePath = "C:\\Users\\User\\Documents\\studia\\ja\\jpeg-build\\jpeg-6b\\testoutt.jpg";
	filePathOut = "C:\\Users\\User\\Documents\\studia\\ja\\jpeg-build\\jpeg-6b\\testout.jpg";
}

PictureManager::~PictureManager(){}

bool PictureManager::openPictureAndGetRGBVector(){

	if ((infile = fopen(filePath, "rb")) == NULL) {
		fprintf(stderr, "can't open %s\n", filePath);
		return false;
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
		return false;
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
			rgb.push_back(r);
			rgb.push_back(g);
			rgb.push_back(b);
		}
	}
	fclose(infile);
	(void)jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	int* aaa = (int*)pTest;

	std::cout << "Height: " << height << ", width: " << width << "\n";
	//std::cout << pTest << "\n";

	return true;
}



bool PictureManager::savePicture() {
	struct jpeg_compress_struct cinfo;

	struct jpeg_error_mgr jerr;

	FILE * outfile;
	JSAMPROW row_pointer[1];
	int row;

	JSAMPLE * image_buffer;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);

	if ((outfile = fopen(filePathOut, "wb")) == NULL) {
		fprintf(stderr, "can't open %s\n", filePathOut);
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

	unsigned char* bytes = new unsigned char[width * 3]; //tutaj wielkosc

	int v = 0;

	while (cinfo.next_scanline < cinfo.image_height) {
		for (int i = 0; i < width*3; i += 3){
			bytes[i] = static_cast<int>(rgb.at(v)) & 0xff;
			bytes[i + 1] = static_cast<int>(rgb.at(v + 1)) & 0xff;
			bytes[i + 2] = static_cast<int>(rgb.at(v + 2)) & 0xff;
			v += 3;
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