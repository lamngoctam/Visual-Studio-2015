
#include "../stdafx.h"

extern double MinVoxelL;					//Length of the model minimum voxel
extern double MinVoxelH;					//Height of the model minimum voxel
extern short OctLevels;


//extern OctVoxel UpBoundingBox;
vector<CVector3d> New_peak_octrees;
CVector3d moveback_midpoint(0.0, 0.0, 0.0);



void Check_Plane2(Model& m, OctVoxel& boundingbox, double Rotated_Angle, CVector3d& min, CVector3d& max, CVector3d& newCentbox) {

	vector<CVector3d> move_vertexW;
	for (auto i(0); i < m.Octrees.size(); ++i) {
		//move_vertexW.push_back(m.Octrees[i].origin - Vector_move);
		move_vertexW.push_back(m.Octrees[i].origin);
	}

	for (auto i(0); i < m.Octrees.size(); ++i) {
		m.Octrees[i].origin.Clear();
	}
	double Theta = Rotated_Angle;

	CVector3d W_(0.0, 0.0, 1.0);
	CMatrix Rodrigues(3, 3);  //matrix rotation
	Rodrigues.SetZero();

	cout << "Theta " << Theta << endl;
	Rodrigues.At(0, 0) = cos(Theta) + W_.x*W_.x*(1 - cos(Theta));
	Rodrigues.At(1, 0) = W_.z*sin(Theta) + W_.x*W_.y*(1 - cos(Theta));
	Rodrigues.At(2, 0) = -W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));

	Rodrigues.At(0, 1) = W_.x*W_.y*(1 - cos(Theta)) - W_.z*sin(Theta);
	Rodrigues.At(1, 1) = cos(Theta) + W_.y*W_.y*(1 - cos(Theta));
	Rodrigues.At(2, 1) = W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));

	Rodrigues.At(0, 2) = W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));
	Rodrigues.At(1, 2) = -W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));
	Rodrigues.At(2, 2) = cos(Theta) + W_.z*W_.z*(1 - cos(Theta));

	for (auto i(0); i < move_vertexW.size(); ++i) {
		CVector3d temp_vertexW(0.0, 0.0, 0.0);
		temp_vertexW.x = Rodrigues.At(0, 0)*move_vertexW[i].x + Rodrigues.At(0, 1)*move_vertexW[i].y + Rodrigues.At(0, 2)*move_vertexW[i].z;
		temp_vertexW.y = Rodrigues.At(1, 0)*move_vertexW[i].x + Rodrigues.At(1, 1)*move_vertexW[i].y + Rodrigues.At(1, 2)*move_vertexW[i].z;
		temp_vertexW.z = Rodrigues.At(2, 0)*move_vertexW[i].x + Rodrigues.At(2, 1)*move_vertexW[i].y + Rodrigues.At(2, 2)*move_vertexW[i].z;
		m.Octrees[i].origin = (temp_vertexW);				// change rotated_octrees to OXYZ
	}

	//for (auto i(0); i < move_octree.size(); ++i) { m.Octrees[i].origin.Clear(); }
	//for (auto i(0); i < move_octree.size(); ++i) { m.Octrees[i].origin = move_octree[i]; }
	//
	////--------------------------------------------------------------//
	//for (auto i(0); i < m.Octrees.size(); ++i) {				//save Center of Octrees
	//	CVector3d Centervertex(0.0, 0.0, 0.0);
	//	m.Octrees[i].SetVertexWorld_Center_(Centervertex);
	//	m.New_center_octrees.push_back(Centervertex);
	//	m.Octrees[i].Center_Octrees = Centervertex;			//will be cleared at Octree_to_voxel
	//}
	//for (auto i(0); i < m.Octrees.size(); ++i) {				//save Peak6 of Octrees
	//	CVector3d peakvertex(0.0, 0.0, 0.0);
	//	m.Octrees[i].SetVertexWorld_6(peakvertex);
	//	New_peak_octrees.push_back(peakvertex);
	//}
	move_vertexW.clear();
	//----------------------------------------
	//Rotated Bounding box
	CVector3d RodCentBox(0.0, 0.0, 0.0);
	boundingbox.SetVertexWorld_Center_Rotated(Rotated_Angle, RodCentBox);
	
	newCentbox.x = Rodrigues.At(0, 0)*RodCentBox.x + Rodrigues.At(0, 1)*RodCentBox.y + Rodrigues.At(0, 2)*RodCentBox.z;
	newCentbox.y = Rodrigues.At(1, 0)*RodCentBox.x + Rodrigues.At(1, 1)*RodCentBox.y + Rodrigues.At(1, 2)*RodCentBox.z;
	newCentbox.z = Rodrigues.At(2, 0)*RodCentBox.x + Rodrigues.At(2, 1)*RodCentBox.y + Rodrigues.At(2, 2)*RodCentBox.z;
	
}


