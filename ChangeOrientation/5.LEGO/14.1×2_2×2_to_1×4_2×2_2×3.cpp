#include "../stdafx.h"
#include "../Voxel.h"
#include "../Lego.h"		//LEGOƒuƒƒbƒN‚ğ‘g‚İ—§‚Ä‚é‚½‚ß‚ÌƒNƒ‰ƒX

extern int ID14;
extern int ID22;
extern int ID23;

extern int num12;		//‚P~‚Q‚ÌƒuƒƒbƒN‚Ì”
extern int num14;		//‚P~‚S‚ÌƒuƒƒbƒN‚Ì”
extern int num22;		//‚Q~‚Q‚ÌƒuƒƒbƒN‚Ì”
extern int num23;		//‚Q~‚R‚ÌƒuƒƒbƒN‚Ì”

void outputFlag(string filename, int* size);

//‚P~‚Q‚Ì‚S•ûŒü‚É@1~‚Q@‚Ü‚½‚Í@‚Q~‚Q@‚ª‚ ‚Á‚½‚çŒ‹‡‚³‚¹‚é
//‚P~‚Q‚Ì’·•Ó•ûŒü‚ª@X²@‚©@Y²@‚©‚É‚æ‚èê‡‚í‚¯‚ª‚ ‚é
//‚³‚ç‚ÉAŠï”‚Ì‘w‚Æ‹ô”‚Ì‘w‚É•ª‚¯‚é
void Small_to_Big_step4(Lego*** block, int*  VoxSize)
{
	int x,y,z;
	for(z=1; z < VoxSize[2]-1; z++ ){
		//#######################
		//                       Šï”‘w                         
		//#######################
		if(z%2){
			for(x=1; x < VoxSize[0]-1; x=x+2){
				for(y=1; y < VoxSize[1]-1; y=y+2){
					//ã                                                                                                                                    
					if(block[x][y][z].flag == 2 && block[x][y+1][z].flag == 2)
					{
						//‰E‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
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
						//ã‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
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
					//¶                                                                                                                                  
					else if(block[x][y][z].flag == 2 && block[x+1][y][z].flag == 2)
					{
						//‰º‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
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
						//¶‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
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
					//‰º                                                                                                                                                           
					else if(block[x+1][y][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						//‰E‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
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
						//‰º‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
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
					//‰E                                                                                                                                                           
					else if(block[x][y+1][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						//‰º‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
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
						//‰E‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
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
		//‹ô”‘w
		else
		{
			for(x=0; x < VoxSize[0]-1; x=x+2)
			{
				for(y=0; y < VoxSize[1]-1; y=y+2)
				{
					//ã                                                                                                                                    
					if(block[x][y][z].flag == 2 && block[x][y+1][z].flag == 2)
					{
						//‰E‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
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
						//ã‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
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
					//¶                                                                                                                                  
					else if(block[x][y][z].flag == 2 && block[x+1][y][z].flag == 2)
					{
						//‰º‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
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
						//¶‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
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
					//‰º                                                                                                                                                           
					else if(block[x+1][y][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						//‰E‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
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
						//‰º‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
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
					//‰E                                                                                                                                                           
					else if(block[x][y+1][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						//‰º‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
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
						//‰E‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
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
		//Šï”‘w
		if(z%2)
		{
			for(x=1; x < VoxSize[0]-1; x=x+2)
			{
				for(y=1; y < VoxSize[1]-1; y=y+2)
				{
					//ã                                                                                                                                    
					if(block[x][y][z].flag == 2 && block[x][y+1][z].flag == 2)
					{
						//‰E‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
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
						//ã‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
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
					//¶                                                                                                                                  
					else if(block[x][y][z].flag == 2 && block[x+1][y][z].flag == 2)
					{
						//‰º‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
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
						//¶‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
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
					//‰º                                                                                                                                                           
					else if(block[x+1][y][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						//‰E‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
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
						//‰º‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
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
					//‰E                                                                                                                                                           
					else if(block[x][y+1][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						//‰º‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
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
						//‰E‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
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
		//‹ô”‘w
		else
		{
			for(x=0; x < VoxSize[0]-1; x=x+2)
			{
				for(y=0; y < VoxSize[1]-1; y=y+2)
				{
					//ã                                                                                                                                    
					if(block[x][y][z].flag == 2 && block[x][y+1][z].flag == 2)
					{
						//‰E‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
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
						//ã‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
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
					//¶                                                                                                                                  
					else if(block[x][y][z].flag == 2 && block[x+1][y][z].flag == 2)
					{
						//‰º‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
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
						//¶‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
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
					//‰º                                                                                                                                                           
					else if(block[x+1][y][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						//‰E‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
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
						//‰º‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
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
					//‰E                                                                                                                                                           
					else if(block[x][y+1][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						//‰º‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
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
						//‰E‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
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


//‚P~‚Q‚Ìã‰º‚ğŒ©‚ÄÅ‘å‚Å‚à‚P~‚P‚µ‚©‚È‚¢ê‡‚Í—Dæ“I‚É‚Ù‚©‚ÌƒuƒƒbƒN‚Æ‚­‚Á‚Â‚¯‚é
void Small_to_Big_before_step4(Lego*** block, int*  VoxSize)
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
					if(block[x][y][z].flag == 2 && block[x][y+1][z].flag == 2)
					{
						if(block[x][y][z-1].flag < 2 && block[x][y+1][z-1].flag < 2 && block[x][y][z+1].flag < 2 && block[x][y+1][z+1].flag < 2)
						{
							//‰E‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
							if(block[x][y+2][z].flag == 2)
							{
								if(block[x][y+3][z].flag == 2)
								{
									//ã‰º‚ğŒ©‚ÄÅ’á‚Å‚à1‚Â‚Ìƒtƒ‰ƒO‚ª‚QˆÈã‚Å‚ ‚ê‚Î
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
							//ã‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
							if(block[x-1][y][z].flag == 2 && block[x-1][y+1][z].flag == 2)
							{
								//ã‰º‚ğŒ©‚ÄÅ’á‚Å‚à1‚Â‚Ìƒtƒ‰ƒO‚ª‚QˆÈã‚Å‚ ‚ê‚Î
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
					//¶
					else if(block[x][y][z].flag == 2 && block[x+1][y][z].flag == 2)
					{
						if(block[x][y][z-1].flag < 2 && block[x+1][y][z-1].flag < 2 && block[x][y][z+1].flag < 2 && block[x+1][y][z+1].flag < 2)
						{
							//‰º‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
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
							//¶‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
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
					//‰º
					else if(block[x+1][y][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						if(block[x+1][y][z-1].flag < 2 && block[x+1][y+1][z-1].flag < 2 && block[x+1][y][z+1].flag < 2 && block[x+1][y+1][z+1].flag < 2)
						{
							//‰E‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
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
							//‰º‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
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
					//‰E
					else if(block[x][y+1][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						if(block[x][y+1][z-1].flag < 2 && block[x+1][y+1][z-1].flag < 2 && block[x][y+1][z+1].flag < 2 && block[x+1][y+1][z+1].flag < 2)
						{
							//‰º‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
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
							//‰E‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
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
		//‹ô”‘w
		else
		{
			for(x=0; x < VoxSize[0]-1; x=x+2)
			{
				for(y=0; y < VoxSize[1]-1; y=y+2)
				{
					//ã
					if(block[x][y][z].flag == 2 && block[x][y+1][z].flag == 2)
					{
						if(block[x][y][z-1].flag < 2 && block[x][y+1][z-1].flag < 2 && block[x][y][z+1].flag < 2 && block[x][y+1][z+1].flag < 2)
						{
							//‰E‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
							if(block[x][y+2][z].flag == 2 )
							{
								if(block[x][y+3][z].flag == 2)
								{
									//ã‰º‚ğŒ©‚ÄÅ’á‚Å‚à1‚Â‚Ìƒtƒ‰ƒO‚ª‚QˆÈã‚Å‚ ‚ê‚Î
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
							//ã‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
							if(block[x-1][y][z].flag == 2 && block[x-1][y+1][z].flag == 2)
							{
								//ã‰º‚ğŒ©‚ÄÅ’á‚Å‚à1‚Â‚Ìƒtƒ‰ƒO‚ª‚QˆÈã‚Å‚ ‚ê‚Î
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
					//¶
					else if(block[x][y][z].flag == 2 && block[x+1][y][z].flag == 2)
					{
						if(block[x][y][z-1].flag < 2 && block[x+1][y][z-1].flag < 2 && block[x][y][z+1].flag < 2 && block[x+1][y][z+1].flag < 2)
						{
							//‰º‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
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
							//¶‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
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
					//‰º
					else if(block[x+1][y][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						if(block[x+1][y][z-1].flag < 2 && block[x+1][y+1][z-1].flag < 2 && block[x+1][y][z+1].flag < 2 && block[x+1][y+1][z+1].flag < 2)
						{
							//‰E‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
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
							//‰º‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
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
					//‰E
					else if(block[x][y+1][z].flag == 2 && block[x+1][y+1][z].flag == 2)
					{
						if(block[x][y+1][z-1].flag < 2 && block[x+1][y+1][z-1].flag < 2 && block[x][y+1][z+1].flag < 2 && block[x+1][y+1][z+1].flag < 2)
						{
							//‰º‚ğŒ©‚éi1~‚Qj‚ª‚ ‚Á‚½‚ç‚P~‚S‚É‚·‚é
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
							//‰E‚ğŒ©‚éi‚P~‚Qj‚Ü‚½‚Íi‚Q~‚Qj‚ª‚ ‚Á‚½‚ç‡‘Ì
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
		}//else(‹ô”‘w)

	}	//for(z)

	cout<<count << "ŒÂ‚ÌŒÇ—§‚µ‚»‚¤‚È‚P~‚Q‚ª—Dæ‡¬‚³‚ê‚½I "<<endl;

	//outputFlag("test04_12_22_to_14_22_23_before.txt", VoxSize);

}