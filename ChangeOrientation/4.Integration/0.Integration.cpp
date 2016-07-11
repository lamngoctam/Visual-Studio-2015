#include "../stdafx.h"

extern OctVoxel Angle_;

extern int ImageNum;
extern CMatrix ICPMatrix;
extern short OctLevels;
extern double Width;

extern Model UP;				//new UP
extern Model DOWN;				//new DOWN
extern Model Integ;
extern CColor*** color;

extern string directory[2];
extern string model;
extern string pose[3];

extern OctVoxel DownBoundingBox;
extern OctVoxel UpBoundingBox;

extern CMatrix *ART;
extern CMatrix *ARTRTinv;
extern CVector3d* CameraPosUp;
extern CVector3d* CameraPosDown;
extern CVector3d centroid;

extern double MinVoxelL;			//new UP & DOWN
extern double MinVoxelH;			//new UP & DOWN

CVector3d Min(0.0, 0.0, 0.0);	//
CVector3d Max(0.0, 0.0, 0.0);	//FindMinAndMax(NewUP, NewDOWN, Min, Max, MinVoxelL, MinVoxelH);

void ReadSilhouette(int, string, string, string, vector<cv::Mat>&);
void CalcWorldToImage(int, string*, string, string*, CMatrix*, CVector3d*);
void CheckBoundingBox(int ImageNum, vector<cv::Mat>&, Cpixel**);
void DividVoxelTo8(short, OctVoxel&, CMatrix*, vector<cv::Mat>&, vector<OctVoxel>&);
void SetVertexImage(OctVoxel& box, Cpixel** vertexI, CMatrix* ART);

void FindMinAndMax(Model& up, Model& down, CVector3d& min, CVector3d& max, double MinVoxelL, double MinVoxelH);
void OctreeToVoxel(Model& m, short level, CVector3d min, CVector3d max, double MinVoxelL, double MinVoxelH);

void FindOutsideVoxel(Model& m);
void CalculateDistance(Model& m);
void CalculateNormal(Model& m);

void UPandDOWN(Model& up, Model& down, Model& integ, CVector3d min, double MinVoxelL, double MinVoxelH);
void UPandDOWN_zhang(Model& up, Model& down, Model& integ, CVector3d min, double MinVoxelL, double MinVoxelH);
void CalcDownCamaraPos();
void Unio(Model& integ);
void Intersection(Model& integ);
void ProposedMethod(Model& integ);
void Coloring(Model& integ);

void OutputOff(Model& m);
void ElimIsoVoxels_LUT(Model& m);
void ElimIsoVoxels(Model& m);

void SetVoxelParameter(Model& m, CVector3d min, double MinVoxelL, double MinVoxelH);
void FreeMemory_Voxel(Model& m);
void SetSrufToVector(Model& m);

void  LegoRGB_to_Lab(Model& m);
void RealColor_to_LegoColor_lab(Model& m);
//void RealColor_to_LegoColor_ab(Model& m);
//void RealColor_to_LegoColor_hue(Model& m);
void RealColor_to_LegoColor_rgb(Model& m);

//2014
void Putout_txt(Model& integ, string Filename, double length);
void Out_camera(string Filename, CVector3d* Camera);
void Camera_para(string Filename, CMatrix* ART);
void In_camara(string Filename, CVector3d* Camera);
void In_camera_para(string Filename, CMatrix* ART);
void Slice(Model& integ);

// ---------------- new -----------
void Check_Integ_Rotation(Model& up, Model& down, OctVoxel& upboundingbox, OctVoxel& downboundingbox, double Rotated_Angle);
void Check_UpDown_Rotation(Model& up, Model& down, OctVoxel& upboundingbox, OctVoxel& downboundingbox, double Rotated_Angle);
void DividVoxelTo8_Rotated(double, short, OctVoxel&, CMatrix*, vector<cv::Mat>&, vector<OctVoxel>&);
void Divided_lowerLV_Octree(Model& m, short LV, double Rotated_Angle, vector<OctVoxel>& Octree);
void Find_Rodrigues_Formular(OctVoxel& box, double Rotated_Angle, Cpixel** vertex2D, CMatrix* ART);
void SetVertexImage_Rotated(double Rotated_Angle, OctVoxel& box, Cpixel** vertexI, CMatrix* ART);
void Octree_to_voxel(Model& m, short level, CVector3d& min, CVector3d& max, double MinVoxelL, double MinVoxelH);
void RunOpenGL(int argc, char *argv[]);		//Shape From Silhouette
void RunOpenGLDown(int argc, char *argv[]);		//Shape From Silhouette

