#define _USE_MATH_DEFINES	//â~é¸ó¶M_PIÇégÇ§ÇΩÇﬂÇ…ïKóv
#include "l3.h"
#include <cmath>

//Åy01ÅzÉRÉìÉXÉgÉâÉNÉ^
CColor::CColor(){
	r = g = b = 0.0;
}

//Åy02ÅzÉRÉìÉXÉgÉâÉNÉ^
CColor::CColor(double R, double G, double B){
	r = R; g = G; b = B;
}

//Åy03Åzê›íu
void CColor::Set(double R, double G, double B){
	r = R; g = G; b = B;
}

//Åy04Åzê›íu
void CColor::SetGL(double R, double G, double B){
	r = R/255.0; g = G/255.0; b = B/255.0;
}

//Åy05ÅzçïÇ≈ÉNÉäÉA
void CColor::Clear(){
	r = g = b = 0.0;
}

//Åy06ÅzèoóÕ
void CColor::Print(){
	std::cout<<"("<<r<<","<<g<<","<<b<<");"<<std::endl;
}

//Åy7ÅzÉJÉâÅ[ÉoÅ[ópä÷êî
void CColor::ColorBar(double value, double max, double min, int PalettesCaseNumber, bool LinearFlag){
	CColor rgb;
	if(value > max)	value = max;
	if(value < min) value = min;

	double H, S, V;
	double startH,endH;

	S = 1.0;	//ç ìx 1.0Ç≈å≈íË
	V = 1.0;	//ñæìx 1.0Ç≈å≈íË

	switch(PalettesCaseNumber){
	case 0:	//B->G->R
		startH = 240.0;		endH = 0.0;
		break;
	case 1:	//G->R
		startH = 120.0;		endH = 0.0;
		break;
	case 2://B->G
		startH = 240.0;		endH = 120.0;
		break;
	default://R->M->B->C->G->Y->R
		startH = 359.9999;	endH = 0.0;
		break;
	}

	H = startH - ( startH - endH )*(value -min)/(max - min);
	rgb = ConvertHSVtoRGB(H,S,V,LinearFlag);
	r = rgb.r;
	g = rgb.g;
	b = rgb.b;
}

//Åy8ÅzÉIÅ[ÉoÅ[ÉçÅ[Éh
CColor::operator double*()
{
	double *c = new double[3];
	c[0] = r;
	c[1] = g;
	c[2] = b;
	return (c);
}

//Åy09ÅzHSVÇ©ÇÁRGBÇ÷ïœä∑
CColor CColor::ConvertHSVtoRGB(double H, double S, double V,bool LinearFlag){
	CColor rgb;
	if(S==0.0)	//Gray
	{
		rgb.r = rgb.g = rgb.b= V;
	}
	else{
		int Hi = (int)fmod(floor(H/60.0),6.0);
		double f = H/60.0 - floor(H/60);
		double p = V * (1-S);
		double q,t;
		if(LinearFlag){
			q = V * (1-f*S);
			t = V * (1-(1-f)*S);
		}else{
			q = V * (-cos((1-f*S)*M_PI)+1)/2.0;
			t = V * (1+cos((1-f)*S*M_PI))/2.0;
		}

		switch(Hi)
		{
		case 0:
			rgb.r = V; rgb.g = t; rgb.b = p;
			break;
		case 1:
			rgb.r = q; rgb.g = V; rgb.b = p;
			break;
		case 2:
			rgb.r = p; rgb.g = V; rgb.b = t;
			break;
		case 3:
			rgb.r = p; rgb.g = q; rgb.b = V;
			break;
		case 4:
			rgb.r = t; rgb.g = p; rgb.b = V;
			break;
		case 5:
			rgb.r = V; rgb.g = p; rgb.b = q;
			break;
		default:
			rgb.r = 0; rgb.g = 0; rgb.b = 0;
			break;
		}
	}
	return(rgb);
}

