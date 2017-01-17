#ifndef HOCKEYAI_H
#define HOCKEYAI_H

#include "Game.h"
#include "Vector3.h"

class Game;

/**
* ��ϷAI������
*/
class HockeyAI
{
public:
	HockeyAI(int malletID, Game &g);
	~HockeyAI();
	virtual Vector3 nextPos() = 0;
	Game &game;		//�����ģ����ڻ�ȡ��Ϸ�Ļ����Լ���������
	int malletID;	//AI���Ƶ�mallet��ID
};

/**
* ��ϷAI��level 0
*/
class HockeyAI_L0: public HockeyAI
{
public:
	HockeyAI_L0(int malletID, Game &g);
	~HockeyAI_L0();
	virtual Vector3 nextPos();

private:
	const double MALLET_STEP;	//ai mallet�ƶ��Ĳ���
	const double X_LINE;	//ai malletλ�ڵ�"ˮƽ��"
	Vector3 nextDiret;		//ai mallet����һ���˶�����
};

/**
* ��ϷAI��level 1
*/
class HockeyAI_L1: public HockeyAI
{
public:
	HockeyAI_L1(int malletID, Game &g);
	~HockeyAI_L1();
	virtual Vector3 nextPos();

private:
	const double MALLET_STEP;	//ai mallet�ƶ��Ĳ���
	const double X_LINE;	//ai malletλ�ڵ�"ˮƽ��"
	Vector3 nextDiret;		//ai mallet����һ���˶�����
};



#endif