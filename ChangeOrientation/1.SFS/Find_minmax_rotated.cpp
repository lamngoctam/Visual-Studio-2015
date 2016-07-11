

#include "../stdafx.h"

extern OctVoxel Angle_;

extern CVector3d VertexMin_;	//origin
extern CVector3d VertexMax_;	//Diagonal point of origin

//Bounding Box‚(x,y,z)X,Y,Z
void Find_minmax_rotated(Model& m, vector<CVector3d>& New_center_octrees, CVector3d& min, CVector3d& max, double MinVoxelL, double MinVoxelH)
{

	cout << "Find_minmax_rotated\n";
	vector<CVector3d> vertex_origin;
	vector<CVector3d> vertex_peak;

	CVector3d x(MinVoxelL/2, 0.0, 0.0);
	CVector3d y(0.0, MinVoxelL/2, 0.0);
	CVector3d z(0.0, 0.0, MinVoxelH/2);
	
	for (int i(0); i < m.Octrees.size(); ++i){
		vertex_origin.push_back(New_center_octrees[i] -x - y- z);
		vertex_peak.push_back(New_center_octrees[i] + z + x + y);

		if (vertex_origin[i].x <= min.x){ min.x = vertex_origin[i].x; }
		if (vertex_origin[i].y <= min.y){ min.y = vertex_origin[i].y; }
		if (vertex_origin[i].z <= min.z){ min.z = vertex_origin[i].z; }

		if (vertex_peak[i].x >= max.x){ max.x = vertex_peak[i].x; }
		if (vertex_peak[i].y >= max.y){ max.y = vertex_peak[i].y; }
		if (vertex_peak[i].z >= max.z){ max.z = vertex_peak[i].z; }

	}

	m.P_IntersecPoint[0] = min;
	m.P_IntersecPoint[1].x = max.x;
	m.P_IntersecPoint[1].y = min.y;
	m.P_IntersecPoint[1].z = min.z;
	m.P_IntersecPoint[2].x = max.x;
	m.P_IntersecPoint[2].y = max.y;
	m.P_IntersecPoint[2].z = min.z;
	m.P_IntersecPoint[3].x = min.x;
	m.P_IntersecPoint[3].y = max.y;
	m.P_IntersecPoint[3].z = min.z;
	m.P_IntersecPoint[4].x = min.x;
	m.P_IntersecPoint[4].y = min.y;
	m.P_IntersecPoint[4].z = max.z;
	m.P_IntersecPoint[5].x = max.x;
	m.P_IntersecPoint[5].y = min.y;
	m.P_IntersecPoint[5].z = max.z;
	m.P_IntersecPoint[6] = max;
	m.P_IntersecPoint[7].x = min.x;
	m.P_IntersecPoint[7].y = max.y;
	m.P_IntersecPoint[7].z = max.z;


	//
	m.num[0] = (int)((max.x - min.x) / MinVoxelL);	//X-Axis number of voxel 
	m.num[1] = (int)((max.y - min.y) / MinVoxelL);	//Y-Axis
	m.num[2] = (int)((max.z - min.z) / MinVoxelH);	//Z-Axis

	m.VoxelNum = m.num[0] * m.num[1] * m.num[2];
	cout << "Number of voxel before create a new bbox : " << m.num[0] << "*" << m.num[1] << "*" << m.num[2] << "*" << m.VoxelNum << endl;


	max.x = max.x + MinVoxelL;
	max.y = max.y + MinVoxelL;
	max.z = max.z + MinVoxelH;

	min.x = min.x - MinVoxelL;
	min.y = min.y - MinVoxelL;
	min.z = min.z - MinVoxelH;

	m.New_smallcubicvertex[0] = min;
	m.New_smallcubicvertex[1].x = max.x;
	m.New_smallcubicvertex[1].y = min.y;
	m.New_smallcubicvertex[1].z = min.z;
	m.New_smallcubicvertex[2].x = max.x;
	m.New_smallcubicvertex[2].y = max.y;
	m.New_smallcubicvertex[2].z = min.z;
	m.New_smallcubicvertex[3].x = min.x;
	m.New_smallcubicvertex[3].y = max.y;
	m.New_smallcubicvertex[3].z = min.z;
	m.New_smallcubicvertex[4].x = min.x;
	m.New_smallcubicvertex[4].y = min.y;
	m.New_smallcubicvertex[4].z = max.z;
	m.New_smallcubicvertex[5].x = max.x;
	m.New_smallcubicvertex[5].y = min.y;
	m.New_smallcubicvertex[5].z = max.z;
	m.New_smallcubicvertex[6] = max;
	m.New_smallcubicvertex[7].x = min.x;
	m.New_smallcubicvertex[7].y = max.y;
	m.New_smallcubicvertex[7].z = max.z;


	m.num[0] = (int)((max.x - min.x) / MinVoxelL);	//X-Axis number of voxel 
	m.num[1] = (int)((max.y - min.y) / MinVoxelL);	//Y-Axis
	m.num[2] = (int)((max.z - min.z) / MinVoxelH);	//Z-Axis

	m.VoxelNum = m.num[0] * m.num[1] * m.num[2];
	cout << "Number of voxel after create a new bbox : " << m.num[0] << "*" << m.num[1] << "*" << m.num[2] << "*" << m.VoxelNum << endl;


}

