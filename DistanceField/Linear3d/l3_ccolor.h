#pragma once
/*****************************************************************
Fî•ñ‚Ìƒ‰ƒCƒuƒ‰ƒŠ ƒNƒ‰ƒX–¼FColor

¦g—p—á
‡@F•t‚¯
glColor3dv(GetColor(CColor::magenta));
ã‹L‚ğ‘‚­‚¾‚¯‚ÅF‚ªƒ}ƒ[ƒ“ƒ^‚É•Ï‚í‚è‚Ü‚·B
‚Ü‚½A
glColor3dv(GetColor(37));
‚Å‚àƒ}ƒ[ƒ“ƒ^‚ÌF‚Æ‚È‚è‚Ü‚·B

‡AƒJƒ‰[ƒo[‚ğg‚¤ê‡
CColor tmp;
tmp.ColorBar(value,max,min,PalettesCaseNumber,LinearFlag);
ˆø”: value:’l, max,min:ƒJƒ‰[ƒo[‚ÌÅ‘å’lAÅ¬’l
PalettesCaseNumber:0‚È‚çRGB, 
LinearFlag:1‚¾‚ÆüŒ`‚ÅF‚Ì•âŠÔA2‚¾‚ÆOŠpŠÖ”‚É‚æ‚éF‚Ì•âŠÔ
tmp‚Ì’†‚É’l‚ªŠi”[‚³‚ê‚Ü‚·B

F‚Ì–¼Ì‚ÍHTML‚Å—p‚¢‚ç‚ê‚é–¼‘O‚Æ“¯ˆê‚É‚µ‚Ä‚¢‚Ü‚·B
Ú‚µ‚­‚Íwiki“™‚ğŒ©‚ÄŠe©•×‹­‚µ‚Ä‰º‚³‚¢B

F‚É‚Â‚¢‚Ä‚ÍˆÈ‰º‚ğQl‚ÉI
WEBFŒ©–{@Œ´F‘å«“T	http://www.colordic.org/
wikipedia ƒEƒFƒuƒJƒ‰[	http://ja.wikipedia.org/wiki/%E3%82%A6%E3%82%A7%E3%83%96%E3%82%AB%E3%83%A9%E3%83%BC
F‘ŠŠÖ‚É‚Â‚¢‚Ä			http://homepage3.nifty.com/ishidate/vcpp_color/vcpp_color.htm
******************************************************************/

//###################################################//
//	CColor (RGBƒNƒ‰ƒX)								 //
//###################################################//
class CColor
{
public://ƒƒ“ƒo[•Ï”
	double r;	//Ô
	double g;	//—Î
	double b;	//Â

