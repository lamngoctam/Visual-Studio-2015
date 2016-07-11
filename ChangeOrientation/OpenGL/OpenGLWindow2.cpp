#include "../stdafx.h"
#include "OpenGL.h"
#include "OpenGLprimitive.h"
using namespace std;

extern int WinID[5]; //ウィンドウID
OpenGL GLSettings2;	//窓2の設定

extern Model UP;
extern Model DOWN;

extern CMatrix SIMatrix;
extern CMatrix ICPMatrix;
extern CMatrix PCAMatrix;
extern CMatrix TMatrix;
int Upicknum = 0;
int Dpicknum = 0;

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

//
void ConclusiveAxis(void);
void DrawUnitNormal(vector<Voxel>& m, int colorID);
void DrawCorre(vector<CVector3d> &up, vector<CVector3d> &down);
void DrawVoxelCenter(vector<CVector3d> &m, int colorID);
void DrawWireVoxelModel(vector<Voxel>& m, int colorID);
void DrawDown_After_Matrix(vector<Voxel>& m, int colorID, CMatrix& A);
void DrawSolidVoxelModel(vector<Voxel>& m, int colorID);


bool UPF(true);			//UP
bool DOWNF(false);		//DOWN
bool DOWNFSI(false);	//
bool DOWNFICP(true);	//ICP

/***************************************************/
extern vector<CVector3d> UPsurf_ICP;
extern vector<CVector3d> DOWNsurf_ICP;

/***************************************************/
//
void OpenGLDisplay2(void){
	DisplayInit();	//
	GLSettings2.SetEyePosition();
	/********************************/

	//	//
	if (UPF){
		DrawSolidVoxelModel(UP.SurfVoxels, 6);
		//DrawWireVoxelModel(UP.SurfVoxels, 6);
		//DrawUnitNormal(UP.SurfVoxels,31);
	}
	if (DOWNF){
		DrawSolidVoxelModel(DOWN.SurfVoxels, 87);
		//DrawWireVoxelModel(DOWN.SurfVoxels, 87);
		//DrawUnitNormal(DOWN.SurfVoxels,31);
	}
	if (DOWNFSI)
	{
		//DrawDown_After_Matrix(DOWN.SurfVoxels, 62 ,SIMatrix);
		DrawDown_After_Matrix(DOWN.SurfVoxels, 62, PCAMatrix);
	}
	if (DOWNFICP)
	{
		DrawDown_After_Matrix(DOWN.SurfVoxels, 64, ICPMatrix);
	}
	//

	ConclusiveAxis();

	DrawVoxelCenter(UPsurf_ICP, 20);	//UP
	DrawVoxelCenter(DOWNsurf_ICP, 80);	//DOWN


	//DrawCorre(UPcorres, DOWNcorres);	

	/********************************/

	/********************************/
	DisplayPostprocessor();	//後処理
}


