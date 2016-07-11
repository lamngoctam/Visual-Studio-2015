#pragma once
#include <iostream>
#include <vector>
using namespace std;

class CVector;
class CMatrix;

//#################################//
//	�x�N�g���ɂ��ẴN���X
//#################################//
class CVector
{
private://�����o�[�ϐ�	���A�N�Z�X������������ׂ�private
	vector<double> v;	//�z��

public://�����o�[�֐��y�уt�����h�֐�
	/***** �R���X�g���N�^���f�X�g���N�^ *****/
	CVector();										//�y01�z�R���X�g���N�^
	CVector(int m_size, double m_init=0);			//�y02�zm_size�F�z��,m_init�F�f�t�H���g��0(�����̈����͖����ł�OK)
	CVector(CVector &m_v);							//�y03�zm_v�̒��g���R�s�[���Đ�������
	CVector(vector<double> &m_v);					//�y04�zm_v�̒��g���R�s�[���Đ�������
	CVector(int m_size, double *m_v);				//�y05�zm_v�̒��g���R�s�[���Đ�������
	CVector(CVector &m_v, int m_first, int m_end);	//�y06�zm_v�̒���m_first�Ԗڂ���m_end�Ԗڂ܂ł��R�s�[���Đ���
	CVector(vector<double> &m_v, int m_first, int m_end);	//�y07�zm_v�̒���m_first�Ԗڂ���m_end�Ԗڂ܂ł��R�s�[���Đ���	
	~CVector();										//�y08�z�f�X�g���N�^ �S�v�f���폜

	/***** �̈�m�� *****/
	void	assign(int m_size, double m_init=0);		//�y10�zm_size�F�z��,m_init�F�f�t�H���g��0(�����̈����͖����ł�OK)
	void	assign(CVector &m_v, int m_first, int m_end);//�y11�zm_v�̒���m_first�Ԗڂ���m_end�Ԗڂ܂ł��R�s�[���Đ���

	/***** �v�f�֌W *****/
	int		size();								//�y20�z�z��̐���Ԃ�
	void	Add(double m_element);				//�y21�z�v�f��ǉ�����
	void	Clear();							//�y22�z�v�f�̒��g����ɂ���
	void	SetZero();							//�y23�z���g���O�ɂ���
	void	Print();							//�y24�z���g���o��

	/***** �I�[�o�[���[�h *****/
	double	&operator[](const int &pos);		//�y30�zvec.v[10]����vec[10]�ւ̏������ɕύX����
	CVector	&operator=(CVector &m_v);			//�y31�z=���Z�q�I�[�o�[���[�h
	CVector	&operator=(vector<double> &m_v);	//�y32�z=���Z�q�I�[�o�[���[�h
	CVector	operator+(CVector &m_v);			//�y33�z+���Z�q�I�[�o�[���[�h
	CVector	&operator+=(CVector &m_v);			//�y34�z+=���Z�q�I�[�o�[���[�h
	CVector	operator-(CVector &m_v);			//�y35�z-���Z�q�I�[�o�[���[�h
	CVector	&operator-=(CVector &m_v);			//�y36�z-=���Z�q�I�[�o�[���[�h
	CVector	operator-();						//�y37�z-���Z�q�I�[�o�[���[�h
	CVector	operator*(const double k);			//�y38�z*���Z�q�I�[�o�[���[�h
	friend CVector operator*(const double k, CVector &m_v);//�y39�z*���Z�q�I�[�o�[���[�h
	double	operator*(CVector &m_v);			//�y40�z*���Z�q�I�[�o�[���[�h
	CVector	operator*(CMatrix &m_mt);			//�y41�z*���Z�q�I�[�o�[���[�h

	/***** ���K�� *****/
	double	Norm();								//�y50�z�m�������v�Z����
	void	Normalize();						//�y51�z���K������

};


//#################################//
//	�s��ɂ��ẴN���X
//#################################//
class CMatrix
{
private://�����o�[�ϐ�	���A�N�Z�X������������ׂ�private
	vector<vector<double> > mt;
public:
	/***** �R���X�g���N�^���f�X�g���N�^ *****/
	CMatrix();											//�y01�z�R���X�g���N�^
	CMatrix(int m_row, int m_col, double m_init=0);		//�y02�zm_row�F�s��, m_col�F��, m_init�F�f�t�H���g��0(�����̈����͖����ł�OK)
	CMatrix(int m_rank);								//�y03�zm_rank�F�s��(�����s��̐���)
	CMatrix(CMatrix &m_mt);								//�y04�zm_mt�Ɠ����s����R�s�[���Đ���
	CMatrix(vector<vector<double> > &m_mt);				//�y05�zm_mt�Ɠ����s����R�s�[���Đ���
	CMatrix(int m_row, int m_col, double **m_mt);		//�y06�zm_mt�Ɠ����s����R�s�[���Đ���
	~CMatrix();											//�y07�z�f�X�g���N�^ �S�v�f���폜

	/***** �̈�m�� *****/
	void	assign(int m_row, int m_col, double m_init=0);	//�y10�zm_row�F�s��, m_col�F��, m_init�F�f�t�H���g��0(�����̈����͖����ł�OK)
	void	assign(int m_rank);								//�y11�zm_rank�F�s��(�����s��̐���)
	void	assign(CMatrix &m_mt);							//�y12�zm_mt�Ɠ����s����R�s�[���Đ����̈���m�ۂ���
	void	assign(vector<vector<double> > &m_mt);			//�y13�zm_mt�Ɠ����s����R�s�[���Đ����̈���m�ۂ���
	void	assign(int m_row, int m_col, double **m_mt);	//�y14�zm_mt�Ɠ����s����R�s�[���Đ����̈���m�ۂ���

