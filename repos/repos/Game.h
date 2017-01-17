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

extern const int CHAR_NUM;	//128个ascii码

struct Limit
{
	double XL, XR, YL, YR;
};

enum Player {I, AI};	//玩家
enum GameStatus {I_WIN, AI_WIN, GAME_START};	//游戏状态

/**
* 游戏类，负责游戏绘制与逻辑
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

	int WIDTH;		//窗口宽
	int HEIGHT;		//窗口高

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
	int currentAI;		//当前正在运行的AI

	Camera *camera;
	Cylinder *puck;
	Cylinder *mallet[2];	//mallet[0]--my mallet; mallet[1]--ai mallet
	Cuboid *table;
	Cuboid *walls;
	Rect *floor;
	
	Vector3 puckDirect;		//puck的运行方向
	const double PUCK_STEP;		//puck的运行步长
	vector<Rect*> collideRects;		//需要进行碰撞检测的矩形面
	Limit malletLimit[2];		//规定mallet的可活动范围

	bool charListInit;		//判断打印字母的列表是否初始化
	unsigned int charList;		//打印字母的列表
};



















#endif