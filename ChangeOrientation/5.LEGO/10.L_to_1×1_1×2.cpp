#include "../stdafx.h"
#include "../Voxel.h"
#include "../Lego.h"		//LEGOブロックを組み立てるためのクラス

void outputFlag(string filename, int* size);

extern int num11;		//１×１のブロックの数
extern int num12;		//１×２のブロックの数
extern int num22;		//２×２のブロックの数

extern int ID12;	
extern int ID22;	

//L字を1×１　と　１×２に置き換える
void Small_to_Big_step0( Lego*** block, int* VoxSize)
{
	int Left_Up(0);
	int Left_Down(0);
	int Right_Up(0);
	int Right_Down(0);

	int count(0);		//L字が１×１と１×２に分割できなかった個数
	int countLN(0);
	int x,y,z;
	//奇数層
	for(z=1; z < VoxSize[2]-1; z++ )
	{
		if(z%2)
		{
			for(x=1; x < VoxSize[0]-1; x=x+2)
			{
				for(y=1; y < VoxSize[1]-1; y=y+2)
				{
					//注目ボクセルのIDが３になる場合
					if(block[x][y][z].flag == 3)
					{
						//                                                                                                                                
						//ケース２
						if(block[x][y+1][z].flag == 0)
						{
							countLN++;
							//一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							if( (block[x][y][z-1].flag > 3 || block[x][y][z+1].flag > 3) &&  block[x+1][y+1][z-1].flag < 4 && block[x+1][y+1][z+1].flag < 4 )
							{
								block[x][y][z].flag = 1;
								block[x+1][y][z].flag = 2; 
								block[x+1][y+1][z].flag = 2;
								num11++;
								num12++;
							}
							//もう一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							else if( block[x][y][z-1].flag < 4 && block[x][y][z+1].flag < 4 && ( block[x+1][y+1][z-1].flag > 3 || block[x+1][y+1][z+1].flag > 3))
							{
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 2; 
								block[x+1][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//注目の２つのボクセルの上下（４つ）ともに１×１以下のボクセルであるとき
							else if(block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2)
							{
								count++;
								num22++;
								//２×２に無理やり変えますよんんんん〜
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x][y+1][z].fill = true;
								cout<<"分割できなかったから2×2に変えたぞ！"<<x<<" "<<y<<" "<<z<<endl;
							}
							//上記以外の時は
							else
							{
								//上と下のボクセルのフラグの値をかけて大きい方を分割する
								Left_Up = (block[x][y][z-1].flag) * (block[x][y][z+1].flag);
								Right_Down =  (block[x+1][y+1][z-1].flag) * (block[x+1][y+1][z+1].flag);
								if(Left_Up > Right_Down)
								{
									block[x][y][z].flag = 1;
									block[x+1][y][z].flag = 2; 
									block[x+1][y+1][z].flag = 2; 
									num11++;
									num12++;
								}
								else
								{
									block[x][y][z].flag = 2;
									block[x+1][y][z].flag = 2; 
									block[x+1][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
						//						                                                                                                                                
						//ケース３
						else if(block[x+1][y+1][z].flag == 0)
						{
							countLN++;
							//一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							if( (block[x+1][y][z-1].flag >3  ||  block[x+1][y][z+1].flag > 3) && block[x][y+1][z-1].flag < 4 &&  block[x][y+1][z+1].flag < 4 )
							{
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 1; 
								block[x][y+1][z].flag = 2; 
								num11++;
								num12++;
							}
							//もう一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							else if( block[x+1][y][z-1].flag < 4  &&  block[x+1][y][z+1].flag < 4 && (block[x][y+1][z-1].flag > 3 &&  block[x][y+1][z+1].flag > 3) )
							{
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 2; 
								block[x][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//注目の２つのボクセルの上下（４つ）ともに１×１以下のボクセルであるとき
							else if(block[x+1][y][z-1].flag < 2 &&  block[x+1][y][z+1].flag < 2 && block[x][y+1][z-1].flag < 2 &&  block[x][y+1][z+1].flag < 2 )
							{
								count++;
								num22++;
								//２×２に無理やり変えますよんんんん〜
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x+1][y+1][z].fill = true;
								cout<<"分割できなかったから2×2に変えたぞ！"<<x<<" "<<y<<" "<<z<<endl;
							}
							//上記以外の時は
							else
							{
								Left_Down = (block[x+1][y][z-1].flag) * (block[x+1][y][z+1].flag);
								Right_Up =  (block[x][y+1][z-1].flag) * (block[x][y+1][z+1].flag);
								if(Left_Down > Right_Up)
								{
									block[x][y][z].flag = 2;
									block[x+1][y][z].flag = 1; 
									block[x][y+1][z].flag = 2; 
									num11++;
									num12++;
								}
								else
								{
									block[x][y][z].flag = 2;
									block[x+1][y][z].flag = 2; 
									block[x][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
						//                                                                                                     
						//ケース４
						else if(block[x+1][y][z].flag == 0)
						{
							countLN++;
							//一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							if( (block[x][y][z-1].flag > 3 ||  block[x][y][z+1].flag > 3) && block[x+1][y+1][z-1].flag < 4 &&  block[x+1][y+1][z+1].flag < 4 )
							{
								block[x][y][z].flag = 1;
								block[x][y+1][z].flag = 2; 
								block[x+1][y+1][z].flag = 2; 
								num11++;
								num12++;
							}
							//もう一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							else if( block[x][y][z-1].flag < 4 &&  block[x][y][z+1].flag < 4 && (block[x+1][y+1][z-1].flag > 3 ||  block[x+1][y+1][z+1].flag > 3) )
							{
								block[x][y][z].flag = 2;
								block[x][y+1][z].flag = 2; 
								block[x+1][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//注目ボクセルの上下4つともに１×１または何もない場合
							else if( block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2 )
							{
								count++;
								num22++;
								//２×２に無理やり変えますよんんんん〜
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x+1][y][z].fill = true;
								cout<<"分割できなかったから2×2に変えたぞ！"<<x<<" "<<y<<" "<<z<<endl;
							}
							//上記以外の場合
							else
							{
								//上と下のボクセルのフラグの値をかけて大きい方を分割する
								Left_Up = (block[x][y][z-1].flag) * (block[x][y][z+1].flag);
								Right_Down =  (block[x+1][y+1][z-1].flag) * (block[x+1][y+1][z+1].flag);
								if(Left_Up > Right_Down)
								{
									block[x][y][z].flag = 1;
									block[x][y+1][z].flag = 2; 
									block[x+1][y+1][z].flag = 2; 
									num11++;
									num12++;
								}
								else
								{
									block[x][y][z].flag = 2;
									block[x][y+1][z].flag = 2; 
									block[x+1][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
					}
					//注目ボクセルのIDが0になる場合
					else if(block[x][y][z].flag == 0 )
					{
						if(block[x][y+1][z].flag == 3)			//ケース１
						{
							countLN++;
							if( (block[x+1][y][z-1].flag > 3 ||  block[x+1][y][z+1].flag > 3) && block[x][y+1][z-1].flag < 4 &&  block[x][y+1][z+1].flag < 4)
							{
								block[x+1][y+1][z].flag = 2;
								block[x+1][y][z].flag = 1; 
								block[x][y+1][z].flag = 2; 
								num11++;
								num12++;
							}
							else if(block[x+1][y][z-1].flag < 4 &&  block[x+1][y][z+1].flag < 4 && (block[x][y+1][z-1].flag > 3 ||  block[x][y+1][z+1].flag > 3) )
							{
								block[x+1][y+1][z].flag = 2;
								block[x+1][y][z].flag = 2; 
								block[x][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							else if( block[x+1][y][z-1].flag < 2 && block[x+1][y][z+1].flag < 2 && block[x][y+1][z-1].flag < 2 &&  block[x][y+1][z+1].flag < 2)
							{
								count++;
								num22++;
								//２×２に無理やり変えますよんんんん〜
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x][y][z].fill = true;
								cout<<"分割できなかったから2×2に変えたぞ！"<<x<<" "<<y<<" "<<z<<endl;
							}
							else
							{
								//上と下のボクセルのフラグの値をかけて大きい方を分割する
								Left_Down = (block[x+1][y][z-1].flag) * (block[x+1][y][z+1].flag);
								Right_Up =  (block[x][y+1][z-1].flag) * (block[x][y+1][z+1].flag);
								if(Left_Down > Right_Up)
								{
									block[x+1][y+1][z].flag = 2;
									block[x+1][y][z].flag = 1; 
									block[x][y+1][z].flag = 2; 
									num11++;
									num12++;
								}
								else
								{
									block[x+1][y+1][z].flag = 2;
									block[x+1][y][z].flag = 2; 
									block[x][y+1][z].flag = 1; 
									num11++;
									num12++;
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
			for(x=0; x < VoxSize[0]-1; x=x+2)
			{
				for(y=0; y < VoxSize[1]-1; y=y+2)
				{
					//注目ボクセルのIDが３になる場合
					if(block[x][y][z].flag == 3)
					{
						//                                                                                                                                
						//ケース２
						if(block[x][y+1][z].flag == 0)
						{
							countLN++;
							//一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							if( (block[x][y][z-1].flag > 3 || block[x][y][z+1].flag > 3) &&  block[x+1][y+1][z-1].flag < 4 && block[x+1][y+1][z+1].flag < 4 )
							{
								block[x][y][z].flag = 1;
								block[x+1][y][z].flag = 2; 
								block[x+1][y+1][z].flag = 2; 
								num11++;
								num12++;
							}
							//もう一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							else if( block[x][y][z-1].flag < 4 && block[x][y][z+1].flag < 4 && ( block[x+1][y+1][z-1].flag > 3 || block[x+1][y+1][z+1].flag > 3))
							{
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 2; 
								block[x+1][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//注目の２つのボクセルの上下（４つ）ともに１×１以下のボクセルであるとき
							else if(block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2)
							{
								count++;
								num22++;
								//２×２に無理やり変えますよんんんん〜
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x][y+1][z].fill = true;
								cout<<"分割できなかったから2×2に変えたぞ！"<<x<<" "<<y<<" "<<z<<endl;
							}
							//上記以外の時は
							else
							{
								//上と下のボクセルのフラグの値をかけて大きい方を分割する
								Left_Up = (block[x][y][z-1].flag) * (block[x][y][z+1].flag);
								Right_Down =  (block[x+1][y+1][z-1].flag) * (block[x+1][y+1][z+1].flag);
								if(Left_Up > Right_Down)
								{
									block[x][y][z].flag = 1;
									block[x+1][y][z].flag = 2; 
									block[x+1][y+1][z].flag = 2; 
									num11++;
									num12++;
								}
								else
								{
									block[x][y][z].flag = 2;
									block[x+1][y][z].flag = 2; 
									block[x+1][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
						//						                                                                                                                                
						//ケース３
						else if(block[x+1][y+1][z].flag == 0)
						{
							countLN++;
							//一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							if( (block[x+1][y][z-1].flag >3  ||  block[x+1][y][z+1].flag > 3) && block[x][y+1][z-1].flag < 4 &&  block[x][y+1][z+1].flag < 4 )
							{
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 1; 
								block[x][y+1][z].flag = 2; 
								num11++;
								num12++;
							}
							//もう一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							else if( block[x+1][y][z-1].flag < 4  &&  block[x+1][y][z+1].flag < 4 && (block[x][y+1][z-1].flag > 3 &&  block[x][y+1][z+1].flag > 3) )
							{
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 2; 
								block[x][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//注目の２つのボクセルの上下（４つ）ともに１×１以下のボクセルであるとき
							else if(block[x+1][y][z-1].flag < 2 &&  block[x+1][y][z+1].flag < 2 && block[x][y+1][z-1].flag < 2 &&  block[x][y+1][z+1].flag < 2 )
							{
								count++;
								num22++;
								//２×２に無理やり変えますよんんんん〜
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x+1][y+1][z].fill = true;
								cout<<"分割できなかったから2×2に変えたぞ！"<<x<<" "<<y<<" "<<z<<endl;
							}
							//上記以外の時は
							else
							{
								Left_Down = (block[x+1][y][z-1].flag) * (block[x+1][y][z+1].flag);
								Right_Up =  (block[x][y+1][z-1].flag) * (block[x][y+1][z+1].flag);
								if(Left_Down > Right_Up)
								{
									block[x][y][z].flag = 2;
									block[x+1][y][z].flag = 1; 
									block[x][y+1][z].flag = 2; 
									num11++;
									num12++;
								}
								else
								{
									block[x][y][z].flag = 2;
									block[x+1][y][z].flag = 2; 
									block[x][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
						//                                                                                                     
						//ケース４
						else if(block[x+1][y][z].flag == 0)
						{
							countLN++;
							//一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							if( (block[x][y][z-1].flag > 3 ||  block[x][y][z+1].flag > 3) && block[x+1][y+1][z-1].flag < 4 &&  block[x+1][y+1][z+1].flag < 4 )
							{
								block[x][y][z].flag = 1;
								block[x][y+1][z].flag = 2; 
								block[x+1][y+1][z].flag = 2; 
								num11++;
								num12++;
							}
							//もう一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							else if( block[x][y][z-1].flag < 4 &&  block[x][y][z+1].flag < 4 && (block[x+1][y+1][z-1].flag > 3 ||  block[x+1][y+1][z+1].flag > 3) )
							{
								block[x][y][z].flag = 2;
								block[x][y+1][z].flag = 2; 
								block[x+1][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//注目ボクセルの上下4つともに１×１または何もない場合
							else if( block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2 )
							{
								count++;
								num22++;
								//２×２に無理やり変えますよんんんん〜
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x+1][y][z].fill = true;
								cout<<"分割できなかったから2×2に変えたぞ！"<<x<<" "<<y<<" "<<z<<endl;
							}
							//上記以外の場合
							else
							{
								//上と下のボクセルのフラグの値をかけて大きい方を分割する
								Left_Up = (block[x][y][z-1].flag) * (block[x][y][z+1].flag);
								Right_Down =  (block[x+1][y+1][z-1].flag) * (block[x+1][y+1][z+1].flag);
								if(Left_Up > Right_Down)
								{
									block[x][y][z].flag = 1;
									block[x][y+1][z].flag = 2; 
									block[x+1][y+1][z].flag = 2; 
									num11++;
									num12++;
								}
								else
								{
									block[x][y][z].flag = 2;
									block[x][y+1][z].flag = 2; 
									block[x+1][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
					}
					//注目ボクセルのIDが0になる場合
					else if(block[x][y][z].flag == 0 )
					{
						if(block[x][y+1][z].flag == 3)			//ケース１
						{
							countLN++;
							if( (block[x+1][y][z-1].flag > 3 ||  block[x+1][y][z+1].flag > 3) && block[x][y+1][z-1].flag < 4 &&  block[x][y+1][z+1].flag < 4)
							{
								block[x+1][y+1][z].flag = 2;
								block[x+1][y][z].flag = 1; 
								block[x][y+1][z].flag = 2; 
								num11++;
								num12++;
							}
							else if(block[x+1][y][z-1].flag < 4 &&  block[x+1][y][z+1].flag < 4 && (block[x][y+1][z-1].flag > 3 ||  block[x][y+1][z+1].flag > 3) )
							{
								block[x+1][y+1][z].flag = 2;
								block[x+1][y][z].flag = 2; 
								block[x][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							else if( block[x+1][y][z-1].flag < 2 && block[x+1][y][z+1].flag < 2 && block[x][y+1][z-1].flag < 2 &&  block[x][y+1][z+1].flag < 2)
							{
								count++;
								num22++;
								//２×２に無理やり変えますよんんんん〜
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x][y][z].fill = true;
								cout<<"分割できなかったから2×2に変えたぞ！"<<x<<" "<<y<<" "<<z<<endl;
							}
							else
							{
								//上と下のボクセルのフラグの値をかけて大きい方を分割する
								Left_Down = (block[x+1][y][z-1].flag) * (block[x+1][y][z+1].flag);
								Right_Up =  (block[x][y+1][z-1].flag) * (block[x][y+1][z+1].flag);
								if(Left_Down > Right_Up)
								{
									block[x+1][y+1][z].flag = 2;
									block[x+1][y][z].flag = 1; 
									block[x][y+1][z].flag = 2; 
									num11++;
									num12++;
								}
								else
								{
									block[x+1][y+1][z].flag = 2;
									block[x+1][y][z].flag = 2; 
									block[x][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
					}
				}
			}
		}
	}

	cout<<countLN<<"個中　"<<count<<" 個のLを１×１と１×２に分割できなかった！"<<endl;
	outputFlag("test00_L_to11_12.txt", VoxSize);

}

void Small_to_Big_step0_color( Lego*** block, int* VoxSize)
{
	int Left_Up(0);
	int Left_Down(0);
	int Right_Up(0);
	int Right_Down(0);

	int count(0);		//L字が１×１と１×２に分割できなかった個数
	int countLN(0);
	int x,y,z;
	//奇数層
	for(z=1; z < VoxSize[2]-1; z++ )
	{
		if(z%2)
		{
			for(x=1; x < VoxSize[0]-1; x=x+2)
			{
				for(y=1; y < VoxSize[1]-1; y=y+2)
				{
					//注目ボクセルのIDが３になる場合
					if(block[x][y][z].flag == 3)
					{
						//                                                                                                                                
						//ケース２(２×２のマスクに対して３つのボクセルがどのように配置しているのか)
						if(block[x][y+1][z].flag == 0)
						{
							countLN++;
							//一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							if( (block[x][y][z-1].flag > 3 || block[x][y][z+1].flag > 3) &&  block[x+1][y+1][z-1].flag < 4 && block[x+1][y+1][z+1].flag < 4 )
							{
								ID12++;
								block[x][y][z].flag = 1;
								block[x+1][y][z].flag = 2;			block[x+1][y][z].ID = ID12; 
								block[x+1][y+1][z].flag = 2;		block[x+1][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//もう一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							else if( block[x][y][z-1].flag < 4 && block[x][y][z+1].flag < 4 && ( block[x+1][y+1][z-1].flag > 3 || block[x+1][y+1][z+1].flag > 3))
							{
								ID12++;
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 2;			block[x+1][y][z].ID = ID12; 
								block[x+1][y+1][z].flag = 1;		block[x+1][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//注目の２つのボクセルの上下（４つ）ともに１×１以下のボクセルであるとき
							else if(block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2)
							{
								ID22++;
								count++;
								num22++;
								//２×２に無理やり変えます
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x][y+1][z].fill = true;
								cout<<"分割できなかったから2×2に変えたぞ！"<<x<<" "<<y<<" "<<z<<endl;
							}
							//上記以外の時は
							else
							{
								//上と下のボクセルのフラグの値をかけて大きい方を分割する
								Left_Up = (block[x][y][z-1].flag) * (block[x][y][z+1].flag);
								Right_Down =  (block[x+1][y+1][z-1].flag) * (block[x+1][y+1][z+1].flag);
								if(Left_Up > Right_Down)
								{
									ID12++;
									block[x][y][z].flag = 1;
									block[x+1][y][z].flag = 2;					block[x+1][y][z].ID = ID12; 
									block[x+1][y+1][z].flag = 2;				block[x+1][y+1][z].ID = ID12; 
									num11++;
									num12++;
								}
								else
								{
									ID12++;
									block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
									block[x+1][y][z].flag = 2;				block[x+1][y][z].ID = ID12; 
									block[x+1][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
						//						                                                                                                                                
						//ケース３
						else if(block[x+1][y+1][z].flag == 0)
						{
							countLN++;
							//一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							if( (block[x+1][y][z-1].flag >3  ||  block[x+1][y][z+1].flag > 3) && block[x][y+1][z-1].flag < 4 &&  block[x][y+1][z+1].flag < 4 )
							{
								ID12++;
								block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
								block[x+1][y][z].flag = 1; 
								block[x][y+1][z].flag = 2;				block[x][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//もう一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							else if( block[x+1][y][z-1].flag < 4  &&  block[x+1][y][z+1].flag < 4 && (block[x][y+1][z-1].flag > 3 &&  block[x][y+1][z+1].flag > 3) )
							{
								ID12++;
								block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
								block[x+1][y][z].flag = 2; 				block[x+1][y][z].ID = ID12; 
								block[x][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//注目の２つのボクセルの上下（４つ）ともに１×１以下のボクセルであるとき
							else if(block[x+1][y][z-1].flag < 2 &&  block[x+1][y][z+1].flag < 2 && block[x][y+1][z-1].flag < 2 &&  block[x][y+1][z+1].flag < 2 )
							{
								ID22++;
								count++;
								num22++;
								//２×２に無理やり変えますよんんんん〜
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x+1][y+1][z].fill = true;
								cout<<"分割できなかったから2×2に変えたぞ！"<<x<<" "<<y<<" "<<z<<endl;
							}
							//上記以外の時は
							else
							{
								Left_Down = (block[x+1][y][z-1].flag) * (block[x+1][y][z+1].flag);
								Right_Up =  (block[x][y+1][z-1].flag) * (block[x][y+1][z+1].flag);
								if(Left_Down > Right_Up)
								{
									ID12++;
									block[x][y][z].flag = 2;						block[x][y][z].ID = ID12;
									block[x+1][y][z].flag = 1; 
									block[x][y+1][z].flag = 2;					block[x][y+1][z].ID = ID12; 
									num11++;
									num12++;
								}
								else
								{
									ID12++;
									block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
									block[x+1][y][z].flag = 2; 				block[x+1][y][z].ID = ID12; 
									block[x][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
						//                                                                                                     
						//ケース４
						else if(block[x+1][y][z].flag == 0)
						{
							countLN++;
							//一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							if( (block[x][y][z-1].flag > 3 ||  block[x][y][z+1].flag > 3) && block[x+1][y+1][z-1].flag < 4 &&  block[x+1][y+1][z+1].flag < 4 )
							{
								ID12++;
								block[x][y][z].flag = 1;
								block[x][y+1][z].flag = 2; 				block[x][y+1][z].ID = ID12; 
								block[x+1][y+1][z].flag = 2;			block[x+1][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//もう一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							else if( block[x][y][z-1].flag < 4 &&  block[x][y][z+1].flag < 4 && (block[x+1][y+1][z-1].flag > 3 ||  block[x+1][y+1][z+1].flag > 3) )
							{
								ID12++;
								block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
								block[x][y+1][z].flag = 2;				block[x][y+1][z].ID = ID12; 
								block[x+1][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//注目ボクセルの上下4つともに１×１または何もない場合
							else if( block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2 )
							{
								ID22++;
								count++;
								num22++;
								//２×２に無理やり変えますよんんんん〜
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x+1][y][z].fill = true;
								cout<<"分割できなかったから2×2に変えたぞ！"<<x<<" "<<y<<" "<<z<<endl;
							}
							//上記以外の場合
							else
							{
								//上と下のボクセルのフラグの値をかけて大きい方を分割する
								Left_Up = (block[x][y][z-1].flag) * (block[x][y][z+1].flag);
								Right_Down =  (block[x+1][y+1][z-1].flag) * (block[x+1][y+1][z+1].flag);
								if(Left_Up > Right_Down)
								{
									ID12++;
									block[x][y][z].flag = 1;
									block[x][y+1][z].flag = 2;							block[x][y+1][z].ID = ID12; 
									block[x+1][y+1][z].flag = 2; 						block[x+1][y+1][z].ID = ID12; 
									num11++;
									num12++;
								}
								else
								{
									ID12++;
									block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
									block[x][y+1][z].flag = 2;				block[x][y+1][z].ID = ID12; 
									block[x+1][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
					}
					//注目ボクセルのIDが0になる場合
					else if(block[x][y][z].flag == 0 )
					{
						if(block[x][y+1][z].flag == 3)			//ケース１
						{
							countLN++;
							if( (block[x+1][y][z-1].flag > 3 ||  block[x+1][y][z+1].flag > 3) && block[x][y+1][z-1].flag < 4 &&  block[x][y+1][z+1].flag < 4)
							{
								ID12++;
								block[x+1][y+1][z].flag = 2;					block[x+1][y+1][z].ID = ID12;
								block[x+1][y][z].flag = 1; 
								block[x][y+1][z].flag = 2; 					block[x][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							else if(block[x+1][y][z-1].flag < 4 &&  block[x+1][y][z+1].flag < 4 && (block[x][y+1][z-1].flag > 3 ||  block[x][y+1][z+1].flag > 3) )
							{
								ID12++;
								block[x+1][y+1][z].flag = 2;				block[x+1][y+1][z].ID = ID12;
								block[x+1][y][z].flag = 2; 					block[x+1][y][z].ID = ID12; 
								block[x][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							else if( block[x+1][y][z-1].flag < 2 && block[x+1][y][z+1].flag < 2 && block[x][y+1][z-1].flag < 2 &&  block[x][y+1][z+1].flag < 2)
							{
								ID22++;
								count++;
								num22++;
								//２×２に無理やり変えますよんんんん〜
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x][y][z].fill = true;
								cout<<"分割できなかったから2×2に変えたぞ！"<<x<<" "<<y<<" "<<z<<endl;
							}
							else
							{
								//上と下のボクセルのフラグの値をかけて大きい方を分割する
								Left_Down = (block[x+1][y][z-1].flag) * (block[x+1][y][z+1].flag);
								Right_Up =  (block[x][y+1][z-1].flag) * (block[x][y+1][z+1].flag);
								if(Left_Down > Right_Up)
								{
									ID12++;
									block[x+1][y+1][z].flag = 2;					block[x+1][y+1][z].ID = ID12;
									block[x+1][y][z].flag = 1; 
									block[x][y+1][z].flag = 2; 						block[x][y+1][z].ID = ID12; 
									num11++;
									num12++;
								}
								else
								{
									ID12++;
									block[x+1][y+1][z].flag = 2;					block[x+1][y+1][z].ID = ID12;
									block[x+1][y][z].flag = 2; 						block[x+1][y][z].ID = ID12; 
									block[x][y+1][z].flag = 1; 
									num11++;
									num12++;
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
			for(x=0; x < VoxSize[0]-1; x=x+2)
			{
				for(y=0; y < VoxSize[1]-1; y=y+2)
				{
					//注目ボクセルのIDが３になる場合
					if(block[x][y][z].flag == 3)
					{
						//                                                                                                                                
						//ケース２
						if(block[x][y+1][z].flag == 0)
						{
							countLN++;
							//一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							if( (block[x][y][z-1].flag > 3 || block[x][y][z+1].flag > 3) &&  block[x+1][y+1][z-1].flag < 4 && block[x+1][y+1][z+1].flag < 4 )
							{
								ID12++;
								block[x][y][z].flag = 1;
								block[x+1][y][z].flag = 2;			block[x+1][y][z].ID = ID12; 
								block[x+1][y+1][z].flag = 2;		block[x+1][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//もう一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							else if( block[x][y][z-1].flag < 4 && block[x][y][z+1].flag < 4 && ( block[x+1][y+1][z-1].flag > 3 || block[x+1][y+1][z+1].flag > 3))
							{
								ID12++;
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 2;			block[x+1][y][z].ID = ID12; 
								block[x+1][y+1][z].flag = 1;		block[x+1][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//注目の２つのボクセルの上下（４つ）ともに１×１以下のボクセルであるとき
							else if(block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2)
							{
								ID22++;
								count++;
								num22++;
								//２×２に無理やり変えますよんんんん〜
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x][y+1][z].fill = true;
								cout<<"分割できなかったから2×2に変えたぞ！"<<x<<" "<<y<<" "<<z<<endl;
							}
							//上記以外の時は
							else
							{
								//上と下のボクセルのフラグの値をかけて大きい方を分割する
								Left_Up = (block[x][y][z-1].flag) * (block[x][y][z+1].flag);
								Right_Down =  (block[x+1][y+1][z-1].flag) * (block[x+1][y+1][z+1].flag);
								if(Left_Up > Right_Down)
								{
									ID12++;
									block[x][y][z].flag = 1;
									block[x+1][y][z].flag = 2;					block[x+1][y][z].ID = ID12; 
									block[x+1][y+1][z].flag = 2;				block[x+1][y+1][z].ID = ID12; 
									num11++;
									num12++;
								}
								else
								{
									ID12++;
									block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
									block[x+1][y][z].flag = 2;				block[x+1][y][z].ID = ID12; 
									block[x+1][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
						//						                                                                                                                                
						//ケース３
						else if(block[x+1][y+1][z].flag == 0)
						{
							countLN++;
							//一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							if( (block[x+1][y][z-1].flag >3  ||  block[x+1][y][z+1].flag > 3) && block[x][y+1][z-1].flag < 4 &&  block[x][y+1][z+1].flag < 4 )
							{
								ID12++;
								block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
								block[x+1][y][z].flag = 1; 
								block[x][y+1][z].flag = 2;				block[x][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//もう一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							else if( block[x+1][y][z-1].flag < 4  &&  block[x+1][y][z+1].flag < 4 && (block[x][y+1][z-1].flag > 3 &&  block[x][y+1][z+1].flag > 3) )
							{
								ID12++;
								block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
								block[x+1][y][z].flag = 2; 				block[x+1][y][z].ID = ID12; 
								block[x][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//注目の２つのボクセルの上下（４つ）ともに１×１以下のボクセルであるとき
							else if(block[x+1][y][z-1].flag < 2 &&  block[x+1][y][z+1].flag < 2 && block[x][y+1][z-1].flag < 2 &&  block[x][y+1][z+1].flag < 2 )
							{
								ID22++;
								count++;
								num22++;
								//２×２に無理やり変えますよんんんん〜
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x+1][y+1][z].fill = true;
								cout<<"分割できなかったから2×2に変えたぞ！"<<x<<" "<<y<<" "<<z<<endl;
							}
							//上記以外の時は
							else
							{
								Left_Down = (block[x+1][y][z-1].flag) * (block[x+1][y][z+1].flag);
								Right_Up =  (block[x][y+1][z-1].flag) * (block[x][y+1][z+1].flag);
								if(Left_Down > Right_Up)
								{
									ID12++;
									block[x][y][z].flag = 2;						block[x][y][z].ID = ID12;
									block[x+1][y][z].flag = 1; 
									block[x][y+1][z].flag = 2;					block[x][y+1][z].ID = ID12; 
									num11++;
									num12++;
								}
								else
								{
									ID12++;
									block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
									block[x+1][y][z].flag = 2; 				block[x+1][y][z].ID = ID12; 
									block[x][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
						//                                                                                                     
						//ケース４
						else if(block[x+1][y][z].flag == 0)
						{
							countLN++;
							//一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							if( (block[x][y][z-1].flag > 3 ||  block[x][y][z+1].flag > 3) && block[x+1][y+1][z-1].flag < 4 &&  block[x+1][y+1][z+1].flag < 4 )
							{
								ID12++;
								block[x][y][z].flag = 1;
								block[x][y+1][z].flag = 2; 				block[x][y+1][z].ID = ID12; 
								block[x+1][y+1][z].flag = 2;			block[x+1][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//もう一方のボクセルの上または下にのみ２×２があったらそれを１×１にする
							else if( block[x][y][z-1].flag < 4 &&  block[x][y][z+1].flag < 4 && (block[x+1][y+1][z-1].flag > 3 ||  block[x+1][y+1][z+1].flag > 3) )
							{
								ID12++;
								block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
								block[x][y+1][z].flag = 2;				block[x][y+1][z].ID = ID12; 
								block[x+1][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//注目ボクセルの上下4つともに１×１または何もない場合
							else if( block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2 )
							{
								ID22++;
								count++;
								num22++;
								//２×２に無理やり変えますよんんんん〜
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x+1][y][z].fill = true;
								cout<<"分割できなかったから2×2に変えたぞ！"<<x<<" "<<y<<" "<<z<<endl;
							}
							//上記以外の場合
							else
							{
								//上と下のボクセルのフラグの値をかけて大きい方を分割する
								Left_Up = (block[x][y][z-1].flag) * (block[x][y][z+1].flag);
								Right_Down =  (block[x+1][y+1][z-1].flag) * (block[x+1][y+1][z+1].flag);
								if(Left_Up > Right_Down)
								{
									ID12++;
									block[x][y][z].flag = 1;
									block[x][y+1][z].flag = 2;							block[x][y+1][z].ID = ID12; 
									block[x+1][y+1][z].flag = 2; 						block[x+1][y+1][z].ID = ID12; 
									num11++;
									num12++;
								}
								else
								{
									ID12++;
									block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
									block[x][y+1][z].flag = 2;				block[x][y+1][z].ID = ID12; 
									block[x+1][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
					}
					//注目ボクセルのIDが0になる場合
					else if(block[x][y][z].flag == 0 )
					{
						if(block[x][y+1][z].flag == 3)			//ケース１
						{
							countLN++;
							if( (block[x+1][y][z-1].flag > 3 ||  block[x+1][y][z+1].flag > 3) && block[x][y+1][z-1].flag < 4 &&  block[x][y+1][z+1].flag < 4)
							{
								ID12++;
								block[x+1][y+1][z].flag = 2;					block[x+1][y+1][z].ID = ID12;
								block[x+1][y][z].flag = 1; 
								block[x][y+1][z].flag = 2; 					block[x][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							else if(block[x+1][y][z-1].flag < 4 &&  block[x+1][y][z+1].flag < 4 && (block[x][y+1][z-1].flag > 3 ||  block[x][y+1][z+1].flag > 3) )
							{
								ID12++;
								block[x+1][y+1][z].flag = 2;				block[x+1][y+1][z].ID = ID12;
								block[x+1][y][z].flag = 2; 					block[x+1][y][z].ID = ID12; 
								block[x][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							else if( block[x+1][y][z-1].flag < 2 && block[x+1][y][z+1].flag < 2 && block[x][y+1][z-1].flag < 2 &&  block[x][y+1][z+1].flag < 2)
							{
								ID22++;
								count++;
								num22++;
								//２×２に無理やり変えますよんんんん〜
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x][y][z].fill = true;
								cout<<"分割できなかったから2×2に変えたぞ！"<<x<<" "<<y<<" "<<z<<endl;
							}
							else
							{
								//上と下のボクセルのフラグの値をかけて大きい方を分割する
								Left_Down = (block[x+1][y][z-1].flag) * (block[x+1][y][z+1].flag);
								Right_Up =  (block[x][y+1][z-1].flag) * (block[x][y+1][z+1].flag);
								if(Left_Down > Right_Up)
								{
									ID12++;
									block[x+1][y+1][z].flag = 2;					block[x+1][y+1][z].ID = ID12;
									block[x+1][y][z].flag = 1; 
									block[x][y+1][z].flag = 2; 						block[x][y+1][z].ID = ID12; 
									num11++;
									num12++;
								}
								else
								{
									ID12++;
									block[x+1][y+1][z].flag = 2;					block[x+1][y+1][z].ID = ID12;
									block[x+1][y][z].flag = 2; 						block[x+1][y][z].ID = ID12; 
									block[x][y+1][z].flag = 1; 
									num11++;
									num12++;
								}
							}
						}
					}
				}
			}
		}
	}

	cout<<countLN<<"個中　"<<count<<" 個のLを１×１と１×２に分割できなかった！"<<endl;
	//outputFlag("test00_L_to11_12.txt", VoxSize);

}

