#pragma once

//#############################################################
//	DEFINE(�g�p�����`�c�덷��臒l�����܂�)
//#############################################################
#define WIN32_LEAN_AND_MEAN	// Windows�w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
#define _USE_MATH_DEFINES	//�~����M_PI���g�����߂ɕK�v

// TODO: �v���O�����ɕK�v�Ȓǉ��w�b�_�[
//#############################################################
//	SYSTEM INCLUDES(��{�I�ȃw�b�_�[�t�@�C��)
//#############################################################
#include <iostream>		//���o��
#include <cstdlib>		//�����_�����g������
#include <cmath>		//�������g������
#include <vector>		//���I�z����g������
#include <string>		//��������g������
#include <fstream>		//�t�@�C������������
#include <sstream>		//�X�g�����O�X�g���[�����g������
#include <ctime>		//���Ԃ�ʂ肽��
#include <algorithm>	//max()���g������
#include <iomanip>		//�����t�o�͂�������
#include <float.h>		//DBL_MAX���g������
#include <stdio.h>

//#############################################################
//	OTHER INCLUDES(����w�b�_�[�t�@�C����)
//#############################################################
#include "Linear3d/l3.h"	//�􉽊w�v�Z�܂Ƃ߃t�@�C��
//#include "gnuplot\gnuplot.h"
//#include "Bspline/NonUniBspline.h"
#include "OpenGL/OpenGL.h"
//#include "HalfEdge/n-Solid.h"			//Solid���f��������
#include "Voxel.h"			

//#############################################################
//	WORNING ERROR ���
//#############################################################
#pragma warning(disable : 4996)//about scanf
#pragma warning(disable : 4244)//csparse�@�ϊ�
