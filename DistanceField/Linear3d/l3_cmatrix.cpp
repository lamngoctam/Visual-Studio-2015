#include "l3.h"
#include <fstream>
#include <string>
using namespace std;

//######################################//
//	CVector�̃����o�[�֐��A�t�����h�֐�	//
//######################################//
/****** �R���X�g���N�^���f�X�g���N�^ *****/

//�y01�z�R���X�g���N�^
CVector::CVector(){}

//�y02�zm_size�F�z��,m_init�F�f�t�H���g��0(�����̈����͖����ł�OK)
CVector::CVector(int m_size, double m_init)
{
	v.assign(m_size,m_init);
}

//�y03�zm_v�̒��g���R�s�[���Đ�������
CVector::CVector(CVector &m_v)
{
	v.assign(m_v.v.begin(),m_v.v.end());
}

//�y04�zm_v�̒��g���R�s�[���Đ�������
CVector::CVector(vector<double> &m_v)
{
	v.assign(m_v.begin(),m_v.end());
}

//�y05�zm_v�̒��g���R�s�[���Đ�������
CVector::CVector(int m_size, double *m_v)
{
	v.assign(m_size,0);
	for(int i=0; i<m_size; i++)	v[i] = m_v[i];
}

//�y06�zm_v�̒���m_first�Ԗڂ���m_end�Ԗڂ܂ł��R�s�[���Đ���
CVector::CVector(CVector &m_v, int m_first, int m_end)
{
	v.assign(m_end-m_first+1,0);
	for(int i=m_first;i<=m_end;i++) v[i-m_first]=m_v.v[i];
}


//�y07�zm_v�̒���m_first�Ԗڂ���m_end�Ԗڂ܂ł��R�s�[���Đ���
CVector::CVector(vector<double> &m_v, int m_first, int m_end)
{
	v.assign(m_end-m_first+1,0);
	for(int i=m_first;i<=m_end;i++) v[i-m_first]=m_v[i];
}

//�y08�z�f�X�g���N�^ �S�v�f���폜
CVector::~CVector(){v.clear();}

/**************** �̈�m�� ***************/

//�y10�zm_size�F�z��,m_init�F�f�t�H���g��0(�����̈����͖����ł�OK)
void CVector::assign(int m_size, double m_init)
{
	v.assign(m_size,m_init);
}

//�y11�zm_v�̒���m_first�Ԗڂ���m_end�Ԗڂ܂ł��R�s�[���Đ���
void CVector::assign(CVector &m_v, int m_first, int m_end)
{
	v.assign(m_end-m_first+1,0);
	for(int i=m_first;i<=m_end;i++) v[i-m_first]=m_v.v[i];
}

/***************** �v�f�֌W ***************/

//�y20�z�z��̐���Ԃ�
int CVector::size()
{
	return ((int)v.size());
}

//�y21�z�v�f��ǉ�����
void CVector::Add(double m_element)
{
	v.push_back(m_element);
}

//�y22�z�v�f�̒��g����ɂ���
void CVector::Clear()
{
	v.clear();
}

//�y23�z���g���O�ɂ���
void CVector::SetZero()
{
	for(int i=0;i<(int)v.size();i++) v[i]=0;
}

//�y24�z���g���o�͂���
void CVector::Print()
{
	cout<<"v["<<v.size()<<"]= (";
	for(int i=0;i<(int)v.size();i++) cout<<v[i]<<", ";
	cout<<")"<<endl;
}

/***************** �I�[�o�[���[�h ***************/

//�y30�z[]���� vec.v[10]����vec[10]�ւ̏������ɕύX����
double& CVector::operator[](const int &pos)
{
	return (v[pos]);
}

//�y31�z=���Z�q�I�[�o�[���[�h
CVector& CVector::operator=(CVector &m_v)
{
	register int n = (int)m_v.v.size();
	for(int i=0;i<n;i++)	v[i]=m_v.v[i];
	return *this;
}

//�y32�z=���Z�q�I�[�o�[���[�h
CVector& CVector::operator=(vector<double> &m_v)
{
	register int n = (int)m_v.size();
	for(int i=0;i<n;i++)	v[i]=m_v[i];
	return *this;
}

//�y33�z+���Z�q�I�[�o�[���[�h
CVector CVector::operator+(CVector &m_v)
{
	CVector tmp;
	register int n = (int)v.size();
	tmp.v.assign(n,0);
	for(int i=0;i<n;i++) tmp.v[i]=v[i]+m_v.v[i];
	return (tmp);
}

//�y34�z+=���Z�q�I�[�o�[���[�h
CVector& CVector::operator+=(CVector &m_v)
{
	register int n = (int)v.size();
	for(int i=0;i<n;i++) v[i] += m_v.v[i];
	return *this;
}

//�y35�z-���Z�q�I�[�o�[���[�h
CVector CVector::operator-(CVector &m_v)
{
	CVector tmp;
	register int n = (int)v.size();
	tmp.v.assign(n,0);
	for(int i=0;i<n;i++) tmp.v[i]=v[i]-m_v.v[i];
	return (tmp);
}

//�y36�z-=���Z�q�I�[�o�[���[�h
CVector& CVector::operator-=(CVector &m_v)
{
	register int n = (int)v.size();
	for(int i=0;i<n;i++) v[i] -= m_v.v[i];
	return *this;
}

//�y37�z-���Z�q�I�[�o�[���[�h�@�z��̒��̕������t�ɂ���
CVector CVector::operator-()
{
	register int n = (int)v.size();
	CVector tmp(n);
	for(int i=0;i<n;i++) tmp.v[i]=-v[i];
	return (tmp);
}

//�y38�z*���Z�q�I�[�o�[���[�h�@�X�J���[�{
CVector CVector::operator*(const double k)
{
	register int n = (int)v.size();
	CVector tmp(n);
	for(int i=0;i<n;i++) tmp.v[i]=k*v[i];
	return tmp;
}

//�y39�z*���Z�q�I�[�o�[���[�h�@�X�J���[�{
CVector operator*(const double k, CVector &m_v)
{
	register int n = (int)m_v.size();
	CVector tmp(n);
	for(int i=0;i<n;i++) tmp.v[i]=k*m_v.v[i];
	return (tmp);
}

//�y40�z*���Z�q�I�[�o�[���[�h �s�x�N�g���Ɨ�x�N�g���̐�
double CVector::operator*(CVector &m_v)
{
	double md = 0.0;
	register int n = (int)v.size();
	for(int i=0;i<n;i++) md+=v[i]*m_v.v[i];
	return (md);
}

