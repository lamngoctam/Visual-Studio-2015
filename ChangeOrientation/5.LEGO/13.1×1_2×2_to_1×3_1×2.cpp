#include "../stdafx.h"
#include "../Voxel.h"
#include "../Lego.h"		//LEGOÉuÉçÉbÉNÇëgÇ›óßÇƒÇÈÇΩÇﬂÇÃÉNÉâÉX

extern int ID12;			
extern int ID13;

extern int num11;
extern int num12;
extern int num13;
extern int num22;

void outputFlag(string filename, int* size);

//ÇQÅ~ÇQÇÃé¸ï”ÇWÉ}ÉXÇå©ÇƒÅAÇªÇ±Ç…ÇPÅ~ÇPÇ™Ç†ÇËÅAÇ©Ç¬ÇPÅ~ÇRÇ∆ÇPÅ~ÇQÇ…ï™äÑÇµÇƒÇ‡ñ‚ëËÇ»Ç¢èÍçáÇÕï™äÑÇ∑ÇÈ
void Small_to_Big_step3(Lego*** block, int*  VoxSize)
{
	int count(0);
	int x,y,z;
	for(z = 1; z<VoxSize[2]-1; z++)
	{
		//äÔêîëw
		if(z%2)
		{
			for(x = 1; x<VoxSize[0]-1; x=x+2)
			{
				for(y = 1; y<VoxSize[1]-1; y=y+2)
				{
					//íçñ⁄ÇÃÇQÅ~ÇQÇÃÉ}ÉXÉNÇÃÉtÉâÉOÇ™ÇSÇé¶ÇµÇƒÇ¢ÇΩÇÁ
					if(block[x][y][z].flag == 4 && block[x+1][y+1][z].flag == 4)
					{
						//è„ÇÃç∂
						if(block[x-1][y][z].flag == 1)
						{
							//1ÇÃè„â∫ÇÃÉ{ÉNÉZÉãÇÃflagÇ™Ç∆Ç‡Ç…ÇPÇ‹ÇΩÇÕÇOÇ»ÇÁÇŒ(Ç±Ç±ÇÃîªíËÇÇªÇ±Ç‹Ç≈åµÇµÇ≠ÇµÇ»Ç≠ÇƒÇ‡Ç¢Ç¢Ç©Ç‡ÇµÇÍÇ»Ç¢ÅH)
							if(block[x-1][y][z-1].flag < 2 && block[x-1][y][z+1].flag < 2 )
							{
								if(block[x+2][y][z].flag > 1 && block[x+2][y+1][z].flag > 1)	//flagÇÃílÇ™2à»è„Ç≈Ç†ÇÍÇŒ
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
						//è„ÇÃâE
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
						//ç∂ÇÃè„
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
						//ç∂ÇÃâ∫
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
						//â∫ÇÃç∂
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
						//â∫ÇÃâE
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

						//âEÇÃè„
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
						//âEÇÃâ∫
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
		//ãÙêîëw
		else
		{
			for(x = 0; x<VoxSize[0]-1; x=x+2)
			{
				for(y = 0; y<VoxSize[1]-1; y=y+2)
				{
					//íçñ⁄ÇÃÇQÅ~ÇQÇÃÉ}ÉXÉNÇÃÉtÉâÉOÇ™ÇSÇé¶ÇµÇƒÇ¢ÇΩÇÁ
					if(block[x][y][z].flag == 4 && block[x+1][y+1][z].flag == 4)
					{
						//è„ÇÃç∂
						if(block[x-1][y][z].flag == 1)
						{
							//1ÇÃè„â∫ÇÃÉ{ÉNÉZÉãÇÃflagÇ™Ç∆Ç‡Ç…ÇPÇ‹ÇΩÇÕÇOÇ»ÇÁÇŒ(Ç±Ç±ÇÃîªíËÇÇªÇ±Ç‹Ç≈åµÇµÇ≠ÇµÇ»Ç≠ÇƒÇ‡Ç¢Ç¢Ç©Ç‡ÇµÇÍÇ»Ç¢ÅH)
							if(block[x-1][y][z-1].flag < 2 && block[x-1][y][z+1].flag < 2 )
							{
								if(block[x+2][y][z].flag > 1 && block[x+2][y+1][z].flag > 1)	//flagÇÃílÇ™2à»è„Ç≈Ç†ÇÍÇŒ
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
						//è„ÇÃâE
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
						//ç∂ÇÃè„
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
						//ç∂ÇÃâ∫
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
						//â∫ÇÃç∂
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
						//â∫ÇÃâE
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

						//âEÇÃè„
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
						//âEÇÃâ∫
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

	cout<<count<<"å¬ÇÃÇPÅ~ÇPÇ∆ÇQÅ~ÇQÇ©ÇÁÇPÅ~ÇRÇ∆ÇPÅ~ÇQÇ™Ç≈Ç´ÇΩÅI"<<endl;
	//outputFlag("test03_11_22_to_13_12.txt", VoxSize);

}