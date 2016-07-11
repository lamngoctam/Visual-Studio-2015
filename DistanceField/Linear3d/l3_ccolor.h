#pragma once
/*****************************************************************
�F���̃��C�u���� �N���X���FColor

���g�p��
�@�F�t��
glColor3dv(GetColor(CColor::magenta));
��L�����������ŐF���}�[���^�ɕς��܂��B
�܂��A
glColor3dv(GetColor(37));
�ł��}�[���^�̐F�ƂȂ�܂��B

�A�J���[�o�[���g���ꍇ
CColor tmp;
tmp.ColorBar(value,max,min,PalettesCaseNumber,LinearFlag);
����: value:�l, max,min:�J���[�o�[�̍ő�l�A�ŏ��l
PalettesCaseNumber:0�Ȃ�RGB, 
LinearFlag:1���Ɛ��`�ŐF�̕�ԁA2���ƎO�p�֐��ɂ��F�̕��
tmp�̒��ɒl���i�[����܂��B

�F�̖��̂�HTML�ŗp�����閼�O�Ɠ���ɂ��Ă��܂��B
�ڂ�����wiki�������Ċe���׋����ĉ������B

�F�ɂ��Ă͈ȉ����Q�l�ɁI
WEB�F���{�@���F�厫�T	http://www.colordic.org/
wikipedia �E�F�u�J���[	http://ja.wikipedia.org/wiki/%E3%82%A6%E3%82%A7%E3%83%96%E3%82%AB%E3%83%A9%E3%83%BC
�F���ւɂ���			http://homepage3.nifty.com/ishidate/vcpp_color/vcpp_color.htm
******************************************************************/

//###################################################//
//	CColor (RGB�N���X)								 //
//###################################################//
class CColor
{
public://�����o�[�ϐ�
	double r;	//��
	double g;	//��
	double b;	//��

	CColor();									//�y01�z�R���X�g���N�^
	CColor(double R, double G, double B);		//�y02�z�R���X�g���N�^
	void Set(double R, double G, double B);		//�y03�z�ݒu
	void SetGL(double R, double G, double B);	//�y04�z�ݒu
	void Clear();								//�y05�z���ŃN���A
	void Print();								//�y06�z�o��
	void ColorBar(double value, double max, double min, int PalettesCaseNumber=0, bool LinearFlag=1);	//�y7�z�J���[�o�[�p�֐�
	operator double*();							//�y08�z�I�[�o�[���[�h
	//HTML�ł̐F����
	enum Color_Name{
		/****** �Ԍn�̐F(09�F) ID:000�`008 *****/
		indianred,		lightcoral,	salmon,		darksalmon,			//�Ԍn�̐F ID:0�`8
		lightsalmon,	crimson,	red,		firebrick,			//�Ԍn�̐F ID:0�`8
		darkred,													//�Ԍn�̐F ID:0�`8
		/****** ���n�̐F(06�F) ID:009�`014 *****/
		pink,			lightpink,	hotpink,	deeppink,			//���n�̐F ID:9�`14
		mediumvioletred,	palevioletred,							//���n�̐F ID:9�`14
		/****** ��n�̐F(06�F) ID:015�`019 *****/
		coral,		tomato,		orangered,		darkorange,			//��n�̐F ID:15�`19
		orange,														//��n�̐F ID:15�`19
		/****** ���n�̐F(11�F) ID:020�`030 *****/
		gold,			yellow,		lightyellow,	lemonchiffon,	//���n�̐F ID:20�`30
		lightgoldenrodyellow,		papayawhip,		moccasin,		//���n�̐F ID:20�`30
		peachpuff,		palegoldenrod,	khaki,		darkkhaki,		//���n�̐F ID:20�`30
		/****** ���n�̐F(19�F) ID:031�`049 *****/
		lavender,		thistle,	plum,		violet,				//���n�̐F ID:31�`49
		orchid,			fuchsia,	magenta,	mediumorchid,		//���n�̐F ID:31�`49
		mediumpurple,	amethyst,	blueviolet,	darkviolet,			//���n�̐F ID:31�`49
		darkorchid,		darkmagenta,	purple,		indigo,			//���n�̐F ID:31�`49
		slateblue,		darkslateblue,	mediumslateblue,			//���n�̐F ID:31�`49
		/***** �Όn�̐F(23�F) ID:050�`072 *****/
		greenyellow,	chartreuse,	lawngreen,	lime,				//�Όn�̐F ID:50�`72
		limegreen, 		palegreen,	lightgreen, mediumspringgreen,	//�Όn�̐F ID:50�`72
		springgreen, 	mediumseagreen, 		seagreen,			//�Όn�̐F ID:50�`72
		forestgreen, 	green,		darkgreen, 	yellowgreen,		//�Όn�̐F ID:50�`72
		olivedrab,		olive,		darkolivegreen,					//�Όn�̐F ID:50�`72
		mediumaquamarine,			darkseagreen,					//�Όn�̐F ID:50�`72
		lightseagreen,	darkcyan,	teal,							//�Όn�̐F ID:50�`72
		/***** �n�̐F(25�F) ID:073�`096 *****/
		aqua,			cyan,		lightcyan,	paleturquoise,		//�n�̐F ID:73�`96
		aquamarine,		turquoise,	mediumturquoise,				//�n�̐F ID:73�`96
		darkturquoise,	cadetblue,	steelblue, 	lightsteelblue,		//�n�̐F ID:73�`96
		powderblue,		lightblue,	skyblue, 	lightskyblue,		//�n�̐F ID:73�`96
		deepskyblue,	dodgerblue,	cornflowerblue,					//�n�̐F ID:73�`96
		royalblue,		blue,		mediumblue,						//�n�̐F ID:73�`96
		darkblue,		navy,		midnightblue,					//�n�̐F ID:73�`96
		/***** ���n�̐F(17�F) ID:097�`113 *****/
		cornsilk,		blanchedalmond,			bisque,				//���n�̐F ID:97�`113
		navajowhite,	wheat,		burlywood, 	tan,				//���n�̐F ID:97�`113
		rosybrown,		sandybrown,	goldenrod, 	darkgoldenrod,		//���n�̐F ID:97�`113
		peru,			chocolate, 	saddlebrown,sienna,				//���n�̐F ID:97�`113
		brown,			maroon, 
		/***** ���n�̐F(17�F) ID:114�`130 *****/
		white,			snow,		honeydew,	mintcream,			//���n�̐F ID:114�`130
		azure,			aliceblue, 	ghostwhite, whitesmoke,			//���n�̐F ID:114�`130
		seashell, 		beige, 		oldlace, 	floralwhite,		//���n�̐F ID:114�`130
		ivory, 			antiquewhite,			linen,				//���n�̐F ID:114�`130
		lavenderblush, 	mistyrose, 
		/***** �D�n�̐F(10�F) ID:131�`140*****/
		gainsboro,		lightgrey,	silver,		darkgray,			//�D�n�̐F ID:131�`140
		gray,			dimgray, 	lightslategray,					//�D�n�̐F ID:131�`140
		slategray, 		darkslategray,			black,				//�D�n�̐F ID:131�`140
		color_num	//�F����141�F
	}colorname;

private:
	CColor ConvertHSVtoRGB(double H, double S, double V, bool LinearFlag=1);	//�y09�zHSV����RGB�֕ϊ�
};


//�F�t��
CColor GetColor(int ColorID);