#include "../stdafx.h"


//model
void FindOutsideVoxel(Model& m)
{
	int x, y, z;
	m.SurfNum = 0;
	for (x = 1; x<m.num[0] - 1; ++x)				//x:1~num[0]-2　は一番外側の層にボクセルは存在しない(距離場計算のために入れた層)
	{
		for (y = 1; y<m.num[1] - 1; ++y)			//一番外側の層にボクセルは存在しない
		{
			for (z = 1; z< m.num[2] - 1; ++z)		//一番外側の層にボクセルは存在しない
			{
				
				if (m.Voxels[x][y][z].fill)
				{
					//上(z + 1)
					if (m.Voxels[x][y][z + 1].fill == false)
					{
						m.Voxels[x][y][z].surf = true;
						m.SurfNum++;
						m.Voxels[x][y][z].coord.x = x;
						m.Voxels[x][y][z].coord.y = y;
						m.Voxels[x][y][z].coord.z = z;
						continue;
					}
					//下(z - 1)
					if (m.Voxels[x][y][z - 1].fill == false)
					{
						m.Voxels[x][y][z].surf = true;
						m.SurfNum++;
						m.Voxels[x][y][z].coord.x = x;
						m.Voxels[x][y][z].coord.y = y;
						m.Voxels[x][y][z].coord.z = z;
						continue;
					}
					//前(x + 1)
					if (m.Voxels[x + 1][y][z].fill == false)
					{
						m.Voxels[x][y][z].surf = true;
						m.SurfNum++;
						m.Voxels[x][y][z].coord.x = x;
						m.Voxels[x][y][z].coord.y = y;
						m.Voxels[x][y][z].coord.z = z;
						continue;
					}
					//後(x - 1)
					if (m.Voxels[x - 1][y][z].fill == false)
					{
						m.Voxels[x][y][z].surf = true;
						m.SurfNum++;
						m.Voxels[x][y][z].coord.x = x;
						m.Voxels[x][y][z].coord.y = y;
						m.Voxels[x][y][z].coord.z = z;
						continue;
					}
					//左(y + 1)
					if (m.Voxels[x][y + 1][z].fill == false)
					{
						m.Voxels[x][y][z].surf = true;
						m.SurfNum++;
						m.Voxels[x][y][z].coord.x = x;
						m.Voxels[x][y][z].coord.y = y;
						m.Voxels[x][y][z].coord.z = z;
						continue;
					}
					//右(y - 1)
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

