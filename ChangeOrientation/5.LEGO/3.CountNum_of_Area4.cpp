#include "../stdafx.h"

extern int num11;		//�P�~�P�̃u���b�N�̐�
extern int num12;		//�P�~�Q�̃u���b�N�̐�
extern int num22;		//�Q�~�Q�̃u���b�N�̐�

extern int ID12;
extern int ID22;

void outputFlag(string filename, int* size);

void CountNum_of_4(Lego*** block, int* VoxSize)
{
	unsigned short count4(0);			
	int x, y, z;
	
	for (z = 1; z < VoxSize[2] - 1; z = z + 2)				//����1,3,5,...
	{
		for (x = 1; x < VoxSize[0] - 1; x = x + 2)
		{
			for (y = 1; y < VoxSize[1] - 1; y = y + 2)
			{
				count4 = 0;			//������
				//�S�̃{�N�Z�������ĉ��������{�N�Z���Ȃ̂����J�E���g�i�����v�܂��j
				if (block[x][y][z].fill)					count4++;
				if (block[x][y + 1][z].fill)				count4++;
				if (block[x + 1][y + 1][z].fill)			count4++;
				if (block[x + 1][y][z].fill)				count4++;

				//�e�{�N�Z����ID�����Ă���
				if (block[x][y][z].fill)					block[x][y][z].flag = count4;
				if (block[x][y + 1][z].fill)				block[x][y + 1][z].flag = count4;
				if (block[x + 1][y + 1][z].fill)			block[x + 1][y + 1][z].flag = count4;
				if (block[x + 1][y][z].fill)				block[x + 1][y][z].flag = count4;

				if (count4 == 1)				//�P�~�P�̐������Z
					num11++;
				else if (count4 == 4)		//�Q�~�Q�̐������Z
					num22++;
				//count4=2�LEGO
				else if (count4 == 2)
				{
					if (block[x][y][z].fill == true && block[x + 1][y + 1][z].fill == true)	//�Ίp���ɂȂ�P�[�X�P
					{
						block[x][y][z].flag = 1;
						block[x + 1][y + 1][z].flag = 1;
					}
					else if (block[x + 1][y][z].fill == true && block[x][y + 1][z].fill == true)	//�Ίp���ɂȂ�P�[�X�Q
					{
						block[x + 1][y][z].flag = 1;
						block[x][y + 1][z].flag = 1;
					}
					else
						num12++;		//�P�~�Q�̐������Z
				}
			}
		}
	}

	for (z = 2; z < VoxSize[2] - 1; z = z + 2)				//����2,4,6,...
	{
		for (x = 0; x < VoxSize[0] - 1; x = x + 2)
		{
			for (y = 0; y < VoxSize[1] - 1; y = y + 2)
			{
				count4 = 0;			//������
				//�S�̃{�N�Z�������ĉ��������{�N�Z���Ȃ̂����J�E���g�i�����v�܂��j
				if (block[x][y][z].fill)					count4++;
				if (block[x][y + 1][z].fill)				count4++;
				if (block[x + 1][y + 1][z].fill)			count4++;
				if (block[x + 1][y][z].fill)				count4++;

				//�e�{�N�Z����ID�����Ă���
				if (block[x][y][z].fill)					block[x][y][z].flag = count4;
				if (block[x][y + 1][z].fill)				block[x][y + 1][z].flag = count4;
				if (block[x + 1][y + 1][z].fill)			block[x + 1][y + 1][z].flag = count4;
				if (block[x + 1][y][z].fill)				block[x + 1][y][z].flag = count4;

				if (count4 == 1)				//�P�~�P�̐������Z
					num11++;
				else if (count4 == 4)		//�Q�~�Q�̐������Z
					num22++;

				//count4=2�̎��̗�O�����@���LEGO�u���b�N���Ίp���ɂ���Ƃ�
				else if (count4 == 2)
				{
					if (block[x][y][z].fill == true && block[x + 1][y + 1][z].fill == true)	//�Ίp���ɂȂ�P�[�X�P
					{
						block[x][y][z].flag = 1;
						block[x + 1][y + 1][z].flag = 1;
					}
					else if (block[x + 1][y][z].fill == true && block[x][y + 1][z].fill == true)	//�Ίp���ɂȂ�P�[�X�Q
					{
						block[x + 1][y][z].flag = 1;
						block[x][y + 1][z].flag = 1;
					}
					else
						num12++;
				}
			}
		}
	}

	string file1("test.txt");
	outputFlag(file1, VoxSize);
	//step1�����܂�


}

