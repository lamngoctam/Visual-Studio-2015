#include "../stdafx.h"

//http://imagingsolution.blog107.fc2.com/blog-entry-193.html

void VoxelLabeling(Model& m, Labeling*** box,	vector<int>& src, vector<int>& dst)
{
	
	int LabelNum(0);		
	int count13(0);			
	int minLabel(0);		
	vector<int> temp;		

	//int dai(0);
	//int shou(0);
	//int ikoru(0);
	//ofstream fout("LUT.csv");

	//edge
	for(int z(1); z<m.num[2]-1; z++)
	{
		for(int y(1); y<m.num[1]-1; y++)
		{
			for(int x(1); x<m.num[0]-1; x++)
			{
				//
				if(box[x][y][z].GetFillValue())
				{
					//                                              
					//
					//                                              
					count13 = 0;
					for(int c(0); c<2; c++)				
					{
						for(int b(0); b<3; b++)			
						{
							for(int a(0); a<3; a++)		
							{
								temp.push_back(box[x-1+a][y-1+b][z-1+c].label);
								count13++;						//13
								if(count13 == 13){goto next;}	//‚±‚±‚©‚ç
							}
						}
					}
next:	//
					//                                             
					//         
					//                                             
					minLabel = *min_element(temp.begin(), temp.end());

					//‚PD‚·(INT_MAX)
					if(minLabel == INT_MAX)
					{
						box[x][y][z].SetLabelNumber(LabelNum);	
						src.push_back(LabelNum);				
						dst.push_back(LabelNum);
						LabelNum++;								
					}
					//‚QD‚OiINT_MAX								
					else
					{
						minLabel = dst[minLabel];		//src != dst	

						box[x][y][z].SetLabelNumber(minLabel);			
																		
						vector<int>::iterator it = temp.begin();
						while( it != temp.end())
						{
																		
							if((*it) != minLabel && (*it) != INT_MAX)
							{
								if( minLabel < dst[*it] ){
									//fout<<"A,"<<src[*it]<<","<<dst[*it]<<","<<minLabel<<endl;
									dst[dst[*it]] = minLabel;		
									dst[*it] = minLabel;			
									//dai++;	
								}
								else if( dst[*it] < minLabel ){
									//fout<<"B,"<<src[*it]<<","<<dst[*it]<<","<<minLabel<<endl;
									dst[minLabel] = dst[*it];		
									//shou++;	
								}
								//else{
								//	fout<<"C,"<<src[*it]<<","<<dst[*it]<<","<<minLabel<<endl;
								//	ikoru++;
								//}
							}
							++it;
						}
					}
					
					temp.clear();
				}
			}
		}
	}
	//cout<<"XV‚·‚éF"<<dai<<endl;
	//cout<<"XV‚·‚éF"<<shou<<endl;
	//cout<<"XV‚µ‚È‚¢F"<<ikoru<<endl;

	//cout<<"ƒ‹ƒbƒNƒAƒbƒvƒe[ƒuƒ‹FXV‘O"<<endl;

	//for(int i(0); i<src.size(); i++){
	//	fout<<src[i]<<","<<dst[i]<<endl;
	//}

	//
	for(int i(0); i<src.size(); i++)
	{
		if(src[i] != dst[i])
		{
			dst[i] = dst[dst[i]];
		}
	}

	//for(int i(0); i<src.size(); i++){
	//	fout<<src[i]<<","<<dst[i]<<endl;
	//}	

	int tempLabel(0);
	for(int z(1); z<m.num[2]-1; z++)
	{
		for(int y(1); y<m.num[1]-1; y++)
		{
			for(int x(1); x<m.num[0]-1; x++)
			{
				//“à•”ƒ{ƒNƒZƒ‹‚Ìê‡
				if(box[x][y][z].GetFillValue())
				{
					//box[x][y][z].GetLabelNumber()‚Í” ‚Ìƒ‰ƒxƒ‹”Ô†(‚OA‚PA‚QEEE)‚ğ•Ô‚·
					tempLabel = dst[box[x][y][z].GetLabelNumber()];
					box[x][y][z].SetLabelNumber(tempLabel); 
				}
			}
		}
	}
}

