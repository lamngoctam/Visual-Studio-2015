#include "../stdafx.h"
extern double MinVoxelL;			//new UP & DOWN
extern double MinVoxelH;

void MoveDown(Model& UP, Model& DOWN) {
	vector<CVector3d> move_vertexW;
	for (auto i(0); i < DOWN.Octrees.size(); ++i) {
		move_vertexW.push_back(DOWN.Octrees[i].origin);
	}

	for (auto i(0); i < DOWN.Octrees.size(); ++i) {
		DOWN.Octrees[i].origin.Clear();
	}

	for (auto i(0); i < move_vertexW.size(); ++i) {
		move_vertexW[i].x = move_vertexW[i].x - MinVoxelL;
		move_vertexW[i].y = move_vertexW[i].y + 0.5*MinVoxelL;
		move_vertexW[i].z = move_vertexW[i].z + 2.0*MinVoxelH;
		DOWN.Octrees[i].origin = move_vertexW[i];
	}


}