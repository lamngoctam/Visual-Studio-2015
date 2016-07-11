#define _USE_MATH_DEFINES	//�~����M_PI���g�����߂ɕK�v
#include "l3.h"
using namespace std;
//##########################################//
//	CPoint3d�̃����o�[�֐��A�t�����h�֐�	//
//##########################################//
/****** �R���X�g���N�^���f�X�g���N�^ *****/

//�y01�z�R���X�g���N�^
CPoint3d::CPoint3d()
{
	x = y = z = 0.0;
	w = 1.0;
}

//�y02�z�R���X�g���N�^
CPoint3d::CPoint3d(double X, double Y, double Z, double W)
{
	x = X;	y = Y;	z = Z;	w = W;
}

//�y03�z�f�X�g���N�^
CPoint3d::~CPoint3d(){}

/*************** �v�f�֌W ***************/

//�y04�z���W�l�̓���
void CPoint3d::Set(double X, double Y, double Z, double W)
{
	x = X;	y = Y;	z = Z;	w = W;
}

//�y05�z���W���Z�b�g��A���K������
void CPoint3d::UnitVector(double X, double Y, double Z)
{
	double norm = sqrt(X*X+Y*Y+Z*Z);
	x = X/norm;	y = Y/norm;	z = Z/norm;
}

//�y06�z�x�N�g���̃N���A
void CPoint3d::Clear()
{
	x = 0.0;	y = 0.0;	z = 0.0;	w = 1.0;
}

//�y07�z�v�����g�o��
void CPoint3d::Print()
{
	std::cout<<"("<<x<<","<<y<<","<<z<<","<<w<<");"<<std::endl;
}

/*************** �I�[�o�[���[�h ***************/

//�y10�z=���Z�q�I�[�o�[���[�h
CPoint3d& CPoint3d::operator=(const CPoint3d& obj)
{
	x = obj.x;	y = obj.y;	z = obj.z;	w = obj.w;
	return *this;
}

//�y11�z+���Z�q�I�[�o�[���[�h
CPoint3d CPoint3d::operator+(const CPoint3d& obj)
{
	CPoint3d tmp;
	tmp.x = x + obj.x;	tmp.y = y + obj.y;	tmp.z = z + obj.z;
	return (tmp);
}

//�y12�z+=���Z�q�I�[�o�[���[�h
CPoint3d& CPoint3d::operator+=(const CPoint3d& obj)
{
	x += obj.x;	y += obj.y;	z += obj.z;
	return *this;
}

//�y13�z-���Z�q�I�[�o�[���[�h
CPoint3d CPoint3d::operator-(const CPoint3d& obj)
{
	CPoint3d tmp;
	tmp.x = x - obj.x;	tmp.y = y - obj.y;	tmp.z = z - obj.z;
	return (tmp);
}

//�y14�z-=���Z�q�I�[�o�[���[�h
CPoint3d& CPoint3d::operator-=(const CPoint3d& obj)
{
	x -= obj.x;	y -= obj.y;	z -= obj.z;
	return *this;
}

//�y15�z-���Z�q�I�[�o�[���[�h �������t�ɂ���
CPoint3d  CPoint3d::operator-()
{
	CPoint3d tmp;
	tmp.x = -x; tmp.y = -y; tmp.z = -z;
	return(tmp);
}

//�y16�z*���Z�q�I�[�o�[���[�h
CPoint3d CPoint3d::operator*(const double k)
{
	CPoint3d tmp;
	tmp.x = k * x;	tmp.y = k * y;	tmp.z = k * z;
	return (tmp);
}
//�y17�z*���Z�q�I�[�o�[���[�h
CPoint3d operator*(const double k, const CPoint3d& obj)
{
	CPoint3d tmp;
	tmp.x = k * obj.x;	tmp.y = k * obj.y;	tmp.z = k * obj.z;
	return (tmp);
}

//�y18�zCVector3d�^�ϊ����Z�q�̃I�[�o�[���[�h
CPoint3d::operator CVector3d()
{
	return CVector3d(x,y,z);
}

