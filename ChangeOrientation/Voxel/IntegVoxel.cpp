#include "../Voxel.h"

//コンストラクタ
VoxelFlag::VoxelFlag()
{
	this->up = false;
	this->down = false;
	this->upCan = false;
	this->downCan = false;
}

void VoxelFlag::Initialization()
{
	this->upCan = false;
	this->downCan = false;
}
