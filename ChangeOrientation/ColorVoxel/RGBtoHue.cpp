#include "../stdafx.h"
#include "../Lego.h"

extern Model Integ;
extern string directory[2];
extern BrickTable table;


double Min(double r, double g, double b);
double Max(double r, double g, double b);
void  LegoRGB_to_Hue(Model& m);

double RGBtoHue(double r, double g, double b);
CColor RGB_to_Lab(CColor& rgb);
CColor RGB_to_Lab2(CColor& rgb);
double DeltaE(CColor& aa, CColor& bb);
double DeltaE_noL(CColor& aa, CColor& bb);
double DeltaRGB(CColor& aa, CColor& bb);
void  LegoRGB_to_Lab(Model& m);

void RealColor_to_LegoColor_lab(Model& m, Lego*** block);

// RGB‚Hue
double RGBtoHue(double r, double g, double b)		//r,g,b(0.0~1.0)
{
	double max = Max(r, g, b);
	double min = Min(r, g, b);
	double hue(0.0);
	if (max == 0.0 || max == min)
		return 0.0;

	//F‘Š‚ðŒvŽZ‚·‚é
	if (max == r)
		hue = 60.0 * (g - b) / (max - min);
	else if (max == g)
		hue = 60.0 * (b - r) / (max - min) + 120.0;
	else if (max == b)
		hue = 60.0 * (r - g) / (max - min) + 240.0;

	//—áŠOˆ— hue < 0@‚È‚ç‚Î360.0‚ð‘«‚·
	if (hue < 0.0)
		hue += 360.0;
	//—áŠOˆ— hue > 360@‚È‚ç‚Î360‚ÅŠ„‚Á‚½‚ ‚Ü‚è
	else if (hue > 360.0)
		hue = fmod(hue, 360.0);

	return hue;
}

//LEGO‚RGB‚
void  LegoRGB_to_Hue(Model& m)
{
	//LEGO
	//string filename("LEGOColorRGB.txt");
	string filename("lego_color_rgb.txt");
	ifstream fin(directory[0] + filename);					//
	if (!fin){
		cout << filename << "  " << endl;
		exit(-1);
	}
	string line;
	istringstream ssline;
	CColor temp;

	while (!fin.eof())
	{
		getline(fin, line);										
		if (line.size() == 0 || line[0] == '\n') continue;		
		ssline.str(line);										
		ssline >> temp.r >> temp.g >> temp.b;					
		temp.r = temp.r / 255.0;								
		temp.g = temp.g / 255.0;
		temp.b = temp.b / 255.0;
		m.LegoColor.push_back(temp);							
		ssline.clear();											
	}
	ssline.str("");		

	m.LegoHue.reserve(m.LegoColor.size());						

	//cout<<"LEGO "<<LegoColor.size()<<endl;
	for (int i(0); i < m.LegoColor.size(); i++)
		m.LegoHue[i] = RGBtoHue(m.LegoColor[i].r, m.LegoColor[i].g, m.LegoColor[i].b);
}

