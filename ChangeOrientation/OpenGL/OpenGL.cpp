//############################################################################
// 2015/08
//############################################################################
#include "../stdafx.h"
#include "OpenGL.h"
using namespace std;

//(OpenGLMouse)
//MouseFunction
void OpenGL::Tracking( int Button, int State, int x, int y ){

	if( State == GLUT_DOWN ){
		m_State  = GLUT_DOWN;	
		m_Button = Button;		
		m_mouseLastX = x;		
		m_mouseLastY = y;		

		
		if(Button==GLUT_LEFT_BUTTON){
			(*PickObject)( x, y, Button );	
		}
	}
	
	else if( State == GLUT_UP ){
		m_State  = GLUT_UP;		
		m_Button = NONE;		
	}
	glutPostRedisplay();
}


//(OpenGLMotion)
void OpenGL::MovingMouse( int x, int y ){
	m_mouseCurrentX = x;	
	m_mouseCurrentY = y;	

	
	if( m_State == GLUT_DOWN && m_Button == GLUT_LEFT_BUTTON ){
		double dx = (x - m_mouseLastX)*0.0003*m_EyeDis;
		double dy = (m_mouseLastY - y)*0.0003*m_EyeDis;	
		*ObjectPosition = (*ObjectPosition) + (dx * m_Right) + (dy * m_Upper);
	}

	//
	if ( m_State == GLUT_DOWN && m_Button == GLUT_MIDDLE_BUTTON ){
		double dx = -(x - m_mouseLastX)*0.0003*m_EyeDis;
		double dy = -(m_mouseLastY - y)*0.0003*m_EyeDis;	
		m_Eye += dx * m_Right + dy * m_Upper;
		m_Center += dx * m_Right + dy * m_Upper;

		glutPostRedisplay ();
	}
	

	if( m_State == GLUT_DOWN && m_Button == GLUT_RIGHT_BUTTON ){
		double dt = -(x - m_mouseLastX)*0.01;	
		double dp = -(m_mouseLastY - y)*0.01;
		m_Right = (cos(dt) * m_Right) + (sin(dt) * m_Front);
		m_Upper = (cos(dp) * m_Upper) + (sin(dp) * m_Front);
		m_Front = m_Upper.Cross(m_Right);
		m_Front.Normalize(m_Front);	
		glutPostRedisplay ();
	}

	m_mouseLastX = x;
	m_mouseLastY = y;
}

//
void OpenGL::DoMouseWheel(int direction){
	m_EyeDis -= (double)direction*0.2*m_EyeDis;
	glutPostRedisplay ();
}

//
void OpenGL::SetEyePosition(){
	SetEyes();

	gluLookAt( m_Eye.x, m_Eye.y, m_Eye.z, 
		m_Center.x, m_Center.y, m_Center.z,
		m_Upper.x, m_Upper.y, m_Upper.z );
}

