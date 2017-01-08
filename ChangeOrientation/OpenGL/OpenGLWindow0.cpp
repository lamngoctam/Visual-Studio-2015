//############################################################################

//############################################################################
#include "OpenGLWindow0.h"

using namespace std;

extern int WinID[5];
OpenGL GLSettings0;

int CrossSectionNum(1);

//UP MODEL
bool upBBF(true);			//UP Model Bounding Box Flag
bool upWOMF(true);		//UP Wire Octree Model Flag
bool upFOMF(true);			//UP Face Octree Model Flag
bool upWVMF(true);		//UP Wire Voxel Model Flag

bool PickF(0);				//pick up
bool Origin_all_voxel(true);

bool upbox(true);
bool upvertex(true);
/***************************************************/
/*			OpenGL  */
/***************************************************/
void DrawWire_BoundingBox_UP(OctVoxel &box);


//
extern CVector3d BBox_Origin;
extern vector<CVector3d> Origin_;
extern vector<CVector3d> display8point;
extern vector<CVector3d> back_octree;

extern vector<OctVoxel> UpBbox_Scale;

extern OctVoxel scale_;

void OpenGLDisplay0(void) {
	DisplayInit();						
	GLSettings0.SetEyePosition();		
	/********************************/
	/********************************/
	ConclusiveAxis();

	EnableLight(1);
	DrawSphere(BBox_Origin, 5);   
	DisableLight();

	//glPointSize(9);
	//glColor3d(0.5, 0.0, 0.5);
	//glBegin(GL_POINTS);
	//for (auto i(0); i < 8; ++i){
	//	glVertex3d(New_center_octrees[i].x, New_center_octrees[i].y, New_center_octrees[i].z);
	//}
	//glEnd();
	//
	//Draw_VertexMax_Octree(UP);  //max
	//Draw_VertexMin_Octree(UP);
	//
	//glLineWidth(5);
	//glColor3d(0.0, 0.0, 0.5);
	//glBegin(GL_LINES);
	//glVertex3d(UP.VertexMin_.x, UP.VertexMin_.y, UP.VertexMin_.z);
	//glVertex3d(UP.VertexMax_.x, UP.VertexMax_.y, UP.VertexMax_.z);
	//glEnd();
	//
	//
	//
	//EnableLight(1);
	//DrawSphere(VertexMax_, 3);
	//DisableLight();
	//
	//DrawBoundingbox(UP.VertexMin_, UP.VertexMax_);
	//
	//if (upvertex) { Draw_Plane_Octree(UP); }  //vertex
	//if (upbox) { Draw_Boundary_Octree(UP); }  //line



	//------------------------------------------------------------
	if (upBBF) {
		DrawWire_BoundingBox_UP(UpBoundingBox);
	}  
	if (upFOMF) {
		DrawFaceOctreeModel_SFS_UP(UP.Octrees);
	} 
	if (upWOMF) {
		DrawWireOctreeModel_SFS_UP(UP.Octrees);
	}

	/********************************/
	DisplayPostprocessor();	
}



/***************************************************/
/*			OpenGL */
/***************************************************/
//http://e-words.jp/p/r-ascii.html
//BackSpace‚
//	16'\x08'	C++ 16i”
//	 8'\010'	C++ 8i”
void OpenGLKeyboard0(unsigned char Key, int x, int y) {

	switch (Key) {
	case '\x1b':	//Esc
		std::cout << "Exit OpenGL System" << std::endl;
		glutLeaveMainLoop();		//OpenGL
		break;
	case '\x0d':	//Enter
		break;

	case '\x20':	//Space
		break;

	case '\x7f':	//Delete
		break;

	case '\x08':	//BackSpace
		break;

	case '\t':		//TAB
		break;

	case '2':
		upbox = !upbox;
		break;
	case '3':
		upvertex = !upvertex;
		break;

	case 'a':
		Origin_all_voxel = !Origin_all_voxel;
		break;

	case 'f':
		upFOMF = !upFOMF;
		break;
	case 'w':
		upWOMF = !upWOMF;
		break;

	case 's':		//s
		PickF = true;
		cout << "P model pick up mode start" << endl;
		for (int i(0); i < 3; i++) {
			UP.Pick[i].x = 0;
			UP.Pick[i].y = 0;
			UP.Pick[i].z = 0;
		}
		break;

	case 'e':		//e
		PickF = false;
		cout << "P model pick up mode end\n" << endl;
		for (int i(0); i < 3; i++)
			cout << UP.Pick[i] << endl;
		break;

	case '1':	//
		GLSettings0.m_EyeDis = 400;
		GLSettings0.m_Center.Clear();
		GLSettings0.m_Front.Set(2.0, 2.0, -0.1);
		GLSettings0.m_Upper.Set(0.2, 0.2, 2.0);
		break;

	case '@':	//
		writefile(GL2PS_EPS, GL2PS_SMPLE_SORT, GL2PS_DRAW_BACKGROUND, 0, "Window0", "eps", WinID[0], GLSettings0);
		writefile(GL2PS_SVG, GL2PS_SMPLE_SORT, GL2PS_DRAW_BACKGROUND, 0, "Window0", "svg", WinID[0], GLSettings0);
		writebmpfile("Window0", "bmp", WinID[0]);

		printf("GL2PS %d.%d.%d done with all images\n",
			GL2PS_MAJOR_VERSION, GL2PS_MINOR_VERSION, GL2PS_PATCH_VERSION);
		break;
	}

	glutPostRedisplay();
}


