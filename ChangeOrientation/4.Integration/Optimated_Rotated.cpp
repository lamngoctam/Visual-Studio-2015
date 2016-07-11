#include "../stdafx.h"

extern double MinVoxelL;					//Length of the model minimum voxel
extern double MinVoxelH;					//Height of the model minimum voxel
extern short OctLevels;

void Optimated_Rotated(Model& m, OctVoxel& bbox, double Rotated_Angle, CVector3d& min, CVector3d& max) {
	//=--------------------------------------------------------
	//------------ 2016 06 03
	//--------------  Roatated down model 2nd
//	CVector3d Vector_move(0.0, 0.0, 0.0);
//	bbox.origin;
//	Vector_move = bbox.origin;
//
//	vector<CVector3d> move1;
//	for (auto i(0); i < m.Octrees.size(); ++i) {
//		//move1.push_back(m.Octrees[i].origin - Vector_move);
//		move1.push_back(m.Octrees[i].origin);
//	}
//
//	for (auto i(0); i < m.Octrees.size(); ++i) { m.Octrees[i].origin.Clear();	}
//
//	double Theta = Rotated_Angle;
//
//	CVector3d W_(0.0, 0.0, 1.0);
//	CMatrix Rod1(3, 3); 
//	Rod1.SetZero();
//	
//	cout << "Theta " << Theta << endl;
//	Rod1.At(0, 0) = cos(Theta) + W_.x*W_.x*(1 - cos(Theta));
//	Rod1.At(1, 0) = W_.z*sin(Theta) + W_.x*W_.y*(1 - cos(Theta));
//	Rod1.At(2, 0) = -W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));
//
//	Rod1.At(0, 1) = W_.x*W_.y*(1 - cos(Theta)) - W_.z*sin(Theta);
//	Rod1.At(1, 1) = cos(Theta) + W_.y*W_.y*(1 - cos(Theta));
//	Rod1.At(2, 1) = W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));
//
//	Rod1.At(0, 2) = W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));
//	Rod1.At(1, 2) = -W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));
//	Rod1.At(2, 2) = cos(Theta) + W_.z*W_.z*(1 - cos(Theta));
//
//	for (auto i(0); i < move1.size(); ++i) {
//		CVector3d temp_vertexW(0.0, 0.0, 0.0);
//		temp_vertexW.x = Rod1.At(0, 0)*move1[i].x + Rod1.At(0, 1)*move1[i].y + Rod1.At(0, 2)*move1[i].z;
//		temp_vertexW.y = Rod1.At(1, 0)*move1[i].x + Rod1.At(1, 1)*move1[i].y + Rod1.At(1, 2)*move1[i].z;
//		temp_vertexW.z = Rod1.At(2, 0)*move1[i].x + Rod1.At(2, 1)*move1[i].y + Rod1.At(2, 2)*move1[i].z;
//		m.Octrees[i].origin = (temp_vertexW);				// change rotated_octrees to OXYZ
//	}

	//rotated 90degree
	vector<CVector3d> move2;
	for (auto i(0); i < m.Octrees.size(); ++i) { move2.push_back(m.Octrees[i].origin); }

	for (auto i(0); i < m.Octrees.size(); ++i) { m.Octrees[i].origin.Clear(); }

	//double Theta2 = Rotated_Angle; (50 * M_PI / 180);
	double Theta2 = -(90 * M_PI / 180);
	CVector3d W_(0.0, 0.0, 1.0);
	CMatrix Rod2(3, 3);
	Rod2.SetZero();

	cout << "Theta2 " << Theta2 << endl;
	Rod2.At(0, 0) = cos(Theta2) + W_.x*W_.x*(1 - cos(Theta2));
	Rod2.At(1, 0) = W_.z*sin(Theta2) + W_.x*W_.y*(1 - cos(Theta2));
	Rod2.At(2, 0) = -W_.y*sin(Theta2) + W_.x*W_.z*(1 - cos(Theta2));

	Rod2.At(0, 1) = W_.x*W_.y*(1 - cos(Theta2)) - W_.z*sin(Theta2);
	Rod2.At(1, 1) = cos(Theta2) + W_.y*W_.y*(1 - cos(Theta2));
	Rod2.At(2, 1) = W_.x*sin(Theta2) + W_.y*W_.z*(1 - cos(Theta2));

	Rod2.At(0, 2) = W_.y*sin(Theta2) + W_.x*W_.z*(1 - cos(Theta2));
	Rod2.At(1, 2) = -W_.x*sin(Theta2) + W_.y*W_.z*(1 - cos(Theta2));
	Rod2.At(2, 2) = cos(Theta2) + W_.z*W_.z*(1 - cos(Theta2));

	for (auto i(0); i < move2.size(); ++i) {
		CVector3d temp_vertexW(0.0, 0.0, 0.0);
		temp_vertexW.x = Rod2.At(0, 0)*move2[i].x + Rod2.At(0, 1)*move2[i].y + Rod2.At(0, 2)*move2[i].z;
		temp_vertexW.y = Rod2.At(1, 0)*move2[i].x + Rod2.At(1, 1)*move2[i].y + Rod2.At(1, 2)*move2[i].z;
		temp_vertexW.z = Rod2.At(2, 0)*move2[i].x + Rod2.At(2, 1)*move2[i].y + Rod2.At(2, 2)*move2[i].z;
		m.Octrees[i].origin = (temp_vertexW);				// change rotated_octrees to OXYZ
	}

	CVector3d OriginBBox[8];
	bbox.SetVertexWorld_Rotated(Rotated_Angle, OriginBBox);

	//Rotated origin Bounding box to RotatedBBox
	CVector3d RotatedBBox[8];
	RotatedBBox[0].x = Rod2.At(0, 0)*bbox.origin.x + Rod2.At(0, 1)*bbox.origin.y + Rod2.At(0, 2)*bbox.origin.z;
	RotatedBBox[0].y = Rod2.At(1, 0)*bbox.origin.x + Rod2.At(1, 1)*bbox.origin.y + Rod2.At(1, 2)*bbox.origin.z;
	RotatedBBox[0].z = Rod2.At(2, 0)*bbox.origin.x + Rod2.At(2, 1)*bbox.origin.y + Rod2.At(2, 2)*bbox.origin.z;


	CVector3d moveback_midpoint(0.0, 0.0, 0.0);
	moveback_midpoint = OriginBBox[3] - RotatedBBox[0];			//???????????????????????????

	vector<CVector3d> move_octree;
	for (auto i(0); i < m.Octrees.size(); ++i) {
		move_octree.push_back(m.Octrees[i].origin + moveback_midpoint);
		//move_octree.push_back(m.Octrees[i].origin );
	}

	for (auto i(0); i < move_octree.size(); ++i) { m.Octrees[i].origin.Clear(); }
	for (auto i(0); i < move_octree.size(); ++i) { m.Octrees[i].origin = move_octree[i]; }

	move_octree.clear();

		//--------------------------------------------------------------
}

