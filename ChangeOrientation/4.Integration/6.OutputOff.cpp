#include "../stdafx.h"
#include "../V_ID_F.h"
#include "../VertexPro.h"

extern string directory[2];
extern string model;
extern string pose[3];	


void MakeFaceList(Model& m, int& vertex_num,	vector<CVector3d>& vert, vector<V_ID_F>& face, VertexPro*** vertPro,	int* Vert8, int* aa,int* bb, int* cc, int x, int y, int z);


void OutputOff(Model& m)
{
	int face_num(0);
	int vertex_num(0);					
	vector<CVector3d> vert;		
	vector<V_ID_F> face;		
	vector<CColor> vox;			
	VertexPro*** vertPro;		
	
	//6
	int Vert8[6][4] =
	{{3, 2, 1, 0},
	{3, 0, 4, 7},
	{2, 3, 7, 6},
	{1, 2, 6, 5},
	{0, 1, 5, 4},
	{4, 5, 6, 7}};	//z-1, x-1, y+1, x+1, y-1, z+1

	int aa[8] = {0, 1, 1, 0, 0, 1, 1, 0};		//x
	int bb[8] = {0, 0, 1, 1, 0, 0, 1, 1};		//y
	int cc[8] = {0, 0, 0, 0, 1, 1, 1, 1};		//z
	
	int face6[6][3] = {
		{0,0,-1},
		{-1,0,0},
		{0,1,0},
		{1,0,0},
		{0,-1,0},
		{0,0,1}	};	//
	
	//
	vertPro = new VertexPro** [m.num[0]+1];
	for(int x(0); x<m.num[0]+1; x++){
		vertPro[x] = new VertexPro* [m.num[1]+1];
		for(int y(0); y<m.num[1]+1; y++){
			vertPro[x][y] = new VertexPro [m.num[2]+1];
		}
	}
	//
	vector<CColor>::iterator itC = m.SurfColors.begin();
	vector<Voxel>::iterator itV = m.SurfVoxels.begin();
	while(itV != m.SurfVoxels.end())
	{
		for(int i(0); i<6; i++)		
		{
			if(m.Voxels[(itV->coord.x) + face6[i][0]][(itV->coord.y) + face6[i][1]][(itV->coord.z) + face6[i][2]].fill == false)		//６隣接のボクセルが存在しないなら
			{
				face_num++;			//
				MakeFaceList(m, vertex_num, vert, face, vertPro, Vert8[i], aa, bb, cc, (itV->coord.x), (itV->coord.y), (itV->coord.z));		//面を構成する頂点のIDのリストを決める
				vox.push_back(*itC);
			}
		}
		++itV;
		++itC;
	}

	//                                              
	for(int x(0); x<m.num[0]+1; x++){
		for(int y(0); y<m.num[1]+1; y++){
			delete [] vertPro[x][y];
		}
		delete [] vertPro[x];
	}
	delete [] vertPro;

	////            .off              
	//string fileName("SurfVoxel.off");			
	//ofstream fout(directory[1] + model + fileName);			
	//fout << "OFF" <<endl;
	//fout << vertex_num << " " << face_num << " " << 0 << endl;
	//for(int i(0); i<vertex_num; i++)
	//	fout<< vert[i].x << " " << vert[i].y << " " << vert[i].z <<endl;
	//for(int i(0);i <face_num; i++)
	//	fout<< 4 << " " << face[i].left_down << " " << face[i].right_down << " " << face[i].right_up << " " << face[i].left_up << endl; 

	//               
	string fileName1("SurfVoxel_Color.off");			
	ofstream fout1(directory[1] + model + fileName1);		
	double alpha(0.5);
	fout1 << "OFF" <<endl;
	fout1 << vertex_num << " " << face_num << " " << 0 << endl;
	for(int i(0); i<vertex_num; i++)
		fout1 << vert[i].x << " " << vert[i].y << " " << vert[i].z <<endl;
	for(int i(0);i <face_num; i++)
		fout1 << 4 << " " << face[i].left_down << " " << face[i].right_down << " " << face[i].right_up << " " << face[i].left_up << " " <<vox[i].r << " " << vox[i].g << " " << vox[i].b << " " << alpha <<endl; 

}