// http://opengl.jp/glut/section07-09.html
void OpenGLSpecial0(int Key, int x, int y) {
	switch (Key) {

	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;

	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;

	case GLUT_KEY_PAGE_UP:
		break;
	case GLUT_KEY_PAGE_DOWN:
		break;
	}
	glutPostRedisplay();
}

/***************************************************/
int PickUp0(int x, int y, int hit_name[2], int Button) {
	GLint hits;
	GLuint selectBuf[BUFSIZE];
	glSelectBuffer(BUFSIZE, selectBuf);

	PickUpInit(x, y);				
	GLSettings0.SetEyePosition();	

	PickUpPostprocessor();		

	hits = glRenderMode(GL_RENDER);		

	return SelectHits(hits, selectBuf, hit_name);
}


void PickObject0(int x, int y, int Button) {
	int hit_name[2];	
	if (PickUp0(x, y, hit_name, Button) == -1) {
		
		GLSettings0.ObjectPosition = &GLSettings0.ObjectTemp;	
		return;
	}


	GLSettings0.m_ObjectDepth = ReturnDepth(x, y);


	int cnt(0);
	for (vector<Voxel>::iterator it = UP.SurfVoxels.begin(); it != UP.SurfVoxels.end(); it++)
	{
		if (cnt == hit_name[1])
		{
			cout << picknum + 1 << "  " << (*it).coord << endl;
			UP.CorresVoxel3[picknum] = (*it);
			UP.Pick[picknum] = (*it).coord;
			if ((*it).pic == false)				
				(*it).pic = true;
			else										
				(*it).pic = false;
			picknum++;
			picknum = picknum % 3;
			break;
		}
		cnt++;
	}


}

void OpenGLMouse0(int Button, int State, int x, int y) {
	GLSettings0.Tracking(Button, State, x, y);
}

void OpenGLMotion0(int x, int y) {
	GLSettings0.MovingMouse(x, y);
}

/***************************************************/
//freeglut

void OpenGLMouseWheel0(int wheel_number, int direction, int x, int y) {
	GLSettings0.DoMouseWheel(direction);
}

/***************************************************/
//gluPerspective
void OpenGLReshape0(int width, int height) {
	GLSettings0.m_Aspect = static_cast<double>(width) / static_cast<double>(height);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(10.0, GLSettings0.m_Aspect, 0.01, -1.0);
	glMatrixMode(GL_MODELVIEW);
}


/***************************************************/

void OpenGLCallBack0(void) {
	GLSettings0.PickObject = PickObject0;
	OpenGLInitialize(0, GLSettings0, 0, 0, 600, 800, "Window0");
	glutDisplayFunc(OpenGLDisplay0);	// program

	glutReshapeFunc(OpenGLReshape0);
	glutMouseFunc(OpenGLMouse0);
	glutMotionFunc(OpenGLMotion0);

	glutMouseWheelFunc(OpenGLMouseWheel0);
	glutKeyboardFunc(OpenGLKeyboard0);
	glutSpecialFunc(OpenGLSpecial0);
	glutIdleFunc(OpenGLIdle);	// no need  to reDisplay			
	OpenGLPostprocessor(GLSettings0);
}
