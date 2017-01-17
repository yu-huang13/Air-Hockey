#ifndef HANDLEERROR_H
#define HANDLEERROR_H

#include <iostream>
#include <cstring>
using namespace std;

/**
* ¥ÌŒÛ¥¶¿Ì¿‡
*/
class HandleError{
public:
	static const int FILE_OPEN_ERROR;
	static const int NOT_BMP_ERROR;
	static const int BMP_BI_BIT_Count_ERROR;
	static const int BMP_DIVISIBLEBY_4_ERROR;
	static const int READ_BMP_ERROR;
	static const int DISPLAYER_INIT_ERROR;
	static const int SAVE_BMP_ERROR;
	static const int ARGC_ERROR;
	static const int GL_GEN_TEXTURES_ERROR;
	static const int TEXTURE_NOT_LOAD_ERROR;
	
	static void handle(int error_num);
private:
	
};


#endif