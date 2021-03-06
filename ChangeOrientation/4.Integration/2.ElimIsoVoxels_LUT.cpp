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
								if(count13 == 13){goto next;}	//±±©ç
							}
						}
					}
next:	//
					//                                             
					//         
					//                                             
					minLabel = *min_element(temp.begin(), temp.end());

					//PD·(INT_MAX)
					if(minLabel == INT_MAX)
					{
						box[x][y][z].SetLabelNumber(LabelNum);	
						src.push_back(LabelNum);				
						dst.push_back(LabelNum);
						LabelNum++;								
					}
					//QDOiINT_MAX								
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
	//cout<<"XV·éF"<<dai<<endl;
	//cout<<"XV·éF"<<shou<<endl;
	//cout<<"XVµÈ¢F"<<ikoru<<endl;

	//cout<<"bNAbve[uFXVO"<<endl;

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
				//à{NZÌê
				if(box[x][y][z].GetFillValue())
				{
					//box[x][y][z].GetLabelNumber()Í ÌxÔ(OAPAQEEE)ðÔ·
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
	//bNAbve[u
	int LabelNum(0);			//xÔ(O©çnÜéÆ·é)
	int minLabel(0);			//xÔÌÅ¬l
	vector<int> temp;		//Ú{NZÌüÓ3{NZÌxði[·ézñ
	vector<int>::iterator it;
	int dai(0);
	int shou(0);
	int ikoru(0);
	//ofstream fout("LUT.csv");

	//edge{NZÈOÌS{NZÅñ·
	for(int z(1); z<m.num[2]-1; z++){
		for(int y(1); y<m.num[1]-1; y++){
			for(int x(1); x<m.num[0]-1; x++){
				//à{NZÌêi{NZüè26ßT
				if(box[x][y][z].GetFillValue()){
					//üÓR{NZÌxÌÔðzñÉÅ¿Þ
					temp.push_back(box[x-1][y][z].label);
					temp.push_back(box[x][y-1][z].label);
					temp.push_back(box[x][y][z-1].label);
					//xN^zñÌxÌÅ¬ð©Â¯é      
					minLabel = *min_element(temp.begin(), temp.end());
					//PD·×ÄO(INT_MAX)Ìê@¨@ÅãÉèUÁ½Ô{PÌxÔðèUé
					if(minLabel == INT_MAX){
						//fout<<LabelNum<<","<<x<<","<<y<<","<<z<<endl;
						box[x][y][z].SetLabelNumber(LabelNum);	//{bNXÌxÉxÔðèUé
						src.push_back(LabelNum);	//Vµ­xðUèª¯½ÌÅ»ÌÔðbNAbve[uÉi[
						dst.push_back(LabelNum);
						LabelNum++;					//ÅãÉèUÁ½Ô{P
					}
					//QDOiINT_MAXjÈOÌÅ¬lðÂêÍ»ÌlðxÔðèUé
					else{
						minLabel = dst[minLabel];		//src != dstÌê dstÌÙ¤ª¬³¢ÌÅ±êÅXV·é
						box[x][y][z].SetLabelNumber(minLabel);	//{bNXÌxÉxÔðèUé
						//############################
						//¦±±dv@¨@RÂÌ{NZÉ¡ÌxÔð¶Ý·éÌ½ßÉbNAbve[u(LUT)ðXV
						//############################
						it = temp.begin();
						while( it != temp.end())
						{
							//{NZÌxÔªÅ¬ÅàOiINT_MAXjÅàÈ¢ÈçÎbNAbve[uðXV
							if((*it) != minLabel && (*it) != INT_MAX)
							{
								if( minLabel < dst[*it] ){
									//fout<<"A,"<<src[*it]<<","<<dst[*it]<<","<<minLabel<<endl;
									dst[dst[*it]] = minLabel;		//bNAbve[uð
									dst[*it] = minLabel;			//bNAbve[uð
									dai++;	
								}					
								else if( dst[*it] < minLabel ){
									//fout<<"B,"<<src[*it]<<","<<dst[*it]<<","<<minLabel<<endl;
									dst[minLabel] = dst[*it];		//bNAbve[uð
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
					//Ì[vÌ×Ézñðú»
					temp.clear();
				}
			}
		}
	}

	////cout<<"bNAbve[uFXVO"<<endl;
	//for(int i(0); i<src.size(); i++){
	//	fout<<src[i]<<","<<dst[i]<<endl;
	//}

	//bNAbve[uð®·é
	for(int i(0); i<src.size(); i++){
		if(src[i] != dst[i]){
			dst[i] = dst[dst[i]];
		}
	}

	////cout<<"bNAbve[uFXVã"<<endl;
	//for(int i(0); i<src.size(); i++){
	//	fout<<src[i]<<","<<dst[i]<<endl;
	//}	

	//bNAbve[uð³É{NZÌxðXV
	int tempLabel(0);
	for(int z(1); z<m.num[2]-1; z++){
		for(int y(1); y<m.num[1]-1; y++){
			for(int x(1); x<m.num[0]-1; x++){
				//à{NZÌê
				if(box[x][y][z].GetFillValue()){
					//box[x][y][z].GetLabelNumber()Í ÌxÔ(OAPAQEEE)ðÔ·
					tempLabel = dst[box[x][y][z].GetLabelNumber()];
					box[x][y][z].SetLabelNumber(tempLabel); 
				}
			}
		}
	}

}

//Ç§{NZÌí
void ElimIsoVoxels_LUT(Model& m)
{
	//                                             
	//      xOpNXÌÌæmÛ     
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
	//       fÌ{NZ©Ç¤©           
	//                                                         
	for(int x(1); x<m.num[0]-1; x++)
		for(int y(1); y<m.num[1]-1; y++)
			for(int z(1); z<m.num[2]-1; z++)
				if(m.Voxels[x][y][z].fill)			//à{NZÌê
					box[x][y][z].SetFillValue(true);

	//                                                         
	//           {NZðxO              
	//                                                         
	vector<int> src;
	vector<int> dst;
	//VoxelLabeling(m, box, src, dst);			//26A
	VoxelLabeling_6(m, box, src, dst);			//6A

	//xÔOFHHÂ@PFHHÂ@QFHHÂEEEÌJEg
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

	//cout<<"bNAbve[uÌTCYF"<<src.size()<<" "<<dst.size()<<endl;
	//for(int i(0); i<src.size(); i++)
	//{
	//	cout<<src[i]<<" "<<dst[i]<<" "<<count[i]<<"Â"<<endl;
	//}


	src.clear();
	src.shrink_to_fit();
	dst.clear();
	dst.shrink_to_fit();

	//                                               
	//                                               
	int maxLabelNum(*max_element(count.begin(), count.end()));
	int mem(0);		//{NZÌÅêÔ½¢xðÁÄ¢éxÌÔði[
	for(int i(0); i<count.size(); i++)
	{
		if(maxLabelNum == count[i])
		{
			mem = i;				//ÌæÌ{NZªêÔ½¢xÔ
			break;
		}
	}
	//                                               
	//             Ç§{NZÌí                
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

	//Ìðú
	for(int x(0); x<m.num[0]; x++){
		for(int y(0); y<m.num[1]; y++){
			delete [] box[x][y];
		}
		delete [] box[x];
	}
	delete [] box;

}
