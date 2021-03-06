#include "../stdafx.h"
#include "../Voxel.h"
#include "../Lego.h"		//LEGOブロックを組み立てるためのクラス

extern int ID14;
extern int ID22;
extern int ID23;

extern int num12;		//１×２のブロックの数
extern int num14;		//１×４のブロックの数
extern int num22;		//２×２のブロックの数
extern int num23;		//２×３のブロックの数

void outputFlag(string filename, int* size);

//１×２の４方向に　1×２　または　２×２　があったら結合させる
//１×２の長辺方向が　X軸　か　Y軸　かにより場合わけがある
//さらに、奇数の層と偶数の層に分ける
void Small_to_Big_step4(Lego*** block, int*  VoxSize)
{
	int x,y,z;
	for(z=1; z < VoxSize[2]-1; z++ ){
		//#######################
		//                       奇数層                         
		//#######################
		if(z%2){
			for(x=1; x < VoxSize[0]-1; x=x+2){
				for(y=1; y < VoxSize[1]-1; y=y+2){
					//上                                                                                                                                    
					if(block[x][y][z].flag == 2 && block[x][y+1][z].flag == 2)
					{
						//右を見る（1×２）があったら１×４にする
						if(block[x][y+2][z].flag == 2)
						{
							if(block[x][y+3][z].flag == 2)
							{
								ID14++;
								num12 = num12 - 2;
								num14++;
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
						//上を見る（１×２）または（２×２）があったら合体
						if(block[x-1][y][z].flag == 2 && block[x-1][y+1][z].flag == 2)
						{
							ID22++;
							num12 = num12 - 2;
							num22++;
							for(int i(0); i<2; i++)
							{
								for(int k(0); k<2; k++)
								{
									block[x-i][y+k][z].flag = 22;
									block[x-i][y+k][z].ID = ID22;
								}
							}
							block[x-1][y][z].corner = 1;
							block[x][y+1][z].corner = 2;
							continue;
						}
						else if(block[x-1][y][z].flag == 4)
						{
							ID23++;
							num12--;
							num22--;
							num23++;
							for(int i(0); i<3; i++)
							{
								for(int k(0); k<2; k++)
								{
									block[x-i][y+k][z].flag = 23;
									block[x-i][y+k][z].ID = ID23;
								}
							}
							block[x-2][y][z].corner = 1;
							block[x][y+1][z].corner = 2;
							continue;
						}
					}
					//左                                                                                                                                  
					else if(block[x][y][z].flag == 2 && block[x+1][y][z].flag == 2)
					{
						//下を見る（1×２）があったら１×４にする
						if(block[x+2][y][z].flag == 2)
						{
							if(block[x+3][y][z].flag == 2)
							{
								ID14++;
								num12 = num12 - 2;
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
						//左を見る（１×２）または（２×２）があったら合体
						if(block[x][y-1][z].flag == 2 && block[x+1][y-1][z].flag == 2)
						{
							ID22++;
							num12 = num12 - 2;
							num22++;
							for(int i(0); i<2; i++)
							{
								for(int k(0); k<2; k++)
								{
									block[x+i][y-k][z].flag = 22;
									block[x+i][y-k][z].ID = ID22;
								}
							}
							block[x][y-1][z].corner = 1;
							block[x+1][y][z].corner = 2;
							continue;
						}
						else if(block[x][y-1][z].flag == 4)
						{
							ID23++;
							num12--;
							num22--;
							num23++;
							for(int i(0); i<2; i++)
							{
								for(int k(0); k<3; k++)
								{
									block[x+i][y-k][z].flag = 23;
									block[x+i][y-k][z].ID = ID23;
								}
							}
							block[x][y-2][z].corner = 1;
							block[x+1][y][z].corner = 2;
							continue;
						}

					}
					//下                                                                                                                                                           
					else if(block[x+1][y][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						//右を見る（1×２）があったら１×４にする
						if(block[x+1][y+2][z].flag == 2 )
						{
							if(block[x+1][y+3][z].flag == 2)
							{
								ID14++;
								num12 = num12 - 2;
								num14++;
								for(int i(0); i<4; i++)
								{
									block[x+1][y+i][z].flag = 14;
									block[x+1][y+i][z].ID = ID14;
								}
								block[x+1][y][z].corner = 1;
								block[x+1][y+3][z].corner = 2;
								continue;
							}
						}
						//下を見る（１×２）または（２×２）があったら合体
						if(block[x+2][y][z].flag == 2 && block[x+2][y+1][z].flag == 2)
						{
							ID22++;
							num12 = num12 - 2;
							num22++;
							for(int i(0); i<2; i++)
							{
								for(int k(0); k<2; k++)
								{
									block[x+i+1][y+k][z].flag = 22;
									block[x+i+1][y+k][z].ID = ID22;
								}
							}
							block[x+1][y][z].corner = 1;
							block[x+2][y+1][z].corner = 2;
							continue;
						}
						else if(block[x+2][y][z].flag == 4)
						{
							ID23++;
							num12--;
							num22--;
							num23++;
							for(int i(0); i<3; i++)
							{
								for(int k(0); k<2; k++)
								{
									block[x+i+1][y+k][z].flag = 23;
									block[x+i+1][y+k][z].ID = ID23;
								}
							}
							block[x+1][y][z].corner = 1;
							block[x+3][y+1][z].corner = 2;
							continue;
						}
					}
					//右                                                                                                                                                           
					else if(block[x][y+1][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						//下を見る（1×２）があったら１×４にする
						if(block[x+2][y+1][z].flag == 2)
						{
							if(block[x+3][y+1][z].flag == 2)
							{
								ID14++;
								num12 = num12 - 2;
								num14++;
								for(int i(0); i<4; i++)
								{
									block[x+i][y+1][z].flag = 14;
									block[x+i][y+1][z].ID = ID14;
								}
								block[x][y+1][z].corner = 1;
								block[x+3][y+1][z].corner = 2;
								continue;
							}
						}
						//右を見る（１×２）または（２×２）があったら合体
						if(block[x][y+2][z].flag == 2 && block[x+1][y+2][z].flag == 2)
						{
							ID22++;
							num12 = num12 - 2;
							num22++;
							for(int i(0); i<2; i++)
							{
								for(int k(0); k<2; k++)
								{
									block[x+i][y+k+1][z].flag = 22;
									block[x+i][y+k+1][z].ID = ID22;
								}
							}
							block[x][y+1][z].corner = 1;
							block[x+1][y+2][z].corner = 2;
							continue;
						}
						else if(block[x][y+2][z].flag == 4)
						{
							ID23++;
							num12--;
							num22--;
							num23++;
							for(int i(0); i<2; i++)
							{
								for(int k(0); k<3; k++)
								{
									block[x+i][y+k+1][z].flag = 23;
									block[x+i][y+k+1][z].ID = ID23;
								}
							}
							block[x][y+1][z].corner = 1;
							block[x+1][y+3][z].corner = 2;
							continue;
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
					//上                                                                                                                                    
					if(block[x][y][z].flag == 2 && block[x][y+1][z].flag == 2)
					{
						//右を見る（1×２）があったら１×４にする
						if(block[x][y+2][z].flag == 2 )
						{
							if(block[x][y+3][z].flag == 2)
							{
								ID14++;
								num12 = num12 - 2;
								num14++;
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
						//上を見る（１×２）または（２×２）があったら合体
						if(block[x-1][y][z].flag == 2 && block[x-1][y+1][z].flag == 2)
						{
							ID22++;
							num12 = num12 - 2;
							num22++;
							for(int i(0); i<2; i++)
							{
								for(int k(0); k<2; k++)
								{
									block[x-i][y+k][z].flag = 22;
									block[x-i][y+k][z].ID = ID22;
								}
							}
							block[x-1][y][z].corner = 1;
							block[x][y+1][z].corner = 2;
							continue;
						}
						else if(block[x-1][y][z].flag == 4)
						{
							ID23++;
							num12--;
							num22--;
							num23++;
							for(int i(0); i<3; i++)
							{
								for(int k(0); k<2; k++)
								{
									block[x-i][y+k][z].flag = 23;
									block[x-i][y+k][z].ID = ID23;
								}
							}
							block[x-2][y][z].corner = 1;
							block[x][y+1][z].corner = 2;
							continue;
						}
					}
					//左                                                                                                                                  
					else if(block[x][y][z].flag == 2 && block[x+1][y][z].flag == 2)
					{
						//下を見る（1×２）があったら１×４にする
						if(block[x+2][y][z].flag == 2)
						{
							if(block[x+3][y][z].flag == 2)
							{
								ID14++;
								num12 = num12 - 2;
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
						//左を見る（１×２）または（２×２）があったら合体
						if(block[x][y-1][z].flag == 2 && block[x+1][y-1][z].flag == 2)
						{
							ID22++;
							num12 = num12 - 2;
							num22++;
							for(int i(0); i<2; i++)
							{
								for(int k(0); k<2; k++)
								{
									block[x+i][y-k][z].flag = 22;
									block[x+i][y-k][z].ID = ID22;
								}
							}
							block[x][y-1][z].corner = 1;
							block[x+1][y][z].corner = 2;
							continue;
						}
						else if(block[x][y-1][z].flag == 4)
						{
							ID23++;
							num12--;
							num22--;
							num23++;
							for(int i(0); i<2; i++)
							{
								for(int k(0); k<3; k++)
								{
									block[x+i][y-k][z].flag = 23;
									block[x+i][y-k][z].ID = ID23;
								}
							}
							block[x][y-2][z].corner = 1;
							block[x+1][y][z].corner = 2;
							continue;
						}

					}
					//下                                                                                                                                                           
					else if(block[x+1][y][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						//右を見る（1×２）があったら１×４にする
						if(block[x+1][y+2][z].flag == 2 )
						{
							if(block[x+1][y+3][z].flag == 2)
							{
								ID14++;
								num12 = num12 - 2;
								num14++;
								for(int i(0); i<4; i++)
								{
									block[x+1][y+i][z].flag = 14;
									block[x+1][y+i][z].ID = ID14;
								}
								block[x+1][y][z].corner = 1;
								block[x+1][y+3][z].corner = 2;
								continue;
							}
						}
						//下を見る（１×２）または（２×２）があったら合体
						if(block[x+2][y][z].flag == 2 && block[x+2][y+1][z].flag == 2)
						{
							ID22++;
							num12 = num12 - 2;
							num22++;
							for(int i(0); i<2; i++)
							{
								for(int k(0); k<2; k++)
								{
									block[x+i+1][y+k][z].flag = 22;
									block[x+i+1][y+k][z].ID = ID22;
								}
							}
							block[x+1][y][z].corner = 1;
							block[x+2][y+1][z].corner = 2;
							continue;
						}
						else if(block[x+2][y][z].flag == 4)
						{
							ID23++;
							num12--;
							num22--;
							num23++;
							for(int i(0); i<3; i++)
							{
								for(int k(0); k<2; k++)
								{
									block[x+i+1][y+k][z].flag = 23;
									block[x+i+1][y+k][z].ID = ID23;
								}
							}
							block[x+1][y][z].corner = 1;
							block[x+3][y+1][z].corner = 2;
							continue;
						}
					}
					//右                                                                                                                                                           
					else if(block[x][y+1][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						//下を見る（1×２）があったら１×４にする
						if(block[x+2][y+1][z].flag == 2 )
						{
							if(block[x+3][y+1][z].flag == 2)
							{
								ID14++;
								num12 = num12 - 2;
								num14++;
								for(int i(0); i<4; i++)
								{
									block[x+i][y+1][z].flag = 14;
									block[x+i][y+1][z].ID = ID14;
								}
								block[x][y+1][z].corner = 1;
								block[x+3][y+1][z].corner = 2;
								continue;
							}
						}
						//右を見る（１×２）または（２×２）があったら合体
						if(block[x][y+2][z].flag == 2 && block[x+1][y+2][z].flag == 2)
						{
							ID22++;
							num12 = num12 - 2;
							num22++;
							for(int i(0); i<2; i++)
							{
								for(int k(0); k<2; k++)
								{
									block[x+i][y+k+1][z].flag = 22;
									block[x+i][y+k+1][z].ID = ID22;
								}
							}
							block[x][y+1][z].corner = 1;
							block[x+1][y+2][z].corner = 2;
							continue;
						}
						else if(block[x][y+2][z].flag == 4)
						{
							ID23++;
							num12--;
							num22--;
							num23++;
							for(int i(0); i<2; i++)
							{
								for(int k(0); k<3; k++)
								{
									block[x+i][y+k+1][z].flag = 23;
									block[x+i][y+k+1][z].ID = ID23;
								}
							}
							block[x][y+1][z].corner = 1;
							block[x+1][y+3][z].corner = 2;
							continue;
						}
					}

				}
			}
		}
	}


	outputFlag("test04_12_22_to_14_22_23.txt", VoxSize);

}


void Small_to_Big_step4_color(Lego*** block, int*  VoxSize)
{
	int x,y,z;
	for(z=1; z < VoxSize[2]-1; z++ )
	{
		//奇数層
		if(z%2)
		{
			for(x=1; x < VoxSize[0]-1; x=x+2)
			{
				for(y=1; y < VoxSize[1]-1; y=y+2)
				{
					//上                                                                                                                                    
					if(block[x][y][z].flag == 2 && block[x][y+1][z].flag == 2)
					{
						//右を見る（1×２）があったら１×４にする
						if(block[x][y+2][z].flag == 2)
						{
							if(block[x][y+3][z].flag == 2)
							{
								if(block[x][y][z].ColorID == block[x][y+2][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y+2][z].ColorID < 1)
								{
									ID14++;
									num12 = num12 - 2;
									num14++;
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
						//上を見る（１×２）または（２×２）があったら合体
						if(block[x-1][y][z].flag == 2 && block[x-1][y+1][z].flag == 2)
						{
							if(block[x][y][z].ColorID == block[x-1][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x-1][y][z].ColorID < 1)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y+k][z].flag = 22;
										block[x-i][y+k][z].ID = ID22;
									}
								}
								block[x-1][y][z].corner = 1;
								block[x][y+1][z].corner = 2;
								continue;
							}
						}
						else if(block[x-1][y][z].flag == 4)
						{
							if(block[x][y][z].ColorID == block[x-1][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x-1][y][z].ColorID < 1)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								for(int i(0); i<3; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y+k][z].flag = 23;
										block[x-i][y+k][z].ID = ID23;
									}
								}
								block[x-2][y][z].corner = 1;
								block[x][y+1][z].corner = 2;
								continue;
							}
						}
					}
					//左                                                                                                                                  
					else if(block[x][y][z].flag == 2 && block[x+1][y][z].flag == 2)
					{
						//下を見る（1×２）があったら１×４にする
						if(block[x+2][y][z].flag == 2)
						{
							if(block[x+3][y][z].flag == 2)
							{
								if(block[x][y][z].ColorID == block[x+2][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x+2][y][z].ColorID < 1)
								{
									ID14++;
									num12 = num12 - 2;
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
						//左を見る（１×２）または（２×２）があったら合体
						if(block[x][y-1][z].flag == 2 && block[x+1][y-1][z].flag == 2)
						{
							if(block[x][y][z].ColorID == block[x][y-1][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y-1][z].ColorID < 1)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y-k][z].flag = 22;
										block[x+i][y-k][z].ID = ID22;
									}
								}
								block[x][y-1][z].corner = 1;
								block[x+1][y][z].corner = 2;
								continue;
							}
						}
						else if(block[x][y-1][z].flag == 4)
						{
							if(block[x][y][z].ColorID == block[x][y-1][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y-1][z].ColorID < 1)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<3; k++)
									{
										block[x+i][y-k][z].flag = 23;
										block[x+i][y-k][z].ID = ID23;
									}
								}
								block[x][y-2][z].corner = 1;
								block[x+1][y][z].corner = 2;
								continue;
							}
						}

					}
					//下                                                                                                                                                           
					else if(block[x+1][y][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						//右を見る（1×２）があったら１×４にする
						if(block[x+1][y+2][z].flag == 2 )
						{
							if(block[x+1][y+3][z].flag == 2)
							{
								if(block[x+1][y][z].ColorID == block[x+1][y+2][z].ColorID || block[x+1][y][z].ColorID < 1 || block[x+1][y+2][z].ColorID < 1)
								{
									ID14++;
									num12 = num12 - 2;
									num14++;
									for(int i(0); i<4; i++)
									{
										block[x+1][y+i][z].flag = 14;
										block[x+1][y+i][z].ID = ID14;
									}
									block[x+1][y][z].corner = 1;
									block[x+1][y+3][z].corner = 2;
									continue;
								}
							}
						}
						//下を見る（１×２）または（２×２）があったら合体
						if(block[x+2][y][z].flag == 2 && block[x+2][y+1][z].flag == 2)
						{
							if(block[x+1][y][z].ColorID == block[x+2][y][z].ColorID || block[x+1][y][z].ColorID < 1 || block[x+2][y][z].ColorID < 1)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y+k][z].flag = 22;
										block[x+i+1][y+k][z].ID = ID22;
									}
								}
								block[x+1][y][z].corner = 1;
								block[x+2][y+1][z].corner = 2;
								continue;
							}
						}
						else if(block[x+2][y][z].flag == 4)
						{
							if(block[x+1][y][z].ColorID == block[x+2][y][z].ColorID || block[x+1][y][z].ColorID < 1 || block[x+2][y][z].ColorID < 1)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								for(int i(0); i<3; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y+k][z].flag = 23;
										block[x+i+1][y+k][z].ID = ID23;
									}
								}
								block[x+1][y][z].corner = 1;
								block[x+3][y+1][z].corner = 2;
								continue;
							}
						}
					}
					//右                                                                                                                                                           
					else if(block[x][y+1][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						//下を見る（1×２）があったら１×４にする
						if(block[x+2][y+1][z].flag == 2)
						{
							if(block[x+3][y+1][z].flag == 2)
							{
								if(block[x][y+1][z].ColorID == block[x+2][y+1][z].ColorID || block[x][y+1][z].ColorID < 1 || block[x+2][y+1][z].ColorID < 1)
								{
									ID14++;
									num12 = num12 - 2;
									num14++;
									for(int i(0); i<4; i++)
									{
										block[x+i][y+1][z].flag = 14;
										block[x+i][y+1][z].ID = ID14;
									}
									block[x][y+1][z].corner = 1;
									block[x+3][y+1][z].corner = 2;
									continue;
								}
							}
						}
						//右を見る（１×２）または（２×２）があったら合体
						if(block[x][y+2][z].flag == 2 && block[x+1][y+2][z].flag == 2)
						{
							if(block[x][y+1][z].ColorID == block[x][y+2][z].ColorID || block[x][y+1][z].ColorID < 1 || block[x][y+2][z].ColorID < 1)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k+1][z].flag = 22;
										block[x+i][y+k+1][z].ID = ID22;
									}
								}
								block[x][y+1][z].corner = 1;
								block[x+1][y+2][z].corner = 2;
								continue;
							}
						}
						else if(block[x][y+2][z].flag == 4)
						{
							if(block[x][y+1][z].ColorID == block[x][y+2][z].ColorID || block[x][y+1][z].ColorID < 1 || block[x][y+2][z].ColorID < 1)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<3; k++)
									{
										block[x+i][y+k+1][z].flag = 23;
										block[x+i][y+k+1][z].ID = ID23;
									}
								}
								block[x][y+1][z].corner = 1;
								block[x+1][y+3][z].corner = 2;
								continue;
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
					//上                                                                                                                                    
					if(block[x][y][z].flag == 2 && block[x][y+1][z].flag == 2)
					{
						//右を見る（1×２）があったら１×４にする
						if(block[x][y+2][z].flag == 2)
						{
							if(block[x][y+3][z].flag == 2)
							{
								if(block[x][y][z].ColorID == block[x][y+2][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y+2][z].ColorID < 1)
								{
									ID14++;
									num12 = num12 - 2;
									num14++;
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
						//上を見る（１×２）または（２×２）があったら合体
						if(block[x-1][y][z].flag == 2 && block[x-1][y+1][z].flag == 2)
						{
							if(block[x][y][z].ColorID == block[x-1][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x-1][y][z].ColorID < 1)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y+k][z].flag = 22;
										block[x-i][y+k][z].ID = ID22;
									}
								}
								block[x-1][y][z].corner = 1;
								block[x][y+1][z].corner = 2;
								continue;
							}
						}
						else if(block[x-1][y][z].flag == 4)
						{
							if(block[x][y][z].ColorID == block[x-1][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x-1][y][z].ColorID < 1)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								for(int i(0); i<3; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y+k][z].flag = 23;
										block[x-i][y+k][z].ID = ID23;
									}
								}
								block[x-2][y][z].corner = 1;
								block[x][y+1][z].corner = 2;
								continue;
							}
						}
					}
					//左                                                                                                                                  
					else if(block[x][y][z].flag == 2 && block[x+1][y][z].flag == 2)
					{
						//下を見る（1×２）があったら１×４にする
						if(block[x+2][y][z].flag == 2)
						{
							if(block[x+3][y][z].flag == 2)
							{
								if(block[x][y][z].ColorID == block[x+2][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x+2][y][z].ColorID < 1)
								{
									ID14++;
									num12 = num12 - 2;
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
						//左を見る（１×２）または（２×２）があったら合体
						if(block[x][y-1][z].flag == 2 && block[x+1][y-1][z].flag == 2)
						{
							if(block[x][y][z].ColorID == block[x][y-1][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y-1][z].ColorID < 1)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y-k][z].flag = 22;
										block[x+i][y-k][z].ID = ID22;
									}
								}
								block[x][y-1][z].corner = 1;
								block[x+1][y][z].corner = 2;
								continue;
							}
						}
						else if(block[x][y-1][z].flag == 4)
						{
							if(block[x][y][z].ColorID == block[x][y-1][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y-1][z].ColorID < 1)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<3; k++)
									{
										block[x+i][y-k][z].flag = 23;
										block[x+i][y-k][z].ID = ID23;
									}
								}
								block[x][y-2][z].corner = 1;
								block[x+1][y][z].corner = 2;
								continue;
							}
						}

					}
					//下                                                                                                                                                           
					else if(block[x+1][y][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						//右を見る（1×２）があったら１×４にする
						if(block[x+1][y+2][z].flag == 2 )
						{
							if(block[x+1][y+3][z].flag == 2)
							{
								if(block[x+1][y][z].ColorID == block[x+1][y+2][z].ColorID || block[x+1][y][z].ColorID < 1 || block[x+1][y+2][z].ColorID < 1)
								{
									ID14++;
									num12 = num12 - 2;
									num14++;
									for(int i(0); i<4; i++)
									{
										block[x+1][y+i][z].flag = 14;
										block[x+1][y+i][z].ID = ID14;
									}
									block[x+1][y][z].corner = 1;
									block[x+1][y+3][z].corner = 2;
									continue;
								}
							}
						}
						//下を見る（１×２）または（２×２）があったら合体
						if(block[x+2][y][z].flag == 2 && block[x+2][y+1][z].flag == 2)
						{
							if(block[x+1][y][z].ColorID == block[x+2][y][z].ColorID || block[x+1][y][z].ColorID < 1 || block[x+2][y][z].ColorID < 1)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y+k][z].flag = 22;
										block[x+i+1][y+k][z].ID = ID22;
									}
								}
								block[x+1][y][z].corner = 1;
								block[x+2][y+1][z].corner = 2;
								continue;
							}
						}
						else if(block[x+2][y][z].flag == 4)
						{
							if(block[x+1][y][z].ColorID == block[x+2][y][z].ColorID || block[x+1][y][z].ColorID < 1 || block[x+2][y][z].ColorID < 1)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								for(int i(0); i<3; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y+k][z].flag = 23;
										block[x+i+1][y+k][z].ID = ID23;
									}
								}
								block[x+1][y][z].corner = 1;
								block[x+3][y+1][z].corner = 2;
								continue;
							}
						}
					}
					//右                                                                                                                                                           
					else if(block[x][y+1][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						//下を見る（1×２）があったら１×４にする
						if(block[x+2][y+1][z].flag == 2)
						{
							if(block[x+3][y+1][z].flag == 2)
							{
								if(block[x][y+1][z].ColorID == block[x+2][y+1][z].ColorID || block[x][y+1][z].ColorID < 1 || block[x+2][y+1][z].ColorID < 1)
								{
									ID14++;
									num12 = num12 - 2;
									num14++;
									for(int i(0); i<4; i++)
									{
										block[x+i][y+1][z].flag = 14;
										block[x+i][y+1][z].ID = ID14;
									}
									block[x][y+1][z].corner = 1;
									block[x+3][y+1][z].corner = 2;
									continue;
								}
							}
						}
						//右を見る（１×２）または（２×２）があったら合体
						if(block[x][y+2][z].flag == 2 && block[x+1][y+2][z].flag == 2)
						{
							if(block[x][y+1][z].ColorID == block[x][y+2][z].ColorID || block[x][y+1][z].ColorID < 1 || block[x][y+2][z].ColorID < 1)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k+1][z].flag = 22;
										block[x+i][y+k+1][z].ID = ID22;
									}
								}
								block[x][y+1][z].corner = 1;
								block[x+1][y+2][z].corner = 2;
								continue;
							}
						}
						else if(block[x][y+2][z].flag == 4)
						{
							if(block[x][y+1][z].ColorID == block[x][y+2][z].ColorID || block[x][y+1][z].ColorID < 1 || block[x][y+2][z].ColorID < 1)
							{
								ID23++;
								num12--;
								num22--;
								num23++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<3; k++)
									{
										block[x+i][y+k+1][z].flag = 23;
										block[x+i][y+k+1][z].ID = ID23;
									}
								}
								block[x][y+1][z].corner = 1;
								block[x+1][y+3][z].corner = 2;
								continue;
							}
						}
					}

				}
			}
		}
	}


	outputFlag("test04_12_22_to_14_22_23.txt", VoxSize);

}


