#include "../stdafx.h"
#include "../Voxel.h"
#include "../Lego.h"		//LEGOブロックを組み立てるためのクラス

void outputFlag(string filename, int* size);
void outputID(string filename, int* size);

extern int num11;		//２×２のブロックの数
extern int num12;		//２×２のブロックの数
extern int num22;		//２×２のブロックの数

//１×１の上下を見てブロックがなかったら消す
void Delete_Iso_Blocks_11(Lego*** block, int* VoxSize)
{
	int x,y,z;
	int count(0);
	for(z=1; z<VoxSize[2]-1; z++)
	{
		for(x=1; x<VoxSize[0]-1; x++)
		{
			for(y=1; y<VoxSize[1]-1; y++)
			{
				//１×１の孤立ブロックを消す
				if(block[x][y][z].flag == 1)
				{
					//上下のブロックを見て両方とも何もない場合
					if(block[x][y][z-1].flag < 1 && block[x][y][z+1].flag < 1)
					{
						count++;
						num11--;
						block[x][y][z].Initiaization();
					}
				}
			}
		}
	}
	cout<<count<<"個の１×１が削除された"<<endl;
	//outputFlag("Delete_Blocks_11.txt", VoxSize);
}

//１×２の上下を見てブロックがなかったら消す
void Delete_Iso_Blocks_12(Lego*** block, int* VoxSize)
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
					if(block[x][y][z].flag == 12 && block[x][y+1][z].flag == 12)
					{
						if(block[x][y][z-1].flag < 1 && block[x][y+1][z-1].flag < 1 && block[x][y][z+1].flag < 1 && block[x][y+1][z+1].flag < 1)
						{
							count++;
							num12--;
							block[x][y][z].Initiaization();
							block[x][y+1][z].Initiaization();
							cout<<x<<" "<<y<<" "<<z<<endl;
						}
					}
					//左
					else if(block[x][y][z].flag == 12 && block[x+1][y][z].flag == 12)
					{
						if(block[x][y][z-1].flag < 1 && block[x+1][y][z-1].flag < 1 && block[x][y][z+1].flag < 1 && block[x+1][y][z+1].flag < 1)
						{
							count++;
							num12--;
							block[x][y][z].Initiaization();
							block[x+1][y][z].Initiaization();
							cout<<x<<" "<<y<<" "<<z<<endl;
						}
					}
					//下
					else if(block[x+1][y][z].flag == 12 && block[x+1][y+1][z].flag == 12)
					{
						if(block[x+1][y][z-1].flag < 1 && block[x+1][y+1][z-1].flag < 1 && block[x+1][y][z+1].flag < 1 && block[x+1][y+1][z+1].flag < 1)
						{
							count++;
							num12--;
							block[x+1][y][z].Initiaization();
							block[x+1][y+1][z].Initiaization();
							cout<<x<<" "<<y<<" "<<z<<endl;
						}
					}
					//右
					else if(block[x][y+1][z].flag == 12 && block[x+1][y+1][z].flag == 12)
					{
						if(block[x][y+1][z-1].flag < 1 && block[x+1][y+1][z-1].flag < 1 && block[x][y+1][z+1].flag < 1 && block[x+1][y+1][z+1].flag < 1)
						{
							count++;
							num12--;
							block[x][y+1][z].Initiaization();
							block[x+1][y+1][z].Initiaization();
							cout<<x<<" "<<y<<" "<<z<<endl;
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
					if(block[x][y][z].flag == 12 && block[x][y+1][z].flag == 12)
					{
						if(block[x][y][z-1].flag < 1 && block[x][y+1][z-1].flag < 1 && block[x][y][z+1].flag < 1 && block[x][y+1][z+1].flag < 1)
						{
							count++;
							num12--;
							block[x][y][z].Initiaization();
							block[x][y+1][z].Initiaization();
							cout<<x<<" "<<y<<" "<<z<<endl;
						}
					}
					//左
					else if(block[x][y][z].flag == 12 && block[x+1][y][z].flag == 12)
					{
						if(block[x][y][z-1].flag < 1 && block[x+1][y][z-1].flag < 1 && block[x][y][z+1].flag < 1 && block[x+1][y][z+1].flag < 1)
						{
							count++;
							num12--;
							block[x][y][z].Initiaization();
							block[x+1][y][z].Initiaization();
							cout<<x<<" "<<y<<" "<<z<<endl;
						}
					}
					//下
					else if(block[x+1][y][z].flag == 12 && block[x+1][y+1][z].flag == 12)
					{
						if(block[x+1][y][z-1].flag < 1 && block[x+1][y+1][z-1].flag < 1 && block[x+1][y][z+1].flag < 1 && block[x+1][y+1][z+1].flag < 1)
						{
							count++;
							num12--;
							block[x+1][y][z].Initiaization();
							block[x+1][y+1][z].Initiaization();
							cout<<x<<" "<<y<<" "<<z<<endl;
						}
					}
					//右
					else if(block[x][y+1][z].flag == 12 && block[x+1][y+1][z].flag == 12)
					{
						if(block[x][y+1][z-1].flag < 1 && block[x+1][y+1][z-1].flag < 1 && block[x][y+1][z+1].flag < 1 && block[x+1][y+1][z+1].flag < 1)
						{
							count++;
							num12--;
							block[x][y+1][z].Initiaization();
							block[x+1][y+1][z].Initiaization();
							cout<<x<<" "<<y<<" "<<z<<endl;
						}
					}
				}
			}
		}
	}

	cout<<count<<"個の１×２が削除された！"<<endl;
	//outputFlag("Delete_Blocks_12.txt", VoxSize);

}

