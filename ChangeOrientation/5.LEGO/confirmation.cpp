#include "../stdafx.h"

extern Model Integ;
extern Lego*** block;
extern double delThres;


int Block_count(int* size ){
	int count(0);
	for(int z(1); z < size[2]-1; z++ )
	{
		for(int x(1); x < size[0]-1; x++)
		{
			for(int y(1); y < size[1]-1; y++)
			{
				if(block[x][y][z].flag)
					count++;
			}
		}
	}
	return count;
}

void outputFlag(string filename, int* size)
{
	//ˆÈ‰ºŠm”F—p
	ofstream fout(filename);
	for(int z(1); z < size[2]-1; z++ )				//‚š1,3,5,...
	{
		for(int x(1); x < size[0]-1; x++)
		{
			for(int y(1); y < size[1]-1; y++)
			{
				fout<<block[x][y][z].flag<< " ";
			}
			fout<<endl;
		}
		fout<<endl;
	}
}

void outputID(string filename, int* size)
{
	//ˆÈ‰ºŠm”F—p
	ofstream fout(filename);
	for(int z(1); z < size[2]-1; z++ )				//‚š1,3,5,...
	{
		for(int x(1); x < size[0]-1; x++)
		{
			for(int y(1); y < size[1]-1; y++)
			{
				fout<<block[x][y][z].ID<< " ";
			}
			fout<<endl;
		}
		fout<<endl;
	}
}

void outputColorID(string filename, int* size)
{
	//ˆÈ‰ºŠm”F—p
	ofstream fout(filename);
	for(int z(1); z < size[2]-1; z++ )				//‚š1,3,5,...
	{
		for(int x(1); x < size[0]-1; x++)
		{
			for(int y(1); y < size[1]-1; y++)
			{
				fout<<block[x][y][z].ColorID<< " ";
			}
			fout<<endl;
		}
		fout<<endl;
	}
}

void delete_InnerBlocks(int* VoxSize)
{

	for(int z(1); z<VoxSize[2]-1; z++)
	{
		for(int x(1); x<VoxSize[0]-1; x++)
		{
			for(int y(1); y<VoxSize[1]-1; y++)
			{
				if(Integ.Voxels[x][y][z].fill)
				{
					if(Integ.Voxels[x][y][z].dist < delThres)
					{
						Integ.Voxels[x][y][z].ClearDist();
						Integ.Voxels[x][y][z].fill = false;
					}
				}
			}
		}
	}
}

void delete_Inner11(int* VoxSize)
{
	////###############################
	////‘S•”‚ðÁ‚·ƒo[ƒWƒ‡ƒ“
	////###############################
	//for(int z(1); z<VoxSize[2]-1; z++)
	//{
	//	for(int x(1); x<VoxSize[0]-1; x++)
	//	{
	//		for(int y(1); y<VoxSize[1]-1; y++)
	//		{
	//			if(block[x][y][z].fill)
	//				if(!block[x][y][z].surf)
	//					if(block[x][y][z].flag == 1)
	//						block[x][y][z].Initiaization();
	//		}
	//	}
	//}

	//###############################

	//###############################
	for(int z(1); z<VoxSize[2]-1; z++)
	{
		for(int x(1); x<VoxSize[0]-1; x++)
		{
			for(int y(1); y<VoxSize[1]-1; y++)
			{
				if(block[x][y][z].fill)
					if(!block[x][y][z].surf)
						if(block[x][y][z].flag == 1)
							if(!block[x][y][z+1].fill || !block[x][y][z-1].fill)
								block[x][y][z].Initiaization();
			}
		}
	}


}

void GiveColorIDto12_22(int* VoxSize)
{
	//2013/10/13

	for(int z(1); z < VoxSize[2]-1; z++)
	{
		for(int x(1); x < VoxSize[0]-1; x++)
		{
			for(int y(1); y < VoxSize[1]-1; y++)
			{
				if(block[x][y][z].surf)
				{
					//‚P~‚Q‚Ìê‡
					if(block[x][y][z].flag == 2)
					{
						//‚SŽü•Ó‚ðŒ©‚Äflag‚àID‚à“¯‚¶‚È‚ç‚Î•\–Êƒ{ƒNƒZƒ‹‚Æ“¯‚¶ColorID‚ð‚Â‚¯‚é
						if(block[x-1][y][z].flag == block[x][y][z].flag && block[x-1][y][z].ID == block[x][y][z].ID)
							block[x-1][y][z].ColorID = block[x][y][z].ColorID;

						else if(block[x+1][y][z].flag == block[x][y][z].flag && block[x+1][y][z].ID == block[x][y][z].ID)
							block[x+1][y][z].ColorID = block[x][y][z].ColorID;

						else if(block[x][y-1][z].flag == block[x][y][z].flag && block[x][y-1][z].ID == block[x][y][z].ID)
							block[x][y-1][z].ColorID = block[x][y][z].ColorID;

						else if(block[x][y+1][z].flag == block[x][y][z].flag && block[x][y+1][z].ID == block[x][y][z].ID)
							block[x][y+1][z].ColorID = block[x][y][z].ColorID;
					}

					//‚Q~‚Q‚Ìê‡
					else if(block[x][y][z].flag == 4)
					{
						//‘ÎŠp‚Ì‚SŽü•Ó‚ðŒ©‚Äflag‚àID‚à“¯‚¶‚È‚ç‚Î•\–Êƒ{ƒNƒZƒ‹‚Æ“¯‚¶ColorID‚ð‚Â‚¯‚é
						if(block[x-1][y-1][z].flag == block[x][y][z].flag && block[x-1][y-1][z].ID == block[x][y][z].ID)
						{
							block[x-1][y-1][z].ColorID = block[x][y][z].ColorID;
							block[x-1][y][z].ColorID = block[x][y][z].ColorID;
							block[x][y-1][z].ColorID = block[x][y][z].ColorID;
						}
						else if(block[x+1][y-1][z].flag == block[x][y][z].flag && block[x+1][y-1][z].ID == block[x][y][z].ID)
						{
							block[x+1][y-1][z].ColorID = block[x][y][z].ColorID;
							block[x][y-1][z].ColorID = block[x][y][z].ColorID;
							block[x+1][y][z].ColorID = block[x][y][z].ColorID;
						}
						else if(block[x-1][y+1][z].flag == block[x][y][z].flag && block[x-1][y+1][z].ID == block[x][y][z].ID)
						{
							block[x-1][y+1][z].ColorID = block[x][y][z].ColorID;
							block[x-1][y][z].ColorID = block[x][y][z].ColorID;
							block[x][y+1][z].ColorID = block[x][y][z].ColorID;
						}
						else if(block[x+1][y+1][z].flag == block[x][y][z].flag && block[x+1][y+1][z].ID == block[x][y][z].ID)
						{
							block[x+1][y+1][z].ColorID = block[x][y][z].ColorID;
							block[x+1][y][z].ColorID = block[x][y][z].ColorID;
							block[x][y+1][z].ColorID = block[x][y][z].ColorID;
						}
					}
				}
			}
		}
	}

}

