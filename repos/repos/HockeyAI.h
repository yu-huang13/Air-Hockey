#ifndef HOCKEYAI_H
#define HOCKEYAI_H

#include "Game.h"
#include "Vector3.h"

class Game;

/**
* 游戏AI，基类
*/
class HockeyAI
{
public:
	HockeyAI(int malletID, Game &g);
	~HockeyAI();
	virtual Vector3 nextPos() = 0;
	Game &game;		//上下文，用于获取游戏的环境以及各个参数
	int malletID;	//AI控制的mallet的ID
};

/**
* 游戏AI，level 0
*/
class HockeyAI_L0: public HockeyAI
{
public:
	HockeyAI_L0(int malletID, Game &g);
	~HockeyAI_L0();
	virtual Vector3 nextPos();

private:
	const double MALLET_STEP;	//ai mallet移动的步长
	const double X_LINE;	//ai mallet位于的"水平线"
	Vector3 nextDiret;		//ai mallet的下一个运动方向
};

/**
* 游戏AI，level 1
*/
class HockeyAI_L1: public HockeyAI
{
public:
	HockeyAI_L1(int malletID, Game &g);
	~HockeyAI_L1();
	virtual Vector3 nextPos();

private:
	const double MALLET_STEP;	//ai mallet移动的步长
	const double X_LINE;	//ai mallet位于的"水平线"
	Vector3 nextDiret;		//ai mallet的下一个运动方向
};



#endif