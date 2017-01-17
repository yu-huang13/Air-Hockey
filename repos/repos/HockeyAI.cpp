#include "HockeyAI.h"

HockeyAI::HockeyAI(int malletID, Game &g): game(g){
	this->malletID = malletID;
}

HockeyAI::~HockeyAI(){
}

HockeyAI_L0::HockeyAI_L0(int malletID, Game &g): 
	HockeyAI(malletID, g), MALLET_STEP(0.0005), 
	X_LINE(game.malletLimit[malletID].XL + 10 * game.puck->radius)
{

}

HockeyAI_L0::~HockeyAI_L0(){
}

/**
* 根据游戏状态，计算mallet的下一个位置
*/
Vector3 HockeyAI_L0::nextPos(){
	nextDiret.y = sign(game.puck->pos.y - game.mallet[malletID]->pos.y);
	nextDiret.x = sign(X_LINE - game.mallet[malletID]->pos.x);
	nextDiret.z = 0;
	return game.mallet[malletID]->pos + nextDiret * MALLET_STEP;
}

HockeyAI_L1::HockeyAI_L1(int malletID, Game &g): 
	HockeyAI(malletID, g), MALLET_STEP(0.001), 
	X_LINE(game.malletLimit[malletID].XL + 3 * game.puck->radius)
{
}

HockeyAI_L1::~HockeyAI_L1(){
}

/**
* 根据游戏状态，计算mallet的下一个位置
*/
Vector3 HockeyAI_L1::nextPos(){
	nextDiret.y = sign(game.puck->pos.y - game.mallet[malletID]->pos.y);
	if (game.puckDirect.dot(Vector3(1, 0, 0)) > 0)
		nextDiret.y = -nextDiret.y;
	nextDiret.x = sign(X_LINE - game.mallet[malletID]->pos.x);

	nextDiret.z = 0;
	return game.mallet[malletID]->pos + nextDiret * MALLET_STEP;
}