//�y41�z*���Z�q�I�[�o�[���[�h�@matrix[][] * vector[]
CVector	CVector::operator*(CMatrix &m_mt)
{
	CVector tmp;
	register int n = (int)m_mt.c_size();
	tmp.assign(n);
	for(int j=0;j<n;j++) tmp[j]=(*this)*m_mt.col(j);
	return tmp;
}

/***************** ���K�� ***************/

//�y50�z�m�������v�Z����
double CVector::Norm()
{
	double md;
	md=0;
	register int n = (int)v.size();
	for(int i=0;i<n;i++) md+=v[i]*v[i];
	return sqrt(md);
}

//�y51�z���K������
void CVector::Normalize()
{
	double md = 0.0;
	register int n = (int)v.size();
	for(int i=0;i<n;i++) md+=pow(v[i],2);
	for(int i=0;i<n;i++) v[i]=v[i]/sqrt(md);
}


//######################################//
//	CMatrix�̃����o�[�֐��A�t�����h�֐�	//
//######################################//
/****** �R���X�g���N�^���f�X�g���N�^ *****/

//�y01�z�R���X�g���N�^
CMatrix::CMatrix(){}

//�y02�zm_row�F�s��, m_col�F��, m_init�F�f�t�H���g��0(�����̈����͖����ł�OK)
CMatrix::CMatrix(int m_row, int m_col, double m_init)
{
	vector<double> tmp(m_col,m_init);
	mt.assign(m_row,tmp);
}

//�y03�zm_rank�F�s��(�����s��̐���)
CMatrix::CMatrix(int m_rank)
{
	vector<double> tmp(m_rank,0);
	mt.assign(m_rank,tmp);
}

//�y04�zm_mt�Ɠ����s����R�s�[���Đ���
CMatrix::CMatrix(CMatrix &m_mt)
{
	vector<double> tmp((*m_mt.mt.begin()).size(),0);
	mt.assign(m_mt.mt.size(),tmp);
	int i,j;
	for(i=0;i<(int)m_mt.mt.size();i++){
		for(j=0;j<(int)(*m_mt.mt.begin()).size();j++){
			mt[i][j]=m_mt.mt[i][j];
		}
	}
}

//�y05�zm_mt�Ɠ����s����R�s�[���Đ���
CMatrix::CMatrix(vector<vector<double> > &m_mt)
{
	vector<double> tmp((*m_mt.begin()).size(),0);
	mt.assign(m_mt.size(),tmp);
	int i,j;
	for(i=0;i<(int)m_mt.size();i++){
		for(j=0;j<(int)(*m_mt.begin()).size();j++){
			mt[i][j]=m_mt[i][j];
		}
	}
}

//�y06�zm_mt�Ɠ����s����R�s�[���Đ���
CMatrix::CMatrix(int m_row, int m_col, double **m_mt)
{
	vector<double> tmp(m_col,0);
	mt.assign(m_row,tmp);
	int i,j;
	for(i=0; i<m_row; i++){
		for(j=0; j<m_col; j++){
			mt[i][j] = m_mt[i][j];
		}
	}
}

//�y07�z�f�X�g���N�^ �S�v�f���폜
CMatrix::~CMatrix(){mt.clear();}

/*************** �̈�m�� ***************/

//�y10�zm_row�F�s��, m_col�F��, m_init�F�f�t�H���g��0(�����̈����͖����ł�OK)
void CMatrix::assign(int m_row, int m_col, double m_init)
{
	vector<double> tmp(m_col,m_init);
	mt.assign(m_row,tmp);
}

//�y11�zm_rank�F�s��(�����s��̐���)
void CMatrix::assign(int m_rank)
{
	vector<double> tmp(m_rank,0);
	mt.assign(m_rank,tmp);
}

//�y12�zm_mt�Ɠ����s����R�s�[���Đ����̈���m�ۂ���
void CMatrix::assign(CMatrix &m_mt)
{
	vector<double> tmp((*m_mt.mt.begin()).size(),0);
	mt.assign(m_mt.mt.size(),tmp);
	int i,j;
	for(i=0;i<(int)m_mt.mt.size();i++){
		for(j=0;j<(int)(*m_mt.mt.begin()).size();j++){
			mt[i][j]=m_mt.mt[i][j];
		}
	}
}

//�y13�zm_mt�Ɠ����s����R�s�[���Đ����̈���m�ۂ���
void CMatrix::assign(vector<vector<double> > &m_mt)
{
	vector<double> tmp((*m_mt.begin()).size(),0);
	mt.assign(m_mt.size(),tmp);
	int i,j;
	for(i=0;i<(int)m_mt.size();i++){
		for(j=0;j<(int)(*m_mt.begin()).size();j++){
			mt[i][j]=m_mt[i][j];
		}
	}
}

//�y14�zm_mt�Ɠ����s����R�s�[���Đ����̈���m�ۂ���
void CMatrix::assign(int m_row, int m_col, double **m_mt)
{
	vector<double> tmp(m_col,0);
	mt.assign(m_row,tmp);
	int i,j;
	for(i=0; i<m_row; i++){
		for(j=0; j<m_col; j++){
			mt[i][j] = m_mt[i][j];
		}
	}
}

/*************** �v�f�֌W ***************/

//�y15�z�s����Ԃ�
int CMatrix::r_size()
{
	return((int)mt.size());
}

//�y16�z�񐔂�Ԃ�
int CMatrix::c_size()
{
	return((int)(*mt.begin()).size());
}

//�y17�zm_r�s��m_v�x�N�g����������
void CMatrix::SetR(int m_r, CVector m_v)
{
	for(int j=0;j<c_size();j++) mt[m_r][j] = m_v[j];
}

//�y18�zm_c���m_v�x�N�g����������
void CMatrix::SetC(int m_c, CVector m_v)
{
	for(int i=0; i<r_size(); i++) mt[i][m_c] = m_v[i];
}

//�y20�z���g��S��0�ɂ���
void CMatrix::SetZero()
{
	for(int i=0; i<r_size(); i++){
		for(int j=0; j<c_size(); j++){
			mt[i][j] = 0.0;
		}
	}
}

//�y21�zm_r�s�ڂ̃x�N�g����Ԃ�
CVector	CMatrix::row(int m_r)
{
	CVector tmp(mt[m_r]);
	return (tmp);
}

