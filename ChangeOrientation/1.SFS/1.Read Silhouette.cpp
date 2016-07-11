#include "../stdafx.h"

extern short angel; //LEGO rotate
//       Silhouette reading function      
void ReadSilhouette(int ImageNum, string directory, string model, string pose, vector<Mat>& Silhouette)
{
	ostringstream SS;		

	for(int k=angel; k<ImageNum+angel; ++k){
		if(k<10){
			SS<< directory << model << pose << "result_00" << k << ".bmp";
			//cout<<SS.str()<<"ReadI"<<endl;
		}
		else if(k<36){
			SS<< directory << model << pose << "result_0" << k << ".bmp";
			//cout<<SS.str()<<"ReadI"<<endl;
		}
		else {
			SS<< directory << model << pose << "result_00" << k-36 << ".bmp";
		
		}

		Silhouette[k-angel] = imread( SS.str(), CV_LOAD_IMAGE_GRAYSCALE);		//Read the silhouette as a gray image
		if(!SS.str().data())
			cout<< SS.str() << "is not foundI"<<endl;

		//Clear the variable of istringstream
		static const string empty_string;	
		//To return the initial state
		SS.str(empty_string);		
		SS.clear();					
		SS<<dec;					

		//For confirmation 
		//display silhouette images
		//namedWindow( "Silhouette" , CV_WINDOW_AUTOSIZE | CV_WINDOW_KEEPRATIO);
		//imshow( "Silhouette", Silhouette[k]);
		//waitKey(0);
	}
	//destroyWindow("Silhouette");	
}
