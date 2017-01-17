#include "Image.h"

Image::Image(){}

Image::Image(int w, int h){
	width = w;
	height = h;
	data = new unsigned char[width*height*3];
}

Image::Image(unsigned char* d, int w, int h){
	data = d;
	width = w;
	height = h;
}

Image::~Image(){
	if (data)
		delete []data;
}

/**
* ȡ��(idx, idy)����r��g��bֵ
*/
void Image::getPixel(int idx, int idy, unsigned char& r, unsigned char& g, unsigned char& b){
	int pos = getPos(idx, idy);
	r = data[pos+2];
	g = data[pos+1];
	b = data[pos];
}

/**
* ����(idx, idy)����r��g��bֵ
*/
void Image::setPixel(int idx, int idy, unsigned char r, unsigned char g, unsigned char b){
	int pos = getPos(idx, idy);
	data[pos] = b;
	data[pos+1] = g;
	data[pos+2] = r;
}

/**
* ��������������ص��������е�λ��
*/
int Image::getPos(const int &idx, const int &idy){
	return (idy * width + idx) * 3;
}

/**
* ��ȡbmp�ļ����ɹ�����true��ʧ�ܷ���false
*/
bool Image::loadFromBmp(const char* filename){
	unsigned char tempRGB;
	
	//���ļ�
	FILE *fp;
	fp = fopen(filename, "rb");	
	if (fp == NULL){
		HandleError::handle(HandleError::FILE_OPEN_ERROR);
		return false;
	}
		

	//��ȡbmFileHeader
	BITMAPFILEHEADER bmFileHeader;	
	fread(&bmFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);	
	if (bmFileHeader.bfType != (WORD)('M'<<8|'B')){	//����Ƿ�ΪBMP�ļ�
		HandleError::handle(HandleError::NOT_BMP_ERROR);
		return false;
	}

	//��ȡbmInfoHeader
	BITMAPINFOHEADER bmInfoHeader;
	fread(&bmInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);	
	if (bmInfoHeader.biBitCount != 24){	//���ش洢λ����Ϊ24
		HandleError::handle(HandleError::BMP_BI_BIT_Count_ERROR);
		return false;
	}

	//��ȡͼƬ����
	if (bmInfoHeader.biWidth % 4 != 0){	//bmp�Ŀ��Ҫ��4����
		HandleError::handle(HandleError::BMP_DIVISIBLEBY_4_ERROR);
		return false;
	}
	width = bmInfoHeader.biWidth; 
	height = bmInfoHeader.biHeight;
	int length = width * height * 3;
	data = new unsigned char[length];

	fseek(fp, bmFileHeader.bfOffBits, SEEK_SET);	//���ļ�ָ���ƶ���ͼƬ���ݴ�
	fread(data, 1, length, fp);

	fclose(fp);
	return true;
}

/**
* ����bmpͼ��
*/
bool Image::saveBmp(const char* filename){
	return SaveDIB24(filename, width, height, data);
}

/**
* ����bmpͼ��
*/
boolean Image::SaveDIB24(const char* lpszFileName, DWORD dwWidth, DWORD dwHeight, void* lpvBits)
{
	HANDLE hFile;

	BOOL bOK;
	DWORD dwNumWritten;
	DWORD dwWidthAlign;
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;

	__try {

		hFile = CreateFile(
			lpszFileName,
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			0,
			NULL
		);
		if (hFile==INVALID_HANDLE_VALUE) return 0;

		dwWidthAlign = ((dwWidth*sizeof(RGBTRIPLE)+3)/4)*4;

		// BITMAPFILEHEADDER
		bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
		bmfh.bfType = ('B'|'M'<<8);
		bmfh.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
		bmfh.bfSize = bmfh.bfOffBits + dwWidthAlign*dwHeight;

		bOK = WriteFile(
			hFile,
			&bmfh,
			sizeof(bmfh),
			&dwNumWritten,
			NULL
		);
		if (!bOK) return 0;


		bmih.biSize = sizeof(BITMAPINFOHEADER);
		bmih.biWidth = dwWidth;
		bmih.biHeight = dwHeight;
		bmih.biPlanes = 1;
		bmih.biBitCount = 24;
		bmih.biCompression = 0;
		bmih.biSizeImage = 0;
		bmih.biXPelsPerMeter = 0;
		bmih.biYPelsPerMeter = 0;
		bmih.biClrUsed = 0;
		bmih.biClrImportant = 0;

		bOK = WriteFile(
			hFile,
			&bmih,
			sizeof(bmih),
			&dwNumWritten,
			NULL
		);
		if (!bOK) return 0;

		bOK = WriteFile(
			hFile,
			lpvBits,
			dwWidthAlign*dwHeight,
			&dwNumWritten,
			NULL
		);
		if (!bOK) return 0;
	
	} __finally {

		CloseHandle(hFile);

	}
	
	return 1;
}

/**
* ������������½�����(idx1, idy1)�����Ͻ�����(idx2, idy2)������������rgb
*/
void Image::output(int idx1, int idy1, int idx2, int idy2){
	unsigned char r, g, b;
	for (int j = idy1; j < idy2; ++j){
		for (int i = idx1; i < idx2; ++i){
			//cout << i << " " << j << endl;
			getPixel(i, j, r, g, b);
			cout << "[" << (int)r << ", " << (int)g << ", " << (int)b << "] ";
		}
		cout << endl;
	}
}

/**
* �������ͼ�����
*/
void Image::output(){
	output(0, 0, width, height);
}

/**
* ���idy�е�rgb
*/
void Image::outputLine(int idy){
	output(0, idy, width, idy+1);
}