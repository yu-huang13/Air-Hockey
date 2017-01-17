//
//  main.cpp
//  repos
//
//  Created by HY on 17/01/11.
//  Copyright © 2017年 HY. All rights reserved.
//

#include <windows.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <glut.h>

#include "Game.h"
#include "Cylinder.h"

using namespace std;

Game *game;
const int WIDTH = 800;
const int HEIGHT = 800;

void mousePassiveMove(int x, int y){
	game->mousePassiveMove(x, y);
}

void keyboard(unsigned char key, int x, int y){
	game->keyboard(key, x, y);
}

void specialKeyboard(int key, int x, int y){
	game->specialKeyboard(key, x, y);
}

void display(){
	game->display();
}

void idle(){
	game->idle();
}


int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT); 
	glutCreateWindow("Air Hockey");

	game = new Game(WIDTH, HEIGHT);
	glEnable(GL_DEPTH_TEST);				// Enables Depth Testing

	glutPassiveMotionFunc(mousePassiveMove);
    glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();
	delete game;
}


