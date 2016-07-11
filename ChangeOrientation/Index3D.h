#pragma once
class Index3D{
public:
	int x;
	int y;
	int z;
	
	Index3D(void);
	Index3D(int x, int y, int z);

	~Index3D(void);
	void setValue(int x, int y, int z);

};