#include "../Voxel.h"

OnetoOne::OnetoOne()
{
	this->dist = DBL_MAX;		//�����̒l�𖳌���ɂ���
	this->flag = false;	
	this->num = 0;
}

void OnetoOne::Initial()		//����������
{
	this->dist = DBL_MAX;		//�����̒l�𖳌���ɂ���
	this->flag = false;
	this->num = 0;
}