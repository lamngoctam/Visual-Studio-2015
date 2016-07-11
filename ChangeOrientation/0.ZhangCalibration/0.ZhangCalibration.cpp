//============================================================================================
//http://docs.opencv.org/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html
//https://github.com/Itseez/opencv/blob/master/samples/cpp/calibration.cpp
//
//
//=============================================================

#include "../stdafx.h"
//from Function.h
extern string directory[2];
extern string model;
extern string pose[3];

int ZhangCalibration(int argc, char* argv[])
{
	const std::string windowNameSrc(" NameScreen ");
	const std::string windowNameUnd(" NameUnd");
	const int numberOfCheckerPatterns(36);

	cv::vector<cv::Mat> checkerImgs;
	//const cv::Size patternSize(8, 9);		//lion	
	//const cv::Size patternSize(7, 8);		//duck	
	const cv::Size patternSize(10, 9);	 //newpanda
	cv::vector<cv::vector<cv::Point3f>> worldPoints(numberOfCheckerPatterns);
	cv::vector<cv::vector<cv::Point2f>> imagePoints(numberOfCheckerPatterns);
	cv::TermCriteria criteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.001);


	cv::Mat									cameraMatrix;
	cv::Mat									distCoeffs;
	cv::vector<cv::Mat>				rotationVectors;
	cv::vector<cv::Mat>				rotationMatrix(numberOfCheckerPatterns);
	cv::vector<cv::Mat>				translationVectors;

	for (int i(0); i < numberOfCheckerPatterns; i++)
	{
		std::stringstream		stream;
		if (i<10) {
			stream << directory[0] << model << pose[2] << "calib_00" << i << ".TIF";
			//stream << directory[0] << model << pose[2] << "obj_00" <<  i << ".TIF";
		}
		else {
			stream << directory[0] << model << pose[2] << "calib_0" << i << ".TIF";
			//stream <<  directory[0] << model << pose[2] << "obj_0" <<  i << ".TIF";
		}
		std::string	fileName = stream.str();
		checkerImgs.push_back(cv::imread(fileName, 0));
		std::cout << "Load checker image: " << fileName << std::endl;
	}

	// imagePoints
