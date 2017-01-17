#include "Game.h"

const int CHAR_NUM = 128;

Game::Game(int width, int height):PUCK_STEP(0.001){
	srand(time(NULL));

	WIDTH = width;
	HEIGHT = height;

	//初始化相机
	camera = new Camera(30, WIDTH/(double)HEIGHT, 1, 200, Vector3(0, 0, 0), 30 * PI / 180, 60 * PI / 180, 14);
	updateView();

	//初始化场景
	table = new Cuboid(Vector3(0, 0, -1.1), Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1), 4.2, 2.2, 2.2, Color::GREY);
	table->setColor(UP, Color::GREEN);

	puck = new Cylinder(Vector3(0, 0, 0.05), 0.1, 0.1, Color::RED);
	mallet[0] = new Cylinder(Vector3(1, 0, 0.05), 0.15, 0.1, Color::BLUE);
	mallet[1] = new Cylinder(Vector3(-1, 0, 0.05), 0.15, 0.1, Color::PURPLE);
	
	walls = new Cuboid[6];
	Vector3 X(1, 0, 0); Vector3 Y(0, 1, 0); Vector3 Z(0, 0, 1);
	walls[0].setParameter(Vector3(0, -1.05, 0.05), X, Y, Z, 4.2, 0.1, 0.1, Color::WHITE);
	walls[1].setParameter(Vector3(0, 1.05, 0.05), X, Y, Z, 4.2, 0.1, 0.1, Color::WHITE);
	walls[2].setParameter(Vector3(-2.05, -0.7, 0.05), X, Y, Z, 0.1, 0.6, 0.1, Color::WHITE);
	walls[3].setParameter(Vector3(2.05, -0.7, 0.05), X, Y, Z, 0.1, 0.6, 0.1, Color::WHITE);
	walls[4].setParameter(Vector3(-2.05, 0.7, 0.05), X, Y, Z, 0.1, 0.6, 0.1, Color::WHITE);
	walls[5].setParameter(Vector3(2.05, 0.7, 0.05), X, Y, Z, 0.1, 0.6, 0.1, Color::WHITE);
	collideRects.push_back(&(walls[0].rect[RIGHT])); collideRects.push_back(&(walls[1].rect[LEFT]));
	collideRects.push_back(&(walls[2].rect[FRONT])); collideRects.push_back(&(walls[3].rect[BACK]));
	collideRects.push_back(&(walls[4].rect[FRONT])); collideRects.push_back(&(walls[5].rect[BACK]));

	malletLimit[0].XL = 0 + mallet[0]->radius; 
	malletLimit[0].XR = table->xLen/2 - walls[3].xLen - mallet[0]->radius;
	malletLimit[0].YL = -table->yLen/2 + walls[0].yLen + mallet[0]->radius; 
	malletLimit[0].YR = table->yLen/2 - walls[1].yLen - mallet[0]->radius;

	malletLimit[1].XL = -table->xLen/2 + walls[2].xLen + mallet[1]->radius;
	malletLimit[1].XR = 0 - mallet[1]->radius;
	malletLimit[1].YL = -table->yLen/2 + walls[0].yLen + mallet[1]->radius;
	malletLimit[1].YR = table-> yLen/2 - walls[1].yLen - mallet[1]->radius;

	floor = new Rect(Vector3(0, 0, -2.2), Z, X, Y, 20, 20, Color::BLACK);
	floor->loadTexture("floor.bmp");

	//初始化AI
	hockeyAI[0] = new HockeyAI_L0(1, *this);
	hockeyAI[1] = new HockeyAI_L1(1, *this);
	currentAI = 0;

	charListInit = false;

	//初始化游戏状态
	gameStatus = GAME_START;	
	initPuckDirect();
}

Game::~Game(){
	delete camera;
	delete puck;
	for (int i = 0; i < 2; ++i)
		delete mallet[i];
	for (int i = 0; i < 2; ++i)
		delete hockeyAI[i];
	delete table;
	delete []walls;
	delete floor;
}

