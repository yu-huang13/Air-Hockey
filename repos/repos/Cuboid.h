#ifndef CUBOID_H
#define CUBOID_H

#include <glut.h>
#include "Rect.h"

enum Surface {FRONT=0, BACK=1, LEFT=2, RIGHT=3, UP=4, DOWN=5};

/**
* 长方体类
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
	

	Vector3 pos;				//长方体中心点
	Vector3 X, Y, Z;			//长方体长、宽、高的单位向量，Z = X (叉乘) Y
	double xLen, yLen, zLen;	//长宽高
	Rect rect[6];			//6个矩形面

private:


};



#endif