void Voxel2Block(int* VoxSize)
{
	cout << "Voxel to Block:\n";
	for(int x(1); x < VoxSize[0]-1; x++)
	{
		for(int y(1); y < VoxSize[1]-1; y++)
		{
			for(int z(1); z < VoxSize[2]-1; z++)
			{
				if(Integ.Voxels[x][y][z].fill)		//“à•”ƒ{ƒNƒZƒ‹‚Å‚ ‚é
				{
					//‹——£êHHˆÈã‚ðíœ‚·‚é
				/*	if(Integ.Voxels[x][y][z].dist < delThres)
						continue;*/
					block[x][y][z].fill = true;			//“à•”ƒ{ƒNƒZƒ‹ƒtƒ‰ƒO‚ð—§‚Ä‚é
					//•\–Êƒ{ƒNƒZƒ‹‚Å‚ ‚é
					if(Integ.Voxels[x][y][z].surf)
						block[x][y][z].surf = true;	//•\–Êƒ{ƒNƒZƒ‹ƒtƒ‰ƒO‚ð—§‚Ä‚é

				}
			}
		}
	}
}


void insurf_LEGO(int* VoxSize)
{
	int ID(0);
	int flag(0);
	for(int z(1); z < VoxSize[2]-1; z++)
	{
		for(int y(1); y < VoxSize[1]-1; y++)
		{
			for(int x(1); x < VoxSize[0]-1; x++)
			{
				if(block[x][y][z].in_surf)		//“à•”•\–Êƒ{ƒNƒZƒ‹‚Å‚ ‚é
				{
					ID=block[x][y][z].ID;
					flag=block[x][y][z].flag;
					for(int i(-3); i < 4 ; i++)
						for(int j(-3); j < 4 ; j++){
							if((x+i)>0&&(x+i)<VoxSize[0])
							if((y+j)>0&&(y+j)<VoxSize[1])
							if(block[x+i][y+j][z].ID==ID&&block[x+i][y+j][z].flag==flag){
								block[x+i][y+j][z].in_surf=true;
							}
						}
				}
			}
		}
	}
}


void FindOutsideBlocks(Lego*** m, int* VoxSize)
{
	int x, y, z;

	for (x = 1; x<VoxSize[0] - 1; ++x)				//x:1~num[0]-2@‚Íˆê”ÔŠO‘¤‚Ì‘w‚Éƒ{ƒNƒZƒ‹‚Í‘¶Ý‚µ‚È‚¢(‹——£êŒvŽZ‚Ì‚½‚ß‚É“ü‚ê‚½‘w)
	{
		for (y = 1; y<VoxSize[1] - 1; ++y)			//ˆê”ÔŠO‘¤‚Ì‘w‚Éƒ{ƒNƒZƒ‹‚Í‘¶Ý‚µ‚È‚¢
		{
			for (z = 1; z< VoxSize[2] - 1; ++z)		//ˆê”ÔŠO‘¤‚Ì‘w‚Éƒ{ƒNƒZƒ‹‚Í‘¶Ý‚µ‚È‚¢
			{
				if (m[x][y][z].fill)
				{
					//ã(z + 1)
					if (!m[x][y][z + 1].fill)
					{
						m[x][y][z].surf = true;
						continue;
					}
					//‰º(z - 1)
					if (!m[x][y][z - 1].fill)
					{
						m[x][y][z].surf = true;
						continue;
					}
					//‘O(x + 1)
					if (!m[x + 1][y][z].fill)
					{
						m[x][y][z].surf = true;
						continue;
					}
					//Œã(x - 1)
					if (!m[x - 1][y][z].fill)
					{
						m[x][y][z].surf = true;
						continue;
					}
					//¶(y + 1)
					if (!m[x][y + 1][z].fill)
					{
						m[x][y][z].surf = true;
						continue;
					}
					//‰E(y - 1)
					if (m[x][y - 1][z].fill == false)
					{
						m[x][y][z].surf = true;
					}
				}
			}
		}
	}
}

