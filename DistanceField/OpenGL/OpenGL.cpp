//############################################################################
//OpenGL.hのメンバ関数を記述しているファイル
//マウス操作などが書かれている。
//視点操作などの操作感を変えたいなら、このファイルをいじればよい
//############################################################################
#include "../stdafx.h"
#include "OpenGL.h"
using namespace std;

//マウストラッキング、ボタンを押すと呼ばれる(OpenGLMouse)
//引数はMouseFunctionと同じ
void idle(void)
{
  glutPostRedisplay();
}

void OpenGL::Tracking( int Button, int State, int x, int y ){
	//ボタンが押された瞬間
	if( State == GLUT_DOWN ){
		m_State  = GLUT_DOWN;	//押されている状況を記憶
		m_Button = Button;		//左クリック？中クリック？右クリック
		m_mouseLastX = x;		//押した瞬間のマウス座標を取得
		m_mouseLastY = y;		//押した瞬間のマウス座標を取得

		//左クリックは物体選択
		if(Button==GLUT_LEFT_BUTTON){
			glutIdleFunc(idle);
			//ピックする関数は描画ウインドウによって違うため、関数ポインタを使う
			(*PickObject)( x, y, Button );	//ピックする関数
		}
	}
	//ボタンが離された瞬間
	else if( State == GLUT_UP ){
		m_State  = GLUT_UP;		//離されている状況を記憶
		m_Button = NONE;		//どのボタンも該当しない
		//  glutIdleFunc(0);
			glutIdleFunc(idle);

	}
	glutPostRedisplay();
}


//ボタンを押しつつマウスを動かすと呼ばれる関数(OpenGLMotion)
void OpenGL::MovingMouse( int x, int y ){
	m_mouseCurrentX = x;	//押した瞬間のマウス座標
	m_mouseCurrentY = y;	//押した瞬間のマウス座標

	//左クリックのドラッグは物体移動
	if( m_State == GLUT_DOWN && m_Button == GLUT_LEFT_BUTTON ){
		      //glutIdleFunc(idle);

	}

//---------------------------前からあるやつ--------------------------------//
	//	double dx = (x - m_mouseLastX)*0.0003*m_EyeDis;
	//	double dy = (m_mouseLastY - y)*0.0003*m_EyeDis;	//画像平面のy軸は下向きであるため逆
	//	*ObjectPosition = (*ObjectPosition) + (dx * m_Right) + (dy * m_Upper);
	//}

	//中クリックのドラッグは視点移動
	if ( m_State == GLUT_DOWN && m_Button == GLUT_MIDDLE_BUTTON ){
		double dx = -(x - m_mouseLastX)*0.0003*m_EyeDis;
		double dy = -(m_mouseLastY - y)*0.0003*m_EyeDis;	//画像平面のy軸は下向きであるため逆
		m_Eye += dx * m_Right + dy * m_Upper;
		m_Center += dx * m_Right + dy * m_Upper;

		glutPostRedisplay ();
	}
	
	//右クリックのドラッグは視点回転
	if( m_State == GLUT_DOWN && m_Button == GLUT_RIGHT_BUTTON ){
		double dt = -(x - m_mouseLastX)*0.01;	//横回転の角度
		double dp = -(m_mouseLastY - y)*0.01;	//縦回転の角度
		m_Right = (cos(dt) * m_Right) + (sin(dt) * m_Front);
		m_Upper = (cos(dp) * m_Upper) + (sin(dp) * m_Front);
		m_Front = m_Upper.Cross(m_Right);
		m_Front.Normalize(m_Front);	//これをしないと、丸め誤差でひどくなる
		glutPostRedisplay ();
	}

	m_mouseLastX = x;
	m_mouseLastY = y;
}

//マウスホイールを転がすと呼ばれる関数
void OpenGL::DoMouseWheel(int direction){
	m_EyeDis -= (double)direction*0.2*m_EyeDis;
	glutPostRedisplay ();
}

//視点の決定
void OpenGL::SetEyePosition(){
	SetEyes();

	gluLookAt( m_Eye.x, m_Eye.y, m_Eye.z, 
		m_Center.x, m_Center.y, m_Center.z,
		m_Upper.x, m_Upper.y, m_Upper.z );
}
