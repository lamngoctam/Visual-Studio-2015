#pragma once
/*****************************************************************

WEB	http://www.colordic.org/
wikipedia 	http://ja.wikipedia.org/wiki/%E3%82%A6%E3%82%A7%E3%83%96%E3%82%AB%E3%83%A9%E3%83%BC
******************************************************************/

//###################################################//
//	CColor (RGBNX)								 //
//###################################################//
class CColor
{
public://o[Ο
	double r;	//Τ
	double g;	//Ξ
	double b;	//Β

	CColor();									//y01zRXgN^
	CColor(double R, double G, double B);		//y02zRXgN^
	void Set(double R, double G, double B);		//y03zέu
	void SetGL(double R, double G, double B);	//y04zέu
	void Clear();							//y05zΕNA
	void Print();								//y06zoΝ
	void ColorBar(double value, double max, double min, int PalettesCaseNumber=0, bool LinearFlag=1);	//y7zJ[o[pΦ

	static bool Less_r(const CColor& a, const CColor& b)	{	return a.r < b.r;	};			//LINΗΑiRπΈΙΐΧι½ίΙKvj
	static bool Less_g(const CColor& a, const CColor& b)	{	return a.g < b.g;	};			//LINΗΑiGπΈΙΐΧι½ίΙKvj
	static bool Less_b(const CColor& a, const CColor& b)	{	return a.b < b.b;	};			//LINΗΑiBπΈΙΐΧι½ίΙKvj

	operator double*();							//y08zI[o[[h
	//HTMLΕΜFΌΜ
	enum Color_Name{
		/****** ΤnΜF(09F) ID:000`008 *****/
		indianred,		lightcoral,	salmon,		darksalmon,			//ΤnΜF ID:0`8
		lightsalmon,	crimson,	red,		firebrick,			//ΤnΜF ID:0`8
		darkred,													//ΤnΜF ID:0`8
		/****** nΜF(06F) ID:009`014 *****/
		pink,			lightpink,	hotpink,	deeppink,			//nΜF ID:9`14
		mediumvioletred,	palevioletred,							//nΜF ID:9`14
		/****** ςnΜF(06F) ID:015`019 *****/
		coral,		tomato,		orangered,		darkorange,			//ςnΜF ID:15`19
		orange,														//ςnΜF ID:15`19
		/****** ©nΜF(11F) ID:020`030 *****/
		gold,			yellow,		lightyellow,	lemonchiffon,	//©nΜF ID:20`30
		lightgoldenrodyellow,		papayawhip,		moccasin,		//©nΜF ID:20`30
		peachpuff,		palegoldenrod,	khaki,		darkkhaki,		//©nΜF ID:20`30
		/****** nΜF(19F) ID:031`049 *****/
		lavender,		thistle,	plum,		violet,				//nΜF ID:31`49
		orchid,			fuchsia,	magenta,	mediumorchid,		//nΜF ID:31`49
		mediumpurple,	amethyst,	blueviolet,	darkviolet,			//nΜF ID:31`49
		darkorchid,		darkmagenta,	purple,		indigo,			//nΜF ID:31`49
		slateblue,		darkslateblue,	mediumslateblue,			//nΜF ID:31`49
		/***** ΞnΜF(23F) ID:050`072 *****/
		greenyellow,	chartreuse,	lawngreen,	lime,				//ΞnΜF ID:50`72
		limegreen, 		palegreen,	lightgreen, mediumspringgreen,	//ΞnΜF ID:50`72
		springgreen, 	mediumseagreen, 		seagreen,			//ΞnΜF ID:50`72
		forestgreen, 	green,		darkgreen, 	yellowgreen,		//ΞnΜF ID:50`72
		olivedrab,		olive,		darkolivegreen,					//ΞnΜF ID:50`72
		mediumaquamarine,			darkseagreen,					//ΞnΜF ID:50`72
		lightseagreen,	darkcyan,	teal,							//ΞnΜF ID:50`72
		/***** ΒnΜF(25F) ID:073`096 *****/
		aqua,			cyan,		lightcyan,	paleturquoise,		//ΒnΜF ID:73`96
		aquamarine,		turquoise,	mediumturquoise,				//ΒnΜF ID:73`96
		darkturquoise,	cadetblue,	steelblue, 	lightsteelblue,		//ΒnΜF ID:73`96
		powderblue,		lightblue,	skyblue, 	lightskyblue,		//ΒnΜF ID:73`96
		deepskyblue,	dodgerblue,	cornflowerblue,					//ΒnΜF ID:73`96
		royalblue,		blue,		mediumblue,						//ΒnΜF ID:73`96
		darkblue,		navy,		midnightblue,					//ΒnΜF ID:73`96
		/***** nΜF(17F) ID:097`113 *****/
		cornsilk,		blanchedalmond,			bisque,				//nΜF ID:97`113
		navajowhite,	wheat,		burlywood, 	tan,				//nΜF ID:97`113
		rosybrown,		sandybrown,	goldenrod, 	darkgoldenrod,		//nΜF ID:97`113
		peru,			chocolate, 	saddlebrown,sienna,				//nΜF ID:97`113
		brown,			maroon, 
		/***** nΜF(17F) ID:114`130 *****/
		white,			snow,		honeydew,	mintcream,			//nΜF ID:114`130
		azure,			aliceblue, 	ghostwhite, whitesmoke,			//nΜF ID:114`130
		seashell, 		beige, 		oldlace, 	floralwhite,		//nΜF ID:114`130
		ivory, 			antiquewhite,			linen,				//nΜF ID:114`130
		lavenderblush, 	mistyrose, 
		/***** DnΜF(10F) ID:131`140*****/
		gainsboro,		lightgrey,	silver,		darkgray,			//DnΜF ID:131`140
		gray,			dimgray, 	lightslategray,					//DnΜF ID:131`140
		slategray, 		darkslategray,			black,				//DnΜF ID:131`140
		color_num	//F141F
	}colorname;

private:
	CColor ConvertHSVtoRGB(double H, double S, double V, bool LinearFlag=1);	//y09zHSV©ηRGBΦΟ·
};


//Ft―
CColor GetColor(int ColorID);