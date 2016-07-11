
#include "../stdafx.h"

extern double MinVoxelL;					//Length of the model minimum voxel
extern double MinVoxelH;					//Height of the model minimum voxel

extern CVector3d VertexMin_;					//origin
extern CVector3d VertexMax_;					//Diagonal point of origin
extern vector<CVector3d> Origin_;
extern CVector3d BBox_Origin;

extern OctVoxel Angle_;

void Check_Plane(Model& m, OctVoxel& box, vector<OctVoxel>& scale_box, double Rotated_Angle){
	cout << "Check_Plane\n";
	CVector3d vertexW[8];
	box.SetVertexWorld_Rotated(Rotated_Angle, vertexW);

	//Plane_1 : 
	CVector3d NormVec1(0.0, 0.0, 0.0);
	NormVec1.x = vertexW[3].x - BBox_Origin.x;
	NormVec1.y = vertexW[3].y - BBox_Origin.y;
	NormVec1.z = vertexW[3].z - BBox_Origin.z;
	NormVec1 = NormVec1.Normalize();				//Normalize
	double a1(0.0), b1(0.0), c1(0.0), d1(0.0);
	a1 = NormVec1.x;
	b1 = NormVec1.y;
	c1 = NormVec1.z;
	d1 = -(NormVec1.x*BBox_Origin.x + NormVec1.y*BBox_Origin.y + NormVec1.z*BBox_Origin.z);
	cout << "d1: " << d1 << endl;
	double Dist1(5000.0);
	double Dist_voxel(0.0);

	for (auto i(0); i < m.Octrees.size(); ++i){
		Dist_voxel = abs(d1 + NormVec1.Dot(m.min_vertex_point[i])) / (1);
		//cout << "Dist_voxel " << Dist_voxel << endl;
		if (Dist1 >= Dist_voxel){
			Dist1 = Dist_voxel;
			m.min_vertex_bbox[0] = m.min_vertex_point[i];
		}
		Dist_voxel = 0.0;
	}
	double new_d1(0.0);                  //create new plane through min_vertex_bbox point.
	new_d1 = -(NormVec1.x*m.min_vertex_bbox[0].x + NormVec1.y*m.min_vertex_bbox[0].y + NormVec1.z*m.min_vertex_bbox[0].z);

	//Plane_2 : 
	CVector3d NormVec2(0.0, 0.0, 0.0);
	NormVec2.x = vertexW[1].x - BBox_Origin.x;
	NormVec2.y = vertexW[1].y - BBox_Origin.y;
	NormVec2.z = vertexW[1].z - BBox_Origin.z;
	NormVec2 = NormVec2.Normalize(); //Normalize
	double a2(0.0), b2(0.0), c2(0.0), d2(0.0);
	a2 = NormVec2.x;
	b2 = NormVec2.y;
	c2 = NormVec2.z;
	d2 = -(NormVec2.x*BBox_Origin.x + NormVec2.y*BBox_Origin.y + NormVec2.z*BBox_Origin.z);
	cout << "d2: " << d2 << endl;
	double Dist2(5000.0);
	for (auto i(0); i < m.Octrees.size(); ++i){
		Dist_voxel = abs(d2 + NormVec2.Dot(m.min_vertex_point[i])) / (1);
		//cout << "Dist_voxel " << Dist_voxel << endl;
		if (Dist2 >= Dist_voxel){
			Dist2 = Dist_voxel;
			m.min_vertex_bbox[1] = m.min_vertex_point[i];
		}
		Dist_voxel = 0.0;
	}
	double new_d2(0.0);
	new_d2 = -(NormVec2.x*m.min_vertex_bbox[1].x + NormVec2.y*m.min_vertex_bbox[1].y + NormVec2.z*m.min_vertex_bbox[1].z);

	//Plane_3
	CVector3d NormVec3(0.0, 0.0, 0.0);
	NormVec3.x = BBox_Origin.x - vertexW[3].x;
	NormVec3.y = BBox_Origin.y - vertexW[3].y;
	NormVec3.z = BBox_Origin.z - vertexW[3].z;
	NormVec3 = NormVec3.Normalize();            //Normalize
	double a3(0.0), b3(0.0), c3(0.0), d3(0.0);
	a3 = NormVec3.x;
	b3 = NormVec3.y;
	c3 = NormVec3.z;
	d3 = -(NormVec3.x*vertexW[3].x + NormVec3.y*vertexW[3].y + NormVec3.z*vertexW[3].z);
	cout << "d3: " << d3 << endl;
	double Dist3(5000.0);
	for (auto i(0); i < m.Octrees.size(); ++i){
		Dist_voxel = abs(d3 + NormVec3.Dot(m.max_vertex_point[i])) / (1);
		//cout << "Dist_voxel " << Dist_voxel << endl;
		if (Dist3 >= Dist_voxel){
			Dist3 = Dist_voxel;
			m.min_vertex_bbox[2] = m.max_vertex_point[i];
		}
		Dist_voxel = 0.0;
	}
	double new_d3(0.0);
	new_d3 = -(NormVec3.x*m.min_vertex_bbox[2].x + NormVec3.y*m.min_vertex_bbox[2].y + NormVec3.z*m.min_vertex_bbox[2].z);

	//Plane_4
	CVector3d NormVec4(0.0,0.0,0.0);
	NormVec4.x = BBox_Origin.x - vertexW[1].x;
	NormVec4.y = BBox_Origin.y - vertexW[1].y;
	NormVec4.z = BBox_Origin.z - vertexW[1].z;
	NormVec4 = NormVec4.Normalize();	//Normalize
	double a4(0.0), b4(0.0), c4(0.0), d4(0.0);
	a4 = NormVec4.x;
	b4 = NormVec4.y;
	c4 = NormVec4.z;
	d4 = -(NormVec4.x*vertexW[1].x + NormVec4.y*vertexW[1].y + NormVec4.z*vertexW[1].z);
	cout << "d4: " << d4 << endl;
	double Dist4(5000.0);
	for (auto i(0); i < m.Octrees.size(); ++i){
		Dist_voxel = abs(d4 + NormVec4.Dot(m.max_vertex_point[i])) / (1);
		//cout << "Dist_voxel " << Dist_voxel << endl;
		if (Dist4 >= Dist_voxel){
			Dist4 = Dist_voxel;
			m.min_vertex_bbox[3] = m.max_vertex_point[i];
		}
		Dist_voxel = 0.0;
	}
	double new_d4(0.0);
	new_d4 = -(NormVec4.x*m.min_vertex_bbox[3].x + NormVec4.y*m.min_vertex_bbox[3].y + NormVec4.z*m.min_vertex_bbox[3].z);

	//Plane_5
	CVector3d NormVec5(0.0, 0.0, 0.0);
	NormVec5.x = vertexW[4].x - BBox_Origin.x;
	NormVec5.y = vertexW[4].y - BBox_Origin.y;
	NormVec5.z = vertexW[4].z - BBox_Origin.z;
	NormVec5 = NormVec5.Normalize(); //Normalize
	double a5(0.0), b5(0.0), c5(0.0), d5(0.0);
	a5 = NormVec5.x;
	b5 = NormVec5.y;
	c5 = NormVec5.z;
	d5 = -(NormVec5.x*BBox_Origin.x + NormVec5.y*BBox_Origin.y + NormVec5.z*BBox_Origin.z);
	double Dist5(5000.0);
	for (auto i(0); i < m.Octrees.size(); ++i){
		Dist_voxel = abs(d5 + NormVec5.Dot(m.min_vertex_point[i])) / (1);
		//cout << "Dist_voxel " << Dist_voxel << endl;
		if (Dist5 >= Dist_voxel){
			Dist5 = Dist_voxel;
			m.min_vertex_bbox[4] = m.min_vertex_point[i];
		}
		Dist_voxel = 0.0;
	}
	double new_d5(0.0);
	new_d5 = -(NormVec5.x*m.min_vertex_bbox[4].x + NormVec5.y*m.min_vertex_bbox[4].y + NormVec5.z*m.min_vertex_bbox[4].z);

	//Plane_6
	CVector3d NormVec6(0.0, 0.0, 0.0);
	NormVec6.x = BBox_Origin.x - vertexW[4].x;
	NormVec6.y = BBox_Origin.y - vertexW[4].y;
	NormVec6.z = BBox_Origin.z - vertexW[4].z;

	NormVec6 = NormVec6.Normalize(); //Normalize
	double a6(0.0), b6(0.0), c6(0.0), d6(0.0);
	a6 = NormVec6.x;
	b6 = NormVec6.y;
	c6 = NormVec6.z;
	d6 = -(NormVec6.x*vertexW[4].x + NormVec6.y*vertexW[4].y + NormVec6.z*vertexW[4].z);
	double Dist6(5000.0);
	for (auto i(0); i < m.Octrees.size(); ++i){
		Dist_voxel = abs(d6 + NormVec6.Dot(m.max_vertex_point[i])) / (1);
		//cout << "Dist_voxel " << Dist_voxel << endl;
		if (Dist6 >= Dist_voxel){
			Dist6 = Dist_voxel;
			m.min_vertex_bbox[5] = m.max_vertex_point[i];
		}
		Dist_voxel = 0.0;
	}
	double new_d6(0.0);
	new_d6 = -(NormVec6.x*m.min_vertex_bbox[5].x + NormVec6.y*m.min_vertex_bbox[5].y + NormVec6.z*m.min_vertex_bbox[5].z);

	// Find the Intersection point between 3 plane 1 2 5

//	CVector3d numerator[8];
//	double 	denominator[8];
//
//	//1,2,5
//	numerator[0] = (-new_d1)*((NormVec2.Cross(NormVec5))) - new_d2*((NormVec5.Cross(NormVec1))) - new_d5*((NormVec1.Cross(NormVec2)));
//	denominator[0] = NormVec1.Dot((NormVec2.Cross(NormVec5)));
//	//1-4-5
//	numerator[1] = (-new_d1)*((NormVec4.Cross(NormVec5))) - new_d4*((NormVec5.Cross(NormVec1))) - new_d5*((NormVec1.Cross(NormVec4)));
//	denominator[1] = NormVec1.Dot((NormVec4.Cross(NormVec5)));
//	//3-4-5	
//	numerator[2] = (-new_d3)*((NormVec4.Cross(NormVec5))) - new_d4*((NormVec5.Cross(NormVec3))) - new_d5*((NormVec3.Cross(NormVec4)));
//	denominator[2] = NormVec3.Dot((NormVec4.Cross(NormVec5)));
//	//2-3-5
//	numerator[3] = (-new_d2)*((NormVec3.Cross(NormVec5))) - new_d3*((NormVec5.Cross(NormVec2))) - new_d5*((NormVec2.Cross(NormVec3)));
//	denominator[3] = NormVec2.Dot((NormVec3.Cross(NormVec5)));
//	//1-2-6 
//	numerator[4] = (-new_d1)*((NormVec2.Cross(NormVec6))) - new_d2*((NormVec6.Cross(NormVec1))) - new_d6*((NormVec1.Cross(NormVec2)));
//	denominator[4] = NormVec1.Dot((NormVec2.Cross(NormVec6)));
//	//1-4-6
//	numerator[5] = (-new_d1)*((NormVec4.Cross(NormVec6))) - new_d4*((NormVec6.Cross(NormVec1))) - new_d6*((NormVec1.Cross(NormVec4)));
//	denominator[5] = NormVec1.Dot((NormVec4.Cross(NormVec6)));
//	//3-4-6	
//	numerator[6] = (-new_d3)*((NormVec4.Cross(NormVec6))) - new_d4*((NormVec6.Cross(NormVec3))) - new_d6*((NormVec3.Cross(NormVec4)));
//	denominator[6] = NormVec3.Dot((NormVec4.Cross(NormVec6)));
//	//2-3-6
//	numerator[7] = (-new_d2)*((NormVec3.Cross(NormVec6))) - new_d3*((NormVec6.Cross(NormVec2))) - new_d6*((NormVec2.Cross(NormVec3)));
//	denominator[7] = NormVec2.Dot((NormVec3.Cross(NormVec6)));
//
//	for (auto i(0); i < 8; i++) {
//		m.P_IntersecPoint[i] = numerator[i] / denominator[i];
//		scale_box[i].origin.x = m.P_IntersecPoint[i].x;
//		scale_box[i].origin.y = m.P_IntersecPoint[i].y;
//		scale_box[i].origin.z = m.P_IntersecPoint[i].z;
//	}
//	
	//-----------------

//	CVector3d Vector_move(0.0, 0.0, 0.0);
//	Vector_move = (m.P_IntersecPoint[0] + m.P_IntersecPoint[6]) / 2.0;
//
//	CVector3d move_center_octree[8];
//	for (auto i(0); i < 8; ++i){
//		move_center_octree[i] = (m.P_IntersecPoint[i] - Vector_move);
//	}
//
//	CVector3d W_(0.0, 0.0, 1.0);
//	CMatrix Rodrigues(3, 3);
//	Rodrigues.SetZero();
//	double Theta = Rotated_Angle;
//
//	Rodrigues.At(0, 0) = cos(Theta) + W_.x*W_.x*(1 - cos(Theta));
//	Rodrigues.At(1, 0) = W_.z*sin(Theta) + W_.x*W_.y*(1 - cos(Theta));
//	Rodrigues.At(2, 0) = -W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));
//
//	Rodrigues.At(0, 1) = W_.x*W_.y*(1 - cos(Theta)) - W_.z*sin(Theta);
//	Rodrigues.At(1, 1) = cos(Theta) + W_.y*W_.y*(1 - cos(Theta));
//	Rodrigues.At(2, 1) = W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));
//
//	Rodrigues.At(0, 2) = W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));
//	Rodrigues.At(1, 2) = -W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));
//	Rodrigues.At(2, 2) = cos(Theta) + W_.z*W_.z*(1 - cos(Theta));

	cout << "test..................................................................\n";

	//for (int i(0); i < 8; ++i){
	//	New_center_octrees[i].x = Rodrigues.At(0, 0)*move_center_octree[i].x + Rodrigues.At(0, 1)*move_center_octree[i].y + Rodrigues.At(0, 2)*move_center_octree[i].z;
	//	New_center_octrees[i].y = Rodrigues.At(1, 0)*move_center_octree[i].x + Rodrigues.At(1, 1)*move_center_octree[i].y + Rodrigues.At(1, 2)*move_center_octree[i].z;
	//	New_center_octrees[i].z = Rodrigues.At(2, 0)*move_center_octree[i].x + Rodrigues.At(2, 1)*move_center_octree[i].y + Rodrigues.At(2, 2)*move_center_octree[i].z;
	//}
	//////-----------------------------------
	//m.num[0] = (int)((New_center_octrees[1].x - New_center_octrees[0].x) / MinVoxelL);	//X-Axis number of voxel 
	//m.num[1] = (int)((New_center_octrees[3].y - New_center_octrees[0].y) / MinVoxelL);	//Y-Axis
	//m.num[2] = (int)((New_center_octrees[4].z - New_center_octrees[0].z) / MinVoxelH);	//Z-Axis
	//
	//m.VoxelNum = m.num[0] * m.num[1] * m.num[2];
	//cout << "Number of voxel before create a new bbox : " << m.num[0] << "*" << m.num[1] << "*" << m.num[2] << "*" << m.VoxelNum << endl;
	//

	//getchar();


//	vertexW->Clear();
//	numerator->Clear();
//	move_center_octree->Clear();

}
