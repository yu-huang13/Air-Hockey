#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"

/**
* �����
*/
class Camera
{
public:
	Camera(double fovy, double aspect, double zNear, double zFar, Vector3 lookat, double alphaXY, double alphaZ, double dist);
	~Camera();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	double fovy;	//���ӽ�
	double aspect;	//��߱�w/h
	double zNear;	//zNear
	double zFar;	//zFar

	Vector3 pos;	//���λ��
	Vector3 lookat;		//����۲��
	Vector3 up;		//����Ϸ���

private:
	void update(double &alphaXY, double &alphaZ);

	double alphaXY;		//ray��xyƽ���ϵ�ͶӰ��x��ļн�
	double alphaZ;		//ray������xyƽ���ϵ�ͶӰ�ļн�
	Vector3 ray;	//���λ�õ��۲��ĵ�λ����
	double dist;	//���λ�õ��۲��ľ���

	const double ROTATE_STEP;	//��ת�Ĳ���
	const double ROTATE_LEFT_BORDER;	//��ת����ĽǶ�
	const double ROTATE_RIGHT_BORDER;	//��ת���ҵĽǶ�
	const double ROTATE_UP_BORDER;		//��ת���ϵĽǶ�
	const double ROTATE_DOWN_BORDER;	//��ת���µĽǶ�
	
};



















#endif