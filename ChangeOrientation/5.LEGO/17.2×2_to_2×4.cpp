#include "../stdafx.h"
#include "../Voxel.h"
#include "../Lego.h"		//LEGO�u���b�N��g�ݗ��Ă邽�߂̃N���X


extern int ID12;
extern int ID22;
extern int ID24;

extern int num22;		//�Q�~�Q�̃u���b�N�̐�
extern int num24;		//�Q�~�S�̃u���b�N�̐�

void outputFlag(string filename, int* size);

//�Q�~�Q�@�ƂQ�~�Q����Q�~�S������
void Small_to_Big_step7(Lego*** block, int*  VoxSize)
{
	int x,y,z;
	//��w
	for(z=1; z < VoxSize[2]-1; z=z+2 )				//����1,3,5,...
	{
		for(x=1; x < VoxSize[0]-1; x=x+2)
		{
			for(y=1; y < VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag == 4)
				{
					//���������ɓ����Q�~�Q������΂Q�~�S�ɒu��������
					if(block[x][y+2][z].flag == 4)
					{
						ID24++;
						num22 = num22 - 2;
						num24++;
						for(int i(0); i<2; i++)
						{
							for(int k(0); k<4; k++)
							{
								block[x+i][y+k][z].flag = 24;
								block[x+i][y+k][z].ID = ID24;
							}
						}
						block[x][y][z].corner  = 1;
						block[x+1][y+3][z].corner  = 2;
						continue;
					}

					//���������ɓ����Q�~�Q������΂Q�~�S�ɒu��������
					if(block[x+2][y][z].flag == 4)
					{
						ID24++;
						num22 = num22 - 2;
						num24++;
						for(int i(0); i<4; i++)
						{				
							for(int k(0); k<2; k++)
							{	
								block[x+i][y+k][z].flag = 24;
								block[x+i][y+k][z].ID = ID24;
							}
						}
						block[x][y][z].corner  = 1;
						block[x+3][y+1][z].corner  = 2;
					}

				}
			}
		}
	}

	//�����w
	for(z=2; z < VoxSize[2]-1; z=z+2 )				//����2,4,6,...
	{	
		for(x=0; x < VoxSize[0]-1; x=x+2)
		{
			for(y=0; y < VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag == 4)
				{
					//���������ɓ����Q�~�Q������΂Q�~�S�ɒu��������
					if(block[x][y+2][z].flag == 4)
					{
						ID24++;
						num22 = num22 - 2;
						num24++;
						for(int i(0); i<2; i++)
						{
							for(int k(0); k<4; k++)
							{
								block[x+i][y+k][z].flag = 24;
								block[x+i][y+k][z].ID = ID24;
							}
						}
						block[x][y][z].corner  = 1;
						block[x+1][y+3][z].corner  = 2;
						continue;
					}

					//���������ɓ����Q�~�Q������΂Q�~�S�ɒu��������
					if(block[x+2][y][z].flag == 4)
					{
						ID24++;
						num22 = num22 - 2;
						num24++;
						for(int i(0); i<4; i++)
						{				
							for(int k(0); k<2; k++)
							{	
								block[x+i][y+k][z].flag = 24;
								block[x+i][y+k][z].ID = ID24;
							}
						}
						block[x][y][z].corner  = 1;
						block[x+3][y+1][z].corner  = 2;
					}

				}
			}
		}
	}
	outputFlag("test07_22_to_24.txt", VoxSize);

}

