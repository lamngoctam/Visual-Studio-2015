#include "../stdafx.h"


double DeltaE(CColor& aa, CColor& bb);
CColor RGB_to_Lab(CColor& rgb);



CColor GetVoxelColor_hue_mode(vector<Color_hue>& v)
{
	

	const int partN(25);					//色相の分割区間数
	const double minH(0.0);				//色相の最小値
	const double maxH(360.0);		//色相の最大値
	double sec = maxH/partN;			//色相の分割区間幅

	//
	int* count;							
	count = new int [partN];
	for(int i(0); i<partN; i++)
		count[i] = 0;

	int maxN(0);		//最大区間に含まれる色の数
	int maxS(0);		//最大区間の番号(３６：０〜３５)

	int kk;
	int start(0);
	int end(0);
	CColor temp(0.0,0.0,0.0);
	//###############################
	//                          色相(hue)の昇順                          
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
	//分割区間数に関するメモ
	//パンダの場合15で左右の目が出る、鼻は１ブロック
	//	24の場合左目がよく出るが、右目があまり出ない

	//const int partN(10);					//色相の分割区間数
	//const double minH(0.0);				//色相の最小値
	//const double maxH(360.0);		//色相の最大値
	//double sec = maxH/partN;			//色相の分割区間幅

	////分割区間数毎に入っている頻度をカウントする
	//int* count;							
	//count = new int [partN];
	//for(int i(0); i<partN; i++)
	//	count[i] = 0;

	//int maxN(0);		//最大区間に含まれる色の数
	//int maxS(0);		//最大区間の番号(３６：０〜３５)

	//int kk;
	//int start(0);
	//int end(0);

	int* coutN = new int [(int)m.LegoColor.size()];
	for(int i(0);i<(int)m.LegoColor.size();i++)
		coutN[i]=0;
	CColor temp(0.0,0.0,0.0);
	double tempDeltaE;
	double min;			//最小値


	for(int j(0);j<(int)v.size();j++){
	
	temp=RGB_to_Lab(v[j]);
	
	int min_no(0);		//最小値が何番目なのか
	min = DBL_MAX;					//最小値をdouble型の最大とおく
	min_no = 0;

	for(int ii(0); ii<m.LegoColor.size(); ii++){
		tempDeltaE = DeltaE(m.LegoColor_Lab[ii], temp);
		if(tempDeltaE < min){
			min = tempDeltaE;			//最小値の更新
			min_no = ii;						//最小値が何番目か
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
	////                          色相(hue)の昇順                          
	////###############################
	//sort(v.begin(), v.end(), Color_hue::Less_Hue);
	//
	////各区間の頻度をカウント
	//for(int i=0; i<v.size(); i++){
	//	kk = (int)(v[i].hue/sec);

	//	if(kk<0 || kk>partN-1)
	//		cout<<"baku-----"<<endl;
	//	else
	//		count[kk]++;
	//}

	////最頻値区間を算出
	//for(int i=0; i<partN; i++){
	//	if(count[i] > maxN){
	//		maxN = count[i];
	//		maxS = i;
	//	}
	//}

	////最頻区間は配列のstart〜endである
	//for(int i=0; i<maxS; i++){
	//	start += count[i];
	//}
	//end = start + maxN;

	////最頻値区間のrgbを加算する
	//for(int i=start; i<end; i++){
	//	temp.r += v[i].r;
	//	temp.g += v[i].g;
	//	temp.b += v[i].b;
	//}

	////平均値を算出
	//temp.r = temp.r/maxN;
	//temp.g = temp.g/maxN;
	//temp.b = temp.b/maxN;

	//return temp;
}

CColor GetVoxelColor_lumi_mode(vector<Color_hue>& v)
{
	const int partN(15);					//輝度（0~255）の分割区間数
	const double minL(0.0);				//輝度の最小値
	const double maxL(255.0);			//輝度の最大値
	double sec = maxL/partN;			//輝度の分割区間幅

	//分割区間数毎に入っている頻度をカウントする
	int* count;							
	count = new int [partN];
	for(int i(0); i<partN; i++)
		count[i] = 0;

	int maxN(0);		//最大区間に含まれる色の数
	int maxS(0);		//最大区間の番号(３６：０〜３５)

	int kk;
	int start(0);
	int end(0);
	CColor temp;

	//###############################
	//                          輝度(lumi)の昇順                          
	//###############################
	sort(v.begin(), v.end(), Color_hue::Less_Lumi);
	
	//各区間の頻度をカウント
	for(int i=0; i<v.size(); i++){
		kk = (int)(v[i].luminance/sec);

		if(kk<0 || kk>partN-1)
			cout<<"baku-----"<<endl;
		else
			count[kk]++;
	}

	//最頻値区間を算出
	for(int i=0; i<partN; i++){
		if(count[i] > maxN){
			maxN = count[i];
			maxS = i;
		}
	}

	//最頻区間は配列のstart〜endである
	for(int i=0; i<maxS; i++){
		start += count[i];
	}
	end = start + maxN;

	//最頻値区間のrgbを加算する
	for(int i=start; i<end; i++){
		temp.r += v[i].r;
		temp.g += v[i].g;
		temp.b += v[i].b;
	}

	//平均値を算出
	temp.r = temp.r/maxN;
	temp.g = temp.g/maxN;
	temp.b = temp.b/maxN;

	return temp;
}
