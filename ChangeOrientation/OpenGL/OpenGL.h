//############################################################################
//クラスの記述があるファイル
//メンバ関数はOpenGL.cppに記述している
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
//ウインドウを制御するクラス
//窓毎に違う情報を記憶する
//##################################
class OpenGL{

public:
	int	m_WindowWidth;		//ウィンドウの横幅
	int	m_WindowHeight;		//ウィンドウの縦幅
	int	m_State;						//マウスボタンが押されているか離されているか
	int	m_Button;					//左クリックか中クリックか右クリックか
	int	m_mouseLastX;			//直前マウス位置X
	int	m_mouseLastY;			//直前マウス位置Y
	int	m_mouseCurrentX;		//現在マウス位置X
	int	m_mouseCurrentY;		//現在マウス位置Y
	double	m_Aspect;				//現在のウインドウのアスペクト比
	double	m_ObjectDepth;		//選択物体の奥行き深さ

	//古い視点操作用
	double  m_Rotate[3];	 //回転量(x,y,z)
	double  m_EyePos[3];	 //視点位置(x,y,z)

	//新しい視点操作用（POV-Rayのカメラ座標系を参考にしました。）
	CVector3d	m_Center;	//注目点
	double		m_EyeDis;	//視点から注目点までの距離
	CVector3d	m_Upper;	//上方向
	CVector3d	m_Front;		//前方向
	CVector3d	m_Right;		//右方向	
	CVector3d	m_Eye;		//視点


	//コンストラクタ
	OpenGL() : m_WindowWidth(800), m_WindowHeight(800), 
		m_State(GLUT_UP),   m_Button(NONE),
		m_mouseLastX(0),    m_mouseLastY(0) 
	{
		//古い視点操作用
		m_Rotate[0]=0.0; m_Rotate[1]=0.0; m_Rotate[2]=0.0;
		m_EyePos[0]=0.0; m_EyePos[1]=0.0; m_EyePos[2]=10.0;

		
		m_EyeDis = 1500;
		m_Center = CVector3d(0.0, 0.0, 0.0);
		m_Front = CVector3d(0.0, 0.0, -1.0);
		m_Upper = CVector3d(0.0, 1.0, 0.0);
	}

	//メンバ関数
	void Tracking( int, int, int, int );	//マウストラッキング、ボタンを押すと呼ばれる
	void MovingMouse( int, int );			//ボタンを押しつつマウスを動かすと呼ばれる
	void SetEyePosition();
	void DoMouseWheel(int direction);
	void SetEyes(){
		m_Eye = m_Center - (m_EyeDis * m_Front);		
		m_Right = m_Front.Cross(m_Upper);
	}

	//############################
	//	OpenGLPicking	物体の選択
	//############################
	CVector3d *ObjectPosition;		//選択した物体の位置
	CVector3d ObjectTemp;			//何も選択しなかったときのObjectPositionの受け皿
	void (*PickObject)( int x, int y, int Button );		//物体選択関数の関数ポインタ
};





#endif