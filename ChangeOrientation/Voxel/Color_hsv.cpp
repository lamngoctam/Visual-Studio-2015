#include "../Voxel.h"

double Min(double r, double g, double b);
double Max(double r, double g, double b);

double Max(double r, double g, double b)
{
	double max(r);
	if (g > max)
		max = g;
	if (b > max)
		max = b;
	return max;
}

double Min(double r, double g, double b)
{
	double min(r);
	if (g < min)
		min = g;
	if (b < min)
		min = b;
	return min;
}

double Color_hue::GetLuminance()
{
	return this->luminance;
}

//http://ofo.jp/osakana/cgtips/grayscale.phtml
void Color_hue::CalcLuminance(){
	this->luminance = 0.298912 *(this->r) + 0.586611 * (this->g) + 0.114478 * (this->b);			
}

Color_hue::Color_hue()
{
	this->r = 0.0;
	this->g = 0.0;
	this->b = 0.0;
	this->hue = 0.0;
	this->luminance = 0.0;
}

void Color_hue::CalcHue()
{
	double max = Max(this->r, this->g, this->b);
	double min = Min(this->r, this->g, this->b);

	if (max == 0.0 || max == min)
		this->hue = 0.0;
	else
	{
		if (max == this->r)
			this->hue = 60.0 * (this->g - this->b) / (max - min);
		else if (max == this->g)
			this->hue = 60.0 * (this->b - this->r) / (max - min) + 120.0;
		else if (max == this->b)
			this->hue = 60.0 * (this->r - this->g) / (max - min) + 240.0;

		//— hue < 0 360.0
		if (this->hue < 0.0)
			this->hue = this->hue + 360.0;
		//—áŠOˆ— hue > 360@‚È‚ç‚Î360‚ÅŠ„‚Á‚½‚ ‚Ü‚è
		else if (this->hue > 360.0)
			this->hue = fmod(this->hue, 360.0);
	}
}

double Color_hue::GetHue()
{
	return this->hue;
}

void Color_hue::Clear()
{
	this->b = 0.0;
	this->g = 0.0;
	this->r = 0.0;
	this->hue = 0.0;
	this->luminance = 0.0;
}
