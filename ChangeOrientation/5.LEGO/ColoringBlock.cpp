#include "../stdafx.h"

void  LegoRGB_to_Lab(Model& m);
CColor RGB_to_Lab(CColor& rgb);
double DeltaE(CColor& aa, CColor& bb);
int GetSimilarColor(CColor temp, vector<CColor>& LegoColor);

extern unsigned int** BlockNum;
extern unsigned int Block_colorNum;				//�g�p����F�̎��
extern unsigned int Block_varietyNum;			//�g�p�����{�u���b�N�̎��
extern vector<Brick> LDD;
extern BrickTable table;
extern CMatrix rot[2];

//2013/9/23

void ColoringBlock_lavest(Model& m, Lego*** b)
{
	int x,y,z;
	CColor temp( 0.0, 0.0, 0.0);
	int blocknum(0);				//�P�̃u���b�N�ɐF�t���̃{�N�Z�������܂ނ�
	int min_no(0);					//�ŏ��l�����ԖڂȂ̂�
	CColor anycolor(2.0, 0.0, 0.0);		//�F�̂Ȃ��u���b�N�ɂ���F(��ق�OpenDraw�ŕ`�悷��Ƃ��g��)
	Brick tempB;

	//#####################################
	//#####################################
	Block_colorNum = m.LegoColor.size() + 1;		//���S�̐F�̐��i�{�P�͖��F�̐��j
	
	BlockNum = new unsigned int * [Block_varietyNum];
	for(int i(0); i<Block_varietyNum; i++)
		BlockNum[i] = new unsigned int [Block_colorNum];

	//������
	for(int i(0); i<Block_varietyNum; i++)
		for(int k(0); k<Block_colorNum; k++)
			BlockNum[i][k] = 0;

	rot[0].assign(3);
	rot[1].assign(3);

	rot[0].IdentifyMatrix();		//�P�ʍs��
	rot[1].SetZero();		//������LDD�i���������̃\�[�X��j90����]
	rot[1][0][2] = 1.0;
	rot[1][1][1] = 1.0;
	rot[1][2][0] = -1.0;

	double xyD(0.8);			//�������ʂւǂꂭ�炢�ړ����邩
	double zD(0.96);			//�P�w�オ��Ƃǂꂭ�炢�ړ����邩

	//�����̃u���b�N���폜������̑Ή������Ă��Ȃ�
	for(z=1; z<m.num[2]-1; z++)
	{
		for(x=1; x<m.num[0]-1; x++)
		{
			for(y=1; y<m.num[1]-1; y++)
			{
				//cout<<x<<" "<<y<<" "<<z<<endl;
				//###################################
				//�P�~�P�̏ꍇ
				//###################################
				if(b[x][y][z].flag == 1)
				{
					tempB.clear();
					if(b[x][y][z].surf)
					{
						temp = m.Voxel_colors[x][y][z];
						min_no = GetSimilarColor(temp, m.LegoColor_Lab);
						m.Voxel_colors[x][y][z] = m.LegoColor[min_no];
						BlockNum[0][min_no]++;
						tempB.DesignID = table.DesignID[0];
						tempB.colorID = table.ColorID[min_no];
						tempB.itemNos = table.itemNos[0][min_no];
					}
					else
					{
						m.Voxel_colors[x][y][z] = anycolor;
						BlockNum[0][Block_colorNum-1]++;
						tempB.DesignID = table.DesignID[0];
						tempB.colorID = table.ColorID[table.ColorID.size() - 1];
						tempB.itemNos = table.itemNos[0][table.ColorID.size() - 1];
					}
					tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
					tempB.trans.y = (z-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
					tempB.trans.z = 0.4+(x-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
					tempB.rn = 0;
					LDD.push_back(tempB);
				}
				//####################################
				//�܂�u���b�N������ꍇ
				//####################################
				else if(b[x][y][z].flag > 1)
				{
					if(b[x][y][z].corner != 1)
						continue;
					tempB.clear();
					//###################################
					//�P�~�Q�̏ꍇ
					//###################################
					//else if(b[x][y][z].flag == 12 && b[x][y][z].corner == 1)
					if(b[x][y][z].flag == 12)
					{
						//�P�~�Q���������̏ꍇ(��]�����Ȃ�)
						if(b[x][y+1][z].flag == 12 && b[x][y][z].ID == b[x][y+1][z].ID && b[x][y+1][z].corner == 2)
						{
							blocknum = 0;
							temp.r = 0.0;
							temp.g = 0.0;
							temp.b = 0.0;
							//�\�ʃ{�N�Z���Ȃ�ΐF�����I
							for(int i(0); i<2; i++)
							{							
								//�\�ʃ{�N�Z���Ȃ�΁A�F�����̂�
								if(b[x][y+i][z].surf)
								{
									blocknum++;
									temp.r += m.Voxel_colors[x][y+i][z].r;
									temp.g += m.Voxel_colors[x][y+i][z].g;
									temp.b += m.Voxel_colors[x][y+i][z].b;
								}
							}
							if(blocknum > 0)
							{
								temp.r = temp.r/blocknum;
								temp.g = temp.g/blocknum;
								temp.b = temp.b/blocknum;
								//���S�̐F�ւƒu������
								//���ڕ\�ʃ{�N�Z����RGB����L*a*b*���v�Z
								min_no = GetSimilarColor(temp, m.LegoColor_Lab);
								for(int i(0); i<2; i++)
									m.Voxel_colors[x][y+i][z] = m.LegoColor[min_no];
								BlockNum[1][min_no]++;
								tempB.DesignID = table.DesignID[1];
								tempB.colorID = table.ColorID[min_no];
								tempB.itemNos = table.itemNos[1][min_no];
							}
							else
							{
								for(int i(0); i<2; i++)
									m.Voxel_colors[x][y+i][z] = anycolor;
								BlockNum[1][Block_colorNum-1]++;
								tempB.DesignID = table.DesignID[1];
								tempB.colorID = table.ColorID[table.ColorID.size() - 1];
								tempB.itemNos = table.itemNos[1][table.ColorID.size() - 1];
							}
							tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
							tempB.trans.y = (z-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
							tempB.trans.z = 0.4+(x-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
							tempB.rn = 0;									//��]�����Ȃ�
							LDD.push_back(tempB);
							continue;
						}

						//�P�~�Q���������̏ꍇ�i��]������j
						if(b[x+1][y][z].flag == 12 && b[x][y][z].ID == b[x+1][y][z].ID && b[x+1][y][z].corner == 2)
						{
							blocknum = 0;
							temp.r = 0.0;
							temp.g = 0.0;
							temp.b = 0.0;
							//�\�ʃ{�N�Z���Ȃ�ΐF�����I
							for(int i(0); i<2; i++)
							{
								if(b[x+i][y][z].surf)
								{
									blocknum++;
									temp.r += m.Voxel_colors[x+i][y][z].r;
									temp.g += m.Voxel_colors[x+i][y][z].g;
									temp.b += m.Voxel_colors[x+i][y][z].b;
								}
							}
							if(blocknum > 0)
							{
								temp.r = temp.r/blocknum;
								temp.g = temp.g/blocknum;
								temp.b = temp.b/blocknum;
								//���S�̐F�ւƒu������
								//���ڕ\�ʃ{�N�Z����RGB����L*a*b*���v�Z
								min_no = GetSimilarColor(temp, m.LegoColor_Lab);
								for(int i(0); i<2; i++)
									m.Voxel_colors[x+i][y][z] = m.LegoColor[min_no];
								BlockNum[1][min_no]++;
								tempB.DesignID = table.DesignID[1];
								tempB.colorID = table.ColorID[min_no];
								tempB.itemNos = table.itemNos[1][min_no];
							}
							else
							{
								for(int i(0); i<2; i++)
									m.Voxel_colors[x+i][y][z] = anycolor;
								BlockNum[1][Block_colorNum-1]++;
								tempB.DesignID = table.DesignID[1];
								tempB.colorID = table.ColorID[table.ColorID.size() - 1];
								tempB.itemNos = table.itemNos[1][table.ColorID.size() - 1];
							}
							tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
							tempB.trans.y = (z-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
							tempB.trans.z = 0.4+(x-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
							tempB.rn = 1;									//��]�����Ȃ�
							LDD.push_back(tempB);
						}
					}
					//###################################
					//�P�~�R�̏ꍇ
					//###################################
					//else if(b[x][y][z].flag == 13 && b[x][y][z].corner == 1)
					else if(b[x][y][z].flag == 13)
					{
						//�P�~�R���������̏ꍇ
						if(y+2 < m.num[1])
						{
							if(b[x][y+2][z].flag == 13 && b[x][y][z].ID == b[x][y+2][z].ID && b[x][y+2][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;
								//�\�ʃ{�N�Z���Ȃ�ΐF�����I
								for(int i(0); i<3; i++)
								{
									if(b[x][y+i][z].surf)
									{
										blocknum++;
										temp.r += m.Voxel_colors[x][y+i][z].r;
										temp.g += m.Voxel_colors[x][y+i][z].g;
										temp.b += m.Voxel_colors[x][y+i][z].b;
									}
								}
								if(blocknum > 0)
								{
									temp.r = temp.r/blocknum;
									temp.g = temp.g/blocknum;
									temp.b = temp.b/blocknum;
									//���S�̐F�ւƒu������
									//���ڕ\�ʃ{�N�Z����RGB����L*a*b*���v�Z
									min_no = GetSimilarColor(temp, m.LegoColor_Lab);
									for(int i(0); i<3; i++)
										m.Voxel_colors[x][y+i][z] = m.LegoColor[min_no];
									BlockNum[2][min_no]++;
									tempB.DesignID = table.DesignID[2];
									tempB.colorID = table.ColorID[min_no];
									tempB.itemNos = table.itemNos[2][min_no];
								}
								else
								{
									for(int i(0); i<3; i++)
										m.Voxel_colors[x][y+i][z] = anycolor;
									BlockNum[2][Block_colorNum-1]++;
									tempB.DesignID = table.DesignID[2];
									tempB.colorID = table.ColorID[table.ColorID.size() - 1];
									tempB.itemNos = table.itemNos[2][table.ColorID.size() - 1];
								}
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.y = (z-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.z = 0.4+(x-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.rn = 0;									//0:��]�����Ȃ�	1:��]������
								LDD.push_back(tempB);
								continue;
							}
						}
						//�P�~�R���������̏ꍇ
						if(x+2 < m.num[0])
						{
							if(b[x+2][y][z].flag == 13 && b[x][y][z].ID == b[x+2][y][z].ID && b[x+2][y][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;
								//�\�ʃ{�N�Z���Ȃ�ΐF�����I
								for(int i(0); i<3; i++)
								{
									if(b[x+i][y][z].surf)
									{
										blocknum++;
										temp.r += m.Voxel_colors[x+i][y][z].r;
										temp.g += m.Voxel_colors[x+i][y][z].g;
										temp.b += m.Voxel_colors[x+i][y][z].b;
									}
								}
								if(blocknum > 0)
								{
									temp.r = temp.r/blocknum;
									temp.g = temp.g/blocknum;
									temp.b = temp.b/blocknum;
									//���S�̐F�ւƒu������
									//���ڕ\�ʃ{�N�Z����RGB����L*a*b*���v�Z
									min_no = GetSimilarColor(temp, m.LegoColor_Lab);
									for(int i(0); i<3; i++)
										m.Voxel_colors[x+i][y][z] = m.LegoColor[min_no];
									BlockNum[2][min_no]++;
									tempB.DesignID = table.DesignID[2];
									tempB.colorID = table.ColorID[min_no];
									tempB.itemNos = table.itemNos[2][min_no];
								}
								else
								{
									for(int i(0); i<3; i++)
										m.Voxel_colors[x+i][y][z] = anycolor;
									BlockNum[2][Block_colorNum-1]++;
									tempB.DesignID = table.DesignID[2];
									tempB.colorID = table.ColorID[table.ColorID.size() - 1];
									tempB.itemNos = table.itemNos[2][table.ColorID.size() - 1];
								}
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.y = (z-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.z = 0.4+(x-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.rn = 1;									//0:��]�����Ȃ�	1:��]������
								LDD.push_back(tempB);
							}
						}
					}
					//###################################
					//�P�~�S�̏ꍇ
					//###################################
					//else if(b[x][y][z].flag == 14 && b[x][y][z].corner == 1)
					else if(b[x][y][z].flag == 14)
					{
						//�P�~�S���������̏ꍇ
						if(y+3 < m.num[1])
						{
							if(b[x][y+3][z].flag == 14 && b[x][y][z].ID == b[x][y+3][z].ID && b[x][y+3][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;
								//�\�ʃ{�N�Z���Ȃ�ΐF�����I
								for(int i(0); i<4; i++)
								{
									if(b[x][y+i][z].surf)	//�Ȃ��Ă�������������Ȃ�
									{
										blocknum++;
										temp.r += m.Voxel_colors[x][y+i][z].r;
										temp.g += m.Voxel_colors[x][y+i][z].g;
										temp.b += m.Voxel_colors[x][y+i][z].b;
									}
								}
								if(blocknum > 0)
								{
									temp.r = temp.r/blocknum;
									temp.g = temp.g/blocknum;
									temp.b = temp.b/blocknum;
									//���S�̐F�ւƒu������
									//���ڕ\�ʃ{�N�Z����RGB����L*a*b*���v�Z
									min_no = GetSimilarColor(temp, m.LegoColor_Lab);
									for(int i(0); i<4; i++)
										m.Voxel_colors[x][y+i][z] = m.LegoColor[min_no];
									BlockNum[3][min_no]++;
									tempB.DesignID = table.DesignID[3];
									tempB.colorID = table.ColorID[min_no];
									tempB.itemNos = table.itemNos[3][min_no];
								}
								else
								{
									for(int i(0); i<4; i++)
										m.Voxel_colors[x][y+i][z] = anycolor;
									BlockNum[3][Block_colorNum-1]++;
									tempB.DesignID = table.DesignID[3];
									tempB.colorID = table.ColorID[table.ColorID.size() - 1];
									tempB.itemNos = table.itemNos[3][table.ColorID.size() - 1];
								}
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.y = (z-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.z = 0.4+(x-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.rn = 0;									//0:��]�����Ȃ�	1:��]������
								LDD.push_back(tempB);
								continue;

							}
						}
						//�P�~�S���������̏ꍇ
						if(x+3 < m.num[0])
						{
							if(b[x+3][y][z].flag == 14 && b[x][y][z].ID == b[x+3][y][z].ID && b[x+3][y][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;
								//�\�ʃ{�N�Z���Ȃ�ΐF�����I
								for(int i(0); i<4; i++)
								{
									if(b[x+i][y][z].surf)
									{
										blocknum++;
										temp.r += m.Voxel_colors[x+i][y][z].r;
										temp.g += m.Voxel_colors[x+i][y][z].g;
										temp.b += m.Voxel_colors[x+i][y][z].b;
									}
								}
								if(blocknum > 0)
								{
									temp.r = temp.r/blocknum;
									temp.g = temp.g/blocknum;
									temp.b = temp.b/blocknum;
									//���S�̐F�ւƒu������
									//���ڕ\�ʃ{�N�Z����RGB����L*a*b*���v�Z
									min_no = GetSimilarColor(temp, m.LegoColor_Lab);
									for(int i(0); i<4; i++)
										m.Voxel_colors[x+i][y][z] = m.LegoColor[min_no];
									BlockNum[3][min_no]++;
									tempB.DesignID = table.DesignID[3];
									tempB.colorID = table.ColorID[min_no];
									tempB.itemNos = table.itemNos[3][min_no];
								}
								else
								{
									for(int i(0); i<4; i++)
										m.Voxel_colors[x+i][y][z] = anycolor;
									BlockNum[3][Block_colorNum-1]++;
									tempB.DesignID = table.DesignID[3];
									tempB.colorID = table.ColorID[table.ColorID.size() - 1];
									tempB.itemNos = table.itemNos[3][table.ColorID.size() - 1];
								}
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.y = (z-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.z = 0.4+(x-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.rn = 1;									//0:��]�����Ȃ�	1:��]������
								LDD.push_back(tempB);
							}
						}
					}
					//###################################
					//�Q�~�Q�̏ꍇ
					//###################################
					//else if(b[x][y][z].flag == 22 && b[x][y][z].corner == 1)
					else if(b[x][y][z].flag == 22)
					{
						if(b[x+1][y+1][z].flag == 22 && b[x][y][z].ID == b[x+1][y+1][z].ID && b[x+1][y+1][z].corner == 2)
						{
							blocknum = 0;
							temp.r = 0.0;
							temp.g = 0.0;
							temp.b = 0.0;
							for(int i(0); i<2; i++)
							{
								for(int k(0); k<2; k++)
								{
									if(b[x+i][y+k][z].surf)
									{
										blocknum++;
										temp.r += m.Voxel_colors[x+i][y+k][z].r;
										temp.g += m.Voxel_colors[x+i][y+k][z].g;
										temp.b += m.Voxel_colors[x+i][y+k][z].b;
									}
								}
							}
							if(blocknum > 0)
							{
								temp.r = temp.r/blocknum;
								temp.g = temp.g/blocknum;
								temp.b = temp.b/blocknum;
								//���S�̐F�ւƒu������
								//���ڕ\�ʃ{�N�Z����RGB����L*a*b*���v�Z
								min_no = GetSimilarColor(temp, m.LegoColor_Lab);
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										m.Voxel_colors[x+i][y+k][z] = m.LegoColor[min_no];

								BlockNum[4][min_no]++;
								tempB.DesignID = table.DesignID[4];
								tempB.colorID = table.ColorID[min_no];
								tempB.itemNos = table.itemNos[4][min_no];
							}
							else
							{
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										m.Voxel_colors[x+i][y+k][z] = anycolor;
								BlockNum[4][Block_colorNum-1]++;
								tempB.DesignID = table.DesignID[4];
								tempB.colorID = table.ColorID[table.ColorID.size() - 1];
								tempB.itemNos = table.itemNos[4][table.ColorID.size() - 1];
							}
							tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
							tempB.trans.y = (z-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
							tempB.trans.z = 0.4+x*xyD;		//LDD�̂��ɑΉ�����̂͂�
							tempB.rn = 0;									//0:��]�����Ȃ�	1:��]������
							LDD.push_back(tempB);
						}
					}
					//###################################
					//�Q�~�R�̏ꍇ
					//###################################
					//else if(b[x][y][z].flag == 23 && b[x][y][z].corner == 1)
					else if(b[x][y][z].flag == 23)
					{
						//�Q�~�R���������̏ꍇ
						if(y+2 < m.num[1] )
						{
							if(b[x+1][y+2][z].flag == 23 && b[x][y][z].ID == b[x+1][y+2][z].ID && b[x+1][y+2][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<3; k++)
									{		
										if(b[x+i][y+k][z].surf)
										{
											blocknum++;
											temp.r += m.Voxel_colors[x+i][y+k][z].r;
											temp.g += m.Voxel_colors[x+i][y+k][z].g;
											temp.b += m.Voxel_colors[x+i][y+k][z].b;
										}
									}
								}
								if(blocknum > 0)
								{
									temp.r = temp.r/blocknum;
									temp.g = temp.g/blocknum;
									temp.b = temp.b/blocknum;
									//���S�̐F�ւƒu������
									//���ڕ\�ʃ{�N�Z����RGB����L*a*b*���v�Z
									min_no = GetSimilarColor(temp, m.LegoColor_Lab);
									for(int i(0); i<2; i++)
										for(int k(0); k<3; k++)
											m.Voxel_colors[x+i][y+k][z] = m.LegoColor[min_no];

									BlockNum[5][min_no]++;
									tempB.DesignID = table.DesignID[5];
									tempB.colorID = table.ColorID[min_no];
									tempB.itemNos = table.itemNos[5][min_no];
								}
								else
								{
									for(int i(0); i<2; i++)
										for(int k(0); k<3; k++)
											m.Voxel_colors[x+i][y+k][z] = anycolor;
									BlockNum[5][Block_colorNum-1]++;
									tempB.DesignID = table.DesignID[5];
									tempB.colorID = table.ColorID[table.ColorID.size() - 1];
									tempB.itemNos = table.itemNos[5][table.ColorID.size() - 1];
								}
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.y = (z-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.z = 0.4+x*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.rn = 0;									//0:��]�����Ȃ�	1:��]������
								LDD.push_back(tempB);
								continue;

							}
						}
						//�Q�~�R���������̏ꍇ
						if(x+2 < m.num[0])
						{
							if(b[x+2][y+1][z].flag == 23 && b[x][y][z].ID == b[x+2][y+1][z].ID && b[x+2][y+1][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;

								for(int i(0); i<3; i++)
								{
									for(int k(0); k<2; k++)
									{
										if(b[x+i][y+k][z].surf)
										{
											blocknum++;
											temp.r += m.Voxel_colors[x+i][y+k][z].r;
											temp.g += m.Voxel_colors[x+i][y+k][z].g;
											temp.b += m.Voxel_colors[x+i][y+k][z].b;
										}
									}
								}
								if(blocknum > 0)
								{
									temp.r = temp.r/blocknum;
									temp.g = temp.g/blocknum;
									temp.b = temp.b/blocknum;
									//���S�̐F�ւƒu������
									//���ڕ\�ʃ{�N�Z����RGB����L*a*b*���v�Z
									min_no = GetSimilarColor(temp, m.LegoColor_Lab);
									for(int i(0); i<3; i++)
										for(int k(0); k<2; k++)
											m.Voxel_colors[x+i][y+k][z] = m.LegoColor[min_no];

									BlockNum[5][min_no]++;
									tempB.DesignID = table.DesignID[5];
									tempB.colorID = table.ColorID[min_no];
									tempB.itemNos = table.itemNos[5][min_no];
								}
								else
								{
									for(int i(0); i<3; i++)
										for(int k(0); k<2; k++)
											m.Voxel_colors[x+i][y+k][z] = anycolor;

									BlockNum[5][Block_colorNum-1]++;
									tempB.DesignID = table.DesignID[5];
									tempB.colorID = table.ColorID[table.ColorID.size() - 1];
									tempB.itemNos = table.itemNos[5][table.ColorID.size() - 1];
								}
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.y = (z-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.z = 0.4+(x-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.rn = 1;									//0:��]�����Ȃ�	1:��]������
								LDD.push_back(tempB);
							}
						}
					}
					//###################################
					//�Q�~�S�̏ꍇ
					//###################################
					//else if(b[x][y][z].flag == 24 && b[x][y][z].corner == 1)
					else if(b[x][y][z].flag == 24)
					{
						//�Q�~�S���������̏ꍇ
						if(y+3 < m.num[1])
						{
							if(b[x+1][y+3][z].flag == 24 && b[x][y][z].ID == b[x+1][y+3][z].ID && b[x+1][y+3][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<4; k++)
									{
										if(b[x+i][y+k][z].surf)
										{
											blocknum++;
											temp.r += m.Voxel_colors[x+i][y+k][z].r;
											temp.g += m.Voxel_colors[x+i][y+k][z].g;
											temp.b += m.Voxel_colors[x+i][y+k][z].b;
										}
									}
								}
								if(blocknum > 0)
								{
									temp.r = temp.r/blocknum;
									temp.g = temp.g/blocknum;
									temp.b = temp.b/blocknum;
									min_no = GetSimilarColor(temp, m.LegoColor_Lab);
									for(int i(0); i<2; i++)
										for(int k(0); k<4; k++)
											m.Voxel_colors[x+i][y+k][z] = m.LegoColor[min_no];

									BlockNum[6][min_no]++;
									tempB.DesignID = table.DesignID[6];
									tempB.colorID = table.ColorID[min_no];
									tempB.itemNos = table.itemNos[6][min_no];
								}
								else
								{
									for(int i(0); i<2; i++)
										for(int k(0); k<4; k++)
											m.Voxel_colors[x+i][y+k][z] = anycolor;
									BlockNum[6][Block_colorNum-1]++;
									tempB.DesignID = table.DesignID[6];
									tempB.colorID = table.ColorID[table.ColorID.size() - 1];
									tempB.itemNos = table.itemNos[6][table.ColorID.size() - 1];
								}
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.y = (z-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.z = 0.4+x*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.rn = 0;									//0:��]�����Ȃ�	1:��]������
								LDD.push_back(tempB);
								continue;
							}
						}
						//�Q�~�S���������̏ꍇ
						if(x+3 < m.num[0])
						{
							if(b[x+3][y+1][z].flag == 24 && b[x][y][z].ID == b[x+3][y+1][z].ID && b[x+3][y+1][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;
								for(int i(0); i<4; i++)
								{
									for(int k(0); k<2; k++)
									{
										if(b[x+i][y+k][z].surf)
										{
											blocknum++;
											temp.r += m.Voxel_colors[x+i][y+k][z].r;
											temp.g += m.Voxel_colors[x+i][y+k][z].g;
											temp.b += m.Voxel_colors[x+i][y+k][z].b;
										}
									}
								}
								if(blocknum > 0)
								{
									temp.r = temp.r/blocknum;
									temp.g = temp.g/blocknum;
									temp.b = temp.b/blocknum;
									//���S�̐F�ւƒu������
									//���ڕ\�ʃ{�N�Z����RGB����L*a*b*���v�Z
									min_no = GetSimilarColor(temp, m.LegoColor_Lab);
									for(int i(0); i<4; i++)
										for(int k(0); k<2; k++)
											m.Voxel_colors[x+i][y+k][z] = m.LegoColor[min_no];

									BlockNum[6][min_no]++;
									tempB.DesignID = table.DesignID[6];
									tempB.colorID = table.ColorID[min_no];
									tempB.itemNos = table.itemNos[6][min_no];
								}
								else
								{
									for(int i(0); i<4; i++)
										for(int k(0); k<2; k++)
											m.Voxel_colors[x+i][y+k][z] = anycolor;
									BlockNum[6][Block_colorNum-1]++;
									tempB.DesignID = table.DesignID[6];
									tempB.colorID = table.ColorID[table.ColorID.size() - 1];
									tempB.itemNos = table.itemNos[6][table.ColorID.size() - 1];
								}
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.y = (z-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.z = 0.4+(x-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.rn = 1;									//0:��]�����Ȃ�	1:��]������
								LDD.push_back(tempB);
							}
						}
					}
				}
			}
		}
	}

}

void ColoringBlock_zhang(Model& m, Lego*** b)
{

	cout << "ColoringBlock_zhang\n";

	int x,y,z;
	CColor temp( 0.0, 0.0, 0.0);
	int blocknum(0);				//�P�̃u���b�N�ɐF�t���̃{�N�Z�������܂ނ�
	int min_no(0);					//�ŏ��l�����ԖڂȂ̂�
	CColor anycolor(2.0, 0.0, 0.0);		//�F�̂Ȃ��u���b�N�ɂ���F(��ق�OpenDraw�ŕ`�悷��Ƃ��g��)
	Brick tempB;

	//#####################################
	//              
	//#####################################
	Block_colorNum = m.LegoColor.size() + 1;		

	BlockNum = new unsigned int * [Block_varietyNum];
	for(int i(0); i<Block_varietyNum; i++)
		BlockNum[i] = new unsigned int [Block_colorNum];

	//������
	for(int i(0); i<Block_varietyNum; i++)
		for(int k(0); k<Block_colorNum; k++)
			BlockNum[i][k] = 0;

	rot[0].assign(3);
	rot[1].assign(3);

	rot[0].IdentifyMatrix();	
	rot[1].SetZero();			
	rot[1][0][2] = 1.0;
	rot[1][1][1] = 1.0;
	rot[1][2][0] = -1.0;

	double xyD(0.8);			
	double zD(0.96);			

	
	for(z=1; z<m.num[2]-1; z++)
	{
		for(x=1; x<m.num[0]-1; x++)
		{
			for(y=1; y<m.num[1]-1; y++)
			{
				//cout<<x<<" "<<y<<" "<<z<<endl;
				//###################################
				//�P�~�P�̏ꍇ
				//###################################
				if(b[x][y][z].flag == 1)
				{
					tempB.clear();
					if(b[x][y][z].surf)
					{
						temp = m.Voxel_colors[x][y][z];
						min_no = GetSimilarColor(temp, m.LegoColor_Lab);
						m.Voxel_colors[x][y][z] = m.LegoColor[min_no];
						BlockNum[0][min_no]++;
						tempB.DesignID = table.DesignID[0];
						tempB.colorID = table.ColorID[min_no];
						tempB.itemNos = table.itemNos[0][min_no];
					}
					else
					{
						m.Voxel_colors[x][y][z] = anycolor;
						BlockNum[0][Block_colorNum-1]++;
						tempB.DesignID = table.DesignID[0];
						tempB.colorID = table.ColorID[table.ColorID.size() - 1];
						tempB.itemNos = table.itemNos[0][table.ColorID.size() - 1];
					}
					tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
					tempB.trans.y = ((m.num[2] - z -1) - 1)*zD;					//LDD�̂��ɑΉ�����̂͂�
					tempB.trans.z = 0.4+((m.num[0] - x -1) - 1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
					tempB.rn = 0;
					LDD.push_back(tempB);
				}
				//####################################
				
				//####################################
				else if(b[x][y][z].flag > 1)
				{
					if(b[x][y][z].corner != 1)
						continue;
					tempB.clear();
					//###################################
					//�P�~�Q�̏ꍇ
					//###################################
					//else if(b[x][y][z].flag == 12 && b[x][y][z].corner == 1)
					if(b[x][y][z].flag == 12)
					{
						//�P�~�Q���������̏ꍇ(��]�����Ȃ�)
						if(b[x][y+1][z].flag == 12 && b[x][y][z].ID == b[x][y+1][z].ID && b[x][y+1][z].corner == 2)
						{
							blocknum = 0;
							temp.r = 0.0;
							temp.g = 0.0;
							temp.b = 0.0;
							//�\�ʃ{�N�Z���Ȃ�ΐF�����I
							for(int i(0); i<2; i++)
							{							
								//�\�ʃ{�N�Z���Ȃ�΁A�F�����̂�
								if(b[x][y+i][z].surf)
								{
									blocknum++;
									temp.r += m.Voxel_colors[x][y+i][z].r;
									temp.g += m.Voxel_colors[x][y+i][z].g;
									temp.b += m.Voxel_colors[x][y+i][z].b;
								}
							}
							if(blocknum > 0)
							{
								temp.r = temp.r/blocknum;
								temp.g = temp.g/blocknum;
								temp.b = temp.b/blocknum;
								//���S�̐F�ւƒu������
								//���ڕ\�ʃ{�N�Z����RGB����L*a*b*���v�Z
								min_no = GetSimilarColor(temp, m.LegoColor_Lab);
								for(int i(0); i<2; i++)
									m.Voxel_colors[x][y+i][z] = m.LegoColor[min_no];
								BlockNum[1][min_no]++;
								tempB.DesignID = table.DesignID[1];
								tempB.colorID = table.ColorID[min_no];
								tempB.itemNos = table.itemNos[1][min_no];
							}
							else
							{
								for(int i(0); i<2; i++)
									m.Voxel_colors[x][y+i][z] = anycolor;
								BlockNum[1][Block_colorNum-1]++;
								tempB.DesignID = table.DesignID[1];
								tempB.colorID = table.ColorID[table.ColorID.size() - 1];
								tempB.itemNos = table.itemNos[1][table.ColorID.size() - 1];
							}
							tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
							tempB.trans.y = ((m.num[2] - z -1)-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
							tempB.trans.z = 0.4+((m.num[0] - x - 1)-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
							tempB.rn = 0;									//��]�����Ȃ�
							LDD.push_back(tempB);
							continue;
						}

						//�P�~�Q���������̏ꍇ�i��]������j
						if(b[x+1][y][z].flag == 12 && b[x][y][z].ID == b[x+1][y][z].ID && b[x+1][y][z].corner == 2)
						{
							blocknum = 0;
							temp.r = 0.0;
							temp.g = 0.0;
							temp.b = 0.0;
							//�\�ʃ{�N�Z���Ȃ�ΐF�����I
							for(int i(0); i<2; i++)
							{
								if(b[x+i][y][z].surf)
								{
									blocknum++;
									temp.r += m.Voxel_colors[x+i][y][z].r;
									temp.g += m.Voxel_colors[x+i][y][z].g;
									temp.b += m.Voxel_colors[x+i][y][z].b;
								}
							}
							if(blocknum > 0)
							{
								temp.r = temp.r/blocknum;
								temp.g = temp.g/blocknum;
								temp.b = temp.b/blocknum;
								//���S�̐F�ւƒu������
								//���ڕ\�ʃ{�N�Z����RGB����L*a*b*���v�Z
								min_no = GetSimilarColor(temp, m.LegoColor_Lab);
								for(int i(0); i<2; i++)
									m.Voxel_colors[x+i][y][z] = m.LegoColor[min_no];
								BlockNum[1][min_no]++;
								tempB.DesignID = table.DesignID[1];
								tempB.colorID = table.ColorID[min_no];
								tempB.itemNos = table.itemNos[1][min_no];
							}
							else
							{
								for(int i(0); i<2; i++)
									m.Voxel_colors[x+i][y][z] = anycolor;
								BlockNum[1][Block_colorNum-1]++;
								tempB.DesignID = table.DesignID[1];
								tempB.colorID = table.ColorID[table.ColorID.size() - 1];
								tempB.itemNos = table.itemNos[1][table.ColorID.size() - 1];
							}
							tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
							tempB.trans.y = ((m.num[2] - z -1)-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
							tempB.trans.z = 0.4+((m.num[0] - x -2)-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
							tempB.rn = 1;									//��]�����Ȃ�
							LDD.push_back(tempB);
						}
					}
					//###################################
					//�P�~�R�̏ꍇ
					//###################################
					//else if(b[x][y][z].flag == 13 && b[x][y][z].corner == 1)
					else if(b[x][y][z].flag == 13)
					{
						//�P�~�R���������̏ꍇ
						if(y+2 < m.num[1])
						{
							if(b[x][y+2][z].flag == 13 && b[x][y][z].ID == b[x][y+2][z].ID && b[x][y+2][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;
								//�\�ʃ{�N�Z���Ȃ�ΐF�����I
								for(int i(0); i<3; i++)
								{
									if(b[x][y+i][z].surf)
									{
										blocknum++;
										temp.r += m.Voxel_colors[x][y+i][z].r;
										temp.g += m.Voxel_colors[x][y+i][z].g;
										temp.b += m.Voxel_colors[x][y+i][z].b;
									}
								}
								if(blocknum > 0)
								{
									temp.r = temp.r/blocknum;
									temp.g = temp.g/blocknum;
									temp.b = temp.b/blocknum;
									//���S�̐F�ւƒu������
									//���ڕ\�ʃ{�N�Z����RGB����L*a*b*���v�Z
									min_no = GetSimilarColor(temp, m.LegoColor_Lab);
									for(int i(0); i<3; i++)
										m.Voxel_colors[x][y+i][z] = m.LegoColor[min_no];
									BlockNum[2][min_no]++;
									tempB.DesignID = table.DesignID[2];
									tempB.colorID = table.ColorID[min_no];
									tempB.itemNos = table.itemNos[2][min_no];
								}
								else
								{
									for(int i(0); i<3; i++)
										m.Voxel_colors[x][y+i][z] = anycolor;
									BlockNum[2][Block_colorNum-1]++;
									tempB.DesignID = table.DesignID[2];
									tempB.colorID = table.ColorID[table.ColorID.size() - 1];
									tempB.itemNos = table.itemNos[2][table.ColorID.size() - 1];
								}
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.y = ((m.num[2] - z -1)-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.z = 0.4+((m.num[0] - x - 1)-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.rn = 0;									//0:��]�����Ȃ�	1:��]������
								LDD.push_back(tempB);
								continue;
							}
						}
						//�P�~�R���������̏ꍇ
						if(x+2 < m.num[0])
						{
							if(b[x+2][y][z].flag == 13 && b[x][y][z].ID == b[x+2][y][z].ID && b[x+2][y][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;
								//�\�ʃ{�N�Z���Ȃ�ΐF�����I
								for(int i(0); i<3; i++)
								{
									if(b[x+i][y][z].surf)
									{
										blocknum++;
										temp.r += m.Voxel_colors[x+i][y][z].r;
										temp.g += m.Voxel_colors[x+i][y][z].g;
										temp.b += m.Voxel_colors[x+i][y][z].b;
									}
								}
								if(blocknum > 0)
								{
									temp.r = temp.r/blocknum;
									temp.g = temp.g/blocknum;
									temp.b = temp.b/blocknum;
									//���S�̐F�ւƒu������
									//���ڕ\�ʃ{�N�Z����RGB����L*a*b*���v�Z
									min_no = GetSimilarColor(temp, m.LegoColor_Lab);
									for(int i(0); i<3; i++)
										m.Voxel_colors[x+i][y][z] = m.LegoColor[min_no];
									BlockNum[2][min_no]++;
									tempB.DesignID = table.DesignID[2];
									tempB.colorID = table.ColorID[min_no];
									tempB.itemNos = table.itemNos[2][min_no];
								}
								else
								{
									for(int i(0); i<3; i++)
										m.Voxel_colors[x+i][y][z] = anycolor;
									BlockNum[2][Block_colorNum-1]++;
									tempB.DesignID = table.DesignID[2];
									tempB.colorID = table.ColorID[table.ColorID.size() - 1];
									tempB.itemNos = table.itemNos[2][table.ColorID.size() - 1];
								}
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.y = ((m.num[2] - z -1)-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.z = 0.4+((m.num[0] - x -3)-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.rn = 1;									//0:��]�����Ȃ�	1:��]������
								LDD.push_back(tempB);
							}
						}
					}
					//###################################
					//�P�~�S�̏ꍇ
					//###################################
					//else if(b[x][y][z].flag == 14 && b[x][y][z].corner == 1)
					else if(b[x][y][z].flag == 14)
					{
						//�P�~�S���������̏ꍇ
						if(y+3 < m.num[1])
						{
							if(b[x][y+3][z].flag == 14 && b[x][y][z].ID == b[x][y+3][z].ID && b[x][y+3][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;
								//�\�ʃ{�N�Z���Ȃ�ΐF�����I
								for(int i(0); i<4; i++)
								{
									if(b[x][y+i][z].surf)	//�Ȃ��Ă�������������Ȃ�
									{
										blocknum++;
										temp.r += m.Voxel_colors[x][y+i][z].r;
										temp.g += m.Voxel_colors[x][y+i][z].g;
										temp.b += m.Voxel_colors[x][y+i][z].b;
									}
								}
								if(blocknum > 0)
								{
									temp.r = temp.r/blocknum;
									temp.g = temp.g/blocknum;
									temp.b = temp.b/blocknum;
									//���S�̐F�ւƒu������
									//���ڕ\�ʃ{�N�Z����RGB����L*a*b*���v�Z
									min_no = GetSimilarColor(temp, m.LegoColor_Lab);
									for(int i(0); i<4; i++)
										m.Voxel_colors[x][y+i][z] = m.LegoColor[min_no];
									BlockNum[3][min_no]++;
									tempB.DesignID = table.DesignID[3];
									tempB.colorID = table.ColorID[min_no];
									tempB.itemNos = table.itemNos[3][min_no];
								}
								else
								{
									for(int i(0); i<4; i++)
										m.Voxel_colors[x][y+i][z] = anycolor;
									BlockNum[3][Block_colorNum-1]++;
									tempB.DesignID = table.DesignID[3];
									tempB.colorID = table.ColorID[table.ColorID.size() - 1];
									tempB.itemNos = table.itemNos[3][table.ColorID.size() - 1];
								}
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.y = ((m.num[2] - z -1)-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.z = 0.4+((m.num[0] - x - 1)-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.rn = 0;									//0:��]�����Ȃ�	1:��]������
								LDD.push_back(tempB);
								continue;

							}
						}
						//�P�~�S���������̏ꍇ
						if(x+3 < m.num[0])
						{
							if(b[x+3][y][z].flag == 14 && b[x][y][z].ID == b[x+3][y][z].ID && b[x+3][y][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;
								//�\�ʃ{�N�Z���Ȃ�ΐF�����I
								for(int i(0); i<4; i++)
								{
									if(b[x+i][y][z].surf)
									{
										blocknum++;
										temp.r += m.Voxel_colors[x+i][y][z].r;
										temp.g += m.Voxel_colors[x+i][y][z].g;
										temp.b += m.Voxel_colors[x+i][y][z].b;
									}
								}
								if(blocknum > 0)
								{
									temp.r = temp.r/blocknum;
									temp.g = temp.g/blocknum;
									temp.b = temp.b/blocknum;
									//���S�̐F�ւƒu������
									//���ڕ\�ʃ{�N�Z����RGB����L*a*b*���v�Z
									min_no = GetSimilarColor(temp, m.LegoColor_Lab);
									for(int i(0); i<4; i++)
										m.Voxel_colors[x+i][y][z] = m.LegoColor[min_no];
									BlockNum[3][min_no]++;
									tempB.DesignID = table.DesignID[3];
									tempB.colorID = table.ColorID[min_no];
									tempB.itemNos = table.itemNos[3][min_no];
								}
								else
								{
									for(int i(0); i<4; i++)
										m.Voxel_colors[x+i][y][z] = anycolor;
									BlockNum[3][Block_colorNum-1]++;
									tempB.DesignID = table.DesignID[3];
									tempB.colorID = table.ColorID[table.ColorID.size() - 1];
									tempB.itemNos = table.itemNos[3][table.ColorID.size() - 1];
								}
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.y = ((m.num[2] - z -1)-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.z = 0.4+((m.num[0] - x - 4) - 1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.rn = 1;									//0:��]�����Ȃ�	1:��]������
								LDD.push_back(tempB);
							}
						}
					}
					//###################################
					//�Q�~�Q�̏ꍇ
					//###################################
					//else if(b[x][y][z].flag == 22 && b[x][y][z].corner == 1)
					else if(b[x][y][z].flag == 22)
					{
						if(b[x+1][y+1][z].flag == 22 && b[x][y][z].ID == b[x+1][y+1][z].ID && b[x+1][y+1][z].corner == 2)
						{
							blocknum = 0;
							temp.r = 0.0;
							temp.g = 0.0;
							temp.b = 0.0;
							for(int i(0); i<2; i++)
							{
								for(int k(0); k<2; k++)
								{
									if(b[x+i][y+k][z].surf)
									{
										blocknum++;
										temp.r += m.Voxel_colors[x+i][y+k][z].r;
										temp.g += m.Voxel_colors[x+i][y+k][z].g;
										temp.b += m.Voxel_colors[x+i][y+k][z].b;
									}
								}
							}
							if(blocknum > 0)
							{
								temp.r = temp.r/blocknum;
								temp.g = temp.g/blocknum;
								temp.b = temp.b/blocknum;
								//���S�̐F�ւƒu������
								//���ڕ\�ʃ{�N�Z����RGB����L*a*b*���v�Z
								min_no = GetSimilarColor(temp, m.LegoColor_Lab);
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										m.Voxel_colors[x+i][y+k][z] = m.LegoColor[min_no];

								BlockNum[4][min_no]++;
								tempB.DesignID = table.DesignID[4];
								tempB.colorID = table.ColorID[min_no];
								tempB.itemNos = table.itemNos[4][min_no];
							}
							else
							{
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										m.Voxel_colors[x+i][y+k][z] = anycolor;
								BlockNum[4][Block_colorNum-1]++;
								tempB.DesignID = table.DesignID[4];
								tempB.colorID = table.ColorID[table.ColorID.size() - 1];
								tempB.itemNos = table.itemNos[4][table.ColorID.size() - 1];
							}
							tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
							tempB.trans.y = ((m.num[2] - z -1)-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
							tempB.trans.z = 0.4+(m.num[0] - x - 2)*xyD;		//LDD�̂��ɑΉ�����̂͂�
							tempB.rn = 0;									//0:��]�����Ȃ�	1:��]������
							LDD.push_back(tempB);
						}
					}
					//###################################
					//�Q�~�R�̏ꍇ
					//###################################
					//else if(b[x][y][z].flag == 23 && b[x][y][z].corner == 1)
					else if(b[x][y][z].flag == 23)
					{
						//�Q�~�R���������̏ꍇ
						if(y+2 < m.num[1] )
						{
							if(b[x+1][y+2][z].flag == 23 && b[x][y][z].ID == b[x+1][y+2][z].ID && b[x+1][y+2][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<3; k++)
									{		
										if(b[x+i][y+k][z].surf)
										{
											blocknum++;
											temp.r += m.Voxel_colors[x+i][y+k][z].r;
											temp.g += m.Voxel_colors[x+i][y+k][z].g;
											temp.b += m.Voxel_colors[x+i][y+k][z].b;
										}
									}
								}
								if(blocknum > 0)
								{
									temp.r = temp.r/blocknum;
									temp.g = temp.g/blocknum;
									temp.b = temp.b/blocknum;
									//���S�̐F�ւƒu������
									//���ڕ\�ʃ{�N�Z����RGB����L*a*b*���v�Z
									min_no = GetSimilarColor(temp, m.LegoColor_Lab);
									for(int i(0); i<2; i++)
										for(int k(0); k<3; k++)
											m.Voxel_colors[x+i][y+k][z] = m.LegoColor[min_no];

									BlockNum[5][min_no]++;
									tempB.DesignID = table.DesignID[5];
									tempB.colorID = table.ColorID[min_no];
									tempB.itemNos = table.itemNos[5][min_no];
								}
								else
								{
									for(int i(0); i<2; i++)
										for(int k(0); k<3; k++)
											m.Voxel_colors[x+i][y+k][z] = anycolor;
									BlockNum[5][Block_colorNum-1]++;
									tempB.DesignID = table.DesignID[5];
									tempB.colorID = table.ColorID[table.ColorID.size() - 1];
									tempB.itemNos = table.itemNos[5][table.ColorID.size() - 1];
								}
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.y = ((m.num[2] - z -1)-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.z = 0.4+(m.num[0] - x - 2)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.rn = 0;									//0:��]�����Ȃ�	1:��]������
								LDD.push_back(tempB);
								continue;

							}
						}
						//�Q�~�R���������̏ꍇ
						if(x+2 < m.num[0])
						{
							if(b[x+2][y+1][z].flag == 23 && b[x][y][z].ID == b[x+2][y+1][z].ID && b[x+2][y+1][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;

								for(int i(0); i<3; i++)
								{
									for(int k(0); k<2; k++)
									{
										if(b[x+i][y+k][z].surf)
										{
											blocknum++;
											temp.r += m.Voxel_colors[x+i][y+k][z].r;
											temp.g += m.Voxel_colors[x+i][y+k][z].g;
											temp.b += m.Voxel_colors[x+i][y+k][z].b;
										}
									}
								}
								if(blocknum > 0)
								{
									temp.r = temp.r/blocknum;
									temp.g = temp.g/blocknum;
									temp.b = temp.b/blocknum;
									//���S�̐F�ւƒu������
									//���ڕ\�ʃ{�N�Z����RGB����L*a*b*���v�Z
									min_no = GetSimilarColor(temp, m.LegoColor_Lab);
									for(int i(0); i<3; i++)
										for(int k(0); k<2; k++)
											m.Voxel_colors[x+i][y+k][z] = m.LegoColor[min_no];

									BlockNum[5][min_no]++;
									tempB.DesignID = table.DesignID[5];
									tempB.colorID = table.ColorID[min_no];
									tempB.itemNos = table.itemNos[5][min_no];
								}
								else
								{
									for(int i(0); i<3; i++)
										for(int k(0); k<2; k++)
											m.Voxel_colors[x+i][y+k][z] = anycolor;

									BlockNum[5][Block_colorNum-1]++;
									tempB.DesignID = table.DesignID[5];
									tempB.colorID = table.ColorID[table.ColorID.size() - 1];
									tempB.itemNos = table.itemNos[5][table.ColorID.size() - 1];
								}
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.y = ((m.num[2] - z -1)-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.z = 0.4+((m.num[0] - x - 3)-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.rn = 1;									//0:��]�����Ȃ�	1:��]������
								LDD.push_back(tempB);
							}
						}
					}
					//###################################
					//�Q�~�S�̏ꍇ
					//###################################
					//else if(b[x][y][z].flag == 24 && b[x][y][z].corner == 1)
					else if(b[x][y][z].flag == 24)
					{
						//�Q�~�S���������̏ꍇ
						if(y+3 < m.num[1])
						{
							if(b[x+1][y+3][z].flag == 24 && b[x][y][z].ID == b[x+1][y+3][z].ID && b[x+1][y+3][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<4; k++)
									{
										if(b[x+i][y+k][z].surf)
										{
											blocknum++;
											temp.r += m.Voxel_colors[x+i][y+k][z].r;
											temp.g += m.Voxel_colors[x+i][y+k][z].g;
											temp.b += m.Voxel_colors[x+i][y+k][z].b;
										}
									}
								}
								if(blocknum > 0)
								{
									temp.r = temp.r/blocknum;
									temp.g = temp.g/blocknum;
									temp.b = temp.b/blocknum;
									min_no = GetSimilarColor(temp, m.LegoColor_Lab);
									for(int i(0); i<2; i++)
										for(int k(0); k<4; k++)
											m.Voxel_colors[x+i][y+k][z] = m.LegoColor[min_no];

									BlockNum[6][min_no]++;
									tempB.DesignID = table.DesignID[6];
									tempB.colorID = table.ColorID[min_no];
									tempB.itemNos = table.itemNos[6][min_no];
								}
								else
								{
									for(int i(0); i<2; i++)
										for(int k(0); k<4; k++)
											m.Voxel_colors[x+i][y+k][z] = anycolor;
									BlockNum[6][Block_colorNum-1]++;
									tempB.DesignID = table.DesignID[6];
									tempB.colorID = table.ColorID[table.ColorID.size() - 1];
									tempB.itemNos = table.itemNos[6][table.ColorID.size() - 1];
								}
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.y = ((m.num[2] - z -1)-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.z = 0.4+(m.num[0] - x - 2)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.rn = 0;									//0:��]�����Ȃ�	1:��]������
								LDD.push_back(tempB);
								continue;
							}
						}
						//�Q�~�S���������̏ꍇ
						if(x+3 < m.num[0])
						{
							if(b[x+3][y+1][z].flag == 24 && b[x][y][z].ID == b[x+3][y+1][z].ID && b[x+3][y+1][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;
								for(int i(0); i<4; i++)
								{
									for(int k(0); k<2; k++)
									{
										if(b[x+i][y+k][z].surf)
										{
											blocknum++;
											temp.r += m.Voxel_colors[x+i][y+k][z].r;
											temp.g += m.Voxel_colors[x+i][y+k][z].g;
											temp.b += m.Voxel_colors[x+i][y+k][z].b;
										}
									}
								}
								if(blocknum > 0)
								{
									temp.r = temp.r/blocknum;
									temp.g = temp.g/blocknum;
									temp.b = temp.b/blocknum;
									//���S�̐F�ւƒu������
									//���ڕ\�ʃ{�N�Z����RGB����L*a*b*���v�Z
									min_no = GetSimilarColor(temp, m.LegoColor_Lab);
									for(int i(0); i<4; i++)
										for(int k(0); k<2; k++)
											m.Voxel_colors[x+i][y+k][z] = m.LegoColor[min_no];

									BlockNum[6][min_no]++;
									tempB.DesignID = table.DesignID[6];
									tempB.colorID = table.ColorID[min_no];
									tempB.itemNos = table.itemNos[6][min_no];
								}
								else
								{
									for(int i(0); i<4; i++)
										for(int k(0); k<2; k++)
											m.Voxel_colors[x+i][y+k][z] = anycolor;
									BlockNum[6][Block_colorNum-1]++;
									tempB.DesignID = table.DesignID[6];
									tempB.colorID = table.ColorID[table.ColorID.size() - 1];
									tempB.itemNos = table.itemNos[6][table.ColorID.size() - 1];
								}
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.y = ((m.num[2] - z -1)-1)*zD;					//LDD�̂��ɑΉ�����̂͂�
								tempB.trans.z = 0.4+((m.num[0] - x - 4) - 1)*xyD;		//LDD�̂��ɑΉ�����̂͂�
								tempB.rn = 1;									//0:��]�����Ȃ�	1:��]������
								LDD.push_back(tempB);
							}
						}
					}
				}
			}
		}
	}

}


int GetSimilarColor(CColor temp, vector<CColor>& LegoColor)
{
	temp = RGB_to_Lab(temp);			//�F��RGB����CIELab�ɕԊ�
	double min = DBL_MAX;					//�ŏ��l��double�^�̍ő�Ƃ���
	int min_no;										//�ŏ��l���J���[�z��̉��Ԗڂ�
	double 	tempDeltaE;								//�F�̍�
	//L*a*b*�LEGO
	
	for(int i(0); i<LegoColor.size(); i++)
	{
		tempDeltaE = DeltaE(LegoColor[i], temp);
		if(tempDeltaE < min)
		{
			min = tempDeltaE;			//�ŏ��l�̍X�V
			min_no = i;						//�ŏ��l�����Ԗڂ�
		}
	}
	return min_no;
}