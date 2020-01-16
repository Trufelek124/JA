#ifndef PICTUREMANAGER_H
#define PICTUREMANAGER_H

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <jpeglib.h>    
#include <jerror.h>
#include <vector>
#include <string.h>


class PictureManager
{
public:
	PictureManager();
	virtual ~PictureManager();

	bool openPictureAndGetRGBVector();
	bool brightenImageCPP();
	bool savePicture();

protected:

private:
	std::vector<int> rgb; //rgb vector
	unsigned char a, r, g, b;
	int width, height;
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	const char * filePath;
	const char * filePathOut;
	unsigned char* bytes;
	FILE * infile;        /* source file */
	JSAMPARRAY pJpegBuffer;       /* Output row buffer */
	int row_stride;       /* physical row width in output buffer */
};

#endif // PICTUREMANAGER_H
