//############################################################################
//�����̃E�C���h�E�ɋ��ʂ���֐��͂��̃t�@�C���ɏ�����
//������K�v�͂��܂�Ȃ��Ǝv���B������Ƃ�����ARunOpenGL�֐����炢����
//############################################################################
#include "../stdafx.h"
#include "OpenGL.h"
#include "OpenGLprimitive.h"

using namespace std;
//#pragma warning(disable : 4996)//about scanf

int WinID[2]; //�E�B���h�EID

//�֐��̃v���g�^�C�v�錾
void OpenGLDisplay0(void);
//void OpenGLDisplay1(void);
void OpenGLCallBack0(void);
//void OpenGLCallBack1(void);
void OpenGLPreparation0();
//void OpenGLPreparation1();


/***************************************************/
/*			�@OpenGL�f�B�X�v���C�֐�		�@�@   */
/***************************************************/
//�f�B�X�v���C�֐��O����
void DisplayInit(){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glEnable(GL_BLEND);	//���ߏ���
	glBlendFunc(GL_ONE, GL_ZERO);

	SetLight();	//�����Ō����ݒ肷��΁A�����͎��_�ɌŒ�

	glPushMatrix();
}

//�f�B�X�v���C�֐��㏈��
void DisplayPostprocessor(){
	glDepthMask(TRUE);//���ߏ���end
	glDisable(GL_BLEND);

	glPopMatrix();
	glutSwapBuffers();
}


/***************************************************/
/*			�@OpenGL�s�b�N�A�b�v�֐�		�@�@   */
/***************************************************/
//�s�b�L���O�֐��O����
//������Ƃ�����A�s�b�L���O�̈�̂Ƃ���B
void PickUpInit(int x, int y){
	GLint viewport[4];
	double current_aspect;
	glGetIntegerv(GL_VIEWPORT, viewport);

	(void) glRenderMode(GL_SELECT);

	glInitNames();
	glMatrixMode(GL_PROJECTION);			//�v���W�F�N�V�������[�h
	glPushMatrix();							//�Z���N�V�������[�h�̂Ƃ��̂݉��̍s��v�Z
	glLoadIdentity();						//�𔽉f�����邽�߂�Push����

	//�s�b�L���O�s��̏�Z
	gluPickMatrix(x,viewport[3]-y, 25.0, 25.0, viewport);
	//3�Ԗڂ̈�����x�����̃s�N�Z�����A4�Ԗڂ̈�����y�����̃s�N�Z����
	//�N���b�N�����s�N�Z���̎��̓s�N�Z�����ǂ̂��炢�s�b�L���O�̈�Ɋ܂߂邩�ǂ����B
	//�s�b�L���O�̈���ɓ����Ă��镨�̂͑S�ăq�b�g����B

	current_aspect = (double)viewport[2]/(double)viewport[3];

	gluPerspective( 10.0, current_aspect, 0.01, -1.0 );

	glMatrixMode( GL_MODELVIEW );		//�����Ń��f���r���[���[�h�ɂ���I�I�I�I
	glPushMatrix();	
}

//�s�b�L���O�֐��㏈��
void PickUpPostprocessor(void){
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );			//���f���r���[���[�h�֖߂�
}

//�q�b�g�������̂�ID���擾
//�q�b�g���������̕��̂̒�����A��Ԏ�O�ɐݒu����Ă��镨�̂�I��
int SelectHits( GLuint hits, GLuint* buf, int hit_name[2] ){
	hit_name[0]=-1;
	hit_name[1]=-1;	//�K�w�͂Q

	double depth_min=10.0;	//��ԉ�
	double depth_1=1.0;
	double depth_2=1.0;
	GLuint depth_name;
	GLuint *ptr;
	// �q�b�g�����f�[�^�Ȃ�
	if(hits<=0){
		return -1;
	}

	// �|�C���^����Ɨpptr�֓n���D
	ptr = buf;

	//�q�b�g��������������
	for(unsigned int i=0; i<hits; ++i){
		depth_name = *ptr;	// ���ʔԍ��̊K�w�̐[��	//�l�[���X�^�b�N�ɐς܂ꂽ���O�̐�

		//OpenGL�ɂ����āA�ʐς������́iteapot�Ȃǁj�̓|���S�����b�V���Ƃ��ĕ\������Ă���B
		//���̃|���S�����b�V�����܂ޒ��_�̒��ŁA��ԉ��ɂ�����̂ƈ�Ԏ�O�ɂ�����̂�����B
		++ptr;
		depth_1 = *ptr/0x7fffffff;	//�I��͈͂����؂�v���~�e�B�u�̒��_�̃f�v�X�l�̍ŏ��l
		//��Ԏ�O�ɂ��钸�_�̐[��

		++ptr;
		depth_2 = *ptr/0x7fffffff;	//�I��͈͂����؂�v���~�e�B�u�̒��_�̃f�v�X�l�̍ő�l
		//��ԉ��ɂ��钸�_�̐[��

		// �ŏ��f�v�X�̊m�F
		if(depth_min>depth_1){	//������O�̒��_�̐[�����A�ŏ��f�v�X��菬�������
			depth_min = depth_1;	//���̒��_�̐[�����ŏ��f�v�X�ɂ���B

			//���ʔԍ��̊K�w�̐[������������
			for(unsigned int j=0; j<depth_name; ++j){
				++ptr;
				hit_name[j] = (int)(*ptr);	//���̒��_��id����hit_name�Ɋi�[
			}
		}else{		//������O�̒��_�̐[�����ŏ��f�v�X�����傫�����
			for(unsigned int j=0; j<depth_name; ++j){
				++ptr;		//id���͊i�[���Ȃ��B�X���[����B
			}
		}
		++ptr;	//���̑I�𕨑̂�
	}
	return hit_name[0];
}


