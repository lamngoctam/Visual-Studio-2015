#include "../stdafx.h"
#include "../Voxel.h"
#include "../Lego.h"		//LEGO�u���b�N��g�ݗ��Ă邽�߂̃N���X

void outputFlag(string filename, int* size);

extern int num11;		//�P�~�P�̃u���b�N�̐�
extern int num12;		//�P�~�Q�̃u���b�N�̐�
extern int num22;		//�Q�~�Q�̃u���b�N�̐�

extern int ID12;	
extern int ID22;	

//L����1�~�P�@�Ɓ@�P�~�Q�ɒu��������
void Small_to_Big_step0( Lego*** block, int* VoxSize)
{
	int Left_Up(0);
	int Left_Down(0);
	int Right_Up(0);
	int Right_Down(0);

	int count(0);		//L�����P�~�P�ƂP�~�Q�ɕ����ł��Ȃ�������
	int countLN(0);
	int x,y,z;
	//��w
	for(z=1; z < VoxSize[2]-1; z++ )
	{
		if(z%2)
		{
			for(x=1; x < VoxSize[0]-1; x=x+2)
			{
				for(y=1; y < VoxSize[1]-1; y=y+2)
				{
					//���ڃ{�N�Z����ID���R�ɂȂ�ꍇ
					if(block[x][y][z].flag == 3)
					{
						//                                                                                                                                
						//�P�[�X�Q
						if(block[x][y+1][z].flag == 0)
						{
							countLN++;
							//����̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							if( (block[x][y][z-1].flag > 3 || block[x][y][z+1].flag > 3) &&  block[x+1][y+1][z-1].flag < 4 && block[x+1][y+1][z+1].flag < 4 )
							{
								block[x][y][z].flag = 1;
								block[x+1][y][z].flag = 2; 
								block[x+1][y+1][z].flag = 2;
								num11++;
								num12++;
							}
							//��������̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							else if( block[x][y][z-1].flag < 4 && block[x][y][z+1].flag < 4 && ( block[x+1][y+1][z-1].flag > 3 || block[x+1][y+1][z+1].flag > 3))
							{
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 2; 
								block[x+1][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//���ڂ̂Q�̃{�N�Z���̏㉺�i�S�j�Ƃ��ɂP�~�P�ȉ��̃{�N�Z���ł���Ƃ�
							else if(block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2)
							{
								count++;
								num22++;
								//�Q�~�Q�ɖ������ς��܂�������`
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x][y+1][z].fill = true;
								cout<<"�����ł��Ȃ���������2�~2�ɕς������I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//��L�ȊO�̎���
							else
							{
								//��Ɖ��̃{�N�Z���̃t���O�̒l�������đ傫�����𕪊�����
								Left_Up = (block[x][y][z-1].flag) * (block[x][y][z+1].flag);
								Right_Down =  (block[x+1][y+1][z-1].flag) * (block[x+1][y+1][z+1].flag);
								if(Left_Up > Right_Down)
								{
									block[x][y][z].flag = 1;
									block[x+1][y][z].flag = 2; 
									block[x+1][y+1][z].flag = 2; 
									num11++;
									num12++;
								}
								else
								{
									block[x][y][z].flag = 2;
									block[x+1][y][z].flag = 2; 
									block[x+1][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
						//						                                                                                                                                
						//�P�[�X�R
						else if(block[x+1][y+1][z].flag == 0)
						{
							countLN++;
							//����̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							if( (block[x+1][y][z-1].flag >3  ||  block[x+1][y][z+1].flag > 3) && block[x][y+1][z-1].flag < 4 &&  block[x][y+1][z+1].flag < 4 )
							{
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 1; 
								block[x][y+1][z].flag = 2; 
								num11++;
								num12++;
							}
							//��������̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							else if( block[x+1][y][z-1].flag < 4  &&  block[x+1][y][z+1].flag < 4 && (block[x][y+1][z-1].flag > 3 &&  block[x][y+1][z+1].flag > 3) )
							{
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 2; 
								block[x][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//���ڂ̂Q�̃{�N�Z���̏㉺�i�S�j�Ƃ��ɂP�~�P�ȉ��̃{�N�Z���ł���Ƃ�
							else if(block[x+1][y][z-1].flag < 2 &&  block[x+1][y][z+1].flag < 2 && block[x][y+1][z-1].flag < 2 &&  block[x][y+1][z+1].flag < 2 )
							{
								count++;
								num22++;
								//�Q�~�Q�ɖ������ς��܂�������`
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x+1][y+1][z].fill = true;
								cout<<"�����ł��Ȃ���������2�~2�ɕς������I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//��L�ȊO�̎���
							else
							{
								Left_Down = (block[x+1][y][z-1].flag) * (block[x+1][y][z+1].flag);
								Right_Up =  (block[x][y+1][z-1].flag) * (block[x][y+1][z+1].flag);
								if(Left_Down > Right_Up)
								{
									block[x][y][z].flag = 2;
									block[x+1][y][z].flag = 1; 
									block[x][y+1][z].flag = 2; 
									num11++;
									num12++;
								}
								else
								{
									block[x][y][z].flag = 2;
									block[x+1][y][z].flag = 2; 
									block[x][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
						//                                                                                                     
						//�P�[�X�S
						else if(block[x+1][y][z].flag == 0)
						{
							countLN++;
							//����̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							if( (block[x][y][z-1].flag > 3 ||  block[x][y][z+1].flag > 3) && block[x+1][y+1][z-1].flag < 4 &&  block[x+1][y+1][z+1].flag < 4 )
							{
								block[x][y][z].flag = 1;
								block[x][y+1][z].flag = 2; 
								block[x+1][y+1][z].flag = 2; 
								num11++;
								num12++;
							}
							//��������̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							else if( block[x][y][z-1].flag < 4 &&  block[x][y][z+1].flag < 4 && (block[x+1][y+1][z-1].flag > 3 ||  block[x+1][y+1][z+1].flag > 3) )
							{
								block[x][y][z].flag = 2;
								block[x][y+1][z].flag = 2; 
								block[x+1][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//���ڃ{�N�Z���̏㉺4�Ƃ��ɂP�~�P�܂��͉����Ȃ��ꍇ
							else if( block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2 )
							{
								count++;
								num22++;
								//�Q�~�Q�ɖ������ς��܂�������`
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x+1][y][z].fill = true;
								cout<<"�����ł��Ȃ���������2�~2�ɕς������I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//��L�ȊO�̏ꍇ
							else
							{
								//��Ɖ��̃{�N�Z���̃t���O�̒l�������đ傫�����𕪊�����
								Left_Up = (block[x][y][z-1].flag) * (block[x][y][z+1].flag);
								Right_Down =  (block[x+1][y+1][z-1].flag) * (block[x+1][y+1][z+1].flag);
								if(Left_Up > Right_Down)
								{
									block[x][y][z].flag = 1;
									block[x][y+1][z].flag = 2; 
									block[x+1][y+1][z].flag = 2; 
									num11++;
									num12++;
								}
								else
								{
									block[x][y][z].flag = 2;
									block[x][y+1][z].flag = 2; 
									block[x+1][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
					}
					//���ڃ{�N�Z����ID��0�ɂȂ�ꍇ
					else if(block[x][y][z].flag == 0 )
					{
						if(block[x][y+1][z].flag == 3)			//�P�[�X�P
						{
							countLN++;
							if( (block[x+1][y][z-1].flag > 3 ||  block[x+1][y][z+1].flag > 3) && block[x][y+1][z-1].flag < 4 &&  block[x][y+1][z+1].flag < 4)
							{
								block[x+1][y+1][z].flag = 2;
								block[x+1][y][z].flag = 1; 
								block[x][y+1][z].flag = 2; 
								num11++;
								num12++;
							}
							else if(block[x+1][y][z-1].flag < 4 &&  block[x+1][y][z+1].flag < 4 && (block[x][y+1][z-1].flag > 3 ||  block[x][y+1][z+1].flag > 3) )
							{
								block[x+1][y+1][z].flag = 2;
								block[x+1][y][z].flag = 2; 
								block[x][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							else if( block[x+1][y][z-1].flag < 2 && block[x+1][y][z+1].flag < 2 && block[x][y+1][z-1].flag < 2 &&  block[x][y+1][z+1].flag < 2)
							{
								count++;
								num22++;
								//�Q�~�Q�ɖ������ς��܂�������`
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x][y][z].fill = true;
								cout<<"�����ł��Ȃ���������2�~2�ɕς������I"<<x<<" "<<y<<" "<<z<<endl;
							}
							else
							{
								//��Ɖ��̃{�N�Z���̃t���O�̒l�������đ傫�����𕪊�����
								Left_Down = (block[x+1][y][z-1].flag) * (block[x+1][y][z+1].flag);
								Right_Up =  (block[x][y+1][z-1].flag) * (block[x][y+1][z+1].flag);
								if(Left_Down > Right_Up)
								{
									block[x+1][y+1][z].flag = 2;
									block[x+1][y][z].flag = 1; 
									block[x][y+1][z].flag = 2; 
									num11++;
									num12++;
								}
								else
								{
									block[x+1][y+1][z].flag = 2;
									block[x+1][y][z].flag = 2; 
									block[x][y+1][z].flag = 1; 
									num11++;
									num12++;
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
			for(x=0; x < VoxSize[0]-1; x=x+2)
			{
				for(y=0; y < VoxSize[1]-1; y=y+2)
				{
					//���ڃ{�N�Z����ID���R�ɂȂ�ꍇ
					if(block[x][y][z].flag == 3)
					{
						//                                                                                                                                
						//�P�[�X�Q
						if(block[x][y+1][z].flag == 0)
						{
							countLN++;
							//����̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							if( (block[x][y][z-1].flag > 3 || block[x][y][z+1].flag > 3) &&  block[x+1][y+1][z-1].flag < 4 && block[x+1][y+1][z+1].flag < 4 )
							{
								block[x][y][z].flag = 1;
								block[x+1][y][z].flag = 2; 
								block[x+1][y+1][z].flag = 2; 
								num11++;
								num12++;
							}
							//��������̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							else if( block[x][y][z-1].flag < 4 && block[x][y][z+1].flag < 4 && ( block[x+1][y+1][z-1].flag > 3 || block[x+1][y+1][z+1].flag > 3))
							{
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 2; 
								block[x+1][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//���ڂ̂Q�̃{�N�Z���̏㉺�i�S�j�Ƃ��ɂP�~�P�ȉ��̃{�N�Z���ł���Ƃ�
							else if(block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2)
							{
								count++;
								num22++;
								//�Q�~�Q�ɖ������ς��܂�������`
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x][y+1][z].fill = true;
								cout<<"�����ł��Ȃ���������2�~2�ɕς������I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//��L�ȊO�̎���
							else
							{
								//��Ɖ��̃{�N�Z���̃t���O�̒l�������đ傫�����𕪊�����
								Left_Up = (block[x][y][z-1].flag) * (block[x][y][z+1].flag);
								Right_Down =  (block[x+1][y+1][z-1].flag) * (block[x+1][y+1][z+1].flag);
								if(Left_Up > Right_Down)
								{
									block[x][y][z].flag = 1;
									block[x+1][y][z].flag = 2; 
									block[x+1][y+1][z].flag = 2; 
									num11++;
									num12++;
								}
								else
								{
									block[x][y][z].flag = 2;
									block[x+1][y][z].flag = 2; 
									block[x+1][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
						//						                                                                                                                                
						//�P�[�X�R
						else if(block[x+1][y+1][z].flag == 0)
						{
							countLN++;
							//����̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							if( (block[x+1][y][z-1].flag >3  ||  block[x+1][y][z+1].flag > 3) && block[x][y+1][z-1].flag < 4 &&  block[x][y+1][z+1].flag < 4 )
							{
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 1; 
								block[x][y+1][z].flag = 2; 
								num11++;
								num12++;
							}
							//��������̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							else if( block[x+1][y][z-1].flag < 4  &&  block[x+1][y][z+1].flag < 4 && (block[x][y+1][z-1].flag > 3 &&  block[x][y+1][z+1].flag > 3) )
							{
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 2; 
								block[x][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//���ڂ̂Q�̃{�N�Z���̏㉺�i�S�j�Ƃ��ɂP�~�P�ȉ��̃{�N�Z���ł���Ƃ�
							else if(block[x+1][y][z-1].flag < 2 &&  block[x+1][y][z+1].flag < 2 && block[x][y+1][z-1].flag < 2 &&  block[x][y+1][z+1].flag < 2 )
							{
								count++;
								num22++;
								//�Q�~�Q�ɖ������ς��܂�������`
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x+1][y+1][z].fill = true;
								cout<<"�����ł��Ȃ���������2�~2�ɕς������I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//��L�ȊO�̎���
							else
							{
								Left_Down = (block[x+1][y][z-1].flag) * (block[x+1][y][z+1].flag);
								Right_Up =  (block[x][y+1][z-1].flag) * (block[x][y+1][z+1].flag);
								if(Left_Down > Right_Up)
								{
									block[x][y][z].flag = 2;
									block[x+1][y][z].flag = 1; 
									block[x][y+1][z].flag = 2; 
									num11++;
									num12++;
								}
								else
								{
									block[x][y][z].flag = 2;
									block[x+1][y][z].flag = 2; 
									block[x][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
						//                                                                                                     
						//�P�[�X�S
						else if(block[x+1][y][z].flag == 0)
						{
							countLN++;
							//����̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							if( (block[x][y][z-1].flag > 3 ||  block[x][y][z+1].flag > 3) && block[x+1][y+1][z-1].flag < 4 &&  block[x+1][y+1][z+1].flag < 4 )
							{
								block[x][y][z].flag = 1;
								block[x][y+1][z].flag = 2; 
								block[x+1][y+1][z].flag = 2; 
								num11++;
								num12++;
							}
							//��������̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							else if( block[x][y][z-1].flag < 4 &&  block[x][y][z+1].flag < 4 && (block[x+1][y+1][z-1].flag > 3 ||  block[x+1][y+1][z+1].flag > 3) )
							{
								block[x][y][z].flag = 2;
								block[x][y+1][z].flag = 2; 
								block[x+1][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//���ڃ{�N�Z���̏㉺4�Ƃ��ɂP�~�P�܂��͉����Ȃ��ꍇ
							else if( block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2 )
							{
								count++;
								num22++;
								//�Q�~�Q�ɖ������ς��܂�������`
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x+1][y][z].fill = true;
								cout<<"�����ł��Ȃ���������2�~2�ɕς������I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//��L�ȊO�̏ꍇ
							else
							{
								//��Ɖ��̃{�N�Z���̃t���O�̒l�������đ傫�����𕪊�����
								Left_Up = (block[x][y][z-1].flag) * (block[x][y][z+1].flag);
								Right_Down =  (block[x+1][y+1][z-1].flag) * (block[x+1][y+1][z+1].flag);
								if(Left_Up > Right_Down)
								{
									block[x][y][z].flag = 1;
									block[x][y+1][z].flag = 2; 
									block[x+1][y+1][z].flag = 2; 
									num11++;
									num12++;
								}
								else
								{
									block[x][y][z].flag = 2;
									block[x][y+1][z].flag = 2; 
									block[x+1][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
					}
					//���ڃ{�N�Z����ID��0�ɂȂ�ꍇ
					else if(block[x][y][z].flag == 0 )
					{
						if(block[x][y+1][z].flag == 3)			//�P�[�X�P
						{
							countLN++;
							if( (block[x+1][y][z-1].flag > 3 ||  block[x+1][y][z+1].flag > 3) && block[x][y+1][z-1].flag < 4 &&  block[x][y+1][z+1].flag < 4)
							{
								block[x+1][y+1][z].flag = 2;
								block[x+1][y][z].flag = 1; 
								block[x][y+1][z].flag = 2; 
								num11++;
								num12++;
							}
							else if(block[x+1][y][z-1].flag < 4 &&  block[x+1][y][z+1].flag < 4 && (block[x][y+1][z-1].flag > 3 ||  block[x][y+1][z+1].flag > 3) )
							{
								block[x+1][y+1][z].flag = 2;
								block[x+1][y][z].flag = 2; 
								block[x][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							else if( block[x+1][y][z-1].flag < 2 && block[x+1][y][z+1].flag < 2 && block[x][y+1][z-1].flag < 2 &&  block[x][y+1][z+1].flag < 2)
							{
								count++;
								num22++;
								//�Q�~�Q�ɖ������ς��܂�������`
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x][y][z].fill = true;
								cout<<"�����ł��Ȃ���������2�~2�ɕς������I"<<x<<" "<<y<<" "<<z<<endl;
							}
							else
							{
								//��Ɖ��̃{�N�Z���̃t���O�̒l�������đ傫�����𕪊�����
								Left_Down = (block[x+1][y][z-1].flag) * (block[x+1][y][z+1].flag);
								Right_Up =  (block[x][y+1][z-1].flag) * (block[x][y+1][z+1].flag);
								if(Left_Down > Right_Up)
								{
									block[x+1][y+1][z].flag = 2;
									block[x+1][y][z].flag = 1; 
									block[x][y+1][z].flag = 2; 
									num11++;
									num12++;
								}
								else
								{
									block[x+1][y+1][z].flag = 2;
									block[x+1][y][z].flag = 2; 
									block[x][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
					}
				}
			}
		}
	}

	cout<<countLN<<"���@"<<count<<" ��L���P�~�P�ƂP�~�Q�ɕ����ł��Ȃ������I"<<endl;
	outputFlag("test00_L_to11_12.txt", VoxSize);

}

void Small_to_Big_step0_color( Lego*** block, int* VoxSize)
{
	int Left_Up(0);
	int Left_Down(0);
	int Right_Up(0);
	int Right_Down(0);

	int count(0);		//L�����P�~�P�ƂP�~�Q�ɕ����ł��Ȃ�������
	int countLN(0);
	int x,y,z;
	//��w
	for(z=1; z < VoxSize[2]-1; z++ )
	{
		if(z%2)
		{
			for(x=1; x < VoxSize[0]-1; x=x+2)
			{
				for(y=1; y < VoxSize[1]-1; y=y+2)
				{
					//���ڃ{�N�Z����ID���R�ɂȂ�ꍇ
					if(block[x][y][z].flag == 3)
					{
						//                                                                                                                                
						//�P�[�X�Q(�Q�~�Q�̃}�X�N�ɑ΂��ĂR�̃{�N�Z�����ǂ̂悤�ɔz�u���Ă���̂�)
						if(block[x][y+1][z].flag == 0)
						{
							countLN++;
							//����̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							if( (block[x][y][z-1].flag > 3 || block[x][y][z+1].flag > 3) &&  block[x+1][y+1][z-1].flag < 4 && block[x+1][y+1][z+1].flag < 4 )
							{
								ID12++;
								block[x][y][z].flag = 1;
								block[x+1][y][z].flag = 2;			block[x+1][y][z].ID = ID12; 
								block[x+1][y+1][z].flag = 2;		block[x+1][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//��������̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							else if( block[x][y][z-1].flag < 4 && block[x][y][z+1].flag < 4 && ( block[x+1][y+1][z-1].flag > 3 || block[x+1][y+1][z+1].flag > 3))
							{
								ID12++;
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 2;			block[x+1][y][z].ID = ID12; 
								block[x+1][y+1][z].flag = 1;		block[x+1][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//���ڂ̂Q�̃{�N�Z���̏㉺�i�S�j�Ƃ��ɂP�~�P�ȉ��̃{�N�Z���ł���Ƃ�
							else if(block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2)
							{
								ID22++;
								count++;
								num22++;
								//�Q�~�Q�ɖ������ς��܂�
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x][y+1][z].fill = true;
								cout<<"�����ł��Ȃ���������2�~2�ɕς������I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//��L�ȊO�̎���
							else
							{
								//��Ɖ��̃{�N�Z���̃t���O�̒l�������đ傫�����𕪊�����
								Left_Up = (block[x][y][z-1].flag) * (block[x][y][z+1].flag);
								Right_Down =  (block[x+1][y+1][z-1].flag) * (block[x+1][y+1][z+1].flag);
								if(Left_Up > Right_Down)
								{
									ID12++;
									block[x][y][z].flag = 1;
									block[x+1][y][z].flag = 2;					block[x+1][y][z].ID = ID12; 
									block[x+1][y+1][z].flag = 2;				block[x+1][y+1][z].ID = ID12; 
									num11++;
									num12++;
								}
								else
								{
									ID12++;
									block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
									block[x+1][y][z].flag = 2;				block[x+1][y][z].ID = ID12; 
									block[x+1][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
						//						                                                                                                                                
						//�P�[�X�R
						else if(block[x+1][y+1][z].flag == 0)
						{
							countLN++;
							//����̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							if( (block[x+1][y][z-1].flag >3  ||  block[x+1][y][z+1].flag > 3) && block[x][y+1][z-1].flag < 4 &&  block[x][y+1][z+1].flag < 4 )
							{
								ID12++;
								block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
								block[x+1][y][z].flag = 1; 
								block[x][y+1][z].flag = 2;				block[x][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//��������̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							else if( block[x+1][y][z-1].flag < 4  &&  block[x+1][y][z+1].flag < 4 && (block[x][y+1][z-1].flag > 3 &&  block[x][y+1][z+1].flag > 3) )
							{
								ID12++;
								block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
								block[x+1][y][z].flag = 2; 				block[x+1][y][z].ID = ID12; 
								block[x][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//���ڂ̂Q�̃{�N�Z���̏㉺�i�S�j�Ƃ��ɂP�~�P�ȉ��̃{�N�Z���ł���Ƃ�
							else if(block[x+1][y][z-1].flag < 2 &&  block[x+1][y][z+1].flag < 2 && block[x][y+1][z-1].flag < 2 &&  block[x][y+1][z+1].flag < 2 )
							{
								ID22++;
								count++;
								num22++;
								//�Q�~�Q�ɖ������ς��܂�������`
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x+1][y+1][z].fill = true;
								cout<<"�����ł��Ȃ���������2�~2�ɕς������I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//��L�ȊO�̎���
							else
							{
								Left_Down = (block[x+1][y][z-1].flag) * (block[x+1][y][z+1].flag);
								Right_Up =  (block[x][y+1][z-1].flag) * (block[x][y+1][z+1].flag);
								if(Left_Down > Right_Up)
								{
									ID12++;
									block[x][y][z].flag = 2;						block[x][y][z].ID = ID12;
									block[x+1][y][z].flag = 1; 
									block[x][y+1][z].flag = 2;					block[x][y+1][z].ID = ID12; 
									num11++;
									num12++;
								}
								else
								{
									ID12++;
									block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
									block[x+1][y][z].flag = 2; 				block[x+1][y][z].ID = ID12; 
									block[x][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
						//                                                                                                     
						//�P�[�X�S
						else if(block[x+1][y][z].flag == 0)
						{
							countLN++;
							//����̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							if( (block[x][y][z-1].flag > 3 ||  block[x][y][z+1].flag > 3) && block[x+1][y+1][z-1].flag < 4 &&  block[x+1][y+1][z+1].flag < 4 )
							{
								ID12++;
								block[x][y][z].flag = 1;
								block[x][y+1][z].flag = 2; 				block[x][y+1][z].ID = ID12; 
								block[x+1][y+1][z].flag = 2;			block[x+1][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//��������̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							else if( block[x][y][z-1].flag < 4 &&  block[x][y][z+1].flag < 4 && (block[x+1][y+1][z-1].flag > 3 ||  block[x+1][y+1][z+1].flag > 3) )
							{
								ID12++;
								block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
								block[x][y+1][z].flag = 2;				block[x][y+1][z].ID = ID12; 
								block[x+1][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//���ڃ{�N�Z���̏㉺4�Ƃ��ɂP�~�P�܂��͉����Ȃ��ꍇ
							else if( block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2 )
							{
								ID22++;
								count++;
								num22++;
								//�Q�~�Q�ɖ������ς��܂�������`
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x+1][y][z].fill = true;
								cout<<"�����ł��Ȃ���������2�~2�ɕς������I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//��L�ȊO�̏ꍇ
							else
							{
								//��Ɖ��̃{�N�Z���̃t���O�̒l�������đ傫�����𕪊�����
								Left_Up = (block[x][y][z-1].flag) * (block[x][y][z+1].flag);
								Right_Down =  (block[x+1][y+1][z-1].flag) * (block[x+1][y+1][z+1].flag);
								if(Left_Up > Right_Down)
								{
									ID12++;
									block[x][y][z].flag = 1;
									block[x][y+1][z].flag = 2;							block[x][y+1][z].ID = ID12; 
									block[x+1][y+1][z].flag = 2; 						block[x+1][y+1][z].ID = ID12; 
									num11++;
									num12++;
								}
								else
								{
									ID12++;
									block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
									block[x][y+1][z].flag = 2;				block[x][y+1][z].ID = ID12; 
									block[x+1][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
					}
					//���ڃ{�N�Z����ID��0�ɂȂ�ꍇ
					else if(block[x][y][z].flag == 0 )
					{
						if(block[x][y+1][z].flag == 3)			//�P�[�X�P
						{
							countLN++;
							if( (block[x+1][y][z-1].flag > 3 ||  block[x+1][y][z+1].flag > 3) && block[x][y+1][z-1].flag < 4 &&  block[x][y+1][z+1].flag < 4)
							{
								ID12++;
								block[x+1][y+1][z].flag = 2;					block[x+1][y+1][z].ID = ID12;
								block[x+1][y][z].flag = 1; 
								block[x][y+1][z].flag = 2; 					block[x][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							else if(block[x+1][y][z-1].flag < 4 &&  block[x+1][y][z+1].flag < 4 && (block[x][y+1][z-1].flag > 3 ||  block[x][y+1][z+1].flag > 3) )
							{
								ID12++;
								block[x+1][y+1][z].flag = 2;				block[x+1][y+1][z].ID = ID12;
								block[x+1][y][z].flag = 2; 					block[x+1][y][z].ID = ID12; 
								block[x][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							else if( block[x+1][y][z-1].flag < 2 && block[x+1][y][z+1].flag < 2 && block[x][y+1][z-1].flag < 2 &&  block[x][y+1][z+1].flag < 2)
							{
								ID22++;
								count++;
								num22++;
								//�Q�~�Q�ɖ������ς��܂�������`
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x][y][z].fill = true;
								cout<<"�����ł��Ȃ���������2�~2�ɕς������I"<<x<<" "<<y<<" "<<z<<endl;
							}
							else
							{
								//��Ɖ��̃{�N�Z���̃t���O�̒l�������đ傫�����𕪊�����
								Left_Down = (block[x+1][y][z-1].flag) * (block[x+1][y][z+1].flag);
								Right_Up =  (block[x][y+1][z-1].flag) * (block[x][y+1][z+1].flag);
								if(Left_Down > Right_Up)
								{
									ID12++;
									block[x+1][y+1][z].flag = 2;					block[x+1][y+1][z].ID = ID12;
									block[x+1][y][z].flag = 1; 
									block[x][y+1][z].flag = 2; 						block[x][y+1][z].ID = ID12; 
									num11++;
									num12++;
								}
								else
								{
									ID12++;
									block[x+1][y+1][z].flag = 2;					block[x+1][y+1][z].ID = ID12;
									block[x+1][y][z].flag = 2; 						block[x+1][y][z].ID = ID12; 
									block[x][y+1][z].flag = 1; 
									num11++;
									num12++;
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
			for(x=0; x < VoxSize[0]-1; x=x+2)
			{
				for(y=0; y < VoxSize[1]-1; y=y+2)
				{
					//���ڃ{�N�Z����ID���R�ɂȂ�ꍇ
					if(block[x][y][z].flag == 3)
					{
						//                                                                                                                                
						//�P�[�X�Q
						if(block[x][y+1][z].flag == 0)
						{
							countLN++;
							//����̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							if( (block[x][y][z-1].flag > 3 || block[x][y][z+1].flag > 3) &&  block[x+1][y+1][z-1].flag < 4 && block[x+1][y+1][z+1].flag < 4 )
							{
								ID12++;
								block[x][y][z].flag = 1;
								block[x+1][y][z].flag = 2;			block[x+1][y][z].ID = ID12; 
								block[x+1][y+1][z].flag = 2;		block[x+1][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//��������̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							else if( block[x][y][z-1].flag < 4 && block[x][y][z+1].flag < 4 && ( block[x+1][y+1][z-1].flag > 3 || block[x+1][y+1][z+1].flag > 3))
							{
								ID12++;
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 2;			block[x+1][y][z].ID = ID12; 
								block[x+1][y+1][z].flag = 1;		block[x+1][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//���ڂ̂Q�̃{�N�Z���̏㉺�i�S�j�Ƃ��ɂP�~�P�ȉ��̃{�N�Z���ł���Ƃ�
							else if(block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2)
							{
								ID22++;
								count++;
								num22++;
								//�Q�~�Q�ɖ������ς��܂�������`
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x][y+1][z].fill = true;
								cout<<"�����ł��Ȃ���������2�~2�ɕς������I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//��L�ȊO�̎���
							else
							{
								//��Ɖ��̃{�N�Z���̃t���O�̒l�������đ傫�����𕪊�����
								Left_Up = (block[x][y][z-1].flag) * (block[x][y][z+1].flag);
								Right_Down =  (block[x+1][y+1][z-1].flag) * (block[x+1][y+1][z+1].flag);
								if(Left_Up > Right_Down)
								{
									ID12++;
									block[x][y][z].flag = 1;
									block[x+1][y][z].flag = 2;					block[x+1][y][z].ID = ID12; 
									block[x+1][y+1][z].flag = 2;				block[x+1][y+1][z].ID = ID12; 
									num11++;
									num12++;
								}
								else
								{
									ID12++;
									block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
									block[x+1][y][z].flag = 2;				block[x+1][y][z].ID = ID12; 
									block[x+1][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
						//						                                                                                                                                
						//�P�[�X�R
						else if(block[x+1][y+1][z].flag == 0)
						{
							countLN++;
							//����̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							if( (block[x+1][y][z-1].flag >3  ||  block[x+1][y][z+1].flag > 3) && block[x][y+1][z-1].flag < 4 &&  block[x][y+1][z+1].flag < 4 )
							{
								ID12++;
								block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
								block[x+1][y][z].flag = 1; 
								block[x][y+1][z].flag = 2;				block[x][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//��������̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							else if( block[x+1][y][z-1].flag < 4  &&  block[x+1][y][z+1].flag < 4 && (block[x][y+1][z-1].flag > 3 &&  block[x][y+1][z+1].flag > 3) )
							{
								ID12++;
								block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
								block[x+1][y][z].flag = 2; 				block[x+1][y][z].ID = ID12; 
								block[x][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//���ڂ̂Q�̃{�N�Z���̏㉺�i�S�j�Ƃ��ɂP�~�P�ȉ��̃{�N�Z���ł���Ƃ�
							else if(block[x+1][y][z-1].flag < 2 &&  block[x+1][y][z+1].flag < 2 && block[x][y+1][z-1].flag < 2 &&  block[x][y+1][z+1].flag < 2 )
							{
								ID22++;
								count++;
								num22++;
								//�Q�~�Q�ɖ������ς��܂�������`
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x+1][y+1][z].fill = true;
								cout<<"�����ł��Ȃ���������2�~2�ɕς������I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//��L�ȊO�̎���
							else
							{
								Left_Down = (block[x+1][y][z-1].flag) * (block[x+1][y][z+1].flag);
								Right_Up =  (block[x][y+1][z-1].flag) * (block[x][y+1][z+1].flag);
								if(Left_Down > Right_Up)
								{
									ID12++;
									block[x][y][z].flag = 2;						block[x][y][z].ID = ID12;
									block[x+1][y][z].flag = 1; 
									block[x][y+1][z].flag = 2;					block[x][y+1][z].ID = ID12; 
									num11++;
									num12++;
								}
								else
								{
									ID12++;
									block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
									block[x+1][y][z].flag = 2; 				block[x+1][y][z].ID = ID12; 
									block[x][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
						//                                                                                                     
						//�P�[�X�S
						else if(block[x+1][y][z].flag == 0)
						{
							countLN++;
							//����̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							if( (block[x][y][z-1].flag > 3 ||  block[x][y][z+1].flag > 3) && block[x+1][y+1][z-1].flag < 4 &&  block[x+1][y+1][z+1].flag < 4 )
							{
								ID12++;
								block[x][y][z].flag = 1;
								block[x][y+1][z].flag = 2; 				block[x][y+1][z].ID = ID12; 
								block[x+1][y+1][z].flag = 2;			block[x+1][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//��������̃{�N�Z���̏�܂��͉��ɂ݂̂Q�~�Q���������炻����P�~�P�ɂ���
							else if( block[x][y][z-1].flag < 4 &&  block[x][y][z+1].flag < 4 && (block[x+1][y+1][z-1].flag > 3 ||  block[x+1][y+1][z+1].flag > 3) )
							{
								ID12++;
								block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
								block[x][y+1][z].flag = 2;				block[x][y+1][z].ID = ID12; 
								block[x+1][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//���ڃ{�N�Z���̏㉺4�Ƃ��ɂP�~�P�܂��͉����Ȃ��ꍇ
							else if( block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2 )
							{
								ID22++;
								count++;
								num22++;
								//�Q�~�Q�ɖ������ς��܂�������`
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x+1][y][z].fill = true;
								cout<<"�����ł��Ȃ���������2�~2�ɕς������I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//��L�ȊO�̏ꍇ
							else
							{
								//��Ɖ��̃{�N�Z���̃t���O�̒l�������đ傫�����𕪊�����
								Left_Up = (block[x][y][z-1].flag) * (block[x][y][z+1].flag);
								Right_Down =  (block[x+1][y+1][z-1].flag) * (block[x+1][y+1][z+1].flag);
								if(Left_Up > Right_Down)
								{
									ID12++;
									block[x][y][z].flag = 1;
									block[x][y+1][z].flag = 2;							block[x][y+1][z].ID = ID12; 
									block[x+1][y+1][z].flag = 2; 						block[x+1][y+1][z].ID = ID12; 
									num11++;
									num12++;
								}
								else
								{
									ID12++;
									block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
									block[x][y+1][z].flag = 2;				block[x][y+1][z].ID = ID12; 
									block[x+1][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
					}
					//���ڃ{�N�Z����ID��0�ɂȂ�ꍇ
					else if(block[x][y][z].flag == 0 )
					{
						if(block[x][y+1][z].flag == 3)			//�P�[�X�P
						{
							countLN++;
							if( (block[x+1][y][z-1].flag > 3 ||  block[x+1][y][z+1].flag > 3) && block[x][y+1][z-1].flag < 4 &&  block[x][y+1][z+1].flag < 4)
							{
								ID12++;
								block[x+1][y+1][z].flag = 2;					block[x+1][y+1][z].ID = ID12;
								block[x+1][y][z].flag = 1; 
								block[x][y+1][z].flag = 2; 					block[x][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							else if(block[x+1][y][z-1].flag < 4 &&  block[x+1][y][z+1].flag < 4 && (block[x][y+1][z-1].flag > 3 ||  block[x][y+1][z+1].flag > 3) )
							{
								ID12++;
								block[x+1][y+1][z].flag = 2;				block[x+1][y+1][z].ID = ID12;
								block[x+1][y][z].flag = 2; 					block[x+1][y][z].ID = ID12; 
								block[x][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							else if( block[x+1][y][z-1].flag < 2 && block[x+1][y][z+1].flag < 2 && block[x][y+1][z-1].flag < 2 &&  block[x][y+1][z+1].flag < 2)
							{
								ID22++;
								count++;
								num22++;
								//�Q�~�Q�ɖ������ς��܂�������`
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x][y][z].fill = true;
								cout<<"�����ł��Ȃ���������2�~2�ɕς������I"<<x<<" "<<y<<" "<<z<<endl;
							}
							else
							{
								//��Ɖ��̃{�N�Z���̃t���O�̒l�������đ傫�����𕪊�����
								Left_Down = (block[x+1][y][z-1].flag) * (block[x+1][y][z+1].flag);
								Right_Up =  (block[x][y+1][z-1].flag) * (block[x][y+1][z+1].flag);
								if(Left_Down > Right_Up)
								{
									ID12++;
									block[x+1][y+1][z].flag = 2;					block[x+1][y+1][z].ID = ID12;
									block[x+1][y][z].flag = 1; 
									block[x][y+1][z].flag = 2; 						block[x][y+1][z].ID = ID12; 
									num11++;
									num12++;
								}
								else
								{
									ID12++;
									block[x+1][y+1][z].flag = 2;					block[x+1][y+1][z].ID = ID12;
									block[x+1][y][z].flag = 2; 						block[x+1][y][z].ID = ID12; 
									block[x][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
					}
				}
			}
		}
	}

	cout<<countLN<<"���@"<<count<<" ��L���P�~�P�ƂP�~�Q�ɕ����ł��Ȃ������I"<<endl;
	//outputFlag("test00_L_to11_12.txt", VoxSize);

}

