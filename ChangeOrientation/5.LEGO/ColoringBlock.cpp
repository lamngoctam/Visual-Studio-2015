#include "../stdafx.h"

void  LegoRGB_to_Lab(Model& m);
CColor RGB_to_Lab(CColor& rgb);
double DeltaE(CColor& aa, CColor& bb);
int GetSimilarColor(CColor temp, vector<CColor>& LegoColor);

extern unsigned int** BlockNum;
extern unsigned int Block_colorNum;				//使用する色の種類
extern unsigned int Block_varietyNum;			//使用する基本ブロックの種類
extern vector<Brick> LDD;
extern BrickTable table;
extern CMatrix rot[2];

//2013/9/23

void ColoringBlock_lavest(Model& m, Lego*** b)
{
	int x,y,z;
	CColor temp( 0.0, 0.0, 0.0);
	int blocknum(0);				//１つのブロックに色付きのボクセルを何個含むか
	int min_no(0);					//最小値が何番目なのか
	CColor anycolor(2.0, 0.0, 0.0);		//色のないブロックにつける色(後ほどOpenDrawで描画するとき使う)
	Brick tempB;

	//#####################################
	//#####################################
	Block_colorNum = m.LegoColor.size() + 1;		//レゴの色の数（＋１は無色の数）
	
	BlockNum = new unsigned int * [Block_varietyNum];
	for(int i(0); i<Block_varietyNum; i++)
		BlockNum[i] = new unsigned int [Block_colorNum];

	//初期化
	for(int i(0); i<Block_varietyNum; i++)
		for(int k(0); k<Block_colorNum; k++)
			BlockNum[i][k] = 0;

	rot[0].assign(3);
	rot[1].assign(3);

	rot[0].IdentifyMatrix();		//単位行列化
	rot[1].SetZero();		//ｘ→ｚLDD（ｙ→ｘこのソース上）90°回転
	rot[1][0][2] = 1.0;
	rot[1][1][1] = 1.0;
	rot[1][2][0] = -1.0;

	double xyD(0.8);			//ｘｙ平面へどれくらい移動するか
	double zD(0.96);			//１層上がるとどれくらい移動するか

	//複数のブロックを削除した後の対応が取れていない
	for(z=1; z<m.num[2]-1; z++)
	{
		for(x=1; x<m.num[0]-1; x++)
		{
			for(y=1; y<m.num[1]-1; y++)
			{
				//cout<<x<<" "<<y<<" "<<z<<endl;
				//###################################
				//１×１の場合
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
					tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
					tempB.trans.y = (z-1)*zD;					//LDDのｙに対応するのはｚ
					tempB.trans.z = 0.4+(x-1)*xyD;		//LDDのｚに対応するのはｘ
					tempB.rn = 0;
					LDD.push_back(tempB);
				}
				//####################################
				//つまりブロックがある場合
				//####################################
				else if(b[x][y][z].flag > 1)
				{
					if(b[x][y][z].corner != 1)
						continue;
					tempB.clear();
					//###################################
					//１×２の場合
					//###################################
					//else if(b[x][y][z].flag == 12 && b[x][y][z].corner == 1)
					if(b[x][y][z].flag == 12)
					{
						//１×２がｙ方向の場合(回転させない)
						if(b[x][y+1][z].flag == 12 && b[x][y][z].ID == b[x][y+1][z].ID && b[x][y+1][z].corner == 2)
						{
							blocknum = 0;
							temp.r = 0.0;
							temp.g = 0.0;
							temp.b = 0.0;
							//表面ボクセルならば色を持つ！
							for(int i(0); i<2; i++)
							{							
								//表面ボクセルならば、色を持つので
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
								//レゴの色へと置換する
								//注目表面ボクセルのRGBからL*a*b*を計算
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
							tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
							tempB.trans.y = (z-1)*zD;					//LDDのｙに対応するのはｚ
							tempB.trans.z = 0.4+(x-1)*xyD;		//LDDのｚに対応するのはｘ
							tempB.rn = 0;									//回転させない
							LDD.push_back(tempB);
							continue;
						}

						//１×２がｘ方向の場合（回転させる）
						if(b[x+1][y][z].flag == 12 && b[x][y][z].ID == b[x+1][y][z].ID && b[x+1][y][z].corner == 2)
						{
							blocknum = 0;
							temp.r = 0.0;
							temp.g = 0.0;
							temp.b = 0.0;
							//表面ボクセルならば色を持つ！
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
								//レゴの色へと置換する
								//注目表面ボクセルのRGBからL*a*b*を計算
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
							tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
							tempB.trans.y = (z-1)*zD;					//LDDのｙに対応するのはｚ
							tempB.trans.z = 0.4+(x-1)*xyD;		//LDDのｚに対応するのはｘ
							tempB.rn = 1;									//回転させない
							LDD.push_back(tempB);
						}
					}
					//###################################
					//１×３の場合
					//###################################
					//else if(b[x][y][z].flag == 13 && b[x][y][z].corner == 1)
					else if(b[x][y][z].flag == 13)
					{
						//１×３がｙ方向の場合
						if(y+2 < m.num[1])
						{
							if(b[x][y+2][z].flag == 13 && b[x][y][z].ID == b[x][y+2][z].ID && b[x][y+2][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;
								//表面ボクセルならば色を持つ！
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
									//レゴの色へと置換する
									//注目表面ボクセルのRGBからL*a*b*を計算
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
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
								tempB.trans.y = (z-1)*zD;					//LDDのｙに対応するのはｚ
								tempB.trans.z = 0.4+(x-1)*xyD;		//LDDのｚに対応するのはｘ
								tempB.rn = 0;									//0:回転させない	1:回転させる
								LDD.push_back(tempB);
								continue;
							}
						}
						//１×３がｘ方向の場合
						if(x+2 < m.num[0])
						{
							if(b[x+2][y][z].flag == 13 && b[x][y][z].ID == b[x+2][y][z].ID && b[x+2][y][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;
								//表面ボクセルならば色を持つ！
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
									//レゴの色へと置換する
									//注目表面ボクセルのRGBからL*a*b*を計算
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
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
								tempB.trans.y = (z-1)*zD;					//LDDのｙに対応するのはｚ
								tempB.trans.z = 0.4+(x-1)*xyD;		//LDDのｚに対応するのはｘ
								tempB.rn = 1;									//0:回転させない	1:回転させる
								LDD.push_back(tempB);
							}
						}
					}
					//###################################
					//１×４の場合
					//###################################
					//else if(b[x][y][z].flag == 14 && b[x][y][z].corner == 1)
					else if(b[x][y][z].flag == 14)
					{
						//１×４がｙ方向の場合
						if(y+3 < m.num[1])
						{
							if(b[x][y+3][z].flag == 14 && b[x][y][z].ID == b[x][y+3][z].ID && b[x][y+3][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;
								//表面ボクセルならば色を持つ！
								for(int i(0); i<4; i++)
								{
									if(b[x][y+i][z].surf)	//なくてもいいかもしれない
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
									//レゴの色へと置換する
									//注目表面ボクセルのRGBからL*a*b*を計算
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
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
								tempB.trans.y = (z-1)*zD;					//LDDのｙに対応するのはｚ
								tempB.trans.z = 0.4+(x-1)*xyD;		//LDDのｚに対応するのはｘ
								tempB.rn = 0;									//0:回転させない	1:回転させる
								LDD.push_back(tempB);
								continue;

							}
						}
						//１×４がｘ方向の場合
						if(x+3 < m.num[0])
						{
							if(b[x+3][y][z].flag == 14 && b[x][y][z].ID == b[x+3][y][z].ID && b[x+3][y][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;
								//表面ボクセルならば色を持つ！
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
									//レゴの色へと置換する
									//注目表面ボクセルのRGBからL*a*b*を計算
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
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
								tempB.trans.y = (z-1)*zD;					//LDDのｙに対応するのはｚ
								tempB.trans.z = 0.4+(x-1)*xyD;		//LDDのｚに対応するのはｘ
								tempB.rn = 1;									//0:回転させない	1:回転させる
								LDD.push_back(tempB);
							}
						}
					}
					//###################################
					//２×２の場合
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
								//レゴの色へと置換する
								//注目表面ボクセルのRGBからL*a*b*を計算
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
							tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
							tempB.trans.y = (z-1)*zD;					//LDDのｙに対応するのはｚ
							tempB.trans.z = 0.4+x*xyD;		//LDDのｚに対応するのはｘ
							tempB.rn = 0;									//0:回転させない	1:回転させる
							LDD.push_back(tempB);
						}
					}
					//###################################
					//２×３の場合
					//###################################
					//else if(b[x][y][z].flag == 23 && b[x][y][z].corner == 1)
					else if(b[x][y][z].flag == 23)
					{
						//２×３がｙ方向の場合
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
									//レゴの色へと置換する
									//注目表面ボクセルのRGBからL*a*b*を計算
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
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
								tempB.trans.y = (z-1)*zD;					//LDDのｙに対応するのはｚ
								tempB.trans.z = 0.4+x*xyD;		//LDDのｚに対応するのはｘ
								tempB.rn = 0;									//0:回転させない	1:回転させる
								LDD.push_back(tempB);
								continue;

							}
						}
						//２×３がｘ方向の場合
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
									//レゴの色へと置換する
									//注目表面ボクセルのRGBからL*a*b*を計算
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
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
								tempB.trans.y = (z-1)*zD;					//LDDのｙに対応するのはｚ
								tempB.trans.z = 0.4+(x-1)*xyD;		//LDDのｚに対応するのはｘ
								tempB.rn = 1;									//0:回転させない	1:回転させる
								LDD.push_back(tempB);
							}
						}
					}
					//###################################
					//２×４の場合
					//###################################
					//else if(b[x][y][z].flag == 24 && b[x][y][z].corner == 1)
					else if(b[x][y][z].flag == 24)
					{
						//２×４がｙ方向の場合
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
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
								tempB.trans.y = (z-1)*zD;					//LDDのｙに対応するのはｚ
								tempB.trans.z = 0.4+x*xyD;		//LDDのｚに対応するのはｘ
								tempB.rn = 0;									//0:回転させない	1:回転させる
								LDD.push_back(tempB);
								continue;
							}
						}
						//２×４がｘ方向の場合
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
									//レゴの色へと置換する
									//注目表面ボクセルのRGBからL*a*b*を計算
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
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
								tempB.trans.y = (z-1)*zD;					//LDDのｙに対応するのはｚ
								tempB.trans.z = 0.4+(x-1)*xyD;		//LDDのｚに対応するのはｘ
								tempB.rn = 1;									//0:回転させない	1:回転させる
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
	int blocknum(0);				//１つのブロックに色付きのボクセルを何個含むか
	int min_no(0);					//最小値が何番目なのか
	CColor anycolor(2.0, 0.0, 0.0);		//色のないブロックにつける色(後ほどOpenDrawで描画するとき使う)
	Brick tempB;

	//#####################################
	//              
	//#####################################
	Block_colorNum = m.LegoColor.size() + 1;		

	BlockNum = new unsigned int * [Block_varietyNum];
	for(int i(0); i<Block_varietyNum; i++)
		BlockNum[i] = new unsigned int [Block_colorNum];

	//初期化
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
				//１×１の場合
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
					tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
					tempB.trans.y = ((m.num[2] - z -1) - 1)*zD;					//LDDのｙに対応するのはｚ
					tempB.trans.z = 0.4+((m.num[0] - x -1) - 1)*xyD;		//LDDのｚに対応するのはｘ
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
					//１×２の場合
					//###################################
					//else if(b[x][y][z].flag == 12 && b[x][y][z].corner == 1)
					if(b[x][y][z].flag == 12)
					{
						//１×２がｙ方向の場合(回転させない)
						if(b[x][y+1][z].flag == 12 && b[x][y][z].ID == b[x][y+1][z].ID && b[x][y+1][z].corner == 2)
						{
							blocknum = 0;
							temp.r = 0.0;
							temp.g = 0.0;
							temp.b = 0.0;
							//表面ボクセルならば色を持つ！
							for(int i(0); i<2; i++)
							{							
								//表面ボクセルならば、色を持つので
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
								//レゴの色へと置換する
								//注目表面ボクセルのRGBからL*a*b*を計算
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
							tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
							tempB.trans.y = ((m.num[2] - z -1)-1)*zD;					//LDDのｙに対応するのはｚ
							tempB.trans.z = 0.4+((m.num[0] - x - 1)-1)*xyD;		//LDDのｚに対応するのはｘ
							tempB.rn = 0;									//回転させない
							LDD.push_back(tempB);
							continue;
						}

						//１×２がｘ方向の場合（回転させる）
						if(b[x+1][y][z].flag == 12 && b[x][y][z].ID == b[x+1][y][z].ID && b[x+1][y][z].corner == 2)
						{
							blocknum = 0;
							temp.r = 0.0;
							temp.g = 0.0;
							temp.b = 0.0;
							//表面ボクセルならば色を持つ！
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
								//レゴの色へと置換する
								//注目表面ボクセルのRGBからL*a*b*を計算
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
							tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
							tempB.trans.y = ((m.num[2] - z -1)-1)*zD;					//LDDのｙに対応するのはｚ
							tempB.trans.z = 0.4+((m.num[0] - x -2)-1)*xyD;		//LDDのｚに対応するのはｘ
							tempB.rn = 1;									//回転させない
							LDD.push_back(tempB);
						}
					}
					//###################################
					//１×３の場合
					//###################################
					//else if(b[x][y][z].flag == 13 && b[x][y][z].corner == 1)
					else if(b[x][y][z].flag == 13)
					{
						//１×３がｙ方向の場合
						if(y+2 < m.num[1])
						{
							if(b[x][y+2][z].flag == 13 && b[x][y][z].ID == b[x][y+2][z].ID && b[x][y+2][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;
								//表面ボクセルならば色を持つ！
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
									//レゴの色へと置換する
									//注目表面ボクセルのRGBからL*a*b*を計算
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
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
								tempB.trans.y = ((m.num[2] - z -1)-1)*zD;					//LDDのｙに対応するのはｚ
								tempB.trans.z = 0.4+((m.num[0] - x - 1)-1)*xyD;		//LDDのｚに対応するのはｘ
								tempB.rn = 0;									//0:回転させない	1:回転させる
								LDD.push_back(tempB);
								continue;
							}
						}
						//１×３がｘ方向の場合
						if(x+2 < m.num[0])
						{
							if(b[x+2][y][z].flag == 13 && b[x][y][z].ID == b[x+2][y][z].ID && b[x+2][y][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;
								//表面ボクセルならば色を持つ！
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
									//レゴの色へと置換する
									//注目表面ボクセルのRGBからL*a*b*を計算
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
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
								tempB.trans.y = ((m.num[2] - z -1)-1)*zD;					//LDDのｙに対応するのはｚ
								tempB.trans.z = 0.4+((m.num[0] - x -3)-1)*xyD;		//LDDのｚに対応するのはｘ
								tempB.rn = 1;									//0:回転させない	1:回転させる
								LDD.push_back(tempB);
							}
						}
					}
					//###################################
					//１×４の場合
					//###################################
					//else if(b[x][y][z].flag == 14 && b[x][y][z].corner == 1)
					else if(b[x][y][z].flag == 14)
					{
						//１×４がｙ方向の場合
						if(y+3 < m.num[1])
						{
							if(b[x][y+3][z].flag == 14 && b[x][y][z].ID == b[x][y+3][z].ID && b[x][y+3][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;
								//表面ボクセルならば色を持つ！
								for(int i(0); i<4; i++)
								{
									if(b[x][y+i][z].surf)	//なくてもいいかもしれない
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
									//レゴの色へと置換する
									//注目表面ボクセルのRGBからL*a*b*を計算
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
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
								tempB.trans.y = ((m.num[2] - z -1)-1)*zD;					//LDDのｙに対応するのはｚ
								tempB.trans.z = 0.4+((m.num[0] - x - 1)-1)*xyD;		//LDDのｚに対応するのはｘ
								tempB.rn = 0;									//0:回転させない	1:回転させる
								LDD.push_back(tempB);
								continue;

							}
						}
						//１×４がｘ方向の場合
						if(x+3 < m.num[0])
						{
							if(b[x+3][y][z].flag == 14 && b[x][y][z].ID == b[x+3][y][z].ID && b[x+3][y][z].corner == 2)
							{
								blocknum = 0;
								temp.r = 0.0;
								temp.g = 0.0;
								temp.b = 0.0;
								//表面ボクセルならば色を持つ！
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
									//レゴの色へと置換する
									//注目表面ボクセルのRGBからL*a*b*を計算
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
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
								tempB.trans.y = ((m.num[2] - z -1)-1)*zD;					//LDDのｙに対応するのはｚ
								tempB.trans.z = 0.4+((m.num[0] - x - 4) - 1)*xyD;		//LDDのｚに対応するのはｘ
								tempB.rn = 1;									//0:回転させない	1:回転させる
								LDD.push_back(tempB);
							}
						}
					}
					//###################################
					//２×２の場合
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
								//レゴの色へと置換する
								//注目表面ボクセルのRGBからL*a*b*を計算
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
							tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
							tempB.trans.y = ((m.num[2] - z -1)-1)*zD;					//LDDのｙに対応するのはｚ
							tempB.trans.z = 0.4+(m.num[0] - x - 2)*xyD;		//LDDのｚに対応するのはｘ
							tempB.rn = 0;									//0:回転させない	1:回転させる
							LDD.push_back(tempB);
						}
					}
					//###################################
					//２×３の場合
					//###################################
					//else if(b[x][y][z].flag == 23 && b[x][y][z].corner == 1)
					else if(b[x][y][z].flag == 23)
					{
						//２×３がｙ方向の場合
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
									//レゴの色へと置換する
									//注目表面ボクセルのRGBからL*a*b*を計算
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
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
								tempB.trans.y = ((m.num[2] - z -1)-1)*zD;					//LDDのｙに対応するのはｚ
								tempB.trans.z = 0.4+(m.num[0] - x - 2)*xyD;		//LDDのｚに対応するのはｘ
								tempB.rn = 0;									//0:回転させない	1:回転させる
								LDD.push_back(tempB);
								continue;

							}
						}
						//２×３がｘ方向の場合
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
									//レゴの色へと置換する
									//注目表面ボクセルのRGBからL*a*b*を計算
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
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
								tempB.trans.y = ((m.num[2] - z -1)-1)*zD;					//LDDのｙに対応するのはｚ
								tempB.trans.z = 0.4+((m.num[0] - x - 3)-1)*xyD;		//LDDのｚに対応するのはｘ
								tempB.rn = 1;									//0:回転させない	1:回転させる
								LDD.push_back(tempB);
							}
						}
					}
					//###################################
					//２×４の場合
					//###################################
					//else if(b[x][y][z].flag == 24 && b[x][y][z].corner == 1)
					else if(b[x][y][z].flag == 24)
					{
						//２×４がｙ方向の場合
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
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
								tempB.trans.y = ((m.num[2] - z -1)-1)*zD;					//LDDのｙに対応するのはｚ
								tempB.trans.z = 0.4+(m.num[0] - x - 2)*xyD;		//LDDのｚに対応するのはｘ
								tempB.rn = 0;									//0:回転させない	1:回転させる
								LDD.push_back(tempB);
								continue;
							}
						}
						//２×４がｘ方向の場合
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
									//レゴの色へと置換する
									//注目表面ボクセルのRGBからL*a*b*を計算
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
								tempB.trans.x = 0.4+(y-1)*xyD;		//LDDのｘに対応するのはｙ
								tempB.trans.y = ((m.num[2] - z -1)-1)*zD;					//LDDのｙに対応するのはｚ
								tempB.trans.z = 0.4+((m.num[0] - x - 4) - 1)*xyD;		//LDDのｚに対応するのはｘ
								tempB.rn = 1;									//0:回転させない	1:回転させる
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
	temp = RGB_to_Lab(temp);			//色をRGBからCIELabに返還
	double min = DBL_MAX;					//最小値をdouble型の最大とおく
	int min_no;										//最小値がカラー配列の何番目か
	double 	tempDeltaE;								//色の差
	//L*a*b*�LEGO
	
	for(int i(0); i<LegoColor.size(); i++)
	{
		tempDeltaE = DeltaE(LegoColor[i], temp);
		if(tempDeltaE < min)
		{
			min = tempDeltaE;			//最小値の更新
			min_no = i;						//最小値が何番目か
		}
	}
	return min_no;
}