//############################################################################

#include "../stdafx.h"
#include "OpenGL.h"
#include "OpenGLprimitive.h"
#include "OpenGLWindow0.h"

using namespace std;

extern int WinID[5];
OpenGL GLSettings1;
extern int RtNum;


extern Model UP;
extern Model DOWN;
extern CMatrix *Rt;


void DisplayInit();
void DisplayPostprocessor();
void writefile(int format, int sort, int options, int nbcol, char *filename, char *extension, int winid, OpenGL GLSettings);
void writebmpfile(char *filename, char *extension, int winid);
void OpenGLIdle();
void OpenGLReshape(int width, int height);
void OpenGLInitialize(int WindowID, OpenGL GLSettings, int InitPosiX, int InitPosiY, int WindowWidth, int WindowHeight, char* WindowName);
void OpenGLPostprocessor(OpenGL GLSettings);
void PickUpInit(int x, int y);
void PickUpPostprocessor(void);
int SelectHits(GLuint hits, GLuint* buf, int hit_name[2]);
double ReturnDepth(int x, int y);

//
void ConclusiveAxis(void);
void DrawWireVoxelModel(vector<Voxel>& m);
void Draw_RotateVoxel(vector<Voxel>& m, CMatrix &Rt, double *color);
void DrawFaceVoxelModel(vector<Voxel>& m);

//PCA
void DrawWireOctree_PCA(Voxel& box);
void DrawFaceOctree_PCA(Voxel& box);
//void DrawWireVoxelModel_PCA(vector<Voxel>& m, int colorID);
//void DrawTeapot(vector<CVector3d> Position);

void DrawAxis();

//spin image
void DrawSpinImageOfUpLattice();
void DrawSpinImageOfUp(int ImageNum);

//2-D points
void Draw2DpointsLattice();
void Draw2Dpoints(int ImageNum);

//
extern vector<CVector3d> Teapots;
int SpinImageNum(0);

bool AF(true);
bool SI(true);
bool AB(true);
bool UF(true);
bool DF(true); 
bool Down_Origin(false); 

bool SurfOctrees(true);
bool Center_Octree(true);

bool CenterOctree(true);
bool OriginOctree(true);
bool PeakOctree(true);

extern vector<CVector3d> UPsurf;
extern vector<CVector3d> DOWNsurf;

void DrawVoxelCenter(vector<CVector3d> &m, int colorID);
void DrawVoxelCenter(vector<CVector3d> &m, CMatrix &Rt, int colorID);

void Draw_Center_Octree(Model& m);
void Draw_peak_octrees(Model& m);
void Draw_origin_octrees(Model& m);

void DrawWire_BoundingBox_UP(OctVoxel &box);


/***************************************************/
extern vector<CVector3d> up_octree_surf;

/***************************************************/
extern CVector3d BBox_Origin;
void OpenGLDisplay1(void){
	DisplayInit();	//ëOèàóù
	GLSettings1.SetEyePosition();

	//-----------------------------------------------------//
	if (AF)	{
		ConclusiveAxis();					//DrawAxis();
		DrawWire_BoundingBox_UP(UpBoundingBox);
	}

	if (UF){
		DrawWireVoxelModel(UP.SurfVoxels);
		DrawFaceVoxelModel(UP.SurfVoxels);

		DrawAllow(DOWN.CoV, DOWN.PrAxix[0], 70, 0.8);
		DrawAllow(DOWN.CoV, DOWN.PrAxix[1], 70, 0.8);
		DrawAllow(DOWN.CoV, DOWN.PrAxix[2], 70, 0.8);
	}

	if (Down_Origin){

		DrawWireVoxelModel(DOWN.SurfVoxels);
		DrawFaceVoxelModel(DOWN.SurfVoxels);

	}

	if (SI){
		DrawVoxelCenter(UPsurf, 35);
		DrawAllow(UP.CoV, UP.PrAxix[0], 80, 1);
		DrawAllow(UP.CoV, UP.PrAxix[1], 80, 1);
		DrawAllow(UP.CoV, UP.PrAxix[2], 80, 1);
	}

	double color[3];
	color[0] = 1.0; color[1] = 0.5; color[2] = 0.0;
	if (DF){
		Draw_RotateVoxel(DOWN.SurfVoxels, Rt[RtNum], color);
		DrawVoxelCenter(DOWNsurf, Rt[RtNum], 60);   //voxel center
		

	}
//	//_________________Octrees_______________________//
//
//	if (SurfOctrees){
//		DrawWireVoxelModel(UP.SurfOctrees);	//keyboard b
//		DrawFaceVoxelModel(UP.SurfOctrees);
//	}
//	if (Center_Octree){		
//		DrawVoxelCenter(up_octree_surf, 75);	//keyboard v
//	}
//
//	if (CenterOctree){
//		Draw_Center_Octree(UP);		//keyboard m
//	}
//
//	if (OriginOctree){
//		Draw_origin_octrees(UP); 	//keyboard n
//	}
//	
//	/********************************/
//	if (PeakOctree){
//		Draw_peak_octrees(UP); 	//keyboard n
//	}



	DisplayPostprocessor();
}


/***************************************************/

