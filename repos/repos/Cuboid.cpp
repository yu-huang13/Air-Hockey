#include "Cuboid.h"

Cuboid::Cuboid(){}

Cuboid::Cuboid(Vector3 pos, Vector3 X, Vector3 Y, Vector3 Z, double xLen, double yLen, double zLen, GLubyte* color){
	setParameter(pos, X, Y, Z, xLen, yLen, zLen, color);
}

Cuboid::~Cuboid(){
}

/**
* 设置长方体的参数
*/
void Cuboid::setParameter(Vector3 pos, Vector3 X, Vector3 Y, Vector3 Z, double xLen, double yLen, double zLen, GLubyte* color){
	this->pos = pos;
	this->X = X;
	this->Y = Y;
	this->Z = Z;
	this->xLen = xLen;
	this->yLen = yLen;
	this->zLen = zLen;

	Vector3 halfX = X * xLen * 0.5;
	Vector3 halfY = Y * yLen * 0.5;
	Vector3 halfZ = Z * zLen * 0.5;
	rect[FRONT].setParameter(pos+halfX, X, Y, Z, yLen, zLen, color);
	rect[BACK].setParameter(pos-halfX, -X, Y, -Z, yLen, zLen, color);
	rect[LEFT].setParameter(pos-halfY, -Y, X, Z, xLen, zLen, color);
	rect[RIGHT].setParameter(pos+halfY, Y, -X, Z, xLen, zLen, color);
	rect[UP].setParameter(pos+halfZ, Z, X, Y, xLen, yLen, color);
	rect[DOWN].setParameter(pos-halfZ, -Z, X, -Y, xLen, yLen, color);
}

/**
* 设置长方体某个面的颜色
*/
void Cuboid::setColor(Surface surface, GLubyte *color){
	rect[surface].color = color;
}


/*
* 绘制长方体
*/
void Cuboid::draw(){
	glPushMatrix();

	for (int i = 0; i < 6; ++i)
		rect[i].draw();
    
	glPopMatrix();
}