#include "../stdafx.h"

void CalculateNormal(Model& m)
{
	CVector3d temp;

	int x, y, z;
	for (x = 1; x<m.num[0] - 1; ++x){
		for (y = 1; y<m.num[1] - 1; ++y){
			for (z = 1; z<m.num[2] - 1; ++z){
				if (m.Voxels[x][y][z].surf)	
				{
					temp.x = 0.0625 * (			//	1.0/16.0 = 0.0625
						  4.0*(m.Voxels[x + 1][y][z].dist - m.Voxels[x - 1][y][z].dist)
						+ 2.0*(m.Voxels[x + 1][y + 1][z].dist - m.Voxels[x - 1][y + 1][z].dist)
						+ 2.0*(m.Voxels[x + 1][y - 1][z].dist - m.Voxels[x - 1][y - 1][z].dist)
						+ 2.0*(m.Voxels[x + 1][y][z + 1].dist - m.Voxels[x - 1][y][z + 1].dist)
						+ 2.0*(m.Voxels[x + 1][y][z - 1].dist - m.Voxels[x - 1][y][z - 1].dist)
						+ (m.Voxels[x + 1][y + 1][z + 1].dist - m.Voxels[x - 1][y + 1][z + 1].dist)
						+ (m.Voxels[x + 1][y + 1][z - 1].dist - m.Voxels[x - 1][y + 1][z - 1].dist)
						+ (m.Voxels[x + 1][y - 1][z + 1].dist - m.Voxels[x - 1][y - 1][z + 1].dist)
						+ (m.Voxels[x + 1][y - 1][z - 1].dist - m.Voxels[x - 1][y - 1][z - 1].dist)
						);
					temp.y = 0.0625 * (
						4.0*(m.Voxels[x][y + 1][z].dist - m.Voxels[x][y - 1][z].dist)
						+ 2.0*(m.Voxels[x + 1][y + 1][z].dist - m.Voxels[x + 1][y - 1][z].dist)
						+ 2.0*(m.Voxels[x - 1][y + 1][z].dist - m.Voxels[x - 1][y - 1][z].dist)
						+ 2.0*(m.Voxels[x][y + 1][z + 1].dist - m.Voxels[x][y - 1][z + 1].dist)
						+ 2.0*(m.Voxels[x][y + 1][z - 1].dist - m.Voxels[x][y - 1][z - 1].dist)
						+ (m.Voxels[x + 1][y + 1][z + 1].dist - m.Voxels[x + 1][y - 1][z + 1].dist)
						+ (m.Voxels[x + 1][y + 1][z - 1].dist - m.Voxels[x + 1][y - 1][z - 1].dist)
						+ (m.Voxels[x - 1][y + 1][z + 1].dist - m.Voxels[x - 1][y - 1][z + 1].dist)
						+ (m.Voxels[x - 1][y + 1][z - 1].dist - m.Voxels[x - 1][y - 1][z - 1].dist)
						);
					temp.z = 0.0625 * (
						4.0*(m.Voxels[x][y][z + 1].dist - m.Voxels[x][y][z - 1].dist)
						+ 2.0*(m.Voxels[x + 1][y][z + 1].dist - m.Voxels[x + 1][y][z - 1].dist)
						+ 2.0*(m.Voxels[x - 1][y][z + 1].dist - m.Voxels[x - 1][y][z - 1].dist)
						+ 2.0*(m.Voxels[x][y + 1][z + 1].dist - m.Voxels[x][y + 1][z - 1].dist)
						+ 2.0*(m.Voxels[x][y - 1][z + 1].dist - m.Voxels[x][y - 1][z - 1].dist)
						+ (m.Voxels[x + 1][y + 1][z + 1].dist - m.Voxels[x + 1][y + 1][z - 1].dist)
						+ (m.Voxels[x + 1][y - 1][z + 1].dist - m.Voxels[x + 1][y - 1][z - 1].dist)
						+ (m.Voxels[x - 1][y + 1][z + 1].dist - m.Voxels[x - 1][y + 1][z - 1].dist)
						+ (m.Voxels[x - 1][y - 1][z + 1].dist - m.Voxels[x - 1][y - 1][z - 1].dist)
						);
				}
				m.Voxels[x][y][z].normal = temp.Normalize();
				//cout<<box[x][y][z].coord<<box[x][y][z].normal.x<<","<<box[x][y][z].normal.y<<","<<box[x][y][z].normal.z<<endl;
			}
		}
	}
}