//�y22�zm_c��ڂ̃x�N�g����Ԃ�
CVector	CMatrix::col(int m_c)
{
	CVector tmp(r_size());
	for(int i=0;i<r_size();i++) tmp[i]=mt[i][m_c];
	return (tmp);
}

//�y23�z���g���o��
void CMatrix::Print()
{
	int i,j;
	for(i=0; i<r_size(); i++){
		for(j=0; j<c_size(); j++){
			cout<<mt[i][j]<<" ";
		}
		cout<<endl;
	}
}

//�y24�z���g��CSV�o��
void CMatrix::FPrint(int NameNumber)
{
	int i,j;
	char str[32];
	char str1[32] = "../Matrix";
	char str2[] =".csv";
	sprintf(str,"%s%d%s",str1,NameNumber,str2);	

	ofstream fout(str);

	for(i=0; i<r_size(); i++){
		for(j=0; j<c_size(); j++){
			fout<<mt[i][j]<<",";
		}
		fout<<endl;
	}
	fout.close();
}

//�y25�zCSparse��Matrix�ɕϊ�	��CSparse�g�p�҂�USE_SCPARSE���`���ĉ�����
#ifdef USE_CSPARSE
cs *CMatrix::ConstractCSMatrix(int m_r, int m_c,int nzmax)
{
	cs *tmp;
	int TotalM = 0;
	int i,j,k=1;
	tmp = cs_spalloc(m_r, m_c, nzmax, 1, 0);//csparse�p�s��m��
	tmp->p[0] = 0;

	//�s��̐���
	for(i=0; i<m_r; i++){
		for(j=0; j<m_c; j++){
			if(mt[i][j] > MACHINE_ERROR){
				tmp->i[TotalM] = j;
				tmp->x[TotalM] = mt[i][j];
				TotalM++;
			}
		}
		tmp->p[k] = TotalM;
		k++;
	}
	return (tmp);
	cs_free(tmp);
}
#endif

/*************** �I�[�o�[���[�h ***************/

//�y30�z[]���ʃI�[�o�[���[�h
vector<double> &CMatrix::operator[](int m_r)
{
	return (mt[m_r]);
}

//�y31�z=���Z�q�I�[�o�[���[�h
CMatrix& CMatrix::operator=(CMatrix &m_mt)
{
	int i,j;
	for(i=0;i<(int)mt.size();i++)
		for(j=0;j<(int)(*mt.begin()).size();j++) mt[i][j]=m_mt.mt[i][j];	
	return *this;
}

//�y32�z=���Z�q�I�[�o�[���[�h
CMatrix& CMatrix::operator=(vector<vector<double> > &m_mt)
{
	int i,j;
	for(i=0;i<(int)mt.size();i++){
		for(j=0;j<(int)(*mt.begin()).size();j++){
			mt[i][j]=m_mt[i][j];
		}
	}
	return *this;
}

//�y33�z+���Z�q�I�[�o�[���[�h
CMatrix	CMatrix::operator+(CMatrix &m_mt)
{
	int i,j;
	CMatrix tmp(r_size(),c_size());
	for(i=0;i<r_size();i++){
		for(j=0;j<c_size();j++){
			tmp.mt[i][j]=mt[i][j]+m_mt.mt[i][j];
		}
	}
	return (tmp);
}

//�y34�z+=���Z�q�I�[�o�[���[�h
CMatrix& CMatrix::operator+=(CMatrix &m_mt)
{
	int i,j;
	for(i=0;i<r_size();i++){
		for(j=0;j<c_size();j++){
			mt[i][j] +=m_mt.mt[i][j];
		}
	}
	return *this;
}

//�y35�z-���Z�q�I�[�o�[���[�h
CMatrix	CMatrix::operator-(CMatrix &m_mt)
{
	int i,j;
	CMatrix tmp(r_size(),c_size());
	for(i=0;i<r_size();i++){
		for(j=0;j<c_size();j++){
			tmp.mt[i][j]=mt[i][j]-m_mt.mt[i][j];
		}
	}
	return (tmp);
}

//�y36�z-=���Z�q�I�[�o�[���[�h
CMatrix& CMatrix::operator-=(CMatrix &m_mt)
{
	int i,j;
	for(i=0;i<r_size();i++){
		for(j=0;j<c_size();j++){
			mt[i][j] -= m_mt.mt[i][j];
		}
	}
	return *this;
}

//�y37�z-���Z�q�I�[�o�[���[�h �s����̗v�f�̕������t�ɂ���
CMatrix	CMatrix::operator-()
{
	int i,j;
	CMatrix tmp(r_size(),c_size());
	for(i=0;i<r_size();i++){
		for(j=0;j<c_size();j++){
			tmp.mt[i][j]=-mt[i][j];
		}
	}
	return (tmp);
}

//�y38�z*���Z�q�I�[�o�[���[�h
CMatrix	CMatrix::operator*(double k)
{
	int i,j;
	CMatrix tmp(r_size(),c_size());
	for(i=0;i<r_size();i++){
		for(j=0;j<c_size();j++){
			tmp.mt[i][j]=k*mt[i][j];
		}
	}
	return (tmp);
}

//�y39�z*���Z�q�I�[�o�[���[�h
CMatrix	operator*(double k, CMatrix &m_mt)
{
	int i,j;
	CMatrix tmp(m_mt.r_size(),m_mt.c_size());
	for(i=0;i<m_mt.r_size();i++){
		for(j=0;j<m_mt.c_size();j++){
			tmp.mt[i][j]=k*m_mt.mt[i][j];
		}
	}
	return (tmp);
}

//�y40�z*���Z�q�I�[�o�[���[�h
CVector	CMatrix::operator*(CVector &m_v)
{
	CVector tmp;
	tmp.assign(r_size());
	for(int i=0;i<r_size();i++) tmp[i]=(*this).row(i)*m_v;
	return (tmp);
}

//�y41�z*���Z�q�I�[�o�[���[�h
CMatrix	CMatrix::operator*(CMatrix &m_mt)
{
	CMatrix tmp;
	int i,j;
	tmp.assign(r_size(),m_mt.c_size());
	for(i=0;i<r_size();i++){
		for(j=0;j<m_mt.c_size();j++){
			tmp.mt[i][j]=(*this).row(i)*m_mt.col(j);
		}
	}
	return tmp;
}

//�y42�z()���ʃI�[�o�[���[�h
double& CMatrix::operator()(int i, int j)
{
	return(mt[i][j]);
}