//�y19�z/���Z�q�̃I�[�o�[���[�h
CPoint3d CPoint3d::operator/(const double k)
{
	CPoint3d tmp;
	tmp.x = x / k;	tmp.y = y / k;	tmp.z = z / k;
	return (tmp);
}

//�y20�z*���Z�q�̃I�[�o�[���[�h
CPoint3d::operator double*()
{
	static double r[4];
	r[0] = x; r[1] = y; r[2] = z; r[3] = w;
	return r;
}


/*************** �x�N�g���v�Z ***************/

//�y20�z�x�N�g���̒��_�����߂�
CPoint3d CPoint3d::Mid(CPoint3d &obj)
{
	CPoint3d tmp;
	tmp.x = (x + obj.x)/2.0;
	tmp.y = (y + obj.y)/2.0;
	tmp.z = (z + obj.z)/2.0;
	return (tmp);
}

//�y20-2�z�x�N�g���̒��_�����߂�
CPoint3d CPoint3d::Mid(CVector3d &obj)
{
	CPoint3d tmp;
	tmp.x = (x + obj.x)/2.0;
	tmp.y = (y + obj.y)/2.0;
	tmp.z = (z + obj.z)/2.0;
	return (tmp);
}

//�y21�z�i�[����Ă�����W�̐��K��������
CPoint3d CPoint3d::Normalize()
{
	double norm = Norm();
	CPoint3d tmp;
	if(norm!=0){
		tmp.x = x/norm;	tmp.y = y/norm;	tmp.z = z/norm;
	}
	return (tmp);
}

//�y22�z���K������
void CPoint3d::Normalize(CPoint3d &obj)
{
	double norm = obj.Norm();
	if(norm!=0){
		x = obj.x/norm;	y = obj.y/norm;	z = obj.z/norm;
	}
}

//�y23�z���[�N���b�h�m����
double CPoint3d::Norm()
{
	return (sqrt( x*x + y*y + z*z ));
}

//�y24�z�����̌v�Z
double CPoint3d::Distance(CPoint3d &obj)
{
	double X = x - obj.x;	
	double Y = y - obj.y;
	double Z = z - obj.z;
	return (sqrt( X*X + Y*Y + Z*Z));
}

//�y24-2�z�����̌v�Z
double CPoint3d::Distance(CVector3d &obj)
{
	double X = x - obj.x;	
	double Y = y - obj.y;
	double Z = z - obj.z;
	return (sqrt( X*X + Y*Y + Z*Z));
}

//�y25�z�x�N�g���̓���
double CPoint3d::Dot(CPoint3d &obj)
{
	double dot = x * obj.x;
	dot += y * obj.y;
	dot += z * obj.z;
	return (dot);
}

//�y25-2�z�x�N�g���̓���
double CPoint3d::Dot(CVector3d &obj)
{
	double dot = x * obj.x;
	dot += y * obj.y;
	dot += z * obj.z;
	return (dot);
}

//�y26�z�x�N�g���̊O��
CPoint3d CPoint3d::Cross(CPoint3d &obj)
{
	CPoint3d tmp;
	tmp.x = y*obj.z - z*obj.y;
	tmp.y = z*obj.x - x*obj.z;
	tmp.z = x*obj.y - y*obj.x;
	return (tmp);
}

//�y26-2�z�x�N�g���̊O��
CPoint3d CPoint3d::Cross(CVector3d &obj)
{
	CPoint3d tmp;
	tmp.x = y*obj.z - z*obj.y;
	tmp.y = z*obj.x - x*obj.z;
	tmp.z = x*obj.y - y*obj.x;
	return (tmp);
}

//�y27�za�Ƃ̊p�x
double CPoint3d::Angle(CPoint3d &obj)
{
	double deg,den;
	den = Norm()*obj.Norm();
	if( den <1.0e-15 ){
		std::cout<<"error"<<std::endl;
		return 0;
	}
	deg = Dot(obj)/den;
	if(deg > 1.0)	deg = 1.0;
	if(deg < -1.0)	deg =-1.0;

	deg = acos(deg);
	deg = 180.0*(deg/M_PI);

	return deg;
}