/**
* 限制x，使其位于[l, r]区间
*/
double Game::limit(double x, double l, double r){
	if (x < l)	return l;
	else if (x > r) return r;
	return x;
}

/**
* 限制pos，使其位于Limit表示的区间内
*/
void Game::posLimit(Vector3& pos, Limit& li){
	pos.x = limit(pos.x, li.XL, li.XR); 
	pos.y = limit(pos.y, li.YL, li.YR);
}

/**
* 初始化puck的运动方向
* 在xy平面上，以y轴为起点，随机产生角度在[30, 150] || [-30, -150]的方向
*/
void Game::initPuckDirect(){
	double alpha = ((rand() % 2) ? -1.0 : 1.0) * (rand() % 120 + 30) * PI / 180;	//[30, 150] || [-30, -150]
	puckDirect = Vector3(sin(alpha), cos(alpha), 0.0);
}

/**
* 重置游戏
*/
void Game::reset(){
	puck->pos = Vector3(0, 0, 0.05);
	initPuckDirect();

	mallet[0]->pos = Vector3(1, 0, 0.05);
	mallet[1]->pos = Vector3(-1, 0, 0.05);
}

/**
* 根据puck的位置，更新游戏状态
*/
void Game::updateGameStatus()
{
	if (puck->pos.x > table->xLen/2)
		gameStatus = AI_WIN;
	else if (puck->pos.x < -table->xLen/2)
		gameStatus = I_WIN;
	else
		gameStatus = GAME_START;
}

/**
* 设置字体大小以及样式
*/
void Game::selectFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(
		size, 0, 0, 0, FW_MEDIUM, 0, 0, 0, charset, 
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face
	);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont); 
}

/**
* 在窗口中央打印字符串
*/
void Game::drawString(const char* str){
	//把投影矩阵设置成二维裁剪矩阵
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5, 5, -5, 5);//裁剪范围(左, 右, 下, 上)如果不希望变形，裁剪范围要和窗口成比例
	//回到模型视图矩阵模式
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	selectFont(128, ANSI_CHARSET, "Comic Sans MS");
	if (!charListInit){
		charList = glGenLists(CHAR_NUM);
		wglUseFontBitmaps(wglGetCurrentDC(), 0, CHAR_NUM, charList);
		charListInit = true;
	}

	glColor3ubv(Color::YELLOW);
	glRasterPos2d(-3, -0.5);
	for(; *str!='\0'; ++str)
		glCallList(charList + *str);
	updateView();		//恢复视角以及投影
}

/**
* 更新投影矩阵与视点
*/
void Game::updateView(){
	glViewport(0, 0, WIDTH, HEIGHT);	// Reset The Current Viewport
	glMatrixMode(GL_PROJECTION);        // 设置透视投影矩阵
    glLoadIdentity();                   // 初始化为单位阵
    gluPerspective(camera->fovy, camera->aspect, camera->zNear, camera->zFar);       // 可视角，w/h，zNear，zFar
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	gluLookAt(
		camera->pos.x, camera->pos.y, camera->pos.z, 
		camera->lookat.x, camera->lookat.y, camera->lookat.z, 
		camera->up.x, camera->up.y, camera->up.z
	);        //eye，center，up
}

/**
* 碰撞检测
*/
void Game::collideTestAll(){
	for (int i = 0; i < 2; ++i)
		collideTest(mallet[i], puck, puckDirect);
	for (vector<Rect*>::iterator it = collideRects.begin(); it != collideRects.end(); ++it)
		collideTest(*it, puck, puckDirect);
}

/**
* 检测圆柱体cylin是否与矩形面rect碰撞，若碰撞则将圆柱体cylin的direct改为碰撞后的direct，否则不变
*/
void Game::collideTest(Rect* rect, Cylinder* cylin, Vector3 &direct){
	double dist = (cylin->pos - rect->pos).dot(rect->N);
	if (fabs(dist) > cylin->radius + EPS)	//未与矩形所在平面碰撞，返回
		return;		

	Vector3 rectPosToCollPos = (cylin->pos - rect->N * dist) - rect->pos;
	if (fabs(rectPosToCollPos.dot(rect->X)) > rect->xLen/2 + EPS || fabs(rectPosToCollPos.dot(rect->Y)) > rect->yLen/2 + EPS)//与矩形所在平面碰撞但不与矩形碰撞，返回
		return;		

	direct = (-direct).reflect(rect->N);	//与矩形碰撞，计算新方向
}

