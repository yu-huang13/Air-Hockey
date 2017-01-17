#include "Camera.h"

Camera::Camera(double fovy, double aspect, double zNear, double zFar, Vector3 lookat, double alphaXY, double alphaZ, double dist)
	:ROTATE_STEP(2 * PI / 100), ROTATE_LEFT_BORDER(-60 * PI / 180), ROTATE_RIGHT_BORDER(60 * PI / 180),
	 ROTATE_UP_BORDER(70 * PI / 180), ROTATE_DOWN_BORDER(30 * PI / 180)
{
	this->fovy = fovy;
	this->aspect = aspect;
	this->zNear = zNear;
	this->zFar = zFar;

	this->alphaXY = alphaXY;
	this->alphaZ = alphaZ;
	this->dist = dist;
	this->lookat = lookat;

	update(alphaXY, alphaZ);
}

Camera::~Camera(){

}

/**
* 根据alphaXY与alphaZ计算ray、pos、up
*/
void Camera::update(double &alphaXY, double &alphaZ){
	ray = -Vector3(cos(alphaXY), sin(alphaXY), tan(alphaZ)).unitVector();
	pos = lookat - ray * dist;
	up = (Vector3(0, 0, 1) + ray * cos(alphaZ)).unitVector();
}

/**
* 相机向左移动
*/
void Camera::moveLeft(){
	alphaXY -= ROTATE_STEP;
	if (alphaXY < ROTATE_LEFT_BORDER)
		alphaXY = ROTATE_LEFT_BORDER;
	update(alphaXY, alphaZ);
}

/**
* 相机向右移动
*/
void Camera::moveRight(){
	alphaXY += ROTATE_STEP;
	if (alphaXY > ROTATE_RIGHT_BORDER)
		alphaXY = ROTATE_RIGHT_BORDER;
	update(alphaXY, alphaZ);
}

/**
* 相机向上移动
*/
void Camera::moveUp(){
	alphaZ += ROTATE_STEP;
	if (alphaZ > ROTATE_UP_BORDER)
		alphaZ = ROTATE_UP_BORDER;
	update(alphaXY, alphaZ);
}

/**
* 相机向下移动
*/
void Camera::moveDown(){
	alphaZ -= ROTATE_STEP;
	if (alphaZ < ROTATE_DOWN_BORDER)
		alphaZ = ROTATE_DOWN_BORDER;
	update(alphaXY, alphaZ);
}