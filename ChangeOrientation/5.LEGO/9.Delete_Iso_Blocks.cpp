#include "../stdafx.h"
#include "../Voxel.h"
#include "../Lego.h"		//LEGOƒuƒƒbƒN‚ğ‘g‚İ—§‚Ä‚é‚½‚ß‚ÌƒNƒ‰ƒX

void outputFlag(string filename, int* size);
void outputID(string filename, int* size);

extern int num11;		//‚Q~‚Q‚ÌƒuƒƒbƒN‚Ì”
extern int num12;		//‚Q~‚Q‚ÌƒuƒƒbƒN‚Ì”
extern int num22;		//‚Q~‚Q‚ÌƒuƒƒbƒN‚Ì”

//‚P~‚P‚Ìã‰º‚ğŒ©‚ÄƒuƒƒbƒN‚ª‚È‚©‚Á‚½‚çÁ‚·
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
				//‚P~‚P‚ÌŒÇ—§ƒuƒƒbƒN‚ğÁ‚·
				if(block[x][y][z].flag == 1)
				{
					//ã‰º‚ÌƒuƒƒbƒN‚ğŒ©‚Ä—¼•û‚Æ‚à‰½‚à‚È‚¢ê‡
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
	cout<<count<<"ŒÂ‚Ì‚P~‚P‚ªíœ‚³‚ê‚½"<<endl;
	//outputFlag("Delete_Blocks_11.txt", VoxSize);
}

//‚P~‚Q‚Ìã‰º‚ğŒ©‚ÄƒuƒƒbƒN‚ª‚È‚©‚Á‚½‚çÁ‚·
void Delete_Iso_Blocks_12(Lego*** block, int* VoxSize)
{
	int x,y,z;
	int count(0);
	for(z=1; z < VoxSize[2]-1; z++ )
	{
		//Šï”‘w
		if(z%2)
		{
			for(x=1; x < VoxSize[0]-1; x=x+2)
			{
				for(y=1; y < VoxSize[1]-1; y=y+2)
				{
					//ã
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
					//¶
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
					//‰º
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
					//‰E
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
		//‹ô”‘w
		else
		{
			for(x=0; x < VoxSize[0]-1; x=x+2)
			{
				for(y=0; y < VoxSize[1]-1; y=y+2)
				{
					//ã
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
					//¶
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
					//‰º
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
					//‰E
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

	cout<<count<<"ŒÂ‚Ì‚P~‚Q‚ªíœ‚³‚ê‚½I"<<endl;
	//outputFlag("Delete_Blocks_12.txt", VoxSize);

}

//‚Q~‚Q‚Ì“Æ—§‚µ‚Ä‚¢‚éƒ{ƒNƒZƒ‹‚ğíœ
void Delete_Iso_Blocks_22(Lego*** block, int* VoxSize)
{
	int x,y,z;
	int count(0);
	for(z=1; z < VoxSize[2]-1; z++ )
	{
		//Šï”‘w
		if(z%2)
		{
			for(x=1; x < VoxSize[0]-1; x=x+2)
			{
				for(y=1; y < VoxSize[1]-1; y=y+2)
				{
					//‘ÎŠpü‚Ìƒ{ƒNƒZƒ‹‚Ìflag‚ª‚Q‚Q‚¾‚Á‚½‚ç
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
		//‹ô”‘w
		else
		{
			for(x=0; x < VoxSize[0]-1; x=x+2)
			{
				for(y=0; y < VoxSize[1]-1; y=y+2)
				{
					//‘ÎŠpü‚Ìƒ{ƒNƒZƒ‹‚Ìflag‚ª‚Q‚Q‚¾‚Á‚½‚ç
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

	cout<<count<<"ŒÂ‚Ì‚Q~‚Q‚ªíœ‚³‚ê‚½I"<<endl;
	//outputFlag("Delete_Blocks_22.txt", VoxSize);
}

//ŒÇ—§‚µ‚»‚¤‚ÈƒuƒƒbƒNŒQ‚ğÁ‚·‚æ‚¤‚É‚·‚é
//‚Ü‚¸A‚P~‚Q‚ğ’T‚·
//‚»‚Ìã‰º‚ÌƒuƒƒbƒN‚ª‚P~‚P‚Ü‚½‚Í‰½‚à‚È‚¢ê‡‚³‚ç‚É‚»‚ê‚ğŒ©‚Ä‚¢‚­
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
					//‚™•ûŒü‚Ì‚P~‚Q
					//################################
					if(block[x][y+1][z].flag == 12 && block[x][y+1][z].ID == block[x][y][z].ID)
					{
						num = 0;
						//‚PŒÂ–Ú‚Ì‰º‚ğŒ©‚é
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
						//‚PŒÂ–Ú‚Ìã‚ğŒ©‚é
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
						//‚QŒÂ–Ú‚Ì‰º‚ğŒ©‚é
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
						//‚QŒÂ–Ú‚Ìã‚ğŒ©‚é
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
						//‚P~‚Q‚Ìã‰º‡Œv‚U‚Â‚Ìƒ{ƒNƒZƒ‹‚Ìflag‚ğ‚O‚É‚·‚é —pŒŸ“¢II
						for(int i(0); i<2; i++)
						{
							for(int k(0); k<3; k++)
								block[x][y+i][z+k-1].Initiaization();
						}
						cout<<"ƒuƒƒbƒN‚ğíœ‚µ‚½IF"<<x<<" "<<y<<" "<<z<<endl;
					}
					//################################
					//‚˜•ûŒü‚Ì‚P~‚Q
					//################################
					else if(block[x+1][y][z].flag == 12 && block[x+1][y][z].ID == block[x][y][z].ID)
					{
						num = 0;
						//‚PŒÂ–Ú‚Ì‰º‚ğŒ©‚é
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
						//‚PŒÂ–Ú‚Ìã‚ğŒ©‚é
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
						//‚QŒÂ–Ú‚Ì‰º‚ğŒ©‚é
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
						//‚QŒÂ–Ú‚Ìã‚ğŒ©‚é
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

						//‚P~‚Q‚Ìã‰º‡Œv‚U‚Â‚Ìƒ{ƒNƒZƒ‹‚Ìflag‚ğ‚O‚É‚·‚é
						for(int i(0); i<2; i++)
						{
							for(int k(0); k<3; k++)
								block[x+i][y][z+k-1].Initiaization();
						}
						//‚P~‚P‚Í‰½ŒÂHi‚P`‚Sj
						cout<<"ƒuƒƒbƒN‚ğíœ‚µ‚½IF"<<x<<" "<<y<<" "<<z<<endl;
					}
				}
			}
		}
	}

	outputFlag("Delete_Blocks.txt", VoxSize);
	//outputID("Delete_Blocks_ID.txt", VoxSize);
}
