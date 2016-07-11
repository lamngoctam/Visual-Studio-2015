#include "stdafx.h"
using namespace std;


void RunOpenGL0(int argc, char *argv[]);
void InputData(string &FileName, Voxel &VoxSpace);
void CalcVoxNormal(Voxel &VoxSpace);
void FindOutsideVoxel1(Voxel &m);

extern OpenGL GLSettings0;
Voxel PM;


string Dire=".txt";
string Input="DATA/";

//string Filename="T_Voxel";
string Filename="voxeldata1";
string Fn="OUTDATA";



Point3d Color_Mapping(double cur, double max, double min, int casenumber);

CColor Colormap(double Max,double Min,double cur){
	CColor temp;
	double CC=0.0;
	Max = Max-Min;
	cur = cur - Min;
	Min =0;
	double Mean = (Max+Min)/2.0;
	double Quarter = (Max+Min)/4.0;
			//á@0Å`0.25
		if(cur < Quarter){
			CC =1.0- (double)(Quarter-cur)/(double)Quarter;
			temp.Set(0.0,CC,1.0);
		}
		//áA0.25Å`0.50
		else if(cur < Mean){
			CC =(double)(Mean-cur)/(double)(Mean-Quarter);
			temp.Set(0.0,1.0,CC);
		}		
		//áB0.50Å`0.75
		else if(cur < Quarter*3){
			CC =1.0- (double)(Quarter*3-cur)/(double)(Quarter*3-Mean);
			temp.Set(CC,1.0,0.0);
		}				
		//áC0.75Å`1.00
		else if(cur < Max){
			CC =(double)(Max-cur)/(double)(Max-Quarter*3);
			temp.Set(1.0,CC,0.0);
		}
		else{
			temp.Set(1.0,0.0,0.0);
		}
	return temp;
}

int main(int argc, char *argv[]){
	string Inputfilename;
	string FileName;

	//for(int i(0); i< argc;i++)
	//	Inputfilename=argv[i];
	//FileName=Inputfilename.substr(Inputfilename.rfind("\\")+1,Inputfilename.size()-Inputfilename.rfind("\\"));


	InputData(Filename+Dire,PM);
	//InputData(FileName,PM);
	
	//PM.Fillcontent();
	FindOutsideVoxel1(PM);
	//
	CalcVoxNormal(PM);

	ofstream fout(Fn+Dire);
	fout<<PM.ND[0]-2<<"  "<<PM.ND[1]-2<<"  "<<PM.ND[2]-2<<"  "<<PM.Length<<endl;
	fout<<PM.OriPt.x<<"  "<<PM.OriPt.y<<"  "<<PM.OriPt.z<<endl;
	for(int x=1; x<PM.ND[0]-1; ++x)				//x:1~ND[0]-2
	{
		for(int y=1; y<PM.ND[1]-1; ++y)			   
		{
			for(int z=1; z< PM.ND[2]-1; ++z)	{	
				if(!PM.Grid3D[x][y][z].Fill)continue;
				fout<<x-1<<"  "<<y-1<<"  "<<z-1<<"  "<<PM.Grid3D[x][y][z].Dist<<endl;
		}
	}
}
	double Max=0.0;
	double Min=0.0;
	for(int x=1; x<PM.ND[0]-1; ++x)				//x:1~ND[0]-2
	{
		for(int y=1; y<PM.ND[1]-1; ++y)			   
		{
			for(int z=1; z< PM.ND[2]-1; ++z)	{	
				if(!PM.Grid3D[x][y][z].Fill)continue;
				if (Max<PM.Grid3D[x][y][z].Dist){
					Max =PM.Grid3D[x][y][z].Dist;
				}
			}
		}
	}
	for(int x=1; x<PM.ND[0]-1; ++x)				//x:1~ND[0]-2ÅE
	{
		for(int y=1; y<PM.ND[1]-1; ++y)			   
		{
			for(int z=1; z< PM.ND[2]-1; ++z)	{	
				if(!PM.Grid3D[x][y][z].Fill)continue;
			PM.Grid3D[x][y][z].Color = Color_Mapping(PM.Grid3D[x][y][z].Dist-Max/2.0,Max/2.0,-Max/2.0,1);
			PM.Grid3D[x][y][z].C = Colormap(Max,0.0,PM.Grid3D[x][y][z].Dist);
			}
		}
	}
	RunOpenGL0(argc, argv);

}


