#include "../stdafx.h"

extern int ImageNum;
extern CMatrix *ART;
extern int Surf_OctreeNum;


extern double MinVoxelL;			//Length of the model minimum voxel
extern double MinVoxelH;			//Height of the model minimum voxel



//First, the voxel 8 split.
//Next, each divided voxel sets the world coordinates and the image coordinates of the vertices.
//Then projecting 12 edges of voxels in the image. judge in,out,amb
//IN Å finish the split
//OUT Throw away
//AMB ÅSplit again



//Function prototype
void SetVertexImage(OctVoxel& box, Cpixel** vertexI, CMatrix* ART);
void LineBlackWhite(OctVoxel& box, vector<cv::Mat>& Silhouette, Cpixel** vertexI);



//-------------------------------------------------------------------------------
void DividVoxelTo8(short LV, OctVoxel& parent, CMatrix* ART, vector<cv::Mat>& Silhouette, vector<OctVoxel>& Octree)
{
	//Set the origin of the eight voxels after the voxel has been divided into eight
	OctVoxel children;					            //8 voxels after 8 dividing 1 voxel.
	children.SetParameter(parent.length / 2.0);		//Set the width and height of voxel
	Cpixel** vertexI;						       //Points on 8 vertices of the imageÅÇRÇU imageÅ

	CVector3d x(children.length, 0.0, 0.0);
	CVector3d y(0.0, children.length, 0.0);
	CVector3d z(0.0, 0.0, children.height);
	CVector3d vertexW[8];

	vertexW[0] = parent.origin;
	vertexW[1] = parent.origin + x;
	vertexW[2] = parent.origin + x + y;
	vertexW[3] = parent.origin + y;
	vertexW[4] = parent.origin + z;
	vertexW[5] = parent.origin + z + x;
	vertexW[6] = parent.origin + z + x + y;
	vertexW[7] = parent.origin + z + y;

	//dividid voxel
	for (int n = 0; n < 8; ++n){            // 8 Vertexs of voxel
		children.SetOrigin(vertexW[n]);		//Set the origin of voxel
		//Allocate memory for 36 images coordinates of the voxel
		vertexI = new Cpixel *[ImageNum];
		for (int i(0); i < ImageNum; i++)
			vertexI[i] = new Cpixel[8];

		SetVertexImage(children, vertexI, ART);			//Return the image coordinates of 8 vertices from the child's origin
		LineBlackWhite(children, Silhouette, vertexI);	//Flag by projecting the voxel int the image (IN? or OUT? or AMB?)

		//Release the memory of the image coordinates
		for (int i = 0; i < ImageNum; i++)
			delete[] vertexI[i];
		delete[] vertexI;

		//          If the voxel is within the silhouete,         
		if (children.in == true){
			//Stop the split.(Stored in the vector of the voxel)
			children.LV = parent.LV + 1;
			Octree.push_back(children);

			//CheckBoundingBox(ImageNum, children, Silhouette, vertexI);			
		}

		//       When voxel spans in a silhouette,      
		else if (children.amb == true){
			children.LV = parent.LV + 1;

			//cout << children.LV << " " << LV << endl;
			if (children.LV == LV){		//No longer divide it if a level reaches a division level
				//in
				if (children.in == true){
					children.LV = parent.LV + 1;
					Octree.push_back(children);

				}
				//amb
				else if (children.amb == true){
					children.LV = parent.LV + 1;
					Octree.push_back(children);
				}
				//out
				else{
					//Do nothing
				}
			}
			else{
				//Divide it again if you have not yet reached the level
				//Furthermore divide.
				DividVoxelTo8(LV, children, ART, Silhouette, Octree);
			}
		}
		//         voxel is out         
		else{

		}
	}


}

