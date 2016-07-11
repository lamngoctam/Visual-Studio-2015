#include "../Voxel.h"

Model::Model(int level)
{
	OctLevel = level;
	VoxelNum = 0;
	FillVoxelNum = 0;
	SurfNum = 0;
	MinDist = 0.0;
	count_label = 0;
}


