#ifndef CUBOID_H
#define CUBOID_H

#include <glut.h>
#include "Rect.h"

enum Surface {FRONT=0, BACK=1, LEFT=2, RIGHT=3, UP=4, DOWN=5};

/**
* ��������
*/
class Cuboid
{
public:
	Cuboid();
	Cuboid(Vector3 pos, Vector3 X, Vector3 Y, Vector3 Z, double xLen, double yLen, double zLen, GLubyte* color);
	~Cuboid();
	void setColor(Surface surface, GLubyte *color);
	void setParameter(Vector3 pos, Vector3 X, Vector3 Y, Vector3 Z, double xLen, double yLen, double zLen, GLubyte* color);
	void draw();
	

	Vector3 pos;				//���������ĵ�
	Vector3 X, Y, Z;			//�����峤�����ߵĵ�λ������Z = X (���) Y
	double xLen, yLen, zLen;	//�����
	Rect rect[6];			//6��������

private:


};



#endif