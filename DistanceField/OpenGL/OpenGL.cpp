//############################################################################
//OpenGL.h�̃����o�֐����L�q���Ă���t�@�C��
//�}�E�X����Ȃǂ�������Ă���B
//���_����Ȃǂ̑��슴��ς������Ȃ�A���̃t�@�C����������΂悢
//############################################################################
#include "../stdafx.h"
#include "OpenGL.h"
using namespace std;

//�}�E�X�g���b�L���O�A�{�^���������ƌĂ΂��(OpenGLMouse)
//������MouseFunction�Ɠ���
void idle(void)
{
  glutPostRedisplay();
}

void OpenGL::Tracking( int Button, int State, int x, int y ){
	//�{�^���������ꂽ�u��
	if( State == GLUT_DOWN ){
		m_State  = GLUT_DOWN;	//������Ă���󋵂��L��
		m_Button = Button;		//���N���b�N�H���N���b�N�H�E�N���b�N
		m_mouseLastX = x;		//�������u�Ԃ̃}�E�X���W���擾
		m_mouseLastY = y;		//�������u�Ԃ̃}�E�X���W���擾

		//���N���b�N�͕��̑I��
		if(Button==GLUT_LEFT_BUTTON){
			glutIdleFunc(idle);
			//�s�b�N����֐��͕`��E�C���h�E�ɂ���ĈႤ���߁A�֐��|�C���^���g��
			(*PickObject)( x, y, Button );	//�s�b�N����֐�
		}
	}
	//�{�^���������ꂽ�u��
	else if( State == GLUT_UP ){
		m_State  = GLUT_UP;		//������Ă���󋵂��L��
		m_Button = NONE;		//�ǂ̃{�^�����Y�����Ȃ�
		//  glutIdleFunc(0);
			glutIdleFunc(idle);

	}
	glutPostRedisplay();
}


//�{�^���������}�E�X�𓮂����ƌĂ΂��֐�(OpenGLMotion)
void OpenGL::MovingMouse( int x, int y ){
	m_mouseCurrentX = x;	//�������u�Ԃ̃}�E�X���W
	m_mouseCurrentY = y;	//�������u�Ԃ̃}�E�X���W

	//���N���b�N�̃h���b�O�͕��̈ړ�
	if( m_State == GLUT_DOWN && m_Button == GLUT_LEFT_BUTTON ){
		      //glutIdleFunc(idle);

	}

//---------------------------�O���炠����--------------------------------//
	//	double dx = (x - m_mouseLastX)*0.0003*m_EyeDis;
	//	double dy = (m_mouseLastY - y)*0.0003*m_EyeDis;	//�摜���ʂ�y���͉������ł��邽�ߋt
	//	*ObjectPosition = (*ObjectPosition) + (dx * m_Right) + (dy * m_Upper);
	//}

	//���N���b�N�̃h���b�O�͎��_�ړ�
	if ( m_State == GLUT_DOWN && m_Button == GLUT_MIDDLE_BUTTON ){
		double dx = -(x - m_mouseLastX)*0.0003*m_EyeDis;
		double dy = -(m_mouseLastY - y)*0.0003*m_EyeDis;	//�摜���ʂ�y���͉������ł��邽�ߋt
		m_Eye += dx * m_Right + dy * m_Upper;
		m_Center += dx * m_Right + dy * m_Upper;

		glutPostRedisplay ();
	}
	
	//�E�N���b�N�̃h���b�O�͎��_��]
	if( m_State == GLUT_DOWN && m_Button == GLUT_RIGHT_BUTTON ){
		double dt = -(x - m_mouseLastX)*0.01;	//����]�̊p�x
		double dp = -(m_mouseLastY - y)*0.01;	//�c��]�̊p�x
		m_Right = (cos(dt) * m_Right) + (sin(dt) * m_Front);
		m_Upper = (cos(dp) * m_Upper) + (sin(dp) * m_Front);
		m_Front = m_Upper.Cross(m_Right);
		m_Front.Normalize(m_Front);	//��������Ȃ��ƁA�ۂߌ덷�łЂǂ��Ȃ�
		glutPostRedisplay ();
	}

	m_mouseLastX = x;
	m_mouseLastY = y;
}

//�}�E�X�z�C�[����]�����ƌĂ΂��֐�
void OpenGL::DoMouseWheel(int direction){
	m_EyeDis -= (double)direction*0.2*m_EyeDis;
	glutPostRedisplay ();
}

//���_�̌���
void OpenGL::SetEyePosition(){
	SetEyes();

	gluLookAt( m_Eye.x, m_Eye.y, m_Eye.z, 
		m_Center.x, m_Center.y, m_Center.z,
		m_Upper.x, m_Upper.y, m_Upper.z );
}
