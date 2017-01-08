//
#include "../stdafx.h"
#include "OpenGL.h"
#include "OpenGLprimitive.h"
using namespace std;

extern OpenGL GLSettings2;
extern OpenGL GLSettings4;

extern OctVoxel Angle_;
extern CVector3d center_boundingbox;
extern vector<CVector3d> New_peak_octrees;

void GradientBackGround(float *tcolor, float *bcolor) {
	// 
	DisableLight();
	glMatrixMode(GL_MODELVIEW);  // ModelViews
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION); // Projections
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);    // DepthTest
	glBegin(GL_QUADS);
	glColor3fv(bcolor);
	glVertex3d(-1, -1, 0);
	glVertex3d(1, -1, 0);
	glColor3fv(tcolor);
	glVertex3d(1, 1, 0);
	glVertex3d(-1, 1, 0);
	glEnd();
	glEnable(GL_DEPTH_TEST);     // DepthTest
	glMatrixMode(GL_PROJECTION); // Projections
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);  // ModelViews
	glPopMatrix();
}

/*                                                 */
/*              Draw Bounding Box                  */
/*                                                 */
void DrawBoundingbox(CVector3d MaxPt, CVector3d MinPt) {
	glLineWidth(4.0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3d(MinPt.x, MaxPt.y, MaxPt.z);//1
	glVertex3d(MaxPt.x, MaxPt.y, MaxPt.z);//2
	glVertex3d(MaxPt.x, MaxPt.y, MinPt.z);//3
	glVertex3d(MinPt.x, MaxPt.y, MinPt.z);//4
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3d(MinPt.x, MinPt.y, MinPt.z);//8
	glVertex3d(MaxPt.x, MinPt.y, MinPt.z);//7
	glVertex3d(MaxPt.x, MinPt.y, MaxPt.z);//6
	glVertex3d(MinPt.x, MinPt.y, MaxPt.z);//5
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3d(MinPt.x, MaxPt.y, MaxPt.z);//1
	glVertex3d(MinPt.x, MaxPt.y, MinPt.z);//4
	glVertex3d(MinPt.x, MinPt.y, MinPt.z);//8
	glVertex3d(MinPt.x, MinPt.y, MaxPt.z);//5
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3d(MinPt.x, MaxPt.y, MaxPt.z);//1
	glVertex3d(MinPt.x, MinPt.y, MaxPt.z);//5
	glVertex3d(MaxPt.x, MinPt.y, MaxPt.z);//6
	glVertex3d(MaxPt.x, MaxPt.y, MaxPt.z);//2
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3d(MaxPt.x, MaxPt.y, MinPt.z);//3
	glVertex3d(MaxPt.x, MaxPt.y, MaxPt.z);//2
	glVertex3d(MaxPt.x, MinPt.y, MaxPt.z);//6
	glVertex3d(MaxPt.x, MinPt.y, MinPt.z);//7
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3d(MinPt.x, MaxPt.y, MinPt.z);//4
	glVertex3d(MaxPt.x, MaxPt.y, MinPt.z);//3
	glVertex3d(MaxPt.x, MinPt.y, MinPt.z);//7
	glVertex3d(MinPt.x, MinPt.y, MinPt.z);//8
	glEnd();
}

//#################################################
//
//#################################################
void ConclusiveAxis(void) {
	glLineWidth(1.0);
	double radius = 1.0;		
	double stringspace = 4.0;	

	CVector3d O(0.0, 0.0, 0.0);		CVector3d X(1.0, 0.0, 0.0);
	CVector3d Y(0.0, 1.0, 0.0);		CVector3d Z(0.0, 0.0, 1.0);

	CVector3d Os(-stringspace, -stringspace, -stringspace);
	CVector3d Xs(4.0*stringspace, -2.0* stringspace, 0.0);
	CVector3d Ys(-2.0*stringspace, 4.0*stringspace, 0.0);
	CVector3d Zs(0.0, -2.0*stringspace, 4.0*stringspace);

	glColor3d(0.0, 0.0, 0.0);
	DrawString("O", O + Os, GLUT_BITMAP_TIMES_ROMAN_24, GL2PS_TEXT_BL);

	//x
	glColor3d(1.0, 0.0, 0.0);
	DrawAllowOpt(-X, X, 50.0, radius, 3.5, 1.618*2.0, 12);
	DrawString("X", Xs, GLUT_BITMAP_TIMES_ROMAN_24, GL2PS_TEXT_BL);


	//y
	glColor3d(0.0, 1.0, 0.0);
	DrawAllowOpt(-Y, Y, 50.0, radius, 3.5, 1.618*2.0, 12);
	DrawString("Y", Ys, GLUT_BITMAP_TIMES_ROMAN_24, GL2PS_TEXT_BL);


	//z
	glColor3d(0.0, 0.0, 1.0);
	DrawAllowOpt(-Z, Z, 50.0, radius, 3.5, 1.618*2.0, 12);
	DrawString("Z", Zs, GLUT_BITMAP_TIMES_ROMAN_24, GL2PS_TEXT_BL);

}

//#################################################
//
//#################################################
void Draw_Center_Octree(Model& m) {
	//2016/5/19
	//glPointSize(9);
	glColor3d(0.5, 1.0, 0.5);
	glBegin(GL_POINTS);
	for (auto i(0); i < m.New_center_octrees.size(); ++i) {
		glVertex3d(m.New_center_octrees[i].x, m.New_center_octrees[i].y, m.New_center_octrees[i].z);
	}
	glEnd();
}
void Draw_VertexMin_Octree(Model& m) {
	glPointSize(8);
	glColor3d(0.5, 1.0, 0.5);
	glBegin(GL_POINTS);
	for (auto i(0); i < m.min_vertex_point.size(); ++i) {
		glVertex3d(m.min_vertex_point[i].x, m.min_vertex_point[i].y, m.min_vertex_point[i].z);
	}
	glEnd();
}
//
void Draw_origin_octrees(Model& m) {
	glPointSize(8);
	glColor3d(0.5, 1.0, 0.5);
	glBegin(GL_POINTS);
	for (auto i(0); i < m.New_origin_octrees.size(); ++i) {
		glVertex3d(m.New_origin_octrees[i].x, m.New_origin_octrees[i].y, m.New_origin_octrees[i].z);
	}
	glEnd();
}

void Draw_peak_octrees(Model& m) {
	glPointSize(8);
	glColor3d(0.5, 1.0, 0.5);
	glBegin(GL_POINTS);
	for (auto i(0); i < New_peak_octrees.size(); ++i) {
		glVertex3d(New_peak_octrees[i].x, New_peak_octrees[i].y, New_peak_octrees[i].z);
	}
	glEnd();
}

//###################################################
//                SFS Rotated    UP            
//###################################################
void DrawWireOctree_SFS_UP(OctVoxel &box)
{
	int line[12][2] =
	{ { 0, 1 },{ 1, 2 },{ 2, 3 },{ 3, 0 },
	{ 0, 4 },{ 1, 5 },{ 2, 6 },{ 3, 7 },
	{ 4, 5 },{ 5, 6 },{ 6, 7 },{ 7, 4 } };
	glLineWidth(3);
	glColor3d(1.0, 0.5, 0.5);
	CVector3d vertexW[8];
	//box.SetVertexWorld(vertexW);
	box.SetVertexWorld_Rotated(Angle_.Orientation_Angle, vertexW);

	for (int i(0); i < 12; ++i) {
		glBegin(GL_LINES);
		glVertex3d(vertexW[line[i][0]].x, vertexW[line[i][0]].y, vertexW[line[i][0]].z);
		glVertex3d(vertexW[line[i][1]].x, vertexW[line[i][1]].y, vertexW[line[i][1]].z);
		glEnd();
	}
}
void DrawWireOctreeModel_SFS_UP(vector<OctVoxel>& Octree)
{
	for (vector<OctVoxel>::iterator it = Octree.begin(); it != Octree.end(); ++it) {
		DrawWireOctree_SFS_UP(*it);
	}
}
void DrawFaceOctree_SFS_UP(OctVoxel &box)
{
	int line[6][4] =	{ { 0, 1, 2, 3 },	{ 4, 5, 6, 7 },	{ 0, 4, 7, 3 },	{ 1, 5, 4, 0 },	{ 2, 6, 5, 1 },	{ 3, 7, 6, 2 } };
	glColor3d(1.0, 0.0, 0.5);
	CVector3d vertexW[8];
	//box.SetVertexWorld(vertexW);
	box.SetVertexWorld_Rotated(Angle_.Orientation_Angle, vertexW);
	glBegin(GL_QUADS);
	for (int i(0); i < 6; ++i)
	{
		for (int k(0); k < 4; ++k){
			glVertex3d(vertexW[line[i][k]].x, vertexW[line[i][k]].y, vertexW[line[i][k]].z);
		}
	}
	glEnd();
}
//
void DrawFaceOctreeModel_SFS_UP(vector<OctVoxel>& Octree)
{
	int line[12][2] =
	{ { 0, 1 },{ 1, 2 },{ 2, 3 },{ 3, 0 },
	{ 0, 4 },{ 1, 5 },{ 2, 6 },{ 3, 7 },
	{ 4, 5 },{ 5, 6 },{ 6, 7 },{ 7, 4 } };
	glLineWidth(3);
	glColor3d(0.1, 0.0, 1.0);
	for (vector<OctVoxel>::iterator it = Octree.begin(); it != Octree.end(); ++it) {
		DrawFaceOctree_SFS_UP(*it);
	}
}
void DrawWire_BoundingBox_UP(OctVoxel &box)
{
	int line[12][2] =
	{ { 0, 1 },{ 1, 2 },{ 2, 3 },{ 3, 0 },
	{ 0, 4 },{ 1, 5 },{ 2, 6 },{ 3, 7 },
	{ 4, 5 },{ 5, 6 },{ 6, 7 },{ 7, 4 } };
	glLineWidth(3);
	glColor3d(0.5, 1.0, 1.0);
	CVector3d vertexW[8];
	box.SetVertexWorld_Rotated(Angle_.Orientation_Angle, vertexW);

	for (int i(0); i < 12; ++i) {
		glBegin(GL_LINES);
		glVertex3d(vertexW[line[i][0]].x, vertexW[line[i][0]].y, vertexW[line[i][0]].z);
		glVertex3d(vertexW[line[i][1]].x, vertexW[line[i][1]].y, vertexW[line[i][1]].z);

		glEnd();
	}

}
//###################################################
//                SFS Rotated       DOWN         
//###################################################
void DrawWireOctree_SFS_DOWN(OctVoxel &box)
{
	int line[12][2] =
	{ { 0, 1 },{ 1, 2 },{ 2, 3 },{ 3, 0 },
	{ 0, 4 },{ 1, 5 },{ 2, 6 },{ 3, 7 },
	{ 4, 5 },{ 5, 6 },{ 6, 7 },{ 7, 4 } };
	glLineWidth(3);
	glColor3d(0.8, 0.3, 0.7);
	CVector3d vertexW[8];
	//box.SetVertexWorld(vertexW);
	box.SetVertexWorld_Rotated(Angle_.Orientation_Angle, vertexW);

	for (int i(0); i < 12; ++i) {
		glBegin(GL_LINES);
		glVertex3d(vertexW[line[i][0]].x, vertexW[line[i][0]].y, vertexW[line[i][0]].z);
		glVertex3d(vertexW[line[i][1]].x, vertexW[line[i][1]].y, vertexW[line[i][1]].z);
		glEnd();
	}
}
void DrawWireOctreeModel_SFS_DOWN(vector<OctVoxel>& Octree)
{
	for (vector<OctVoxel>::iterator it = Octree.begin(); it != Octree.end(); ++it) {
		DrawWireOctree_SFS_DOWN(*it);
	}
}
void DrawFaceOctree_SFS_DOWN(OctVoxel &box)
{
	int line[6][4] = { { 0, 1, 2, 3 },{ 4, 5, 6, 7 },{ 0, 4, 7, 3 },{ 1, 5, 4, 0 },{ 2, 6, 5, 1 },{ 3, 7, 6, 2 } };
	glColor3d(0.8, 0.6, 0.5);
	CVector3d vertexW[8];
	//box.SetVertexWorld(vertexW);
	box.SetVertexWorld_Rotated(Angle_.Orientation_Angle, vertexW);
	glBegin(GL_QUADS);
	for (int i(0); i < 6; ++i)
	{
		for (int k(0); k < 4; ++k) {
			glVertex3d(vertexW[line[i][k]].x, vertexW[line[i][k]].y, vertexW[line[i][k]].z);
		}
	}
	glEnd();
}
void DrawFaceOctreeModel_SFS_DOWN(vector<OctVoxel>& Octree)
{
	int line[12][2] =
	{ { 0, 1 },{ 1, 2 },{ 2, 3 },{ 3, 0 },
	{ 0, 4 },{ 1, 5 },{ 2, 6 },{ 3, 7 },
	{ 4, 5 },{ 5, 6 },{ 6, 7 },{ 7, 4 } };
	glLineWidth(3);
	glColor3d(0.6, 0.4, 0.7);
	for (vector<OctVoxel>::iterator it = Octree.begin(); it != Octree.end(); ++it) {
		DrawFaceOctree_SFS_DOWN(*it);
	}
}

void DrawWire_BoundingBox_DOWN(OctVoxel &box)
{
	int line[12][2] =
	{ { 0, 1 },{ 1, 2 },{ 2, 3 },{ 3, 0 },
	{ 0, 4 },{ 1, 5 },{ 2, 6 },{ 3, 7 },
	{ 4, 5 },{ 5, 6 },{ 6, 7 },{ 7, 4 } };
	glLineWidth(3);
	glColor3d(0.0, 1.0, 0.5);
	CVector3d vertexW[8];
	box.SetVertexWorld_Rotated(Angle_.Orientation_Angle, vertexW);

	for (int i(0); i < 12; ++i) {
		glBegin(GL_LINES);
		glVertex3d(vertexW[line[i][0]].x, vertexW[line[i][0]].y, vertexW[line[i][0]].z);
		glVertex3d(vertexW[line[i][1]].x, vertexW[line[i][1]].y, vertexW[line[i][1]].z);

		glEnd();
	}

}


//###################################################
//                 LEGO    PCA Rotated                
//###################################################
void DrawWireOctree_PCA(Voxel& box)
{
	int line[12][2] =
	{ { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 },
	{ 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 },
	{ 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 } };
	glLineWidth(3);
	glColor3d(0.5, 0.5, 0.0);
	CVector3d vertexW[8];
	//box.SetVertexWorld(vertexW);
	box.SetVertexWorld_Rotated_PCA(Angle_.Orientation_Angle, vertexW);

	for (int i(0); i < 12; ++i) {
		glBegin(GL_LINES);
		glVertex3d(vertexW[line[i][0]].x, vertexW[line[i][0]].y, vertexW[line[i][0]].z);
		glVertex3d(vertexW[line[i][1]].x, vertexW[line[i][1]].y, vertexW[line[i][1]].z);

		glEnd();
	}

}

void DrawFaceOctree_PCA(Voxel& box) {
	int line[6][4] =
	{ { 0, 1, 2, 3 },
	{ 4, 5, 6, 7 },
	{ 0, 4, 7, 3 },
	{ 1, 5, 4, 0 },
	{ 2, 6, 5, 1 },
	{ 3, 7, 6, 2 } };

	glColor3d(0.5, 0.5, 1.0);
	CVector3d vertexW[8];
//	box.SetVertexWorld(vertexW);
	box.SetVertexWorld_Rotated_PCA(Angle_.Orientation_Angle, vertexW);

	glBegin(GL_QUADS);
	for (int i(0); i < 6; ++i)
	{
		for (int k(0); k < 4; ++k)
		{
			glVertex3d(vertexW[line[i][k]].x, vertexW[line[i][k]].y, vertexW[line[i][k]].z);
		}
	}
	glEnd();
}

void DrawFaceVoxelModel(vector<Voxel>&m) {

	for (vector<Voxel>::iterator it = m.begin(); it != m.end(); ++it) {
		DrawFaceOctree_PCA(*it);
	}
}


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//                                                   
//                draw Wire Octree     SFS               
//      
void Draw_Plane_Octree(Model& m) {

	EnableLight(3);
	for (int i(0); i < 6; ++i) {
		//DrawSphere(m.min_vertex_bbox[i], 1);      
	}
	DisableLight();

	EnableLight(4);
	for (int i(0); i < 8; ++i) {
		DrawSphere(m.New_smallcubicvertex[i], 0.3);
	}
	DisableLight();

	EnableLight(5);
	for (int i(0); i < 8; ++i) {
		DrawSphere(m.P_IntersecPoint[i], 0.25);
	}
	DisableLight();

	glPointSize(13);
	glColor3d(0.5, 0.0, 0.5);      // origin of octree after tranlation - rotation to OXYZ
	glBegin(GL_POINTS);
	for (auto i(0); i < m.Octrees.size(); ++i) {
		glVertex3d(m.Octrees[i].origin.x, m.Octrees[i].origin.y, m.Octrees[i].origin.z);
	}glEnd();



}

void Draw_Boundary_Octree(Model& m) {
	int line[12][2] =
	{ { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 },
	{ 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 },
	{ 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 } };

	glLineWidth(1);
	glColor3d(1.0, 0.5, 0.0);

	for (int i(0); i < 12; ++i) {
		glBegin(GL_LINES);
		glVertex3d(m.P_IntersecPoint[line[i][0]].x, m.P_IntersecPoint[line[i][0]].y, m.P_IntersecPoint[line[i][0]].z);
		glVertex3d(m.P_IntersecPoint[line[i][1]].x, m.P_IntersecPoint[line[i][1]].y, m.P_IntersecPoint[line[i][1]].z);
		glEnd();
	}

	glLineWidth(2);
	glColor3d(0.0, 0.5, 0.5);

	for (int i(0); i < 12; ++i) {
		glBegin(GL_LINES);
		glVertex3d(m.New_smallcubicvertex[line[i][0]].x, m.New_smallcubicvertex[line[i][0]].y, m.New_smallcubicvertex[line[i][0]].z);
		glVertex3d(m.New_smallcubicvertex[line[i][1]].x, m.New_smallcubicvertex[line[i][1]].y, m.New_smallcubicvertex[line[i][1]].z);
		glEnd();
	}

	glPointSize(9);
	glColor3d(0.5, 0.0, 0.5);  //check_plane2
	glBegin(GL_POINTS);
	for (auto i(0); i < m.Octrees.size(); ++i) {
		//glVertex3d(m.Octrees[i].Center_Octrees.x, m.Octrees[i].Center_Octrees.y, m.Octrees[i].Center_Octrees.z);
	}
	glEnd();

	//	glPointSize(9);
	//	glColor3d(0.5, 0.0, 0.5);  //check_plane2
	//	glBegin(GL_POINTS);
	//	for (auto i(0); i < m.Octrees.size(); ++i){
	//		glVertex3d(m.Octrees[i].Center_Octrees.x, m.Octrees[i].Center_Octrees.y, m.Octrees[i].Center_Octrees.z);
	//	}
	//	glEnd();

		//check New_Octree with LV< level
	glPointSize(9);
	glColor3d(0.5, 0.0, 0.5);  //check_plane2
	glBegin(GL_POINTS);
	for (auto i(0); i < m.Octrees.size(); ++i) {
		//glVertex3d(m.Octrees[i].origin.x, m.Octrees[i].origin.y, m.Octrees[i].origin.z);
	}
	glEnd();


}

void DrawWireOctree(OctVoxel &box, int colorID)
{
	int line[12][2] =
	{ { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 },
	{ 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 },
	{ 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 } };
	glLineWidth(3);
	//glColor3dv(GetColor(colorID)); 
	glColor3d(1.0, 0.5, 0.5);
	CVector3d vertexW[8];
	box.SetVertexWorld(vertexW);
	// box.SetVertexWorld_Rotated(Angle_.Orientation_Angle, vertexW);

	for (int i(0); i < 12; ++i) {
		glBegin(GL_LINES);
		glVertex3d(vertexW[line[i][0]].x, vertexW[line[i][0]].y, vertexW[line[i][0]].z);
		glVertex3d(vertexW[line[i][1]].x, vertexW[line[i][1]].y, vertexW[line[i][1]].z);

		glEnd();
	}

}

//                                                  
//                Draw face octree                  
//                                                  
void DrawFaceOctree(OctVoxel &box, int colorID)
{
	int line[6][4] =
	{ { 0, 1, 2, 3 },
	{ 4, 5, 6, 7 },
	{ 0, 4, 7, 3 },
	{ 1, 5, 4, 0 },
	{ 2, 6, 5, 1 },
	{ 3, 7, 6, 2 } };

	glColor3dv(GetColor(colorID)); // err
	//glColor3d(1.0, 0.0, 0.5);
	CVector3d vertexW[8];
	box.SetVertexWorld(vertexW);
	//box.SetVertexWorld_Rotated(Angle_.Orientation_Angle, vertexW);
	glBegin(GL_QUADS);
	for (int i(0); i < 6; ++i)
	{
		for (int k(0); k < 4; ++k)
		{
			glVertex3d(vertexW[line[i][k]].x, vertexW[line[i][k]].y, vertexW[line[i][k]].z);
		}
	}
	glEnd();
}

//                                                  
//            draw Octree model (wire)              
//                                                  
void DrawWireOctreeModel(vector<OctVoxel>& Octree, int colorID)
{
	for (vector<OctVoxel>::iterator it = Octree.begin(); it != Octree.end(); ++it) {
		DrawWireOctree(*it, 83);		
	}
}

//                                                                   
//            draw Octree model (face)              
//                                                                   
void DrawFaceOctreeModel(vector<OctVoxel>& Octree, int colorID)
{
	int line[12][2] =
	{ { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 },
	{ 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 },
	{ 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 } };
	glLineWidth(3);
	glColor3d(0.1, 0.0, 1.0);
	for (vector<OctVoxel>::iterator it = Octree.begin(); it != Octree.end(); ++it) {
		//if ((it->LV <6)){
		DrawFaceOctree(*it, colorID);
		//}

	}
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//                                                            
//           draw wire voxel                 
//                                                            
void DrawWireVoxel(CVector3d* vertexW)
{
	int line[12][2] =
	{ { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 },
	{ 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 },
	{ 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 } };
	glLineWidth(4);

	for (int i(0); i < 12; ++i) {
		glBegin(GL_LINES);
		glVertex3d(vertexW[line[i][0]].x, vertexW[line[i][0]].y, vertexW[line[i][0]].z);
		glVertex3d(vertexW[line[i][1]].x, vertexW[line[i][1]].y, vertexW[line[i][1]].z);
		glEnd();
	}

}

void DrawFaceVoxel(CVector3d* vertexW)
{

	int face[6][4] = {
		{ 0, 3, 2, 1 },		//Z
		{ 1, 2, 6, 5 },		//X
		{ 2, 3, 6, 7 },		//Y
		{ 3, 0, 4, 7 },		//X
		{ 0, 1, 5, 4 },		//Y
		{ 4, 5, 6, 7 }			//
	};

	GLdouble normal[6][3] = {
		{ 0.0, 0.0, -1.0 },		//Z
		{ 1.0, 0.0, 0.0 },	        //X
		{ 0.0, 1.0, 0.0 },		//Y
		{ -1.0, 0.0, 0.0 },		//X
		{ 0.0, -1.0, 0.0 },		//Y
		{ 0.0, 0.0, 1.0 }		//Z
	};

	glBegin(GL_QUADS);
	for (int i(0); i < 6; ++i)
	{
		glNormal3dv(normal[i]);
		for (int k(0); k < 4; ++k)
			glVertex3d(vertexW[face[i][k]].x, vertexW[face[i][k]].y, vertexW[face[i][k]].z);
	}
	glEnd();

}

//                                                                   
//            Draw Voxel model (wire)               
//                                                                   
void DrawWireVoxelModel(vector<Voxel>& m)
{
	//glColor3d(0.1, 0.1, 0.5);
	for (vector<Voxel>::iterator it = m.begin(); it != m.end(); ++it)
	{
		//DrawWireCuboid((*it).center, (*it).length);
		DrawWireOctree_PCA(*it);
	}
}


void DrawVoxelCenter(vector<CVector3d> &m, int colorID)
{
	//glColor3dv(GetColor(colorID));
	glColor3d(1.0, 0.5, 1.0);
	glPointSize(8.0);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	for (int i(0); i < m.size(); i++)
		glVertex3d(m[i].x, m[i].y, m[i].z);
	glEnd();

}

void DrawVoxelCenter(vector<CVector3d> &m, CMatrix &Rt, int colorID) {
	glColor3dv(GetColor(colorID));
	glPointSize(8.0);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	CVector NPt;  //new points
	CVector OPt;  //old points

	for (int i(0); i < m.size(); i++) {

		NPt.assign(4);//4sŠm•Û
		OPt.assign(4);//4sŠm•Û

		OPt[0] = m[i].x;
		OPt[1] = m[i].y;
		OPt[2] = m[i].z;
		OPt[3] = 1.0;

		NPt = Rt * OPt;
		glVertex3d(NPt[0], NPt[1], NPt[2]);
	}
	glEnd();

}


//###########################################
//              Draw Camera Position                                      
//###########################################
void DrawCameraPosition(CVector3d* pos)
{
	EnableLight(3);
	for (int i(0); i < 36; i++)
	{
		DrawSphere(pos[i], 4.0 + 0.1*i);
	}
	DisableLight();
}



//################################################
//                PCA
//################################################
void Draw_RotateBox(Voxel& DW, CMatrix &Rt)
{
	DisableLight();
	CVector NPt;//@new points
	CVector OPt;//@old points

	//8’¸“_‚ð•`ŽÊ
	CVector3d X(DW.length, 0.0, 0.0);
	CVector3d Y(0.0, DW.length, 0.0);
	CVector3d Z(0.0, 0.0, DW.height);

	//Rotate‘O‚ÌÀ•W
	CVector3d Pt[8];

	CVector3d x_rotated = X;	//X *cos(Angle_.Orientation_Angle) - Y*sin(Angle_.Orientation_Angle);
	CVector3d y_rotated = Y;	//X *sin(Angle_.Orientation_Angle) + Y*cos(Angle_.Orientation_Angle);
	CVector3d z_rotated = Z;



	Pt[0] = DW.origin;
	Pt[1] = DW.origin + X;
	Pt[2] = DW.origin + X + Y;
	Pt[3] = DW.origin + Y;

	Pt[4] = DW.origin + Z;
	Pt[5] = DW.origin + X + Z;
	Pt[6] = DW.origin + X + Y + Z;
	Pt[7] = DW.origin + Y + Z;

	//Rotate•W
	CVector3d Q[8];

	//
	int line[12][2] = { { 0, 1 }, { 1, 5 }, { 5, 4 }, { 4, 0 }, { 1, 2 }, { 2, 6 }, { 6, 5 }, { 6, 7 }, { 7, 4 }, { 7, 3 }, { 3, 2 }, { 3, 0 } };

	//8
	for (int i = 0; i < 8; i++)
	{
		NPt.assign(4);//4sŠm•Û
		OPt.assign(4);//4sŠm•Û

		OPt[0] = Pt[i].x;
		OPt[1] = Pt[i].y;
		OPt[2] = Pt[i].z;
		OPt[3] = 1.0;

		NPt = Rt * OPt;

		Q[i].x = NPt[0];
		Q[i].y = NPt[1];
		Q[i].z = NPt[2];
	}

	//
	for (int i = 0; i < 12; i++)
	{
		glBegin(GL_LINES);
		glVertex3d(Q[line[i][0]].x, Q[line[i][0]].y, Q[line[i][0]].z);
		glVertex3d(Q[line[i][1]].x, Q[line[i][1]].y, Q[line[i][1]].z);
		glEnd();
	}
}

void Draw_RotateVoxel(vector<Voxel>& m, CMatrix &Rt, double *color)
{
	glColor3dv(color);
	for (int i = 0; i < m.size(); i++)
	{
		Draw_RotateBox(m[i], Rt);
	}
}

//################################################
//                 ICP
//################################################
void DrawUnitNormal(vector<Voxel>& m, int colorID)
{
	EnableLight(7);
	for (vector<Voxel>::iterator it = m.begin(); it != m.end(); ++it)
		DrawAllowOpt((*it).center, (*it).normal, 4.0, 0.3, 1.8, 2.5, 12);
	DisableLight();
}
//                                                                    
//               
void DrawCorre(vector<CVector3d> &up, vector<CVector3d> &down)
{

	glColor3d(0.1, 0.7, 1.0);
	glLineWidth(4.0);

	glBegin(GL_LINES);
	for (int i(0); i < up.size(); i++)
	{
		glVertex3d(up[i].x, up[i].y, up[i].z);
		glVertex3d(down[i].x, down[i].y, down[i].z);
	}
	glEnd();

}

//-----------------------ICP-----------------
//-------------------------------------------                                                                  
//Draw Voxel model (solid)                                                                                
void DrawSolidVoxelModel(vector<Voxel>& m, int colorID)
{
	GLfloat white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat yellow[4] = { 0.8f, 0.8f, 0.0f, 1.0f };
	GLfloat shininess = 50;
	GLfloat light0_position[4] = { (float)GLSettings2.m_Eye.x, (float)GLSettings2.m_Eye.y, (float)GLSettings2.m_Eye.z, 1.0f };

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);

	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);


	CColor temp(GetColor(colorID));
	GLfloat color[4] = { (float)temp.r, (float)temp.g, (float)temp.b, 0.5f };
	int cnt(0);
	for (vector<Voxel>::iterator it = m.begin(); it != m.end(); ++it)
	{

		glPushName(cnt);
		if ((*it).pic) {
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
			DrawSolidCuboid((*it).center, (*it).length);
			//DrawFaceOctree_PCA(*it);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
			DrawWireCuboid((*it).center, (*it).length);
			//DrawWireOctree_PCA(*it);

		}
		else {
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
			DrawSolidCuboid((*it).center, (*it).length);
			//DrawFaceOctree_PCA(*it);

			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
			DrawWireCuboid((*it).center, (*it).length);
			//DrawWireOctree_PCA(*it);

		}
		glPopName();
		cnt++;
	}

	glDisable(GL_LIGHTING);
}


