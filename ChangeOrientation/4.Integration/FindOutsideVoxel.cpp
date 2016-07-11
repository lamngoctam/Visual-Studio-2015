#include "../stdafx.h"


//model
void FindOutsideVoxel(Model& m)
{
	int x, y, z;
	m.SurfNum = 0;
	for (x = 1; x<m.num[0] - 1; ++x)				//x:1~num[0]-2�@�͈�ԊO���̑w�Ƀ{�N�Z���͑��݂��Ȃ�(������v�Z�̂��߂ɓ��ꂽ�w)
	{
		for (y = 1; y<m.num[1] - 1; ++y)			//��ԊO���̑w�Ƀ{�N�Z���͑��݂��Ȃ�
		{
			for (z = 1; z< m.num[2] - 1; ++z)		//��ԊO���̑w�Ƀ{�N�Z���͑��݂��Ȃ�
			{
				
				if (m.Voxels[x][y][z].fill)
				{
					//��(z + 1)
					if (m.Voxels[x][y][z + 1].fill == false)
					{
						m.Voxels[x][y][z].surf = true;
						m.SurfNum++;
						m.Voxels[x][y][z].coord.x = x;
						m.Voxels[x][y][z].coord.y = y;
						m.Voxels[x][y][z].coord.z = z;
						continue;
					}
					//��(z - 1)
					if (m.Voxels[x][y][z - 1].fill == false)
					{
						m.Voxels[x][y][z].surf = true;
						m.SurfNum++;
						m.Voxels[x][y][z].coord.x = x;
						m.Voxels[x][y][z].coord.y = y;
						m.Voxels[x][y][z].coord.z = z;
						continue;
					}
					//�O(x + 1)
					if (m.Voxels[x + 1][y][z].fill == false)
					{
						m.Voxels[x][y][z].surf = true;
						m.SurfNum++;
						m.Voxels[x][y][z].coord.x = x;
						m.Voxels[x][y][z].coord.y = y;
						m.Voxels[x][y][z].coord.z = z;
						continue;
					}
					//��(x - 1)
					if (m.Voxels[x - 1][y][z].fill == false)
					{
						m.Voxels[x][y][z].surf = true;
						m.SurfNum++;
						m.Voxels[x][y][z].coord.x = x;
						m.Voxels[x][y][z].coord.y = y;
						m.Voxels[x][y][z].coord.z = z;
						continue;
					}
					//��(y + 1)
					if (m.Voxels[x][y + 1][z].fill == false)
					{
						m.Voxels[x][y][z].surf = true;
						m.SurfNum++;
						m.Voxels[x][y][z].coord.x = x;
						m.Voxels[x][y][z].coord.y = y;
						m.Voxels[x][y][z].coord.z = z;
						continue;
					}
					//�E(y - 1)
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