//�y27�za�Ƃ̊p�x
double CPoint3d::Angle(CVector3d &obj)
{
	double deg,den;
	den = Norm()*obj.Norm();
	if( den <1.0e-15 ){
		std::cout<<"error"<<std::endl;
		return 0;
	}
	deg = Dot(obj)/den;
	if(deg > 1.0)	deg = 1.0;
	if(deg < -1.0)	deg =-1.0;

	deg = acos(deg);
	deg = 180.0*(deg/M_PI);

	return deg;
}

//�y28�zPoint-Line Distance
double CPoint3d::PointLineDistance(CPoint3d &P0, CPoint3d &P1)
{
	CPoint3d A = P1-P0;
	CPoint3d B( x-P0.x, y-P0.y, z-P0.z);
	return ( (A.Cross(B)).Norm()/P0.Distance(P1) );
}

//�y29�za�_�Ƃ�xyz�e�ő�l��Ԃ�
CPoint3d CPoint3d::Max(CPoint3d &obj)
{
	CPoint3d tmp;
	tmp.x = max(x,obj.x);
	tmp.y = max(y,obj.y);
	tmp.z = max(z,obj.z);
	return (tmp);
}

//�y29-2�za�_�Ƃ�xyz�e�ő�l��Ԃ�
CPoint3d CPoint3d::Max(CVector3d &obj)
{
	CPoint3d tmp;
	tmp.x = max(x,obj.x);
	tmp.y = max(y,obj.y);
	tmp.z = max(z,obj.z);
	return (tmp);
}

//�y30�za�_�Ƃ�xyz�e�ŏ��l��Ԃ�
CPoint3d CPoint3d::Min(CPoint3d &obj)
{
	CPoint3d tmp;
	tmp.x = min(x,obj.x);
	tmp.y = min(y,obj.y);
	tmp.z = min(z,obj.z);
	return (tmp);
}

//�y30-2�za�_�Ƃ�xyz�e�ŏ��l��Ԃ�
CPoint3d CPoint3d::Min(CVector3d &obj)
{
	CPoint3d tmp;
	tmp.x = min(x,obj.x);
	tmp.y = min(y,obj.y);
	tmp.z = min(z,obj.z);
	return (tmp);
}

//�y31�zX�������rad��]
CPoint3d CPoint3d::RotateX( double rad )
{
	CPoint3d tmp;
	tmp.x = x;
	tmp.y = (y*cos(rad)) - (z*sin(rad));
	tmp.z = (y*sin(rad)) + (z*cos(rad));
	return (tmp);
}

//�y32�zY�������rad��]
CPoint3d CPoint3d::RotateY( double rad )
{
	CPoint3d tmp;
	tmp.x = (z*sin(rad)) + (x*cos(rad));
	tmp.y = y;
	tmp.z = (z*cos(rad)) - (x*sin(rad));
	return (tmp);
}

//�y33�zZ�������rad��]
CPoint3d CPoint3d::RotateZ( double rad )
{
	CPoint3d tmp;
	tmp.x = (x*cos(rad)) - (y*sin(rad));
	tmp.y = (x*sin(rad)) + (y*cos(rad));
	tmp.z = z;
	return (tmp);
}



/*************** CVector3d�Ƃ̌݊��� ***************/

//�y10-2�z=���Z�q�I�[�o�[���[�h
CPoint3d& CPoint3d::operator=(const CVector3d& obj)
{
	x = obj.x;	y = obj.y;	z = obj.z;
	return *this;
}

//�y11-2�z+���Z�q�I�[�o�[���[�h
CPoint3d CPoint3d::operator+(const CVector3d& obj)
{
	CPoint3d tmp;
	tmp.x = x + obj.x;	tmp.y = y + obj.y;	tmp.z = z + obj.z;
	return (tmp);
}

//�y12-2�z+=���Z�q�I�[�o�[���[�h
CPoint3d& CPoint3d::operator+=(const CVector3d& obj)
{
	x += obj.x;	y += obj.y;	z += obj.z;
	return *this;
}

//�y13-2�z-���Z�q�I�[�o�[���[�h
CPoint3d CPoint3d::operator-(const CVector3d& obj)
{
	CPoint3d tmp;
	tmp.x = x - obj.x;	tmp.y = y - obj.y;	tmp.z = z - obj.z;
	return (tmp);
}

