#pragma once
#include "stdafx.h"

class Brick
{

public:
	unsigned colorID;
	unsigned DesignID;
	unsigned itemNos;		
	CVector3d trans;			//���i�ړ���
	unsigned rn;				//rn = 0:��]���Ȃ��@1:90����]����(LDD��ł�Y������X������Z�������ւ̉�])


	Brick(void);
	~Brick(void);

	void clear();

};
