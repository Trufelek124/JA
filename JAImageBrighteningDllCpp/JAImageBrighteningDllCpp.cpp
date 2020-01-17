// JAImageBrighteningDllCpp.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include "JAImageBrighteningDllCpp.h"

JAIMAGEBRIGHTENINGDLLCPP_API int*  __cdecl brightenImage(INT32 length, int* in, int* out, float mutiplier)
{
	*out = 0;
	int temp = 0;
	for (int i = 0; i <  length - 1; i++)
	{
		temp = in[i] * mutiplier;
		if (temp > 255){
			temp = 255;
		}
		else if (temp < 0){
			temp = 0;
		}
		out[i] = temp;
	}
	return out;
}
