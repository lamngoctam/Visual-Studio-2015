#include "../stdafx.h"
#include "../Voxel.h"
#include "../Lego.h"		//LEGOブロックを組み立てるためのクラス


extern int ID12;
extern int ID22;
extern int ID24;

extern int num22;		//２×２のブロックの数
extern int num24;		//２×４のブロックの数

void outputFlag(string filename, int* size);

//２×２　と２×２から２×４を合成
void Small_to_Big_step7(Lego*** block, int*  VoxSize)
{
	int x,y,z;
	//奇数層
	for(z=1; z < VoxSize[2]-1; z=z+2 )				//ｚ＝1,3,5,...
	{
		for(x=1; x < VoxSize[0]-1; x=x+2)
		{
			for(y=1; y < VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag == 4)
				{
					//ｙ軸方向に同じ２×２があれば２×４に置き換える
					if(block[x][y+2][z].flag == 4)
					{
						ID24++;
						num22 = num22 - 2;
						num24++;
						for(int i(0); i<2; i++)
						{
							for(int k(0); k<4; k++)
							{
								block[x+i][y+k][z].flag = 24;
								block[x+i][y+k][z].ID = ID24;
							}
						}
						block[x][y][z].corner  = 1;
						block[x+1][y+3][z].corner  = 2;
						continue;
					}

					//ｘ軸方向に同じ２×２があれば２×４に置き換える
					if(block[x+2][y][z].flag == 4)
					{
						ID24++;
						num22 = num22 - 2;
						num24++;
						for(int i(0); i<4; i++)
						{				
							for(int k(0); k<2; k++)
							{	
								block[x+i][y+k][z].flag = 24;
								block[x+i][y+k][z].ID = ID24;
							}
						}
						block[x][y][z].corner  = 1;
						block[x+3][y+1][z].corner  = 2;
					}

				}
			}
		}
	}

	//偶数層
	for(z=2; z < VoxSize[2]-1; z=z+2 )				//ｚ＝2,4,6,...
	{	
		for(x=0; x < VoxSize[0]-1; x=x+2)
		{
			for(y=0; y < VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag == 4)
				{
					//ｙ軸方向に同じ２×２があれば２×４に置き換える
					if(block[x][y+2][z].flag == 4)
					{
						ID24++;
						num22 = num22 - 2;
						num24++;
						for(int i(0); i<2; i++)
						{
							for(int k(0); k<4; k++)
							{
								block[x+i][y+k][z].flag = 24;
								block[x+i][y+k][z].ID = ID24;
							}
						}
						block[x][y][z].corner  = 1;
						block[x+1][y+3][z].corner  = 2;
						continue;
					}

					//ｘ軸方向に同じ２×２があれば２×４に置き換える
					if(block[x+2][y][z].flag == 4)
					{
						ID24++;
						num22 = num22 - 2;
						num24++;
						for(int i(0); i<4; i++)
						{				
							for(int k(0); k<2; k++)
							{	
								block[x+i][y+k][z].flag = 24;
								block[x+i][y+k][z].ID = ID24;
							}
						}
						block[x][y][z].corner  = 1;
						block[x+3][y+1][z].corner  = 2;
					}

				}
			}
		}
	}
	outputFlag("test07_22_to_24.txt", VoxSize);

}

void Small_to_Big_step7_color(Lego*** block, int*  VoxSize)
{
	int x,y,z;
	//奇数層
	for(z=1; z < VoxSize[2]-1; z=z+2 )				//ｚ＝1,3,5,...
	{
		for(x=1; x < VoxSize[0]-1; x=x+2)
		{
			for(y=1; y < VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag == 4)
				{
					//ｙ軸方向に同じ２×２があれば２×４に置き換える
					if(block[x][y+2][z].flag == 4)
					{
						if(block[x][y][z].ColorID == block[x][y+2][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y+2][z].ColorID < 1)
						{
							ID24++;
							num22 = num22 - 2;
							num24++;
							for(int i(0); i<2; i++)
							{
								for(int k(0); k<4; k++)
								{
									block[x+i][y+k][z].flag = 24;
									block[x+i][y+k][z].ID = ID24;
								}
							}
							block[x][y][z].corner  = 1;
							block[x+1][y+3][z].corner  = 2;
							continue;
						}
					}

					//ｘ軸方向に同じ２×２があれば２×４に置き換える
					if(block[x+2][y][z].flag == 4)
					{
						if(block[x][y][z].ColorID == block[x+2][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x+2][y][z].ColorID < 1)
						{
							ID24++;
							num22 = num22 - 2;
							num24++;
							for(int i(0); i<4; i++)
							{				
								for(int k(0); k<2; k++)
								{	
									block[x+i][y+k][z].flag = 24;
									block[x+i][y+k][z].ID = ID24;
								}
							}
							block[x][y][z].corner  = 1;
							block[x+3][y+1][z].corner  = 2;
						}
					}
				}
			}
		}
	}

	//偶数層
	for(z=2; z < VoxSize[2]-1; z=z+2 )				//ｚ＝2,4,6,...
	{	
		for(x=0; x < VoxSize[0]-1; x=x+2)
		{
			for(y=0; y < VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag == 4)
				{
					//ｙ軸方向に同じ２×２があれば２×４に置き換える
					if(block[x][y+2][z].flag == 4)
					{
						if(block[x][y][z].ColorID == block[x][y+2][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y+2][z].ColorID < 1)
						{
							ID24++;
							num22 = num22 - 2;
							num24++;
							for(int i(0); i<2; i++)
							{
								for(int k(0); k<4; k++)
								{
									block[x+i][y+k][z].flag = 24;
									block[x+i][y+k][z].ID = ID24;
								}
							}
							block[x][y][z].corner  = 1;
							block[x+1][y+3][z].corner  = 2;
							continue;
						}
					}

					//ｘ軸方向に同じ２×２があれば２×４に置き換える
					if(block[x+2][y][z].flag == 4)
					{
						if(block[x][y][z].ColorID == block[x+2][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x+2][y][z].ColorID < 1)
						{
							ID24++;
							num22 = num22 - 2;
							num24++;
							for(int i(0); i<4; i++)
							{				
								for(int k(0); k<2; k++)
								{	
									block[x+i][y+k][z].flag = 24;
									block[x+i][y+k][z].ID = ID24;
								}
							}
							block[x][y][z].corner  = 1;
							block[x+3][y+1][z].corner  = 2;
							//continue;
						}
					}



				}
			}
		}
	}
	//outputFlag("test07_22_to_24.txt", VoxSize);

}

