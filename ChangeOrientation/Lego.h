#pragma once

class Lego
{
public:
	unsigned short flag;			//(DesignID) (P�~�P�A�P�~�Q�B�B�B)�LEGO
	bool fill;							//(Voxel)fill
	bool surf;							//(Voxel)surface
	bool in_surf;						//inside surface 2014/09/11
	bool p_fill;						//p fill 2015/09/11�
	bool root;							//root
	bool airP;							//airP
	unsigned ID;					//(refID) flag�ID
	unsigned short corner;	        //OpenGL� K�v�iconer 1� 2� 
	unsigned ColorID;			    //(ColorID)�F� ID

	//
	bool calc;							//
	int BrickN;						//Brick Number
	Lego(void);
	~Lego(void);
	void Initiaization(void);
};