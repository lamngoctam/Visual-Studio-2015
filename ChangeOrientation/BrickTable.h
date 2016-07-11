#pragma once
#include <vector>
#include <iostream>

using namespace std;
class BrickTable
{

public:
	//unsigned ColorID[10];
	//unsigned DesignID[7];
	//unsigned itemNos[7][10];

	vector<unsigned> ColorID;
	vector<unsigned> DesignID;
	vector<vector<unsigned>> itemNos;

	BrickTable(void);
	~BrickTable(void);
	void OutputData();
};
