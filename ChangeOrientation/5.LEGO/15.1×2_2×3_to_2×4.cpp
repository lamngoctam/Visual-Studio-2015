#include "../stdafx.h"
#include "../Voxel.h"
#include "../Lego.h"		//LEGOƒuƒƒbƒN‚ğ‘g‚İ—§‚Ä‚é‚½‚ß‚ÌƒNƒ‰ƒX

extern int ID24;

extern int num12;		//‚P~‚Q‚ÌƒuƒƒbƒN‚Ì”
extern int num23;		//‚Q~‚R‚ÌƒuƒƒbƒN‚Ì”
extern int num24;		//‚Q~‚S‚ÌƒuƒƒbƒN‚Ì”

void outputFlag(string filename, int* size);

//‚P~‚Q‚Æ‚Q~‚R@‚©‚ç@‚Q~‚S‚ğ‡¬@

void Small_to_Big_step5(Lego*** block, int* VoxSize)
{
	int x,y,z;
	int count(0);
	//Šï”‘w
	for(z=1; z < VoxSize[2]-1; z=z+2 )				//‚š1,3,5,...
	{
		for(x=1; x < VoxSize[0]-1; x=x+2)
		{
			for(y=1; y < VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag == 23 && block[x+1][y+1][z].flag == 23)
				{
					//‰º‚Ì‚P~‚Q‚Æ‡¬
					if(block[x-1][y][z].flag == 23 && block[x-1][y][z].ID == block[x][y][z].ID)
					{
						if(block[x+2][y][z].flag == 2 && block[x+2][y+1][z].flag == 2)
						{
							ID24++;
							num12--;
							num23--;
							num24++;
							count++;
							cout<<x<<" "<<y<<" "<<z<<endl;
							for(int i(0); i<4; i++)
							{
								for(int k(0); k<2; k++)
								{
									block[x+i-1][y+k][z].flag = 24;
									block[x+i-1][y+k][z].ID = ID24;
								}
							}
							block[x-1][y][z].corner = 1;
							block[x+2][y+1][z].corner = 2;
						}
					}
					//ã‚Ì‚P~‚Q‚Æ‡¬
					else if(block[x+2][y][z].flag == 23 && block[x+2][y][z].ID == block[x][y][z].ID)
					{
						if(block[x-1][y][z].flag == 2 && block[x-1][y+1][z].flag == 2)
						{
							ID24++;
							num12--;
							num23--;
							num24++;
							count++;
							cout<<x<<" "<<y<<" "<<z<<endl;
							for(int i(0); i<4; i++)
							{
								for(int k(0); k<2; k++)
								{
									block[x+i-1][y+k][z].flag = 24;
									block[x+i-1][y+k][z].ID = ID24;
								}
							}
							block[x-1][y][z].corner = 1;
							block[x+2][y+1][z].corner = 2;
						}
					}
					//¶‚Ì‚P~‚Q‚Æ‡¬
					else if(block[x][y+2][z].flag == 23 && block[x][y+2][z].ID == block[x][y][z].ID)
					{
						if(block[x][y-1][z].flag == 2 && block[x+1][y-1][z].flag == 2)
						{
							ID24++;
							num12--;
							num23--;
							num24++;
							count++;
							cout<<x<<" "<<y<<" "<<z<<endl;
							for(int i(0); i<2; i++)
							{
								for(int k(0); k<4; k++)
								{
									block[x+i][y+k-1][z].flag = 24;
									block[x+i][y+k-1][z].ID = ID24;
								}
							}
							block[x][y-1][z].corner = 1;
							block[x+1][y+2][z].corner = 2;
						}
					}
					//‰E‚Ì‚P~‚Q‚Æ‡¬
					else if(block[x][y-1][z].flag == 23 && block[x][y-1][z].ID == block[x][y][z].ID)
					{
						if(block[x][y+2][z].flag == 2 && block[x+1][y+2][z].flag == 2)
						{
							ID24++;
							num12--;
							num23--;
							num24++;
							count++;
							cout<<x<<" "<<y<<" "<<z<<endl;
							for(int i(0); i<2; i++)
							{
								for(int k(0); k<4; k++)
								{
									block[x+i][y+k-1][z].flag = 24;
									block[x+i][y+k-1][z].ID = ID24;
								}
							}
							block[x][y-1][z].corner = 1;
							block[x+1][y+2][z].corner = 2;
						}
					}
					//‚±‚ê‚ÍƒGƒ‰[‚¾I
					else
					{
						cout<<"ƒGƒ‰[II"<<endl;
						exit(-1);
					}
				}
			}
		}
	}

	//‹ô”‘w
	for(z=2; z<VoxSize[2]-1; z=z+2 )				//‚š2,4,6,...
	{	
		for(x=0; x<VoxSize[0]-1; x=x+2)
		{
			for(y=0; y<VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag == 23 && block[x+1][y+1][z].flag == 23)
				{
					//‰º‚Ì‚P~‚Q‚Æ‡¬
					if(block[x-1][y][z].flag == 23 && block[x-1][y][z].ID == block[x][y][z].ID)
					{
						if(block[x+2][y][z].flag == 2 && block[x+2][y+1][z].flag == 2)
						{
							ID24++;
							num12--;
							num23--;
							num24++;
							count++;
							cout<<x<<" "<<y<<" "<<z<<endl;
							for(int i(0); i<4; i++)
							{
								for(int k(0); k<2; k++)
								{
									block[x+i-1][y+k][z].flag = 24;
									block[x+i-1][y+k][z].ID = ID24;
								}
							}
							block[x-1][y][z].corner = 1;
							block[x+2][y+1][z].corner = 2;
						}
					}
					//ã‚Ì‚P~‚Q‚Æ‡¬
					else if(block[x+2][y][z].flag == 23 && block[x+2][y][z].ID == block[x][y][z].ID)
					{
						if(block[x-1][y][z].flag == 2 && block[x-1][y+1][z].flag == 2)
						{
							ID24++;
							num12--;
							num23--;
							num24++;
							count++;
							cout<<x<<" "<<y<<" "<<z<<endl;
							for(int i(0); i<4; i++)
							{
								for(int k(0); k<2; k++)
								{
									block[x+i-1][y+k][z].flag = 24;
									block[x+i-1][y+k][z].ID = ID24;
								}
							}
							block[x-1][y][z].corner = 1;
							block[x+2][y+1][z].corner = 2;
						}
					}
					//¶‚Ì‚P~‚Q‚Æ‡¬
					else if(block[x][y+2][z].flag == 23 && block[x][y+2][z].ID == block[x][y][z].ID)
					{
						if(block[x][y-1][z].flag == 2 && block[x+1][y-1][z].flag == 2)
						{
							ID24++;
							num12--;
							num23--;
							num24++;
							count++;
							cout<<x<<" "<<y<<" "<<z<<endl;
							for(int i(0); i<2; i++)
							{
								for(int k(0); k<4; k++)
								{
									block[x+i][y+k-1][z].flag = 24;
									block[x+i][y+k-1][z].ID = ID24;
								}
							}
							block[x][y-1][z].corner = 1;
							block[x+1][y+2][z].corner = 2;
						}
					}
					//‰E‚Ì‚P~‚Q‚Æ‡¬
					else if(block[x][y-1][z].flag == 23 && block[x][y-1][z].ID == block[x][y][z].ID)
					{
						if(block[x][y+2][z].flag == 2 && block[x+1][y+2][z].flag == 2)
						{
							ID24++;
							num12--;
							num23--;
							num24++;
							count++;
							cout<<x<<" "<<y<<" "<<z<<endl;
							for(int i(0); i<2; i++)
							{
								for(int k(0); k<4; k++)
								{
									block[x+i][y+k-1][z].flag = 24;
									block[x+i][y+k-1][z].ID = ID24;
								}
							}
							block[x][y-1][z].corner = 1;
							block[x+1][y+2][z].corner = 2;
						}
					}
					//‚±‚ê‚ÍƒGƒ‰[‚¾I
					else
					{
						cout<<"ƒGƒ‰[II"<<endl;
						exit(-1);
					}
				}
			}
		}
	}

	cout<<count<<" ŒÂ‚Ì‚Q~‚S‚ª‚P~‚Q‚Æ‚Q~‚R‚©‚ç‚Å‚«‚½I"<<endl;
	outputFlag("test05_12_23_to_24.txt", VoxSize);
}

