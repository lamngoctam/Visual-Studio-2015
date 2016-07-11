#include "stdafx.h"		
#include <iterator>    
using namespace std;

void heap_sort_dbl(double*ar,int*x_ar,int Nmt );


//Calculate distance
void DISTANCE_CALC(Voxel &VoxSpace, vector<double> &TimeList, vector<VoxCoord>&coord, int ox, int oy, int oz, int nx, int ny, int nz)
	//, int  p_cnt, double nt)//ox:old x    nx:new x
{
	VoxCoord VC;//box p 
	if((VoxSpace.Grid3D[ox][oy][oz].Edge !=1) || ((0<=nx ) && (nx<VoxSpace.ND[0])) &&  ((0<=ny) && (ny<VoxSpace.ND[1])) && ((0<=nz) && (nz<VoxSpace.ND[2])))    //P[i][j]が存在しないことを防ぐ
	{
		if(VoxSpace.Grid3D[nx][ny][nz].Status==2)
		{
			VoxSpace.Grid3D[nx][ny][nz].Status=1;
			VC.Coord[0]=nx;
			VC.Coord[1]=ny;
			VC.Coord[2]=nz;
			coord.push_back(VC);

			double dt0=0.0, dt1=0.0, dt2=0.0;
			//int tfact;//Tnewの係数

			//・ikonal・F=1・ｂｭ
			//VoxSpace.Grid3D[nx][ny][nz]・
			//dt2*x^2+dt1*x+dt0-1/F=0
			if((0<=nx-1) && VoxSpace.Grid3D[nx-1][ny][nz].Status != 2) 
			{
				dt0  += VoxSpace.Grid3D[nx-1][ny][nz].Dist*VoxSpace.Grid3D[nx-1][ny][nz].Dist;
				dt1  += -2*VoxSpace.Grid3D[nx-1][ny][nz].Dist;
				dt2  += 1.0;
			}
			if((0<=ny-1) && VoxSpace.Grid3D[nx][ny-1][nz].Status != 2)
			{
				dt0  += VoxSpace.Grid3D[nx][ny-1][nz].Dist*VoxSpace.Grid3D[nx][ny-1][nz].Dist;
				dt1  += -2*VoxSpace.Grid3D[nx][ny-1][nz].Dist;
				dt2  += 1.0;
			}
			if((0<=nz-1) &&  VoxSpace.Grid3D[nx][ny][nz-1].Status != 2)
			{
				dt0  += VoxSpace.Grid3D[nx][ny][nz-1].Dist*VoxSpace.Grid3D[nx][ny][nz-1].Dist;
				dt1  += -2*VoxSpace.Grid3D[nx][ny][nz-1].Dist;
				dt2  += 1.0;
			}

			if((nx+1<VoxSpace.ND[0]) &&  VoxSpace.Grid3D[nx+1][ny][nz].Status != 2)
			{
				dt0  += VoxSpace.Grid3D[nx+1][ny][nz].Dist*VoxSpace.Grid3D[nx+1][ny][nz].Dist;
				dt1  += -2*VoxSpace.Grid3D[nx+1][ny][nz].Dist;
				dt2  += 1.0;
			}
			if((ny+1<VoxSpace.ND[1]) &&  VoxSpace.Grid3D[nx][ny+1][nz].Status != 2)
			{
				dt0  += VoxSpace.Grid3D[nx][ny+1][nz].Dist*VoxSpace.Grid3D[nx][ny+1][nz].Dist;
				dt1  += -2*VoxSpace.Grid3D[nx][ny+1][nz].Dist;
				dt2  += 1.0;
			}
			if((nz+1<VoxSpace.ND[2]) && VoxSpace.Grid3D[nx][ny][nz+1].Status != 2)
			{
				dt0  += VoxSpace.Grid3D[nx][ny][nz+1].Dist*VoxSpace.Grid3D[nx][ny][nz+1].Dist;
				dt1  += -2*VoxSpace.Grid3D[nx][ny][nz+1].Dist;
				dt2  += 1.0;
			}

			dt0 += -1.0;//(1 / f) transposition // this is f = 1;

			double b2m4ac=dt1*dt1-4.0*dt0*dt2;//b^2 minus 4ac　　Must be a positive thing because in the root b ^ 2-4ac
			if((b2m4ac)>0.0)
				VoxSpace.Grid3D[nx][ny][nz].Dist = (-dt1+sqrt(dt1*dt1-4.0*dt2*dt0))/(2*dt2);
			else if((b2m4ac)==0.0)	
				VoxSpace.Grid3D[nx][ny][nz].Dist = (-dt1+sqrt(dt1*dt1-4.0*dt2*dt0))/(2*dt2);
			else//Once I think maybe not
				VoxSpace.Grid3D[nx][ny][nz].Dist = VoxSpace.Grid3D[ox][oy][oz].Dist+1;

			TimeList.push_back(VoxSpace.Grid3D[nx][ny][nz].Dist);//
		}
	}
}


