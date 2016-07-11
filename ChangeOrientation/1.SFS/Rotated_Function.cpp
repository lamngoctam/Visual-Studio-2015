#include "../stdafx.h"

extern int ImageNum;
extern CMatrix *ART;
extern int Surf_OctreeNum;

extern double MinVoxelL;			//Length of the model minimum voxel
extern double MinVoxelH;			//Height of the model minimum voxel


void SetVertexImage_Rotated(double Rotated_Angle, OctVoxel& box, Cpixel** vertexI, CMatrix* ART);
//void DividVoxelTo8_Rotated(double Rotated_Angle, short LV, OctVoxel& parent, CMatrix* ART, vector<cv::Mat>& Silhouette, vector<OctVoxel>& Octree);
void DividVoxelTo8_Rotated(double Rotated_Angle, short LV, OctVoxel& parent, CMatrix* ART, vector<cv::Mat>& Silhouette, vector<OctVoxel>& Octree);
void LineBlackWhite_Rotated(double Rotated_Angle, OctVoxel& box, vector<Mat>& Silhouette, Cpixel**vertexI, CMatrix* ART);

void SetVertexImage_Rotated2(double Rotated_Angle, OctVoxel& box, CVector3d* vertexW, Cpixel** vertexI, CMatrix* ART);
void DividVoxelTo8_Rotated2(double Rotated_Angle, short LV, OctVoxel& parent, CMatrix* ART, vector<cv::Mat>& Silhouette, vector<OctVoxel>& Octree);

void Rotated_BoundingBox_Arbitrary(double Rotated_Angle, OctVoxel& box, Cpixel** vertexI, CMatrix* ART);
//======================================================
//
//					For rotated
//======================================================
vector<CVector3d> display8point;

