#include "../stdafx.h"
#include "../Voxel.h"
#include "../Lego.h"		//LEGOブロックを組み立てるためのクラス

extern int ID12;			
extern int ID13;
extern int ID14;

extern int num11;		//１×１のブロックの数
extern int num12;		//１×２のブロックの数
extern int num13;		//１×３のブロックの数
extern int num14;		//１×４のブロックの数
extern int num22;		//２×２のブロックの数
extern int num23;		//２×３のブロックの数
extern int num24;		//２×４のブロックの数

void outputFlag(string filename, int* size);

//１×１の４方向に　１×１　または　１×２　があったら　結合させる
//２０１３・７・２０（土）１×１　＋　１×２　＋　１×１　→　１×４にした方がいい？　それとも後で　１×３　＋　１×１　→　１×４
void Small_to_Big_step1(Lego*** block, int* VoxSize)
{
	for(int z(1); z < VoxSize[2]-1; z++ )
	{
		//奇数層
		if(z%2)
		{
			for(int x(1); x < VoxSize[0]-1; x=x+2)
			{
				for(int y(1); y < VoxSize[1]-1; y=y+2)
				{
					//                                                                                                
					//左上が１×１の場合
					if(block[x][y][z].flag == 1)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						if(block[x-1][y][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x-1][y][z].flag = 12;		block[x-1][y][z].ID = ID12;	block[x-1][y][z].corner = 1;
							goto Odd_Right_Up;		//continueを使わないのは４ますの中で１×１が対角線で存在する場合にもう一方が計算されない
							//continue;
						}
						if(block[x][y-1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							//１×２にする
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x][y-1][z].flag = 12;		block[x][y-1][z].ID = ID12;	block[x][y-1][z].corner = 1;
							goto Odd_Right_Up;
						}
						//１×２がある場合
						if(block[x-1][y][z].flag == 2 )
						{
							if(block[x-2][y][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								//１×３にする
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
								//１×３にする
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
					//右上が１×１の場合
					if(block[x][y+1][z].flag == 1)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						//１×１がある場合
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
						//１×２がある場合
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
					//左下が１×１の場合
					if(block[x+1][y][z].flag == 1)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						//１×１がある場合
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
						//１×２がある場合
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
					//右下
					if(block[x+1][y+1][z].flag == 1)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						//１×１がある場合
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
						//１×２がある場合
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

		//偶数層
		else
		{
			for(int x(0); x < VoxSize[0]-1; x=x+2)
			{
				for(int y(0); y < VoxSize[1]-1; y=y+2)
				{
					//                                                                                                
					//左上が１×１の場合
					if(block[x][y][z].flag == 1)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						if(block[x-1][y][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x-1][y][z].flag = 12;		block[x-1][y][z].ID = ID12;	block[x-1][y][z].corner = 1;
							goto Even_Right_Up;		//continueを使わないのは４ますの中で１×１が対角線で存在する場合にもう一方が計算されない
							//continue;
						}
						if(block[x][y-1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							//１×２にする
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x][y-1][z].flag = 12;		block[x][y-1][z].ID = ID12;	block[x][y-1][z].corner = 1;
							goto Even_Right_Up;
						}
						//１×２がある場合
						if(block[x-1][y][z].flag == 2)
						{
							if(block[x-2][y][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								//１×３にする
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
								//１×３にする
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
					//右上が１×１の場合
					if(block[x][y+1][z].flag == 1)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						//１×１がある場合
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
						//１×２がある場合
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
					//左下が１×１の場合
					if(block[x+1][y][z].flag == 1)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						//１×１がある場合
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
						//１×２がある場合
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
					//右下
					if(block[x+1][y+1][z].flag == 1)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						//１×１がある場合
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
						//１×２がある場合
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

//色の相違を考慮して合成するか否かを判断する2013/9/14
void Small_to_Big_step1_color(Lego*** block, int* VoxSize)
{
	for(int z(1); z < VoxSize[2]-1; z++ )
	{
		//奇数層
		if(z%2)
		{
			for(int x(1); x < VoxSize[0]-1; x=x+2)
			{
				for(int y(1); y < VoxSize[1]-1; y=y+2)
				{
					//                                                                                                
					//左上が１×１の場合
					if(block[x][y][z].flag == 1)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						if(block[x-1][y][z].flag == 1)
						{
							//2つのブロックの色が同じまたはどちらかのボクセルに色を持たないならば合成する
							if(block[x][y][z].ColorID == block[x-1][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x-1][y][z].ColorID<1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
								block[x-1][y][z].flag = 12;		block[x-1][y][z].ID = ID12;	block[x-1][y][z].corner = 1;
								goto Odd_Right_Up;		//continueを使わないのは４ますの中で１×１が対角線で存在する場合にもう一方が計算されない
							}
						}
						if(block[x][y-1][z].flag == 1)
						{
							if(block[x][y][z].ColorID == block[x][y-1][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y-1][z].ColorID<1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								//１×２にする
								block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
								block[x][y-1][z].flag = 12;		block[x][y-1][z].ID = ID12;	block[x][y-1][z].corner = 1;
								goto Odd_Right_Up;
							}
						}
						//１×２がある場合
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
									//１×３にする
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
									//１×３にする
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
					//右上が１×１の場合
					if(block[x][y+1][z].flag == 1)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						//１×１がある場合
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
						//１×２がある場合
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
					//左下が１×１の場合
					if(block[x+1][y][z].flag == 1)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						//１×１がある場合
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
						//１×２がある場合
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
					//右下
					if(block[x+1][y+1][z].flag == 1)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						//１×１がある場合
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
						//１×２がある場合
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

		//偶数層
		else
		{
			for(int x(0); x < VoxSize[0]-1; x=x+2)
			{
				for(int y(0); y < VoxSize[1]-1; y=y+2)
				{

					//                                                                                                
					//左上が１×１の場合
					if(block[x][y][z].flag == 1)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						if(block[x-1][y][z].flag == 1)
						{
							//2つのブロックの色が同じまたはどちらかのボクセルに色を持たないならば合成する
							if(block[x][y][z].ColorID == block[x-1][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x-1][y][z].ColorID<1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
								block[x-1][y][z].flag = 12;		block[x-1][y][z].ID = ID12;	block[x-1][y][z].corner = 1;
								goto Even_Right_Up;		//continueを使わないのは４ますの中で１×１が対角線で存在する場合にもう一方が計算されない
							}
						}
						if(block[x][y-1][z].flag == 1)
						{
							if(block[x][y][z].ColorID == block[x][y-1][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y-1][z].ColorID<1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								//１×２にする
								block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
								block[x][y-1][z].flag = 12;		block[x][y-1][z].ID = ID12;	block[x][y-1][z].corner = 1;
								goto Even_Right_Up;
							}
						}
						//１×２がある場合
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
									//１×３にする
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
									//１×３にする
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
					//右上が１×１の場合
					if(block[x][y+1][z].flag == 1)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						//１×１がある場合
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
						//１×２がある場合
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
					//左下が１×１の場合
					if(block[x+1][y][z].flag == 1)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						//１×１がある場合
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
						//１×２がある場合
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
					//右下
					if(block[x+1][y+1][z].flag == 1)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						//１×１がある場合
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
						//１×２がある場合
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

//孤立している１×１を先にほかのピースとくっつける関数
void Small_to_Big_before_step1(Lego*** block, int* VoxSize)
{
	int count(0);		//孤立しそうな1×１の数
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


					//                                                                                                
					//左上が１×１の場合＆孤立しそうな場合
					if(block[x][y][z].flag == 1 && block[x][y][z-1].flag < 2 && block[x][y][z+1].flag < 2)		
					{

						//上ほど優先順位が高く　下ほど優先順位が低い
						if(block[x-1][y][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x-1][y][z].flag = 12;		block[x-1][y][z].ID = ID12;	block[x-1][y][z].corner = 1;
							goto Odd_Right_Up;		//continueを使わないのは４ますの中で１×１が対角線で存在する場合にもう一方が計算されない
							//continue;
						}
						if(block[x][y-1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							//１×２にする
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x][y-1][z].flag = 12;		block[x][y-1][z].ID = ID12;	block[x][y-1][z].corner = 1;
							goto Odd_Right_Up;
						}
						//１×２がある場合
						if(block[x-1][y][z].flag == 2)
						{
							if(block[x-2][y][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								count++;
								//１×３にする
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
								//１×３にする
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
					//右上が１×１の場合
					if(block[x][y+1][z].flag == 1 && block[x][y+1][z-1].flag < 2 && block[x][y+1][z+1].flag < 2)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						//１×１がある場合
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
						//１×２がある場合
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
					//左下が１×１の場合
					if(block[x+1][y][z].flag == 1 && block[x+1][y][z-1].flag < 2 && block[x+1][y][z+1].flag < 2)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						//１×１がある場合
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
						//１×２がある場合
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
					//右下
					if(block[x+1][y+1][z].flag == 1 && block[x+1][y+1][z-1].flag < 2 && block[x+1][y+1][z+1].flag < 2)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						//１×１がある場合
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
						//１×２がある場合
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

		//偶数層
		else
		{
			for(x=0; x < VoxSize[0]-1; x=x+2)
			{
				for(y=0; y < VoxSize[1]-1; y=y+2)
				{
					//                                                                                                
					//左上が１×１の場合
					if(block[x][y][z].flag == 1 && block[x][y][z-1].flag < 2 && block[x][y][z+1].flag < 2)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						if(block[x-1][y][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x-1][y][z].flag = 12;		block[x-1][y][z].ID = ID12;	block[x-1][y][z].corner = 1;
							goto Even_Right_Up;		//continueを使わないのは４ますの中で１×１が対角線で存在する場合にもう一方が計算されない
							//continue;
						}
						if(block[x][y-1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							//１×２にする
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x][y-1][z].flag = 12;		block[x][y-1][z].ID = ID12;	block[x][y-1][z].corner = 1;
							goto Even_Right_Up;
						}
						//１×２がある場合
						if(block[x-1][y][z].flag == 2 )
						{
							if(block[x-2][y][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								count++;
								//１×３にする
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
								//１×３にする
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
					//右上が１×１の場合
					if(block[x][y+1][z].flag == 1 && block[x][y+1][z-1].flag < 2 && block[x][y+1][z+1].flag < 2)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						//１×１がある場合
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
						//１×２がある場合
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
					//左下が１×１の場合
					if(block[x+1][y][z].flag == 1 && block[x+1][y][z-1].flag < 2 && block[x+1][y][z+1].flag < 2)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						//１×１がある場合
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
						//１×２がある場合
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
					//右下
					if(block[x+1][y+1][z].flag == 1 && block[x+1][y+1][z-1].flag < 2 && block[x+1][y+1][z+1].flag < 2)		
					{
						//上ほど優先順位が高く　下ほど優先順位が低い
						//１×１がある場合
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
						//１×２がある場合
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
		//奇数層と偶数層を分ける
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
		//奇数層と偶数層を分ける
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