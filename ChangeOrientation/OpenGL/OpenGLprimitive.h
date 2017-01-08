#ifndef _OPENGLLIGHT_H
#define _OPENGLLIGHT_H

#include "../stdafx.h"
#include "OpenGL.h"
using namespace std;

extern float scale;			//1.2
extern OpenGL GLSettings1;
extern OpenGL GLSettings0;
extern OctVoxel Angle_;
extern CVector3d center_boundingbox;

inline void SetLight(){
	CVector3d EyePos0(-35.0, -35.0, -50.0);

	/****************************************************/
	/*	You can determine the light source yourself.				*/
	/****************************************************/
	//Decide eight colors.
	double ColID[8];
	ColID[0] = CColor::white;
	ColID[1] = CColor::lime;
	ColID[2] = CColor::blue;
	ColID[3] = CColor::yellow;
	ColID[4] = CColor::magenta;
	ColID[5] = CColor::red;
	ColID[6] = CColor::lightcyan;
	ColID[7] = CColor::silver;

	GLfloat global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	//GLfloat light0_ambient[4] = { (float)GetColor((int)ColID[0]).r, (float)GetColor((int)ColID[0]).g, (float)GetColor((int)ColID[0]).b, 1.0f };  
	GLfloat light0_ambient[4] = { 1.0f, 1.0f, 1.0f, .5f };			
	GLfloat light0_diffuse[4] = { 1.0f, 1.0f, 1.0f, .5f };			
	GLfloat light0_specular[4] = { 1.0f, 1.0f, 1.0f, .5f };			
	//GLfloat light0_position[4] = { -35.0f, 35.0f, 50.0f, 0.0f };	
	GLfloat light0_position[4] = { (float)EyePos0.x, (float)EyePos0.y, (float)EyePos0.z, 1.0f };

	GLfloat light1_ambient[4] = { (float)GetColor((int)ColID[1]).r, (float)GetColor((int)ColID[1]).g, (float)GetColor((int)ColID[1]).b, 1.0f };
	GLfloat light1_diffuse[4];	GLfloat light1_specular[4];	GLfloat light1_position[4];
	memmove( light1_diffuse, light1_ambient, sizeof(light1_ambient) );
	memmove( light1_specular, light0_specular, sizeof(light0_specular) );
	memmove( light1_position, light0_position, sizeof(light0_specular) );

	GLfloat light2_ambient[4] = { (float)GetColor((int)ColID[2]).r, (float)GetColor((int)ColID[2]).g, (float)GetColor((int)ColID[2]).b, 1.0f };
	GLfloat light2_diffuse[4];	GLfloat light2_specular[4];	GLfloat light2_position[4];
	memmove( light2_diffuse, light2_ambient, sizeof(light2_ambient) );
	memmove( light2_specular, light0_specular, sizeof(light0_specular) );
	memmove( light2_position, light0_position, sizeof(light0_specular) );

	GLfloat light3_ambient[4] = { (float)GetColor((int)ColID[3]).r, (float)GetColor((int)ColID[3]).g, (float)GetColor((int)ColID[3]).b, 1.0f };
	GLfloat light3_diffuse[4];	GLfloat light3_specular[4];	GLfloat light3_position[4];
	memmove( light3_diffuse, light3_ambient, sizeof(light3_ambient) );
	memmove( light3_specular, light0_specular, sizeof(light0_specular) );
	memmove( light3_position, light0_position, sizeof(light0_specular) );

	GLfloat light4_ambient[4] = { (float)GetColor((int)ColID[4]).r, (float)GetColor((int)ColID[4]).g, (float)GetColor((int)ColID[4]).b, 1.0f };
	GLfloat light4_diffuse[4];	GLfloat light4_specular[4];	GLfloat light4_position[4];
	memmove( light4_diffuse, light4_ambient, sizeof(light4_ambient) );
	memmove( light4_specular, light0_specular, sizeof(light0_specular) );
	memmove( light4_position, light0_position, sizeof(light0_specular) );

	GLfloat light5_ambient[4] = { (float)GetColor((int)ColID[5]).r, (float)GetColor((int)ColID[5]).g, (float)GetColor((int)ColID[5]).b, 1.0f };
	GLfloat light5_diffuse[4];	GLfloat light5_specular[4];	GLfloat light5_position[4];
	memmove( light5_diffuse, light5_ambient, sizeof(light5_ambient) );
	memmove( light5_specular, light0_specular, sizeof(light0_specular) );
	memmove( light5_position, light0_position, sizeof(light0_specular) );

	GLfloat light6_ambient[4] = { (float)GetColor((int)ColID[6]).r, (float)GetColor((int)ColID[6]).g, (float)GetColor((int)ColID[6]).b, 1.0f };
	GLfloat light6_diffuse[4];	GLfloat light6_specular[4];	GLfloat light6_position[4];
	memmove( light6_diffuse, light6_ambient, sizeof(light6_ambient) );
	memmove( light6_specular, light0_specular, sizeof(light0_specular) );
	memmove( light6_position, light0_position, sizeof(light0_specular) );

	GLfloat light7_ambient[4] = { (float)GetColor((int)ColID[7]).r, (float)GetColor((int)ColID[7]).g, (float)GetColor((int)ColID[7]).b, 1.0f };
	GLfloat light7_diffuse[4];	GLfloat light7_specular[4];	GLfloat light7_position[4];
	memmove( light7_diffuse, light7_ambient, sizeof(light7_ambient) );
	memmove( light7_specular, light0_specular, sizeof(light0_specular) );
	memmove( light7_position, light0_position, sizeof(light0_specular) );

	GLfloat mat_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 100.0 };
	
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv( GL_LIGHT0, GL_POSITION, light0_position );
	glLightfv( GL_LIGHT0, GL_AMBIENT,  light0_ambient );
	glLightfv( GL_LIGHT0, GL_DIFFUSE,  light0_diffuse );
	glLightfv( GL_LIGHT0, GL_SPECULAR, light0_specular );
	glLightfv( GL_LIGHT1, GL_POSITION, light1_position );
	glLightfv( GL_LIGHT1, GL_AMBIENT,  light1_ambient );
	glLightfv( GL_LIGHT1, GL_DIFFUSE,  light1_diffuse );
	glLightfv( GL_LIGHT1, GL_SPECULAR, light1_specular );
	glLightfv( GL_LIGHT2, GL_POSITION, light2_position );
	glLightfv( GL_LIGHT2, GL_AMBIENT,  light2_ambient );
	glLightfv( GL_LIGHT2, GL_DIFFUSE,  light2_diffuse );
	glLightfv( GL_LIGHT2, GL_SPECULAR, light2_specular );
	glLightfv( GL_LIGHT3, GL_POSITION, light3_position );
	glLightfv( GL_LIGHT3, GL_AMBIENT,  light3_ambient );
	glLightfv( GL_LIGHT3, GL_DIFFUSE,  light3_diffuse );
	glLightfv( GL_LIGHT3, GL_SPECULAR, light3_specular );
	glLightfv( GL_LIGHT4, GL_POSITION, light4_position );
	glLightfv( GL_LIGHT4, GL_AMBIENT,  light4_ambient );
	glLightfv( GL_LIGHT4, GL_DIFFUSE,  light4_diffuse );
	glLightfv( GL_LIGHT4, GL_SPECULAR, light4_specular );
	glLightfv( GL_LIGHT5, GL_POSITION, light5_position );
	glLightfv( GL_LIGHT5, GL_AMBIENT,  light5_ambient );
	glLightfv( GL_LIGHT5, GL_DIFFUSE,  light5_diffuse );
	glLightfv( GL_LIGHT5, GL_SPECULAR, light5_specular );
	glLightfv( GL_LIGHT6, GL_POSITION, light6_position );
	glLightfv( GL_LIGHT6, GL_AMBIENT,  light6_ambient );
	glLightfv( GL_LIGHT6, GL_DIFFUSE,  light6_diffuse );
	glLightfv( GL_LIGHT6, GL_SPECULAR, light6_specular );
	glLightfv( GL_LIGHT7, GL_POSITION, light7_position );
	glLightfv( GL_LIGHT7, GL_AMBIENT,  light7_ambient );
	glLightfv( GL_LIGHT7, GL_DIFFUSE,  light7_diffuse );
	glLightfv( GL_LIGHT7, GL_SPECULAR, light7_specular );

}


