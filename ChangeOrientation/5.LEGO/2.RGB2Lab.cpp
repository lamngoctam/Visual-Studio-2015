#include "../stdafx.h"
#include "../Voxel.h"
#include "../Lego.h"		//LEGO�u���b�N��g�ݗ��Ă邽�߂̃N���X

//A����(���d��)�AC����(�k������)
//D65�ŎZ�o���ꂽXYZ��LAB�͈ȉ��̃T�C�g�Ƃ̌v�Z�͍�����D50�͍���Ȃ��I
//�Q�l�T�C�g�Fhttp://www.easyrgb.com/index.php?X=CALC#Result(���܂��܂ȕ\�F�n���m�̕ϊ����\)

//http://w3.kcua.ac.jp/~fujiwara/infosci/colorspace/colorspace2.html(���{��T�C�g)
//http://php-archive.net/php/rgb2lab/(����͈Ⴄ���A�Q�l�ɂȂ�\�[�X�R�[�h������)

CColor RGB_to_sRGB(CColor& rgb);
CColor sRGB_to_XYZ(CColor& rgb);
CColor XYZ_to_Lab(CColor& xyz);
double XYZLab_func(double tt);
double DeltaE(CColor& aa, CColor& bb);
CColor RGB_to_Lab(CColor& rgb);

//RGB�\�F�n����CIEL*a*b*�\�F�n�֕ϊ�
CColor RGB_to_Lab(CColor& rgb)
{
	//�Q�l�t�q�k
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
//RGB�\�F�n����CIEL*a*b*�\�F�n�֕ϊ�
CColor RGB_to_Lab2(CColor& rgb)
{
	CColor xyz = sRGB_to_XYZ(rgb);
	CColor lab = XYZ_to_Lab(xyz);
	return lab;
}
//sRGB / Adobe RGB �� RGB �l�́C�X�N���[����Ŏ��R�Ȗ��邳�Ɍ�����悤�ɖ��邳�̕␳���Ȃ���Ă���
CColor RGB_to_sRGB(CColor& rgb)
{
	CColor temp;
	//cout<<"rgb"<<rgb.r<<" "<<rgb.g<<" "<<rgb.b<<endl;
	double gamma(2.4);
	if(rgb.r > 0.040450)
		temp.r = pow((rgb.r + 0.055)/1.055, gamma);
	else
		temp.r = rgb.r/12.92;
	if(rgb.g > 0.040450)
		temp.g = pow((rgb.g + 0.055)/1.055, gamma);
	else
		temp.g = rgb.g/12.92;
	if(rgb.b > 0.040450)
		temp.b = pow((rgb.b + 0.055)/1.055, gamma);
	else
		temp.b = rgb.b/12.92;
	//cout<<"srgb"<<temp.r<<" "<<temp.g<<" "<<temp.b<<endl;

	return temp;
}

//sRGB�\�F�n��XYZ�\�F�n�֕ϊ�
CColor sRGB_to_XYZ(CColor& rgb)
{
	CColor xyz;
	//observer �� 2��(1931)
	//sRGB illuminant �� D50
	//xyz.r = rgb.r * 0.4360747 + rgb.g * 0.3850649 + rgb.b * 0.1430804;
	//xyz.g = rgb.r * 0.2225045 + rgb.g * 0.7168786 + rgb.b * 0.0606169;
	//xyz.b = rgb.r * 0.0139322 + rgb.g * 0.0971045 + rgb.b * 0.7141733;
	
	rgb.r = 100.0*rgb.r;
	rgb.g = 100.0*rgb.g;
	rgb.b = 100.0*rgb.b;

	// //sRGB illuminant �� D65
	xyz.r = rgb.r * 0.4124 + rgb.g * 0.3576 + rgb.b *  0.1805;
	xyz.g = rgb.r * 0.2126 + rgb.g * 0.7152 + rgb.b *  0.0722;
	xyz.b = rgb.r * 0.0193 + rgb.g * 0.1192 + rgb.b *  0.9505;

	//xyz.r = rgb.r * 0.4124564 + rgb.g * 0.3575761 + rgb.b *  0.1804375;
	//xyz.g = rgb.r * 0.2126729 + rgb.g * 0.7151522 + rgb.b *  0.0721750;
	//xyz.b = rgb.r * 0.0193339 + rgb.g * 0.1191920 + rgb.b *  0.9503041;

	//OpenCV�̒��Ŏg�p����Ă���l
	//xyz.r = rgb.r * 0.412453 + rgb.g * 0.357580 + rgb.b *  0.180423;
	//xyz.g = rgb.r * 0.212671 + rgb.g * 0.715160 + rgb.b *  0.072169;
	//xyz.b = rgb.r * 0.019334 + rgb.g * 0.119193 + rgb.b *  0.950227;
	
	//cout<<"XYZ"<<xyz.r<<" "<<xyz.g<<" "<<xyz.b<<endl;
	return xyz;
}

//XYZ�\�F�n��CIEL*a*b*�\�F�n�֕ϊ�
CColor XYZ_to_Lab(CColor& xyz)
{
	//observer �� 2��(1931)	illuminant �� D50
	//double Xn(0.9642);
	//double Yn(1.0);
	//double Zn(0.8249);
	//double Xn(0.96422);
	//double Yn(1.0000);
	//double Zn(0.82521);

	//observer �� 2��(1931)	illuminant �� D65
	//double Xn(0.95046);
	//double Yn(1.0000);
	//double Zn(1.08906);
	double Xn(95.047);
	double Yn(100.000);
	double Zn(108.883);

	////OpenCV�Ŏg�p���Ă���l	
	//double Xn(0.950456);
	//double Yn(1.0000);
	//double Zn(1.088754);

	double Ft_x = XYZLab_func(xyz.r/Xn);
	double Ft_y = XYZLab_func(xyz.g/Yn);
	double Ft_z = XYZLab_func(xyz.b/Zn);

	CColor lab;
	lab.r = 116.0 * Ft_y - 16.0;
	lab.g = 500.0 * (Ft_x - Ft_y);
	lab.b = 200.0 * (Ft_y - Ft_z);

	return lab;
}

//XYZ�\�F�n��CIEL*a*b*�\�F�n�֕ϊ�����Ƃ��Ɏg�p����֐�
double XYZLab_func(double tt)
{
	//double threshold = pow(6.0/29.0, 3);
	double threshold = 0.008856;

	if( tt > threshold )
		return pow(tt, 1.0/3.0);
	else
		return (7.787 * tt  + 4.0/29.0);

	//return (pow((29.0/6.0), 2) * tt /3.0 + 4.0/29.0);
}

//���́F�Q�̐F��(Lab)�@�o�́F�F����Ԃ�
double DeltaE(CColor& aa, CColor& bb)
{
	double color_difference = sqrt((aa.r - bb.r)*(aa.r - bb.r) + (aa.g - bb.g)*(aa.g - bb.g) + (aa.b - bb.b)*(aa.b - bb.b));
	return color_difference;
}

//���́F�Q�̐F��(ab)�@�o�́F�F����Ԃ�(���邳���l�����Ȃ�)
double DeltaE_noL(CColor& aa, CColor& bb)
{
	double color_difference = sqrt((aa.g - bb.g)*(aa.g - bb.g) + (aa.b - bb.b)*(aa.b - bb.b));
	return color_difference;
}
