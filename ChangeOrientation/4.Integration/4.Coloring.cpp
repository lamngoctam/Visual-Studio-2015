#include "../stdafx.h"


extern int ImageNum;
extern CMatrix *ART;
extern CMatrix *ARTRTinv;
extern CVector3d* CameraPosUp;
extern CVector3d* CameraPosDown;
extern string directory[2];			//ÉfÅ[É^ÇÃÉfÉBÉåÉNÉgÉä
extern string model;				//ÉÇÉfÉãÇÃñºëO
extern string pose[3];				//épê®1Ç∆2
extern double DeltaE_Thres;			//êFÇÃç∑ÇÃËáíl
extern double HueGap_Thres;


void CalculateDistance(Model& m);
void CalculateNormal(Model& m);
void SetSrufToVector(Model& m);
void CanSee(Model& integ, int x, int y, int z, CVector3d& CameraPos, string pose);
void ReadSilhouette(int, string, string, string, vector<cv::Mat>&);
void ReadColorImage(int, string, string, string, vector<cv::Mat>&);
CVector3d CalcDeptPoint(Model& integ, int x, int y, int z);
cv::Point CalcImageCoord(CMatrix& ART, CVector3d vertW);

void CalculateDistance_AllVoxel(Model& m);

CColor RGB_to_Lab(CColor& rgb);
double GetDeltaE(CColor a, CColor b);
double RGBtoHue(double r, double g, double b);
double GetHueGap(CColor a, CColor b);
CColor GetVoxelColor_hue_mode(vector<Color_hue>& v);
CColor GetVoxelColor_hue_mode(vector<Color_hue>& v, Model& m);
CColor GetVoxelColor_lumi_mode(vector<Color_hue>& v);
void Bounding_Box(cv::Point &max, cv::Point &min, cv::Point *point);
void Projection(bool **&Pro, int num, CVector3d vert, cv::Point min, cv::Point max, double length, double height, CMatrix ART);
double DeltaE(CColor& aa, CColor& bb);


