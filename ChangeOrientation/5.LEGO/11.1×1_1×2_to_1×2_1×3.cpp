#include "../stdafx.h"
#include "../Voxel.h"
#include "../Lego.h"		//LEGOƒuƒƒbƒN‚ğ‘g‚İ—§‚Ä‚é‚½‚ß‚ÌƒNƒ‰ƒX

extern int ID12;			
extern int ID13;
extern int ID14;

extern int num11;		//‚P~‚P‚ÌƒuƒƒbƒN‚Ì”
extern int num12;		//‚P~‚Q‚ÌƒuƒƒbƒN‚Ì”
extern int num13;		//‚P~‚R‚ÌƒuƒƒbƒN‚Ì”
extern int num14;		//‚P~‚S‚ÌƒuƒƒbƒN‚Ì”
extern int num22;		//‚Q~‚Q‚ÌƒuƒƒbƒN‚Ì”
extern int num23;		//‚Q~‚R‚ÌƒuƒƒbƒN‚Ì”
extern int num24;		//‚Q~‚S‚ÌƒuƒƒbƒN‚Ì”

void outputFlag(string filename, int* size);

//‚P~‚P‚Ì‚S•ûŒü‚É@‚P~‚P@‚Ü‚½‚Í@‚P~‚Q@‚ª‚ ‚Á‚½‚ç@Œ‹‡‚³‚¹‚é
//‚Q‚O‚P‚RE‚VE‚Q‚Oi“yj‚P~‚P@{@‚P~‚Q@{@‚P~‚P@¨@‚P~‚S‚É‚µ‚½•û‚ª‚¢‚¢H@‚»‚ê‚Æ‚àŒã‚Å@‚P~‚R@{@‚P~‚P@¨@‚P~‚S
void Small_to_Big_step1(Lego*** block, int* VoxSize)
{
	for(int z(1); z < VoxSize[2]-1; z++ )
	{
		//Šï”‘w
		if(z%2)
		{
			for(int x(1); x < VoxSize[0]-1; x=x+2)
			{
				for(int y(1); y < VoxSize[1]-1; y=y+2)
				{
					//                                                                                                
					//¶ã‚ª‚P~‚P‚Ìê‡
					if(block[x][y][z].flag == 1)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						if(block[x-1][y][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x-1][y][z].flag = 12;		block[x-1][y][z].ID = ID12;	block[x-1][y][z].corner = 1;
							goto Odd_Right_Up;		//continue‚ğg‚í‚È‚¢‚Ì‚Í‚S‚Ü‚·‚Ì’†‚Å‚P~‚P‚ª‘ÎŠpü‚Å‘¶İ‚·‚éê‡‚É‚à‚¤ˆê•û‚ªŒvZ‚³‚ê‚È‚¢
							//continue;
						}
						if(block[x][y-1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							//‚P~‚Q‚É‚·‚é
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x][y-1][z].flag = 12;		block[x][y-1][z].ID = ID12;	block[x][y-1][z].corner = 1;
							goto Odd_Right_Up;
						}
						//‚P~‚Q‚ª‚ ‚éê‡
						if(block[x-1][y][z].flag == 2 )
						{
							if(block[x-2][y][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								//‚P~‚R‚É‚·‚é
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
								//‚P~‚R‚É‚·‚é
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
					//‰Eã‚ª‚P~‚P‚Ìê‡
					if(block[x][y+1][z].flag == 1)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						//‚P~‚P‚ª‚ ‚éê‡
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
						//‚P~‚Q‚ª‚ ‚éê‡
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
					//¶‰º‚ª‚P~‚P‚Ìê‡
					if(block[x+1][y][z].flag == 1)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						//‚P~‚P‚ª‚ ‚éê‡
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
						//‚P~‚Q‚ª‚ ‚éê‡
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
					//‰E‰º
					if(block[x+1][y+1][z].flag == 1)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						//‚P~‚P‚ª‚ ‚éê‡
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
						//‚P~‚Q‚ª‚ ‚éê‡
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

		//‹ô”‘w
		else
		{
			for(int x(0); x < VoxSize[0]-1; x=x+2)
			{
				for(int y(0); y < VoxSize[1]-1; y=y+2)
				{
					//                                                                                                
					//¶ã‚ª‚P~‚P‚Ìê‡
					if(block[x][y][z].flag == 1)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						if(block[x-1][y][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x-1][y][z].flag = 12;		block[x-1][y][z].ID = ID12;	block[x-1][y][z].corner = 1;
							goto Even_Right_Up;		//continue‚ğg‚í‚È‚¢‚Ì‚Í‚S‚Ü‚·‚Ì’†‚Å‚P~‚P‚ª‘ÎŠpü‚Å‘¶İ‚·‚éê‡‚É‚à‚¤ˆê•û‚ªŒvZ‚³‚ê‚È‚¢
							//continue;
						}
						if(block[x][y-1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							//‚P~‚Q‚É‚·‚é
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x][y-1][z].flag = 12;		block[x][y-1][z].ID = ID12;	block[x][y-1][z].corner = 1;
							goto Even_Right_Up;
						}
						//‚P~‚Q‚ª‚ ‚éê‡
						if(block[x-1][y][z].flag == 2)
						{
							if(block[x-2][y][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								//‚P~‚R‚É‚·‚é
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
								//‚P~‚R‚É‚·‚é
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
					//‰Eã‚ª‚P~‚P‚Ìê‡
					if(block[x][y+1][z].flag == 1)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						//‚P~‚P‚ª‚ ‚éê‡
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
						//‚P~‚Q‚ª‚ ‚éê‡
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
					//¶‰º‚ª‚P~‚P‚Ìê‡
					if(block[x+1][y][z].flag == 1)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						//‚P~‚P‚ª‚ ‚éê‡
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
						//‚P~‚Q‚ª‚ ‚éê‡
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
					//‰E‰º
					if(block[x+1][y+1][z].flag == 1)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						//‚P~‚P‚ª‚ ‚éê‡
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
						//‚P~‚Q‚ª‚ ‚éê‡
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

//F‚Ì‘Šˆá‚ğl—¶‚µ‚Ä‡¬‚·‚é‚©”Û‚©‚ğ”»’f‚·‚é2013/9/14
void Small_to_Big_step1_color(Lego*** block, int* VoxSize)
{
	for(int z(1); z < VoxSize[2]-1; z++ )
	{
		//Šï”‘w
		if(z%2)
		{
			for(int x(1); x < VoxSize[0]-1; x=x+2)
			{
				for(int y(1); y < VoxSize[1]-1; y=y+2)
				{
					//                                                                                                
					//¶ã‚ª‚P~‚P‚Ìê‡
					if(block[x][y][z].flag == 1)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						if(block[x-1][y][z].flag == 1)
						{
							//2‚Â‚ÌƒuƒƒbƒN‚ÌF‚ª“¯‚¶‚Ü‚½‚Í‚Ç‚¿‚ç‚©‚Ìƒ{ƒNƒZƒ‹‚ÉF‚ğ‚½‚È‚¢‚È‚ç‚Î‡¬‚·‚é
							if(block[x][y][z].ColorID == block[x-1][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x-1][y][z].ColorID<1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
								block[x-1][y][z].flag = 12;		block[x-1][y][z].ID = ID12;	block[x-1][y][z].corner = 1;
								goto Odd_Right_Up;		//continue‚ğg‚í‚È‚¢‚Ì‚Í‚S‚Ü‚·‚Ì’†‚Å‚P~‚P‚ª‘ÎŠpü‚Å‘¶İ‚·‚éê‡‚É‚à‚¤ˆê•û‚ªŒvZ‚³‚ê‚È‚¢
							}
						}
						if(block[x][y-1][z].flag == 1)
						{
							if(block[x][y][z].ColorID == block[x][y-1][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y-1][z].ColorID<1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								//‚P~‚Q‚É‚·‚é
								block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
								block[x][y-1][z].flag = 12;		block[x][y-1][z].ID = ID12;	block[x][y-1][z].corner = 1;
								goto Odd_Right_Up;
							}
						}
						//‚P~‚Q‚ª‚ ‚éê‡
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
									//‚P~‚R‚É‚·‚é
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
									//‚P~‚R‚É‚·‚é
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
					//‰Eã‚ª‚P~‚P‚Ìê‡
					if(block[x][y+1][z].flag == 1)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						//‚P~‚P‚ª‚ ‚éê‡
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
						//‚P~‚Q‚ª‚ ‚éê‡
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
					//¶‰º‚ª‚P~‚P‚Ìê‡
					if(block[x+1][y][z].flag == 1)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						//‚P~‚P‚ª‚ ‚éê‡
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
						//‚P~‚Q‚ª‚ ‚éê‡
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
					//‰E‰º
					if(block[x+1][y+1][z].flag == 1)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						//‚P~‚P‚ª‚ ‚éê‡
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
						//‚P~‚Q‚ª‚ ‚éê‡
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

		//‹ô”‘w
		else
		{
			for(int x(0); x < VoxSize[0]-1; x=x+2)
			{
				for(int y(0); y < VoxSize[1]-1; y=y+2)
				{

					//                                                                                                
					//¶ã‚ª‚P~‚P‚Ìê‡
					if(block[x][y][z].flag == 1)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						if(block[x-1][y][z].flag == 1)
						{
							//2‚Â‚ÌƒuƒƒbƒN‚ÌF‚ª“¯‚¶‚Ü‚½‚Í‚Ç‚¿‚ç‚©‚Ìƒ{ƒNƒZƒ‹‚ÉF‚ğ‚½‚È‚¢‚È‚ç‚Î‡¬‚·‚é
							if(block[x][y][z].ColorID == block[x-1][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x-1][y][z].ColorID<1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
								block[x-1][y][z].flag = 12;		block[x-1][y][z].ID = ID12;	block[x-1][y][z].corner = 1;
								goto Even_Right_Up;		//continue‚ğg‚í‚È‚¢‚Ì‚Í‚S‚Ü‚·‚Ì’†‚Å‚P~‚P‚ª‘ÎŠpü‚Å‘¶İ‚·‚éê‡‚É‚à‚¤ˆê•û‚ªŒvZ‚³‚ê‚È‚¢
							}
						}
						if(block[x][y-1][z].flag == 1)
						{
							if(block[x][y][z].ColorID == block[x][y-1][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y-1][z].ColorID<1)
							{
								ID12++;
								num11 = num11 - 2;
								num12++;
								//‚P~‚Q‚É‚·‚é
								block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
								block[x][y-1][z].flag = 12;		block[x][y-1][z].ID = ID12;	block[x][y-1][z].corner = 1;
								goto Even_Right_Up;
							}
						}
						//‚P~‚Q‚ª‚ ‚éê‡
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
									//‚P~‚R‚É‚·‚é
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
									//‚P~‚R‚É‚·‚é
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
					//‰Eã‚ª‚P~‚P‚Ìê‡
					if(block[x][y+1][z].flag == 1)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						//‚P~‚P‚ª‚ ‚éê‡
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
						//‚P~‚Q‚ª‚ ‚éê‡
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
					//¶‰º‚ª‚P~‚P‚Ìê‡
					if(block[x+1][y][z].flag == 1)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						//‚P~‚P‚ª‚ ‚éê‡
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
						//‚P~‚Q‚ª‚ ‚éê‡
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
					//‰E‰º
					if(block[x+1][y+1][z].flag == 1)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						//‚P~‚P‚ª‚ ‚éê‡
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
						//‚P~‚Q‚ª‚ ‚éê‡
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

//ŒÇ—§‚µ‚Ä‚¢‚é‚P~‚P‚ğæ‚É‚Ù‚©‚Ìƒs[ƒX‚Æ‚­‚Á‚Â‚¯‚éŠÖ”
void Small_to_Big_before_step1(Lego*** block, int* VoxSize)
{
	int count(0);		//ŒÇ—§‚µ‚»‚¤‚È1~‚P‚Ì”
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


					//                                                                                                
					//¶ã‚ª‚P~‚P‚Ìê‡•ŒÇ—§‚µ‚»‚¤‚Èê‡
					if(block[x][y][z].flag == 1 && block[x][y][z-1].flag < 2 && block[x][y][z+1].flag < 2)		
					{

						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						if(block[x-1][y][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x-1][y][z].flag = 12;		block[x-1][y][z].ID = ID12;	block[x-1][y][z].corner = 1;
							goto Odd_Right_Up;		//continue‚ğg‚í‚È‚¢‚Ì‚Í‚S‚Ü‚·‚Ì’†‚Å‚P~‚P‚ª‘ÎŠpü‚Å‘¶İ‚·‚éê‡‚É‚à‚¤ˆê•û‚ªŒvZ‚³‚ê‚È‚¢
							//continue;
						}
						if(block[x][y-1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							//‚P~‚Q‚É‚·‚é
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x][y-1][z].flag = 12;		block[x][y-1][z].ID = ID12;	block[x][y-1][z].corner = 1;
							goto Odd_Right_Up;
						}
						//‚P~‚Q‚ª‚ ‚éê‡
						if(block[x-1][y][z].flag == 2)
						{
							if(block[x-2][y][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								count++;
								//‚P~‚R‚É‚·‚é
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
								//‚P~‚R‚É‚·‚é
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
					//‰Eã‚ª‚P~‚P‚Ìê‡
					if(block[x][y+1][z].flag == 1 && block[x][y+1][z-1].flag < 2 && block[x][y+1][z+1].flag < 2)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						//‚P~‚P‚ª‚ ‚éê‡
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
						//‚P~‚Q‚ª‚ ‚éê‡
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
					//¶‰º‚ª‚P~‚P‚Ìê‡
					if(block[x+1][y][z].flag == 1 && block[x+1][y][z-1].flag < 2 && block[x+1][y][z+1].flag < 2)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						//‚P~‚P‚ª‚ ‚éê‡
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
						//‚P~‚Q‚ª‚ ‚éê‡
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
					//‰E‰º
					if(block[x+1][y+1][z].flag == 1 && block[x+1][y+1][z-1].flag < 2 && block[x+1][y+1][z+1].flag < 2)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						//‚P~‚P‚ª‚ ‚éê‡
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
						//‚P~‚Q‚ª‚ ‚éê‡
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

		//‹ô”‘w
		else
		{
			for(x=0; x < VoxSize[0]-1; x=x+2)
			{
				for(y=0; y < VoxSize[1]-1; y=y+2)
				{
					//                                                                                                
					//¶ã‚ª‚P~‚P‚Ìê‡
					if(block[x][y][z].flag == 1 && block[x][y][z-1].flag < 2 && block[x][y][z+1].flag < 2)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						if(block[x-1][y][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x-1][y][z].flag = 12;		block[x-1][y][z].ID = ID12;	block[x-1][y][z].corner = 1;
							goto Even_Right_Up;		//continue‚ğg‚í‚È‚¢‚Ì‚Í‚S‚Ü‚·‚Ì’†‚Å‚P~‚P‚ª‘ÎŠpü‚Å‘¶İ‚·‚éê‡‚É‚à‚¤ˆê•û‚ªŒvZ‚³‚ê‚È‚¢
							//continue;
						}
						if(block[x][y-1][z].flag == 1)
						{
							ID12++;
							num11 = num11 - 2;
							num12++;
							count++;
							//‚P~‚Q‚É‚·‚é
							block[x][y][z].flag = 12;			block[x][y][z].ID = ID12;		block[x][y][z].corner = 2;
							block[x][y-1][z].flag = 12;		block[x][y-1][z].ID = ID12;	block[x][y-1][z].corner = 1;
							goto Even_Right_Up;
						}
						//‚P~‚Q‚ª‚ ‚éê‡
						if(block[x-1][y][z].flag == 2 )
						{
							if(block[x-2][y][z].flag == 2)
							{
								ID13++;
								num11--;
								num12--;
								num13++;
								count++;
								//‚P~‚R‚É‚·‚é
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
								//‚P~‚R‚É‚·‚é
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
					//‰Eã‚ª‚P~‚P‚Ìê‡
					if(block[x][y+1][z].flag == 1 && block[x][y+1][z-1].flag < 2 && block[x][y+1][z+1].flag < 2)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						//‚P~‚P‚ª‚ ‚éê‡
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
						//‚P~‚Q‚ª‚ ‚éê‡
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
					//¶‰º‚ª‚P~‚P‚Ìê‡
					if(block[x+1][y][z].flag == 1 && block[x+1][y][z-1].flag < 2 && block[x+1][y][z+1].flag < 2)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						//‚P~‚P‚ª‚ ‚éê‡
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
						//‚P~‚Q‚ª‚ ‚éê‡
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
					//‰E‰º
					if(block[x+1][y+1][z].flag == 1 && block[x+1][y+1][z-1].flag < 2 && block[x+1][y+1][z+1].flag < 2)		
					{
						//ã‚Ù‚Ç—Dæ‡ˆÊ‚ª‚‚­@‰º‚Ù‚Ç—Dæ‡ˆÊ‚ª’á‚¢
						//‚P~‚P‚ª‚ ‚éê‡
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
						//‚P~‚Q‚ª‚ ‚éê‡
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
		//Šï”‘w‚Æ‹ô”‘w‚ğ•ª‚¯‚é
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
		//Šï”‘w‚Æ‹ô”‘w‚ğ•ª‚¯‚é
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