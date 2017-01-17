#ifndef Rect_H
#define Rect_H

#include <glut.h>

#include "Vector3.h"
#include "Color.h"
#include "Image.h"

/**
* 矩形类
*/
class Rect
{
public:
	Rect();
	Rect(Vector3 pos, Vector3 N, Vector3 X, Vector3 Y, double xLen, double yLen, GLubyte* color);
	~Rect();
	void draw();
	void drawWithTex();
	void setParameter(Vector3 pos, Vector3 N, Vector3 X, Vector3 Y, double xLen, double yLen, GLubyte* color);
	bool loadTexture(const char* bmpName);

	Vector3 pos, N;		//矩形中心点，平面法向量
	double xLen, yLen;	//矩形长，宽
	Vector3 X, Y;		//矩形长、宽方向的单位向量，X (叉乘) Y = N
	
	Vector3 points[4];	//矩形的4个顶点
	GLubyte *color;		//矩形颜色

private:
	Image texImage;					//矩形纹理
	unsigned int textureID;			//纹理列表
	double coordX[4], coordY[4];	//纹理坐标
};




#endif