#include "../Voxel.h"

OnetoOne::OnetoOne()
{
	this->dist = DBL_MAX;		//‹——£‚Ì’l‚ğ–³ŒÀ‘å‚É‚·‚é
	this->flag = false;	
	this->num = 0;
}

void OnetoOne::Initial()		//‰Šú‰»‚·‚é
{
	this->dist = DBL_MAX;		//‹——£‚Ì’l‚ğ–³ŒÀ‘å‚É‚·‚é
	this->flag = false;
	this->num = 0;
}