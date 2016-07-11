#include "../Voxel.h"

extern float scale;
extern int ImageNum;


OctVoxel::OctVoxel()
{


	this->Orientation_Angle = 0.0;

	this->origin.Clear();

	this->in = false;
	this->out = false;
	this->amb = false;

	this->Center_Octrees.Clear();
}

OctVoxel::OctVoxel(double width)
{
	this->length = width;
	this->height = scale * length;

	this->LV = 0;
	this->in = false;
	this->out = false;
	this->amb = false;
}

void OctVoxel::SetParameter(double width)
{
	this->length = width;
	this->height = scale * length;
	this->in = false;
	this->out = false;
	this->amb = false;
}


void OctVoxel::SetOrigin(CVector3d& ori){
	this->origin = ori;
}

void OctVoxel::SetVertexWorld(CVector3d* vertW)
//
{
	//8 vertices world coordinates of the voxel (x,y,z)
	CVector3d x(length, 0.0, 0.0);
	CVector3d y(0.0, length, 0.0);
	CVector3d z(0.0, 0.0, height);

	vertW[0] = this->origin;
	vertW[1] = this->origin + x;
	vertW[2] = this->origin + x + y;
	vertW[3] = this->origin + y;
	vertW[4] = this->origin + z;
	vertW[5] = this->origin + z + x;
	vertW[6] = this->origin + z + x + y;
	vertW[7] = this->origin + z + y;

}


void OctVoxel::SetVertexWorld_Rotated(double Rotated_Angle, CVector3d* vertW)
//
{
	//8 vertices world coordinates of the voxel (x,y,z)
	CVector3d x(length, 0.0, 0.0);
	CVector3d y(0.0, length, 0.0);
	CVector3d z(0.0, 0.0, height);

	CVector3d x_rotated = x *cos(Rotated_Angle) - y*sin(Rotated_Angle);
	CVector3d y_rotated = x *sin(Rotated_Angle) + y*cos(Rotated_Angle);
	CVector3d z_rotated = z;

	vertW[0] = this->origin;
	vertW[1] = this->origin + x_rotated;
	vertW[2] = this->origin + x_rotated + y_rotated;
	vertW[3] = this->origin + y_rotated;
	vertW[4] = this->origin + z_rotated;
	vertW[5] = this->origin + z_rotated + x_rotated;
	vertW[6] = this->origin + z_rotated + x_rotated + y_rotated;
	vertW[7] = this->origin + z_rotated + y_rotated;

}

void OctVoxel::SetVertexWorld_6(CVector3d& vertW)		//
{
	//W(x,y,z)
	CVector3d x(length, 0.0, 0.0);
	CVector3d y(0.0, length, 0.0);
	CVector3d z(0.0, 0.0, height);
	vertW = this->origin + z + x + y;
}

void OctVoxel::SetVertexWorld_6_Rotated(double Rotated_Angle, CVector3d& vertW)		//
{
	//W(x,y,z)

	//8 vertices world coordinates of the voxel (x,y,z)
	CVector3d x(length, 0.0, 0.0);
	CVector3d y(0.0, length, 0.0);
	CVector3d z(0.0, 0.0, height);

	CVector3d x_rotated = x *cos(Rotated_Angle) - y*sin(Rotated_Angle);
	CVector3d y_rotated = x *sin(Rotated_Angle) + y*cos(Rotated_Angle);
	CVector3d z_rotated = z;

	vertW = this->origin + x_rotated + y_rotated + z_rotated;
}

void OctVoxel::SetVertexWorld_Center_Rotated(double Rotated_Angle, CVector3d& vertW)		//
{
	//W(x,y,z)

	//8 vertices world coordinates of the voxel (x,y,z)
	CVector3d x(length / 2.0, 0.0, 0.0);
	CVector3d y(0.0, length / 2.0, 0.0);
	CVector3d z(0.0, 0.0, height / 2.0);

	CVector3d x_rotated = x *cos(Rotated_Angle) - y*sin(Rotated_Angle);
	CVector3d y_rotated = x *sin(Rotated_Angle) + y*cos(Rotated_Angle);
	CVector3d z_rotated = z;

	vertW = this->origin + x_rotated + y_rotated + z_rotated;
}
void OctVoxel::SetVertexWorld_Center_(CVector3d& vertW)		//
{
	//W(x,y,z)

	//8 vertices world coordinates of the voxel (x,y,z)
	CVector3d x(length / 2.0, 0.0, 0.0);
	CVector3d y(0.0, length / 2.0, 0.0);
	CVector3d z(0.0, 0.0, height / 2.0);

	vertW = this->origin + x + y + z;
}

void OctVoxel::Set_Middle_World(CVector3d* vertW)
//
{
	//8 vertices world coordinates of the voxel (x,y,z)
	CVector3d x(length / 2.0, 0.0, 0.0);
	CVector3d y(0.0, length / 2.0, 0.0);
	CVector3d z(0.0, 0.0, height / 2.0);

	vertW[0] = this->origin - x - y - z;                 // origin at middle of bounding box
	vertW[1] = this->origin + x - y - z;
	vertW[2] = this->origin + x + y - z;
	vertW[3] = this->origin - x + y - z;
	vertW[4] = this->origin - x - y + z;
	vertW[5] = this->origin + x - y + z;
	vertW[6] = this->origin + x + y + z;
	vertW[7] = this->origin - x + y + z;
}


void OctVoxel::OutputInformation()
{
	cout << "l(length):" << length << endl;
	cout << "height:" << height << endl;
	cout << "LV(level):" << LV << endl;
	cout << "Inside:" << in << endl;
	cout << "Outside:" << out << endl;
	cout << "Ambiguous:" << amb << endl;

	//for(int i(0); i<8; ++i)
	//	cout<<"( "<<vertexW[i].x<<" , "<<vertexW[i].y<<" , "<<vertexW[i].z <<" )"<<endl;

}
