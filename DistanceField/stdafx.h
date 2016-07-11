#pragma once

//#############################################################
//	DEFINE(使用する定義…誤差の閾値等も含む)
//#############################################################
#define WIN32_LEAN_AND_MEAN	// Windowsヘッダーから使用されていない部分を除外します。
#define _USE_MATH_DEFINES	//円周率M_PIを使うために必要

// TODO: プログラムに必要な追加ヘッダー
//#############################################################
//	SYSTEM INCLUDES(基本的なヘッダーファイル)
//#############################################################
#include <iostream>		//入出力
#include <cstdlib>		//ランダムが使いたい
#include <cmath>		//数式を使いたい
#include <vector>		//動的配列を使いたい
#include <string>		//文字列を使いたい
#include <fstream>		//ファイルを扱いたい
#include <sstream>		//ストリングストリームを使いたい
#include <ctime>		//時間を量りたい
#include <algorithm>	//max()が使いたい
#include <iomanip>		//書式付出力がしたい
#include <float.h>		//DBL_MAXを使いたい
#include <stdio.h>

//#############################################################
//	OTHER INCLUDES(自作ヘッダーファイル等)
//#############################################################
#include "Linear3d/l3.h"	//幾何学計算まとめファイル
//#include "gnuplot\gnuplot.h"
//#include "Bspline/NonUniBspline.h"
#include "OpenGL/OpenGL.h"
//#include "HalfEdge/n-Solid.h"			//Solidモデルを扱う
#include "Voxel.h"			

//#############################################################
//	WORNING ERROR 回避
//#############################################################
#pragma warning(disable : 4996)//about scanf
#pragma warning(disable : 4244)//csparse　変換
