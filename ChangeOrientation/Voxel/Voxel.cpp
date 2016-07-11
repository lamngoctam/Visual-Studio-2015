#include "../Voxel.h"

extern float scale;


double Voxel::height;
double Voxel::length;

Voxel::Voxel()
{
	fill = false;
	surf = false; 
	dist = DBL_MAX;

	trial = false;
	unknown = true;
	known = false;	

	pic = false;

	coord.x = 0;
	coord.y = 0;
	coord.z = 0;

	normal.x = 0.0;
	normal.y = 0.0;
	normal.z = 0.0;

	pushed = false;
}

void Voxel::SetParameter(double width)
{
	length = width;
	height = scale * length;
}

void Voxel::SetOrigin(CVector3d& ori){
	this->origin = ori;
}

void Voxel::SetOrigin_Rotated(CVector3d& ori, double Rotated_Angle){

	this->origin.x = ori.x *cos(Rotated_Angle) - ori.y*sin(Rotated_Angle);
	this->origin.y = ori.x *sin(Rotated_Angle) + ori.y*cos(Rotated_Angle);
	this->origin.z = ori.z;
}

void Voxel::SetCenterOfGrabity()
{
	CVector3d x( this->length/2.0, 0.0, 0.0 );
	CVector3d y( 0.0, this->length/2.0, 0.0 );
	CVector3d z( 0.0, 0.0, this->height/2.0 );
	this->center = this->origin + x + y + z;
}

void Voxel::SetCenterOfGrabity_Rotated(double Rotated_Angle)
{
	CVector3d x(this->length / 2.0, 0.0, 0.0);
	CVector3d y(0.0, this->length / 2.0, 0.0);
	CVector3d z(0.0, 0.0, this->height / 2.0);

	CVector3d x_rotated = x *cos(Rotated_Angle) - y*sin(Rotated_Angle);
	CVector3d y_rotated = x *sin(Rotated_Angle) + y*cos(Rotated_Angle);
	CVector3d z_rotated = z;
	
	this->center = this->origin + x_rotated + y_rotated + z_rotated;
}

void Voxel::SetVertexWorld_Rotated_PCA(double Rotated_Angle, CVector3d* vertW){
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

double Voxel::Dist(Voxel a)
{
	double temp =
	sqrt( (this->center.x - a.center.x)*(this->center.x - a.center.x)
		+ (this->center.y - a.center.y)*(this->center.y - a.center.y)
		+ (this->center.z - a.center.z)*(this->center.z - a.center.z) );

	return temp;
}


void Voxel::SetTrial()
{
	trial = true;
	unknown = false;
	known = false;
}

void Voxel::SetKnown()
{
	trial = false;
	unknown = false;
	known = true;
}

void Voxel::SetCoord(int x,int y,int z)
{
	this->coord.x = x;
	this->coord.y = y;
	this->coord.z = z;
}

void Voxel::SetCoord_Rotated(int x, int y, int z, double Rotated_Angle)
{
	this->coord.x = x *cos(Rotated_Angle) - y*sin(Rotated_Angle);
	this->coord.y = x *sin(Rotated_Angle) + y*cos(Rotated_Angle);
	this->coord.z = z;

}
//
void Voxel::ClearDist()
{
	trial = false;
	unknown = true;
	known = false;
	
	pushed = false;

	dist = DBL_MAX;

}


void Voxel::CoordTrans(CMatrix& m, CVector3d* vertexW)
{
	Voxel am;	
	CMatrix temp(4,1);	
	for(int i(0); i<8 ; i++){

		temp(0,0) = vertexW[i].x;
		temp(1,0) = vertexW[i].y;
		temp(2,0) = vertexW[i].z;
		temp(3,0) = 1.0;
		
		temp = m*temp;
		
		vertexW[i].x = temp(0,0);
		vertexW[i].y = temp(1,0); 
		vertexW[i].z = temp(2,0); 
	}

}

void Voxel::SetVertexWorld(CVector3d* vertW){


	CVector3d x( length, 0.0, 0.0 );
	CVector3d y( 0.0, length, 0.0 );
	CVector3d z( 0.0, 0.0, height );		

	vertW[0] = this->origin;
	vertW[1] = this->origin     + x;
	vertW[2] = this->origin     + x + y;
	vertW[3] = this->origin     + y;
	vertW[4] = this->origin + z;
	vertW[5] = this->origin + z + x;
	vertW[6] = this->origin + z + x + y;
	vertW[7] = this->origin + z + y;
}





//
cv::Point Voxel::CalcImageCoordofCenter(CMatrix ART)
{
	cv::Point coord(0,0);
	CVector temp(4);
	temp[3] = 1.0;

	temp[0] = this->center.x;
	temp[1] = this->center.y;
	temp[2] = this->center.z;

	temp = ART*temp;
	coord.x = (int)(temp[0]/temp[2]); 
	coord.y = (int)(temp[1]/temp[2]);
	
	return coord;
}

