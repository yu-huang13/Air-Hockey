#include "Cylinder.h"

Cylinder::Cylinder(Vector3 pos, double radius, double height, GLubyte* color): slices(32), stacks(5){
	this->pos = pos;
	this->radius = radius;
	this->height = height;
	qobj = gluNewQuadric();
	this->color = color;
}

Cylinder::~Cylinder(){
}

/**
* 绘制圆柱
*/
void Cylinder::draw(){
	glPushMatrix();
	glColor3ubv(color);
	glTranslated(pos.x, pos.y, pos.z);
	glTranslated(0.0, 0.0, -height/2);
	gluCylinder(qobj, radius, radius, height, slices, stacks);
	drawCycle(radius, slices);
	glTranslated(0.0, 0.0, height);
	drawCycle(radius, slices);
	glPopMatrix();
}

/**
* 绘制圆
*/
void Cylinder::drawCycle(const double &radius, const int &slices){
	glColor3ubv(color);
	glBegin(GL_TRIANGLE_FAN);	//扇形连续填充三角形串  
    glVertex3f(0.0, 0.0, 0.0);
	double stepAngle = 2 * PI / slices;
	double angle = 0;
    for (int i = 0; i <= slices; ++i)  {  
        glVertex3f(radius * sin(angle), radius * cos(angle), 0.0f);  
		angle += stepAngle;
    }  
    glEnd();  
}