//�N���b�N�����Ƃ���ɐݒu���Ă�����̂̃f�v�X�l���擾����B
double ReturnDepth( int x, int y ){
	double z;
	GLint viewport[4];			//�r���[�|�[�g
	//�f�o�C�X���W�n�ƃE�B���h�E���W�n�̕ϊ�
	glGetIntegerv(GL_VIEWPORT,viewport);	//���݂̃r���[�|�[�g����
	glReadPixels(x,viewport[3]-y,1,1,
		GL_DEPTH_COMPONENT,
		GL_FLOAT,
		&z);
	return z;
}




/***************************************************/
/*				�@�@eps�����o���֐��@�@	�@�@   �@�@*/
/***************************************************/
void writefile(int format, int sort, int options, int nbcol,char *filename, char *extension, int winid, OpenGL GLSettings){
	FILE *fp;
	char file[256];
	int state = GL2PS_OVERFLOW, buffsize = 0;
	GLint viewport[4];

	strcpy_s(file, filename);
	strcat_s(file, ".");
	strcat_s(file, extension);

	viewport[0] = 0;
	viewport[1] = 0;

	viewport[2] = GLSettings.m_WindowWidth;//window��
	viewport[3] = GLSettings.m_WindowHeight;//window����

	fp = fopen(file, "wb");

	if(!fp){
		printf("Unable to open file %s for writing\n", file);
		exit(1);
	}

	printf("Saving image to file %s... ", file);
	fflush(stdout);

	while(state == GL2PS_OVERFLOW){
		//eps
		buffsize += 1024*1024;
		gl2psBeginPage(file, "gl2psTest", viewport, format, sort, options,GL_RGBA, 0, NULL, nbcol, nbcol, nbcol,buffsize, fp, file);

		//�`�悷�鑋�ɂ���ČĂяo���֐��͈Ⴄ
		if(winid==WinID[0]){
			OpenGLDisplay0();
		}else if(winid==WinID[1]){
			//OpenGLDisplay1();
		}

		state = gl2psEndPage();
	}

	fclose(fp);
	printf("Done!\n");
	fflush(stdout);
}


/***************************************************/
/*			�@�@	bmp�����o���֐��@�@	�@�@   �@�@*/
/***************************************************/
void writebmpfile(char *filename, char *extension, int winid){
	char file[256];
	strcpy_s(file, filename);
	strcat_s(file, ".");
	strcat_s(file, extension);

	if(winid==WinID[0]){
		OpenGLDisplay0();
	}else if(winid==WinID[1]){
	//	OpenGLDisplay1();
	}

	gl_screenshot gs;
	gs.screenshot(file, 24);
}


/***************************************************/
/*					�������Ȃ��Ƃ�	�@�@	�@�@   */
/***************************************************/
void OpenGLIdle(void){
	glutPostRedisplay();
}




/***************************************************/
/*			�@�@�@OpenGL�������֐�				   */
/***************************************************/
void OpenGLInitialize(int WindowID, OpenGL GLSettings, int InitPosiX, int InitPosiY, int WindowWidth, int WindowHeight, char* WindowName){
	GLSettings.m_WindowHeight = WindowHeight;
	GLSettings.m_WindowWidth = WindowWidth;
	glutInitWindowPosition(InitPosiX, InitPosiY);		//�E�C���h�E�̏����ʒu
	glutInitDisplayMode(GLUT_RGBA| GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize( WindowWidth, WindowHeight );	//�E�C���h�E�̃T�C�Y
	WinID[WindowID] = glutCreateWindow(WindowName);		//�E�C���h�E�̐���
}

/***************************************************/
/*			�@�@�@OpenGL�㏈���֐�				   */
/***************************************************/
void OpenGLPostprocessor(OpenGL GLSettings){
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );	//�w�i�F
	glClearDepth( 1.0f );
	glEnable    ( GL_DEPTH_TEST );	//�A�ʏ���
	glDepthFunc ( GL_LEQUAL );
	glShadeModel( GL_SMOOTH );		//�X���[�X�V�F�[�f�B���O

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D( -GLSettings.m_WindowWidth,  GLSettings.m_WindowWidth, -GLSettings.m_WindowHeight, GLSettings.m_WindowHeight );

	glMatrixMode( GL_MODELVIEW );
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);	//�}�E�X�z�C�[���ɕK�v
}


/***************************************************/
/*			�@�@�@OpenGL�����֐�	�@�@	�@�@   */
/***************************************************/
void RunOpenGL0(int argc, char *argv[]){
	glutInit(&argc, argv);		//freeglut���ƕK�v
	OpenGLPreparation0();
	OpenGLCallBack0();	//��0
	glutMainLoop();		//���[�v�ɓ���A���͑ҋ@���[�h�ɂȂ�B
}

//void RunOpenGL1(int argc, char *argv[]){
//	glutInit(&argc, argv);		//freeglut���ƕK�v
//	OpenGLPreparation1();
//	OpenGLCallBack1();	//��1
//	glutMainLoop();		//���[�v�ɓ���A���͑ҋ@���[�h�ɂȂ�B
//}
