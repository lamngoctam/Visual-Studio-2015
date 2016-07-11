#include "../stdafx.h"



void CalcRt(CMatrix &Rt, CVector3d *PFP, CVector3d *QFP);

void MakeMatrix(Model& up, Model& down, CMatrix *Rt)
{
	//Principal axis‚

	CVector3d *PFP;//UP
	PFP = new CVector3d[3];
	CVector3d *QFP;//DOWN
	QFP = new CVector3d[3];

	PFP[0] = up.CoV;
	PFP[1] = up.CoV + up.PrAxix[0];
	PFP[2] = up.CoV + up.PrAxix[1];

	int pm1, pm2;
	for (int i = 0; i < 4; i++){
		if (i / 2) pm1 = 1; // i= 0,1
		else pm1 = -1;   // i= 2,3 

		if (i % 2) pm2 = 1;  //i%2==1; mean i=1,3 odd number
		else pm2 = -1;    //else i%2==0; mean i=0,2 even number

		QFP[0] = down.CoV;
		QFP[1] = down.CoV + pm1 * down.PrAxix[0];
		QFP[2] = down.CoV + pm2 * down.PrAxix[1];

		CalcRt(Rt[i], PFP, QFP);
	}

}

bool Jacobi(double(&a)[4][4], double(&v)[4][4], double(&d)[4]);