inline void EnableLight(int value){
	//Turn on the light source
	glEnable( GL_LIGHTING );
	glEnable( GL_NORMALIZE );

	switch (value){
	case 0:
		glEnable( GL_LIGHT0 );
		break;
	case 1:
		glEnable( GL_LIGHT1 );
		break;
	case 2:
		glEnable( GL_LIGHT2 );
		break;
	case 3:
		glEnable( GL_LIGHT3 );
		break;
	case 4:
		glEnable( GL_LIGHT4 );
		break;
	case 5:
		glEnable( GL_LIGHT5 );
		break;
	case 6:
		glEnable( GL_LIGHT6 );
		break;
	case 7:
		glEnable( GL_LIGHT7 );
		break;
	}
}


inline void DisableLight(void){
	
	glDisable( GL_LIGHT0);	glDisable( GL_LIGHT1);	glDisable( GL_LIGHT2);
	glDisable( GL_LIGHT3);	glDisable( GL_LIGHT4);	glDisable( GL_LIGHT5);
	glDisable( GL_LIGHT6);	glDisable( GL_LIGHT7);

	// turn off the light source
	glDisable( GL_LIGHTING );
	glDisable( GL_NORMALIZE );
}

//inline void LEGOlight(CColor& C){
//	//CVector3d EyePos0(-35.0, 35.0, 50.0);
//
//	GLfloat materialCol[4] = { (GLfloat)C.r, (GLfloat)C.g, (GLfloat)C.b, 1};		
//
//	GLfloat light0_position[4] = { (GLfloat)GLSettings0.m_EyePos[0], (GLfloat)GLSettings0.m_EyePos[1], (GLfloat)GLSettings0.m_EyePos[2], 0.0f };
//	GLfloat light0_ambient[4] = {1.0f,1.0f,1.0f, 1.0f };  //Ambient light
//	GLfloat light0_diffuse[4] = { 1.0f, 1.0f, 1.0f, .5f };  //
//	GLfloat light0_specular[4] = { 1.0f, 1.0f, 1.0f, .5f };  //
//
//	glLightfv( GL_LIGHT0, GL_POSITION, light0_position );
//	glLightfv( GL_LIGHT0, GL_AMBIENT,  light0_ambient );
//	glLightfv( GL_LIGHT0, GL_DIFFUSE, light0_diffuse );
//	glLightfv( GL_LIGHT0, GL_SPECULAR,  light0_specular );
//
//	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialCol);
//	
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//}