//Get 8 vertex of the image coordinates of the voxel to 36 images 
//Projection of voxel to images
void SetVertexImage(OctVoxel& box, Cpixel** vertexI, CMatrix* ART)
{
	CVector M(4);		//Homogeneous coordinates of the vertices(x,y,z,1) world coordinate
	CVector m(4);		//That the image coordinates (normalized) expressed in homogeneous coordinates
	M[3] = 1.0;
	//8 vertices world coordinates of the voxel (x,y,z)
	CVector3d vertexW[8];
	box.SetVertexWorld(vertexW);

	for (int j = 0; j < ImageNum; ++j){		//36 image
		for (int k = 0; k < 8; ++k){	//8 vertices of the voxel
			M[0] = vertexW[k].x;
			M[1] = vertexW[k].y;
			M[2] = vertexW[k].z;
			m = ART[j] * M;
			vertexI[j][k].setPixel_u_v((int)(m[0] / m[2]), (int)(m[1] / m[2]));  // normalize

			//cout << vertexW[k].x << " " << vertexW[k].y << " " << vertexW[k].z << endl;
		}

		     //cout << M[0] << " " << M[1] << " " << M[2] << endl;

	}
	//getchar();
}
//
void SetVertexImage(OctVoxel& box, Cpixel* vertexI, CMatrix& ART)
{
	CVector M(4);		//í∏ì_ÇÃìØéüç¿ïW
	CVector m(4);		//âÊëúç¿ïW(ê≥ãKâª)ÇìØéûç¿ïWÇ≈ï\ÇµÇΩÇ‡ÇÃ
	M[3] = 1.0;
	CVector3d vertexW[8];
	box.SetVertexWorld(vertexW);

	//É{ÉNÉZÉãÇÃ8í∏ì_
	for (int k = 0; k < 8; ++k){
		M[0] = vertexW[k].x;
		M[1] = vertexW[k].y;
		M[2] = vertexW[k].z;
		m = ART * M;
		vertexI[k].setPixel_u_v((int)(m[0] / m[2]), (int)(m[1] / m[2]));
	}
}



//InputÅFVoxel
//OutputÅFVoxel is in? out? amb?
//MethodÅF Make determinations whether in or out or amb usiing the 12 lines of voxels
void LineBlackWhite(OctVoxel& box, vector<cv::Mat>& Silhouette, Cpixel** vertexI)
{

	int Bbox_line[12][2] =
	{
		{ 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 },
		{ 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 },
		{ 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 }
	};								//Vertex number 

	unsigned LineNum(0);		//Projecting the voxel in  silhouette, count the number of lines within the image.
	unsigned countWhite(0);			//the number of line of white pixels
	unsigned countBlack(0);				//the number of line of black pixels

	unsigned countWhiteLine(0);		//How many is the number of lines which are white among 12 lines? max 12
	unsigned countBlackLine(0);		//How many is the number of lines which are black among 12 lines? max 12

	unsigned countWhiteNum(0);		//How many is the number of voxel that is white in 36 images?
	unsigned countBlackNum(0);		//How many is the number of voxel that is white in 36 images?
	cv::Point Point_Start;								//initial point of the line
	cv::Point Point_End;								//terminal of the line

	//#pragma omp parallel for//It is for parallel calculations
	for (int k = 0; k < ImageNum; k++)		//For 36 images
	{
		for (int h = 0; h < 12; h++)	//For 12 lines
		{
			Point_Start.x = vertexI[k][Bbox_line[h][0]].getPixel_u();
			Point_Start.y = vertexI[k][Bbox_line[h][0]].getPixel_v();

			Point_End.x = vertexI[k][Bbox_line[h][1]].getPixel_u();
			Point_End.y = vertexI[k][Bbox_line[h][1]].getPixel_v();

			//When 2 vertices of LineIterator protrude from image together, these become it.count == 0.
			//Generate it.count only of the thing that does not protrude when only one vertex protrudes from image.
			cv::LineIterator it(Silhouette[k], Point_Start, Point_End, 8, false);
			if (it.count != 0){ LineNum++; }
			//if it.countÅÇ0, line or part is projected on the image. increment LineNum

			//Count the white number of pixels on the line and a black number for one of 12 lines.
			for (int i(0); i < it.count; i++, ++it){	//Pixels from point A to point B from the left to the right.
				//if(it.ptr[1] == 255){
				if (*(it.ptr) == 255)		//luminance = 255(white)
				{
					countWhite++;
				}
				else						//luminance < 255(black)
				{
					countBlack++;
				}
			}

			if (countWhite == it.count)		//In the case of all white
			{
				countWhiteLine++;
			}		//increment white line
			else if (countBlack == it.count)	//In the case of all black
			{
				countBlackLine++;
			}		//increment black line
			else if (it.count == 0)			//When there are 2 vertices of the line outside the image,
			{
				countBlackLine++;
			}		//two vertices out of the image with a black lineÅIÅ@ÅÀ  increment black line
			else							//Otherwise
			{	//Do nothing
			}
			countWhite = 0;		//Initialization
			countBlack = 0;		//Initialization
		}

		if (countWhiteLine == LineNum)		//12 lines are white lines.
		{
			countWhiteNum++;
		}
		else if (countBlackLine == LineNum)	//12 lines are black lines.
		{
			countBlackNum++;
		}
		else								//Otherwise(white and a black line are mixed)
		{	//Do nothing
		}
		countWhiteLine = 0;		//Initialization
		countBlackLine = 0;		//Initialization
		LineNum = 0;

		//if(countBlackNum > 0)
		//	break;
	}

	//The voxel puts up the flag which which is in or out or amb.
	if (countWhiteNum == ImageNum)		//It is white in all 36 images.
	{
		box.in = true;				//Put up the internal flag
		box.out = false;
		box.amb = false;
	}
	else if (countBlackNum > 0)	//If there is black , judge to be outside.
	{
		box.in = false;
		box.out = true;				//Put up the external flag
		box.amb = false;
	}
	else						//otherwise ,voxel is amb.
	{
		box.in = false;
		box.out = false;
		box.amb = true;				//Put up the amb flag
	}


}

