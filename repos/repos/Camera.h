#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"

/**
* 相机类
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

	double fovy;	//可视角
	double aspect;	//宽高比w/h
	double zNear;	//zNear
	double zFar;	//zFar

	Vector3 pos;	//相机位置
	Vector3 lookat;		//相机观察点
	Vector3 up;		//相机上方向

private:
	void update(double &alphaXY, double &alphaZ);

	double alphaXY;		//ray在xy平面上的投影与x轴的夹角
	double alphaZ;		//ray与其在xy平面上的投影的夹角
	Vector3 ray;	//相机位置到观察点的单位向量
	double dist;	//相机位置到观察点的距离

	const double ROTATE_STEP;	//旋转的步长
	const double ROTATE_LEFT_BORDER;	//旋转最左的角度
	const double ROTATE_RIGHT_BORDER;	//旋转最右的角度
	const double ROTATE_UP_BORDER;		//旋转最上的角度
	const double ROTATE_DOWN_BORDER;	//旋转最下的角度
	
};



















#endif