void Small_to_Big_step5_color(Lego*** block, int* VoxSize)
{
	int x,y,z;
	int count(0);
	//Šï”‘w
	for(z=1; z < VoxSize[2]-1; z=z+2 )				//‚š1,3,5,...
	{
		for(x=1; x < VoxSize[0]-1; x=x+2)
		{
			for(y=1; y < VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag == 23 && block[x+1][y+1][z].flag == 23)
				{
					//‰º‚Ì‚P~‚Q‚Æ‡¬
					if(block[x-1][y][z].flag == 23 && block[x-1][y][z].ID == block[x][y][z].ID)
					{
						if(block[x+2][y][z].flag == 2 && block[x+2][y+1][z].flag == 2)
						{
							if(block[x][y][z].ColorID == block[x+2][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x+2][y][z].ColorID < 1)
							{
								ID24++;
								num12--;
								num23--;
								num24++;
								count++;
								//cout<<x<<" "<<y<<" "<<z<<endl;
								for(int i(0); i<4; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i-1][y+k][z].flag = 24;
										block[x+i-1][y+k][z].ID = ID24;
									}
								}
								block[x-1][y][z].corner = 1;
								block[x+2][y+1][z].corner = 2;
							}
						}
					}
					//ã‚Ì‚P~‚Q‚Æ‡¬
					else if(block[x+2][y][z].flag == 23 && block[x+2][y][z].ID == block[x][y][z].ID)
					{
						if(block[x-1][y][z].flag == 2 && block[x-1][y+1][z].flag == 2)
						{
							if(block[x][y][z].ColorID == block[x-1][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x-1][y][z].ColorID < 1)
							{
								ID24++;
								num12--;
								num23--;
								num24++;
								count++;
								//cout<<x<<" "<<y<<" "<<z<<endl;
								for(int i(0); i<4; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i-1][y+k][z].flag = 24;
										block[x+i-1][y+k][z].ID = ID24;
									}
								}
								block[x-1][y][z].corner = 1;
								block[x+2][y+1][z].corner = 2;
							}
						}
					}
					//¶‚Ì‚P~‚Q‚Æ‡¬
					else if(block[x][y+2][z].flag == 23 && block[x][y+2][z].ID == block[x][y][z].ID)
					{
						if(block[x][y-1][z].flag == 2 && block[x+1][y-1][z].flag == 2)
						{
							if(block[x][y][z].ColorID == block[x][y-1][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y-1][z].ColorID < 1)
							{
								ID24++;
								num12--;
								num23--;
								num24++;
								count++;
								//cout<<x<<" "<<y<<" "<<z<<endl;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<4; k++)
									{
										block[x+i][y+k-1][z].flag = 24;
										block[x+i][y+k-1][z].ID = ID24;
									}
								}
								block[x][y-1][z].corner = 1;
								block[x+1][y+2][z].corner = 2;
							}
						}
					}
					//‰E‚Ì‚P~‚Q‚Æ‡¬
					else if(block[x][y-1][z].flag == 23 && block[x][y-1][z].ID == block[x][y][z].ID)
					{
						if(block[x][y+2][z].flag == 2 && block[x+1][y+2][z].flag == 2)
						{
							if(block[x][y][z].ColorID == block[x][y+2][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y+2][z].ColorID < 1)
							{
								ID24++;
								num12--;
								num23--;
								num24++;
								count++;
								//cout<<x<<" "<<y<<" "<<z<<endl;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<4; k++)
									{
										block[x+i][y+k-1][z].flag = 24;
										block[x+i][y+k-1][z].ID = ID24;
									}
								}
								block[x][y-1][z].corner = 1;
								block[x+1][y+2][z].corner = 2;
							}
						}
					}
					//‚±‚ê‚ÍƒGƒ‰[‚¾I
					else
					{
						cout<<"ƒGƒ‰[II"<<endl;
						exit(-1);
					}
				}
			}
		}
	}

	//‹ô”‘w
	for(z=2; z<VoxSize[2]-1; z=z+2 )				//‚š2,4,6,...
	{	
		for(x=0; x<VoxSize[0]-1; x=x+2)
		{
			for(y=0; y<VoxSize[1]-1; y=y+2)
			{
				if(block[x][y][z].flag == 23 && block[x+1][y+1][z].flag == 23)
				{
					//‰º‚Ì‚P~‚Q‚Æ‡¬
					if(block[x-1][y][z].flag == 23 && block[x-1][y][z].ID == block[x][y][z].ID)
					{
						if(block[x+2][y][z].flag == 2 && block[x+2][y+1][z].flag == 2)
						{
							if(block[x][y][z].ColorID == block[x+2][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x+2][y][z].ColorID < 1)
							{
								ID24++;
								num12--;
								num23--;
								num24++;
								count++;
								//cout<<x<<" "<<y<<" "<<z<<endl;
								for(int i(0); i<4; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i-1][y+k][z].flag = 24;
										block[x+i-1][y+k][z].ID = ID24;
									}
								}
								block[x-1][y][z].corner = 1;
								block[x+2][y+1][z].corner = 2;
							}
						}
					}
					//ã‚Ì‚P~‚Q‚Æ‡¬
					else if(block[x+2][y][z].flag == 23 && block[x+2][y][z].ID == block[x][y][z].ID)
					{
						if(block[x-1][y][z].flag == 2 && block[x-1][y+1][z].flag == 2)
						{
							if(block[x][y][z].ColorID == block[x-1][y][z].ColorID || block[x][y][z].ColorID < 1 || block[x-1][y][z].ColorID < 1)
							{
								ID24++;
								num12--;
								num23--;
								num24++;
								count++;
								//cout<<x<<" "<<y<<" "<<z<<endl;
								for(int i(0); i<4; i++)
								{
									for(int k(0); k<2; k++)
									{
										block[x+i-1][y+k][z].flag = 24;
										block[x+i-1][y+k][z].ID = ID24;
									}
								}
								block[x-1][y][z].corner = 1;
								block[x+2][y+1][z].corner = 2;
							}
						}
					}
					//¶‚Ì‚P~‚Q‚Æ‡¬
					else if(block[x][y+2][z].flag == 23 && block[x][y+2][z].ID == block[x][y][z].ID)
					{
						if(block[x][y-1][z].flag == 2 && block[x+1][y-1][z].flag == 2)
						{
							if(block[x][y][z].ColorID == block[x][y-1][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y-1][z].ColorID < 1)
							{
								ID24++;
								num12--;
								num23--;
								num24++;
								count++;
								//cout<<x<<" "<<y<<" "<<z<<endl;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<4; k++)
									{
										block[x+i][y+k-1][z].flag = 24;
										block[x+i][y+k-1][z].ID = ID24;
									}
								}
								block[x][y-1][z].corner = 1;
								block[x+1][y+2][z].corner = 2;
							}
						}
					}
					//‰E‚Ì‚P~‚Q‚Æ‡¬
					else if(block[x][y-1][z].flag == 23 && block[x][y-1][z].ID == block[x][y][z].ID)
					{
						if(block[x][y+2][z].flag == 2 && block[x+1][y+2][z].flag == 2)
						{
							if(block[x][y][z].ColorID == block[x][y+2][z].ColorID || block[x][y][z].ColorID < 1 || block[x][y+2][z].ColorID < 1)
							{
								ID24++;
								num12--;
								num23--;
								num24++;
								count++;
								//cout<<x<<" "<<y<<" "<<z<<endl;
								for(int i(0); i<2; i++)
								{
									for(int k(0); k<4; k++)
									{
										block[x+i][y+k-1][z].flag = 24;
										block[x+i][y+k-1][z].ID = ID24;
									}
								}
								block[x][y-1][z].corner = 1;
								block[x+1][y+2][z].corner = 2;
							}
						}
					}
					//‚±‚ê‚ÍƒGƒ‰[‚¾I
					else
					{
						cout<<"ƒGƒ‰[II"<<endl;
						exit(-1);
					}
				}
			}
		}
	}

	cout<<count<<" ŒÂ‚Ì‚Q~‚S‚ª‚P~‚Q‚Æ‚Q~‚R‚©‚ç‚Å‚«‚½I"<<endl;
	//outputFlag("test05_12_23_to_24.txt", VoxSize);
}