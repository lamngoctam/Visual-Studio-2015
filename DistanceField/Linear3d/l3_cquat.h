#pragma once
//�N�H�[�^�j�I�����Z���C�u����	
//�y�Q�l���z3D-CG�v���O���}�[�̂��߂̃��A���^�C���V�F�[�_�[�y���_�Ǝ��H�z�Q��
class CQuat;

//##############################################//
//	�N�H�[�^�j�I���N���X						//
//##############################################//
class CQuat
{
public://�����o�[�ϐ�
	double x;	//x���W
	double y;	//y���W
	double z;	//z���W
	double w;	//

public://�����o�[�֐��y�уt�����h�֐�
	/***** �R���X�g���N�^���f�X�g���N�^ *****/
	CQuat();											//�y01�z�R���X�g���N�^
	CQuat(double X, double Y, double Z, double W);		//�y02�z�R���X�g���N�^
	~CQuat();											//�y03�z�f�X�g���N�^
	/***** �v�f�֌W *****/
	void Set(double X, double Y, double Z, double W);	//�y04�z���W���Z�b�g����
	void Clear();										//�y06�z�N�H�[�^�j�I���̃N���A
	void Print();										//�y07�z�N�H�[�^�j�I���̏o��
	/***** �I�[�o�[���[�h *****/
	CQuat& operator=(const CQuat& obj);					//�y10�z=���Z�q�I�[�o�[���[�h
	CQuat  operator+(const CQuat& obj);					//�y11�z+���Z�q�I�[�o�[���[�h
	CQuat& operator+=(const CQuat& obj);				//�y12�z+=���Z�q�I�[�o�[���[�h
	CQuat  operator-(const CQuat& obj);					//�y13�z-���Z�q�I�[�o�[���[�h
	CQuat& operator-=(const CQuat& obj);				//�y14�z-=���Z�q�I�[�o�[���[�h
	CQuat  operator-();									//�y15�z-���Z�q�I�[�o�[���[�h
	CQuat  operator*(const double a);					//�y16�z*���Z�q�I�[�o�[���[�h
	friend CQuat operator*(const double a,const CQuat& obj);	//�y17�z*���Z�q�I�[�o�[���[�h
	CQuat  operator*(const CQuat& obj);					//�y18�z*���Z�q�I�[�o�[���[�h
	/***** �N�H�[�^�j�I���̌v�Z *****/
	CQuat Identify();					//�y21�z�i�[����Ă�����W�̐��K��������
	double	Norm();						//�y23�z�N�H�[�^�j�I���̑傫�������߂�
	double	Norm_sqr();					//�y24�z�N�H�[�^�j�I���̃m����
};