void MakeFaceList(Model& m, int& vertex_num,vector<CVector3d>& vert, vector<V_ID_F>& face, VertexPro*** vertPro,	int* Vert8, int* aa,int* bb, int* cc, int x, int y, int z)
{
	int v8;		
	CVector3d vertexW[8];
	m.Voxels[x][y][z].SetVertexWorld(vertexW);
	
	for(int i(0); i<4; i++)				
	{
		v8 = Vert8[i];
		if(vertPro[x + aa[v8]] [y + bb[v8]] [z + cc[v8]].pushed == false){
			vertex_num++;														
			vertPro[x + aa[v8]] [y + bb[v8]] [z + cc[v8]].pushed = true;		
			vertPro[x + aa[v8]] [y + bb[v8]] [z + cc[v8]].ID = vertex_num-1;	
			vert.push_back(vertexW[v8]);							            
		}
	}
	
	V_ID_F temp;
	
	temp.left_down	= vertPro[x + aa[Vert8[0]]] [y + bb[Vert8[0]]] [z + cc[Vert8[0]]].ID;
	temp.right_down	= vertPro[x + aa[Vert8[1]]] [y + bb[Vert8[1]]] [z + cc[Vert8[1]]].ID;
	temp.right_up	= vertPro[x + aa[Vert8[2]]] [y + bb[Vert8[2]]] [z + cc[Vert8[2]]].ID;
	temp.left_up	= vertPro[x + aa[Vert8[3]]] [y + bb[Vert8[3]]] [z + cc[Vert8[3]]].ID;

	face.push_back(temp);			
}



//2014/6/10

void OutputOff_noncolor(Model& m)
{
	int face_num(0);
	int vertex_num(0);			
	vector<CVector3d> vert;		
	vector<V_ID_F> face;		
	vector<CColor> vox;			
	VertexPro*** vertPro;		
	
	//6
	int Vert8[6][4] =
	{{3, 2, 1, 0},
	{3, 0, 4, 7},
	{2, 3, 7, 6},
	{1, 2, 6, 5},
	{0, 1, 5, 4},
	{4, 5, 6, 7}};	//z-1, x-1, y+1, x+1, y-1, z+1

	int aa[8] = {0, 1, 1, 0, 0, 1, 1, 0};		//x
	int bb[8] = {0, 0, 1, 1, 0, 0, 1, 1};		//y
	int cc[8] = {0, 0, 0, 0, 1, 1, 1, 1};		//z
	
	int face6[6][3] = {
		{0,0,-1},
		{-1,0,0},
		{0,1,0},
		{1,0,0},
		{0,-1,0},
		{0,0,1}	};	//z-1, x-1, y+1, x+1, y-1, z+1
	
	//
	vertPro = new VertexPro** [m.num[0]+1];
	for(int x(0); x<m.num[0]+1; x++){
		vertPro[x] = new VertexPro* [m.num[1]+1];
		for(int y(0); y<m.num[1]+1; y++){
			vertPro[x][y] = new VertexPro [m.num[2]+1];
		}
	}
	//全ボクセルで回す
	vector<Voxel>::iterator itV = m.SurfVoxels.begin();
	while(itV != m.SurfVoxels.end())
	{
		for(int i(0); i<6; i++)		
		{
			if(m.Voxels[(itV->coord.x) + face6[i][0]][(itV->coord.y) + face6[i][1]][(itV->coord.z) + face6[i][2]].fill == false)		//６隣接のボクセルが存在しないなら
			{
				face_num++;			//表面ボクセルの表面の数を加算していく
				MakeFaceList(m, vertex_num, vert, face, vertPro, Vert8[i], aa, bb, cc, (itV->coord.x), (itV->coord.y), (itV->coord.z));		//面を構成する頂点のIDのリストを決める
			}
		}
		++itV;
	}

	//                          領域解放                        
	for(int x(0); x<m.num[0]+1; x++){
		for(int y(0); y<m.num[1]+1; y++){
			delete [] vertPro[x][y];
		}
		delete [] vertPro[x];
	}
	delete [] vertPro;

	//       off         
	string fileName1("SurfVoxel.off");			
	ofstream fout1(directory[1] + model + fileName1);			
	double alpha(0.5);
	fout1 << "OFF" <<endl;
	fout1 << vertex_num << " " << face_num << " " << 0 << endl;
	for(int i(0); i<vertex_num; i++)
		fout1 << vert[i].x << " " << vert[i].y << " " << vert[i].z <<endl;
	for(int i(0);i <face_num; i++)
		fout1 << 4 << " " << face[i].left_down << " " << face[i].right_down << " " << face[i].right_up << " " << face[i].left_up <<endl; 

}


