#include "../stdafx.h"


double DeltaE(CColor& aa, CColor& bb);
CColor RGB_to_Lab(CColor& rgb);



CColor GetVoxelColor_hue_mode(vector<Color_hue>& v)
{
	

	const int partN(25);					//�F���̕�����Ԑ�
	const double minH(0.0);				//�F���̍ŏ��l
	const double maxH(360.0);		//�F���̍ő�l
	double sec = maxH/partN;			//�F���̕�����ԕ�

	//
	int* count;							
	count = new int [partN];
	for(int i(0); i<partN; i++)
		count[i] = 0;

	int maxN(0);		//�ő��ԂɊ܂܂��F�̐�
	int maxS(0);		//�ő��Ԃ̔ԍ�(�R�U�F�O�`�R�T)

	int kk;
	int start(0);
	int end(0);
	CColor temp(0.0,0.0,0.0);
	//###############################
	//                          �F��(hue)�̏���                          
	//###############################
	sort(v.begin(), v.end(), Color_hue::Less_Hue);
	
	//
	for(int i=0; i<v.size(); i++){
		kk = (int)(v[i].hue/sec);

		if(kk<0 || kk>partN-1)
			cout<<"baku-----"<<endl;
		else
			count[kk]++;
	}

	//�
	for(int i=0; i<partN; i++){
		if(count[i] > maxN){
			maxN = count[i];
			maxS = i;
		}
	}

	//�
	for(int i=0; i<maxS; i++){
		start += count[i];
	}
	end = start + maxN;

	//
	for(int i=start; i<end; i++){
		temp.r += v[i].r;
		temp.g += v[i].g;
		temp.b += v[i].b;
	}

	//
	temp.r = temp.r/maxN;
	temp.g = temp.g/maxN;
	temp.b = temp.b/maxN;

	return temp;
}


CColor GetVoxelColor_hue_mode(vector<Color_hue>& v,Model &m)
{
	//������Ԑ��Ɋւ��郁��
	//�p���_�̏ꍇ15�ō��E�̖ڂ��o��A�@�͂P�u���b�N
	//	24�̏ꍇ���ڂ��悭�o�邪�A�E�ڂ����܂�o�Ȃ�

	//const int partN(10);					//�F���̕�����Ԑ�
	//const double minH(0.0);				//�F���̍ŏ��l
	//const double maxH(360.0);		//�F���̍ő�l
	//double sec = maxH/partN;			//�F���̕�����ԕ�

	////������Ԑ����ɓ����Ă���p�x���J�E���g����
	//int* count;							
	//count = new int [partN];
	//for(int i(0); i<partN; i++)
	//	count[i] = 0;

	//int maxN(0);		//�ő��ԂɊ܂܂��F�̐�
	//int maxS(0);		//�ő��Ԃ̔ԍ�(�R�U�F�O�`�R�T)

	//int kk;
	//int start(0);
	//int end(0);

	int* coutN = new int [(int)m.LegoColor.size()];
	for(int i(0);i<(int)m.LegoColor.size();i++)
		coutN[i]=0;
	CColor temp(0.0,0.0,0.0);
	double tempDeltaE;
	double min;			//�ŏ��l


	for(int j(0);j<(int)v.size();j++){
	
	temp=RGB_to_Lab(v[j]);
	
	int min_no(0);		//�ŏ��l�����ԖڂȂ̂�
	min = DBL_MAX;					//�ŏ��l��double�^�̍ő�Ƃ���
	min_no = 0;

	for(int ii(0); ii<m.LegoColor.size(); ii++){
		tempDeltaE = DeltaE(m.LegoColor_Lab[ii], temp);
		if(tempDeltaE < min){
			min = tempDeltaE;			//�ŏ��l�̍X�V
			min_no = ii;						//�ŏ��l�����Ԗڂ�
		}
	}
	coutN[min_no]++;
	}
	int max(0);
	int max_no(0);
	for(int i(0);i<(int)m.LegoColor.size();i++){
		if(max<coutN[i]){
		max=coutN[i];
		max_no=i;
		}
	}
	temp=m.LegoColor[max_no];
	delete [] coutN;
	return temp;

	////###############################
	////                          �F��(hue)�̏���                          
	////###############################
	//sort(v.begin(), v.end(), Color_hue::Less_Hue);
	//
	////�e��Ԃ̕p�x���J�E���g
	//for(int i=0; i<v.size(); i++){
	//	kk = (int)(v[i].hue/sec);

	//	if(kk<0 || kk>partN-1)
	//		cout<<"baku-----"<<endl;
	//	else
	//		count[kk]++;
	//}

	////�ŕp�l��Ԃ��Z�o
	//for(int i=0; i<partN; i++){
	//	if(count[i] > maxN){
	//		maxN = count[i];
	//		maxS = i;
	//	}
	//}

	////�ŕp��Ԃ͔z���start�`end�ł���
	//for(int i=0; i<maxS; i++){
	//	start += count[i];
	//}
	//end = start + maxN;

	////�ŕp�l��Ԃ�rgb�����Z����
	//for(int i=start; i<end; i++){
	//	temp.r += v[i].r;
	//	temp.g += v[i].g;
	//	temp.b += v[i].b;
	//}

	////���ϒl���Z�o
	//temp.r = temp.r/maxN;
	//temp.g = temp.g/maxN;
	//temp.b = temp.b/maxN;

	//return temp;
}

CColor GetVoxelColor_lumi_mode(vector<Color_hue>& v)
{
	const int partN(15);					//�P�x�i0~255�j�̕�����Ԑ�
	const double minL(0.0);				//�P�x�̍ŏ��l
	const double maxL(255.0);			//�P�x�̍ő�l
	double sec = maxL/partN;			//�P�x�̕�����ԕ�

	//������Ԑ����ɓ����Ă���p�x���J�E���g����
	int* count;							
	count = new int [partN];
	for(int i(0); i<partN; i++)
		count[i] = 0;

	int maxN(0);		//�ő��ԂɊ܂܂��F�̐�
	int maxS(0);		//�ő��Ԃ̔ԍ�(�R�U�F�O�`�R�T)

	int kk;
	int start(0);
	int end(0);
	CColor temp;

	//###############################
	//                          �P�x(lumi)�̏���                          
	//###############################
	sort(v.begin(), v.end(), Color_hue::Less_Lumi);
	
	//�e��Ԃ̕p�x���J�E���g
	for(int i=0; i<v.size(); i++){
		kk = (int)(v[i].luminance/sec);

		if(kk<0 || kk>partN-1)
			cout<<"baku-----"<<endl;
		else
			count[kk]++;
	}

	//�ŕp�l��Ԃ��Z�o
	for(int i=0; i<partN; i++){
		if(count[i] > maxN){
			maxN = count[i];
			maxS = i;
		}
	}

	//�ŕp��Ԃ͔z���start�`end�ł���
	for(int i=0; i<maxS; i++){
		start += count[i];
	}
	end = start + maxN;

	//�ŕp�l��Ԃ�rgb�����Z����
	for(int i=start; i<end; i++){
		temp.r += v[i].r;
		temp.g += v[i].g;
		temp.b += v[i].b;
	}

	//���ϒl���Z�o
	temp.r = temp.r/maxN;
	temp.g = temp.g/maxN;
	temp.b = temp.b/maxN;

	return temp;
}
