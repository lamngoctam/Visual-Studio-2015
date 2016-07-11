#include "../stdafx.h"
#include "../Voxel.h"

extern int ImageNum;
extern CMatrix *ART;
//First, the voxel 8 split.
//Next, each divided voxel sets the world coordinates and the image coordinates of the vertices.
//Then projecting 12 edges of voxels in the image. judge in,out,amb
//IN  finish the split
//OUT Throw away
//AMB Split again

Point Start_point;
Point End_point;
Point center;

vector<Point> PointStart;
vector<Point> PointEnd;
vector<Point> vertices;


void FindLargest_ProjectionVoxel(int ImageNum, vector<OctVoxel>& Octree, vector<cv::Mat>& Silhouette, Cpixel*** vertexII, CMatrix* ART);

void CheckContour(int ImageNum, vector<cv::Mat>& Silhouette, Cpixel** vertexII);



/** @function thresh_callback */
void thresh_callback(Mat src_gray, Mat& drawing, double scale, Size& ssize)
{
	RNG rng(12345);
	int thresh = 100;
	ofstream fout("larget_contour_area.txt");

	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	double max_contour_area(0.0);
	int largest_contour_index(0);

	/// Detect edges using canny
	Canny(src_gray, canny_output, thresh, thresh * 2, 3);
	/// Find contours
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// Get the moments
	vector<Moments> mu(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
		//cout << "# of contour points: " << contours[i].size() << endl;
		for (int j = 0; j < contours[i].size(); j++)
		{
			//cout << "Point(x,y)=" <<i<<" j "<<j<<" "<< contours[i][j] << endl;
		}
	}

	///  Get the mass centers:
	vector<Point2f> mc(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
	}

	//----------- Find the convex hull object for each contour
	vector<vector<Point>>hull(contours.size());
	for (int i = 0; i < contours.size(); i++){
		convexHull(Mat(contours[i]), hull[i], false);
	}

	//------------ Draw contours
	drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	//Size ssize;

	ssize = Size((int)(drawing.size().width * scale), (int)(drawing.size().height*scale));
	//the dst image size,e.g.100x100

	// Calculate the area with the moments 00 and compare with the result of the OpenCV function
	//printf("\t Info: Area and Contour Length \n");

	//cout << "contours.size() " << contours.size() << endl;
	double countour_Area(0.0), arc_Length(0.0);

	for (int i = 0; i < contours.size(); i++)
	{
		countour_Area = (double)contourArea(contours[i]);
		arc_Length = (double)arcLength(contours[i], true);

		//cout << "contourArea [" << i << "] " << ": Moment " << mu[i].m00 
		//	 << " OpenCV " << countour_Area << " arcLength " << arc_Length << endl;

		//cout << "countour_Area "<< countour_Area << " " << endl;
		if (countour_Area > max_contour_area){
			max_contour_area = countour_Area;
			largest_contour_index = i;
		}

		//------- draw all contour ---------------
		//Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		//drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
		//circle(drawing, mc[i], 4, color, -1, 8, 0);

	}
	//------- draw largest contour ---------------
	if (contours.size() > 0){
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, largest_contour_index, color, 1, 8, hierarchy, 0, Point());
		circle(drawing, mc[largest_contour_index], 4, color, -1, 8, 0);
		drawContours(drawing, hull, largest_contour_index, color, 1, 8, vector<Vec4i>(), 0, Point());
	}
	fout << max_contour_area << endl;
	cout << "max_contour_area " << max_contour_area << endl;

}

void condefects(vector<Vec4i>convexityDefectsSet, vector<Point> mycontour, Mat& drawing){
	for (int cDefIt = 0; cDefIt < convexityDefectsSet.size(); cDefIt++)
	{
		int startIdx = convexityDefectsSet[cDefIt].val[0]; Point ptStart(mycontour[startIdx]);
		int endIdx = convexityDefectsSet[cDefIt].val[1];	Point ptEnd(mycontour[endIdx]);
		int defectPtIdx = convexityDefectsSet[cDefIt].val[2]; Point ptFar(mycontour[defectPtIdx]);
		double depth = (double)convexityDefectsSet[cDefIt].val[3] / 256.0f;  // see documentation link below why this

		circle(drawing, ptStart, 5, CV_RGB(255, 0, 0), 2, 8);
		circle(drawing, ptEnd, 5, CV_RGB(255, 0, 0), 2, 8);
		circle(drawing, ptFar, 5, CV_RGB(255, 0, 0), 2, 8);
		// do something with *contour[defectPtIdx]*.. This is e.g. the defect point.

	}
}

