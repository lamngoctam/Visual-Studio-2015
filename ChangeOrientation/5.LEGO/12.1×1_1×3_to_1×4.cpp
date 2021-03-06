#include "../stdafx.h"
#include "../Voxel.h"
#include "../Lego.h"		//LEGOブロックを組み立てるためのクラス

extern int ID14;
extern int ID13;

extern int num11;		//１×１のブロックの数
extern int num12;		//１×2のブロックの数
extern int num13;		//１×３のブロックの数
extern int num14;		//１×４のブロックの数

void outputFlag(string filename, int* size);

//１×１の４方向に　１×3　があったら　結合させる
void Small_to_Big_step2(Lego*** block, int* VoxSize)
{
	int count(0);
	//1×1の４方向を見て　
	for(int z(1); z < VoxSize[2]-1; z++ )
	{
		for(int x(1); x < VoxSize[0]-1; x++)
		{
			for(int y(1); y < VoxSize[1]-1; y++)
			{
				//表面ブロックかつブロックのIDが１（１×１）の場合
				if(block[x][y][z].flag == 1)
				{
					//１×3がある場合
					//ｙ軸の進行方向
					if(y+3<VoxSize[1]-1)
					{
						if(block[x][y+1][z].flag == 13 && block[x][y+2][z].flag == 13 && block[x][y+3][z].flag == 13)		
						{
							count++;
							ID14++;
							num11--;
							num13--;
							num14++;
							//１×４へと変換する
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
						if(block[x+1][y][z].flag == 13 && block[x+2][y][z].flag == 13 && block[x+3][y][z].flag == 13)		//ｘ軸の進行方向
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
						if(block[x][y-1][z].flag == 13 && block[x][y-2][z].flag == 13 && block[x][y-3][z].flag == 13 )			//ｙ軸の進行逆方向
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
						if(block[x-1][y][z].flag == 13 && block[x-2][y][z].flag == 13 && block[x-3][y][z].flag == 13)			//ｘ軸の進行逆方向
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

	cout<<count<<"個の１×４が　１×１　と　１×３から生成された！"<<endl;
	outputFlag("test02_11_13_to_14.txt", VoxSize);

}


void Small_to_Big_step2_color(Lego*** block, int* VoxSize)
{
	int count(0);
	//1×1の４方向を見て　
	for(int z(1); z < VoxSize[2]-1; z++ )
	{
		for(int x(1); x < VoxSize[0]-1; x++)
		{
			for(int y(1); y < VoxSize[1]-1; y++)
			{
				//表面ブロックかつブロックのIDが１（１×１）の場合
				if(block[x][y][z].flag == 1)
				{
					//１×3がある場合
					//ｙ軸の進行方向
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
								//１×3へと変換する
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
						if(block[x+1][y][z].flag == 13 && block[x+2][y][z].flag == 13 && block[x+3][y][z].flag == 13)		//ｘ軸の進行方向
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
						if(block[x][y-1][z].flag == 13 && block[x][y-2][z].flag == 13 && block[x][y-3][z].flag == 13 )			//ｙ軸の進行逆方向
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
						if(block[x-1][y][z].flag == 13 && block[x-2][y][z].flag == 13 && block[x-3][y][z].flag == 13)			//ｘ軸の進行逆方向
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

	cout<<count<<"個の１×４が　１×１　と　１×３から生成された！"<<endl;
	//outputFlag("test02_11_13_to_14.txt", VoxSize);

}

//1×1と1×2を合成
void Small_to_Big_before_before_step2_color(Lego*** block, int* VoxSize)
{
	int count(0);
	//1×1の４方向を見て　
	for(int z(1); z < VoxSize[2]-1; z++ )
	{
		for(int x(1); x < VoxSize[0]-1; x++)
		{
			for(int y(1); y < VoxSize[1]-1; y++)
			{
				//表面ブロックかつブロックのIDが１（１×１）の場合
				if(block[x][y][z].flag == 1)
				{
					//１×3がある場合
					//ｙ軸の進行方向
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
								//１×3へと変換する
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
						if(block[x+1][y][z].flag == 12 && block[x+2][y][z].flag == 12 )		//ｘ軸の進行方向
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
						if(block[x][y-1][z].flag == 12 && block[x][y-2][z].flag == 12  )			//ｙ軸の進行逆方向
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
						if(block[x-1][y][z].flag == 12 && block[x-2][y][z].flag == 12 )			//ｘ軸の進行逆方向
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

	cout<<count<<"個の１×3が　１×１　と　１×３から生成された！"<<endl;
	//outputFlag("test02_11_13_to_14.txt", VoxSize);

}

//1×1と1×2を結合
void Small_to_Big_before_step2_color(Lego*** block, int* VoxSize)
{
	int count(0);
	//1×1の４方向を見て　
	for(int z(1); z < VoxSize[2]-1; z++ )
	{
		for(int x(1); x < VoxSize[0]-1; x++)
		{
			for(int y(1); y < VoxSize[1]-1; y++)
			{
				//表面ブロックかつブロックのIDが１（１×１）の場合
				if(block[x][y][z].flag == 1)
				{
					//１×2がある場合
					//ｙ軸の進行方向
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
								//１×４へと変換する
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
						if(block[x+1][y][z].flag == 2 && block[x+2][y][z].flag == 2 )		//ｘ軸の進行方向
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
						if(block[x][y-1][z].flag == 2 && block[x][y-2][z].flag == 2  )			//ｙ軸の進行逆方向
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
						if(block[x-1][y][z].flag == 2 && block[x-2][y][z].flag == 2 )			//ｘ軸の進行逆方向
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

	cout<<count<<"個の１×3が　１×１　と　１×2から生成された！"<<endl;
	//outputFlag("test02_11_13_to_14.txt", VoxSize);

}