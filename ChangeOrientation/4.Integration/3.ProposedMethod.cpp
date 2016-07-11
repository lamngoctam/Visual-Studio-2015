#include "../stdafx.h"


extern int ImageNum;
extern CMatrix ICPMatrix;

extern CVector3d* CameraPosUp;
extern CVector3d* CameraPosDown;

extern CVector3d Min;			//�ŏ��̔��ŏ��ix,y,z�j
extern CVector3d Max;		//�ŏ��̔��ő�ix,y,z�j

extern double MinVoxelL;			//new UP & DOWN���f���ŏ��{�N�Z���̒�ʂ̈��
extern double MinVoxelH;			//new UP & DOWN���f���ŏ��{�N�Z���̍���

extern double thresh;

//�a�W��
void Unio(Model& integ);

//�ϏW��
void Intersection(Model& integ);

void FindOutsideVoxel(Model& m);
void CalculateDistance(Model& m);
void CalculateNormal(Model& m);

void ElimIsoVoxels_LUT(Model& m);
void ElimIsoVoxels(Model& m);

void DeleteCuboids(Model& integ, int& delnum, int& delsum)
{
	delnum = 0;	//���[�v���ɏ�����
	for (int x(1); x < integ.num[0] - 1; x++)
	{
		for (int y(1); y < integ.num[1] - 1; y++)
		{
			for (int z(1); z < integ.num[2] - 1; z++)
			{
				//�\�ʃ{�N�Z���ł���ꍇ
				if (integ.Voxels[x][y][z].surf)
				{
					//P����̂݉��AP�ɑ����Ȃ�
					if (integ.Flags[x][y][z].upCan == true &&
						integ.Flags[x][y][z].downCan == false &&
						integ.Flags[x][y][z].up == false)
					{
						//�{�N�Z�����폜
						integ.Voxels[x][y][z].fill = false;
						integ.Voxels[x][y][z].surf = false;
						integ.FillVoxelNum--;
						integ.SurfNum--;
						delnum++;	//�P��̃��[�v�ō폜�����{�N�Z���̐����J�E���g
						delsum++;	//�폜�����{�N�Z���̍��v�����J�E���g
					}

					//Q����̂݉��AQ�ɑ����Ȃ�
					else if (integ.Flags[x][y][z].upCan == false &&
						integ.Flags[x][y][z].downCan == true &&
						integ.Flags[x][y][z].down == false)
					{
						//�{�N�Z�����폜
						integ.Voxels[x][y][z].fill = false;
						integ.Voxels[x][y][z].surf = false;
						integ.FillVoxelNum--;
						integ.SurfNum--;
						delnum++;	//�P��̃��[�v�ō폜�����{�N�Z���̐����J�E���g
						delsum++;	//�폜�����{�N�Z���̍��v�����J�E���g
					}
				}
			}
		}
	}
}



//(2014/5/20)
void CanSee(Model& integ, int x, int y, int z, CVector3d& CameraPos, string pose)
{
	double temp(0.0);								//(3.40)
	CVector3d Camera(0.0, 0.0, 0.0);

	int xi(0);	//
	int yi(0);	//
	int zi(0);	//

	int parti;
	CVector3d cent(0.0, 0.0, 0.0);
	CVector3d line(0.0, 0.0, 0.0);
	                                                                                                                    
	//                             
	//                                                                                                                    
	cent = integ.Voxels[x][y][z].center;
	Camera = CameraPos - cent;
	Camera = Camera.Normalize();
	temp = (integ.Voxels[x][y][z].normal).Dot(Camera);	//(3.40)

	//double threshdown(cos(30 / 180.0*M_PI));
	double threshdown(cos(40/180.0*M_PI));

	if (pose == "UP")
		integ.Flags[x][y][z].upCan = false;
	else
		integ.Flags[x][y][z].downCan = false;


	//
	if (temp > thresh && threshdown > temp)
	{
		//
		if (pose == "UP")			//pose == true(UP)
		{
			integ.Flags[x][y][z].upCan = true;
		}
		else if (pose == "DOWN")		//pose == false(DOWN)
		{
			integ.Flags[x][y][z].downCan = true;
		}
		//cout<<endl;

		for (int t(0); t < 100; t++)    //100�2014/05/20�j
		{
			//
			line = line + Camera;

			xi = x + int(line.x);		//
			yi = y + int(line.y);		//
			zi = z + int(line.z);		//

			//
			if (xi != x || yi != y || zi != z)
				if (-1 < xi && xi < integ.num[0] && -1 < yi && yi < integ.num[1] && -1 < zi && zi < integ.num[2])
				{
					if (integ.Voxels[xi][yi][zi].fill)
					{
						if (pose == "UP")
						{
							integ.Flags[x][y][z].upCan = false;
						}
						else if (pose == "DOWN")
						{
							integ.Flags[x][y][z].downCan = false;
						}
						break;
					}
				}


		}
	}

}

//
void Visibility(Model& integ, string pose, CVector3d* CameraPos)
{
	int x, y, z, i;
	//                                                         
	//                                     
	//                                                         
	for (x = 1; x < integ.num[0] - 1; x++)
	{
		for (y = 1; y < integ.num[1] - 1; y++)
		{
			for (z = 1; z < integ.num[2] - 1; z++)
			{
				if (integ.Voxels[x][y][z].surf)
				{
					//                                                 
					//                                                 
					for (i = 0; i < ImageNum; i++)
					{
						CanSee(integ, x, y, z, CameraPos[i], pose);

						if (pose == "UP")		//pose == true(UP)
						{
							if (integ.Flags[x][y][z].upCan) { break; }
						}
						else if (pose == "DOWN")	//pose == false(DOWN)
						{
							if (integ.Flags[x][y][z].downCan) { break; }
						}
					}
				}
			}
		}
	}
}

void CalcDownCamaraPos()
{
	//downcamera
	CameraPosDown = new CVector3d[ImageNum];
	CVector NewQCP(4, 1.0);	//new qmodel camera points�S�s�P��
	CVector OldQCP(4, 1.0);	//old qmodel camera points�S�s�P��
	for (int i(0); i < ImageNum; i++) {

		OldQCP[0] = CameraPosUp[i].x;
		OldQCP[1] = CameraPosUp[i].y;
		OldQCP[2] = CameraPosUp[i].z;
		OldQCP[3] = 1.0;

		NewQCP = ICPMatrix * OldQCP;


		CameraPosDown[i].x = NewQCP[0];
		CameraPosDown[i].y = NewQCP[1];
		CameraPosDown[i].z = NewQCP[2];
	}

}



void ProposedMethod(Model& integ)
{
	int loopnum(0);
	int delnum(0);
	int delsum(0);

	//                                          
	//                                   
	//                                          
//	Unio(integ);

	Intersection(integ);

	//                                          
	//                   
	//                                          
	do {
		loopnum++;

		FindOutsideVoxel(integ);


		CalculateDistance(integ);


		CalculateNormal(integ);


		Visibility(integ, "UP", CameraPosUp);
		Visibility(integ, "DOWN", CameraPosDown);

		//                                                         
		//                                        
		//                                                         
		DeleteCuboids(integ, delnum, delsum);

		cout << "loopnum " << loopnum << " DelNum " << delnum << endl;
		//                                                                         
		//                      
		//                                                                         
		for (int x(0); x < integ.num[0]; x++)
		{
			for (int y(0); y < integ.num[1]; y++)
			{
				for (int z(0); z < integ.num[2]; z++)
				{
					integ.Voxels[x][y][z].ClearDist();
				}
			}
		}

	} while (delnum != 0);

	cout << "delete sum " << delsum << " finish " << endl;

}