/*************** �s��̌v�Z ***************/

//�y50�z��m_r�s�Ƒ�m_c�����菜���ē���s��@[n-1][m-1]�s��ƂȂ�
CMatrix	CMatrix::Remove(int m_r, int m_c)
{
	CMatrix tmp(r_size()-1,c_size()-1);
	int i,j;
	for(i=0;i<m_r;i++)
		for(j=0;j<m_c;j++) tmp.mt[i][j]=mt[i][j];
	for(i=m_r;i<r_size()-1;i++)
		for(j=0;j<m_c;j++) tmp.mt[i][j]=mt[i+1][j];
	for(i=0;i<m_r;i++)
		for(j=m_c;j<c_size()-1;j++) tmp.mt[i][j]=mt[i][j+1];
	for(i=m_r;i<r_size()-1;i++)
		for(j=m_c;j<c_size()-1;j++) tmp.mt[i][j]=mt[i+1][j+1];
	return (tmp);
}

//�y51�z�]�u�s��(transpose matrix)��Ԃ�
CMatrix	CMatrix::Transpose()
{
	CMatrix tmp(c_size(),r_size());
	int i,j;
	for(i=0;i<c_size();i++)
		for(j=0;j<r_size();j++) tmp.mt[i][j]=mt[j][i];
	return (tmp);

}

//�y52�z�s��(determinant)��Ԃ�
double	CMatrix::Det()
{
	double d;
	if(r_size()==1) d=mt[0][0];
	else
	{
		int j;
		d=0;
		for(j=0;j<r_size();j++)
			d+=pow(-1.0,j)*mt[0][j]*(*this).Remove(0,j).Det();
	}
	return d;
}

//�y53�z�P�ʍs��
void CMatrix::IdentifyMatrix()
{
	SetZero();
	int n = min(r_size(),c_size());
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){ 
			if(i==j){
				mt[i][j]=1;
			}
		}
	}
}

//�y54�z�t�s��(inverse matrix)��Ԃ�
CMatrix	CMatrix::Inverse()
{
	CMatrix ma,mat(mt),m_zero(r_size());
	CVector vec1(r_size()),vec2(r_size());
	ma.assign(r_size());
	ma.IdentifyMatrix();

	int i,j;
	for(i=0;i<r_size()-1;i++)
	{
		if(mat[i][i]==0)
		{
			for(j=i+1;j<r_size();j++)
			{
				if(mat[j][i]!=0)
				{
					vec1=mat.row(i); vec2=mat.row(j);
					mat.SetR(i,vec2); mat.SetR(j,vec1);
					vec1=ma.row(i); vec2=ma.row(j);
					ma.SetR(i,vec2); ma.SetR(j,vec1);
					break;
				}
			}
			if(j==r_size()) return m_zero;
		}

		for(j=i+1;j<r_size();j++)
		{
			vec1=(-mat[j][i]/mat[i][i])*mat.row(i)+mat.row(j);
			vec2=(-mat[j][i]/mat[i][i])*ma.row(i)+ma.row(j);
			mat.SetR(j,vec1);
			ma.SetR(j,vec2);
		}
	}

	if(mat[r_size()-1][r_size()-1]==0) return m_zero;
	else
	{
		for(i=r_size()-1;i>0;i--)
		{
			for(j=i-1;j>=0;j--)
			{
				vec1=(-mat[j][i]/mat[i][i])*mat.row(i)+mat.row(j);
				vec2=(-mat[j][i]/mat[i][i])*ma.row(i)+ma.row(j);
				mat.SetR(j,vec1);
				ma.SetR(j,vec2);
			}
		}
	}

	for(i=0;i<r_size();i++)
	{
		for(j=0;j<r_size();j++) {ma.mt[i][j]=ma.mt[i][j]/mat.mt[i][i];}
	}
	return ma;
}

//�y55�z�v�Z speed up
void CMatrix::Inverse(CMatrix& ma,CMatrix& mat, CVector& vec1, CVector& vec2)
{
	ma.IdentifyMatrix();
	mat=mt;

	int i,j;
	for(i=0;i<r_size()-1;i++)
	{
		if(mat[i][i]==0)
		{
			for(j=i+1;j<r_size();j++)
			{
				if(mat[j][i]!=0)
				{
					vec1=mat.row(i); vec2=mat.row(j);
					mat.SetR(i,vec2); mat.SetR(j,vec1);
					vec1=ma.row(i); vec2=ma.row(j);
					ma.SetR(i,vec2); ma.SetR(j,vec1);
					break;
				}
			}
			if(j==r_size()) return ;
		}

		for(j=i+1;j<r_size();j++)
		{
			vec1=(-mat[j][i]/mat[i][i])*mat.row(i)+mat.row(j);
			vec2=(-mat[j][i]/mat[i][i])*ma.row(i)+ma.row(j);
			mat.SetR(j,vec1);
			ma.SetR(j,vec2);
		}
	}

	if(mat[r_size()-1][r_size()-1]==0) return ;
	else
	{
		for(i=r_size()-1;i>0;i--)
		{
			for(j=i-1;j>=0;j--)
			{
				vec1=(-mat[j][i]/mat[i][i])*mat.row(i)+mat.row(j);
				vec2=(-mat[j][i]/mat[i][i])*ma.row(i)+ma.row(j);
				mat.SetR(j,vec1);
				ma.SetR(j,vec2);
			}
		}
	}

	for(i=0;i<r_size();i++)
	{
		for(j=0;j<r_size();j++) {ma.mt[i][j]=ma.mt[i][j]/mat.mt[i][i];}
	}
}

