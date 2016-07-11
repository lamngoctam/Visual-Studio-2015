#include "../stdafx.h"
#include "OpenGL.h"
#include "OpenGLprimitive.h"
using namespace std;

extern int WinID[5]; //ID
OpenGL GLSettings3;	//

extern Model UP;
extern Model DOWN;
extern Model Integ;

extern CMatrix SIMatrix;
extern CMatrix ICPMatrix;
extern CVector3d* CameraPosUp;
extern CVector3d* CameraPosDown;

//extern Lego*** block;

//
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

//----------
float BackTopColor[] = { 0.941f, 1.0f, 1.0f };
float BackBotColor[] = { 0.275f, 0.51f, 0.706f };
void GradientBackGround(float *tcolor, float *bcolor);


//描画関数
void ConclusiveAxis(void);
//void DrawUnitNormal(Model& m,int colorID);
void DrawCorre(vector<CVector3d> &up, vector<CVector3d> &down);
void DrawVoxelCenter(vector<CVector3d> &m, int colorID);
//void Drawbox(CVector3d min, CVector3d max);

void DrawColorSolidModel(Model&);
void DrawSolidVoxelModel(vector<Voxel>& m, int colorID);
void DrawCameraPosition(CVector3d* pos);
void DrawIsoVoxels(Model& integ);
void Drawline(Model& integ, int num);

void DrawBoundingbox(CVector3d MaxPt, CVector3d MinPt);
void DrawFaceOctreeModel(vector<OctVoxel>& Octree, int colorID);
void DrawWireOctreeModel(vector<OctVoxel>& Octree, int colorID);
//flag
bool upF(false);
bool downF(false);
bool IntegF(true);
int num = 0;

/***************************************************/
extern vector<CVector3d> origin1;
extern vector<CVector3d> temp_vertexW;


void OpenGLDisplay3(void) {
	DisplayInit();

	GradientBackGround(BackTopColor, BackBotColor);
	GLSettings3.SetEyePosition();
	
	ConclusiveAxis();
	
	if (upF)  //keyboard 2
		DrawSolidVoxelModel(UP.SurfVoxels, 6);
		
	if (downF) //3
		DrawSolidVoxelModel(DOWN.SurfVoxels, 87);

	if (IntegF) {//4
		DrawColorSolidModel(Integ);
		//DrawSolidVoxelModel(Integ.SurfVoxels, 87);
		DrawIsoVoxels(Integ);          //draw the Eliminate voxels
	}

	//DrawCameraPosition(CameraPosUp);
	//DrawCameraPosition(CameraPosDown);
	//Drawline(Integ, num);
	



//	DrawSolidVoxelModel(Integ.SurfVoxels, 6);

	glPointSize(8);
	glColor3d(0.5, 1.0, 0.5);
	glBegin(GL_POINTS);
	for (auto i(0); i < temp_vertexW.size(); ++i) {
		//glVertex3d(temp_vertexW[i].x, temp_vertexW[i].y, temp_vertexW[i].z);
	}
	glEnd();




	DisplayPostprocessor();
}


void OpenGLKeyboard3(unsigned char Key, int x, int y) {

	switch (Key) {
	case '\x1b':	//Esc
		std::cout << "Exit OpenGL System" << std::endl;
		glutLeaveMainLoop();		//OpenGL
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

	case '1':	//視点切替
		GLSettings3.m_EyeDis = 20;
		GLSettings3.m_Center.Clear();
		GLSettings3.m_Front.Set(0.0, 0.0, -1.0);
		GLSettings3.m_Upper.Set(0.0, 1.0, 0.0);
		break;
	case '2':	//UPモデル
		upF = !upF;
		break;

	case '3':	//DOWNモデル
		downF = !downF;
		break;

	case '4':	//統合モデル
		IntegF = !IntegF;
		break;

	case '5':
		cout << GLSettings3.m_EyeDis << endl;
		cout << GLSettings3.m_Center.x << " " << GLSettings3.m_Center.y << " " << GLSettings3.m_Center.z << endl;
		cout << GLSettings3.m_Front.x << " " << GLSettings3.m_Front.y << " " << GLSettings3.m_Front.z << endl;
		cout << GLSettings3.m_Upper.x << " " << GLSettings3.m_Upper.y << " " << GLSettings3.m_Upper.z << endl;
		break;

	case '6':	//視点切替
		GLSettings3.m_EyeDis = 405.569;
		GLSettings3.m_Center.Set(12.8757, 18.5644, 29.6544);
		GLSettings3.m_Front.Set(-0.167235, 0.0270888, -0.985545);
		GLSettings3.m_Upper.Set(0.864818, -0.475966, -0.159831);
		break;

	case '+':
		num = num + 1;
		break;
	case '-':
		num = num - 1;
		break;

	case '@':	//描画出力
		writefile(GL2PS_EPS, GL2PS_SMPLE_SORT, GL2PS_DRAW_BACKGROUND, 0, "Window3", "eps", 3, GLSettings3);
		writefile(GL2PS_SVG, GL2PS_SMPLE_SORT, GL2PS_DRAW_BACKGROUND, 0, "Window3", "svg", 3, GLSettings3);
		writebmpfile("Window3", "bmp", 3);

		printf("GL2PS %d.%d.%d done with all images\n",
			GL2PS_MAJOR_VERSION, GL2PS_MINOR_VERSION, GL2PS_PATCH_VERSION);
		break;
	}

	glutPostRedisplay();
}