// err
CColor GetColor(int ColorID)
{
	CColor tmp;
	switch (ColorID){
		/***** Red *****/
	case 0://IndianRed
		tmp.SetGL(205,92,92);	 break;
	case 1://LightCoral
		tmp.SetGL(240,128,128);	 break;
	case 2://Salmon
		tmp.SetGL(250,128,114);	 break;
	case 3://DarkSalmon
		tmp.SetGL(233,150,122);	 break;
	case 4://LightSalmon
		tmp.SetGL(255,160,122);	 break;
	case 5://Crimson
		tmp.SetGL(220,20,60);	 break;
	case 6://Red
		tmp.SetGL(255,0,0);		 break;
	case 7://FireBrick
		tmp.SetGL(178,34,34);	 break;
	case 8://DarkRed
		tmp.SetGL(139,0,0);	 	 break;
		/****** Pink *****/
	case 9://Pink
		tmp.SetGL(255,192,203);	 break;
	case 10://LightPink
		tmp.SetGL(255,182,193);	 break;
	case 11://HotPink
		tmp.SetGL(255,105,180);	 break;
	case 12://DeepPink
		tmp.SetGL(255,20,147); 	 break;
	case 13://MediumVioletRed
		tmp.SetGL(199,21,133);	 break;
	case 14://PaleVioletRed
		tmp.SetGL(219,112,147);	 break;
		/***** Orange *****/
	case 15://Coral
		tmp.SetGL(255,127,80);	 break;
	case 16://Tomato
		tmp.SetGL(255,99,71);	 break;
	case 17://OrangeRed
		tmp.SetGL(255,69,0);	 break;
	case 18://DarkOrange
		tmp.SetGL(255,140,0);	 break;
	case 19://Orange
		tmp.SetGL(255,165,0);	 break;
		/***** Yellow *****/
	case 20://Gold
		tmp.SetGL(255,215,0);	 break;
	case 21://Yellow
		tmp.SetGL(255,255,0);	 break;
	case 22://LightYellow
		tmp.SetGL(255,255,224);	 break;
	case 23://LemonChiffon
		tmp.SetGL(255,250,205);	 break;
	case 24://LightGoldenrodYellow
		tmp.SetGL(250,250,210);	 break;
	case 25://PapayaWhip
		tmp.SetGL(255,239,213);	 break;
	case 26://Moccasin
		tmp.SetGL(255,228,181);	 break;
	case 27://PeachPuff
		tmp.SetGL(255,218,185);	 break;
	case 28://PaleGoldenrod
		tmp.SetGL(238,232,170);	 break;
	case 29://Khaki
		tmp.SetGL(240,230,140);	 break;
	case 30://DarkKhaki
		tmp.SetGL(189,183,107);	 break;
		/***** Purple *****/
	case 31://Lavender
		tmp.SetGL(230,230,250);	 break;
	case 32://Thistle
		tmp.SetGL(216,191,216);	 break;
	case 33://Plum
		tmp.SetGL(221,160,221);	 break;
	case 34://Violet
		tmp.SetGL(238,130,238);	 break;
	case 35://Orchid
		tmp.SetGL(218,112,214);	 break;
	case 36://Fuchsia
		tmp.SetGL(255,0,255);	 break;
	case 37://Magenta
		tmp.SetGL(255,0,255);	 break;
	case 38://MediumOrchid
		tmp.SetGL(186,85,211);	 break;
	case 39://MediumPurple
		tmp.SetGL(147,112,219);	 break;
	case 40://Amethyst
		tmp.SetGL(153,102,204);	 break;
	case 41://BlueViolet
		tmp.SetGL(138,43,226);	 break;
	case 42://DarkViolet
		tmp.SetGL(148,0,211);	 break;
	case 43://DarkOrchid
		tmp.SetGL(153,50,204);	 break;
	case 44://DarkMagenta
		tmp.SetGL(139,0,139);	 break;
	case 45://Purple
		tmp.SetGL(128,0,128);	 break;
	case 46://Indigo
		tmp.SetGL(75,0,130);	 break;
	case 47://SlateBlue
		tmp.SetGL(106,90,205);	 break;
	case 48://DarkSlateBlue
		tmp.SetGL(72,61,139);	 break;
	case 49://MediumSlateBlue
		tmp.SetGL(123,104,238);	 break;
		/***** Green *****/
	case 50://GreenYellow
		tmp.SetGL(173,255,47);	 break;
	case 51://Chartreuse
		tmp.SetGL(127,255,0);	 break;
	case 52://LawnGreen
		tmp.SetGL(124,252,0);	 break;
	case 53://Lime
		tmp.SetGL(0,255,0);		 break;
	case 54://LimeGreen
		tmp.SetGL(50,205,50);	 break;
	case 55://PaleGreen
		tmp.SetGL(152,251,152);	 break;
	case 56://LightGreen
		tmp.SetGL(144,238,144);	 break;
	case 57://MediumSpringGreen
		tmp.SetGL(0,250,154);	 break;
	case 58://SpringGreen
		tmp.SetGL(0,255,127);	 break;
	case 59://MediumSeaGreen
		tmp.SetGL(60,179,113);	 break;
	case 60://SeaGreen
		tmp.SetGL(46,139,87);	 break;
	case 61://ForestGreen
		tmp.SetGL(34,139,34);	 break;
	case 62://Green
		tmp.SetGL(0,128,0);		 break;
	case 63://DarkGreen
		tmp.SetGL(0,100,0);		 break;
	case 64://YellowGreen
		tmp.SetGL(154,205,50);	 break;
	case 65://OliveDrab
		tmp.SetGL(107,142,35);	 break;
	case 66://Olive
		tmp.SetGL(128,128,0);	 break;
	case 67://DarkOliveGreen
		tmp.SetGL(85,107,47);	 break;
	case 68://MediumAquamarine
		tmp.SetGL(102,205,170);	 break;
	case 69://DarkSeaGreen
		tmp.SetGL(143,188,143);	 break;
	case 70://LightSeaGreen
		tmp.SetGL(32,178,170);	 break;
	case 71://DarkCyan
		tmp.SetGL(0,139,139);	 break;
	case 72://Teal
		tmp.SetGL(0,128,128);	 break;
		/***** Blue *****/
	case 73://Aqua
		tmp.SetGL(0,255,255);	 break;
	case 74://Cyan
		tmp.SetGL(0,255,255);	 break;
	case 75://LightCyan
		tmp.SetGL(224,255,255);	 break;
	case 76://PaleTurquoise
		tmp.SetGL(175,238,238);	 break;
	case 77://Aquamarine
		tmp.SetGL(127,255,212);	 break;
	case 78://Turquoise
		tmp.SetGL(64,224,208);	 break;
	case 79://MediumTurquoise
		tmp.SetGL(72,209,204);	 break;
	case 80://DarkTurquoise
		tmp.SetGL(0,206,209);	 break;
	case 81://CadetBlue
		tmp.SetGL(95,158,160);	 break;
	case 82://SteelBlue
		tmp.SetGL(70,130,180);	 break;
	case 83://LightSteelBlue
		tmp.SetGL(176,196,222);	 break;
	case 84://PowderBlue
		tmp.SetGL(176,224,230);	 break;
	case 85://LightBlue
		tmp.SetGL(173,216,230);	 break;
	case 86://SkyBlue
		tmp.SetGL(135,206,235);	 break;
	case 87://LightSkyBlue
		tmp.SetGL(135,206,250);	 break;
	case 88://DeepSkyBlue
		tmp.SetGL(0,191,255);	 break;
	case 89://DodgerBlue
		tmp.SetGL(30,144,255);	 break;
	case 90://CornflowerBlue
		tmp.SetGL(100,149,237);	 break;
	case 91://RoyalBlue
		tmp.SetGL(65,105,225);	 break;
	case 92://Blue
		tmp.SetGL(0,0,255);		 break;
	case 93://MediumBlue
		tmp.SetGL(0,0,205);		 break;
	case 94://DarkBlue
		tmp.SetGL(0,0,139);		 break;
	case 95://Navy 
		tmp.SetGL(0,0,128);		 break;
	case 96://MidnightBlue 
		tmp.SetGL(25,25,112);	 break;
		/***** Brown *****/
	case 97://Cornsilk
		tmp.SetGL(255,248,220);	 break;
	case 98://BlanchedAlmond
		tmp.SetGL(255,235,205);	 break;
	case 99://Bisque
		tmp.SetGL(255,228,196);	 break;
	case 100://NavajoWhite
		tmp.SetGL(255,222,173);	 break;
	case 101://Wheat
		tmp.SetGL(245,222,179);	 break;
	case 102://BurlyWood
		tmp.SetGL(222,184,135);	 break;
	case 103://Tan
		tmp.SetGL(210,180,140);	 break;
	case 104://RosyBrown
		tmp.SetGL(188,143,143);	 break;
	case 105://SandyBrown
		tmp.SetGL(244,164,96);	 break;
	case 106://Goldenrod
		tmp.SetGL(218,165,32);	 break;
	case 107://DarkGoldenrod
		tmp.SetGL(184,134,11);	 break;
	case 108://Peru
		tmp.SetGL(205,133,63);	 break;
	case 109://Chocolate
		tmp.SetGL(210,105,30);	 break;
	case 110://SaddleBrown
		tmp.SetGL(139,69,19);	 break;
	case 111://Sienna
		tmp.SetGL(160,82,45);	 break;
	case 112://Brown
		tmp.SetGL(165,42,42);	 break;
	case 113://Maroon
		tmp.SetGL(128,0,0);	 	 break;
		/***** White *****/
	case 114://White
		tmp.SetGL(255,255,255);	 break;
	case 115://Snow
		tmp.SetGL(255,250,250);	 break;
	case 116://Honeydew
		tmp.SetGL(240,255,240);	 break;
	case 117://MintCream
		tmp.SetGL(245,255,250);	 break;
	case 118://Azure
		tmp.SetGL(240,255,255);	 break;
	case 119://AliceBlue
		tmp.SetGL(240,248,255);	 break;
	case 120://GhostWhite
		tmp.SetGL(248,248,255);	 break;
	case 121://WhiteSmoke
		tmp.SetGL(245,245,245);	 break;
	case 122://Seashell
		tmp.SetGL(255,245,238);	 break;
	case 123://Beige
		tmp.SetGL(245,245,220);	 break;
	case 124://OldLace
		tmp.SetGL(253,245,230);	 break;
	case 125://FloralWhite
		tmp.SetGL(255,250,240);	 break;
	case 126://Ivory
		tmp.SetGL(255,255,240);	 break;
	case 127://AntiqueWhite
		tmp.SetGL(250,235,215);	 break;
	case 128://Linen
		tmp.SetGL(250,240,230);	 break;
	case 129://LavenderBlush
		tmp.SetGL(255,240,245);	 break;
	case 130://MistyRose
		tmp.SetGL(255,228,225);	 break;
		/***** Gray *****/
	case 131://Gainsboro
		tmp.SetGL(220,220,220);	 break;
	case 132://LightGrey
		tmp.SetGL(211,211,211);	 break;
	case 133://Silver
		tmp.SetGL(192,192,192);	 break;
	case 134://DarkGray
		tmp.SetGL(169,169,169);	 break;
	case 135://Gray
		tmp.SetGL(128,128,128);	 break;
	case 136://DimGray
		tmp.SetGL(105,105,105);	 break;
	case 137://LightSlateGray
		tmp.SetGL(119,136,153);	 break;
	case 138://SlateGray
		tmp.SetGL(112,128,144);	 break;
	case 139://DarkSlateGray
		tmp.SetGL(47,79,79);	 break;
	case 140://Black
		tmp.SetGL(0,0,0);		 break;
	default:
		break;
	}
	return(tmp);
}	