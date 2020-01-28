#include "pch.h"
#include "JaProjektDllCpp.h"
#include <Windows.h>


using namespace std;

void brightenImage(unsigned char* inArray, unsigned char* outArray, int mainSize, float multiplier)
{

	for (int i = 0; i < mainSize; i++) {
		int temp = (int)inArray[i];
		float temp2 = temp * multiplier;
		temp = (int) temp2;
		if (temp > 255) {
			temp = 255;
		}
		if (temp < 0) {
			temp = 0;
		}
		outArray[i] = (unsigned char)temp;
	}
}