#ifdef JACPP_EXPORTS
#define JACPP_API _declspec (dllexport)
#else
#define JACPP_API _declspec (dllimport)
#endif

extern "C" JACPP_API void brightenImage(unsigned char* inArray, unsigned char* outArray, int mainSize, float multiplier);