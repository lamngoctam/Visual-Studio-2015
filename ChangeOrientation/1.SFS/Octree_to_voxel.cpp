#include "../stdafx.h"


void Set_voxel_parameter(Model& m, CVector3d& min, double MinVoxelL, double MinVoxelH)
{
	CVector3d temp(0.0, 0.0, 0.0);
	int x, y, z;

	cout << "set parameter\n";                           //Full bounding box
	m.Voxels[0][0][0].SetParameter(MinVoxelL);

	//Output 
//	ofstream fout;
//	fout.open("newzebraCubesUp8.txt");
//	fout << m.num[0] << " " << m.num[1] << " " << m.num[2] << " " << MinVoxelL << endl;    //1st
//	fout << m.BoundingBox.origin.x << " " << m.BoundingBox.origin.y << " " << m.BoundingBox.origin.z << endl;							//2nd
//	
//	for (x = 0; x < m.num[0]; x++) {
//		for (y = 0; y < m.num[1]; y++) {
//			for (z = 0; z < m.num[2]; z++) {
//				//if (m.Voxels[x][y][z].fill)
//					fout << x << " " << y << " " << z << endl;   //3rd-> 
//			}
//		}
//	}
//	fout.close();
	
	for (x = 0; x < m.num[0]; x++) {
		for (y = 0; y < m.num[1]; y++) {
			for (z = 0; z < m.num[2]; z++) {
				
				{
					temp.x = min.x + x*MinVoxelL;
					temp.y = min.y + y*MinVoxelL;
					temp.z = min.z + z*MinVoxelH;

					m.Voxels[x][y][z].SetOrigin(temp);
					m.Voxels[x][y][z].SetCenterOfGrabity(); //save the center of voxel
					m.Voxels[x][y][z].SetCoord(x, y, z);
				}
				//m.Voxels[x][y][z].SetCenterOfGrabity_Rotated(Rotated_Angle);
				//cout<<m.Voxels[x][y][z].center.x<<" "<< m.Voxels[x][y][z].center.y<<" "<< m.Voxels[x][y][z].center.z << endl;
			}
		}
	}
}

void Octree_to_voxel(Model& m, short level, CVector3d& min, CVector3d& max, double MinVoxelL, double MinVoxelH)
{
	cout << "\nOctree to Voxel\n ";

	CVector3d vertexW;
	m.FillVoxelNum = 0;
	int count(0);

	int x0(0), x1(0);
	int y0(0), y1(0);
	int z0(0), z1(0);
	double resultx(0.0), resulty(0.0),resultz(0.0);
	double tempx(0.0),tempy(0.0),tempz(0.0);

	double resultx2(0.0), resulty2(0.0), resultz2(0.0);
	double tempx2(0.0), tempy2(0.0), tempz2(0.0);

	vector<OctVoxel>::iterator it;
	for (it = m.Octrees.begin(); it != m.Octrees.end(); ++it) {
	
		resultx = ((it->origin.x - min.x) / MinVoxelL);
		resulty = ((it->origin.y - min.y) / MinVoxelL);
		resultz = ((it->origin.z - min.z) / MinVoxelH);

		//cout << resultx << " " << resulty << " " << resultz << endl;

		x0 = (int)resultx;
		tempx = resultx - x0;
		if (tempx > 0.5) { x0++; }

		y0 = (int)resulty;
		tempy = resulty - y0;
		if (tempy > 0.5) { y0++; }

		z0 = (int)resultz;
		tempz = resultz - z0;
		if (tempz > 0.5) { z0++; }

		it->SetVertexWorld_6(vertexW);
		if (it->LV < level) {

			resultx2 = ((vertexW.x - min.x) / MinVoxelL);
			resulty2 = ((vertexW.y - min.y) / MinVoxelL);
			resultz2 = ((vertexW.z - min.z) / MinVoxelH);

			x1 = (int)resultx2;
			tempx2 = resultx2 - x1;
			if (tempx2 > 0.5) { x1++; }

			y1 = (int)resulty2;
			tempy2 = resulty2 - y1;
			if (tempy2 > 0.5) { y1++; }

			z1 = (int)resultz2;
			tempz2 = resultz2 - z1;
			if (tempz2 > 0.5) { z1++; }

			for (int p(x0); p<x1; ++p) {
				for (int q(y0); q<y1; ++q) {
					for (int r(z0); r<z1; ++r) {
						m.Voxels[p][q][r].fill = true;
						m.FillVoxelNum++;
						count++;
					}
				}
			}
		}
		else if (it->LV == level) {
			m.Voxels[x0][y0][z0].fill = true;
			count++;
			m.FillVoxelNum++;

		}
	}


	cout << "  count# " << count << endl;
	cout << "--------------+++++++++++--------- fill voxel num: " << m.FillVoxelNum << endl;

	Set_voxel_parameter(m, min, MinVoxelL, MinVoxelH);

	cout << "=========  Finish otree to voxel  ======\n";
	m.Octrees.clear();
	m.Octrees.shrink_to_fit();

}

