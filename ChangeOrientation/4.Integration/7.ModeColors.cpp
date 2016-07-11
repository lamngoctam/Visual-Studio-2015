#include "../stdafx.h"


double DeltaE(CColor& aa, CColor& bb);
CColor RGB_to_Lab(CColor& rgb);



CColor GetVoxelColor_hue_mode(vector<Color_hue>& v)
{
	

	const int partN(25);					//F‘Š‚Ì•ªŠ„‹æŠÔ”
	const double minH(0.0);				//F‘Š‚ÌÅ¬’l
	const double maxH(360.0);		//F‘Š‚ÌÅ‘å’l
	double sec = maxH/partN;			//F‘Š‚Ì•ªŠ„‹æŠÔ•

	//
	int* count;							
	count = new int [partN];
	for(int i(0); i<partN; i++)
		count[i] = 0;

	int maxN(0);		//Å‘å‹æŠÔ‚ÉŠÜ‚Ü‚ê‚éF‚Ì”
	int maxS(0);		//Å‘å‹æŠÔ‚Ì”Ô†(‚R‚UF‚O`‚R‚T)

	int kk;
	int start(0);
	int end(0);
	CColor temp(0.0,0.0,0.0);
	//###############################
	//                          F‘Š(hue)‚Ì¸‡                          
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

	//
	for(int i=0; i<partN; i++){
		if(count[i] > maxN){
			maxN = count[i];
			maxS = i;
		}
	}

	//
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
	//•ªŠ„‹æŠÔ”‚ÉŠÖ‚·‚éƒƒ‚
	//ƒpƒ“ƒ_‚Ìê‡15‚Å¶‰E‚Ì–Ú‚ªo‚éA•@‚Í‚PƒuƒƒbƒN
	//	24‚Ìê‡¶–Ú‚ª‚æ‚­o‚é‚ªA‰E–Ú‚ª‚ ‚Ü‚èo‚È‚¢

	//const int partN(10);					//F‘Š‚Ì•ªŠ„‹æŠÔ”
	//const double minH(0.0);				//F‘Š‚ÌÅ¬’l
	//const double maxH(360.0);		//F‘Š‚ÌÅ‘å’l
	//double sec = maxH/partN;			//F‘Š‚Ì•ªŠ„‹æŠÔ•

	////•ªŠ„‹æŠÔ”–ˆ‚É“ü‚Á‚Ä‚¢‚é•p“x‚ğƒJƒEƒ“ƒg‚·‚é
	//int* count;							
	//count = new int [partN];
	//for(int i(0); i<partN; i++)
	//	count[i] = 0;

	//int maxN(0);		//Å‘å‹æŠÔ‚ÉŠÜ‚Ü‚ê‚éF‚Ì”
	//int maxS(0);		//Å‘å‹æŠÔ‚Ì”Ô†(‚R‚UF‚O`‚R‚T)

	//int kk;
	//int start(0);
	//int end(0);

	int* coutN = new int [(int)m.LegoColor.size()];
	for(int i(0);i<(int)m.LegoColor.size();i++)
		coutN[i]=0;
	CColor temp(0.0,0.0,0.0);
	double tempDeltaE;
	double min;			//Å¬’l


	for(int j(0);j<(int)v.size();j++){
	
	temp=RGB_to_Lab(v[j]);
	
	int min_no(0);		//Å¬’l‚ª‰½”Ô–Ú‚È‚Ì‚©
	min = DBL_MAX;					//Å¬’l‚ğdoubleŒ^‚ÌÅ‘å‚Æ‚¨‚­
	min_no = 0;

	for(int ii(0); ii<m.LegoColor.size(); ii++){
		tempDeltaE = DeltaE(m.LegoColor_Lab[ii], temp);
		if(tempDeltaE < min){
			min = tempDeltaE;			//Å¬’l‚ÌXV
			min_no = ii;						//Å¬’l‚ª‰½”Ô–Ú‚©
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
	////                          F‘Š(hue)‚Ì¸‡                          
	////###############################
	//sort(v.begin(), v.end(), Color_hue::Less_Hue);
	//
	////Še‹æŠÔ‚Ì•p“x‚ğƒJƒEƒ“ƒg
	//for(int i=0; i<v.size(); i++){
	//	kk = (int)(v[i].hue/sec);

	//	if(kk<0 || kk>partN-1)
	//		cout<<"baku-----"<<endl;
	//	else
	//		count[kk]++;
	//}

	////Å•p’l‹æŠÔ‚ğZo
	//for(int i=0; i<partN; i++){
	//	if(count[i] > maxN){
	//		maxN = count[i];
	//		maxS = i;
	//	}
	//}

	////Å•p‹æŠÔ‚Í”z—ñ‚Ìstart`end‚Å‚ ‚é
	//for(int i=0; i<maxS; i++){
	//	start += count[i];
	//}
	//end = start + maxN;

	////Å•p’l‹æŠÔ‚Ìrgb‚ğ‰ÁZ‚·‚é
	//for(int i=start; i<end; i++){
	//	temp.r += v[i].r;
	//	temp.g += v[i].g;
	//	temp.b += v[i].b;
	//}

	////•½‹Ï’l‚ğZo
	//temp.r = temp.r/maxN;
	//temp.g = temp.g/maxN;
	//temp.b = temp.b/maxN;

	//return temp;
}

CColor GetVoxelColor_lumi_mode(vector<Color_hue>& v)
{
	const int partN(15);					//‹P“xi0~255j‚Ì•ªŠ„‹æŠÔ”
	const double minL(0.0);				//‹P“x‚ÌÅ¬’l
	const double maxL(255.0);			//‹P“x‚ÌÅ‘å’l
	double sec = maxL/partN;			//‹P“x‚Ì•ªŠ„‹æŠÔ•

	//•ªŠ„‹æŠÔ”–ˆ‚É“ü‚Á‚Ä‚¢‚é•p“x‚ğƒJƒEƒ“ƒg‚·‚é
	int* count;							
	count = new int [partN];
	for(int i(0); i<partN; i++)
		count[i] = 0;

	int maxN(0);		//Å‘å‹æŠÔ‚ÉŠÜ‚Ü‚ê‚éF‚Ì”
	int maxS(0);		//Å‘å‹æŠÔ‚Ì”Ô†(‚R‚UF‚O`‚R‚T)

	int kk;
	int start(0);
	int end(0);
	CColor temp;

	//###############################
	//                          ‹P“x(lumi)‚Ì¸‡                          
	//###############################
	sort(v.begin(), v.end(), Color_hue::Less_Lumi);
	
	//Še‹æŠÔ‚Ì•p“x‚ğƒJƒEƒ“ƒg
	for(int i=0; i<v.size(); i++){
		kk = (int)(v[i].luminance/sec);

		if(kk<0 || kk>partN-1)
			cout<<"baku-----"<<endl;
		else
			count[kk]++;
	}

	//Å•p’l‹æŠÔ‚ğZo
	for(int i=0; i<partN; i++){
		if(count[i] > maxN){
			maxN = count[i];
			maxS = i;
		}
	}

	//Å•p‹æŠÔ‚Í”z—ñ‚Ìstart`end‚Å‚ ‚é
	for(int i=0; i<maxS; i++){
		start += count[i];
	}
	end = start + maxN;

	//Å•p’l‹æŠÔ‚Ìrgb‚ğ‰ÁZ‚·‚é
	for(int i=start; i<end; i++){
		temp.r += v[i].r;
		temp.g += v[i].g;
		temp.b += v[i].b;
	}

	//•½‹Ï’l‚ğZo
	temp.r = temp.r/maxN;
	temp.g = temp.g/maxN;
	temp.b = temp.b/maxN;

	return temp;
}