	/***** �v�f�֌W *****/
	int		r_size();									//�y15�z�s����Ԃ�
	int		c_size();									//�y16�z�񐔂�Ԃ�
	void	SetR(int m_r, CVector m_v);					//�y17�zm_r�s��m_v�x�N�g����������
	void	SetC(int m_c, CVector m_v);					//�y18�zm_c���m_v�x�N�g����������
	void	SetZero();									//�y20�z���g��S��0�ɂ���
	CVector	row(int m_r);								//�y21�zm_r�s�ڂ̃x�N�g����Ԃ�
	CVector	col(int m_c);								//�y22�zm_c��ڂ̃x�N�g����Ԃ�
	void	Print();									//�y23�z���g���o��
	void	FPrint(int NameNumber=0);					//�y24�z���g��CSV�o��
#ifdef USE_CSPARSE
	cs		*ConstractCSMatrix(int m_r, int m_c,int nzmax);//�y25�zCSparse��Matrix�ɕϊ�(CSparse�g�p�҂̂�)
#endif

	/***** �I�[�o�[���[�h *****/
	vector<double> &operator[](const int m_r);			//�y30�z[]���ʃI�[�o�[���[�h
	CMatrix	&operator=(CMatrix &m_mt);					//�y31�z=���Z�q�I�[�o�[���[�h
	CMatrix	&operator=(vector<vector<double>> &m_mt);	//�y32�z=���Z�q�I�[�o�[���[�h
	CMatrix	operator+(CMatrix &m_mt);					//�y33�z+���Z�q�I�[�o�[���[�h
	CMatrix &operator+=(CMatrix &m_mt);					//�y34�z+=���Z�q�I�[�o�[���[�h
	CMatrix	operator-(CMatrix &m_mt);					//�y35�z-���Z�q�I�[�o�[���[�h
	CMatrix &operator-=(CMatrix &m_mt);					//�y36�z-=���Z�q�I�[�o�[���[�h
	CMatrix	operator-();								//�y37�z-���Z�q�I�[�o�[���[�h
	CMatrix	operator*(const double k);					//�y38�z*���Z�q�I�[�o�[���[�h
	friend CMatrix	operator*(const double k,CMatrix &m_mt);	//�y39�z*���Z�q�I�[�o�[���[�h
	CVector	operator*(CVector &m_v);				//�y40�z*���Z�q�I�[�o�[���[�h
	CMatrix	operator*(CMatrix &m_mt);				//�y41�z*���Z�q�I�[�o�[���[�h
	double &operator()(int i, int j);					//�y42�z()���ʃI�[�o�[���[�h

	/***** �s��̌v�Z *****/
	CMatrix	Remove(int m_r, int m_c);					//�y50�z��m_r�s�Ƒ�m_c�����菜���ē���s��
	CMatrix	Transpose();								//�y51�z�]�u�s��(transpose matrix)��Ԃ�
	double	Det();										//�y52�z�s��(determinant)��Ԃ�
	void	IdentifyMatrix();							//�y53�z�P�ʍs��
	CMatrix	Inverse();									//�y54�z�t�s��(inverse matrix)��Ԃ�
	void	Inverse(CMatrix& ma,CMatrix& mat, CVector& vec1, CVector& vec2); //�y55�z�v�Z speed up

	/***** LU���� *****/
	void	ludcmp(int *indx, double *d);				//�y60�zLU����
	void	lubksb(int *indx, double b[]);				//�y61�zn�̐��`�������̑g A * x = B �������֐�
	CMatrix InverseLU();								//�y62�z�t�s���Ԃ�(LU������p����)

	/***** 4�s4��ɓ���������],���i�s��v�Z *****/
	operator double*();													//�y100�z�Q�����z����P�����z���
	void	SetTranslate4d(double dx, double dy, double dz);			//�y101�z���i�s��𐶐�
	void	SetRotate4d(double Angle, double vx, double vy, double vz);	//�y102�z��]�s��𐶐�
	void	SetScale4d(double scaleX, double scaleY, double scaleZ);	//�y103�z�g��k���̍s�񐶐�
	double	Det4d();													//�y104�z�s��(determinant)��Ԃ�												
	CMatrix	Inverse4d();												//�y105�z�t�s��(inverse matrix)��Ԃ�
	void	Inverse4d(CMatrix &m_matrix);								//�y106�z�t�s��(inverse matrix)��Ԃ�
	CMatrix Translate4d(double dx, double dy, double dz);				//�y107�z���i�s���Ԃ�
	CMatrix Rotate4d(double Angle, double vx, double vy, double vz);	//�y108�z��]�s���Ԃ�
	CMatrix Scale4d(double scaleX, double scaleY, double scaleZ);		//�y109�z�g��k���̍s���Ԃ�
};

//CVector�̏o��
inline std::ostream& operator<<(std::ostream& s, CVector &A){
	for(int i=0; i<A.size(); i++){
		s<<A[i]<<" "<<::endl;
	}
	return s;
}

//CMatrix�̏o��
inline std::ostream& operator<<(std::ostream& s, CMatrix &A){
	for(int i=0; i<A.r_size(); i++){
		for(int j=0; j<A.c_size(); j++){
			s<<A[i][j]<<" ";
		}
		s<<std::endl;
	}
	return s;
}