void DrawBoundary_Octrees(Model& m, double Theta, CVector3d& min, CVector3d& max, CVector3d& vector_move){

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

	CVector3d Boundary_rotated[8];
	CVector3d Extern_Boundary_rotated[8];
	CVector3d move_vertexW[8];
	CVector3d Extern_move_vertexW[8];

	for (int i(0); i < 8; ++i){
		move_vertexW[i] = m.P_IntersecPoint[i];
		Extern_move_vertexW[i] = m.New_smallcubicvertex[i];
	}

	for (int i(0); i < 8; ++i){
		CVector3d temp_vertexW(0.0, 0.0, 0.0);
		temp_vertexW.x = Rodrigues.At(0, 0)*move_vertexW[i].x + Rodrigues.At(0, 1)*move_vertexW[i].y + Rodrigues.At(0, 2)*move_vertexW[i].z;
		temp_vertexW.y = Rodrigues.At(1, 0)*move_vertexW[i].x + Rodrigues.At(1, 1)*move_vertexW[i].y + Rodrigues.At(1, 2)*move_vertexW[i].z;
		temp_vertexW.z = Rodrigues.At(2, 0)*move_vertexW[i].x + Rodrigues.At(2, 1)*move_vertexW[i].y + Rodrigues.At(2, 2)*move_vertexW[i].z;
		Boundary_rotated[i] = temp_vertexW;
		m.P_IntersecPoint[i].Clear();
	}
	
	for (int i(0); i < 8; ++i){
		m.P_IntersecPoint[i] = Boundary_rotated[i] +vector_move;
	}

	for (int i(0); i < 8; ++i){
		CVector3d temp_vertexW(0.0, 0.0, 0.0);
		temp_vertexW.x = Rodrigues.At(0, 0)*Extern_move_vertexW[i].x + Rodrigues.At(0, 1)*Extern_move_vertexW[i].y + Rodrigues.At(0, 2)*Extern_move_vertexW[i].z;
		temp_vertexW.y = Rodrigues.At(1, 0)*Extern_move_vertexW[i].x + Rodrigues.At(1, 1)*Extern_move_vertexW[i].y + Rodrigues.At(1, 2)*Extern_move_vertexW[i].z;
		temp_vertexW.z = Rodrigues.At(2, 0)*Extern_move_vertexW[i].x + Rodrigues.At(2, 1)*Extern_move_vertexW[i].y + Rodrigues.At(2, 2)*Extern_move_vertexW[i].z;
		Extern_Boundary_rotated[i] = temp_vertexW;
		m.New_smallcubicvertex[i].Clear();
	}

	for (int i(0); i < 8; ++i){
		m.New_smallcubicvertex[i] = Extern_Boundary_rotated[i] +vector_move;
	}

}