inline void DrawString(char *string, CVector3d V, void *font, GLint alignment ){
	glRasterPos3d(V.x,V.y,V.z);
	for(; *string; *string++){
		gl2psTextOpt( string, "Times-Roman", 64, alignment, 0.0f);
		glutBitmapCharacter(font, *string);	
	}
}

//                                                                   
//　　　　　　　　 LEGO　　　　　　　　　　 
//                                                                   
inline void DrawSolidCuboid(CVector3d center , double leng)
{
	glPushMatrix();
	//glRotatef(50, 0.0, 0.0, 1.0);
	glTranslated(center.x , center.y , center.z);
	glScaled(1.0, 1.0, scale);
	glutSolidCube(leng);
	glPopMatrix();
}
//                                                                                                     
//                    LEGO　                              
//                                                                                                     
inline void DrawWireCuboid(CVector3d& center , double leng)
{	
	glPushMatrix();		
	glTranslated(center.x, center.y, center.z);
	//glRotatef(50, 0.0, 0.0, 1.0);
	glScaled(1.0, 1.0, scale);							
	glutWireCube(leng);									
	glPopMatrix();										
}

//                                                                                             
inline void DrawSolidCuboid(CVector3d& center , double leng, CColor& Vcolor)
{
	//Voxel material setting
	GLfloat color[4] ={(float)Vcolor.r, (float)Vcolor.g, (float)Vcolor.b, 0.9f};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
	

	glPushMatrix();
	glTranslated(center.x , center.y , center.z);
	glScaled(1.0, 1.0, scale);
	glutSolidCube(leng);
	glPopMatrix();
}
//                                                                                                     
//                                           
//                                                                                                     
inline void DrawWireCuboid(CVector3d& center , double leng, CColor& Vcolor)
{
	GLfloat color[4] ={(float)Vcolor.r, (float)Vcolor.g, (float)Vcolor.b, 1.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

	glPushMatrix();				       
	glTranslated(center.x , center.y , center.z);   //Move the voxel as it is at the origin at the beginning
	glScaled(1.0, 1.0, scale);			//Scale of cube in x, y, z axis direction
	glutWireCube(leng);				//Draw a wire cube
	glPopMatrix();					//Without this the voxel, it will not go to its original position
}

//                                                                                             
//　                LEGO 　　　　　　　
//                                                                                             
inline void DrawSolidBlock(CVector3d center, CVector3d scale)
{
	glPushMatrix();
	glTranslated(center.x , center.y , center.z);
	glScaled(scale.x, scale.y, scale.z);
	glutSolidCube(1.0);
	glPopMatrix();
}
//                                                                                                     
//                   For rectangular parallelepiped voxel drawing (LEGO)                             
//                                                                                                     
inline void DrawWireBlock(CVector3d center, CVector3d scale)
{
	glPushMatrix();
	glTranslated(center.x , center.y , center.z);
	glScaled(scale.x, scale.y, scale.z);
	glutWireCube(1.0);
	glPopMatrix();
}

// draw a cylinder
// d is the radius, s is the length
inline void DrawCylinder(GLdouble d, GLdouble s){
	int m = 1, n = 12;
	double u0, u1, v0;
	
	for(int i=0; i<m; ++i){
		u0 = (double)i*s/(double)m;
		u1 = (double)(i+1)*s/(double)m;
		glBegin(GL_QUAD_STRIP);
		for(int j=0; j<=n; ++j){
			v0 = (double)j*2.0*M_PI/(double)n;
			glNormal3d(cos(v0), sin(v0), 0.0);
			glVertex3d(d*cos(v0), d*sin(v0), u0);
			glVertex3d(d*cos(v0), d*sin(v0), u1);
		}
		glEnd();
	}
	
}

// draw the face of the circle
inline void DrawCircle(GLdouble d, int n){
	int i;
	double t;
	glBegin(GL_TRIANGLE_STRIP);
	for(i=0; i<=n; ++i){
		t = (double)i*2.0*M_PI/(double)n;
		glNormal3d(0.0, 0.0, 1.0);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(d*cos(t), d*sin(t), 0.0);
	}
	glEnd();
}

//Draw a circle
inline void DrawCircleLine(GLdouble d, int n){
	int i;
	double dt;
	glBegin(GL_LINE_STRIP);
	for(i=0; i<=n; ++i){
		dt = 2.0*M_PI/(double)n;
		glVertex3d(d*cos((double)i*dt), d*sin((double)i*dt), 0.0);
		glVertex3d(d*cos((double)(i+1)*dt), d*sin((double)(i+1)*dt), 0.0);
	}
	glEnd();
}


//Write a circle face at an arbitrary position and direction
inline void DrawCircleAnyDirection(CVector3d P, CVector3d N, GLdouble d, int n){
	N.Normalize(N);
	double r = acos(N.z);
	glPushMatrix();
	glTranslated( P.x,P.y,P.z );
	glRotated(r * 180.0 / M_PI, -N.y, N.x, 0.0);
	DrawCircle(d,n);
	glPopMatrix();
}

//Write a circle line at an arbitrary position and direction
inline void DrawCircleLineAnyDirection(CVector3d P, CVector3d N, GLdouble d, int n){
	N.Normalize(N);;
	double r = acos(N.z);
	glPushMatrix();
	glTranslated( P.x,P.y,P.z );
	glRotated(r * 180.0 / M_PI, -N.y, N.x, 0.0);
	DrawCircleLine(d,n);
	glPopMatrix();
}

//Draw a sphere
inline void DrawSphere( CVector3d A, double radius ){
	int n = 12;
	glPushMatrix();
	glTranslated( A.x,A.y,A.z );
	glutWireSphere(radius,n,n);
	//glutSolidSphere(radius,n,n);
	glPopMatrix();
}

// draw a cylinder line
// cylinder connecting point A and point B
inline void DrawPipe( CVector3d A, CVector3d B, double radius ){
	CVector3d C = B - A;
	double h = C.Norm();
	double r;
	if(h > 0.0){
		r = acos(C.z / h);
		glPushMatrix();
		glTranslated(A.x,A.y,A.z);
		glRotated(r * 180.0 / M_PI, -C.y, C.x, 0.0);
		DrawCylinder(radius,h);
		glPopMatrix();
	}
}


inline void DrawCone(double r, double h, int n){
	double t0;

	glBegin(GL_TRIANGLE_STRIP);
	for(int i=0; i<=n; ++i){
		t0 = (double)i*2.0*M_PI/(double)n;
		glNormal3d(cos(t0), sin(t0), r/h);
		glVertex3d(0.0, 0.0, h);
		glNormal3d(cos(t0), sin(t0), r/h);
		glVertex3d(r*cos(t0), r*sin(t0), 0.0);		
	}
	glEnd();

	glPushMatrix();
	glRotated(180, 1.0, 0.0, 0.0);
	DrawCircle(r,n);
	glPopMatrix();
}


inline void CalcAllowScale(double h, double cr, double ch, double &coner, double &coneh, double &radius){
	coner = cr*radius;	// radius of the cone
	coneh = ch*coner;	//Length of cone

	//When h is too short
	if(0.5*h<coneh){
		coneh=0.5*h;
		coner=coneh/ch;
		radius=coner/cr;
	}
}

inline void DrawAllowOpt( CVector3d V, CVector3d T, double h, double radius, double cr, double ch, int n){
	T.Normalize(T);	//Unitization of T

	double coner;	
	double coneh;	

	CalcAllowScale(h,cr,ch,coner,coneh,radius);

	if(h!=0.0){
		double angle = acos(T.z) * 180.0/M_PI;
		glPushMatrix();
		glTranslated(V.x,V.y,V.z);
		glRotated(angle, -T.y, T.x, 0.0);
		DrawCylinder(radius,h-coneh);

		glTranslated(0.0,0.0,h-coneh);
		DrawCone(coner, coneh, n);
		glPopMatrix();
	}

}

//
inline void DrawAllow( CVector3d V, CVector3d T, double h, double radius){
	DrawAllowOpt(V, T, h, radius, 2.5, 1.618*2.0, 12);
	//1.618
}

inline void ClacAllow(CVector3d V, CVector3d T, double h, double &radius, double &coner, CVector3d &Cbot, CVector3d &Ctop){
	T.Normalize(T);
	double coneh;	
	CalcAllowScale(h,2.5,1.618*2.0,coner,coneh,radius);
	Cbot = V + ((h-coneh) * T);
	Ctop = V + h * T;
}

//**********************
//	POV-Ray
//**********************

inline CVector3d RotEye(CVector3d Rot, CVector3d View){
	//View = View.RotateZ(-Rot.z*M_PI/180.0);
	//View = View.RotateY(-Rot.y*M_PI/180.0);
	//View = View.RotateX(-Rot.x*M_PI/180.0);
	View = View.RotateX(-Rot.x*M_PI/180.0);
	View = View.RotateY(-Rot.y*M_PI/180.0);
	View = View.RotateZ(-Rot.z*M_PI/180.0);
	return View;
}

//inline CVector3d RotTransEye(CVector3d Eye, CVector3d Rot, CVector3d V){
//	V -= Eye;
//	V = V.RotateX(Rot.x*M_PI/180.0);
//	V = V.RotateY(Rot.y*M_PI/180.0);
//	V = V.RotateZ(Rot.z*M_PI/180.0);
//	return V;
//}

// Output coordinate as character string
// Convert to left handed coordinates and output
inline string P2S( CVector3d A ){
	ostringstream B;
	B << "<" << A.x << "," << A.y << "," << -A.z << ">";
	return B.str();
}
// Output as right handed type
inline string P2S_R( CVector3d A ){
	ostringstream B;
	B << "<" << A.x << "," << A.y << "," << A.z << ">";
	return B.str();
}

inline void DrawCylinder_Pov( ostringstream &ssPov, CVector3d A, CVector3d B, double rc, string material ){
	if(A.Distance(B)>1.0e-14){
		if(rc>1.0e-14){
			ssPov << "cylinder{" << P2S(A) <<", "<< P2S(B) <<","<< rc <<" material{" << material <<"} no_shadow}"<< endl;
		}
	}
}


inline void DrawSphere_Pov( ostringstream &ssPov, CVector3d A, double rs, string material ){
	if(rs>1.0e-14){
		ssPov << "sphere{" << P2S(A) <<", "<< rs <<" material{" << material <<"} no_shadow}"<< endl;
	}
}

inline void DrawAllow_Pov( ostringstream &ssPov, CVector3d V, CVector3d T, double h, double piper, string material ){
	if(h>1.0e-14&&piper>1.0e-14&&T.Norm()>1.0e-14){	// Do not display small
		double coner;	CVector3d Cbot, Ctop;
		ClacAllow( V, T, h, piper, coner, Cbot, Ctop);
		ssPov << "cylinder{" << P2S(V) <<", "<< P2S(Cbot) <<"," << piper <<" material{" << material <<"}}"<< endl;
		ssPov << "cone{" << P2S(Cbot) <<", "<< coner <<"," << P2S(Ctop) <<",0.0 material{" << material <<"}}"<< endl;
	}
}


inline void DrawTriangle_Pov( ostringstream &ssPov, CVector3d A, CVector3d B, CVector3d C, string material ){
	ssPov << "triangle{" << P2S(A) <<", "<< P2S(B) <<", "<< P2S(C) <<" material{" << material <<"}}"<< endl;
}

inline void DrawSmoothTriangle_Pov( ostringstream &ssPov, CVector3d Va, CVector3d Na, CVector3d Vb, CVector3d Nb, CVector3d Vc, CVector3d Nc, string material ){
	ssPov << "smooth_triangle{" << P2S(Va) <<", "<< P2S(Na) <<", "<< P2S(Vb) <<", "<< P2S(Nb) <<", "<< P2S(Vc) <<", "<< P2S(Nc) <<" material{" << material <<"}}"<< endl;
}

#endif
