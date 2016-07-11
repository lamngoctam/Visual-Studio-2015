#include "../stdafx.h"
#include "../Voxel.h"
#include "../Lego.h"		//LEGO�u���b�N��g�ݗ��Ă邽�߂̃N���X

extern int ID14;
extern int ID13;

extern int num11;		//�P�~�P�̃u���b�N�̐�
extern int num12;		//�P�~2�̃u���b�N�̐�
extern int num13;		//�P�~�R�̃u���b�N�̐�
extern int num14;		//�P�~�S�̃u���b�N�̐�

void outputFlag(string filename, int* size);

//�P�~�P�̂S�����Ɂ@�P�~3�@����������@����������
void Small_to_Big_step2(Lego*** block, int* VoxSize)
{
	int count(0);
	//1�~1�̂S���������ā@
	for(int z(1); z < VoxSize[2]-1; z++ )
	{
		for(int x(1); x < VoxSize[0]-1; x++)
		{
			for(int y(1); y < VoxSize[1]-1; y++)
			{
				//�\�ʃu���b�N���u���b�N��ID���P�i�P�~�P�j�̏ꍇ
				if(block[x][y][z].flag == 1)
				{
					//�P�~3������ꍇ
					//�����̐i�s����
					if(y+3<VoxSize[1]-1)
					{
						if(block[x][y+1][z].flag == 13 && block[x][y+2][z].flag == 13 && block[x][y+3][z].flag == 13)		
						{
							count++;
							ID14++;
							num11--;
							num13--;
							num14++;
							//�P�~�S�ւƕϊ�����
							for(int i(0); i<4; i++)
							{
								block[x][y+i][z].flag = 14;			
								block[x][y+i][z].ID = ID14;
							}
							block[x][y][z].corner = 1;
							block[x][y+3][z].corner = 2;
							continue;
						}
					}
					if(x+3<VoxSize[1]-1)
					{
						if(block[x+1][y][z].flag == 13 && block[x+2][y][z].flag == 13 && block[x+3][y][z].flag == 13)		//�����̐i�s����
						{
							count++;
							ID14++;
							num11--;
							num13--;
							num14++;
							for(int i(0); i<4; i++)
							{
								block[x+i][y][z].flag = 14;			
								block[x+i][y][z].ID = ID14;
							}
							block[x][y][z].corner = 1;
							block[x+3][y][z].corner = 2;
							continue;
						}
					}
					if(y-3 > 0)
					{
						if(block[x][y-1][z].flag == 13 && block[x][y-2][z].flag == 13 && block[x][y-3][z].flag == 13 )			//�����̐i�s�t����
						{
							count++;
							ID14++;
							num11--;
							num13--;
							num14++;
							for(int i(0); i<4; i++)
							{
								block[x][y-3+i][z].flag = 14;			
								block[x][y-3+i][z].ID = ID14;
							}
							block[x][y][z].corner = 2;
							block[x][y-3][z].corner = 1;
							continue;
						}
					}
					if(x-3 > 0)
					{
						if(block[x-1][y][z].flag == 13 && block[x-2][y][z].flag == 13 && block[x-3][y][z].flag == 13)			//�����̐i�s�t����
						{
							count++;
							ID14++;
							num11--;
							num13--;
							num14++;
							for(int i(0); i<4; i++)
							{
								block[x-3+i][y][z].flag = 14;			
								block[x-3+i][y][z].ID = ID14;
							}
							block[x][y][z].corner = 2;
							block[x-3][y][z].corner = 1;
							continue;
						}
					}
				}
			}
		}
	}

	cout<<count<<"�̂P�~�S���@�P�~�P�@�Ɓ@�P�~�R���琶�����ꂽ�I"<<endl;
	outputFlag("test02_11_13_to_14.txt", VoxSize);

}


