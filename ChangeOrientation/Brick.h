#pragma once
#include "stdafx.h"

class Brick
{

public:
	unsigned colorID;
	unsigned DesignID;
	unsigned itemNos;		
	CVector3d trans;			//•ÀiˆÚ“®—Ê
	unsigned rn;				//rn = 0:‰ñ“]‚µ‚È‚¢@1:90‹‰ñ“]‚·‚é(LDDã‚Å‚ÍY²ü‚èX²‚©‚çZ²•ûŒü‚Ö‚Ì‰ñ“])


	Brick(void);
	~Brick(void);

	void clear();

};
