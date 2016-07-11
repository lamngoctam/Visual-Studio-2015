#pragma once
class Cpixel
{
public:

	//Default constructor
	Cpixel(void);
	//Default Deconstructor
	~Cpixel(void);
	//Muatator Functions
	void setPixel_u_v(short x, short y);
	void setPixel_u_v(Cpixel pix);		
	
	//Overload constructor
	Cpixel getPixel_u_v() const;

	//Accessor Functions
	short getPixel_u() const;			//
	short getPixel_v() const;			//

private:
	//member variables
	short u;	//W(-32768 Å` 32767)
	short v;	//W(-32768 Å` 32767)
};

