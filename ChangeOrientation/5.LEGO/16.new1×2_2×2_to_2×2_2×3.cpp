#include "../stdafx.h"

extern int ID22;
extern int ID23;
extern int ID14;
extern int num12;		//１×２のブロックの数
extern int num22;		//２×２のブロックの数
extern int num23;		//２×３のブロックの数
extern int num14;		//1×4のブロックの数

void outputFlag(string filename, int* size);

//Input：		１×１　と　１×１　によってできた　(１×２)　と　１×２　と　１×２　(２×２)　によってできたもんを合成だもん！
//Output：	できるのは	２×２　または　２×３
void Small_to_Big_step6(Lego*** block, int*  VoxSize)
{
	int x,y,z;
	int count(0);

	for(z=1; z < VoxSize[2]-1; z++ )
	{
		//奇数層
		if(z%2)
		{
			for(x=1; x < VoxSize[0]-1; x=x+2)
			{
				for(y=1; y < VoxSize[1]-1; y=y+2)
				{
					//左上===========================================================
					if(block[x][y][z].flag == 12)
					{
						//上を見る
						if(block[x-1][y][z].flag == 12 && block[x-1][y][z].ID == block[x][y][z].ID)
						{
							//左に１×２（１×１と１×１によって合成できたものならば）があれば
							if(block[x-1][y-1][z].flag == 12 && block[x][y-1][z].flag == 12 && block[x-1][y-1][z].ID == block[x][y-1][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y-k][z].flag = 22;
										block[x-i][y-k][z].ID = ID22;
									}
								}
								block[x-1][y-1][z].corner = 1;
								block[x][y][z].corner = 2;

							}
							//左に２×２（１×２と１×２によって合成できたものならば）があれば
							else if(block[x-1][y-1][z].flag == 22)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<3; k++)
									{
										block[x-i][y-k][z].flag = 23;
										block[x-i][y-k][z].ID = ID23;
									}
								}
								block[x-1][y-2][z].corner = 1;
								block[x][y][z].corner = 2;
							}
						}
						//左を見る
						else if(block[x][y-1][z].flag == 12 && block[x][y-1][z].ID == block[x][y][z].ID)
						{
							//上に１×２（１×１と１×１によって合成できたものならば）があれば
							if(block[x-1][y-1][z].flag == 12 && block[x-1][y][z].flag == 12 && block[x-1][y-1][z].ID == block[x-1][y][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y-k][z].flag = 22;
										block[x-i][y-k][z].ID = ID22;
									}
								}
								block[x-1][y-1][z].corner = 1;
								block[x][y][z].corner = 2;
							}
							//上に２×２（１×２と１×２によって合成できたものならば）があれば
							else if(block[x-1][y-1][z].flag == 22)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								count++;
								for(int i(0); i<3; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y-k][z].flag = 23;
										block[x-i][y-k][z].ID = ID23;
									}
								}
								block[x-2][y-1][z].corner = 1;
								block[x][y][z].corner = 2;
							}
						}
					}

					//右上===========================================================
					else if(block[x][y+1][z].flag == 12)
					{
						//右を見る
						if(block[x][y+2][z].flag ==12 && block[x][y+2][z].ID == block[x][y+1][z].ID)
						{
							//上に１×２がある場合
							if(block[x-1][y+1][z].flag ==12 && block[x-1][y+2][z].flag ==12 && block[x-1][y+1][z].ID == block[x-1][y+2][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y+k+1][z].flag = 22;
										block[x-i][y+k+1][z].ID = ID22;
									}
								}
								block[x-1][y+1][z].corner = 1;
								block[x][y+2][z].corner = 2;
							}
							//上に２×２がある場合
							else if(block[x-1][y+2][z].flag == 22)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								count++;
								for(int i(0); i<3; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y+k+1][z].flag = 23;
										block[x-i][y+k+1][z].ID = ID23;
									}
								}
								block[x-2][y+1][z].corner = 1;
								block[x][y+2][z].corner = 2;
							}
						}
						//上を見る
						else if(block[x-1][y+1][z].flag == 12 && block[x-1][y+1][z].ID == block[x][y+1][z].ID)
						{
							//右に１×２がある場合
							if(block[x][y+2][z].flag == 12 && block[x-1][y+2][z].flag == 12 && block[x][y+2][z].ID == block[x-1][y+2][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y+k+1][z].flag = 22;
										block[x-i][y+k+1][z].ID = ID22;
									}
								}
								block[x-1][y+1][z].corner = 1;
								block[x][y+2][z].corner = 2;
							}
							//右に２×２がある場合
							else if(block[x-1][y+2][z].flag == 22)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<3; k++)
									{
										block[x-i][y+k+1][z].flag = 23;
										block[x-i][y+k+1][z].ID = ID23;
									}
								}
								block[x-1][y+1][z].corner = 1;
								block[x][y+3][z].corner = 2;
							}
						}
					}
					//左下===========================================================
					else if(block[x+1][y][z].flag == 12)
					{
						//左を見る
						if(block[x+1][y-1][z].flag == 12 && block[x+1][y-1][z].ID == block[x+1][y][z].ID)
						{
							//下に１×２がある場合
							if(block[x+2][y-1][z].flag == 12 && block[x+2][y][z].flag == 12 && block[x+2][y-1][z].ID == block[x+2][y][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y-k][z].flag = 22;
										block[x+i+1][y-k][z].ID = ID22;
									}
								}
								block[x+1][y-1][z].corner = 1;
								block[x+2][y][z].corner = 2;
							}
							//下に２×２がある場合
							else if(block[x+2][y-1][z].flag == 22)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								count++;
								for(int i(0); i<3; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y-k][z].flag = 23;
										block[x+i+1][y-k][z].ID = ID23;
									}
								}
								block[x+1][y-1][z].corner = 1;
								block[x+3][y][z].corner = 2;
							}
						}
						//下を見る
						else if(block[x+2][y][z].flag == 12 && block[x+2][y][z].ID == block[x+1][y][z].ID)
						{
							//左に１×２がある場合
							if(block[x+1][y-1][z].flag == 12 && block[x+2][y-1][z].flag == 12 && block[x+1][y-1][z].ID == block[x+2][y-1][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y-k][z].flag = 22;
										block[x+i+1][y-k][z].ID = ID22;
									}
								}
								block[x+1][y-1][z].corner = 1;
								block[x+2][y][z].corner = 2;
							}
							//左に２×２がある場合
							else if(block[x+2][y-1][z].flag == 22)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<3; k++)
									{
										block[x+i+1][y-k][z].flag = 23;
										block[x+i+1][y-k][z].ID = ID23;
									}
								}
								block[x+1][y-2][z].corner = 1;
								block[x+2][y][z].corner = 2;
							}
						}

					}

					//右下===========================================================
					else if(block[x+1][y+1][z].flag == 12)
					{
						//右を見る
						if(block[x+1][y+2][z].flag == 12 && block[x+1][y+2][z].ID == block[x+1][y+1][z].ID)
						{
							//下に１×２がある場合
							if(block[x+2][y+1][z].flag == 12 && block[x+2][y+2][z].flag == 12 && block[x+2][y+1][z].ID ==  block[x+2][y+2][z].ID )
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y+k+1][z].flag = 22;
										block[x+i+1][y+k+1][z].ID = ID22;
									}
								}
								block[x+1][y+1][z].corner = 1;
								block[x+2][y+2][z].corner = 2;
							}
							//下に２×２がある場合
							else if(block[x+2][y+2][z].flag == 22)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								count++;
								for(int i(0); i<3; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y+k+1][z].flag = 23;
										block[x+i+1][y+k+1][z].ID = ID23;
									}
								}
								block[x+1][y+1][z].corner = 1;
								block[x+3][y+2][z].corner = 2;
							}
						}
						//下を見る
						else if(block[x+2][y+1][z].flag == 12 && block[x+2][y+1][z].ID == block[x+1][y+1][z].ID)
						{
							//右に１×２がある場合
							if(block[x+1][y+2][z].flag == 12 && block[x+2][y+2][z].flag == 12 && block[x+1][y+2][z].ID == block[x+2][y+2][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y+k+1][z].flag = 22;
										block[x+i+1][y+k+1][z].ID = ID22;
									}
								}
								block[x+1][y+1][z].corner = 1;
								block[x+2][y+2][z].corner = 2;
							}
							//右に２×２がある場合
							else if(block[x+2][y+2][z].flag == 22)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<3; k++)
									{
										block[x+i+1][y+k+1][z].flag = 23;
										block[x+i+1][y+k+1][z].ID = ID23;
									}
								}
								block[x+1][y+1][z].corner = 1;
								block[x+2][y+3][z].corner = 2;
							}
						}
					}
				}
			}
		}
		//偶数層
		else
		{
			for(x=0; x < VoxSize[0]-1; x=x+2)
			{
				for(y=0; y < VoxSize[1]-1; y=y+2)
				{
					//左上===========================================================
					if(block[x][y][z].flag == 12)
					{
						//上を見る
						if(block[x-1][y][z].flag == 12 && block[x-1][y][z].ID == block[x][y][z].ID)
						{
							//左に１×２（１×１と１×１によって合成できたものならば）があれば
							if(block[x-1][y-1][z].flag == 12 && block[x][y-1][z].flag == 12 && block[x-1][y-1][z].ID == block[x][y-1][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y-k][z].flag = 22;
										block[x-i][y-k][z].ID = ID22;
									}
								}
								block[x-1][y-1][z].corner = 1;
								block[x][y][z].corner = 2;

							}
							//左に２×２（１×２と１×２によって合成できたものならば）があれば
							else if(block[x-1][y-1][z].flag == 22)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<3; k++)
									{
										block[x-i][y-k][z].flag = 23;
										block[x-i][y-k][z].ID = ID23;
									}
								}
								block[x-1][y-2][z].corner = 1;
								block[x][y][z].corner = 2;
							}
						}
						//左を見る
						else if(block[x][y-1][z].flag == 12 && block[x][y-1][z].ID == block[x][y][z].ID)
						{
							//上に１×２（１×１と１×１によって合成できたものならば）があれば
							if(block[x-1][y-1][z].flag == 12 && block[x-1][y][z].flag == 12 && block[x-1][y-1][z].ID == block[x-1][y][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y-k][z].flag = 22;
										block[x-i][y-k][z].ID = ID22;
									}
								}
								block[x-1][y-1][z].corner = 1;
								block[x][y][z].corner = 2;
							}
							//上に２×２（１×２と１×２によって合成できたものならば）があれば
							else if(block[x-1][y-1][z].flag == 22)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								count++;
								for(int i(0); i<3; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y-k][z].flag = 23;
										block[x-i][y-k][z].ID = ID23;
									}
								}
								block[x-2][y-1][z].corner = 1;
								block[x][y][z].corner = 2;
							}
						}
					}

					//右上===========================================================
					else if(block[x][y+1][z].flag == 12)
					{
						//右を見る
						if(block[x][y+2][z].flag ==12 && block[x][y+2][z].ID == block[x][y+1][z].ID)
						{
							//上に１×２がある場合
							if(block[x-1][y+1][z].flag ==12 && block[x-1][y+2][z].flag ==12 && block[x-1][y+1][z].ID == block[x-1][y+2][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y+k+1][z].flag = 22;
										block[x-i][y+k+1][z].ID = ID22;
									}
								}
								block[x-1][y+1][z].corner = 1;
								block[x][y+2][z].corner = 2;
							}
							//上に２×２がある場合
							else if(block[x-1][y+2][z].flag == 22)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								count++;
								for(int i(0); i<3; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y+k+1][z].flag = 23;
										block[x-i][y+k+1][z].ID = ID23;
									}
								}
								block[x-2][y+1][z].corner = 1;
								block[x][y+2][z].corner = 2;
							}
						}
						//上を見る
						else if(block[x-1][y+1][z].flag == 12 && block[x-1][y+1][z].ID == block[x][y+1][z].ID)
						{
							//右に１×２がある場合
							if(block[x][y+2][z].flag == 12 && block[x-1][y+2][z].flag == 12 && block[x][y+2][z].ID == block[x-1][y+2][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y+k+1][z].flag = 22;
										block[x-i][y+k+1][z].ID = ID22;
									}
								}
								block[x-1][y+1][z].corner = 1;
								block[x][y+2][z].corner = 2;
							}
							//右に２×２がある場合
							else if(block[x-1][y+2][z].flag == 22)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<3; k++)
									{
										block[x-i][y+k+1][z].flag = 23;
										block[x-i][y+k+1][z].ID = ID23;
									}
								}
								block[x-1][y+1][z].corner = 1;
								block[x][y+3][z].corner = 2;
							}
						}
					}
					//左下===========================================================
					else if(block[x+1][y][z].flag == 12)
					{
						//左を見る
						if(block[x+1][y-1][z].flag == 12 && block[x+1][y-1][z].ID == block[x+1][y][z].ID)
						{
							//下に１×２がある場合
							if(block[x+2][y-1][z].flag == 12 && block[x+2][y][z].flag == 12 && block[x+2][y-1][z].ID == block[x+2][y][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y-k][z].flag = 22;
										block[x+i+1][y-k][z].ID = ID22;
									}
								}
								block[x+1][y-1][z].corner = 1;
								block[x+2][y][z].corner = 2;
							}
							//下に２×２がある場合
							else if(block[x+2][y-1][z].flag == 22)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								count++;
								for(int i(0); i<3; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y-k][z].flag = 23;
										block[x+i+1][y-k][z].ID = ID23;
									}
								}
								block[x+1][y-1][z].corner = 1;
								block[x+3][y][z].corner = 2;
							}
						}
						//下を見る
						else if(block[x+2][y][z].flag == 12 && block[x+2][y][z].ID == block[x+1][y][z].ID)
						{
							//左に１×２がある場合
							if(block[x+1][y-1][z].flag == 12 && block[x+2][y-1][z].flag == 12 && block[x+1][y-1][z].ID == block[x+2][y-1][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y-k][z].flag = 22;
										block[x+i+1][y-k][z].ID = ID22;
									}
								}
								block[x+1][y-1][z].corner = 1;
								block[x+2][y][z].corner = 2;
							}
							//左に２×２がある場合
							else if(block[x+2][y-1][z].flag == 22)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<3; k++)
									{
										block[x+i+1][y-k][z].flag = 23;
										block[x+i+1][y-k][z].ID = ID23;
									}
								}
								block[x+1][y-2][z].corner = 1;
								block[x+2][y][z].corner = 2;
							}
						}

					}

					//右下===========================================================
					else if(block[x+1][y+1][z].flag == 12)
					{
						//右を見る
						if(block[x+1][y+2][z].flag == 12 && block[x+1][y+2][z].ID == block[x+1][y+1][z].ID)
						{
							//下に１×２がある場合
							if(block[x+2][y+1][z].flag == 12 && block[x+2][y+2][z].flag == 12 && block[x+2][y+1][z].ID ==  block[x+2][y+2][z].ID )
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y+k+1][z].flag = 22;
										block[x+i+1][y+k+1][z].ID = ID22;
									}
								}
								block[x+1][y+1][z].corner = 1;
								block[x+2][y+2][z].corner = 2;
							}
							//下に２×２がある場合
							else if(block[x+2][y+2][z].flag == 22)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								count++;
								for(int i(0); i<3; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y+k+1][z].flag = 23;
										block[x+i+1][y+k+1][z].ID = ID23;
									}
								}
								block[x+1][y+1][z].corner = 1;
								block[x+3][y+2][z].corner = 2;
							}
						}
						//下を見る
						else if(block[x+2][y+1][z].flag == 12 && block[x+2][y+1][z].ID == block[x+1][y+1][z].ID)
						{
							//右に１×２がある場合
							if(block[x+1][y+2][z].flag == 12 && block[x+2][y+2][z].flag == 12 && block[x+1][y+2][z].ID == block[x+2][y+2][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y+k+1][z].flag = 22;
										block[x+i+1][y+k+1][z].ID = ID22;
									}
								}
								block[x+1][y+1][z].corner = 1;
								block[x+2][y+2][z].corner = 2;
							}
							//右に２×２がある場合
							else if(block[x+2][y+2][z].flag == 22)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<3; k++)
									{
										block[x+i+1][y+k+1][z].flag = 23;
										block[x+i+1][y+k+1][z].ID = ID23;
									}
								}
								block[x+1][y+1][z].corner = 1;
								block[x+2][y+3][z].corner = 2;
							}
						}
					}

				}
			}
		}
	}

	cout<<count<<"個の２×２or２×３が　１×２（１×１と１×１からなる）と２×２（１×２と１×２からなる）からできた"<<endl;
	//outputFlag("test6_12_22_to_22_23.txt", VoxSize);

}