	CColor();									//y01zƒRƒ“ƒXƒgƒ‰ƒNƒ^
	CColor(double R, double G, double B);		//y02zƒRƒ“ƒXƒgƒ‰ƒNƒ^
	void Set(double R, double G, double B);		//y03zİ’u
	void SetGL(double R, double G, double B);	//y04zİ’u
	void Clear();								//y05z•‚ÅƒNƒŠƒA
	void Print();								//y06zo—Í
	void ColorBar(double value, double max, double min, int PalettesCaseNumber=0, bool LinearFlag=1);	//y7zƒJƒ‰[ƒo[—pŠÖ”
	operator double*();							//y08zƒI[ƒo[ƒ[ƒh
	//HTML‚Å‚ÌF–¼Ì
	enum Color_Name{
		/****** ÔŒn‚ÌF(09F) ID:000`008 *****/
		indianred,		lightcoral,	salmon,		darksalmon,			//ÔŒn‚ÌF ID:0`8
		lightsalmon,	crimson,	red,		firebrick,			//ÔŒn‚ÌF ID:0`8
		darkred,													//ÔŒn‚ÌF ID:0`8
		/****** “Œn‚ÌF(06F) ID:009`014 *****/
		pink,			lightpink,	hotpink,	deeppink,			//“Œn‚ÌF ID:9`14
		mediumvioletred,	palevioletred,							//“Œn‚ÌF ID:9`14
		/****** òŒn‚ÌF(06F) ID:015`019 *****/
		coral,		tomato,		orangered,		darkorange,			//òŒn‚ÌF ID:15`19
		orange,														//òŒn‚ÌF ID:15`19
		/****** ‰©Œn‚ÌF(11F) ID:020`030 *****/
		gold,			yellow,		lightyellow,	lemonchiffon,	//‰©Œn‚ÌF ID:20`30
		lightgoldenrodyellow,		papayawhip,		moccasin,		//‰©Œn‚ÌF ID:20`30
		peachpuff,		palegoldenrod,	khaki,		darkkhaki,		//‰©Œn‚ÌF ID:20`30
		/****** ‡Œn‚ÌF(19F) ID:031`049 *****/
		lavender,		thistle,	plum,		violet,				//‡Œn‚ÌF ID:31`49
		orchid,			fuchsia,	magenta,	mediumorchid,		//‡Œn‚ÌF ID:31`49
		mediumpurple,	amethyst,	blueviolet,	darkviolet,			//‡Œn‚ÌF ID:31`49
		darkorchid,		darkmagenta,	purple,		indigo,			//‡Œn‚ÌF ID:31`49
		slateblue,		darkslateblue,	mediumslateblue,			//‡Œn‚ÌF ID:31`49
		/***** —ÎŒn‚ÌF(23F) ID:050`072 *****/
		greenyellow,	chartreuse,	lawngreen,	lime,				//—ÎŒn‚ÌF ID:50`72
		limegreen, 		palegreen,	lightgreen, mediumspringgreen,	//—ÎŒn‚ÌF ID:50`72
		springgreen, 	mediumseagreen, 		seagreen,			//—ÎŒn‚ÌF ID:50`72
		forestgreen, 	green,		darkgreen, 	yellowgreen,		//—ÎŒn‚ÌF ID:50`72
		olivedrab,		olive,		darkolivegreen,					//—ÎŒn‚ÌF ID:50`72
		mediumaquamarine,			darkseagreen,					//—ÎŒn‚ÌF ID:50`72
		lightseagreen,	darkcyan,	teal,							//—ÎŒn‚ÌF ID:50`72
		/***** ÂŒn‚ÌF(25F) ID:073`096 *****/
		aqua,			cyan,		lightcyan,	paleturquoise,		//ÂŒn‚ÌF ID:73`96
		aquamarine,		turquoise,	mediumturquoise,				//ÂŒn‚ÌF ID:73`96
		darkturquoise,	cadetblue,	steelblue, 	lightsteelblue,		//ÂŒn‚ÌF ID:73`96
		powderblue,		lightblue,	skyblue, 	lightskyblue,		//ÂŒn‚ÌF ID:73`96
		deepskyblue,	dodgerblue,	cornflowerblue,					//ÂŒn‚ÌF ID:73`96
		royalblue,		blue,		mediumblue,						//ÂŒn‚ÌF ID:73`96
		darkblue,		navy,		midnightblue,					//ÂŒn‚ÌF ID:73`96
		/***** ’ƒŒn‚ÌF(17F) ID:097`113 *****/
		cornsilk,		blanchedalmond,			bisque,				//’ƒŒn‚ÌF ID:97`113
		navajowhite,	wheat,		burlywood, 	tan,				//’ƒŒn‚ÌF ID:97`113
		rosybrown,		sandybrown,	goldenrod, 	darkgoldenrod,		//’ƒŒn‚ÌF ID:97`113
		peru,			chocolate, 	saddlebrown,sienna,				//’ƒŒn‚ÌF ID:97`113
		brown,			maroon, 
		/***** ”’Œn‚ÌF(17F) ID:114`130 *****/
		white,			snow,		honeydew,	mintcream,			//”’Œn‚ÌF ID:114`130
		azure,			aliceblue, 	ghostwhite, whitesmoke,			//”’Œn‚ÌF ID:114`130
		seashell, 		beige, 		oldlace, 	floralwhite,		//”’Œn‚ÌF ID:114`130
		ivory, 			antiquewhite,			linen,				//”’Œn‚ÌF ID:114`130
		lavenderblush, 	mistyrose, 
		/***** ŠDŒn‚ÌF(10F) ID:131`140*****/
		gainsboro,		lightgrey,	silver,		darkgray,			//ŠDŒn‚ÌF ID:131`140
		gray,			dimgray, 	lightslategray,					//ŠDŒn‚ÌF ID:131`140
		slategray, 		darkslategray,			black,				//ŠDŒn‚ÌF ID:131`140
		color_num	//F‘”141F
	}colorname;

private:
	CColor ConvertHSVtoRGB(double H, double S, double V, bool LinearFlag=1);	//y09zHSV‚©‚çRGB‚Ö•ÏŠ·
};


//F•t‚¯
CColor GetColor(int ColorID);