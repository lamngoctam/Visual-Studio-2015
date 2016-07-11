#include "../stdafx.h"

void Check_Integ_Rotation(Model& up, Model& down, OctVoxel& upboundingbox, OctVoxel& downboundingbox, double Rotated_Angle) {

	CVector3d Vector_move_up(0.0,0.0,0.0);
	Vector_move_up = up.Octrees[0].origin;

	vector<CVector3d> move_ver_up;
	for (auto i(0); i < up.Octrees.size(); ++i) {
		//move_ver_up.push_back(up.Octrees[i].origin - Vector_move_up);
		move_ver_up.push_back(up.Octrees[i].origin);
	}
	for (auto i(0); i < up.Octrees.size(); ++i) {
		up.Octrees[i].origin.Clear();
	}

	CVector3d W_(0.0, 0.0, 1.0);
	double Theta = Rotated_Angle;

	CMatrix Rod_up(3, 3);  //matrix rotation
	Rod_up.SetZero();
	cout << "Theta " << Theta << endl;
	Rod_up.At(0, 0) = cos(Theta) + W_.x*W_.x*(1 - cos(Theta));
	Rod_up.At(1, 0) = W_.z*sin(Theta) + W_.x*W_.y*(1 - cos(Theta));
	Rod_up.At(2, 0) = -W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));

	Rod_up.At(0, 1) = W_.x*W_.y*(1 - cos(Theta)) - W_.z*sin(Theta);
	Rod_up.At(1, 1) = cos(Theta) + W_.y*W_.y*(1 - cos(Theta));
	Rod_up.At(2, 1) = W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));

	Rod_up.At(0, 2) = W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));
	Rod_up.At(1, 2) = -W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));
	Rod_up.At(2, 2) = cos(Theta) + W_.z*W_.z*(1 - cos(Theta));

	for (auto i(0); i < move_ver_up.size(); ++i) {
		CVector3d temp(0.0, 0.0, 0.0);
		temp.x = Rod_up.At(0, 0)*move_ver_up[i].x + Rod_up.At(0, 1)*move_ver_up[i].y + Rod_up.At(0, 2)*move_ver_up[i].z;
		temp.y = Rod_up.At(1, 0)*move_ver_up[i].x + Rod_up.At(1, 1)*move_ver_up[i].y + Rod_up.At(1, 2)*move_ver_up[i].z;
		temp.z = Rod_up.At(2, 0)*move_ver_up[i].x + Rod_up.At(2, 1)*move_ver_up[i].y + Rod_up.At(2, 2)*move_ver_up[i].z;
		//up.New_origin_octrees.push_back(temp);
		up.Octrees[i].origin = (temp);
	}
	
	//move back
	CVector3d newPoint(0.0, 0.0, 0.0);
	newPoint = up.Octrees[0].origin;

	CVector3d moveback_midpoint(0.0, 0.0, 0.0);
	moveback_midpoint = newPoint - Vector_move_up;

	vector<CVector3d> move_octree;
	for (auto i(0); i < up.Octrees.size(); ++i) {
		//move_octree.push_back(up.Octrees[i].origin + moveback_midpoint);
		move_octree.push_back(up.Octrees[i].origin);
	}

	for (auto i(0); i < move_octree.size(); ++i) { up.Octrees[i].origin.Clear(); }
	for (auto i(0); i < move_octree.size(); ++i) { up.Octrees[i].origin = move_octree[i]; }

	//============================ down ===============================
	//============================      ===============================

	vector<CVector3d> move_ver_down;
	for (auto i(0); i < down.Octrees.size(); ++i) {
		//move_ver_down.push_back(down.Octrees[i].origin - Vector_move_down);
		move_ver_down.push_back(down.Octrees[i].origin);
	}
	for (auto i(0); i < down.Octrees.size(); ++i) {
		down.Octrees[i].origin.Clear();
	}

	double down_Theta = Rotated_Angle;

	CMatrix Rod_down(3, 3);  //matrix rotation
	Rod_down.SetZero();
	Rod_down.At(0, 0) = cos(down_Theta) + W_.x*W_.x*(1 - cos(down_Theta));
	Rod_down.At(1, 0) = W_.z*sin(down_Theta) + W_.x*W_.y*(1 - cos(down_Theta));
	Rod_down.At(2, 0) = -W_.y*sin(down_Theta) + W_.x*W_.z*(1 - cos(down_Theta));

	Rod_down.At(0, 1) = W_.x*W_.y*(1 - cos(down_Theta)) - W_.z*sin(down_Theta);
	Rod_down.At(1, 1) = cos(down_Theta) + W_.y*W_.y*(1 - cos(down_Theta));
	Rod_down.At(2, 1) = W_.x*sin(down_Theta) + W_.y*W_.z*(1 - cos(down_Theta));

	Rod_down.At(0, 2) = W_.y*sin(down_Theta) + W_.x*W_.z*(1 - cos(down_Theta));
	Rod_down.At(1, 2) = -W_.x*sin(down_Theta) + W_.y*W_.z*(1 - cos(down_Theta));
	Rod_down.At(2, 2) = cos(down_Theta) + W_.z*W_.z*(1 - cos(down_Theta));

	for (auto i(0); i < move_ver_down.size(); ++i) {
		CVector3d temp(0.0, 0.0, 0.0);
		temp.x = Rod_down.At(0, 0)*move_ver_down[i].x + Rod_down.At(0, 1)*move_ver_down[i].y + Rod_down.At(0, 2)*move_ver_down[i].z;
		temp.y = Rod_down.At(1, 0)*move_ver_down[i].x + Rod_down.At(1, 1)*move_ver_down[i].y + Rod_down.At(1, 2)*move_ver_down[i].z;
		temp.z = Rod_down.At(2, 0)*move_ver_down[i].x + Rod_down.At(2, 1)*move_ver_down[i].y + Rod_down.At(2, 2)*move_ver_down[i].z;
		down.Octrees[i].origin = (temp);
	}
	
	//move back to origin position

	vector<CVector3d> move_octree2;
	for (auto i(0); i < down.Octrees.size(); ++i) {
		//move_octree2.push_back(down.Octrees[i].origin + moveback_midpoint);
		move_octree2.push_back(down.Octrees[i].origin);
	}

	for (auto i(0); i < move_octree2.size(); ++i) { down.Octrees[i].origin.Clear(); }
	for (auto i(0); i < move_octree2.size(); ++i) { down.Octrees[i].origin = move_octree2[i]; }
}