//2013/9/14

//void CountNum_of_4_ID(Lego*** block, int* VoxSize)
//{
//	unsigned short count4(0);			//�Q�~�Q�}�X�̒��ɑ��݂���{�N�Z�����J�E���g
//	int x,y,z;
//	//��w�@���_�i�P�C�P�j
//	for(z=1; z < VoxSize[2]-1; z = z + 2 )				//����1,3,5,...
//	{
//		for(x=1; x < VoxSize[0]-1; x = x + 2)
//		{
//			for(y=1; y < VoxSize[1]-1; y = y + 2)
//			{
//				count4 = 0;			//������
//				//�S�̃{�N�Z�������ĉ��������{�N�Z���Ȃ̂����J�E���g�i�����v�܂��j
//				if(block[x][y][z].fill)					count4++;
//				if(block[x][y+1][z].fill)				count4++;
//				if(block[x+1][y+1][z].fill)			count4++;
//				if(block[x+1][y][z].fill)				count4++;
//
//				//�e�{�N�Z����ID�����Ă���
//				if(block[x][y][z].fill)					block[x][y][z].flag = count4;
//				if(block[x][y+1][z].fill)				block[x][y+1][z].flag = count4;
//				if(block[x+1][y+1][z].fill)			block[x+1][y+1][z].flag = count4;
//				if(block[x+1][y][z].fill)				block[x+1][y][z].flag = count4;
//
//				if(count4 == 1)				//�P�~�P�̐������Z
//					num11++;
//				else if(count4 == 4)		//�Q�~�Q�̐������Z
//				{
//					num22++;
//					ID22++;
//					block[x][y][z].ID = ID22;
//					block[x][y+1][z].ID = ID22;
//					block[x+1][y+1][z].ID = ID22;
//					block[x+1][y][z].ID = ID22;
//				}
//				//count4=2�̎��̗�O�����@���LEGO�u���b�N���Ίp���ɂ���Ƃ�
//				else if(count4 == 2)
//				{
//					//�P�~�Q�ɂȂ�ꍇ
//					if(block[x][y][z].fill)
//					{
//						//�����ɕ��s
//						if(block[x+1][y][z].fill)
//						{
//							num12++;		//�P�~�Q�̐������Z
//							ID12++;
//							block[x][y][z].ID = ID12;
//							block[x+1][y][z].ID = ID12;
//							continue;
//						}
//						//�����ɕ��s
//						else if(block[x][y+1][z].fill)
//						{
//							num12++;		//�P�~�Q�̐������Z
//							ID12++;
//							block[x][y][z].ID = ID12;
//							block[x][y+1][z].ID = ID12;
//							continue;
//						}
//					}
//					if(block[x+1][y+1][z].fill)
//					{
//						//�����ɕ��s
//						if(block[x][y+1][z].fill)
//						{
//							num12++;		//�P�~�Q�̐������Z
//							ID12++;
//							block[x+1][y+1][z].ID = ID12;
//							block[x][y+1][z].ID = ID12;
//							continue;
//						}
//						//�����ɕ��s
//						else if(block[x+1][y][z].fill)
//						{
//							num12++;		//�P�~�Q�̐������Z
//							ID12++;
//							block[x+1][y+1][z].ID = ID12;
//							block[x+1][y][z].ID = ID12;
//							continue;
//						}
//					}
//
//					//�Ίp����ɂ���ꍇ�̏ꍇ
//					if(block[x][y][z].fill == true && block[x+1][y+1][z].fill == true)	//�Ίp���ɂȂ�P�[�X�P
//					{
//						block[x][y][z].flag = 1;				
//						block[x+1][y+1][z].flag = 1;
//					}
//					else if(block[x+1][y][z].fill == true && block[x][y+1][z].fill == true)	//�Ίp���ɂȂ�P�[�X�Q
//					{
//						block[x+1][y][z].flag = 1;
//						block[x][y+1][z].flag = 1;
//					}
//
//				}
//			}
//		}
//	}
//
//	//�����w�@���_�i�Q�C�Q�j
//	for(z=2; z < VoxSize[2]-1; z = z + 2 )				//����2,4,6,...
//	{
//		for(x=0; x < VoxSize[0]-1; x = x + 2)
//		{
//			for(y=0; y < VoxSize[1]-1; y = y + 2)
//			{
//				count4 = 0;			//������
//				//�S�̃{�N�Z�������ĉ��������{�N�Z���Ȃ̂����J�E���g�i�����v�܂��j
//				if(block[x][y][z].fill)					count4++;
//				if(block[x][y+1][z].fill)				count4++;
//				if(block[x+1][y+1][z].fill)			count4++;
//				if(block[x+1][y][z].fill)				count4++;
//
//				//�e�{�N�Z����ID�����Ă���
//				if(block[x][y][z].fill)					block[x][y][z].flag = count4;
//				if(block[x][y+1][z].fill)				block[x][y+1][z].flag = count4;
//				if(block[x+1][y+1][z].fill)			block[x+1][y+1][z].flag = count4;
//				if(block[x+1][y][z].fill)				block[x+1][y][z].flag = count4;
//
//				if(count4 == 1)				//�P�~�P�̐������Z
//					num11++;
//				else if(count4 == 4)		//�Q�~�Q�̐������Z
//				{
//					num22++;
//					ID22++;
//					block[x][y][z].ID = ID22;
//					block[x][y+1][z].ID = ID22;
//					block[x+1][y+1][z].ID = ID22;
//					block[x+1][y][z].ID = ID22;
//				}
//				//count4=2�̎��̗�O�����@���LEGO�u���b�N���Ίp���ɂ���Ƃ�
//				else if(count4 == 2)
//				{
//					//�P�~�Q�ɂȂ�ꍇ
//					if(block[x][y][z].fill)
//					{
//						//�����ɕ��s
//						if(block[x+1][y][z].fill)
//						{
//							num12++;		//�P�~�Q�̐������Z
//							ID12++;
//							block[x][y][z].ID = ID12;
//							block[x+1][y][z].ID = ID12;
//							continue;
//						}
//						//�����ɕ��s
//						else if(block[x][y+1][z].fill)
//						{
//							num12++;		//�P�~�Q�̐������Z
//							ID12++;
//							block[x][y][z].ID = ID12;
//							block[x][y+1][z].ID = ID12;
//							continue;
//						}
//					}
//					if(block[x+1][y+1][z].fill)
//					{
//						//�����ɕ��s
//						if(block[x][y+1][z].fill)
//						{
//							num12++;		//�P�~�Q�̐������Z
//							ID12++;
//							block[x+1][y+1][z].ID = ID12;
//							block[x][y+1][z].ID = ID12;
//							continue;
//						}
//						//�����ɕ��s
//						else if(block[x+1][y][z].fill)
//						{
//							num12++;		//�P�~�Q�̐������Z
//							ID12++;
//							block[x+1][y+1][z].ID = ID12;
//							block[x+1][y][z].ID = ID12;
//							continue;
//						}
//					}
//
//					//�Ίp����ɂ���ꍇ�̏ꍇ
//					if(block[x][y][z].fill == true && block[x+1][y+1][z].fill == true)	//�Ίp���ɂȂ�P�[�X�P
//					{
//						block[x][y][z].flag = 1;				
//						block[x+1][y+1][z].flag = 1;
//					}
//					else if(block[x+1][y][z].fill == true && block[x][y+1][z].fill == true)	//�Ίp���ɂȂ�P�[�X�Q
//					{
//						block[x+1][y][z].flag = 1;
//						block[x][y+1][z].flag = 1;
//					}
//				}
//			}
//		}
//	}
//
//	//string file1("test.txt");
//	//outputFlag(file1, VoxSize);
//	//step1�����܂�
//
//}

