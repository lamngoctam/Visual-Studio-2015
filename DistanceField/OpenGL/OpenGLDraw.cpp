//############################################################################
//このファイルは物体の描画関数を書きます
//よくいじるファイルになると思う
//############################################################################
#include "../stdafx.h"
#include "OpenGL.h"
#include "OpenGLprimitive.h"
using namespace std;



extern OpenGL GLSettings0;	//窓0の設定

//#################################################
//	座標軸とか 共通部分を此処に書く
//#################################################
void ConclusiveAxis(void){
	glLineWidth(1.0);
	double radius = 0.01;		//パイプの太さ
	double stringspace = 0.05;	//文字と軸の隙間

	CVector3d O(0.0, 0.0, 0.0);				CVector3d X(1.0, 0.0, 0.0);
	CVector3d Y(0.0, 1.0, 0.0);		CVector3d Z(0.0, 0.0, 1.0);

	CVector3d Os( stringspace, stringspace, stringspace );
	CVector3d Xs(  -2.0*stringspace, stringspace, stringspace );
	CVector3d Ys(  -2.0*stringspace,  -2.0*stringspace, stringspace );
	CVector3d Zs( -2.0*stringspace, -2.0*stringspace, stringspace );

	glColor3d(0.0,0.0,0.0);
	DrawString("O", O +Os, GLUT_BITMAP_TIMES_ROMAN_24, GL2PS_TEXT_BL);	

	//x軸
	EnableLight(7);
	DrawAllowOpt( -X , X , 2.0, radius, 3.5, 1.618*2.0, 12);
	DisableLight();
	glColor3d(0.0,0.0,0.0);
	DrawString("X", X + Xs, GLUT_BITMAP_TIMES_ROMAN_24, GL2PS_TEXT_BL);


	//y軸
	EnableLight(7);
	DrawAllowOpt( -Y, Y, 2.0, radius, 3.5, 1.618*2.0, 12);
	DisableLight();
	glColor3d(0.0,0.0,0.0);
	DrawString("Y", Y + Ys, GLUT_BITMAP_TIMES_ROMAN_24, GL2PS_TEXT_BL);


	//z軸
	EnableLight(7);
	DrawAllowOpt( -Z, Z, 2.0, radius, 3.5, 1.618*2.0, 12);
	DisableLight();
	glColor3d(0.0,0.0,0.0);
	DrawString("Z", Z + Zs, GLUT_BITMAP_TIMES_ROMAN_24, GL2PS_TEXT_BL);

}

//And stores the current point of view
void SaveView(double &m_EyeDis, CVector3d &m_Center, CVector3d &m_Front,CVector3d &m_Upper)
{
	string FileName="SaveView.txt";	
	ofstream fout(FileName.c_str());
	fout<<m_EyeDis<<endl;
	fout<<m_Center.x<<" "<<m_Center.y<<" "<<m_Center.z<<endl;
	fout<<m_Front.x<<" "<<m_Front.y<<" "<<m_Front.z<<endl;
	fout<<m_Upper.x<<" "<<m_Upper.y<<" "<<m_Upper.z<<endl;
	fout.close();
}

