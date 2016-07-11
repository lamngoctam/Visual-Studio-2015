//############################################################################

//############################################################################

#include "OpenGLWindow0.h"
using namespace std;

extern int WinID[5];
OpenGL GLSettingsDown;

int CrossSectionNumDown(1);

//DOWN MODEL
bool upBBF_(1);		//UP Model Big Bounding Box Flag
bool downWOMF(1);	//DOWN Wire Octree Model Flag
bool downFOMF(1);		//DOWN Face Octree Model Flag
bool downWVMF(1);	//DOWN Wire Voxel Model Flag
bool downFVMF(1);		//DOWN Face Voxel Model Flag

bool PickUp(0);				//pick up
bool origin(1);
/***************************************************/
/*			OpenGL  */
/***************************************************/
//
void DrawWire_BoundingBox_UP(OctVoxel &box);
void DrawWire_BoundingBox_DOWN(OctVoxel &box);



extern CVector3d BBox_Origin;

extern vector<CVector3d> Origin_;

void OpenGLDisplayDown(void) {
	DisplayInit();						
	GLSettingsDown.SetEyePosition();		
	/********************************/
	/********************************/
	ConclusiveAxis();

	EnableLight(1);
	DrawSphere(BBox_Origin, 5);
	DisableLight();

	//glLineWidth(5);
	//glColor3d(0.0, 0.0, 0.5);
	//glBegin(GL_LINES);
	//glVertex3d(DOWN.VertexMin_.x, DOWN.VertexMin_.y, DOWN.VertexMin_.z);
	//glVertex3d(DOWN.VertexMax_.x, DOWN.VertexMax_.y, DOWN.VertexMax_.z);
	//glEnd();
	//
	//if (origin) {
	//	Draw_Plane_Octree(DOWN);
	//	Draw_Boundary_Octree(DOWN);
	//}
	
	//UP MODEL
	if (upBBF_) {
		DrawWire_BoundingBox_UP(UpBoundingBox);  
		DrawFaceOctreeModel_SFS_UP(UP.Octrees);
		DrawWireOctreeModel_SFS_UP(UP.Octrees);
	}

	if (downFOMF) { 
		DrawFaceOctreeModel_SFS_DOWN(DOWN.Octrees); 
		DrawWire_BoundingBox_DOWN(DownBoundingBox);
	}

	if (downWOMF) { 
		DrawWireOctreeModel_SFS_DOWN(DOWN.Octrees); 
	}

	/********************************/
	//
	/********************************/
	DisplayPostprocessor();	
}



/***************************************************/
/*			OpenGL */
/***************************************************/

void OpenGLKeyboardDown(unsigned char Key, int x, int y) {

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
	case 'f':
		upBBF_ = !upBBF_;
		break;
	case 'w':
		downFOMF = !downFOMF;
		break;

	case 'o':
		origin = !origin; break;
	case 's':		//s
		PickUp = true;
		cout << "P model pick up mode start" << endl;
		for (int i(0); i < 3; i++) {
			UP.Pick[i].x = 0;
			UP.Pick[i].y = 0;
			UP.Pick[i].z = 0;
		}
		break;

	case 'e':		
		PickUp = false;
		cout << "P model pick up mode end\n" << endl;
		for (int i(0); i < 3; i++)
			cout << UP.Pick[i] << endl;
		break;

	case '1':	//
		GLSettingsDown.m_EyeDis = 400;
		GLSettingsDown.m_Center.Clear();
		GLSettingsDown.m_Front.Set(2.0, 2.0, -0.1);
		GLSettingsDown.m_Upper.Set(0.2, 0.2, 2.0);
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

void OpenGLSpecialDown(int Key, int x, int y) {
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

int PickUpDown(int x, int y, int hit_name[2], int Button) {
	GLint hits;
	GLuint selectBuf[BUFSIZE];
	glSelectBuffer(BUFSIZE, selectBuf);

	PickUpInit(x, y);
	GLSettingsDown.SetEyePosition();

	/************************************/
	PickUpPostprocessor();

	hits = glRenderMode(GL_RENDER);

	return SelectHits(hits, selectBuf, hit_name);
}
/***************************************************/
void PickObjectDown(int x, int y, int Button) {
	int hit_name[2];	//
	if (PickUpDown(x, y, hit_name, Button) == -1) {
		//
		GLSettingsDown.ObjectPosition = &GLSettingsDown.ObjectTemp;	
		return;
	}

	GLSettingsDown.m_ObjectDepth = ReturnDepth(x, y);

	int cnt(0);
	for (vector<Voxel>::iterator it = UP.SurfVoxels.begin(); it != UP.SurfVoxels.end(); it++)
	{
		if (cnt == hit_name[1])
		{
			cout << picknum + 1 << "  " << (*it).coord << endl;
			UP.CorresVoxel3[picknum] = (*it);
			UP.Pick[picknum] = (*it).coord;
			if ((*it).pic == false)				(*it).pic = true;
			else										(*it).pic = false;
			picknum++;
			picknum = picknum % 3;
			break;
		}
		cnt++;
	}
}

void OpenGLMouseDown(int Button, int State, int x, int y) {
	GLSettingsDown.Tracking(Button, State, x, y);
}

void OpenGLMotionDown(int x, int y) {
	GLSettingsDown.MovingMouse(x, y);
}

void OpenGLMouseWheelDown(int wheel_number, int direction, int x, int y) {
	GLSettingsDown.DoMouseWheel(direction);
}


void OpenGLReshapeDown(int width, int height) {
	GLSettingsDown.m_Aspect = static_cast<double>(width) / static_cast<double>(height);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(10.0, GLSettingsDown.m_Aspect, 0.01, -1.0);
	glMatrixMode(GL_MODELVIEW);
}


/***************************************************/
/*	Å                                               */
/***************************************************/
//
void OpenGLCallBackDown(void) {
	GLSettingsDown.PickObject = PickObjectDown;
	OpenGLInitialize(0, GLSettingsDown, 0, 0, 600, 800, "WindowDown");
	glutDisplayFunc(OpenGLDisplayDown);	// program

	glutReshapeFunc(OpenGLReshapeDown);
	glutMouseFunc(OpenGLMouseDown);
	glutMotionFunc(OpenGLMotionDown);

	glutMouseWheelFunc(OpenGLMouseWheelDown);
	glutKeyboardFunc(OpenGLKeyboardDown);
	glutSpecialFunc(OpenGLSpecialDown);
	glutIdleFunc(OpenGLIdle);
	OpenGLPostprocessor(GLSettingsDown);
}