#include "../stdafx.h"

//
void ElimIsoVoxels(Model& m)
{
	cout<<"============================"<<endl;
	cout<<" Eliminate Voxels           "<<endl;
	cout<<"============================"<<endl;
	clock_t time[2];	
	time[0] = clock();
	//##########################
	//        
	//##########################
	Labeling*** box;
	box = new Labeling **[m.num[0]];
	for(int x=0; x<m.num[0]; x++){
		box[x] = new Labeling *[m.num[1]];
		for(int y=0; y<m.num[1]; y++){
			box[x][y] = new Labeling [m.num[2]];
		}
	}
	//                                                         
	//                 
	//                                                         
	for(int x=0; x<m.num[0]; x++){
		for(int y=0; y<m.num[1]; y++){
			for(int z=0; z<m.num[2]; z++){
				if(m.Voxels[x][y][z].fill){			
					box[x][y][z].SetFillValue(true);
				}
			}
		}
	}
	//                                                        
	//                            
	//                                                        
	cout<<"\nStart check label for voxels\n"<<endl;
	int label(0);
	vector<cv::Point3i> samelabel;
	for(int x=1; x<m.num[0]-1; x++){
		for(int y=1; y<m.num[1]-1; y++){
			for(int z=1; z<m.num[2]-1; z++){
				//
				if(box[x][y][z].GetFillValue()){
					//
					if(box[x][y][z].GetLabelNumber()==INT_MAX){
						box[x][y][z].SetLabelNumber(label);
						box[x][y][z].SetFillValue(false);					
						
						if(box[x-1][y][z].GetFillValue()){				//x-1
							samelabel.push_back(cv::Point3i(x-1,y,z));
							box[x-1][y][z].SetFillValue(false);				
						}
						if(box[x+1][y][z].GetFillValue()){				//x+1
							samelabel.push_back(cv::Point3i(x+1,y,z));
							box[x+1][y][z].SetFillValue(false);				
						}
						if(box[x][y-1][z].GetFillValue()){				//y-1
							samelabel.push_back(cv::Point3i(x,y-1,z));
							box[x][y-1][z].SetFillValue(false);				
						}
						if(box[x][y+1][z].GetFillValue()){				//y+1
							samelabel.push_back(cv::Point3i(x,y+1,z));
							box[x][y+1][z].SetFillValue(false);				
						}
						if(box[x][y][z-1].GetFillValue()){				//z-1
							samelabel.push_back(cv::Point3i(x,y,z-1));
							box[x][y][z-1].SetFillValue(false);				
						}
						if(box[x][y][z+1].GetFillValue()){				//z+1
							samelabel.push_back(cv::Point3i(x,y,z+1));
							box[x][y][z+1].SetFillValue(false);				 
						}

						for(int i(0); i<samelabel.size(); i++){
							if(box[ samelabel[i].x ][ samelabel[i].y ][ samelabel[i].z ].GetLabelNumber() == INT_MAX){
								box[ samelabel[i].x ][ samelabel[i].y ][ samelabel[i].z ].SetLabelNumber(label);

								if(box[ samelabel[i].x-1 ][ samelabel[i].y ][ samelabel[i].z ].GetFillValue())	{		//x-1
									samelabel.push_back(cv::Point3i(samelabel[i].x-1, samelabel[i].y, samelabel[i].z));
									box[ samelabel[i].x-1 ][ samelabel[i].y ][ samelabel[i].z ].SetFillValue(false);		
								}
								if(box[ samelabel[i].x+1 ][ samelabel[i].y ][ samelabel[i].z ].GetFillValue()){			//x+1
									samelabel.push_back(cv::Point3i(samelabel[i].x+1, samelabel[i].y, samelabel[i].z));
									box[ samelabel[i].x+1 ][ samelabel[i].y ][ samelabel[i].z ].SetFillValue(false);		
								}
								if(box[ samelabel[i].x ][ samelabel[i].y-1 ][ samelabel[i].z ].GetFillValue()){			//y-1
									samelabel.push_back(cv::Point3i(samelabel[i].x, samelabel[i].y-1, samelabel[i].z));
									box[ samelabel[i].x ][ samelabel[i].y-1 ][ samelabel[i].z ].SetFillValue(false);		
								}
								if(box[ samelabel[i].x ][ samelabel[i].y+1 ][ samelabel[i].z ].GetFillValue()){			//y+1
									samelabel.push_back(cv::Point3i(samelabel[i].x, samelabel[i].y+1, samelabel[i].z));
									box[ samelabel[i].x ][ samelabel[i].y+1 ][ samelabel[i].z ].SetFillValue(false);		
								}
								if(box[ samelabel[i].x ][ samelabel[i].y ][ samelabel[i].z-1 ].GetFillValue())	{		//z-1
									samelabel.push_back(cv::Point3i(samelabel[i].x, samelabel[i].y, samelabel[i].z-1));
									box[ samelabel[i].x ][ samelabel[i].y ][ samelabel[i].z-1 ].SetFillValue(false);		
								}
								if(box[ samelabel[i].x ][ samelabel[i].y ][ samelabel[i].z+1 ].GetFillValue()){			//z+1
									samelabel.push_back(cv::Point3i(samelabel[i].x, samelabel[i].y, samelabel[i].z+1));
									box[ samelabel[i].x ][ samelabel[i].y ][ samelabel[i].z+1 ].SetFillValue(false);		
								}
							}
						}
						samelabel.clear();
						samelabel.shrink_to_fit();
						label++;		//0,‚P,‚Q,‚Rc
					}
				}
			}
		}
	}
	cout<<" "<<endl;
	//                                                                         
	// 
	//                                                                         
	int *voxnum;
	voxnum = new int [label];
	//
	for(int i(0); i<label; i++)
		voxnum[i]=0;

	int temp(0);
	for(int x=1; x<m.num[0]-1; x++){
		for(int y=1; y<m.num[1]-1; y++){
			for(int z=1; z<m.num[2]-1; z++){
				//
				if(m.Voxels[x][y][z].fill){
					temp = box[x][y][z].GetLabelNumber();
					voxnum[temp]++;
				}
			}
		}
	}
	int max = voxnum[0];
	int label_max = 0;		

	for(int i(1); i<label; i++){
		if(voxnum[i] > max){
			max = voxnum[i];
			label_max = i;
		}
	}

	//
	cout<<" "<<endl;
	for(int i(0); i<label; i++)
		cout<<"label"<<i<<" voxnum["<<i<<"] "<<voxnum[i]<<endl;

	int deleNum(0);
	for(int x=1; x<m.num[0]-1; x++){
		for(int y=1; y<m.num[1]-1; y++){
			for(int z=1; z<m.num[2]-1; z++){
				//
				if(m.Voxels[x][y][z].fill){
					//
					if(box[x][y][z].GetLabelNumber() != label_max)		
					{
						//
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

	cout << "deleteNum: " << deleNum << endl;
	cout<<"New Integration FillVoxelNum: "<<m.FillVoxelNum<<endl;
	
	//
	delete [] voxnum;
	for(int x=0; x<m.num[0]; x++){
		for(int y=0; y<m.num[1]; y++){
			delete [] box[x][y];
		}
		delete [] box[x];
	}
	delete [] box;

time[1] = clock();
cout<<"time eliminate voxels "<<(double)(time[1]-time[0])/CLOCKS_PER_SEC<<"s"<<endl;
}
