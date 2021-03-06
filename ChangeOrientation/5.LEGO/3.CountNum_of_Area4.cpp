#include "../stdafx.h"

extern int num11;		//１×１のブロックの数
extern int num12;		//１×２のブロックの数
extern int num22;		//２×２のブロックの数

extern int ID12;
extern int ID22;

void outputFlag(string filename, int* size);

void CountNum_of_4(Lego*** block, int* VoxSize)
{
	unsigned short count4(0);			
	int x, y, z;
	
	for (z = 1; z < VoxSize[2] - 1; z = z + 2)				//ｚ＝1,3,5,...
	{
		for (x = 1; x < VoxSize[0] - 1; x = x + 2)
		{
			for (y = 1; y < VoxSize[1] - 1; y = y + 2)
			{
				count4 = 0;			//初期化
				//４つのボクセルを見て何個が内部ボクセルなのかをカウント（反時計まわり）
				if (block[x][y][z].fill)					count4++;
				if (block[x][y + 1][z].fill)				count4++;
				if (block[x + 1][y + 1][z].fill)			count4++;
				if (block[x + 1][y][z].fill)				count4++;

				//各ボクセルにIDをつけていく
				if (block[x][y][z].fill)					block[x][y][z].flag = count4;
				if (block[x][y + 1][z].fill)				block[x][y + 1][z].flag = count4;
				if (block[x + 1][y + 1][z].fill)			block[x + 1][y + 1][z].flag = count4;
				if (block[x + 1][y][z].fill)				block[x + 1][y][z].flag = count4;

				if (count4 == 1)				//１×１の数を加算
					num11++;
				else if (count4 == 4)		//２×２の数を加算
					num22++;
				//count4=2�LEGO
				else if (count4 == 2)
				{
					if (block[x][y][z].fill == true && block[x + 1][y + 1][z].fill == true)	//対角線になるケース１
					{
						block[x][y][z].flag = 1;
						block[x + 1][y + 1][z].flag = 1;
					}
					else if (block[x + 1][y][z].fill == true && block[x][y + 1][z].fill == true)	//対角線になるケース２
					{
						block[x + 1][y][z].flag = 1;
						block[x][y + 1][z].flag = 1;
					}
					else
						num12++;		//１×２の数を加算
				}
			}
		}
	}

	for (z = 2; z < VoxSize[2] - 1; z = z + 2)				//ｚ＝2,4,6,...
	{
		for (x = 0; x < VoxSize[0] - 1; x = x + 2)
		{
			for (y = 0; y < VoxSize[1] - 1; y = y + 2)
			{
				count4 = 0;			//初期化
				//４つのボクセルを見て何個が内部ボクセルなのかをカウント（反時計まわり）
				if (block[x][y][z].fill)					count4++;
				if (block[x][y + 1][z].fill)				count4++;
				if (block[x + 1][y + 1][z].fill)			count4++;
				if (block[x + 1][y][z].fill)				count4++;

				//各ボクセルにIDをつけていく
				if (block[x][y][z].fill)					block[x][y][z].flag = count4;
				if (block[x][y + 1][z].fill)				block[x][y + 1][z].flag = count4;
				if (block[x + 1][y + 1][z].fill)			block[x + 1][y + 1][z].flag = count4;
				if (block[x + 1][y][z].fill)				block[x + 1][y][z].flag = count4;

				if (count4 == 1)				//１×１の数を加算
					num11++;
				else if (count4 == 4)		//２×２の数を加算
					num22++;

				//count4=2の時の例外処理　二つのLEGOブロックが対角線にあるとき
				else if (count4 == 2)
				{
					if (block[x][y][z].fill == true && block[x + 1][y + 1][z].fill == true)	//対角線になるケース１
					{
						block[x][y][z].flag = 1;
						block[x + 1][y + 1][z].flag = 1;
					}
					else if (block[x + 1][y][z].fill == true && block[x][y + 1][z].fill == true)	//対角線になるケース２
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
	//step1ここまで


}

//2013/9/14

//void CountNum_of_4_ID(Lego*** block, int* VoxSize)
//{
//	unsigned short count4(0);			//２×２マスの中に存在するボクセルをカウント
//	int x,y,z;
//	//奇数層　原点（１，１）
//	for(z=1; z < VoxSize[2]-1; z = z + 2 )				//ｚ＝1,3,5,...
//	{
//		for(x=1; x < VoxSize[0]-1; x = x + 2)
//		{
//			for(y=1; y < VoxSize[1]-1; y = y + 2)
//			{
//				count4 = 0;			//初期化
//				//４つのボクセルを見て何個が内部ボクセルなのかをカウント（反時計まわり）
//				if(block[x][y][z].fill)					count4++;
//				if(block[x][y+1][z].fill)				count4++;
//				if(block[x+1][y+1][z].fill)			count4++;
//				if(block[x+1][y][z].fill)				count4++;
//
//				//各ボクセルにIDをつけていく
//				if(block[x][y][z].fill)					block[x][y][z].flag = count4;
//				if(block[x][y+1][z].fill)				block[x][y+1][z].flag = count4;
//				if(block[x+1][y+1][z].fill)			block[x+1][y+1][z].flag = count4;
//				if(block[x+1][y][z].fill)				block[x+1][y][z].flag = count4;
//
//				if(count4 == 1)				//１×１の数を加算
//					num11++;
//				else if(count4 == 4)		//２×２の数を加算
//				{
//					num22++;
//					ID22++;
//					block[x][y][z].ID = ID22;
//					block[x][y+1][z].ID = ID22;
//					block[x+1][y+1][z].ID = ID22;
//					block[x+1][y][z].ID = ID22;
//				}
//				//count4=2の時の例外処理　二つのLEGOブロックが対角線にあるとき
//				else if(count4 == 2)
//				{
//					//１×２になる場合
//					if(block[x][y][z].fill)
//					{
//						//ｙ軸に平行
//						if(block[x+1][y][z].fill)
//						{
//							num12++;		//１×２の数を加算
//							ID12++;
//							block[x][y][z].ID = ID12;
//							block[x+1][y][z].ID = ID12;
//							continue;
//						}
//						//ｘ軸に平行
//						else if(block[x][y+1][z].fill)
//						{
//							num12++;		//１×２の数を加算
//							ID12++;
//							block[x][y][z].ID = ID12;
//							block[x][y+1][z].ID = ID12;
//							continue;
//						}
//					}
//					if(block[x+1][y+1][z].fill)
//					{
//						//ｙ軸に平行
//						if(block[x][y+1][z].fill)
//						{
//							num12++;		//１×２の数を加算
//							ID12++;
//							block[x+1][y+1][z].ID = ID12;
//							block[x][y+1][z].ID = ID12;
//							continue;
//						}
//						//ｘ軸に平行
//						else if(block[x+1][y][z].fill)
//						{
//							num12++;		//１×２の数を加算
//							ID12++;
//							block[x+1][y+1][z].ID = ID12;
//							block[x+1][y][z].ID = ID12;
//							continue;
//						}
//					}
//
//					//対角線上にある場合の場合
//					if(block[x][y][z].fill == true && block[x+1][y+1][z].fill == true)	//対角線になるケース１
//					{
//						block[x][y][z].flag = 1;				
//						block[x+1][y+1][z].flag = 1;
//					}
//					else if(block[x+1][y][z].fill == true && block[x][y+1][z].fill == true)	//対角線になるケース２
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
//	//偶数層　原点（２，２）
//	for(z=2; z < VoxSize[2]-1; z = z + 2 )				//ｚ＝2,4,6,...
//	{
//		for(x=0; x < VoxSize[0]-1; x = x + 2)
//		{
//			for(y=0; y < VoxSize[1]-1; y = y + 2)
//			{
//				count4 = 0;			//初期化
//				//４つのボクセルを見て何個が内部ボクセルなのかをカウント（反時計まわり）
//				if(block[x][y][z].fill)					count4++;
//				if(block[x][y+1][z].fill)				count4++;
//				if(block[x+1][y+1][z].fill)			count4++;
//				if(block[x+1][y][z].fill)				count4++;
//
//				//各ボクセルにIDをつけていく
//				if(block[x][y][z].fill)					block[x][y][z].flag = count4;
//				if(block[x][y+1][z].fill)				block[x][y+1][z].flag = count4;
//				if(block[x+1][y+1][z].fill)			block[x+1][y+1][z].flag = count4;
//				if(block[x+1][y][z].fill)				block[x+1][y][z].flag = count4;
//
//				if(count4 == 1)				//１×１の数を加算
//					num11++;
//				else if(count4 == 4)		//２×２の数を加算
//				{
//					num22++;
//					ID22++;
//					block[x][y][z].ID = ID22;
//					block[x][y+1][z].ID = ID22;
//					block[x+1][y+1][z].ID = ID22;
//					block[x+1][y][z].ID = ID22;
//				}
//				//count4=2の時の例外処理　二つのLEGOブロックが対角線にあるとき
//				else if(count4 == 2)
//				{
//					//１×２になる場合
//					if(block[x][y][z].fill)
//					{
//						//ｙ軸に平行
//						if(block[x+1][y][z].fill)
//						{
//							num12++;		//１×２の数を加算
//							ID12++;
//							block[x][y][z].ID = ID12;
//							block[x+1][y][z].ID = ID12;
//							continue;
//						}
//						//ｘ軸に平行
//						else if(block[x][y+1][z].fill)
//						{
//							num12++;		//１×２の数を加算
//							ID12++;
//							block[x][y][z].ID = ID12;
//							block[x][y+1][z].ID = ID12;
//							continue;
//						}
//					}
//					if(block[x+1][y+1][z].fill)
//					{
//						//ｙ軸に平行
//						if(block[x][y+1][z].fill)
//						{
//							num12++;		//１×２の数を加算
//							ID12++;
//							block[x+1][y+1][z].ID = ID12;
//							block[x][y+1][z].ID = ID12;
//							continue;
//						}
//						//ｘ軸に平行
//						else if(block[x+1][y][z].fill)
//						{
//							num12++;		//１×２の数を加算
//							ID12++;
//							block[x+1][y+1][z].ID = ID12;
//							block[x+1][y][z].ID = ID12;
//							continue;
//						}
//					}
//
//					//対角線上にある場合の場合
//					if(block[x][y][z].fill == true && block[x+1][y+1][z].fill == true)	//対角線になるケース１
//					{
//						block[x][y][z].flag = 1;				
//						block[x+1][y+1][z].flag = 1;
//					}
//					else if(block[x+1][y][z].fill == true && block[x][y+1][z].fill == true)	//対角線になるケース２
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
//	//step1ここまで
//
//}

//2014/5/21
void CountNum_of_4_ID(Lego*** block, int* VoxSize)
{
	unsigned short count4(0);			//２×２マスの中に存在するボクセルをカウント
	unsigned short Ccount(0);			//２×２マスの中に存在する同色ボクセルをカウント
	unsigned short Scount(0);			//２×２マスの中に存在する表面ボクセルをカウント
	int x, y, z;
	//奇数層　原点（１，１）
	for (z = 1; z < VoxSize[2] - 1; z = z + 2)				//ｚ＝1,3,5,...
	{
		for (x = 1; x < VoxSize[0] - 1; x = x + 2)
		{
			for (y = 1; y < VoxSize[1] - 1; y = y + 2)
			{
				int CoC[8] = { 0,0,0,0,0,0,0,0 };
				count4 = 0;			//初期化
				Ccount = 0;			//初期化
				//４つのボクセルを見て何個が内部ボクセルなのかをカウント（反時計まわり）
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
				//			num12++;		//１×２の数を加算
				//			ID12++;
				//			block[x][y][z].ID = ID12;
				//			block[x+1][y][z].ID = ID12;
				//			num12++;		//１×２の数を加算
				//			ID12++;
				//			block[x][y+1][z].ID = ID12;
				//			block[x+1][y+1][z].ID = ID12;					
				//	}
				//	else if((block[x][y][z].ColorID==0&&block[x+1][y][z].ColorID==0)||
				//		(block[x][y][z].ColorID>0&&block[x+1][y][z].ColorID>0)){
				//			num12++;		//１×２の数を加算
				//			ID12++;
				//			block[x][y][z].ID = ID12;
				//			block[x+1][y][z].ID = ID12;
				//			num12++;		//１×２の数を加算
				//			ID12++;
				//			block[x][y+1][z].ID = ID12;
				//			block[x+1][y+1][z].ID = ID12;								
				//	}
				//	else{
				//			num12++;		//１×２の数を加算
				//			ID12++;
				//			block[x][y][z].ID = ID12;
				//			block[x][y+1][z].ID = ID12;
				//			num12++;		//１×２の数を加算
				//			ID12++;
				//			block[x+1][y][z].ID = ID12;
				//			block[x+1][y+1][z].ID = ID12;										
				//	}
				//}
				//3つの場合
				if (count4 == 3 && Ccount > 1) {
					if (block[x][y][z].fill)	block[x][y][z].flag = 1;
					if (block[x][y + 1][z].fill)   block[x][y + 1][z].flag = 1;
					if (block[x + 1][y + 1][z].fill)   block[x + 1][y + 1][z].flag = 1;
					if (block[x + 1][y][z].fill)   block[x + 1][y][z].flag = 1;
					num11 = num11 + 3;
				}

				if (count4 == 1)				//１×１の数を加算
					num11++;

				//count4=2の時の例外処理　二つのLEGOブロックが対角線にあるとき
				else if (count4 == 2)
				{
					//１×２になる場合
					if (block[x][y][z].fill)
					{
						//ｙ軸に平行
						if (block[x + 1][y][z].fill)
						{
							if (block[x][y][z].ColorID == block[x + 1][y][z].ColorID
								|| (block[x][y][z].ColorID == 0 || block[x + 1][y][z].ColorID == 0)) {
								num12++;		//１×２の数を加算
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
						//ｘ軸に平行
						else if (block[x][y + 1][z].fill)
						{
							if (block[x][y][z].ColorID == block[x][y + 1][z].ColorID ||
								(block[x][y][z].ColorID == 0 || block[x][y + 1][z].ColorID == 0)) {
								num12++;		//１×２の数を加算
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
						//ｙ軸に平行
						if (block[x][y + 1][z].fill)
						{
							if (block[x + 1][y + 1][z].ColorID == block[x][y + 1][z].ColorID
								|| (block[x + 1][y + 1][z].ColorID == 0 || block[x][y + 1][z].ColorID == 0)) {
								num12++;		//１×２の数を加算
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
						//ｘ軸に平行
						else if (block[x + 1][y][z].fill)
						{
							if (block[x + 1][y + 1][z].ColorID == block[x + 1][y][z].ColorID
								|| (block[x + 1][y + 1][z].ColorID == 0 || block[x + 1][y][z].ColorID == 0)) {
								num12++;		//１×２の数を加算
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

					//対角線上にある場合の場合
					if (block[x][y][z].fill == true && block[x + 1][y + 1][z].fill == true)	//対角線になるケース１
					{
						block[x][y][z].flag = 1;
						block[x + 1][y + 1][z].flag = 1;
						num11++;
						num11++;
					}
					else if (block[x + 1][y][z].fill == true && block[x][y + 1][z].fill == true)	//対角線になるケース２
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

	//偶数層　原点（２，２）
	for (z = 2; z < VoxSize[2] - 1; z = z + 2)				//ｚ＝2,4,6,...
	{
		for (x = 0; x < VoxSize[0] - 1; x = x + 2)
		{
			for (y = 0; y < VoxSize[1] - 1; y = y + 2)
			{
				int CoC[8] = { 0,0,0,0,0,0,0,0 };
				count4 = 0;			//初期化
				Ccount = 0;			//初期化
				//４つのボクセルを見て何個が内部ボクセルなのかをカウント（反時計まわり）
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
				//各ボクセルにIDをつけていく
				if (block[x][y][z].fill)					block[x][y][z].flag = count4;
				if (block[x][y + 1][z].fill)				block[x][y + 1][z].flag = count4;
				if (block[x + 1][y + 1][z].fill)			block[x + 1][y + 1][z].flag = count4;
				if (block[x + 1][y][z].fill)				block[x + 1][y][z].flag = count4;

				//4つある場合
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
				//			num12++;		//１×２の数を加算
				//			ID12++;
				//			block[x][y][z].ID = ID12;
				//			block[x+1][y][z].ID = ID12;
				//			num12++;		//１×２の数を加算
				//			ID12++;
				//			block[x][y+1][z].ID = ID12;
				//			block[x+1][y+1][z].ID = ID12;					
				//	}
				//	else if((block[x][y][z].ColorID==0&&block[x+1][y][z].ColorID==0)||
				//		(block[x][y][z].ColorID>0&&block[x+1][y][z].ColorID>0)){
				//			num12++;		//１×２の数を加算
				//			ID12++;
				//			block[x][y][z].ID = ID12;
				//			block[x+1][y][z].ID = ID12;
				//			num12++;		//１×２の数を加算
				//			ID12++;
				//			block[x][y+1][z].ID = ID12;
				//			block[x+1][y+1][z].ID = ID12;								
				//	}
				//	else{
				//			num12++;		//１×２の数を加算
				//			ID12++;
				//			block[x][y][z].ID = ID12;
				//			block[x][y+1][z].ID = ID12;
				//			num12++;		//１×２の数を加算
				//			ID12++;
				//			block[x+1][y][z].ID = ID12;
				//			block[x+1][y+1][z].ID = ID12;										
				//	}
				//}
				//3つの場合
				if (count4 == 3 && Ccount > 1) {
					if (block[x][y][z].fill)	block[x][y][z].flag = 1;
					if (block[x][y + 1][z].fill)   block[x][y + 1][z].flag = 1;
					if (block[x + 1][y + 1][z].fill)   block[x + 1][y + 1][z].flag = 1;
					if (block[x + 1][y][z].fill)   block[x + 1][y][z].flag = 1;
					num11 = num11 + 3;
				}

				if (count4 == 1)				//１×１の数を加算
					num11++;

				//count4=2の時の例外処理　二つのLEGOブロックが対角線にあるとき
				else if (count4 == 2)
				{
					//１×２になる場合
					if (block[x][y][z].fill)
					{
						//ｙ軸に平行
						if (block[x + 1][y][z].fill)
						{
							if (block[x][y][z].ColorID == block[x + 1][y][z].ColorID
								|| (block[x][y][z].ColorID == 0 || block[x + 1][y][z].ColorID == 0)) {
								num12++;		//１×２の数を加算
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
						//ｘ軸に平行
						else if (block[x][y + 1][z].fill)
						{
							if (block[x][y][z].ColorID == block[x][y + 1][z].ColorID ||
								(block[x][y][z].ColorID == 0 || block[x][y + 1][z].ColorID == 0)) {
								num12++;		//１×２の数を加算
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
						//ｙ軸に平行
						if (block[x][y + 1][z].fill)
						{
							if (block[x + 1][y + 1][z].ColorID == block[x][y + 1][z].ColorID
								|| (block[x + 1][y + 1][z].ColorID == 0 || block[x][y + 1][z].ColorID == 0)) {
								num12++;		//１×２の数を加算
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
						//ｘ軸に平行
						else if (block[x + 1][y][z].fill)
						{
							if (block[x + 1][y + 1][z].ColorID == block[x + 1][y][z].ColorID
								|| (block[x + 1][y + 1][z].ColorID == 0 || block[x + 1][y][z].ColorID == 0)) {
								num12++;		//１×２の数を加算
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

					//対角線上にある場合の場合
					if (block[x][y][z].fill == true && block[x + 1][y + 1][z].fill == true)	//対角線になるケース１
					{
						block[x][y][z].flag = 1;
						block[x + 1][y + 1][z].flag = 1;
						num11++;
						num11++;
					}
					else if (block[x + 1][y][z].fill == true && block[x][y + 1][z].fill == true)	//対角線になるケース２
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
	//step1ここまで

}