//To move the stored viewpoi
void ChangeView(double &m_EyeDis, CVector3d &m_Center, CVector3d &m_Front,CVector3d &m_Upper)
{
	string FileName="SaveView.txt";	

	ifstream file1(FileName.c_str());
	if (!file1){
		cout <<"File not found!"<< endl;
	}

	file1>>m_EyeDis;
	file1>>m_Center.x>>m_Center.y>>m_Center.z;
	file1>>m_Front.x>>m_Front.y>>m_Front.z;
	file1>>m_Upper.x>>m_Upper.y>>m_Upper.z;
	file1.close();
}
//#################################################
//Drawing of the voxel
// ################################################ #
// Depict a voxel with a wire frame
void DrawLineBox(double *r, double l)
{
	glBegin(GL_LINES);////////////////////////ここで12本の辺を描いている
	glVertex3d( r[0] , r[1] , r[2] );
	glVertex3d( r[0]+l , r[1] , r[2] );
	glEnd();

	glBegin(GL_LINES);
	glVertex3d( r[0] , r[1] , r[2] );
	glVertex3d( r[0] , r[1]+l , r[2] );
	glEnd();

	glBegin(GL_LINES);
	glVertex3d( r[0] , r[1]+l , r[2] );
	glVertex3d( r[0]+l , r[1]+l , r[2] );
	glEnd();

	glBegin(GL_LINES);
	glVertex3d( r[0]+l , r[1] , r[2] );
	glVertex3d( r[0]+l , r[1]+l , r[2] );
	glEnd();


	glBegin(GL_LINES);
	glVertex3d( r[0] , r[1] , r[2] );
	glVertex3d( r[0] , r[1] , r[2]+l );
	glEnd();

	glBegin(GL_LINES);
	glVertex3d( r[0] , r[1]+l , r[2] );
	glVertex3d( r[0] , r[1]+l , r[2]+l );
	glEnd();

	glBegin(GL_LINES);
	glVertex3d( r[0]+l , r[1] , r[2] );
	glVertex3d( r[0]+l , r[1] , r[2]+l );
	glEnd();

	glBegin(GL_LINES);
	glVertex3d( r[0]+l , r[1]+l , r[2] );
	glVertex3d( r[0]+l , r[1]+l , r[2]+l );
	glEnd();


	glBegin(GL_LINES);
	glVertex3d( r[0] , r[1] , r[2]+l );
	glVertex3d( r[0]+l , r[1] , r[2]+l );
	glEnd();

	glBegin(GL_LINES);
	glVertex3d( r[0] , r[1] , r[2]+l );
	glVertex3d( r[0] , r[1]+l , r[2]+l );
	glEnd();

	glBegin(GL_LINES);
	glVertex3d( r[0] , r[1]+l , r[2]+l );
	glVertex3d( r[0]+l , r[1]+l , r[2]+l );
	glEnd();

	glBegin(GL_LINES);
	glVertex3d( r[0]+l , r[1] , r[2]+l );
	glVertex3d( r[0]+l , r[1]+l , r[2]+l );
	glEnd();



}
// Solid voxel drawing)
void DrawSolidBox(double *r, double leng)
{
	glPushMatrix();
	glTranslated(r[0]+0.5*leng, r[1]+0.5*leng, r[2]+0.5*leng);
	glutSolidCube(leng);
	glTranslated(-r[0]-0.5*leng, -r[1]-0.5*leng, -r[2]-0.5*leng);
	glPopMatrix();

}

// Display the coordinates of the point
void DrawDV(double *r){
	glPointSize( 5 );
	glBegin(GL_POINTS);
	glVertex3d( r[0] , r[1] , r[2] );
	glEnd();
}