//2016/06/23
void Check_Plane2(Model& m, OctVoxel& boundingbox, double Rotated_Angle, CVector3d& min, CVector3d& max, CVector3d& newCentbox);
void Rotated_Back(Model& m, double Rotated_Angle, CVector3d centroid_before, CVector3d centroid_after);

void Optimated_Rotated(Model& m, OctVoxel& bbox, double Rotated_Angle, CVector3d& min, CVector3d& max);

void RunOpenGL3(int argc, char *argv[]);
void MoveDown(Model& UP, Model& DOWN);
void Integ_Rotated(Model& m, double Rotated_Angle);
void Integ_Rotated_Back(Model& m, double Rotated_Angle);

void CheckContour(int ImageNum, Model& Integ, vector<cv::Mat>& Silhouette, Cpixel*** vertexII, CMatrix* ART);

using namespace cv;
int Integration(int argc, char *argv[])
{
	cout << "====================================\n             Integration             \n====================================" << endl;

	//            A[RT][RT]^-1           

	CMatrix RTinv = ICPMatrix.Inverse();
	//-----------------------
	ARTRTinv = new CMatrix[ImageNum];
	for (int i(0); i < ImageNum; i++)
	{
		ARTRTinv[i].assign(4);
		ARTRTinv[i] = ART[i] * RTinv;
		ARTRTinv[i](3, 3) = 1.0;
	}
	cout << "ARTRT " << endl;
	//              DOWN                
	CalcDownCamaraPos();

	//                UP    
	vector<Mat> UpSilhouette(ImageNum);			//è36 images
	ReadSilhouette(ImageNum, directory[1], model, pose[0], UpSilhouette);
	cout << "UP silhouette " << endl;

	//         up bounding boxç                 
	CVector3d Origin;
	if (model == "newzebra/") {
		if (Angle_.Orientation_Angle == 0 * M_PI / 180)
			Origin.Set(50, 50, -120);
		else if (Angle_.Orientation_Angle == 10 * M_PI / 180)
			Origin.Set(50, 70, -120);
		else if (Angle_.Orientation_Angle == 20 * M_PI / 180)
			Origin.Set(45, 80, -120);
		else if (Angle_.Orientation_Angle == 30 * M_PI / 180)
			Origin.Set(40, 90, -120);
		else if (Angle_.Orientation_Angle == 40 * M_PI / 180)
			Origin.Set(40, 105, -120);
		else if (Angle_.Orientation_Angle == 50 * M_PI / 180)
			Origin.Set(40, 115, -120);
		//Origin.Set(15, 20, -80);
		else if (Angle_.Orientation_Angle == 60 * M_PI / 180)
			Origin.Set(40, 130, -120);
		else if (Angle_.Orientation_Angle == 70 * M_PI / 180)
			Origin.Set(45, 140, -120);
		else if (Angle_.Orientation_Angle == 80 * M_PI / 180)
			Origin.Set(50, 160, -120);
		else if (Angle_.Orientation_Angle == 90 * M_PI / 180)
			Origin.Set(60, 175, -120);
	}
	else if (model == "newpanda/") {
		if (Angle_.Orientation_Angle == 0 * M_PI / 180)
			Origin.Set(35.0, 35.0, -168);
		else if (Angle_.Orientation_Angle == 10 * M_PI / 180)
			Origin.Set(30.0, 55.0, -168);
		else if (Angle_.Orientation_Angle == 20 * M_PI / 180)
			Origin.Set(15.0, 65.0, -168);
		else if (Angle_.Orientation_Angle == 30 * M_PI / 180)
			Origin.Set(10.0, 75.0, -168);
		else if (Angle_.Orientation_Angle == 40 * M_PI / 180)
			Origin.Set(5.0, 90.0, -168);
		else if (Angle_.Orientation_Angle == 50 * M_PI / 180)
			Origin.Set(10.0, 110.0, -168);
		else if (Angle_.Orientation_Angle == 60 * M_PI / 180)
			Origin.Set(10.0, 125.0, -168);
		else if (Angle_.Orientation_Angle == 70 * M_PI / 180)
			Origin.Set(10.0, 140.0, -168);
		else if (Angle_.Orientation_Angle == 80 * M_PI / 180)
			Origin.Set(20.0, 160.0, -168);
		else if (Angle_.Orientation_Angle == 90 * M_PI / 180)
			Origin.Set(35.0, 180.0, -168);
	}
	else if (model == "newflog/") {
		if (Angle_.Orientation_Angle == 0 * M_PI / 180)
			Origin.Set(55, 55, -144);
		else if (Angle_.Orientation_Angle == 10 * M_PI / 180)
			Origin.Set(40, 55, -144);
		else if (Angle_.Orientation_Angle == 20 * M_PI / 180)
			Origin.Set(30, 65, -144);
		else if (Angle_.Orientation_Angle == 30 * M_PI / 180)
			Origin.Set(20, 75, -144);
		else if (Angle_.Orientation_Angle == 40 * M_PI / 180)
			Origin.Set(20, 90, -144);
		else if (Angle_.Orientation_Angle == 50 * M_PI / 180)
			Origin.Set(15, 125, -144);
		else if (Angle_.Orientation_Angle == 60 * M_PI / 180)
			Origin.Set(20, 130, -144);
		else if (Angle_.Orientation_Angle == 70 * M_PI / 180)
			Origin.Set(20, 140, -144);
		else if (Angle_.Orientation_Angle == 80 * M_PI / 180)
			Origin.Set(25, 160, -144);
		else if (Angle_.Orientation_Angle == 90 * M_PI / 180)
			Origin.Set(35, 180, -144);
	}


	cout << Origin.x << " " << Origin.y << " " << Origin.z;
	UpBoundingBox.SetOrigin(Origin);

	cout << "BBox origin: " << UpBoundingBox.origin.x << " " << UpBoundingBox.origin.y << " " << UpBoundingBox.origin.z << endl;

	Cpixel** vertexUp;
	vertexUp = new Cpixel *[36];
	for (int i(0); i < 36; i++)
		vertexUp[i] = new Cpixel[8];
	//SetVertexImage(UpBoundingBox, vertexUp, ART);
	//SetVertexImage_Rotated(Angle_.Orientation_Angle, UpBoundingBox, vertexUp, ART); //Projection of voxel to images               
	//CheckBoundingBox(ImageNum, UpBoundingBox, UpSilhouette, vertexUp);
	//Find_Rodrigues_Formular(UpBoundingBox, Angle_.Orientation_Angle, vertexUp, ART);
	//CheckBoundingBox(ImageNum, UpSilhouette, vertexUp);

	for (int i(0); i < 36; i++)
		delete[] vertexUp[i];
	delete[] vertexUp;

	DividVoxelTo8_Rotated(Angle_.Orientation_Angle, OctLevels, UpBoundingBox, ART, UpSilhouette, UP.Octrees);
	cout << "Number of Octrees ----- before:  " << UP.Octrees.size() << endl;
	//DividVoxelTo8(OctLevels, UpBoundingBox, ART, UpSilhouette, UP.Octrees);
//	Divided_lowerLV_Octree(UP, OctLevels, Angle_.Orientation_Angle, UP.Octrees);
	cout << "Number of Octrees  ----- after:  " << UP.Octrees.size() << endl;

	UP.Octrees.shrink_to_fit();
	//UpSilhouette.clear();
	//UpSilhouette.shrink_to_fit();

	////Find centroid before
	//CVector3d centroid_before(0.0, 0.0, 0.0);
	//UpBoundingBox.SetVertexWorld_Center_Rotated(Angle_.Orientation_Angle, centroid_before);
	//CVector3d centroid_after(0.0, 0.0, 0.0);
	//Check_Plane2(UP, UpBoundingBox, Angle_.Orientation_Angle, Min, Max, centroid_after);
	//Rotated_Back(UP, 90 * M_PI / 180, centroid_before, centroid_after);
	//centroid_before.Clear();
	//centroid_after.Clear();

	//-----------------------------------------    DOWN Model   Å--------------------------------------//
	cout << "DOWN Model  " << endl;
	vector<Mat> DownSilhouette(ImageNum);
	ReadSilhouette(ImageNum, directory[1], model, pose[1], DownSilhouette);

	DownBoundingBox.SetOrigin(Origin);

	Cpixel** vertexDown;
	vertexDown = new Cpixel *[ImageNum];
	for (int i(0); i < ImageNum; i++)
		vertexDown[i] = new Cpixel[8];

	//SetVertexImage(DownBoundingBox, vertexDown, ARTRTinv);
	//SetVertexImage_Rotated(Angle_.Orientation_Angle, DownBoundingBox, vertexDown, ARTRTinv);
	//SetVertexImage_Rotated(Angle_.Orientation_Angle, DownBoundingBox, vertexDown, ART);
	//CheckBoundingBox(ImageNum, DownBoundingBox, DownSilhouette, vertexDown);
	//Find_Rodrigues_Formular(DownBoundingBox, Angle_.Orientation_Angle, vertexDown, ARTRTinv);	
	//CheckBoundingBox(ImageNum, DownSilhouette, vertexDown);

	for (int i(0); i < ImageNum; i++)
		delete[] vertexDown[i];
	delete[] vertexDown;

	//DividVoxelTo8_Rotated(Angle_.Orientation_Angle, OctLevels, DownBoundingBox, ART, DownSilhouette, DOWN.Octrees);
	DividVoxelTo8_Rotated(Angle_.Orientation_Angle, OctLevels, DownBoundingBox, ARTRTinv, DownSilhouette, DOWN.Octrees);
	//DividVoxelTo8(OctLevels, DownBoundingBox, ARTRTinv, DownSilhouette, DOWN.Octrees);
//	Divided_lowerLV_Octree(DOWN, OctLevels, Angle_.Orientation_Angle, DOWN.Octrees);
	cout << "Number of Octrees  ----- after:  " << DOWN.Octrees.size() << endl;
	
	DOWN.Octrees.shrink_to_fit();
	DownSilhouette.clear();
	DownSilhouette.shrink_to_fit();

	cout << "Up octree " << UP.Octrees.size() << endl;
	cout << "DOWN octree " << DOWN.Octrees.size() << endl;

	////Find centroid before   2016/06/23
	//DownBoundingBox.SetVertexWorld_Center_Rotated(Angle_.Orientation_Angle, centroid_before);
	//Check_Plane2(DOWN, DownBoundingBox, Angle_.Orientation_Angle, Min, Max, centroid_after);
	//Rotated_Back(DOWN, 90 * M_PI / 180, centroid_before, centroid_after);
	//centroid_before.Clear();
	//centroid_after.Clear();

//	RunOpenGLDown(argc, argv);

//	getchar();

	Check_UpDown_Rotation(UP, DOWN, UpBoundingBox, DownBoundingBox, Angle_.Orientation_Angle);

	cout << "\nFind minmax Integration\n";
	FindMinAndMax(UP, DOWN, Min, Max, MinVoxelL, MinVoxelH);

	cout << "Find Min " << Min.x << " " << Min.y << " " << Min.z << endl;
	cout << "Find Max " << Max.x << " " << Max.y << " " << Max.z << endl;

	//cout << "RunOpenGLDown\n";
	//RunOpenGLDown(argc, argv);


	//       UP & DOWN           
	UP.Voxels = new Voxel **[UP.num[0]];
	DOWN.Voxels = new Voxel **[DOWN.num[0]];
	for (int i(0); i < UP.num[0]; i++) {
		UP.Voxels[i] = new Voxel *[UP.num[1]];
		DOWN.Voxels[i] = new Voxel *[DOWN.num[1]];
		for (int k(0); k < UP.num[1]; k++) {
			UP.Voxels[i][k] = new Voxel[UP.num[2]];
			DOWN.Voxels[i][k] = new Voxel[DOWN.num[2]];
		}
	}

	clock_t time[2];
	time[0] = clock();
	// Voxel      
#pragma omp parallel sections
	{
#pragma omp section
		Octree_to_voxel(UP, OctLevels, Min, Max, MinVoxelL, MinVoxelH);

#pragma omp section
		Octree_to_voxel(DOWN, OctLevels, Min, Max, MinVoxelL, MinVoxelH);
	}
	time[1] = clock();
	cout << "Time Octree_to_Voxel " << (double)(time[1] - time[0]) / CLOCKS_PER_SEC << "s" << endl;
	cout << "New UP & DOWN\n MinVoxelL:" << MinVoxelL << " MinVoxelH:" << MinVoxelH << endl;

#pragma omp parallel sections
	{
#pragma omp section
		FindOutsideVoxel(UP);
#pragma omp section
		FindOutsideVoxel(DOWN);
	}
	cout << "Up.VoxelNum	 " << UP.VoxelNum << endl;
	cout << "Up.FillVoxelNum " << UP.FillVoxelNum << endl;
	cout << "Up.SurfaceNum   " << UP.SurfNum << endl;
	cout << "Dowm.VoxelNum      " << DOWN.VoxelNum << endl;
	cout << "Dowm.FillVoxelNum  " << DOWN.FillVoxelNum << endl;
	cout << "Dowm.SurfaceNum    " << DOWN.SurfNum << endl << endl;

	for (int i(0); i < 3; i++)
		Integ.num[i] = UP.num[i];

	Integ.Flags = new VoxelFlag **[Integ.num[0]];
	for (int i(0); i < Integ.num[0]; i++) {
		Integ.Flags[i] = new VoxelFlag *[Integ.num[1]];
		for (int k(0); k < Integ.num[1]; k++) {
			Integ.Flags[i][k] = new VoxelFlag[Integ.num[2]];
		}
	}

	UPandDOWN(UP, DOWN, Integ, Min, MinVoxelL, MinVoxelH);
	//UPandDOWN_zhang(UP, DOWN, Integ, Min, MinVoxelL, MinVoxelH);

	Integ.Voxels = new Voxel **[Integ.num[0]];
	for (int i(0); i < Integ.num[0]; i++) {
		Integ.Voxels[i] = new Voxel *[Integ.num[1]];
		for (int k(0); k < Integ.num[1]; k++) {
			Integ.Voxels[i][k] = new Voxel[Integ.num[2]];
		}
	}

	//        center, origin, coord   
	SetVoxelParameter(Integ, Min, MinVoxelL, MinVoxelH);

	//--------------------------------------------------------------------
	// Using whether Union or Intersection between two models
	//
	//         1.                         
	//Unio(Integ);
	//cout<<"\n "<<endl;
	//
	//         2.        (intersection 2models)                    
	Intersection(Integ);
	//Slice(Integ);			//2014/08/17
	//cout<<"Integ.FillVoxelNum  "<<Integ.FillVoxelNum<<endl;
	//cout << "\nFinish Intersection" << endl;
	//
	//         3.     if use the theta angle to check the visibility    (union 2models)             
	//Using whether Union or Intersection between two models inside ProposedMethod(Integ) function
	//ProposedMethod(Integ);
	//	Slice(Integ);					//2014/08/17
	
	//RunOpenGL3(argc, argv);

	//ElimIsoVoxels_LUT(Integ);		

	ElimIsoVoxels(Integ);

	string name("voxeldata.txt");
	Putout_txt(Integ, directory[1] + model + name, MinVoxelL);

	//string cameraup("UPcamera/coord.txt");
	//Out_camera(directory[1] + model + cameraup, CameraPosUp);
	//string cameradown("DOWNcamera/coord.txt");
	//Out_camera(directory[1] + model + cameradown, CameraPosDown);
	//string CPU("ART/");
	//string CPD("ARTRT/");
	//Camera_para(directory[1] + model + CPU, ART);
	//Camera_para(directory[1] + model + CPD, ARTRTinv);

	SetSrufToVector(UP);
	FreeMemory_Voxel(UP);
	SetSrufToVector(DOWN);
	FreeMemory_Voxel(DOWN);

	//              
	FindOutsideVoxel(Integ);
	cout << "Integ.VoxelNum    " << Integ.VoxelNum << endl;
	cout << "Integ.FillVoxelNum" << Integ.FillVoxelNum << endl;
	cout << "Integ.SurfNum     " << Integ.SurfNum << endl;

	Integ_Rotated(Integ, Angle_.Orientation_Angle);
	//--------------------------------------------------------------------

	cout << "Lego RGB to Lab and Coloring " << endl;
	LegoRGB_to_Lab(Integ);		//LEGOÇRGBÇCIELab

	Coloring(Integ);

	RealColor_to_LegoColor_lab(Integ);
	//RealColor_to_LegoColor_ab(Integ);	
	//RealColor_to_LegoColor_hue(Integ);
	//RealColor_to_LegoColor_rgb(Integ);

	cout << "ColorModel.txt\n";

	string ColoredFile("ColorModel/ColoredFrog_7_20.txt");
	ofstream fout(ColoredFile);

	//fout << integ.num[0] << "  " << integ.num[1] << "   " << integ.num[2] << "  " << length << endl;
	//fout << Integ.num[0] << " " << Integ.num[1] << " " << Integ.num[2] << endl;
	//fout << Integ.num[0] + 6 << "  " << Integ.num[1] + 6 << "  " << Integ.num[2] + 6 << endl;

	fout << Integ.num[0] + 6 << " " << Integ.num[1] + 6 << " " << Integ.num[2] + 6 << endl;
	//fout << integ.Voxels[0][0][0].origin.x << "  " << integ.Voxels[0][0][0].origin.y << "   " << integ.Voxels[0][0][0].origin.z << endl;
	int count_surf = 0;
	for (int x(1); x < Integ.num[0] - 1; x++)
	{
		for (int y(1); y < Integ.num[1] - 1; y++)
		{
			for (int z(1); z < Integ.num[2] - 1; z++)
			{
				if (Integ.Voxels[x][y][z].fill) {
					if (Integ.Voxels[x][y][z].surf) {
						//cout << x << " " << y << " " << z << " " << Integ.Voxel_colors[x][y][z].r << " " << Integ.Voxel_colors[x][y][z].g << " " << Integ.Voxel_colors[x][y][z].b << endl;
						//fout << x << " " << y << " " << z << " " << Integ.ColorID[count_surf] << endl;
						fout << x + 3 << " " << y + 3 << " " << z + 3 << " " << Integ.ColorID[count_surf] << endl;
						count_surf++;
					}
					else {
						fout << x + 3 << " " << y + 3 << " " << z + 3 << " " << 0 << endl;
					}
				}
			}
		}
	}


	SetSrufToVector(Integ);    // Integ.SurfVoxels
	//FreeMemory_Voxel(Integ);		
	//Integ_Rotated_Back(Integ, Angle_.Orientation_Angle);

	////-------------------------- 2nd projection -----------------------------------
	Cpixel*** vertexII;
	vertexII = new Cpixel **[ImageNum];
	for (int i(0); i < ImageNum; i++) {
		vertexII[i] = new Cpixel*[Integ.SurfVoxels.size()];
		for (int j(0); j < Integ.SurfVoxels.size(); j++) {
			vertexII[i][j] = new Cpixel[8];
		}
	}

	// CheckContour(ImageNum, Integ, UpSilhouette, vertexII, ART);

	for (int i(0); i < ImageNum; i++) {
		for (int j(0); j < Integ.SurfVoxels.size(); j++) {
			delete[] vertexII[i][j];
		}delete[] vertexII[i];
	}delete[] vertexII;

	UpSilhouette.clear();
	UpSilhouette.shrink_to_fit();

	//  output off                            
	OutputOff(Integ);

	cout << "\nRun OpenGl3 " << endl;

	RunOpenGL3(argc, argv);

	for (int i(0); i < Integ.num[0]; i++) {
		for (int k(0); k < Integ.num[1]; k++) {
			delete[] Integ.Flags[i][k];
		}
		delete[] Integ.Flags[i];
	}
	delete[] Integ.Flags;

	//UP & DOWNÅïInteg
	UP.SurfVoxels.clear();
	UP.SurfVoxels.shrink_to_fit();
	DOWN.SurfVoxels.clear();
	DOWN.SurfVoxels.shrink_to_fit();

	Integ.SurfVoxels.clear();
	Integ.SurfVoxels.shrink_to_fit();
	//vector
	Integ.SurfColors.clear();
	Integ.SurfColors.shrink_to_fit();


	cout << "Finish Integration " << endl;
	return 0;
}

