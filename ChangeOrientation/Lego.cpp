#include "Lego.h"


Lego::Lego(void){
	this->flag = 0;
	this->fill = false;
	this->surf = false;
	this->ID = 0;
	this->corner = 0;
	this->ColorID = 0;

	this->root = false;

	this->in_surf = false;
	this->p_fill = false;
	this->airP = false;

	this->calc = false;
	this->BrickN = 0;
}
Lego::~Lego(void){

}
void Lego::Initiaization(void){
	this->flag = 0;
	this->fill = false;
	this->surf = false;
	this->ID = 0;
	this->corner = 0;
	this->ColorID = 0;

	this->in_surf = false;
	this->p_fill = false;
	this->airP = false;
}