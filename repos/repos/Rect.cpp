#include "Rect.h"

Rect::Rect(){
	textureID = 0;
}

Rect::Rect(Vector3 pos, Vector3 N, Vector3 X, Vector3 Y, double xLen, double yLen, GLubyte* color){
	setParameter(pos, N, X, Y, xLen, yLen, color);
	textureID = 0;
}

Rect::~Rect(){
}

/**
* 设置参数
*/
void Rect::setParameter(Vector3 pos, Vector3 N, Vector3 X, Vector3 Y, double xLen, double yLen, GLubyte* color){
	this->pos = pos;
	this->N = N;
	this->X = X;
	this->Y = Y;
	this->xLen = xLen;
	this->yLen = yLen;

	Vector3 halfX = X * xLen * 0.5;
	Vector3 halfY = Y * yLen * 0.5;
	points[0] = pos + halfX + halfY;
	points[1] = pos - halfX + halfY;
	points[2] =  pos -halfX - halfY;
	points[3] = pos + halfX - halfY;
	this->color = color;
}

/**
* 载入纹理
*/
bool Rect::loadTexture(const char* bmpName){
	
	texImage.loadFromBmp(bmpName);
	glGenTextures(1, &textureID);
	if (textureID == 0){
		HandleError::handle(HandleError::GL_GEN_TEXTURES_ERROR);
		return false;
	}
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texImage.width, texImage.height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, texImage.data);
	coordX[0] = 0.0; coordY[0] = 0.0;
	coordX[1] = 10.0; coordY[1] = 0.0;
	coordX[2] = 10.0; coordY[2] = 10.0;
	coordX[3] = 0.0; coordY[3] = 10.0;

	return true;
}

/**
* 使用Color绘制矩形面
*/
void Rect::draw(){
	glPushMatrix();
	glColor3ubv(color);
    glBegin(GL_QUADS);
	for (int i = 0; i < 4; ++i)
		glVertex3d(points[i].x, points[i].y, points[i].z);
    glEnd();
	
	glPopMatrix();
}

/**
* 使用纹理绘制矩形面
*/
void Rect::drawWithTex(){
	if (textureID == 0){
		HandleError::handle(HandleError::TEXTURE_NOT_LOAD_ERROR);
		return;
	}
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);
	for (int i = 0; i < 4; ++i){
		glTexCoord2d(coordX[i], coordY[i]);
		glVertex3d(points[i].x, points[i].y, points[i].z);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}