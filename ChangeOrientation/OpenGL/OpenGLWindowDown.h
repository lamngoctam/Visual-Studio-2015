//#ifndef ___OPENGLWINDOWDOWN_H_
//#define ___OPENGLWINDOWDOWN_H_
//
//#include "glui.h"
//#include "../stdafx.h"
//#include "OpenGL.h"
//#include "OpenGLprimitive.h"
//
//
//関数のプロトタイプ宣言
//void DisplayInit();
//void DisplayPostprocessor();
//void writefile(int format, int sort, int options, int nbcol,char *filename, char *extension, int winid, OpenGL GLSettings);
//void writebmpfile(char *filename, char *extension, int winid);
//void OpenGLIdle();
//void OpenGLReshape( int width, int height );
//void OpenGLInitialize(int WindowID, OpenGL GLSettings, int InitPosiX, int InitPosiY, int WindowWidth, int WindowHeight, char* WindowName);
//void OpenGLPostprocessor(OpenGL GLSettings);
//void PickUpInit(int x, int y);
//void PickUpPostprocessor(void);
//int SelectHits( GLuint hits, GLuint* buf, int hit_name[2] );
//double ReturnDepth( int x, int y );
//
//
//描画関数
//void DrawBoundingbox(CVector3d MaxPt,CVector3d MinPt);
//void ConclusiveAxis(void);
//void DrawInitalPosition(Solid &M);
//void SelectPoint(Solid &M, int Pnum);
//
//Octree
//void DrawWireOctree(OctVoxel box, int colorID);
//void DrawWireOctreeModel( vector<OctVoxel>& Octree ,int colorID);
//void DrawFaceOctreeModel( vector<OctVoxel>& Octree ,int colorID);
//
//Voxel
//void DrawWireVoxelModel(vector<Voxel>& m,int colorID);
//void DrawSolidVoxelModel(vector<Voxel>& m,int colorID);
//
//
//Object
//extern Solid InitM;
//extern Model UP;		//UPのモデル
//extern Model DOWN;		//DOWNのモデル
//
//extern OctVoxel UpBoundingBox;			//UP bb
//extern OctVoxel DownBoundingBox;		//UPモデルのバウンディングボックス
//
//extern vector<cv::Point3f> vertex;
//
//extern int picknum;
//
//extern Octree UP;
//void Box(Octree UP);
//void ver(vector<Point3f> vertex);
//
//#endif