/**
* 检测圆柱体c1是否与圆柱体c2碰撞，若碰撞则将圆柱体cylin的direct改为碰撞后的direct，否则不变
*/
void Game::collideTest(Cylinder* c1, Cylinder *c2, Vector3 &direct){
	Vector3 c1Toc2 = c2->pos - c1->pos;
	if (c1Toc2.module() > c1->radius + c2->radius + EPS)	//未碰撞，方向不变
		return;
	
	if (direct.dot(c1Toc2) > 0)	//c2的运行方向背离c1
		return;

	direct = (-direct).reflect(c1Toc2.unitVector());		//碰撞，计算新方向
}

/**
* 鼠标移动事件处理函数
*/
void Game::mousePassiveMove(int winx, int winy){
	//获取鼠标所在处视线的方向
	double modelMatrix[16];
	double projMatrix[16];
	int viewport[4];
	Vector3 nearP, farP, ray, intersect;

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	
	gluUnProject(winx, HEIGHT - winy, 0.0, modelMatrix, projMatrix, viewport, &(nearP.x), &(nearP.y), &(nearP.z));
	ray = (nearP - camera->pos).unitVector();

	//求视线与桌面的交点
	Vector3 &N = table->rect[UP].N;
	Vector3 &O = table->rect[UP].pos;
	double cosH = N.dot(ray);
	if (isZero(cosH)) return;	//平行
	double dist = N.dot(O - camera->pos) / cosH;
	intersect = camera->pos + ray * dist;

	//将mallet的x、y坐标设为交点的x、y坐标
	mallet[0]->pos.x = intersect.x; mallet[0]->pos.y = intersect.y;
	posLimit(mallet[0]->pos, malletLimit[0]);
}

/**
* 键盘事件处理函数
*/
void Game::keyboard(unsigned char key, int x, int y){
    switch(key){
		case '1': currentAI = 0; break;	
		case '2': currentAI = 1; break;
		case 13: reset(); break;	//回车
		case 27: break;		//esc
        default: break;
    }
}

/**
* 键盘事件处理函数
*/
void Game::specialKeyboard(int key, int x, int y){
	switch(key){
		case GLUT_KEY_LEFT: camera->moveLeft(); updateView(); break;	//方向键：左
		case GLUT_KEY_RIGHT: camera->moveRight(); updateView(); break;	//方向键：右
		case GLUT_KEY_UP: camera->moveUp(); updateView();  break;		//方向键：上
		case GLUT_KEY_DOWN: camera->moveDown(); updateView(); break;	//方向键：下
		default: break;
	}
}

/**
* 绘制事件处理函数
*/
void Game::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	puck->draw();
	for (int i = 0; i < 2; ++i)
		mallet[i]->draw();
	table->draw();
	for (int i = 0; i < 6; ++i)
		walls[i].draw();
	floor->drawWithTex();
	glFlush();
}

/**
* 空闲处理函数
*/
void Game::idle(){
	updateGameStatus();		//根据puck的位置判断游戏是否结束
	display();

	if (gameStatus == GAME_START){
		collideTestAll();	//碰撞检测
		puck->pos += puckDirect * PUCK_STEP;	//更新puck的位置
		mallet[1]->pos = hockeyAI[currentAI]->nextPos();	//更新ai mallet的位置
		posLimit(mallet[1]->pos, malletLimit[1]);
	}
	else if (gameStatus == I_WIN)
		drawString("YOU WIN!");		//窗口输出"YOU WIN!"字样
	else if (gameStatus == AI_WIN)
		drawString("YOU LOSE!");	//窗口输出"YOU LOST!"字样

    glutSwapBuffers();
}