Point3d Color_Mapping(double cur, double max, double min, int casenumber){

	Point3d color;
	double tol_col_max;
	double tol_col_min;

	if (casenumber == 0){

		double mid2, bad, good, mid1;

		bad = (max - min)*0.8;
		mid1 = (max - min)*0.6;
		mid2 = (max - min)*0.4;
		good = (max - min)*0.2;


		if (cur >= bad){						//0.8-
			color.r[0] = 1.0;
			color.r[1] = 0.0;
			color.r[2] = 0.0;
		}
		else if (cur >= mid1 && cur < bad){		//0.6-0.8
			color.r[0] = 1.0;
			color.r[1] = 1.0;
			color.r[2] = 0.0;
		}
		else if (cur >= mid2 && cur < mid1){	//0.4-0.6
			color.r[0] = 0.0;
			color.r[1] = 1.0;
			color.r[2] = 0.0;
		}
		else if (cur >= good && cur < mid2){	//0.2-0.4
			color.r[0] = 0.0;
			color.r[1] = 1.0;
			color.r[2] = 1.0;
		}
		else if (cur < good){					//-0.2
			color.r[0] = 0.0;
			color.r[1] = 0.0;
			color.r[2] = 1.0;
		}

	}

	if (casenumber == 1){
		if (max == 0 && min == 0)
			return(Point3d(0.0, 1.0, 0.0));
		tol_col_max = max;
		tol_col_min = min;
		double div = (tol_col_max - tol_col_min) / 8.0;
		double maxdiv = (tol_col_max - tol_col_min) / 6.0;
		double mindiv = (tol_col_max - tol_col_min) / 6.0;


		if (cur >= 2 * maxdiv){
			color.r[0] = 1.0;
			color.r[1] = 0.0;											//G	
			color.r[2] = 0.0;
		}if (cur >= maxdiv && cur < 2 * maxdiv){
			color.r[0] = 1.0;
			color.r[1] = 1.0 - 1.0 * (-maxdiv + cur) / (maxdiv);													//G	
			color.r[2] = 0.0;
		}
		else if (cur >= 0.0 && cur < 0.0 + maxdiv){
			color.r[0] = 1.0 * (cur) / maxdiv;
			color.r[1] = 1.0;											//G	
			color.r[2] = 0.0;
		}
		else if (cur >= -mindiv && cur < 0.0){
			color.r[0] = 0.0;
			color.r[1] = 1.0; 												//G	
			color.r[2] = 1.0 - 1.0 * (cur + mindiv) / mindiv;
		}
		else if (cur >= -2 * mindiv && cur < -mindiv){
			color.r[0] = 0.0;
			color.r[1] = 1.0 + 1.0 * (cur + mindiv) / (mindiv);											//G	
			color.r[2] = 1.0;
		}
		else if (cur < -2 * mindiv){
			color.r[0] = 0.0;
			color.r[1] = 0.0;
			color.r[2] = 1.0;
		}

		//cout << color.r[1]<<endl;
		if (color.r[0] >= 1.0)	color.r[0] = 1.0;
		if (color.r[1] >= 1.0)	color.r[1] = 1.0;
		if (color.r[2] >= 1.0)	color.r[2] = 1.0;

		if (color.r[0] <= 0.0)	color.r[0] = 0.0;
		if (color.r[1] <= 0.0)	color.r[1] = 0.0;
		if (color.r[2] <= 0.0)	color.r[2] = 0.0;

	}

	return (color);
}