void Draw_voxel(Voxel &VM,int num){
	CVector3d U,D;
	GLfloat color[4] = { 0.0, 0.0, 0.0, 1.0 };	
	GLfloat white[4] = {1.0, 1.0, 1.0, 1.0};
	GLfloat black[4] = {0.5, 0.5, 0.5, 1.0};
	GLfloat shininess = 30;		//最大128（プラスチックの場合は１０～４０）
	GLfloat light0_position[4] = { (float)GLSettings0.m_Eye.x, (float)GLSettings0.m_Eye.y, (float)GLSettings0.m_Eye.z, 1.0f };//光源の位置 ＝ 視点の位置

	//////Setting of the light source--------------------------------------
	//glEnable(GL_DEPTH_TEST);
	//glEnable( GL_NORMALIZE );
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);			//光源0を利用

	//glLightfv(GL_LIGHT0, GL_POSITION, light0_position);				//ライト0の位置を設定する
	//glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, white);		//ライト0のを設定する
	//glLightfv(GL_LIGHT0, GL_SPECULAR, white);								//ライト0のを設定する

	////Setting of common material in all the blocks
	//glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	//glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	double coord[3];
	glLineWidth(0.00001);
	for(int i=1;i<VM.ND[0]-1;i++){
		for(int j=1;j<VM.ND[1]-1;j++){
			for(int k=1;k<VM.ND[2]-1;k++){
				if(!VM.Grid3D[i][j][k].Fill)continue;
				int kkk=num;	

				//if(VM.Grid3D[i][j][k].Fill){		
				//	glColor3b(0,0,0);
				//	coord[0]=VM.OriPt.x+i*VM.Length;
				//	coord[1]=VM.OriPt.y+j*VM.Length;
				//	coord[2]=VM.OriPt.z+k*VM.Length;
				//	DrawLineBox(coord,VM.Length);
				//}
				//if(VM.Grid3D[i][j][k].surf){		
				//	glColor3b(1.0,1.0,0);
				//	coord[0]=VM.OriPt.x+i*VM.Length;
				//	coord[1]=VM.OriPt.y+j*VM.Length;
				//	coord[2]=VM.OriPt.z+k*VM.Length;
				//	DrawLineBox(coord,VM.Length);
				//}
				//if(VM.Grid3D[i][j][k].Dist<=(kkk+1)*VM.Length&&VM.Grid3D[i][j][k].Dist>=(kkk)*VM.Length){

				//EnableLight(2);
				coord[0]=VM.OriPt.x+i*VM.Length;
				coord[1]=VM.OriPt.y+j*VM.Length;
				coord[2]=VM.OriPt.z+k*VM.Length;
				//if(15*i+11*j<10*540&&15*i+11*j>10*538){
				if(k==80&&(15*i+11*j>10*538&&(11*i-15*j>10*(-107)))){
					color[0]=VM.Grid3D[i][j][k].C.r;
					color[1]=VM.Grid3D[i][j][k].C.g;
					color[2]=VM.Grid3D[i][j][k].C.b;
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

					//glColor3dv(VM.Grid3D[i][j][k].Color.r);
					glColor3d(VM.Grid3D[i][j][k].C.r,VM.Grid3D[i][j][k].C.g,VM.Grid3D[i][j][k].C.b);
					DrawSolidBox(coord,VM.Length);
				}
				//else if(15*i+11*j<10*540&&VM.Grid3D[i][j][k].Surf)
				//else if(k>80&&VM.Grid3D[i][j][k].Surf)
				//{
				//	color[0]=VM.Grid3D[i][j][k].C.r;
				//	color[1]=VM.Grid3D[i][j][k].C.g;
				//	color[2]=VM.Grid3D[i][j][k].C.b;
				//		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
				//		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);

				//	//glColor3d(VM.Grid3D[i][j][k].C.r,VM.Grid3D[i][j][k].C.g,VM.Grid3D[i][j][k].C.b);
				//	//DrawSolidBox(coord,VM.Length);
				//	glColor4fv(black);
				//	DrawLineBox(coord,VM.Length);
				//}
				else if(15*i+11*j<10*540&&15*i+11*j>10*538&&k<80&&(11*i-15*j>10*(-107))){
					color[0]=VM.Grid3D[i][j][k].C.r;
					color[1]=VM.Grid3D[i][j][k].C.g;
					color[2]=VM.Grid3D[i][j][k].C.b;
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

					//glColor3dv(VM.Grid3D[i][j][k].Color.r);
					glColor3d(VM.Grid3D[i][j][k].C.r,VM.Grid3D[i][j][k].C.g,VM.Grid3D[i][j][k].C.b);
					DrawSolidBox(coord,VM.Length);
				}
				else if(11*i-15*j<10*(-105)&&11*i-15*j>10*(-107)&&k<80&&15*i+11*j>10*538){
					color[0]=VM.Grid3D[i][j][k].C.r;
					color[1]=VM.Grid3D[i][j][k].C.g;
					color[2]=VM.Grid3D[i][j][k].C.b;
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

					//glColor3dv(VM.Grid3D[i][j][k].Color.r);
					glColor3d(VM.Grid3D[i][j][k].C.r,VM.Grid3D[i][j][k].C.g,VM.Grid3D[i][j][k].C.b);
					DrawSolidBox(coord,VM.Length);
				}
				//else if(11*i-15*j<10*(-185)&&11*i-15*j>10*(-187)){
				//	color[0]=VM.Grid3D[i][j][k].C.r;
				//	color[1]=VM.Grid3D[i][j][k].C.g;
				//	color[2]=VM.Grid3D[i][j][k].C.b;
				//	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

				//	//glColor3dv(VM.Grid3D[i][j][k].Color.r);
				//	glColor3d(VM.Grid3D[i][j][k].C.r,VM.Grid3D[i][j][k].C.g,VM.Grid3D[i][j][k].C.b);
				//	DrawSolidBox(coord,VM.Length);
				//}
				else if((15*i+11*j<10*540||k>80||11*i-15*j<10*(-105))&&VM.Grid3D[i][j][k].Surf)
				{
					color[0]=VM.Grid3D[i][j][k].C.r;
					color[1]=VM.Grid3D[i][j][k].C.g;
					color[2]=VM.Grid3D[i][j][k].C.b;
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

					glColor4fv(color);
					//glColor3d(VM.Grid3D[i][j][k].C.r,VM.Grid3D[i][j][k].C.g,VM.Grid3D[i][j][k].C.b);
					//DrawSolidBox(coord,VM.Length);
					//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
					glColor4fv(black);
					DrawLineBox(coord,VM.Length);
				}

				else if(VM.Grid3D[i][j][k].Surf&&15*i+11*j>10*540){
					//	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
					//glColor4fv(black);

					//DrawLineBox(coord,VM.Length);
				}
				//DisableLight();
				//}
			}
		}
	}
	glDisable(GL_LIGHTING);
}

