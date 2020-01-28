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

PictureManager::PictureManager(char* filePathVar, char* filePathOutVar, bool asmUse, int threadsQuantity, float multipilerVar) {
	filePath = filePathVar; //"C:\\Users\\User\\Documents\\studia\\ja\\jpeg-build\\jpeg-6b\\testoutt.jpg";
	filePathOut = filePathOutVar; //"C:\\Users\\User\\Documents\\studia\\ja\\jpeg-build\\jpeg-6b\\testout.jpg";
	useAsm = asmUse;
	multipiler = multipilerVar;
	threadCount = threadsQuantity;
}

PictureManager::PictureManager() {
	filePath = "C:\\BMP\\glowny.bmp";
	filePathOut = "img.bmp";
	useAsm = true;
	multipiler = 1.7f;
	threadCount = 1;
}

PictureManager::~PictureManager() {}

bool PictureManager::openPictureAndGetByteArray() {
	cout << "Reading file\n";
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

	cout << "Brightening picture\n";
	if (useAsm)
	{
		hGetProcIDDLL = LoadLibrary(TEXT("JAProjektDllAsm.dll"));
	}
	else
	{
		hGetProcIDDLL = LoadLibrary(TEXT("JAProjektDllCpp.dll"));
	}

	if (!hGetProcIDDLL) {
		return false;
	}

	function = (brightenImage)GetProcAddress(hGetProcIDDLL, "brightenImage");
	if (!function) {
		return false;
	}


	std::thread** threads = new std::thread * [threadCount];
	params = (threadParam*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
		sizeof(threadParam));
	if (params == NULL)
		return false;


	std::vector<Picture> vPictures;


	int size = rgbByte.size();

	int quantityForThread = (int)(size / threadCount);

	for (int i = 0; i < threadCount; i++) {
		Picture* tmp = new Picture;

		//teraz tablica

		int last = (i + 1) * quantityForThread;

		if (((i + 2) * quantityForThread > size) && ((i + 1) * quantityForThread < size)) {
			last = size;
		}

		int quantity = last - (i * quantityForThread);
		unsigned char* in = new unsigned char[quantity];
		unsigned char* out = new unsigned char[quantity];
		int count = 0;

		for (int j = i * quantityForThread; j < last; j++) {
			in[count] = rgbByte.at(j);
			count++;
		}

		tmp->inArray = in;
		tmp->outArray = out;
		tmp->size = quantity;
		vPictures.push_back(*tmp);
	}

	params->pMutex = (HANDLE*)(new std::mutex());
	params->current = &current;
	params->function = function;
	params->pictures = vPictures;
	params->multiplierTP = multipiler;


	clock_t clck = clock();

	for (int i = 0; i < threadCount; i++)
	{
		threads[i] = new thread(threadFunction, params);

		SetThreadPriority(threads[i]->native_handle(), THREAD_PRIORITY_HIGHEST);
	}

	for (int i = 0; i < threadCount; i++)
	{
		threads[i]->join();
	}
	clck = clock() - clck;

	string dllInUse = "CPP";
	if (useAsm) {
		dllInUse = "ASM";
	}

	string logData = "Execution time: " + to_string(((double)clck) / CLOCKS_PER_SEC)
		+ "\nThreads: " + to_string(threadCount) + "\n"
		+ "Used DLL: " + dllInUse + "\n"
		+ "Image size: " + to_string(width) + "x" + to_string(height) + "\n"
		+ "\n" 
		+ "__________________________________\n";
	appendLogs(logData);

	cout << logData;

	for (int i = 0; i < threadCount; i++)
	{
		Picture temp = params->pictures.at(i);
		for (int j = 0; j < temp.size; j++) {
			rgbByteSave.push_back(temp.outArray[j]);
		//	cout << (int)temp.inArray[j] << " -> " << (int)temp.outArray[j] << "\n";
		}
	}


	return true;

}

unsigned int __stdcall threadFunction(void* vParam)
{

	//std::cout << "jestem2";
	threadParam* params = (threadParam*)vParam;

	while (*params->current < params->pictures.size())
	{
		if (params->pMutex == NULL)
			_endthreadex(0);
		((std::mutex*)(params->pMutex))->lock();
		int index = *(params->current);
		(*params->current)++;
		((std::mutex*)(params->pMutex))->unlock();


		if (index >= params->pictures.size())
		{
			return 0;
		}
		Picture picture = params->pictures.at(index);
		params->function(picture.inArray, picture.outArray, picture.size, params->multiplierTP);

		//for (int i = 0; i < picture.size; i++) {
		//	cout << (int)picture.inArray[i] << " -> " << (int)picture.outArray[i] << "\n";
		//}
		std::vector<unsigned char> rgbAfterChange;

		for (int i = 0; i < picture.size; i++) {
			rgbAfterChange.push_back((int)picture.outArray[i]);
		}

		if (rgbAfterChange.size() < 1) {
			std::cout << "nie uda³o siê :(" << "\n";
			return false;
		}
	}
	return true;
}

bool PictureManager::savePicture() {
	//works with bmp
	cout << "Saving picture\n";

	FILE* f;
	unsigned char* img = NULL;
	int filesize = 54 + 3 * width * height;

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

void appendLogs(string data) {
	ofstream outfile;

	outfile.open("log.txt", std::ios_base::app); // append instead of overwrite
	outfile << data;
}