#include "../Voxel.h"

Labeling::Labeling()
{
	this->fill = false;
	this->label = INT_MAX;	//0じゃなくてunsigned short のマックス値（プログラムを組む都合上）
}

void Labeling::SetFillValue(bool num)
{
	this->fill = num;
}

void Labeling::SetLabelNumber(int num)
{
	this->label = num;
}

bool Labeling::GetFillValue(void)
{
	return (this->fill);
}
int Labeling::GetLabelNumber(void)
{
	return (this->label);
}