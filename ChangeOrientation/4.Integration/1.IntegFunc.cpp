#include "../stdafx.h"

extern OctVoxel Angle_;
extern int  zcood;

//Bounding Box‚(x,y,z)
void FindMinAndMax(Model& up, Model& down, CVector3d& min, CVector3d& max, double MinVoxelL, double MinVoxelH)
{
	CVector3d vertexW;

	for (vector<OctVoxel>::iterator it = up.Octrees.begin(); it != up.Octrees.end(); ++it) {
		it->SetVertexWorld_6(vertexW);

		if (it->origin.x <= min.x) { min.x = it->origin.x; }

		if (it->origin.y <= min.y) { min.y = it->origin.y; }

		if (it->origin.z <= min.z) { min.z = it->origin.z; }


		if (vertexW.x >= max.x) { max.x = vertexW.x; }

		if (vertexW.y >= max.y) { max.y = vertexW.y; }

		if (vertexW.z >= max.z) { max.z = vertexW.z; }
	}

	//
	for (vector<OctVoxel>::iterator it = down.Octrees.begin(); it != down.Octrees.end(); ++it) {
		it->SetVertexWorld_6(vertexW);

		if (it->origin.x <= min.x) { min.x = it->origin.x; }

		if (it->origin.y <= min.y) { min.y = it->origin.y; }

		if (it->origin.z <= min.z) { min.z = it->origin.z; }

		if (vertexW.x >= max.x) { max.x = vertexW.x; }

		if (vertexW.y >= max.y) { max.y = vertexW.y; }

		if (vertexW.z >= max.z) { max.z = vertexW.z; }
	}

	max.x = max.x + MinVoxelL;
	max.y = max.y + MinVoxelL;
	max.z = max.z + MinVoxelH;

	min.x = min.x - MinVoxelL;
	min.y = min.y - MinVoxelL;
	min.z = min.z - MinVoxelH;

	cout << "min " << min.x << " " << min.y << " " << min.z << endl;
	cout << "max " << max.x << " " << max.y << " " << max.z << endl;

	double resultx(0.0), resulty(0.0), resultz(0.0);
	double tempx(0.0), tempy(0.0), tempz(0.0);

	resultx = ((max.x - min.x) / MinVoxelL);
	resulty = ((max.y - min.y) / MinVoxelL);
	resultz = ((max.z - min.z) / MinVoxelH);

	up.num[0] = (int)resultx;
	tempx = resultx - up.num[0];
	if (tempx > 0.5) { up.num[0]++; }

	up.num[1] = (int)resulty;
	tempy = resulty - up.num[1];
	if (tempy > 0.5) { up.num[1]++; }

	up.num[2] = (int)resultz;
	tempz = resultz - up.num[2];
	if (tempz > 0.5) { up.num[2]++; }


	//up.num[0] = (int)((max.x - min.x)/MinVoxelL);	//X•
	//up.num[1] = (int)((max.y - min.y)/MinVoxelL);	//Y•
	//up.num[2] = (int)((max.z - min.z)/MinVoxelH);	//Z•

	down.num[0] = up.num[0];	//X
	down.num[1] = up.num[1];	//Y
	down.num[2] = up.num[2];	//Z

	up.VoxelNum = up.num[0] * up.num[1] * up.num[2];
	down.VoxelNum = up.VoxelNum;
}


//
void UPandDOWN(Model& up, Model& down, Model& integ, CVector3d min, double MinVoxelL, double MinVoxelH)
{
	integ.VoxelNum = up.VoxelNum;

	for (int x(1); x < integ.num[0] - 1; x++) {
		for (int y(1); y < integ.num[1] - 1; y++) {
			for (int z(1); z < integ.num[2] - 1; z++) {
				if (up.Voxels[x][y][z].fill)
					integ.Flags[x][y][z].up = true;

				if (down.Voxels[x][y][z].fill)
					integ.Flags[x][y][z].down = true;
			}
		}
	}
}

//(Zhang)
void UPandDOWN_zhang(Model& up, Model& down, Model& integ, CVector3d min, double MinVoxelL, double MinVoxelH)
{
	integ.VoxelNum = up.VoxelNum;
	for (int x(1); x < integ.num[0] - 1; x++)
	{
		for (int y(1); y < integ.num[1] - 1; y++)
		{
			for (int z(1); z < integ.num[2] - 1; z++)
			{
				if (up.Voxels[x][y][z].fill)
					integ.Flags[integ.num[0] - x - 1][y][integ.num[2] - z - 1].up = true;

				if (down.Voxels[x][y][z].fill)
					integ.Flags[integ.num[0] - x - 1][y][integ.num[2] - z - 1].down = true;
			}
		}
	}
}


//˜aW‡
void Unio(Model& integ)
{

	for (int x(1); x < integ.num[0] - 1; x++)
	{
		for (int y(1); y < integ.num[1] - 1; y++)
		{
			for (int z(1); z < integ.num[2] - 1; z++)
			{
				//
				if (integ.Flags[x][y][z].up == true || integ.Flags[x][y][z].down == true)
				{
					//
					integ.Voxels[x][y][z].fill = true;
					integ.FillVoxelNum++;
				}
			}
		}
	}
}


