#include "stdafx.h"
#include "PictureManager.h"

extern "C" int _stdcall brightenImage2(DWORD x, DWORD y);

int main() {

	PictureManager* pManager = new PictureManager();

	pManager->openPictureAndGetRGBVector();
	pManager->brightenImageFun();
	pManager->savePicture();

	int k = 3, w = 4, c = 0;
	c = brightenImage2(k, w); // wywołanie procedury asemblerowej z biblioteki
	std::cout << c << "\n";

	return 0;
}