void Coloring(Model& integ)
{

	//CalculateDistance(integ);
	CalculateDistance_AllVoxel(integ);

	cout << "CalculateNormal: " << endl;
	//
	CalculateNormal(integ);

	//
	vector<cv::Mat> UpSilhouette(ImageNum);
	ReadSilhouette(ImageNum, directory[1], model, pose[0], UpSilhouette);
	vector<cv::Mat> DownSilhouette(ImageNum);
	ReadSilhouette(ImageNum, directory[1], model, pose[1], DownSilhouette);
	vector<cv::Mat> UpImage(ImageNum);
	ReadColorImage(ImageNum, directory[0], model, pose[0], UpImage);
	vector<cv::Mat> DownImage(ImageNum);
	ReadColorImage(ImageNum, directory[0], model, pose[1], DownImage);

	cv::Point temp;
	int R, G, B;
	int step = UpImage[0].step;
	int width = UpSilhouette[0].cols;
	int height = UpSilhouette[0].rows;

	CColor tempColor(0.0, 0.0, 0.0);
	Color_hue tempColorH;
	vector<Color_hue> VoxColor;

	CVector3d Point_Image;
	short templum;
	//short thre(50);
	short thre(123);

	Color_hue tempBackColor;
	tempBackColor.r = integ.BackColor.r;
	tempBackColor.g = integ.BackColor.g;
	tempBackColor.b = integ.BackColor.b;
	tempBackColor.CalcHue();

	integ.SurfColors.reserve(integ.SurfNum);		//

	int ring1[][2] = { {0, 0},		{-1, -1},		{-1, 0},
					   {-1, 1},		{0, -1},		{0, 1},
					   {1, -1},		{1, 0},		    {1, 1}
	};

	//                                                                                   
	//                                     
	//                                                                                   
	integ.Voxel_colors = new CColor **[integ.num[0]];
	for (int i(0); i < integ.num[0]; i++) {
		integ.Voxel_colors[i] = new CColor *[integ.num[1]];
		for (int k(0); k < integ.num[1]; k++)
			integ.Voxel_colors[i][k] = new CColor[integ.num[2]];
	}

	cout << "\nCheck visable voxels which can be seen\n" << endl;

	for (int x = 1; x < integ.num[0] - 1; x++) {
		for (int y = 1; y < integ.num[1] - 1; y++) {
			for (int z = 1; z < integ.num[2] - 1; z++) {
				//
				if (integ.Voxels[x][y][z].surf) {
					//
					VoxColor.clear();
					for (int i = 0; i < ImageNum; i++)
					{
						CanSee(integ, x, y, z, CameraPosUp[i], "UP");					//true(UP)
						//UP
						if (integ.Flags[x][y][z].upCan)
						{
							integ.Voxels[x][y][z].line.push_back(CameraPosUp[i] - integ.Voxels[x][y][z].center);
							temp = integ.Voxels[x][y][z].CalcImageCoordofCenter(ART[i]);
							//Å
							//
							for (int n = 0; n < 9; n++) {
								templum = (short)(UpSilhouette[i].data[width * (temp.y + ring1[n][1]) + temp.x + ring1[n][0]]);
								if (templum < thre)	
									continue;
								//opencv
								tempColorH.Clear();
								B = UpImage[i].data[step * (temp.y + ring1[n][1]) + (temp.x + ring1[n][0]) * 3];
								G = UpImage[i].data[step * (temp.y + ring1[n][1]) + (temp.x + ring1[n][0]) * 3 + 1];
								R = UpImage[i].data[step * (temp.y + ring1[n][1]) + (temp.x + ring1[n][0]) * 3 + 2];
								tempColorH.b = B / 255.0;
								tempColorH.g = G / 255.0;
								tempColorH.r = R / 255.0;
								tempColorH.CalcHue();
								tempColorH.CalcLuminance();
								//if( fabs(tempBackColor.GetHue() - tempColorH.GetHue()) < HueGap_Thres )				//îwåiêFÇÃêFëäÇ…ãﬂÇ¢êFÇÕégópÇµÇ»Ç¢
								//	continue;
								//								//ÉVÉ}ÉEÉ}êÍóp
								//if(tempColorH.luminance>0.5){
								//	tempColorH.Set(1.0,1.0,1.0);
								//}
								//else{
								//	tempColorH.Set(0.0,0.0,0.0);
								//}
								VoxColor.push_back(tempColorH);
							}
						}
						CanSee(integ, x, y, z, CameraPosDown[i], "DOWN");		//false(DOWN)
						//DOWN
						if (integ.Flags[x][y][z].downCan)
						{
							integ.Voxels[x][y][z].line.push_back(CameraPosDown[i] - integ.Voxels[x][y][z].center);
							temp = integ.Voxels[x][y][z].CalcImageCoordofCenter(ARTRTinv[i]);
							//Å
							//
							for (int n = 0; n < 9; n++) {
								templum = (short)(DownSilhouette[i].data[width * (temp.y + ring1[n][1]) + temp.x + ring1[n][0]]);
								if (templum < thre)	//
									continue;
								//opencvÇ
								tempColorH.Clear();
								B = DownImage[i].data[step * (temp.y + ring1[n][1]) + (temp.x + ring1[n][0]) * 3];
								G = DownImage[i].data[step * (temp.y + ring1[n][1]) + (temp.x + ring1[n][0]) * 3 + 1];
								R = DownImage[i].data[step * (temp.y + ring1[n][1]) + (temp.x + ring1[n][0]) * 3 + 2];
								tempColorH.b = B / 255.0;
								tempColorH.g = G / 255.0;
								tempColorH.r = R / 255.0;
								tempColorH.CalcHue();
								tempColorH.CalcLuminance();
								//if( fabs(tempBackColor.GetHue() - tempColorH.GetHue()) < HueGap_Thres )				
								//	continue;
								//								
								//if(tempColorH.luminance>0.5){
								//	tempColorH.Set(1.0,1.0,1.0);
								//}
								//else{
								//	tempColorH.Set(0.0,0.0,0.0);
								//}
								VoxColor.push_back(tempColorH);
							}
						}
					}

					if (!VoxColor.empty()) {
						tempColor = GetVoxelColor_hue_mode(VoxColor);
						//tempColor = GetVoxelColor_lumi_mode(VoxColor);			
						//cout<<tempColor.r <<" "<<tempColor.g<<" "<<tempColor.b<<endl;
						integ.Voxel_colors[x][y][z] = tempColor;
						integ.SurfColors.push_back(tempColor);
					}

					else {
						integ.Voxel_colors[x][y][z] = tempColor;
						integ.SurfColors.push_back(tempColor);   //0.0.0.0.0.0
					}
				}
			}
		}
	}

	//
	UpSilhouette.clear();
	UpSilhouette.shrink_to_fit();
	DownSilhouette.clear();
	DownSilhouette.shrink_to_fit();
	UpImage.clear();
	UpImage.shrink_to_fit();
	DownImage.clear();
	DownImage.shrink_to_fit();
}


