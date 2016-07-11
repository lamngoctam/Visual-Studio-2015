#include "../stdafx.h"

extern int ID22;
extern int ID23;
extern int ID14;
extern int num12;		//‚P~‚Q‚ÌƒuƒƒbƒN‚Ì”
extern int num22;		//‚Q~‚Q‚ÌƒuƒƒbƒN‚Ì”
extern int num23;		//‚Q~‚R‚ÌƒuƒƒbƒN‚Ì”
extern int num14;		//1~4‚ÌƒuƒƒbƒN‚Ì”

void outputFlag(string filename, int* size);

//InputF		‚P~‚P@‚Æ@‚P~‚P@‚É‚æ‚Á‚Ä‚Å‚«‚½@(‚P~‚Q)@‚Æ@‚P~‚Q@‚Æ@‚P~‚Q@(‚Q~‚Q)@‚É‚æ‚Á‚Ä‚Å‚«‚½‚à‚ñ‚ğ‡¬‚¾‚à‚ñI
//OutputF	‚Å‚«‚é‚Ì‚Í	‚Q~‚Q@‚Ü‚½‚Í@‚Q~‚R
void Small_to_Big_step6(Lego*** block, int*  VoxSize)
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
					//¶ã===========================================================
					if(block[x][y][z].flag == 12)
					{
						//ã‚ğŒ©‚é
						if(block[x-1][y][z].flag == 12 && block[x-1][y][z].ID == block[x][y][z].ID)
						{
							//¶‚É‚P~‚Qi‚P~‚P‚Æ‚P~‚P‚É‚æ‚Á‚Ä‡¬‚Å‚«‚½‚à‚Ì‚È‚ç‚Îj‚ª‚ ‚ê‚Î
							if(block[x-1][y-1][z].flag == 12 && block[x][y-1][z].flag == 12 && block[x-1][y-1][z].ID == block[x][y-1][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y-k][z].flag = 22;
										block[x-i][y-k][z].ID = ID22;
									}
								}
								block[x-1][y-1][z].corner = 1;
								block[x][y][z].corner = 2;

							}
							//¶‚É‚Q~‚Qi‚P~‚Q‚Æ‚P~‚Q‚É‚æ‚Á‚Ä‡¬‚Å‚«‚½‚à‚Ì‚È‚ç‚Îj‚ª‚ ‚ê‚Î
							else if(block[x-1][y-1][z].flag == 22)
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
										block[x-i][y-k][z].flag = 23;
										block[x-i][y-k][z].ID = ID23;
									}
								}
								block[x-1][y-2][z].corner = 1;
								block[x][y][z].corner = 2;
							}
						}
						//¶‚ğŒ©‚é
						else if(block[x][y-1][z].flag == 12 && block[x][y-1][z].ID == block[x][y][z].ID)
						{
							//ã‚É‚P~‚Qi‚P~‚P‚Æ‚P~‚P‚É‚æ‚Á‚Ä‡¬‚Å‚«‚½‚à‚Ì‚È‚ç‚Îj‚ª‚ ‚ê‚Î
							if(block[x-1][y-1][z].flag == 12 && block[x-1][y][z].flag == 12 && block[x-1][y-1][z].ID == block[x-1][y][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y-k][z].flag = 22;
										block[x-i][y-k][z].ID = ID22;
									}
								}
								block[x-1][y-1][z].corner = 1;
								block[x][y][z].corner = 2;
							}
							//ã‚É‚Q~‚Qi‚P~‚Q‚Æ‚P~‚Q‚É‚æ‚Á‚Ä‡¬‚Å‚«‚½‚à‚Ì‚È‚ç‚Îj‚ª‚ ‚ê‚Î
							else if(block[x-1][y-1][z].flag == 22)
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
										block[x-i][y-k][z].flag = 23;
										block[x-i][y-k][z].ID = ID23;
									}
								}
								block[x-2][y-1][z].corner = 1;
								block[x][y][z].corner = 2;
							}
						}
					}

					//‰Eã===========================================================
					else if(block[x][y+1][z].flag == 12)
					{
						//‰E‚ğŒ©‚é
						if(block[x][y+2][z].flag ==12 && block[x][y+2][z].ID == block[x][y+1][z].ID)
						{
							//ã‚É‚P~‚Q‚ª‚ ‚éê‡
							if(block[x-1][y+1][z].flag ==12 && block[x-1][y+2][z].flag ==12 && block[x-1][y+1][z].ID == block[x-1][y+2][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y+k+1][z].flag = 22;
										block[x-i][y+k+1][z].ID = ID22;
									}
								}
								block[x-1][y+1][z].corner = 1;
								block[x][y+2][z].corner = 2;
							}
							//ã‚É‚Q~‚Q‚ª‚ ‚éê‡
							else if(block[x-1][y+2][z].flag == 22)
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
										block[x-i][y+k+1][z].flag = 23;
										block[x-i][y+k+1][z].ID = ID23;
									}
								}
								block[x-2][y+1][z].corner = 1;
								block[x][y+2][z].corner = 2;
							}
						}
						//ã‚ğŒ©‚é
						else if(block[x-1][y+1][z].flag == 12 && block[x-1][y+1][z].ID == block[x][y+1][z].ID)
						{
							//‰E‚É‚P~‚Q‚ª‚ ‚éê‡
							if(block[x][y+2][z].flag == 12 && block[x-1][y+2][z].flag == 12 && block[x][y+2][z].ID == block[x-1][y+2][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y+k+1][z].flag = 22;
										block[x-i][y+k+1][z].ID = ID22;
									}
								}
								block[x-1][y+1][z].corner = 1;
								block[x][y+2][z].corner = 2;
							}
							//‰E‚É‚Q~‚Q‚ª‚ ‚éê‡
							else if(block[x-1][y+2][z].flag == 22)
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
										block[x-i][y+k+1][z].flag = 23;
										block[x-i][y+k+1][z].ID = ID23;
									}
								}
								block[x-1][y+1][z].corner = 1;
								block[x][y+3][z].corner = 2;
							}
						}
					}
					//¶‰º===========================================================
					else if(block[x+1][y][z].flag == 12)
					{
						//¶‚ğŒ©‚é
						if(block[x+1][y-1][z].flag == 12 && block[x+1][y-1][z].ID == block[x+1][y][z].ID)
						{
							//‰º‚É‚P~‚Q‚ª‚ ‚éê‡
							if(block[x+2][y-1][z].flag == 12 && block[x+2][y][z].flag == 12 && block[x+2][y-1][z].ID == block[x+2][y][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y-k][z].flag = 22;
										block[x+i+1][y-k][z].ID = ID22;
									}
								}
								block[x+1][y-1][z].corner = 1;
								block[x+2][y][z].corner = 2;
							}
							//‰º‚É‚Q~‚Q‚ª‚ ‚éê‡
							else if(block[x+2][y-1][z].flag == 22)
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
										block[x+i+1][y-k][z].flag = 23;
										block[x+i+1][y-k][z].ID = ID23;
									}
								}
								block[x+1][y-1][z].corner = 1;
								block[x+3][y][z].corner = 2;
							}
						}
						//‰º‚ğŒ©‚é
						else if(block[x+2][y][z].flag == 12 && block[x+2][y][z].ID == block[x+1][y][z].ID)
						{
							//¶‚É‚P~‚Q‚ª‚ ‚éê‡
							if(block[x+1][y-1][z].flag == 12 && block[x+2][y-1][z].flag == 12 && block[x+1][y-1][z].ID == block[x+2][y-1][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y-k][z].flag = 22;
										block[x+i+1][y-k][z].ID = ID22;
									}
								}
								block[x+1][y-1][z].corner = 1;
								block[x+2][y][z].corner = 2;
							}
							//¶‚É‚Q~‚Q‚ª‚ ‚éê‡
							else if(block[x+2][y-1][z].flag == 22)
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
										block[x+i+1][y-k][z].flag = 23;
										block[x+i+1][y-k][z].ID = ID23;
									}
								}
								block[x+1][y-2][z].corner = 1;
								block[x+2][y][z].corner = 2;
							}
						}

					}

					//‰E‰º===========================================================
					else if(block[x+1][y+1][z].flag == 12)
					{
						//‰E‚ğŒ©‚é
						if(block[x+1][y+2][z].flag == 12 && block[x+1][y+2][z].ID == block[x+1][y+1][z].ID)
						{
							//‰º‚É‚P~‚Q‚ª‚ ‚éê‡
							if(block[x+2][y+1][z].flag == 12 && block[x+2][y+2][z].flag == 12 && block[x+2][y+1][z].ID ==  block[x+2][y+2][z].ID )
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y+k+1][z].flag = 22;
										block[x+i+1][y+k+1][z].ID = ID22;
									}
								}
								block[x+1][y+1][z].corner = 1;
								block[x+2][y+2][z].corner = 2;
							}
							//‰º‚É‚Q~‚Q‚ª‚ ‚éê‡
							else if(block[x+2][y+2][z].flag == 22)
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
										block[x+i+1][y+k+1][z].flag = 23;
										block[x+i+1][y+k+1][z].ID = ID23;
									}
								}
								block[x+1][y+1][z].corner = 1;
								block[x+3][y+2][z].corner = 2;
							}
						}
						//‰º‚ğŒ©‚é
						else if(block[x+2][y+1][z].flag == 12 && block[x+2][y+1][z].ID == block[x+1][y+1][z].ID)
						{
							//‰E‚É‚P~‚Q‚ª‚ ‚éê‡
							if(block[x+1][y+2][z].flag == 12 && block[x+2][y+2][z].flag == 12 && block[x+1][y+2][z].ID == block[x+2][y+2][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y+k+1][z].flag = 22;
										block[x+i+1][y+k+1][z].ID = ID22;
									}
								}
								block[x+1][y+1][z].corner = 1;
								block[x+2][y+2][z].corner = 2;
							}
							//‰E‚É‚Q~‚Q‚ª‚ ‚éê‡
							else if(block[x+2][y+2][z].flag == 22)
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
										block[x+i+1][y+k+1][z].flag = 23;
										block[x+i+1][y+k+1][z].ID = ID23;
									}
								}
								block[x+1][y+1][z].corner = 1;
								block[x+2][y+3][z].corner = 2;
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
					//¶ã===========================================================
					if(block[x][y][z].flag == 12)
					{
						//ã‚ğŒ©‚é
						if(block[x-1][y][z].flag == 12 && block[x-1][y][z].ID == block[x][y][z].ID)
						{
							//¶‚É‚P~‚Qi‚P~‚P‚Æ‚P~‚P‚É‚æ‚Á‚Ä‡¬‚Å‚«‚½‚à‚Ì‚È‚ç‚Îj‚ª‚ ‚ê‚Î
							if(block[x-1][y-1][z].flag == 12 && block[x][y-1][z].flag == 12 && block[x-1][y-1][z].ID == block[x][y-1][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y-k][z].flag = 22;
										block[x-i][y-k][z].ID = ID22;
									}
								}
								block[x-1][y-1][z].corner = 1;
								block[x][y][z].corner = 2;

							}
							//¶‚É‚Q~‚Qi‚P~‚Q‚Æ‚P~‚Q‚É‚æ‚Á‚Ä‡¬‚Å‚«‚½‚à‚Ì‚È‚ç‚Îj‚ª‚ ‚ê‚Î
							else if(block[x-1][y-1][z].flag == 22)
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
										block[x-i][y-k][z].flag = 23;
										block[x-i][y-k][z].ID = ID23;
									}
								}
								block[x-1][y-2][z].corner = 1;
								block[x][y][z].corner = 2;
							}
						}
						//¶‚ğŒ©‚é
						else if(block[x][y-1][z].flag == 12 && block[x][y-1][z].ID == block[x][y][z].ID)
						{
							//ã‚É‚P~‚Qi‚P~‚P‚Æ‚P~‚P‚É‚æ‚Á‚Ä‡¬‚Å‚«‚½‚à‚Ì‚È‚ç‚Îj‚ª‚ ‚ê‚Î
							if(block[x-1][y-1][z].flag == 12 && block[x-1][y][z].flag == 12 && block[x-1][y-1][z].ID == block[x-1][y][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y-k][z].flag = 22;
										block[x-i][y-k][z].ID = ID22;
									}
								}
								block[x-1][y-1][z].corner = 1;
								block[x][y][z].corner = 2;
							}
							//ã‚É‚Q~‚Qi‚P~‚Q‚Æ‚P~‚Q‚É‚æ‚Á‚Ä‡¬‚Å‚«‚½‚à‚Ì‚È‚ç‚Îj‚ª‚ ‚ê‚Î
							else if(block[x-1][y-1][z].flag == 22)
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
										block[x-i][y-k][z].flag = 23;
										block[x-i][y-k][z].ID = ID23;
									}
								}
								block[x-2][y-1][z].corner = 1;
								block[x][y][z].corner = 2;
							}
						}
					}

					//‰Eã===========================================================
					else if(block[x][y+1][z].flag == 12)
					{
						//‰E‚ğŒ©‚é
						if(block[x][y+2][z].flag ==12 && block[x][y+2][z].ID == block[x][y+1][z].ID)
						{
							//ã‚É‚P~‚Q‚ª‚ ‚éê‡
							if(block[x-1][y+1][z].flag ==12 && block[x-1][y+2][z].flag ==12 && block[x-1][y+1][z].ID == block[x-1][y+2][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y+k+1][z].flag = 22;
										block[x-i][y+k+1][z].ID = ID22;
									}
								}
								block[x-1][y+1][z].corner = 1;
								block[x][y+2][z].corner = 2;
							}
							//ã‚É‚Q~‚Q‚ª‚ ‚éê‡
							else if(block[x-1][y+2][z].flag == 22)
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
										block[x-i][y+k+1][z].flag = 23;
										block[x-i][y+k+1][z].ID = ID23;
									}
								}
								block[x-2][y+1][z].corner = 1;
								block[x][y+2][z].corner = 2;
							}
						}
						//ã‚ğŒ©‚é
						else if(block[x-1][y+1][z].flag == 12 && block[x-1][y+1][z].ID == block[x][y+1][z].ID)
						{
							//‰E‚É‚P~‚Q‚ª‚ ‚éê‡
							if(block[x][y+2][z].flag == 12 && block[x-1][y+2][z].flag == 12 && block[x][y+2][z].ID == block[x-1][y+2][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y+k+1][z].flag = 22;
										block[x-i][y+k+1][z].ID = ID22;
									}
								}
								block[x-1][y+1][z].corner = 1;
								block[x][y+2][z].corner = 2;
							}
							//‰E‚É‚Q~‚Q‚ª‚ ‚éê‡
							else if(block[x-1][y+2][z].flag == 22)
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
										block[x-i][y+k+1][z].flag = 23;
										block[x-i][y+k+1][z].ID = ID23;
									}
								}
								block[x-1][y+1][z].corner = 1;
								block[x][y+3][z].corner = 2;
							}
						}
					}
					//¶‰º===========================================================
					else if(block[x+1][y][z].flag == 12)
					{
						//¶‚ğŒ©‚é
						if(block[x+1][y-1][z].flag == 12 && block[x+1][y-1][z].ID == block[x+1][y][z].ID)
						{
							//‰º‚É‚P~‚Q‚ª‚ ‚éê‡
							if(block[x+2][y-1][z].flag == 12 && block[x+2][y][z].flag == 12 && block[x+2][y-1][z].ID == block[x+2][y][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y-k][z].flag = 22;
										block[x+i+1][y-k][z].ID = ID22;
									}
								}
								block[x+1][y-1][z].corner = 1;
								block[x+2][y][z].corner = 2;
							}
							//‰º‚É‚Q~‚Q‚ª‚ ‚éê‡
							else if(block[x+2][y-1][z].flag == 22)
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
										block[x+i+1][y-k][z].flag = 23;
										block[x+i+1][y-k][z].ID = ID23;
									}
								}
								block[x+1][y-1][z].corner = 1;
								block[x+3][y][z].corner = 2;
							}
						}
						//‰º‚ğŒ©‚é
						else if(block[x+2][y][z].flag == 12 && block[x+2][y][z].ID == block[x+1][y][z].ID)
						{
							//¶‚É‚P~‚Q‚ª‚ ‚éê‡
							if(block[x+1][y-1][z].flag == 12 && block[x+2][y-1][z].flag == 12 && block[x+1][y-1][z].ID == block[x+2][y-1][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y-k][z].flag = 22;
										block[x+i+1][y-k][z].ID = ID22;
									}
								}
								block[x+1][y-1][z].corner = 1;
								block[x+2][y][z].corner = 2;
							}
							//¶‚É‚Q~‚Q‚ª‚ ‚éê‡
							else if(block[x+2][y-1][z].flag == 22)
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
										block[x+i+1][y-k][z].flag = 23;
										block[x+i+1][y-k][z].ID = ID23;
									}
								}
								block[x+1][y-2][z].corner = 1;
								block[x+2][y][z].corner = 2;
							}
						}

					}

					//‰E‰º===========================================================
					else if(block[x+1][y+1][z].flag == 12)
					{
						//‰E‚ğŒ©‚é
						if(block[x+1][y+2][z].flag == 12 && block[x+1][y+2][z].ID == block[x+1][y+1][z].ID)
						{
							//‰º‚É‚P~‚Q‚ª‚ ‚éê‡
							if(block[x+2][y+1][z].flag == 12 && block[x+2][y+2][z].flag == 12 && block[x+2][y+1][z].ID ==  block[x+2][y+2][z].ID )
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y+k+1][z].flag = 22;
										block[x+i+1][y+k+1][z].ID = ID22;
									}
								}
								block[x+1][y+1][z].corner = 1;
								block[x+2][y+2][z].corner = 2;
							}
							//‰º‚É‚Q~‚Q‚ª‚ ‚éê‡
							else if(block[x+2][y+2][z].flag == 22)
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
										block[x+i+1][y+k+1][z].flag = 23;
										block[x+i+1][y+k+1][z].ID = ID23;
									}
								}
								block[x+1][y+1][z].corner = 1;
								block[x+3][y+2][z].corner = 2;
							}
						}
						//‰º‚ğŒ©‚é
						else if(block[x+2][y+1][z].flag == 12 && block[x+2][y+1][z].ID == block[x+1][y+1][z].ID)
						{
							//‰E‚É‚P~‚Q‚ª‚ ‚éê‡
							if(block[x+1][y+2][z].flag == 12 && block[x+2][y+2][z].flag == 12 && block[x+1][y+2][z].ID == block[x+2][y+2][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i+1][y+k+1][z].flag = 22;
										block[x+i+1][y+k+1][z].ID = ID22;
									}
								}
								block[x+1][y+1][z].corner = 1;
								block[x+2][y+2][z].corner = 2;
							}
							//‰E‚É‚Q~‚Q‚ª‚ ‚éê‡
							else if(block[x+2][y+2][z].flag == 22)
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
										block[x+i+1][y+k+1][z].flag = 23;
										block[x+i+1][y+k+1][z].ID = ID23;
									}
								}
								block[x+1][y+1][z].corner = 1;
								block[x+2][y+3][z].corner = 2;
							}
						}
					}

				}
			}
		}
	}

	cout<<count<<"ŒÂ‚Ì‚Q~‚Qor‚Q~‚R‚ª@‚P~‚Qi‚P~‚P‚Æ‚P~‚P‚©‚ç‚È‚éj‚Æ‚Q~‚Qi‚P~‚Q‚Æ‚P~‚Q‚©‚ç‚È‚éj‚©‚ç‚Å‚«‚½"<<endl;
	//outputFlag("test6_12_22_to_22_23.txt", VoxSize);

}