//�y14-2�z-=���Z�q�I�[�o�[���[�h
CPoint3d& CPoint3d::operator-=(const CVector3d& obj)
{
	x -= obj.x;	y -= obj.y;	z -= obj.z;
	return *this;
}

//######################################//
//	CVector3d�̃����o�[�֐��A�t�����h�֐�	//
//######################################//
/****** �R���X�g���N�^���f�X�g���N�^ *****/

//�y01�z�R���X�g���N�^
CVector3d::CVector3d()
{
	x = y = z = 0.0;
}

//�y02�z�R���X�g���N�^
CVector3d::CVector3d(double X, double Y, double Z)
{
	x = X;	y = Y;	z = Z;
}

//�y03�z�f�X�g���N�^
CVector3d::~CVector3d(){}

/*************** �v�f�֌W ***************/

//�y04�z���W�l�̓���
void CVector3d::Set(double X, double Y, double Z)
{
	x = X;	y = Y;	z = Z;	
}

//�y05�z���W���Z�b�g��A���K������
void CVector3d::UnitVector(double X, double Y, double Z)
{
	double norm = sqrt(X*X+Y*Y+Z*Z);
	x = X/norm;	y = Y/norm;	z = Z/norm;
}

//�y06�z�x�N�g���̃N���A
void CVector3d::Clear()
{
	x = 0.0;	y = 0.0;	z = 0.0;
}

//�y07�z�v�����g�o��
void CVector3d::Print()
{
	std::cout<<"("<<x<<","<<y<<","<<z<<")"<<std::endl;
}

/*************** �I�[�o�[���[�h ***************/

//�y10�z=���Z�q�I�[�o�[���[�h
CVector3d& CVector3d::operator=(const CVector3d& obj)
{
	x = obj.x;	y = obj.y;	z = obj.z;
	return *this;
}

//�y11�z+���Z�q�I�[�o�[���[�h
CVector3d CVector3d::operator+(const CVector3d& obj)
{
	CVector3d tmp;
	tmp.x = x + obj.x;	tmp.y = y + obj.y;	tmp.z = z + obj.z;
	return (tmp);
}

//�y12�z+=���Z�q�I�[�o�[���[�h
CVector3d& CVector3d::operator+=(const CVector3d& obj)
{
	x += obj.x;	y += obj.y;	z += obj.z;
	return *this;
}

//�y13�z-���Z�q�I�[�o�[���[�h
CVector3d CVector3d::operator-(const CVector3d& obj)
{
	CVector3d tmp;
	tmp.x = x - obj.x;	tmp.y = y - obj.y;	tmp.z = z - obj.z;
	return (tmp);
}

//�y14�z-=���Z�q�I�[�o�[���[�h
CVector3d& CVector3d::operator-=(const CVector3d& obj)
{
	x -= obj.x;	y -= obj.y;	z -= obj.z;
	return *this;
}

//�y15�z-���Z�q�I�[�o�[���[�h �������t�ɂ���
CVector3d  CVector3d::operator-()
{
	CVector3d tmp;
	tmp.x = -x; tmp.y = -y; tmp.z = -z;
	return(tmp);
}

//�y16�z*���Z�q�I�[�o�[���[�h
CVector3d CVector3d::operator*(const double k)
{
	CVector3d tmp;
	tmp.x = k * x;	tmp.y = k * y;	tmp.z = k * z;
	return (tmp);
}
//�y17�z*���Z�q�I�[�o�[���[�h
CVector3d operator*(const double k, const CVector3d& obj)
{
	CVector3d tmp;
	tmp.x = k * obj.x;	tmp.y = k * obj.y;	tmp.z = k * obj.z;
	return (tmp);
}

//�y18�zCPoint3d�^�ϊ����Z�q�̃I�[�o�[���[�h
CVector3d::operator CPoint3d()
{
	return CPoint3d(x,y,z);
}

//�y19�z/���Z�q�̃I�[�o�[���[�h
CVector3d CVector3d::operator/(const double k)
{
	CVector3d tmp;
	tmp.x = x / k;	tmp.y = y / k;	tmp.z = z / k;
	return (tmp);
}

