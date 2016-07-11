#include "../stdafx.h"
#include "../Voxel.h"
#include "../Lego.h"		//LEGO�u���b�N��g�ݗ��Ă邽�߂̃N���X

extern int ID12;			
extern int ID13;
extern int ID14;

extern int num11;		//�P�~�P�̃u���b�N�̐�
extern int num12;		//�P�~�Q�̃u���b�N�̐�
extern int num13;		//�P�~�R�̃u���b�N�̐�
extern int num14;		//�P�~�S�̃u���b�N�̐�
extern int num22;		//�Q�~�Q�̃u���b�N�̐�
extern int num23;		//�Q�~�R�̃u���b�N�̐�
extern int num24;		//�Q�~�S�̃u���b�N�̐�

void outputFlag(string filename, int* size);

//�P�~�P�̂S�����Ɂ@�P�~�P�@�܂��́@�P�~�Q�@����������@����������
//�Q�O�P�R�E�V�E�Q�O�i�y�j�P�~�P�@�{�@�P�~�Q�@�{�@�P�~�P�@���@�P�~�S�ɂ������������H�@����Ƃ���Ł@�P�~�R�@�{�@�P�~�P�@���@�P�~�S
void Small_to_Big_step1(Lego*** block, int* VoxSize)
{
	for(int z(1); z < VoxSize[2]-1; z++ )
	{
		//��w
		if(z%2)
		{
			for(int x(1); x < VoxSize[0]-1; x=x+2)
			{
				for(int y(1); y < VoxSize[1]-1; y=y+2)
				{
					//                                                                                                
					//���オ�P�~�P�̏ꍇ
					if(block[x][y][z].flag == 1)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						if(block[x-1][y][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x-1][y][z].flag = 12;		block[x-1][y][z].ID = ID12;	block[x-1][y][z].corner = 1;
							goto Odd_Right_Up;		//continue���g��Ȃ��̂͂S�܂��̒��łP�~�P���Ίp���ő��݂���ꍇ�ɂ���������v�Z����Ȃ�
							//continue;
						}
						if(block[x][y-1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							//�P�~�Q�ɂ���
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x][y-1][z].flag = 12;		block[x][y-1][z].ID = ID12;	block[x][y-1][z].corner = 1;
							goto Odd_Right_Up;
						}
						//�P�~�Q������ꍇ
						if(block[x-1][y][z].flag == 2 )
						{
							if(block[x-2][y][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								//�P�~�R�ɂ���
								for(int i(0); i<3; i++){
									block[x-i][y][z].flag = 13;			block[x-i][y][z].ID = ID13;
								}
								block[x][y][z].corner = 2;
								block[x-2][y][z].corner = 1;
								goto Odd_Right_Up;
							}
						}
						if(block[x][y-1][z].flag == 2 )
						{
							if(block[x][y-2][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								//�P�~�R�ɂ���
								for(int i(0); i<3; i++){
									block[x][y-i][z].flag = 13;			block[x][y-i][z].ID = ID13;
								}
								block[x][y][z].corner = 2;
								block[x][y-2][z].corner = 1;
								//goto Odd_Right_Up;
							}
						}
					}
Odd_Right_Up:
					//                                                                                                
					//�E�オ�P�~�P�̏ꍇ
					if(block[x][y+1][z].flag == 1)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						//�P�~�P������ꍇ
						if(block[x-1][y+1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;			block[x][y+1][z].corner = 2;		
							block[x-1][y+1][z].flag = 12;		block[x-1][y+1][z].ID = ID12;		block[x-1][y+1][z].corner = 1;
							goto Odd_Left_Down;
						}
						if(block[x][y+2][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;			block[x][y+1][z].corner = 1;
							block[x][y+2][z].flag = 12;		block[x][y+2][z].ID = ID12;			block[x][y+2][z].corner = 2;
							goto Odd_Left_Down;
						}
						//�P�~�Q������ꍇ
						if(block[x-1][y+1][z].flag == 2)
						{
							if(block[x-2][y+1][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;

								for(int i(0); i<3; i++){
									block[x-i][y+1][z].flag = 13;			block[x-i][y+1][z].ID = ID13;
								}
								block[x][y+1][z].corner = 2;
								block[x-2][y+1][z].corner = 1;
								goto Odd_Left_Down;
							}
						}
						if(block[x][y+2][z].flag == 2)
						{
							if(block[x][y+3][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								for(int i(0); i<3; i++){
									block[x][y+i+1][z].flag = 13;			block[x][y+i+1][z].ID = ID13;
								}
								block[x][y+1][z].corner = 1;
								block[x][y+3][z].corner = 2;
								//goto Odd_Left_Down;
							}
						}
					}
Odd_Left_Down:
					//                                                                                               
					//�������P�~�P�̏ꍇ
					if(block[x+1][y][z].flag == 1)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						//�P�~�P������ꍇ
						if(block[x+1][y-1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 2;
							block[x+1][y-1][z].flag = 12;		block[x+1][y-1][z].ID = ID12;	block[x+1][y-1][z].corner = 1;
							goto Odd_Right_Down;
						}
						if(block[x+2][y][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 1;
							block[x+2][y][z].flag = 12;		block[x+2][y][z].ID = ID12;		block[x+2][y][z].corner = 2;
							goto Odd_Right_Down;
						}
						//�P�~�Q������ꍇ
						if(block[x+1][y-1][z].flag == 2)
						{
							if(block[x+1][y-2][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								for(int i(0); i<3; i++){
									block[x+1][y-i][z].flag = 13;	block[x+1][y-i][z].ID = ID13;
								}
								block[x+1][y][z].corner = 2;
								block[x+1][y-2][z].corner = 1;
								goto Odd_Right_Down;
							}
						}
						if(block[x+2][y][z].flag == 2 )
						{
							if(block[x+3][y][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								for(int i(0); i<3; i++){
									block[x+i+1][y][z].flag = 13;			block[x+i+1][y][z].ID = ID13;
								}
								block[x+1][y][z].corner = 1;
								block[x+3][y][z].corner = 2;
								//goto Odd_Right_Down;
							}
						}
					}
Odd_Right_Down:
					//                                                                                               
					//�E��
					if(block[x+1][y+1][z].flag == 1)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						//�P�~�P������ꍇ
						if(block[x+1][y+2][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x+1][y+1][z].flag = 12;		block[x+1][y+1][z].ID = ID12;		block[x+1][y+1][z].corner = 1;
							block[x+1][y+2][z].flag = 12;		block[x+1][y+2][z].ID = ID12;		block[x+1][y+2][z].corner = 2;
							continue;
						}
						if(block[x+2][y+1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x+1][y+1][z].flag = 12;		block[x+1][y+1][z].ID = ID12;		block[x+1][y+1][z].corner = 1;
							block[x+2][y+1][z].flag = 12;		block[x+2][y+1][z].ID = ID12;		block[x+2][y+1][z].corner = 2;
							continue;
						}
						//�P�~�Q������ꍇ
						if(block[x+1][y+2][z].flag == 2 )
						{
							if(block[x+1][y+3][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								for(int i(0); i<3; i++){
									block[x+1][y+i+1][z].flag = 13;	block[x+1][y+i+1][z].ID = ID13;
								}
								block[x+1][y+1][z].corner = 1;
								block[x+1][y+3][z].corner = 2;
								continue;
							}
						}
						if(block[x+2][y+1][z].flag == 2 )
						{
							if(block[x+3][y+1][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								for(int i(0); i<3; i++){
									block[x+i+1][y+1][z].flag = 13;			block[x+i+1][y+1][z].ID = ID13;
								}
								block[x+1][y+1][z].corner = 1;
								block[x+3][y+1][z].corner = 2;
								continue;
							}
						}
					}

				}
			}
		}

		//�����w
		else
		{
			for(int x(0); x < VoxSize[0]-1; x=x+2)
			{
				for(int y(0); y < VoxSize[1]-1; y=y+2)
				{
					//                                                                                                
					//���オ�P�~�P�̏ꍇ
					if(block[x][y][z].flag == 1)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						if(block[x-1][y][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x-1][y][z].flag = 12;		block[x-1][y][z].ID = ID12;	block[x-1][y][z].corner = 1;
							goto Even_Right_Up;		//continue���g��Ȃ��̂͂S�܂��̒��łP�~�P���Ίp���ő��݂���ꍇ�ɂ���������v�Z����Ȃ�
							//continue;
						}
						if(block[x][y-1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							//�P�~�Q�ɂ���
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x][y-1][z].flag = 12;		block[x][y-1][z].ID = ID12;	block[x][y-1][z].corner = 1;
							goto Even_Right_Up;
						}
						//�P�~�Q������ꍇ
						if(block[x-1][y][z].flag == 2)
						{
							if(block[x-2][y][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								//�P�~�R�ɂ���
								for(int i(0); i<3; i++){
									block[x-i][y][z].flag = 13;			block[x-i][y][z].ID = ID13;
								}
								block[x][y][z].corner = 2;
								block[x-2][y][z].corner = 1;
								goto Even_Right_Up;
							}
						}
						if(block[x][y-1][z].flag == 2)
						{
							if(block[x][y-2][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								//�P�~�R�ɂ���
								for(int i(0); i<3; i++){
									block[x][y-i][z].flag = 13;			block[x][y-i][z].ID = ID13;
								}
								block[x][y][z].corner = 2;
								block[x][y-2][z].corner = 1;
								//goto Even_Right_Up;
							}
						}
					}
Even_Right_Up:
					//                                                                                                
					//�E�オ�P�~�P�̏ꍇ
					if(block[x][y+1][z].flag == 1)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						//�P�~�P������ꍇ
						if(block[x-1][y+1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;			block[x][y+1][z].corner = 2;		
							block[x-1][y+1][z].flag = 12;		block[x-1][y+1][z].ID = ID12;		block[x-1][y+1][z].corner = 1;
							goto Even_Left_Down;
						}
						if(block[x][y+2][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;			block[x][y+1][z].corner = 1;
							block[x][y+2][z].flag = 12;		block[x][y+2][z].ID = ID12;			block[x][y+2][z].corner = 2;
							goto Even_Left_Down;
						}
						//�P�~�Q������ꍇ
						if(block[x-1][y+1][z].flag == 2 )
						{
							if(block[x-2][y+1][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								for(int i(0); i<3; i++){
									block[x-i][y+1][z].flag = 13;			block[x-i][y+1][z].ID = ID13;
								}
								block[x][y+1][z].corner = 2;
								block[x-2][y+1][z].corner = 1;
								goto Even_Left_Down;
							}
						}
						if(block[x][y+2][z].flag == 2)
						{
							if(block[x][y+3][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								for(int i(0); i<3; i++){
									block[x][y+i+1][z].flag = 13;			block[x][y+i+1][z].ID = ID13;
								}
								block[x][y+1][z].corner = 1;
								block[x][y+3][z].corner = 2;
								//goto Even_Left_Down;
							}
						}
					}
Even_Left_Down:
					//                                                                                               
					//�������P�~�P�̏ꍇ
					if(block[x+1][y][z].flag == 1)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						//�P�~�P������ꍇ
						if(block[x+1][y-1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 2;
							block[x+1][y-1][z].flag = 12;		block[x+1][y-1][z].ID = ID12;	block[x+1][y-1][z].corner = 1;
							goto Even_Right_Down;
						}
						if(block[x+2][y][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 1;
							block[x+2][y][z].flag = 12;		block[x+2][y][z].ID = ID12;		block[x+2][y][z].corner = 2;
							goto Even_Right_Down;
						}
						//�P�~�Q������ꍇ
						if(block[x+1][y-1][z].flag == 2)
						{
							if(block[x+1][y-2][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								for(int i(0); i<3; i++){
									block[x+1][y-i][z].flag = 13;	block[x+1][y-i][z].ID = ID13;
								}
								block[x+1][y][z].corner = 2;
								block[x+1][y-2][z].corner = 1;
								goto Even_Right_Down;
							}
						}
						if(block[x+2][y][z].flag == 2)
						{
							if(block[x+3][y][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								for(int i(0); i<3; i++){
									block[x+i+1][y][z].flag = 13;			block[x+i+1][y][z].ID = ID13;
								}
								block[x+1][y][z].corner = 1;
								block[x+3][y][z].corner = 2;
								//goto Even_Right_Down;
							}
						}
					}
Even_Right_Down:
					//                                                                                               
					//�E��
					if(block[x+1][y+1][z].flag == 1)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						//�P�~�P������ꍇ
						if(block[x+1][y+2][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x+1][y+1][z].flag = 12;		block[x+1][y+1][z].ID = ID12;		block[x+1][y+1][z].corner = 1;
							block[x+1][y+2][z].flag = 12;		block[x+1][y+2][z].ID = ID12;		block[x+1][y+2][z].corner = 2;
							continue;
						}
						if(block[x+2][y+1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x+1][y+1][z].flag = 12;		block[x+1][y+1][z].ID = ID12;		block[x+1][y+1][z].corner = 1;
							block[x+2][y+1][z].flag = 12;		block[x+2][y+1][z].ID = ID12;		block[x+2][y+1][z].corner = 2;
							continue;
						}
						//�P�~�Q������ꍇ
						if(block[x+1][y+2][z].flag == 2 )
						{
							if(block[x+1][y+3][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								for(int i(0); i<3; i++){
									block[x+1][y+i+1][z].flag = 13;	block[x+1][y+i+1][z].ID = ID13;
								}
								block[x+1][y+1][z].corner = 1;
								block[x+1][y+3][z].corner = 2;
								continue;
							}
						}
						if(block[x+2][y+1][z].flag == 2)
						{
							if(block[x+3][y+1][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								for(int i(0); i<3; i++){
									block[x+i+1][y+1][z].flag = 13;			block[x+i+1][y+1][z].ID = ID13;
								}
								block[x+1][y+1][z].corner = 1;
								block[x+3][y+1][z].corner = 2;
								continue;
							}
						}
					}

				}
			}
		}
	}

	outputFlag("test01_11_12_to_12_13.txt", VoxSize);

}

//�F�̑�����l�����č������邩�ۂ��𔻒f����2013/9/14
void Small_to_Big_step1_color(Lego*** block, int* VoxSize)
{
	for(int z(1); z < VoxSize[2]-1; z++ )
	{
		//��w
		if(z%2)
		{
			for(int x(1); x < VoxSize[0]-1; x=x+2)
			{
				for(int y(1); y < VoxSize[1]-1; y=y+2)
				{
					//                                                                                                
					//���オ�P�~�P�̏ꍇ
					if(block[x][y][z].flag == 1)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						if(block[x-1][y][z].flag == 1)
						{
							//2�̃u���b�N�̐F�������܂��͂ǂ��炩�̃{�N�Z���ɐF�������Ȃ��Ȃ�΍�������
							if(block[x][y][z].ColorID == block[x-1][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x-1][y][z].ColorID<1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
								block[x-1][y][z].flag = 12;		block[x-1][y][z].ID = ID12;	block[x-1][y][z].corner = 1;
								goto Odd_Right_Up;		//continue���g��Ȃ��̂͂S�܂��̒��łP�~�P���Ίp���ő��݂���ꍇ�ɂ���������v�Z����Ȃ�
							}
						}
						if(block[x][y-1][z].flag == 1)
						{
							if(block[x][y][z].ColorID == block[x][y-1][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y-1][z].ColorID<1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								//�P�~�Q�ɂ���
								block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
								block[x][y-1][z].flag = 12;		block[x][y-1][z].ID = ID12;	block[x][y-1][z].corner = 1;
								goto Odd_Right_Up;
							}
						}
						//�P�~�Q������ꍇ
						if(block[x-1][y][z].flag == 2 )
						{
							if(block[x-2][y][z].flag == 2)
							{
								if(block[x][y][z].ColorID == block[x-1][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x-1][y][z].ColorID < 1)
								{
									ID13++;
									num11--;
									num12--;
									num13++;
									//�P�~�R�ɂ���
									for(int i(0); i<3; i++){
										block[x-i][y][z].flag = 13;			block[x-i][y][z].ID = ID13;
									}
									block[x][y][z].corner = 2;
									block[x-2][y][z].corner = 1;
									goto Odd_Right_Up;
								}
							}
						}
						if(block[x][y-1][z].flag == 2 )
						{
							if(block[x][y-2][z].flag == 2)
							{
								if(block[x][y][z].ColorID == block[x][y-1][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y-1][z].ColorID<1)
								{
									ID13++;
									num11--;
									num12--;
									num13++;
									//�P�~�R�ɂ���
									for(int i(0); i<3; i++){
										block[x][y-i][z].flag = 13;			block[x][y-i][z].ID = ID13;
									}
									block[x][y][z].corner = 2;
									block[x][y-2][z].corner = 1;
									//goto Odd_Right_Up;
								}
							}
						}
					}
Odd_Right_Up:
					//                                                                                                
					//�E�オ�P�~�P�̏ꍇ
					if(block[x][y+1][z].flag == 1)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						//�P�~�P������ꍇ
						if(block[x-1][y+1][z].flag == 1)
						{
							if(block[x][y+1][z].ColorID == block[x-1][y+1][z].ColorID || block[x][y+1][z].ColorID < 1 || block[x-1][y+1][z].ColorID<1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;			block[x][y+1][z].corner = 2;		
								block[x-1][y+1][z].flag = 12;		block[x-1][y+1][z].ID = ID12;		block[x-1][y+1][z].corner = 1;
								goto Odd_Left_Down;
							}
						}
						if(block[x][y+2][z].flag == 1)
						{
							if(block[x][y+1][z].ColorID == block[x][y+2][z].ColorID || block[x][y+1][z].ColorID < 1 || block[x][y+2][z].ColorID<1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;			block[x][y+1][z].corner = 1;
								block[x][y+2][z].flag = 12;		block[x][y+2][z].ID = ID12;			block[x][y+2][z].corner = 2;
								goto Odd_Left_Down;
							}
						}
						//�P�~�Q������ꍇ
						if(block[x-1][y+1][z].flag == 2)
						{
							if(block[x-2][y+1][z].flag == 2)
							{
								if(block[x][y+1][z].ColorID == block[x-1][y+1][z].ColorID || block[x][y+1][z].ColorID < 1 || block[x-1][y+1][z].ColorID<1)
								{
									ID13++;
									num11--;
									num12--;
									num13++;

									for(int i(0); i<3; i++){
										block[x-i][y+1][z].flag = 13;			block[x-i][y+1][z].ID = ID13;
									}
									block[x][y+1][z].corner = 2;
									block[x-2][y+1][z].corner = 1;
									goto Odd_Left_Down;
								}
							}
						}
						if(block[x][y+2][z].flag == 2)
						{
							if(block[x][y+3][z].flag == 2)
							{
								if(block[x][y+1][z].ColorID == block[x][y+2][z].ColorID || block[x][y+1][z].ColorID < 1 || block[x][y+2][z].ColorID<1)
								{
									ID13++;
									num11--;
									num12--;
									num13++;
									for(int i(0); i<3; i++){
										block[x][y+i+1][z].flag = 13;			block[x][y+i+1][z].ID = ID13;
									}
									block[x][y+1][z].corner = 1;
									block[x][y+3][z].corner = 2;
									//goto Odd_Left_Down;
								}
							}
						}
					}
Odd_Left_Down:
					//                                                                                               
					//�������P�~�P�̏ꍇ
					if(block[x+1][y][z].flag == 1)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						//�P�~�P������ꍇ
						if(block[x+1][y-1][z].flag == 1)
						{
							if(block[x+1][y][z].ColorID == block[x+1][y-1][z].ColorID || block[x+1][y][z].ColorID < 1 || block[x+1][y-1][z].ColorID < 1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 2;
								block[x+1][y-1][z].flag = 12;		block[x+1][y-1][z].ID = ID12;	block[x+1][y-1][z].corner = 1;
								goto Odd_Right_Down;
							}
						}
						if(block[x+2][y][z].flag == 1)
						{
							if(block[x+1][y][z].ColorID == block[x+2][y][z].ColorID || block[x+1][y][z].ColorID < 1 || block[x+2][y][z].ColorID < 1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 1;
								block[x+2][y][z].flag = 12;		block[x+2][y][z].ID = ID12;		block[x+2][y][z].corner = 2;
								goto Odd_Right_Down;
							}
						}
						//�P�~�Q������ꍇ
						if(block[x+1][y-1][z].flag == 2)
						{
							if(block[x+1][y-2][z].flag == 2)
							{
								if(block[x+1][y][z].ColorID == block[x+1][y-1][z].ColorID || block[x+1][y][z].ColorID < 1 || block[x+1][y-1][z].ColorID < 1)
								{
									ID13++;
									num11--;
									num12--;
									num13++;
									for(int i(0); i<3; i++){
										block[x+1][y-i][z].flag = 13;	block[x+1][y-i][z].ID = ID13;
									}
									block[x+1][y][z].corner = 2;
									block[x+1][y-2][z].corner = 1;
									goto Odd_Right_Down;
								}
							}
						}
						if(block[x+2][y][z].flag == 2 )
						{
							if(block[x+3][y][z].flag == 2)
							{
								if(block[x+1][y][z].ColorID == block[x+2][y][z].ColorID || block[x+1][y][z].ColorID < 1 || block[x+2][y][z].ColorID < 1)
								{
									ID13++;
									num11--;
									num12--;
									num13++;
									for(int i(0); i<3; i++){
										block[x+i+1][y][z].flag = 13;			block[x+i+1][y][z].ID = ID13;
									}
									block[x+1][y][z].corner = 1;
									block[x+3][y][z].corner = 2;
									//goto Odd_Right_Down;
								}
							}
						}
					}
Odd_Right_Down:
					//                                                                                               
					//�E��
					if(block[x+1][y+1][z].flag == 1)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						//�P�~�P������ꍇ
						if(block[x+1][y+2][z].flag == 1)
						{
							if(block[x+1][y+1][z].ColorID == block[x+1][y+2][z].ColorID || block[x+1][y+1][z].ColorID < 1 || block[x+1][y+2][z].ColorID < 1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								block[x+1][y+1][z].flag = 12;		block[x+1][y+1][z].ID = ID12;		block[x+1][y+1][z].corner = 1;
								block[x+1][y+2][z].flag = 12;		block[x+1][y+2][z].ID = ID12;		block[x+1][y+2][z].corner = 2;
								continue;
							}
						}
						if(block[x+2][y+1][z].flag == 1)
						{
							if(block[x+1][y+1][z].ColorID == block[x+2][y+1][z].ColorID || block[x+1][y+1][z].ColorID < 1 || block[x+2][y+1][z].ColorID < 1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								block[x+1][y+1][z].flag = 12;		block[x+1][y+1][z].ID = ID12;		block[x+1][y+1][z].corner = 1;
								block[x+2][y+1][z].flag = 12;		block[x+2][y+1][z].ID = ID12;		block[x+2][y+1][z].corner = 2;
								continue;
							}
						}
						//�P�~�Q������ꍇ
						if(block[x+1][y+2][z].flag == 2 )
						{
							if(block[x+1][y+3][z].flag == 2)
							{
								if(block[x+1][y+1][z].ColorID == block[x+1][y+2][z].ColorID || block[x+1][y+1][z].ColorID < 1 || block[x+1][y+2][z].ColorID < 1)
								{
									ID13++;
									num11--;
									num12--;
									num13++;
									for(int i(0); i<3; i++){
										block[x+1][y+i+1][z].flag = 13;	block[x+1][y+i+1][z].ID = ID13;
									}
									block[x+1][y+1][z].corner = 1;
									block[x+1][y+3][z].corner = 2;
									continue;
								}
							}
						}
						if(block[x+2][y+1][z].flag == 2 )
						{
							if(block[x+3][y+1][z].flag == 2)
							{
								if(block[x+1][y+1][z].ColorID == block[x+2][y+1][z].ColorID || block[x+1][y+1][z].ColorID < 1 || block[x+2][y+1][z].ColorID < 1)
								{
									ID13++;
									num11--;
									num12--;
									num13++;
									for(int i(0); i<3; i++){
										block[x+i+1][y+1][z].flag = 13;			block[x+i+1][y+1][z].ID = ID13;
									}
									block[x+1][y+1][z].corner = 1;
									block[x+3][y+1][z].corner = 2;
									continue;
								}
							}
						}
					}

				}
			}
		}

		//�����w
		else
		{
			for(int x(0); x < VoxSize[0]-1; x=x+2)
			{
				for(int y(0); y < VoxSize[1]-1; y=y+2)
				{

					//                                                                                                
					//���オ�P�~�P�̏ꍇ
					if(block[x][y][z].flag == 1)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						if(block[x-1][y][z].flag == 1)
						{
							//2�̃u���b�N�̐F�������܂��͂ǂ��炩�̃{�N�Z���ɐF�������Ȃ��Ȃ�΍�������
							if(block[x][y][z].ColorID == block[x-1][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x-1][y][z].ColorID<1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
								block[x-1][y][z].flag = 12;		block[x-1][y][z].ID = ID12;	block[x-1][y][z].corner = 1;
								goto Even_Right_Up;		//continue���g��Ȃ��̂͂S�܂��̒��łP�~�P���Ίp���ő��݂���ꍇ�ɂ���������v�Z����Ȃ�
							}
						}
						if(block[x][y-1][z].flag == 1)
						{
							if(block[x][y][z].ColorID == block[x][y-1][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y-1][z].ColorID<1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								//�P�~�Q�ɂ���
								block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
								block[x][y-1][z].flag = 12;		block[x][y-1][z].ID = ID12;	block[x][y-1][z].corner = 1;
								goto Even_Right_Up;
							}
						}
						//�P�~�Q������ꍇ
						if(block[x-1][y][z].flag == 2 )
						{
							if(block[x-2][y][z].flag == 2)
							{
								if(block[x][y][z].ColorID == block[x-1][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x-1][y][z].ColorID < 1)
								{
									ID13++;
									num11--;
									num12--;
									num13++;
									//�P�~�R�ɂ���
									for(int i(0); i<3; i++){
										block[x-i][y][z].flag = 13;			block[x-i][y][z].ID = ID13;
									}
									block[x][y][z].corner = 2;
									block[x-2][y][z].corner = 1;
									goto Even_Right_Up;
								}
							}
						}
						if(block[x][y-1][z].flag == 2 )
						{
							if(block[x][y-2][z].flag == 2)
							{
								if(block[x][y][z].ColorID == block[x][y-1][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y-1][z].ColorID<1)
								{
									ID13++;
									num11--;
									num12--;
									num13++;
									//�P�~�R�ɂ���
									for(int i(0); i<3; i++){
										block[x][y-i][z].flag = 13;			block[x][y-i][z].ID = ID13;
									}
									block[x][y][z].corner = 2;
									block[x][y-2][z].corner = 1;
									//goto Odd_Right_Up;
								}
							}
						}
					}
Even_Right_Up:
					//                                                                                                
					//�E�オ�P�~�P�̏ꍇ
					if(block[x][y+1][z].flag == 1)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						//�P�~�P������ꍇ
						if(block[x-1][y+1][z].flag == 1)
						{
							if(block[x][y+1][z].ColorID == block[x-1][y+1][z].ColorID || block[x][y+1][z].ColorID < 1 || block[x-1][y+1][z].ColorID<1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;			block[x][y+1][z].corner = 2;		
								block[x-1][y+1][z].flag = 12;		block[x-1][y+1][z].ID = ID12;		block[x-1][y+1][z].corner = 1;
								goto Even_Left_Down;
							}
						}
						if(block[x][y+2][z].flag == 1)
						{
							if(block[x][y+1][z].ColorID == block[x][y+2][z].ColorID || block[x][y+1][z].ColorID < 1 || block[x][y+2][z].ColorID<1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;			block[x][y+1][z].corner = 1;
								block[x][y+2][z].flag = 12;		block[x][y+2][z].ID = ID12;			block[x][y+2][z].corner = 2;
								goto Even_Left_Down;
							}
						}
						//�P�~�Q������ꍇ
						if(block[x-1][y+1][z].flag == 2)
						{
							if(block[x-2][y+1][z].flag == 2)
							{
								if(block[x][y+1][z].ColorID == block[x-1][y+1][z].ColorID || block[x][y+1][z].ColorID < 1 || block[x-1][y+1][z].ColorID<1)
								{
									ID13++;
									num11--;
									num12--;
									num13++;

									for(int i(0); i<3; i++){
										block[x-i][y+1][z].flag = 13;			block[x-i][y+1][z].ID = ID13;
									}
									block[x][y+1][z].corner = 2;
									block[x-2][y+1][z].corner = 1;
									goto Even_Left_Down;
								}
							}
						}
						if(block[x][y+2][z].flag == 2)
						{
							if(block[x][y+3][z].flag == 2)
							{
								if(block[x][y+1][z].ColorID == block[x][y+2][z].ColorID || block[x][y+1][z].ColorID < 1 || block[x][y+2][z].ColorID<1)
								{
									ID13++;
									num11--;
									num12--;
									num13++;
									for(int i(0); i<3; i++){
										block[x][y+i+1][z].flag = 13;			block[x][y+i+1][z].ID = ID13;
									}
									block[x][y+1][z].corner = 1;
									block[x][y+3][z].corner = 2;
									//goto Odd_Left_Down;
								}
							}
						}
					}
Even_Left_Down:
					//                                                                                               
					//�������P�~�P�̏ꍇ
					if(block[x+1][y][z].flag == 1)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						//�P�~�P������ꍇ
						if(block[x+1][y-1][z].flag == 1)
						{
							if(block[x+1][y][z].ColorID == block[x+1][y-1][z].ColorID || block[x+1][y][z].ColorID < 1 || block[x+1][y-1][z].ColorID < 1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 2;
								block[x+1][y-1][z].flag = 12;		block[x+1][y-1][z].ID = ID12;	block[x+1][y-1][z].corner = 1;
								goto Enen_Right_Down;
							}
						}
						if(block[x+2][y][z].flag == 1)
						{
							if(block[x+1][y][z].ColorID == block[x+2][y][z].ColorID || block[x+1][y][z].ColorID < 1 || block[x+2][y][z].ColorID < 1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 1;
								block[x+2][y][z].flag = 12;		block[x+2][y][z].ID = ID12;		block[x+2][y][z].corner = 2;
								goto Enen_Right_Down;
							}
						}
						//�P�~�Q������ꍇ
						if(block[x+1][y-1][z].flag == 2)
						{
							if(block[x+1][y-2][z].flag == 2)
							{
								if(block[x+1][y][z].ColorID == block[x+1][y-1][z].ColorID || block[x+1][y][z].ColorID < 1 || block[x+1][y-1][z].ColorID < 1)
								{
									ID13++;
									num11--;
									num12--;
									num13++;
									for(int i(0); i<3; i++){
										block[x+1][y-i][z].flag = 13;	block[x+1][y-i][z].ID = ID13;
									}
									block[x+1][y][z].corner = 2;
									block[x+1][y-2][z].corner = 1;
									goto Enen_Right_Down;
								}
							}
						}
						if(block[x+2][y][z].flag == 2 )
						{
							if(block[x+3][y][z].flag == 2)
							{
								if(block[x+1][y][z].ColorID == block[x+2][y][z].ColorID || block[x+1][y][z].ColorID < 1 || block[x+2][y][z].ColorID < 1)
								{
									ID13++;
									num11--;
									num12--;
									num13++;
									for(int i(0); i<3; i++){
										block[x+i+1][y][z].flag = 13;			block[x+i+1][y][z].ID = ID13;
									}
									block[x+1][y][z].corner = 1;
									block[x+3][y][z].corner = 2;
									//goto Odd_Right_Down;
								}
							}
						}
					}
Enen_Right_Down:
					//                                                                                               
					//�E��
					if(block[x+1][y+1][z].flag == 1)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						//�P�~�P������ꍇ
						if(block[x+1][y+2][z].flag == 1)
						{
							if(block[x+1][y+1][z].ColorID == block[x+1][y+2][z].ColorID || block[x+1][y+1][z].ColorID < 1 || block[x+1][y+2][z].ColorID < 1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								block[x+1][y+1][z].flag = 12;		block[x+1][y+1][z].ID = ID12;		block[x+1][y+1][z].corner = 1;
								block[x+1][y+2][z].flag = 12;		block[x+1][y+2][z].ID = ID12;		block[x+1][y+2][z].corner = 2;
								continue;
							}
						}
						if(block[x+2][y+1][z].flag == 1)
						{
							if(block[x+1][y+1][z].ColorID == block[x+2][y+1][z].ColorID || block[x+1][y+1][z].ColorID < 1 || block[x+2][y+1][z].ColorID < 1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								block[x+1][y+1][z].flag = 12;		block[x+1][y+1][z].ID = ID12;		block[x+1][y+1][z].corner = 1;
								block[x+2][y+1][z].flag = 12;		block[x+2][y+1][z].ID = ID12;		block[x+2][y+1][z].corner = 2;
								continue;
							}
						}
						//�P�~�Q������ꍇ
						if(block[x+1][y+2][z].flag == 2 )
						{
							if(block[x+1][y+3][z].flag == 2)
							{
								if(block[x+1][y+1][z].ColorID == block[x+1][y+2][z].ColorID || block[x+1][y+1][z].ColorID < 1 || block[x+1][y+2][z].ColorID < 1)
								{
									ID13++;
									num11--;
									num12--;
									num13++;
									for(int i(0); i<3; i++){
										block[x+1][y+i+1][z].flag = 13;	block[x+1][y+i+1][z].ID = ID13;
									}
									block[x+1][y+1][z].corner = 1;
									block[x+1][y+3][z].corner = 2;
									continue;
								}
							}
						}
						if(block[x+2][y+1][z].flag == 2 )
						{
							if(block[x+3][y+1][z].flag == 2)
							{
								if(block[x+1][y+1][z].ColorID == block[x+2][y+1][z].ColorID || block[x+1][y+1][z].ColorID < 1 || block[x+2][y+1][z].ColorID < 1)
								{
									ID13++;
									num11--;
									num12--;
									num13++;
									for(int i(0); i<3; i++){
										block[x+i+1][y+1][z].flag = 13;			block[x+i+1][y+1][z].ID = ID13;
									}
									block[x+1][y+1][z].corner = 1;
									block[x+3][y+1][z].corner = 2;
									continue;
								}
							}
						}
					}

				}
			}
		}
	}

	//outputFlag("test01_11_12_to_12_13.txt", VoxSize);

}

//�Ǘ����Ă���P�~�P���ɂق��̃s�[�X�Ƃ�������֐�
void Small_to_Big_before_step1(Lego*** block, int* VoxSize)
{
	int count(0);		//�Ǘ���������1�~�P�̐�
	int x,y,z;
	for(z=1; z < VoxSize[2]-1; z++ )
	{
		//��w
		if(z%2)
		{
			for(x=1; x < VoxSize[0]-1; x=x+2)
			{
				for(y=1; y < VoxSize[1]-1; y=y+2)
				{


					//                                                                                                
					//���オ�P�~�P�̏ꍇ���Ǘ��������ȏꍇ
					if(block[x][y][z].flag == 1 && block[x][y][z-1].flag < 2 && block[x][y][z+1].flag < 2)		
					{

						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						if(block[x-1][y][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x-1][y][z].flag = 12;		block[x-1][y][z].ID = ID12;	block[x-1][y][z].corner = 1;
							goto Odd_Right_Up;		//continue���g��Ȃ��̂͂S�܂��̒��łP�~�P���Ίp���ő��݂���ꍇ�ɂ���������v�Z����Ȃ�
							//continue;
						}
						if(block[x][y-1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							//�P�~�Q�ɂ���
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x][y-1][z].flag = 12;		block[x][y-1][z].ID = ID12;	block[x][y-1][z].corner = 1;
							goto Odd_Right_Up;
						}
						//�P�~�Q������ꍇ
						if(block[x-1][y][z].flag == 2)
						{
							if(block[x-2][y][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								count++;
								//�P�~�R�ɂ���
								for(int i(0); i<3; i++){
									block[x-i][y][z].flag = 13;			block[x-i][y][z].ID = ID13;
								}
								block[x][y][z].corner = 2;
								block[x-2][y][z].corner = 1;
								goto Odd_Right_Up;
							}
						}
						if(block[x][y-1][z].flag == 2 )
						{
							if(block[x][y-2][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								//�P�~�R�ɂ���
								count++;
								for(int i(0); i<3; i++){
									block[x][y-i][z].flag = 13;			block[x][y-i][z].ID = ID13;
								}
								block[x][y][z].corner = 2;
								block[x][y-2][z].corner = 1;
								//goto Odd_Right_Up;
							}
						}
					}
Odd_Right_Up:
					//                                                                                                
					//�E�オ�P�~�P�̏ꍇ
					if(block[x][y+1][z].flag == 1 && block[x][y+1][z-1].flag < 2 && block[x][y+1][z+1].flag < 2)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						//�P�~�P������ꍇ
						if(block[x-1][y+1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;			block[x][y+1][z].corner = 2;		
							block[x-1][y+1][z].flag = 12;		block[x-1][y+1][z].ID = ID12;		block[x-1][y+1][z].corner = 1;
							goto Odd_Left_Down;
						}
						if(block[x][y+2][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;			block[x][y+1][z].corner = 1;
							block[x][y+2][z].flag = 12;		block[x][y+2][z].ID = ID12;			block[x][y+2][z].corner = 2;
							goto Odd_Left_Down;
						}
						//�P�~�Q������ꍇ
						if(block[x-1][y+1][z].flag == 2)
						{
							if(block[x-2][y+1][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								count++;
								for(int i(0); i<3; i++){
									block[x-i][y+1][z].flag = 13;			block[x-i][y+1][z].ID = ID13;
								}
								block[x][y+1][z].corner = 2;
								block[x-2][y+1][z].corner = 1;
								goto Odd_Left_Down;
							}
						}
						if(block[x][y+2][z].flag == 2 )
						{
							if(block[x][y+3][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								count++;
								for(int i(0); i<3; i++){
									block[x][y+i+1][z].flag = 13;			block[x][y+i+1][z].ID = ID13;
								}
								block[x][y+1][z].corner = 1;
								block[x][y+3][z].corner = 2;
								//goto Odd_Left_Down;
							}
						}
					}
Odd_Left_Down:
					//                                                                                               
					//�������P�~�P�̏ꍇ
					if(block[x+1][y][z].flag == 1 && block[x+1][y][z-1].flag < 2 && block[x+1][y][z+1].flag < 2)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						//�P�~�P������ꍇ
						if(block[x+1][y-1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 2;
							block[x+1][y-1][z].flag = 12;		block[x+1][y-1][z].ID = ID12;	block[x+1][y-1][z].corner = 1;
							goto Odd_Right_Down;
						}
						if(block[x+2][y][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 1;
							block[x+2][y][z].flag = 12;		block[x+2][y][z].ID = ID12;		block[x+2][y][z].corner = 2;
							goto Odd_Right_Down;
						}
						//�P�~�Q������ꍇ
						if(block[x+1][y-1][z].flag == 2 )
						{
							if(block[x+1][y-2][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								count++;
								for(int i(0); i<3; i++){
									block[x+1][y-i][z].flag = 13;	block[x+1][y-i][z].ID = ID13;
								}
								block[x+1][y][z].corner = 2;
								block[x+1][y-2][z].corner = 1;
								goto Odd_Right_Down;
							}
						}
						if(block[x+2][y][z].flag == 2)
						{
							if(block[x+3][y][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								count++;
								for(int i(0); i<3; i++){
									block[x+i+1][y][z].flag = 13;			block[x+i+1][y][z].ID = ID13;
								}
								block[x+1][y][z].corner = 1;
								block[x+3][y][z].corner = 2;
								//goto Odd_Right_Down;
							}
						}
					}
Odd_Right_Down:
					//                                                                                               
					//�E��
					if(block[x+1][y+1][z].flag == 1 && block[x+1][y+1][z-1].flag < 2 && block[x+1][y+1][z+1].flag < 2)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						//�P�~�P������ꍇ
						if(block[x+1][y+2][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							block[x+1][y+1][z].flag = 12;		block[x+1][y+1][z].ID = ID12;		block[x+1][y+1][z].corner = 1;
							block[x+1][y+2][z].flag = 12;		block[x+1][y+2][z].ID = ID12;		block[x+1][y+2][z].corner = 2;
							continue;
						}
						if(block[x+2][y+1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							block[x+1][y+1][z].flag = 12;		block[x+1][y+1][z].ID = ID12;		block[x+1][y+1][z].corner = 1;
							block[x+2][y+1][z].flag = 12;		block[x+2][y+1][z].ID = ID12;		block[x+2][y+1][z].corner = 2;
							continue;
						}
						//�P�~�Q������ꍇ
						if(block[x+1][y+2][z].flag == 2 )
						{
							if(block[x+1][y+3][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								count++;
								for(int i(0); i<3; i++){
									block[x+1][y+i+1][z].flag = 13;	block[x+1][y+i+1][z].ID = ID13;
								}
								block[x+1][y+1][z].corner = 1;
								block[x+1][y+3][z].corner = 2;
								continue;
							}
						}
						if(block[x+2][y+1][z].flag == 2)
						{
							if(block[x+3][y+1][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								count++;
								for(int i(0); i<3; i++){
									block[x+i+1][y+1][z].flag = 13;			block[x+i+1][y+1][z].ID = ID13;
								}
								block[x+1][y+1][z].corner = 1;
								block[x+3][y+1][z].corner = 2;
								continue;
							}
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
					//                                                                                                
					//���オ�P�~�P�̏ꍇ
					if(block[x][y][z].flag == 1 && block[x][y][z-1].flag < 2 && block[x][y][z+1].flag < 2)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						if(block[x-1][y][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x-1][y][z].flag = 12;		block[x-1][y][z].ID = ID12;	block[x-1][y][z].corner = 1;
							goto Even_Right_Up;		//continue���g��Ȃ��̂͂S�܂��̒��łP�~�P���Ίp���ő��݂���ꍇ�ɂ���������v�Z����Ȃ�
							//continue;
						}
						if(block[x][y-1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							//�P�~�Q�ɂ���
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x][y-1][z].flag = 12;		block[x][y-1][z].ID = ID12;	block[x][y-1][z].corner = 1;
							goto Even_Right_Up;
						}
						//�P�~�Q������ꍇ
						if(block[x-1][y][z].flag == 2 )
						{
							if(block[x-2][y][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								count++;
								//�P�~�R�ɂ���
								for(int i(0); i<3; i++){
									block[x-i][y][z].flag = 13;			block[x-i][y][z].ID = ID13;
								}
								block[x][y][z].corner = 2;
								block[x-2][y][z].corner = 1;
								goto Even_Right_Up;
							}
						}
						if(block[x][y-1][z].flag == 2)
						{
							if(block[x][y-2][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								count++;
								//�P�~�R�ɂ���
								for(int i(0); i<3; i++){
									block[x][y-i][z].flag = 13;			block[x][y-i][z].ID = ID13;
								}
								block[x][y][z].corner = 2;
								block[x][y-2][z].corner = 1;
								//goto Even_Right_Up;
							}
						}
					}
Even_Right_Up:
					//                                                                                                
					//�E�オ�P�~�P�̏ꍇ
					if(block[x][y+1][z].flag == 1 && block[x][y+1][z-1].flag < 2 && block[x][y+1][z+1].flag < 2)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						//�P�~�P������ꍇ
						if(block[x-1][y+1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;			block[x][y+1][z].corner = 2;		
							block[x-1][y+1][z].flag = 12;		block[x-1][y+1][z].ID = ID12;		block[x-1][y+1][z].corner = 1;
							goto Even_Left_Down;
						}
						if(block[x][y+2][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;			block[x][y+1][z].corner = 1;
							block[x][y+2][z].flag = 12;		block[x][y+2][z].ID = ID12;			block[x][y+2][z].corner = 2;
							goto Even_Left_Down;
						}
						//�P�~�Q������ꍇ
						if(block[x-1][y+1][z].flag == 2)
						{
							if(block[x-2][y+1][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								count++;
								for(int i(0); i<3; i++){
									block[x-i][y+1][z].flag = 13;			block[x-i][y+1][z].ID = ID13;
								}
								block[x][y+1][z].corner = 2;
								block[x-2][y+1][z].corner = 1;
								goto Even_Left_Down;
							}
						}
						if(block[x][y+2][z].flag == 2)
						{
							if(block[x][y+3][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								count++;
								for(int i(0); i<3; i++){
									block[x][y+i+1][z].flag = 13;			block[x][y+i+1][z].ID = ID13;
								}
								block[x][y+1][z].corner = 1;
								block[x][y+3][z].corner = 2;
								//goto Even_Left_Down;
							}
						}
					}
Even_Left_Down:
					//                                                                                               
					//�������P�~�P�̏ꍇ
					if(block[x+1][y][z].flag == 1 && block[x+1][y][z-1].flag < 2 && block[x+1][y][z+1].flag < 2)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						//�P�~�P������ꍇ
						if(block[x+1][y-1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 2;
							block[x+1][y-1][z].flag = 12;		block[x+1][y-1][z].ID = ID12;	block[x+1][y-1][z].corner = 1;
							goto Even_Right_Down;
						}
						if(block[x+2][y][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 1;
							block[x+2][y][z].flag = 12;		block[x+2][y][z].ID = ID12;		block[x+2][y][z].corner = 2;
							goto Even_Right_Down;
						}
						//�P�~�Q������ꍇ
						if(block[x+1][y-1][z].flag == 2)
						{
							if(block[x+1][y-2][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								count++;
								for(int i(0); i<3; i++){
									block[x+1][y-i][z].flag = 13;	block[x+1][y-i][z].ID = ID13;
								}
								block[x+1][y][z].corner = 2;
								block[x+1][y-2][z].corner = 1;
								goto Even_Right_Down;
							}
						}
						if(block[x+2][y][z].flag == 2)
						{
							if(block[x+3][y][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								count++;
								for(int i(0); i<3; i++){
									block[x+i+1][y][z].flag = 13;			block[x+i+1][y][z].ID = ID13;
								}
								block[x+1][y][z].corner = 1;
								block[x+3][y][z].corner = 2;
								//goto Even_Right_Down;
							}
						}
					}
Even_Right_Down:
					//                                                                                               
					//�E��
					if(block[x+1][y+1][z].flag == 1 && block[x+1][y+1][z-1].flag < 2 && block[x+1][y+1][z+1].flag < 2)		
					{
						//��قǗD�揇�ʂ������@���قǗD�揇�ʂ��Ⴂ
						//�P�~�P������ꍇ
						if(block[x+1][y+2][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							block[x+1][y+1][z].flag = 12;		block[x+1][y+1][z].ID = ID12;		block[x+1][y+1][z].corner = 1;
							block[x+1][y+2][z].flag = 12;		block[x+1][y+2][z].ID = ID12;		block[x+1][y+2][z].corner = 2;
							continue;
						}
						if(block[x+2][y+1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							block[x+1][y+1][z].flag = 12;		block[x+1][y+1][z].ID = ID12;		block[x+1][y+1][z].corner = 1;
							block[x+2][y+1][z].flag = 12;		block[x+2][y+1][z].ID = ID12;		block[x+2][y+1][z].corner = 2;
							continue;
						}
						//�P�~�Q������ꍇ
						if(block[x+1][y+2][z].flag == 2 )
						{
							if(block[x+1][y+3][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								count++;
								for(int i(0); i<3; i++){
									block[x+1][y+i+1][z].flag = 13;	block[x+1][y+i+1][z].ID = ID13;
								}
								block[x+1][y+1][z].corner = 1;
								block[x+1][y+3][z].corner = 2;
								continue;
							}
						}
						if(block[x+2][y+1][z].flag == 2)
						{
							if(block[x+3][y+1][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								count++;
								for(int i(0); i<3; i++){
									block[x+i+1][y+1][z].flag = 13;			block[x+i+1][y+1][z].ID = ID13;
								}
								block[x+1][y+1][z].corner = 1;
								block[x+3][y+1][z].corner = 2;
							}
						}
					}
				}
			}
		}
	}

	cout<<"count: "<<count<<" "<<endl;

	//outputFlag("test01_11_12_to_12_13_before.txt", VoxSize);

}

void Small_to_Big_step1_color_new(Lego*** block, int* VoxSize){

	for(int z(1); z < VoxSize[2]-1; z++ )
	{
		//��w�Ƌ����w�𕪂���
		if(z%2)
		for(int x(1); x < VoxSize[0]-1; x=x+1)
		{
		if(x%2)
			for(int y(1); y < VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag==1){

					if(block[x-1][y][z].flag==1){

						if(block[x][y][z].ColorID<1||block[x-1][y][z].ColorID<1||block[x-1][y][z].ColorID==block[x][y][z].ColorID){
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x-1][y][z].flag = 12;		block[x-1][y][z].ID = ID12;	block[x-1][y][z].corner = 1;
							continue;
						}
					}

				 if(block[x][y-1][z].flag==1){

						if(block[x][y][z].ColorID<1||block[x][y-1][z].ColorID<1||block[x][y-1][z].ColorID==block[x][y][z].ColorID){

							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x][y-1][z].flag = 12;		block[x][y-1][z].ID = ID12;	block[x][y-1][z].corner = 1;
							continue;
						}
					}

				 if(block[x+1][y][z].flag==1){

						if(block[x][y][z].ColorID<1||block[x+1][y][z].ColorID<1||block[x+1][y][z].ColorID==block[x][y][z].ColorID){

							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 1;
							block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;	block[x+1][y][z].corner = 2;
							continue;
						}
					}

					if(block[x][y+1][z].flag==1){

						if(block[x][y][z].ColorID<1||block[x][y+1][z].ColorID<1||block[x][y+1][z].ColorID==block[x][y][z].ColorID){

							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 1;
							block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;	block[x][y+1][z].corner = 2;
							continue;
						}
					}
				}
			}
		if(!(x%2))
			for(int y(0); y < VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag==1){

					if(block[x-1][y][z].flag==1){

						if(block[x][y][z].ColorID<1||block[x-1][y][z].ColorID<1||block[x-1][y][z].ColorID==block[x][y][z].ColorID){
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x-1][y][z].flag = 12;		block[x-1][y][z].ID = ID12;	block[x-1][y][z].corner = 1;
							continue;
						}
					}

				 if(block[x][y-1][z].flag==1){

						if(block[x][y][z].ColorID<1||block[x][y-1][z].ColorID<1||block[x][y-1][z].ColorID==block[x][y][z].ColorID){

							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x][y-1][z].flag = 12;		block[x][y-1][z].ID = ID12;	block[x][y-1][z].corner = 1;
							continue;
						}
					}

				 if(block[x+1][y][z].flag==1){

						if(block[x][y][z].ColorID<1||block[x+1][y][z].ColorID<1||block[x+1][y][z].ColorID==block[x][y][z].ColorID){

							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 1;
							block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;	block[x+1][y][z].corner = 2;
							continue;
						}
					}

					if(block[x][y+1][z].flag==1){

						if(block[x][y][z].ColorID<1||block[x][y+1][z].ColorID<1||block[x][y+1][z].ColorID==block[x][y][z].ColorID){

							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 1;
							block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;	block[x][y+1][z].corner = 2;
							continue;
						}
					}
				}
			}
		}
		//��w�Ƌ����w�𕪂���
		if(!(z%2))
		for(int x(0); x < VoxSize[0]-1; x=x+1)
		{
			if(x%2)
			for(int y(0); y < VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag==1){

					if(block[x-1][y][z].flag==1){

						if(block[x][y][z].ColorID<1||block[x-1][y][z].ColorID<1||block[x-1][y][z].ColorID==block[x][y][z].ColorID){
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x-1][y][z].flag = 12;		block[x-1][y][z].ID = ID12;	block[x-1][y][z].corner = 1;
							continue;
						}
					}

				 if(block[x][y-1][z].flag==1){

						if(block[x][y][z].ColorID<1||block[x][y-1][z].ColorID<1||block[x][y-1][z].ColorID==block[x][y][z].ColorID){

							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x][y-1][z].flag = 12;		block[x][y-1][z].ID = ID12;	block[x][y-1][z].corner = 1;
							continue;
						}
					}

				 if(block[x+1][y][z].flag==1){

						if(block[x][y][z].ColorID<1||block[x+1][y][z].ColorID<1||block[x+1][y][z].ColorID==block[x][y][z].ColorID){

							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 1;
							block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;	block[x+1][y][z].corner = 2;
							continue;
						}
					}

					if(block[x][y+1][z].flag==1){

						if(block[x][y][z].ColorID<1||block[x][y+1][z].ColorID<1||block[x][y+1][z].ColorID==block[x][y][z].ColorID){

							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 1;
							block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;	block[x][y+1][z].corner = 2;
							continue;
						}
					}
				}
			}
		if(!(x%2))
			for(int y(1); y < VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag==1){

					if(block[x-1][y][z].flag==1){

						if(block[x][y][z].ColorID<1||block[x-1][y][z].ColorID<1||block[x-1][y][z].ColorID==block[x][y][z].ColorID){
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x-1][y][z].flag = 12;		block[x-1][y][z].ID = ID12;	block[x-1][y][z].corner = 1;
							continue;
						}
					}

				 if(block[x][y-1][z].flag==1){

						if(block[x][y][z].ColorID<1||block[x][y-1][z].ColorID<1||block[x][y-1][z].ColorID==block[x][y][z].ColorID){

							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x][y-1][z].flag = 12;		block[x][y-1][z].ID = ID12;	block[x][y-1][z].corner = 1;
							continue;
						}
					}

				 if(block[x+1][y][z].flag==1){

						if(block[x][y][z].ColorID<1||block[x+1][y][z].ColorID<1||block[x+1][y][z].ColorID==block[x][y][z].ColorID){

							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 1;
							block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;	block[x+1][y][z].corner = 2;
							continue;
						}
					}

					if(block[x][y+1][z].flag==1){

						if(block[x][y][z].ColorID<1||block[x][y+1][z].ColorID<1||block[x][y+1][z].ColorID==block[x][y][z].ColorID){

							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 1;
							block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;	block[x][y+1][z].corner = 2;
							continue;
						}
					}
				}
			}
		}

	}
}