void Draw_voxel1(Voxel &VM,int num){
	CVector3d U,D;
	GLfloat color[4] = { 0.0, 0.0, 0.0, 1.0 };	
	GLfloat white[4] = {1.0, 1.0, 1.0, 1.0};
	GLfloat black[4] = {0.5, 0.5, 0.5, 1.0};
	GLfloat shininess = 30;		//Up to 128 (10 to 40 in the case of plastic)
	GLfloat light0_position[4] = { (float)GLSettings0.m_Eye.x, (float)GLSettings0.m_Eye.y, (float)GLSettings0.m_Eye.z, 1.0f };//光源の位置 ＝ 視点の位置

	double coord[3];
	glLineWidth(0.00001);
	for(int i=1;i<VM.ND[0]-1;i++){
		for(int j=1;j<VM.ND[1]-1;j++){
			for(int k=1;k<VM.ND[2]-1;k++){
				if(!VM.Grid3D[i][j][k].Fill)continue;
				if(VM.Grid3D[i][j][k].Dist>(num+1))continue;
				if(VM.Grid3D[i][j][k].Dist<=num)continue;
				coord[0]=VM.OriPt.x+i*VM.Length;
				coord[1]=VM.OriPt.y+j*VM.Length;
				coord[2]=VM.OriPt.z+k*VM.Length;
				color[0]=VM.Grid3D[i][j][k].C.r;
				color[1]=VM.Grid3D[i][j][k].C.g;
				color[2]=VM.Grid3D[i][j][k].C.b;
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
				glColor3d(VM.Grid3D[i][j][k].C.r,VM.Grid3D[i][j][k].C.g,VM.Grid3D[i][j][k].C.b);
				DrawSolidBox(coord,VM.Length);
			}
		}
	}
	glDisable(GL_LIGHTING);
}
