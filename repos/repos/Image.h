#ifndef IMAGE_H
#define IMAGE_H

#include <windows.h>	//BITMAPFILEHEADER
#include <cstdio>		//FILE
#include <iostream>
#include <algorithm>	//swap
#include <cmath>

#include "HandleError.h"

using namespace std;

/**
* bmp文件读取类
*/
class Image
{
public:
	Image();
	Image(int w, int h);
	Image(unsigned char* d, int w, int h);
	~Image();
	bool loadFromBmp(const char* filename);
	bool saveBmp(const char* filename);
	void getPixel(int idx, int idy, unsigned char& r, unsigned char& g, unsigned char& b);
	void setPixel(int idx, int idy, unsigned char r, unsigned char g, unsigned char b);
	void output();
	void outputLine(int idy);
	void output(int idx1, int idy1, int idx2, int idy2);

	unsigned char* data;
	int width;
	int height;

private:
	int getPos(const int &idx, const int &idy);
	boolean SaveDIB24(const char* lpszFileName, DWORD dwWidth, DWORD dwHeight, void* lpvBits);
};

#endif