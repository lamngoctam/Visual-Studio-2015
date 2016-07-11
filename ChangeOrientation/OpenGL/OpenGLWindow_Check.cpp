
#include "OpenGLWindow0.h"

using namespace std;

extern int WinID[5];	
OpenGL GLSettings_Check;

int CrossSectionNum_Check(1);
bool Pick_Check(0);				

extern CVector3d VertexMin_;	//origin
extern CVector3d VertexMax_;	//Diagonal point of origin
extern CVector3d BBox_Origin;

extern vector<CVector3d> Origin_;


void OpenGLDisplay_Check(void){
	DisplayInit();						
	GLSettings_Check.SetEyePosition();
	ConclusiveAxis();
	
	if (true)	{ DrawWireOctree(DownBoundingBox, 88); } // blue
	
	DisplayPostprocessor();	
}


/*			OpenGL */
/***************************************************/

void OpenGLKeyboard_Check(unsigned char Key, int x, int y){

	switch (Key){
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

	case 's':		//s
		Pick_Check = true;
		cout << "P model pick up mode start" << endl;
		for (int i(0); i < 3; i++){
			UP.Pick[i].x = 0;
			UP.Pick[i].y = 0;
			UP.Pick[i].z = 0;
		}
		break;

	case 'e':		//e
		Pick_Check = false;
		cout << "P model pick up mode end\n" << endl;
		for (int i(0); i < 3; i++)
			cout << UP.Pick[i] << endl;
		break;

	case '1':	//éãì_êÿë÷
		GLSettings_Check.m_EyeDis = 400;
		GLSettings_Check.m_Center.Clear();
		GLSettings_Check.m_Front.Set(2.0, 2.0, -0.1);
		GLSettings_Check.m_Upper.Set(0.2, 0.2, 2.0);
		break;

	case '@':	//ï`âÊèoóÕ
		writefile(GL2PS_EPS, GL2PS_SMPLE_SORT, GL2PS_DRAW_BACKGROUND, 0, "Window0", "eps", WinID[0], GLSettings0);
		writefile(GL2PS_SVG, GL2PS_SMPLE_SORT, GL2PS_DRAW_BACKGROUND, 0, "Window0", "svg", WinID[0], GLSettings0);
		writebmpfile("Window0", "bmp", WinID[0]);

		printf("GL2PS %d.%d.%d done with all images\n",
			GL2PS_MAJOR_VERSION, GL2PS_MINOR_VERSION, GL2PS_PATCH_VERSION);
		break;
	}

	glutPostRedisplay();
}

void OpenGLSpecial_Check(int Key, int x, int y){
	switch (Key){

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

int PickUp_Check(int x, int y, int hit_name[2], int Button){
	GLint hits;
	GLuint selectBuf[BUFSIZE];
	glSelectBuffer(BUFSIZE, selectBuf);

	PickUpInit(x, y);				
	GLSettings_Check.SetEyePosition();
	/************************************/
	
	/************************************/
	PickUpPostprocessor();		

	hits = glRenderMode(GL_RENDER);		

	return SelectHits(hits, selectBuf, hit_name);
}
/***************************************************/
void PickObject_Check(int x, int y, int Button){
	int hit_name[2];	//
	if (PickUp_Check(x, y, hit_name, Button) == -1){
		//
		GLSettings_Check.ObjectPosition = &GLSettings_Check.ObjectTemp;	//ÉSÉ~Çäiî[
		return;
	}
	
	GLSettings_Check.m_ObjectDepth = ReturnDepth(x, y);
	
	int cnt(0);
	for (vector<Voxel>::iterator it = UP.SurfVoxels.begin(); it != UP.SurfVoxels.end(); it++)
	{
		if (cnt == hit_name[1])
		{
			cout << picknum + 1 <<"  "<< (*it).coord << endl;
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

void OpenGLMouse_Check(int Button, int State, int x, int y){
	GLSettings_Check.Tracking(Button, State, x, y);
}

void OpenGLMotion_Check(int x, int y){
	GLSettings_Check.MovingMouse(x, y);
}

void OpenGLMouseWheel_Check(int wheel_number, int direction, int x, int y){
	GLSettings_Check.DoMouseWheel(direction);
}


void OpenGLReshape_Check(int width, int height){
	GLSettings_Check.m_Aspect = static_cast<double>(width) / static_cast<double>(height);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(10.0, GLSettings_Check.m_Aspect, 0.01, -1.0);
	glMatrixMode(GL_MODELVIEW);
}


/***************************************************/
/*	Å                                               */
/***************************************************/
//
void OpenGLCallBack_Check(void){
	GLSettings_Check.PickObject = PickObject_Check;
	OpenGLInitialize(0, GLSettings_Check, 0, 0, 600, 800, "WindowDown");
	glutDisplayFunc(OpenGLDisplay_Check);	// program

	glutReshapeFunc(OpenGLReshape_Check);
	glutMouseFunc(OpenGLMouse_Check);
	glutMotionFunc(OpenGLMotion_Check);

	glutMouseWheelFunc(OpenGLMouseWheel_Check);
	glutKeyboardFunc(OpenGLKeyboard_Check);
	glutSpecialFunc(OpenGLSpecial_Check);
	glutIdleFunc(OpenGLIdle);				
	OpenGLPostprocessor(GLSettings_Check);
}