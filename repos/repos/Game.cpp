#include "Game.h"

const int CHAR_NUM = 128;

Game::Game(int width, int height):PUCK_STEP(0.001){
	srand(time(NULL));

	WIDTH = width;
	HEIGHT = height;

	//��ʼ�����
	camera = new Camera(30, WIDTH/(double)HEIGHT, 1, 200, Vector3(0, 0, 0), 30 * PI / 180, 60 * PI / 180, 14);
	updateView();

	//��ʼ������
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

	//��ʼ��AI
	hockeyAI[0] = new HockeyAI_L0(1, *this);
	hockeyAI[1] = new HockeyAI_L1(1, *this);
	currentAI = 0;

	charListInit = false;

	//��ʼ����Ϸ״̬
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
* ����x��ʹ��λ��[l, r]����
*/
double Game::limit(double x, double l, double r){
	if (x < l)	return l;
	else if (x > r) return r;
	return x;
}

/**
* ����pos��ʹ��λ��Limit��ʾ��������
*/
void Game::posLimit(Vector3& pos, Limit& li){
	pos.x = limit(pos.x, li.XL, li.XR); 
	pos.y = limit(pos.y, li.YL, li.YR);
}

/**
* ��ʼ��puck���˶�����
* ��xyƽ���ϣ���y��Ϊ��㣬��������Ƕ���[30, 150] || [-30, -150]�ķ���
*/
void Game::initPuckDirect(){
	double alpha = ((rand() % 2) ? -1.0 : 1.0) * (rand() % 120 + 30) * PI / 180;	//[30, 150] || [-30, -150]
	puckDirect = Vector3(sin(alpha), cos(alpha), 0.0);
}

/**
* ������Ϸ
*/
void Game::reset(){
	puck->pos = Vector3(0, 0, 0.05);
	initPuckDirect();

	mallet[0]->pos = Vector3(1, 0, 0.05);
	mallet[1]->pos = Vector3(-1, 0, 0.05);
}

/**
* ����puck��λ�ã�������Ϸ״̬
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
* ���������С�Լ���ʽ
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
* �ڴ��������ӡ�ַ���
*/
void Game::drawString(const char* str){
	//��ͶӰ�������óɶ�ά�ü�����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5, 5, -5, 5);//�ü���Χ(��, ��, ��, ��)�����ϣ�����Σ��ü���ΧҪ�ʹ��ڳɱ���
	//�ص�ģ����ͼ����ģʽ
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
	updateView();		//�ָ��ӽ��Լ�ͶӰ
}

/**
* ����ͶӰ�������ӵ�
*/
void Game::updateView(){
	glViewport(0, 0, WIDTH, HEIGHT);	// Reset The Current Viewport
	glMatrixMode(GL_PROJECTION);        // ����͸��ͶӰ����
    glLoadIdentity();                   // ��ʼ��Ϊ��λ��
    gluPerspective(camera->fovy, camera->aspect, camera->zNear, camera->zFar);       // ���ӽǣ�w/h��zNear��zFar
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	gluLookAt(
		camera->pos.x, camera->pos.y, camera->pos.z, 
		camera->lookat.x, camera->lookat.y, camera->lookat.z, 
		camera->up.x, camera->up.y, camera->up.z
	);        //eye��center��up
}

/**
* ��ײ���
*/
void Game::collideTestAll(){
	for (int i = 0; i < 2; ++i)
		collideTest(mallet[i], puck, puckDirect);
	for (vector<Rect*>::iterator it = collideRects.begin(); it != collideRects.end(); ++it)
		collideTest(*it, puck, puckDirect);
}

/**
* ���Բ����cylin�Ƿ��������rect��ײ������ײ��Բ����cylin��direct��Ϊ��ײ���direct�����򲻱�
*/
void Game::collideTest(Rect* rect, Cylinder* cylin, Vector3 &direct){
	double dist = (cylin->pos - rect->pos).dot(rect->N);
	if (fabs(dist) > cylin->radius + EPS)	//δ���������ƽ����ײ������
		return;		

	Vector3 rectPosToCollPos = (cylin->pos - rect->N * dist) - rect->pos;
	if (fabs(rectPosToCollPos.dot(rect->X)) > rect->xLen/2 + EPS || fabs(rectPosToCollPos.dot(rect->Y)) > rect->yLen/2 + EPS)//���������ƽ����ײ�����������ײ������
		return;		

	direct = (-direct).reflect(rect->N);	//�������ײ�������·���
}

/**
* ���Բ����c1�Ƿ���Բ����c2��ײ������ײ��Բ����cylin��direct��Ϊ��ײ���direct�����򲻱�
*/
void Game::collideTest(Cylinder* c1, Cylinder *c2, Vector3 &direct){
	Vector3 c1Toc2 = c2->pos - c1->pos;
	if (c1Toc2.module() > c1->radius + c2->radius + EPS)	//δ��ײ�����򲻱�
		return;
	
	if (direct.dot(c1Toc2) > 0)	//c2�����з�����c1
		return;

	direct = (-direct).reflect(c1Toc2.unitVector());		//��ײ�������·���
}

/**
* ����ƶ��¼�������
*/
void Game::mousePassiveMove(int winx, int winy){
	//��ȡ������ڴ����ߵķ���
	double modelMatrix[16];
	double projMatrix[16];
	int viewport[4];
	Vector3 nearP, farP, ray, intersect;

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	
	gluUnProject(winx, HEIGHT - winy, 0.0, modelMatrix, projMatrix, viewport, &(nearP.x), &(nearP.y), &(nearP.z));
	ray = (nearP - camera->pos).unitVector();

	//������������Ľ���
	Vector3 &N = table->rect[UP].N;
	Vector3 &O = table->rect[UP].pos;
	double cosH = N.dot(ray);
	if (isZero(cosH)) return;	//ƽ��
	double dist = N.dot(O - camera->pos) / cosH;
	intersect = camera->pos + ray * dist;

	//��mallet��x��y������Ϊ�����x��y����
	mallet[0]->pos.x = intersect.x; mallet[0]->pos.y = intersect.y;
	posLimit(mallet[0]->pos, malletLimit[0]);
}

/**
* �����¼�������
*/
void Game::keyboard(unsigned char key, int x, int y){
    switch(key){
		case '1': currentAI = 0; break;	
		case '2': currentAI = 1; break;
		case 13: reset(); break;	//�س�
		case 27: break;		//esc
        default: break;
    }
}

/**
* �����¼�������
*/
void Game::specialKeyboard(int key, int x, int y){
	switch(key){
		case GLUT_KEY_LEFT: camera->moveLeft(); updateView(); break;	//���������
		case GLUT_KEY_RIGHT: camera->moveRight(); updateView(); break;	//���������
		case GLUT_KEY_UP: camera->moveUp(); updateView();  break;		//���������
		case GLUT_KEY_DOWN: camera->moveDown(); updateView(); break;	//���������
		default: break;
	}
}

/**
* �����¼�������
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
* ���д�����
*/
void Game::idle(){
	updateGameStatus();		//����puck��λ���ж���Ϸ�Ƿ����
	display();

	if (gameStatus == GAME_START){
		collideTestAll();	//��ײ���
		puck->pos += puckDirect * PUCK_STEP;	//����puck��λ��
		mallet[1]->pos = hockeyAI[currentAI]->nextPos();	//����ai mallet��λ��
		posLimit(mallet[1]->pos, malletLimit[1]);
	}
	else if (gameStatus == I_WIN)
		drawString("YOU WIN!");		//�������"YOU WIN!"����
	else if (gameStatus == AI_WIN)
		drawString("YOU LOSE!");	//�������"YOU LOST!"����

    glutSwapBuffers();
}

