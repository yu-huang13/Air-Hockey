#include "HandleError.h"


const int HandleError::FILE_OPEN_ERROR = 1;
const int HandleError::NOT_BMP_ERROR = FILE_OPEN_ERROR + 1;
const int HandleError::BMP_BI_BIT_Count_ERROR = NOT_BMP_ERROR + 1;
const int HandleError::BMP_DIVISIBLEBY_4_ERROR = BMP_BI_BIT_Count_ERROR + 1;
const int HandleError::READ_BMP_ERROR = BMP_DIVISIBLEBY_4_ERROR + 1;
const int HandleError::DISPLAYER_INIT_ERROR = READ_BMP_ERROR + 1;
const int HandleError::SAVE_BMP_ERROR = DISPLAYER_INIT_ERROR + 1;
const int HandleError::ARGC_ERROR = SAVE_BMP_ERROR + 1;
const int HandleError::GL_GEN_TEXTURES_ERROR = ARGC_ERROR + 1;
const int HandleError::TEXTURE_NOT_LOAD_ERROR = GL_GEN_TEXTURES_ERROR + 1;

void HandleError::handle(int error_num){
		switch(error_num){
			case FILE_OPEN_ERROR: 
				cout << "failed to open file!" << endl; 
				break;
			case NOT_BMP_ERROR: 
				cout << "file is not bmp!" << endl; 
				break;
			case BMP_BI_BIT_Count_ERROR:
				cout << "biBitCount is not 24" << endl;
				break;
			case BMP_DIVISIBLEBY_4_ERROR: 
				cout << "biWidth is not divisible by 4!" << endl;
				break;
			case READ_BMP_ERROR:
				cout << "failed to read bmp!" << endl;
				break;
			case DISPLAYER_INIT_ERROR:
				cout << "failed to init displayer!" << endl;
				break;
			case SAVE_BMP_ERROR:
				cout << "failed to save bmp!" << endl;
				break;
			case ARGC_ERROR:
				cout << "format: repos.exe filename alpha" << endl;
				break;
			case GL_GEN_TEXTURES_ERROR:
				cout << "failed to generate texture ID!" << endl;
				break;
			case TEXTURE_NOT_LOAD_ERROR:
				cout << "texture is not loaded!" << endl;
				break;
		}
	}