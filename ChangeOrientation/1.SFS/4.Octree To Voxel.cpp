#include "../stdafx.h"

extern OctVoxel Angle_;
extern vector<CVector3d> Origin_;
extern int Surf_OctreeNum;



//Bounding Box‚(x,y,z)X,Y,Z
void FindMinAndMax(Model& m, CVector3d& min, CVector3d& max, double MinVoxelL, double MinVoxelH)
{
	CVector3d vertexW;

	for (vector<OctVoxel>::iterator it = m.Octrees.begin(); it != m.Octrees.end(); ++it) {
		//it->SetVertexWorld_6_Rotated(Angle_.Orientation_Angle, vertexW);  
		it->SetVertexWorld_6(vertexW);

		if (it->origin.x <= min.x) { min.x = it->origin.x; }
		if (it->origin.y <= min.y) { min.y = it->origin.y; }
		if (it->origin.z <= min.z) { min.z = it->origin.z; }

		if (vertexW.x >= max.x) { max.x = vertexW.x; }
		if (vertexW.y >= max.y) { max.y = vertexW.y; }
		if (vertexW.z >= max.z) { max.z = vertexW.z; }
	}
	//find 8 bbox point
	cout << "\nmin " << min.x << " " << min.y << " " << min.z << endl;
	cout << "max " << max.x << " " << max.y << " " << max.z << endl;

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
	//--------------------------------
	double resultx(0.0);
	double resulty(0.0);
	double resultz(0.0);
	double tempx(0.0);
	double tempy(0.0);
	double tempz(0.0);

	resultx = (max.x - min.x) / MinVoxelL;
	resulty = (max.y - min.y) / MinVoxelL;
	resultz = (max.z - min.z) / MinVoxelH;

	m.num[0] = (int)resultx;
	tempx = resultx - m.num[0];
	if (tempx > 0.5) { m.num[0]++; }

	m.num[1] = (int)resulty;
	tempy = resulty - m.num[1];
	if (tempy > 0.5) { m.num[1]++; }

	m.num[2] = (int)resultz;
	tempz = resultz - m.num[2];
	if (tempz > 0.5) { m.num[2]++; }

	//if ((resultx != m.num[0]) || (resulty != m.num[1]) || (resultz != m.num[2])) {
	//	cout << "something wrong in here\n";
		//	exit(1); 
	//}

	m.VoxelNum = m.num[0] * m.num[1] * m.num[2];
	cout << "Number of voxel before create a new bbox : " << m.num[0] << "*" << m.num[1] << "*" << m.num[2] << "*" << m.VoxelNum << endl;

	max.x = max.x + MinVoxelL;
	max.y = max.y + MinVoxelL;
	max.z = max.z + MinVoxelH;

	min.x = min.x - MinVoxelL;
	min.y = min.y - MinVoxelL;
	min.z = min.z - MinVoxelH;



	resultx = 0.0;	resulty = 0.0;	resultz = 0.0;	tempx = 0.0;	tempy = 0.0;	tempz = 0.0;

	resultx = (max.x - min.x) / MinVoxelL;
	resulty = (max.y - min.y) / MinVoxelL;
	resultz = (max.z - min.z) / MinVoxelH;

	m.num[0] = (int)resultx;
	tempx = resultx - m.num[0];
	if (tempx > 0.5) { m.num[0]++; }

	m.num[1] = (int)resulty;
	tempy = resulty - m.num[1];
	if (tempy > 0.5) { m.num[1]++; }

	m.num[2] = (int)resultz;
	tempz = resultz - m.num[2];
	if (tempz > 0.5) { m.num[2]++; }


	m.VoxelNum = m.num[0] * m.num[1] * m.num[2];
	cout << "Number of voxel after create a new bbox : " << m.num[0] << "*" << m.num[1] << "*" << m.num[2] << "*" << m.VoxelNum << endl;

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

	//min = m.New_smallcubicvertex[0];
	//max = m.New_smallcubicvertex[6];

}