//�y60�zLU����
void CMatrix::ludcmp(int *indx, double *d)
{
	//input a[n�~n�s��],n,
	//output a(�㏑��),indx[���s1��],d(�s�����񐔁@�����Ȃ�1��Ȃ�-1)
	int n = r_size();
	int i,imax,j,k;
	double big,dum,sum,temp;
	double *vv;				//vv�͊e�s�̈Öق̃X�P�[�����O���L�^����

	vv = new double[n];
	*d  = 1.0;				//�܂��s���������Ă��Ȃ�

	for(i=0; i<n; i++){		//�s�ɂ��ă��[�v���A�Öق̃X�P�[�����O���L�^
		big = 0.0;

		for(j=0; j<n; j++){
			if((temp=fabs(mt[i][j])) > big){
				big = temp;
			}
		}

		if(big == 0.0){
			cout<<"error"<<endl;	//�ő�̗v�f��0�Ȃ���ٍs��ł���
			break;
		}

		vv[i] = 1.0/big;			//�X�P�[�����O���L�^����
	}

	for(j=0; j<n; j++){				//Crout�@,��ɂ��Ẵ��[�v�@������2.3.12��i=j�ȊO
		for(i=0; i<j; i++){
			sum=mt[i][j];
			for(k=0; k<i; k++){
				sum -= mt[i][k]*mt[k][j];
			}
			mt[i][j]=sum;
		}

		big=0.0;				//�ő�̃s�{�b�g�v�f��T������

		for(i=j; i<n; i++){		//��2.3.12��i=j�Ǝ�2.3.13��i=j+1,...,N
			sum=mt[i][j];
			for(k=0; k<j; k++){
				sum -= mt[i][k]*mt[k][j];
			}

			mt[i][j]=sum;

			if( (dum=vv[i]*fabs(sum)) >= big){	//�s�{�b�g�̂悳�͍��܂ł̍ő�l�ȏォ�H
				big = dum;
				imax= i;
			}
		}
		if(j != imax){				//�s�����̕K�v�́H�@
			for(k=0; k<n; k++){		//����
				dum=mt[imax][k];
				mt[imax][k]=mt[j][k];
				mt[j][k]=dum;
			}

			*d = -(*d);				//������d�̋���ς���
			vv[imax]=vv[j];			//�X�P�[�����q����������
		}

		indx[j]=imax;

		if(mt[j][j] == 0.0){			//�����s�{�b�g�v�f��0�Ȃ�s��͓��قł���B
			mt[j][j] = MACHINE_ERROR;	//���ٍs��̗��p�@��TINY��0�ɂ���΂悢���Ƃ�����
		}

		if(j != n-1){
			dum=1.0/(mt[j][j]);
			for(i=j+1; i<n; i++){
				mt[i][j] *= dum;
			}
		}
	}							//���̗��ЂÂ��ɂ�����
	delete[] vv;
}

//�y61�zn�̐��`�������̑g A * x = B �������֐�
void CMatrix::lubksb(int *indx, double b[])
{
	//n�̐��`�������̑g A * x = B �������B���͍s��A��ludcmp�ŋ��߂�A��LU����
	//���͂���x�N�g��indx[1,...,n]��ludcmp���Ԃ��s�������ł���B
	//	input	b[](�E�ӂ̃x�N�g��B),indx��ludcmp����̍s�������
	//	output	x[](���x�N�g��x)
	int n = r_size();
	int i,ii=0,ip,j;
	double sum;

	for(i=0; i<n; i++){			//ii�����Ȃ�A�����b�̍ŏ���0�łȂ��v�f�̓Y�����ł���B
		ip	= indx[i];			//�s���������ɖ߂��Ȃ��玮(2.3.6)�̑O�i������s��
		sum	= b[ip];
		b[ip]=b[i];

		if(ii != 0){
			for(j=ii-1; j<i; j++){
				sum -= mt[i][j]*b[j];
			}

		}else if(sum != 0){			//���v�f�ɏo������B����ȍ~�͏�̃��[�v�Řa�����߂Ȃ���΂Ȃ�Ȃ�
			ii = i+1;

		}
		b[i]=sum;
	}

	for(i=n-1; i>=0; i--){		//��(2.3.7)�̌�ޑ��
		sum=b[i];
		for(j=i+1; j<n; j++){
			sum -= mt[i][j]*b[j];
		}
		b[i]=sum/mt[i][i];		//���x�N�g�� x �̐�����ۑ������I
	}
}

//�y62�z�t�s���Ԃ�(LU������p����)
CMatrix CMatrix::InverseLU()
{
	int i,j;
	int *indx = new int [r_size()];
	double d,*col;
	col = new double[r_size()];
	CMatrix tmp(r_size(),c_size());
	ludcmp(indx,&d);

	for(j=0; j<r_size(); j++){
		for(i=0; i<r_size(); i++)	col[i] = 0.0;
		col[j] = 1.0;
		lubksb(indx,col);
		for(i=0; i<r_size(); i++)	tmp.mt[i][j] = col[i];
	}
	return (tmp);
}


/********** 4�s4��ɓ���������],���i�s��v�Z **********/

//�y100�z�Q�����z����P�����z���
CMatrix::operator double*()
{
	static double tmp[16];
	int i,j,k=0;
	for(j=0; j<4; j++){
		for(i=0; i<4; i++)
		{
			tmp[k]=mt[i][j];
			k++;
		}
	}
	return (tmp);
}

//�y101�z���i�s��𐶐�
void CMatrix::SetTranslate4d(double dx, double dy, double dz)
{
	mt[0][0]=1; mt[0][1]=0; mt[0][2]=0; mt[0][3]=dx;
	mt[1][0]=0; mt[1][1]=1; mt[1][2]=0; mt[1][3]=dy;
	mt[2][0]=0; mt[2][1]=0; mt[2][2]=1; mt[2][3]=dz;
	mt[3][0]=0; mt[3][1]=0; mt[3][2]=0; mt[3][3]=1;
}

//�y102�z��]�s��𐶐�
void CMatrix::SetRotate4d(double Angle, double vx, double vy, double vz)
{
	double v[3];
	v[0]=vx/sqrt(vx*vx+vy*vy+vz*vz); 
	v[1]=vy/sqrt(vx*vx+vy*vy+vz*vz); 
	v[2]=vz/sqrt(vx*vx+vy*vy+vz*vz);

	mt[0][0]=v[0]*v[0]*(1-cos(Angle))+cos(Angle);
	mt[0][1]=v[0]*v[1]*(1-cos(Angle))-v[2]*sin(Angle);
	mt[0][2]=v[0]*v[2]*(1-cos(Angle))+v[1]*sin(Angle);

	mt[1][0]=v[0]*v[1]*(1-cos(Angle))+v[2]*sin(Angle);
	mt[1][1]=v[1]*v[1]*(1-cos(Angle))+cos(Angle);
	mt[1][2]=v[2]*v[1]*(1-cos(Angle))-v[0]*sin(Angle);

	mt[2][0]=v[0]*v[2]*(1-cos(Angle))-v[1]*sin(Angle);
	mt[2][1]=v[1]*v[2]*(1-cos(Angle))+v[0]*sin(Angle);
	mt[2][2]=v[2]*v[2]*(1-cos(Angle))+cos(Angle);

	mt[0][3]=0; mt[1][3]=0; mt[2][3]=0;
	mt[3][0]=0; mt[3][1]=0; mt[3][2]=0; mt[3][3]=1;
}

