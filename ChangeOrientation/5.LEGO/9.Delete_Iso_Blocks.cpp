#include "../stdafx.h"
#include "../Voxel.h"
#include "../Lego.h"		//LEGO�u���b�N��g�ݗ��Ă邽�߂̃N���X

void outputFlag(string filename, int* size);
void outputID(string filename, int* size);

extern int num11;		//�Q�~�Q�̃u���b�N�̐�
extern int num12;		//�Q�~�Q�̃u���b�N�̐�
extern int num22;		//�Q�~�Q�̃u���b�N�̐�

//�P�~�P�̏㉺�����ău���b�N���Ȃ����������
void Delete_Iso_Blocks_11(Lego*** block, int* VoxSize)
{
	int x,y,z;
	int count(0);
	for(z=1; z<VoxSize[2]-1; z++)
	{
		for(x=1; x<VoxSize[0]-1; x++)
		{
			for(y=1; y<VoxSize[1]-1; y++)
			{
				//�P�~�P�̌Ǘ��u���b�N������
				if(block[x][y][z].flag == 1)
				{
					//�㉺�̃u���b�N�����ė����Ƃ������Ȃ��ꍇ
					if(block[x][y][z-1].flag < 1 && block[x][y][z+1].flag < 1)
					{
						count++;
						num11--;
						block[x][y][z].Initiaization();
					}
				}
			}
		}
	}
	cout<<count<<"�̂P�~�P���폜���ꂽ"<<endl;
	//outputFlag("Delete_Blocks_11.txt", VoxSize);
}

//�P�~�Q�̏㉺�����ău���b�N���Ȃ����������
void Delete_Iso_Blocks_12(Lego*** block, int* VoxSize)
{
	int x,y,z;
	int count(0);
	for(z=1; z < VoxSize[2]-1; z++ )
	{
		//��w
		if(z%2)
		{
			for(x=1; x < VoxSize[0]-1; x=x+2)
			{
				for(y=1; y < VoxSize[1]-1; y=y+2)
				{
					//��
					if(block[x][y][z].flag == 12 && block[x][y+1][z].flag == 12)
					{
						if(block[x][y][z-1].flag < 1 && block[x][y+1][z-1].flag < 1 && block[x][y][z+1].flag < 1 && block[x][y+1][z+1].flag < 1)
						{
							count++;
							num12--;
							block[x][y][z].Initiaization();
							block[x][y+1][z].Initiaization();
							cout<<x<<" "<<y<<" "<<z<<endl;
						}
					}
					//��
					else if(block[x][y][z].flag == 12 && block[x+1][y][z].flag == 12)
					{
						if(block[x][y][z-1].flag < 1 && block[x+1][y][z-1].flag < 1 && block[x][y][z+1].flag < 1 && block[x+1][y][z+1].flag < 1)
						{
							count++;
							num12--;
							block[x][y][z].Initiaization();
							block[x+1][y][z].Initiaization();
							cout<<x<<" "<<y<<" "<<z<<endl;
						}
					}
					//��
					else if(block[x+1][y][z].flag == 12 && block[x+1][y+1][z].flag == 12)
					{
						if(block[x+1][y][z-1].flag < 1 && block[x+1][y+1][z-1].flag < 1 && block[x+1][y][z+1].flag < 1 && block[x+1][y+1][z+1].flag < 1)
						{
							count++;
							num12--;
							block[x+1][y][z].Initiaization();
							block[x+1][y+1][z].Initiaization();
							cout<<x<<" "<<y<<" "<<z<<endl;
						}
					}
					//�E
					else if(block[x][y+1][z].flag == 12 && block[x+1][y+1][z].flag == 12)
					{
						if(block[x][y+1][z-1].flag < 1 && block[x+1][y+1][z-1].flag < 1 && block[x][y+1][z+1].flag < 1 && block[x+1][y+1][z+1].flag < 1)
						{
							count++;
							num12--;
							block[x][y+1][z].Initiaization();
							block[x+1][y+1][z].Initiaization();
							cout<<x<<" "<<y<<" "<<z<<endl;
						}
					}
				}
			}
		}
		//�����w
		else
		{
			for(x=0; x < VoxSize[0]-1; x=x+2)
			{
				for(y=0; y < VoxSize[1]-1; y=y+2)
				{
					//��
					if(block[x][y][z].flag == 12 && block[x][y+1][z].flag == 12)
					{
						if(block[x][y][z-1].flag < 1 && block[x][y+1][z-1].flag < 1 && block[x][y][z+1].flag < 1 && block[x][y+1][z+1].flag < 1)
						{
							count++;
							num12--;
							block[x][y][z].Initiaization();
							block[x][y+1][z].Initiaization();
							cout<<x<<" "<<y<<" "<<z<<endl;
						}
					}
					//��
					else if(block[x][y][z].flag == 12 && block[x+1][y][z].flag == 12)
					{
						if(block[x][y][z-1].flag < 1 && block[x+1][y][z-1].flag < 1 && block[x][y][z+1].flag < 1 && block[x+1][y][z+1].flag < 1)
						{
							count++;
							num12--;
							block[x][y][z].Initiaization();
							block[x+1][y][z].Initiaization();
							cout<<x<<" "<<y<<" "<<z<<endl;
						}
					}
					//��
					else if(block[x+1][y][z].flag == 12 && block[x+1][y+1][z].flag == 12)
					{
						if(block[x+1][y][z-1].flag < 1 && block[x+1][y+1][z-1].flag < 1 && block[x+1][y][z+1].flag < 1 && block[x+1][y+1][z+1].flag < 1)
						{
							count++;
							num12--;
							block[x+1][y][z].Initiaization();
							block[x+1][y+1][z].Initiaization();
							cout<<x<<" "<<y<<" "<<z<<endl;
						}
					}
					//�E
					else if(block[x][y+1][z].flag == 12 && block[x+1][y+1][z].flag == 12)
					{
						if(block[x][y+1][z-1].flag < 1 && block[x+1][y+1][z-1].flag < 1 && block[x][y+1][z+1].flag < 1 && block[x+1][y+1][z+1].flag < 1)
						{
							count++;
							num12--;
							block[x][y+1][z].Initiaization();
							block[x+1][y+1][z].Initiaization();
							cout<<x<<" "<<y<<" "<<z<<endl;
						}
					}
				}
			}
		}
	}

	cout<<count<<"�̂P�~�Q���폜���ꂽ�I"<<endl;
	//outputFlag("Delete_Blocks_12.txt", VoxSize);

}

