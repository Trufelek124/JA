#include <iostream>
#include <string>
#include "PictureManager.h"

using namespace std;
string filePathInS;
string filePathOutS;
string dllInUse;
bool dllAsm = false;
int threads;
string multiplierS;
float multiplier;

void menu() {
	cout << "Please provide input file path: ";
	cin >> filePathInS;
	cout << "\nPlease provide output file path: ";
	cin >> filePathOutS;
	cout << "\nPlease provide dll name to use (ASM\\CPP): ";
	cin >> dllInUse;
	if (dllInUse == "ASM" || dllInUse == "Asm" || dllInUse == "asm") {
		dllAsm = true;
	}
	cout << "\nPlease provide Number of threads (1 - 64): ";
	cin >> threads;
	cout << "\nPlease type in multiplier (more than 0): ";
	cin >> multiplierS;
	multiplier = stof(multiplierS);
	if (multiplier < 0) {
		multiplier = 0.0f;
	}
}

int main(int argc, char* argv[])
{

	menu();
	
	int n = filePathInS.length();
	int m = filePathOutS.length();
	char* filePathIn = new char[n+1];
	char* filePathOut = new char[m + 1];
	strcpy(filePathIn, filePathInS.c_str());
	strcpy(filePathOut, filePathOutS.c_str());

	PictureManager* pManager = new PictureManager(filePathIn, filePathOut, dllAsm, threads, multiplier);
	//PictureManager* pManager = new PictureManager();
	pManager->openPictureAndGetByteArray();
	pManager->brightenImageFun();
	pManager->savePicture();
	return 0;
}