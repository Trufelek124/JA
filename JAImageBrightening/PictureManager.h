#ifndef PICTUREMANAGER_H
#define PICTUREMANAGER_H

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <jpeglib.h>    
#include <jerror.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

typedef void(__cdecl *brightenImage)(INT32, double*, double*, double);


struct Picture
{
	double* inArray;
	double* outArray;
	INT32 width;
	INT32 height;
	INT32 size;
};

class PictureManager
{
public:
	PictureManager(char * filePathVar, char * filePathOutVar, bool asmUse, float multipilerVar);
	virtual ~PictureManager();

	bool openPictureAndGetRGBVector();
	bool brightenImageFun();
	bool savePicture();

protected:

private:
	//Program variables
	const char * filePath; //file path to in file
	const char * filePathOut; //file path to out file
	bool useAsm; //usage of asm/c++ dll
	float multipiler;
	Picture * temp;

	//Picture variables
	std::vector<int> rgb; //rgb vector for pictore
	unsigned char a, r, g, b; //alpha, red, green and blue values to read from file
	int width, height; //width and height od file

	//Picture read.write variables
	FILE * infile;        //source file
	struct jpeg_decompress_struct cinfo; //variable for reading file
	struct jpeg_error_mgr jerr; //error variable if any occures
	unsigned char* bytes; //bytes array to write file
	JSAMPARRAY pJpegBuffer; //output row buffer
	int row_stride;       //physical row width in output buffer 

	//Dll variables
	HINSTANCE hGetProcIDDLL; //dynamic loading of library
	brightenImage function; //dll function
};

#endif // PICTUREMANAGER_H
