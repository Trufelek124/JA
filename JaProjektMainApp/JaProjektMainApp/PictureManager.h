#ifndef PICTUREMANAGER_H
#define PICTUREMANAGER_H

#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

typedef void(__cdecl* brightenImage)(unsigned char*, unsigned char*, INT32, float);


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
	PictureManager(char* filePathVar, char* filePathOutVar, bool asmUse, float multipilerVar);
	PictureManager();
	virtual ~PictureManager();
	bool openPictureAndGetByteArray();
	bool brightenImageFun();
	bool savePicture();

protected:

private:
	//Program variables
	const char* filePath; //file path to in file
	const char* filePathOut; //file path to out file
	bool useAsm; //usage of asm/c++ dll
	float multipiler;
	Picture* temp;
	unsigned char* image; 
	char* imageSign;
	unsigned int* buffer;

	//Picture variables
	std::vector<int> rgb; //rgb vector for pictore
	std::vector<int> rgb2; //rgb vector for pictore
	std::vector<unsigned char> rgbByte; //rgb vector for pictore
	std::vector<unsigned char> rgb2Byte; //rgb vector for pictore
	std::vector<unsigned char> rgbByteSave; //rgb vector for pictore
	unsigned char a, r, g, b; //alpha, red, green and blue values to read from file
	int width, height; //width and height od file
	const int bytesPerPixel = 4; /// red, green, blue
	const int fileHeaderSize = 14;
	const int infoHeaderSize = 40;

	//Picture read.write variables
	FILE* infile;        //source file
	unsigned char* bytes; //bytes array to write file

	//Dll variables
	HINSTANCE hGetProcIDDLL; //dynamic loading of library
	brightenImage function; //dll function
};

#endif // PICTUREMANAGER_H