//２×２の独立しているボクセルを削除
void Delete_Iso_Blocks_22(Lego*** block, int* VoxSize)
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
					//対角線のボクセルのflagが２２だったら
					if(block[x][y][z].flag == 22 && block[x+1][y+1][z].flag == 22)	
					{
						if(block[x][y][z-1].flag < 1 && block[x][y][z+1].flag < 1)
							if(block[x][y+1][z-1].flag < 1 && block[x][y+1][z+1].flag < 1)
								if(block[x+1][y][z-1].flag < 1 && block[x+1][y][z+1].flag < 1)
									if(block[x+1][y+1][z-1].flag < 1 && block[x+1][y+1][z+1].flag < 1)
									{
										count++;
										num22--;
										for(int i(0); i<2; i++)
											for(int k(0); k<2; k++)
												block[x+i][y+k][z].Initiaization();
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
					//対角線のボクセルのflagが２２だったら
					if(block[x][y][z].flag == 22 && block[x+1][y+1][z].flag == 22)	
					{
						if(block[x][y][z-1].flag < 1 && block[x][y][z+1].flag < 1)
							if(block[x][y+1][z-1].flag < 1 && block[x][y+1][z+1].flag < 1)
								if(block[x+1][y][z-1].flag < 1 && block[x+1][y][z+1].flag < 1)
									if(block[x+1][y+1][z-1].flag < 1 && block[x+1][y+1][z+1].flag < 1)
									{
										count++;
										num22--;
										for(int i(0); i<2; i++)
											for(int k(0); k<2; k++)
												block[x+i][y+k][z].Initiaization();
									}
					}
				}
			}
		}
	}

	cout<<count<<"個の２×２が削除された！"<<endl;
	//outputFlag("Delete_Blocks_22.txt", VoxSize);
}

