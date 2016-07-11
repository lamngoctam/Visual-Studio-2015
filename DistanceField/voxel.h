#ifndef VOXEL_H
#define VOXEL_H

#include "stdafx.h"

struct Point3d
{
	double r[3];

	Point3d()
	{
		r[0] = r[1] = r[2] = 0.0;
	}

	Point3d(double a, double b, double c)
	{
		this->r[0] = a;
		this->r[1] = b;
		this->r[2] = c;
	}

	Point3d(double* rr)
	{
		this->r[0] = rr[0];
		this->r[1] = rr[1];
		this->r[2] = rr[2];
	}

};

class Box{
public:
	bool Fill;		
	bool Surf;		
	bool surf;
	bool Edge;		
	bool Pic;		
	bool calc;		
	double Dist;	
	Point3d Color;
	CColor C;		
	int Status;
	int num;
	CVector3d Normal;
	Box(){
	Fill=false;
	Surf=false;
	surf=false;
	calc=false;
	num=0;
	Status=0;
	}
	~Box(){}
};

class VoxCoord{
public:
	int Coord[3];
};

class Voxel{
public:
	int ND[3];				//number of division x,y,z•
	int SurfNum;		
	double Length;		

	CVector3d OriPt;	
	CVector3d Cent;		

	Box ***Grid3D;		

	//void VoxInit();	
	//void FindVoxSurf();
	void Fillcontent();
};



#endif
