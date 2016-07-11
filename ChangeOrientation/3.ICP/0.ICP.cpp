#include "../stdafx.h"

extern OctVoxel Angle_;
extern Model UP;
extern Model DOWN;

extern CMatrix ICPMatrix;
extern CMatrix PCAMatrix;
extern CMatrix TMatrix;

void OutsideVoxeltoVector(Model &m, vector<CVector3d> &surf);
void RenewPointwithMatrix(vector<CVector3d> &point, CMatrix &mat);
double CalcAveofPoint(vector<CVector3d> &up, vector<CVector3d> &down);

//void FindCorresPoint(vector<OnetoOne> &upone, vector<OnetoOne> &downone, vector<CVector3d> &upsurf, vector<CVector3d> &downsurf, const double thres);
void FindCorresPoint(vector<OnetoOne> &upone, vector<OnetoOne> &downone, MyKdTree& upTree, vector<CVector3d> &downsurf, const double thres);

void MakeMatrixICP(vector<CVector3d> &up, vector<CVector3d> &down, CMatrix &mat);
void RunOpenGL2(int argc, char *argv[]);


vector<CVector3d> UPsurf_ICP;				//UP
vector<CVector3d> DOWNsurf_ICP;			//DOWN

CMatrix ICPMatrixRod(4);
extern CVector3d moveback_midpoint;


//Iterative Closest Point –