//LEGO‚RGB‚Lab
void  LegoRGB_to_Lab(Model& m)
{
	string line;
	istringstream ssline;
	CColor temp;
	string temps;
	vector<string> iro;
	vector<CColor> tempLegoColor;
	int BackColorNum(0);
	int i(0);
	//LEGO
	string filename("lego_color_rgb.txt");
	//string filename("lego_color_rgb_tree.txt");
	//string filename("lego_color_rgb_palette.txt");
	ifstream fin(directory[0] + filename);
	if (!fin){
		cout << filename << " lego_color_rgb.txt was not found!!!  " << endl;
		exit(-1);
	}

	//###########################
	//###########################
	while (!fin.eof()){
		getline(fin, line);									
		if (line.size() == 0 || line[0] == '\n') continue;	
		//Block_colorNum++;	
		ssline.str(line);									
		ssline >> temp.r >> temp.g >> temp.b >> temps;		
		temp.r = temp.r / 255.0;							
		temp.g = temp.g / 255.0;
		temp.b = temp.b / 255.0;
		iro.push_back(temps);
		tempLegoColor.push_back(temp);						
		ssline.clear();			//ssline
	}

	//###########################
	//
	//###########################
	for (i = 0; i < iro.size(); i++)
		cout << i << ":" << iro[i] << endl;


	for (;;){
		cout << "         " << endl;
		cout << "0-" << iro.size() - 1 << ":choose one of that color, Other: not " << endl;
		//cin >> BackColorNum;
		BackColorNum = 2;

		if (-1 < BackColorNum && BackColorNum < iro.size())
		{
			cout << iro[BackColorNum] << " was chosen." << endl;
			m.BackColor = tempLegoColor[BackColorNum];
			cout << "RGB to Hue: " << RGBtoHue(m.BackColor.r, m.BackColor.g, m.BackColor.b) << endl;

			for (i = 0; i < iro.size(); i++){
				if (i == BackColorNum)
					continue;
				m.LegoColor.push_back(tempLegoColor[i]);
			}
			break;
		}
		else
			break;
	}
	for (i = 0; i < iro.size(); i++) {
		cout << "iro[" << i << "] m.LegoColor[" << i << "] r." << m.LegoColor[i].r<<" g." << m.LegoColor[i].g<<" b." << m.LegoColor[i].b << endl;
	}

	//#################################
	//                                     
	//#################################

	string filename1("BrickTable.txt");
	ifstream fin1(directory[0] + filename1);
	if (!fin1){
		cout << filename1 << " could not find!!" << endl;
		exit(-1);
	}

	unsigned designID;
	getline(fin1, line);								//1s–ÚiDesign IDj
	ssline.str(line);
	for (i = 0; i < 7; i++){
		ssline >> designID;
		table.DesignID.push_back(designID);
	}
	ssline.clear();			//ssline‚Ì‘S—v‘f‚ðíœ

	table.itemNos.resize(7);
	unsigned colorID;
	unsigned itemnos;
	int k(0);
	while (!fin1.eof()){
		getline(fin1, line);									

		if (line.size() == 0 || line[0] == '\n') continue;		
		if (k != BackColorNum){
			ssline.str(line);									
			ssline >> colorID;				
			table.ColorID.push_back(colorID);

			//cout << "colorID " << colorID << "-k" << k << " -table.ColorID " << table.ColorID[k] << endl;

			for (i = 0; i < 7; i++){
				ssline >> itemnos;
				table.itemNos[i].push_back(itemnos);
			//	cout << "itemnos " << itemnos << " table.itemNos[" << i << "]\n";
			}
		}
		k++;
		ssline.clear();			//ssline‚Ì‘S—v‘f‚ðíœ
	}

	//###########################
	//###########################
	//m.LegoColor = tempLegoColor;
	m.LegoColor_Lab.resize(m.LegoColor.size());
	vector<CColor>::iterator rgbit = m.LegoColor.begin();
	vector<CColor>::iterator labit = m.LegoColor_Lab.begin();
	while (rgbit != m.LegoColor.end())
	{
		(*labit) = RGB_to_Lab(*rgbit);
		//(*labit) = RGB_to_Lab2(*rgbit);
		cout << labit->r << " " << labit->g << " " << labit->b << endl;

		++rgbit;
		++labit;
	}
	cout << "\nLegoColor size:" << m.LegoColor.size() << "\nLEGO RGB to CIE L*a*b* " << endl;
	ssline.str("");			//ssline

}

double DeltaRGB(CColor& aa, CColor& bb)
{
	double color_difference = sqrt((aa.r - bb.r)*(aa.r - bb.r) + (aa.g - bb.g)*(aa.g - bb.g) + (aa.b - bb.b)*(aa.b - bb.b));
	return color_difference;
}