//�Q�~�Q�̓Ɨ����Ă���{�N�Z�����폜
void Delete_Iso_Blocks_22(Lego*** block, int* VoxSize)
{
	int x,y,z;
	int count(0);
	for(z=1; z < VoxSize[2]-1; z++ )
	{
		//��w
		if(z%2)
		{
			for(x=1; x < VoxSize[0]-1; x=x+2)
			{
				for(y=1; y < VoxSize[1]-1; y=y+2)
				{
					//�Ίp���̃{�N�Z����flag���Q�Q��������
					if(block[x][y][z].flag == 22 && block[x+1][y+1][z].flag == 22)	
					{
						if(block[x][y][z-1].flag < 1 && block[x][y][z+1].flag < 1)
							if(block[x][y+1][z-1].flag < 1 && block[x][y+1][z+1].flag < 1)
								if(block[x+1][y][z-1].flag < 1 && block[x+1][y][z+1].flag < 1)
									if(block[x+1][y+1][z-1].flag < 1 && block[x+1][y+1][z+1].flag < 1)
									{
										count++;
										num22--;
										for(int i(0); i<2; i++)
											for(int k(0); k<2; k++)
												block[x+i][y+k][z].Initiaization();
									}
					}
				}
			}
		}
		//�����w
		else
		{
			for(x=0; x < VoxSize[0]-1; x=x+2)
			{
				for(y=0; y < VoxSize[1]-1; y=y+2)
				{
					//�Ίp���̃{�N�Z����flag���Q�Q��������
					if(block[x][y][z].flag == 22 && block[x+1][y+1][z].flag == 22)	
					{
						if(block[x][y][z-1].flag < 1 && block[x][y][z+1].flag < 1)
							if(block[x][y+1][z-1].flag < 1 && block[x][y+1][z+1].flag < 1)
								if(block[x+1][y][z-1].flag < 1 && block[x+1][y][z+1].flag < 1)
									if(block[x+1][y+1][z-1].flag < 1 && block[x+1][y+1][z+1].flag < 1)
									{
										count++;
										num22--;
										for(int i(0); i<2; i++)
											for(int k(0); k<2; k++)
												block[x+i][y+k][z].Initiaization();
									}
					}
				}
			}
		}
	}

	cout<<count<<"�̂Q�~�Q���폜���ꂽ�I"<<endl;
	//outputFlag("Delete_Blocks_22.txt", VoxSize);
}

