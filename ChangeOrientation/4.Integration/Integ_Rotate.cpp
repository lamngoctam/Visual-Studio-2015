#include "../stdafx.h"

vector<CVector3d> center1;
vector<CVector3d> origin1;
vector<Point3i> coord1;

vector<CVector3d> temp_vertexW;

void Integ_Rotated(Model& m, double Rotated_Angle) {
	//=--------------------------------------------------------
	//------------   2016 06 03
	//-------------- Back Roatated Integration
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



	int count(0);
	for (auto x = 0; x < m.num[0]; ++x)
		for (auto y = 0; y < m.num[1]; ++y)
			for (auto z = 0; z < m.num[2]; ++z)
			{
				center1.push_back(m.Voxels[x][y][z].center);
				origin1.push_back(m.Voxels[x][y][z].origin);
				coord1.push_back(m.Voxels[x][y][z].coord);
				count++;
			}

	for (auto x = 0; x < m.num[0]; ++x)
		for (auto y = 0; y < m.num[1]; ++y)
			for (auto z = 0; z < m.num[2]; ++z)
			{
				m.Voxels[x][y][z].center.Clear();
				m.Voxels[x][y][z].origin.Clear();
				m.Voxels[x][y][z].SetCoord(0.0, 0.0, 0.0);
			}




	for (auto i(0); i < count; i++) {
		CVector3d temp_(0.0, 0.0, 0.0);
		temp_.x = Rod1.At(0, 0)*center1[i].x + Rod1.At(0, 1)*center1[i].y + Rod1.At(0, 2)*center1[i].z;
		temp_.y = Rod1.At(1, 0)*center1[i].x + Rod1.At(1, 1)*center1[i].y + Rod1.At(1, 2)*center1[i].z;
		temp_.z = Rod1.At(2, 0)*center1[i].x + Rod1.At(2, 1)*center1[i].y + Rod1.At(2, 2)*center1[i].z;
		temp_vertexW.push_back(temp_);
	}


	int t(0);
	cout << "t " << t << endl;
	//while (t != count)
	{
		for (auto x = 0; x < m.num[0]; ++x)
			for (auto y = 0; y < m.num[1]; ++y)
				for (auto z = 0; z < m.num[2]; ++z)
				{

					CVector3d temp(0.0, 0.0, 0.0);
					temp = temp_vertexW[t];
					m.Voxels[x][y][z].SetOrigin(temp);
					m.Voxels[x][y][z].SetCenterOfGrabity();
					m.Voxels[x][y][z].SetCoord(x, y, z);

					t++;
					if (t > count)
						break;
					//cout << x << " " << y << " " << z << " " << m.num[0] << " " << m.num[1] << " " << m.num[2] << endl;
					//cout << m.Voxels[x][y][z].origin.x << " " << m.Voxels[x][y][z].origin.y << " " << m.Voxels[x][y][z].origin.z << endl;
					//getchar();
				}
	}

	//--------------------------------------

	center1.clear();
	origin1.clear();
	coord1.clear();
}

void Integ_Rotated_Back(Model& m, double Rotated_Angle) {
	//=--------------------------------------------------------
	//------------   2016 06 03
	//-------------- Back Roatated Integration
	double Theta = Rotated_Angle;
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
	for (auto i(0); i < m.SurfVoxels.size(); i++){
		center1.push_back(m.SurfVoxels[i].center);
	}
	for (auto i(0); i < m.SurfVoxels.size(); i++){
		m.SurfVoxels[i].center.Clear();
	}

	for (auto i(0); i < center1.size(); i++){
		CVector3d temp_(0.0, 0.0, 0.0);
		temp_.x = Rod1.At(0, 0)*center1[i].x + Rod1.At(0, 1)*center1[i].y + Rod1.At(0, 2)*center1[i].z;
		temp_.y = Rod1.At(1, 0)*center1[i].x + Rod1.At(1, 1)*center1[i].y + Rod1.At(1, 2)*center1[i].z;
		temp_.z = Rod1.At(2, 0)*center1[i].x + Rod1.At(2, 1)*center1[i].y + Rod1.At(2, 2)*center1[i].z;
		m.SurfVoxels[i].center=temp_;
	}
	for (auto i(0); i < m.SurfVoxels.size(); i++) {
	}


	center1.clear();

}

