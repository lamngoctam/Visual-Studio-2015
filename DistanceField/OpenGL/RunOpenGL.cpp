//############################################################################
//複数のウインドウに共通する関数はこのファイルに書いた
//いじる必要はあまりないと思う。いじるとしたら、RunOpenGL関数くらいかな
//############################################################################
#include "../stdafx.h"
#include "OpenGL.h"
#include "OpenGLprimitive.h"

using namespace std;
//#pragma warning(disable : 4996)//about scanf

int WinID[2]; //ウィンドウID

//関数のプロトタイプ宣言
void OpenGLDisplay0(void);
//void OpenGLDisplay1(void);
void OpenGLCallBack0(void);
//void OpenGLCallBack1(void);
void OpenGLPreparation0();
//void OpenGLPreparation1();


/***************************************************/
/*			　OpenGLディスプレイ関数		　　   */
/***************************************************/
//ディスプレイ関数前処理
void DisplayInit(){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glEnable(GL_BLEND);	//透過処理
	glBlendFunc(GL_ONE, GL_ZERO);

	SetLight();	//ここで光源設定すれば、光源は視点に固定

	glPushMatrix();
}

//ディスプレイ関数後処理
void DisplayPostprocessor(){
	glDepthMask(TRUE);//透過処理end
	glDisable(GL_BLEND);

	glPopMatrix();
	glutSwapBuffers();
}


/***************************************************/
/*			　OpenGLピックアップ関数		　　   */
/***************************************************/
//ピッキング関数前処理
//いじるとしたら、ピッキング領域のところ。
void PickUpInit(int x, int y){
	GLint viewport[4];
	double current_aspect;
	glGetIntegerv(GL_VIEWPORT, viewport);

	(void) glRenderMode(GL_SELECT);

	glInitNames();
	glMatrixMode(GL_PROJECTION);			//プロジェクションモード
	glPushMatrix();							//セレクションモードのときのみ下の行列計算
	glLoadIdentity();						//を反映させるためにPushする

	//ピッキング行列の乗算
	gluPickMatrix(x,viewport[3]-y, 25.0, 25.0, viewport);
	//3番目の引数はx方向のピクセル数、4番目の引数はy方向のピクセル数
	//クリックしたピクセルの周囲ピクセルをどのくらいピッキング領域に含めるかどうか。
	//ピッキング領域内に入っている物体は全てヒットする。

	current_aspect = (double)viewport[2]/(double)viewport[3];

	gluPerspective( 10.0, current_aspect, 0.01, -1.0 );

	glMatrixMode( GL_MODELVIEW );		//ここでモデルビューモードにする！！！！
	glPushMatrix();	
}

//ピッキング関数後処理
void PickUpPostprocessor(void){
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );			//モデルビューモードへ戻す
}

//ヒットした物体のIDを取得
//ヒットした複数の物体の中から、一番手前に設置されている物体を選択
int SelectHits( GLuint hits, GLuint* buf, int hit_name[2] ){
	hit_name[0]=-1;
	hit_name[1]=-1;	//階層は２

	double depth_min=10.0;	//一番奥
	double depth_1=1.0;
	double depth_2=1.0;
	GLuint depth_name;
	GLuint *ptr;
	// ヒットしたデータなし
	if(hits<=0){
		return -1;
	}

	// ポインタを作業用ptrへ渡す．
	ptr = buf;

	//ヒットした数だけ巡る
	for(unsigned int i=0; i<hits; ++i){
		depth_name = *ptr;	// 識別番号の階層の深さ	//ネームスタックに積まれた名前の数

		//OpenGLにおいて、面積を持つ物体（teapotなど）はポリゴンメッシュとして表現されている。
		//そのポリゴンメッシュが含む頂点の中で、一番奥にあるものと一番手前にあるものがある。
		++ptr;
		depth_1 = *ptr/0x7fffffff;	//選択範囲を横切るプリミティブの頂点のデプス値の最小値
		//一番手前にある頂点の深さ

		++ptr;
		depth_2 = *ptr/0x7fffffff;	//選択範囲を横切るプリミティブの頂点のデプス値の最大値
		//一番奥にある頂点の深さ

		// 最小デプスの確認
		if(depth_min>depth_1){	//もし手前の頂点の深さが、最小デプスより小さければ
			depth_min = depth_1;	//その頂点の深さを最小デプスにする。

			//識別番号の階層の深さ分だけ巡る
			for(unsigned int j=0; j<depth_name; ++j){
				++ptr;
				hit_name[j] = (int)(*ptr);	//その頂点のid情報をhit_nameに格納
			}
		}else{		//もし手前の頂点の深さが最小デプスよりも大きければ
			for(unsigned int j=0; j<depth_name; ++j){
				++ptr;		//id情報は格納しない。スルーする。
			}
		}
		++ptr;	//次の選択物体へ
	}
	return hit_name[0];
}


//クリックしたところに設置してあるもののデプス値を取得する。
double ReturnDepth( int x, int y ){
	double z;
	GLint viewport[4];			//ビューポート
	//デバイス座標系とウィンドウ座標系の変換
	glGetIntegerv(GL_VIEWPORT,viewport);	//現在のビューポートを代入
	glReadPixels(x,viewport[3]-y,1,1,
		GL_DEPTH_COMPONENT,
		GL_FLOAT,
		&z);
	return z;
}




/***************************************************/
/*				　　eps書き出し関数　　	　　   　　*/
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
		}else if(winid==WinID[1]){
			//OpenGLDisplay1();
		}

		state = gl2psEndPage();
	}

	fclose(fp);
	printf("Done!\n");
	fflush(stdout);
}


/***************************************************/
/*			　　	bmp書き出し関数　　	　　   　　*/
/***************************************************/
void writebmpfile(char *filename, char *extension, int winid){
	char file[256];
	strcpy_s(file, filename);
	strcat_s(file, ".");
	strcat_s(file, extension);

	if(winid==WinID[0]){
		OpenGLDisplay0();
	}else if(winid==WinID[1]){
	//	OpenGLDisplay1();
	}

	gl_screenshot gs;
	gs.screenshot(file, 24);
}


/***************************************************/
/*					何もしないとき	　　	　　   */
/***************************************************/
void OpenGLIdle(void){
	glutPostRedisplay();
}




/***************************************************/
/*			　　　OpenGL初期化関数				   */
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
/*			　　　OpenGL後処理関数				   */
/***************************************************/
void OpenGLPostprocessor(OpenGL GLSettings){
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );	//背景色
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
/*			　　　OpenGL実装関数	　　	　　   */
/***************************************************/
void RunOpenGL0(int argc, char *argv[]){
	glutInit(&argc, argv);		//freeglutだと必要
	OpenGLPreparation0();
	OpenGLCallBack0();	//窓0
	glutMainLoop();		//ループに入り、入力待機モードになる。
}

//void RunOpenGL1(int argc, char *argv[]){
//	glutInit(&argc, argv);		//freeglutだと必要
//	OpenGLPreparation1();
//	OpenGLCallBack1();	//窓1
//	glutMainLoop();		//ループに入り、入力待機モードになる。
//}