void Rotated_BoundingBox_Arbitrary(double Rotated_Angle, OctVoxel& box, Cpixel** vertexI, CMatrix* ART){

	CVector3d vertexW[8];
	box.SetVertexWorld_Rotated(Rotated_Angle, vertexW);

	CVector3d mid_point_center(0.0, 0.0, 0.0);
	CVector3d mid_point_down(0.0, 0.0, 0.0);
	mid_point_center = (vertexW[0] + vertexW[6]) / 2.0;
	mid_point_down = (vertexW[0] + vertexW[2]) / 2.0;

	CVector3d Rotated_Axis;
	Rotated_Axis = mid_point_center - mid_point_down;

	CMatrix Point_Original1(4, 4);
	CMatrix Point_Original2(4, 4);

	CMatrix Point_After_Rotated1(4, 4);
	CMatrix Point_After_Rotated2(4, 4);

	CMatrix D_TranslateToOrigin(4, 4);
	CMatrix Rx_Rotated_X_Axis(4, 4);
	CMatrix Ry_Rotated_Y_Axis(4, 4);
	CMatrix Rz_Rotated_Angle(4, 4);
	CMatrix Ry_1_Reverse(4, 4);
	CMatrix Rx_1_Reverse(4, 4);
	CMatrix D_1_Reverse_Traslation(4, 4);
	CMatrix Total_Transormation(4, 4);


	Point_Original1.SetZero();
	Point_Original2.SetZero();

	Point_After_Rotated1.SetZero();
	Point_After_Rotated2.SetZero();

	D_TranslateToOrigin.SetZero();
	Rx_Rotated_X_Axis.SetZero();
	Ry_Rotated_Y_Axis.SetZero();
	Rz_Rotated_Angle.SetZero();
	Ry_1_Reverse.SetZero();
	Rx_1_Reverse.SetZero();
	D_1_Reverse_Traslation.SetZero();
	Total_Transormation.SetZero();


	for (auto j(0); j < 4; ++j){
		Point_Original1.At(0, j) = vertexW[j].x;
		Point_Original1.At(1, j) = vertexW[j].y;
		Point_Original1.At(2, j) = vertexW[j].z;
		Point_Original1.At(3, j) = 1.0;
	}
		for (auto j(4); j < 8; ++j){
		Point_Original2.At(0, j) = vertexW[j].x;
		Point_Original2.At(1, j) = vertexW[j].y;
		Point_Original2.At(2, j) = vertexW[j].z;
		Point_Original2.At(3, j) = 1.0;
		
	}


	double A(0.0), B(0.0), C(0.0), L(0.0), V(0.0);
	A = mid_point_center.x - mid_point_down.x;
	B = mid_point_center.y - mid_point_down.y;
	C = mid_point_center.z - mid_point_down.z;

	L = sqrt(A*A + B*B + C*C);
	V = sqrt(B*B + C*C);

	cout << mid_point_center.x << " " << mid_point_center.y << " " << mid_point_center.z << endl;
	cout << mid_point_down.x << " " << mid_point_down.y << " " << mid_point_down.z << endl;


	cout << A << " " << B << " " << C << " " << L << " " << V << endl;
	getchar();

	for (auto i(0); i < 4; ++i){
		D_TranslateToOrigin.At(i, i) = 1.0;
		D_TranslateToOrigin.At(0, 3) = mid_point_down.x;
		D_TranslateToOrigin.At(1, 3) = mid_point_down.y;
		D_TranslateToOrigin.At(2, 3) = mid_point_down.z;
	}
	
	Rx_Rotated_X_Axis.At(0, 0) = Rx_Rotated_X_Axis.At(3, 3) = 1.0;
	Rx_Rotated_X_Axis.At(1, 1) = Rx_Rotated_X_Axis.At(2, 2) = C / V;
	Rx_Rotated_X_Axis.At(1, 2) = -B / V;
	Rx_Rotated_X_Axis.At(2, 1) = B / V;


	Ry_Rotated_Y_Axis.At(0, 0) = Ry_Rotated_Y_Axis.At(2, 2) = V / L;
	Ry_Rotated_Y_Axis.At(1, 1) = Ry_Rotated_Y_Axis.At(3, 3) = 1.0;
	Ry_Rotated_Y_Axis.At(0, 2) = -A / L;
	Ry_Rotated_Y_Axis.At(2, 0) = A / L;

	Rz_Rotated_Angle.At(2, 2) = Rz_Rotated_Angle.At(3, 3) = 1.0;
	Rz_Rotated_Angle.At(0, 0) = Rz_Rotated_Angle.At(1, 1) = cos(Rotated_Angle);
	Rz_Rotated_Angle.At(0, 1) = -sin(Rotated_Angle);
	Rz_Rotated_Angle.At(1, 0) = sin(Rotated_Angle);


	Ry_1_Reverse.At(0, 0) = Ry_1_Reverse.At(2, 2) = V / L;
	Ry_1_Reverse.At(1, 1) = Ry_1_Reverse.At(3, 3) = 1.0;
	Ry_1_Reverse.At(0, 2) = A / L;
	Ry_1_Reverse.At(2, 0) = -A / L;

	Rx_1_Reverse.At(0, 0) = Rx_1_Reverse.At(3, 3) = 1.0;
	Rx_1_Reverse.At(1, 1) = Rx_1_Reverse.At(1, 1) = C / V;
	Rx_1_Reverse.At(1, 2) = B / V;
	Rx_1_Reverse.At(2, 1) = -B / V;

	for (auto i(0); i < 4; ++i){
		D_1_Reverse_Traslation.At(i, i) = 1.0;
		D_1_Reverse_Traslation.At(0, 3) = -mid_point_down.x;
		D_1_Reverse_Traslation.At(1, 3) = -mid_point_down.y;
		D_1_Reverse_Traslation.At(2, 3) = -mid_point_down.z;
		
	}

	Total_Transormation = D_1_Reverse_Traslation*Rx_1_Reverse*Ry_1_Reverse*Rz_Rotated_Angle*Ry_Rotated_Y_Axis*Rx_Rotated_X_Axis*D_TranslateToOrigin;

	Point_After_Rotated1 = Total_Transormation* Point_Original1;
	Point_After_Rotated2 = Total_Transormation* Point_Original2;

	for (auto i(0); i < 4; ++i){
		for (auto j(0); j < 4; ++j){
			cout << setw(2) << Point_After_Rotated1.At(i, j) << endl;
		}
	}
	for (auto i(4); i < 8; ++i){
		for (auto j(4); j <8; ++j){
	//		cout << setw(2) << Point_After_Rotated2.At(i, j) << endl;
		}
	}
	getchar();

	for (auto j(0); j < 4; ++j){
		display8point[j].x = Point_After_Rotated1.At(0, j);
		display8point[j].y = Point_After_Rotated1.At(1, j);
		display8point[j].z = Point_After_Rotated1.At(2, j);
	}
	for (auto j(4); j < 8; ++j){
		display8point[j].x = Point_After_Rotated2.At(0, j);
		display8point[j].y = Point_After_Rotated2.At(1, j);
		display8point[j].z = Point_After_Rotated2.At(2, j);
	}

	getchar();

	CVector M(4);		//Homogeneous coordinates of the vertices(x,y,z,1) world coordinate
	CVector m(4);		//That the image coordinates (normalized) expressed in homogeneous coordinates
	M[3] = 1.0;

	for (int j = 0; j < ImageNum; ++j){		//36 image
		for (int k = 0; k < 8; ++k){	//8 vertices of the voxel
			M[0] = display8point[k].x;
			M[1] = display8point[k].y;
			M[2] = display8point[k].z;
			m = ART[j] * M;
			vertexI[j][k].setPixel_u_v((int)(m[0] / m[2]), (int)(m[1] / m[2]));  // normalize
		}
	}
	getchar();
}