//孤立しそうなブロック群を消すようにする
//まず、１×２を探す
//その上下のブロックが１×１または何もない場合さらにそれを見ていく
void Delete_Iso_Blocks(Lego*** block, int* VoxSize)
{
	int x,y,z;
	int num(0);

	for(z=1; z < VoxSize[2]-1; z++ )
	{
		for(x=1; x < VoxSize[0]-1; x++)
		{
			for(y=1; y < VoxSize[1]-1; y++)
			{
				if(block[x][y][z].flag == 12)
				{
					//################################
					//ｙ方向の１×２
					//################################
					if(block[x][y+1][z].flag == 12 && block[x][y+1][z].ID == block[x][y][z].ID)
					{
						num = 0;
						//１個目の下を見る
						//if(block[x][y][z-1].flag == 1 && block[x][y][z-2].flag < 1)
						if(block[x][y][z-1].flag == 1)
						{
							if(block[x][y][z-2].flag < 1)
								num++;
						}
						else if(block[x][y][z-1].flag < 1)
							num++;
						else
							continue;
						//１個目の上を見る
						//if(block[x][y][z+1].flag == 1 && block[x][y][z+2].flag < 1)
						if(block[x][y][z+1].flag == 1)
						{
							if(block[x][y][z+2].flag < 1)
								num++;
						}
						else if(block[x][y][z+1].flag < 1)
							num++;
						else
							continue;
						//２個目の下を見る
						//if(block[x][y+1][z-1].flag == 1 && block[x][y+1][z-2].flag < 1)
						if(block[x][y+1][z-1].flag == 1 )
						{
							if(block[x][y+1][z-2].flag < 1)
								num++;
						}
						else if(block[x][y+1][z-1].flag < 1)
							num++;
						else
							continue;
						//２個目の上を見る
						if(block[x][y+1][z+1].flag == 1)
						{
							if(block[x][y+1][z+2].flag < 1)
								num++;
						}
						else if(block[x][y+1][z+1].flag < 1)
							num++;
						else
							continue;

						if(num<4)
							continue;
						for(int i(0); i<2; i++)
						{
							for(int k(0); k<3; k = k + 2)
								if(block[x][y+i][z+k-1].flag == 1)
									num11--;
						}
						num12--;
						//１×２の上下合計６つのボクセルのflagを０にする 用検討！！
						for(int i(0); i<2; i++)
						{
							for(int k(0); k<3; k++)
								block[x][y+i][z+k-1].Initiaization();
						}
						cout<<"ブロックを削除した！："<<x<<" "<<y<<" "<<z<<endl;
					}
					//################################
					//ｘ方向の１×２
					//################################
					else if(block[x+1][y][z].flag == 12 && block[x+1][y][z].ID == block[x][y][z].ID)
					{
						num = 0;
						//１個目の下を見る
						//if(block[x][y][z-1].flag == 1 && block[x][y][z-2].flag < 1)
						if(block[x][y][z-1].flag == 1)
						{
							if(block[x][y][z-2].flag < 1)
								num++;
						}
						else if(block[x][y][z-1].flag < 1)
							num++;
						else
							continue;
						//１個目の上を見る
						//if(block[x][y][z+1].flag == 1 && block[x][y][z+2].flag < 1)
						if(block[x][y][z+1].flag == 1)
						{
							if(block[x][y][z+2].flag < 1)
								num++;
						}
						else if(block[x][y][z+1].flag < 1)
							num++;
						else
							continue;
						//２個目の下を見る
						//if(block[x+1][y][z-1].flag == 1 && block[x+1][y][z-2].flag < 1)
						if(block[x+1][y][z-1].flag == 1)
						{
							if(block[x+1][y][z-2].flag < 1)
								num++;
						}
						else if(block[x+1][y][z-1].flag < 1)
							num++;
						else
							continue;
						//２個目の上を見る
						//if(block[x+1][y][z+1].flag == 1 && block[x+1][y][z+2].flag < 1)
						if(block[x+1][y][z+1].flag == 1 )
						{
							if(block[x+1][y][z+2].flag < 1)
								num++;
						}
						else if(block[x+1][y][z+1].flag < 1)
							num++;
						else
							continue;

						if(num<4)
							continue;

						for(int i(0); i<2; i++)
						{
							for(int k(0); k<3; k = k + 2)
								if(block[x+i][y][z+k-1].flag == 1)
									num11--;
						}
						num12--;

						//１×２の上下合計６つのボクセルのflagを０にする
						for(int i(0); i<2; i++)
						{
							for(int k(0); k<3; k++)
								block[x+i][y][z+k-1].Initiaization();
						}
						//１×１は何個？（１〜４）
						cout<<"ブロックを削除した！："<<x<<" "<<y<<" "<<z<<endl;
					}
				}
			}
		}
	}

	outputFlag("Delete_Blocks.txt", VoxSize);
	//outputID("Delete_Blocks_ID.txt", VoxSize);
}