//�y103�z�g��k���̍s�񐶐�
void CMatrix::SetScale4d(double scaleX, double scaleY, double scaleZ)
{
	mt[0][0]=scaleX; mt[0][1]=0;	  mt[0][2]=0;      mt[0][3]=0;
	mt[1][0]=0;		 mt[1][1]=scaleY; mt[1][2]=0;      mt[1][3]=0;
	mt[2][0]=0;		 mt[2][1]=0;      mt[2][2]=scaleZ; mt[2][3]=0;
	mt[3][0]=0;		 mt[3][1]=0;      mt[3][2]=0;      mt[3][3]=1;
}

//�y104�z�s��(determinant)��Ԃ�												
double	CMatrix::Det4d()
{
	return(mt[0][0]*mt[1][1]*mt[2][2]*mt[3][3]-mt[0][0]*mt[1][1]*mt[2][3]*mt[3][2]-mt[0][0]*mt[2][1]*mt[1][2]*mt[3][3]+mt[0][0]*mt[2][1]*mt[1][3]*mt[3][2]+mt[0][0]*mt[3][1]*mt[1][2]*mt[2][3]-mt[0][0]*mt[3][1]*mt[1][3]*mt[2][2]-mt[1][0]*mt[0][1]*mt[2][2]*mt[3][3]+mt[1][0]*mt[0][1]*mt[2][3]*mt[3][2]+mt[1][0]*mt[2][1]*mt[0][2]*mt[3][3]-mt[1][0]*mt[2][1]*mt[0][3]*mt[3][2]-mt[1][0]*mt[3][1]*mt[0][2]*mt[2][3]+mt[1][0]*mt[3][1]*mt[0][3]*mt[2][2]+mt[2][0]*mt[0][1]*mt[1][2]*mt[3][3]-mt[2][0]*mt[0][1]*mt[1][3]*mt[3][2]-mt[2][0]*mt[1][1]*mt[0][2]*mt[3][3]+mt[2][0]*mt[1][1]*mt[0][3]*mt[3][2]+mt[2][0]*mt[3][1]*mt[0][2]*mt[1][3]-mt[2][0]*mt[3][1]*mt[0][3]*mt[1][2]-mt[3][0]*mt[0][1]*mt[1][2]*mt[2][3]+mt[3][0]*mt[0][1]*mt[1][3]*mt[2][2]+mt[3][0]*mt[1][1]*mt[0][2]*mt[2][3]-mt[3][0]*mt[1][1]*mt[0][3]*mt[2][2]-mt[3][0]*mt[2][1]*mt[0][2]*mt[1][3]+mt[3][0]*mt[2][1]*mt[0][3]*mt[1][2]);
}

//�y105�z�t�s��(inverse matrix)��Ԃ�
CMatrix	CMatrix::Inverse4d()
{
	CMatrix tmp(4);
	double  determinant = Det4d();

	tmp.mt[0][0]=(mt[1][1]*mt[2][2]*mt[3][3]-mt[1][1]*mt[2][3]*mt[3][2]-mt[2][1]*mt[1][2]*mt[3][3]+mt[2][1]*mt[1][3]*mt[3][2]+mt[3][1]*mt[1][2]*mt[2][3]-mt[3][1]*mt[1][3]*mt[2][2])/determinant;
	tmp.mt[0][1]=(-mt[0][1]*mt[2][2]*mt[3][3]+mt[0][1]*mt[2][3]*mt[3][2]+mt[2][1]*mt[0][2]*mt[3][3]-mt[2][1]*mt[0][3]*mt[3][2]-mt[3][1]*mt[0][2]*mt[2][3]+mt[3][1]*mt[0][3]*mt[2][2])/determinant;
	tmp.mt[0][2]=(mt[0][1]*mt[1][2]*mt[3][3]-mt[0][1]*mt[1][3]*mt[3][2]-mt[1][1]*mt[0][2]*mt[3][3]+mt[1][1]*mt[0][3]*mt[3][2]+mt[3][1]*mt[0][2]*mt[1][3]-mt[3][1]*mt[0][3]*mt[1][2])/determinant;
	tmp.mt[0][3]=(-mt[0][1]*mt[1][2]*mt[2][3]+mt[0][1]*mt[1][3]*mt[2][2]+mt[1][1]*mt[0][2]*mt[2][3]-mt[1][1]*mt[0][3]*mt[2][2]-mt[2][1]*mt[0][2]*mt[1][3]+mt[2][1]*mt[0][3]*mt[1][2])/determinant;
	tmp.mt[1][0]=(-mt[1][0]*mt[2][2]*mt[3][3]+mt[1][0]*mt[2][3]*mt[3][2]+mt[2][0]*mt[1][2]*mt[3][3]-mt[2][0]*mt[1][3]*mt[3][2]-mt[3][0]*mt[1][2]*mt[2][3]+mt[3][0]*mt[1][3]*mt[2][2])/determinant;
	tmp.mt[1][1]=(mt[0][0]*mt[2][2]*mt[3][3]-mt[0][0]*mt[2][3]*mt[3][2]-mt[2][0]*mt[0][2]*mt[3][3]+mt[2][0]*mt[0][3]*mt[3][2]+mt[3][0]*mt[0][2]*mt[2][3]-mt[3][0]*mt[0][3]*mt[2][2])/determinant;
	tmp.mt[1][2]=(-mt[0][0]*mt[1][2]*mt[3][3]+mt[0][0]*mt[1][3]*mt[3][2]+mt[1][0]*mt[0][2]*mt[3][3]-mt[1][0]*mt[0][3]*mt[3][2]-mt[3][0]*mt[0][2]*mt[1][3]+mt[3][0]*mt[0][3]*mt[1][2])/determinant;
	tmp.mt[1][3]=(mt[0][0]*mt[1][2]*mt[2][3]-mt[0][0]*mt[1][3]*mt[2][2]-mt[1][0]*mt[0][2]*mt[2][3]+mt[1][0]*mt[0][3]*mt[2][2]+mt[2][0]*mt[0][2]*mt[1][3]-mt[2][0]*mt[0][3]*mt[1][2])/determinant;
	tmp.mt[2][0]=(mt[1][0]*mt[2][1]*mt[3][3]-mt[1][0]*mt[2][3]*mt[3][1]-mt[2][0]*mt[1][1]*mt[3][3]+mt[2][0]*mt[1][3]*mt[3][1]+mt[3][0]*mt[1][1]*mt[2][3]-mt[3][0]*mt[1][3]*mt[2][1])/determinant;
	tmp.mt[2][1]=(-mt[0][0]*mt[2][1]*mt[3][3]+mt[0][0]*mt[2][3]*mt[3][1]+mt[2][0]*mt[0][1]*mt[3][3]-mt[2][0]*mt[0][3]*mt[3][1]-mt[3][0]*mt[0][1]*mt[2][3]+mt[3][0]*mt[0][3]*mt[2][1])/determinant;
	tmp.mt[2][2]=(mt[0][0]*mt[1][1]*mt[3][3]-mt[0][0]*mt[1][3]*mt[3][1]-mt[1][0]*mt[0][1]*mt[3][3]+mt[1][0]*mt[0][3]*mt[3][1]+mt[3][0]*mt[0][1]*mt[1][3]-mt[3][0]*mt[0][3]*mt[1][1])/determinant;
	tmp.mt[2][3]=(-mt[0][0]*mt[1][1]*mt[2][3]+mt[0][0]*mt[1][3]*mt[2][1]+mt[1][0]*mt[0][1]*mt[2][3]-mt[1][0]*mt[0][3]*mt[2][1]-mt[2][0]*mt[0][1]*mt[1][3]+mt[2][0]*mt[0][3]*mt[1][1])/determinant;
	tmp.mt[3][0]=(-mt[1][0]*mt[2][1]*mt[3][2]+mt[1][0]*mt[2][2]*mt[3][1]+mt[2][0]*mt[1][1]*mt[3][2]-mt[2][0]*mt[1][2]*mt[3][1]-mt[3][0]*mt[1][1]*mt[2][2]+mt[3][0]*mt[1][2]*mt[2][1])/determinant;
	tmp.mt[3][1]=(mt[0][0]*mt[2][1]*mt[3][2]-mt[0][0]*mt[2][2]*mt[3][1]-mt[2][0]*mt[0][1]*mt[3][2]+mt[2][0]*mt[0][2]*mt[3][1]+mt[3][0]*mt[0][1]*mt[2][2]-mt[3][0]*mt[0][2]*mt[2][1])/determinant;
	tmp.mt[3][2]=(-mt[0][0]*mt[1][1]*mt[3][2]+mt[0][0]*mt[1][2]*mt[3][1]+mt[1][0]*mt[0][1]*mt[3][2]-mt[1][0]*mt[0][2]*mt[3][1]-mt[3][0]*mt[0][1]*mt[1][2]+mt[3][0]*mt[0][2]*mt[1][1])/determinant;
	tmp.mt[3][3]=(mt[0][0]*mt[1][1]*mt[2][2]-mt[0][0]*mt[1][2]*mt[2][1]-mt[1][0]*mt[0][1]*mt[2][2]+mt[1][0]*mt[0][2]*mt[2][1]+mt[2][0]*mt[0][1]*mt[1][2]-mt[2][0]*mt[0][2]*mt[1][1])/determinant;

	return (tmp);
}

