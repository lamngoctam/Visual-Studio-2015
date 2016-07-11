#include "../stdafx.h"
#include "../Voxel.h"
#include "../Lego.h"		//LEGO


//D65ÇXYZÇ∆LABÇD50
//http://www.easyrgb.com/index.php?X=CALC#Result

//http://w3.kcua.ac.jp/~fujiwara/infosci/colorspace/colorspace2.html(ì˙ñ{åÍÉTÉCÉg)
//http://php-archive.net/php/rgb2lab/(åæåÍÇÕà·Ç§Ç™ÅAéQçlÇ…Ç»ÇÈÉ\Å[ÉXÉRÅ[ÉhÇ™Ç†ÇÈ)

CColor RGB_to_sRGB(CColor& rgb);
CColor sRGB_to_XYZ(CColor& rgb);
CColor XYZ_to_Lab(CColor& xyz);
double XYZLab_func(double tt);
double DeltaE(CColor& aa, CColor& bb);
CColor RGB_to_Lab(CColor& rgb);

//RGBï\êFånÇ©ÇÁCIEL*a*b*ï\êFånÇ÷ïœä∑
CColor RGB_to_Lab(CColor& rgb)
{
	//lÇtÇqÇk
	//http://www.easyrgb.com/index.php?X=MATH&H=02#text2
	//cout<<"RGB:"<<rgb.r<< " " << rgb.g << " "<<rgb.b<<endl;
	CColor srgb = RGB_to_sRGB(rgb);
	//cout<<"sRGB:"<<srgb.r<< " " << srgb.g << " "<<srgb.b<<endl;
	CColor xyz = sRGB_to_XYZ(srgb);
	//cout<<"XYZ:"<<xyz.r<< " " << xyz.g << " "<<xyz.b<<endl;
	CColor lab = XYZ_to_Lab(xyz);
	//cout<<"LAB:"<<lab.r<< " " << lab.g << " "<<lab.b<<endl;
	return lab;
}
//RGBï\êFånÇ©ÇÁCIEL*a*b*ï\êFånÇ÷ïœä∑
CColor RGB_to_Lab2(CColor& rgb)
{
	CColor xyz = sRGB_to_XYZ(rgb);
	CColor lab = XYZ_to_Lab(xyz);
	return lab;
}
//sRGB / Adobe RGB Ç RGB 
CColor RGB_to_sRGB(CColor& rgb)
{
	CColor temp;
	//cout<<"rgb"<<rgb.r<<" "<<rgb.g<<" "<<rgb.b<<endl;
	double gamma(2.4);
	if (rgb.r > 0.040450)
		temp.r = pow((rgb.r + 0.055) / 1.055, gamma);
	else
		temp.r = rgb.r / 12.92;
	if (rgb.g > 0.040450)
		temp.g = pow((rgb.g + 0.055) / 1.055, gamma);
	else
		temp.g = rgb.g / 12.92;
	if (rgb.b > 0.040450)
		temp.b = pow((rgb.b + 0.055) / 1.055, gamma);
	else
		temp.b = rgb.b / 12.92;
	//cout<<"srgb"<<temp.r<<" "<<temp.g<<" "<<temp.b<<endl;

	return temp;
}

//sRGBïÇXYZ

CColor sRGB_to_XYZ(CColor& rgb)
{
	CColor xyz;
	//observer Å® 2Åã(1931)
	//sRGB illuminant Å® D50
	//xyz.r = rgb.r * 0.4360747 + rgb.g * 0.3850649 + rgb.b * 0.1430804;
	//xyz.g = rgb.r * 0.2225045 + rgb.g * 0.7168786 + rgb.b * 0.0606169;
	//xyz.b = rgb.r * 0.0139322 + rgb.g * 0.0971045 + rgb.b * 0.7141733;

	rgb.r = 100.0*rgb.r;
	rgb.g = 100.0*rgb.g;
	rgb.b = 100.0*rgb.b;

	// //sRGB illuminant Å® D65
	xyz.r = rgb.r * 0.4124 + rgb.g * 0.3576 + rgb.b *  0.1805;
	xyz.g = rgb.r * 0.2126 + rgb.g * 0.7152 + rgb.b *  0.0722;
	xyz.b = rgb.r * 0.0193 + rgb.g * 0.1192 + rgb.b *  0.9505;

	//xyz.r = rgb.r * 0.4124564 + rgb.g * 0.3575761 + rgb.b *  0.1804375;
	//xyz.g = rgb.r * 0.2126729 + rgb.g * 0.7151522 + rgb.b *  0.0721750;
	//xyz.b = rgb.r * 0.0193339 + rgb.g * 0.1191920 + rgb.b *  0.9503041;

	//OpenCVÇÃíÜÇ≈égópÇ≥ÇÍÇƒÇ¢ÇÈíl
	//xyz.r = rgb.r * 0.412453 + rgb.g * 0.357580 + rgb.b *  0.180423;
	//xyz.g = rgb.r * 0.212671 + rgb.g * 0.715160 + rgb.b *  0.072169;
	//xyz.b = rgb.r * 0.019334 + rgb.g * 0.119193 + rgb.b *  0.950227;

	//cout<<"XYZ"<<xyz.r<<" "<<xyz.g<<" "<<xyz.b<<endl;
	return xyz;
}

//XYZïCIEL*a*b*ï
CColor XYZ_to_Lab(CColor& xyz)
{
	//observer Å® 2Åã(1931)	illuminant Å® D50
	//double Xn(0.9642);
	//double Yn(1.0);
	//double Zn(0.8249);
	//double Xn(0.96422);
	//double Yn(1.0000);
	//double Zn(0.82521);

	//observer Å® 2Åã(1931)	illuminant Å® D65
	//double Xn(0.95046);
	//double Yn(1.0000);
	//double Zn(1.08906);
	
	//double Xn(95.047);
	//double Yn(100.000);
	//double Zn(108.883);

	////OpenCV
	double Xn(98.072);
	double Yn(100.000);
	double Zn(118.225);

	double Ft_x = XYZLab_func(xyz.r / Xn);
	double Ft_y = XYZLab_func(xyz.g / Yn);
	double Ft_z = XYZLab_func(xyz.b / Zn);

	CColor lab;
	lab.r = 116.0 * Ft_y - 16.0;   //L
	lab.g = 500.0 * (Ft_x - Ft_y); //a
	lab.b = 200.0 * (Ft_y - Ft_z);  //b

	return lab;
}

//XYZï\êCIEL*a*b*ï\ê
double XYZLab_func(double tt)
{
	//double threshold = pow(6.0/29.0, 3);
	double threshold = 0.008856;

	if (tt > threshold)
		return pow(tt, 1.0 / 3.0);
	else
		return (7.787 * tt + 4.0 / 29.0);

	//return (pow((29.0/6.0), 2) * tt /3.0 + 4.0/29.0);
}


double DeltaE(CColor& aa, CColor& bb)
{
	double color_difference = sqrt((aa.r - bb.r)*(aa.r - bb.r) + (aa.g - bb.g)*(aa.g - bb.g) + (aa.b - bb.b)*(aa.b - bb.b));
	return color_difference;
}


double DeltaE_noL(CColor& aa, CColor& bb)
{
	double color_difference = sqrt((aa.g - bb.g)*(aa.g - bb.g) + (aa.b - bb.b)*(aa.b - bb.b));
	return color_difference;
}
