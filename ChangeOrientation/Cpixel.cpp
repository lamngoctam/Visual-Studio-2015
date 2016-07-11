#include "Cpixel.h"

Cpixel::Cpixel(void)
{
	this->u = 0;
	this->v = 0;
}

Cpixel::~Cpixel(void)
{
}
void Cpixel::setPixel_u_v(short x, short y)
{
	this->u = x;
	this->v = y;
}
void Cpixel::setPixel_u_v(Cpixel pix)
{
	this->u = pix.u;
	this->v = pix.v;
}

//const
Cpixel Cpixel::getPixel_u_v() const
{
	return *this;
}

short Cpixel::getPixel_u() const
{
	return this->u;
}
short Cpixel::getPixel_v() const
{
	return this->v;
}
