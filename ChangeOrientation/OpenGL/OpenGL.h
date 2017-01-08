//############################################################################
//
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
//
//##################################
class OpenGL{

public:
	int	m_WindowWidth;		
	int	m_WindowHeight;		
	int	m_State;						
	int	m_Button;					
	int	m_mouseLastX;			
	int	m_mouseLastY;			
	int	m_mouseCurrentX;		
	int	m_mouseCurrentY;		
	double	m_Aspect;				
	double	m_ObjectDepth;		

	//
	double  m_Rotate[3];	 
	double  m_EyePos[3];	

	//
	CVector3d	m_Center;	
	double		m_EyeDis;	
	CVector3d	m_Upper;	
	CVector3d	m_Front;		
	CVector3d	m_Right;			
	CVector3d	m_Eye;		


	
	OpenGL() : m_WindowWidth(800), m_WindowHeight(800), 
		m_State(GLUT_UP),   m_Button(NONE),
		m_mouseLastX(0),    m_mouseLastY(0) 
	{
		//
		m_Rotate[0]=0.0; m_Rotate[1]=0.0; m_Rotate[2]=0.0;
		m_EyePos[0]=0.0; m_EyePos[1]=0.0; m_EyePos[2]=10.0;

		
		m_EyeDis = 1500;
		m_Center = CVector3d(0.0, 0.0, 0.0);
		m_Front = CVector3d(0.0, 0.0, -1.0);
		m_Upper = CVector3d(0.0, 1.0, 0.0);
	}

	
	void Tracking( int, int, int, int );	
	void MovingMouse( int, int );			
	void SetEyePosition();
	void DoMouseWheel(int direction);
	void SetEyes(){
		m_Eye = m_Center - (m_EyeDis * m_Front);		
		m_Right = m_Front.Cross(m_Upper);
	}

	//############################
	//	OpenGLPicking
	//############################
	CVector3d *ObjectPosition;		
	CVector3d ObjectTemp;			
	void (*PickObject)( int x, int y, int Button );		
};





#endif
