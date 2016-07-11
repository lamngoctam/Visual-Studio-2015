// stdafx.h : 

#ifndef ___STDAFX_H
#define ___STDAFX_H

#define _USE_MATH_DEFINES	//M_PI

// TODO: 


#include <iostream>		
#include <cstdlib>		
#include <cmath>		
#include <vector>		
#include <string>		
#include <fstream>		
#include <sstream>		
#include <ctime>		
#include <algorithm>	//max()
#include <iomanip>		
#include <float.h>		//DBL_MAX

#include "Linear3d/l3.h"		

#include <opencv2/opencv.hpp>	//OpenCV
#include <opencv2/contrib/contrib.hpp>

#include "Voxel.h"
#include "Cpixel.h"
#include "Brick.h"

#include "BrickTable.h"

#include "Index3D.h"
#include "Lego.h"

using namespace std;
using namespace cv;

//#ifndef _OPENMP
#include <omp.h>	    //OpenMP‚
//#endif



#endif