int Input(int argc, char *argv[]) {

	cout << "============================" << endl;
	cout << "       Input Camera         " << endl;
	cout << "============================" << endl;

	ART = new CMatrix[ImageNum];
	ARTRTinv = new CMatrix[ImageNum];
	CameraPosDown = new CVector3d[ImageNum];
	CameraPosUp = new CVector3d[ImageNum];

	for (int k(0); k < ImageNum; k++) {
		ART[k].assign(4);
		ART[k](3, 3) = 1.0;
		ARTRTinv[k].assign(4);
		ARTRTinv[k](3, 3) = 1.0;
	}


	string name("voxeldata.txt");
	string cameraup("UPcamera/coord.txt");
	string cameradown("DOWNcamera/coord.txt");
	string CPU("ART/");
	string CPD("ARTRT/");
	In_camara(directory[1] + model + cameraup, CameraPosUp);
	In_camara(directory[1] + model + cameradown, CameraPosDown);
	In_camera_para(directory[1] + model + CPU, ART);
	In_camera_para(directory[1] + model + CPD, ARTRTinv);

	string sline;
	istringstream ssline;
	string Filename;
	Filename = directory[1] + model + name;
	ifstream file(Filename);
	if (!file) {
		std::cout << Filename << "is not found!" << std::endl;
		exit(0);
	}
	int ii, jj, kk;

	getline(file, sline);
	ssline.str(sline);
	ssline >> Integ.num[0] >> Integ.num[1] >> Integ.num[2] >> MinVoxelL;
	MinVoxelH = 1.2*MinVoxelL;
	ssline.clear();
	getline(file, sline);
	ssline.str(sline);
	ssline >> Min.x >> Min.y >> Min.z;
	ssline.clear();

	//                                    
	Integ.Voxels = new Voxel **[Integ.num[0]];
	for (int i(0); i < Integ.num[0]; i++) {
		Integ.Voxels[i] = new Voxel *[Integ.num[1]];
		for (int k(0); k < Integ.num[1]; k++) {
			Integ.Voxels[i][k] = new Voxel[Integ.num[2]];
		}
	}
	//                   
	Integ.Flags = new VoxelFlag **[Integ.num[0]];
	for (int i(0); i < Integ.num[0]; i++) {
		Integ.Flags[i] = new VoxelFlag *[Integ.num[1]];
		for (int k(0); k < Integ.num[1]; k++) {
			Integ.Flags[i][k] = new VoxelFlag[Integ.num[2]];
		}
	}


	SetVoxelParameter(Integ, Min, MinVoxelL, MinVoxelH);

	for (int i(0); i < Integ.num[0]; i++) {
		for (int j(0); j < Integ.num[1]; j++) {
			for (int k(0); k < Integ.num[2]; k++) {
				Integ.Voxels[i][j][k].fill = false;
			}
		}
	}

	while (!file.eof())
	{
		getline(file, sline);
		ssline.str(sline);
		ssline >> ii >> jj >> kk;
		ssline.clear();
		Integ.Voxels[ii][jj][kk].fill = true;
		Integ.FillVoxelNum++;
	}


	//                
	FindOutsideVoxel(Integ);
	cout << "voxel Num " << Integ.VoxelNum << endl;
	cout << "voxel fillnum " << Integ.FillVoxelNum << endl;
	cout << "voxel surface " << Integ.SurfNum << endl;

	//#########################
	//                       êFïtÇØ                            
	//#########################
	cout << "   " << endl;
	LegoRGB_to_Lab(Integ);
	Coloring(Integ);
	//                          
	RealColor_to_LegoColor_lab(Integ);
	//RealColor_to_LegoColor_ab(Integ);			
	//RealColor_to_LegoColor_hue(Integ);		
	//RealColor_to_LegoColor_rgb(Integ);

	//
	SetSrufToVector(Integ);
	//FreeMemory_Voxel(Integ);		
	
	//                output off                            
	OutputOff(Integ);

	


	RunOpenGL3(argc, argv);


	Integ.SurfVoxels.clear();
	Integ.SurfVoxels.shrink_to_fit();
	//
	Integ.SurfColors.clear();
	Integ.SurfColors.shrink_to_fit();
	//                        
	for (int i(0); i < Integ.num[0]; i++) {
		for (int k(0); k < Integ.num[1]; k++) {
			delete[] Integ.Flags[i][k];
		}
		delete[] Integ.Flags[i];
	}
	delete[] Integ.Flags;


	cout << "Finish Input " << endl;


	return 0;
} 