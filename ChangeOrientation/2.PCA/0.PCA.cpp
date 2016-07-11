#include "../stdafx.h"

using namespace std;

extern Model UP;		//UP
extern Model DOWN;		//DOWN
extern CVector3d centroid;


vector<CVector3d> UPsurf;
vector<CVector3d> DOWNsurf;		//DOWN

extern CMatrix PCAMatrix;
CMatrix *Rt;

int RtNum = 0;//4
void FindOutsideVoxel1(Model& m);
void SetSrufToVector1(Model& m);
void FreeMemory_Voxel1(Model& m);

void CalcPA(Model& m);

void OutsideVoxeltoVector(Model &m, vector<CVector3d> &surf);
void RenewPointwithMatrix(vector<CVector3d> &point, CMatrix &mat);
void FindCorresPoint(vector<OnetoOne> &upone, vector<OnetoOne> &downone, MyKdTree& upTree, vector<CVector3d> &downsurf, const double thres);
double CalcAveofPoint(vector<CVector3d> &up, vector<CVector3d> &down);


void MakeMatrix(Model& up, Model& down, CMatrix *Rt);
void RunOpenGL1(int argc, char *argv[]);

//argc
//argv
int PCA1(int argc, char *argv[]){
	cout << "====================================\n             PCA             \n====================================" << endl;
	//															          
	//           	          
	//														              
	clock_t time[6];
	time[0] = clock();

	Rt = new CMatrix[4];
	for (int i = 0; i < 4; i++)
		Rt[i].assign(4, 4);

#pragma omp parallel sections
	{
#pragma omp section
		FindOutsideVoxel1(UP);
#pragma omp section
		FindOutsideVoxel1(DOWN);
	}
	cout << "UP\n" << "Voxelnum " << UP.VoxelNum << "\nFillVoxelNum:" << UP.FillVoxelNum << "\nSurfaceNum:" << UP.SurfNum << endl;
	cout << "DOWN\n" << "Voxelnum " << DOWN.VoxelNum << "\nFillVoxelnum:" << DOWN.FillVoxelNum << "\nSurfaceNum:" << DOWN.SurfNum << endl << endl;

	// 
#pragma omp parallel sections
	{
#pragma omp section
		SetSrufToVector1(UP);
		FreeMemory_Voxel1(UP);
#pragma omp section
		SetSrufToVector1(DOWN);
		FreeMemory_Voxel1(DOWN);
	}

//	RunOpenGL1(argc, argv);	//OpenGL


	
	time[1] = clock();
	cout << "Time to loading data" << (double)(time[1] - time[0]) / CLOCKS_PER_SEC << "s" << endl;
	cout << "Up Surface voxel size: " << UP.SurfVoxels.size();

	CalcPA(UP);//P model principal axis
	CalcPA(DOWN);//Q model principal axis 
	//
	centroid = UP.CoV;
	MakeMatrix(UP, DOWN, Rt);

	time[2] = clock();
	printf("Time to calculate the PCA: %.2f(s)\n", (double)(time[2] - time[0]) / CLOCKS_PER_SEC);

	//4---------------------------
	//kdtree 2014/08/08
	const double thres(15.0);		//
	double error[4];				//4

	UPsurf.reserve(UP.SurfNum);
	DOWNsurf.reserve(DOWN.SurfNum);

	vector<CVector3d> UPcorres;		//UP
	vector<CVector3d> DOWNcorres;	//DOWN
	UPcorres.reserve(UP.SurfNum);
	DOWNcorres.reserve(DOWN.SurfNum);
	//getchar();
	                                                                             
#pragma omp parallel sections
	{
#pragma omp section
		OutsideVoxeltoVector(UP, UPsurf);
#pragma omp section
		OutsideVoxeltoVector(DOWN, DOWNsurf);
	}

	//MyKdTree upTree;	//kdtree
	//upTree.setInputCloud(UPsurf);
	//
	////DOWNsurf
	//for (int j = 0; j < 4; j++){
	//	RenewPointwithMatrix(DOWNsurf, Rt[j]);
	//
	//	vector<OnetoOne> UPone(UP.SurfNum);								
	//	vector<OnetoOne> DOWNone(DOWN.SurfNum);							
	//	FindCorresPoint(UPone, DOWNone, upTree, DOWNsurf, thres);		
	//	for (int i(0); i < DOWNsurf.size(); i++){
	//		if (DOWNone[i].flag){
	//			DOWNcorres.push_back(DOWNsurf[i]);						
	//			UPcorres.push_back(UPsurf[DOWNone[i].num]);				
	//		}
	//	}
	//	UPone.clear();													
	//	UPone.resize(UP.SurfNum);										
	//	DOWNone.clear();
	//	DOWNone.resize(DOWN.SurfNum);
	//	//
	//	error[j] = CalcAveofPoint(UPcorres, DOWNcorres);
	//	UPcorres.clear();
	//	DOWNcorres.clear();
	//}
	//

	//int Rnum = 0;
	int Rnum = 2;    //frog 20,30,40,50  //panda 0,

	//double Emin = DBL_MAX;
	//for (int i = 0; i < 4; i++){
	//	cout << "error: " << error[i] << endl;
	//	if (error[i] < Emin){
	//		Rnum = i;
	//		Emin = error[i];
	//	}
	//}
	//
	RtNum = Rnum;
	cout << "RT num " << RtNum << endl;

	//
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){

			PCAMatrix(i, j) = Rt[RtNum](i, j);
			cout << Rt[RtNum].At(i, j) << " ";
		}
		cout << endl;
	}
	//try
	ofstream fout("PCAMAtrix.txt");
	fout << "Matrix " << RtNum << endl;
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			fout << Rt[RtNum].At(i, j) << " ";
		}
		fout << endl;
	}
	//getchar();

	//RunOpenGL1(argc, argv);	//OpenGL


	UP.Save_Up_Octrees.clear();
	UP.Save_Up_Octrees.shrink_to_fit();
	UP.Save_Down_Octrees.clear();
	UP.Save_Down_Octrees.shrink_to_fit();

	UP.max_vertex_point.clear();
	UP.max_vertex_point.shrink_to_fit();

	UP.min_vertex_point.clear();
	UP.min_vertex_point.shrink_to_fit();

	delete[] Rt;
	return 0;

}