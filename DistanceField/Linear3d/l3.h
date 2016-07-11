#pragma once
/****************************************************************
*	New!Linear3d												*
*	3次元座標の新・計算ライブラリです。							*
*									programed by Kineri			*
*	program ver. 1.6	2012.7.23								*
*	program ver. 1.7 	2012.7.24								*
*	program ver. 1.8	2012.8.8								*
*****************************************************************/
#define MACHINE_ERROR 1.0e-15
#pragma warning(disable : 4996)//about scanf

//CSparse使用者は #define USE_CSPARSEを書いてください
#ifdef USE_CSPARSE
#include "../Csparse3.0.1\cs.h"
#endif
#include "l3_cpoint3d.h"	//頂点クラスライブラリ
#include "l3_cmatrix.h"		//行列計算ライブラリ
#include "l3_cquat.h"		//四元数ライブラリ
#include "l3_ccolor.h"		//色情報ライブラリ
#include <algorithm>