void Small_to_Big_step7_color(Lego*** block, int*  VoxSize)
{
	int x,y,z;
	//��w
	for(z=1; z < VoxSize[2]-1; z=z+2 )				//����1,3,5,...
	{
		for(x=1; x < VoxSize[0]-1; x=x+2)
		{
			for(y=1; y < VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag == 4)
				{
					//���������ɓ����Q�~�Q������΂Q�~�S�ɒu��������
					if(block[x][y+2][z].flag == 4)
					{
						if(block[x][y][z].ColorID == block[x][y+2][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y+2][z].ColorID < 1)
						{
							ID24++;
							num22 = num22 - 2;
							num24++;
							for(int i(0); i<2; i++)
							{
								for(int k(0); k<4; k++)
								{
									block[x+i][y+k][z].flag = 24;
									block[x+i][y+k][z].ID = ID24;
								}
							}
							block[x][y][z].corner  = 1;
							block[x+1][y+3][z].corner  = 2;
							continue;
						}
					}

					//���������ɓ����Q�~�Q������΂Q�~�S�ɒu��������
					if(block[x+2][y][z].flag == 4)
					{
						if(block[x][y][z].ColorID == block[x+2][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x+2][y][z].ColorID < 1)
						{
							ID24++;
							num22 = num22 - 2;
							num24++;
							for(int i(0); i<4; i++)
							{				
								for(int k(0); k<2; k++)
								{	
									block[x+i][y+k][z].flag = 24;
									block[x+i][y+k][z].ID = ID24;
								}
							}
							block[x][y][z].corner  = 1;
							block[x+3][y+1][z].corner  = 2;
						}
					}
				}
			}
		}
	}

	//�����w
	for(z=2; z < VoxSize[2]-1; z=z+2 )				//����2,4,6,...
	{	
		for(x=0; x < VoxSize[0]-1; x=x+2)
		{
			for(y=0; y < VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag == 4)
				{
					//���������ɓ����Q�~�Q������΂Q�~�S�ɒu��������
					if(block[x][y+2][z].flag == 4)
					{
						if(block[x][y][z].ColorID == block[x][y+2][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y+2][z].ColorID < 1)
						{
							ID24++;
							num22 = num22 - 2;
							num24++;
							for(int i(0); i<2; i++)
							{
								for(int k(0); k<4; k++)
								{
									block[x+i][y+k][z].flag = 24;
									block[x+i][y+k][z].ID = ID24;
								}
							}
							block[x][y][z].corner  = 1;
							block[x+1][y+3][z].corner  = 2;
							continue;
						}
					}

					//���������ɓ����Q�~�Q������΂Q�~�S�ɒu��������
					if(block[x+2][y][z].flag == 4)
					{
						if(block[x][y][z].ColorID == block[x+2][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x+2][y][z].ColorID < 1)
						{
							ID24++;
							num22 = num22 - 2;
							num24++;
							for(int i(0); i<4; i++)
							{				
								for(int k(0); k<2; k++)
								{	
									block[x+i][y+k][z].flag = 24;
									block[x+i][y+k][z].ID = ID24;
								}
							}
							block[x][y][z].corner  = 1;
							block[x+3][y+1][z].corner  = 2;
							//continue;
						}
					}



				}
			}
		}
	}
	//outputFlag("test07_22_to_24.txt", VoxSize);

}

void Change_flag_4_to_22(Lego*** block, int*  VoxSize)
{
	int x,y,z;
	int count(0);
	//��w
	for(z=1; z < VoxSize[2]-1; z=z+2 )				//����1,3,5,...
	{
		for(x=1; x < VoxSize[0]-1; x=x+2)
		{
			for(y=1; y < VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag == 4)
				{
					ID22++;
					count++;
					for(int i(0); i<2; i++)
					{
						for(int k(0); k<2; k++)
						{
							block[x+i][y+k][z].flag = 22;
							block[x+i][y+k][z].ID = ID22;
						}
					}
					block[x][y][z].corner = 1;
					block[x+1][y+1][z].corner = 2;
				}
			}
		}
	}

	//�����w
	for(z=2; z < VoxSize[2]-1; z=z+2 )				//����2,4,6,...
	{	
		for(x=0; x < VoxSize[0]-1; x=x+2)
		{
			for(y=0; y < VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag == 4)
				{
					ID22++;
					count++;
					for(int i(0); i<2; i++)
					{
						for(int k(0); k<2; k++)
						{
							block[x+i][y+k][z].flag = 22;
							block[x+i][y+k][z].ID = ID22;
						}
					}
					block[x][y][z].corner = 1;
					block[x+1][y+1][z].corner = 2;
				}
			}
		}
	}
	cout<<count<<"�̂Q�~�Q��flag���@�S�@����@�Q�Q�ɕς�����I"<<endl;
	//outputFlag("change_2�~2_flag_4_to_22.txt", VoxSize);
}