//�y20�z*���Z�q�̃I�[�o�[���[�h
CVector3d::operator double*()
{
	static double r[3];
	r[0] = x; r[1] = y; r[2] = z;
	return r;
}

/*************** �x�N�g���v�Z ***************/

//�y20�z�x�N�g���̒��_�����߂�
CVector3d CVector3d::Mid(CVector3d &obj)
{
	CVector3d tmp;
	tmp.x = (x + obj.x)/2.0;
	tmp.y = (y + obj.y)/2.0;
	tmp.z = (z + obj.z)/2.0;
	return (tmp);
}

//�y20-2�z�x�N�g���̒��_�����߂�
CVector3d CVector3d::Mid(CPoint3d &obj)
{
	CVector3d tmp;
	tmp.x = (x + obj.x)/2.0;
	tmp.y = (y + obj.y)/2.0;
	tmp.z = (z + obj.z)/2.0;
	return (tmp);
}

//�y21�z�i�[����Ă�����W�̐��K��������
CVector3d CVector3d::Normalize()
{
	double norm = Norm();
	CVector3d tmp;
	tmp.x = x/norm;	tmp.y = y/norm;	tmp.z = z/norm;
	return (tmp);
}

//�y22�z���K������
void CVector3d::Normalize(CVector3d &obj)
{
	double norm = obj.Norm();
	x = obj.x/norm;	y = obj.y/norm;	z = obj.z/norm;

}

//�y23�z���[�N���b�h�m����
double CVector3d::Norm()
{
	return (sqrt( x*x + y*y + z*z ));
}

//�y24�z�����̌v�Z
double CVector3d::Distance(CVector3d &obj)
{
	double X = x - obj.x;	
	double Y = y - obj.y;
	double Z = z - obj.z;
	return (sqrt( X*X + Y*Y + Z*Z));
}

//�y24-2�z�����̌v�Z
double CVector3d::Distance(CPoint3d &obj)
{
	double X = x - obj.x;	
	double Y = y - obj.y;
	double Z = z - obj.z;
	return (sqrt( X*X + Y*Y + Z*Z));
}

//�y25�z�x�N�g���̓���
double CVector3d::Dot(CVector3d &obj)
{
	double dot = x * obj.x;
	dot += y * obj.y;
	dot += z * obj.z;
	return (dot);
}

//�y25-2�z�x�N�g���̓���
double CVector3d::Dot(CPoint3d &obj)
{
	double dot = x * obj.x;
	dot += y * obj.y;
	dot += z * obj.z;
	return (dot);
}

//�y26�z�x�N�g���̊O��
CVector3d CVector3d::Cross(CVector3d &obj)
{
	CVector3d tmp;
	tmp.x = y*obj.z - z*obj.y;
	tmp.y = z*obj.x - x*obj.z;
	tmp.z = x*obj.y - y*obj.x;
	return (tmp);
}

//�y26-2�z�x�N�g���̊O��
CVector3d CVector3d::Cross(CPoint3d &obj)
{
	CVector3d tmp;
	tmp.x = y*obj.z - z*obj.y;
	tmp.y = z*obj.x - x*obj.z;
	tmp.z = x*obj.y - y*obj.x;
	return (tmp);
}

//�y27�za�Ƃ̊p�x
double CVector3d::Angle(CVector3d &obj)
{
	double deg,den;
	den = Norm()*obj.Norm();
	if( den <1.0e-15 ){
		std::cout<<"error"<<std::endl;
		return 0;
	}
	deg = Dot(obj)/den;
	if(deg > 1.0)	deg = 1.0;
	if(deg < -1.0)	deg =-1.0;

	deg = acos(deg);
	deg = 180.0*(deg/M_PI);

	return deg;
}

//�y27-2�za�Ƃ̊p�x
double CVector3d::Angle(CPoint3d &obj)
{
	double deg,den;
	den = Norm()*obj.Norm();
	if( den <1.0e-15 ){
		std::cout<<"error"<<std::endl;
		return 0;
	}
	deg = Dot(obj)/den;
	if(deg > 1.0)	deg = 1.0;
	if(deg < -1.0)	deg =-1.0;

	deg = acos(deg);
	deg = 180.0*(deg/M_PI);

	return deg;
}