//１×２の上下を見て最大でも１×１しかない場合は優先的にほかのブロックとくっつける
void Small_to_Big_before_step4(Lego*** block, int*  VoxSize)
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
					//上
					if(block[x][y][z].flag == 2 && block[x][y+1][z].flag == 2)
					{
						if(block[x][y][z-1].flag < 2 && block[x][y+1][z-1].flag < 2 && block[x][y][z+1].flag < 2 && block[x][y+1][z+1].flag < 2)
						{
							//右を見る（1×２）があったら１×４にする
							if(block[x][y+2][z].flag == 2)
							{
								if(block[x][y+3][z].flag == 2)
								{
									//上下を見て最低でも1つのフラグが２以上であれば
									if(block[x][y+2][z-1].flag  > 1  || block[x][y+3][z-1].flag  > 1  || block[x][y+2][z+1].flag > 1 || block[x][y+3][z+1].flag > 1)
									{
										ID14++;
										num12 = num12 - 2;
										num14++;
										count++;
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
							//上を見る（１×２）または（２×２）があったら合体
							if(block[x-1][y][z].flag == 2 && block[x-1][y+1][z].flag == 2)
							{
								//上下を見て最低でも1つのフラグが２以上であれば
								if(block[x-1][y][z-1].flag  > 1  || block[x-1][y+1][z-1].flag  > 1  || block[x-1][y][z+1].flag  > 1  || block[x-1][y+1][z+1].flag  > 1)
								{
									ID22++;
									num12 = num12 - 2;
									num22++;
									count++;
									for(int i(0); i<2; i++)
									{
										for(int k(0); k<2; k++)
										{
											block[x-i][y+k][z].flag = 22;
											block[x-i][y+k][z].ID = ID22;
										}
									}
									block[x-1][y][z].corner = 1;
									block[x][y+1][z].corner = 2;
									continue;
								}
							}
							else if(block[x-1][y][z].flag == 4)
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
										block[x-i][y+k][z].flag = 23;
										block[x-i][y+k][z].ID = ID23;
									}
								}
								block[x-2][y][z].corner = 1;
								block[x][y+1][z].corner = 2;
								continue;
							}
						}
					}
					//左
					else if(block[x][y][z].flag == 2 && block[x+1][y][z].flag == 2)
					{
						if(block[x][y][z-1].flag < 2 && block[x+1][y][z-1].flag < 2 && block[x][y][z+1].flag < 2 && block[x+1][y][z+1].flag < 2)
						{
							//下を見る（1×２）があったら１×４にする
							if(block[x+2][y][z].flag == 2 )
							{
								if(block[x+3][y][z].flag == 2)
								{
									if(block[x+2][y][z-1].flag > 1 || block[x+3][y][z-1].flag > 1 || block[x+2][y][z+1].flag > 1 || block[x+3][y][z+1].flag > 1)
									{
										ID14++;
										num12 = num12 - 2;
										num14++;
										count++;
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
							//左を見る（１×２）または（２×２）があったら合体
							if(block[x][y-1][z].flag == 2 && block[x+1][y-1][z].flag == 2)
							{
								if(block[x][y-1][z-1].flag > 1 || block[x+1][y-1][z-1].flag > 1 || block[x][y-1][z+1].flag > 1 || block[x+1][y-1][z+1].flag > 1 )
								{
									ID22++;
									num12 = num12 - 2;
									num22++;
									count++;
									for(int i(0); i<2; i++)
									{
										for(int k(0); k<2; k++)
										{
											block[x+i][y-k][z].flag = 22;
											block[x+i][y-k][z].ID = ID22;
										}
									}
									block[x][y-1][z].corner = 1;
									block[x+1][y][z].corner = 2;
									continue;
								}
							}
							else if(block[x][y-1][z].flag == 4)
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
										block[x+i][y-k][z].flag = 23;
										block[x+i][y-k][z].ID = ID23;
									}
								}
								block[x][y-2][z].corner = 1;
								block[x+1][y][z].corner = 2;
								continue;
							}
						}
					}
					//下
					else if(block[x+1][y][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						if(block[x+1][y][z-1].flag < 2 && block[x+1][y+1][z-1].flag < 2 && block[x+1][y][z+1].flag < 2 && block[x+1][y+1][z+1].flag < 2)
						{
							//右を見る（1×２）があったら１×４にする
							if(block[x+1][y+2][z].flag == 2)
							{
								if(block[x+1][y+3][z].flag == 2)
								{
									if(block[x+1][y+2][z-1].flag > 1 ||  block[x+1][y+3][z-1].flag > 1 || block[x+1][y+2][z+1].flag > 1 ||  block[x+1][y+3][z+1].flag > 1)
									{
										ID14++;
										num12 = num12 - 2;
										num14++;
										count++;
										for(int i(0); i<4; i++)
										{
											block[x+1][y+i][z].flag = 14;
											block[x+1][y+i][z].ID = ID14;
										}
										block[x+1][y][z].corner = 1;
										block[x+1][y+3][z].corner = 2;
										continue;
									}
								}
							}
							//下を見る（１×２）または（２×２）があったら合体
							if(block[x+2][y][z].flag == 2 && block[x+2][y+1][z].flag == 2)
							{
								if(block[x+2][y][z-1].flag > 1 || block[x+2][y+1][z-1].flag > 1 || block[x+2][y][z+1].flag > 1 || block[x+2][y+1][z+1].flag > 1 )
								{
									ID22++;
									num12 = num12 - 2;
									num22++;
									count++;
									for(int i(0); i<2; i++)
									{
										for(int k(0); k<2; k++)
										{
											block[x+i+1][y+k][z].flag = 22;
											block[x+i+1][y+k][z].ID = ID22;
										}
									}
									block[x+1][y][z].corner = 1;
									block[x+2][y+1][z].corner = 2;
									continue;
								}
							}
							else if(block[x+2][y][z].flag == 4)
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
										block[x+i+1][y+k][z].flag = 23;
										block[x+i+1][y+k][z].ID = ID23;
									}
								}
								block[x+1][y][z].corner = 1;
								block[x+3][y+1][z].corner = 2;
								continue;
							}
						}
					}
					//右
					else if(block[x][y+1][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						if(block[x][y+1][z-1].flag < 2 && block[x+1][y+1][z-1].flag < 2 && block[x][y+1][z+1].flag < 2 && block[x+1][y+1][z+1].flag < 2)
						{
							//下を見る（1×２）があったら１×４にする
							if(block[x+2][y+1][z].flag == 2)
							{
								if(block[x+3][y+1][z].flag == 2)
								{
									if(block[x+2][y+1][z-1].flag > 1 || block[x+3][y+1][z-1].flag > 1 || block[x+2][y+1][z+1].flag > 1 || block[x+3][y+1][z+1].flag > 1 )
									{
										ID14++;
										num12 = num12 - 2;
										num14++;
										count++;
										for(int i(0); i<4; i++)
										{
											block[x+i][y+1][z].flag = 14;
											block[x+i][y+1][z].ID = ID14;
										}
										block[x][y+1][z].corner = 1;
										block[x+3][y+1][z].corner = 2;
										continue;
									}
								}
							}
							//右を見る（１×２）または（２×２）があったら合体
							if(block[x][y+2][z].flag == 2 && block[x+1][y+2][z].flag == 2)
							{
								if(block[x][y+2][z-1].flag > 1 || block[x+1][y+2][z-1].flag > 1 || block[x][y+2][z+1].flag > 1 || block[x+1][y+2][z+1].flag > 1 )
								{
									ID22++;
									num12 = num12 - 2;
									num22++;
									count++;
									for(int i(0); i<2; i++)
									{
										for(int k(0); k<2; k++)
										{
											block[x+i][y+k+1][z].flag = 22;
											block[x+i][y+k+1][z].ID = ID22;
										}
									}
									block[x][y+1][z].corner = 1;
									block[x+1][y+2][z].corner = 2;
									continue;
								}
							}
							else if(block[x][y+2][z].flag == 4)
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
										block[x+i][y+k+1][z].flag = 23;
										block[x+i][y+k+1][z].ID = ID23;
									}
								}
								block[x][y+1][z].corner = 1;
								block[x+1][y+3][z].corner = 2;
								continue;
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
					//上
					if(block[x][y][z].flag == 2 && block[x][y+1][z].flag == 2)
					{
						if(block[x][y][z-1].flag < 2 && block[x][y+1][z-1].flag < 2 && block[x][y][z+1].flag < 2 && block[x][y+1][z+1].flag < 2)
						{
							//右を見る（1×２）があったら１×４にする
							if(block[x][y+2][z].flag == 2 )
							{
								if(block[x][y+3][z].flag == 2)
								{
									//上下を見て最低でも1つのフラグが２以上であれば
									if(block[x][y+2][z-1].flag  > 1  || block[x][y+3][z-1].flag  > 1  || block[x][y+2][z+1].flag > 1 || block[x][y+3][z+1].flag > 1)
									{
										ID14++;
										num12 = num12 - 2;
										num14++;
										count++;
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
							//上を見る（１×２）または（２×２）があったら合体
							if(block[x-1][y][z].flag == 2 && block[x-1][y+1][z].flag == 2)
							{
								//上下を見て最低でも1つのフラグが２以上であれば
								if(block[x-1][y][z-1].flag  > 1  || block[x-1][y+1][z-1].flag  > 1  || block[x-1][y][z+1].flag  > 1  || block[x-1][y+1][z+1].flag  > 1)
								{
									ID22++;
									num12 = num12 - 2;
									num22++;
									count++;
									for(int i(0); i<2; i++)
									{
										for(int k(0); k<2; k++)
										{
											block[x-i][y+k][z].flag = 22;
											block[x-i][y+k][z].ID = ID22;
										}
									}
									block[x-1][y][z].corner = 1;
									block[x][y+1][z].corner = 2;
									continue;
								}
							}
							else if(block[x-1][y][z].flag == 4)
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
										block[x-i][y+k][z].flag = 23;
										block[x-i][y+k][z].ID = ID23;
									}
								}
								block[x-2][y][z].corner = 1;
								block[x][y+1][z].corner = 2;
								continue;
							}
						}
					}
					//左
					else if(block[x][y][z].flag == 2 && block[x+1][y][z].flag == 2)
					{
						if(block[x][y][z-1].flag < 2 && block[x+1][y][z-1].flag < 2 && block[x][y][z+1].flag < 2 && block[x+1][y][z+1].flag < 2)
						{
							//下を見る（1×２）があったら１×４にする
							if(block[x+2][y][z].flag == 2 )
							{
								if(block[x+3][y][z].flag == 2)
								{
									if(block[x+2][y][z-1].flag > 1 || block[x+3][y][z-1].flag > 1 || block[x+2][y][z+1].flag > 1 || block[x+3][y][z+1].flag > 1)
									{
										ID14++;
										num12 = num12 - 2;
										num14++;
										count++;
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
							//左を見る（１×２）または（２×２）があったら合体
							if(block[x][y-1][z].flag == 2 && block[x+1][y-1][z].flag == 2)
							{
								if(block[x][y-1][z-1].flag > 1 || block[x+1][y-1][z-1].flag > 1 || block[x][y-1][z+1].flag > 1 || block[x+1][y-1][z+1].flag > 1 )
								{
									ID22++;
									num12 = num12 - 2;
									num22++;
									count++;
									for(int i(0); i<2; i++)
									{
										for(int k(0); k<2; k++)
										{
											block[x+i][y-k][z].flag = 22;
											block[x+i][y-k][z].ID = ID22;
										}
									}
									block[x][y-1][z].corner = 1;
									block[x+1][y][z].corner = 2;
									continue;
								}
							}
							else if(block[x][y-1][z].flag == 4)
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
										block[x+i][y-k][z].flag = 23;
										block[x+i][y-k][z].ID = ID23;
									}
								}
								block[x][y-2][z].corner = 1;
								block[x+1][y][z].corner = 2;
								continue;
							}
						}
					}
					//下
					else if(block[x+1][y][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						if(block[x+1][y][z-1].flag < 2 && block[x+1][y+1][z-1].flag < 2 && block[x+1][y][z+1].flag < 2 && block[x+1][y+1][z+1].flag < 2)
						{
							//右を見る（1×２）があったら１×４にする
							if(block[x+1][y+2][z].flag == 2)
							{
								if(block[x+1][y+3][z].flag == 2)
								{
									if(block[x+1][y+2][z-1].flag > 1 ||  block[x+1][y+3][z-1].flag > 1 || block[x+1][y+2][z+1].flag > 1 ||  block[x+1][y+3][z+1].flag > 1)
									{
										ID14++;
										num12 = num12 - 2;
										num14++;
										count++;
										for(int i(0); i<4; i++)
										{
											block[x+1][y+i][z].flag = 14;
											block[x+1][y+i][z].ID = ID14;
										}
										block[x+1][y][z].corner = 1;
										block[x+1][y+3][z].corner = 2;
										continue;
									}
								}
							}
							//下を見る（１×２）または（２×２）があったら合体
							if(block[x+2][y][z].flag == 2 && block[x+2][y+1][z].flag == 2)
							{
								if(block[x+2][y][z-1].flag > 1 || block[x+2][y+1][z-1].flag > 1 || block[x+2][y][z+1].flag > 1 || block[x+2][y+1][z+1].flag > 1 )
								{
									ID22++;
									num12 = num12 - 2;
									num22++;
									count++;
									for(int i(0); i<2; i++)
									{
										for(int k(0); k<2; k++)
										{
											block[x+i+1][y+k][z].flag = 22;
											block[x+i+1][y+k][z].ID = ID22;
										}
									}
									block[x+1][y][z].corner = 1;
									block[x+2][y+1][z].corner = 2;
									continue;
								}
							}
							else if(block[x+2][y][z].flag == 4)
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
										block[x+i+1][y+k][z].flag = 23;
										block[x+i+1][y+k][z].ID = ID23;
									}
								}
								block[x+1][y][z].corner = 1;
								block[x+3][y+1][z].corner = 2;
								continue;
							}
						}
					}
					//右
					else if(block[x][y+1][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						if(block[x][y+1][z-1].flag < 2 && block[x+1][y+1][z-1].flag < 2 && block[x][y+1][z+1].flag < 2 && block[x+1][y+1][z+1].flag < 2)
						{
							//下を見る（1×２）があったら１×４にする
							if(block[x+2][y+1][z].flag == 2)
							{
								if(block[x+3][y+1][z].flag == 2)
								{
									if(block[x+2][y+1][z-1].flag > 1 || block[x+3][y+1][z-1].flag > 1 || block[x+2][y+1][z+1].flag > 1 || block[x+3][y+1][z+1].flag > 1 )
									{
										ID14++;
										num12 = num12 - 2;
										num14++;
										count++;
										for(int i(0); i<4; i++)
										{
											block[x+i][y+1][z].flag = 14;
											block[x+i][y+1][z].ID = ID14;
										}
										block[x][y+1][z].corner = 1;
										block[x+3][y+1][z].corner = 2;
										continue;
									}
								}
							}
							//右を見る（１×２）または（２×２）があったら合体
							if(block[x][y+2][z].flag == 2 && block[x+1][y+2][z].flag == 2)
							{
								if(block[x][y+2][z-1].flag > 1 || block[x+1][y+2][z-1].flag > 1 || block[x][y+2][z+1].flag > 1 || block[x+1][y+2][z+1].flag > 1 )
								{
									ID22++;
									num12 = num12 - 2;
									num22++;
									count++;
									for(int i(0); i<2; i++)
									{
										for(int k(0); k<2; k++)
										{
											block[x+i][y+k+1][z].flag = 22;
											block[x+i][y+k+1][z].ID = ID22;
										}
									}
									block[x][y+1][z].corner = 1;
									block[x+1][y+2][z].corner = 2;
									continue;
								}
							}
							else if(block[x][y+2][z].flag == 4)
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
										block[x+i][y+k+1][z].flag = 23;
										block[x+i][y+k+1][z].ID = ID23;
									}
								}
								block[x][y+1][z].corner = 1;
								block[x+1][y+3][z].corner = 2;
								continue;
							}

						}
					}
				}
			}
		}//else(偶数層)

	}	//for(z)

	cout<<count << "個の孤立しそうな１×２が優先合成された！ "<<endl;

	//outputFlag("test04_12_22_to_14_22_23_before.txt", VoxSize);

}