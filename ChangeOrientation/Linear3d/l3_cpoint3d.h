#pragma once

class CPoint3d;
class CVector3d;

//##############################################//
//	���_���ɂ��ẴN���X(����_�p�N���X)	//
//##############################################//
class CPoint3d
{
public://�����o�[�ϐ�
	double x;	//x���W
	double y;	//y���W
	double z;	//z���W
	double w;	//�d��

public://�����o�[�֐��y�уt�����h�֐�
	/***** �R���X�g���N�^���f�X�g���N�^ *****/
	CPoint3d();												//�y01�z�R���X�g���N�^
	CPoint3d(double X, double Y, double Z, double W = 1.0);	//�y02�z�R���X�g���N�^
	~CPoint3d();											//�y03�z�f�X�g���N�^

	/***** �v�f�֌W *****/
	void Set(double X, double Y, double Z, double W = 1.0 );//�y04�z���W���Z�b�g����
	void UnitVector(double X, double Y, double Z);			//�y05�z���W���Z�b�g��A���K������
	void Clear();											//�y06�z�x�N�g���̃N���A
	void Print();											//�y07�z�x�N�g���̏o��

	/***** �I�[�o�[���[�h *****/
	CPoint3d& operator=(const CPoint3d& obj);	//�y10�z=���Z�q�I�[�o�[���[�h
	CPoint3d  operator+(const CPoint3d& obj);	//�y11�z+���Z�q�I�[�o�[���[�h
	CPoint3d& operator+=(const CPoint3d& obj);	//�y12�z+=���Z�q�I�[�o�[���[�h
	CPoint3d  operator-(const CPoint3d& obj);	//�y13�z-���Z�q�I�[�o�[���[�h
	CPoint3d& operator-=(const CPoint3d& obj);	//�y14�z-=���Z�q�I�[�o�[���[�h
	CPoint3d  operator-();						//�y15�z-���Z�q�I�[�o�[���[�h
	CPoint3d  operator*(const double k);		//�y16�z*���Z�q�I�[�o�[���[�h
	friend CPoint3d operator*(const double k,const CPoint3d& obj);	//�y17�z*���Z�q�I�[�o�[���[�h
	operator CVector3d();						//�y18�zCVector3d�^�ϊ����Z�q�̃I�[�o�[���[�h
	CPoint3d operator/(const double k);			//�y19�z/���Z�q�̃I�[�o�[���[�h
	operator	 double*();						//�y20�z*���Z�q�̃I�[�o�[���[�h

	/***** �x�N�g���v�Z *****/
	CPoint3d Mid(CPoint3d &obj);			//�y20�zobj�_�Ƃ̒��_�����߂�
	CPoint3d Normalize();					//�y21�z�i�[����Ă�����W�̐��K��������
	void	Normalize(CPoint3d &obj);		//�y22�zobj�_�𐳋K������
	double	Norm();							//�y23�z�x�N�g���̑傫�������߂�
	double	Distance(CPoint3d &obj);		//�y24�zobj�_�Ƃ̋��������߂�
	double	Dot(CPoint3d &obj);				//�y25�zobj�_�Ƃ̓��ς����߂�
	CPoint3d Cross(CPoint3d &obj);			//�y26�zobj�_�Ƃ̊O�ς����߂�
	double	Angle(CPoint3d &obj);			//�y27�zobj�Ƃ̊p�x
	double	PointLineDistance(CPoint3d &P0, CPoint3d &P1);	//�y28�zPoint-Line Distance
	CPoint3d Max(CPoint3d &obj);			//�y29�zobj�_�Ƃ�xyz�e�ő�l��Ԃ�
	CPoint3d Min(CPoint3d &obj);			//�y30�zobj�_�Ƃ�xyz�e�ŏ��l��Ԃ�
	CPoint3d RotateX(double rad);			//�y31�zX�������rad��]
	CPoint3d RotateY(double rad);			//�y32�zY�������rad��]
	CPoint3d RotateZ(double rad);			//�y33�zZ�������rad��]

	/***** CVector3d�Ƃ̌݊���*****/
	CPoint3d& operator=(const CVector3d& obj);	//�y10-2�z=���Z�q�I�[�o�[���[�h
	CPoint3d  operator+(const CVector3d& obj);	//�y11-2�z+���Z�q�I�[�o�[���[�h
	CPoint3d& operator+=(const CVector3d& obj);	//�y12-2�z+=���Z�q�I�[�o�[���[�h
	CPoint3d  operator-(const CVector3d& obj);	//�y13-2�z-���Z�q�I�[�o�[���[�h
	CPoint3d& operator-=(const CVector3d& obj);	//�y14-2�z-=���Z�q�I�[�o�[���[�h
	CPoint3d Mid(CVector3d &obj);				//�y20-2�zobj�_�Ƃ̒��_�����߂�
	double	Distance(CVector3d &obj);			//�y24-2�zobj�_�Ƃ̋��������߂�
	double	Dot(CVector3d &obj);				//�y25-2�zobj�_�Ƃ̓��ς����߂�
	CPoint3d Cross(CVector3d &obj);				//�y26-2�zobj�_�Ƃ̊O�ς����߂�
	double	Angle(CVector3d &obj);				//�y27-2�zobj�Ƃ̊p�x
	CPoint3d Max(CVector3d &obj);				//�y29-2�zobj�_�Ƃ�xyz�e�ő�l��Ԃ�
	CPoint3d Min(CVector3d &obj);				//�y30-2�zobj�_�Ƃ�xyz�e�ŏ��l��Ԃ�
};