////
void SetVertexImage_Rotated(double Rotated_Angle, OctVoxel& box, Cpixel** vertexI, CMatrix* ART){
	CVector M(4);		//Homogeneous coordinates of the vertices(x,y,z,1) world coordinate
	CVector m(4);		//That the image coordinates (normalized) expressed in homogeneous coordinates
	M[3] = 1.0;
	//8 vertices world coordinates of the voxel (x,y,z)
	CVector3d vertexW[8];
	box.SetVertexWorld_Rotated(Rotated_Angle, vertexW);
	//box.SetVertexWorld(vertexW);

	for (int j = 0; j < ImageNum; ++j){		//36 image
		for (int k = 0; k < 8; ++k){	//8 vertices of the voxel
			M[0] = vertexW[k].x;
			M[1] = vertexW[k].y;
			M[2] = vertexW[k].z;
			m = ART[j] * M;
			vertexI[j][k].setPixel_u_v((int)(m[0] / m[2]), (int)(m[1] / m[2]));  // normalize
		
			//cout << vertexW[k].x << "  " << vertexW[k].y << " " << vertexW[k].z << endl;		
		}

		//cout << M[0] << " " << M[1] << " " << M[2] << endl;
		
	}
}

void LineBlackWhite_Rotated(double Rotated_Angle, OctVoxel& box, vector<Mat>& Silhouette, Cpixel**vertexI, CMatrix* ART){
	int Bbox_line[12][2] =
	{
		{ 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 },
		{ 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 },
		{ 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 }
	};								//Vertex number 

	unsigned LineNum(0);			//Projecting the voxel in  silhouette, count the number of lines within the image.
	unsigned countWhite(0);			//the number of line of white pixels
	unsigned countBlack(0);			//the number of line of black pixels

	unsigned countWhiteLine(0);		//How many is the number of lines which are white among 12 lines? max 12
	unsigned countBlackLine(0);		//How many is the number of lines which are black among 12 lines? max 12

	unsigned countWhiteNum(0);		//How many is the number of voxel that is white in 36 images?
	unsigned countBlackNum(0);		//How many is the number of voxel that is black in 36 images?
	cv::Point Point_Start;			//initial point of the line
	cv::Point Point_End;			//terminal of the line

	CVector M(4);
	CVector m(4);
	M[3] = 1.0;

	CVector3d vertexW[8];

	for (int k = 0; k < ImageNum; k++)											//For 36 images
	{
		box.SetVertexWorld_Rotated(Rotated_Angle, vertexW);
		for (int h = 0; h < 8; ++h){											//8 vertices of the voxel
			M[0] = vertexW[h].x;
			M[1] = vertexW[h].y;
			M[2] = vertexW[h].z;
			m = ART[k] * M;
			vertexI[k][h].setPixel_u_v((int)(m[0] / m[2]), (int)(m[1] / m[2]));  // normalize
		}

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
			for (int i(0); i < it.count; i++, ++it){
				//Pixels from point A to point B from the left to the right.
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
				countWhiteLine++;			//increment white line
			}
			else if (countBlack == it.count)	//In the case of all black
			{
				countBlackLine++;				//increment black line
			}
			else if (it.count == 0)				//When there are 2 vertices of the line outside the image,
			{
				countBlackLine++;				//two vertices out of the image with a black lineÅIÅ@ÅÀ  increment black line
			}
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

void DividVoxelTo8_Rotated(double Rotated_Angle, short LV, OctVoxel& parent, CMatrix* ART, vector<cv::Mat>& Silhouette, vector<OctVoxel>& Octree)
{
	//Set the origin of the eight voxels after the voxel has been divided into eight
	OctVoxel children;					            //8 voxels after 8 dividing 1 voxel.
	children.SetParameter(parent.length / 2.0);		//Set the width and height of voxel

	CVector3d x(children.length, 0.0, 0.0);
	CVector3d y(0.0, children.length, 0.0);
	CVector3d z(0.0, 0.0, children.height);
	
	CVector3d vertexW[8];

	CVector3d x_rotated = x *cos(Rotated_Angle) - y*sin(Rotated_Angle);
	CVector3d y_rotated = x *sin(Rotated_Angle) + y*cos(Rotated_Angle);
	CVector3d z_rotated = z;

	vertexW[0] = parent.origin;
	vertexW[1] = parent.origin + x_rotated;
	vertexW[2] = parent.origin + x_rotated + y_rotated;
	vertexW[3] = parent.origin + y_rotated;
	vertexW[4] = parent.origin + z_rotated;
	vertexW[5] = parent.origin + z_rotated + x_rotated;
	vertexW[6] = parent.origin + z_rotated + x_rotated + y_rotated;
	vertexW[7] = parent.origin + z_rotated + y_rotated;
	
	Cpixel** vertexI;						//Points on 8 vertices of the imageÅÇRÇU imageÅ

	//dividid voxel
	for (int n = 0; n < 8; ++n){            //8 small devided voxel
		children.SetOrigin(vertexW[n]);		//Set the origin of 8 small devided voxel

		//if (children.LV < 0){
		//	cout << "children.LV " << children.LV <<"parent.LV "<<parent.LV<< endl;
		//	//getchar();
		//}
		vertexI = new Cpixel *[ImageNum];   //Allocate memory for 36 images coordinates of the voxel
		for (int i(0); i < ImageNum; i++)
			vertexI[i] = new Cpixel[8];
		//SetVertexImage_Rotated(Rotated_Angle, children, vertexI, ART);          //Return the image coordinates of 8 vertices from the child's origin
		//SetVertexImage(children, vertexI, ART);          //Return the image coordinates of 8 vertices from the child's origin
		//LineBlackWhite(children, Silhouette, vertexI);
		LineBlackWhite_Rotated(Rotated_Angle, children, Silhouette, vertexI, ART);	//Flag by projecting the voxel int the image (IN? or OUT? or AMB?)

		for (int i = 0; i < ImageNum; i++)
			delete[] vertexI[i];
		delete[] vertexI;

		if (children.in == true){						//If the voxel is within the silhouete,
			//Stop the split.(Stored in the vector of the voxel)
			children.LV = parent.LV + 1;
			Octree.push_back(children);
		
			
			//cout << "children.LV " << children.LV;
			//getchar();
			//CheckBoundingBox(ImageNum, children, Silhouette, vertexI);			
		}
		else if (children.amb == true){					// When voxel spans in a silhouette, 
			children.LV = parent.LV + 1;

			if (children.LV == LV){						//No longer divide it if a level reaches a division level

				if (children.in == true){				//in
					children.LV = parent.LV + 1;
					Octree.push_back(children);
					

				}
				else if (children.amb == true){			//amb
					children.LV = parent.LV + 1;
					Octree.push_back(children);
				

				}
				else{									//out
					//Do nothing
				}
			}
			else{
				//Divide it again if you have not yet reached the level
				//Furthermore divide.
				DividVoxelTo8_Rotated(Rotated_Angle, LV, children, ART, Silhouette, Octree);
			}
		}
		else{    // voxel is out     
		}
	}

}


void SetVertexImage_Rotated2(double Rotated_Angle, OctVoxel& box, CVector3d* vertexW, Cpixel** vertexI, CMatrix* ART){
	CVector M(4);		//Homogeneous coordinates of the vertices(x,y,z,1) world coordinate
	CVector m(4);		//That the image coordinates (normalized) expressed in homogeneous coordinates
	M[3] = 1.0;
	//8 vertices world coordinates of the voxel (x,y,z)	
	for (int j = 0; j < ImageNum; ++j){		//36 image
		for (int k = 0; k < 8; ++k){	//8 vertices of the voxel
			M[0] = vertexW[k].x;
			M[1] = vertexW[k].y;
			M[2] = vertexW[k].z;
			m = ART[j] * M;
			vertexI[j][k].setPixel_u_v((int)(m[0] / m[2]), (int)(m[1] / m[2]));  // normalize
		}
	}
}

void DividVoxelTo8_Rotated2(double Rotated_Angle, short LV, OctVoxel& parent, CMatrix* ART, vector<cv::Mat>& Silhouette, vector<OctVoxel>& Octree)
{
	//Set the origin of the eight voxels after the voxel has been divided into eight
	OctVoxel children;					            //8 voxels after 8 dividing 1 voxel.
	children.SetParameter(parent.length / 2.0);		//Set the width and height of voxel

	CVector3d x(children.length, 0.0, 0.0);
	CVector3d y(0.0, children.length, 0.0);
	CVector3d z(0.0, 0.0, children.height);

	CVector3d vertexW[8];

	CVector3d x_rotated = x *cos(Rotated_Angle) - y*sin(Rotated_Angle);
	CVector3d y_rotated = x *sin(Rotated_Angle) + y*cos(Rotated_Angle);
	CVector3d z_rotated = z;

	vertexW[0] = parent.origin;
	vertexW[1] = parent.origin + x_rotated;
	vertexW[2] = parent.origin + x_rotated + y_rotated;
	vertexW[3] = parent.origin + y_rotated;
	vertexW[4] = parent.origin + z_rotated;
	vertexW[5] = parent.origin + z_rotated + x_rotated;
	vertexW[6] = parent.origin + z_rotated + x_rotated + y_rotated;
	vertexW[7] = parent.origin + z_rotated + y_rotated;

	Cpixel** vertexI;						//Points on 8 vertices of the imageÅÇRÇU imageÅ

	//dividid voxel
	for (int n = 0; n < 8; ++n){            //8 small devided voxel
		children.SetOrigin(vertexW[n]);		//Set the origin of 8 small devided voxel

		//if (children.LV < 0){
		//	cout << "children.LV " << children.LV <<"parent.LV "<<parent.LV<< endl;
		//	//getchar();
		//}
		vertexI = new Cpixel *[ImageNum];   //Allocate memory for 36 images coordinates of the voxel
		for (int i(0); i < ImageNum; i++)
			vertexI[i] = new Cpixel[8];
		//SetVertexImage_Rotated(Rotated_Angle, children, vertexI, ART);          //Return the image coordinates of 8 vertices from the child's origin
		//SetVertexImage(children, vertexI, ART);          //Return the image coordinates of 8 vertices from the child's origin
		//LineBlackWhite(children, Silhouette, vertexI);
		LineBlackWhite_Rotated(Rotated_Angle, children, Silhouette, vertexI, ART);	//Flag by projecting the voxel int the image (IN? or OUT? or AMB?)

		for (int i = 0; i < ImageNum; i++)
			delete[] vertexI[i];
		delete[] vertexI;

		if (children.in == true){						//If the voxel is within the silhouete,
			//Stop the split.(Stored in the vector of the voxel)
			children.LV = parent.LV + 1;
			Octree.push_back(children);
			//Save_Down_Octrees.push_back(children);
		}
		else if (children.amb == true){					// When voxel spans in a silhouette, 
			children.LV = parent.LV + 1;

			if (children.LV == LV){						//No longer divide it if a level reaches a division level

				if (children.in == true){				//in
					//children.LV = parent.LV + 1;
					Octree.push_back(children);
					//Save_Down_Octrees.push_back(children);
				}
				else if (children.amb == true){			//amb
					//children.LV = parent.LV + 1;
					Octree.push_back(children);
					//Save_Down_Octrees.push_back(children);
				}
				else{									//out
					//Do nothing
				}
			}
			else{
				//Divide it again if you have not yet reached the level
				//Furthermore divide.
				DividVoxelTo8_Rotated2(Rotated_Angle, LV, children, ART, Silhouette, Octree);
			}
		}
		else{    // voxel is out     
		}
	}

}

void CheckBoundingBox(double Rotated_Angle, int ImageNum, OctVoxel BoundingBox, vector<cv::Mat>& Silhouette, Cpixel** vertexI, CMatrix *ART)
{
	string windowname("Is a model satisfied in a box");						//window's name
	cv::namedWindow(windowname, CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);	//create window
	double scale(0.5);						//Indication magnification
	cv::Size ssize((int)(Silhouette[0].size().width*scale), (int)(Silhouette[0].size().height*scale));
	cv::Mat img;							//copy

	int anchor[12][2] = {
		{ 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 },
		{ 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 },
		{ 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 }
	};										//Vertices number of 12 lines.
	cout << "Confirm whether bounding box is OK" << endl;

	cv::Point tempS;
	cv::Point tempE;
	cv::Point tempCircle;

	CVector M(4);		//Homogeneous coordinates of the vertices(x,y,z,1) world coordinate
	CVector m(4);		//That the image coordinates (normalized) expressed in homogeneous coordinates
	M[3] = 1.0;
	//8 vertices world coordinates of the voxel (x,y,z)
	CVector3d vertexW[8];
	BoundingBox.SetVertexWorld_Rotated(Rotated_Angle, vertexW);	//set BoundingBox with 8Vertex 

	for (int k = 0; k < ImageNum; ++k){
		Silhouette[k].copyTo(img);			//Copy the silhouette image in img.

		////1.Projection each vertex of voxel to image2D

		for (int j = 0; j < 8; ++j){		// 8 vertices of the voxel
			M[0] = vertexW[j].x;
			M[1] = vertexW[j].y;
			M[2] = vertexW[j].z;			// 3D world point
			m = ART[k] * M;					// m=A[RT]M
			vertexI[k][j].setPixel_u_v((int)(m[0] / m[2]), (int)(m[1] / m[2]));  // normalize
		}

		//2.Projection each edges of voxel to each silhouettes 

		for (int h(0); h < 12; ++h){
			//Draw 12 lines of the voxel in img.
			tempS.x = vertexI[k][anchor[h][0]].getPixel_u();
			tempS.y = vertexI[k][anchor[h][0]].getPixel_v();

			tempE.x = vertexI[k][anchor[h][1]].getPixel_u();
			tempE.y = vertexI[k][anchor[h][1]].getPixel_v();

			cv::line(img, tempS, tempE, cv::Scalar(255, 255, 255), 5, CV_AA);  // draw the 12 edges
			//cv::line( img, BoundingBox.vertexI[k][ anchor[h][0] ], BoundingBox.vertexI[k][ anchor[h][1] ], Scalar(255, 255, 255) , 5, CV_AA);
		}

		//Draw a circle on the origin
		tempCircle.x = vertexI[k][0].getPixel_u();
		tempCircle.y = vertexI[k][0].getPixel_v();

		cv::circle(img, tempCircle, 20, cv::Scalar(255, 255, 255), -1, CV_AA);	//Draw a circle on the origin
		//circle( img, BoundingBox.vertexI[k][0], 20, Scalar(255, 255, 255), -1, CV_AA); //Draw a circle on the origin

		//// Drawing 8 vertex circle of BoundingBox
		//for (int j = 0; j < 8; j++){
		//	//Draw a circle on the origin
		//	tempCircle.x = vertexI[k][j].getPixel_u();
		//	tempCircle.y = vertexI[k][j].getPixel_v();
		//	cv::circle(img, tempCircle, 20, cv::Scalar(255, 255, 255), -1, CV_AA);	//Draw a circle on the origin
		//}

		//Display silhouette image with bounding box was projected.
		//cv::resize(img, img, ssize, cv::INTER_NEAREST);
		//cv::imshow(windowname, img);				//show window
		//cv::waitKey(0);
	}
	destroyWindow(windowname);	//destory window
}

