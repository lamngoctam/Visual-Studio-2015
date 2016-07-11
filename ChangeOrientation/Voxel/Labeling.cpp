#include "../Voxel.h"

Labeling::Labeling()
{
	this->fill = false;
	this->label = INT_MAX;	//0����Ȃ���unsigned short �̃}�b�N�X�l�i�v���O������g�ޓs����j
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