//	cv::namedWindow(windowNameSrc, CV_WINDOW_AUTOSIZE);
	
	for (int i(0); i < numberOfCheckerPatterns; i++) {
		std::cout << "Find corners from image " << i + 1;
		if (cv::findChessboardCorners(checkerImgs[i], patternSize, imagePoints[i])) {
			std::cout << " ... All corners found." << std::endl;
			//
			cv::cornerSubPix(checkerImgs[i], imagePoints[i], cv::Size(11, 11), cv::Size(-1, -1), criteria);
			cv::drawChessboardCorners(checkerImgs[i], patternSize, (cv::Mat)(imagePoints[i]), true);
		//	cv::imshow(windowNameSrc, checkerImgs[i]);
		//	cv::waitKey(5);
		}
		else {
			std::cout << " ... at least 1 corner not found." << std::endl;
		//	cv::imshow(windowNameSrc, checkerImgs[i]);
			
		
		
		//cv::waitKey( 0 );
			//return -1;
		}
	}

	//
	for (int i = 0; i < numberOfCheckerPatterns; i++)
	{
		for (int j = 0; j < patternSize.area(); j++)
		{
			worldPoints[i].push_back(cv::Point3f(static_cast<float>(j % patternSize.width * 25),		//x座標
				static_cast<float>(j / patternSize.width * 25),																	//y座標
				0.0));																									//z座標 = 0.0
		}
	}

	//std::cout<<worldPoints[0]<<std::endl;
	//for(int i(0); i<numberOfCheckerPatterns; i++)
	//	for(int j(0); j<patternSize.area(); j++)
	//		std::cout<<	worldPoints[i][j]<<std::endl;

	//
	//cv::calibrateCamera( worldPoints, imagePoints, checkerImgs[0].size(), cameraMatrix, distCoeffs, rotationVectors, translationVectors);
	cv::calibrateCamera(worldPoints, imagePoints, checkerImgs[0].size(), cameraMatrix, distCoeffs, rotationVectors, translationVectors, 0 | CV_CALIB_FIX_K4 | CV_CALIB_FIX_K5);
	//std::cout<<"何かの係数 "<<distCoeffs<<std::endl;

	//
	std::cout << "Camera parameters have been estimated" << std::endl << std::endl;
	std::cout << cameraMatrix.at<double>(0, 0) << endl;
	//std::cout << cameraMatrix << std::endl;

	std::cout << "Rotation Vectors" << std::endl;
	for (int i(0); i<rotationVectors.size(); i++)
	{
		///std::cout << i+1 << "枚：" << rotationVectors[i] << std::endl;
		cv::Rodrigues(rotationVectors[i], rotationMatrix[i]);
		///std::cout << i+1 << "枚：" << rotationMatrix[i] << std::endl;
		//cv::invert(rotationMatrix[i], rotationMatrix[i]);
	}

	//CV_EXPORTS_W void cv::projectPoints( InputArray objectPoints,vector<Point3f>
	//                                InputArray rvec, InputArray tvec,
	//                                InputArray cameraMatrix, InputArray distCoeffs,
	//                                OutputArray imagePoints,	出力される，画像上の点の 2xN または Nx2 の1チャンネル配列，あるいは 1xN または Nx1 の2チャンネル配列． (あるいは vector<Point2f> )
	//                                OutputArray jacobian=noArray(),
	//                                double aspectRatio=0 );

	std::cout << "Transtation Vectors" << std::endl;
	for (int i(0); i < translationVectors.size(); i++) {
		///std::cout << i+1 << "枚：" << translationVectors[i] << std::endl;
	}

	//###########################
	//###########################
	std::stringstream File;
	File << directory[1] << model << pose[2] << "datain.txt";
	std::string InnerFileName = File.str();
	std::ofstream fout1(InnerFileName);
	for (int i(0); i<3; i++) {
		fout1 << cameraMatrix.at<double>(i, 0) << " " << cameraMatrix.at<double>(i, 1) << " " << cameraMatrix.at<double>(i, 2) << std::endl;
	}
	fout1 << 0.0 << " " << 0.0 << " " << 0.0 << " " << 0.0 << std::endl;

	//###########################
	//###########################
	for (int i(0); i < numberOfCheckerPatterns; i++)
	{
		std::stringstream stream;
		stream << directory[1] << model << pose[2] << "data" << i << ".txt";
		std::string OuterFileName = stream.str();
		std::ofstream fout(OuterFileName);
		for (int k(0); k<3; k++)
		{
			fout << rotationMatrix[i].at<double>(k, 0) << " " << rotationMatrix[i].at<double>(k, 1) << " " << rotationMatrix[i].at<double>(k, 2) << " " << translationVectors[i].at<double>(k) << std::endl;
		}
	}
	//for(int i(0); i<numberOfCheckerPatterns; i++)
	//{
	//	cv::Mat silhouette;
	//	cv::Mat silhouette1;
	//	std::stringstream stream1;
	//	if(i < 10){
	//	stream1 << "up/result_00" <<  i << ".bmp";
	//	}
	//	else{
	//	stream1 << "up/result_0" <<  i << ".bmp";
	//	}
	//	std::string fileName = stream1.str();
	//	std::stringstream stream2;
	//	stream2 << "upNew/result_" <<  i << ".bmp";
	//	std::string fileName2 = stream2.str();
	//	cv::undistort( cv::imread(fileName, 0), silhouette, cameraMatrix, distCoeffs );
	//	cv::imwrite(fileName2, silhouette);			//resultImgの画像をOutputImgNameに書き込む
	//}

	//std::cout << "Undistorted images" << std::endl;
	//cv::Mat	undistorted;
	//cv::namedWindow( windowNameUnd );
	//for( int i = 0; i < numberOfCheckerPatterns; i++ ) {
	//	cv::undistort( checkerImgs[i], undistorted, cameraMatrix, distCoeffs );
	//	cv::imshow( windowNameUnd, undistorted );
	//	cv::imshow( windowNameSrc, checkerImgs[i] );
	//	cv::waitKey( 0 );
	//}

	return 0;
}
