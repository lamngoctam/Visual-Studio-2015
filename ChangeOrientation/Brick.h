#pragma once
#include "stdafx.h"

class Brick
{

public:
	unsigned colorID;
	unsigned DesignID;
	unsigned itemNos;		
	CVector3d trans;			//並進移動量
	unsigned rn;				//rn = 0:回転しない　1:90°回転する(LDD上ではY軸周りX軸からZ軸方向への回転)


	Brick(void);
	~Brick(void);

	void clear();

};
