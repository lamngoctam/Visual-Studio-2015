#include "../stdafx.h"
#include "../Voxel.h"
#include "../Lego.h"		//LEGOƒuƒƒbƒN‚ğ‘g‚İ—§‚Ä‚é‚½‚ß‚ÌƒNƒ‰ƒX

void outputFlag(string filename, int* size);

extern int num11;		//‚P~‚P‚ÌƒuƒƒbƒN‚Ì”
extern int num12;		//‚P~‚Q‚ÌƒuƒƒbƒN‚Ì”
extern int num22;		//‚Q~‚Q‚ÌƒuƒƒbƒN‚Ì”

extern int ID12;	
extern int ID22;	

//Lš‚ğ1~‚P@‚Æ@‚P~‚Q‚É’u‚«Š·‚¦‚é
void Small_to_Big_step0( Lego*** block, int* VoxSize)
{
	int Left_Up(0);
	int Left_Down(0);
	int Right_Up(0);
	int Right_Down(0);

	int count(0);		//Lš‚ª‚P~‚P‚Æ‚P~‚Q‚É•ªŠ„‚Å‚«‚È‚©‚Á‚½ŒÂ”
	int countLN(0);
	int x,y,z;
	//Šï”‘w
	for(z=1; z < VoxSize[2]-1; z++ )
	{
		if(z%2)
		{
			for(x=1; x < VoxSize[0]-1; x=x+2)
			{
				for(y=1; y < VoxSize[1]-1; y=y+2)
				{
					//’–Úƒ{ƒNƒZƒ‹‚ÌID‚ª‚R‚É‚È‚éê‡
					if(block[x][y][z].flag == 3)
					{
						//                                                                                                                                
						//ƒP[ƒX‚Q
						if(block[x][y+1][z].flag == 0)
						{
							countLN++;
							//ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							if( (block[x][y][z-1].flag > 3 || block[x][y][z+1].flag > 3) &&  block[x+1][y+1][z-1].flag < 4 && block[x+1][y+1][z+1].flag < 4 )
							{
								block[x][y][z].flag = 1;
								block[x+1][y][z].flag = 2; 
								block[x+1][y+1][z].flag = 2;
								num11++;
								num12++;
							}
							//‚à‚¤ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							else if( block[x][y][z-1].flag < 4 && block[x][y][z+1].flag < 4 && ( block[x+1][y+1][z-1].flag > 3 || block[x+1][y+1][z+1].flag > 3))
							{
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 2; 
								block[x+1][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//’–Ú‚Ì‚Q‚Â‚Ìƒ{ƒNƒZƒ‹‚Ìã‰ºi‚S‚Âj‚Æ‚à‚É‚P~‚PˆÈ‰º‚Ìƒ{ƒNƒZƒ‹‚Å‚ ‚é‚Æ‚«
							else if(block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2)
							{
								count++;
								num22++;
								//‚Q~‚Q‚É–³—‚â‚è•Ï‚¦‚Ü‚·‚æ‚ñ‚ñ‚ñ‚ñ`
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x][y+1][z].fill = true;
								cout<<"•ªŠ„‚Å‚«‚È‚©‚Á‚½‚©‚ç2~2‚É•Ï‚¦‚½‚¼I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//ã‹LˆÈŠO‚Ì‚Í
							else
							{
								//ã‚Æ‰º‚Ìƒ{ƒNƒZƒ‹‚Ìƒtƒ‰ƒO‚Ì’l‚ğ‚©‚¯‚Ä‘å‚«‚¢•û‚ğ•ªŠ„‚·‚é
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
						//ƒP[ƒX‚R
						else if(block[x+1][y+1][z].flag == 0)
						{
							countLN++;
							//ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							if( (block[x+1][y][z-1].flag >3  ||  block[x+1][y][z+1].flag > 3) && block[x][y+1][z-1].flag < 4 &&  block[x][y+1][z+1].flag < 4 )
							{
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 1; 
								block[x][y+1][z].flag = 2; 
								num11++;
								num12++;
							}
							//‚à‚¤ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							else if( block[x+1][y][z-1].flag < 4  &&  block[x+1][y][z+1].flag < 4 && (block[x][y+1][z-1].flag > 3 &&  block[x][y+1][z+1].flag > 3) )
							{
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 2; 
								block[x][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//’–Ú‚Ì‚Q‚Â‚Ìƒ{ƒNƒZƒ‹‚Ìã‰ºi‚S‚Âj‚Æ‚à‚É‚P~‚PˆÈ‰º‚Ìƒ{ƒNƒZƒ‹‚Å‚ ‚é‚Æ‚«
							else if(block[x+1][y][z-1].flag < 2 &&  block[x+1][y][z+1].flag < 2 && block[x][y+1][z-1].flag < 2 &&  block[x][y+1][z+1].flag < 2 )
							{
								count++;
								num22++;
								//‚Q~‚Q‚É–³—‚â‚è•Ï‚¦‚Ü‚·‚æ‚ñ‚ñ‚ñ‚ñ`
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x+1][y+1][z].fill = true;
								cout<<"•ªŠ„‚Å‚«‚È‚©‚Á‚½‚©‚ç2~2‚É•Ï‚¦‚½‚¼I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//ã‹LˆÈŠO‚Ì‚Í
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
						//ƒP[ƒX‚S
						else if(block[x+1][y][z].flag == 0)
						{
							countLN++;
							//ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							if( (block[x][y][z-1].flag > 3 ||  block[x][y][z+1].flag > 3) && block[x+1][y+1][z-1].flag < 4 &&  block[x+1][y+1][z+1].flag < 4 )
							{
								block[x][y][z].flag = 1;
								block[x][y+1][z].flag = 2; 
								block[x+1][y+1][z].flag = 2; 
								num11++;
								num12++;
							}
							//‚à‚¤ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							else if( block[x][y][z-1].flag < 4 &&  block[x][y][z+1].flag < 4 && (block[x+1][y+1][z-1].flag > 3 ||  block[x+1][y+1][z+1].flag > 3) )
							{
								block[x][y][z].flag = 2;
								block[x][y+1][z].flag = 2; 
								block[x+1][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//’–Úƒ{ƒNƒZƒ‹‚Ìã‰º4‚Â‚Æ‚à‚É‚P~‚P‚Ü‚½‚Í‰½‚à‚È‚¢ê‡
							else if( block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2 )
							{
								count++;
								num22++;
								//‚Q~‚Q‚É–³—‚â‚è•Ï‚¦‚Ü‚·‚æ‚ñ‚ñ‚ñ‚ñ`
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x+1][y][z].fill = true;
								cout<<"•ªŠ„‚Å‚«‚È‚©‚Á‚½‚©‚ç2~2‚É•Ï‚¦‚½‚¼I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//ã‹LˆÈŠO‚Ìê‡
							else
							{
								//ã‚Æ‰º‚Ìƒ{ƒNƒZƒ‹‚Ìƒtƒ‰ƒO‚Ì’l‚ğ‚©‚¯‚Ä‘å‚«‚¢•û‚ğ•ªŠ„‚·‚é
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
					//’–Úƒ{ƒNƒZƒ‹‚ÌID‚ª0‚É‚È‚éê‡
					else if(block[x][y][z].flag == 0 )
					{
						if(block[x][y+1][z].flag == 3)			//ƒP[ƒX‚P
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
								//‚Q~‚Q‚É–³—‚â‚è•Ï‚¦‚Ü‚·‚æ‚ñ‚ñ‚ñ‚ñ`
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x][y][z].fill = true;
								cout<<"•ªŠ„‚Å‚«‚È‚©‚Á‚½‚©‚ç2~2‚É•Ï‚¦‚½‚¼I"<<x<<" "<<y<<" "<<z<<endl;
							}
							else
							{
								//ã‚Æ‰º‚Ìƒ{ƒNƒZƒ‹‚Ìƒtƒ‰ƒO‚Ì’l‚ğ‚©‚¯‚Ä‘å‚«‚¢•û‚ğ•ªŠ„‚·‚é
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
		//‹ô”‘w
		else
		{
			for(x=0; x < VoxSize[0]-1; x=x+2)
			{
				for(y=0; y < VoxSize[1]-1; y=y+2)
				{
					//’–Úƒ{ƒNƒZƒ‹‚ÌID‚ª‚R‚É‚È‚éê‡
					if(block[x][y][z].flag == 3)
					{
						//                                                                                                                                
						//ƒP[ƒX‚Q
						if(block[x][y+1][z].flag == 0)
						{
							countLN++;
							//ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							if( (block[x][y][z-1].flag > 3 || block[x][y][z+1].flag > 3) &&  block[x+1][y+1][z-1].flag < 4 && block[x+1][y+1][z+1].flag < 4 )
							{
								block[x][y][z].flag = 1;
								block[x+1][y][z].flag = 2; 
								block[x+1][y+1][z].flag = 2; 
								num11++;
								num12++;
							}
							//‚à‚¤ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							else if( block[x][y][z-1].flag < 4 && block[x][y][z+1].flag < 4 && ( block[x+1][y+1][z-1].flag > 3 || block[x+1][y+1][z+1].flag > 3))
							{
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 2; 
								block[x+1][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//’–Ú‚Ì‚Q‚Â‚Ìƒ{ƒNƒZƒ‹‚Ìã‰ºi‚S‚Âj‚Æ‚à‚É‚P~‚PˆÈ‰º‚Ìƒ{ƒNƒZƒ‹‚Å‚ ‚é‚Æ‚«
							else if(block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2)
							{
								count++;
								num22++;
								//‚Q~‚Q‚É–³—‚â‚è•Ï‚¦‚Ü‚·‚æ‚ñ‚ñ‚ñ‚ñ`
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x][y+1][z].fill = true;
								cout<<"•ªŠ„‚Å‚«‚È‚©‚Á‚½‚©‚ç2~2‚É•Ï‚¦‚½‚¼I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//ã‹LˆÈŠO‚Ì‚Í
							else
							{
								//ã‚Æ‰º‚Ìƒ{ƒNƒZƒ‹‚Ìƒtƒ‰ƒO‚Ì’l‚ğ‚©‚¯‚Ä‘å‚«‚¢•û‚ğ•ªŠ„‚·‚é
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
						//ƒP[ƒX‚R
						else if(block[x+1][y+1][z].flag == 0)
						{
							countLN++;
							//ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							if( (block[x+1][y][z-1].flag >3  ||  block[x+1][y][z+1].flag > 3) && block[x][y+1][z-1].flag < 4 &&  block[x][y+1][z+1].flag < 4 )
							{
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 1; 
								block[x][y+1][z].flag = 2; 
								num11++;
								num12++;
							}
							//‚à‚¤ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							else if( block[x+1][y][z-1].flag < 4  &&  block[x+1][y][z+1].flag < 4 && (block[x][y+1][z-1].flag > 3 &&  block[x][y+1][z+1].flag > 3) )
							{
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 2; 
								block[x][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//’–Ú‚Ì‚Q‚Â‚Ìƒ{ƒNƒZƒ‹‚Ìã‰ºi‚S‚Âj‚Æ‚à‚É‚P~‚PˆÈ‰º‚Ìƒ{ƒNƒZƒ‹‚Å‚ ‚é‚Æ‚«
							else if(block[x+1][y][z-1].flag < 2 &&  block[x+1][y][z+1].flag < 2 && block[x][y+1][z-1].flag < 2 &&  block[x][y+1][z+1].flag < 2 )
							{
								count++;
								num22++;
								//‚Q~‚Q‚É–³—‚â‚è•Ï‚¦‚Ü‚·‚æ‚ñ‚ñ‚ñ‚ñ`
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x+1][y+1][z].fill = true;
								cout<<"•ªŠ„‚Å‚«‚È‚©‚Á‚½‚©‚ç2~2‚É•Ï‚¦‚½‚¼I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//ã‹LˆÈŠO‚Ì‚Í
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
						//ƒP[ƒX‚S
						else if(block[x+1][y][z].flag == 0)
						{
							countLN++;
							//ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							if( (block[x][y][z-1].flag > 3 ||  block[x][y][z+1].flag > 3) && block[x+1][y+1][z-1].flag < 4 &&  block[x+1][y+1][z+1].flag < 4 )
							{
								block[x][y][z].flag = 1;
								block[x][y+1][z].flag = 2; 
								block[x+1][y+1][z].flag = 2; 
								num11++;
								num12++;
							}
							//‚à‚¤ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							else if( block[x][y][z-1].flag < 4 &&  block[x][y][z+1].flag < 4 && (block[x+1][y+1][z-1].flag > 3 ||  block[x+1][y+1][z+1].flag > 3) )
							{
								block[x][y][z].flag = 2;
								block[x][y+1][z].flag = 2; 
								block[x+1][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//’–Úƒ{ƒNƒZƒ‹‚Ìã‰º4‚Â‚Æ‚à‚É‚P~‚P‚Ü‚½‚Í‰½‚à‚È‚¢ê‡
							else if( block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2 )
							{
								count++;
								num22++;
								//‚Q~‚Q‚É–³—‚â‚è•Ï‚¦‚Ü‚·‚æ‚ñ‚ñ‚ñ‚ñ`
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x+1][y][z].fill = true;
								cout<<"•ªŠ„‚Å‚«‚È‚©‚Á‚½‚©‚ç2~2‚É•Ï‚¦‚½‚¼I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//ã‹LˆÈŠO‚Ìê‡
							else
							{
								//ã‚Æ‰º‚Ìƒ{ƒNƒZƒ‹‚Ìƒtƒ‰ƒO‚Ì’l‚ğ‚©‚¯‚Ä‘å‚«‚¢•û‚ğ•ªŠ„‚·‚é
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
					//’–Úƒ{ƒNƒZƒ‹‚ÌID‚ª0‚É‚È‚éê‡
					else if(block[x][y][z].flag == 0 )
					{
						if(block[x][y+1][z].flag == 3)			//ƒP[ƒX‚P
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
								//‚Q~‚Q‚É–³—‚â‚è•Ï‚¦‚Ü‚·‚æ‚ñ‚ñ‚ñ‚ñ`
								for(int i(0); i<2; i++)
									for(int k(0); k<2; k++)
										block[x+i][y+k][z].flag = 4;
								block[x][y][z].fill = true;
								cout<<"•ªŠ„‚Å‚«‚È‚©‚Á‚½‚©‚ç2~2‚É•Ï‚¦‚½‚¼I"<<x<<" "<<y<<" "<<z<<endl;
							}
							else
							{
								//ã‚Æ‰º‚Ìƒ{ƒNƒZƒ‹‚Ìƒtƒ‰ƒO‚Ì’l‚ğ‚©‚¯‚Ä‘å‚«‚¢•û‚ğ•ªŠ„‚·‚é
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

	cout<<countLN<<"ŒÂ’†@"<<count<<" ŒÂ‚ÌL‚ğ‚P~‚P‚Æ‚P~‚Q‚É•ªŠ„‚Å‚«‚È‚©‚Á‚½I"<<endl;
	outputFlag("test00_L_to11_12.txt", VoxSize);

}

void Small_to_Big_step0_color( Lego*** block, int* VoxSize)
{
	int Left_Up(0);
	int Left_Down(0);
	int Right_Up(0);
	int Right_Down(0);

	int count(0);		//Lš‚ª‚P~‚P‚Æ‚P~‚Q‚É•ªŠ„‚Å‚«‚È‚©‚Á‚½ŒÂ”
	int countLN(0);
	int x,y,z;
	//Šï”‘w
	for(z=1; z < VoxSize[2]-1; z++ )
	{
		if(z%2)
		{
			for(x=1; x < VoxSize[0]-1; x=x+2)
			{
				for(y=1; y < VoxSize[1]-1; y=y+2)
				{
					//’–Úƒ{ƒNƒZƒ‹‚ÌID‚ª‚R‚É‚È‚éê‡
					if(block[x][y][z].flag == 3)
					{
						//                                                                                                                                
						//ƒP[ƒX‚Q(‚Q~‚Q‚Ìƒ}ƒXƒN‚É‘Î‚µ‚Ä‚R‚Â‚Ìƒ{ƒNƒZƒ‹‚ª‚Ç‚Ì‚æ‚¤‚É”z’u‚µ‚Ä‚¢‚é‚Ì‚©)
						if(block[x][y+1][z].flag == 0)
						{
							countLN++;
							//ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							if( (block[x][y][z-1].flag > 3 || block[x][y][z+1].flag > 3) &&  block[x+1][y+1][z-1].flag < 4 && block[x+1][y+1][z+1].flag < 4 )
							{
								ID12++;
								block[x][y][z].flag = 1;
								block[x+1][y][z].flag = 2;			block[x+1][y][z].ID = ID12; 
								block[x+1][y+1][z].flag = 2;		block[x+1][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//‚à‚¤ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							else if( block[x][y][z-1].flag < 4 && block[x][y][z+1].flag < 4 && ( block[x+1][y+1][z-1].flag > 3 || block[x+1][y+1][z+1].flag > 3))
							{
								ID12++;
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 2;			block[x+1][y][z].ID = ID12; 
								block[x+1][y+1][z].flag = 1;		block[x+1][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//’–Ú‚Ì‚Q‚Â‚Ìƒ{ƒNƒZƒ‹‚Ìã‰ºi‚S‚Âj‚Æ‚à‚É‚P~‚PˆÈ‰º‚Ìƒ{ƒNƒZƒ‹‚Å‚ ‚é‚Æ‚«
							else if(block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2)
							{
								ID22++;
								count++;
								num22++;
								//‚Q~‚Q‚É–³—‚â‚è•Ï‚¦‚Ü‚·
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x][y+1][z].fill = true;
								cout<<"•ªŠ„‚Å‚«‚È‚©‚Á‚½‚©‚ç2~2‚É•Ï‚¦‚½‚¼I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//ã‹LˆÈŠO‚Ì‚Í
							else
							{
								//ã‚Æ‰º‚Ìƒ{ƒNƒZƒ‹‚Ìƒtƒ‰ƒO‚Ì’l‚ğ‚©‚¯‚Ä‘å‚«‚¢•û‚ğ•ªŠ„‚·‚é
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
						//ƒP[ƒX‚R
						else if(block[x+1][y+1][z].flag == 0)
						{
							countLN++;
							//ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							if( (block[x+1][y][z-1].flag >3  ||  block[x+1][y][z+1].flag > 3) && block[x][y+1][z-1].flag < 4 &&  block[x][y+1][z+1].flag < 4 )
							{
								ID12++;
								block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
								block[x+1][y][z].flag = 1; 
								block[x][y+1][z].flag = 2;				block[x][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//‚à‚¤ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							else if( block[x+1][y][z-1].flag < 4  &&  block[x+1][y][z+1].flag < 4 && (block[x][y+1][z-1].flag > 3 &&  block[x][y+1][z+1].flag > 3) )
							{
								ID12++;
								block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
								block[x+1][y][z].flag = 2; 				block[x+1][y][z].ID = ID12; 
								block[x][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//’–Ú‚Ì‚Q‚Â‚Ìƒ{ƒNƒZƒ‹‚Ìã‰ºi‚S‚Âj‚Æ‚à‚É‚P~‚PˆÈ‰º‚Ìƒ{ƒNƒZƒ‹‚Å‚ ‚é‚Æ‚«
							else if(block[x+1][y][z-1].flag < 2 &&  block[x+1][y][z+1].flag < 2 && block[x][y+1][z-1].flag < 2 &&  block[x][y+1][z+1].flag < 2 )
							{
								ID22++;
								count++;
								num22++;
								//‚Q~‚Q‚É–³—‚â‚è•Ï‚¦‚Ü‚·‚æ‚ñ‚ñ‚ñ‚ñ`
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x+1][y+1][z].fill = true;
								cout<<"•ªŠ„‚Å‚«‚È‚©‚Á‚½‚©‚ç2~2‚É•Ï‚¦‚½‚¼I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//ã‹LˆÈŠO‚Ì‚Í
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
						//ƒP[ƒX‚S
						else if(block[x+1][y][z].flag == 0)
						{
							countLN++;
							//ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							if( (block[x][y][z-1].flag > 3 ||  block[x][y][z+1].flag > 3) && block[x+1][y+1][z-1].flag < 4 &&  block[x+1][y+1][z+1].flag < 4 )
							{
								ID12++;
								block[x][y][z].flag = 1;
								block[x][y+1][z].flag = 2; 				block[x][y+1][z].ID = ID12; 
								block[x+1][y+1][z].flag = 2;			block[x+1][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//‚à‚¤ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							else if( block[x][y][z-1].flag < 4 &&  block[x][y][z+1].flag < 4 && (block[x+1][y+1][z-1].flag > 3 ||  block[x+1][y+1][z+1].flag > 3) )
							{
								ID12++;
								block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
								block[x][y+1][z].flag = 2;				block[x][y+1][z].ID = ID12; 
								block[x+1][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//’–Úƒ{ƒNƒZƒ‹‚Ìã‰º4‚Â‚Æ‚à‚É‚P~‚P‚Ü‚½‚Í‰½‚à‚È‚¢ê‡
							else if( block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2 )
							{
								ID22++;
								count++;
								num22++;
								//‚Q~‚Q‚É–³—‚â‚è•Ï‚¦‚Ü‚·‚æ‚ñ‚ñ‚ñ‚ñ`
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x+1][y][z].fill = true;
								cout<<"•ªŠ„‚Å‚«‚È‚©‚Á‚½‚©‚ç2~2‚É•Ï‚¦‚½‚¼I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//ã‹LˆÈŠO‚Ìê‡
							else
							{
								//ã‚Æ‰º‚Ìƒ{ƒNƒZƒ‹‚Ìƒtƒ‰ƒO‚Ì’l‚ğ‚©‚¯‚Ä‘å‚«‚¢•û‚ğ•ªŠ„‚·‚é
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
					//’–Úƒ{ƒNƒZƒ‹‚ÌID‚ª0‚É‚È‚éê‡
					else if(block[x][y][z].flag == 0 )
					{
						if(block[x][y+1][z].flag == 3)			//ƒP[ƒX‚P
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
								//‚Q~‚Q‚É–³—‚â‚è•Ï‚¦‚Ü‚·‚æ‚ñ‚ñ‚ñ‚ñ`
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x][y][z].fill = true;
								cout<<"•ªŠ„‚Å‚«‚È‚©‚Á‚½‚©‚ç2~2‚É•Ï‚¦‚½‚¼I"<<x<<" "<<y<<" "<<z<<endl;
							}
							else
							{
								//ã‚Æ‰º‚Ìƒ{ƒNƒZƒ‹‚Ìƒtƒ‰ƒO‚Ì’l‚ğ‚©‚¯‚Ä‘å‚«‚¢•û‚ğ•ªŠ„‚·‚é
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
		//‹ô”‘w
		else
		{
			for(x=0; x < VoxSize[0]-1; x=x+2)
			{
				for(y=0; y < VoxSize[1]-1; y=y+2)
				{
					//’–Úƒ{ƒNƒZƒ‹‚ÌID‚ª‚R‚É‚È‚éê‡
					if(block[x][y][z].flag == 3)
					{
						//                                                                                                                                
						//ƒP[ƒX‚Q
						if(block[x][y+1][z].flag == 0)
						{
							countLN++;
							//ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							if( (block[x][y][z-1].flag > 3 || block[x][y][z+1].flag > 3) &&  block[x+1][y+1][z-1].flag < 4 && block[x+1][y+1][z+1].flag < 4 )
							{
								ID12++;
								block[x][y][z].flag = 1;
								block[x+1][y][z].flag = 2;			block[x+1][y][z].ID = ID12; 
								block[x+1][y+1][z].flag = 2;		block[x+1][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//‚à‚¤ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							else if( block[x][y][z-1].flag < 4 && block[x][y][z+1].flag < 4 && ( block[x+1][y+1][z-1].flag > 3 || block[x+1][y+1][z+1].flag > 3))
							{
								ID12++;
								block[x][y][z].flag = 2;
								block[x+1][y][z].flag = 2;			block[x+1][y][z].ID = ID12; 
								block[x+1][y+1][z].flag = 1;		block[x+1][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//’–Ú‚Ì‚Q‚Â‚Ìƒ{ƒNƒZƒ‹‚Ìã‰ºi‚S‚Âj‚Æ‚à‚É‚P~‚PˆÈ‰º‚Ìƒ{ƒNƒZƒ‹‚Å‚ ‚é‚Æ‚«
							else if(block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2)
							{
								ID22++;
								count++;
								num22++;
								//‚Q~‚Q‚É–³—‚â‚è•Ï‚¦‚Ü‚·‚æ‚ñ‚ñ‚ñ‚ñ`
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x][y+1][z].fill = true;
								cout<<"•ªŠ„‚Å‚«‚È‚©‚Á‚½‚©‚ç2~2‚É•Ï‚¦‚½‚¼I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//ã‹LˆÈŠO‚Ì‚Í
							else
							{
								//ã‚Æ‰º‚Ìƒ{ƒNƒZƒ‹‚Ìƒtƒ‰ƒO‚Ì’l‚ğ‚©‚¯‚Ä‘å‚«‚¢•û‚ğ•ªŠ„‚·‚é
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
						//ƒP[ƒX‚R
						else if(block[x+1][y+1][z].flag == 0)
						{
							countLN++;
							//ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							if( (block[x+1][y][z-1].flag >3  ||  block[x+1][y][z+1].flag > 3) && block[x][y+1][z-1].flag < 4 &&  block[x][y+1][z+1].flag < 4 )
							{
								ID12++;
								block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
								block[x+1][y][z].flag = 1; 
								block[x][y+1][z].flag = 2;				block[x][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//‚à‚¤ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							else if( block[x+1][y][z-1].flag < 4  &&  block[x+1][y][z+1].flag < 4 && (block[x][y+1][z-1].flag > 3 &&  block[x][y+1][z+1].flag > 3) )
							{
								ID12++;
								block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
								block[x+1][y][z].flag = 2; 				block[x+1][y][z].ID = ID12; 
								block[x][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//’–Ú‚Ì‚Q‚Â‚Ìƒ{ƒNƒZƒ‹‚Ìã‰ºi‚S‚Âj‚Æ‚à‚É‚P~‚PˆÈ‰º‚Ìƒ{ƒNƒZƒ‹‚Å‚ ‚é‚Æ‚«
							else if(block[x+1][y][z-1].flag < 2 &&  block[x+1][y][z+1].flag < 2 && block[x][y+1][z-1].flag < 2 &&  block[x][y+1][z+1].flag < 2 )
							{
								ID22++;
								count++;
								num22++;
								//‚Q~‚Q‚É–³—‚â‚è•Ï‚¦‚Ü‚·‚æ‚ñ‚ñ‚ñ‚ñ`
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x+1][y+1][z].fill = true;
								cout<<"•ªŠ„‚Å‚«‚È‚©‚Á‚½‚©‚ç2~2‚É•Ï‚¦‚½‚¼I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//ã‹LˆÈŠO‚Ì‚Í
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
						//ƒP[ƒX‚S
						else if(block[x+1][y][z].flag == 0)
						{
							countLN++;
							//ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							if( (block[x][y][z-1].flag > 3 ||  block[x][y][z+1].flag > 3) && block[x+1][y+1][z-1].flag < 4 &&  block[x+1][y+1][z+1].flag < 4 )
							{
								ID12++;
								block[x][y][z].flag = 1;
								block[x][y+1][z].flag = 2; 				block[x][y+1][z].ID = ID12; 
								block[x+1][y+1][z].flag = 2;			block[x+1][y+1][z].ID = ID12; 
								num11++;
								num12++;
							}
							//‚à‚¤ˆê•û‚Ìƒ{ƒNƒZƒ‹‚Ìã‚Ü‚½‚Í‰º‚É‚Ì‚İ‚Q~‚Q‚ª‚ ‚Á‚½‚ç‚»‚ê‚ğ‚P~‚P‚É‚·‚é
							else if( block[x][y][z-1].flag < 4 &&  block[x][y][z+1].flag < 4 && (block[x+1][y+1][z-1].flag > 3 ||  block[x+1][y+1][z+1].flag > 3) )
							{
								ID12++;
								block[x][y][z].flag = 2;					block[x][y][z].ID = ID12;
								block[x][y+1][z].flag = 2;				block[x][y+1][z].ID = ID12; 
								block[x+1][y+1][z].flag = 1; 
								num11++;
								num12++;
							}
							//’–Úƒ{ƒNƒZƒ‹‚Ìã‰º4‚Â‚Æ‚à‚É‚P~‚P‚Ü‚½‚Í‰½‚à‚È‚¢ê‡
							else if( block[x][y][z-1].flag < 2 &&  block[x][y][z+1].flag < 2 && block[x+1][y+1][z-1].flag < 2 &&  block[x+1][y+1][z+1].flag < 2 )
							{
								ID22++;
								count++;
								num22++;
								//‚Q~‚Q‚É–³—‚â‚è•Ï‚¦‚Ü‚·‚æ‚ñ‚ñ‚ñ‚ñ`
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x+1][y][z].fill = true;
								cout<<"•ªŠ„‚Å‚«‚È‚©‚Á‚½‚©‚ç2~2‚É•Ï‚¦‚½‚¼I"<<x<<" "<<y<<" "<<z<<endl;
							}
							//ã‹LˆÈŠO‚Ìê‡
							else
							{
								//ã‚Æ‰º‚Ìƒ{ƒNƒZƒ‹‚Ìƒtƒ‰ƒO‚Ì’l‚ğ‚©‚¯‚Ä‘å‚«‚¢•û‚ğ•ªŠ„‚·‚é
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
					//’–Úƒ{ƒNƒZƒ‹‚ÌID‚ª0‚É‚È‚éê‡
					else if(block[x][y][z].flag == 0 )
					{
						if(block[x][y+1][z].flag == 3)			//ƒP[ƒX‚P
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
								//‚Q~‚Q‚É–³—‚â‚è•Ï‚¦‚Ü‚·‚æ‚ñ‚ñ‚ñ‚ñ`
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i][y+k][z].flag = 4;
										block[x+i][y+k][z].ID = ID22;
									}
								}
								block[x][y][z].fill = true;
								cout<<"•ªŠ„‚Å‚«‚È‚©‚Á‚½‚©‚ç2~2‚É•Ï‚¦‚½‚¼I"<<x<<" "<<y<<" "<<z<<endl;
							}
							else
							{
								//ã‚Æ‰º‚Ìƒ{ƒNƒZƒ‹‚Ìƒtƒ‰ƒO‚Ì’l‚ğ‚©‚¯‚Ä‘å‚«‚¢•û‚ğ•ªŠ„‚·‚é
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

	cout<<countLN<<"ŒÂ’†@"<<count<<" ŒÂ‚ÌL‚ğ‚P~‚P‚Æ‚P~‚Q‚É•ªŠ„‚Å‚«‚È‚©‚Á‚½I"<<endl;
	//outputFlag("test00_L_to11_12.txt", VoxSize);

}

