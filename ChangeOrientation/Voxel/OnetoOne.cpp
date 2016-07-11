#include "../Voxel.h"

OnetoOne::OnetoOne()
{
	this->dist = DBL_MAX;		//距離の値を無限大にする
	this->flag = false;	
	this->num = 0;
}

void OnetoOne::Initial()		//初期化する
{
	this->dist = DBL_MAX;		//距離の値を無限大にする
	this->flag = false;
	this->num = 0;
}