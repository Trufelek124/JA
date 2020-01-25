#include <iostream>
#include "PictureManager.h"

int main(int argc, char* argv[])
{
	PictureManager* pManager = new PictureManager();
	pManager->openPictureAndGetByteArray();
	pManager->brightenImageFun();
	pManager->savePicture();
	return 0;
}