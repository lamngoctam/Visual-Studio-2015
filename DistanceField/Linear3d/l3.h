#pragma once
/****************************************************************
*	New!Linear3d												*
*	3�������W�̐V�E�v�Z���C�u�����ł��B							*
*									programed by Kineri			*
*	program ver. 1.6	2012.7.23								*
*	program ver. 1.7 	2012.7.24								*
*	program ver. 1.8	2012.8.8								*
*****************************************************************/
#define MACHINE_ERROR 1.0e-15
#pragma warning(disable : 4996)//about scanf

//CSparse�g�p�҂� #define USE_CSPARSE�������Ă�������
#ifdef USE_CSPARSE
#include "../Csparse3.0.1\cs.h"
#endif
#include "l3_cpoint3d.h"	//���_�N���X���C�u����
#include "l3_cmatrix.h"		//�s��v�Z���C�u����
#include "l3_cquat.h"		//�l�������C�u����
#include "l3_ccolor.h"		//�F��񃉃C�u����
#include <algorithm>