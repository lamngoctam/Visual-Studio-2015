#include "../stdafx.h"


void SetSrufToVector(Model& m)
{
	cout<<"Surface num: " << m.SurfNum << endl;
	m.SurfVoxels.reserve(m.SurfNum);
	int x, y, z;
	for (x = 1; x<m.num[0] - 1; ++x)
	for (y = 1; y<m.num[1] - 1; ++y)
	for (z = 1; z<m.num[2] - 1; ++z)
	if (m.Voxels[x][y][z].surf)
		m.SurfVoxels.push_back(m.Voxels[x][y][z]);

}

void FreeMemory_Voxel(Model& m)
{
	//       voxel     
	for (int i(0); i<m.num[0]; i++)
	{
		for (int k(0); k<m.num[1]; k++)
		{
			delete[] m.Voxels[i][k];
		}
		delete[] m.Voxels[i];
	}
	delete[] m.Voxels;
}