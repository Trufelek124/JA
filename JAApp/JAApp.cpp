#include "stdafx.h"
#include "PictureManager.h"

extern "C" int _stdcall MyProc1(DWORD x, DWORD y);

int main() {

	PictureManager* pManager = new PictureManager();


	pManager->openPictureAndGetRGBVector();
	pManager->brightenImageCPP();
	pManager->savePicture();

	int k = 3, w = 4, c = 0;
	c = MyProc1(k, w); // wywołanie procedury asemblerowej z biblioteki
	std::cout << c << "\n";

	return 0;
}