#include "../stdafx.h"

extern Model UP;
extern Model DOWN;

extern int ImageNum;				//number of image at UP,DOWN modelÇ
extern double scale;				//Voxel heightÅF1.0Å@orÅF1.2 (LEGO)
extern double Width;				//Width of bounding box of Down mode
extern short OctLevels;				//Level of Octree

extern string directory[2];		    //Data directory ={ "../../data/input/", "../../data/output/" };
extern string model;				//model's name
extern string pose[3];				//pose 1 or 2   ={"up/","down/","Zhang_Calib/"};

extern OctVoxel UpBoundingBox;		//Bounding box of UP model
extern OctVoxel DownBoundingBox;	//Bounding box of DOWN model

extern double MinVoxelL;			//Length of the model minimum voxel
extern double MinVoxelH;			//Height of the model minimum voxel

extern CMatrix *ART;				//ART MatrixÅiA:Internal parametersÅ@R:Rotation matrixÅ@TÅFTranslation matrixÅj
extern CVector3d* CameraPosUp;		//CameraPosUp:Position in world coordinates of the camera

//2016/05/14
extern vector<OctVoxel> UpBbox_Scale;
extern vector<OctVoxel> DownBbox_Scale;

//Function prototype
void ReadSilhouette(int, string, string, string, vector<cv::Mat>&);
void CalcWorldToImage(int, string*, string, string*, CMatrix*, CVector3d*);
void CheckBoundingBox(int ImageNum, vector<cv::Mat>&, Cpixel**);
void DividVoxelTo8(short, OctVoxel&, CMatrix*, vector<cv::Mat>&, vector<OctVoxel>&);
void FindMinAndMax(Model& m, CVector3d& min, CVector3d& max, double MinVoxelL, double MinVoxelH);

void OctreeToVoxel(Model& m, double Rotated_Angle, short level, CVector3d& min, CVector3d& max, double MinVoxelL, double MinVoxelH);

void SetVertexImage(OctVoxel& box, Cpixel** vertexI, CMatrix* ART);

void RunOpenGL(int argc, char *argv[]);		//Shape From Silhouette
void RunOpenGLDown(int argc, char *argv[]);		//Shape From Silhouette

void FindLargest_ProjectionVoxel(int ImageNum, vector<OctVoxel>&, vector<cv::Mat>&, Cpixel***);
void SetVertexImageII(vector<OctVoxel>& box, Cpixel*** vertexII, CMatrix* ART);
void CheckContour(int ImageNum, vector<OctVoxel>& Octree, vector<cv::Mat>& Silhouette, Cpixel*** vertexII);

void SetVertexImage_Rotated(double Rotated_Angle, OctVoxel& box, Cpixel** vertexI, CMatrix* ART);
//void DividVoxelTo8_Rotated(double, short, OctVoxel&, CMatrix*, vector<cv::Mat>&, vector<OctVoxel>&);
void DividVoxelTo8_Rotated(double, short, OctVoxel&, CMatrix*, vector<cv::Mat>&, vector<OctVoxel>&);

void SetVertexImage_Rotated2(double Rotated_Angle, OctVoxel& box, CVector3d* vertexW, Cpixel** vertexI, CMatrix* ART);
void DividVoxelTo8_Rotated2(double Rotated_Angle, short LV, OctVoxel& parent, CMatrix* ART, vector<cv::Mat>& Silhouette, vector<OctVoxel>& Octree);

extern CVector3d BBox_Origin;

void Check_Plane(Model& m, OctVoxel& box, vector<OctVoxel>& scale_box, double Rotated_Angle);
void Rotated_BoundingBox_Arbitrary(double Rotated_Angle, OctVoxel& box, Cpixel** vertexI, CMatrix* ART);
void Find_Rodrigues_Formular(OctVoxel& box, double Rotated_Angle, Cpixel** vertex2D, CMatrix* ART);
void Find_Scale_Bbox(Model& m, OctVoxel& box, vector<OctVoxel>& scale_box, double Rotated_Angle);

extern int Surf_OctreeNum;

//test 2016/05/17

//
void Check_Plane2(Model& m, OctVoxel& boundingbox, double Rotated_Angle, CVector3d& min, CVector3d& max, CVector3d& newCentbox);
void Octree_to_voxel(Model& m, short level, CVector3d& min, CVector3d& max, double MinVoxelL, double MinVoxelH);

