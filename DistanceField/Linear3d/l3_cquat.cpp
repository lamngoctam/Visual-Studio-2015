#include "l3.h"
using namespace std;
//##########################################//
//	CPoint3d�̃����o�[�֐��A�t�����h�֐�	//
//##########################################//
/****** �R���X�g���N�^���f�X�g���N�^ *****/

//�y01�z�R���X�g���N�^
CQuat::CQuat()
{
	x = y = z = w = 0.0;
}

//�y02�z�R���X�g���N�^
CQuat::CQuat(double X, double Y, double Z, double W)
{
	x = X;	y = Y;	z = Z;	w = W;
}

//�y03�z�f�X�g���N�^
CQuat::~CQuat(){}

/*************** �v�f�֌W ***************/

//�y04�z���W�l�̓���
void CQuat::Set(double X, double Y, double Z, double W)
{
	x = X;	y = Y;	z = Z;	w = W;
}

//�y06�z�x�N�g���̃N���A
void CQuat::Clear()
{
	x = 0.0;	y = 0.0;	z = 0.0;	w = 0.0;
}

//�y07�z�v�����g�o��
void CQuat::Print()
{
	std::cout<<"("<<x<<","<<y<<","<<z<<","<<w<<")"<<std::endl;
}

/*************** �I�[�o�[���[�h ***************/

//�y10�z=���Z�q�I�[�o�[���[�h
CQuat& CQuat::operator=(const CQuat& obj)
{
	x = obj.x;	y = obj.y;	z = obj.z;	w = obj.w;
	return *this;
}

//�y11�z+���Z�q�I�[�o�[���[�h
CQuat CQuat::operator+(const CQuat& obj)
{
	CQuat tmp;
	tmp.x = x + obj.x;	tmp.y = y + obj.y;	tmp.z = z + obj.z;	tmp.w = w + obj.w;
	return (tmp);
}

//�y12�z+=���Z�q�I�[�o�[���[�h
CQuat& CQuat::operator+=(const CQuat& obj)
{
	x += obj.x;	y += obj.y;	z += obj.z; w += obj.w;
	return *this;
}

//�y13�z-���Z�q�I�[�o�[���[�h
CQuat CQuat::operator-(const CQuat& obj)
{
	CQuat tmp;
	tmp.x = x - obj.x;	tmp.y = y - obj.y;	tmp.z = z - obj.z;	tmp.w = w - obj.w;
	return (tmp);
}

//�y14�z-=���Z�q�I�[�o�[���[�h
CQuat& CQuat::operator-=(const CQuat& obj)
{
	x -= obj.x;	y -= obj.y;	z -= obj.z;	w -= obj.w;
	return *this;
}

//�y15�z-���Z�q�I�[�o�[���[�h �������t�ɂ���
CQuat  CQuat::operator-()
{
	CQuat tmp;
	tmp.x = -x; tmp.y = -y; tmp.z = -z;	tmp.w = -w;
	return(tmp);
}

//�y16�z*���Z�q�I�[�o�[���[�h
CQuat CQuat::operator*(const double a)
{
	CQuat tmp;
	tmp.x = a * x;	tmp.y = a * y;	tmp.z = a * z;	tmp.w = a * w;
	return (tmp);
}
//�y17�z*���Z�q�I�[�o�[���[�h
CQuat operator*(const double a, const CQuat& obj)
{
	CQuat tmp;
	tmp.x = a * obj.x;	tmp.y = a * obj.y;	tmp.z = a * obj.z;	tmp.w = a * obj.w;
	return (tmp);
}

//�y18�z*���Z�q�I�[�o�[���[�h
CQuat  CQuat::operator*(const CQuat& obj)
{
	CQuat tmp;
	tmp.w = w * obj.w - x * obj.x - y * obj.y - z * obj.z;
	tmp.x = w * obj.x + x * obj.w - y * obj.z + z * obj.y;
	tmp.y = w * obj.y + x * obj.z + y * obj.w - z * obj.x;
	tmp.z = w * obj.z - x * obj.y + y * obj.x + z * obj.w;
	
	return (tmp);
}

/*************** �N�H�[�^�j�I���v�Z ***************/
//�y21�z�i�[����Ă�����W�̐��K��������
CQuat CQuat::Identify()
{
	CQuat tmp(0,0,0,1.0);
	return (tmp);
}

//�y23�z�N�H�[�^�j�I���̑傫�������߂�
double CQuat::Norm()
{
	return (sqrt(Norm_sqr()));
}

//�y24�z�N�H�[�^�j�I���̃m����
double CQuat::Norm_sqr()
{
	return (x*x + y*y + z*z + w*w);
}