// JAApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include "jpeglib.h"

extern "C" int _stdcall MyProc1(DWORD x, DWORD y);

int main() {
	int x = 3, y = 4, z = 0;
	int a;
	z = MyProc1(x, y); // wywołanie procedury asemblerowej z biblioteki
	//std::cout << z << "\n";
	//std::cin >> a;
	return 0;
}