void OpenGLKeyboard1(unsigned char Key, int x, int y){

	switch (Key){
	case '\x1b':	//Esc
		std::cout << "Exit OpenGL System" << std::endl;
		glutLeaveMainLoop();
		break;
	case '\x0d':	//Enter
		break;

	case '\x20':	//Space
		break;

	case '\x7f':	//Delete
		break;

	case '\x08':	//BackSpace
		break;

	case '\t':		//TAB
		break;

		//case '+':	//ç¿ïWé≤
		//	SpinImageNum = SpinImageNum+1;
		//	break;
		//
		//case '-':	//ç¿ïWé≤
		//	if(SpinImageNum > 0)
		//		SpinImageNum = (SpinImageNum-1);
		//	break;	

	case '+':	//ç¿ïWé≤2
		RtNum = (RtNum + 1) % 4;
		break;

	case '-':	//ç¿ïWé≤
		if (RtNum > 0)
			RtNum--;
		break;

	case '2':	//ÉøÇ∆É¿ÇÃÇQÅ|ÇcpointsâÊëú
		SI = !SI;
		break;

	case '3':	//spint image
		AB = !AB;
		break; 
	case '4':	//spint image
		Down_Origin = !Down_Origin;
		break;
	case 'm':
		CenterOctree = !CenterOctree;
		break;
	case 'n':
		OriginOctree = !OriginOctree;
		break;
	case 'v':
		Center_Octree = !Center_Octree;
		break;
	case 'b':
		SurfOctrees = !SurfOctrees;
		break;
	case 'p':
		PeakOctree = !PeakOctree;
		break;

	case 'x':
		AF = !AF;
		break;
	case 'u':
		UF = !UF;
		break;

	case 'd':
		DF = !DF;
		break;

	case '1':	//éãì_êÿë÷
		GLSettings1.m_EyeDis = 20;
		GLSettings1.m_Center.Clear();
		GLSettings1.m_Front.Set(0.0, 0.0, -1.0);
		GLSettings1.m_Upper.Set(0.0, 1.0, 0.0);
		break;

	case '@':	//ï`âÊèoóÕ
		writefile(GL2PS_EPS, GL2PS_SMPLE_SORT, GL2PS_DRAW_BACKGROUND, 0, "Window1", "eps", WinID[1], GLSettings1);
		writefile(GL2PS_SVG, GL2PS_SMPLE_SORT, GL2PS_DRAW_BACKGROUND, 0, "Window1", "svg", WinID[1], GLSettings1);
		writebmpfile("Window1", "bmp", WinID[1]);

		printf("GL2PS %d.%d.%d done with all images\n",
			GL2PS_MAJOR_VERSION, GL2PS_MINOR_VERSION, GL2PS_PATCH_VERSION);
		break;
	}

	glutPostRedisplay();
}


/***************************************************/
/***************************************************/
void OpenGLSpecial1(int Key, int x, int y){
	switch (Key){

	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;

	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;

	case GLUT_KEY_PAGE_UP:
		break;
	case GLUT_KEY_PAGE_DOWN:
		break;
	}
	glutPostRedisplay();
}

/***************************************************/
/***************************************************/
int PickUp1(int x, int y, int hit_name[2], int Button){
	GLint hits;
	GLuint selectBuf[BUFSIZE];
	glSelectBuffer(BUFSIZE, selectBuf);

	PickUpInit(x, y);
	GLSettings1.SetEyePosition();

	PickUpPostprocessor();

	hits = glRenderMode(GL_RENDER);

	return SelectHits(hits, selectBuf, hit_name);
}

/***************************************************/

void PickObject1(int x, int y, int Button){
	int hit_name[2];

	if (PickUp1(x, y, hit_name, Button) == -1){
		GLSettings1.ObjectPosition = new CVector3d;
		return;
	}
	GLSettings1.m_ObjectDepth = ReturnDepth(x, y);

	if (GLSettings1.m_ObjectDepth > -1.0 && GLSettings1.m_ObjectDepth < 1.0){

	}
}

/***************************************************/
void OpenGLMouse1(int Button, int State, int x, int y){
	GLSettings1.Tracking(Button, State, x, y);
}
/***************************************************/
void OpenGLMotion1(int x, int y){
	GLSettings1.MovingMouse(x, y);
}

/***************************************************/
void OpenGLMouseWheel1(int wheel_number, int direction, int x, int y){
	GLSettings1.DoMouseWheel(direction);
};

/***************************************************/
void OpenGLReshape1(int width, int height){
	GLSettings1.m_Aspect = static_cast<double>(width) / static_cast<double>(height);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(10.0, GLSettings1.m_Aspect, 0.01, -1.0);
	glMatrixMode(GL_MODELVIEW);
}



/***************************************************/

void OpenGLCallBack1(void){
	GLSettings1.PickObject = PickObject1;
	OpenGLInitialize(1, GLSettings1, 0, 0, 600, 600, "Window1");
	glutDisplayFunc(OpenGLDisplay1);
	glutReshapeFunc(OpenGLReshape1);
	glutMouseFunc(OpenGLMouse1);
	glutMotionFunc(OpenGLMotion1);
	glutMouseWheelFunc(OpenGLMouseWheel1);
	glutKeyboardFunc(OpenGLKeyboard1);
	glutSpecialFunc(OpenGLSpecial1);
	glutIdleFunc(OpenGLIdle);
	OpenGLPostprocessor(GLSettings1);
}