void SetVoxelParameter(Model& m, CVector3d min, double MinVoxelL, double MinVoxelH)
{
	CVector3d temp(0.0, 0.0, 0.0);
	int x, y, z;

	m.Voxels[0][0][0].SetParameter(MinVoxelL);

	for (x = 0; x < m.num[0]; x++) {
		for (y = 0; y < m.num[1]; y++) {
			for (z = 0; z < m.num[2]; z++) {
				temp.x = min.x + x*MinVoxelL;
				temp.y = min.y + y*MinVoxelL;
				temp.z = min.z + z*MinVoxelH;
				m.Voxels[x][y][z].SetOrigin(temp);
				m.Voxels[x][y][z].SetCenterOfGrabity();
				m.Voxels[x][y][z].SetCoord(x, y, z);
			}
		}
	}

}

void SetVoxelParameter(Model& m, double Rotated_Angle, CVector3d& min, double MinVoxelL, double MinVoxelH)
{
	CVector3d temp(0.0, 0.0, 0.0);

	int x, y, z;

	cout << "set parameter\n";                           //Full bounding box
	m.Voxels[0][0][0].SetParameter(MinVoxelL);
	int NumofXenterVoxel(0);

	for (x = 0; x < m.num[0]; x++) {
		for (y = 0; y < m.num[1]; y++) {
			for (z = 0; z < m.num[2]; z++) {

				temp.x = min.x + x*MinVoxelL;
				temp.y = min.y + y*MinVoxelL;
				temp.z = min.z + z*MinVoxelH;

				//temp.x = temp.x *cos(Rotated_Angle) - temp.y*sin(Rotated_Angle);
				//temp.y = temp.x *sin(Rotated_Angle) + temp.y*cos(Rotated_Angle);
				//temp.z = temp.z;

				//	m.Voxels[x][y][z].SetOrigin_Rotated(temp, Rotated_Angle);
				//	m.Voxels[x][y][z].SetCoord_Rotated(x, y, z, Rotated_Angle);

				//	m.Voxels[x][y][z].SetParameter(MinVoxelL);			
				m.Voxels[x][y][z].SetOrigin(temp);
				//m.Voxels[x][y][z].SetCenterOfGrabity(); //save the center of voxel
				m.Voxels[x][y][z].SetCoord(x, y, z);
				m.Voxels[x][y][z].SetCenterOfGrabity_Rotated(Rotated_Angle);


				NumofXenterVoxel++;
				//m.min_vertex_point.push_back(temp);
			}
		}
	}

	cout << "NumofXenterVoxel  " << NumofXenterVoxel << endl;
	//getchar();

}