//2014/5/21
void CountNum_of_4_ID(Lego*** block, int* VoxSize)
{
	unsigned short count4(0);			//�Q�~�Q�}�X�̒��ɑ��݂���{�N�Z�����J�E���g
	unsigned short Ccount(0);			//�Q�~�Q�}�X�̒��ɑ��݂��铯�F�{�N�Z�����J�E���g
	unsigned short Scount(0);			//�Q�~�Q�}�X�̒��ɑ��݂���\�ʃ{�N�Z�����J�E���g
	int x, y, z;
	//��w�@���_�i�P�C�P�j
	for (z = 1; z < VoxSize[2] - 1; z = z + 2)				//����1,3,5,...
	{
		for (x = 1; x < VoxSize[0] - 1; x = x + 2)
		{
			for (y = 1; y < VoxSize[1] - 1; y = y + 2)
			{
				int CoC[8] = { 0,0,0,0,0,0,0,0 };
				count4 = 0;			//������
				Ccount = 0;			//������
				//�S�̃{�N�Z�������ĉ��������{�N�Z���Ȃ̂����J�E���g�i�����v�܂��j
				if (block[x][y][z].fill)					count4++;
				if (block[x][y + 1][z].fill)				count4++;
				if (block[x + 1][y + 1][z].fill)			count4++;
				if (block[x + 1][y][z].fill)				count4++;

				if (block[x][y][z].fill)					CoC[block[x][y][z].ColorID]++;
				if (block[x][y + 1][z].fill)				CoC[block[x][y + 1][z].ColorID]++;
				if (block[x + 1][y + 1][z].fill)			CoC[block[x + 1][y + 1][z].ColorID]++;
				if (block[x + 1][y][z].fill)				CoC[block[x + 1][y][z].ColorID]++;

				if (block[x][y][z].surf)					Scount++;
				if (block[x][y + 1][z].surf)				Scount++;
				if (block[x + 1][y + 1][z].surf)			Scount++;
				if (block[x + 1][y][z].surf)				Scount++;
				for (int i(1); i < 8; i++) {
					if (CoC[i] > 0)
						Ccount++;
				}
				//ID
				if (block[x][y][z].fill)					block[x][y][z].flag = count4;
				if (block[x][y + 1][z].fill)				block[x][y + 1][z].flag = count4;
				if (block[x + 1][y + 1][z].fill)			block[x + 1][y + 1][z].flag = count4;
				if (block[x + 1][y][z].fill)				block[x + 1][y][z].flag = count4;

				//4
				if (count4 == 4 && Ccount < 2) {
					num22++;
					ID22++;
					block[x][y][z].ID = ID22;
					block[x][y + 1][z].ID = ID22;
					block[x + 1][y + 1][z].ID = ID22;
					block[x + 1][y][z].ID = ID22;
				}
				else if (count4 == 4 && Ccount > 1) {
					block[x][y][z].flag = 1;
					block[x][y + 1][z].flag = 1;
					block[x + 1][y + 1][z].flag = 1;
					block[x + 1][y][z].flag = 1;
					num11 = num11 + 4;
				}
				//else {
				//	if((block[x][y][z].ColorID==0&&block[x][y+1][z].ColorID==0)||
				//		(block[x][y][z].ColorID>0&&block[x][y+1][z].ColorID>0)){
				//			num12++;		//�P�~�Q�̐������Z
				//			ID12++;
				//			block[x][y][z].ID = ID12;
				//			block[x+1][y][z].ID = ID12;
				//			num12++;		//�P�~�Q�̐������Z
				//			ID12++;
				//			block[x][y+1][z].ID = ID12;
				//			block[x+1][y+1][z].ID = ID12;					
				//	}
				//	else if((block[x][y][z].ColorID==0&&block[x+1][y][z].ColorID==0)||
				//		(block[x][y][z].ColorID>0&&block[x+1][y][z].ColorID>0)){
				//			num12++;		//�P�~�Q�̐������Z
				//			ID12++;
				//			block[x][y][z].ID = ID12;
				//			block[x+1][y][z].ID = ID12;
				//			num12++;		//�P�~�Q�̐������Z
				//			ID12++;
				//			block[x][y+1][z].ID = ID12;
				//			block[x+1][y+1][z].ID = ID12;								
				//	}
				//	else{
				//			num12++;		//�P�~�Q�̐������Z
				//			ID12++;
				//			block[x][y][z].ID = ID12;
				//			block[x][y+1][z].ID = ID12;
				//			num12++;		//�P�~�Q�̐������Z
				//			ID12++;
				//			block[x+1][y][z].ID = ID12;
				//			block[x+1][y+1][z].ID = ID12;										
				//	}
				//}
				//3�̏ꍇ
				if (count4 == 3 && Ccount > 1) {
					if (block[x][y][z].fill)	block[x][y][z].flag = 1;
					if (block[x][y + 1][z].fill)   block[x][y + 1][z].flag = 1;
					if (block[x + 1][y + 1][z].fill)   block[x + 1][y + 1][z].flag = 1;
					if (block[x + 1][y][z].fill)   block[x + 1][y][z].flag = 1;
					num11 = num11 + 3;
				}

				if (count4 == 1)				//�P�~�P�̐������Z
					num11++;

				//count4=2�̎��̗�O�����@���LEGO�u���b�N���Ίp���ɂ���Ƃ�
				else if (count4 == 2)
				{
					//�P�~�Q�ɂȂ�ꍇ
					if (block[x][y][z].fill)
					{
						//�����ɕ��s
						if (block[x + 1][y][z].fill)
						{
							if (block[x][y][z].ColorID == block[x + 1][y][z].ColorID
								|| (block[x][y][z].ColorID == 0 || block[x + 1][y][z].ColorID == 0)) {
								num12++;		//�P�~�Q�̐������Z
								ID12++;
								block[x][y][z].ID = ID12;
								block[x + 1][y][z].ID = ID12;
								block[x][y][z].flag = 2;
								block[x + 1][y][z].flag = 2;
								continue;
							}
							else {
								num11++;
								num11++;
								block[x][y][z].flag = 1;
								block[x + 1][y][z].flag = 1;
							}
						}
						//�����ɕ��s
						else if (block[x][y + 1][z].fill)
						{
							if (block[x][y][z].ColorID == block[x][y + 1][z].ColorID ||
								(block[x][y][z].ColorID == 0 || block[x][y + 1][z].ColorID == 0)) {
								num12++;		//�P�~�Q�̐������Z
								ID12++;
								block[x][y][z].ID = ID12;
								block[x][y + 1][z].ID = ID12;
								block[x][y][z].flag = 2;
								block[x][y + 1][z].flag = 2;
								continue;
							}
							else {
								num11++;
								num11++;
								block[x][y][z].flag = 1;
								block[x][y + 1][z].flag = 1;
							}
						}
					}
					if (block[x + 1][y + 1][z].fill)
					{
						//�����ɕ��s
						if (block[x][y + 1][z].fill)
						{
							if (block[x + 1][y + 1][z].ColorID == block[x][y + 1][z].ColorID
								|| (block[x + 1][y + 1][z].ColorID == 0 || block[x][y + 1][z].ColorID == 0)) {
								num12++;		//�P�~�Q�̐������Z
								ID12++;
								block[x + 1][y + 1][z].ID = ID12;
								block[x][y + 1][z].ID = ID12;
								block[x + 1][y + 1][z].flag = 2;
								block[x][y + 1][z].flag = 2;
								continue;
							}
							else {
								num11++;
								num11++;
								block[x + 1][y + 1][z].flag = 1;
								block[x][y + 1][z].flag = 1;
							}
						}
						//�����ɕ��s
						else if (block[x + 1][y][z].fill)
						{
							if (block[x + 1][y + 1][z].ColorID == block[x + 1][y][z].ColorID
								|| (block[x + 1][y + 1][z].ColorID == 0 || block[x + 1][y][z].ColorID == 0)) {
								num12++;		//�P�~�Q�̐������Z
								ID12++;
								block[x + 1][y + 1][z].ID = ID12;
								block[x + 1][y][z].ID = ID12;
								block[x + 1][y + 1][z].flag = 2;
								block[x + 1][y][z].flag = 2;
								continue;
							}
							else {
								num11++;
								num11++;
								block[x + 1][y + 1][z].flag = 1;
								block[x + 1][y][z].flag = 1;
							}
						}
					}

					//�Ίp����ɂ���ꍇ�̏ꍇ
					if (block[x][y][z].fill == true && block[x + 1][y + 1][z].fill == true)	//�Ίp���ɂȂ�P�[�X�P
					{
						block[x][y][z].flag = 1;
						block[x + 1][y + 1][z].flag = 1;
						num11++;
						num11++;
					}
					else if (block[x + 1][y][z].fill == true && block[x][y + 1][z].fill == true)	//�Ίp���ɂȂ�P�[�X�Q
					{
						block[x + 1][y][z].flag = 1;
						block[x][y + 1][z].flag = 1;
						num11++;
						num11++;
					}

				}
			}
		}
	}

	//�����w�@���_�i�Q�C�Q�j
	for (z = 2; z < VoxSize[2] - 1; z = z + 2)				//����2,4,6,...
	{
		for (x = 0; x < VoxSize[0] - 1; x = x + 2)
		{
			for (y = 0; y < VoxSize[1] - 1; y = y + 2)
			{
				int CoC[8] = { 0,0,0,0,0,0,0,0 };
				count4 = 0;			//������
				Ccount = 0;			//������
				//�S�̃{�N�Z�������ĉ��������{�N�Z���Ȃ̂����J�E���g�i�����v�܂��j
				if (block[x][y][z].fill)					count4++;
				if (block[x][y + 1][z].fill)				count4++;
				if (block[x + 1][y + 1][z].fill)			count4++;
				if (block[x + 1][y][z].fill)				count4++;

				if (block[x][y][z].fill)					CoC[block[x][y][z].ColorID]++;
				if (block[x][y + 1][z].fill)				CoC[block[x][y + 1][z].ColorID]++;
				if (block[x + 1][y + 1][z].fill)			CoC[block[x + 1][y + 1][z].ColorID]++;
				if (block[x + 1][y][z].fill)				CoC[block[x + 1][y][z].ColorID]++;

				if (block[x][y][z].surf)					Scount++;
				if (block[x][y + 1][z].surf)				Scount++;
				if (block[x + 1][y + 1][z].surf)			Scount++;
				if (block[x + 1][y][z].surf)				Scount++;
				for (int i(1); i < 8; i++) {
					if (CoC[i] > 0)
						Ccount++;
				}
				//�e�{�N�Z����ID�����Ă���
				if (block[x][y][z].fill)					block[x][y][z].flag = count4;
				if (block[x][y + 1][z].fill)				block[x][y + 1][z].flag = count4;
				if (block[x + 1][y + 1][z].fill)			block[x + 1][y + 1][z].flag = count4;
				if (block[x + 1][y][z].fill)				block[x + 1][y][z].flag = count4;

				//4����ꍇ
				if (count4 == 4 && Ccount < 2) {
					num22++;
					ID22++;
					block[x][y][z].ID = ID22;
					block[x][y + 1][z].ID = ID22;
					block[x + 1][y + 1][z].ID = ID22;
					block[x + 1][y][z].ID = ID22;
				}
				else if (count4 == 4 && Ccount > 1) {
					block[x][y][z].flag = 1;
					block[x][y + 1][z].flag = 1;
					block[x + 1][y + 1][z].flag = 1;
					block[x + 1][y][z].flag = 1;
					num11 = num11 + 4;
				}
				//else {
				//	if((block[x][y][z].ColorID==0&&block[x][y+1][z].ColorID==0)||
				//		(block[x][y][z].ColorID>0&&block[x][y+1][z].ColorID>0)){
				//			num12++;		//�P�~�Q�̐������Z
				//			ID12++;
				//			block[x][y][z].ID = ID12;
				//			block[x+1][y][z].ID = ID12;
				//			num12++;		//�P�~�Q�̐������Z
				//			ID12++;
				//			block[x][y+1][z].ID = ID12;
				//			block[x+1][y+1][z].ID = ID12;					
				//	}
				//	else if((block[x][y][z].ColorID==0&&block[x+1][y][z].ColorID==0)||
				//		(block[x][y][z].ColorID>0&&block[x+1][y][z].ColorID>0)){
				//			num12++;		//�P�~�Q�̐������Z
				//			ID12++;
				//			block[x][y][z].ID = ID12;
				//			block[x+1][y][z].ID = ID12;
				//			num12++;		//�P�~�Q�̐������Z
				//			ID12++;
				//			block[x][y+1][z].ID = ID12;
				//			block[x+1][y+1][z].ID = ID12;								
				//	}
				//	else{
				//			num12++;		//�P�~�Q�̐������Z
				//			ID12++;
				//			block[x][y][z].ID = ID12;
				//			block[x][y+1][z].ID = ID12;
				//			num12++;		//�P�~�Q�̐������Z
				//			ID12++;
				//			block[x+1][y][z].ID = ID12;
				//			block[x+1][y+1][z].ID = ID12;										
				//	}
				//}
				//3�̏ꍇ
				if (count4 == 3 && Ccount > 1) {
					if (block[x][y][z].fill)	block[x][y][z].flag = 1;
					if (block[x][y + 1][z].fill)   block[x][y + 1][z].flag = 1;
					if (block[x + 1][y + 1][z].fill)   block[x + 1][y + 1][z].flag = 1;
					if (block[x + 1][y][z].fill)   block[x + 1][y][z].flag = 1;
					num11 = num11 + 3;
				}

				if (count4 == 1)				//�P�~�P�̐������Z
					num11++;

				//count4=2�̎��̗�O�����@���LEGO�u���b�N���Ίp���ɂ���Ƃ�
				else if (count4 == 2)
				{
					//�P�~�Q�ɂȂ�ꍇ
					if (block[x][y][z].fill)
					{
						//�����ɕ��s
						if (block[x + 1][y][z].fill)
						{
							if (block[x][y][z].ColorID == block[x + 1][y][z].ColorID
								|| (block[x][y][z].ColorID == 0 || block[x + 1][y][z].ColorID == 0)) {
								num12++;		//�P�~�Q�̐������Z
								ID12++;
								block[x][y][z].ID = ID12;
								block[x + 1][y][z].ID = ID12;
								block[x][y][z].flag = 2;
								block[x + 1][y][z].flag = 2;
								continue;
							}
							else {
								num11++;
								num11++;
								block[x][y][z].flag = 1;
								block[x + 1][y][z].flag = 1;
							}
						}
						//�����ɕ��s
						else if (block[x][y + 1][z].fill)
						{
							if (block[x][y][z].ColorID == block[x][y + 1][z].ColorID ||
								(block[x][y][z].ColorID == 0 || block[x][y + 1][z].ColorID == 0)) {
								num12++;		//�P�~�Q�̐������Z
								ID12++;
								block[x][y][z].ID = ID12;
								block[x][y + 1][z].ID = ID12;
								block[x][y][z].flag = 2;
								block[x][y + 1][z].flag = 2;
								continue;
							}
							else {
								num11++;
								num11++;
								block[x][y][z].flag = 1;
								block[x][y + 1][z].flag = 1;
							}
						}
					}
					if (block[x + 1][y + 1][z].fill)
					{
						//�����ɕ��s
						if (block[x][y + 1][z].fill)
						{
							if (block[x + 1][y + 1][z].ColorID == block[x][y + 1][z].ColorID
								|| (block[x + 1][y + 1][z].ColorID == 0 || block[x][y + 1][z].ColorID == 0)) {
								num12++;		//�P�~�Q�̐������Z
								ID12++;
								block[x + 1][y + 1][z].ID = ID12;
								block[x][y + 1][z].ID = ID12;
								block[x + 1][y + 1][z].flag = 2;
								block[x][y + 1][z].flag = 2;
								continue;
							}
							else {
								num11++;
								num11++;
								block[x + 1][y + 1][z].flag = 1;
								block[x][y + 1][z].flag = 1;
							}
						}
						//�����ɕ��s
						else if (block[x + 1][y][z].fill)
						{
							if (block[x + 1][y + 1][z].ColorID == block[x + 1][y][z].ColorID
								|| (block[x + 1][y + 1][z].ColorID == 0 || block[x + 1][y][z].ColorID == 0)) {
								num12++;		//�P�~�Q�̐������Z
								ID12++;
								block[x + 1][y + 1][z].ID = ID12;
								block[x + 1][y][z].ID = ID12;
								block[x + 1][y + 1][z].flag = 2;
								block[x + 1][y][z].flag = 2;
								continue;
							}
							else {
								num11++;
								num11++;
								block[x + 1][y + 1][z].flag = 1;
								block[x + 1][y][z].flag = 1;
							}
						}
					}

					//�Ίp����ɂ���ꍇ�̏ꍇ
					if (block[x][y][z].fill == true && block[x + 1][y + 1][z].fill == true)	//�Ίp���ɂȂ�P�[�X�P
					{
						block[x][y][z].flag = 1;
						block[x + 1][y + 1][z].flag = 1;
						num11++;
						num11++;
					}
					else if (block[x + 1][y][z].fill == true && block[x][y + 1][z].fill == true)	//�Ίp���ɂȂ�P�[�X�Q
					{
						block[x + 1][y][z].flag = 1;
						block[x][y + 1][z].flag = 1;
						num11++;
						num11++;
					}

				}
			}
		}
	}

	//string file1("test.txt");
	//outputFlag(file1, VoxSize);
	//step1�����܂�

}