//ÅI‡¬
void Small_to_Big_step8(Lego*** block, int*  VoxSize)
{
	int x,y,z;
	int count(0);

	for(z=1; z < VoxSize[2]-1; z++ )
	{
			for(x=1; x < VoxSize[0]-1; x=x+1)
			{
				for(y=1; y < VoxSize[1]-1; y=y+1)
				{
					//¶ã===========================================================
					if(block[x][y][z].flag == 12)
					{
						//ã‚ğŒ©‚é
						if(block[x-1][y][z].flag == 12 && block[x-1][y][z].ID == block[x][y][z].ID)
						{
							//¶‚É‚P~‚Qi‚P~‚P‚Æ‚P~‚P‚É‚æ‚Á‚Ä‡¬‚Å‚«‚½‚à‚Ì‚È‚ç‚Îj‚ª‚ ‚ê‚Î
							if(block[x][y][z].ColorID==block[x-1][y-1][z].ColorID)
							if(block[x-1][y-1][z].flag == 12 && block[x][y-1][z].flag == 12 && block[x-1][y-1][z].ID == block[x][y-1][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y-k][z].flag = 22;
										block[x-i][y-k][z].ID = ID22;
									}
								}
								block[x-1][y-1][z].corner = 1;
								block[x][y][z].corner = 2;

							}
							//¶‚É‚Q~‚Qi‚P~‚Q‚Æ‚P~‚Q‚É‚æ‚Á‚Ä‡¬‚Å‚«‚½‚à‚Ì‚È‚ç‚Îj‚ª‚ ‚ê‚Î
							else if(block[x-1][y-1][z].flag == 22)
							if(block[x][y][z].ColorID==block[x-1][y-1][z].ColorID)
								if(block[x-1][y-1][z].ID==block[x][y-2][z].ID)
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
										block[x-i][y-k][z].flag = 23;
										block[x-i][y-k][z].ID = ID23;
									}
								}
								block[x-1][y-2][z].corner = 1;
								block[x][y][z].corner = 2;
							}
							//¶‚É1~‚Qi‚P~1‚Æ‚P~1‚É‚æ‚Á‚Ä‡¬‚Å‚«‚½‚à‚Ì‚È‚ç‚Îj‚ª‚ ‚ê‚Î
							else if(block[x-2][y][z].flag == 12)
							if(block[x][y][z].ColorID==block[x-2][y][z].ColorID)
								if(block[x-2][y][z].ID==block[x-3][y][z].ID)
							{
								ID14++;
								num12--;
								num12--;
								num14++;
								count++;
									for(int k(0); k<4; k++)
									{
										block[x-k][y][z].flag = 14;
										block[x-k][y][z].ID = ID14;
									}
								block[x-3][y][z].corner = 1;
								block[x][y][z].corner = 2;
							}
								//‰E‚É2~2i1~2‚Æ1~2‚É‚æ‚Á‚Ä‡¬‚Å‚«‚½‚à‚Ì‚È‚ç‚Îj
							else if(block[x-1][y+1][z].flag == 22)
							if(block[x][y][z].ColorID==block[x-1][y+2][z].ColorID)
								if(block[x-1][y+2][z].ID==block[x][y+3][z].ID)
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
										block[x-i][y+k][z].flag = 23;
										block[x-i][y+k][z].ID = ID23;
									}
								}
								block[x-1][y][z].corner = 1;
								block[x][y+2][z].corner = 2;
							}
						}
						

						//¶‚ğŒ©‚é
						else if(block[x][y-1][z].flag == 12 && block[x][y-1][z].ID == block[x][y][z].ID)
						{
							//ã‚É‚P~‚Qi‚P~‚P‚Æ‚P~‚P‚É‚æ‚Á‚Ä‡¬‚Å‚«‚½‚à‚Ì‚È‚ç‚Îj‚ª‚ ‚ê‚Î
							if(block[x][y][z].ColorID==block[x-1][y-1][z].ColorID)
							if(block[x-1][y-1][z].flag == 12 && block[x-1][y][z].flag == 12 && block[x-1][y-1][z].ID == block[x-1][y][z].ID)
							{
								ID22++;
								num12 = num12 - 2;
								num22++;
								count++;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x-i][y-k][z].flag = 22;
										block[x-i][y-k][z].ID = ID22;
									}
								}
								block[x-1][y-1][z].corner = 1;
								block[x][y][z].corner = 2;
							}
							//ã‚É‚Q~‚Qi‚P~‚Q‚Æ‚P~‚Q‚É‚æ‚Á‚Ä‡¬‚Å‚«‚½‚à‚Ì‚È‚ç‚Îj‚ª‚ ‚ê‚Î
							else if(block[x-1][y-1][z].flag == 22)
							if(block[x][y][z].ColorID==block[x-1][y-1][z].ColorID)
								if(block[x-1][y-1][z].ID==block[x-2][y][z].ID)
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
										block[x-i][y-k][z].flag = 23;
										block[x-i][y-k][z].ID = ID23;
									}
								}
								block[x-2][y-1][z].corner = 1;
								block[x][y][z].corner = 2;
							}
				
							//ã‚É1~‚Qi‚P~1‚Æ‚P~1‚É‚æ‚Á‚Ä‡¬‚Å‚«‚½‚à‚Ì‚È‚ç‚Îj‚ª‚ ‚ê‚Î
							else if(block[x][y-2][z].flag == 12)
							if(block[x][y][z].ColorID==block[x][y-2][z].ColorID)
								if(block[x][y-2][z].ID==block[x][y-3][z].ID)
							{
								ID14++;
								num12--;
								num12--;
								num14++;
								count++;
								for(int i(0); i<4; i++)
								{
										block[x][y-i][z].flag = 14;
										block[x][y-i][z].ID = ID14;
								}
								block[x][y-3][z].corner = 1;
								block[x][y][z].corner = 2;
							}
							//‰º‚É‚Q~‚Qi‚P~‚Q‚Æ‚P~‚Q‚É‚æ‚Á‚Ä‡¬‚Å‚«‚½‚à‚Ì‚È‚ç‚Îj‚ª‚ ‚ê‚Î
							else if(block[x+1][y][z].flag == 22)
							if(block[x][y][z].ColorID==block[x+1][y][z].ColorID)
								if(block[x+1][y][z].ID==block[x+2][y-1][z].ID)
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
										block[x+i][y-k][z].flag = 23;
										block[x+i][y-k][z].ID = ID23;
									}
								}
								block[x][y-1][z].corner = 1;
								block[x+2][y][z].corner = 2;
							}
				
						}
					}
				}
			}
		}


	std::cout<<"count: "<<count<<"\nSmall_to_Big_step8 Finish\n"<<endl;
	//outputFlag("test6_12_22_to_22_23.txt", VoxSize);

}

