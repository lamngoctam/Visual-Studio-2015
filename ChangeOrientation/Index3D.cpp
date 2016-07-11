#include "Index3D.h"

Index3D::Index3D(void){
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Index3D::Index3D(int x, int y, int z){
	this->x = x;
	this->y = y;
	this->z = z;
}

Index3D::~Index3D(void){

}

void Index3D::setValue(int x, int y, int z){
	this->x = x;
	this->y = y;
	this->z = z;
}