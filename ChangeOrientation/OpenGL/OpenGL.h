//############################################################################
//�N���X�̋L�q������t�@�C��
//�����o�֐���OpenGL.cpp�ɋL�q���Ă���
//############################################################################
#ifndef _INCLUDED_OPENGL_H
#define _INCLUDED_OPENGL_H

#include "../stdafx.h"
#include <freeglut.h>
#include "gl2ps.h"
#include "gl_screenshot.h"


#pragma warning(disable : 4996)//about scanf

#define NONE		-1
#define BUFSIZE		512


//##################################
//�E�C���h�E�𐧌䂷��N���X
//�����ɈႤ�����L������
//##################################
class OpenGL{

public:
	int	m_WindowWidth;		//�E�B���h�E�̉���
	int	m_WindowHeight;		//�E�B���h�E�̏c��
	int	m_State;						//�}�E�X�{�^����������Ă��邩������Ă��邩
	int	m_Button;					//���N���b�N�����N���b�N���E�N���b�N��
	int	m_mouseLastX;			//���O�}�E�X�ʒuX
	int	m_mouseLastY;			//���O�}�E�X�ʒuY
	int	m_mouseCurrentX;		//���݃}�E�X�ʒuX
	int	m_mouseCurrentY;		//���݃}�E�X�ʒuY
	double	m_Aspect;				//���݂̃E�C���h�E�̃A�X�y�N�g��
	double	m_ObjectDepth;		//�I�𕨑̂̉��s���[��

	//�Â����_����p
	double  m_Rotate[3];	 //��]��(x,y,z)
	double  m_EyePos[3];	 //���_�ʒu(x,y,z)

	//�V�������_����p�iPOV-Ray�̃J�������W�n���Q�l�ɂ��܂����B�j
	CVector3d	m_Center;	//���ړ_
	double		m_EyeDis;	//���_���璍�ړ_�܂ł̋���
	CVector3d	m_Upper;	//�����
	CVector3d	m_Front;		//�O����
	CVector3d	m_Right;		//�E����	
	CVector3d	m_Eye;		//���_


	//�R���X�g���N�^
	OpenGL() : m_WindowWidth(800), m_WindowHeight(800), 
		m_State(GLUT_UP),   m_Button(NONE),
		m_mouseLastX(0),    m_mouseLastY(0) 
	{
		//�Â����_����p
		m_Rotate[0]=0.0; m_Rotate[1]=0.0; m_Rotate[2]=0.0;
		m_EyePos[0]=0.0; m_EyePos[1]=0.0; m_EyePos[2]=10.0;

		
		m_EyeDis = 1500;
		m_Center = CVector3d(0.0, 0.0, 0.0);
		m_Front = CVector3d(0.0, 0.0, -1.0);
		m_Upper = CVector3d(0.0, 1.0, 0.0);
	}

	//�����o�֐�
	void Tracking( int, int, int, int );	//�}�E�X�g���b�L���O�A�{�^���������ƌĂ΂��
	void MovingMouse( int, int );			//�{�^���������}�E�X�𓮂����ƌĂ΂��
	void SetEyePosition();
	void DoMouseWheel(int direction);
	void SetEyes(){
		m_Eye = m_Center - (m_EyeDis * m_Front);		
		m_Right = m_Front.Cross(m_Upper);
	}

	//############################
	//	OpenGLPicking	���̂̑I��
	//############################
	CVector3d *ObjectPosition;		//�I���������̂̈ʒu
	CVector3d ObjectTemp;			//�����I�����Ȃ������Ƃ���ObjectPosition�̎󂯎M
	void (*PickObject)( int x, int y, int Button );		//���̑I���֐��̊֐��|�C���^
};





#endif