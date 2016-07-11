#include "../stdafx.h"

extern int num11;		//‚P~‚P‚ÌƒuƒƒbƒN‚Ì”
extern int num12;		//‚P~‚Q‚ÌƒuƒƒbƒN‚Ì”
extern int num22;		//‚Q~‚Q‚ÌƒuƒƒbƒN‚Ì”

extern int ID12;
extern int ID22;

void outputFlag(string filename, int* size);

void CountNum_of_4(Lego*** block, int* VoxSize)
{
	unsigned short count4(0);			
	int x, y, z;
	
	for (z = 1; z < VoxSize[2] - 1; z = z + 2)				//‚š1,3,5,...
	{
		for (x = 1; x < VoxSize[0] - 1; x = x + 2)
		{
			for (y = 1; y < VoxSize[1] - 1; y = y + 2)
			{
				count4 = 0;			//‰Šú‰»
				//‚S‚Â‚Ìƒ{ƒNƒZƒ‹‚ğŒ©‚Ä‰½ŒÂ‚ª“à•”ƒ{ƒNƒZƒ‹‚È‚Ì‚©‚ğƒJƒEƒ“ƒgi”½Œv‚Ü‚í‚èj
				if (block[x][y][z].fill)					count4++;
				if (block[x][y + 1][z].fill)				count4++;
				if (block[x + 1][y + 1][z].fill)			count4++;
				if (block[x + 1][y][z].fill)				count4++;

				//Šeƒ{ƒNƒZƒ‹‚ÉID‚ğ‚Â‚¯‚Ä‚¢‚­
				if (block[x][y][z].fill)					block[x][y][z].flag = count4;
				if (block[x][y + 1][z].fill)				block[x][y + 1][z].flag = count4;
				if (block[x + 1][y + 1][z].fill)			block[x + 1][y + 1][z].flag = count4;
				if (block[x + 1][y][z].fill)				block[x + 1][y][z].flag = count4;

				if (count4 == 1)				//‚P~‚P‚Ì”‚ğ‰ÁZ
					num11++;
				else if (count4 == 4)		//‚Q~‚Q‚Ì”‚ğ‰ÁZ
					num22++;
				//count4=2‚LEGO
				else if (count4 == 2)
				{
					if (block[x][y][z].fill == true && block[x + 1][y + 1][z].fill == true)	//‘ÎŠpü‚É‚È‚éƒP[ƒX‚P
					{
						block[x][y][z].flag = 1;
						block[x + 1][y + 1][z].flag = 1;
					}
					else if (block[x + 1][y][z].fill == true && block[x][y + 1][z].fill == true)	//‘ÎŠpü‚É‚È‚éƒP[ƒX‚Q
					{
						block[x + 1][y][z].flag = 1;
						block[x][y + 1][z].flag = 1;
					}
					else
						num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
				}
			}
		}
	}

	for (z = 2; z < VoxSize[2] - 1; z = z + 2)				//‚š2,4,6,...
	{
		for (x = 0; x < VoxSize[0] - 1; x = x + 2)
		{
			for (y = 0; y < VoxSize[1] - 1; y = y + 2)
			{
				count4 = 0;			//‰Šú‰»
				//‚S‚Â‚Ìƒ{ƒNƒZƒ‹‚ğŒ©‚Ä‰½ŒÂ‚ª“à•”ƒ{ƒNƒZƒ‹‚È‚Ì‚©‚ğƒJƒEƒ“ƒgi”½Œv‚Ü‚í‚èj
				if (block[x][y][z].fill)					count4++;
				if (block[x][y + 1][z].fill)				count4++;
				if (block[x + 1][y + 1][z].fill)			count4++;
				if (block[x + 1][y][z].fill)				count4++;

				//Šeƒ{ƒNƒZƒ‹‚ÉID‚ğ‚Â‚¯‚Ä‚¢‚­
				if (block[x][y][z].fill)					block[x][y][z].flag = count4;
				if (block[x][y + 1][z].fill)				block[x][y + 1][z].flag = count4;
				if (block[x + 1][y + 1][z].fill)			block[x + 1][y + 1][z].flag = count4;
				if (block[x + 1][y][z].fill)				block[x + 1][y][z].flag = count4;

				if (count4 == 1)				//‚P~‚P‚Ì”‚ğ‰ÁZ
					num11++;
				else if (count4 == 4)		//‚Q~‚Q‚Ì”‚ğ‰ÁZ
					num22++;

				//count4=2‚Ì‚Ì—áŠOˆ—@“ñ‚Â‚ÌLEGOƒuƒƒbƒN‚ª‘ÎŠpü‚É‚ ‚é‚Æ‚«
				else if (count4 == 2)
				{
					if (block[x][y][z].fill == true && block[x + 1][y + 1][z].fill == true)	//‘ÎŠpü‚É‚È‚éƒP[ƒX‚P
					{
						block[x][y][z].flag = 1;
						block[x + 1][y + 1][z].flag = 1;
					}
					else if (block[x + 1][y][z].fill == true && block[x][y + 1][z].fill == true)	//‘ÎŠpü‚É‚È‚éƒP[ƒX‚Q
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
	//step1‚±‚±‚Ü‚Å


}

//2013/9/14

//void CountNum_of_4_ID(Lego*** block, int* VoxSize)
//{
//	unsigned short count4(0);			//‚Q~‚Qƒ}ƒX‚Ì’†‚É‘¶İ‚·‚éƒ{ƒNƒZƒ‹‚ğƒJƒEƒ“ƒg
//	int x,y,z;
//	//Šï”‘w@Œ´“_i‚PC‚Pj
//	for(z=1; z < VoxSize[2]-1; z = z + 2 )				//‚š1,3,5,...
//	{
//		for(x=1; x < VoxSize[0]-1; x = x + 2)
//		{
//			for(y=1; y < VoxSize[1]-1; y = y + 2)
//			{
//				count4 = 0;			//‰Šú‰»
//				//‚S‚Â‚Ìƒ{ƒNƒZƒ‹‚ğŒ©‚Ä‰½ŒÂ‚ª“à•”ƒ{ƒNƒZƒ‹‚È‚Ì‚©‚ğƒJƒEƒ“ƒgi”½Œv‚Ü‚í‚èj
//				if(block[x][y][z].fill)					count4++;
//				if(block[x][y+1][z].fill)				count4++;
//				if(block[x+1][y+1][z].fill)			count4++;
//				if(block[x+1][y][z].fill)				count4++;
//
//				//Šeƒ{ƒNƒZƒ‹‚ÉID‚ğ‚Â‚¯‚Ä‚¢‚­
//				if(block[x][y][z].fill)					block[x][y][z].flag = count4;
//				if(block[x][y+1][z].fill)				block[x][y+1][z].flag = count4;
//				if(block[x+1][y+1][z].fill)			block[x+1][y+1][z].flag = count4;
//				if(block[x+1][y][z].fill)				block[x+1][y][z].flag = count4;
//
//				if(count4 == 1)				//‚P~‚P‚Ì”‚ğ‰ÁZ
//					num11++;
//				else if(count4 == 4)		//‚Q~‚Q‚Ì”‚ğ‰ÁZ
//				{
//					num22++;
//					ID22++;
//					block[x][y][z].ID = ID22;
//					block[x][y+1][z].ID = ID22;
//					block[x+1][y+1][z].ID = ID22;
//					block[x+1][y][z].ID = ID22;
//				}
//				//count4=2‚Ì‚Ì—áŠOˆ—@“ñ‚Â‚ÌLEGOƒuƒƒbƒN‚ª‘ÎŠpü‚É‚ ‚é‚Æ‚«
//				else if(count4 == 2)
//				{
//					//‚P~‚Q‚É‚È‚éê‡
//					if(block[x][y][z].fill)
//					{
//						//‚™²‚É•½s
//						if(block[x+1][y][z].fill)
//						{
//							num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
//							ID12++;
//							block[x][y][z].ID = ID12;
//							block[x+1][y][z].ID = ID12;
//							continue;
//						}
//						//‚˜²‚É•½s
//						else if(block[x][y+1][z].fill)
//						{
//							num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
//							ID12++;
//							block[x][y][z].ID = ID12;
//							block[x][y+1][z].ID = ID12;
//							continue;
//						}
//					}
//					if(block[x+1][y+1][z].fill)
//					{
//						//‚™²‚É•½s
//						if(block[x][y+1][z].fill)
//						{
//							num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
//							ID12++;
//							block[x+1][y+1][z].ID = ID12;
//							block[x][y+1][z].ID = ID12;
//							continue;
//						}
//						//‚˜²‚É•½s
//						else if(block[x+1][y][z].fill)
//						{
//							num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
//							ID12++;
//							block[x+1][y+1][z].ID = ID12;
//							block[x+1][y][z].ID = ID12;
//							continue;
//						}
//					}
//
//					//‘ÎŠpüã‚É‚ ‚éê‡‚Ìê‡
//					if(block[x][y][z].fill == true && block[x+1][y+1][z].fill == true)	//‘ÎŠpü‚É‚È‚éƒP[ƒX‚P
//					{
//						block[x][y][z].flag = 1;				
//						block[x+1][y+1][z].flag = 1;
//					}
//					else if(block[x+1][y][z].fill == true && block[x][y+1][z].fill == true)	//‘ÎŠpü‚É‚È‚éƒP[ƒX‚Q
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
//	//‹ô”‘w@Œ´“_i‚QC‚Qj
//	for(z=2; z < VoxSize[2]-1; z = z + 2 )				//‚š2,4,6,...
//	{
//		for(x=0; x < VoxSize[0]-1; x = x + 2)
//		{
//			for(y=0; y < VoxSize[1]-1; y = y + 2)
//			{
//				count4 = 0;			//‰Šú‰»
//				//‚S‚Â‚Ìƒ{ƒNƒZƒ‹‚ğŒ©‚Ä‰½ŒÂ‚ª“à•”ƒ{ƒNƒZƒ‹‚È‚Ì‚©‚ğƒJƒEƒ“ƒgi”½Œv‚Ü‚í‚èj
//				if(block[x][y][z].fill)					count4++;
//				if(block[x][y+1][z].fill)				count4++;
//				if(block[x+1][y+1][z].fill)			count4++;
//				if(block[x+1][y][z].fill)				count4++;
//
//				//Šeƒ{ƒNƒZƒ‹‚ÉID‚ğ‚Â‚¯‚Ä‚¢‚­
//				if(block[x][y][z].fill)					block[x][y][z].flag = count4;
//				if(block[x][y+1][z].fill)				block[x][y+1][z].flag = count4;
//				if(block[x+1][y+1][z].fill)			block[x+1][y+1][z].flag = count4;
//				if(block[x+1][y][z].fill)				block[x+1][y][z].flag = count4;
//
//				if(count4 == 1)				//‚P~‚P‚Ì”‚ğ‰ÁZ
//					num11++;
//				else if(count4 == 4)		//‚Q~‚Q‚Ì”‚ğ‰ÁZ
//				{
//					num22++;
//					ID22++;
//					block[x][y][z].ID = ID22;
//					block[x][y+1][z].ID = ID22;
//					block[x+1][y+1][z].ID = ID22;
//					block[x+1][y][z].ID = ID22;
//				}
//				//count4=2‚Ì‚Ì—áŠOˆ—@“ñ‚Â‚ÌLEGOƒuƒƒbƒN‚ª‘ÎŠpü‚É‚ ‚é‚Æ‚«
//				else if(count4 == 2)
//				{
//					//‚P~‚Q‚É‚È‚éê‡
//					if(block[x][y][z].fill)
//					{
//						//‚™²‚É•½s
//						if(block[x+1][y][z].fill)
//						{
//							num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
//							ID12++;
//							block[x][y][z].ID = ID12;
//							block[x+1][y][z].ID = ID12;
//							continue;
//						}
//						//‚˜²‚É•½s
//						else if(block[x][y+1][z].fill)
//						{
//							num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
//							ID12++;
//							block[x][y][z].ID = ID12;
//							block[x][y+1][z].ID = ID12;
//							continue;
//						}
//					}
//					if(block[x+1][y+1][z].fill)
//					{
//						//‚™²‚É•½s
//						if(block[x][y+1][z].fill)
//						{
//							num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
//							ID12++;
//							block[x+1][y+1][z].ID = ID12;
//							block[x][y+1][z].ID = ID12;
//							continue;
//						}
//						//‚˜²‚É•½s
//						else if(block[x+1][y][z].fill)
//						{
//							num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
//							ID12++;
//							block[x+1][y+1][z].ID = ID12;
//							block[x+1][y][z].ID = ID12;
//							continue;
//						}
//					}
//
//					//‘ÎŠpüã‚É‚ ‚éê‡‚Ìê‡
//					if(block[x][y][z].fill == true && block[x+1][y+1][z].fill == true)	//‘ÎŠpü‚É‚È‚éƒP[ƒX‚P
//					{
//						block[x][y][z].flag = 1;				
//						block[x+1][y+1][z].flag = 1;
//					}
//					else if(block[x+1][y][z].fill == true && block[x][y+1][z].fill == true)	//‘ÎŠpü‚É‚È‚éƒP[ƒX‚Q
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
//	//step1‚±‚±‚Ü‚Å
//
//}

//2014/5/21
void CountNum_of_4_ID(Lego*** block, int* VoxSize)
{
	unsigned short count4(0);			//‚Q~‚Qƒ}ƒX‚Ì’†‚É‘¶İ‚·‚éƒ{ƒNƒZƒ‹‚ğƒJƒEƒ“ƒg
	unsigned short Ccount(0);			//‚Q~‚Qƒ}ƒX‚Ì’†‚É‘¶İ‚·‚é“¯Fƒ{ƒNƒZƒ‹‚ğƒJƒEƒ“ƒg
	unsigned short Scount(0);			//‚Q~‚Qƒ}ƒX‚Ì’†‚É‘¶İ‚·‚é•\–Êƒ{ƒNƒZƒ‹‚ğƒJƒEƒ“ƒg
	int x, y, z;
	//Šï”‘w@Œ´“_i‚PC‚Pj
	for (z = 1; z < VoxSize[2] - 1; z = z + 2)				//‚š1,3,5,...
	{
		for (x = 1; x < VoxSize[0] - 1; x = x + 2)
		{
			for (y = 1; y < VoxSize[1] - 1; y = y + 2)
			{
				int CoC[8] = { 0,0,0,0,0,0,0,0 };
				count4 = 0;			//‰Šú‰»
				Ccount = 0;			//‰Šú‰»
				//‚S‚Â‚Ìƒ{ƒNƒZƒ‹‚ğŒ©‚Ä‰½ŒÂ‚ª“à•”ƒ{ƒNƒZƒ‹‚È‚Ì‚©‚ğƒJƒEƒ“ƒgi”½Œv‚Ü‚í‚èj
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
				//			num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
				//			ID12++;
				//			block[x][y][z].ID = ID12;
				//			block[x+1][y][z].ID = ID12;
				//			num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
				//			ID12++;
				//			block[x][y+1][z].ID = ID12;
				//			block[x+1][y+1][z].ID = ID12;					
				//	}
				//	else if((block[x][y][z].ColorID==0&&block[x+1][y][z].ColorID==0)||
				//		(block[x][y][z].ColorID>0&&block[x+1][y][z].ColorID>0)){
				//			num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
				//			ID12++;
				//			block[x][y][z].ID = ID12;
				//			block[x+1][y][z].ID = ID12;
				//			num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
				//			ID12++;
				//			block[x][y+1][z].ID = ID12;
				//			block[x+1][y+1][z].ID = ID12;								
				//	}
				//	else{
				//			num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
				//			ID12++;
				//			block[x][y][z].ID = ID12;
				//			block[x][y+1][z].ID = ID12;
				//			num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
				//			ID12++;
				//			block[x+1][y][z].ID = ID12;
				//			block[x+1][y+1][z].ID = ID12;										
				//	}
				//}
				//3‚Â‚Ìê‡
				if (count4 == 3 && Ccount > 1) {
					if (block[x][y][z].fill)	block[x][y][z].flag = 1;
					if (block[x][y + 1][z].fill)   block[x][y + 1][z].flag = 1;
					if (block[x + 1][y + 1][z].fill)   block[x + 1][y + 1][z].flag = 1;
					if (block[x + 1][y][z].fill)   block[x + 1][y][z].flag = 1;
					num11 = num11 + 3;
				}

				if (count4 == 1)				//‚P~‚P‚Ì”‚ğ‰ÁZ
					num11++;

				//count4=2‚Ì‚Ì—áŠOˆ—@“ñ‚Â‚ÌLEGOƒuƒƒbƒN‚ª‘ÎŠpü‚É‚ ‚é‚Æ‚«
				else if (count4 == 2)
				{
					//‚P~‚Q‚É‚È‚éê‡
					if (block[x][y][z].fill)
					{
						//‚™²‚É•½s
						if (block[x + 1][y][z].fill)
						{
							if (block[x][y][z].ColorID == block[x + 1][y][z].ColorID
								|| (block[x][y][z].ColorID == 0 || block[x + 1][y][z].ColorID == 0)) {
								num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
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
						//‚˜²‚É•½s
						else if (block[x][y + 1][z].fill)
						{
							if (block[x][y][z].ColorID == block[x][y + 1][z].ColorID ||
								(block[x][y][z].ColorID == 0 || block[x][y + 1][z].ColorID == 0)) {
								num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
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
						//‚™²‚É•½s
						if (block[x][y + 1][z].fill)
						{
							if (block[x + 1][y + 1][z].ColorID == block[x][y + 1][z].ColorID
								|| (block[x + 1][y + 1][z].ColorID == 0 || block[x][y + 1][z].ColorID == 0)) {
								num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
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
						//‚˜²‚É•½s
						else if (block[x + 1][y][z].fill)
						{
							if (block[x + 1][y + 1][z].ColorID == block[x + 1][y][z].ColorID
								|| (block[x + 1][y + 1][z].ColorID == 0 || block[x + 1][y][z].ColorID == 0)) {
								num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
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

					//‘ÎŠpüã‚É‚ ‚éê‡‚Ìê‡
					if (block[x][y][z].fill == true && block[x + 1][y + 1][z].fill == true)	//‘ÎŠpü‚É‚È‚éƒP[ƒX‚P
					{
						block[x][y][z].flag = 1;
						block[x + 1][y + 1][z].flag = 1;
						num11++;
						num11++;
					}
					else if (block[x + 1][y][z].fill == true && block[x][y + 1][z].fill == true)	//‘ÎŠpü‚É‚È‚éƒP[ƒX‚Q
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

	//‹ô”‘w@Œ´“_i‚QC‚Qj
	for (z = 2; z < VoxSize[2] - 1; z = z + 2)				//‚š2,4,6,...
	{
		for (x = 0; x < VoxSize[0] - 1; x = x + 2)
		{
			for (y = 0; y < VoxSize[1] - 1; y = y + 2)
			{
				int CoC[8] = { 0,0,0,0,0,0,0,0 };
				count4 = 0;			//‰Šú‰»
				Ccount = 0;			//‰Šú‰»
				//‚S‚Â‚Ìƒ{ƒNƒZƒ‹‚ğŒ©‚Ä‰½ŒÂ‚ª“à•”ƒ{ƒNƒZƒ‹‚È‚Ì‚©‚ğƒJƒEƒ“ƒgi”½Œv‚Ü‚í‚èj
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
				//Šeƒ{ƒNƒZƒ‹‚ÉID‚ğ‚Â‚¯‚Ä‚¢‚­
				if (block[x][y][z].fill)					block[x][y][z].flag = count4;
				if (block[x][y + 1][z].fill)				block[x][y + 1][z].flag = count4;
				if (block[x + 1][y + 1][z].fill)			block[x + 1][y + 1][z].flag = count4;
				if (block[x + 1][y][z].fill)				block[x + 1][y][z].flag = count4;

				//4‚Â‚ ‚éê‡
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
				//			num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
				//			ID12++;
				//			block[x][y][z].ID = ID12;
				//			block[x+1][y][z].ID = ID12;
				//			num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
				//			ID12++;
				//			block[x][y+1][z].ID = ID12;
				//			block[x+1][y+1][z].ID = ID12;					
				//	}
				//	else if((block[x][y][z].ColorID==0&&block[x+1][y][z].ColorID==0)||
				//		(block[x][y][z].ColorID>0&&block[x+1][y][z].ColorID>0)){
				//			num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
				//			ID12++;
				//			block[x][y][z].ID = ID12;
				//			block[x+1][y][z].ID = ID12;
				//			num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
				//			ID12++;
				//			block[x][y+1][z].ID = ID12;
				//			block[x+1][y+1][z].ID = ID12;								
				//	}
				//	else{
				//			num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
				//			ID12++;
				//			block[x][y][z].ID = ID12;
				//			block[x][y+1][z].ID = ID12;
				//			num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
				//			ID12++;
				//			block[x+1][y][z].ID = ID12;
				//			block[x+1][y+1][z].ID = ID12;										
				//	}
				//}
				//3‚Â‚Ìê‡
				if (count4 == 3 && Ccount > 1) {
					if (block[x][y][z].fill)	block[x][y][z].flag = 1;
					if (block[x][y + 1][z].fill)   block[x][y + 1][z].flag = 1;
					if (block[x + 1][y + 1][z].fill)   block[x + 1][y + 1][z].flag = 1;
					if (block[x + 1][y][z].fill)   block[x + 1][y][z].flag = 1;
					num11 = num11 + 3;
				}

				if (count4 == 1)				//‚P~‚P‚Ì”‚ğ‰ÁZ
					num11++;

				//count4=2‚Ì‚Ì—áŠOˆ—@“ñ‚Â‚ÌLEGOƒuƒƒbƒN‚ª‘ÎŠpü‚É‚ ‚é‚Æ‚«
				else if (count4 == 2)
				{
					//‚P~‚Q‚É‚È‚éê‡
					if (block[x][y][z].fill)
					{
						//‚™²‚É•½s
						if (block[x + 1][y][z].fill)
						{
							if (block[x][y][z].ColorID == block[x + 1][y][z].ColorID
								|| (block[x][y][z].ColorID == 0 || block[x + 1][y][z].ColorID == 0)) {
								num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
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
						//‚˜²‚É•½s
						else if (block[x][y + 1][z].fill)
						{
							if (block[x][y][z].ColorID == block[x][y + 1][z].ColorID ||
								(block[x][y][z].ColorID == 0 || block[x][y + 1][z].ColorID == 0)) {
								num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
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
						//‚™²‚É•½s
						if (block[x][y + 1][z].fill)
						{
							if (block[x + 1][y + 1][z].ColorID == block[x][y + 1][z].ColorID
								|| (block[x + 1][y + 1][z].ColorID == 0 || block[x][y + 1][z].ColorID == 0)) {
								num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
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
						//‚˜²‚É•½s
						else if (block[x + 1][y][z].fill)
						{
							if (block[x + 1][y + 1][z].ColorID == block[x + 1][y][z].ColorID
								|| (block[x + 1][y + 1][z].ColorID == 0 || block[x + 1][y][z].ColorID == 0)) {
								num12++;		//‚P~‚Q‚Ì”‚ğ‰ÁZ
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

					//‘ÎŠpüã‚É‚ ‚éê‡‚Ìê‡
					if (block[x][y][z].fill == true && block[x + 1][y + 1][z].fill == true)	//‘ÎŠpü‚É‚È‚éƒP[ƒX‚P
					{
						block[x][y][z].flag = 1;
						block[x + 1][y + 1][z].flag = 1;
						num11++;
						num11++;
					}
					else if (block[x + 1][y][z].fill == true && block[x][y + 1][z].fill == true)	//‘ÎŠpü‚É‚È‚éƒP[ƒX‚Q
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
	//step1‚±‚±‚Ü‚Å

}