void CalcRt(CMatrix &Rt, CVector3d *PFP, CVector3d *QFP)
{
	//#################################################
	//	step1 Find the corresponding pint
	//#################################################

	CVector3d PAve, QAve;//Coordinate point

	//
	PAve = 1.0 / 3.0 * PFP[0] + 1.0 / 3.0 * PFP[1] + 1.0 / 3.0 * PFP[2];
	QAve = 1.0 / 3.0 * QFP[0] + 1.0 / 3.0 * QFP[1] + 1.0 / 3.0 * QFP[2];


	//#################################################
	//	step2 - Covariance Matrix
	//#################################################
	CMatrix Cov(3, 3); //
	Cov.SetZero();

	for (int i = 0; i < 3; i++){
		Cov.At(0, 0) += (QFP[i].x - QAve.x)*(PFP[i].x - PAve.x);
		Cov.At(0, 1) += (QFP[i].x - QAve.x)*(PFP[i].y - PAve.y);
		Cov.At(0, 2) += (QFP[i].x - QAve.x)*(PFP[i].z - PAve.z);

		Cov.At(1, 0) += (QFP[i].y - QAve.y)*(PFP[i].x - PAve.x);
		Cov.At(1, 1) += (QFP[i].y - QAve.y)*(PFP[i].y - PAve.y);
		Cov.At(1, 2) += (QFP[i].y - QAve.y)*(PFP[i].z - PAve.z);

		Cov.At(2, 0) += (QFP[i].z - QAve.z)*(PFP[i].x - PAve.x);
		Cov.At(2, 1) += (QFP[i].z - QAve.z)*(PFP[i].y - PAve.y);
		Cov.At(2, 2) += (QFP[i].z - QAve.z)*(PFP[i].z - PAve.z);
	}

	Cov = (1 / 3.0)*Cov;//±‚1/3

	//cout << "Cov" << endl;
	//for (int i = 0; i < 3; i++){
	//	for (int j = 0; j < 3; j++){
	//		cout << setw(8) << Cov.At(i, j) << " ";
	//	}
	//	cout << endl;
	//}

	//#############################//
	//#### step3  Quadterion   ####//
	//#############################//
	CMatrix CovT(3, 3);//covariance transpose martrix
	CovT.SetZero();
	CovT = Cov.Transpose();

	CMatrix A(3, 3);//subtraction amtrix
	A.SetZero();

	A = Cov - CovT;

	CVector3d D;//vector
	D.x = A.At(1, 2);
	D.y = A.At(2, 0);
	D.z = A.At(0, 1);

	double s = 0;//scale
	s = Cov.At(0, 0) + Cov.At(1, 1) + Cov.At(2, 2);

	CMatrix SI(3, 3);//double s the identity matrix
	SI.IdentifyMatrix();
	SI = s*SI;

	CMatrix T(3, 3);//
	T.SetZero();
	T = Cov + CovT - SI;

	//cout << "T = (Cov + Cov^t) - s*I ‚Ì•\Ž¦" << endl;
	//for(int i=0; i<3; i++){
	//	for(int j=0; j<3; j++) cout << ' ' << T.At(i,j);
	//	cout << endl;
	//}
	//cout << endl;

	double Q[4][4];
	Q[0][0] = s;
	Q[0][1] = D.x;
	Q[0][2] = D.y;
	Q[0][3] = D.z;

	Q[1][0] = D.x;
	Q[1][1] = T.At(0, 0);
	Q[1][2] = T.At(0, 1);
	Q[1][3] = T.At(0, 2);

	Q[2][0] = D.y;
	Q[2][1] = T.At(1, 0);
	Q[2][2] = T.At(1, 1);
	Q[2][3] = T.At(1, 2);

	Q[3][0] = D.z;
	Q[3][1] = T.At(2, 0);
	Q[3][2] = T.At(2, 1);
	Q[3][3] = T.At(2, 2);

	//#########################################################//
	//#### Step3.1  Largest Eigenvalue & Eigenvector       ####//
	//#########################################################//
	double Eramda[4];
	double Evector[4][4];
	CPoint3d q;

	Jacobi(Q, Evector, Eramda);

	//####
	double max = Eramda[0];
	int maxn = 0;
	for (int i = 0; i < 4; i++){
		if (max < Eramda[i]){
			max = Eramda[i];
			maxn = i;
		}
	}
	q.x = Evector[0][maxn];
	q.y = Evector[1][maxn];
	q.z = Evector[2][maxn];
	q.w = Evector[3][maxn];

	//#################################//
	//#### Step4 Rotation matrix   ####//
	//#################################//
	CMatrix Tr(4, 4);
	Tr.SetZero();

	Tr.At(0, 0) = q.x*q.x + q.y*q.y - q.z*q.z - q.w*q.w;
	Tr.At(0, 1) = 2 * (q.y*q.z - q.x*q.w);
	Tr.At(0, 2) = 2 * (q.y*q.w + q.x*q.z);

	Tr.At(1, 0) = 2 * (q.y*q.z + q.x*q.w);
	Tr.At(1, 1) = q.x*q.x + q.z*q.z - q.y*q.y - q.w*q.w;
	Tr.At(1, 2) = 2 * (q.z*q.w - q.x*q.y);

	Tr.At(2, 0) = 2 * (q.y*q.w - q.x*q.z);
	Tr.At(2, 1) = 2 * (q.z*q.w + q.x*q.y);
	Tr.At(2, 2) = q.x*q.x + q.w*q.w - q.y*q.y - q.z*q.z;

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			//Rmat[i][j]=Tr.At(i,j);
			Rt(i, j) = Tr(i, j);
		}
	}

	//###################################//
	//#### Step5 Translation Martix ###//
	//###################################//
	CMatrix Trans(4, 1);
	CMatrix M1(4, 1), M2(4, 1);

	M1.At(0, 0) = PAve.x;
	M1.At(1, 0) = PAve.y;
	M1.At(2, 0) = PAve.z;
	M1.At(3, 0) = 1;

	M2.At(0, 0) = QAve.x;
	M2.At(1, 0) = QAve.y;
	M2.At(2, 0) = QAve.z;
	M2.At(3, 0) = 1;

	Trans = M1 - Tr*M2;

	for (int i = 0; i < 3; i++){
		//Tmat[i]=Trans.At(i,0);
		Rt(i, 3) = Trans(i, 0);
	}

	Rt(3, 3) = 1.0;

	////###################################//
	////####      Step6 Output file     ###//
	////###################################//
	cout << "matrix Rt" << endl;
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			cout << setw(8) << Rt(i, j) << " ";
		}
		cout << endl;
	}

	ofstream fout("PCAMatrix1.txt");
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			fout << Rt.At(i, j) << " ";
		}
		fout << endl;
	}
}