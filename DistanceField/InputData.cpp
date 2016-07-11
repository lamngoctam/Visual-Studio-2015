#include "stdafx.h"		//色んなインクルードをまとめた
using namespace std;

void InputData(string &FileName, Voxel &VoxSpace)
{	
	string sline;			//一時読み取り用
	istringstream ssline;

	ifstream file1(FileName.c_str());
	if (!file1){
		cout <<FileName<<"is not found!"<< endl;	//ファイルが無い等
		exit (0);
	}

	int ii,jj,kk;		

	
	getline( file1, sline );
	ssline.str( sline );		
	ssline >> ii  >> jj >> kk >> VoxSpace.Length;	//284  285   164  0.546875 <- length of voxel
	ssline.clear();				

	// create more outside voxel = boundary
	VoxSpace.ND[0] = ii+2;
	VoxSpace.ND[1] = jj+2;
	VoxSpace.ND[2] = kk+2;

	//coordinate of voxel
	getline( file1, sline );	
	ssline.str( sline );		
	ssline >> VoxSpace.OriPt.x >> VoxSpace.OriPt.y >> VoxSpace.OriPt.z;	//-0.546875  -0.546875   -100.687
	ssline.clear();				


	//VoxSpace.OriPt.x = VoxSpace.OriPt.x-5.0*VoxSpace.Length;
	//VoxSpace.OriPt.y = VoxSpace.OriPt.y-5.0*VoxSpace.Length;
	//VoxSpace.OriPt.z = VoxSpace.OriPt.z-5.0*VoxSpace.Length;

	//3d
	VoxSpace.Grid3D = new Box **[VoxSpace.ND[0]];
	for(int i=0; i<VoxSpace.ND[0]; i++){
		VoxSpace.Grid3D[i] = new Box *[VoxSpace.ND[1]];
		for(int j=0; j<VoxSpace.ND[1]; j++){
			VoxSpace.Grid3D[i][j] = new Box[VoxSpace.ND[2]];
		}
	}


	//Fill or empty
	while(!file1.eof())
	{
		getline( file1, sline );
		ssline.str( sline );		
		ssline >> ii >>jj>>kk;
		ssline.clear();				
		VoxSpace.Grid3D[ii+1][jj+1][kk+1].Fill=true;
		VoxSpace.Grid3D[ii+1][jj+1][kk+1].surf=true;
	}
	file1.close();
	cout<<FileName<<" input file"<<endl;
	cout<<"Total of voxel: "<<VoxSpace.ND[0]<<"*"<<VoxSpace.ND[1]<<"*"<<VoxSpace.ND[2]<<"="<<VoxSpace.ND[0]*VoxSpace.ND[1]*VoxSpace.ND[2]<<endl;
}