/***************************************************/
/*			　　OpenGLカーソルキー	　　	　　   */
/***************************************************/
void OpenGLSpecial3(int Key, int x, int y) {
	switch (Key) {

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
/*			　　選択可能物体の設置	　　	　　   */
/***************************************************/
int PickUp3(int x, int y, int hit_name[2], int Button) {
	GLint hits;
	GLuint selectBuf[BUFSIZE];
	glSelectBuffer(BUFSIZE, selectBuf);

	PickUpInit(x, y);		//ピックアップ前処理
	GLSettings3.SetEyePosition();		//視線回転
	/************************************/
	/*			物体設置ここから		*/
	/************************************/


	/************************************/
	/*			物体設置ここまで		*/
	/************************************/
	PickUpPostprocessor();		//ピックアップ後処理

	hits = glRenderMode(GL_RENDER);		//ヒットした物体の個数

	//設置物体の中から、深さが浅いもの（手前に設置されているもの）のidを取得
	return SelectHits(hits, selectBuf, hit_name);
}


/***************************************************/
/*			　　	物体の選択		　　	　　   */
/***************************************************/
void PickObject3(int x, int y, int Button) {
	int hit_name[2];

	if (PickUp3(x, y, hit_name, Button) == -1) {
		GLSettings3.ObjectPosition = new CVector3d;
		return;
	}

	GLSettings3.m_ObjectDepth = ReturnDepth(x, y);

	/************************************/
	if (GLSettings3.m_ObjectDepth > -1.0 && GLSettings3.m_ObjectDepth < 1.0) {

	}
}


/***************************************************/
/*			　　OpenGLマウス関数	　　	　　   */
/***************************************************/
void OpenGLMouse3(int Button, int State, int x, int y) {
	GLSettings3.Tracking(Button, State, x, y);
}
/***************************************************/
/*			　　OpenGLモーション関数　　	　　   */
/***************************************************/
//Callback関数なため、ウインドウ毎に関数が必要
void OpenGLMotion3(int x, int y) {
	GLSettings3.MovingMouse(x, y);
}

/***************************************************/
/*					マウスホイール	　　	　　   */
/***************************************************/
void OpenGLMouseWheel3(int wheel_number, int direction, int x, int y) {
	GLSettings3.DoMouseWheel(direction);
};

/***************************************************/
/*			　　OpenGLリサイズ関数	　　	　　   */
/***************************************************/
void OpenGLReshape3(int width, int height) {
	GLSettings3.m_Aspect = static_cast<double>(width) / static_cast<double>(height);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(10.0, GLSettings3.m_Aspect, 0.01, -1.0);
	glMatrixMode(GL_MODELVIEW);
}



/***************************************************/
/*	　　　	　　   */
/***************************************************/
void OpenGLCallBack3(void) {
	GLSettings3.PickObject = PickObject3;
	OpenGLInitialize(3, GLSettings3, 0, 0, 600, 600, "Window3");
	glutDisplayFunc(OpenGLDisplay3);
	glutReshapeFunc(OpenGLReshape3);
	glutMouseFunc(OpenGLMouse3);
	glutMotionFunc(OpenGLMotion3);
	glutMouseWheelFunc(OpenGLMouseWheel3);
	glutKeyboardFunc(OpenGLKeyboard3);
	glutSpecialFunc(OpenGLSpecial3);
	glutIdleFunc(OpenGLIdle);
	OpenGLPostprocessor(GLSettings3);
}