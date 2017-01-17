#ifndef Rect_H
#define Rect_H

#include <glut.h>

#include "Vector3.h"
#include "Color.h"
#include "Image.h"

/**
* ������
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

	Vector3 pos, N;		//�������ĵ㣬ƽ�淨����
	double xLen, yLen;	//���γ�����
	Vector3 X, Y;		//���γ�������ĵ�λ������X (���) Y = N
	
	Vector3 points[4];	//���ε�4������
	GLubyte *color;		//������ɫ

private:
	Image texImage;					//��������
	unsigned int textureID;			//�����б�
	double coordX[4], coordY[4];	//��������
};




#endif