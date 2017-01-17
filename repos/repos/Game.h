#ifndef GAME_H
#define GAME_H

#include <windows.h>
#include <glut.h>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <vector>

#include "utils.h"
#include "Camera.h"
#include "Cylinder.h"
#include "Cuboid.h"
#include "Rect.h"
#include "Color.h"
#include "Image.h"
#include "HockeyAI.h"

using namespace std;

class HockeyAI;

extern const int CHAR_NUM;	//128��ascii��

struct Limit
{
	double XL, XR, YL, YR;
};

enum Player {I, AI};	//���
enum GameStatus {I_WIN, AI_WIN, GAME_START};	//��Ϸ״̬

/**
* ��Ϸ�࣬������Ϸ�������߼�
*/
class Game
{
public:
	Game(int width, int height);
	~Game();
	friend class HockeyAI_L0;
	friend class HockeyAI_L1;
	void updateView();
	void mousePassiveMove(int winx, int winy);
	void keyboard(unsigned char key, int x, int y);
	void specialKeyboard(int key, int x, int y);
	void reshape(int width, int height);
	void display();
	void idle();
	void run();

	int WIDTH;		//���ڿ�
	int HEIGHT;		//���ڸ�

private:
	void collideTestAll();
	void collideTest(Rect* rect, Cylinder* cylin, Vector3 &direct);
	void collideTest(Cylinder* c1, Cylinder *c2, Vector3 &direct);
	void initPuckDirect();
	void updateGameStatus();
	void reset();
	void selectFont(int size, int charset, const char * face);
	void drawString(const char* str);
	GameStatus gameStatus;
	inline double limit(double x, double l, double r);
	void posLimit(Vector3& pos, Limit& li);

	HockeyAI *hockeyAI[2];		//AI
	int currentAI;		//��ǰ�������е�AI

	Camera *camera;
	Cylinder *puck;
	Cylinder *mallet[2];	//mallet[0]--my mallet; mallet[1]--ai mallet
	Cuboid *table;
	Cuboid *walls;
	Rect *floor;
	
	Vector3 puckDirect;		//puck�����з���
	const double PUCK_STEP;		//puck�����в���
	vector<Rect*> collideRects;		//��Ҫ������ײ���ľ�����
	Limit malletLimit[2];		//�涨mallet�Ŀɻ��Χ

	bool charListInit;		//�жϴ�ӡ��ĸ���б��Ƿ��ʼ��
	unsigned int charList;		//��ӡ��ĸ���б�
};



















#endif