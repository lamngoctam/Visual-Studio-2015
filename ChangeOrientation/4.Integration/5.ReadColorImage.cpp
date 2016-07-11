#include "../stdafx.h"

//                                                   
//                     
//                                                   
extern short angel;
void ReadColorImage(int ImageNum, string directory, string model,string pose,vector<cv::Mat>& Image)
{
	ostringstream SS;		//‰æ‘œêŠ
	for(int k(angel); k<ImageNum+angel; ++k){
		

		if(k<10){
			SS<< directory << model << pose << "obj_00" << k << ".tif";
			//SS<< directory << model << pose << "obj_00" << k << ".bmp";
			//SS<< directory << model << pose << "obj_00" << k << ".png";
			//cout<<SS.str()<<"“Ç‚İ‚ñ‚¾I"<<endl;
		}
		else if(k<36){
			SS<< directory << model << pose << "obj_0" << k << ".tif";
			//SS<< directory << model << pose << "obj_0" << k << ".bmp";
			//SS<< directory << model << pose << "obj_0" << k << ".png";
			//cout<<SS.str()<<"“Ç‚İ‚ñ‚¾I"<<endl;
		}
		else{
			SS<< directory << model << pose << "obj_00" << k-36 << ".tif";
			//SS<< directory << model << pose << "obj_00" << k-36 << ".bmp";
		
		}


		Image[k-angel] = cv::imread( SS.str(), CV_LOAD_IMAGE_COLOR);		
		
		if(!SS.str().data())
			cout<< SS.str() << " "<<endl;

		//ostringstream
		static const string empty_string;	//static
		//stringstream
		SS.str(empty_string);		//SS
		SS.clear();					//clear()
		SS<<dec;					//clear()
	
		//
		//namedWindow( "Color Image" , CV_WINDOW_AUTOSIZE | CV_WINDOW_KEEPRATIO);
		//imshow( "Color Image", Image[k]);
		//waitKey(0);
	}
	//destroyWindow("Color Image");	//window‚Ì”jŠü

}