//Bounding Box
void Bounding_Box(cv::Point &max, cv::Point &min, cv::Point *point) {
	max = point[0];
	min = point[0];
	//8í
	for (int i(1); i < 8; i++) {
		if (max.x < point[i].x)max.x = point[i].x;
		if (max.y < point[i].y)max.y = point[i].y;
		if (min.x > point[i].x)min.x = point[i].x;
		if (min.y > point[i].y)min.y = point[i].y;

	}

}
//(numÇ™0.5ÇÃéûÇÕÇòÇôÅAnumÇ™2.4ÇÃéûÇÕÇöÇòÅAnumÇ™1.3ÇÃéûÇÕÇôÇö)
void Projection(bool **&Pro, int num, CVector3d vert, cv::Point min, cv::Point max, double length, double height, CMatrix ART) {
	cv::Point tempPro;
	CVector3d surfP;
	for (int e(0); e < 20; e++) {
		for (int f(0); f < 20; f++) {
			if (num == 2 || num == 4) {
				surfP.x = vert.x + length*(double)f / 20.0;
				surfP.y = vert.y;
				surfP.z = vert.z + height*(double)e / 20.0;
			}
			if (num == 1 || num == 3) {
				surfP.x = vert.x;
				surfP.y = vert.y + length*(double)f / 20.0;
				surfP.z = vert.z + height*(double)e / 20.0;
			}
			if (num == 0 || num == 5) {
				surfP.x = vert.x + length*(double)f / 20.0;
				surfP.y = vert.y + length*(double)f / 20.0;
				surfP.z = vert.z;
			}
			tempPro = CalcImageCoord(ART, surfP);
			if ((tempPro.x - min.x) > 0 && (tempPro.y - min.y) > 0)
				if ((max.x - tempPro.x) > 0 && (max.y - tempPro.y) > 0)
					Pro[tempPro.x - min.x][tempPro.y - min.y] = true;
		}
	}
}


cv::Point CalcImageCoord(CMatrix& ART, CVector3d vertW)
{
	cv::Point coord(0, 0);
	CVector temp(4);
	temp[3] = 1.0;

	temp[0] = vertW.x;
	temp[1] = vertW.y;
	temp[2] = vertW.z;

	temp = ART*temp;
	coord.x = (int)(temp[0] / temp[2]);
	coord.y = (int)(temp[1] / temp[2]);

	return coord;
}

CVector3d CalcDeptPoint(Model& integ, int x, int y, int z)
{
	CVector3d temp(0.0, 0.0, 0.0);
	vector<int> vert8(8, 0);		//8í∏ì_ÇÉJÉEÉìÉgÇ∑ÇÈîzóÒÅ@ÉTÉCÉYÅFÇWÅ@èâä˙ílÅFÇO
	int max(0);							//ÉJÉEÉìÉgÇÃç≈ëÂíl
	int max_num(0);					//ç≈ëÂílÇÃêî
	CVector3d vertW[8];

	if (integ.Voxels[x + 1][y][z].fill)		//É{ÉNÉZÉãÇ™Ç†ÇÈÇ»ÇÁÇŒÅAñ Çç\ê¨Ç∑ÇÈÇSí∏ì_ÇÃÉJÉEÉìÉgÇâ¡éZ
		vert8[1]++;		vert8[2]++;		vert8[5]++;		vert8[6]++;
	if (integ.Voxels[x][y + 1][z].fill)
		vert8[2]++;		vert8[3]++;		vert8[6]++;		vert8[7]++;
	if (integ.Voxels[x][y][z + 1].fill)
		vert8[4]++;		vert8[5]++;		vert8[6]++;		vert8[7]++;
	if (integ.Voxels[x - 1][y][z].fill)
		vert8[0]++;		vert8[3]++;		vert8[4]++;		vert8[7]++;
	if (integ.Voxels[x][y - 1][z].fill)
		vert8[0]++;		vert8[1]++;		vert8[4]++;		vert8[5]++;
	if (integ.Voxels[x][y][z - 1].fill)
		vert8[0]++;		vert8[1]++;		vert8[2]++;		vert8[3]++;

	max = *max_element(vert8.begin(), vert8.end());		//îzóÒÇÃç≈ëÂílÇï‘Ç∑
	integ.Voxels[x][y][z].SetVertexWorld(vertW);
	for (int k(0); k < 8; k++) {
		if (vert8[k] == max) {
			temp += vertW[k];
			max_num++;
		}
	}
	temp = temp / max_num;		//ì‡ë§ÇÃì_Ç™ÇPå¬à»è„Ç†ÇÈÇ∆Ç´Ç…ÇªÇÃïΩãœÇÃí∏ì_ÇópÇ¢ÇÈ
	return temp;
}

double GetDeltaE(CColor a, CColor b)
{
	double deltaE;
	CColor tempa;
	CColor tempb;
	//CIELABÇ…ïœä∑
	tempa = RGB_to_Lab(a);
	tempb = RGB_to_Lab(b);
	//ÉÜÅ[ÉNÉäÉbÉhãóó£ÇåvéZ
	deltaE = sqrt((tempa.r - tempb.r)*(tempa.r - tempb.r) + (tempa.g - tempb.g)*(tempa.g - tempb.g) + (tempa.b - tempb.b)*(tempa.b - tempb.b));

	return deltaE;
}


double GetHueGap(CColor a, CColor b)
{
	double HueGap;
	double tempa;
	double tempb;
	//RGBÇ©ÇÁhueÇ…ïœä∑
	tempa = RGBtoHue(a.r, a.g, a.b);
	tempb = RGBtoHue(b.r, b.g, b.b);
	//êFëäÇÃç∑
	HueGap = fabs(tempa - tempb);
	return HueGap;
}


