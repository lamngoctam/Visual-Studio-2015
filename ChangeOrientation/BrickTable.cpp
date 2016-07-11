#include "BrickTable.h"

BrickTable::BrickTable(void)
{
}


BrickTable::~BrickTable(void)
{
}


void BrickTable::OutputData()
{
	//colorID
	for (int i(0); i<this->ColorID.size(); i++)
		cout << this->ColorID[i] << " ";
	cout << endl;
	//DesignID
	for (int i(0); i<this->DesignID.size(); i++)
		cout << this->DesignID[i] << " ";
	cout << endl;

	//itemNos
	for (int i(0); i<this->itemNos.size(); i++){
		for (int k(0); k<this->itemNos[i].size(); k++){
			cout << this->itemNos[i][k] << " ";
		}
		cout << endl;
	}

}