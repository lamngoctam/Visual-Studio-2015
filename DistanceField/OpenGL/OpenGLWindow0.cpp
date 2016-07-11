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
/*			�@OpenGL display function�@�@   */
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
	DisplayPostprocessor();	//�㏈��
}



/***************************************************/
/*			�@�@OpenGL�L�[�{�[�h�֐��@�@	�@�@   */
/***************************************************/
//����ȕ����͂�������Q�Ƃ���	http://e-words.jp/p/r-ascii.html
//BackSpace�ɑΉ����鐔���͎��̂悤�ɂȂ�B
//	16�i���\�L����	'\x08'	C++�ɂ�����x����n�܂鐔����16�i��
//	 8�i���\�L����	'\010'	C++�ɂ�����0����n�܂鐔����8�i��
void OpenGLKeyboard0( unsigned char Key, int x, int y ){

	switch( Key ){
	case '\x1b':	//Esc
		std::cout << "�v���O�������I�����܂�" << std::endl;
		exit(0);//�V�X�e�������I��
		break;

	case '\x0d':	//Enter	
		std::cout << "Exit OpenGL System" << std::endl;
		glutLeaveMainLoop();		//OpenGL���I�����Amain�֐��֖߂�
		break;

	case '\x20':	//Space
		break;

	case '\x7f':	//Delete
		break;

	case '\x08':	//BackSpace
		break;

	case '\t':		//TAB
		break;

	case 'a':	//���W��
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

	case 's'://���_���L������
		SaveView(GLSettings0.m_EyeDis, GLSettings0.m_Center, GLSettings0.m_Front, GLSettings0.m_Upper);
		break;

	case 'c'://�L���������_�ɕύX����
		ChangeView(GLSettings0.m_EyeDis, GLSettings0.m_Center, GLSettings0.m_Front, GLSettings0.m_Upper);
		break;

	case '1':	//���_�ؑ�
		GLSettings0.m_EyeDis = 20;
		GLSettings0.m_Center.Clear();
		GLSettings0.m_Front.Set(0.0, 0.0, -1.0);
		GLSettings0.m_Upper.Set(0.0, 1.0, 0.0);
		break;

	case '@':	//�`��o��
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
/*			�@�@OpenGL�J�[�\���L�[	�@�@	�@�@   */
/***************************************************/
//�J�[�\���L�[�ȊO��F1�L�[�Ȃǂ��g����
//�ꗗ�͂�����	http://opengl.jp/glut/section07-09.html
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
/*			�@�@�I���\���̂̐ݒu	�@�@	�@�@   */
/***************************************************/
int PickUp0( int x, int y, int hit_name[2], int Button ){
	GLint hits;
	GLuint selectBuf[BUFSIZE];
	glSelectBuffer(BUFSIZE, selectBuf);

	PickUpInit(x,y);		//�s�b�N�A�b�v�O����
	GLSettings0.SetEyePosition();		//������]
	/************************************/
	/*			���̐ݒu��������		*/
	/************************************/
	if(p_key && v_key){	//���_��I������
		glPushName(0);	//hit_name[0]�̒l�ɑΉ�
		//Draw_Voxel_Pic(PM);
		glPopName();
	}

	/************************************/
	/*			���̐ݒu�����܂�		*/
	/************************************/
	PickUpPostprocessor();		//�s�b�N�A�b�v�㏈��

	hits = glRenderMode(GL_RENDER);		//�q�b�g�������̂̌�

	//�ݒu���̂̒�����A�[�����󂢂��́i��O�ɐݒu����Ă�����́j��id���擾
	return SelectHits(hits,selectBuf,hit_name);
}


/***************************************************/
/*			�@�@	���̂̑I��		�@�@	�@�@   */
/***************************************************/
void PickObject0( int x, int y, int Button ){
	int hit_name[2];	//�q�b�g�������̂�id�ԍ�
	//hit_name[0]	:�ǂ̐ݒu���́H�e�B�[�|�b�g�Ȃ�PICLEDMODEL0�A�h�[�i�c�Ȃ�PICLEDMODEL1
	//hit_name[1]	:���Ԗڂɐݒu�������́H
	//�ݒu�����h�[�i�c�̒���2�Ԗڂɐݒu�������̂ł���΁A
	//hit_name[0]==PICLEDMODEL1�Ahit_name[1]==2

	if( PickUp0(x,y,hit_name,Button) == -1 ){
		//�I���ł��Ȃ������Ƃ��͂������̏���
		GLSettings0.ObjectPosition = &GLSettings0.ObjectTemp;	//�S�~���i�[
		return;

	}

	//Z�o�b�t�@�l���Q�b�g
	GLSettings0.m_ObjectDepth = ReturnDepth(x,y);


	///************************************/
	///*		�I�𕨑̂̌��肱������		*/
	///************************************/
	
	///************************************/
	///*		�I�𕨑̂̌��肱���܂�		*/
	///************************************/

}



/***************************************************/
/*			�@�@OpenGL�}�E�X�֐�	�@�@	�@�@   */
/***************************************************/
void OpenGLMouse0( int Button, int State, int x, int y ){
	GLSettings0.Tracking( Button, State, x, y );
}

/***************************************************/
/*			�@�@OpenGL���[�V�����֐��@�@	�@�@   */
/***************************************************/
void OpenGLMotion0( int x, int y ){
	GLSettings0.MovingMouse( x, y );
}

/***************************************************/
/*					�}�E�X�z�C�[��	�@�@	�@�@   */
/***************************************************/

void OpenGLMouseWheel0(int wheel_number, int direction, int x, int y){
	GLSettings0.DoMouseWheel(direction);
}

/***************************************************/
/*			�@�@OpenGL���T�C�Y�֐�	�@�@	�@�@   */
/***************************************************/
//���܂肢����K�v�͂Ȃ����ȁB������Ƃ�����gluPerspective�֐����B
//�������AgluPerspective��������ƃs�b�L���O�����ɂ��e������̂Œ���
void OpenGLReshape0( int width, int height ){
	GLSettings0.m_Aspect = static_cast<double>(width) / static_cast<double>(height);
	glViewport( 0, 0, width, height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 10.0, GLSettings0.m_Aspect, 0.01, -1.0 );
	glMatrixMode( GL_MODELVIEW );
}


/***************************************************/
/*	�@�@�@�E�C���h�E�O�̃R�[���o�b�N�֐��Q	�@�@   */
/***************************************************/
//���܂肢����K�v�͂Ȃ����ȁB������Ƃ�����E�C���h�E�̃T�C�Y�Ƃ���
void OpenGLCallBack0(void){
	GLSettings0.PickObject = PickObject0;	//���̑I���֐����֐��|�C���^�Ɋi�[
	OpenGLInitialize(0, GLSettings0, 0, 0, 600, 600, "Window0");	//������
	glutDisplayFunc	( OpenGLDisplay0 );		//���̂̕`��
	glutReshapeFunc	( OpenGLReshape0 );		//���T�C�Y��ς����Ƃ��ɔ���
	glutMouseFunc   ( OpenGLMouse0 );		//�}�E�X���������u�ԂƗ������u�Ԃɔ���
	glutMotionFunc  ( OpenGLMotion0 );		//�}�E�X���h���b�O�����Ƃ��ɔ���
	glutMouseWheelFunc( OpenGLMouseWheel0 );	//�}�E�X�z�C�[����]�������Ƃ��ɔ���
	glutKeyboardFunc( OpenGLKeyboard0 );		//�L�[�{�[�h���������Ƃ��ɔ���
	glutSpecialFunc	( OpenGLSpecial0 );		//�J�[�\���L�[�Ȃǂ��������Ƃ��ɔ���
	glutIdleFunc( OpenGLIdle );				//�������삵�Ă��Ȃ��Ƃ��ɔ����i�ȗ��\�j
	OpenGLPostprocessor(GLSettings0);					//�㏈��
}