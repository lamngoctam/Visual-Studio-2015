//principal axis

#include "../stdafx.h"

using namespace std;

void FindVoxSurf(Model& m)
{
	for (int i = 0; i < m.num[0]; i++){
		for (int j = 0; j < m.num[1]; j++){
			for (int k = 0; k < m.num[2]; k++){
				if (m.Voxels[i][j][k].fill == false) continue;

				//—§–@‘Ì‚Ì6–Ê‚É‘Î‚µ‚Ä”»’è
				if (1 <= k && m.Voxels[i][j][k - 1].fill == false)
					m.Voxels[i][j][k].surf = true;
				else if (1 <= j && m.Voxels[i][j - 1][k].fill == false)
					m.Voxels[i][j][k].surf = true;
				else if (i < m.num[0] - 1 && m.Voxels[i + 1][j][k].fill == false)
					m.Voxels[i][j][k].surf = true;
				else if (j < m.num[1] - 1 && m.Voxels[i][j + 1][k].fill == false)
					m.Voxels[i][j][k].surf = true;
				else if (1 <= i && m.Voxels[i - 1][j][k].fill == false)
					m.Voxels[i][j][k].surf = true;
				else if (k < m.num[2] - 1 && m.Voxels[i][j][k + 1].fill == false)
					m.Voxels[i][j][k].surf = true;
			}
		}
	}
	int surfcnt = 0;//•\–Êƒ{ƒNƒZƒ‹‚Ì”
	for (int i = 0; i < m.num[0]; i++){
		for (int j = 0; j < m.num[1]; j++){
			for (int k = 0; k < m.num[2]; k++){
				if (m.Voxels[i][j][k].surf)
					surfcnt++;
			}
		}
	}
	m.SurfNum = surfcnt;
}

//eigne value&vector‚ V:Eigen vector d:Eigne value
void eigen_decomposition(int n, long double **A, long double **V, long double *d);

//principal axis
void CalcPA(Model& m)
{
	//
	CVector3d CenterCo(0.0, 0.0, 0.0);//initialize
	int cnt = 0;
	for (int i(0); i < m.SurfVoxels.size(); i++){
		//if(!m.Voxels[i][j][k].fill) continue;
		CenterCo += m.SurfVoxels[i].center;
		cnt++;
	}
	cout << "\nCentroid point: (" << CenterCo.x << ", " << CenterCo.y << ", " << CenterCo.z <<")\n";
	cout << m.SurfVoxels.size();
	cout << "\nNumber of surface voxel: " << cnt << endl;
	cout << "\nNumber of surface voxel: " << m.SurfNum << endl;

	//
	m.CoV = (1.0 / (double)cnt)*CenterCo;

	CMatrix Covmat(3, 3);//covariance matrix
	Covmat.SetZero();

	CMatrix POvec(3, 1), POT(1, 3);//P-O
	CMatrix Tempvec(3, 1);

	//#################################################
	//	First principal axis
	//#################################################

	for (int i(0); i < m.SurfVoxels.size(); i++){

		POvec.At(0, 0) = m.SurfVoxels[i].center.x - m.CoV.x;
		POvec.At(1, 0) = m.SurfVoxels[i].center.y - m.CoV.y;
		POvec.At(2, 0) = m.SurfVoxels[i].center.z - m.CoV.z;
		Tempvec = POvec;
		POT = Tempvec.Transpose();

		Covmat += POvec * POT;

	}

	cout << "\nCovariance matrix: [" << Covmat.At(0, 0) << " - " << Covmat.At(1, 0) << " - " << Covmat.At(2, 0) << "]"<<endl;


	long double **AA;//input vector
	AA = new long double *[3];
	for (int i = 0; i < 3; i++)
		AA[i] = new long double[3];
	    for (int i = 0; i < 3; i++){
		    for (int j = 0; j < 3; j++){
			    AA[i][j] = (long double)Covmat.At(i, j);  // i:row,j:col_matrix
		}
	}

	long double **VV;//eigne vector
	VV = new long double *[3];
	for (int i = 0; i < 3; i++)
		VV[i] = new long double[3];

	long double *dd;//eigen value
	dd = new long double[3];


	// output VV:eigenvector & dd:eigenvalue
	eigen_decomposition(3, AA, VV, dd);


	//Find Largest eigenvalue 
	int largesteigenID;
	long double temp = 0.0;
	for (int i = 0; i < 3; i++){
		if (temp < dd[i]){
			temp = dd[i];
			largesteigenID = i;
		}
	}
	for (int i = 0; i < 3; i++){
		m.PrAxix[0].x = (double)VV[0][largesteigenID];
		m.PrAxix[0].y = (double)VV[1][largesteigenID];
		m.PrAxix[0].z = (double)VV[2][largesteigenID];
	}

	m.PrAxix[0].Normalize(); //Normalize

	cout << "\nFirst principal axis with first eigen vector :"<<endl;
	cout << m.PrAxix[0].x << " " << m.PrAxix[0].y << " " << m.PrAxix[0].z << endl;

	//#################################################
	//	Second principal axis
	//#################################################
	Covmat.SetZero();
	CVector3d OnPlane;

	//Equation of Plane A*x+B*y+C*z+D=0 -> D= -(Ax+By+Cz)
	double D = -m.PrAxix[0].Dot(m.CoV); 
	double Dist; // distance from Point to plane
	for (int i(0); i < m.SurfVoxels.size(); i++){

		Dist = D + m.PrAxix[0].Dot(m.SurfVoxels[i].center) / (1); // project point to plane
		 // (A^2*B^2*C^2)^(1/2) = 1 because m.PrAxix[0].Normalize(); //Normalize at 1st PC	
		
		OnPlane = m.SurfVoxels[i].center - Dist * m.PrAxix[0];

		POvec.At(0, 0) = OnPlane.x - m.CoV.x;
		POvec.At(1, 0) = OnPlane.y - m.CoV.y;
		POvec.At(2, 0) = OnPlane.z - m.CoV.z;

		Tempvec = POvec;
		POT = Tempvec.Transpose();

		Covmat += POvec * POT;

	}

	//“ü‚ê•¨‚ÌˆÚ‚µ‘Ö‚¦
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			AA[i][j] = (long double)Covmat.At(i, j);
		}
	}

	//
	eigen_decomposition(3, AA, VV, dd);

	//
	temp = 0.0;
	for (int i = 0; i < 3; i++){
		if (temp < dd[i]){
			temp = dd[i];
			largesteigenID = i;
		}
	}
	for (int i = 0; i < 3; i++){
		m.PrAxix[1].x = (double)VV[0][largesteigenID];
		m.PrAxix[1].y = (double)VV[1][largesteigenID];
		m.PrAxix[1].z = (double)VV[2][largesteigenID];
	}
	m.PrAxix[1].Normalize();//
	cout << "\nSecond principal axis with second eigen vector "<<endl;
	cout << m.PrAxix[1].x << " " << m.PrAxix[1].y << " " << m.PrAxix[1].z << endl;


	//#################################################
	//	Third principal axis
	//#################################################
	m.PrAxix[2] = m.PrAxix[0].Cross(m.PrAxix[1]);
	m.PrAxix[2].Normalize();//
	cout << "\nThird principal axis with third eigen vector "<<endl ;
	cout << m.PrAxix[2].x << " " << m.PrAxix[2].y << " " << m.PrAxix[2].z << endl;
}