//Set the distance field
void SetDistField(Voxel &VoxSpace)
{
	//-------------------------   Distance Field    ------------------------------------
	//int i,j,k;
	int Ntrial;//, Ntrial1;  //trial
	int Nmt=-1;             //trial・
	vector<int> Num,Num1;				//蒐um={0,1,2,3,・・・・・999}
	vector<double> DistList, DistList1;	//
	vector<VoxCoord> coord,coord1;		//・

	//reserve
	int NRes=(int)(0.1*VoxSpace.ND[0]*VoxSpace.ND[1]*VoxSpace.ND[2]); //total voxel * 0.1
	coord.reserve(NRes);
	coord1.reserve(NRes);
	Num.reserve(NRes);
	Num1.reserve(NRes);
	DistList.reserve(NRes);
	DistList1.reserve(NRes);

	//
	DistList.push_back(0);
	vector<double>::iterator itTimeList = DistList.begin();  
	double* pTimeList = &*itTimeList;  
	DistList.clear();

	Num.push_back(0);
	vector<int>::iterator itNum = Num.begin(); 
	int* pNum = &*itNum;  
	Num.clear();

	VoxCoord VC;//box p

	for(int i=0; i<VoxSpace.ND[0]; i++)
	{
		for(int j=0; j<VoxSpace.ND[1]; j++)
		{
			for(int k=0; k<VoxSpace.ND[2]; k++)
			{     		
				if(VoxSpace.Grid3D[i][j][k].Surf)		//
				{
					VoxSpace.Grid3D[i][j][k].Dist=0.0;	//
					VoxSpace.Grid3D[i][j][k].Status=1;	//??
					DistList.push_back(0.0);		//距用ush_back
					VC.Coord[0]=i;
					VC.Coord[1]=j;			
					VC.Coord[2]=k;
					coord.push_back(VC);			//push_back
				}
				else								//・
				{
					VoxSpace.Grid3D[i][j][k].Dist=DBL_MAX;	
					VoxSpace.Grid3D[i][j][k].Status=2;		
				}
			}
		}	
	}

	double tmin;	//Tp(=T^2)
	double tmax;	//Tp
	int Ntmin;		//Tp
	int temp;		//
	int p_cnt=0;	//のloopか？
	int ii,jj,kk;
	while(1)
	{
		Ntrial =(int)coord.size();
		for(int i=0; i<Ntrial; i++)				//順 Num={0,1,2,3,・・・・・999}
			Num.push_back(i);

		//heap sort
		if(p_cnt != 0 && (Ntrial-1>0))
			heap_sort_dbl(pTimeList,pNum,Ntrial-1);


		//release memory
		DistList1.clear();
		coord1.clear();
		Num1.clear();

		copy(coord.begin(),coord.end(), back_inserter(coord1));
		copy(Num.begin(),Num.end(), back_inserter(Num1));
		copy(DistList.begin(),DistList.end(), back_inserter(DistList1));

		coord.clear();
		Num.clear();
		DistList.clear();

		tmin=DistList1[0];  //
		tmax=DistList1[Ntrial-1];
		Ntmin=0;      //heap sort・

		for(int  i=0; i<Ntrial; i++)//heap sort・
		{              
			if(DistList1[i]<=(tmin+0.05))//
				Ntmin++;
			else
				break;
		}

		//cout <<(int)DistList.size()<<endl;
		for(int p=0; p<Ntmin; p++)
		{
			temp=Num1[p];
			ii=coord1[temp].Coord[0];
			jj=coord1[temp].Coord[1];			
			kk=coord1[temp].Coord[2];
			//if(i==VoxSpace.ND[0]-1 && j==VoxSpace.ND[1]-1 && k==VoxSpace.ND[2]-1)
			//	cout<<"*";
			if(VoxSpace.Grid3D[ii+1][jj][kk].Fill)
			DISTANCE_CALC(VoxSpace,DistList,coord,ii,jj,kk,ii+1,jj,kk);				
			if(VoxSpace.Grid3D[ii-1][jj][kk].Fill)
			DISTANCE_CALC(VoxSpace,DistList,coord,ii,jj,kk,ii-1,jj,kk);		
			if(VoxSpace.Grid3D[ii][jj+1][kk].Fill)
			DISTANCE_CALC(VoxSpace,DistList,coord,ii,jj,kk,ii,jj+1,kk);		
			if(VoxSpace.Grid3D[ii][jj-1][kk].Fill)
			DISTANCE_CALC(VoxSpace,DistList,coord,ii,jj,kk,ii,jj-1,kk);		
			if(VoxSpace.Grid3D[ii][jj][kk+1].Fill)
			DISTANCE_CALC(VoxSpace,DistList,coord,ii,jj,kk,ii,jj,kk+1);		
			if(VoxSpace.Grid3D[ii][jj][kk-1].Fill)
			DISTANCE_CALC(VoxSpace,DistList,coord,ii,jj,kk,ii,jj,kk-1);	

			VoxSpace.Grid3D[ii][jj][kk].Status=0;
		}

		for(int i=Ntmin; i<Ntrial; i++)//ここＵria５pが、heap sort・
		{              
			
			temp=Num1[i];
			VC.Coord[0]=coord1[temp].Coord[0];
			VC.Coord[1]=coord1[temp].Coord[1];			
			VC.Coord[2]=coord1[temp].Coord[2];
			coord.push_back(VC);
			DistList.push_back(DistList1[i]);
		}

		Ntrial=(int)DistList.size();

		if((Ntrial==0 )/*|| (tmin>3.0)*/)
			break;

		p_cnt++;
	}

	//To determine the processing area
	for(int i=0; i<VoxSpace.ND[0]; i++)
	{
		for(int j=0; j<VoxSpace.ND[1]; j++)
		{
			for(int k=0; k<VoxSpace.ND[2]; k++)
			{    
				if(VoxSpace.Grid3D[i][j][k].Fill ){
					VoxSpace.Grid3D[i][j][k].Dist = VoxSpace.Grid3D[i][j][k].Dist*VoxSpace.Length;
					//VoxSpace.Grid3D[i][j][k].dist[number-1]=VoxSpace.Grid3D[i][j][k].Dist;
				}
				else
					VoxSpace.Grid3D[i][j][k].Dist = -VoxSpace.Grid3D[i][j][k].Dist*VoxSpace.Length;
			}
		}
	}

	cout<<"FMM_EXPAND LOOP  "<<p_cnt<<endl;

}



void CalcVoxNormal(Voxel &VoxSpace)
{
	clock_t start, end;
	start = clock();

		SetDistField(VoxSpace);
	

	end = clock();
	std::printf("time to calculate distance field: %.2f \n",(double)(end-start)/CLOCKS_PER_SEC);


}