//�y106�z�t�s��(inverse matrix)��Ԃ�
void CMatrix::Inverse4d(CMatrix &m_matrix)
{
	double  determinant = Det4d();

	m_matrix.mt[0][0]=(mt[1][1]*mt[2][2]*mt[3][3]-mt[1][1]*mt[2][3]*mt[3][2]-mt[2][1]*mt[1][2]*mt[3][3]+mt[2][1]*mt[1][3]*mt[3][2]+mt[3][1]*mt[1][2]*mt[2][3]-mt[3][1]*mt[1][3]*mt[2][2])/determinant;
	m_matrix.mt[0][1]=(-mt[0][1]*mt[2][2]*mt[3][3]+mt[0][1]*mt[2][3]*mt[3][2]+mt[2][1]*mt[0][2]*mt[3][3]-mt[2][1]*mt[0][3]*mt[3][2]-mt[3][1]*mt[0][2]*mt[2][3]+mt[3][1]*mt[0][3]*mt[2][2])/determinant;
	m_matrix.mt[0][2]=(mt[0][1]*mt[1][2]*mt[3][3]-mt[0][1]*mt[1][3]*mt[3][2]-mt[1][1]*mt[0][2]*mt[3][3]+mt[1][1]*mt[0][3]*mt[3][2]+mt[3][1]*mt[0][2]*mt[1][3]-mt[3][1]*mt[0][3]*mt[1][2])/determinant;
	m_matrix.mt[0][3]=(-mt[0][1]*mt[1][2]*mt[2][3]+mt[0][1]*mt[1][3]*mt[2][2]+mt[1][1]*mt[0][2]*mt[2][3]-mt[1][1]*mt[0][3]*mt[2][2]-mt[2][1]*mt[0][2]*mt[1][3]+mt[2][1]*mt[0][3]*mt[1][2])/determinant;
	m_matrix.mt[1][0]=(-mt[1][0]*mt[2][2]*mt[3][3]+mt[1][0]*mt[2][3]*mt[3][2]+mt[2][0]*mt[1][2]*mt[3][3]-mt[2][0]*mt[1][3]*mt[3][2]-mt[3][0]*mt[1][2]*mt[2][3]+mt[3][0]*mt[1][3]*mt[2][2])/determinant;
	m_matrix.mt[1][1]=(mt[0][0]*mt[2][2]*mt[3][3]-mt[0][0]*mt[2][3]*mt[3][2]-mt[2][0]*mt[0][2]*mt[3][3]+mt[2][0]*mt[0][3]*mt[3][2]+mt[3][0]*mt[0][2]*mt[2][3]-mt[3][0]*mt[0][3]*mt[2][2])/determinant;
	m_matrix.mt[1][2]=(-mt[0][0]*mt[1][2]*mt[3][3]+mt[0][0]*mt[1][3]*mt[3][2]+mt[1][0]*mt[0][2]*mt[3][3]-mt[1][0]*mt[0][3]*mt[3][2]-mt[3][0]*mt[0][2]*mt[1][3]+mt[3][0]*mt[0][3]*mt[1][2])/determinant;
	m_matrix.mt[1][3]=(mt[0][0]*mt[1][2]*mt[2][3]-mt[0][0]*mt[1][3]*mt[2][2]-mt[1][0]*mt[0][2]*mt[2][3]+mt[1][0]*mt[0][3]*mt[2][2]+mt[2][0]*mt[0][2]*mt[1][3]-mt[2][0]*mt[0][3]*mt[1][2])/determinant;
	m_matrix.mt[2][0]=(mt[1][0]*mt[2][1]*mt[3][3]-mt[1][0]*mt[2][3]*mt[3][1]-mt[2][0]*mt[1][1]*mt[3][3]+mt[2][0]*mt[1][3]*mt[3][1]+mt[3][0]*mt[1][1]*mt[2][3]-mt[3][0]*mt[1][3]*mt[2][1])/determinant;
	m_matrix.mt[2][1]=(-mt[0][0]*mt[2][1]*mt[3][3]+mt[0][0]*mt[2][3]*mt[3][1]+mt[2][0]*mt[0][1]*mt[3][3]-mt[2][0]*mt[0][3]*mt[3][1]-mt[3][0]*mt[0][1]*mt[2][3]+mt[3][0]*mt[0][3]*mt[2][1])/determinant;
	m_matrix.mt[2][2]=(mt[0][0]*mt[1][1]*mt[3][3]-mt[0][0]*mt[1][3]*mt[3][1]-mt[1][0]*mt[0][1]*mt[3][3]+mt[1][0]*mt[0][3]*mt[3][1]+mt[3][0]*mt[0][1]*mt[1][3]-mt[3][0]*mt[0][3]*mt[1][1])/determinant;
	m_matrix.mt[2][3]=(-mt[0][0]*mt[1][1]*mt[2][3]+mt[0][0]*mt[1][3]*mt[2][1]+mt[1][0]*mt[0][1]*mt[2][3]-mt[1][0]*mt[0][3]*mt[2][1]-mt[2][0]*mt[0][1]*mt[1][3]+mt[2][0]*mt[0][3]*mt[1][1])/determinant;
	m_matrix.mt[3][0]=(-mt[1][0]*mt[2][1]*mt[3][2]+mt[1][0]*mt[2][2]*mt[3][1]+mt[2][0]*mt[1][1]*mt[3][2]-mt[2][0]*mt[1][2]*mt[3][1]-mt[3][0]*mt[1][1]*mt[2][2]+mt[3][0]*mt[1][2]*mt[2][1])/determinant;
	m_matrix.mt[3][1]=(mt[0][0]*mt[2][1]*mt[3][2]-mt[0][0]*mt[2][2]*mt[3][1]-mt[2][0]*mt[0][1]*mt[3][2]+mt[2][0]*mt[0][2]*mt[3][1]+mt[3][0]*mt[0][1]*mt[2][2]-mt[3][0]*mt[0][2]*mt[2][1])/determinant;
	m_matrix.mt[3][2]=(-mt[0][0]*mt[1][1]*mt[3][2]+mt[0][0]*mt[1][2]*mt[3][1]+mt[1][0]*mt[0][1]*mt[3][2]-mt[1][0]*mt[0][2]*mt[3][1]-mt[3][0]*mt[0][1]*mt[1][2]+mt[3][0]*mt[0][2]*mt[1][1])/determinant;
	m_matrix.mt[3][3]=(mt[0][0]*mt[1][1]*mt[2][2]-mt[0][0]*mt[1][2]*mt[2][1]-mt[1][0]*mt[0][1]*mt[2][2]+mt[1][0]*mt[0][2]*mt[2][1]+mt[2][0]*mt[0][1]*mt[1][2]-mt[2][0]*mt[0][2]*mt[1][1])/determinant;
}