void Check_UpDown_Rotation(Model& up, Model& down, OctVoxel& upboundingbox, OctVoxel& downboundingbox, double Rotated_Angle) {

	CVector3d Vector_move_up(0.0, 0.0, 0.0);
	Vector_move_up = up.Octrees[0].origin;

	vector<CVector3d> move_ver_up;
	for (auto i(0); i < up.Octrees.size(); ++i) {
		move_ver_up.push_back(up.Octrees[i].origin);
	}
	for (auto i(0); i < up.Octrees.size(); ++i) {
		up.Octrees[i].origin.Clear();
	}

	CVector3d W_(0.0, 0.0, 1.0);
	double Theta = Rotated_Angle;

	CMatrix Rod_up(3, 3);  //matrix rotation
	Rod_up.SetZero();
	cout << "Theta " << Theta << endl;
	Rod_up.At(0, 0) = cos(Theta) + W_.x*W_.x*(1 - cos(Theta));
	Rod_up.At(1, 0) = W_.z*sin(Theta) + W_.x*W_.y*(1 - cos(Theta));
	Rod_up.At(2, 0) = -W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));

	Rod_up.At(0, 1) = W_.x*W_.y*(1 - cos(Theta)) - W_.z*sin(Theta);
	Rod_up.At(1, 1) = cos(Theta) + W_.y*W_.y*(1 - cos(Theta));
	Rod_up.At(2, 1) = W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));

	Rod_up.At(0, 2) = W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));
	Rod_up.At(1, 2) = -W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));
	Rod_up.At(2, 2) = cos(Theta) + W_.z*W_.z*(1 - cos(Theta));

	for (auto i(0); i < move_ver_up.size(); ++i) {
		CVector3d temp(0.0, 0.0, 0.0);
		temp.x = Rod_up.At(0, 0)*move_ver_up[i].x + Rod_up.At(0, 1)*move_ver_up[i].y + Rod_up.At(0, 2)*move_ver_up[i].z;
		temp.y = Rod_up.At(1, 0)*move_ver_up[i].x + Rod_up.At(1, 1)*move_ver_up[i].y + Rod_up.At(1, 2)*move_ver_up[i].z;
		temp.z = Rod_up.At(2, 0)*move_ver_up[i].x + Rod_up.At(2, 1)*move_ver_up[i].y + Rod_up.At(2, 2)*move_ver_up[i].z;
		//up.New_origin_octrees.push_back(temp);
		up.Octrees[i].origin = (temp);
	}

	//move back
	CVector3d newPoint(0.0, 0.0, 0.0);
	newPoint = up.Octrees[0].origin;

	CVector3d moveback_midpoint(0.0, 0.0, 0.0);
	moveback_midpoint = Vector_move_up -newPoint;

	vector<CVector3d> move_octree;
	for (auto i(0); i < up.Octrees.size(); ++i) {
		//move_octree.push_back(up.Octrees[i].origin + moveback_midpoint);
		move_octree.push_back(up.Octrees[i].origin);
	}

	for (auto i(0); i < move_octree.size(); ++i) { up.Octrees[i].origin.Clear(); }
	for (auto i(0); i < move_octree.size(); ++i) { up.Octrees[i].origin = move_octree[i]; }

	//============================ down ===============================
	//============================      ===============================

	vector<CVector3d> move_ver_down;
	for (auto i(0); i < down.Octrees.size(); ++i) {
		move_ver_down.push_back(down.Octrees[i].origin);
	}
	for (auto i(0); i < down.Octrees.size(); ++i) {
		down.Octrees[i].origin.Clear();
	}

	double down_Theta = Rotated_Angle;

	CMatrix Rod_down(3, 3);  //matrix rotation
	Rod_down.SetZero();
	Rod_down.At(0, 0) = cos(down_Theta) + W_.x*W_.x*(1 - cos(down_Theta));
	Rod_down.At(1, 0) = W_.z*sin(down_Theta) + W_.x*W_.y*(1 - cos(down_Theta));
	Rod_down.At(2, 0) = -W_.y*sin(down_Theta) + W_.x*W_.z*(1 - cos(down_Theta));

	Rod_down.At(0, 1) = W_.x*W_.y*(1 - cos(down_Theta)) - W_.z*sin(down_Theta);
	Rod_down.At(1, 1) = cos(down_Theta) + W_.y*W_.y*(1 - cos(down_Theta));
	Rod_down.At(2, 1) = W_.x*sin(down_Theta) + W_.y*W_.z*(1 - cos(down_Theta));

	Rod_down.At(0, 2) = W_.y*sin(down_Theta) + W_.x*W_.z*(1 - cos(down_Theta));
	Rod_down.At(1, 2) = -W_.x*sin(down_Theta) + W_.y*W_.z*(1 - cos(down_Theta));
	Rod_down.At(2, 2) = cos(down_Theta) + W_.z*W_.z*(1 - cos(down_Theta));

	for (auto i(0); i < move_ver_down.size(); ++i) {
		CVector3d temp(0.0, 0.0, 0.0);
		temp.x = Rod_down.At(0, 0)*move_ver_down[i].x + Rod_down.At(0, 1)*move_ver_down[i].y + Rod_down.At(0, 2)*move_ver_down[i].z;
		temp.y = Rod_down.At(1, 0)*move_ver_down[i].x + Rod_down.At(1, 1)*move_ver_down[i].y + Rod_down.At(1, 2)*move_ver_down[i].z;
		temp.z = Rod_down.At(2, 0)*move_ver_down[i].x + Rod_down.At(2, 1)*move_ver_down[i].y + Rod_down.At(2, 2)*move_ver_down[i].z;
		down.Octrees[i].origin = (temp);
	}

	//move back to origin position

	vector<CVector3d> move_octree2;
	for (auto i(0); i < down.Octrees.size(); ++i) {
		//move_octree2.push_back(down.Octrees[i].origin + moveback_midpoint);
		move_octree2.push_back(down.Octrees[i].origin);
	}

	for (auto i(0); i < move_octree2.size(); ++i) { down.Octrees[i].origin.Clear(); }
	for (auto i(0); i < move_octree2.size(); ++i) { down.Octrees[i].origin = move_octree2[i]; }

}