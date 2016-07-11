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
								if(count13 == 13){goto next;}	//��������
							}
						}
					}
next:	//
					//                                             
					//         
					//                                             
					minLabel = *min_element(temp.begin(), temp.end());

					//�P�D��(INT_MAX)
					if(minLabel == INT_MAX)
					{
						box[x][y][z].SetLabelNumber(LabelNum);	
						src.push_back(LabelNum);				
						dst.push_back(LabelNum);
						LabelNum++;								
					}
					//�Q�D�O�iINT_MAX�								
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
	//cout<<"�X�V����F"<<dai<<endl;
	//cout<<"�X�V����F"<<shou<<endl;
	//cout<<"�X�V���Ȃ��F"<<ikoru<<endl;

	//cout<<"���b�N�A�b�v�e�[�u���F�X�V�O"<<endl;

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
				//�����{�N�Z���̏ꍇ
				if(box[x][y][z].GetFillValue())
				{
					//box[x][y][z].GetLabelNumber()�͔��̃��x���ԍ�(�O�A�P�A�Q�E�E�E)��Ԃ�
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
	//���b�N�A�b�v�e�[�u��
	int LabelNum(0);			//���x���ԍ�(�O����n�܂�Ƃ���)
	int minLabel(0);			//���x���ԍ��̍ŏ��l
	vector<int> temp;		//���ڃ{�N�Z���̎���3�{�N�Z���̃��x�����i�[����z��
	vector<int>::iterator it;
	int dai(0);
	int shou(0);
	int ikoru(0);
	//ofstream fout("LUT.csv");

	//edge�{�N�Z���ȊO�̑S�{�N�Z���ŉ�
	for(int z(1); z<m.num[2]-1; z++){
		for(int y(1); y<m.num[1]-1; y++){
			for(int x(1); x<m.num[0]-1; x++){
				//�����{�N�Z���̏�i�{�N�Z������26�ߖT
				if(box[x][y][z].GetFillValue()){
					//���ӂR�{�N�Z���̃��x���̔ԍ���z��ɑł�����
					temp.push_back(box[x-1][y][z].label);
					temp.push_back(box[x][y-1][z].label);
					temp.push_back(box[x][y][z-1].label);
					//�x�N�^�z��̃��x���̍ŏ���������      
					minLabel = *min_element(temp.begin(), temp.end());
					//�P�D���ׂĂO(INT_MAX)�̏ꍇ�@���@�Ō�Ɋ���U�����ԍ��{�P�̃��x���ԍ�������U��
					if(minLabel == INT_MAX){
						//fout<<LabelNum<<","<<x<<","<<y<<","<<z<<endl;
						box[x][y][z].SetLabelNumber(LabelNum);	//�{�b�N�X�̃��x���Ƀ��x���ԍ�������U��
						src.push_back(LabelNum);	//�V�������x����U�蕪�����̂ł��̔ԍ������b�N�A�b�v�e�[�u���Ɋi�[
						dst.push_back(LabelNum);
						LabelNum++;					//�Ō�Ɋ���U�����ԍ��{�P
					}
					//�Q�D�O�iINT_MAX�j�ȊO�̍ŏ��l�����ꍇ�͂��̒l�����x���ԍ�������U��
					else{
						minLabel = dst[minLabel];		//src != dst�̏ꍇ dst�̂ق����������̂ł���ōX�V����
						box[x][y][z].SetLabelNumber(minLabel);	//�{�b�N�X�̃��x���Ƀ��x���ԍ�������U��
						//############################
						//�������d�v�@���@�R�̃{�N�Z���ɕ����̃��x���ԍ��𑶍݂��鎞�̂��߂Ƀ��b�N�A�b�v�e�[�u��(LUT)���X�V
						//############################
						it = temp.begin();
						while( it != temp.end())
						{
							//�{�N�Z���̃��x���ԍ����ŏ��ł��O�iINT_MAX�j�ł��Ȃ��Ȃ�΃��b�N�A�b�v�e�[�u�����X�V
							if((*it) != minLabel && (*it) != INT_MAX)
							{
								if( minLabel < dst[*it] ){
									//fout<<"A,"<<src[*it]<<","<<dst[*it]<<","<<minLabel<<endl;
									dst[dst[*it]] = minLabel;		//���b�N�A�b�v�e�[�u����
									dst[*it] = minLabel;			//���b�N�A�b�v�e�[�u����
									dai++;	
								}					
								else if( dst[*it] < minLabel ){
									//fout<<"B,"<<src[*it]<<","<<dst[*it]<<","<<minLabel<<endl;
									dst[minLabel] = dst[*it];		//���b�N�A�b�v�e�[�u����
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
					//���̃��[�v�ׂ̈ɔz���������
					temp.clear();
				}
			}
		}
	}

	////cout<<"���b�N�A�b�v�e�[�u���F�X�V�O"<<endl;
	//for(int i(0); i<src.size(); i++){
	//	fout<<src[i]<<","<<dst[i]<<endl;
	//}

	//���b�N�A�b�v�e�[�u���𐮗�����
	for(int i(0); i<src.size(); i++){
		if(src[i] != dst[i]){
			dst[i] = dst[dst[i]];
		}
	}

	////cout<<"���b�N�A�b�v�e�[�u���F�X�V��"<<endl;
	//for(int i(0); i<src.size(); i++){
	//	fout<<src[i]<<","<<dst[i]<<endl;
	//}	

	//���b�N�A�b�v�e�[�u�������Ƀ{�N�Z���̃��x�����X�V
	int tempLabel(0);
	for(int z(1); z<m.num[2]-1; z++){
		for(int y(1); y<m.num[1]-1; y++){
			for(int x(1); x<m.num[0]-1; x++){
				//�����{�N�Z���̏ꍇ
				if(box[x][y][z].GetFillValue()){
					//box[x][y][z].GetLabelNumber()�͔��̃��x���ԍ�(�O�A�P�A�Q�E�E�E)��Ԃ�
					tempLabel = dst[box[x][y][z].GetLabelNumber()];
					box[x][y][z].SetLabelNumber(tempLabel); 
				}
			}
		}
	}

}

//�Ǘ��{�N�Z���̍폜
void ElimIsoVoxels_LUT(Model& m)
{
	//                                             
	//      ���x�����O�p�N���X�̃������̈�m��     
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
	//       ���f���̃{�N�Z�����ǂ���           
	//                                                         
	for(int x(1); x<m.num[0]-1; x++)
		for(int y(1); y<m.num[1]-1; y++)
			for(int z(1); z<m.num[2]-1; z++)
				if(m.Voxels[x][y][z].fill)			//�����{�N�Z���̏ꍇ
					box[x][y][z].SetFillValue(true);

	//                                                         
	//           �{�N�Z�������x�����O              
	//                                                         
	vector<int> src;
	vector<int> dst;
	//VoxelLabeling(m, box, src, dst);			//26�A��
	VoxelLabeling_6(m, box, src, dst);			//6�A��

	//���x���ԍ��O�F�H�H�@�P�F�H�H�@�Q�F�H�H�E�E�E�̃J�E���g
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

	//cout<<"���b�N�A�b�v�e�[�u���̃T�C�Y�F"<<src.size()<<" "<<dst.size()<<endl;
	//for(int i(0); i<src.size(); i++)
	//{
	//	cout<<src[i]<<" "<<dst[i]<<" "<<count[i]<<"��"<<endl;
	//}


	src.clear();
	src.shrink_to_fit();
	dst.clear();
	dst.shrink_to_fit();

	//                                               
	//                                               
	int maxLabelNum(*max_element(count.begin(), count.end()));
	int mem(0);		//�{�N�Z���̒��ň�ԑ������x���������Ă��郉�x���̔ԍ����i�[
	for(int i(0); i<count.size(); i++)
	{
		if(maxLabelNum == count[i])
		{
			mem = i;				//�̈�̃{�N�Z��������ԑ������x���ԍ�
			break;
		}
	}
	//                                               
	//             �Ǘ��{�N�Z���̍폜                
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

	//�������̉��
	for(int x(0); x<m.num[0]; x++){
		for(int y(0); y<m.num[1]; y++){
			delete [] box[x][y];
		}
		delete [] box[x];
	}
	delete [] box;

}