//5.Building LEGO, output the data file
void RealColor_to_LegoColor_lab(Model& m, Lego*** block)
{
	cout << "RealColor_to_LegoColor_lab - Building LEGO, output the data file: Model.txt\n";
	double min;			
	int min_no(0);		
	CColor temp;
	double tempDeltaE;

	int x, y, z;
	for (z = 1; z < Integ.num[2] - 1; z++){
		for (x = 1; x < Integ.num[0] - 1; x++){
			for (y = 1; y < Integ.num[1] - 1; y++){
				//
				if (Integ.Voxels[x][y][z].surf){
					//RGB, L*a*b*
					temp = RGB_to_Lab(Integ.Voxel_colors[x][y][z]);
					min = DBL_MAX;
					min_no = 0;
					for (int i(0); i < m.LegoColor.size(); i++){
						tempDeltaE = DeltaE(m.LegoColor_Lab[i], temp);
						if (tempDeltaE < min){
							min = tempDeltaE;
							min_no = i;
						}
					}
					//
					block[x][y][z].ColorID = min_no + 1;
				}
			}
		}
	}
	ofstream fout("ColorModel/Frog_7_20.txt");
	fout << Integ.num[0] + 6 << "  " << Integ.num[1] + 6 << "  " << Integ.num[2] + 6 << endl;


	for (z = 1; z < Integ.num[2] - 1; z++){
		for (x = 1; x < Integ.num[0] - 1; x++){
			for (y = 1; y < Integ.num[1] - 1; y++){
				if (block[x][y][z].fill){
					if (block[x][y][z].surf){
						fout << x + 3 << "  " << y + 3 << "  " << z + 3 << "  " << block[x][y][z].ColorID << endl;
						//cout << "ID color- "<<block[x][y][z].ColorID << endl;
						// #0 : 1,2,3,..,8 outside colour
					}
					else if (!block[x][y][z].surf){
						fout << x + 3 << "  " << y + 3 << "  " << z + 3 << "  " << 0 << endl;
						// 0 : inside color
					}
				}
			}
		}
	}
}

//ボクセルのリアルカラーからレゴブロックのカラーへ変換
void RealColor_to_LegoColor_lab(Model& m)
{
	double min;			//最小値
	int min_no(0);		//最小値が何番目なのか
	CColor temp;
	double tempDeltaE;

	m.ColorID.reserve(m.SurfVoxels.size());
	for (vector<CColor>::iterator it = m.SurfColors.begin(); it != m.SurfColors.end(); ++it)
	{
		//注目表面ボクセルのRGBからL*a*b*を計算
		temp = RGB_to_Lab(*it);  // L*a*b
		//temp = RGB_to_Lab2(*it);
		min = DBL_MAX;					//最小値をdouble型の最大とおく
		min_no = 0;

		//算出したL*a*b*の値とLEGOブロックのL*a*b*の値を比較して、一番小さいレゴブロックのカラーをそのボクセルのカラーとする
		for (int i(0); i < m.LegoColor.size(); i++) {
			tempDeltaE = DeltaE(m.LegoColor_Lab[i], temp);
			if (tempDeltaE < min) {
				min = tempDeltaE;			//最小値の更新
				min_no = i;						//最小値が何番目か
			}
		}

		//2016.05.25t takakura
		//ボクセルの色にもっとも近いレゴブロックの色のIDをつける
		///(*it).ColorID = min_no + 1;
		m.ColorID.push_back(min_no + 1);

		(*it) = m.LegoColor[min_no];	//ボクセルの色をレゴブロックの色で置き換える
	}
}


//RGBによる色近似
void RealColor_to_LegoColor_rgb(Model& m)
{
	double min;			//最小値
	int min_no(0);		//最小値が何番目なのか
	double tempDeltaRGB;

	for (vector<CColor>::iterator it = m.SurfColors.begin(); it != m.SurfColors.end(); ++it)
	{
		min = DBL_MAX;					//最小値をdouble型の最大とおく
		min_no = 0;
		//算出したL*a*b*の値とLEGOブロックのL*a*b*の値を比較して、一番小さいレゴブロックのカラーをそのボクセルのカラーとする
		for (int i(0); i < m.LegoColor.size(); i++) {
			tempDeltaRGB = DeltaRGB(m.LegoColor[i], (*it));
			if (tempDeltaRGB < min) {
				min = tempDeltaRGB;			//最小値の更新
				min_no = i;						//最小値が何番目か
			}
		}
		(*it) = m.LegoColor[min_no];	//ボクセルの色をレゴブロックの色で置き換える
	}
}



//
//double Max(double r, double g, double b)
//{
//	double max(r);
//	if (g > max)
//		max = g;
//	if (b > max)
//		max = b;
//	return max;
//}
//
//double Min(double r, double g, double b)
//{
//	double min(r);
//	if (g < min)
//		min = g;
//	if (b < min)
//		min = b;
//	return min;
//}