
//############################################################################
#include "../stdafx.h"
#include "OpenGL.h"
#include "OpenGLprimitive.h"

using namespace std;
//#pragma warning(disable : 4996)//about scanf

int WinID[5]; 

void OpenGLDisplay0(void);
void OpenGLDisplay1(void);
void OpenGLDisplay2(void);
void OpenGLDisplay3(void);
void OpenGLDisplay4(void);
void OpenGLCallBack0(void);
void OpenGLCallBackDown(void);
void OpenGLCallBack1(void);
void OpenGLCallBack2(void);
void OpenGLCallBack3(void);
void OpenGLCallBack4(void);

void OpenGLCallBack_Check(void);
/***************************************************/
/*			OpenGL	  */
/***************************************************/

void DisplayInit(){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	// glEnable(GL_BLEND);	
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SetLight();	

	glPushMatrix();
}


void DisplayPostprocessor(){
	glDepthMask(TRUE);//
	glDisable(GL_BLEND);

	glPopMatrix();
	glutSwapBuffers();
}


/***************************************************/
/*			　OpenGL	　　   */
/***************************************************/

void PickUpInit(int x, int y){
	GLint viewport[4];
	double current_aspect;
	glGetIntegerv(GL_VIEWPORT, viewport);

	(void) glRenderMode(GL_SELECT);

	glInitNames();
	glMatrixMode(GL_PROJECTION);			
	glPushMatrix();							
	glLoadIdentity();						


	gluPickMatrix(x,viewport[3]-y, 25.0, 25.0, viewport);


	current_aspect = (double)viewport[2]/(double)viewport[3];

	gluPerspective( 10.0, current_aspect, 0.01, -1.0 );

	glMatrixMode( GL_MODELVIEW );		
	glPushMatrix();	
}


void PickUpPostprocessor(void){
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );			
}

int SelectHits( GLuint hits, GLuint* buf, int hit_name[2] ){
	hit_name[0]=-1;
	hit_name[1]=-1;	//階層は２

	double depth_min=10.0;	//一番奥
	double depth_1=1.0;
	double depth_2=1.0;
	GLuint depth_name;
	GLuint *ptr;
	
	if(hits<=0){
		return -1;
	}
		
	ptr = buf;
		
	for(unsigned int i=0; i<hits; ++i){
		depth_name = *ptr;	
		++ptr;
		depth_1 = *ptr/0x7fffffff;	
		

		++ptr;
		depth_2 = *ptr/0x7fffffff;	
		if(depth_min>depth_1){	
			depth_min = depth_1;	
						
			for(unsigned int j=0; j<depth_name; ++j){
				++ptr;
				hit_name[j] = (int)(*ptr);	
			}
		}else{		
			for(unsigned int j=0; j<depth_name; ++j){
				++ptr;		
			}
		}
		++ptr;	
	}
	return hit_name[0];
}


double ReturnDepth( int x, int y ){
	double z;
	GLint viewport[4];			
	glGetIntegerv(GL_VIEWPORT,viewport);	
	glReadPixels(x,viewport[3]-y,1,1,
		GL_DEPTH_COMPONENT,
		GL_FLOAT,
		&z);
	return z;
}


/***************************************************/
/*				
/***************************************************/
void writefile(int format, int sort, int options, int nbcol,char *filename, char *extension, int winid, OpenGL GLSettings){
	FILE *fp;
	char file[256];
	int state = GL2PS_OVERFLOW, buffsize = 0;
	GLint viewport[4];

	strcpy_s(file, filename);
	strcat_s(file, ".");
	strcat_s(file, extension);

	viewport[0] = 0;
	viewport[1] = 0;

	viewport[2] = GLSettings.m_WindowWidth;//window幅
	viewport[3] = GLSettings.m_WindowHeight;//window高さ

	fp = fopen(file, "wb");

	if(!fp){
		printf("Unable to open file %s for writing\n", file);
		exit(1);
	}

	printf("Saving image to file %s... ", file);
	fflush(stdout);

	while(state == GL2PS_OVERFLOW){
		//eps
		buffsize += 1024*1024;
		gl2psBeginPage(file, "gl2psTest", viewport, format, sort, options,GL_RGBA, 0, NULL, nbcol, nbcol, nbcol,buffsize, fp, file);

		//描画する窓によって呼び出す関数は違う
		if(winid==WinID[0]){
			OpenGLDisplay0();
		}
		

		state = gl2psEndPage();
	}

	fclose(fp);
	printf("Done!\n");
	fflush(stdout);
}


/***************************************************/
/*	
/***************************************************/
void writebmpfile(char *filename, char *extension, int winid){
	char file[256];
	strcpy_s(file, filename);
	strcat_s(file, ".");
	strcat_s(file, extension);

	if(winid==WinID[0]){
		OpenGLDisplay0();
	}
	gl_screenshot gs;
	gs.screenshot(file, 24);
}


/***************************************************/
/*					
/***************************************************/
void OpenGLIdle(void){
	// glutPostRedisplay();
}


/***************************************************/
/*					   */
/***************************************************/
void OpenGLInitialize(int WindowID, OpenGL GLSettings, int InitPosiX, int InitPosiY, int WindowWidth, int WindowHeight, char* WindowName){
	GLSettings.m_WindowHeight = WindowHeight;
	GLSettings.m_WindowWidth = WindowWidth;
	glutInitWindowPosition(InitPosiX, InitPosiY);		//ウインドウの初期位置
	glutInitDisplayMode(GLUT_RGBA| GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize( WindowWidth, WindowHeight );	//ウインドウのサイズ
	WinID[WindowID] = glutCreateWindow(WindowName);		//ウインドウの生成

}

/***************************************************/
/*			   */
/***************************************************/
void OpenGLPostprocessor(OpenGL GLSettings){
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f);	//背景色
	glClearDepth( 1.0f );
	glEnable    ( GL_DEPTH_TEST );	//陰面消去
	glDepthFunc ( GL_LEQUAL );
	glShadeModel( GL_SMOOTH );		//スムースシェーディング

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D( -GLSettings.m_WindowWidth,  GLSettings.m_WindowWidth, -GLSettings.m_WindowHeight, GLSettings.m_WindowHeight );

	glMatrixMode( GL_MODELVIEW );
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);	//マウスホイールに必要
}


/***************************************************/
/*			  OpenGL               */
/***************************************************/
void RunOpenGL(int argc, char *argv[]){
	glutInit(&argc, argv);		

	OpenGLCallBack0();	

	glutMainLoop();		
}
void RunOpenGLDown(int argc, char *argv[]){
	glutInit(&argc, argv);		

	OpenGLCallBackDown();	

	glutMainLoop();
}
void RunOpenGL1(int argc, char *argv[]){
	glutInit(&argc, argv);		

	OpenGLCallBack1();	

	glutMainLoop();
}

void RunOpenGL2(int argc, char *argv[]){
	glutInit(&argc, argv);		

	OpenGLCallBack2();	

	glutMainLoop();
}

void RunOpenGL3(int argc, char *argv[]){
	glutInit(&argc, argv);		

	OpenGLCallBack3();	

	glutMainLoop();
}

void RunOpenGL4(int argc, char *argv[]) {
	glutInit(&argc, argv);		

	OpenGLCallBack4();	

	glutMainLoop();		
}
void RunOpenGL_Check(int argc, char *argv[]){
	glutInit(&argc, argv);		

	OpenGLCallBack_Check();

	glutMainLoop();
}