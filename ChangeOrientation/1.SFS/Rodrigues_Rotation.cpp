#include "../stdafx.h"

extern int ImageNum;
//extern CMatrix *ART;
extern double MinVoxelL;					//Length of the model minimum voxel
extern double MinVoxelH;					//Height of the model minimum voxel
extern Model UP;
void Find_minmax_rotated(Model& m, vector<CVector3d>& New_center_octrees, CVector3d& min, CVector3d& max, double MinVoxelL, double MinVoxelH);
void DrawBoundary_Octrees(Model& m, double Theta, CVector3d& min, CVector3d& max, CVector3d& vector_move);

void Find_Rodrigues_Formular(OctVoxel& box, double Theta, Cpixel** vertex2D, CMatrix* ART){

	CVector3d W_(0.0, 0.0, 1.0);
	CVector3d New_vertexW[8];
	CVector3d vertexW[8];
	//box.Set_Middle_World(vertexW);
	box.SetVertexWorld_Rotated(Theta,vertexW);
	CVector3d back_vertexW[8];
	CVector3d move_vertexW[8];

	CVector3d midpoint(0.0, 0.0, 0.0);
	midpoint = (vertexW[0] + vertexW[6]) / 2.0;
	//midpoint = box.origin;
	cout <<"midpoint of big bbox "<< " " << midpoint.x << " " << midpoint.y << " " << midpoint.z << endl;
	getchar();

	for (int i(0); i < 8; ++i){
		move_vertexW[i] = vertexW[i] - midpoint;
	}

	CMatrix Rodrigues(3, 3);

	Rodrigues.At(0, 0) = cos(Theta) + W_.x*W_.x*(1 - cos(Theta));
	Rodrigues.At(1, 0) = W_.z*sin(Theta) + W_.x*W_.y*(1 - cos(Theta));
	Rodrigues.At(2, 0) = -W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));

	Rodrigues.At(0, 1) = W_.x*W_.y*(1 - cos(Theta)) - W_.z*sin(Theta);
	Rodrigues.At(1, 1) = cos(Theta) + W_.y*W_.y*(1 - cos(Theta));
	Rodrigues.At(2, 1) = W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));

	Rodrigues.At(0, 2) = W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));
	Rodrigues.At(1, 2) = -W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));
	Rodrigues.At(2, 2) = cos(Theta) + W_.z*W_.z*(1 - cos(Theta));

	for (int i(0); i < 8; ++i){
		New_vertexW[i].x = Rodrigues.At(0, 0)*move_vertexW[i].x + Rodrigues.At(0, 1)*move_vertexW[i].y + Rodrigues.At(0, 2)*move_vertexW[i].z;
		New_vertexW[i].y = Rodrigues.At(1, 0)*move_vertexW[i].x + Rodrigues.At(1, 1)*move_vertexW[i].y + Rodrigues.At(1, 2)*move_vertexW[i].z;
		New_vertexW[i].z = Rodrigues.At(2, 0)*move_vertexW[i].x + Rodrigues.At(2, 1)*move_vertexW[i].y + Rodrigues.At(2, 2)*move_vertexW[i].z;
		//cout <<"new "<< New_vertexW[i].x << " " << New_vertexW[i].y << " " << New_vertexW[i].z << endl;
	}
	for (int i(0); i < 8; ++i){
		back_vertexW[i] = New_vertexW[i] + midpoint;
		//cout << "back " << back_vertexW[i].x << " " << back_vertexW[i].y << " " << back_vertexW[i].z << endl;
	}

	CVector M(4);		//Homogeneous coordinates of the vertices(x,y,z,1) world coordinate
	CVector m(4);		//That the image coordinates (normalized) expressed in homogeneous coordinates
	M[3] = 1.0;

	for (int j = 0; j < ImageNum; ++j){		//36 image
		for (int k = 0; k < 8; ++k){	//8 vertices of the voxel
			M[0] = back_vertexW[k].x;
			M[1] = back_vertexW[k].y;
			M[2] = back_vertexW[k].z;
			m = ART[j] * M;
			vertex2D[j][k].setPixel_u_v((int)(m[0] / m[2]), (int)(m[1] / m[2]));  // normalize
		}
	}


	//Set_Origin_Boundingbox

}


