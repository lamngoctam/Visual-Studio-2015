#include "../stdafx.h"
#include "../Voxel.h"
#include "../Lego.h"		//LEGO�u���b�N��g�ݗ��Ă邽�߂̃N���X

extern int ID12;			
extern int ID13;

extern int num11;
extern int num12;
extern int num13;
extern int num22;

void outputFlag(string filename, int* size);

//�Q�~�Q�̎��ӂW�}�X�����āA�����ɂP�~�P������A���P�~�R�ƂP�~�Q�ɕ������Ă����Ȃ��ꍇ�͕�������
void Small_to_Big_step3(Lego*** block, int*  VoxSize)
{
	int count(0);
	int x,y,z;
	for(z = 1; z<VoxSize[2]-1; z++)
	{
		//��w
		if(z%2)
		{
			for(x = 1; x<VoxSize[0]-1; x=x+2)
			{
				for(y = 1; y<VoxSize[1]-1; y=y+2)
				{
					//���ڂ̂Q�~�Q�̃}�X�N�̃t���O���S�������Ă�����
					if(block[x][y][z].flag == 4 && block[x+1][y+1][z].flag == 4)
					{
						//��̍�
						if(block[x-1][y][z].flag == 1)
						{
							//1�̏㉺�̃{�N�Z����flag���Ƃ��ɂP�܂��͂O�Ȃ��(�����̔���������܂Ō��������Ȃ��Ă�������������Ȃ��H)
							if(block[x-1][y][z-1].flag < 2 && block[x-1][y][z+1].flag < 2 )
							{
								if(block[x+2][y][z].flag > 1 && block[x+2][y+1][z].flag > 1)	//flag�̒l��2�ȏ�ł����
								{
									if( (block[x+1][y][z-1].flag > 1 &&  block[x+2][y][z-1].flag > 1 ) || (block[x+1][y][z+1].flag > 1  && block[x+2][y][z+1].flag > 1) )
									{
										if( (block[x+1][y+1][z-1].flag > 1 && block[x+2][y+1][z-1].flag > 1) || (block[x+1][y+1][z+1].flag > 1 && block[x+2][y+1][z+1].flag > 1 ))
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y+1][z].flag = 12;			block[x][y+1][z].ID = ID12;			block[x][y+1][z].corner = 1;
											block[x+1][y+1][z].flag = 12;		block[x+1][y+1][z].ID = ID12;		block[x+1][y+1][z].corner = 2;	
											block[x-1][y][z].flag = 13;				block[x-1][y][z].ID = ID13;			block[x-1][y][z].corner = 1;
											block[x][y][z].flag = 13;					block[x][y][z].ID = ID13;	
											block[x+1][y][z].flag = 13;			block[x+1][y][z].ID = ID13;			block[x+1][y][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//��̉E
						if(block[x-1][y+1][z].flag == 1)
						{
							if(block[x-1][y+1][z-1].flag < 2 && block[x-1][y+1][z+1].flag < 2 )
							{
								if(block[x+2][y][z].flag > 1 && block[x+2][y+1][z].flag > 1)
								{
									if( (block[x+1][y][z-1].flag > 1 &&  block[x+2][y][z-1].flag > 1 ) || (block[x+1][y][z+1].flag > 1  && block[x+2][y][z+1].flag > 1) )
									{
										if( (block[x+1][y+1][z-1].flag > 1 && block[x+2][y+1][z-1].flag > 1) || (block[x+1][y+1][z+1].flag > 1 && block[x+2][y+1][z+1].flag > 1 ))
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;										
											block[x-1][y+1][z].flag = 13;			block[x-1][y+1][z].ID = ID13;		block[x-1][y+1][z].corner = 1;
											block[x][y+1][z].flag = 13;			block[x][y+1][z].ID = ID13;
											block[x+1][y+1][z].flag = 13;		block[x+1][y+1][z].ID = ID13;		block[x+1][y+1][z].corner = 2;	
											block[x][y][z].flag = 12;					block[x][y][z].ID = ID12;				block[x][y][z].corner = 1;
											block[x+1][y][z].flag = 12;			block[x+1][y][z].ID = ID12;			block[x+1][y][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//���̏�
						if(block[x][y-1][z].flag == 1)
						{
							if(block[x][y-1][z-1].flag < 2 && block[x][y-1][z+1].flag < 2 )
							{
								if(block[x][y+2][z].flag > 1 && block[x+1][y+2][z].flag > 1)
								{
									if( (block[x][y+1][z-1].flag > 1 && block[x][y+2][z-1].flag > 1 ) || (block[x][y+1][z+1].flag > 1 && block[x][y+2][z+1].flag > 1) )
									{
										if((block[x+1][y+1][z-1].flag > 1 && block[x+1][y+2][z-1].flag > 1) || (block[x+1][y+1][z+1].flag > 1 && block[x+1][y+2][z+1].flag > 1))
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y-1][z].flag = 13;			block[x][y-1][z].ID = ID13;		block[x][y-1][z].corner = 1;
											block[x][y][z].flag = 13;				block[x][y][z].ID = ID13;
											block[x][y+1][z].flag = 13;		block[x][y+1][z].ID = ID13;		block[x][y+1][z].corner = 2;	
											block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 1;	
											block[x+1][y+1][z].flag = 12;	block[x+1][y+1][z].ID = ID12;	block[x+1][y+1][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//���̉�
						if(block[x+1][y-1][z].flag == 1)
						{
							if(block[x+1][y-1][z-1].flag < 2 && block[x+1][y-1][z+1].flag < 2 )
							{
								if(block[x][y+2][z].flag > 1 && block[x+1][y+2][z].flag > 1)
								{
									if( (block[x][y+1][z-1].flag > 1 && block[x][y+2][z-1].flag > 1 ) || (block[x][y+1][z+1].flag > 1 && block[x][y+2][z+1].flag > 1) )
									{
										if((block[x+1][y+1][z-1].flag > 1 && block[x+1][y+2][z-1].flag > 1) || (block[x+1][y+1][z+1].flag > 1 && block[x+1][y+2][z+1].flag > 1))
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y][z].flag = 12;				block[x][y][z].ID = ID12;			block[x][y][z].corner = 1;
											block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;		block[x][y+1][z].corner = 2;	
											block[x+1][y-1][z].flag = 13;		block[x+1][y-1][z].ID = ID13;	block[x+1][y-1][z].corner = 1;
											block[x+1][y][z].flag = 13;		block[x+1][y][z].ID = ID13;	
											block[x+1][y+1][z].flag = 13;	block[x+1][y+1][z].ID = ID13;	block[x+1][y+1][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//���̍�
						if(block[x+2][y][z].flag == 1)
						{
							if(block[x+2][y][z-1].flag < 2 && block[x+2][y][z+1].flag < 2 )
							{
								if(block[x-1][y][z].flag > 1 && block[x-1][y+1][z].flag > 1)
								{
									if( (block[x-1][y][z-1].flag > 1 && block[x][y][z-1].flag > 1) || (block[x-1][y][z+1].flag > 1 && block[x][y][z+1].flag > 1) )
									{
										if( ( block[x-1][y+1][z-1].flag > 1 && block[x][y+1][z-1].flag > 1) || (block[x-1][y+1][z+1].flag > 1 && block[x][y+1][z+1].flag > 1) )
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y+1][z].flag = 12;			block[x][y+1][z].ID = ID12;		block[x][y+1][z].corner = 1;
											block[x+1][y+1][z].flag = 12;		block[x+1][y+1][z].ID = ID12;	block[x+1][y+1][z].corner = 2;	
											block[x][y][z].flag = 13;					block[x][y][z].ID = ID13;			block[x][y][z].corner = 1;	
											block[x+1][y][z].flag = 13;			block[x+1][y][z].ID = ID13;
											block[x+2][y][z].flag = 13;			block[x+2][y][z].ID = ID13;		block[x+2][y][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//���̉E
						if(block[x+2][y+1][z].flag == 1)
						{
							if(block[x+2][y+1][z-1].flag < 2 && block[x+2][y+1][z+1].flag < 2 )
							{
								if(block[x-1][y][z].flag > 1 && block[x-1][y+1][z].flag > 1)
								{
									if( (block[x-1][y][z-1].flag > 1 && block[x][y][z-1].flag > 1) || (block[x-1][y][z+1].flag > 1 && block[x][y][z+1].flag > 1) )
									{
										if( ( block[x-1][y+1][z-1].flag > 1 && block[x][y+1][z-1].flag > 1) || (block[x-1][y+1][z+1].flag > 1 && block[x][y+1][z+1].flag > 1) )
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y+1][z].flag = 13;			block[x][y+1][z].ID = ID13;		block[x][y+1][z].corner = 1;
											block[x+1][y+1][z].flag = 13;		block[x+1][y+1][z].ID = ID13;	
											block[x+2][y+1][z].flag = 13;		block[x+2][y+1][z].ID = ID13;	block[x+2][y+1][z].corner = 2;
											block[x][y][z].flag = 12;					block[x][y][z].ID = ID12;			block[x][y][z].corner = 1;	
											block[x+1][y][z].flag = 12;			block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}

						//�E�̏�
						if(block[x][y+2][z].flag == 1)
						{
							if(block[x][y+2][z-1].flag < 2 && block[x][y+2][z+1].flag < 2 )
							{
								if(block[x][y-1][z].flag > 1 && block[x+1][y-1][z].flag > 1)
								{
									if( (block[x][y-1][z-1].flag > 1 && block[x][y][z-1].flag > 1) || (block[x][y-1][z+1].flag > 1 && block[x][y][z+1].flag > 1) )
									{
										if( (block[x+1][y-1][z-1].flag > 1 && block[x+1][y][z-1].flag > 1 ) || ( block[x+1][y-1][z+1].flag > 1 && block[x+1][y][z+1].flag > 1 ) )
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y][z].flag = 13;				block[x][y][z].ID = ID13;			block[x][y][z].corner = 1;
											block[x][y+1][z].flag = 13;		block[x][y+1][z].ID = ID13;
											block[x][y+2][z].flag = 13;		block[x][y+2][z].ID = ID13;		block[x][y+2][z].corner = 2;	
											block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 1;
											block[x+1][y+1][z].flag = 12;	block[x+1][y+1][z].ID = ID12;	block[x+1][y+1][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//�E�̉�
						if(block[x+1][y+2][z].flag == 1)
						{
							if(block[x+1][y+2][z-1].flag < 2 && block[x+1][y+2][z+1].flag < 2 )
							{
								if(block[x][y-1][z].flag > 1 && block[x+1][y-1][z].flag > 1)
								{
									if( (block[x][y-1][z-1].flag > 1 && block[x][y][z-1].flag > 1) || (block[x][y-1][z+1].flag > 1 && block[x][y][z+1].flag > 1) )
									{
										if( (block[x+1][y-1][z-1].flag > 1 && block[x+1][y][z-1].flag > 1 ) || ( block[x+1][y-1][z+1].flag > 1 && block[x+1][y][z+1].flag > 1 ) )
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y][z].flag = 12;				block[x][y][z].ID = ID12;			block[x][y][z].corner = 1;
											block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;		block[x][y+1][z].corner = 2;	
											block[x+1][y][z].flag = 13;		block[x+1][y][z].ID = ID13;		block[x+1][y][z].corner = 1;
											block[x+1][y+1][z].flag = 13;	block[x+1][y+1][z].ID = ID13;	
											block[x+1][y+2][z].flag = 13;	block[x+1][y+2][z].ID = ID13;	block[x+1][y+2][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
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
			for(x = 0; x<VoxSize[0]-1; x=x+2)
			{
				for(y = 0; y<VoxSize[1]-1; y=y+2)
				{
					//���ڂ̂Q�~�Q�̃}�X�N�̃t���O���S�������Ă�����
					if(block[x][y][z].flag == 4 && block[x+1][y+1][z].flag == 4)
					{
						//��̍�
						if(block[x-1][y][z].flag == 1)
						{
							//1�̏㉺�̃{�N�Z����flag���Ƃ��ɂP�܂��͂O�Ȃ��(�����̔���������܂Ō��������Ȃ��Ă�������������Ȃ��H)
							if(block[x-1][y][z-1].flag < 2 && block[x-1][y][z+1].flag < 2 )
							{
								if(block[x+2][y][z].flag > 1 && block[x+2][y+1][z].flag > 1)	//flag�̒l��2�ȏ�ł����
								{
									if( (block[x+1][y][z-1].flag > 1 &&  block[x+2][y][z-1].flag > 1 ) || (block[x+1][y][z+1].flag > 1  && block[x+2][y][z+1].flag > 1) )
									{
										if( (block[x+1][y+1][z-1].flag > 1 && block[x+2][y+1][z-1].flag > 1) || (block[x+1][y+1][z+1].flag > 1 && block[x+2][y+1][z+1].flag > 1 ))
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y+1][z].flag = 12;			block[x][y+1][z].ID = ID12;			block[x][y+1][z].corner = 1;
											block[x+1][y+1][z].flag = 12;		block[x+1][y+1][z].ID = ID12;		block[x+1][y+1][z].corner = 2;	
											block[x-1][y][z].flag = 13;				block[x-1][y][z].ID = ID13;			block[x-1][y][z].corner = 1;
											block[x][y][z].flag = 13;					block[x][y][z].ID = ID13;	
											block[x+1][y][z].flag = 13;			block[x+1][y][z].ID = ID13;			block[x+1][y][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//��̉E
						if(block[x-1][y+1][z].flag == 1)
						{
							if(block[x-1][y+1][z-1].flag < 2 && block[x-1][y+1][z+1].flag < 2 )
							{
								if(block[x+2][y][z].flag > 1 && block[x+2][y+1][z].flag > 1)
								{
									if( (block[x+1][y][z-1].flag > 1 &&  block[x+2][y][z-1].flag > 1 ) || (block[x+1][y][z+1].flag > 1  && block[x+2][y][z+1].flag > 1) )
									{
										if( (block[x+1][y+1][z-1].flag > 1 && block[x+2][y+1][z-1].flag > 1) || (block[x+1][y+1][z+1].flag > 1 && block[x+2][y+1][z+1].flag > 1 ))
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x-1][y+1][z].flag = 13;			block[x-1][y+1][z].ID = ID13;		block[x-1][y+1][z].corner = 1;
											block[x][y+1][z].flag = 13;			block[x][y+1][z].ID = ID13;
											block[x+1][y+1][z].flag = 13;		block[x+1][y+1][z].ID = ID13;		block[x+1][y+1][z].corner = 2;	
											block[x][y][z].flag = 12;					block[x][y][z].ID = ID12;				block[x][y][z].corner = 1;
											block[x+1][y][z].flag = 12;			block[x+1][y][z].ID = ID12;			block[x+1][y][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//���̏�
						if(block[x][y-1][z].flag == 1)
						{
							if(block[x][y-1][z-1].flag < 2 && block[x][y-1][z+1].flag < 2 )
							{
								if(block[x][y+2][z].flag > 1 && block[x+1][y+2][z].flag > 1)
								{
									if( (block[x][y+1][z-1].flag > 1 && block[x][y+2][z-1].flag > 1 ) || (block[x][y+1][z+1].flag > 1 && block[x][y+2][z+1].flag > 1) )
									{
										if((block[x+1][y+1][z-1].flag > 1 && block[x+1][y+2][z-1].flag > 1) || (block[x+1][y+1][z+1].flag > 1 && block[x+1][y+2][z+1].flag > 1))
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y-1][z].flag = 13;			block[x][y-1][z].ID = ID13;		block[x][y-1][z].corner = 1;
											block[x][y][z].flag = 13;				block[x][y][z].ID = ID13;
											block[x][y+1][z].flag = 13;		block[x][y+1][z].ID = ID13;		block[x][y+1][z].corner = 2;	
											block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 1;	
											block[x+1][y+1][z].flag = 12;	block[x+1][y+1][z].ID = ID12;	block[x+1][y+1][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//���̉�
						if(block[x+1][y-1][z].flag == 1)
						{
							if(block[x+1][y-1][z-1].flag < 2 && block[x+1][y-1][z+1].flag < 2 )
							{
								if(block[x][y+2][z].flag > 1 && block[x+1][y+2][z].flag > 1)
								{
									if( (block[x][y+1][z-1].flag > 1 && block[x][y+2][z-1].flag > 1 ) || (block[x][y+1][z+1].flag > 1 && block[x][y+2][z+1].flag > 1) )
									{
										if((block[x+1][y+1][z-1].flag > 1 && block[x+1][y+2][z-1].flag > 1) || (block[x+1][y+1][z+1].flag > 1 && block[x+1][y+2][z+1].flag > 1))
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y][z].flag = 12;				block[x][y][z].ID = ID12;			block[x][y][z].corner = 1;
											block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;		block[x][y+1][z].corner = 2;	
											block[x+1][y-1][z].flag = 13;		block[x+1][y-1][z].ID = ID13;	block[x+1][y-1][z].corner = 1;
											block[x+1][y][z].flag = 13;		block[x+1][y][z].ID = ID13;	
											block[x+1][y+1][z].flag = 13;	block[x+1][y+1][z].ID = ID13;	block[x+1][y+1][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//���̍�
						if(block[x+2][y][z].flag == 1)
						{
							if(block[x+2][y][z-1].flag < 2 && block[x+2][y][z+1].flag < 2 )
							{
								if(block[x-1][y][z].flag > 1 && block[x-1][y+1][z].flag > 1)
								{
									if( (block[x-1][y][z-1].flag > 1 && block[x][y][z-1].flag > 1) || (block[x-1][y][z+1].flag > 1 && block[x][y][z+1].flag > 1) )
									{
										if( ( block[x-1][y+1][z-1].flag > 1 && block[x][y+1][z-1].flag > 1) || (block[x-1][y+1][z+1].flag > 1 && block[x][y+1][z+1].flag > 1) )
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y+1][z].flag = 12;			block[x][y+1][z].ID = ID12;		block[x][y+1][z].corner = 1;
											block[x+1][y+1][z].flag = 12;		block[x+1][y+1][z].ID = ID12;	block[x+1][y+1][z].corner = 2;	
											block[x][y][z].flag = 13;					block[x][y][z].ID = ID13;			block[x][y][z].corner = 1;	
											block[x+1][y][z].flag = 13;			block[x+1][y][z].ID = ID13;
											block[x+2][y][z].flag = 13;			block[x+2][y][z].ID = ID13;		block[x+2][y][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//���̉E
						if(block[x+2][y+1][z].flag == 1)
						{
							if(block[x+2][y+1][z-1].flag < 2 && block[x+2][y+1][z+1].flag < 2 )
							{
								if(block[x-1][y][z].flag > 1 && block[x-1][y+1][z].flag > 1)
								{
									if( (block[x-1][y][z-1].flag > 1 && block[x][y][z-1].flag > 1) || (block[x-1][y][z+1].flag > 1 && block[x][y][z+1].flag > 1) )
									{
										if( ( block[x-1][y+1][z-1].flag > 1 && block[x][y+1][z-1].flag > 1) || (block[x-1][y+1][z+1].flag > 1 && block[x][y+1][z+1].flag > 1) )
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y+1][z].flag = 13;			block[x][y+1][z].ID = ID13;		block[x][y+1][z].corner = 1;
											block[x+1][y+1][z].flag = 13;		block[x+1][y+1][z].ID = ID13;	
											block[x+2][y+1][z].flag = 13;		block[x+2][y+1][z].ID = ID13;	block[x+2][y+1][z].corner = 2;
											block[x][y][z].flag = 12;					block[x][y][z].ID = ID12;			block[x][y][z].corner = 1;	
											block[x+1][y][z].flag = 12;			block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}

						//�E�̏�
						if(block[x][y+2][z].flag == 1)
						{
							if(block[x][y+2][z-1].flag < 2 && block[x][y+2][z+1].flag < 2 )
							{
								if(block[x][y-1][z].flag > 1 && block[x+1][y-1][z].flag > 1)
								{
									if( (block[x][y-1][z-1].flag > 1 && block[x][y][z-1].flag > 1) || (block[x][y-1][z+1].flag > 1 && block[x][y][z+1].flag > 1) )
									{
										if( (block[x+1][y-1][z-1].flag > 1 && block[x+1][y][z-1].flag > 1 ) || ( block[x+1][y-1][z+1].flag > 1 && block[x+1][y][z+1].flag > 1 ) )
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y][z].flag = 13;				block[x][y][z].ID = ID13;			block[x][y][z].corner = 1;
											block[x][y+1][z].flag = 13;		block[x][y+1][z].ID = ID13;
											block[x][y+2][z].flag = 13;		block[x][y+2][z].ID = ID13;		block[x][y+2][z].corner = 2;	
											block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 1;
											block[x+1][y+1][z].flag = 12;	block[x+1][y+1][z].ID = ID12;	block[x+1][y+1][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//�E�̉�
						if(block[x+1][y+2][z].flag == 1)
						{
							if(block[x+1][y+2][z-1].flag < 2 && block[x+1][y+2][z+1].flag < 2 )
							{
								if(block[x][y-1][z].flag > 1 && block[x+1][y-1][z].flag > 1)
								{
									if( (block[x][y-1][z-1].flag > 1 && block[x][y][z-1].flag > 1) || (block[x][y-1][z+1].flag > 1 && block[x][y][z+1].flag > 1) )
									{
										if( (block[x+1][y-1][z-1].flag > 1 && block[x+1][y][z-1].flag > 1 ) || ( block[x+1][y-1][z+1].flag > 1 && block[x+1][y][z+1].flag > 1 ) )
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y][z].flag = 12;				block[x][y][z].ID = ID12;			block[x][y][z].corner = 1;
											block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;		block[x][y+1][z].corner = 2;	
											block[x+1][y][z].flag = 13;		block[x+1][y][z].ID = ID13;		block[x+1][y][z].corner = 1;
											block[x+1][y+1][z].flag = 13;	block[x+1][y+1][z].ID = ID13;	
											block[x+1][y+2][z].flag = 13;	block[x+1][y+2][z].ID = ID13;	block[x+1][y+2][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	cout<<count<<"�̂P�~�P�ƂQ�~�Q����P�~�R�ƂP�~�Q���ł����I"<<endl;
	//outputFlag("test03_11_22_to_13_12.txt", VoxSize);

}