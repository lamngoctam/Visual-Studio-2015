//############################################################################
//To draw a plurality of windows! This is a file on the window 0.
// I think to be the most well fiddle file.
//############################################################################
#include "../stdafx.h"
#include "OpenGL.h"
#include "OpenGLprimitive.h"

using namespace std;

extern int WinID[2]; //Window ID
OpenGL GLSettings0;	//Set of window 0
int cnt=0;
extern Voxel PM;
//keyboard window 0
bool a_key = 0;//axis
int n_key=0;//Voxel normal
int pp_key=1;//Voxel normal
int l_key=5;//light
bool p_key=true;//Whether or not to pick up
int Num=0;
//keyboard for drawing
bool f_key=0;
bool e_key=0;
bool v_key=0;

//Prototype declaration of function
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

//Drawing functions
void ConclusiveAxis(void);
void SaveView(double &m_EyeDis, CVector3d &m_Center, CVector3d &m_Front,CVector3d &m_Upper);
void ChangeView(double &m_EyeDis, CVector3d &m_Center, CVector3d &m_Front,CVector3d &m_Upper);
//void Draw_vertex();
//void Draw_edge();
//void Draw_face(int num);
void Draw_voxel(Voxel &VM,int num);
void Draw_voxel1(Voxel &VM,int num);
void Grid(int num,Voxel &VM);
/***************************************************/
/*			　OpenGL display function　　   */
/***************************************************/
//Display Functions for windows 0. Callback function
void OpenGLDisplay0(void){
	DisplayInit();	//Preprocessing
	GLSettings0.SetEyePosition();		//Line of sight rotation
	/********************************/
	//Graphic definition from here
	/********************************/
	glPushMatrix();
	glScaled(0.1,0.1,0.12);
	//Absolutely axis // each color
	if(a_key)
	ConclusiveAxis();

	 Draw_voxel(PM,Num);
	 Draw_voxel1(PM,Num);

	 glPopMatrix();
	/********************************/
	//Graphic define up to here
	/********************************/
	DisplayPostprocessor();	//後処理
}



/***************************************************/
/*			　　OpenGLキーボード関数　　	　　   */
/***************************************************/
//特殊な文字はこちらを参照しる	http://e-words.jp/p/r-ascii.html
//BackSpaceに対応する数字は次のようになる。
//	16進数表記だと	'\x08'	C++においてxから始まる数字は16進数
//	 8進数表記だと	'\010'	C++において0から始まる数字は8進数
void OpenGLKeyboard0( unsigned char Key, int x, int y ){

	switch( Key ){
	case '\x1b':	//Esc
		std::cout << "プログラムを終了します" << std::endl;
		exit(0);//システム強制終了
		break;

	case '\x0d':	//Enter	
		std::cout << "Exit OpenGL System" << std::endl;
		glutLeaveMainLoop();		//OpenGLが終了し、main関数へ戻る
		break;

	case '\x20':	//Space
		break;

	case '\x7f':	//Delete
		break;

	case '\x08':	//BackSpace
		break;

	case '\t':		//TAB
		break;

	case 'a':	//座標軸
		a_key =! a_key;
		break;

	case 'v':
		v_key =! v_key;
		break;

	case 'f':
		f_key =! f_key;
		break;
	case 'e':
		e_key =! e_key;
		break;

	case 'l':
		l_key = (l_key+1)%3;
		break;

	case 'n':	
		n_key =! n_key;
		break;
case 'p':	
		pp_key =! pp_key;
		break;
	case '+':
		Num = Num+1;
		//if(Num>8)Num=0;
		break;

	case '-':
			Num = (Num-1);
	//if(Num<0)Num=8;

		break;	

	case '0':
			Num = 0;
		break;	

	case 's'://視点を記憶する
		SaveView(GLSettings0.m_EyeDis, GLSettings0.m_Center, GLSettings0.m_Front, GLSettings0.m_Upper);
		break;

	case 'c'://記憶した視点に変更する
		ChangeView(GLSettings0.m_EyeDis, GLSettings0.m_Center, GLSettings0.m_Front, GLSettings0.m_Upper);
		break;

	case '1':	//視点切替
		GLSettings0.m_EyeDis = 20;
		GLSettings0.m_Center.Clear();
		GLSettings0.m_Front.Set(0.0, 0.0, -1.0);
		GLSettings0.m_Upper.Set(0.0, 1.0, 0.0);
		break;

	case '@':	//描画出力
		//writefile(GL2PS_EPS, GL2PS_SMPLE_SORT, GL2PS_DRAW_BACKGROUND, 0, "Window0", "eps", WinID[0], GLSettings0);
		//writefile(GL2PS_SVG, GL2PS_SMPLE_SORT, GL2PS_DRAW_BACKGROUND, 0, "Window0", "svg", WinID[0], GLSettings0);
		writebmpfile("Window0", "bmp", WinID[0]);

		printf("GL2PS %d.%d.%d done with all images\n",
			GL2PS_MAJOR_VERSION, GL2PS_MINOR_VERSION, GL2PS_PATCH_VERSION);
		break;
	}

	glutPostRedisplay();
}