void Change_flag_4_to_22(Lego*** block, int*  VoxSize)
{
	int x,y,z;
	int count(0);
	//奇数層
	for(z=1; z < VoxSize[2]-1; z=z+2 )				//ｚ＝1,3,5,...
	{
		for(x=1; x < VoxSize[0]-1; x=x+2)
		{
			for(y=1; y < VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag == 4)
				{
					ID22++;
					count++;
					for(int i(0); i<2; i++)
					{
						for(int k(0); k<2; k++)
						{
							block[x+i][y+k][z].flag = 22;
							block[x+i][y+k][z].ID = ID22;
						}
					}
					block[x][y][z].corner = 1;
					block[x+1][y+1][z].corner = 2;
				}
			}
		}
	}

	//偶数層
	for(z=2; z < VoxSize[2]-1; z=z+2 )				//ｚ＝2,4,6,...
	{	
		for(x=0; x < VoxSize[0]-1; x=x+2)
		{
			for(y=0; y < VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag == 4)
				{
					ID22++;
					count++;
					for(int i(0); i<2; i++)
					{
						for(int k(0); k<2; k++)
						{
							block[x+i][y+k][z].flag = 22;
							block[x+i][y+k][z].ID = ID22;
						}
					}
					block[x][y][z].corner = 1;
					block[x+1][y+1][z].corner = 2;
				}
			}
		}
	}
	cout<<count<<"個の２×２のflagが　４　から　２２に変わった！"<<endl;
	//outputFlag("change_2×2_flag_4_to_22.txt", VoxSize);
}

