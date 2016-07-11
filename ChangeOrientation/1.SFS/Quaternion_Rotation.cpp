#include "../stdafx.h"


//void Quaternion_Rotation(){


	////==============================================================================//
	//// Use Quaternion method to calculate the Rotation matrix and translation vector
	////==============================================================================//
	//
	////void CalcRt(CMatrix &Rt, CVector3d *P_PrincipalAxis, CVector3d *Q_PrincipalAxis){
	//
	////#################################################
	////	step1 Find the corresponding pint
	////#################################################
	//
	////Coordinate point
	//CVector3d PAve, QAve;  // average
	//PAve = 1.0 / 3.0* P_PrincipalAxis[0] + 1.0 / 3.0* P_PrincipalAxis[1] + 1.0 / 3.0* P_PrincipalAxis[2];
	//QAve = 1.0 / 3.0* Q_PrincipalAxis[0] + 1.0 / 3.0* Q_PrincipalAxis[1] + 1.0 / 3.0* Q_PrincipalAxis[2];
	//
	//
	////PAve = (P_PrincipalAxis[0] + P_PrincipalAxis[1] + P_PrincipalAxis[2]) * (1.0 / 3.0);
	////QAve = (Q_PrincipalAxis[0] + Q_PrincipalAxis[1] + Q_PrincipalAxis[2]) * (1.0 / 3.0);
	////#################################################
	////	step2 - Covariance Matrix
	////#################################################
	//CMatrix Cov(3, 3); //
	//Cov.SetZero();
	//
	//for (int i = 0; i < 3; i++){
	//	Cov.At(0, 0) += (Q_PrincipalAxis[i].x - QAve.x)*(P_PrincipalAxis[i].x - PAve.x);
	//	Cov.At(0, 1) += (Q_PrincipalAxis[i].x - QAve.x)*(P_PrincipalAxis[i].y - PAve.y);
	//	Cov.At(0, 2) += (Q_PrincipalAxis[i].x - QAve.x)*(P_PrincipalAxis[i].z - PAve.z);
	//
	//	Cov.At(1, 0) += (Q_PrincipalAxis[i].y - QAve.y)*(P_PrincipalAxis[i].x - PAve.x);
	//	Cov.At(1, 1) += (Q_PrincipalAxis[i].y - QAve.y)*(P_PrincipalAxis[i].y - PAve.y);
	//	Cov.At(1, 2) += (Q_PrincipalAxis[i].y - QAve.y)*(P_PrincipalAxis[i].z - PAve.z);
	//
	//	Cov.At(2, 0) += (Q_PrincipalAxis[i].z - QAve.z)*(P_PrincipalAxis[i].x - PAve.x);
	//	Cov.At(2, 1) += (Q_PrincipalAxis[i].z - QAve.z)*(P_PrincipalAxis[i].y - PAve.y);
	//	Cov.At(2, 2) += (Q_PrincipalAxis[i].z - QAve.z)*(P_PrincipalAxis[i].z - PAve.z);
	//}
	//
	//Cov = (1 / 3.0)*Cov;
	//cout << "\nCovariance " << endl;
	////cout << "[" << Cov.At(0, 0) << " " << Cov.At(0, 1) << " " << Cov.At(0, 2) 
	////	<< "]\n["<< Cov.At(1, 0) << " " << Cov.At(1, 1) << " " << Cov.At(1, 2) 
	////	<< "]\n[" << Cov.At(2, 0) << " " << Cov.At(2, 1) << " " << Cov.At(2, 2) << "]\n" << endl;
	////
	////getchar();
	//
	////#############################//
	////#### step3  Quadterion   ####//
	////#############################//
	//CMatrix CovTrans(3, 3);	//covariance transpose martrix
	//CovTrans.SetZero();
	//CovTrans = Cov.Transpose();
	//
	//CMatrix A(3, 3);	//subtraction matrix
	//A.SetZero();
	//
	//A = Cov - CovTrans;
	//
	//CVector3d D;//�vector
	//D.x = A.At(1, 2);
	//D.y = A.At(2, 0);
	//D.z = A.At(0, 1);
	//
	//double scale = 0;		//scale
	//scale = Cov.At(0, 0) + Cov.At(1, 1) + Cov.At(2, 2);
	//
	//CMatrix SI(3, 3);	//double s the identity matrix
	//SI.IdentifyMatrix();//Identity matrix
	//SI = scale*SI;
	//
	//CMatrix T(3, 3);//�
	//T.SetZero();
	//T = Cov + CovTrans - SI;
	//
	//double Q[4][4];
	//Q[0][0] = scale;
	//Q[0][1] = D.x;
	//Q[0][2] = D.y;
	//Q[0][3] = D.z;
	//
	//Q[1][0] = D.x;
	//Q[1][1] = T.At(0, 0);
	//Q[1][2] = T.At(0, 1);
	//Q[1][3] = T.At(0, 2);
	//
	//Q[2][0] = D.y;
	//Q[2][1] = T.At(1, 0);
	//Q[2][2] = T.At(1, 1);
	//Q[2][3] = T.At(1, 2);
	//
	//Q[3][0] = D.z;
	//Q[3][1] = T.At(2, 0);
	//Q[3][2] = T.At(2, 1);
	//Q[3][3] = T.At(2, 2);
	//
	////#########################################################//
	////#### Step3.1 � Largest Eigenvalue & Eigenvector       ####//
	////#########################################################//
	//double Eigenvalue[4];
	//double Eigenvector[4][4];
	//CPoint3d q;
	//
	//Jacobi(Q, Eigenvector, Eigenvalue);
	//
	//
	////####�
	//double max = Eigenvalue[0];
	//int max_EigenValue = 0;
	//for (int i = 0; i < 4; i++){
	//	if (max < Eigenvalue[i]){
	//		max = Eigenvalue[i];
	//		max_EigenValue = i;
	//	}
	//}
	//q.x = Eigenvector[0][max_EigenValue];  //quaternion
	//q.y = Eigenvector[1][max_EigenValue];
	//q.z = Eigenvector[2][max_EigenValue];
	//q.w = Eigenvector[3][max_EigenValue];
	//
	////#########################################################//
	////               Step4 Rotation matrix                     //
	//// E. Unit Quaternion and Rotation Berthold K.P.horn paper //
	////#########################################################//
	//CMatrix Tr(4, 4);
	//Tr.SetZero();
	//
	//Tr.At(0, 0) = q.x*q.x + q.y*q.y - q.z*q.z - q.w*q.w;
	//Tr.At(0, 1) = 2 * (q.y*q.z - q.x*q.w);
	//Tr.At(0, 2) = 2 * (q.y*q.w + q.x*q.z);
	//
	//Tr.At(1, 0) = 2 * (q.y*q.z + q.x*q.w);
	//Tr.At(1, 1) = q.x*q.x + q.z*q.z - q.y*q.y - q.w*q.w;
	//Tr.At(1, 2) = 2 * (q.z*q.w - q.x*q.y);
	//
	//Tr.At(2, 0) = 2 * (q.y*q.w - q.x*q.z);
	//Tr.At(2, 1) = 2 * (q.z*q.w + q.x*q.y);
	//Tr.At(2, 2) = q.x*q.x + q.w*q.w - q.y*q.y - q.z*q.z;
	//
	//for (int i = 0; i < 3; i++){
	//	for (int j = 0; j < 3; j++){
	//		Rt(i, j) = Tr(i, j);
	//	}
	//}
	//
	//cout << "Rotation matrix  " << endl;
	////for (int i = 0; i < 3; i++){
	////	for (int j = 0; j < 3; j++){
	////		cout << setw(8) << Rt(i, j) << " ";
	////	}
	////	cout << endl;
	////}cout << endl;
	//
	//


//}