void CheckBoundingBox(int ImageNum, vector<cv::Mat>& Silhouette, Cpixel** vertexI){

	namedWindow("silhouette", CV_WINDOW_AUTOSIZE | CV_WINDOW_KEEPRATIO);
	double scale(0.7);
	Size ssize((int)(Silhouette[0].size().width * scale), (int)(Silhouette[0].size().height*scale));

	int Boundingbox_line[12][2] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 },
	{ 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 },
	{ 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 } };

	Point Start_point;
	Point End_point;
	Mat image;

	for (auto i(0); i < ImageNum; i++){
		Silhouette[i].copyTo(image);
		for (auto k(0); k < 12; k++){
			//Draw 12 lines of the voxel in img.
			Start_point.x = vertexI[i][Boundingbox_line[k][0]].getPixel_u();
			Start_point.y = vertexI[i][Boundingbox_line[k][0]].getPixel_v();

			End_point.x = vertexI[i][Boundingbox_line[k][1]].getPixel_u();
			End_point.y = vertexI[i][Boundingbox_line[k][1]].getPixel_v();

			line(image, Start_point, End_point, Scalar(225, 225, 225), 5, CV_AA);
		}

		for (auto h(4); h <5; h++){
			Point center;
			center.x = vertexI[i][1].getPixel_u();
			center.y = vertexI[i][1].getPixel_v();
			circle(image, center, 20, Scalar(255, 255, 255), -1, 8, CV_AA);
		}
		//display silhouette images
		resize(image, image, ssize, INTER_NEAREST);
		imshow("silhouette", image);
		waitKey(0);
	}

	destroyWindow("silhouette");

}



//-----------------------------------------------------------------------------------------------------------
//
//					find the contour area
//
// http://docs.opencv.org/2.4.2/doc/tutorials/imgproc/shapedescriptors/find_contours/find_contours.html
// http://docs.opencv.org/2.4/doc/tutorials/imgproc/shapedescriptors/moments/moments.html
//
//-----------------------------------------------------------------------------------------------------------