void Change_flag_2_to_12(Lego*** block, int*  VoxSize)
{
	int x,y,z;
	int count(0);
	//��w
	for(z=1; z < VoxSize[2]-1; z=z+2 )				//����1,3,5,...
	{
		for(x=1; x < VoxSize[0]-1; x=x+2)
		{
			for(y=1; y < VoxSize[1]-1; y=y+2)
			{
				//��                                                                                                                                    
				if(block[x][y][z].flag == 2 && block[x][y+1][z].flag == 2)
				{
					ID12++;
					count++;
					block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;			block[x][y][z].corner = 1;
					block[x][y+1][z].flag = 12;	block[x][y+1][z].ID = ID12;		block[x][y+1][z].corner  = 2;
				}
				//��                                                                                                                                  
				else if(block[x][y][z].flag == 2 && block[x+1][y][z].flag == 2)
				{
					ID12++;
					count++;
					block[x][y][z].flag = 12;			block[x][y][z].ID =ID12;			block[x][y][z].corner  = 1;
					block[x+1][y][z].flag = 12;	block[x+1][y][z].ID =ID12;		block[x+1][y][z].corner = 2;
				}
				//��                                                                                                                                                           
				else if(block[x+1][y][z].flag == 2 && block[x+1][y+1][z].flag == 2)
				{
					ID12++;
					count++;
					block[x+1][y][z].flag = 12;		block[x+1][y][z].ID =ID12;		block[x+1][y][z].corner = 1;			
					block[x+1][y+1][z].flag = 12;	block[x+1][y+1][z].ID =ID12;	block[x+1][y+1][z].corner = 2;
				}
				//�E                                                                                                                                                           
				else if(block[x][y+1][z].flag == 2 && block[x+1][y+1][z].flag == 2)
				{
					ID12++;
					count++;
					block[x][y+1][z].flag = 12;		block[x][y+1][z].ID =ID12;		block[x][y+1][z].corner = 1;
					block[x+1][y+1][z].flag = 12;	block[x+1][y+1][z].ID =ID12;	block[x+1][y+1][z].corner = 2;
				}
			}
		}
	}

	//�����w
	for(z=2; z < VoxSize[2]-1; z=z+2 )				//����2,4,6,...
	{	
		for(x=0; x < VoxSize[0]-1; x=x+2)
		{
			for(y=0; y < VoxSize[1]-1; y=y+2)
			{
				//��                                                                                                                                    
				if(block[x][y][z].flag == 2 && block[x][y+1][z].flag == 2)
				{
					ID12++;
					count++;
					block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;			block[x][y][z].corner = 1;
					block[x][y+1][z].flag = 12;	block[x][y+1][z].ID = ID12;		block[x][y+1][z].corner  = 2;
				}
				//��                                                                                                                                  
				else if(block[x][y][z].flag == 2 && block[x+1][y][z].flag == 2)
				{
					ID12++;
					count++;
					block[x][y][z].flag = 12;			block[x][y][z].ID =ID12;			block[x][y][z].corner  = 1;
					block[x+1][y][z].flag = 12;	block[x+1][y][z].ID =ID12;		block[x+1][y][z].corner = 2;
				}
				//��                                                                                                                                                           
				else if(block[x+1][y][z].flag == 2 && block[x+1][y+1][z].flag == 2)
				{
					ID12++;
					count++;
					block[x+1][y][z].flag = 12;		block[x+1][y][z].ID =ID12;		block[x+1][y][z].corner = 1;			
					block[x+1][y+1][z].flag = 12;	block[x+1][y+1][z].ID =ID12;	block[x+1][y+1][z].corner = 2;
				}
				//�E                                                                                                                                                           
				else if(block[x][y+1][z].flag == 2 && block[x+1][y+1][z].flag == 2)
				{
					ID12++;
					count++;
					block[x][y+1][z].flag = 12;		block[x][y+1][z].ID =ID12;		block[x][y+1][z].corner = 1;
					block[x+1][y+1][z].flag = 12;	block[x+1][y+1][z].ID =ID12;	block[x+1][y+1][z].corner = 2;
				}
			}
		}
	}
	cout<<count<<"�̂P�~�Q��flag���@�Q�@����@�P�Q�ɕς�����I"<<endl;
	//outputFlag("change_�P�~2_flag_2_to_12.txt", VoxSize);
}

