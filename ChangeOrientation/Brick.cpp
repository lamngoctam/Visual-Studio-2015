#include "Brick.h"


Brick::Brick(void)
{
	this->colorID = 0;
	this->DesignID = 0;
	this->itemNos = 0;
	this->trans.Clear();
	this->rn = 0;
}


Brick::~Brick(void)
{
}

void Brick::clear()
{
	this->colorID = 0;
	this->DesignID = 0;
	this->itemNos = 0;
	this->trans.Clear();
	this->rn = 0;
}