/***************************************************/
/*			　　OpenGLカーソルキー	　　	　　   */
/***************************************************/
//カーソルキー以外にF1キーなども使える
//一覧はこちら	http://opengl.jp/glut/section07-09.html
void OpenGLSpecial0( int Key, int x, int y ){
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
/*			　　選択可能物体の設置	　　	　　   */
/***************************************************/
int PickUp0( int x, int y, int hit_name[2], int Button ){
	GLint hits;
	GLuint selectBuf[BUFSIZE];
	glSelectBuffer(BUFSIZE, selectBuf);

	PickUpInit(x,y);		//ピックアップ前処理
	GLSettings0.SetEyePosition();		//視線回転
	/************************************/
	/*			物体設置ここから		*/
	/************************************/
	if(p_key && v_key){	//頂点を選択する
		glPushName(0);	//hit_name[0]の値に対応
		//Draw_Voxel_Pic(PM);
		glPopName();
	}

	/************************************/
	/*			物体設置ここまで		*/
	/************************************/
	PickUpPostprocessor();		//ピックアップ後処理

	hits = glRenderMode(GL_RENDER);		//ヒットした物体の個数

	//設置物体の中から、深さが浅いもの（手前に設置されているもの）のidを取得
	return SelectHits(hits,selectBuf,hit_name);
}


/***************************************************/
/*			　　	物体の選択		　　	　　   */
/***************************************************/
void PickObject0( int x, int y, int Button ){
	int hit_name[2];	//ヒットした物体のid番号
	//hit_name[0]	:どの設置物体？ティーポットならPICLEDMODEL0、ドーナツならPICLEDMODEL1
	//hit_name[1]	:何番目に設置した物体？
	//設置したドーナツの中で2番目に設置した物体であれば、
	//hit_name[0]==PICLEDMODEL1、hit_name[1]==2

	if( PickUp0(x,y,hit_name,Button) == -1 ){
		//選択できなかったときはこっちの処理
		GLSettings0.ObjectPosition = &GLSettings0.ObjectTemp;	//ゴミを格納
		return;

	}

	//Zバッファ値をゲット
	GLSettings0.m_ObjectDepth = ReturnDepth(x,y);


	///************************************/
	///*		選択物体の決定ここから		*/
	///************************************/
	
	///************************************/
	///*		選択物体の決定ここまで		*/
	///************************************/

}



/***************************************************/
/*			　　OpenGLマウス関数	　　	　　   */
/***************************************************/
void OpenGLMouse0( int Button, int State, int x, int y ){
	GLSettings0.Tracking( Button, State, x, y );
}

/***************************************************/
/*			　　OpenGLモーション関数　　	　　   */
/***************************************************/
void OpenGLMotion0( int x, int y ){
	GLSettings0.MovingMouse( x, y );
}

/***************************************************/
/*					マウスホイール	　　	　　   */
/***************************************************/

void OpenGLMouseWheel0(int wheel_number, int direction, int x, int y){
	GLSettings0.DoMouseWheel(direction);
}

/***************************************************/
/*			　　OpenGLリサイズ関数	　　	　　   */
/***************************************************/
//あまりいじる必要はないかな。いじるとしたらgluPerspective関数か。
//ただし、gluPerspectiveをいじるとピッキング処理にも影響するので注意
void OpenGLReshape0( int width, int height ){
	GLSettings0.m_Aspect = static_cast<double>(width) / static_cast<double>(height);
	glViewport( 0, 0, width, height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 10.0, GLSettings0.m_Aspect, 0.01, -1.0 );
	glMatrixMode( GL_MODELVIEW );
}


/***************************************************/
/*	　　　ウインドウ０のコールバック関数群	　　   */
/***************************************************/
//あまりいじる必要はないかな。いじるとしたらウインドウのサイズとかか
void OpenGLCallBack0(void){
	GLSettings0.PickObject = PickObject0;	//物体選択関数を関数ポインタに格納
	OpenGLInitialize(0, GLSettings0, 0, 0, 600, 600, "Window0");	//初期化
	glutDisplayFunc	( OpenGLDisplay0 );		//物体の描画
	glutReshapeFunc	( OpenGLReshape0 );		//窓サイズを変えたときに反応
	glutMouseFunc   ( OpenGLMouse0 );		//マウスを押した瞬間と離した瞬間に反応
	glutMotionFunc  ( OpenGLMotion0 );		//マウスをドラッグしたときに反応
	glutMouseWheelFunc( OpenGLMouseWheel0 );	//マウスホイールを転がしたときに反応
	glutKeyboardFunc( OpenGLKeyboard0 );		//キーボードを押したときに反応
	glutSpecialFunc	( OpenGLSpecial0 );		//カーソルキーなどを押したときに反応
	glutIdleFunc( OpenGLIdle );				//何も操作していないときに反応（省略可能）
	OpenGLPostprocessor(GLSettings0);					//後処理
}