//�y107�z���i�s���Ԃ�
CMatrix CMatrix::Translate4d(double dx, double dy, double dz)
{
	CMatrix tmp(4);
	tmp[0][0]=1; tmp[0][1]=0; tmp[0][2]=0; tmp[0][3]=dx;
	tmp[1][0]=0; tmp[1][1]=1; tmp[1][2]=0; tmp[1][3]=dy;
	tmp[2][0]=0; tmp[2][1]=0; tmp[2][2]=1; tmp[2][3]=dz;
	tmp[3][0]=0; tmp[3][1]=0; tmp[3][2]=0; tmp[3][3]=1;
	return (tmp);
}

//�y108�z��]�s���Ԃ�
CMatrix CMatrix::Rotate4d(double Angle, double vx, double vy, double vz)
{
	CMatrix tmp(4);
	double v[3];
	v[0]=vx/sqrt(vx*vx+vy*vy+vz*vz); 
	v[1]=vy/sqrt(vx*vx+vy*vy+vz*vz); 
	v[2]=vz/sqrt(vx*vx+vy*vy+vz*vz);

	tmp[0][0]=v[0]*v[0]*(1-cos(Angle))+cos(Angle);
	tmp[0][1]=v[0]*v[1]*(1-cos(Angle))-v[2]*sin(Angle);
	tmp[0][2]=v[0]*v[2]*(1-cos(Angle))+v[1]*sin(Angle);

	tmp[1][0]=v[0]*v[1]*(1-cos(Angle))+v[2]*sin(Angle);
	tmp[1][1]=v[1]*v[1]*(1-cos(Angle))+cos(Angle);
	tmp[1][2]=v[2]*v[1]*(1-cos(Angle))-v[0]*sin(Angle);

	tmp[2][0]=v[0]*v[2]*(1-cos(Angle))-v[1]*sin(Angle);
	tmp[2][1]=v[1]*v[2]*(1-cos(Angle))+v[0]*sin(Angle);
	tmp[2][2]=v[2]*v[2]*(1-cos(Angle))+cos(Angle);

	tmp[0][3]=0; tmp[1][3]=0; tmp[2][3]=0;
	tmp[3][0]=0; tmp[3][1]=0; tmp[3][2]=0; tmp[3][3]=1;
	return (tmp);
}

//�y109�z�g��k���̍s���Ԃ�
CMatrix CMatrix::Scale4d(double scaleX, double scaleY, double scaleZ)
{
	CMatrix tmp(4);
	tmp[0][0]=scaleX;	tmp[0][1]=0;	  tmp[0][2]=0;      tmp[0][3]=0;
	tmp[1][0]=0;		tmp[1][1]=scaleY; tmp[1][2]=0;      tmp[1][3]=0;
	tmp[2][0]=0;		tmp[2][1]=0;      tmp[2][2]=scaleZ; tmp[2][3]=0;
	tmp[3][0]=0;		tmp[3][1]=0;      tmp[3][2]=0;      tmp[3][3]=1;
	return (tmp);
}