void DrawDown_After_Matrix(vector<Voxel>& m, int colorID, CMatrix& A)
{
	GLfloat white[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat black[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat blue[4] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat shininess = 50;
	GLfloat light0_position[4] = { (float)GLSettings2.m_Eye.x, (float)GLSettings2.m_Eye.y, (float)GLSettings2.m_Eye.z, 1.0f };

	//-------------------------------------
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);

	CColor Ctemp(GetColor(colorID));
	GLfloat color[4] = { (float)Ctemp.r, (float)Ctemp.g, (float)Ctemp.b, 0.3f };

	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

	CVector3d vertW[8];
	CMatrix temp(4, 1);
	int cnt(0);
	for (vector<Voxel>::iterator it = m.begin(); it != m.end(); ++it) {
		//it->SetVertexWorld(vertW); 
		//it->CoordTrans(A, vertW);		
		//DrawFaceVoxel(vertW);
		glPushName(cnt);
		temp(0, 0) = (*it).center.x;
		temp(1, 0) = (*it).center.y;
		temp(2, 0) = (*it).center.z;
		temp(3, 0) = 1.0;
		temp = A*temp;
		vertW[0].x = temp(0, 0);
		vertW[0].y = temp(1, 0);
		vertW[0].z = temp(2, 0);

		if ((*it).pic) {
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
			DrawSolidCuboid(vertW[0], (*it).length);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
			DrawWireCuboid(vertW[0], (*it).length);
		}
		else {
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
			DrawSolidCuboid(vertW[0], (*it).length);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
			DrawWireCuboid(vertW[0], (*it).length);
		}
		glPopName();
		cnt++;
	}

	glDisable(GL_LIGHTING);

}

//==============      2016/06/23            =========================
void DrawWireInteg_(Voxel& box, CColor& Vcolor)
{
	GLfloat color[4] = { (float)Vcolor.r, (float)Vcolor.g, (float)Vcolor.b, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

	int line[12][2] =
	{ { 0, 1 },{ 1, 2 },{ 2, 3 },{ 3, 0 },
	{ 0, 4 },{ 1, 5 },{ 2, 6 },{ 3, 7 },
	{ 4, 5 },{ 5, 6 },{ 6, 7 },{ 7, 4 } };
	glLineWidth(3);
	CVector3d vertexW[8];
	//box.SetVertexWorld(vertexW);
	box.SetVertexWorld_Rotated_PCA(Angle_.Orientation_Angle, vertexW);

	for (int i(0); i < 12; ++i) {
		glBegin(GL_LINES);
		glVertex3d(vertexW[line[i][0]].x, vertexW[line[i][0]].y, vertexW[line[i][0]].z);
		glVertex3d(vertexW[line[i][1]].x, vertexW[line[i][1]].y, vertexW[line[i][1]].z);

		glEnd();
	}

}

void DrawFaceIntegModel_(Voxel&m, CColor& Vcolor) {

	GLfloat color[4] = { (float)Vcolor.r, (float)Vcolor.g, (float)Vcolor.b, 0.9f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
	glShadeModel(GL_SMOOTH);

	int line[6][4] =
	{ { 0, 1, 2, 3 },
	{ 4, 5, 6, 7 },
	{ 0, 4, 7, 3 },
	{ 1, 5, 4, 0 },
	{ 2, 6, 5, 1 },
	{ 3, 7, 6, 2 } };

	CVector3d vertexW[8];
	//	box.SetVertexWorld(vertexW);
	m.SetVertexWorld_Rotated_PCA(Angle_.Orientation_Angle, vertexW);

	glBegin(GL_QUADS);
	for (int i(0); i < 6; ++i)
	{
		for (int k(0); k < 4; ++k)
		{
			glVertex3d(vertexW[line[i][k]].x, vertexW[line[i][k]].y, vertexW[line[i][k]].z);
		}
	}
	glEnd();

	
}
//----------           Coloring    --------
//-------------------------------------------   
//-------------------------------------------------------------------------------------
//                                                                                   
//                   Draw Color Solid Model                           
void DrawColorSolidModel(Model& integ)
{
	GLfloat color[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat white[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat black[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat shininess = 10;
	GLfloat light0_position[4] = { (float)GLSettings2.m_Eye.x, (float)GLSettings2.m_Eye.y, (float)GLSettings2.m_Eye.z, 1.0f };

	CColor Cblack(0.0, 0.0, 0.0);
	CColor Cblue(0.0, 0.0, 1.0);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);

	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	vector<CColor>::iterator itC = integ.SurfColors.begin();
	vector<Voxel>::iterator itV = integ.SurfVoxels.begin();
	while (itV != integ.SurfVoxels.end())
	{
		//DrawSolidCuboid(itV->center, itV->length, (*itC));
		
		DrawFaceIntegModel_(*itV, (*itC));
		
		//glColor3d(0,0,0);
		//for (int i = 0; i < itV->line.size(); i++)
		//	DrawAllow(itV->center,itV->line[i],itV->line[i].Norm(),1.5);
		//DrawSolidCuboid(itV->center, itV->length, Cblue);
		
		//DrawWireCuboid(itV->center, itV->length, Cblack);		
		DrawWireInteg_(*itV, Cblack);

		++itV;
		++itC;
	}
}


void Drawline(Model& integ, int num) {
	GLfloat color[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat white[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat black[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat shininess = 10;
	GLfloat light0_position[4] = { (float)GLSettings2.m_Eye.x, (float)GLSettings2.m_Eye.y, (float)GLSettings2.m_Eye.z, 1.0f };

	CColor Cblack(1.0, 0.0, 0.0);
	CColor Cblue(0.0, 0.0, 1.0);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);


	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	//vector<CColor>::iterator itC = integ.SurfColors.begin();
	//vector<Voxel>::iterator itV = integ.SurfVoxels.begin();
	//while(itV != integ.SurfVoxels.end())
	//{
	for (int i = 0; i < integ.SurfVoxels[num].line.size(); i++)
		DrawAllow(integ.SurfVoxels[num].center, integ.SurfVoxels[num].line[i], integ.SurfVoxels[num].line[i].Norm(), 0.5);
	//++itV;
	//++itC;
	//}
}
//                                                                                   
//                   Draw Color Solid Model                           
void DrawIsoVoxels(Model& integ)
{
	GLfloat color[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat white[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat black[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat shininess = 10;
	GLfloat light0_position[4] = { (float)GLSettings2.m_Eye.x, (float)GLSettings2.m_Eye.y, (float)GLSettings2.m_Eye.z, 1.0f };

	CColor Cblack(0.0, 0.0, 0.0);
	CColor Cred(1.0, 0.0, 0.0);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);

	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	vector<Voxel>::iterator itV = integ.IsoVoxels.begin();
	while (itV != integ.IsoVoxels.end())
	{
		//DrawSolidCuboid(itV->center, itV->length, Cred);
		//DrawWireCuboid(itV->center, itV->length, Cblack);
		DrawWireCuboid(itV->center, itV->length, Cred);
		//DrawSphere(itV->center, itV->length / 3);

		++itV;
	}
}


//##################################################
//					LEGO
//##################################################
void DrawGrid(Model& m, int Znum)
{
	glColor3d(0.0, 0.0, 0.0);
	glLineWidth(0.8f);
	glBegin(GL_LINES);
	for (int x(0); x <= m.num[0]; x++) {
		glVertex2i(x, 0);
		glVertex2i(x, m.num[1]);
	}
	for (int y(0); y <= m.num[1]; y++) {
		glVertex2i(0, y);
		glVertex2i(m.num[0], y);
	}
	glEnd();

}
void DrawSurfSquare(Model& m, Lego*** block, int Znum)
{
	//GLfloat white[4] = {1.0, 1.0, 1.0, 1.0};
	//GLfloat black[4] = {0.0, 0.0, 0.0, 1.0};
	//GLfloat shininess = 10;		
	//GLfloat light0_position[4] = { (float)GLSettings4.m_Eye.x, (float)GLSettings4.m_Eye.y, (float)GLSettings4.m_Eye.z, 1.0f };

	//
	//glEnable(GL_DEPTH_TEST);
	//glEnable( GL_NORMALIZE );
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);			

	//glLightfv(GL_LIGHT0, GL_POSITION, light0_position);			
	//glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, white);	
	//glLightfv(GL_LIGHT0, GL_SPECULAR, white);								

	//GLfloat color[4];

	//glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	//glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	//GLdouble normal[] = {1.0, 1.0, 1.0};

	glBegin(GL_QUADS);
	//glNormal3dv(normal);

	for (int x(1); x<m.num[0] - 1; x++)
	{
		for (int y(1); y<m.num[1] - 1; y++)
		{
			//###################################
			//P-P
			//###################################
			if (block[x][y][Znum].flag == 1)
			{
				//color[0] = (float)m.Voxel_colors[x][y][Znum].r;
				//color[1] = (float)m.Voxel_colors[x][y][Znum].g;
				//color[2] = (float)m.Voxel_colors[x][y][Znum].b;
				//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
				//if(m.Voxel_colors[x][y][Znum].r > 1)
				//	continue;
				//glColor3d(m.Voxel_colors[x][y][Znum].r, m.Voxel_colors[x][y][Znum].g, m.Voxel_colors[x][y][Znum].b );
				glColor4d(m.Voxel_colors[x][y][Znum].r, m.Voxel_colors[x][y][Znum].g, m.Voxel_colors[x][y][Znum].b, 0.8);
				glVertex2i(x, y);
				glVertex2i(x + 1, y);
				glVertex2i(x + 1, y + 1);
				glVertex2i(x, y + 1);
			}
			else if (block[x][y][Znum].flag > 1)
			{
				if (block[x][y][Znum].corner != 1)
					continue;
				//if(m.Voxel_colors[x][y][Znum].r > 1)
				//	continue;
				//color[0] = (float)m.Voxel_colors[x][y][Znum].r;
				//color[1] = (float)m.Voxel_colors[x][y][Znum].g;
				//color[2] = (float)m.Voxel_colors[x][y][Znum].b;
				//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
				//glColor3d(m.Voxel_colors[x][y][Znum].r, m.Voxel_colors[x][y][Znum].g, m.Voxel_colors[x][y][Znum].b );
				glColor4d(m.Voxel_colors[x][y][Znum].r, m.Voxel_colors[x][y][Znum].g, m.Voxel_colors[x][y][Znum].b, 0.8);

				//###################################
				//P-Q
				//###################################
				//else if(block[x][y][Znum].flag == 12 && block[x][y][Znum].corner == 1)
				if (block[x][y][Znum].flag == 12)
				{
					//‚P~‚Q‚ª‚™•ûŒü‚Ìê‡
					if (block[x][y + 1][Znum].flag == 12 && block[x][y][Znum].ID == block[x][y + 1][Znum].ID && block[x][y + 1][Znum].corner == 2)
					{
						glVertex2i(x, y);
						glVertex2i(x + 1, y);
						glVertex2i(x + 1, y + 2);
						glVertex2i(x, y + 2);
						continue;
					}
					//‚P~‚Q‚ª‚˜•ûŒü‚Ìê‡
					if (block[x + 1][y][Znum].flag == 12 && block[x][y][Znum].ID == block[x + 1][y][Znum].ID && block[x + 1][y][Znum].corner == 2)
					{
						glVertex2i(x, y);
						glVertex2i(x + 2, y);
						glVertex2i(x + 2, y + 1);
						glVertex2i(x, y + 1);
					}
				}
				//###################################
				//P-R
				//###################################
				//else if(block[x][y][Znum].flag == 13 && block[x][y][Znum].corner == 1)
				else if (block[x][y][Znum].flag == 13)
				{
					//‚P~‚R‚ª‚™•ûŒü‚Ìê‡
					if (y + 2 < m.num[1])
					{
						if (block[x][y + 2][Znum].flag == 13 && block[x][y][Znum].ID == block[x][y + 2][Znum].ID && block[x][y + 2][Znum].corner == 2)
						{
							glVertex2i(x, y);
							glVertex2i(x + 1, y);
							glVertex2i(x + 1, y + 3);
							glVertex2i(x, y + 3);
							continue;
						}
					}
					
					if (x + 2 < m.num[0])
					{
						if (block[x + 2][y][Znum].flag == 13 && block[x][y][Znum].ID == block[x + 2][y][Znum].ID && block[x + 2][y][Znum].corner == 2)
						{
							glVertex2i(x, y);
							glVertex2i(x + 3, y);
							glVertex2i(x + 3, y + 1);
							glVertex2i(x, y + 1);
						}
					}
				}

				//###################################
				//###################################
				//else if(block[x][y][Znum].flag == 14 && block[x][y][Znum].corner == 1)
				else if (block[x][y][Znum].flag == 14)
				{
					//‚P~‚S‚ª‚™•ûŒü‚Ìê‡
					if (y + 3 < m.num[1])
					{
						if (block[x][y + 3][Znum].flag == 14 && block[x][y][Znum].ID == block[x][y + 3][Znum].ID && block[x][y + 3][Znum].corner == 2)
						{
							glVertex2i(x, y);
							glVertex2i(x + 1, y);
							glVertex2i(x + 1, y + 4);
							glVertex2i(x, y + 4);
							continue;
						}
					}
					//‚P~‚S‚ª‚˜•ûŒü‚Ìê‡
					if (x + 3 < m.num[0])
					{
						if (block[x + 3][y][Znum].flag == 14 && block[x][y][Znum].ID == block[x + 3][y][Znum].ID && block[x + 3][y][Znum].corner == 2)
						{
							glVertex2i(x, y);
							glVertex2i(x + 4, y);
							glVertex2i(x + 4, y + 1);
							glVertex2i(x, y + 1);
						}
					}
				}
				//###################################
				//‚Q-Q
				//###################################
				//else if(block[x][y][Znum].flag == 22 && block[x][y][Znum].corner == 1)
				else if (block[x][y][Znum].flag == 22)
				{
					if (block[x + 1][y + 1][Znum].flag == 22 && block[x][y][Znum].ID == block[x + 1][y + 1][Znum].ID && block[x + 1][y + 1][Znum].corner == 2)
					{
						glVertex2i(x, y);
						glVertex2i(x + 2, y);
						glVertex2i(x + 2, y + 2);
						glVertex2i(x, y + 2);
					}
				}
				//###################################
				//‚Q~‚R‚Ìê‡
				//###################################
				//else if(block[x][y][Znum].flag == 23 && block[x][y][Znum].corner == 1)
				else if (block[x][y][Znum].flag == 23)
				{
					
					if (y + 2 < m.num[1])
					{
						if (block[x + 1][y + 2][Znum].flag == 23 && block[x][y][Znum].ID == block[x + 1][y + 2][Znum].ID && block[x + 1][y + 2][Znum].corner == 2)
						{
							glVertex2i(x, y);
							glVertex2i(x + 2, y);
							glVertex2i(x + 2, y + 3);
							glVertex2i(x, y + 3);
							continue;
						}
					}
					
					if (x + 2 < m.num[0])
					{
						if (block[x + 2][y + 1][Znum].flag == 23 && block[x][y][Znum].ID == block[x + 2][y + 1][Znum].ID && block[x + 2][y + 1][Znum].corner == 2)
						{
							glVertex2i(x, y);
							glVertex2i(x + 3, y);
							glVertex2i(x + 3, y + 2);
							glVertex2i(x, y + 2);
						}
					}
				}
				//###################################
				//
				//###################################
				//else if(block[x][y][Znum].flag == 24 && block[x][y][Znum].corner == 1)
				else if (block[x][y][Znum].flag == 24)
				{
					//‚Q~‚S‚ª‚™•ûŒü‚Ìê‡
					if (y + 3 < m.num[1])
					{
						if (block[x + 1][y + 3][Znum].flag == 24 && block[x][y][Znum].ID == block[x + 1][y + 3][Znum].ID && block[x + 1][y + 3][Znum].corner == 2)
						{
							glVertex2i(x, y);
							glVertex2i(x + 2, y);
							glVertex2i(x + 2, y + 4);
							glVertex2i(x, y + 4);
							continue;
						}
					}
					//‚Q~‚S‚ª‚˜•ûŒü‚Ìê‡
					if (x + 3 < m.num[0])
					{
						if (block[x + 3][y + 1][Znum].flag == 24 && block[x][y][Znum].ID == block[x + 3][y + 1][Znum].ID && block[x + 3][y + 1][Znum].corner == 2)
						{
							glVertex2i(x, y);
							glVertex2i(x + 4, y);
							glVertex2i(x + 4, y + 2);
							glVertex2i(x, y + 2);
						}
					}
				}
			}
		}
	}
	glEnd();

	//glDisable(GL_LIGHTING);
}

//###################################################
//                                                                   
//###################################################

void DrawBuildingInstruction(Model& m, Lego*** block, int Znum)
{
	glColor3d(0.0, 0.0, 0.9);
	glLineWidth(7.0);

	for (int x(1); x<m.num[0] - 1; x++)
	{
		for (int y(1); y<m.num[1] - 1; y++)
		{
			//###################################
			//P~P
			//###################################
			if (block[x][y][Znum].flag == 1)
			{
			
				glBegin(GL_LINE_LOOP);
				glVertex2i(x, y);
				glVertex2i(x + 1, y);
				glVertex2i(x + 1, y + 1);
				glVertex2i(x, y + 1);
				glEnd();
			}
			else if (block[x][y][Znum].flag > 1)
			{
				if (block[x][y][Znum].corner != 1)
					continue;
				//###################################
				//P~Q
				//###################################
				//else if(block[x][y][Znum].flag == 12 && block[x][y][Znum].corner == 1)
				if (block[x][y][Znum].flag == 12)
				{
					//P~Q
					if (block[x][y + 1][Znum].flag == 12 && block[x][y][Znum].ID == block[x][y + 1][Znum].ID && block[x][y + 1][Znum].corner == 2)
					{
						glBegin(GL_LINE_LOOP);
						glVertex2i(x, y);
						glVertex2i(x + 1, y);
						glVertex2i(x + 1, y + 2);
						glVertex2i(x, y + 2);
						glEnd();
					}
					//P~Q
					else if (block[x + 1][y][Znum].flag == 12 && block[x][y][Znum].ID == block[x + 1][y][Znum].ID && block[x + 1][y][Znum].corner == 2)
					{
						glBegin(GL_LINE_LOOP);
						glVertex2i(x, y);
						glVertex2i(x + 2, y);
						glVertex2i(x + 2, y + 1);
						glVertex2i(x, y + 1);
						glEnd();
					}
				}
				//###################################
				//
				//###################################
				//else if(block[x][y][Znum].flag == 13 && block[x][y][Znum].corner == 1)
				else if (block[x][y][Znum].flag == 13)
				{
					
					if (y + 2 < m.num[1])
					{
						if (block[x][y + 2][Znum].flag == 13 && block[x][y][Znum].ID == block[x][y + 2][Znum].ID && block[x][y + 2][Znum].corner == 2)
						{
							glBegin(GL_LINE_LOOP);
							glVertex2i(x, y);
							glVertex2i(x + 1, y);
							glVertex2i(x + 1, y + 3);
							glVertex2i(x, y + 3);
							glEnd();
							continue;
						}
					}
					
					if (x + 2 < m.num[0])
					{
						if (block[x + 2][y][Znum].flag == 13 && block[x][y][Znum].ID == block[x + 2][y][Znum].ID && block[x + 2][y][Znum].corner == 2)
						{
							glBegin(GL_LINE_LOOP);
							glVertex2i(x, y);
							glVertex2i(x + 3, y);
							glVertex2i(x + 3, y + 1);
							glVertex2i(x, y + 1);
							glEnd();
						}
					}
				}

				//###################################
				//P~S
				//###################################
				//else if(block[x][y][Znum].flag == 14 && block[x][y][Znum].corner == 1)
				else if (block[x][y][Znum].flag == 14)
				{
				
					if (y + 3 < m.num[1])
					{
						if (block[x][y + 3][Znum].flag == 14 && block[x][y][Znum].ID == block[x][y + 3][Znum].ID && block[x][y + 3][Znum].corner == 2)
						{
							glBegin(GL_LINE_LOOP);
							glVertex2i(x, y);
							glVertex2i(x + 1, y);
							glVertex2i(x + 1, y + 4);
							glVertex2i(x, y + 4);
							glEnd();
							continue;
						}
					}
				
					if (x + 3 < m.num[0])
					{
						if (block[x + 3][y][Znum].flag == 14 && block[x][y][Znum].ID == block[x + 3][y][Znum].ID && block[x + 3][y][Znum].corner == 2)
						{
							glBegin(GL_LINE_LOOP);
							glVertex2i(x, y);
							glVertex2i(x + 4, y);
							glVertex2i(x + 4, y + 1);
							glVertex2i(x, y + 1);
							glEnd();
						}
					}
				}
				//###################################
				//Q~Q
				//###################################
				//else if(block[x][y][Znum].flag == 22 && block[x][y][Znum].corner == 1)
				else if (block[x][y][Znum].flag == 22)
				{
					if (block[x + 1][y + 1][Znum].flag == 22 && block[x][y][Znum].ID == block[x + 1][y + 1][Znum].ID && block[x + 1][y + 1][Znum].corner == 2)
					{
						glBegin(GL_LINE_LOOP);
						glVertex2i(x, y);
						glVertex2i(x + 2, y);
						glVertex2i(x + 2, y + 2);
						glVertex2i(x, y + 2);
						glEnd();
					}
				}
				//###################################
				//
				//###################################
				//else if(block[x][y][Znum].flag == 23 && block[x][y][Znum].corner == 1)
				else if (block[x][y][Znum].flag == 23)
				{
					
					if (y + 2 < m.num[1])
					{
						if (block[x + 1][y + 2][Znum].flag == 23 && block[x][y][Znum].ID == block[x + 1][y + 2][Znum].ID && block[x + 1][y + 2][Znum].corner == 2)
						{
							glBegin(GL_LINE_LOOP);
							glVertex2i(x, y);
							glVertex2i(x + 2, y);
							glVertex2i(x + 2, y + 3);
							glVertex2i(x, y + 3);
							glEnd();
							continue;
						}
					}
					//
					if (x + 2 < m.num[0])
					{
						if (block[x + 2][y + 1][Znum].flag == 23 && block[x][y][Znum].ID == block[x + 2][y + 1][Znum].ID && block[x + 2][y + 1][Znum].corner == 2)
						{
							glBegin(GL_LINE_LOOP);
							glVertex2i(x, y);
							glVertex2i(x + 3, y);
							glVertex2i(x + 3, y + 2);
							glVertex2i(x, y + 2);
							glEnd();
						}
					}
				}
				//###################################
				//
				//###################################
				//else if(block[x][y][Znum].flag == 24 && block[x][y][Znum].corner == 1)
				else if (block[x][y][Znum].flag == 24)
				{
				
					if (y + 3 < m.num[1])
					{
						if (block[x + 1][y + 3][Znum].flag == 24 && block[x][y][Znum].ID == block[x + 1][y + 3][Znum].ID && block[x + 1][y + 3][Znum].corner == 2)
						{
							glBegin(GL_LINE_LOOP);
							glVertex2i(x, y);
							glVertex2i(x + 2, y);
							glVertex2i(x + 2, y + 4);
							glVertex2i(x, y + 4);
							glEnd();
							continue;
						}
					}
					
					if (x + 3 < m.num[0])
					{
						if (block[x + 3][y + 1][Znum].flag == 24 && block[x][y][Znum].ID == block[x + 3][y + 1][Znum].ID && block[x + 3][y + 1][Znum].corner == 2)
						{
							glBegin(GL_LINE_LOOP);
							glVertex2i(x, y);
							glVertex2i(x + 4, y);
							glVertex2i(x + 4, y + 2);
							glVertex2i(x, y + 2);
							glEnd();
						}
					}
				}
			}
		}
	}
	
	glLineWidth(2.0);
	char buf[5];	
	CVector3d v(-1.0, -1.0, 0.0);
	sprintf(buf, "%d", Znum);	
	glColor3d(0.0, 0.0, 0.0);		
	DrawString(buf, v, GLUT_BITMAP_TIMES_ROMAN_24, GL2PS_TEXT_BL);

}


//#############################################
//                                                            
//#############################################

void DrawBlocks_3D(Model& m, Lego*** block, int Znum)
{
	CVector3d scale_11(1.0, 1.0, 1.2);			
	CVector3d scale_12_y(1.0, 2.0, 1.2);		//
	CVector3d scale_12_x(2.0, 1.0, 1.2);		//
	CVector3d scale_13_y(1.0, 3.0, 1.2);		//
	CVector3d scale_13_x(3.0, 1.0, 1.2);		//
	CVector3d scale_14_y(1.0, 4.0, 1.2);		//
	CVector3d scale_14_x(4.0, 1.0, 1.2);		//
	CVector3d scale_22(2.0, 2.0, 1.2);		//
	CVector3d scale_23_y(2.0, 3.0, 1.2);		//
	CVector3d scale_23_x(3.0, 2.0, 1.2);		//
	CVector3d scale_24_y(2.0, 4.0, 1.2);		//
	CVector3d scale_24_x(4.0, 2.0, 1.2);		//

	CVector3d center;
	GLfloat color[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat white[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat black[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat shininess = 30;		
	GLfloat light0_position[4] = { (float)GLSettings4.m_Eye.x, (float)GLSettings4.m_Eye.y, (float)GLSettings4.m_Eye.z, 1.0f };

																															  //ŒõŒ¹‚ÌÝ’è--------------------------------------
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);			

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);				
	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, white);		
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);								

																			
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	glLineWidth(3.0);

	for (int x(1); x<m.num[0] - 1; x++)
	{
		for (int y(1); y<m.num[1] - 1; y++)
		{
			//###################################
			//P~P
			//###################################
			if (block[x][y][Znum].flag == 1)
			{
				center.x = x + 0.5;
				center.y = y + 0.5;
				center.z = 0.6;
			
				color[0] = (float)m.Voxel_colors[x][y][Znum].r;
				color[1] = (float)m.Voxel_colors[x][y][Znum].g;
				color[2] = (float)m.Voxel_colors[x][y][Znum].b;
				if (color[0] < 2) {
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
					DrawSolidBlock(center, scale_11);
				}
				
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
				DrawWireBlock(center, scale_11);
			}
			else if (block[x][y][Znum].flag > 1)
			{
				if (block[x][y][Znum].corner != 1)
					continue;

				//###################################
				//P~Q
				//###################################
				//else if(block[x][y][Znum].flag == 12 && block[x][y][Znum].corner == 1)
				if (block[x][y][Znum].flag == 12)
				{
					//‚P~‚Q‚ª‚™•ûŒü‚Ìê‡
					if (block[x][y + 1][Znum].flag == 12 && block[x][y][Znum].ID == block[x][y + 1][Znum].ID && block[x][y + 1][Znum].corner == 2)
					{
						center.x = x + 0.5;
						center.y = y + 1.0;
						center.z = 0.6;
						color[0] = (float)m.Voxel_colors[x][y][Znum].r;
						color[1] = (float)m.Voxel_colors[x][y][Znum].g;
						color[2] = (float)m.Voxel_colors[x][y][Znum].b;
						if (color[0] < 2) {
							glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
							DrawSolidBlock(center, scale_12_y);
						}
						glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
						DrawWireBlock(center, scale_12_y);
						continue;
					}
					
					if (block[x + 1][y][Znum].flag == 12 && block[x][y][Znum].ID == block[x + 1][y][Znum].ID && block[x + 1][y][Znum].corner == 2)
					{
						center.x = x + 1.0;
						center.y = y + 0.5;
						center.z = 0.6;
						color[0] = (float)m.Voxel_colors[x][y][Znum].r;
						color[1] = (float)m.Voxel_colors[x][y][Znum].g;
						color[2] = (float)m.Voxel_colors[x][y][Znum].b;
						if (color[0] < 2) {
							glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
							DrawSolidBlock(center, scale_12_x);
						}
						glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
						DrawWireBlock(center, scale_12_x);
					}
				}
				//###################################
				//
				//###################################
				//else if(block[x][y][Znum].flag == 13 && block[x][y][Znum].corner == 1)
				else if (block[x][y][Znum].flag == 13)
				{
				
					if (y + 2 < m.num[1])
					{
						if (block[x][y + 2][Znum].flag == 13 && block[x][y][Znum].ID == block[x][y + 2][Znum].ID && block[x][y + 2][Znum].corner == 2)
						{
							center.x = x + 0.5;
							center.y = y + 1.5;
							center.z = 0.6;
							color[0] = (float)m.Voxel_colors[x][y][Znum].r;
							color[1] = (float)m.Voxel_colors[x][y][Znum].g;
							color[2] = (float)m.Voxel_colors[x][y][Znum].b;
							if (color[0] < 2) {
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
								DrawSolidBlock(center, scale_13_y);
							}
							glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
							DrawWireBlock(center, scale_13_y);
							continue;
						}
					}
					
					if (x + 2 < m.num[0])
					{
						if (block[x + 2][y][Znum].flag == 13 && block[x][y][Znum].ID == block[x + 2][y][Znum].ID && block[x + 2][y][Znum].corner == 2)
						{
							center.x = x + 1.5;
							center.y = y + 0.5;
							center.z = 0.6;
							color[0] = (float)m.Voxel_colors[x][y][Znum].r;
							color[1] = (float)m.Voxel_colors[x][y][Znum].g;
							color[2] = (float)m.Voxel_colors[x][y][Znum].b;
							if (color[0] < 2) {
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
								DrawSolidBlock(center, scale_13_x);
							}
							glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
							DrawWireBlock(center, scale_13_x);
						}
					}
				}

				//###################################
				//P~S
				//###################################
				//else if(block[x][y][Znum].flag == 14 && block[x][y][Znum].corner == 1)
				else if (block[x][y][Znum].flag == 14)
				{
					//‚P~‚S‚ª‚™•ûŒü‚Ìê‡
					if (y + 3 < m.num[1])
					{
						if (block[x][y + 3][Znum].flag == 14 && block[x][y][Znum].ID == block[x][y + 3][Znum].ID && block[x][y + 3][Znum].corner == 2)
						{
							center.x = x + 0.5;
							center.y = y + 2.0;
							center.z = 0.6;
							color[0] = (float)m.Voxel_colors[x][y][Znum].r;
							color[1] = (float)m.Voxel_colors[x][y][Znum].g;
							color[2] = (float)m.Voxel_colors[x][y][Znum].b;
							if (color[0] < 2) {
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
								DrawSolidBlock(center, scale_14_y);
							}
							glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
							DrawWireBlock(center, scale_14_y);
							continue;
						}
					}
					
					if (x + 3 < m.num[0])
					{
						if (block[x + 3][y][Znum].flag == 14 && block[x][y][Znum].ID == block[x + 3][y][Znum].ID && block[x + 3][y][Znum].corner == 2)
						{
							center.x = x + 2.0;
							center.y = y + 0.5;
							center.z = 0.6;
							color[0] = (float)m.Voxel_colors[x][y][Znum].r;
							color[1] = (float)m.Voxel_colors[x][y][Znum].g;
							color[2] = (float)m.Voxel_colors[x][y][Znum].b;
							if (color[0] < 2) {
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
								DrawSolidBlock(center, scale_14_x);
							}
							glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
							DrawWireBlock(center, scale_14_x);
						}
					}
				}
				//###################################
				//Q~Q
				//###################################
				//else if(block[x][y][Znum].flag == 22 && block[x][y][Znum].corner == 1)
				else if (block[x][y][Znum].flag == 22)
				{
					if (block[x + 1][y + 1][Znum].flag == 22 && block[x][y][Znum].ID == block[x + 1][y + 1][Znum].ID && block[x + 1][y + 1][Znum].corner == 2)
					{
						center.x = x + 1.0;
						center.y = y + 1.0;
						center.z = 0.6;
						color[0] = (float)m.Voxel_colors[x][y][Znum].r;
						color[1] = (float)m.Voxel_colors[x][y][Znum].g;
						color[2] = (float)m.Voxel_colors[x][y][Znum].b;
						if (color[0] < 2) {
							glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
							DrawSolidBlock(center, scale_22);
						}
						glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
						DrawWireBlock(center, scale_22);
					}
				}
				//###################################
				//Q~R
				//###################################
				//else if(block[x][y][Znum].flag == 23 && block[x][y][Znum].corner == 1)
				else if (block[x][y][Znum].flag == 23)
				{
					
					if (y + 2 < m.num[1])
					{
						if (block[x + 1][y + 2][Znum].flag == 23 && block[x][y][Znum].ID == block[x + 1][y + 2][Znum].ID && block[x + 1][y + 2][Znum].corner == 2)
						{
							center.x = x + 1.0;
							center.y = y + 1.5;
							center.z = 0.6;
							color[0] = (float)m.Voxel_colors[x][y][Znum].r;
							color[1] = (float)m.Voxel_colors[x][y][Znum].g;
							color[2] = (float)m.Voxel_colors[x][y][Znum].b;
							if (color[0] < 2) {
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
								DrawSolidBlock(center, scale_23_y);
							}
							glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
							DrawWireBlock(center, scale_23_y);
							continue;
						}
					}
				
					if (x + 2 < m.num[0])
					{
						if (block[x + 2][y + 1][Znum].flag == 23 && block[x][y][Znum].ID == block[x + 2][y + 1][Znum].ID && block[x + 2][y + 1][Znum].corner == 2)
						{
							center.x = x + 1.5;
							center.y = y + 1.0;
							center.z = 0.6;
							color[0] = (float)m.Voxel_colors[x][y][Znum].r;
							color[1] = (float)m.Voxel_colors[x][y][Znum].g;
							color[2] = (float)m.Voxel_colors[x][y][Znum].b;
							if (color[0] < 2) {
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
								DrawSolidBlock(center, scale_23_x);
							}
							glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
							DrawWireBlock(center, scale_23_x);
						}
					}
				}
				//###################################
				//Q~S
				//###################################
				//else if(block[x][y][Znum].flag == 24 && block[x][y][Znum].corner == 1)
				else if (block[x][y][Znum].flag == 24)
				{
					//
					if (y + 3 < m.num[1])
					{
						if (block[x + 1][y + 3][Znum].flag == 24 && block[x][y][Znum].ID == block[x + 1][y + 3][Znum].ID && block[x + 1][y + 3][Znum].corner == 2)
						{
							center.x = x + 1.0;
							center.y = y + 2.0;
							center.z = 0.6;
							color[0] = (float)m.Voxel_colors[x][y][Znum].r;
							color[1] = (float)m.Voxel_colors[x][y][Znum].g;
							color[2] = (float)m.Voxel_colors[x][y][Znum].b;
							if (color[0] < 2) {
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
								DrawSolidBlock(center, scale_24_y);
							}
							glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
							DrawWireBlock(center, scale_24_y);
							continue;
						}
					}
					if (x + 3 < m.num[0])
					{
						if (block[x + 3][y + 1][Znum].flag == 24 && block[x][y][Znum].ID == block[x + 3][y + 1][Znum].ID && block[x + 3][y + 1][Znum].corner == 2)
						{
							center.x = x + 2.0;
							center.y = y + 1.0;
							center.z = 0.6;
							color[0] = (float)m.Voxel_colors[x][y][Znum].r;
							color[1] = (float)m.Voxel_colors[x][y][Znum].g;
							color[2] = (float)m.Voxel_colors[x][y][Znum].b;
							if (color[0] < 2) {
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
								DrawSolidBlock(center, scale_24_x);
							}
							glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
							DrawWireBlock(center, scale_24_x);
						}
					}
				}
			}
		}
	}

}


//###########################################
//                                                               
//###########################################
void DrawBlockModel(Model& m, Lego*** block)
{
	CVector3d scale_11(1.0, 1.0, 1.2);			
	CVector3d scale_12_y(1.0, 2.0, 1.2);		//
	CVector3d scale_12_x(2.0, 1.0, 1.2);		//
	CVector3d scale_13_y(1.0, 3.0, 1.2);		//
	CVector3d scale_13_x(3.0, 1.0, 1.2);		//
	CVector3d scale_14_y(1.0, 4.0, 1.2);		//
	CVector3d scale_14_x(4.0, 1.0, 1.2);		//
	CVector3d scale_22(2.0, 2.0, 1.2);			
	CVector3d scale_23_y(2.0, 3.0, 1.2);		//
	CVector3d scale_23_x(3.0, 2.0, 1.2);		//
	CVector3d scale_24_y(2.0, 4.0, 1.2);		//
	CVector3d scale_24_x(4.0, 2.0, 1.2);		//

	CVector3d center;
	GLfloat color[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat white[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat black[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat shininess = 30;		
	GLfloat light0_position[4] = { (float)GLSettings4.m_Eye.x, (float)GLSettings4.m_Eye.y, (float)GLSettings4.m_Eye.z, 1.0f };

																															  //ŒõŒ¹‚ÌÝ’è--------------------------------------
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);			

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);				
	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, white);		
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);								

																			
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	glLineWidth(3.0);

	static int r = 0;
	glRotated((double)r, 0.0, 0.0, 1.0);

	for (int z(1); z<m.num[2] - 1; z++)
	{
		for (int x(1); x<m.num[0] - 1; x++)
		{
			for (int y(1); y<m.num[1] - 1; y++)
			{
				//###################################
				//
				//###################################
				if (block[x][y][z].flag == 1)
				{
					center.x = x + 0.5;
					center.y = y + 0.5;
					center.z = z + 0.5;
					
					color[0] = (float)m.Voxel_colors[x][y][z].r;
					color[1] = (float)m.Voxel_colors[x][y][z].g;
					color[2] = (float)m.Voxel_colors[x][y][z].b;

					//
					if (color[0] < 2)
					{
						glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
						//glMaterialfv(GL_FRONT, GL_SPECULAR, white);
						DrawSolidBlock(center, scale_11);
					}
					////
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
					DrawWireBlock(center, scale_11);
				}
				else if (block[x][y][z].flag > 1)
				{
					if (block[x][y][z].corner != 1)
						continue;

					//###################################
					//
					//###################################
					//else if(block[x][y][z].flag == 12 && block[x][y][z].corner == 1)
					if (block[x][y][z].flag == 12)
					{
						//
						if (block[x][y + 1][z].flag == 12 && block[x][y][z].ID == block[x][y + 1][z].ID && block[x][y + 1][z].corner == 2)
						{
							center.x = x + 0.5;
							center.y = y + 1.0;
							center.z = z + 0.5;
							color[0] = (float)m.Voxel_colors[x][y][z].r;
							color[1] = (float)m.Voxel_colors[x][y][z].g;
							color[2] = (float)m.Voxel_colors[x][y][z].b;
							//
							if (color[0] < 2) {
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
								DrawSolidBlock(center, scale_12_y);
							}
							glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
							DrawWireBlock(center, scale_12_y);
							continue;
						}
						//
						if (block[x + 1][y][z].flag == 12 && block[x][y][z].ID == block[x + 1][y][z].ID && block[x + 1][y][z].corner == 2)
						{
							center.x = x + 1.0;
							center.y = y + 0.5;
							center.z = z + 0.5;
							color[0] = (float)m.Voxel_colors[x][y][z].r;
							color[1] = (float)m.Voxel_colors[x][y][z].g;
							color[2] = (float)m.Voxel_colors[x][y][z].b;
							if (color[0] < 2) {
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
								DrawSolidBlock(center, scale_12_x);
							}
							glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
							DrawWireBlock(center, scale_12_x);
						}
					}
					//###################################
					//
					//###################################
					//else if(block[x][y][z].flag == 13 && block[x][y][z].corner == 1)
					else if (block[x][y][z].flag == 13)
					{
						//
						if (y + 2 < m.num[1])
						{
							if (block[x][y + 2][z].flag == 13 && block[x][y][z].ID == block[x][y + 2][z].ID && block[x][y + 2][z].corner == 2)
							{
								center.x = x + 0.5;
								center.y = y + 1.5;
								center.z = z + 0.5;
								color[0] = (float)m.Voxel_colors[x][y][z].r;
								color[1] = (float)m.Voxel_colors[x][y][z].g;
								color[2] = (float)m.Voxel_colors[x][y][z].b;

								if (color[0] < 2) {
									glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
									DrawSolidBlock(center, scale_13_y);
								}
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
								DrawWireBlock(center, scale_13_y);
								continue;
							}
						}
						//
						if (x + 2 < m.num[0])
						{
							if (block[x + 2][y][z].flag == 13 && block[x][y][z].ID == block[x + 2][y][z].ID && block[x + 2][y][z].corner == 2)
							{
								center.x = x + 1.5;
								center.y = y + 0.5;
								center.z = z + 0.5;
								color[0] = (float)m.Voxel_colors[x][y][z].r;
								color[1] = (float)m.Voxel_colors[x][y][z].g;
								color[2] = (float)m.Voxel_colors[x][y][z].b;


								if (color[0] < 2) {
									glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
									DrawSolidBlock(center, scale_13_x);
								}
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
								DrawWireBlock(center, scale_13_x);
							}
						}
					}

					//###################################
					//
					//###################################
					//else if(block[x][y][z].flag == 14 && block[x][y][z].corner == 1)
					else if (block[x][y][z].flag == 14)
					{
						//‚P~‚S‚ª‚™•ûŒü‚Ìê‡
						if (y + 3 < m.num[1])
						{
							if (block[x][y + 3][z].flag == 14 && block[x][y][z].ID == block[x][y + 3][z].ID && block[x][y + 3][z].corner == 2)
							{
								center.x = x + 0.5;
								center.y = y + 2.0;
								center.z = z + 0.5;
								color[0] = (float)m.Voxel_colors[x][y][z].r;
								color[1] = (float)m.Voxel_colors[x][y][z].g;
								color[2] = (float)m.Voxel_colors[x][y][z].b;
								if (color[0] < 2) {
									glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
									DrawSolidBlock(center, scale_14_y);
								}
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
								DrawWireBlock(center, scale_14_y);
								continue;
							}
						}
						//
						if (x + 3 < m.num[0])
						{
							if (block[x + 3][y][z].flag == 14 && block[x][y][z].ID == block[x + 3][y][z].ID && block[x + 3][y][z].corner == 2)
							{
								center.x = x + 2.0;
								center.y = y + 0.5;
								center.z = z + 0.5;
								color[0] = (float)m.Voxel_colors[x][y][z].r;
								color[1] = (float)m.Voxel_colors[x][y][z].g;
								color[2] = (float)m.Voxel_colors[x][y][z].b;

								if (color[0] < 2) {
									glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
									DrawSolidBlock(center, scale_14_x);
								}
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
								DrawWireBlock(center, scale_14_x);
							}
						}
					}
					//###################################
					//
					//###################################
					//else if(block[x][y][z].flag == 22 && block[x][y][z].corner == 1)
					else if (block[x][y][z].flag == 22)
					{
						if (block[x + 1][y + 1][z].flag == 22 && block[x][y][z].ID == block[x + 1][y + 1][z].ID && block[x + 1][y + 1][z].corner == 2)
						{
							center.x = x + 1.0;
							center.y = y + 1.0;
							center.z = z + 0.5;
							color[0] = (float)m.Voxel_colors[x][y][z].r;
							color[1] = (float)m.Voxel_colors[x][y][z].g;
							color[2] = (float)m.Voxel_colors[x][y][z].b;
							if (color[0] < 2) {
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
								DrawSolidBlock(center, scale_22);
							}
							glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
							DrawWireBlock(center, scale_22);
						}
					}
					//###################################
					//
					//###################################
					//else if(block[x][y][z].flag == 23 && block[x][y][z].corner == 1)
					else if (block[x][y][z].flag == 23)
					{
						//
						if (y + 2 < m.num[1])
						{
							if (block[x + 1][y + 2][z].flag == 23 && block[x][y][z].ID == block[x + 1][y + 2][z].ID && block[x + 1][y + 2][z].corner == 2)
							{
								center.x = x + 1.0;
								center.y = y + 1.5;
								center.z = z + 0.5;
								color[0] = (float)m.Voxel_colors[x][y][z].r;
								color[1] = (float)m.Voxel_colors[x][y][z].g;
								color[2] = (float)m.Voxel_colors[x][y][z].b;
								if (color[0] < 2) {
									glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
									DrawSolidBlock(center, scale_23_y);
								}
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
								DrawWireBlock(center, scale_23_y);
								continue;
							}
						}
						//
						if (x + 2 < m.num[0])
						{
							if (block[x + 2][y + 1][z].flag == 23 && block[x][y][z].ID == block[x + 2][y + 1][z].ID && block[x + 2][y + 1][z].corner == 2)
							{
								center.x = x + 1.5;
								center.y = y + 1.0;
								center.z = z + 0.5;
								color[0] = (float)m.Voxel_colors[x][y][z].r;
								color[1] = (float)m.Voxel_colors[x][y][z].g;
								color[2] = (float)m.Voxel_colors[x][y][z].b;
								if (color[0] < 2) {
									glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
									DrawSolidBlock(center, scale_23_x);
								}
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
								DrawWireBlock(center, scale_23_x);
							}
						}
					}
					//###################################
					//
					//###################################
					//else if(block[x][y][z].flag == 24 && block[x][y][z].corner == 1)
					else if (block[x][y][z].flag == 24)
					{
						//
						if (y + 3 < m.num[1])
						{
							if (block[x + 1][y + 3][z].flag == 24 && block[x][y][z].ID == block[x + 1][y + 3][z].ID && block[x + 1][y + 3][z].corner == 2)
							{
								center.x = x + 1.0;
								center.y = y + 2.0;
								center.z = z + 0.5;
								color[0] = (float)m.Voxel_colors[x][y][z].r;
								color[1] = (float)m.Voxel_colors[x][y][z].g;
								color[2] = (float)m.Voxel_colors[x][y][z].b;
								if (color[0] < 2) {
									glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
									DrawSolidBlock(center, scale_24_y);
								}
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
								DrawWireBlock(center, scale_24_y);
								continue;
							}
						}
						//
						if (x + 3 < m.num[0])
						{
							if (block[x + 3][y + 1][z].flag == 24 && block[x][y][z].ID == block[x + 3][y + 1][z].ID && block[x + 3][y + 1][z].corner == 2)
							{
								center.x = x + 2.0;
								center.y = y + 1.0;
								center.z = z + 0.5;
								color[0] = (float)m.Voxel_colors[x][y][z].r;
								color[1] = (float)m.Voxel_colors[x][y][z].g;
								color[2] = (float)m.Voxel_colors[x][y][z].b;
								if (color[0] < 2) {
									glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
									DrawSolidBlock(center, scale_24_x);
								}
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
								DrawWireBlock(center, scale_24_x);
							}
						}
					}
				}
			}
		}
	}

	//
	if (++r >= 360) r = 0;
	glDisable(GL_LIGHTING);
}

//##########################################
//                                                     
//##########################################
void DrawBlockModel_half(Model& m, Lego*** block, int Znum)
{
	CVector3d scale_11(1.0f, 1.0f, 1.2);			
	CVector3d scale_12_y(1.0, 2.0, 1.2);		//
	CVector3d scale_12_x(2.0, 1.0, 1.2);		//
	CVector3d scale_13_y(1.0, 3.0, 1.2);		//
	CVector3d scale_13_x(3.0, 1.0, 1.2);		//
	CVector3d scale_14_y(1.0, 4.0, 1.2);		//
	CVector3d scale_14_x(4.0, 1.0, 1.2);		//
	CVector3d scale_22(2.0, 2.0, 1.2);		//
	CVector3d scale_23_y(2.0, 3.0, 1.2);		//
	CVector3d scale_23_x(3.0, 2.0, 1.2);		//
	CVector3d scale_24_y(2.0, 4.0, 1.2);		//
	CVector3d scale_24_x(4.0, 2.0, 1.2);		//

	CVector3d center;
	GLfloat color[4] = { 0.0f, 0.0f, 0.0f, 0.7f };
	GLfloat white[4] = { 1.0f, 1.0f, 1.0f, 0.7f };
	GLfloat black[4] = { 0.0f, 0.0f, 0.0f, 0.7f };
	GLfloat shininess = 30;		
	GLfloat light0_position[4] = { (float)GLSettings4.m_Eye.x, (float)GLSettings4.m_Eye.y, (float)GLSettings4.m_Eye.z, 1.0f };

																															 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);			

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);				
	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, white);		
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);								

																			
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	glLineWidth(3.0);
	for (int z(1); z<Znum + 1; z++)
	{
		for (int x(1); x<m.num[0] - 1; x++)
		{
			for (int y(1); y<m.num[1] - 1; y++)
			{
				//###################################
				//
				//###################################
				if (block[x][y][z].flag == 1)
				{
					center.x = x + 0.5;
					center.y = y + 0.5;
					center.z = z + 0.5;
					//ƒJƒ‰[‚ÌƒuƒƒbƒN
					color[0] = (float)m.Voxel_colors[x][y][z].r;
					color[1] = (float)m.Voxel_colors[x][y][z].g;
					color[2] = (float)m.Voxel_colors[x][y][z].b;

					
					if (color[0] < 2)
					{
						glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
						//glMaterialfv(GL_FRONT, GL_SPECULAR, white);
						DrawSolidBlock(center, scale_11);
					}
					
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
					DrawWireBlock(center, scale_11);
				}
				else if (block[x][y][z].flag > 1)
				{
					if (block[x][y][z].corner != 1)
						continue;

					//###################################
					//
					//###################################
					//else if(block[x][y][z].flag == 12 && block[x][y][z].corner == 1)
					if (block[x][y][z].flag == 12)
					{
						
						if (block[x][y + 1][z].flag == 12 && block[x][y][z].ID == block[x][y + 1][z].ID && block[x][y + 1][z].corner == 2)
						{
							center.x = x + 0.5;
							center.y = y + 1.0;
							center.z = z + 0.5;
							color[0] = (float)m.Voxel_colors[x][y][z].r;
							color[1] = (float)m.Voxel_colors[x][y][z].g;
							color[2] = (float)m.Voxel_colors[x][y][z].b;
						
							if (color[0] < 2) {
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
								DrawSolidBlock(center, scale_12_y);
							}
							glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
							DrawWireBlock(center, scale_12_y);
							continue;
						}
						//
						if (block[x + 1][y][z].flag == 12 && block[x][y][z].ID == block[x + 1][y][z].ID && block[x + 1][y][z].corner == 2)
						{
							center.x = x + 1.0;
							center.y = y + 0.5;
							center.z = z + 0.5;
							color[0] = (float)m.Voxel_colors[x][y][z].r;
							color[1] = (float)m.Voxel_colors[x][y][z].g;
							color[2] = (float)m.Voxel_colors[x][y][z].b;
							if (color[0] < 2) {
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
								DrawSolidBlock(center, scale_12_x);
							}
							glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
							DrawWireBlock(center, scale_12_x);
						}
					}
					//###################################
					//
					//###################################
					//else if(block[x][y][z].flag == 13 && block[x][y][z].corner == 1)
					else if (block[x][y][z].flag == 13)
					{
						
						if (y + 2 < m.num[1])
						{
							if (block[x][y + 2][z].flag == 13 && block[x][y][z].ID == block[x][y + 2][z].ID && block[x][y + 2][z].corner == 2)
							{
								center.x = x + 0.5;
								center.y = y + 1.5;
								center.z = z + 0.5;
								color[0] = (float)m.Voxel_colors[x][y][z].r;
								color[1] = (float)m.Voxel_colors[x][y][z].g;
								color[2] = (float)m.Voxel_colors[x][y][z].b;

								if (color[0] < 2) {
									glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
									DrawSolidBlock(center, scale_13_y);
								}
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
								DrawWireBlock(center, scale_13_y);
								continue;
							}
						}
						
						if (x + 2 < m.num[0])
						{
							if (block[x + 2][y][z].flag == 13 && block[x][y][z].ID == block[x + 2][y][z].ID && block[x + 2][y][z].corner == 2)
							{
								center.x = x + 1.5;
								center.y = y + 0.5;
								center.z = z + 0.5;
								color[0] = (float)m.Voxel_colors[x][y][z].r;
								color[1] = (float)m.Voxel_colors[x][y][z].g;
								color[2] = (float)m.Voxel_colors[x][y][z].b;


								if (color[0] < 2) {
									glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
									DrawSolidBlock(center, scale_13_x);
								}
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
								DrawWireBlock(center, scale_13_x);
							}
						}
					}

					//###################################
					//
					//###################################
					//else if(block[x][y][z].flag == 14 && block[x][y][z].corner == 1)
					else if (block[x][y][z].flag == 14)
					{
						
						if (y + 3 < m.num[1])
						{
							if (block[x][y + 3][z].flag == 14 && block[x][y][z].ID == block[x][y + 3][z].ID && block[x][y + 3][z].corner == 2)
							{
								center.x = x + 0.5;
								center.y = y + 2.0;
								center.z = z + 0.5;
								color[0] = (float)m.Voxel_colors[x][y][z].r;
								color[1] = (float)m.Voxel_colors[x][y][z].g;
								color[2] = (float)m.Voxel_colors[x][y][z].b;
								if (color[0] < 2) {
									glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
									DrawSolidBlock(center, scale_14_y);
								}
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
								DrawWireBlock(center, scale_14_y);
								continue;
							}
						}
						
						if (x + 3 < m.num[0])
						{
							if (block[x + 3][y][z].flag == 14 && block[x][y][z].ID == block[x + 3][y][z].ID && block[x + 3][y][z].corner == 2)
							{
								center.x = x + 2.0;
								center.y = y + 0.5;
								center.z = z + 0.5;
								color[0] = (float)m.Voxel_colors[x][y][z].r;
								color[1] = (float)m.Voxel_colors[x][y][z].g;
								color[2] = (float)m.Voxel_colors[x][y][z].b;

								if (color[0] < 2) {
									glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
									DrawSolidBlock(center, scale_14_x);
								}
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
								DrawWireBlock(center, scale_14_x);
							}
						}
					}
					//###################################
					//
					//###################################
					//else if(block[x][y][z].flag == 22 && block[x][y][z].corner == 1)
					else if (block[x][y][z].flag == 22)
					{
						if (block[x + 1][y + 1][z].flag == 22 && block[x][y][z].ID == block[x + 1][y + 1][z].ID && block[x + 1][y + 1][z].corner == 2)
						{
							center.x = x + 1.0;
							center.y = y + 1.0;
							center.z = z + 0.5;
							color[0] = (float)m.Voxel_colors[x][y][z].r;
							color[1] = (float)m.Voxel_colors[x][y][z].g;
							color[2] = (float)m.Voxel_colors[x][y][z].b;
							if (color[0] < 2) {
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
								DrawSolidBlock(center, scale_22);
							}
							glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
							DrawWireBlock(center, scale_22);
						}
					}
					//###################################
					//
					//###################################
					//else if(block[x][y][z].flag == 23 && block[x][y][z].corner == 1)
					else if (block[x][y][z].flag == 23)
					{
					
						if (y + 2 < m.num[1])
						{
							if (block[x + 1][y + 2][z].flag == 23 && block[x][y][z].ID == block[x + 1][y + 2][z].ID && block[x + 1][y + 2][z].corner == 2)
							{
								center.x = x + 1.0;
								center.y = y + 1.5;
								center.z = z + 0.5;
								color[0] = (float)m.Voxel_colors[x][y][z].r;
								color[1] = (float)m.Voxel_colors[x][y][z].g;
								color[2] = (float)m.Voxel_colors[x][y][z].b;
								if (color[0] < 2) {
									glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
									DrawSolidBlock(center, scale_23_y);
								}
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
								DrawWireBlock(center, scale_23_y);
								continue;
							}
						}
					
						if (x + 2 < m.num[0])
						{
							if (block[x + 2][y + 1][z].flag == 23 && block[x][y][z].ID == block[x + 2][y + 1][z].ID && block[x + 2][y + 1][z].corner == 2)
							{
								center.x = x + 1.5;
								center.y = y + 1.0;
								center.z = z + 0.5;
								color[0] = (float)m.Voxel_colors[x][y][z].r;
								color[1] = (float)m.Voxel_colors[x][y][z].g;
								color[2] = (float)m.Voxel_colors[x][y][z].b;
								if (color[0] < 2) {
									glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
									DrawSolidBlock(center, scale_23_x);
								}
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
								DrawWireBlock(center, scale_23_x);
							}
						}
					}
					//###################################
					//
					//###################################
					//else if(block[x][y][z].flag == 24 && block[x][y][z].corner == 1)
					else if (block[x][y][z].flag == 24)
					{
					
						if (y + 3 < m.num[1])
						{
							if (block[x + 1][y + 3][z].flag == 24 && block[x][y][z].ID == block[x + 1][y + 3][z].ID && block[x + 1][y + 3][z].corner == 2)
							{
								center.x = x + 1.0;
								center.y = y + 2.0;
								center.z = z + 0.5;
								color[0] = (float)m.Voxel_colors[x][y][z].r;
								color[1] = (float)m.Voxel_colors[x][y][z].g;
								color[2] = (float)m.Voxel_colors[x][y][z].b;
								if (color[0] < 2) {
									glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
									DrawSolidBlock(center, scale_24_y);
								}
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
								DrawWireBlock(center, scale_24_y);
								continue;
							}
						}
					
						if (x + 3 < m.num[0])
						{
							if (block[x + 3][y + 1][z].flag == 24 && block[x][y][z].ID == block[x + 3][y + 1][z].ID && block[x + 3][y + 1][z].corner == 2)
							{
								center.x = x + 2.0;
								center.y = y + 1.0;
								center.z = z + 0.5;
								color[0] = (float)m.Voxel_colors[x][y][z].r;
								color[1] = (float)m.Voxel_colors[x][y][z].g;
								color[2] = (float)m.Voxel_colors[x][y][z].b;
								if (color[0] < 2) {
									glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
									DrawSolidBlock(center, scale_24_x);
								}
								glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
								DrawWireBlock(center, scale_24_x);
							}
						}
					}
				}
			}
		}
	}
}



//################################
//           GCAD                         
//################################
void DrawGrid_GCAD(Model& m, int Znum)
{
	glColor3d(0.0, 0.0, 0.0);
	//×‚¢ü‚ð‘‚­
	glBegin(GL_LINES);
	glLineWidth(1.0);
	for (int x(1); x<m.num[0]; x++) {
		glVertex3d(x, 0, 1.2*Znum);
		glVertex3d(x, m.num[1], 1.2*Znum);
	}
	for (int y(1); y<m.num[1]; y++) {
		glVertex3d(0, y, 1.2*Znum);
		glVertex3d(m.num[0], y, 1.2*Znum);
	}
	glLineWidth(5.0);
	for (int x(0); x <= m.num[0]; x = x + m.num[0]) {
		glVertex3d(x, 0, 1.2*Znum);
		glVertex3d(x, m.num[1], 1.2*Znum);
	}
	for (int y(0); y <= m.num[1]; y = y + m.num[1]) {
		glVertex3d(0, y, 1.2*Znum);
		glVertex3d(m.num[0], y, 1.2*Znum);
	}
	glEnd();

	CColor surf(0.0, 0.0, 0.0);
	CColor inner(1.0, 0.0, 0.0);
	//
	glBegin(GL_QUADS);
	for (int x(0); x<m.num[0]; x++) {
		for (int y(0); y<m.num[1]; y++) {
			
			if (m.Voxels[x][y][Znum].fill) {
				
				if (m.Voxels[x][y][Znum].surf) {
					glColor4d(surf.r, surf.g, surf.b, 0.9);
					glVertex3d(x, y, 1.2*Znum);
					glVertex3d(x + 1, y, 1.2*Znum);
					glVertex3d(x + 1, y + 1, 1.2*Znum);
					glVertex3d(x, y + 1, 1.2*Znum);
				}
				else {
					//if(m.Voxels[x][y][Znum].dist < -8.0)
					//	continue;
					glColor4d(inner.r - m.Voxels[x][y][Znum].dist / m.MinDist, inner.g, inner.b + m.Voxels[x][y][Znum].dist / m.MinDist, 0.9);
					glVertex3d(x, y, 1.2*Znum);
					glVertex3d(x + 1, y, 1.2*Znum);
					glVertex3d(x + 1, y + 1, 1.2*Znum);
					glVertex3d(x, y + 1, 1.2*Znum);
				}
			}
		}
	}
	glEnd();

}


//################################
//                         GCAD            
//################################
void DrawWireVoxel_GCAD(Model& m)
{

	glColor4d(0.2, 0.2, 0.2, 0.2);
	CVector3d cent;
	for (int z(1); z<m.num[2]; z++) {
		for (int x(1); x<m.num[0]; x++) {
			for (int y(1); y<m.num[1]; y++) {
				if (m.Voxels[x][y][z].surf) {
					cent.x = x + 0.5;
					cent.y = y + 0.5;
					cent.z = 1.2*z;
					DrawWireCuboid(cent, 1.0);
				}
			}
		}
	}

}

void DrawVoxel_GCAD(Model& m, int xx, int yy, int zz)
{
	CColor surf(0.5, 0.5, 0.5);
	CColor inner(1.0, 0.0, 0.0);

	glColor4d(surf.r, surf.g, surf.b, 0.2);
	for (int x(1); x<m.num[0] - 1; x++) {
		for (int y(1); y<m.num[1] - 1; y++) {
			for (int z(1); z<m.num[2] - 1; z++) {
				if (m.Voxels[x][y][z].surf)
					DrawWireCuboid(m.Voxels[x][y][z].center, m.Voxels[x][y][z].length);
			}
		}
	}
	//w
	for (int y(1); y<m.num[1] - 1; y++) {
		for (int z(1); z<m.num[2] - 1; z++) {
			if (m.Voxels[xx][y][z].fill) {
				if (m.Voxels[xx][y][z].surf)
					glColor4d(surf.r, surf.g, surf.b, 0.5);
				else
					glColor4d(inner.r - m.Voxels[xx][y][z].dist / m.MinDist, inner.g, inner.b + m.Voxels[xx][y][z].dist / m.MinDist, 0.8);
				if (m.Voxels[xx][y][z].dist < -3.0 || z < zz)
					continue;
				DrawSolidCuboid(m.Voxels[xx][y][z].center, m.Voxels[xx][y][z].length);
			}
		}
	}
	//x
	for (int x(1); x<m.num[0] - 1; x++) {
		for (int z(1); z<m.num[2] - 1; z++) {
			if (m.Voxels[x][yy][z].fill) {
				if (m.Voxels[x][yy][z].surf)
					glColor4d(surf.r, surf.g, surf.b, 0.5);
				else
					glColor4d(inner.r - m.Voxels[x][yy][z].dist / m.MinDist, inner.g, inner.b + m.Voxels[x][yy][z].dist / m.MinDist, 0.8);
				if (m.Voxels[x][yy][z].dist < -3.0 || z < zz)
					continue;
				DrawSolidCuboid(m.Voxels[x][yy][z].center, m.Voxels[x][yy][z].length);
			}
		}
	}
	//y
	for (int x(1); x<m.num[0] - 1; x++) {
		for (int y(1); y<m.num[1] - 1; y++) {
			if (m.Voxels[x][y][zz].fill) {
				if (m.Voxels[x][y][zz].surf)
					glColor4d(surf.r, surf.g, surf.b, 0.5);
				else
					glColor4d(inner.r - m.Voxels[x][y][zz].dist / m.MinDist, inner.g, inner.b + m.Voxels[x][y][zz].dist / m.MinDist, 0.8);
				if (m.Voxels[x][y][zz].dist < -3.0)
					continue;
				DrawSolidCuboid(m.Voxels[x][y][zz].center, m.Voxels[x][y][zz].length);
			}
		}
	}

}


//###############################
//
//###############################
void DrawSolid_GACD(Model& integ, int Znum)
{
	GLfloat color[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat white[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat black[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat shininess = 10;		
	GLfloat light0_position[4] = { (float)GLSettings4.m_Eye.x, (float)GLSettings4.m_Eye.y, (float)GLSettings4.m_Eye.z, 1.0f };//ŒõŒ¹‚ÌˆÊ’u  Ž‹“_‚ÌˆÊ’u

	CColor Cblack(0.0, 0.0, 0.0);
	CColor Dblack(0.2, 0.2, 0.2);
	CColor inner(1.0, 0.0, 0.0);

	//-------------------------------------
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);			

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);				
	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, white);		
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);								

																			
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	for (int z(1); z<Znum; z++) {
		for (int x(1); x<integ.num[0] - 1; x++) {
			for (int y(1); y<integ.num[1] - 1; y++) {
				if (integ.Voxels[x][y][z].fill) {
					if (integ.Voxels[x][y][z].surf) {
						DrawWireCuboid(integ.Voxels[x][y][z].center, integ.Voxels[x][y][z].length, Cblack);
					}
					else {
						if (integ.Voxels[x][y][z].dist < -3.0)
							continue;
						inner.Set(inner.r - integ.Voxels[x][y][z].dist / integ.MinDist, 0.0, inner.b + integ.Voxels[x][y][z].dist / integ.MinDist);
						DrawWireCuboid(integ.Voxels[x][y][z].center, integ.Voxels[x][y][z].length, Dblack);
						DrawSolidCuboid(integ.Voxels[x][y][z].center, integ.Voxels[x][y][z].length, inner);
						inner.Set(1.0, 0.0, 0.0);
					}
				}
			}
		}
	}

}