//最終合成
void Small_to_Big_step8(Lego*** block, int*  VoxSize)
{
	int x,y,z;
	int count(0);

	for(z=1; z < VoxSize[2]-1; z++ )
	{
			for(x=1; x < VoxSize[0]-1; x=x+1)
			{
				for(y=1; y < VoxSize[1]-1; y=y+1)
				{
					//左上===========================================================
					if(block[x][y][z].flag == 12)
					{
						//上を見る
						if(block[x-1][y][z].flag == 12 && block[x-1][y][z].ID == block[x][y][z].ID)
						{
							//左に１×２（１×１と１×１によって合成できたものならば）があれば
							if(block[x][y][z].ColorID==block[x-1][y-1][z].ColorID)
							if(block[x-1][y-1][z].flag == 12 && block[x][y-1][z].flag == 12 && block[x-1][y-1][z].ID == block[x][y-1][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y-k][z].flag = 22;
										block[x-i][y-k][z].ID = ID22;
									}
								}
								block[x-1][y-1][z].corner = 1;
								block[x][y][z].corner = 2;

							}
							//左に２×２（１×２と１×２によって合成できたものならば）があれば
							else if(block[x-1][y-1][z].flag == 22)
							if(block[x][y][z].ColorID==block[x-1][y-1][z].ColorID)
								if(block[x-1][y-1][z].ID==block[x][y-2][z].ID)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<3; k++)
									{
										block[x-i][y-k][z].flag = 23;
										block[x-i][y-k][z].ID = ID23;
									}
								}
								block[x-1][y-2][z].corner = 1;
								block[x][y][z].corner = 2;
							}
							//左に1×２（１×1と１×1によって合成できたものならば）があれば
							else if(block[x-2][y][z].flag == 12)
							if(block[x][y][z].ColorID==block[x-2][y][z].ColorID)
								if(block[x-2][y][z].ID==block[x-3][y][z].ID)
							{
								ID14++;
								num12--;
								num12--;
								num14++;
								count++;
									for(int k(0); k<4; k++)
									{
										block[x-k][y][z].flag = 14;
										block[x-k][y][z].ID = ID14;
									}
								block[x-3][y][z].corner = 1;
								block[x][y][z].corner = 2;
							}
								//右に2×2（1×2と1×2によって合成できたものならば）
							else if(block[x-1][y+1][z].flag == 22)
							if(block[x][y][z].ColorID==block[x-1][y+2][z].ColorID)
								if(block[x-1][y+2][z].ID==block[x][y+3][z].ID)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<3; k++)
									{
										block[x-i][y+k][z].flag = 23;
										block[x-i][y+k][z].ID = ID23;
									}
								}
								block[x-1][y][z].corner = 1;
								block[x][y+2][z].corner = 2;
							}
						}
						

						//左を見る
						else if(block[x][y-1][z].flag == 12 && block[x][y-1][z].ID == block[x][y][z].ID)
						{
							//上に１×２（１×１と１×１によって合成できたものならば）があれば
							if(block[x][y][z].ColorID==block[x-1][y-1][z].ColorID)
							if(block[x-1][y-1][z].flag == 12 && block[x-1][y][z].flag == 12 && block[x-1][y-1][z].ID == block[x-1][y][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y-k][z].flag = 22;
										block[x-i][y-k][z].ID = ID22;
									}
								}
								block[x-1][y-1][z].corner = 1;
								block[x][y][z].corner = 2;
							}
							//上に２×２（１×２と１×２によって合成できたものならば）があれば
							else if(block[x-1][y-1][z].flag == 22)
							if(block[x][y][z].ColorID==block[x-1][y-1][z].ColorID)
								if(block[x-1][y-1][z].ID==block[x-2][y][z].ID)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								count++;
								for(int i(0); i<3; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y-k][z].flag = 23;
										block[x-i][y-k][z].ID = ID23;
									}
								}
								block[x-2][y-1][z].corner = 1;
								block[x][y][z].corner = 2;
							}
				
							//上に1×２（１×1と１×1によって合成できたものならば）があれば
							else if(block[x][y-2][z].flag == 12)
							if(block[x][y][z].ColorID==block[x][y-2][z].ColorID)
								if(block[x][y-2][z].ID==block[x][y-3][z].ID)
							{
								ID14++;
								num12--;
								num12--;
								num14++;
								count++;
								for(int i(0); i<4; i++)
								{
										block[x][y-i][z].flag = 14;
										block[x][y-i][z].ID = ID14;
								}
								block[x][y-3][z].corner = 1;
								block[x][y][z].corner = 2;
							}
							//下に２×２（１×２と１×２によって合成できたものならば）があれば
							else if(block[x+1][y][z].flag == 22)
							if(block[x][y][z].ColorID==block[x+1][y][z].ColorID)
								if(block[x+1][y][z].ID==block[x+2][y-1][z].ID)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								count++;
								for(int i(0); i<3; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y-k][z].flag = 23;
										block[x+i][y-k][z].ID = ID23;
									}
								}
								block[x][y-1][z].corner = 1;
								block[x+2][y][z].corner = 2;
							}
				
						}
					}
				}
			}
		}


	std::cout<<"count: "<<count<<"\nSmall_to_Big_step8 Finish\n"<<endl;
	//outputFlag("test6_12_22_to_22_23.txt", VoxSize);

}

