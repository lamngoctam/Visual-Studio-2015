#include "../stdafx.h"

extern double MinVoxelL;					//Length of the model minimum voxel
extern double MinVoxelH;					//Height of the model minimum voxel

extern CVector3d VertexMin_;					//origin
extern CVector3d VertexMax_;					//Diagonal point of origin

extern vector<CVector3d> Origin_;
extern CVector3d BBox_Origin;

extern OctVoxel UpBoundingBox;
extern OctVoxel DownBoundingBox;

vector<CVector3d> back_octree;
extern OctVoxel Angle_;



void Rodrigues_Function(double Theta, vector<CVector3d>& move_vertexW, vector<CVector3d>& back_vertexW, CVector3d& midpoint);


//2016/5/15
void Find_Scale_Bbox(Model& m, OctVoxel& box, vector<OctVoxel>& scale_box, double Rotated_Angle){
	cout << "Find_Scale_Bbox \n";

	CVector3d Vector_move(0.0, 0.0, 0.0);

	UpBoundingBox.origin;

	CVector3d x(UpBoundingBox.length / 2.0, 0.0, 0.0);
	CVector3d y(0.0, UpBoundingBox.length / 2.0, 0.0);
	CVector3d z(0.0, 0.0, UpBoundingBox.height / 2.0);

	CVector3d vertexW[8];

	CVector3d x_rotated = x *cos(Rotated_Angle) - y*sin(Rotated_Angle);
	CVector3d y_rotated = x *sin(Rotated_Angle) + y*cos(Rotated_Angle);
	CVector3d z_rotated = z;

	//Vector_move = UpBoundingBox.origin +z_rotated + x_rotated + y_rotated;
	CVector3d SumCenterVertex(0.0, 0.0, 0.0);
	int numVertexPoint = 0;

	for (auto i(0); i < m.Octrees.size(); ++i){
		SumCenterVertex += m.Octrees[i].Center_Octrees;
		numVertexPoint++;
	}
	Vector_move = (1.0 / (double)numVertexPoint)*SumCenterVertex;
	//cout << "Center: " << Vector_move.x << " " << Vector_move.y << " " << Vector_move.z << endl;

	vector<CVector3d> move_center_octree;

	for (auto i(0); i < m.Octrees.size(); ++i){
		move_center_octree.push_back(m.Octrees[i].Center_Octrees - Vector_move);
		//cout << i<<"-new " << m.min_vertex_point[i].x << " " << m.min_vertex_point[i].y << " " << m.min_vertex_point[i].z << endl;
	}

	//Vector_move = UpBoundingBox.origin;
	//
	//vector<CVector3d> move_center_octree;
	//for (auto i(0); i < m.Octrees.size(); ++i){
	//	move_center_octree.push_back(m.Octrees[i].origin - Vector_move);
	//
	//}


	Rodrigues_Function((-Rotated_Angle), move_center_octree, back_octree, Vector_move);

	move_center_octree.clear();

	getchar();
}

