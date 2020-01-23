#include "PictureManager.h"

PictureManager::PictureManager(char* filePathVar, char* filePathOutVar, bool asmUse, float multipilerVar) {
	filePath = filePathVar; //"C:\\Users\\User\\Documents\\studia\\ja\\jpeg-build\\jpeg-6b\\testoutt.jpg";
	filePathOut = filePathOutVar; //"C:\\Users\\User\\Documents\\studia\\ja\\jpeg-build\\jpeg-6b\\testout.jpg";
	useAsm = asmUse;
	multipiler = multipilerVar;
}

PictureManager::~PictureManager() {}

bool PictureManager::openPictureAndGetRGBVector() {
	//TODO OPEN AND read bmp file into rgb array
	return true;
}

bool PictureManager::brightenImageFun() {
	if (useAsm)
	{
		hGetProcIDDLL = LoadLibrary(TEXT("JAProjektDllAsm.dll"));
	}
	else
	{
		hGetProcIDDLL = LoadLibrary(TEXT("JAProjektDllCpp.dll"));
	}

	if (!hGetProcIDDLL) {
		return false;
	}
	function = (brightenImage)GetProcAddress(hGetProcIDDLL, "brightenImage");
	if (!function) {
		return false;
	}

	std::vector<int> rgbAfterChange;
	std::cout << "jestem\n";
	function(temp->size, temp->inArray, temp->outArray, (double)multipiler); //usage of dll function

	std::cout << "jestem\n";

	for (int i = 0; i < temp->size; i++) {
		rgbAfterChange.push_back(temp->outArray[i]);
	}

	rgb = rgbAfterChange;
	return true;

}

bool PictureManager::savePicture() {
	//works with bmp
	struct jpeg_compress_struct cinfo;

	struct jpeg_error_mgr jerr;

	FILE* outfile;
	JSAMPROW row_pointer[1];
	int row;

	JSAMPLE* image_buffer;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);

	if ((outfile = fopen(filePathOut, "wb")) == NULL) {
		fprintf(stderr, "can't open %s\n", filePathOut);
		return false;
	}

	jpeg_stdio_dest(&cinfo, outfile);


	cinfo.image_width = width;
	cinfo.image_height = height;
	cinfo.input_components = 3;
	cinfo.in_color_space = JCS_RGB;

	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, 100, TRUE);

	jpeg_start_compress(&cinfo, TRUE);

	bytes = new unsigned char[width * 3]; //buffer size

	int v = 0;

	while (cinfo.next_scanline < cinfo.image_height) {
		for (int i = 0; i < width * 3; i += 3) {
			bytes[i] = static_cast<int>(rgb.at(v)) & 0xff;
			bytes[i + 1] = static_cast<int>(rgb.at(v + 1)) & 0xff;
			bytes[i + 2] = static_cast<int>(rgb.at(v + 2)) & 0xff;
			v += 3;
		}
		row_pointer[0] = bytes;
		(void)jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	jpeg_finish_compress(&cinfo);
	fclose(outfile);
	jpeg_destroy_compress(&cinfo);

	std::cout << "\n" << "Done" << std::endl;

	return true;
}