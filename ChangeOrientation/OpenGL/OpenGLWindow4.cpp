#include "../stdafx.h"
#include "OpenGL.h"
#include "OpenGLprimitive.h"
#include "../Lego.h"

using namespace std;

extern int WinID[5]; //ウィンドウID
OpenGL GLSettings4;	//窓5の設定

extern int CrossSectionNum;
int xx(1);
int yy(1);
int zz(1);

extern Model Integ;
extern Lego*** block;


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


//関数プロトタイプ宣言
void DrawGrid(Model& m, int Znum);
void DrawSurfSquare(Model& m, Lego*** block, int Znum);
void DrawBuildingInstruction(Model& m, Lego*** block, int Znum);

void DrawBlocks_3D(Model& m, Lego*** block, int Znum);		//ある断面のブロックを描画
void DrawBlockModel(Model& m, Lego*** block);						//ブロックで構成されているモデル
void DrawBlockModel_half(Model& m, Lego*** block, int Znum);
//void DrawBuildingInstruction_3D(Model& m, Lego*** block, int Znum);
void DrawGrid_GCAD(Model& m, int Znum);
void DrawWireVoxel_GCAD(Model& m);
void DrawVoxel_GCAD(Model& m, int xx, int yy, int zz);
void DrawSolid_GACD(Model& integ, int );

bool flag2(true);
bool flag3(true);
bool flag4(true);
bool flag5(true);
bool flag6(true);
bool flag7(true);
bool r(false);


/***************************************************/
/***************************************************/

void OpenGLDisplay4(void){
	DisplayInit();	//前処理
	GLSettings4.SetEyePosition();		//視線回転
	/********************************/
	/********************************/
	if(flag2)
		DrawSurfSquare(Integ, block, CrossSectionNum);
	if(flag3)
		DrawGrid(Integ, CrossSectionNum);
	if(flag4)
		DrawBuildingInstruction(Integ, block, CrossSectionNum);
	if(flag5)
		DrawBlocks_3D(Integ, block, CrossSectionNum);
	if(flag6)
		DrawBlockModel(Integ, block);
	if(flag7)
		DrawBlockModel_half(Integ, block, CrossSectionNum);
	
	//2013/10/11
	//DrawGrid_GCAD(Integ, CrossSectionNum);
	//DrawWireVoxel_GCAD(Integ);

	////2013/10/15
	//DrawVoxel_GCAD(Integ, xx, yy, zz);
	//DrawSolid_GACD(Integ,CrossSectionNum);

	/********************************/
	DisplayPostprocessor();	
}
void idle(void)
{
	//DrawBlockModel(Integ, block);
	glutPostRedisplay();
}


void OpenGLKeyboard4( unsigned char Key, int x, int y ){
	
	switch( Key ){
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

	case 'x':
		if(xx < Integ.num[0]-2)
			xx = xx+1;
		else
			xx = 1;
		break;

	case 'y':
		if(yy < Integ.num[1]-2)
			yy = yy+1;
		else
			yy = 1;
		break;

	case 'z':
		if(zz < Integ.num[2]-2)
			zz = zz+1;
		else
			zz = 1;
		break;

	case 'p':
		cout<<"m_EyeDis:"<<GLSettings4.m_EyeDis<<endl;
		cout<<"m_Center:"<<GLSettings4.m_Center.x<<" "<<GLSettings4.m_Center.y<<" "<<GLSettings4.m_Center.z<<endl;
		cout<<"m_Front:"<<GLSettings4.m_Front.x<<" "<<GLSettings4.m_Front.y<<" "<<GLSettings4.m_Front.z<<endl;
		cout<<"m_Upper:"<<GLSettings4.m_Upper.x<<" "<<GLSettings4.m_Upper.y<<" "<<GLSettings4.m_Upper.z<<" "<<endl;
		break;

			
	case 'l':	//視点切替
		GLSettings4.m_EyeDis = 469.796;
		GLSettings4.m_Center.Set(69.7162, 26.5907, 43.3602);
		GLSettings4.m_Front.Set(0.675699, -0.694145, 0.248181);
		GLSettings4.m_Upper.Set(0.146707, -0.203307, -0.968062);
		break;

	case '+':	//座標軸
		if(CrossSectionNum < Integ.num[2]-2)
			CrossSectionNum = CrossSectionNum+1;
		else
			CrossSectionNum = 1;
		break;

	case '-':	//座標軸
		if(CrossSectionNum > 1)
			CrossSectionNum = (CrossSectionNum-1);
		else
			CrossSectionNum = Integ.num[2]-2;
		break;
	
	case '1':	//視点切替
		GLSettings4.m_EyeDis = 100;
		GLSettings4.m_Center.Clear();
		GLSettings4.m_Front.Set(0.0, 0.0, 1.0);
		GLSettings4.m_Upper.Set(0.0, 1.0, 0.0);
		break;

	case '2':
		flag2 = !flag2;
		break;

	case '3':
		flag3 = !flag3;
		break;

	case '4':
		flag4 = !flag4;
		break;

	case '5':
		flag5 = !flag5;
		break;

	case '6':
		flag6 = !flag6;
		break;

	case '7':
		flag7 = !flag7;
		break;
	case 'r':
		r = !r;
		if (r) {
			glutIdleFunc(idle);
		}
		else {
			glutIdleFunc(0);
		}
		break;
	case 'c':
		char figureName[20];
		sprintf(figureName,"Crossection%d", CrossSectionNum);
		writebmpfile( figureName, "bmp", 3);
		if(CrossSectionNum < Integ.num[2]-2)
			CrossSectionNum++;
		else
			CrossSectionNum = 1;
		break;

	case '@':	//描画出力
		writefile(GL2PS_EPS, GL2PS_SMPLE_SORT, GL2PS_DRAW_BACKGROUND, 0, "Window4", "eps", 3, GLSettings4);
		writefile(GL2PS_SVG, GL2PS_SMPLE_SORT, GL2PS_DRAW_BACKGROUND, 0, "Window4", "svg", 3, GLSettings4);
		writebmpfile("Window4", "bmp", 3);
		printf("GL2PS %d.%d.%d done with all images\n",
			GL2PS_MAJOR_VERSION, GL2PS_MINOR_VERSION, GL2PS_PATCH_VERSION);
		break;
	}

	glutPostRedisplay();
}


