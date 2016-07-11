#include "../stdafx.h"
#include "../Voxel.h"
//LEGOブロックを組み立てるためのクラス

//グローバル変数
extern Model Integ;
extern string directory[2];
extern BrickTable table;


//関数プロトタイプ宣言
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

//色相による色近似
void RealColor_to_LegoColor_hue(Model& m)
{
	//使用するLEGOブロックの色のRGBから色相（Hue）を計算
	LegoRGB_to_Hue(m);

	int InitVoxSize[3];
	for (int i(0); i < 3; i++)
		InitVoxSize[i] = Integ.num[i];

	double hue;			//色相(0.0～360.0)
	double angle;		//注目ボクセルのHueとLEGOのhueとの差を格納する
	double min;			//最小値
	int min_no(0);		//最小値が何番目なのか

	for (vector<CColor>::iterator it = m.SurfColors.begin(); it != m.SurfColors.end(); ++it)
	{
		//注目表面ボクセルのRGBから色相を計算
		hue = RGBtoHue(it->r, it->g, it->b);		//0～360 各ボクセルのRGBから色相を計算
		min = 361.0;
		for (int i(0); i < m.LegoColor.size(); i++)
		{
			angle = fabs(m.LegoHue[i] - hue);		//注目ボクセルの色をLEGOの色の差の絶対値を格納する
			//色相は０～３６０度まで
			if (angle > 180.0)		//差の絶対値が180を超えたら例外処理が必要
				angle = fabs(360.0 - angle);
			if (angle < min)
			{
				min = angle;
				min_no = i;
			}
		}
		(*it) = m.LegoColor[min_no];		//実際の色をLEGOの色の中で最も近い色に置き換える
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
		temp = RGB_to_Lab(*it);
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

//ボクセルのリアルカラーからレゴブロックのカラーへ変換(明度Ｌを考慮しない)　→　使えない（2013/10/13）
void RealColor_to_LegoColor_ab(Model& m)
{

	double min;			//最小値
	int min_no(0);		//最小値が何番目なのか
	CColor temp;
	double tempDeltaE;

	for (vector<CColor>::iterator it = m.SurfColors.begin(); it != m.SurfColors.end(); ++it)
	{
		//注目表面ボクセルのRGBからL*a*b*を計算
		temp = RGB_to_Lab(*it);
		//temp = RGB_to_Lab2(*it);
		min = DBL_MAX;					//最小値をdouble型の最大とおく
		min_no = 0;

		//算出したL*a*b*の値とLEGOブロックのL*a*b*の値を比較して、一番小さいレゴブロックのカラーをそのボクセルのカラーとする
		for (int i(0); i < m.LegoColor.size(); i++) {
			tempDeltaE = DeltaE_noL(m.LegoColor_Lab[i], temp);
			if (tempDeltaE < min) {
				min = tempDeltaE;			//最小値の更新
				min_no = i;						//最小値が何番目か
			}
		}
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



//・・・レゴカラーにIDをつける
void RealColor_to_LegoColor_lab(Model& m, Lego*** block)
{
	double min;			//最小値
	int min_no(0);		//最小値が何番目なのか
	CColor temp;
	double tempDeltaE;

	int x, y, z;
	for (z = 1; z < Integ.num[2] - 1; z++) {
		for (x = 1; x < Integ.num[0] - 1; x++) {
			for (y = 1; y < Integ.num[1] - 1; y++) {
				//表面ボクセルだったら
				if (Integ.Voxels[x][y][z].surf) {
					//注目表面ボクセルのRGBからL*a*b*を計算
					temp = RGB_to_Lab(Integ.Voxel_colors[x][y][z]);
					min = DBL_MAX;					//最小値をdouble型の最大とおく
					min_no = 0;
					for (int i(0); i < m.LegoColor.size(); i++) {
						tempDeltaE = DeltaE(m.LegoColor_Lab[i], temp);
						if (tempDeltaE < min) {
							min = tempDeltaE;			//最小値の更新
							min_no = i;						//最小値が何番目か
						}
					}
					//ボクセルの色にもっとも近いレゴブロックの色のIDをつける
					block[x][y][z].ColorID = min_no + 1;
				}
			}
		}
	}
	ofstream fout("Panda6.txt");
	fout << Integ.num[0] + 6 << "  " << Integ.num[1] + 6 << "  " << Integ.num[2] + 6 << endl;
	for (z = 1; z < Integ.num[2] - 1; z++) {
		for (x = 1; x < Integ.num[0] - 1; x++) {
			for (y = 1; y < Integ.num[1] - 1; y++) {
				if (block[x][y][z].fill) {
					if (block[x][y][z].surf) {
						fout << x + 3 << "  " << y + 3 << "  " << z + 3 << "  " << block[x][y][z].ColorID << endl;
					}
					else if (!block[x][y][z].surf) {
						fout << x + 3 << "  " << y + 3 << "  " << z + 3 << "  " << 0 << endl;
					}
				}
			}
		}
	}
}


//・・・レゴカラーにIDをつける
void RealColor_to_LegoColor_lab_mono(Lego*** block)
{
	double min;			//最小値
	int min_no(0);		//最小値が何番目なのか
	CColor temp;
	double tempDeltaE;

	int x, y, z;
	for (z = 1; z < Integ.num[2] - 1; z++) {
		for (x = 1; x < Integ.num[0] - 1; x++) {
			for (y = 1; y < Integ.num[1] - 1; y++) {
				//表面ボクセルだったら
				if (block[x][y][z].flag == 1) {
					//ボクセルの色にもっとも近いレゴブロックの色のIDをつける
					block[x][y][z].ColorID = 1;
				}
			}
		}
	}

}

//ブロック単位：ボクセルに対応する最も近いブロックのＩＤをつける
void RealColor_to_LegoColor_lab_12_22(Model& m, Lego*** block)
{
	double min;			//最小値
	int min_no(0);		//最小値が何番目なのか
	CColor temp;
	double tempDeltaE;
	int count(0);
	int x, y, z;
	//######################################
	//                 ブロックにcolorIDつける                         
	//######################################
	for (z = 1; z < Integ.num[2] - 1; z++) {
		for (x = 1; x < Integ.num[0] - 1; x++) {
			for (y = 1; y < Integ.num[1] - 1; y++) {
				//表面ボクセルだったら
				if (Integ.Voxels[x][y][z].surf) {
					//注目表面ボクセルのRGBからL*a*b*を計算
					temp = RGB_to_Lab(Integ.Voxel_colors[x][y][z]);
					min = DBL_MAX;					//最小値をdouble型の最大とおく
					min_no = 0;
					for (int i(0); i < m.LegoColor.size(); i++) {
						tempDeltaE = DeltaE(m.LegoColor_Lab[i], temp);
						if (tempDeltaE < min) {
							min = tempDeltaE;			//最小値の更新
							min_no = i;						//最小値が何番目か
						}
					}
					//ボクセルの色にもっとも近いレゴブロックの色のIDをつける
					block[x][y][z].ColorID = min_no + 1;
				}
			}
		}
	}

	int XorY(0);		//Y方向１、Ｘ方向２
	//######################################
	//                 （１×２）ブロックにcolorIDつける                         
	//######################################
	for (z = 1; z < Integ.num[2] - 1; z++) {
		for (x = 1; x < Integ.num[0] - 1; x++) {
			for (y = 1; y < Integ.num[1] - 1; y++) {
				//１×２ならば
				if (block[x][y][z].flag == 2) {
					count = 0;
					temp.Clear();
					XorY = 0;
					//ｙ方向見る
					if (block[x][y + 1][z].flag == 2 && block[x][y][z].ID == block[x][y + 1][z].ID) {
						if (block[x][y][z].surf) {
							count++;
							temp.r = temp.r + Integ.Voxel_colors[x][y][z].r;
							temp.g = temp.g + Integ.Voxel_colors[x][y][z].g;
							temp.b = temp.b + Integ.Voxel_colors[x][y][z].b;
						}
						if (block[x][y + 1][z].surf) {
							count++;
							temp.r = temp.r + Integ.Voxel_colors[x][y + 1][z].r;
							temp.g = temp.g + Integ.Voxel_colors[x][y + 1][z].g;
							temp.b = temp.b + Integ.Voxel_colors[x][y + 1][z].b;
						}
						XorY = 1;
					}
					//ｘ方向見る
					else if (block[x + 1][y][z].flag == 2 && block[x][y][z].ID == block[x + 1][y][z].ID) {
						if (block[x][y][z].surf) {
							count++;
							temp.r = temp.r + Integ.Voxel_colors[x][y][z].r;
							temp.g = temp.g + Integ.Voxel_colors[x][y][z].g;
							temp.b = temp.b + Integ.Voxel_colors[x][y][z].b;

						}
						if (block[x + 1][y][z].surf) {
							count++;
							temp.r = temp.r + Integ.Voxel_colors[x + 1][y][z].r;
							temp.g = temp.g + Integ.Voxel_colors[x + 1][y][z].g;
							temp.b = temp.b + Integ.Voxel_colors[x + 1][y][z].b;
						}
						XorY = 2;
					}
					//一つ以上の表面ボクセルを持つならば
					if (count > 0) {
						//平均する
						temp.r = temp.r / count;
						temp.g = temp.g / count;
						temp.b = temp.b / count;
						temp = RGB_to_Lab(temp);
						min = DBL_MAX;					//最小値をdouble型の最大とおく
						min_no = 0;
						for (int i(0); i < m.LegoColor.size(); i++) {
							tempDeltaE = DeltaE(m.LegoColor_Lab[i], temp);
							if (tempDeltaE < min) {
								min = tempDeltaE;			//最小値の更新
								min_no = i;						//最小値が何番目か
							}
						}
						//ボクセルの色にもっとも近いレゴブロックの色のIDをつける
						block[x][y][z].ColorID = min_no + 1;
						if (XorY == 1)
							block[x][y + 1][z].ColorID = min_no + 1;
						else if (XorY == 2)
							block[x + 1][y][z].ColorID = min_no + 1;
					}
				}
			}
		}
	}
	//######################################
	//                 （２×２）ブロックにcolorIDつける                         
	//######################################
	//奇数層（２×２）
	for (z = 1; z < Integ.num[2] - 1; z = z + 2) {
		for (x = 1; x < Integ.num[0] - 1; x = x + 2) {
			for (y = 1; y < Integ.num[1] - 1; y = y + 2) {
				//２×２ならば
				if (block[x][y][z].flag == 4) {
					count = 0;
					temp.Clear();
					if (block[x][y][z].surf) {
						count++;
						temp.r = temp.r + Integ.Voxel_colors[x][y][z].r;
						temp.g = temp.g + Integ.Voxel_colors[x][y][z].g;
						temp.b = temp.b + Integ.Voxel_colors[x][y][z].b;
					}
					if (block[x][y + 1][z].surf) {
						count++;
						temp.r = temp.r + Integ.Voxel_colors[x][y + 1][z].r;
						temp.g = temp.g + Integ.Voxel_colors[x][y + 1][z].g;
						temp.b = temp.b + Integ.Voxel_colors[x][y + 1][z].b;
					}
					if (block[x + 1][y][z].surf) {
						count++;
						temp.r = temp.r + Integ.Voxel_colors[x + 1][y][z].r;
						temp.g = temp.g + Integ.Voxel_colors[x + 1][y][z].g;
						temp.b = temp.b + Integ.Voxel_colors[x + 1][y][z].b;
					}
					if (block[x + 1][y + 1][z].surf) {
						count++;
						temp.r = temp.r + Integ.Voxel_colors[x + 1][y + 1][z].r;
						temp.g = temp.g + Integ.Voxel_colors[x + 1][y + 1][z].g;
						temp.b = temp.b + Integ.Voxel_colors[x + 1][y + 1][z].b;
					}
					//一つ以上の表面ボクセルを持つならば
					if (count > 0) {
						//平均する
						temp.r = temp.r / count;
						temp.g = temp.g / count;
						temp.b = temp.b / count;
						temp = RGB_to_Lab(temp);
						min = DBL_MAX;					//最小値をdouble型の最大とおく
						min_no = 0;
						for (int i(0); i < m.LegoColor.size(); i++) {
							tempDeltaE = DeltaE(m.LegoColor_Lab[i], temp);
							if (tempDeltaE < min) {
								min = tempDeltaE;			//最小値の更新
								min_no = i;						//最小値が何番目か
							}
						}
						//ボクセルの色にもっとも近いレゴブロックの色のIDをつける
						block[x][y][z].ColorID = min_no + 1;
						block[x][y + 1][z].ColorID = min_no + 1;
						block[x + 1][y][z].ColorID = min_no + 1;
						block[x + 1][y + 1][z].ColorID = min_no + 1;
					}
				}
			}
		}
	}
	//偶数層（２×２）
	for (z = 2; z < Integ.num[2] - 1; z = z + 2) {
		for (x = 0; x < Integ.num[0] - 1; x = x + 2) {
			for (y = 0; y < Integ.num[1] - 1; y = y + 2) {
				//２×２ならば
				if (block[x][y][z].flag == 4) {
					count = 0;
					temp.Clear();
					if (block[x][y][z].surf) {
						count++;
						temp.r = temp.r + Integ.Voxel_colors[x][y][z].r;
						temp.g = temp.g + Integ.Voxel_colors[x][y][z].g;
						temp.b = temp.b + Integ.Voxel_colors[x][y][z].b;
					}
					if (block[x][y + 1][z].surf) {
						count++;
						temp.r = temp.r + Integ.Voxel_colors[x][y + 1][z].r;
						temp.g = temp.g + Integ.Voxel_colors[x][y + 1][z].g;
						temp.b = temp.b + Integ.Voxel_colors[x][y + 1][z].b;
					}
					if (block[x + 1][y][z].surf) {
						count++;
						temp.r = temp.r + Integ.Voxel_colors[x + 1][y][z].r;
						temp.g = temp.g + Integ.Voxel_colors[x + 1][y][z].g;
						temp.b = temp.b + Integ.Voxel_colors[x + 1][y][z].b;
					}
					if (block[x + 1][y + 1][z].surf) {
						count++;
						temp.r = temp.r + Integ.Voxel_colors[x + 1][y + 1][z].r;
						temp.g = temp.g + Integ.Voxel_colors[x + 1][y + 1][z].g;
						temp.b = temp.b + Integ.Voxel_colors[x + 1][y + 1][z].b;
					}
					//一つ以上の表面ボクセルを持つならば
					if (count > 0) {
						//平均する
						temp.r = temp.r / count;
						temp.g = temp.g / count;
						temp.b = temp.b / count;
						temp = RGB_to_Lab(temp);
						min = DBL_MAX;					//最小値をdouble型の最大とおく
						min_no = 0;
						for (int i(0); i < m.LegoColor.size(); i++) {
							tempDeltaE = DeltaE(m.LegoColor_Lab[i], temp);
							if (tempDeltaE < min) {
								min = tempDeltaE;			//最小値の更新
								min_no = i;						//最小値が何番目か
							}
						}
						//ボクセルの色にもっとも近いレゴブロックの色のIDをつける
						block[x][y][z].ColorID = min_no + 1;
						block[x][y + 1][z].ColorID = min_no + 1;
						block[x + 1][y][z].ColorID = min_no + 1;
						block[x + 1][y + 1][z].ColorID = min_no + 1;
					}
				}
			}
		}
	}
}

//RGBの値を入力して、色相（Hue）を返す
//復元したボクセルの色を既存のLEGOブロックの色に置き換えるために必要
double RGBtoHue(double r, double g, double b)		//r,g,b(0.0~1.0)
{
	double max = Max(r, g, b);
	double min = Min(r, g, b);
	double hue(0.0);
	if (max == 0.0 || max == min)
		return 0.0;

	//色相を計算する
	if (max == r)
		hue = 60.0 * (g - b) / (max - min);
	else if (max == g)
		hue = 60.0 * (b - r) / (max - min) + 120.0;
	else if (max == b)
		hue = 60.0 * (r - g) / (max - min) + 240.0;

	//例外処理 hue < 0　ならば360.0を足す
	if (hue < 0.0)
		hue += 360.0;
	//例外処理 hue > 360　ならば360で割ったあまり
	else if (hue > 360.0)
		hue = fmod(hue, 360.0);

	return hue;
}

//LEGOのRGBを色相に変換
void  LegoRGB_to_Hue(Model& m)
{
	//LEGOブロックの色情報ファイルを読み込む
	//string filename("LEGOColorRGB.txt");
	string filename("lego_color_rgb.txt");
	ifstream fin(directory[0] + filename);					//
	if (!fin) {
		cout << filename << " not found！" << endl;
		exit(-1);
	}
	string line;
	istringstream ssline;
	CColor temp;

	//ファイルを1行ずつ読み、かく色の情報を配列に格納
	while (!fin.eof())
	{
		getline(fin, line);															//ファイルの一行を読み込む
		if (line.size() == 0 || line[0] == '\n') continue;			//最後の行に改行などがあった場合の対策
		ssline.str(line);																//読み込んだ行を文字列入力ストリームに格納
		ssline >> temp.r >> temp.g >> temp.b;					//文字列ストリームのｒ、ｇ、ｂをtempに格納
		temp.r = temp.r / 255.0;												//０～２５５ → 0.0～1.0　への変換
		temp.g = temp.g / 255.0;
		temp.b = temp.b / 255.0;
		m.LegoColor.push_back(temp);									//色情報を配列に入れる
		ssline.clear();																//sslineの全要素を削除
	}
	ssline.str("");			//sslineの中身を初期化

	m.LegoHue.reserve(m.LegoColor.size());						//要素の数が既知なのであらかじめメモリを確保するとよい

	//cout<<"LEGOブロックの色相(色数)"<<LegoColor.size()<<endl;
	for (int i(0); i < m.LegoColor.size(); i++)
		m.LegoHue[i] = RGBtoHue(m.LegoColor[i].r, m.LegoColor[i].g, m.LegoColor[i].b);
}

//LEGOのRGBをLabに変換
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
	//LEGOブロックの色情報ファイルを読み込む
	string filename("lego_color_rgb.txt");
	//string filename("lego_color_rgb_tree.txt");
	//string filename("lego_color_rgb_palette.txt");
	ifstream fin(directory[0] + filename);
	if (!fin) {
		cout << filename << " not found！" << endl;
		exit(-1);
	}

	//###########################
	//ファイルを1行ずつ読み、かく色の情報を配列に格納
	//###########################
	while (!fin.eof()) {
		getline(fin, line);														//ファイルの一行を読み込む
		if (line.size() == 0 || line[0] == '\n') continue;		//最後の行に改行などがあった場合の対策
		//Block_colorNum++;	//色の数を加算
		ssline.str(line);															//読み込んだ行を文字列入力ストリームに格納
		ssline >> temp.r >> temp.g >> temp.b >> temps;				//文字列ストリームのｒ、ｇ、ｂをtempに格納
		temp.r = temp.r / 255.0;											//０～２５５ → 0.0～1.0　への変換
		temp.g = temp.g / 255.0;
		temp.b = temp.b / 255.0;
		iro.push_back(temps);
		tempLegoColor.push_back(temp);								//色情報を配列に入れる
		ssline.clear();			//sslineの全要素を削除
	}

	//###########################
	//背景の色を選ばせる
	//###########################
	for (i = 0; i < iro.size(); i++)
		cout << i << ":" << iro[i] << endl;


	for (;;) {
		cout << "Choose kind of background color:"<< endl;
		cout << "0~" << iro.size() - 1 << " 　Other:not " << endl;
		cin >> BackColorNum;
		if (-1 < BackColorNum && BackColorNum < iro.size())
		{
			cout << iro[BackColorNum] << " was choosen!"<< endl;
			m.BackColor = tempLegoColor[BackColorNum];
			cout << "Background color: Hue " << RGBtoHue(m.BackColor.r, m.BackColor.g, m.BackColor.b) << endl;
			for (i = 0; i < iro.size(); i++) {
				if (i == BackColorNum)
					continue;
				m.LegoColor.push_back(tempLegoColor[i]);
			}
			break;
		}
		else
			break;
	}
	//#################################
	//                    ブリックの表を読み込む                           
	//#################################
	//ブリック表のメモリ確保
	string filename1("BrickTable.txt");
	ifstream fin1(directory[0] + filename1);
	if (!fin1) {
		cout << filename1 << " not found！" << endl;
		exit(-1);
	}
	unsigned designID;
	getline(fin1, line);								//1行目（Design ID）
	ssline.str(line);
	for (i = 0; i < 7; i++) {
		ssline >> designID;
		table.DesignID.push_back(designID);
	}
	ssline.clear();			//sslineの全要素を削除

	table.itemNos.resize(7);
	unsigned colorID;
	unsigned itemnos;
	int k(0);
	while (!fin1.eof()) {
		getline(fin1, line);														//ファイルの一行を読み込む

		if (line.size() == 0 || line[0] == '\n') continue;		//最後の行に改行などがあった場合の対策
		if (k != BackColorNum) {
			ssline.str(line);															//読み込んだ行を文字列入力ストリームに格納
			ssline >> colorID;				//文字列ストリームのｒ、ｇ、ｂをtempに格納
			table.ColorID.push_back(colorID);
			cout << "colorID " << colorID << "-k" << k << " -table.ColorID " << table.ColorID[k] << endl;

			for (i = 0; i < 7; i++) {
				ssline >> itemnos;
				table.itemNos[i].push_back(itemnos);
				cout << "itemnos " << itemnos << " table.itemNos[" << i << "]\n";

			}
		}
		k++;
		ssline.clear();			//sslineの全要素を削除
	}
	getchar();
	getchar();
	//###########################
	//使用するレゴブロックの色を選ばれる
	//###########################
	//m.LegoColor = tempLegoColor;
	m.LegoColor_Lab.resize(m.LegoColor.size());		//要素の数が既知なのであらかじめメモリを確保するとよい
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
	cout << "Use the " << m.LegoColor.size() << "  the color of the LEGO block : the completion of a conversion from RGB to CIEL*a*b*!" << endl;
	ssline.str("");			//sslineの中身を初期化
	
}

//３つの内の最大値を返す
double Max(double r, double g, double b)
{
	double max(r);
	if (g > max)
		max = g;
	if (b > max)
		max = b;
	return max;
}
//３つの内の最小値を返す
double Min(double r, double g, double b)
{
	double min(r);
	if (g < min)
		min = g;
	if (b < min)
		min = b;
	return min;
}

//2色のRGBの距離を返す
double DeltaRGB(CColor& aa, CColor& bb)
{
	double color_difference = sqrt((aa.r - bb.r)*(aa.r - bb.r) + (aa.g - bb.g)*(aa.g - bb.g) + (aa.b - bb.b)*(aa.b - bb.b));
	return color_difference;
}