int ICP(int argc, char *argv[])
{

	cout << "====================================\n               ICP              \n====================================" << endl;
	clock_t time[4];
	time[0] = clock();

	vector<CVector3d> UPsurf;				//UP
	vector<CVector3d> DOWNsurf;			//DOWN

	UPsurf.reserve(UP.SurfNum);
	DOWNsurf.reserve(DOWN.SurfNum);

	cout << "UPsurf" << UPsurf.size() << " " << UPsurf.capacity() << endl;
	cout << "DOWNsurf" << DOWNsurf.size() << " " << DOWNsurf.capacity() << endl;

	vector<CVector3d> UPcorres;			//UP
	vector<CVector3d> DOWNcorres;		//DOWN
	UPcorres.reserve(UP.SurfNum);
	DOWNcorres.reserve(DOWN.SurfNum);

	//                                          
	//                                          
	const double thres(10.0);
	double error(0.0);
	double oldError(0.0);
	double deltaError(0.0);		//deltaError = |error - oldError|
	double ErrorThres(0.01);

	int loopmax(150);
	CMatrix mat(4, 4);

	//                                                                             
	//                 
	//                                                                             
#pragma omp parallel sections
	{
#pragma omp section
		OutsideVoxeltoVector(UP, UPsurf);
#pragma omp section
		OutsideVoxeltoVector(DOWN, DOWNsurf);
	}
	cout << "UPsurf" << UPsurf.size() << " " << UPsurf.capacity() << endl;
	cout << "DOWNsurf" << DOWNsurf.size() << " " << DOWNsurf.capacity() << endl;

	MyKdTree upTree;
	upTree.setInputCloud(UPsurf);

	ICPMatrix = PCAMatrix;
	RenewPointwithMatrix(DOWNsurf, PCAMatrix);

	vector<OnetoOne> UPone(UP.SurfNum);
	vector<OnetoOne> DOWNone(DOWN.SurfNum);
	cout << "UPone" << UPone.size() << " " << UPone.capacity() << endl;
	cout << "DOWNone" << DOWNone.size() << " " << DOWNone.capacity() << endl;

	int counter(0);

	while (true)
	{
		//                                         
		//          step1
		time[1] = clock();
		//FindCorresPoint(UPone, DOWNone, UPsurf, DOWNsurf, thres);			//ICP2013/7/3
		FindCorresPoint(UPone, DOWNone, upTree, DOWNsurf, thres);			//ICP2013/7/3
		time[2] = clock();
	//	cout << counter << " time " << (double)(time[2] - time[1]) / CLOCKS_PER_SEC << "s" << endl; // "\n";

		//
		for (int i(0); i < DOWNsurf.size(); i++) {
			if (DOWNone[i].flag) {
				DOWNcorres.push_back(DOWNsurf[i]);				//DOWN
				UPcorres.push_back(UPsurf[DOWNone[i].num]);		//UP
			}
		}
		UPone.clear();
		UPone.resize(UP.SurfNum);
		DOWNone.clear();
		DOWNone.resize(DOWN.SurfNum);

		//RunOpenGL2(argc, argv);
		//                                         
		//          step2.             
		//                                         

		MakeMatrixICP(UPcorres, DOWNcorres, mat);

		ICPMatrix = mat*ICPMatrix;

		//                                         
		//            step3.              
		//                                         
		//DOWN
		RenewPointwithMatrix(DOWNcorres, mat);

		//
		error = CalcAveofPoint(UPcorres, DOWNcorres);
		UPcorres.clear();
		DOWNcorres.clear();

		counter++;
		deltaError = fabs(error - oldError);

	//	cout << "->>> [" << counter << "]" << "error " << error << "    delta Error " << deltaError << "\r";

		oldError = error;
		//                                         
		//             step4.            
		//                                         
		//
		if (error < ErrorThres || loopmax <= counter || deltaError == 0.0)
			break;

		//                                         
		//           step5.        
		//                                         
		else
			RenewPointwithMatrix(DOWNsurf, mat);

	}

	UPsurf_ICP = UPsurf;
	DOWNsurf_ICP = DOWNsurf;

	cout << "/nICP Matrix" << endl;
	ofstream fin("ICPMatrix.txt");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << setw(8) << ICPMatrix(i, j) << " ";
			fin << setw(8) << ICPMatrix(i, j) << " ";
		}
		fin << endl;
		cout << endl;
	}
	time[3] = clock();
	cout << "ICP  " << (double)(time[3] - time[0]) / CLOCKS_PER_SEC << " s" << endl;

	cout << " IdentifyMatrix:   " << endl;
	TMatrix.IdentifyMatrix();

	ICPMatrixRod.SetZero();
	ICPMatrixRod(3, 3) = 1.0;

	//ICPMatrixRod.At(0, 0) = ICPMatrix.At(0, 0);
	//ICPMatrixRod.At(1, 0) = ICPMatrix.At(1, 0);
	//ICPMatrixRod.At(2, 0) = ICPMatrix.At(2, 0);
	//
	//ICPMatrixRod.At(0, 1) = ICPMatrix.At(0, 1);
	//ICPMatrixRod.At(1, 1) = ICPMatrix.At(1, 1);
	//ICPMatrixRod.At(2, 1) = ICPMatrix.At(2, 1);
	//
	//ICPMatrixRod.At(0, 2) = ICPMatrix.At(0, 2);
	//ICPMatrixRod.At(1, 2) = ICPMatrix.At(1, 2);
	//ICPMatrixRod.At(2, 2) = ICPMatrix.At(2, 2);
	//
	//ICPMatrixRod.At(0, 3) = ICPMatrix.At(0, 3) + moveback_midpoint.x;
	//ICPMatrixRod.At(1, 3) = ICPMatrix.At(1, 3) + moveback_midpoint.y;
	//ICPMatrixRod.At(2, 3) = ICPMatrix.At(2, 3) + moveback_midpoint.z;

	CVector3d W_(0.0, 0.0, 1.0);
	CMatrix Rod(3, 3);  //matrix rotation
	Rod.SetZero();
	double Theta = -Angle_.Orientation_Angle;
	Rod.At(0, 0) = cos(Theta) + W_.x*W_.x*(1 - cos(Theta));
	Rod.At(1, 0) = W_.z*sin(Theta) + W_.x*W_.y*(1 - cos(Theta));
	Rod.At(2, 0) = -W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));

	Rod.At(0, 1) = W_.x*W_.y*(1 - cos(Theta)) - W_.z*sin(Theta);
	Rod.At(1, 1) = cos(Theta) + W_.y*W_.y*(1 - cos(Theta));
	Rod.At(2, 1) = W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));

	Rod.At(0, 2) = W_.y*sin(Theta) + W_.x*W_.z*(1 - cos(Theta));
	Rod.At(1, 2) = -W_.x*sin(Theta) + W_.y*W_.z*(1 - cos(Theta));
	Rod.At(2, 2) = cos(Theta) + W_.z*W_.z*(1 - cos(Theta));

	ICPMatrixRod.At(0, 0) = Rod.At(0, 0)*ICPMatrix.At(0, 0) + Rod.At(0, 1)*ICPMatrix.At(1, 0) + Rod.At(0, 2)*ICPMatrix.At(2, 0);
	ICPMatrixRod.At(1, 0) = Rod.At(1, 0)*ICPMatrix.At(0, 0) + Rod.At(1, 1)*ICPMatrix.At(1, 0) + Rod.At(1, 2)*ICPMatrix.At(2, 0);
	ICPMatrixRod.At(2, 0) = Rod.At(2, 0)*ICPMatrix.At(0, 0) + Rod.At(2, 1)*ICPMatrix.At(1, 0) + Rod.At(2, 2)*ICPMatrix.At(2, 0);

	ICPMatrixRod.At(0, 1) = Rod.At(0, 0)*ICPMatrix.At(0, 1) + Rod.At(0, 1)*ICPMatrix.At(1, 1) + Rod.At(0, 2)*ICPMatrix.At(2, 1);
	ICPMatrixRod.At(1, 1) = Rod.At(1, 0)*ICPMatrix.At(0, 1) + Rod.At(1, 1)*ICPMatrix.At(1, 1) + Rod.At(1, 2)*ICPMatrix.At(2, 1);
	ICPMatrixRod.At(2, 1) = Rod.At(2, 0)*ICPMatrix.At(0, 1) + Rod.At(2, 1)*ICPMatrix.At(1, 1) + Rod.At(2, 2)*ICPMatrix.At(2, 1);

	ICPMatrixRod.At(0, 2) = Rod.At(0, 0)*ICPMatrix.At(0, 2) + Rod.At(0, 1)*ICPMatrix.At(1, 2) + Rod.At(0, 2)*ICPMatrix.At(2, 2);
	ICPMatrixRod.At(1, 2) = Rod.At(1, 0)*ICPMatrix.At(0, 2) + Rod.At(1, 1)*ICPMatrix.At(1, 2) + Rod.At(1, 2)*ICPMatrix.At(2, 2);
	ICPMatrixRod.At(2, 2) = Rod.At(2, 0)*ICPMatrix.At(0, 2) + Rod.At(2, 1)*ICPMatrix.At(1, 2) + Rod.At(2, 2)*ICPMatrix.At(2, 2);

	
	ICPMatrixRod.At(0, 3) = Rod.At(0, 0)*ICPMatrix.At(0, 3) + Rod.At(0, 1)*ICPMatrix.At(1, 3) + Rod.At(0, 2)*ICPMatrix.At(2, 3);
	ICPMatrixRod.At(1, 3) = Rod.At(1, 0)*ICPMatrix.At(0, 3) + Rod.At(1, 1)*ICPMatrix.At(1, 3) + Rod.At(1, 2)*ICPMatrix.At(2, 3);
	ICPMatrixRod.At(2, 3) = Rod.At(2, 0)*ICPMatrix.At(0, 3) + Rod.At(2, 1)*ICPMatrix.At(1, 3) + Rod.At(2, 2)*ICPMatrix.At(2, 3);
	
//	RunOpenGL2(argc, argv);


	//=============
	//
	// After we get the [RT]ICP matrixin order to integrate Q Model to P Model, 
	// we delete all information of Up-Down surface Voxels

	UPsurf.clear();
	UPsurf.shrink_to_fit();
	DOWNsurf.clear();
	DOWNsurf.shrink_to_fit();
	UPcorres.clear();
	UPcorres.shrink_to_fit();
	DOWNcorres.clear();
	DOWNcorres.shrink_to_fit();
	UPone.clear();
	UPone.shrink_to_fit();
	DOWNone.clear();
	DOWNone.shrink_to_fit();

	UP.SurfVoxels.clear();
	UP.SurfVoxels.shrink_to_fit();
	DOWN.SurfVoxels.clear();
	DOWN.SurfVoxels.shrink_to_fit();

	return 0;
}