//
void VoxelLabeling_6(Model& m, Labeling*** box,	vector<int>& src, vector<int>& dst)
{
	//ƒ‹ƒbƒNƒAƒbƒvƒe[ƒuƒ‹
	int LabelNum(0);			//ƒ‰ƒxƒ‹”Ô†(‚O‚©‚çn‚Ü‚é‚Æ‚·‚é)
	int minLabel(0);			//ƒ‰ƒxƒ‹”Ô†‚ÌÅ¬’l
	vector<int> temp;		//’–Úƒ{ƒNƒZƒ‹‚Ìü•Ó3ƒ{ƒNƒZƒ‹‚Ìƒ‰ƒxƒ‹‚ğŠi”[‚·‚é”z—ñ
	vector<int>::iterator it;
	int dai(0);
	int shou(0);
	int ikoru(0);
	//ofstream fout("LUT.csv");

	//edgeƒ{ƒNƒZƒ‹ˆÈŠO‚Ì‘Sƒ{ƒNƒZƒ‹‚Å‰ñ‚·
	for(int z(1); z<m.num[2]-1; z++){
		for(int y(1); y<m.num[1]-1; y++){
			for(int x(1); x<m.num[0]-1; x++){
				//“à•”ƒ{ƒNƒZƒ‹‚Ìêiƒ{ƒNƒZƒ‹ü‚è26‹ß–T
				if(box[x][y][z].GetFillValue()){
					//ü•Ó‚Rƒ{ƒNƒZƒ‹‚Ìƒ‰ƒxƒ‹‚Ì”Ô†‚ğ”z—ñ‚É‘Å‚¿‚Ş
					temp.push_back(box[x-1][y][z].label);
					temp.push_back(box[x][y-1][z].label);
					temp.push_back(box[x][y][z-1].label);
					//ƒxƒNƒ^”z—ñ‚Ìƒ‰ƒxƒ‹‚ÌÅ¬‚ğŒ©‚Â‚¯‚é      
					minLabel = *min_element(temp.begin(), temp.end());
					//‚PD‚·‚×‚Ä‚O(INT_MAX)‚Ìê‡@¨@ÅŒã‚ÉŠ„‚èU‚Á‚½”Ô†{‚P‚Ìƒ‰ƒxƒ‹”Ô†‚ğŠ„‚èU‚é
					if(minLabel == INT_MAX){
						//fout<<LabelNum<<","<<x<<","<<y<<","<<z<<endl;
						box[x][y][z].SetLabelNumber(LabelNum);	//ƒ{ƒbƒNƒX‚Ìƒ‰ƒxƒ‹‚Éƒ‰ƒxƒ‹”Ô†‚ğŠ„‚èU‚é
						src.push_back(LabelNum);	//V‚µ‚­ƒ‰ƒxƒ‹‚ğU‚è•ª‚¯‚½‚Ì‚Å‚»‚Ì”Ô†‚ğƒ‹ƒbƒNƒAƒbƒvƒe[ƒuƒ‹‚ÉŠi”[
						dst.push_back(LabelNum);
						LabelNum++;					//ÅŒã‚ÉŠ„‚èU‚Á‚½”Ô†{‚P
					}
					//‚QD‚OiINT_MAXjˆÈŠO‚ÌÅ¬’l‚ğ‚Âê‡‚Í‚»‚Ì’l‚ğƒ‰ƒxƒ‹”Ô†‚ğŠ„‚èU‚é
					else{
						minLabel = dst[minLabel];		//src != dst‚Ìê‡ dst‚Ì‚Ù‚¤‚ª¬‚³‚¢‚Ì‚Å‚±‚ê‚ÅXV‚·‚é
						box[x][y][z].SetLabelNumber(minLabel);	//ƒ{ƒbƒNƒX‚Ìƒ‰ƒxƒ‹‚Éƒ‰ƒxƒ‹”Ô†‚ğŠ„‚èU‚é
						//############################
						//¦‚±‚±d—v@¨@‚RŒÂ‚Ìƒ{ƒNƒZƒ‹‚É•¡”‚Ìƒ‰ƒxƒ‹”Ô†‚ğ‘¶İ‚·‚é‚Ì‚½‚ß‚Éƒ‹ƒbƒNƒAƒbƒvƒe[ƒuƒ‹(LUT)‚ğXV
						//############################
						it = temp.begin();
						while( it != temp.end())
						{
							//ƒ{ƒNƒZƒ‹‚Ìƒ‰ƒxƒ‹”Ô†‚ªÅ¬‚Å‚à‚OiINT_MAXj‚Å‚à‚È‚¢‚È‚ç‚Îƒ‹ƒbƒNƒAƒbƒvƒe[ƒuƒ‹‚ğXV
							if((*it) != minLabel && (*it) != INT_MAX)
							{
								if( minLabel < dst[*it] ){
									//fout<<"A,"<<src[*it]<<","<<dst[*it]<<","<<minLabel<<endl;
									dst[dst[*it]] = minLabel;		//ƒ‹ƒbƒNƒAƒbƒvƒe[ƒuƒ‹‚ğ
									dst[*it] = minLabel;			//ƒ‹ƒbƒNƒAƒbƒvƒe[ƒuƒ‹‚ğ
									dai++;	
								}					
								else if( dst[*it] < minLabel ){
									//fout<<"B,"<<src[*it]<<","<<dst[*it]<<","<<minLabel<<endl;
									dst[minLabel] = dst[*it];		//ƒ‹ƒbƒNƒAƒbƒvƒe[ƒuƒ‹‚ğ
									shou++;	
								}
								//else{
								//	fout<<"C,"<<src[*it]<<","<<dst[*it]<<","<<minLabel<<endl;
								//	ikoru++;
								//}
							}
							++it;
						}
					}
					//Ÿ‚Ìƒ‹[ƒv‚Ìˆ×‚É”z—ñ‚ğ‰Šú‰»
					temp.clear();
				}
			}
		}
	}

	////cout<<"ƒ‹ƒbƒNƒAƒbƒvƒe[ƒuƒ‹FXV‘O"<<endl;
	//for(int i(0); i<src.size(); i++){
	//	fout<<src[i]<<","<<dst[i]<<endl;
	//}

	//ƒ‹ƒbƒNƒAƒbƒvƒe[ƒuƒ‹‚ğ®—‚·‚é
	for(int i(0); i<src.size(); i++){
		if(src[i] != dst[i]){
			dst[i] = dst[dst[i]];
		}
	}

	////cout<<"ƒ‹ƒbƒNƒAƒbƒvƒe[ƒuƒ‹FXVŒã"<<endl;
	//for(int i(0); i<src.size(); i++){
	//	fout<<src[i]<<","<<dst[i]<<endl;
	//}	

	//ƒ‹ƒbƒNƒAƒbƒvƒe[ƒuƒ‹‚ğŒ³‚Éƒ{ƒNƒZƒ‹‚Ìƒ‰ƒxƒ‹‚ğXV
	int tempLabel(0);
	for(int z(1); z<m.num[2]-1; z++){
		for(int y(1); y<m.num[1]-1; y++){
			for(int x(1); x<m.num[0]-1; x++){
				//“à•”ƒ{ƒNƒZƒ‹‚Ìê‡
				if(box[x][y][z].GetFillValue()){
					//box[x][y][z].GetLabelNumber()‚Í” ‚Ìƒ‰ƒxƒ‹”Ô†(‚OA‚PA‚QEEE)‚ğ•Ô‚·
					tempLabel = dst[box[x][y][z].GetLabelNumber()];
					box[x][y][z].SetLabelNumber(tempLabel); 
				}
			}
		}
	}

}