void Coloring_ID(Lego*** block, int*  VoxSize){
	cout << "Coloring ID\n";

	int x,y,z;
	for(int i(0); i<4 ; i++)
		for(z=1; z < VoxSize[2]-1; z++ )
	{
			for(x=1; x < VoxSize[0]-1; x=x+1)
			{
				for(y=1; y < VoxSize[1]-1; y=y+1)
				{
					if(!block[x][y][z].fill)continue;
					if(block[x][y][z].ColorID==0)continue;
					if(block[x][y][z].flag<10)continue;

					if (block[x+1][y][z].flag==block[x][y][z].flag&&block[x+1][y][z].ID==block[x][y][z].ID)
						block[x+1][y][z].ColorID=block[x][y][z].ColorID;
					if (block[x-1][y][z].flag==block[x][y][z].flag&&block[x-1][y][z].ID==block[x][y][z].ID)
						block[x-1][y][z].ColorID=block[x][y][z].ColorID;
					if (block[x][y+1][z].flag==block[x][y][z].flag&&block[x][y+1][z].ID==block[x][y][z].ID)
						block[x][y+1][z].ColorID=block[x][y][z].ColorID;
					if (block[x][y-1][z].flag==block[x][y][z].flag&&block[x][y-1][z].ID==block[x][y][z].ID)
						block[x][y-1][z].ColorID=block[x][y][z].ColorID;
				}
			}
		}
}