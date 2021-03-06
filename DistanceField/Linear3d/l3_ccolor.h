#pragma once
/*****************************************************************
色情報のライブラリ クラス名：Color

※使用例
�@色付け
glColor3dv(GetColor(CColor::magenta));
上記を書くだけで色がマゼンタに変わります。
また、
glColor3dv(GetColor(37));
でもマゼンタの色となります。

�Aカラーバーを使う場合
CColor tmp;
tmp.ColorBar(value,max,min,PalettesCaseNumber,LinearFlag);
引数: value:値, max,min:カラーバーの最大値、最小値
PalettesCaseNumber:0ならRGB, 
LinearFlag:1だと線形で色の補間、2だと三角関数による色の補間
tmpの中に値が格納されます。

色の名称はHTMLで用いられる名前と同一にしています。
詳しくはwiki等を見て各自勉強して下さい。

色については以下を参考に！
WEB色見本　原色大辞典	http://www.colordic.org/
wikipedia ウェブカラー	http://ja.wikipedia.org/wiki/%E3%82%A6%E3%82%A7%E3%83%96%E3%82%AB%E3%83%A9%E3%83%BC
色相関について			http://homepage3.nifty.com/ishidate/vcpp_color/vcpp_color.htm
******************************************************************/

//###################################################//
//	CColor (RGBクラス)								 //
//###################################################//
class CColor
{
public://メンバー変数
	double r;	//赤
	double g;	//緑
	double b;	//青

	CColor();									//【01】コンストラクタ
	CColor(double R, double G, double B);		//【02】コンストラクタ
	void Set(double R, double G, double B);		//【03】設置
	void SetGL(double R, double G, double B);	//【04】設置
	void Clear();								//【05】黒でクリア
	void Print();								//【06】出力
	void ColorBar(double value, double max, double min, int PalettesCaseNumber=0, bool LinearFlag=1);	//【7】カラーバー用関数
	operator double*();							//【08】オーバーロード
	//HTMLでの色名称
	enum Color_Name{
		/****** 赤系の色(09色) ID:000〜008 *****/
		indianred,		lightcoral,	salmon,		darksalmon,			//赤系の色 ID:0〜8
		lightsalmon,	crimson,	red,		firebrick,			//赤系の色 ID:0〜8
		darkred,													//赤系の色 ID:0〜8
		/****** 桃系の色(06色) ID:009〜014 *****/
		pink,			lightpink,	hotpink,	deeppink,			//桃系の色 ID:9〜14
		mediumvioletred,	palevioletred,							//桃系の色 ID:9〜14
		/****** 橙系の色(06色) ID:015〜019 *****/
		coral,		tomato,		orangered,		darkorange,			//橙系の色 ID:15〜19
		orange,														//橙系の色 ID:15〜19
		/****** 黄系の色(11色) ID:020〜030 *****/
		gold,			yellow,		lightyellow,	lemonchiffon,	//黄系の色 ID:20〜30
		lightgoldenrodyellow,		papayawhip,		moccasin,		//黄系の色 ID:20〜30
		peachpuff,		palegoldenrod,	khaki,		darkkhaki,		//黄系の色 ID:20〜30
		/****** 紫系の色(19色) ID:031〜049 *****/
		lavender,		thistle,	plum,		violet,				//紫系の色 ID:31〜49
		orchid,			fuchsia,	magenta,	mediumorchid,		//紫系の色 ID:31〜49
		mediumpurple,	amethyst,	blueviolet,	darkviolet,			//紫系の色 ID:31〜49
		darkorchid,		darkmagenta,	purple,		indigo,			//紫系の色 ID:31〜49
		slateblue,		darkslateblue,	mediumslateblue,			//紫系の色 ID:31〜49
		/***** 緑系の色(23色) ID:050〜072 *****/
		greenyellow,	chartreuse,	lawngreen,	lime,				//緑系の色 ID:50〜72
		limegreen, 		palegreen,	lightgreen, mediumspringgreen,	//緑系の色 ID:50〜72
		springgreen, 	mediumseagreen, 		seagreen,			//緑系の色 ID:50〜72
		forestgreen, 	green,		darkgreen, 	yellowgreen,		//緑系の色 ID:50〜72
		olivedrab,		olive,		darkolivegreen,					//緑系の色 ID:50〜72
		mediumaquamarine,			darkseagreen,					//緑系の色 ID:50〜72
		lightseagreen,	darkcyan,	teal,							//緑系の色 ID:50〜72
		/***** 青系の色(25色) ID:073〜096 *****/
		aqua,			cyan,		lightcyan,	paleturquoise,		//青系の色 ID:73〜96
		aquamarine,		turquoise,	mediumturquoise,				//青系の色 ID:73〜96
		darkturquoise,	cadetblue,	steelblue, 	lightsteelblue,		//青系の色 ID:73〜96
		powderblue,		lightblue,	skyblue, 	lightskyblue,		//青系の色 ID:73〜96
		deepskyblue,	dodgerblue,	cornflowerblue,					//青系の色 ID:73〜96
		royalblue,		blue,		mediumblue,						//青系の色 ID:73〜96
		darkblue,		navy,		midnightblue,					//青系の色 ID:73〜96
		/***** 茶系の色(17色) ID:097〜113 *****/
		cornsilk,		blanchedalmond,			bisque,				//茶系の色 ID:97〜113
		navajowhite,	wheat,		burlywood, 	tan,				//茶系の色 ID:97〜113
		rosybrown,		sandybrown,	goldenrod, 	darkgoldenrod,		//茶系の色 ID:97〜113
		peru,			chocolate, 	saddlebrown,sienna,				//茶系の色 ID:97〜113
		brown,			maroon, 
		/***** 白系の色(17色) ID:114〜130 *****/
		white,			snow,		honeydew,	mintcream,			//白系の色 ID:114〜130
		azure,			aliceblue, 	ghostwhite, whitesmoke,			//白系の色 ID:114〜130
		seashell, 		beige, 		oldlace, 	floralwhite,		//白系の色 ID:114〜130
		ivory, 			antiquewhite,			linen,				//白系の色 ID:114〜130
		lavenderblush, 	mistyrose, 
		/***** 灰系の色(10色) ID:131〜140*****/
		gainsboro,		lightgrey,	silver,		darkgray,			//灰系の色 ID:131〜140
		gray,			dimgray, 	lightslategray,					//灰系の色 ID:131〜140
		slategray, 		darkslategray,			black,				//灰系の色 ID:131〜140
		color_num	//色総数141色
	}colorname;

private:
	CColor ConvertHSVtoRGB(double H, double S, double V, bool LinearFlag=1);	//【09】HSVからRGBへ変換
};


//色付け
CColor GetColor(int ColorID);