#ifndef ___OPENGLWINDOW0_H_
#define ___OPENGLWINDOW0_H_

//#include "glui.h"
#include "../stdafx.h"
#include "OpenGL.h"
#include "OpenGLprimitive.h"


//Function prototype declaration
void DisplayInit();
void DisplayPostprocessor();
void writefile(int format, int sort, int options, int nbcol,char *filename, char *extension, int winid, OpenGL GLSettings);
void writebmpfile(char *filename, char *extension, int winid);
void OpenGLIdle();
void OpenGLReshape( int width, int height );
void OpenGLInitialize(int WindowID, OpenGL GLSettings, int InitPosiX, int InitPosiY, int WindowWidth, int WindowHeight, char* WindowName);
void OpenGLPostprocessor(OpenGL GLSettings);
void PickUpInit(int x, int y);
void PickUpPostprocessor(void);
int SelectHits( GLuint hits, GLuint* buf, int hit_name[2] );
double ReturnDepth( int x, int y );


//Drawing function
void DrawBoundingbox(CVector3d MaxPt,CVector3d MinPt);
void ConclusiveAxis(void);
//void DrawInitalPosition(Solid &M);
//void SelectPoint(Solid &M, int Pnum);

//SFS
void DrawWireOctree_SFS_UP(OctVoxel &box);
void DrawWireOctreeModel_SFS_UP(vector<OctVoxel>& Octree);
void DrawFaceOctreeModel_SFS_UP(vector<OctVoxel>& Octree);

void DrawWireOctree_SFS_DOWN(OctVoxel &box);
void DrawWireOctreeModel_SFS_DOWN(vector<OctVoxel>& Octree);
void DrawFaceOctreeModel_SFS_DOWN(vector<OctVoxel>& Octree);

//Octree
void DrawWireOctree(OctVoxel &box, int colorID);
void DrawWireOctreeModel( vector<OctVoxel>& Octree ,int colorID);
void DrawFaceOctreeModel( vector<OctVoxel>& Octree ,int colorID);

//16/5/9 save octrees
void Draw_Plane_Octree(Model& m);
void Draw_Boundary_Octree(Model& m);

//Object
//extern Solid InitM;
extern Model UP;		
extern Model DOWN;		

extern OctVoxel UpBoundingBox;			//UP model bounding box
extern OctVoxel DownBoundingBox;		//DOWN model bounding box

extern vector<cv::Point3f> vertex;

extern int picknum;

//extern Octree UP;
//void Box(Octree UP);
//void ver(vector<Point3f> vertex);

#endif
