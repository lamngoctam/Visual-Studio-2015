#include "stdafx.h"

//################################
// Global variable                                  
//################################
short OctLevels(7);				//Octree level
short angel(0);					//LEGO rotate
Model UP(OctLevels);			//UP model
Model DOWN(OctLevels);			//DOWN model
Model Integ(OctLevels);			//model


int ImageNum(36);				//number of image
float scale(1.2f);			//Cube 1.0 : LEGO 1.2
//double Width(300.0);		//(mm)(panda)
//double Width(300);			//(mm)(duck)
//double Width(120.0);		//(mm)(newzebra)
//double Width(140.0);		//(mm)(newpanda)
//double Width(500.0);		//(mm)(lion)
double Width(120.0);          //newflog


double thresh(cos(60 / 180.0*M_PI));			//the threshold of the angle
double delThres(-1.5);						//the threshold of distance 

CMatrix* ART;								//ARTmatrixiA:inner@R:rotate@TF)
CMatrix* ARTRTinv;		//inverse matrix		
CVector3d* CameraPosUp;			//UP
CVector3d* CameraPosDown;		//DOWN

CVector3d centroid;			    //UP

CMatrix PCAMatrix(4);			//PCA‚DOWN to UP‚‚matrix
CMatrix ICPMatrix(4);			//ICP‚DOWN to UP‚matrix
CMatrix TMatrix(4);				//

string directory[2] = { "../../data/input/", "../../data/output/" };	//data directory
//string model("newzebra/");
//string model("newpanda/");
string model("newflog/");

string pose[3] = { "up/","down/","Zhang_Calib/" };					//Zhang method

OctVoxel UpBoundingBox(Width);		//Bounding box of UP model
OctVoxel DownBoundingBox(Width);	//Bounding box of DOWN model

double MinVoxelL = Width * pow(0.5, OctLevels);				//UP
double MinVoxelH = scale * Width * pow(0.5, OctLevels);		//UP

int picknum(0);		//pick(3)
int  zcood;
OctVoxel Angle_;


CVector3d BBox_Origin;
vector<CVector3d> Origin_;

//2016/5/12
CVector3d center_boundingbox(0.0, 0.0, 0.0);
int Surf_OctreeNum;

//2016/5/14

vector<OctVoxel> UpBbox_Scale(MinVoxelL);
vector<OctVoxel> DownBbox_Scale(MinVoxelL);
//

OctVoxel scale_(Width);
unsigned int** BlockNum;
unsigned int Block_colorNum(0);			//使用する色の種類
unsigned int Block_varietyNum(7);			//使用する基本ブロックの種類
vector<Brick> LDD;
BrickTable table;
CMatrix rot[2];


//                                                                                  
//                   Zhang Camera Calibration                     
//                                                                                  
int ZhangCalibration(int argc, char* argv[]);

//                                                                                  
//                             Shape from silhouette                  
//                                                                                  
int ShapeFromSilhouette(double Rotated_Angle, int argc, char *argv[]);

//                                                                                  
//                               PCA											
//                                                                                  
int PCA1(int argc, char *argv[]);
int PCA2(int argc, char *argv[]);
int PCA3(int argc, char *argv[]);

//                                                                                  
//                                     ICP                                        
//                                                                                  
int ICP(int argc, char *argv[]);


int Rotated_Integ(int argc, char *argv[]);
int Rotated_Integ3(int argc, char *argv[]);

//                                                                                  
//                                   Integration                             
//                                                                                  
int Integration(int argc, char *argv[]);

//                                                                                 
//                                  Input(“r’†‚©‚ç)@@@@@@@
//                                                                                
//int Input(int argc, char *argv[]);

//                                                                                  
//                                     LEGO                                     
//                                                                                  
int Building(int argc, char *argv[]);

//                                                                                  
//                                Run OpenGL                              
//                                                                                  
void RunOpenGL(int argc, char *argv[]);		//Shape From Silhouette
void RunOpenGLDown(int argc, char *argv[]);		//Principal Analysi Component
void RunOpenGL1(int argc, char *argv[]);		//Principal Analysi Component
void RunOpenGL2(int argc, char *argv[]);		//Iterative Closest Point
void RunOpenGL3(int argc, char *argv[]);		//Voxel Integration
void RunOpenGL4(int argc, char *argv[]);		//Voxel Integration

void RunOpenGL_Check(int argc, char *argv[]);