void Small_to_Big_step2_color(Lego*** block, int* VoxSize)
{
	int count(0);
	//1�~1�̂S���������ā@
	for(int z(1); z < VoxSize[2]-1; z++ )
	{
		for(int x(1); x < VoxSize[0]-1; x++)
		{
			for(int y(1); y < VoxSize[1]-1; y++)
			{
				//�\�ʃu���b�N���u���b�N��ID���P�i�P�~�P�j�̏ꍇ
				if(block[x][y][z].flag == 1)
				{
					//�P�~3������ꍇ
					//�����̐i�s����
					if(y+3<VoxSize[1]-1)
					{
						if(block[x][y+1][z].flag == 13 && block[x][y+2][z].flag == 13 && block[x][y+3][z].flag == 13)		
						{
							if(block[x][y][z].ColorID == block[x][y+1][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y+1][z].ColorID < 1)
							{
								count++;
								ID14++;
								num11--;
								num13--;
								num14++;
								//�P�~3�ւƕϊ�����
								for(int i(0); i<4; i++)
								{
									block[x][y+i][z].flag = 14;			
									block[x][y+i][z].ID = ID14;
								}
								block[x][y][z].corner = 1;
								block[x][y+3][z].corner = 2;
								continue;
							}
						}
					}
					if(x+3<VoxSize[1]-1)
					{
						if(block[x+1][y][z].flag == 13 && block[x+2][y][z].flag == 13 && block[x+3][y][z].flag == 13)		//�����̐i�s����
						{
							if(block[x][y][z].ColorID == block[x+1][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x+1][y][z].ColorID < 1)
							{
								count++;
								ID14++;
								num11--;
								num13--;
								num14++;
								for(int i(0); i<4; i++)
								{
									block[x+i][y][z].flag = 14;			
									block[x+i][y][z].ID = ID14;
								}
								block[x][y][z].corner = 1;
								block[x+3][y][z].corner = 2;
								continue;
							}
						}
					}
					if(y-3 > 0)
					{
						if(block[x][y-1][z].flag == 13 && block[x][y-2][z].flag == 13 && block[x][y-3][z].flag == 13 )			//�����̐i�s�t����
						{
							if(block[x][y][z].ColorID == block[x][y-1][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y-1][z].ColorID < 1)
							{
								count++;
								ID14++;
								num11--;
								num13--;
								num14++;
								for(int i(0); i<4; i++)
								{
									block[x][y-3+i][z].flag = 14;			
									block[x][y-3+i][z].ID = ID14;
								}
								block[x][y][z].corner = 2;
								block[x][y-3][z].corner = 1;
								continue;
							}
						}
					}
					if(x-3 > 0)
					{
						if(block[x-1][y][z].flag == 13 && block[x-2][y][z].flag == 13 && block[x-3][y][z].flag == 13)			//�����̐i�s�t����
						{
							if(block[x][y][z].ColorID == block[x-1][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x-1][y][z].ColorID < 1)
							{
								count++;
								ID14++;
								num11--;
								num13--;
								num14++;
								for(int i(0); i<4; i++)
								{
									block[x-3+i][y][z].flag = 14;			
									block[x-3+i][y][z].ID = ID14;
								}
								block[x][y][z].corner = 2;
								block[x-3][y][z].corner = 1;
								continue;
							}
						}
					}
				}
			}
		}
	}

	cout<<count<<"�̂P�~�S���@�P�~�P�@�Ɓ@�P�~�R���琶�����ꂽ�I"<<endl;
	//outputFlag("test02_11_13_to_14.txt", VoxSize);

}

//1�~1��1�~2������
void Small_to_Big_before_before_step2_color(Lego*** block, int* VoxSize)
{
	int count(0);
	//1�~1�̂S���������ā@
	for(int z(1); z < VoxSize[2]-1; z++ )
	{
		for(int x(1); x < VoxSize[0]-1; x++)
		{
			for(int y(1); y < VoxSize[1]-1; y++)
			{
				//�\�ʃu���b�N���u���b�N��ID���P�i�P�~�P�j�̏ꍇ
				if(block[x][y][z].flag == 1)
				{
					//�P�~3������ꍇ
					//�����̐i�s����
					if(y+2<VoxSize[1]-1)
					{
						if(block[x][y+1][z].flag == 12 && block[x][y+2][z].flag == 12)		
							if(block[x][y+1][z].ID== block[x][y+2][z].ID)		
						{
							if(block[x][y][z].ColorID == block[x][y+1][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y+1][z].ColorID < 1)
							{
								count++;
								ID13++;
								num11--;
								num12--;
								num13++;
								//�P�~3�ւƕϊ�����
								for(int i(0); i<3; i++)
								{
									block[x][y+i][z].flag = 13;			
									block[x][y+i][z].ID = ID13;
								}
								block[x][y][z].corner = 1;
								block[x][y+2][z].corner = 2;
								continue;
							}
						}
					}
					if(x+2<VoxSize[1]-1)
					{
						if(block[x+1][y][z].flag == 12 && block[x+2][y][z].flag == 12 )		//�����̐i�s����
							if(block[x+1][y][z].ID== block[x+2][y][z].ID)		
						{
							if(block[x][y][z].ColorID == block[x+1][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x+1][y][z].ColorID < 1)
							{
								count++;
								ID13++;
								num11--;
								num12--;
								num13++;
								for(int i(0); i<3; i++)
								{
									block[x+i][y][z].flag = 13;			
									block[x+i][y][z].ID = ID13;
								}
								block[x][y][z].corner = 1;
								block[x+2][y][z].corner = 2;
								continue;
							}
						}
					}
					if(y-2 > 0)
					{
						if(block[x][y-1][z].flag == 12 && block[x][y-2][z].flag == 12  )			//�����̐i�s�t����
							if(block[x][y-1][z].ID== block[x][y-2][z].ID)		
						{
							if(block[x][y][z].ColorID == block[x][y-1][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y-1][z].ColorID < 1)
							{
								count++;
								ID13++;
								num11--;
								num12--;
								num13++;
								for(int i(0); i<3; i++)
								{
									block[x][y-i][z].flag = 13;			
									block[x][y-i][z].ID = ID13;
								}
								block[x][y][z].corner = 2;
								block[x][y-2][z].corner = 1;
								continue;
							}
						}
					}
					if(x-2 > 0)
					{
						if(block[x-1][y][z].flag == 12 && block[x-2][y][z].flag == 12 )			//�����̐i�s�t����
							if(block[x-1][y][z].ID== block[x-2][y][z].ID)		
						{
							if(block[x][y][z].ColorID == block[x-1][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x-1][y][z].ColorID < 1)
							{
								count++;
								ID13++;
								num11--;
								num12--;
								num13++;
								for(int i(0); i<3; i++)
								{
									block[x-i][y][z].flag = 13;			
									block[x-i][y][z].ID = ID13;
								}
								block[x][y][z].corner = 2;
								block[x-2][y][z].corner = 1;
								continue;
							}
						}
					}
				}
			}
		}
	}

	cout<<count<<"�̂P�~3���@�P�~�P�@�Ɓ@�P�~�R���琶�����ꂽ�I"<<endl;
	//outputFlag("test02_11_13_to_14.txt", VoxSize);

}