//void CheckBoundingBox(int ImageNum, vector<cv::Mat>& Silhouette, Cpixel** vertexI){
////Mat src;
//int thresh = 100;
//int max_thresh = 255;
//RNG rng(12345);
//
//	double scale(0.5);
//
//	int Boundingbox_line[12][2] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 },
//	{ 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 },
//	{ 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 } };
//
//	Point Start_point;
//	Point End_point;
//	Point tempCircle;
//	//double maxarea(0);
//	ofstream fout("larget_contour_area.txt");
//
//	for (auto h(0); h < ImageNum; h++){
//		cout << "Silhouette " << h << endl;
//
//		double max_contour_area(0.0);
//		int largest_contour_index(0);
//
//		Mat src_gray = Silhouette[h];
//
//		//for (auto k(0); k < 12; k++){
//		//	//Draw 12 lines of the voxel in img.
//		//	Start_point.x = vertexI[h][Boundingbox_line[k][0]].getPixel_u();
//		//	Start_point.y = vertexI[h][Boundingbox_line[k][0]].getPixel_v();
//		//
//		//	End_point.x = vertexI[h][Boundingbox_line[k][1]].getPixel_u();
//		//	End_point.y = vertexI[h][Boundingbox_line[k][1]].getPixel_v();
//		//
//		//	line(src_gray, Start_point, End_point, Scalar(225, 225, 225), 5, CV_AA);
//		//}
//		
//		Mat canny_output;
//		vector<vector<Point> > contours;
//		vector<Vec4i> hierarchy;
//
//		/// Detect edges using canny
//		Canny(src_gray, canny_output, thresh, thresh * 2, 3);
//		/// Find contours
//		findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
//
//		/// Get the moments
//		vector<Moments> mu(contours.size());
//		for (int i = 0; i < contours.size(); i++)
//		{
//			mu[i] = moments(contours[i], false);
//			//cout << "# of contour points: " << contours[i].size() << endl;
//			for (int j = 0; j < contours[i].size(); j++)
//			{
//				//cout << "Point(x,y)=" <<i<<" j "<<j<<" "<< contours[i][j] << endl;
//			}
//		}
//
//		///  Get the mass centers:
//		vector<Point2f> mc(contours.size());
//		for (int i = 0; i < contours.size(); i++)
//		{
//			mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
//		}
//
//		/// Draw contours
//		Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
//		Size ssize((int)(drawing.size().width * scale), (int)(drawing.size().height*scale));//the dst image size,e.g.100x100
//
//		// Calculate the area with the moments 00 and compare with the result of the OpenCV function
//		//printf("\t Info: Area and Contour Length \n");
//
//		//cout << "contours.size() " << contours.size() << endl;
//		double countour_Area(0.0), arc_Length(0.0);
//
//
//
//		for (int i = 0; i < contours.size(); i++)
//		{
//			countour_Area = (double)contourArea(contours[i]);
//			arc_Length = (double)arcLength(contours[i], true);
//
//			//cout << "contourArea [" << i << "] " << ": Moment " << mu[i].m00 
//			//	 << " OpenCV " << countour_Area << " arcLength " << arc_Length << endl;
//
//			//cout << countour_Area << " " << endl;
//			if (countour_Area > max_contour_area){
//				max_contour_area = countour_Area;
//				largest_contour_index = i;
//			}
//		}
//
//		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
//		drawContours(drawing, contours, largest_contour_index, Scalar(225, 225, 225), 2, 8, hierarchy, 0, Point());
//		//circle(drawing, mc[largest_contour_index], 4, color, -1, 8, 0);
//
//		fout << max_contour_area << endl;
//		//cout << "max_contour_area " << max_contour_area << endl;
//
//		////----------------------- bounding box ----------------------------------------
//		
//		for (auto k(0); k < 12; k++){
//			//Draw 12 lines of the voxel in img.
//			Start_point.x = vertexI[h][Boundingbox_line[k][0]].getPixel_u();
//			Start_point.y = vertexI[h][Boundingbox_line[k][0]].getPixel_v();
//		
//			End_point.x = vertexI[h][Boundingbox_line[k][1]].getPixel_u();
//			End_point.y = vertexI[h][Boundingbox_line[k][1]].getPixel_v();
//		
//			line(drawing, Start_point, End_point, Scalar(225, 225, 225), 5, CV_AA);
//		}
//		
//		for (auto i(0); i < 1; i++){
//			Point center;
//			center.x = vertexI[h][i].getPixel_u();
//			center.y = vertexI[h][i].getPixel_v();
//			circle(drawing, center, 20, Scalar(255, 255, 255), -1, 8, CV_AA);
//		}
//		
//		//------------------------------------------------------------------------------
//		//Show in a window
//		resize(drawing, drawing, ssize, INTER_NEAREST);
//		namedWindow("Contours", CV_WINDOW_AUTOSIZE);
//		imshow("Contours", drawing);
//
//		waitKey(0);
//		destroyWindow("silhouette");
//
//	}
//
//	//getchar();
//}


//void checkBBox(int ImageNum, vector<OctVoxel>& Octree, vector<cv::Mat>& Silhouette, Cpixel*** vertexII){
//
//	SetVertexImageII(Octree, vertexII, ART);
//	FindLargest_ProjectionVoxel(ImageNum, Octree, Silhouette, vertexII);
//
//}




