#include "../stdafx.h"

//model
void FindOutsideVoxel1(Model& m)
{
	int x, y, z;
	m.SurfNum = 0;
	for (x = 1; x < m.num[0] - 1; ++x){	//x:1~num[0]-2
		for (y = 1; y < m.num[1] - 1; ++y){
			for (z = 1; z < m.num[2] - 1; ++z){
				if (m.Voxels[x][y][z].fill){
					//(z + 1)
					if (m.Voxels[x][y][z + 1].fill == false)
					{
						m.Voxels[x][y][z].surf = true;
						m.SurfNum++;
						m.Voxels[x][y][z].coord.x = x;
						m.Voxels[x][y][z].coord.y = y;
						m.Voxels[x][y][z].coord.z = z;
						continue;
					}
					//(z - 1)
					if (m.Voxels[x][y][z - 1].fill == false)
					{
						m.Voxels[x][y][z].surf = true;
						m.SurfNum++;
						m.Voxels[x][y][z].coord.x = x;
						m.Voxels[x][y][z].coord.y = y;
						m.Voxels[x][y][z].coord.z = z;
						continue;
					}
					//(x + 1)
					if (m.Voxels[x + 1][y][z].fill == false)
					{
						m.Voxels[x][y][z].surf = true;
						m.SurfNum++;
						m.Voxels[x][y][z].coord.x = x;
						m.Voxels[x][y][z].coord.y = y;
						m.Voxels[x][y][z].coord.z = z;
						continue;
					}
					//(x - 1)
					if (m.Voxels[x - 1][y][z].fill == false)
					{
						m.Voxels[x][y][z].surf = true;
						m.SurfNum++;
						m.Voxels[x][y][z].coord.x = x;
						m.Voxels[x][y][z].coord.y = y;
						m.Voxels[x][y][z].coord.z = z;
						continue;
					}
					//(y + 1)
					if (m.Voxels[x][y + 1][z].fill == false)
					{
						m.Voxels[x][y][z].surf = true;
						m.SurfNum++;
						m.Voxels[x][y][z].coord.x = x;
						m.Voxels[x][y][z].coord.y = y;
						m.Voxels[x][y][z].coord.z = z;
						continue;
					}
					//(y - 1)
					if (m.Voxels[x][y - 1][z].fill == false)
					{
						m.Voxels[x][y][z].surf = true;
						m.SurfNum++;
						m.Voxels[x][y][z].coord.x = x;
						m.Voxels[x][y][z].coord.y = y;
						m.Voxels[x][y][z].coord.z = z;
					}
				}
			}
		}
	}
}

//vector
void SetSrufToVector1(Model& m)
{
	cout << m.SurfNum << endl;
	m.SurfVoxels.reserve(m.SurfNum);		//
	int x, y, z;
	for (x = 1; x < m.num[0] - 1; ++x)
	for (y = 1; y < m.num[1] - 1; ++y)
	for (z = 1; z < m.num[2] - 1; ++z)

	if (m.Voxels[x][y][z].surf)		//
		m.SurfVoxels.push_back(m.Voxels[x][y][z]);
	cout << "Surface voxel size: " << m.SurfVoxels.size() << endl;
}

void FreeMemory_Voxel1(Model& m)
{
	//       voxel
	for (int i(0); i < m.num[0]; i++)
	{
		for (int k(0); k < m.num[1]; k++)
		{
			delete[] m.Voxels[i][k];
		}
		delete[] m.Voxels[i];
	}
	delete[] m.Voxels;
}