//1�~1��1�~2������
void Small_to_Big_before_step2_color(Lego*** block, int* VoxSize)
{
	int count(0);
	//1�~1�̂S���������ā@
	for(int z(1); z < VoxSize[2]-1; z++ )
	{
		for(int x(1); x < VoxSize[0]-1; x++)
		{
			for(int y(1); y < VoxSize[1]-1; y++)
			{
				//�\�ʃu���b�N���u���b�N��ID���P�i�P�~�P�j�̏ꍇ
				if(block[x][y][z].flag == 1)
				{
					//�P�~2������ꍇ
					//�����̐i�s����
					if(y+2<VoxSize[1]-1)
					{
						if(block[x][y+1][z].flag == 2 && block[x][y+2][z].flag == 2 )		
							if(block[x][y+1][z].ID== block[x][y+2][z].ID)		
						{
							if(block[x][y][z].ColorID == block[x][y+1][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y+1][z].ColorID < 1)
							{
								count++;
								ID13++;
								num11--;
								num12--;
								num13++;
								//�P�~�S�ւƕϊ�����
								for(int i(0); i<3; i++)
								{
									block[x][y+i][z].flag = 13;			
									block[x][y+i][z].ID = ID13;
								}
								block[x][y][z].corner = 1;
								block[x][y+2][z].corner = 2;
								continue;
							}
						}
					}
					if(x+2<VoxSize[1]-1)
					{
						if(block[x+1][y][z].flag == 2 && block[x+2][y][z].flag == 2 )		//�����̐i�s����
							if(block[x+1][y][z].ID== block[x+2][y][z].ID)		
						{
							if(block[x][y][z].ColorID == block[x+1][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x+1][y][z].ColorID < 1)
							{
								count++;
								ID13++;
								num11--;
								num12--;
								num13++;
								for(int i(0); i<3; i++)
								{
									block[x+i][y][z].flag = 13;			
									block[x+i][y][z].ID = ID13;
								}
								block[x][y][z].corner = 1;
								block[x+2][y][z].corner = 2;
								continue;
							}
						}
					}
					if(y-2 > 0)
					{
						if(block[x][y-1][z].flag == 2 && block[x][y-2][z].flag == 2  )			//�����̐i�s�t����
							if(block[x][y-1][z].ID== block[x][y-2][z].ID)		
						{
							if(block[x][y][z].ColorID == block[x][y-1][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y-1][z].ColorID < 1)
							{
								count++;
								ID13++;
								num11--;
								num12--;
								num13++;
								for(int i(0); i<3; i++)
								{
									block[x][y-i][z].flag = 13;			
									block[x][y-i][z].ID = ID13;
								}
								block[x][y][z].corner = 2;
								block[x][y-2][z].corner = 1;
								continue;
							}
						}
					}
					if(x-2 > 0)
					{
						if(block[x-1][y][z].flag == 2 && block[x-2][y][z].flag == 2 )			//�����̐i�s�t����
							if(block[x-1][y][z].ID== block[x-2][y][z].ID)		
						{
							if(block[x][y][z].ColorID == block[x-1][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x-1][y][z].ColorID < 1)
							{
								count++;
								ID13++;
								num11--;
								num12--;
								num13++;
								for(int i(0); i<3; i++)
								{
									block[x-i][y][z].flag = 13;			
									block[x-i][y][z].ID = ID13;
								}
								block[x][y][z].corner = 2;
								block[x-2][y][z].corner = 1;
								continue;
							}
						}
					}
				}
			}
		}
	}

	cout<<count<<"�̂P�~3���@�P�~�P�@�Ɓ@�P�~2���琶�����ꂽ�I"<<endl;
	//outputFlag("test02_11_13_to_14.txt", VoxSize);

}