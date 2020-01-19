// JAImageBrighteningDllCpp.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include "JAImageBrighteningDllCpp.h"

JAIMAGEBRIGHTENINGDLLCPP_API void  __cdecl brightenImage(INT32 length, double* in, double* out, double mutiplier)
{
	*out = 0;
	double temp = 0;
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
}