void OpenGLKeyboard2(unsigned char Key, int x, int y){

	switch (Key){
	case '\x1b':	//Esc
		std::cout << "Exit OpenGL System" << std::endl;
		glutLeaveMainLoop();		//OpenGLが終了し、main関数へ戻る
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

	case '2':		//UP
		UPF = !UPF;
		break;

	case '3':		//DOWN
		DOWNF = !DOWNF;
		break;

	case '4':		//DOWN (PCA)
		DOWNFSI = !DOWNFSI;
		break;

	case '5':		//DOWN (ICP)
		DOWNFICP = !DOWNFICP;
		break;

		//---------------------
		//--------------------
	case 'x':		//x
		TMatrix.SetZero();
		TMatrix[0][3] = 1.0;
		ICPMatrix = ICPMatrix + TMatrix;
		//TMatrix.SetZero();
		break;
	case 'X':		//x方向に並進
		TMatrix.SetZero();
		TMatrix[0][3] = -1.0;
		ICPMatrix = ICPMatrix + TMatrix;
		//TMatrix.SetZero();
		break;
	case 'y':		//y方向に並進
		TMatrix.SetZero();
		TMatrix[1][3] = 1.0;
		ICPMatrix = ICPMatrix + TMatrix;
		//TMatrix.SetZero();
		break;
	case 'Y':		//y方向に並進
		TMatrix.SetZero();
		TMatrix[1][3] = -1.0;
		ICPMatrix = ICPMatrix + TMatrix;
		//TMatrix.SetZero();
		break;
	case 'z':		//z方向に並進
		TMatrix.SetZero();
		TMatrix[2][3] = 1.0;
		ICPMatrix = ICPMatrix + TMatrix;
		//TMatrix.SetZero();
		break;
	case 'Z':		//z方向に並進
		TMatrix.SetZero();
		TMatrix[2][3] = -1.0;
		ICPMatrix = ICPMatrix + TMatrix;
		//TMatrix.SetZero();
		break;
		//---------回転行列------------
	case 'q':		//z軸周りに回転
		TMatrix.SetRotate4d(0.01, 0.0, 0.0, 1.0);
		ICPMatrix = ICPMatrix*TMatrix;
		TMatrix.IdentifyMatrix();
		break;
	case 'w':		//z軸周りに回転
		TMatrix.SetRotate4d(-0.01, 0.0, 0.0, 1.0);
		ICPMatrix = ICPMatrix*TMatrix;
		TMatrix.IdentifyMatrix();
		break;
	case 'e':		//y軸周りに回転
		TMatrix.SetRotate4d(0.01, 0.0, 1.0, 0.0);
		ICPMatrix = ICPMatrix*TMatrix;
		TMatrix.IdentifyMatrix();
		break;
	case 'r':		//y軸周りに回転
		TMatrix.SetRotate4d(-0.01, 0.0, 1.0, 0.0);
		ICPMatrix = ICPMatrix*TMatrix;
		TMatrix.IdentifyMatrix();
		break;
	case 't':		//x軸周りに回転
		TMatrix.SetRotate4d(0.01, 1.0, 0.0, 0.0);
		ICPMatrix = ICPMatrix*TMatrix;
		TMatrix.IdentifyMatrix();
		break;
	case 'u':		//z軸周りに回転
		TMatrix.SetRotate4d(-0.01, 1.0, 0.0, 0.0);
		ICPMatrix = ICPMatrix*TMatrix;
		TMatrix.IdentifyMatrix();
		break;

		//--------------------------------------------

	case '1':	//視点切替
		GLSettings2.m_EyeDis = 1200;
		GLSettings2.m_Center.Clear();
		GLSettings2.m_Front.Set(0.0, 0.0, -1.0);
		GLSettings2.m_Upper.Set(0.0, 1.0, 0.0);
		break;

	case '@':	//描画出力
		writefile(GL2PS_EPS, GL2PS_SMPLE_SORT, GL2PS_DRAW_BACKGROUND, 0, "Window2", "eps", 2, GLSettings2);
		writefile(GL2PS_SVG, GL2PS_SMPLE_SORT, GL2PS_DRAW_BACKGROUND, 0, "Window2", "svg", 2, GLSettings2);
		writebmpfile("Window2", "bmp", 2);

		printf("GL2PS %d.%d.%d done with all images\n",
			GL2PS_MAJOR_VERSION, GL2PS_MINOR_VERSION, GL2PS_PATCH_VERSION);
		break;
	}

	glutPostRedisplay();
}