void Check_Plane3(Model& m, OctVoxel& boundingbox, double Rotated_Angle, CVector3d& min, CVector3d& max) {

	CVector3d Vector_move(0.0, 0.0, 0.0);
	boundingbox.SetVertexWorld_Center_Rotated(Rotated_Angle, Vector_move);
	//Vector_move = boundingbox.origin;

	vector<CVector3d> move_vertexW;
	for (auto i(0); i < m.Octrees.size(); ++i) {
		//move_vertexW.push_back(m.Octrees[i].origin - Vector_move);
		move_vertexW.push_back(m.Octrees[i].origin);
	}

	for (auto i(0); i < m.Octrees.size(); ++i) {
		m.Octrees[i].origin.Clear();
	}
	double Theta = Rotated_Angle;

	CVector3d W_(0.0, 0.0, 1.0);
	CMatrix Rodrigues(3, 3);  //matrix rotation
	Rodrigues.SetZero();

	cout << "Theta " << Theta << endl;
	Rodrigues.At(0, 0) = cos(Theta) + W_.x*W_.x*(1 - cos(Theta));
	Rodrigues.At(1, 0) = W_.z*sin(Theta) + W_.x*W_.y*(1 - cos(Theta));
	Rodrigues.At(2, 0) = -W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));

	Rodrigues.At(0, 1) = W_.x*W_.y*(1 - cos(Theta)) - W_.z*sin(Theta);
	Rodrigues.At(1, 1) = cos(Theta) + W_.y*W_.y*(1 - cos(Theta));
	Rodrigues.At(2, 1) = W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));

	Rodrigues.At(0, 2) = W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));
	Rodrigues.At(1, 2) = -W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));
	Rodrigues.At(2, 2) = cos(Theta) + W_.z*W_.z*(1 - cos(Theta));

	for (auto i(0); i < move_vertexW.size(); ++i) {
		CVector3d temp_vertexW(0.0, 0.0, 0.0);
		temp_vertexW.x = Rodrigues.At(0, 0)*move_vertexW[i].x + Rodrigues.At(0, 1)*move_vertexW[i].y + Rodrigues.At(0, 2)*move_vertexW[i].z;
		temp_vertexW.y = Rodrigues.At(1, 0)*move_vertexW[i].x + Rodrigues.At(1, 1)*move_vertexW[i].y + Rodrigues.At(1, 2)*move_vertexW[i].z;
		temp_vertexW.z = Rodrigues.At(2, 0)*move_vertexW[i].x + Rodrigues.At(2, 1)*move_vertexW[i].y + Rodrigues.At(2, 2)*move_vertexW[i].z;
		m.Octrees[i].origin = (temp_vertexW);				// change rotated_octrees to OXYZ
	}
	move_vertexW.clear();



	//	//---------------------------------------
	//	cout << "Find_minmax_rotated\n";
	//	vector<CVector3d> vertex_peak;
	//
	//	CVector3d x(MinVoxelL, 0.0, 0.0);
	//	CVector3d y(0.0, MinVoxelL, 0.0);
	//	CVector3d z(0.0, 0.0, MinVoxelH);
	//
	//	for (int i(0); i < m.Octrees.size(); ++i) {
	//		vertex_peak.push_back(m.Octrees[i].origin + x + y + z);
	//
	//		if (m.Octrees[i].origin.x <= min.x) { min.x = m.Octrees[i].origin.x; }
	//		if (m.Octrees[i].origin.y <= min.y) { min.y = m.Octrees[i].origin.y; }
	//		if (m.Octrees[i].origin.z <= min.z) { min.z = m.Octrees[i].origin.z; }
	//
	//		if (vertex_peak[i].x >= max.x) { max.x = vertex_peak[i].x; }
	//		if (vertex_peak[i].y >= max.y) { max.y = vertex_peak[i].y; }
	//		if (vertex_peak[i].z >= max.z) { max.z = vertex_peak[i].z; }
	//
	//	}
	//	vertex_peak.clear();
	//	//find mid point of origin bounding box
	//	CVector3d OriginBBox[8];
	//	boundingbox.SetVertexWorld_Rotated(Rotated_Angle, OriginBBox);
	//
	//	CVector3d OriginTop(0.0, 0.0, 0.0);
	//	CVector3d OriginBot(0.0, 0.0, 0.0);
	//	CVector3d OriginMid(0.0, 0.0, 0.0);
	//
	//	OriginTop = (OriginBBox[4] + OriginBBox[6]) / 2.0;
	//	OriginBot = (OriginBBox[0] + OriginBBox[2]) / 2.0;
	//	OriginMid = (OriginTop + OriginBot) / 2.0;
	//
	//	//------------------
	//	CVector3d MidRotatedBBox(0.0, 0.0, 0.0);
	//	CVector3d RotBBox(0.0, 0.0, 0.0);
	//	MidRotatedBBox = (min + max) / 2.0;
	//	RotBBox.x = OriginMid.x;
	//	RotBBox.y = OriginMid.y;
	//	RotBBox.z = MidRotatedBBox.z;
	//
	//	CVector3d moveback_midpoint(0.0, 0.0, 0.0);
	//	moveback_midpoint = RotBBox - MidRotatedBBox;			//???????????????????????????
	//
	//	vector<CVector3d> move_octree;
	//	for (auto i(0); i < m.Octrees.size(); ++i) {
	//		//move_octree.push_back(m.Octrees[i].origin +  moveback_midpoint);
	//		move_octree.push_back(m.Octrees[i].origin);
	//
	//	}
	//
	//	for (auto i(0); i < move_octree.size(); ++i) { m.Octrees[i].origin.Clear(); }
	//
	//	for (auto i(0); i < move_octree.size(); ++i) { m.Octrees[i].origin = move_octree[i]; }
	//
	//	move_octree.clear();
	//	min.Clear();
	//	min.x = 1000.0;
	//	min.y = 1000.0;
	//	min.z = 1000.0;
	//	max.Clear();
	//	

}