void Rodrigues_Function(double Theta, vector<CVector3d>& move_vertexW, vector<CVector3d>& back_vertexW, CVector3d& vector_move){

	vector<CVector3d> New_center_octrees;
	CVector3d W_(0.0, 0.0, 1.0);
	CMatrix Rodrigues(3, 3);
	Rodrigues.SetZero();

	Rodrigues.At(0, 0) = cos(Theta) + W_.x*W_.x*(1 - cos(Theta));
	Rodrigues.At(1, 0) = W_.z*sin(Theta) + W_.x*W_.y*(1 - cos(Theta));
	Rodrigues.At(2, 0) = -W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));

	Rodrigues.At(0, 1) = W_.x*W_.y*(1 - cos(Theta)) - W_.z*sin(Theta);
	Rodrigues.At(1, 1) = cos(Theta) + W_.y*W_.y*(1 - cos(Theta));
	Rodrigues.At(2, 1) = W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));

	Rodrigues.At(0, 2) = W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));
	Rodrigues.At(1, 2) = -W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));
	Rodrigues.At(2, 2) = cos(Theta) + W_.z*W_.z*(1 - cos(Theta));

	cout << "Rodrigues_Function\n";

	for (int i(0); i < move_vertexW.size(); ++i){
		CVector3d temp_vertexW(0.0, 0.0, 0.0);
		temp_vertexW.x = Rodrigues.At(0, 0)*move_vertexW[i].x + Rodrigues.At(0, 1)*move_vertexW[i].y + Rodrigues.At(0, 2)*move_vertexW[i].z;
		temp_vertexW.y = Rodrigues.At(1, 0)*move_vertexW[i].x + Rodrigues.At(1, 1)*move_vertexW[i].y + Rodrigues.At(1, 2)*move_vertexW[i].z;
		temp_vertexW.z = Rodrigues.At(2, 0)*move_vertexW[i].x + Rodrigues.At(2, 1)*move_vertexW[i].y + Rodrigues.At(2, 2)*move_vertexW[i].z;
		New_center_octrees.push_back(temp_vertexW);
				
	}

	CVector3d upMin(0.0, 0.0, 0.0);	//origin
	CVector3d upMax(0.0, 0.0, 0.0);			//Diagonal point of origin


	Find_minmax_rotated(UP, New_center_octrees, upMin, upMax, MinVoxelL, MinVoxelH);
	cout << "New_center_octrees.size " << New_center_octrees.size() << endl;

	DrawBoundary_Octrees(UP, (-Theta), upMin, upMax, vector_move);

	vector<CVector3d> Back_Origin;
	Theta = -Theta;
	Rodrigues.SetZero();

	Rodrigues.At(0, 0) = cos(Theta) + W_.x*W_.x*(1 - cos(Theta));
	Rodrigues.At(1, 0) = W_.z*sin(Theta) + W_.x*W_.y*(1 - cos(Theta));
	Rodrigues.At(2, 0) = -W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));

	Rodrigues.At(0, 1) = W_.x*W_.y*(1 - cos(Theta)) - W_.z*sin(Theta);
	Rodrigues.At(1, 1) = cos(Theta) + W_.y*W_.y*(1 - cos(Theta));
	Rodrigues.At(2, 1) = W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));

	Rodrigues.At(0, 2) = W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));
	Rodrigues.At(1, 2) = -W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));
	Rodrigues.At(2, 2) = cos(Theta) + W_.z*W_.z*(1 - cos(Theta));

	for (int i(0); i < New_center_octrees.size(); ++i){

		CVector3d temp_vertexW(0.0, 0.0, 0.0);
		temp_vertexW.x = Rodrigues.At(0, 0)*New_center_octrees[i].x + Rodrigues.At(0, 1)*New_center_octrees[i].y + Rodrigues.At(0, 2)*New_center_octrees[i].z;
		temp_vertexW.y = Rodrigues.At(1, 0)*New_center_octrees[i].x + Rodrigues.At(1, 1)*New_center_octrees[i].y + Rodrigues.At(1, 2)*New_center_octrees[i].z;
		temp_vertexW.z = Rodrigues.At(2, 0)*New_center_octrees[i].x + Rodrigues.At(2, 1)*New_center_octrees[i].y + Rodrigues.At(2, 2)*New_center_octrees[i].z;
		Back_Origin.push_back(temp_vertexW);

		//cout <<"new "<< New_Origin[i].x << " " << New_Origin[i].y << " " << New_Origin[i].z << endl;
	}

	for (int i(0); i < move_vertexW.size(); ++i){
		back_vertexW.push_back(Back_Origin[i]+vector_move);
		//cout << i<<"-back " << back_vertexW[i].x << " " << back_vertexW[i].y << " " << back_vertexW[i].z << endl;
	}

	Back_Origin.clear();
	New_center_octrees.clear();
}
