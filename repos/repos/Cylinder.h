#ifndef CYLINDER_H
#define CYLINDER_H

#include <glut.h>
#include "Vector3.h"

/**
* Բ���࣬��z��ΪԲ����
*/
class Cylinder
{
public:
	Cylinder(Vector3 pos, double radius, double height, GLubyte* color);
	~Cylinder();
	void draw();

	GLUquadric *qobj;
	Vector3 pos;	//Բ��λ�ã���Բ���±���Բ�ĵ�����
	double radius;	//�뾶
	double height;	//�߶�
	GLubyte* color;	//Բ����ɫ
	

private:
	const int slices;	//����Բ��ʱ���з���Ŀ
	const int stacks;

	void drawCycle(const double &radius, const int &slices);

};



















#endif