//##############################################//
//	���_���ɂ��ẴN���X(����_�p�N���X)	//
//##############################################//
class CVector3d
{
public://�����o�[�ϐ�
	double x;	//x���W
	double y;	//y���W
	double z;	//z���W

public://�����o�[�֐��y�уt�����h�֐�
	/***** �R���X�g���N�^���f�X�g���N�^ *****/
	CVector3d();								//�y01�z�R���X�g���N�^
	CVector3d(double X, double Y, double Z);	//�y02�z�R���X�g���N�^
	~CVector3d();								//�y03�z�f�X�g���N�^

	/***** �v�f�֌W *****/
	void Set(double X, double Y, double Z);	//�y04�z���W���Z�b�g����
	void UnitVector(double X, double Y, double Z);	//�y05�z���W���Z�b�g��A���K������
	void Clear();							//�y06�z�x�N�g���̃N���A
	void Print();							//�y07�z�x�N�g���̏o��

	/***** �I�[�o�[���[�h *****/
	CVector3d& operator=(const CVector3d& obj);		//�y10�z=���Z�q�I�[�o�[���[�h
	CVector3d  operator+(const CVector3d& obj);		//�y11�z+���Z�q�I�[�o�[���[�h
	CVector3d& operator+=(const CVector3d& obj);	//�y12�z+=���Z�q�I�[�o�[���[�h
	CVector3d  operator-(const CVector3d& obj);		//�y13�z-���Z�q�I�[�o�[���[�h
	CVector3d& operator-=(const CVector3d& obj);	//�y14�z-=���Z�q�I�[�o�[���[�h
	CVector3d  operator-();							//�y15�z-���Z�q�I�[�o�[���[�h
	CVector3d  operator*(const double k);			//�y16�z*���Z�q�I�[�o�[���[�h
	friend CVector3d operator*(const double k,const CVector3d& obj);	//�y17�z*���Z�q�I�[�o�[���[�h
	operator CPoint3d();							//�y18�zCPoint3d�^�ϊ����Z�q�̃I�[�o�[���[�h
	CVector3d operator/(const double k);			//�y19�z/���Z�q�̃I�[�o�[���[�h
	operator	 double*();							//�y20�z*���Z�q�̃I�[�o�[���[�h

	/***** �x�N�g���v�Z *****/
	CVector3d Mid(CVector3d &obj);			//�y20�zobj�_�Ƃ̒��_�����߂�
	CVector3d Normalize();					//�y21�z�i�[����Ă�����W�̐��K��������
	void	Normalize(CVector3d &obj);		//�y22�zobj�_�𐳋K������
	double	Norm();							//�y23�z�x�N�g���̑傫�������߂�
	double	Distance(CVector3d &obj);		//�y24�zobj�_�Ƃ̋��������߂�
	double SquaredDistance(CVector3d &obj);

	double	Dot(CVector3d &obj);			//�y25�zobj�_�Ƃ̓��ς����߂�
	CVector3d Cross(CVector3d &obj);		//�y26�zobj�_�Ƃ̊O�ς����߂�
	double	Angle(CVector3d &obj);			//�y27�zobj�Ƃ̊p�x
	double	PointLineDistance(CVector3d &P0, CVector3d &P1);	//�y28�zPoint-Line Distance
	CVector3d Max(CVector3d &obj);			//�y29�za�_�Ƃ�xyz�e�ő�l��Ԃ�
	CVector3d Min(CVector3d &obj);			//�y30�za�_�Ƃ�xyz�e�ŏ��l��Ԃ�
	CVector3d RotateX(double rad);			//�y31�zX�������rad��]
	CVector3d RotateY(double rad);			//�y32�zY�������rad��]
	CVector3d RotateZ(double rad);			//�y33�zZ�������rad��]

	/***** CVector3d�Ƃ̌݊���*****/
	CVector3d& operator=(const CPoint3d& obj);	//�y10-2�z=���Z�q�I�[�o�[���[�h
	CVector3d  operator+(const CPoint3d& obj);	//�y11-2�z+���Z�q�I�[�o�[���[�h
	CVector3d& operator+=(const CPoint3d& obj);	//�y12-2�z+=���Z�q�I�[�o�[���[�h
	CVector3d  operator-(const CPoint3d& obj);	//�y13-2�z-���Z�q�I�[�o�[���[�h
	CVector3d& operator-=(const CPoint3d& obj);	//�y14-2�z-=���Z�q�I�[�o�[���[�h
	CVector3d Mid(CPoint3d &obj);				//�y20-2�zobj�_�Ƃ̒��_�����߂�
	double	Distance(CPoint3d &obj);			//�y24-2�zobj�_�Ƃ̋��������߂�
	double	Dot(CPoint3d &obj);				//�y25-2�zobj�_�Ƃ̓��ς����߂�
	CVector3d Cross(CPoint3d &obj);			//�y26-2�zobj�_�Ƃ̊O�ς����߂�
	double	Angle(CPoint3d &obj);			//�y27-2�zobj�Ƃ̊p�x
	CVector3d Max(CPoint3d &obj);			//�y29-2�zobj�_�Ƃ�xyz�e�ő�l��Ԃ�
	CVector3d Min(CPoint3d &obj);			//�y30-2�zobj�_�Ƃ�xyz�e�ŏ��l��Ԃ�
	CVector3d NormalVector(CVector3d b,CVector3d c);	//�y34 3�_a,b,c�̒P�ʖ@���x�N�g����Ԃ�2012/5/29(���̐l�Ƃ̌݊����������̂ł����ꑼ�̏��Ɏ����Ă�)
};