//
void Intersection(Model& integ)
{
	for (int x(1); x < integ.num[0] - 1; x++)
	{
		for (int y(1); y < integ.num[1] - 1; y++)
		{
			for (int z(1); z < integ.num[2] - 1; z++)
			{
				//UPDOWN
				if (integ.Flags[x][y][z].up == true && integ.Flags[x][y][z].down == true)
				{
					//fill‚ðtrue‚
					integ.Voxels[x][y][z].fill = true;
					integ.FillVoxelNum++;
				}
			}
		}
	}
}

//ˆê”Ô‰º‚Ì‘w‚ðí‚é
void Slice(Model& integ)
{

	for (int x(1); x < integ.num[0] - 1; x++)
	{
		for (int y(1); y < integ.num[1] - 1; y++)
		{
			for (int z(1); z < integ.num[2] - 1; z++)
			{
				if (integ.Voxels[x][y][z].fill == true)
				{
					if (zcood < z)
						zcood = z;
				}
			}
		}
	}
	for (int x(1); x < integ.num[0] - 1; x++)
	{
		for (int y(1); y < integ.num[1] - 1; y++)
		{
			if (integ.Voxels[x][y][zcood].fill == true)
				integ.Voxels[x][y][zcood].fill = false;
		}
	}
}


//ƒeƒLƒXƒgƒf[ƒ^‚Éo‚·
void Putout_txt(Model& integ, string Filename, double length)
{
	cout << "Output information of Integ.voxel coordinates [xyz]" << endl;

	ofstream fout(Filename);
	fout << integ.num[0] << "  " << integ.num[1] << "   " << integ.num[2] << "  " << length << endl;
	fout << integ.Voxels[0][0][0].origin.x << "  " << integ.Voxels[0][0][0].origin.y << "   " << integ.Voxels[0][0][0].origin.z << endl;
	
	for (int x(1); x < integ.num[0] - 1; x++)
	{
		for (int y(1); y < integ.num[1] - 1; y++)
		{
			for (int z(1); z < integ.num[2] - 1; z++)
			{
				if (integ.Voxels[x][y][z].fill == true) {
					fout << x << "  " << y << "  " << z << endl;
				}
			}
		}
	}
}
void Out_camera(string Filename, CVector3d* Camera) {
	ofstream fout(Filename);
	for (int i(0); i < 36; i++)//36Ž‹“_‚¾‚©‚ç
		fout << Camera[i].x << "  " << Camera[i].y << "  " << Camera[i].z << endl;
}
void In_camara(string Filename, CVector3d* Camera) {
	ifstream fin(Filename);
	if (!fin) {
		std::cout << Filename << "is not found!" << std::endl;	//ƒtƒ@ƒCƒ‹‚ª–³‚¢“™
		exit(0);
	}
	string sline;
	istringstream ssline;
	//1s–Ú“Ç‚Ýž‚Ý
	for (int i(0); i < 36; i++)
	{
		getline(fin, sline);
		ssline.str(sline);		//ƒXƒgƒŠ[ƒ€‚É•ÏŠ·
		ssline >> Camera[i].x >> Camera[i].y >> Camera[i].z;
		ssline.clear();				//‹ó‚É‚·‚é

	}
	cout << Filename << " Filename of inCamera " << endl;
}
void In_camera_para(string Filename, CMatrix* ART) {

	for (int i(0); i < 36; i++) {//36Ž‹“_‚¾‚©‚ç

		std::stringstream stream;
		stream << Filename << "data" << i << ".txt";
		string Name = stream.str();

		string sline;
		istringstream ssline;
		ifstream fin(Name);
		if (!fin) {
			std::cout << Filename << "is not found!" << std::endl;	//ƒtƒ@ƒCƒ‹‚ª–³‚¢“™
			exit(0);
		}
		int k = 0;
		while (!fin.eof()) {
			getline(fin, sline);
			ssline.str(sline);		//ƒXƒgƒŠ[ƒ€‚É•ÏŠ·
			ssline >> ART[i].At(k, 0) >> ART[i].At(k, 1) >> ART[i].At(k, 2) >> ART[i].At(k, 3);
			ssline.clear();				//‹ó‚É‚·‚é
			k++;
		}
	}
	cout << Filename << "?????????????" << endl;
}
void Camera_para(string Filename, CMatrix* ART) {
	for (int i(0); i < 36; i++) {//36Ž‹“_‚¾‚©‚ç
		std::stringstream stream;
		stream << Filename << "data" << i << ".txt";
		string Name = stream.str();
		ofstream fout(Name);
		for (int k(0); k < 4; k++)
			fout << ART[i].At(k, 0) << "  " << ART[i].At(k, 1) << "  " << ART[i].At(k, 2) << "  " << ART[i].At(k, 3) << endl;
	}
	cout << "Output Camera parameter! " << endl;
}