//�y28�zPoint-Line Distance
double CVector3d::PointLineDistance(CVector3d &P0, CVector3d &P1)
{
	CVector3d A = P1-P0;
	CVector3d B( x-P0.x, y-P0.y, z-P0.z);
	return ( (A.Cross(B)).Norm()/P0.Distance(P1) );
}

//�y29�za�_�Ƃ�xyz�e�ő�l��Ԃ�
CVector3d CVector3d::Max(CVector3d &obj)
{
	CVector3d tmp;
	tmp.x = max(x,obj.x);
	tmp.y = max(y,obj.y);
	tmp.z = max(z,obj.z);
	return (tmp);
}

//�y29-2�za�_�Ƃ�xyz�e�ő�l��Ԃ�
CVector3d CVector3d::Max(CPoint3d &obj)
{
	CVector3d tmp;
	tmp.x = max(x,obj.x);
	tmp.y = max(y,obj.y);
	tmp.z = max(z,obj.z);
	return (tmp);
}

//�y30�za�_�Ƃ�xyz�e�ŏ��l��Ԃ�
CVector3d CVector3d::Min(CVector3d &obj)
{
	CVector3d tmp;
	tmp.x = min(x,obj.x);
	tmp.y = min(y,obj.y);
	tmp.z = min(z,obj.z);
	return (tmp);
}

//�y30-2�za�_�Ƃ�xyz�e�ŏ��l��Ԃ�
CVector3d CVector3d::Min(CPoint3d &obj)
{
	CVector3d tmp;
	tmp.x = min(x,obj.x);
	tmp.y = min(y,obj.y);
	tmp.z = min(z,obj.z);
	return (tmp);
}

//�y31�zX�������rad��]
CVector3d CVector3d::RotateX( double rad )
{
	CVector3d tmp;
	tmp.x = x;
	tmp.y = (y*cos(rad)) - (z*sin(rad));
	tmp.z = (y*sin(rad)) + (z*cos(rad));
	return (tmp);
}

//�y32�zY�������rad��]
CVector3d CVector3d::RotateY( double rad )
{
	CVector3d tmp;
	tmp.x = (z*sin(rad)) + (x*cos(rad));
	tmp.y = y;
	tmp.z = (z*cos(rad)) - (x*sin(rad));
	return (tmp);
}

//�y33�zZ�������rad��]
CVector3d CVector3d::RotateZ( double rad )
{
	CVector3d tmp;
	tmp.x = (x*cos(rad)) - (y*sin(rad));
	tmp.y = (x*sin(rad)) + (y*cos(rad));
	tmp.z = z;
	return (tmp);
}

/*************** CPoint3d�Ƃ̌݊��� ***************/

//�y10-2�z=���Z�q�I�[�o�[���[�h
CVector3d& CVector3d::operator=(const CPoint3d& obj)
{
	x = obj.x;	y = obj.y;	z = obj.z;
	return *this;
}

//�y11-2�z+���Z�q�I�[�o�[���[�h
CVector3d CVector3d::operator+(const CPoint3d& obj)
{
	CVector3d tmp;
	tmp.x = x + obj.x;	tmp.y = y + obj.y;	tmp.z = z + obj.z;
	return (tmp);
}

//�y12-2�z+=���Z�q�I�[�o�[���[�h
CVector3d& CVector3d::operator+=(const CPoint3d& obj)
{
	x += obj.x;	y += obj.y;	z += obj.z;
	return *this;
}

//�y13-2�z-���Z�q�I�[�o�[���[�h
CVector3d CVector3d::operator-(const CPoint3d& obj)
{
	CVector3d tmp;
	tmp.x = x - obj.x;	tmp.y = y - obj.y;	tmp.z = z - obj.z;
	return (tmp);
}

//�y14-2�z-=���Z�q�I�[�o�[���[�h
CVector3d& CVector3d::operator-=(const CPoint3d& obj)
{
	x -= obj.x;	y -= obj.y;	z -= obj.z;
	return *this;
}