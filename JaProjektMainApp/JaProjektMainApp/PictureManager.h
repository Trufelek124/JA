#ifndef PICTUREMANAGER_H
#define PICTUREMANAGER_H

#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <thread>
#include <mutex>
#include <ctime>

using namespace std;
typedef void(__cdecl* brightenImage)(unsigned char*, unsigned char*, INT32, float);


struct Picture
{
	unsigned char* inArray;
	unsigned char* outArray;
	INT32 size;
};

struct threadParam
{
	int* current;
	std::vector<Picture> pictures;
	HANDLE* pMutex;
	brightenImage function;
	float multiplierTP;
};

unsigned int __stdcall threadFunction(void* vParam);
void __stdcall appendLogs(string data);

class PictureManager
{
public:
	PictureManager(char* filePathVar, char* filePathOutVar, bool asmUse, int threadsQuantity, float multipilerVar);
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
	unsigned int* buffer;
	int threadCount;

	int current = 0;
	threadParam* params;

	//Picture variables
	std::vector<unsigned char> rgbByte; //rgb byte vector for picture
	std::vector<unsigned char> rgb2Byte; //rgb byte vector for picture
	std::vector<unsigned char> rgbByteSave; //rgb byte vector for picture
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