void Voxel::Fillcontent(){
	
	//------------------------------------------Preparation----------------------------------------------------//
	for(int i=0 ; i <ND[0]; i++){
		for(int j=0 ; j <ND[1]; j++){
			for(int k=0 ; k <ND[2]; k++){
				Grid3D[i][j][k].num=0;
				if(Grid3D[i][j][k].Fill)
					Grid3D[i][j][k].Surf=true;    // Surface voxel
				//End another treatment is necessary
				if(i==0||j==0||k==0||i==ND[0]-1||j==ND[1]-1||k==ND[2]-1){
					Grid3D[i][j][k].Edge=true;	
						Grid3D[i][j][k].Fill=false;
					if(Grid3D[i][j][k].Surf)
						Grid3D[i][j][k].Fill=true;

				}
				else{
				
				Grid3D[i][j][k].Fill=true;//To all to Fill
				}
			}
		}
	}
	//The operation of the end here
		for(int i=0 ; i <ND[0]; i++){
			for(int j=0 ; j <ND[1]; j++){
				if(!Grid3D[i][j][0].Surf){
					if(!Grid3D[i][j][1].Surf)
					Grid3D[i][j][1].Fill=false;
					Grid3D[i][j][1].num=2;
				}
				if(!Grid3D[i][j][ND[2]-1].Surf){
					if(!Grid3D[i][j][ND[2]-2].Surf)
					Grid3D[i][j][ND[2]-2].Fill=false;
					Grid3D[i][j][ND[2]-2].num=2;
				}
			}
		}
		for(int i=0 ; i <ND[0]; i++){
			for(int k=0 ; k <ND[2]; k++){
				if(!Grid3D[i][0][k].Surf){
				if(!Grid3D[i][1][k].Surf)
					Grid3D[i][1][k].Fill=false;
					Grid3D[i][1][k].num=2;
				}
				if(!Grid3D[i][ND[1]-1][k].Surf){
					if(!Grid3D[i][ND[1]-2][k].Surf)
					Grid3D[i][ND[1]-2][k].Fill=false;
					Grid3D[i][ND[1]-2][k].num=2;
				}
			}
		}
		for(int k=0 ; k <ND[2]; k++){
			for(int j=0 ; j <ND[1]; j++){
				if(!Grid3D[0][j][k].Surf){
				if(!Grid3D[1][j][k].Surf)
					Grid3D[1][j][k].Fill=false;
					Grid3D[1][j][k].num=2;
				}
				if(!Grid3D[ND[0]-1][j][k].Surf){
				if(!Grid3D[ND[0]-2][j][k].Surf)					
					Grid3D[ND[0]-2][j][k].Fill=false;
					Grid3D[ND[0]-2][j][k].num=2;
				}
			}
		}
	//------------------------------------------Preparation up to this point--------------------------------------------------//

	//Fill the contents
	int count=2;//Number of repetitions
	while(count<ND[0]){
	for(int i=1 ; i <ND[0]-1; i++){
		for(int j=1 ; j <ND[1]-1; j++){
			for(int k=1 ; k <ND[2]-1; k++){
				if(Grid3D[i][j][k].Surf)continue;
				if(Grid3D[i][j][k].num==count){

				//6 neighborhood survey
				if(Grid3D[i+1][j][k].num==0)//When the sum is 0
				{
					if(!Grid3D[i+1][j][k].Surf){
					Grid3D[i+1][j][k].Fill=false;
					Grid3D[i+1][j][k].num=count+1;
					}
				}
				if(Grid3D[i-1][j][k].num==0)//When the sum is 0
				{
					if(!Grid3D[i-1][j][k].Surf){
					Grid3D[i-1][j][k].Fill=false;
					Grid3D[i-1][j][k].num=count+1;
					}
				}
				if(Grid3D[i][j-1][k].num==0)//When the sum is 0
				{
					if(!Grid3D[i][j-1][k].Surf){
					Grid3D[i][j-1][k].Fill=false;
					Grid3D[i][j-1][k].num=count+1;
					}
				}
				if(Grid3D[i][j+1][k].num==0)//When the sum is 0
				{
					if(!Grid3D[i][j+1][k].Surf){
					Grid3D[i][j+1][k].Fill=false;
					Grid3D[i][j+1][k].num=count+1;
					}
				}
				if(Grid3D[i][j][k+1].num==0)//When the sum is 0
				{
					if(!Grid3D[i][j][k+1].Surf){
					Grid3D[i][j][k+1].Fill=false;
					Grid3D[i][j][k+1].num=count+1;
					}
				}
				if(Grid3D[i][j][k-1].num==0)//When the sum is 0
				{
					if(!Grid3D[i][j][k-1].Surf){
					Grid3D[i][j][k-1].Fill=false;
					Grid3D[i][j][k-1].num=count+1;
					}
				}
				}
			}
		}
	}	
	count++;
	cout<<"The number of repetitions"<<count<<"It is time"<<'\r';
	}
	cout<<endl;

	//To remove the off voxel (I do not need need kana? 5 times)
	int tt=0;
	while(tt<5){
	for(int i=1 ; i <ND[0]-1; i++){
		for(int j=1 ; j <ND[1]-1; j++){
			for(int k=1 ; k <ND[2]-1; k++){
				if(!Grid3D[i][j][k].Fill)continue;
				if(!Grid3D[i-1][j][k].Fill&&!Grid3D[i][j-1][k].Fill&&
						!Grid3D[i][j+1][k].Fill&&!Grid3D[i+1][j][k].Fill&&
						!Grid3D[i][j][k+1].Fill&&!Grid3D[i][j][k-1].Fill){
							Grid3D[i][j][k].Fill=false;
				}
			}
		}
	}
	tt++;
	}
}

//Find the surface voxel of model
void FindOutsideVoxel1(Voxel &m)
{
	int x,y,z;
	m.SurfNum = 0;
	for(x=1; x<m.ND[0]-1; ++x)				
	{
		for(y=1; y<m.ND[1]-1; ++y)			
		{
			for(z=1; z< m.ND[2]-1; ++z)		
			{				
				if(m.Grid3D[x][y][z].Fill)
				{
					//上(z + 1) up
					if(m.Grid3D[x][y][z+1].Fill == false)
					{
						m.Grid3D[x][y][z].Surf = true;
						m.SurfNum++;

						continue;
					}
					//下(z - 1) down
					if(m.Grid3D[x][y][z-1].Fill == false)
					{
						m.Grid3D[x][y][z].Surf = true;
						m.SurfNum++;
						
						continue;
					}
					//前(x + 1)before
					if(m.Grid3D[x+1][y][z].Fill == false)
					{
						m.Grid3D[x][y][z].Surf = true;
						m.SurfNum++;
						continue;
					}
					//後(x - 1) rear
					if(m.Grid3D[x-1][y][z].Fill == false)
					{
						m.Grid3D[x][y][z].Surf = true;
						m.SurfNum++;
						continue;
					}
					//左(y + 1) left
					if(m.Grid3D[x][y+1][z].Fill == false)
					{		
						m.Grid3D[x][y][z].Surf = true;
						m.SurfNum++;
						continue;
					}
					//右(y - 1) right
					if(m.Grid3D[x][y-1][z].Fill == false)
					{
						m.Grid3D[x][y][z].Surf = true;
						m.SurfNum++;
					}
				}
			}
		}
	}
}