/***************************************************/
/*			＾penGL                                 */
/***************************************************/
void OpenGLSpecial2(int Key, int x, int y){
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
int PickUp2(int x, int y, int hit_name[2], int Button){
	GLint hits;
	GLuint selectBuf[BUFSIZE];
	glSelectBuffer(BUFSIZE, selectBuf);

	PickUpInit(x, y);		
	GLSettings2.SetEyePosition();		//視線回転
	/************************************/
	/************************************/
	if (UPF){
		glPushName(0);
		DrawSolidVoxelModel(UP.SurfVoxels, 6);
		glPopName();
	}
	if (DOWNFICP)
	{
		glPushName(1);
		DrawDown_After_Matrix(DOWN.SurfVoxels, 64, ICPMatrix);
		glPopName();
	}
	/************************************/
	/************************************/
	PickUpPostprocessor();	

	hits = glRenderMode(GL_RENDER);

	return SelectHits(hits, selectBuf, hit_name);
}


/***************************************************/
/***************************************************/
void PickObject2(int x, int y, int Button){
	int hit_name[2];	

	if (PickUp2(x, y, hit_name, Button) == -1){
		GLSettings2.ObjectPosition = new CVector3d;
		return;
	}

	GLSettings2.m_ObjectDepth = ReturnDepth(x, y);

	/************************************/
	/************************************/
	int cnt(0);
	if (hit_name[0] == 0)
	{
		cout << "Up " << Upicknum << " hitname       " << hit_name[1] << endl;
		UP.Pick[Upicknum].x = UP.SurfVoxels[hit_name[1]].center.x;
		UP.Pick[Upicknum].y = UP.SurfVoxels[hit_name[1]].center.y;
		UP.Pick[Upicknum].z = UP.SurfVoxels[hit_name[1]].center.z;
		UP.SurfVoxels[hit_name[1]].pic = true;
		Upicknum++;
		Upicknum = Upicknum % 5;
	}
	else if (hit_name[0] == 1)
	{
		cout << "DOWN" << Dpicknum << " hitname       " << hit_name[1] << endl;
		DOWN.Pick[Dpicknum].x = DOWN.SurfVoxels[hit_name[1]].center.x;
		DOWN.Pick[Dpicknum].y = DOWN.SurfVoxels[hit_name[1]].center.y;
		DOWN.Pick[Dpicknum].z = DOWN.SurfVoxels[hit_name[1]].center.z;
		DOWN.SurfVoxels[hit_name[1]].pic = true;
		Dpicknum++;
		Dpicknum = Dpicknum % 5;
	}

	/************************************/
	/************************************/
	//hit_name[0] = -1;
	//hit_name[1] = -1;
	if (GLSettings2.m_ObjectDepth > -1.0 && GLSettings2.m_ObjectDepth < 1.0){

	}
}


/***************************************************/
/***************************************************/
void OpenGLMouse2(int Button, int State, int x, int y){
	GLSettings2.Tracking(Button, State, x, y);
}
/***************************************************/
/***************************************************/
void OpenGLMotion2(int x, int y){
	GLSettings2.MovingMouse(x, y);
}

/***************************************************/
/***************************************************/
void OpenGLMouseWheel2(int wheel_number, int direction, int x, int y){
	GLSettings2.DoMouseWheel(direction);
};

/***************************************************/
/***************************************************/
void OpenGLReshape2(int width, int height){
	GLSettings2.m_Aspect = static_cast<double>(width) / static_cast<double>(height);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(10.0, GLSettings2.m_Aspect, 0.01, -1.0);
	glMatrixMode(GL_MODELVIEW);
}



/***************************************************/
/***************************************************/
void OpenGLCallBack2(void){
	GLSettings2.PickObject = PickObject2;	//物体選択関数を関数ポインタに格納
	OpenGLInitialize(2, GLSettings2, 0, 0, 600, 600, "Window2");	//初期化
	glutDisplayFunc(OpenGLDisplay2);		//物体の描画
	glutReshapeFunc(OpenGLReshape2);		//窓サイズを変えたときに反応
	glutMouseFunc(OpenGLMouse2);		//マウスを押した瞬間と離した瞬間に反応
	glutMotionFunc(OpenGLMotion2);		//マウスをドラッグしたときに反応
	glutMouseWheelFunc(OpenGLMouseWheel2);//マウスホイールを転がしたときに反応
	glutKeyboardFunc(OpenGLKeyboard2);	//キーボードを押したときに反応
	glutSpecialFunc(OpenGLSpecial2);		//カーソルキーなどを押したときに反応
	glutIdleFunc(OpenGLIdle);				//何も操作していないときに反応（省略可能）
	OpenGLPostprocessor(GLSettings2);					//後処理
}