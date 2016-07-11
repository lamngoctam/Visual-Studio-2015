#include "../stdafx.h"		


bool Jacobi( double (&a)[4][4], double (&v)[4][4], double (&d)[4]);

void MakeMatrixICP(vector<CVector3d> &up, vector<CVector3d> &down, CMatrix &mat)
{
	//#################################################
	//  	step1 
	//#################################################

	CVector3d upAve(0.0, 0.0, 0.0);		
	CVector3d downAve(0.0, 0.0, 0.0);	

	//Ave
	int i,j;
	for(i=0; i<down.size(); i++){
		upAve += up[i];
		downAve += down[i];
	}
	//
	upAve = (1.0/up.size()) * upAve;
	downAve = (1.0/down.size()) * downAve;


	//#################################################
	//          	step2          
	//#################################################
	CMatrix Cov(3,3); 
	Cov.SetZero();

	for(i=0; i<down.size(); i++){

		Cov(0,0) += (down[i].x - downAve.x)*(up[i].x - upAve.x);
		Cov(0,1) += (down[i].x - downAve.x)*(up[i].y - upAve.y);
		Cov(0,2) += (down[i].x - downAve.x)*(up[i].z - upAve.z);

		Cov(1,0) += (down[i].y - downAve.y)*(up[i].x - upAve.x);
		Cov(1,1) += (down[i].y - downAve.y)*(up[i].y - upAve.y);
		Cov(1,2) += (down[i].y - downAve.y)*(up[i].z - upAve.z);

		Cov(2,0) += (down[i].z - downAve.z)*(up[i].x - upAve.x);
		Cov(2,1) += (down[i].z - downAve.z)*(up[i].y - upAve.y);
		Cov(2,2) += (down[i].z - downAve.z)*(up[i].z - upAve.z);
	}

	Cov=(1.0/down.size())*Cov;//‚±‚1/3


	//################################//
	//#### step3   ####//
	//################################//
	CMatrix CovT(3,3);	//‹¤•ªŽUs—ñ‚Ì“]’u
	CovT.SetZero();
	CovT=Cov.Transpose();//“]’u‚³‚¹‚é

	CMatrix A(3,3);		//‹¤•ªŽUs—ñ‚Æ‚»‚Ì“]’u‚Ìˆø‚«ŽZ
	A.SetZero();

	A=Cov-CovT;

	CVector3d D;//sƒxƒNƒgƒ‹??
	D.x=A(1,2);
	D.y=A(2,0);
	D.z=A(0,1);

	double s=0;//ƒXƒJƒ‰[
	s=Cov(0,0)+Cov(1,1)+Cov(2,2);

	CMatrix SI(3,3);		//’PˆÊs—ñ‚Ì‚“”{
	SI.IdentifyMatrix();	//’PˆÊs—ñ
	SI=s*SI;				//’PˆÊs—ñ‚ð‚“”{‚·‚é

	CMatrix T(3,3);			//s—ñT‚ð’è‹`
	T.SetZero();
	T=Cov+CovT-SI;

	double Q[4][4];
	Q[0][0] = s;
	Q[0][1] = D.x;
	Q[0][2] = D.y;
	Q[0][3] = D.z;

	Q[1][0] = D.x;
	Q[1][1] = T(0,0);
	Q[1][2] = T(0,1);
	Q[1][3] = T(0,2);

	Q[2][0] = D.y;
	Q[2][1] = T(1,0);
	Q[2][2] = T(1,1);
	Q[2][3] = T(1,2);

	Q[3][0] = D.z;
	Q[3][1] = T(2,0);
	Q[3][2] = T(2,1);
	Q[3][3] = T(2,2);


	//#########################################################//
	//#### Step3.1                                          ####//
	//#########################################################//
	double Eramda[4];		//ŒÅ—L’l
	double Evector[4][4];	//ŒÅ—LƒxƒNƒgƒ‹
	CPoint3d q;

	Jacobi( Q, Evector, Eramda);//s—ñQ‚ÌŒÅ—L’l(Eramda)‚ÆŒÅ—LƒxƒNƒgƒ‹(Evector)‚ÌŒvŽZ??

	//####Å‘åŒÅ—L’l‚ð’T‚·B
	double max = Eramda[0];
	int maxn =0;
	for(i=0;i<4;i++){
		if(max < Eramda[i]){
			max = Eramda[i];
			maxn = i;
		}
	}
	q.x = Evector[0][maxn];
	q.y = Evector[1][maxn];
	q.z = Evector[2][maxn];
	q.w = Evector[3][maxn];

	//#################################//
	//#### Step4 ‰ñ“]s—ñ‚ð‹‚ß‚éB ####//
	//#################################//
	CMatrix Tr(4,4);//‰ñ“]s—ñ‚Ì¶¬
	Tr.SetZero();

	Tr(0,0) = q.x*q.x+q.y*q.y-q.z*q.z-q.w*q.w;
	Tr(0,1) = 2*(q.y*q.z-q.x*q.w);
	Tr(0,2) = 2*(q.y*q.w+q.x*q.z);

	Tr(1,0) = 2*(q.y*q.z+q.x*q.w);
	Tr(1,1) = q.x*q.x+q.z*q.z-q.y*q.y-q.w*q.w;
	Tr(1,2) = 2*(q.z*q.w-q.x*q.y);

	Tr(2,0) = 2*(q.y*q.w-q.x*q.z);
	Tr(2,1) = 2*(q.z*q.w+q.x*q.y);
	Tr(2,2) = q.x*q.x+q.w*q.w-q.y*q.y-q.z*q.z;

	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			mat(i,j)=Tr(i,j);
		}
	}

	//###################################//
	//#### Step5 •ÀiƒxƒNƒgƒ‹‚ð‹‚ß‚é@###//
	//###################################//
	CMatrix Trans(4,1);//•ÀiƒxƒNƒgƒ‹
	CMatrix M1(4,1);
	CMatrix M2(4,1);

	M1(0,0) = upAve.x;
	M1(1,0) = upAve.y;
	M1(2,0) = upAve.z;
	M1(3,0) = 1.0;

	M2(0,0) = downAve.x;
	M2(1,0) = downAve.y;
	M2(2,0) = downAve.z;
	M2(3,0) = 1.0;

	Trans = M1-Tr*M2;

	for(i=0 ; i<3; i++){
		mat(i,3)=Trans(i,0);
	}

	mat(3,3)=1.0;


	//###################################//
	//####      Step6 Output file     ###//
	//###################################//
	//cout<<"Spin image‚Ì‰ñ“]•Àis—ñF"<<endl;
	//for(int i=0;i<4;i++){
	//	for(int j=0;j<4;j++){
	//		cout<<setw(8)<<mat(i,j)<<" ";
	//	}
	//	cout<<endl;
	//}


}