// 2016/5/18
vector<CVector3d> up_octree_surf;


//2016/5/19
void Divided_lowerLV_Octree(Model& m, short LV, double Rotated_Angle, vector<OctVoxel>& Octree);

void RunOpenGL_Check(int argc, char *argv[]);
void RunOpenGL1(int argc, char *argv[]);

void Rotated_Back(Model& m, double Rotated_Angle, CVector3d centroid_before, CVector3d centroid_after); //2016/06/23

using namespace cv;


//                                                              
// Shape from silhouette          
//                                                              
int ShapeFromSilhouette(double Rotated_Angle, int argc, char *argv[])
{
	cout << "====================================\n       Shape from Silhouette        \n====================================" << endl;
	cout << "Angle " << Rotated_Angle << endl;

	ART = new CMatrix[ImageNum];
	CameraPosUp = new CVector3d[ImageNum];
	CalcWorldToImage(ImageNum, directory, model, pose, ART, CameraPosUp);

	vector<cv::Mat> UpSilhouette(ImageNum);
	ReadSilhouette(ImageNum, directory[1], model, pose[0], UpSilhouette);

	CVector3d UpOrigin_up;

	CVector3d UpOrigin;
	if (model == "newzebra/") {
		if (Rotated_Angle == 0 * M_PI / 180)
			UpOrigin.Set(50, 50, -120);
		else if (Rotated_Angle == 10 * M_PI / 180)
			UpOrigin.Set(50, 70, -120);
		else if (Rotated_Angle == 20 * M_PI / 180)
			UpOrigin.Set(45, 80, -120);
		else if (Rotated_Angle == 30 * M_PI / 180)
			UpOrigin.Set(40, 90, -120);
		else if (Rotated_Angle == 40 * M_PI / 180)
			UpOrigin.Set(40, 105, -120);
		else if (Rotated_Angle == 50 * M_PI / 180)
			UpOrigin.Set(40, 115, -120);
		//UpOrigin.Set(15, 20, -80);
		else if (Rotated_Angle == 60 * M_PI / 180)
			UpOrigin.Set(40, 130, -120);
		else if (Rotated_Angle == 70 * M_PI / 180)
			UpOrigin.Set(45, 140, -120);
		else if (Rotated_Angle == 80 * M_PI / 180)
			UpOrigin.Set(50, 160, -120);
		else if (Rotated_Angle == 90 * M_PI / 180)
			UpOrigin.Set(60, 175, -120);
		//else
		//UpOrigin.Set(30, 25, -80);
	}
	else if (model == "newpanda/") {				//z=-165 for octree5, 
		if (Rotated_Angle == 0 * M_PI / 180)
			UpOrigin.Set(35.0, 35.0, -168);
		else if (Rotated_Angle == 10 * M_PI / 180)
			UpOrigin.Set(30.0, 55.0, -168);
		else if (Rotated_Angle == 20 * M_PI / 180)
			UpOrigin.Set(15.0, 65.0, -168);
		else if (Rotated_Angle == 30 * M_PI / 180)
			UpOrigin.Set(10.0, 75.0, -168);
		else if (Rotated_Angle == 40 * M_PI / 180)
			UpOrigin.Set(5.0, 90.0, -168);
		else if (Rotated_Angle == 50 * M_PI / 180)
			UpOrigin.Set(10.0, 110.0, -168);
		else if (Rotated_Angle == 60 * M_PI / 180)
			UpOrigin.Set(10.0, 125.0, -168);
		else if (Rotated_Angle == 70 * M_PI / 180)
			UpOrigin.Set(10.0, 140.0, -168);
		else if (Rotated_Angle == 80 * M_PI / 180)
			UpOrigin.Set(20.0, 160.0, -168);
		else if (Rotated_Angle == 90 * M_PI / 180)
			UpOrigin.Set(35.0, 180.0, -168);
	}
	else if (model == "newflog/") {
		if (Rotated_Angle == 0 * M_PI / 180)
			UpOrigin.Set(55, 55, -144);
		else if (Rotated_Angle == 10 * M_PI / 180)
			UpOrigin.Set(40, 55, -144);
		else if (Rotated_Angle == 20 * M_PI / 180)
			UpOrigin.Set(30, 65, -144);
		else if (Rotated_Angle == 30 * M_PI / 180)
			UpOrigin.Set(20, 75, -144);
		else if (Rotated_Angle == 40 * M_PI / 180)
			UpOrigin.Set(20, 90, -144);
		else if (Rotated_Angle == 50 * M_PI / 180)
			UpOrigin.Set(15, 125, -144);
		else if (Rotated_Angle == 60 * M_PI / 180)
			UpOrigin.Set(20, 130, -144);
		else if (Rotated_Angle == 70 * M_PI / 180)
			UpOrigin.Set(20, 140, -144);
		else if (Rotated_Angle == 80 * M_PI / 180)
			UpOrigin.Set(25, 160, -144);
		else if (Rotated_Angle == 90 * M_PI / 180)
			UpOrigin.Set(35, 180, -144);
	}

	UpBoundingBox.SetOrigin(UpOrigin);
	BBox_Origin = UpOrigin;
	cout << "BBox origin: " << UpBoundingBox.origin.x << " " << UpBoundingBox.origin.y << " " << UpBoundingBox.origin.z << endl;

	Cpixel** vertexUp;
	vertexUp = new Cpixel *[ImageNum];
	for (int i(0); i < ImageNum; i++)
		vertexUp[i] = new Cpixel[8];

	//SetVertexImage_Rotated(Rotated_Angle, UpBoundingBox, vertexUp, ART);
	//Find_Rodrigues_Formular(UpBoundingBox, Rotated_Angle, vertexUp, ART);
	//	CheckBoundingBox(ImageNum, UpSilhouette, vertexUp);

	for (int i(0); i < ImageNum; i++)
		delete[] vertexUp[i];
	delete[] vertexUp;

	DividVoxelTo8_Rotated2(Rotated_Angle, OctLevels, UpBoundingBox, ART, UpSilhouette, UP.Octrees);
	cout << "Number of Octrees ----- before:  " << UP.Octrees.size() << endl;

	//	Divided_lowerLV_Octree(UP, OctLevels, Rotated_Angle, UP.Octrees);
	cout << "Number of Octrees  ----- after:  " << UP.Octrees.size() << endl;

	//Find centroid before
	CVector3d centroid_before(0.0, 0.0, 0.0);
	UpBoundingBox.SetVertexWorld_Center_Rotated(Rotated_Angle, centroid_before);	
	cout << "centroid_old_Bbox " << centroid_before.x << " " << centroid_before.y << " " << centroid_before.z << endl;

	CVector3d upMin(0.0, 0.0, 0.0);	//origin
	CVector3d upMax(0.0, 0.0, 0.0);			//Diagonal point of origin
	CVector3d centroid_after(0.0, 0.0, 0.0);

	//Check_Plane2(UP, UpBoundingBox, Rotated_Angle, upMin, upMax, centroid_after);
	//Rotated_Back(UP, 90 * M_PI / 180, centroid_before, centroid_after);
	
	FindMinAndMax(UP, upMin, upMax, MinVoxelL, MinVoxelH);

	cout << "\nVertical width " << upMax.x - upMin.x << endl;
	cout << "Lateral width " << upMax.y - upMin.y << endl;
	cout << "Height " << upMax.z - upMin.z << endl;

	cout << "upMin xyz " << upMin.x << " " << upMin.y << " " << upMin.z << endl;
	cout << "upMax xyz " << upMax.x << " " << upMax.y << " " << upMax.z << endl;
	cout << "minVoxelL " << MinVoxelL << "\nminVoxelH " << MinVoxelH << endl;

//   RunOpenGL(argc, argv); //up

	UP.Octrees.shrink_to_fit();
	UpSilhouette.clear();
	UpSilhouette.shrink_to_fit();

	// 3D dynamic array Voxel[0][1][2]
	UP.Voxels = new Voxel **[UP.num[0]];
	for (int i(0); i < UP.num[0]; i++) {
		UP.Voxels[i] = new Voxel *[UP.num[1]];
		for (int k(0); k < UP.num[1]; k++) {
			UP.Voxels[i][k] = new Voxel[UP.num[2]];
		}
	}

	Octree_to_voxel(UP, OctLevels, upMin, upMax, MinVoxelL, MinVoxelH);

	//OctreeToVoxel(UP, Rotated_Angle, OctLevels, upMin, upMax, MinVoxelL, MinVoxelH);

	cout << "Finish to create UP Voxel model\n";

	UP.VertexMax_.Clear();
	UP.VertexMin_.Clear();
	BBox_Origin.Clear();
	UpBbox_Scale.clear();
	UP.New_smallcubicvertex->Clear();
	UP.P_IntersecPoint->Clear();
	
	centroid_before.Clear();
	centroid_after.Clear();
	///=====================================================================////

	cout << "========= Read down silhouette image:======== \n";
	vector<Mat> DownSilhouette(ImageNum);		//Store 36 DOWN silhouette images in mat
	ReadSilhouette(ImageNum, directory[1], model, pose[1], DownSilhouette);
	cout << "DOWN mode - Finish to read imageÅ" << endl;

	CVector3d DownOrigin;
	if (model == "newzebra/") {
		if (Rotated_Angle == 0 * M_PI / 180)
			DownOrigin.Set(55, 60, -120);
		else if (Rotated_Angle == 10 * M_PI / 180)
			DownOrigin.Set(40, 65, -120);       //10
		else if (Rotated_Angle == 20 * M_PI / 180)
			DownOrigin.Set(35, 70, -120);       //20
		else if (Rotated_Angle == 30 * M_PI / 180)
			DownOrigin.Set(38, 78, -120);       //30
		else if (Rotated_Angle == 40 * M_PI / 180)
			DownOrigin.Set(40, 88, -120);       //40
		else if (Rotated_Angle == 50 * M_PI / 180)
			DownOrigin.Set(45, 90, -120);       //50
		else if (Rotated_Angle == 60 * M_PI / 180)
			DownOrigin.Set(30, 130, -120);		  //60
		else if (Rotated_Angle == 70 * M_PI / 180)
			DownOrigin.Set(38, 130, -120);      //70
		else if (Rotated_Angle == 80 * M_PI / 180)
			DownOrigin.Set(40, 150, -120);     //80
		else if (Rotated_Angle == 90 * M_PI / 180)
			DownOrigin.Set(50, 160, -120);            //90
	}
	else if (model == "newpanda/") {
		if (Rotated_Angle == 0 * M_PI / 180)
			DownOrigin.Set(35.0, 35.0, -50);
		else if (Rotated_Angle == 10 * M_PI / 180)
			DownOrigin.Set(40.0, 55.0, -50);
		else if (Rotated_Angle == 20 * M_PI / 180)
			DownOrigin.Set(25.0, 65.0, -50);
		else if (Rotated_Angle == 30 * M_PI / 180)
			DownOrigin.Set(20.0, 85.0, -50);
		else if (Rotated_Angle == 40 * M_PI / 180)
			DownOrigin.Set(20.0, 110.0, -50);
		else if (Rotated_Angle == 50 * M_PI / 180)
			DownOrigin.Set(20.0, 130.0, -50);
		else if (Rotated_Angle == 60 * M_PI / 180)
			DownOrigin.Set(20.0, 150.0, -50);
		else if (Rotated_Angle == 70 * M_PI / 180)
			DownOrigin.Set(30.0, 160.0, -50);
		else if (Rotated_Angle == 80 * M_PI / 180)
			DownOrigin.Set(35.0, 180.0, -50);
		else if (Rotated_Angle == 90 * M_PI / 180)
			DownOrigin.Set(50.0, 190.0, -50);
	}
	else if (model == "newflog/") {
		if (Rotated_Angle == 0 * M_PI / 180)
			DownOrigin.Set(55, 50, -144);
		else if (Rotated_Angle == 10 * M_PI / 180)
			DownOrigin.Set(40, 65, -144);
		else if (Rotated_Angle == 20 * M_PI / 180)
			DownOrigin.Set(30, 75, -144);
		else if (Rotated_Angle == 30 * M_PI / 180)
			DownOrigin.Set(20, 85, -144);
		else if (Rotated_Angle == 40 * M_PI / 180)
			DownOrigin.Set(20, 100, -144);
		else if (Rotated_Angle == 50 * M_PI / 180)
			DownOrigin.Set(15, 115, -144);
		else if (Rotated_Angle == 60 * M_PI / 180)
			DownOrigin.Set(15, 125, -144);
		else if (Rotated_Angle == 70 * M_PI / 180)
			DownOrigin.Set(20, 140, -144);
		else if (Rotated_Angle == 80 * M_PI / 180)
			DownOrigin.Set(25, 155, -144);
		else if (Rotated_Angle == 90 * M_PI / 180)
			DownOrigin.Set(30, 165, -144);
	}

	DownBoundingBox.SetOrigin(DownOrigin);
	BBox_Origin = DownOrigin;
	Cpixel** vertexDown;
	vertexDown = new Cpixel *[ImageNum];
	for (int i(0); i < ImageNum; i++)
		vertexDown[i] = new Cpixel[8];

//	SetVertexImage_Rotated(Rotated_Angle, DownBoundingBox, vertexDown, ART);
	//Find_Rodrigues_Formular(DownBoundingBox, Rotated_Angle, vertexUp, ART);
	//
//	CheckBoundingBox(ImageNum, DownSilhouette, vertexDown);

	DividVoxelTo8_Rotated2(Rotated_Angle, OctLevels, DownBoundingBox, ART, DownSilhouette, DOWN.Octrees);
	cout << "Down Octrees size ----- before:  " << DOWN.Octrees.size() << endl;

	//	Divided_lowerLV_Octree(DOWN, OctLevels, Rotated_Angle, DOWN.Octrees);
	cout << "Number of Octrees  ----- after:  " << DOWN.Octrees.size() << endl;
	
	DownBoundingBox.SetVertexWorld_Center_Rotated(Rotated_Angle, centroid_before);
	cout << "centroid_old_Bbox " << centroid_before.x << " " << centroid_before.y << " " << centroid_before.z << endl;

	for (int i(0); i < ImageNum; i++)
		delete[] vertexDown[i];
	delete[] vertexDown;

	DOWN.Octrees.shrink_to_fit();
	DownSilhouette.clear();
	DownSilhouette.shrink_to_fit();

	CVector3d downMin(0.0, 0.0, 0.0);
	CVector3d downMax(0.0, 0.0, 0.0);

	//	Check_Plane2(DOWN, DownBoundingBox, Rotated_Angle, downMin, downMax, centroid_after);//find the 8 Intersection point
	//	Rotated_Back(DOWN, 90 * M_PI / 180, centroid_before, centroid_after);

	FindMinAndMax(DOWN, downMin, downMax, MinVoxelL, MinVoxelH);

	cout << "downMin xyz " << downMin.x << " " << downMin.y << " " << downMin.z << endl;
	cout << "downMax xyz " << downMax.x << " " << downMax.y << " " << downMax.z << endl;

//	RunOpenGLDown(argc, argv);

	DOWN.Voxels = new Voxel **[DOWN.num[0]];
	for (int i(0); i < DOWN.num[0]; i++) {
		DOWN.Voxels[i] = new Voxel *[DOWN.num[1]];
		for (int k(0); k < DOWN.num[1]; k++) {
			DOWN.Voxels[i][k] = new Voxel[DOWN.num[2]];
		}
	}

	Octree_to_voxel(DOWN, OctLevels, downMin, downMax, MinVoxelL, MinVoxelH);


	//OctreeToVoxel(DOWN, Rotated_Angle, OctLevels, downMin, downMax, MinVoxelL, MinVoxelH);
	cout << "Finish to create DOWN Voxel model" << endl;

	DOWN.VertexMax_.Clear();
	DOWN.VertexMin_.Clear();
	BBox_Origin.Clear();
	DOWN.New_smallcubicvertex->Clear();
	DOWN.P_IntersecPoint->Clear();

	centroid_before.Clear();
	centroid_after.Clear();
	return 0;
}


////-------------------------- 2nd projection -----------------------------------
//Cpixel*** vertexII;
//vertexII = new Cpixel **[ImageNum];
//for (int i(0); i < ImageNum; i++){
//	vertexII[i] = new Cpixel*[UP.Octrees.size()];
//	for (int j(0); j < UP.Octrees.size(); j++){
//		vertexII[i][j] = new Cpixel[8];
//	}
//}
//
////CheckContour(ImageNum, UP.Octrees, UpSilhouette, vertexII);
//
//for (int i(0); i < ImageNum; i++){
//	for (int j(0); j < UP.Octrees.size(); j++){
//		delete[] vertexII[i][j];
//	}delete[] vertexII[i];
//}delete[] vertexII;	