//�Ǘ��������ȃu���b�N�Q�������悤�ɂ���
//�܂��A�P�~�Q��T��
//���̏㉺�̃u���b�N���P�~�P�܂��͉����Ȃ��ꍇ����ɂ�������Ă���
void Delete_Iso_Blocks(Lego*** block, int* VoxSize)
{
	int x,y,z;
	int num(0);

	for(z=1; z < VoxSize[2]-1; z++ )
	{
		for(x=1; x < VoxSize[0]-1; x++)
		{
			for(y=1; y < VoxSize[1]-1; y++)
			{
				if(block[x][y][z].flag == 12)
				{
					//################################
					//�������̂P�~�Q
					//################################
					if(block[x][y+1][z].flag == 12 && block[x][y+1][z].ID == block[x][y][z].ID)
					{
						num = 0;
						//�P�ڂ̉�������
						//if(block[x][y][z-1].flag == 1 && block[x][y][z-2].flag < 1)
						if(block[x][y][z-1].flag == 1)
						{
							if(block[x][y][z-2].flag < 1)
								num++;
						}
						else if(block[x][y][z-1].flag < 1)
							num++;
						else
							continue;
						//�P�ڂ̏������
						//if(block[x][y][z+1].flag == 1 && block[x][y][z+2].flag < 1)
						if(block[x][y][z+1].flag == 1)
						{
							if(block[x][y][z+2].flag < 1)
								num++;
						}
						else if(block[x][y][z+1].flag < 1)
							num++;
						else
							continue;
						//�Q�ڂ̉�������
						//if(block[x][y+1][z-1].flag == 1 && block[x][y+1][z-2].flag < 1)
						if(block[x][y+1][z-1].flag == 1 )
						{
							if(block[x][y+1][z-2].flag < 1)
								num++;
						}
						else if(block[x][y+1][z-1].flag < 1)
							num++;
						else
							continue;
						//�Q�ڂ̏������
						if(block[x][y+1][z+1].flag == 1)
						{
							if(block[x][y+1][z+2].flag < 1)
								num++;
						}
						else if(block[x][y+1][z+1].flag < 1)
							num++;
						else
							continue;

						if(num<4)
							continue;
						for(int i(0); i<2; i++)
						{
							for(int k(0); k<3; k = k + 2)
								if(block[x][y+i][z+k-1].flag == 1)
									num11--;
						}
						num12--;
						//�P�~�Q�̏㉺���v�U�̃{�N�Z����flag���O�ɂ��� �p�����I�I
						for(int i(0); i<2; i++)
						{
							for(int k(0); k<3; k++)
								block[x][y+i][z+k-1].Initiaization();
						}
						cout<<"�u���b�N���폜�����I�F"<<x<<" "<<y<<" "<<z<<endl;
					}
					//################################
					//�������̂P�~�Q
					//################################
					else if(block[x+1][y][z].flag == 12 && block[x+1][y][z].ID == block[x][y][z].ID)
					{
						num = 0;
						//�P�ڂ̉�������
						//if(block[x][y][z-1].flag == 1 && block[x][y][z-2].flag < 1)
						if(block[x][y][z-1].flag == 1)
						{
							if(block[x][y][z-2].flag < 1)
								num++;
						}
						else if(block[x][y][z-1].flag < 1)
							num++;
						else
							continue;
						//�P�ڂ̏������
						//if(block[x][y][z+1].flag == 1 && block[x][y][z+2].flag < 1)
						if(block[x][y][z+1].flag == 1)
						{
							if(block[x][y][z+2].flag < 1)
								num++;
						}
						else if(block[x][y][z+1].flag < 1)
							num++;
						else
							continue;
						//�Q�ڂ̉�������
						//if(block[x+1][y][z-1].flag == 1 && block[x+1][y][z-2].flag < 1)
						if(block[x+1][y][z-1].flag == 1)
						{
							if(block[x+1][y][z-2].flag < 1)
								num++;
						}
						else if(block[x+1][y][z-1].flag < 1)
							num++;
						else
							continue;
						//�Q�ڂ̏������
						//if(block[x+1][y][z+1].flag == 1 && block[x+1][y][z+2].flag < 1)
						if(block[x+1][y][z+1].flag == 1 )
						{
							if(block[x+1][y][z+2].flag < 1)
								num++;
						}
						else if(block[x+1][y][z+1].flag < 1)
							num++;
						else
							continue;

						if(num<4)
							continue;

						for(int i(0); i<2; i++)
						{
							for(int k(0); k<3; k = k + 2)
								if(block[x+i][y][z+k-1].flag == 1)
									num11--;
						}
						num12--;

						//�P�~�Q�̏㉺���v�U�̃{�N�Z����flag���O�ɂ���
						for(int i(0); i<2; i++)
						{
							for(int k(0); k<3; k++)
								block[x+i][y][z+k-1].Initiaization();
						}
						//�P�~�P�͉��H�i�P�`�S�j
						cout<<"�u���b�N���폜�����I�F"<<x<<" "<<y<<" "<<z<<endl;
					}
				}
			}
		}
	}

	outputFlag("Delete_Blocks.txt", VoxSize);
	//outputID("Delete_Blocks_ID.txt", VoxSize);
}
