#include "PictureManager.h"
#include <iostream>
#include <fstream>
#include <array>
#include <thread>
#include <string>
#include <ctime>
#include <Windows.h>
#pragma warning(disable : 4996)

#define headerBMPFile 54

using namespace std;

PictureManager::PictureManager(char* filePathVar, char* filePathOutVar, bool asmUse, float multipilerVar) {
	filePath = filePathVar; //"C:\\Users\\User\\Documents\\studia\\ja\\jpeg-build\\jpeg-6b\\testoutt.jpg";
	filePathOut = filePathOutVar; //"C:\\Users\\User\\Documents\\studia\\ja\\jpeg-build\\jpeg-6b\\testout.jpg";
	useAsm = asmUse;
	multipiler = multipilerVar;
}

PictureManager::PictureManager() {
	filePath = "C:\\BMP\\RGB4.bmp";
	filePathOut = "img.bmp";
	useAsm = false;
	multipiler = 1.2f;
}

PictureManager::~PictureManager() {}

bool PictureManager::openPictureAndGetByteArray() {
	//TODO OPEN AND read bmp file into byte array

		int i;
		FILE* f1 = fopen(filePath, "rb");

		if (f1 == NULL)
			throw "Argument Exception";

		unsigned char info[54];
		fread(info, sizeof(unsigned char), 54, f1); // read the 54-byte header

		// extract image height and width from header
		width = *(int*)&info[18];
		height = *(int*)&info[22];

	/*	cout << endl;
		cout << "  Name: " << filePath << endl;
		cout << " Width: " << width << endl;
		cout << "Height: " << height << endl;*/

		int row_padded = (width * 3 + 3) & (~3);
		unsigned char* data = new unsigned char[row_padded];
		unsigned char tmp;

		for (int i = 0; i < height; i++)
		{
			fread(data, sizeof(unsigned char), row_padded, f1);
			for (int j = 0; j < width * 3; j += 3)
			{
				rgb2Byte.push_back((unsigned char)data[j]);
				rgb2Byte.push_back((unsigned char)data[j + 1]);
				rgb2Byte.push_back((unsigned char)data[j + 2]);
			}
		}

		//TODO odwróciæ wektor wierszami - najpierw ostatni wiersz 
		int rowLength = rgb2Byte.size() / height;
		for (int k = 1; k <= height; k++) {
			for (int j = rowLength * (height - k); j < rowLength * (height - k + 1); j++) {
				rgbByte.push_back(rgb2Byte.at(j));
			}
		}


		fclose(f1);

	return true;
}

bool PictureManager::brightenImageFun() {

	//rgb vector to unsignef char array to funckja to rbg vrctor


	//if (useAsm)
	//{
	//	hGetProcIDDLL = LoadLibrary(TEXT("JAProjektDllAsm.dll"));
	//}
	//else
	//{
		hGetProcIDDLL = LoadLibrary(TEXT("JAProjektDllCpp.dll"));
	////}

	if (!hGetProcIDDLL) {
		return false;
	}

	function = (brightenImage)GetProcAddress(hGetProcIDDLL, "brightenImage");
	if (!function) {
		return false;
	}

	unsigned char* inArray = new unsigned char[rgbByte.size()];
	unsigned char* outArray = new unsigned char[rgbByte.size()];

	for (int i = 0; i < rgbByte.size(); i++) {
		inArray[i] = rgbByte.at(i);
	}

	function(inArray, outArray, rgbByte.size(), (float)multipiler);


	for (int i = 0; i < rgbByte.size(); i++) {
		rgbByteSave.push_back(outArray[i]);
	}

		//brightenImage();

	//std::vector<int> rgbAfterChange;
	//std::cout << "jestem\n";
	//function(temp->size, temp->inArray, temp->outArray, (double)multipiler); //usage of dll function

	//std::cout << "jestem\n";

	//for (int i = 0; i < temp->size; i++) {
	//	rgbAfterChange.push_back(temp->outArray[i]);
	//}

	//rgb = rgbAfterChange;
	return true;

}

bool PictureManager::savePicture() {
	//works with bmp

	FILE* f;
	unsigned char* img = NULL;
	int filesize = 54 + 3 * width * height;  //w is your image width, h is image height, both int

	img = (unsigned char*)malloc(3 * width * height);
	memset(img, 0, 3 * width * height);
	int s = 0;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			img[s] = rgbByteSave.at(s);
			img[s + 1] = rgbByteSave.at(s + 1);
			img[s + 2] = rgbByteSave.at(s + 2);
			s += 3;
		}
	}

	unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
	unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0 };
	unsigned char bmppad[3] = { 0,0,0 };

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(width);
	bmpinfoheader[5] = (unsigned char)(width >> 8);
	bmpinfoheader[6] = (unsigned char)(width >> 16);
	bmpinfoheader[7] = (unsigned char)(width >> 24);
	bmpinfoheader[8] = (unsigned char)(height);
	bmpinfoheader[9] = (unsigned char)(height >> 8);
	bmpinfoheader[10] = (unsigned char)(height >> 16);
	bmpinfoheader[11] = (unsigned char)(height >> 24);

	f = fopen("img.bmp", "wb");
	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);
	for (int i = 0; i < height; i++)
	{
		fwrite(img + (width * (height - i - 1) * 3), 3, width, f);
		fwrite(bmppad, 1, (4 - (width * 3) % 4) % 4, f);
	}

	free(img);
	fclose(f);

	cout << "Done" << endl;

	return true;
}