void OctreeToVoxel(Model& m, double Rotated_Angle, short level, CVector3d& min, CVector3d& max, double MinVoxelL, double MinVoxelH)
{
	cout << "\nOctree to Voxel\n ";

	int x[2] = { 0, 0 };
	int y[2] = { 0, 0 };
	int z[2] = { 0, 0 };

	CVector3d vertexW(0.0, 0.0, 0.0);
	vector<OctVoxel>::iterator it;
	m.FillVoxelNum = 0;

	for (it = m.Octrees.begin(); it != m.Octrees.end(); ++it) {

		it->SetVertexWorld_6_Rotated(Rotated_Angle, vertexW);

		x[0] = (int)abs((it->origin.x - min.x) / MinVoxelL);
		y[0] = (int)abs((it->origin.y - min.y) / MinVoxelL);
		z[0] = (int)abs((it->origin.z - min.z) / MinVoxelH);

		//	//m.min_vertex_point.push_back(it->origin);
		//
		//	cout << it->LV << endl;
		//	cout << x[0] << "*" << y[0] << "*" << z[0] << endl;
		//	cout << min.x << " " << min.y << " " << min.z << endl;
		//	getchar();
		if (it->LV < level) {                                //Octree‚LV
			//cout << "LV < level\n";

			x[1] = (int)abs((vertexW.x - min.x) / MinVoxelL);	//Find how many voxel was divided.
			y[1] = (int)abs((vertexW.y - min.y) / MinVoxelL);
			z[1] = (int)abs((vertexW.z - min.z) / MinVoxelH);

			cout << it->LV << endl;
			cout << x[1] << "*" << y[1] << "*" << z[1] << endl;
			cout << min.x << " " << min.y << " " << min.z << endl;
			//

			if ((x[0] < x[1]) && (y[0] < y[1]) && (z[0] < z[1])) {

				for (int p(x[0]); p < x[1]; ++p) {
					for (int q(y[0]); q < y[1]; ++q) {
						for (int r(z[0]); r < z[1]; ++r) {

							m.Voxels[p][q][r].fill = true;
							m.FillVoxelNum++;
							//
							cout << "x-y-z[0] " << x[0] << "*" << y[0] << "*" << z[0] << endl;
							cout << "x-y-z[1] " << x[1] << "*" << y[1] << "*" << z[1] << endl;
							//						//
							cout << "------fill voxel num: " << m.FillVoxelNum << endl;
							//getchar();
						}
					}
				}
			}
			//
			else if ((x[0] >= x[1]) || (y[0] >= y[1]) || (z[0] >= z[1])) {
				cout << " " << x[0] << "*" << y[0] << "*" << z[0] << endl;
				cout << " " << x[1] << "*" << y[1] << "*" << z[1] << endl;

				cout << "Although it->LV < Octree but can not find the p,q,r\n";
				getchar();
			}
			//getchar();
		}
		//
		else if (it->LV == level) {
			m.Voxels[x[0]][y[0]][z[0]].fill = true;
			m.FillVoxelNum++;

			cout << "------fill voxel num: " << m.FillVoxelNum << endl;
			//getchar();
			//Surf_OctreeNum++;
		}

	}
	cout << " ------ fill voxel num: " << m.FillVoxelNum << endl;

	SetVoxelParameter(m, Rotated_Angle, min, MinVoxelL, MinVoxelH);
	cout << "==============================================================\n";
	m.Octrees.clear();
	m.Octrees.shrink_to_fit();
}

void OctreeToVoxel(Model& m, short level, CVector3d min, CVector3d max, double MinVoxelL, double MinVoxelH)
{
	int x[2] = { 0, 0 };  // ???
	int y[2] = { 0, 0 };
	int z[2] = { 0, 0 };

	CVector3d origin(0.0, 0.0, 0.0);
	CVector3d vertexW;

	m.FillVoxelNum = 0;		//Octree fill
	for (vector<OctVoxel>::iterator it = m.Octrees.begin(); it != m.Octrees.end(); ++it) {
		x[0] = (int)((it->origin.x - min.x) / MinVoxelL);		// why divide by MinVoxelL,H
		y[0] = (int)((it->origin.y - min.y) / MinVoxelL);
		z[0] = (int)((it->origin.z - min.z) / MinVoxelH);

		it->SetVertexWorld_6(vertexW);

		//Octree‚LV
		if (it->LV < level) {
			x[1] = (int)((vertexW.x - min.x) / MinVoxelL);	//Find how many voxel was divided.
			y[1] = (int)((vertexW.y - min.y) / MinVoxelL);
			z[1] = (int)((vertexW.z - min.z) / MinVoxelH);

			for (int p(x[0]); p < x[1]; ++p) {
				for (int q(y[0]); q < y[1]; ++q) {
					for (int r(z[0]); r < z[1]; ++r) {
						m.Voxels[p][q][r].fill = true;
						m.FillVoxelNum++;
					}
				}
			}
		}
		//Octree‚LV‚LV‚
		else if (it->LV == level) {
			m.Voxels[x[0]][y[0]][z[0]].fill = true;
			m.FillVoxelNum++;
		}
	}


	SetVoxelParameter(m, min, MinVoxelL, MinVoxelH);

	//OctreeVoxel
	m.Octrees.clear();
	m.Octrees.shrink_to_fit();
}