//�Q�O�P�R�E�X�E�P�S
void Small_to_Big_after_Coloring(Lego*** block, int*  VoxSize)
{
	int x,y,z;
	//��w
	for(z=1; z < VoxSize[2]-1; z=z+2 )				//����1,3,5,...
	{
		for(x=1; x < VoxSize[0]-1; x=x+2)
		{
			for(y=1; y < VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag == 4)
				{
					//���������ɓ����Q�~�Q������΂Q�~�S�ɒu��������
					if(block[x][y+2][z].flag == 4)
					{
						ID24++;
						num22 = num22 - 2;
						num24++;
						for(int i(0); i<2; i++)
						{
							for(int k(0); k<4; k++)
							{
								block[x+i][y+k][z].flag = 24;
								block[x+i][y+k][z].ID = ID24;
							}
						}
						block[x][y][z].corner  = 1;
						block[x+1][y+3][z].corner  = 2;
						continue;
					}

					//���������ɓ����Q�~�Q������΂Q�~�S�ɒu��������
					if(block[x+2][y][z].flag == 4)
					{
						ID24++;
						num22 = num22 - 2;
						num24++;
						for(int i(0); i<4; i++)
						{				
							for(int k(0); k<2; k++)
							{	
								block[x+i][y+k][z].flag = 24;
								block[x+i][y+k][z].ID = ID24;
							}
						}
						block[x][y][z].corner  = 1;
						block[x+3][y+1][z].corner  = 2;
					}

				}
			}
		}
	}

	//�����w
	for(z=2; z < VoxSize[2]-1; z=z+2 )				//����2,4,6,...
	{	
		for(x=0; x < VoxSize[0]-1; x=x+2)
		{
			for(y=0; y < VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag == 4)
				{
					//���������ɓ����Q�~�Q������΂Q�~�S�ɒu��������
					if(block[x][y+2][z].flag == 4)
					{
						ID24++;
						num22 = num22 - 2;
						num24++;
						for(int i(0); i<2; i++)
						{
							for(int k(0); k<4; k++)
							{
								block[x+i][y+k][z].flag = 24;
								block[x+i][y+k][z].ID = ID24;
							}
						}
						block[x][y][z].corner  = 1;
						block[x+1][y+3][z].corner  = 2;
						continue;
					}

					//���������ɓ����Q�~�Q������΂Q�~�S�ɒu��������
					if(block[x+2][y][z].flag == 4)
					{
						ID24++;
						num22 = num22 - 2;
						num24++;
						for(int i(0); i<4; i++)
						{				
							for(int k(0); k<2; k++)
							{	
								block[x+i][y+k][z].flag = 24;
								block[x+i][y+k][z].ID = ID24;
							}
						}
						block[x][y][z].corner  = 1;
						block[x+3][y+1][z].corner  = 2;
					}

				}
			}
		}
	}
	outputFlag("test07_22_to_24.txt", VoxSize);


}