void Change_flag_2_to_12(Lego*** block, int*  VoxSize)
{
	int x,y,z;
	int count(0);
	//奇数層
	for(z=1; z < VoxSize[2]-1; z=z+2 )				//ｚ＝1,3,5,...
	{
		for(x=1; x < VoxSize[0]-1; x=x+2)
		{
			for(y=1; y < VoxSize[1]-1; y=y+2)
			{
				//上                                                                                                                                    
				if(block[x][y][z].flag == 2 && block[x][y+1][z].flag == 2)
				{
					ID12++;
					count++;
					block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;			block[x][y][z].corner = 1;
					block[x][y+1][z].flag = 12;	block[x][y+1][z].ID = ID12;		block[x][y+1][z].corner  = 2;
				}
				//左                                                                                                                                  
				else if(block[x][y][z].flag == 2 && block[x+1][y][z].flag == 2)
				{
					ID12++;
					count++;
					block[x][y][z].flag = 12;			block[x][y][z].ID =ID12;			block[x][y][z].corner  = 1;
					block[x+1][y][z].flag = 12;	block[x+1][y][z].ID =ID12;		block[x+1][y][z].corner = 2;
				}
				//下                                                                                                                                                           
				else if(block[x+1][y][z].flag == 2 && block[x+1][y+1][z].flag == 2)
				{
					ID12++;
					count++;
					block[x+1][y][z].flag = 12;		block[x+1][y][z].ID =ID12;		block[x+1][y][z].corner = 1;			
					block[x+1][y+1][z].flag = 12;	block[x+1][y+1][z].ID =ID12;	block[x+1][y+1][z].corner = 2;
				}
				//右                                                                                                                                                           
				else if(block[x][y+1][z].flag == 2 && block[x+1][y+1][z].flag == 2)
				{
					ID12++;
					count++;
					block[x][y+1][z].flag = 12;		block[x][y+1][z].ID =ID12;		block[x][y+1][z].corner = 1;
					block[x+1][y+1][z].flag = 12;	block[x+1][y+1][z].ID =ID12;	block[x+1][y+1][z].corner = 2;
				}
			}
		}
	}

	//偶数層
	for(z=2; z < VoxSize[2]-1; z=z+2 )				//ｚ＝2,4,6,...
	{	
		for(x=0; x < VoxSize[0]-1; x=x+2)
		{
			for(y=0; y < VoxSize[1]-1; y=y+2)
			{
				//上                                                                                                                                    
				if(block[x][y][z].flag == 2 && block[x][y+1][z].flag == 2)
				{
					ID12++;
					count++;
					block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;			block[x][y][z].corner = 1;
					block[x][y+1][z].flag = 12;	block[x][y+1][z].ID = ID12;		block[x][y+1][z].corner  = 2;
				}
				//左                                                                                                                                  
				else if(block[x][y][z].flag == 2 && block[x+1][y][z].flag == 2)
				{
					ID12++;
					count++;
					block[x][y][z].flag = 12;			block[x][y][z].ID =ID12;			block[x][y][z].corner  = 1;
					block[x+1][y][z].flag = 12;	block[x+1][y][z].ID =ID12;		block[x+1][y][z].corner = 2;
				}
				//下                                                                                                                                                           
				else if(block[x+1][y][z].flag == 2 && block[x+1][y+1][z].flag == 2)
				{
					ID12++;
					count++;
					block[x+1][y][z].flag = 12;		block[x+1][y][z].ID =ID12;		block[x+1][y][z].corner = 1;			
					block[x+1][y+1][z].flag = 12;	block[x+1][y+1][z].ID =ID12;	block[x+1][y+1][z].corner = 2;
				}
				//右                                                                                                                                                           
				else if(block[x][y+1][z].flag == 2 && block[x+1][y+1][z].flag == 2)
				{
					ID12++;
					count++;
					block[x][y+1][z].flag = 12;		block[x][y+1][z].ID =ID12;		block[x][y+1][z].corner = 1;
					block[x+1][y+1][z].flag = 12;	block[x+1][y+1][z].ID =ID12;	block[x+1][y+1][z].corner = 2;
				}
			}
		}
	}
	cout<<count<<"個の１×２のflagが　２　から　１２に変わった！"<<endl;
	//outputFlag("change_１×2_flag_2_to_12.txt", VoxSize);
}

//２０１３・９・１４
void Small_to_Big_after_Coloring(Lego*** block, int*  VoxSize)
{
	int x,y,z;
	//奇数層
	for(z=1; z < VoxSize[2]-1; z=z+2 )				//ｚ＝1,3,5,...
	{
		for(x=1; x < VoxSize[0]-1; x=x+2)
		{
			for(y=1; y < VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag == 4)
				{
					//ｙ軸方向に同じ２×２があれば２×４に置き換える
					if(block[x][y+2][z].flag == 4)
					{
						ID24++;
						num22 = num22 - 2;
						num24++;
						for(int i(0); i<2; i++)
						{
							for(int k(0); k<4; k++)
							{
								block[x+i][y+k][z].flag = 24;
								block[x+i][y+k][z].ID = ID24;
							}
						}
						block[x][y][z].corner  = 1;
						block[x+1][y+3][z].corner  = 2;
						continue;
					}

					//ｘ軸方向に同じ２×２があれば２×４に置き換える
					if(block[x+2][y][z].flag == 4)
					{
						ID24++;
						num22 = num22 - 2;
						num24++;
						for(int i(0); i<4; i++)
						{				
							for(int k(0); k<2; k++)
							{	
								block[x+i][y+k][z].flag = 24;
								block[x+i][y+k][z].ID = ID24;
							}
						}
						block[x][y][z].corner  = 1;
						block[x+3][y+1][z].corner  = 2;
					}

				}
			}
		}
	}

	//偶数層
	for(z=2; z < VoxSize[2]-1; z=z+2 )				//ｚ＝2,4,6,...
	{	
		for(x=0; x < VoxSize[0]-1; x=x+2)
		{
			for(y=0; y < VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag == 4)
				{
					//ｙ軸方向に同じ２×２があれば２×４に置き換える
					if(block[x][y+2][z].flag == 4)
					{
						ID24++;
						num22 = num22 - 2;
						num24++;
						for(int i(0); i<2; i++)
						{
							for(int k(0); k<4; k++)
							{
								block[x+i][y+k][z].flag = 24;
								block[x+i][y+k][z].ID = ID24;
							}
						}
						block[x][y][z].corner  = 1;
						block[x+1][y+3][z].corner  = 2;
						continue;
					}

					//ｘ軸方向に同じ２×２があれば２×４に置き換える
					if(block[x+2][y][z].flag == 4)
					{
						ID24++;
						num22 = num22 - 2;
						num24++;
						for(int i(0); i<4; i++)
						{				
							for(int k(0); k<2; k++)
							{	
								block[x+i][y+k][z].flag = 24;
								block[x+i][y+k][z].ID = ID24;
							}
						}
						block[x][y][z].corner  = 1;
						block[x+3][y+1][z].corner  = 2;
					}

				}
			}
		}
	}
	outputFlag("test07_22_to_24.txt", VoxSize);


}