/***************************************************/
/***************************************************/
void OpenGLSpecial4( int Key, int x, int y ){
	switch(Key){

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
int PickUp4( int x, int y, int hit_name[2], int Button ){
	GLint hits;
	GLuint selectBuf[BUFSIZE];
	glSelectBuffer(BUFSIZE, selectBuf);

	PickUpInit(x,y);		//ピックアップ前処理
	GLSettings4.SetEyePosition();		//視線回転
	/************************************/

	PickUpPostprocessor();		//ピックアップ後処理

	hits = glRenderMode(GL_RENDER);		//ヒットした物体の個数

	return SelectHits(hits,selectBuf,hit_name);
}


void PickObject4( int x, int y, int Button ){
	int hit_name[2];	//ヒットした物体のid番号

	if( PickUp4(x,y,hit_name,Button) == -1 ){
		GLSettings4.ObjectPosition = new CVector3d;
		return;
	}

	GLSettings4.m_ObjectDepth = ReturnDepth(x,y);



	//hit_name[0] = -1;
	//hit_name[1] = -1;
	if( GLSettings4.m_ObjectDepth > -1.0 && GLSettings4.m_ObjectDepth < 1.0 ){
	
	}
}


/***************************************************/
/***************************************************/
void OpenGLMouse4( int Button, int State, int x, int y ){
	GLSettings4.Tracking( Button, State, x, y );
}
/***************************************************/
/***************************************************/
void OpenGLMotion4( int x, int y ){
	GLSettings4.MovingMouse( x, y );
}

/***************************************************/
/***************************************************/
void OpenGLMouseWheel4(int wheel_number, int direction, int x, int y){
	GLSettings4.DoMouseWheel(direction);
};

/***************************************************/
/***************************************************/
void OpenGLReshape4( int width, int height ){
	GLSettings4.m_Aspect = static_cast<double>(width) / static_cast<double>(height);
	glViewport( 0, 0, width, height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 10.0, GLSettings4.m_Aspect, 0.01, -1.0 );
	glMatrixMode( GL_MODELVIEW );
}



/***************************************************/
/***************************************************/
void OpenGLCallBack4(void){
	GLSettings4.PickObject = PickObject4;	
	OpenGLInitialize(4, GLSettings4, 0, 0, 600, 600, "Window4");	
	glutDisplayFunc	( OpenGLDisplay4 );		
	glutReshapeFunc	( OpenGLReshape4 );		
	glutMouseFunc   ( OpenGLMouse4 );		
	glutMotionFunc  ( OpenGLMotion4 );		
	glutMouseWheelFunc( OpenGLMouseWheel4 );
	glutKeyboardFunc( OpenGLKeyboard4 );	
	glutSpecialFunc	( OpenGLSpecial4 );		
	glutIdleFunc( OpenGLIdle );				
	OpenGLPostprocessor(GLSettings4);		
}