void FindLargest_ProjectionVoxel(int ImageNum, vector<OctVoxel>& Octree, vector<cv::Mat>& Silhouette, Cpixel*** vertexII, CMatrix* ART){

	int thresh = 70;
	int max_thresh = 210;
	RNG rng(12345);

	Mat src_gray;
	Mat drawing;

	double scale(0.7);
	Size ssize;
	CVector M(4);		//Homogeneous coordinates of the vertices(x,y,z,1) world coordinate
	CVector m(4);		//That the image coordinates (normalized) expressed in homogeneous coordinates
	M[3] = 1.0;
	//8 vertices world coordinates of the voxel (x,y,z)
	CVector3d vertexW[8];

	ofstream fout("larget_boundingbox_contour.txt");

	int Boundingbox_line[12][2] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 },
	{ 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 },
	{ 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 } };

	//---------------------------------------------------------------	
	for (auto h(0); h < ImageNum; h++){
		//src_gray = Silhouette[h];         	
		Silhouette[h].copyTo(src_gray);
		cout << "Silhouette_" << h << endl;

		for (auto j(0); j < Octree.size(); j++){

			Octree[j].SetVertexWorld_Rotated(vertexW);
			for (int k = 0; k < 8; ++k){	//8 vertices of the voxel
				M[0] = vertexW[k].x;
				M[1] = vertexW[k].y;
				M[2] = vertexW[k].z;
				m = ART[h] * M;
				vertexII[h][j][k].setPixel_u_v((int)(m[0] / m[2]), (int)(m[1] / m[2]));  // normalize
			}

			//-------------------------------------- bounding box ------------------------
			for (auto k(0); k < 12; k++){
				//Draw 12 lines of the voxel in img.
				Start_point.x = vertexII[h][j][Boundingbox_line[k][0]].getPixel_u();
				Start_point.y = vertexII[h][j][Boundingbox_line[k][0]].getPixel_v();
				PointStart.push_back(Start_point);
				End_point.x = vertexII[h][j][Boundingbox_line[k][1]].getPixel_u();
				End_point.y = vertexII[h][j][Boundingbox_line[k][1]].getPixel_v();
				PointEnd.push_back(End_point);

				//line(src_gray, Start_point, End_point, Scalar(225, 225,255), 2.0, CV_AA);
			}
		}
		

		Mat canny_output;
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;

		double max_contour_area(0.0);
		int largest_contour_index(0);
		
		/// Detect edges using canny
		Canny(src_gray, canny_output, thresh, max_thresh, 3);
		/// Find contours
		//findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
		findContours(canny_output, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE, Point(0, 0));

		/// Draw contours
		drawing = Mat::zeros(canny_output.size(), CV_8UC3);

		for (auto n(0); n < PointEnd.size(); n++){
			line(drawing, PointStart[n], PointEnd[n], Scalar(225, 225, 225), 1.0, 1, 0);
		}

		/// Get the moments
		vector<Moments> mu(contours.size());
		for (int i = 0; i < contours.size(); i++)
		{
			mu[i] = moments(contours[i], false);
			//cout << "# of contour points: " << contours[i].size() << endl;
			for (int j = 0; j < contours[i].size(); j++)
			{
				//cout << "Point(x,y)=" <<i<<" j "<<j<<" "<< contours[i][j] << endl;
			}
		}
		////  Get the mass centers:
		vector<Point2f> mc(contours.size());
		for (int i = 0; i < contours.size(); i++)
		{
			mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
		}
		//// ---------- - Find the convex hull object for each contour
			vector<vector<Point>>hull(contours.size());
		for (int i = 0; i < contours.size(); i++){
			convexHull(Mat(contours[i]), hull[i], false);
		}				
		
		// Calculate the area with the moments 00 and compare with the result of the OpenCV function
		//printf("\t Info: Area and Contour Length \n");

		//cout << "contours.size() " << contours.size() << endl;
		double countour_Area(0.0);
		double arc_Length(0.0);

		for (int i = 0; i < contours.size(); i++)
		{
			countour_Area = (double)contourArea(contours[i]);
			arc_Length = (double)arcLength(contours[i], true);

			//cout << "contourArea [" << i << "] " << ": Moment " << mu[i].m00 
			//	 << " OpenCV " << countour_Area << " arcLength " << arc_Length << endl;		
			//cout << "countour_Area "<< countour_Area << " " << endl;

			if (countour_Area > max_contour_area){
				max_contour_area = countour_Area;
				largest_contour_index = i;
			}

			//------- draw all contour ---------------
			//Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
			//drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
			//circle(drawing, mc[i], 4, color, -1, 8, 0);
			//drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
			//drawContours(drawing, contours, i, Scalar(255, 255, 255), 0.10, 8, hierarchy, 0, Point());

		}
		//------- draw largest contour ---------------
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, largest_contour_index, color, 2, 8, hierarchy, 0, Point());
		//circle(drawing, mc[largest_contour_index], 4, color, -1, 8, 0);		
		//drawContours(drawing, contours, largest_contour_index, Scalar(0, 255, 255), 2, 8, hierarchy, 0, Point());
		//drawContours(drawing, hull, largest_contour_index, color, 2, 8, vector<Vec4i>(), 0, Point());
		//drawContours(drawing, contours, largest_contour_index, Scalar(255, 255, 255), 1, 8, hierarchy, 0, Point());

		fout << max_contour_area << endl;
		cout << "max_contour_area " << max_contour_area << endl;	
		
		//----------------------- Show in a window --------------------------------------
		//resize(drawing, drawing, ssize, INTER_NEAREST);
		namedWindow("Contours", CV_WINDOW_AUTOSIZE);
		imshow("Contours", drawing);

		//output white boundary
		imwrite("../../data2016/input/newzebra/contour_voxel/contour_voxel" + to_string(h) + ".bmp", drawing);

		waitKey(0);
		destroyWindow("silhouette");

		PointStart.clear();
		PointStart.shrink_to_fit();
		PointEnd.clear();
		PointEnd.shrink_to_fit();
	}

	//getchar();
}

void CheckContour(int ImageNum, vector<OctVoxel>& Octree, vector<cv::Mat>& Silhouette, Cpixel*** vertexII){
	FindLargest_ProjectionVoxel(ImageNum, Octree, Silhouette, vertexII, ART);
}

