#pragma once

class Lego
{
public:
	unsigned short flag;			//(DesignID) (PÅ~ÇPÅAÇPÅ~ÇQÅBÅBÅB)ÇLEGO
	bool fill;							//(Voxel)fill
	bool surf;							//(Voxel)surface
	bool in_surf;						//inside surface 2014/09/11
	bool p_fill;						//p fill 2015/09/11Å
	bool root;							//root
	bool airP;							//airP
	unsigned ID;					//(refID) flagÇID
	unsigned short corner;	        //OpenGLÇ KóvÅiconer 1Ç 2Ç 
	unsigned ColorID;			    //(ColorID)êFÇ ID

	//
	bool calc;							//
	int BrickN;						//Brick Number
	Lego(void);
	~Lego(void);
	void Initiaization(void);
};