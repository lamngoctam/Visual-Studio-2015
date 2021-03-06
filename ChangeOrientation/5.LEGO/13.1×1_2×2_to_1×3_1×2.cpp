#include "../stdafx.h"
#include "../Voxel.h"
#include "../Lego.h"		//LEGOブロックを組み立てるためのクラス

extern int ID12;			
extern int ID13;

extern int num11;
extern int num12;
extern int num13;
extern int num22;

void outputFlag(string filename, int* size);

//２×２の周辺８マスを見て、そこに１×１があり、かつ１×３と１×２に分割しても問題ない場合は分割する
void Small_to_Big_step3(Lego*** block, int*  VoxSize)
{
	int count(0);
	int x,y,z;
	for(z = 1; z<VoxSize[2]-1; z++)
	{
		//奇数層
		if(z%2)
		{
			for(x = 1; x<VoxSize[0]-1; x=x+2)
			{
				for(y = 1; y<VoxSize[1]-1; y=y+2)
				{
					//注目の２×２のマスクのフラグが４を示していたら
					if(block[x][y][z].flag == 4 && block[x+1][y+1][z].flag == 4)
					{
						//上の左
						if(block[x-1][y][z].flag == 1)
						{
							//1の上下のボクセルのflagがともに１または０ならば(ここの判定をそこまで厳しくしなくてもいいかもしれない？)
							if(block[x-1][y][z-1].flag < 2 && block[x-1][y][z+1].flag < 2 )
							{
								if(block[x+2][y][z].flag > 1 && block[x+2][y+1][z].flag > 1)	//flagの値が2以上であれば
								{
									if( (block[x+1][y][z-1].flag > 1 &&  block[x+2][y][z-1].flag > 1 ) || (block[x+1][y][z+1].flag > 1  && block[x+2][y][z+1].flag > 1) )
									{
										if( (block[x+1][y+1][z-1].flag > 1 && block[x+2][y+1][z-1].flag > 1) || (block[x+1][y+1][z+1].flag > 1 && block[x+2][y+1][z+1].flag > 1 ))
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y+1][z].flag = 12;			block[x][y+1][z].ID = ID12;			block[x][y+1][z].corner = 1;
											block[x+1][y+1][z].flag = 12;		block[x+1][y+1][z].ID = ID12;		block[x+1][y+1][z].corner = 2;	
											block[x-1][y][z].flag = 13;				block[x-1][y][z].ID = ID13;			block[x-1][y][z].corner = 1;
											block[x][y][z].flag = 13;					block[x][y][z].ID = ID13;	
											block[x+1][y][z].flag = 13;			block[x+1][y][z].ID = ID13;			block[x+1][y][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//上の右
						if(block[x-1][y+1][z].flag == 1)
						{
							if(block[x-1][y+1][z-1].flag < 2 && block[x-1][y+1][z+1].flag < 2 )
							{
								if(block[x+2][y][z].flag > 1 && block[x+2][y+1][z].flag > 1)
								{
									if( (block[x+1][y][z-1].flag > 1 &&  block[x+2][y][z-1].flag > 1 ) || (block[x+1][y][z+1].flag > 1  && block[x+2][y][z+1].flag > 1) )
									{
										if( (block[x+1][y+1][z-1].flag > 1 && block[x+2][y+1][z-1].flag > 1) || (block[x+1][y+1][z+1].flag > 1 && block[x+2][y+1][z+1].flag > 1 ))
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;										
											block[x-1][y+1][z].flag = 13;			block[x-1][y+1][z].ID = ID13;		block[x-1][y+1][z].corner = 1;
											block[x][y+1][z].flag = 13;			block[x][y+1][z].ID = ID13;
											block[x+1][y+1][z].flag = 13;		block[x+1][y+1][z].ID = ID13;		block[x+1][y+1][z].corner = 2;	
											block[x][y][z].flag = 12;					block[x][y][z].ID = ID12;				block[x][y][z].corner = 1;
											block[x+1][y][z].flag = 12;			block[x+1][y][z].ID = ID12;			block[x+1][y][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//左の上
						if(block[x][y-1][z].flag == 1)
						{
							if(block[x][y-1][z-1].flag < 2 && block[x][y-1][z+1].flag < 2 )
							{
								if(block[x][y+2][z].flag > 1 && block[x+1][y+2][z].flag > 1)
								{
									if( (block[x][y+1][z-1].flag > 1 && block[x][y+2][z-1].flag > 1 ) || (block[x][y+1][z+1].flag > 1 && block[x][y+2][z+1].flag > 1) )
									{
										if((block[x+1][y+1][z-1].flag > 1 && block[x+1][y+2][z-1].flag > 1) || (block[x+1][y+1][z+1].flag > 1 && block[x+1][y+2][z+1].flag > 1))
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y-1][z].flag = 13;			block[x][y-1][z].ID = ID13;		block[x][y-1][z].corner = 1;
											block[x][y][z].flag = 13;				block[x][y][z].ID = ID13;
											block[x][y+1][z].flag = 13;		block[x][y+1][z].ID = ID13;		block[x][y+1][z].corner = 2;	
											block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 1;	
											block[x+1][y+1][z].flag = 12;	block[x+1][y+1][z].ID = ID12;	block[x+1][y+1][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//左の下
						if(block[x+1][y-1][z].flag == 1)
						{
							if(block[x+1][y-1][z-1].flag < 2 && block[x+1][y-1][z+1].flag < 2 )
							{
								if(block[x][y+2][z].flag > 1 && block[x+1][y+2][z].flag > 1)
								{
									if( (block[x][y+1][z-1].flag > 1 && block[x][y+2][z-1].flag > 1 ) || (block[x][y+1][z+1].flag > 1 && block[x][y+2][z+1].flag > 1) )
									{
										if((block[x+1][y+1][z-1].flag > 1 && block[x+1][y+2][z-1].flag > 1) || (block[x+1][y+1][z+1].flag > 1 && block[x+1][y+2][z+1].flag > 1))
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y][z].flag = 12;				block[x][y][z].ID = ID12;			block[x][y][z].corner = 1;
											block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;		block[x][y+1][z].corner = 2;	
											block[x+1][y-1][z].flag = 13;		block[x+1][y-1][z].ID = ID13;	block[x+1][y-1][z].corner = 1;
											block[x+1][y][z].flag = 13;		block[x+1][y][z].ID = ID13;	
											block[x+1][y+1][z].flag = 13;	block[x+1][y+1][z].ID = ID13;	block[x+1][y+1][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//下の左
						if(block[x+2][y][z].flag == 1)
						{
							if(block[x+2][y][z-1].flag < 2 && block[x+2][y][z+1].flag < 2 )
							{
								if(block[x-1][y][z].flag > 1 && block[x-1][y+1][z].flag > 1)
								{
									if( (block[x-1][y][z-1].flag > 1 && block[x][y][z-1].flag > 1) || (block[x-1][y][z+1].flag > 1 && block[x][y][z+1].flag > 1) )
									{
										if( ( block[x-1][y+1][z-1].flag > 1 && block[x][y+1][z-1].flag > 1) || (block[x-1][y+1][z+1].flag > 1 && block[x][y+1][z+1].flag > 1) )
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y+1][z].flag = 12;			block[x][y+1][z].ID = ID12;		block[x][y+1][z].corner = 1;
											block[x+1][y+1][z].flag = 12;		block[x+1][y+1][z].ID = ID12;	block[x+1][y+1][z].corner = 2;	
											block[x][y][z].flag = 13;					block[x][y][z].ID = ID13;			block[x][y][z].corner = 1;	
											block[x+1][y][z].flag = 13;			block[x+1][y][z].ID = ID13;
											block[x+2][y][z].flag = 13;			block[x+2][y][z].ID = ID13;		block[x+2][y][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//下の右
						if(block[x+2][y+1][z].flag == 1)
						{
							if(block[x+2][y+1][z-1].flag < 2 && block[x+2][y+1][z+1].flag < 2 )
							{
								if(block[x-1][y][z].flag > 1 && block[x-1][y+1][z].flag > 1)
								{
									if( (block[x-1][y][z-1].flag > 1 && block[x][y][z-1].flag > 1) || (block[x-1][y][z+1].flag > 1 && block[x][y][z+1].flag > 1) )
									{
										if( ( block[x-1][y+1][z-1].flag > 1 && block[x][y+1][z-1].flag > 1) || (block[x-1][y+1][z+1].flag > 1 && block[x][y+1][z+1].flag > 1) )
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y+1][z].flag = 13;			block[x][y+1][z].ID = ID13;		block[x][y+1][z].corner = 1;
											block[x+1][y+1][z].flag = 13;		block[x+1][y+1][z].ID = ID13;	
											block[x+2][y+1][z].flag = 13;		block[x+2][y+1][z].ID = ID13;	block[x+2][y+1][z].corner = 2;
											block[x][y][z].flag = 12;					block[x][y][z].ID = ID12;			block[x][y][z].corner = 1;	
											block[x+1][y][z].flag = 12;			block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}

						//右の上
						if(block[x][y+2][z].flag == 1)
						{
							if(block[x][y+2][z-1].flag < 2 && block[x][y+2][z+1].flag < 2 )
							{
								if(block[x][y-1][z].flag > 1 && block[x+1][y-1][z].flag > 1)
								{
									if( (block[x][y-1][z-1].flag > 1 && block[x][y][z-1].flag > 1) || (block[x][y-1][z+1].flag > 1 && block[x][y][z+1].flag > 1) )
									{
										if( (block[x+1][y-1][z-1].flag > 1 && block[x+1][y][z-1].flag > 1 ) || ( block[x+1][y-1][z+1].flag > 1 && block[x+1][y][z+1].flag > 1 ) )
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y][z].flag = 13;				block[x][y][z].ID = ID13;			block[x][y][z].corner = 1;
											block[x][y+1][z].flag = 13;		block[x][y+1][z].ID = ID13;
											block[x][y+2][z].flag = 13;		block[x][y+2][z].ID = ID13;		block[x][y+2][z].corner = 2;	
											block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 1;
											block[x+1][y+1][z].flag = 12;	block[x+1][y+1][z].ID = ID12;	block[x+1][y+1][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//右の下
						if(block[x+1][y+2][z].flag == 1)
						{
							if(block[x+1][y+2][z-1].flag < 2 && block[x+1][y+2][z+1].flag < 2 )
							{
								if(block[x][y-1][z].flag > 1 && block[x+1][y-1][z].flag > 1)
								{
									if( (block[x][y-1][z-1].flag > 1 && block[x][y][z-1].flag > 1) || (block[x][y-1][z+1].flag > 1 && block[x][y][z+1].flag > 1) )
									{
										if( (block[x+1][y-1][z-1].flag > 1 && block[x+1][y][z-1].flag > 1 ) || ( block[x+1][y-1][z+1].flag > 1 && block[x+1][y][z+1].flag > 1 ) )
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y][z].flag = 12;				block[x][y][z].ID = ID12;			block[x][y][z].corner = 1;
											block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;		block[x][y+1][z].corner = 2;	
											block[x+1][y][z].flag = 13;		block[x+1][y][z].ID = ID13;		block[x+1][y][z].corner = 1;
											block[x+1][y+1][z].flag = 13;	block[x+1][y+1][z].ID = ID13;	
											block[x+1][y+2][z].flag = 13;	block[x+1][y+2][z].ID = ID13;	block[x+1][y+2][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
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
			for(x = 0; x<VoxSize[0]-1; x=x+2)
			{
				for(y = 0; y<VoxSize[1]-1; y=y+2)
				{
					//注目の２×２のマスクのフラグが４を示していたら
					if(block[x][y][z].flag == 4 && block[x+1][y+1][z].flag == 4)
					{
						//上の左
						if(block[x-1][y][z].flag == 1)
						{
							//1の上下のボクセルのflagがともに１または０ならば(ここの判定をそこまで厳しくしなくてもいいかもしれない？)
							if(block[x-1][y][z-1].flag < 2 && block[x-1][y][z+1].flag < 2 )
							{
								if(block[x+2][y][z].flag > 1 && block[x+2][y+1][z].flag > 1)	//flagの値が2以上であれば
								{
									if( (block[x+1][y][z-1].flag > 1 &&  block[x+2][y][z-1].flag > 1 ) || (block[x+1][y][z+1].flag > 1  && block[x+2][y][z+1].flag > 1) )
									{
										if( (block[x+1][y+1][z-1].flag > 1 && block[x+2][y+1][z-1].flag > 1) || (block[x+1][y+1][z+1].flag > 1 && block[x+2][y+1][z+1].flag > 1 ))
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y+1][z].flag = 12;			block[x][y+1][z].ID = ID12;			block[x][y+1][z].corner = 1;
											block[x+1][y+1][z].flag = 12;		block[x+1][y+1][z].ID = ID12;		block[x+1][y+1][z].corner = 2;	
											block[x-1][y][z].flag = 13;				block[x-1][y][z].ID = ID13;			block[x-1][y][z].corner = 1;
											block[x][y][z].flag = 13;					block[x][y][z].ID = ID13;	
											block[x+1][y][z].flag = 13;			block[x+1][y][z].ID = ID13;			block[x+1][y][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//上の右
						if(block[x-1][y+1][z].flag == 1)
						{
							if(block[x-1][y+1][z-1].flag < 2 && block[x-1][y+1][z+1].flag < 2 )
							{
								if(block[x+2][y][z].flag > 1 && block[x+2][y+1][z].flag > 1)
								{
									if( (block[x+1][y][z-1].flag > 1 &&  block[x+2][y][z-1].flag > 1 ) || (block[x+1][y][z+1].flag > 1  && block[x+2][y][z+1].flag > 1) )
									{
										if( (block[x+1][y+1][z-1].flag > 1 && block[x+2][y+1][z-1].flag > 1) || (block[x+1][y+1][z+1].flag > 1 && block[x+2][y+1][z+1].flag > 1 ))
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x-1][y+1][z].flag = 13;			block[x-1][y+1][z].ID = ID13;		block[x-1][y+1][z].corner = 1;
											block[x][y+1][z].flag = 13;			block[x][y+1][z].ID = ID13;
											block[x+1][y+1][z].flag = 13;		block[x+1][y+1][z].ID = ID13;		block[x+1][y+1][z].corner = 2;	
											block[x][y][z].flag = 12;					block[x][y][z].ID = ID12;				block[x][y][z].corner = 1;
											block[x+1][y][z].flag = 12;			block[x+1][y][z].ID = ID12;			block[x+1][y][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//左の上
						if(block[x][y-1][z].flag == 1)
						{
							if(block[x][y-1][z-1].flag < 2 && block[x][y-1][z+1].flag < 2 )
							{
								if(block[x][y+2][z].flag > 1 && block[x+1][y+2][z].flag > 1)
								{
									if( (block[x][y+1][z-1].flag > 1 && block[x][y+2][z-1].flag > 1 ) || (block[x][y+1][z+1].flag > 1 && block[x][y+2][z+1].flag > 1) )
									{
										if((block[x+1][y+1][z-1].flag > 1 && block[x+1][y+2][z-1].flag > 1) || (block[x+1][y+1][z+1].flag > 1 && block[x+1][y+2][z+1].flag > 1))
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y-1][z].flag = 13;			block[x][y-1][z].ID = ID13;		block[x][y-1][z].corner = 1;
											block[x][y][z].flag = 13;				block[x][y][z].ID = ID13;
											block[x][y+1][z].flag = 13;		block[x][y+1][z].ID = ID13;		block[x][y+1][z].corner = 2;	
											block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 1;	
											block[x+1][y+1][z].flag = 12;	block[x+1][y+1][z].ID = ID12;	block[x+1][y+1][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//左の下
						if(block[x+1][y-1][z].flag == 1)
						{
							if(block[x+1][y-1][z-1].flag < 2 && block[x+1][y-1][z+1].flag < 2 )
							{
								if(block[x][y+2][z].flag > 1 && block[x+1][y+2][z].flag > 1)
								{
									if( (block[x][y+1][z-1].flag > 1 && block[x][y+2][z-1].flag > 1 ) || (block[x][y+1][z+1].flag > 1 && block[x][y+2][z+1].flag > 1) )
									{
										if((block[x+1][y+1][z-1].flag > 1 && block[x+1][y+2][z-1].flag > 1) || (block[x+1][y+1][z+1].flag > 1 && block[x+1][y+2][z+1].flag > 1))
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y][z].flag = 12;				block[x][y][z].ID = ID12;			block[x][y][z].corner = 1;
											block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;		block[x][y+1][z].corner = 2;	
											block[x+1][y-1][z].flag = 13;		block[x+1][y-1][z].ID = ID13;	block[x+1][y-1][z].corner = 1;
											block[x+1][y][z].flag = 13;		block[x+1][y][z].ID = ID13;	
											block[x+1][y+1][z].flag = 13;	block[x+1][y+1][z].ID = ID13;	block[x+1][y+1][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//下の左
						if(block[x+2][y][z].flag == 1)
						{
							if(block[x+2][y][z-1].flag < 2 && block[x+2][y][z+1].flag < 2 )
							{
								if(block[x-1][y][z].flag > 1 && block[x-1][y+1][z].flag > 1)
								{
									if( (block[x-1][y][z-1].flag > 1 && block[x][y][z-1].flag > 1) || (block[x-1][y][z+1].flag > 1 && block[x][y][z+1].flag > 1) )
									{
										if( ( block[x-1][y+1][z-1].flag > 1 && block[x][y+1][z-1].flag > 1) || (block[x-1][y+1][z+1].flag > 1 && block[x][y+1][z+1].flag > 1) )
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y+1][z].flag = 12;			block[x][y+1][z].ID = ID12;		block[x][y+1][z].corner = 1;
											block[x+1][y+1][z].flag = 12;		block[x+1][y+1][z].ID = ID12;	block[x+1][y+1][z].corner = 2;	
											block[x][y][z].flag = 13;					block[x][y][z].ID = ID13;			block[x][y][z].corner = 1;	
											block[x+1][y][z].flag = 13;			block[x+1][y][z].ID = ID13;
											block[x+2][y][z].flag = 13;			block[x+2][y][z].ID = ID13;		block[x+2][y][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//下の右
						if(block[x+2][y+1][z].flag == 1)
						{
							if(block[x+2][y+1][z-1].flag < 2 && block[x+2][y+1][z+1].flag < 2 )
							{
								if(block[x-1][y][z].flag > 1 && block[x-1][y+1][z].flag > 1)
								{
									if( (block[x-1][y][z-1].flag > 1 && block[x][y][z-1].flag > 1) || (block[x-1][y][z+1].flag > 1 && block[x][y][z+1].flag > 1) )
									{
										if( ( block[x-1][y+1][z-1].flag > 1 && block[x][y+1][z-1].flag > 1) || (block[x-1][y+1][z+1].flag > 1 && block[x][y+1][z+1].flag > 1) )
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y+1][z].flag = 13;			block[x][y+1][z].ID = ID13;		block[x][y+1][z].corner = 1;
											block[x+1][y+1][z].flag = 13;		block[x+1][y+1][z].ID = ID13;	
											block[x+2][y+1][z].flag = 13;		block[x+2][y+1][z].ID = ID13;	block[x+2][y+1][z].corner = 2;
											block[x][y][z].flag = 12;					block[x][y][z].ID = ID12;			block[x][y][z].corner = 1;	
											block[x+1][y][z].flag = 12;			block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}

						//右の上
						if(block[x][y+2][z].flag == 1)
						{
							if(block[x][y+2][z-1].flag < 2 && block[x][y+2][z+1].flag < 2 )
							{
								if(block[x][y-1][z].flag > 1 && block[x+1][y-1][z].flag > 1)
								{
									if( (block[x][y-1][z-1].flag > 1 && block[x][y][z-1].flag > 1) || (block[x][y-1][z+1].flag > 1 && block[x][y][z+1].flag > 1) )
									{
										if( (block[x+1][y-1][z-1].flag > 1 && block[x+1][y][z-1].flag > 1 ) || ( block[x+1][y-1][z+1].flag > 1 && block[x+1][y][z+1].flag > 1 ) )
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y][z].flag = 13;				block[x][y][z].ID = ID13;			block[x][y][z].corner = 1;
											block[x][y+1][z].flag = 13;		block[x][y+1][z].ID = ID13;
											block[x][y+2][z].flag = 13;		block[x][y+2][z].ID = ID13;		block[x][y+2][z].corner = 2;	
											block[x+1][y][z].flag = 12;		block[x+1][y][z].ID = ID12;		block[x+1][y][z].corner = 1;
											block[x+1][y+1][z].flag = 12;	block[x+1][y+1][z].ID = ID12;	block[x+1][y+1][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
						//右の下
						if(block[x+1][y+2][z].flag == 1)
						{
							if(block[x+1][y+2][z-1].flag < 2 && block[x+1][y+2][z+1].flag < 2 )
							{
								if(block[x][y-1][z].flag > 1 && block[x+1][y-1][z].flag > 1)
								{
									if( (block[x][y-1][z-1].flag > 1 && block[x][y][z-1].flag > 1) || (block[x][y-1][z+1].flag > 1 && block[x][y][z+1].flag > 1) )
									{
										if( (block[x+1][y-1][z-1].flag > 1 && block[x+1][y][z-1].flag > 1 ) || ( block[x+1][y-1][z+1].flag > 1 && block[x+1][y][z+1].flag > 1 ) )
										{
											count++;
											ID12++;
											ID13++;
											num12++;
											num13++;
											num11--;
											num22--;
											block[x][y][z].flag = 12;				block[x][y][z].ID = ID12;			block[x][y][z].corner = 1;
											block[x][y+1][z].flag = 12;		block[x][y+1][z].ID = ID12;		block[x][y+1][z].corner = 2;	
											block[x+1][y][z].flag = 13;		block[x+1][y][z].ID = ID13;		block[x+1][y][z].corner = 1;
											block[x+1][y+1][z].flag = 13;	block[x+1][y+1][z].ID = ID13;	
											block[x+1][y+2][z].flag = 13;	block[x+1][y+2][z].ID = ID13;	block[x+1][y+2][z].corner = 2;
											cout<<x<<","<<y<<","<<z<<endl;
											continue;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	cout<<count<<"個の１×１と２×２から１×３と１×２ができた！"<<endl;
	//outputFlag("test03_11_22_to_13_12.txt", VoxSize);

}