//ŒÇ—§ƒ{ƒNƒZƒ‹‚Ìíœ
void ElimIsoVoxels_LUT(Model& m)
{
	//                                             
	//      ƒ‰ƒxƒŠƒ“ƒO—pƒNƒ‰ƒX‚Ìƒƒ‚ƒŠ—ÌˆæŠm•Û     
	//                                             
	Labeling ***box;
	box = new Labeling **[m.num[0]];
	for(int x(0); x<m.num[0]; x++){
		box[x] = new Labeling *[m.num[1]];
		for(int y(0); y<m.num[1]; y++){
			box[x][y] = new Labeling [m.num[2]];
		}
	}
	//                                                         
	//       ƒ‚ƒfƒ‹‚Ìƒ{ƒNƒZƒ‹‚©‚Ç‚¤‚©           
	//                                                         
	for(int x(1); x<m.num[0]-1; x++)
		for(int y(1); y<m.num[1]-1; y++)
			for(int z(1); z<m.num[2]-1; z++)
				if(m.Voxels[x][y][z].fill)			//“à•”ƒ{ƒNƒZƒ‹‚Ìê‡
					box[x][y][z].SetFillValue(true);

	//                                                         
	//           ƒ{ƒNƒZƒ‹‚ğƒ‰ƒxƒŠƒ“ƒO              
	//                                                         
	vector<int> src;
	vector<int> dst;
	//VoxelLabeling(m, box, src, dst);			//26˜AŒ‹
	VoxelLabeling_6(m, box, src, dst);			//6˜AŒ‹

	//ƒ‰ƒxƒ‹”Ô†‚OFHHŒÂ@‚PFHHŒÂ@‚QFHHŒÂEEE‚ÌƒJƒEƒ“ƒg
	int tempLabel(0);
	vector<int> count(src.size(),0);
	for(int z(1); z<m.num[2]-1; z++){
		for(int y(1); y<m.num[1]-1; y++){
			for(int x(1); x<m.num[0]-1; x++){
				if(m.Voxels[x][y][z].fill){
					tempLabel = box[x][y][z].GetLabelNumber();
					count[tempLabel]++; 
				}
			}
		}
	}

	//cout<<"ƒ‹ƒbƒNƒAƒbƒvƒe[ƒuƒ‹‚ÌƒTƒCƒYF"<<src.size()<<" "<<dst.size()<<endl;
	//for(int i(0); i<src.size(); i++)
	//{
	//	cout<<src[i]<<" "<<dst[i]<<" "<<count[i]<<"ŒÂ"<<endl;
	//}


	src.clear();
	src.shrink_to_fit();
	dst.clear();
	dst.shrink_to_fit();

	//                                               
	//                                               
	int maxLabelNum(*max_element(count.begin(), count.end()));
	int mem(0);		//ƒ{ƒNƒZƒ‹‚Ì’†‚Åˆê”Ô‘½‚¢ƒ‰ƒxƒ‹‚ğ‚Á‚Ä‚¢‚éƒ‰ƒxƒ‹‚Ì”Ô†‚ğŠi”[
	for(int i(0); i<count.size(); i++)
	{
		if(maxLabelNum == count[i])
		{
			mem = i;				//—Ìˆæ‚Ìƒ{ƒNƒZƒ‹”‚ªˆê”Ô‘½‚¢ƒ‰ƒxƒ‹”Ô†
			break;
		}
	}
	//                                               
	//             ŒÇ—§ƒ{ƒNƒZƒ‹‚Ìíœ                
	//                                               
	int deleNum(0);
	for(int z(1); z<m.num[2]-1; z++){
		for(int y(1); y<m.num[1]-1; y++){
			for(int x(1); x<m.num[0]-1; x++){
				
				if(m.Voxels[x][y][z].fill){
					
					if(box[x][y][z].GetLabelNumber() != mem)		
					{
						m.IsoVoxels.push_back(m.Voxels[x][y][z]);
						m.Voxels[x][y][z].fill = false;
						m.Voxels[x][y][z].surf = false;
						m.FillVoxelNum--;
						deleNum++;
					}
				}
			}
		}
	}
	cout<<"--------------------------"<<deleNum<<endl;

	//ƒƒ‚ƒŠ‚Ì‰ğ•ú
	for(int x(0); x<m.num[0]; x++){
		for(int y(0); y<m.num[1]; y++){
			delete [] box[x][y];
		}
		delete [] box[x];
	}
	delete [] box;

}
