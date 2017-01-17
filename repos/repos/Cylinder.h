#ifndef CYLINDER_H
#define CYLINDER_H

#include <glut.h>
#include "Vector3.h"

/**
* 圆柱类，以z轴为圆柱轴
*/
class Cylinder
{
public:
	Cylinder(Vector3 pos, double radius, double height, GLubyte* color);
	~Cylinder();
	void draw();

	GLUquadric *qobj;
	Vector3 pos;	//圆柱位置，即圆柱下表面圆心的坐标
	double radius;	//半径
	double height;	//高度
	GLubyte* color;	//圆柱颜色
	

private:
	const int slices;	//绘制圆柱时的切分数目
	const int stacks;

	void drawCycle(const double &radius, const int &slices);

};



















#endif