//2016/06/23
void Rotated_Back(Model& m, double Rotated_Angle, CVector3d centroid_before, CVector3d centroid_after) {
	//=--------------------------------------------------------
	//------------   2016 06 23
	//-------------- Back Roatated 
	double Theta = -Rotated_Angle;
	CVector3d W_(0.0, 0.0, 1.0);
	CMatrix Rod1(3, 3);
	Rod1.SetZero();

	Rod1.At(0, 0) = cos(Theta) + W_.x*W_.x*(1 - cos(Theta));
	Rod1.At(1, 0) = W_.z*sin(Theta) + W_.x*W_.y*(1 - cos(Theta));
	Rod1.At(2, 0) = -W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));

	Rod1.At(0, 1) = W_.x*W_.y*(1 - cos(Theta)) - W_.z*sin(Theta);
	Rod1.At(1, 1) = cos(Theta) + W_.y*W_.y*(1 - cos(Theta));
	Rod1.At(2, 1) = W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));

	Rod1.At(0, 2) = W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));
	Rod1.At(1, 2) = -W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));
	Rod1.At(2, 2) = cos(Theta) + W_.z*W_.z*(1 - cos(Theta));
	//--------------------------------------------------------------------

	vector<CVector3d> RodvertexW;
	for (auto i(0); i < m.Octrees.size(); ++i) { RodvertexW.push_back(m.Octrees[i].origin);}
	for (auto i(0); i < m.Octrees.size(); ++i) { m.Octrees[i].origin.Clear();	}

	for (auto i(0); i < RodvertexW.size(); ++i) {
		CVector3d temp_(0.0, 0.0, 0.0);
		temp_.x = Rod1.At(0, 0)*RodvertexW[i].x + Rod1.At(0, 1)*RodvertexW[i].y + Rod1.At(0, 2)*RodvertexW[i].z;
		temp_.y = Rod1.At(1, 0)*RodvertexW[i].x + Rod1.At(1, 1)*RodvertexW[i].y + Rod1.At(1, 2)*RodvertexW[i].z;
		temp_.z = Rod1.At(2, 0)*RodvertexW[i].x + Rod1.At(2, 1)*RodvertexW[i].y + Rod1.At(2, 2)*RodvertexW[i].z;
		m.Octrees[i].origin = (temp_);				// change rotated_octrees to OXYZ
	}
	
	////Find centroid after
	CVector3d temp_centafter(0.0, 0.0, 0.0);
	temp_centafter.x = Rod1.At(0, 0)*centroid_after.x + Rod1.At(0, 1)*centroid_after.y + Rod1.At(0, 2)*centroid_after.z;
	temp_centafter.y = Rod1.At(1, 0)*centroid_after.x + Rod1.At(1, 1)*centroid_after.y + Rod1.At(1, 2)*centroid_after.z;
	temp_centafter.z = Rod1.At(2, 0)*centroid_after.x + Rod1.At(2, 1)*centroid_after.y + Rod1.At(2, 2)*centroid_after.z;
	
	cout << "\ncentroid_new_Bbox " << temp_centafter.x << " " << temp_centafter.y << " " << temp_centafter.z << endl << endl;
	
	vector<CVector3d> move_octree;
	for (auto i(0); i < RodvertexW.size(); i++) {
		CVector3d temp(0.0, 0.0, 0.0);
		temp = m.Octrees[i].origin + (centroid_before - temp_centafter);
		move_octree.push_back(temp);
	}
	
	for (auto i(0); i < move_octree.size(); ++i) { m.Octrees[i].origin.Clear(); }
	for (auto i(0); i < move_octree.size(); ++i) { m.Octrees[i].origin = move_octree[i]; }

	RodvertexW.clear();
	move_octree.clear();

	//vector<CVector3d> center2;
	//vector<CVector3d> origin2;
	//vector<Point3i> coord2;
	//
	//vector<CVector3d> temp_vertexW2;
	//
	//int count(0);
	//for (auto x = 0; x < m.num[0]; ++x)
	//	for (auto y = 0; y < m.num[1]; ++y)
	//		for (auto z = 0; z < m.num[2]; ++z)
	//		{
	//			//center2.push_back(m.Voxels[x][y][z].center);
	//			origin2.push_back(m.Voxels[x][y][z].origin);
	//			//coord2.push_back(m.Voxels[x][y][z].coord);
	//			count++;
	//		}
	//
	//for (auto x = 0; x < m.num[0]; ++x)
	//	for (auto y = 0; y < m.num[1]; ++y)
	//		for (auto z = 0; z < m.num[2]; ++z)
	//		{
	//			m.Voxels[x][y][z].center.Clear();
	//			m.Voxels[x][y][z].origin.Clear();
	//			m.Voxels[x][y][z].SetCoord(0.0, 0.0, 0.0);
	//		}
	//
	//for (auto i(0); i < count; i++) {
	//	CVector3d temp_(0.0, 0.0, 0.0);
	//	temp_.x = Rod1.At(0, 0)*origin2[i].x + Rod1.At(0, 1)*origin2[i].y + Rod1.At(0, 2)*origin2[i].z;
	//	temp_.y = Rod1.At(1, 0)*origin2[i].x + Rod1.At(1, 1)*origin2[i].y + Rod1.At(1, 2)*origin2[i].z;
	//	temp_.z = Rod1.At(2, 0)*origin2[i].x + Rod1.At(2, 1)*origin2[i].y + Rod1.At(2, 2)*origin2[i].z;
	//	temp_vertexW2.push_back(temp_);
	//}
	//
	//////Find centroid after
	//CVector3d temp_centafter(0.0, 0.0, 0.0);
	//temp_centafter.x = Rod1.At(0, 0)*centroid_after.x + Rod1.At(0, 1)*centroid_after.y + Rod1.At(0, 2)*centroid_after.z;
	//temp_centafter.y = Rod1.At(1, 0)*centroid_after.x + Rod1.At(1, 1)*centroid_after.y + Rod1.At(1, 2)*centroid_after.z;
	//temp_centafter.z = Rod1.At(2, 0)*centroid_after.x + Rod1.At(2, 1)*centroid_after.y + Rod1.At(2, 2)*centroid_after.z;
	//
	//cout << "\ncentroid_new_Bbox " << temp_centafter.x << " " << temp_centafter.y << " " << temp_centafter.z << endl << endl;
	//
	//vector<CVector3d> new_temp_vertexW;
	//for (auto i(0); i < count; i++) {
	//	CVector3d temp(0.0, 0.0, 0.0);
	//	temp = temp_vertexW2[i] + (centroid_before - temp_centafter);
	//	new_temp_vertexW.push_back(temp);
	//}
	//int t(0);
	//for (auto x = 0; x < m.num[0]; ++x)
	//	for (auto y = 0; y < m.num[1]; ++y)
	//		for (auto z = 0; z < m.num[2]; ++z)
	//		{
	//			CVector3d temp(0.0, 0.0, 0.0);
	//			temp = new_temp_vertexW[t];
	//			m.Voxels[x][y][z].SetOrigin(temp);
	//			m.Voxels[x][y][z].SetCenterOfGrabity();
	//			m.Voxels[x][y][z].SetCoord(x, y, z);
	//
	//			t++;
	//			if (t > count)
	//				break;
	//			//cout << x << " " << y << " " << z << " " << m.num[0] << " " << m.num[1] << " " << m.num[2] << endl;
	//			//cout << m.Voxels[x][y][z].origin.x << " " << m.Voxels[x][y][z].origin.y << " " << m.Voxels[x][y][z].origin.z << endl;
	//			//getchar();
	//		}
	//
	////--------------------------------------
//
	//center2.clear();
	//origin2.clear();
	//coord2.clear();
	
}