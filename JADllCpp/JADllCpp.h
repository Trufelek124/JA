// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the JADLLCPP_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// JADLLCPP_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef JADLLCPP_EXPORTS
#define JADLLCPP_API __declspec(dllexport)
#else
#define JADLLCPP_API __declspec(dllimport)
#endif

extern "C" JADLLCPP_API int* __cdecl brightenImage(INT32 length, int* in, int* out, float mutiplier);