void Coloring_ID(Lego*** block, int*  VoxSize){
	cout << "Coloring ID\n";

	int x,y,z;
	for(int i(0); i<4 ; i++)
		for(z=1; z < VoxSize[2]-1; z++ )
	{
			for(x=1; x < VoxSize[0]-1; x=x+1)
			{
				for(y=1; y < VoxSize[1]-1; y=y+1)
				{
					if(!block[x][y][z].fill)continue;
					if(block[x][y][z].ColorID==0)continue;
					if(block[x][y][z].flag<10)continue;

					if (block[x+1][y][z].flag==block[x][y][z].flag&&block[x+1][y][z].ID==block[x][y][z].ID)
						block[x+1][y][z].ColorID=block[x][y][z].ColorID;
					if (block[x-1][y][z].flag==block[x][y][z].flag&&block[x-1][y][z].ID==block[x][y][z].ID)
						block[x-1][y][z].ColorID=block[x][y][z].ColorID;
					if (block[x][y+1][z].flag==block[x][y][z].flag&&block[x][y+1][z].ID==block[x][y][z].ID)
						block[x][y+1][z].ColorID=block[x][y][z].ColorID;
					if (block[x][y-1][z].flag==block[x][y][z].flag&&block[x][y-1][z].ID==block[x][y][z].ID)
						block[x][y-1][z].ColorID=block[x][y][z].ColorID;
				}
			}
		}
}