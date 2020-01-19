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
#include <thread>

typedef int*(__cdecl *brightenImage)(INT32, int*, int*, float);

using namespace std;

struct threadParam
{
	int* current;
	vector<int>* inArray;
	HANDLE* pMutex;
	brightenImage function;
};

class PictureManager
{
public:
	PictureManager(char * filePathVar, char * filePathOutVar, bool asmUse, float multipilerVar, int threadCountVar);
	virtual ~PictureManager();

	bool setup();
	bool openPictureAndGetRGBVector();
	bool threads();
	bool brightenImageFun();
	bool savePicture();

protected:

private:
	//Program variables
	const char * filePath; //file path to in file
	const char * filePathOut; //file path to out file
	bool useAsm; //usage of asm/c++ dll
	float multipiler;
	int threadCount;
	int current;

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
