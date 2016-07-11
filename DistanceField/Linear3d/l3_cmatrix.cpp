#include "l3.h"
#include <fstream>
#include <string>
using namespace std;

//######################################//
//	CVectorのメンバー関数、フレンド関数	//
//######################################//
/****** コンストラクタ＆デストラクタ *****/

//【01】コンストラクタ
CVector::CVector(){}

//【02】m_size：配列数,m_init：デフォルトで0(ここの引数は無しでもOK)
CVector::CVector(int m_size, double m_init)
{
	v.assign(m_size,m_init);
}

//【03】m_vの中身をコピーして生成する
CVector::CVector(CVector &m_v)
{
	v.assign(m_v.v.begin(),m_v.v.end());
}

//【04】m_vの中身をコピーして生成する
CVector::CVector(vector<double> &m_v)
{
	v.assign(m_v.begin(),m_v.end());
}

//【05】m_vの中身をコピーして生成する
CVector::CVector(int m_size, double *m_v)
{
	v.assign(m_size,0);
	for(int i=0; i<m_size; i++)	v[i] = m_v[i];
}

//【06】m_vの中のm_first番目からm_end番目までをコピーして生成
CVector::CVector(CVector &m_v, int m_first, int m_end)
{
	v.assign(m_end-m_first+1,0);
	for(int i=m_first;i<=m_end;i++) v[i-m_first]=m_v.v[i];
}


//【07】m_vの中のm_first番目からm_end番目までをコピーして生成
CVector::CVector(vector<double> &m_v, int m_first, int m_end)
{
	v.assign(m_end-m_first+1,0);
	for(int i=m_first;i<=m_end;i++) v[i-m_first]=m_v[i];
}

//【08】デストラクタ 全要素を削除
CVector::~CVector(){v.clear();}

/**************** 領域確保 ***************/

//【10】m_size：配列数,m_init：デフォルトで0(ここの引数は無しでもOK)
void CVector::assign(int m_size, double m_init)
{
	v.assign(m_size,m_init);
}

//【11】m_vの中のm_first番目からm_end番目までをコピーして生成
void CVector::assign(CVector &m_v, int m_first, int m_end)
{
	v.assign(m_end-m_first+1,0);
	for(int i=m_first;i<=m_end;i++) v[i-m_first]=m_v.v[i];
}

/***************** 要素関係 ***************/

//【20】配列の数を返す
int CVector::size()
{
	return ((int)v.size());
}

//【21】要素を追加する
void CVector::Add(double m_element)
{
	v.push_back(m_element);
}

//【22】要素の中身を空にする
void CVector::Clear()
{
	v.clear();
}

//【23】中身を０にする
void CVector::SetZero()
{
	for(int i=0;i<(int)v.size();i++) v[i]=0;
}

//【24】中身を出力する
void CVector::Print()
{
	cout<<"v["<<v.size()<<"]= (";
	for(int i=0;i<(int)v.size();i++) cout<<v[i]<<", ";
	cout<<")"<<endl;
}

/***************** オーバーロード ***************/

//【30】[]括弧 vec.v[10]からvec[10]への書き方に変更する
double& CVector::operator[](const int &pos)
{
	return (v[pos]);
}

//【31】=演算子オーバーロード
CVector& CVector::operator=(CVector &m_v)
{
	register int n = (int)m_v.v.size();
	for(int i=0;i<n;i++)	v[i]=m_v.v[i];
	return *this;
}

//【32】=演算子オーバーロード
CVector& CVector::operator=(vector<double> &m_v)
{
	register int n = (int)m_v.size();
	for(int i=0;i<n;i++)	v[i]=m_v[i];
	return *this;
}

//【33】+演算子オーバーロード
CVector CVector::operator+(CVector &m_v)
{
	CVector tmp;
	register int n = (int)v.size();
	tmp.v.assign(n,0);
	for(int i=0;i<n;i++) tmp.v[i]=v[i]+m_v.v[i];
	return (tmp);
}

//【34】+=演算子オーバーロード
CVector& CVector::operator+=(CVector &m_v)
{
	register int n = (int)v.size();
	for(int i=0;i<n;i++) v[i] += m_v.v[i];
	return *this;
}

//【35】-演算子オーバーロード
CVector CVector::operator-(CVector &m_v)
{
	CVector tmp;
	register int n = (int)v.size();
	tmp.v.assign(n,0);
	for(int i=0;i<n;i++) tmp.v[i]=v[i]-m_v.v[i];
	return (tmp);
}

//【36】-=演算子オーバーロード
CVector& CVector::operator-=(CVector &m_v)
{
	register int n = (int)v.size();
	for(int i=0;i<n;i++) v[i] -= m_v.v[i];
	return *this;
}

//【37】-演算子オーバーロード　配列の中の符号を逆にする
CVector CVector::operator-()
{
	register int n = (int)v.size();
	CVector tmp(n);
	for(int i=0;i<n;i++) tmp.v[i]=-v[i];
	return (tmp);
}

//【38】*演算子オーバーロード　スカラー倍
CVector CVector::operator*(const double k)
{
	register int n = (int)v.size();
	CVector tmp(n);
	for(int i=0;i<n;i++) tmp.v[i]=k*v[i];
	return tmp;
}

//【39】*演算子オーバーロード　スカラー倍
CVector operator*(const double k, CVector &m_v)
{
	register int n = (int)m_v.size();
	CVector tmp(n);
	for(int i=0;i<n;i++) tmp.v[i]=k*m_v.v[i];
	return (tmp);
}

//【40】*演算子オーバーロード 行ベクトルと列ベクトルの積
double CVector::operator*(CVector &m_v)
{
	double md = 0.0;
	register int n = (int)v.size();
	for(int i=0;i<n;i++) md+=v[i]*m_v.v[i];
	return (md);
}

//【41】*演算子オーバーロード　matrix[][] * vector[]
CVector	CVector::operator*(CMatrix &m_mt)
{
	CVector tmp;
	register int n = (int)m_mt.c_size();
	tmp.assign(n);
	for(int j=0;j<n;j++) tmp[j]=(*this)*m_mt.col(j);
	return tmp;
}

/***************** 正規化 ***************/

//【50】ノルムを計算する
double CVector::Norm()
{
	double md;
	md=0;
	register int n = (int)v.size();
	for(int i=0;i<n;i++) md+=v[i]*v[i];
	return sqrt(md);
}

//【51】正規化する
void CVector::Normalize()
{
	double md = 0.0;
	register int n = (int)v.size();
	for(int i=0;i<n;i++) md+=pow(v[i],2);
	for(int i=0;i<n;i++) v[i]=v[i]/sqrt(md);
}


//######################################//
//	CMatrixのメンバー関数、フレンド関数	//
//######################################//
/****** コンストラクタ＆デストラクタ *****/

//【01】コンストラクタ
CMatrix::CMatrix(){}

//【02】m_row：行数, m_col：列数, m_init：デフォルトで0(ここの引数は無しでもOK)
CMatrix::CMatrix(int m_row, int m_col, double m_init)
{
	vector<double> tmp(m_col,m_init);
	mt.assign(m_row,tmp);
}

//【03】m_rank：行列数(正方行列の生成)
CMatrix::CMatrix(int m_rank)
{
	vector<double> tmp(m_rank,0);
	mt.assign(m_rank,tmp);
}

//【04】m_mtと同じ行列をコピーして生成
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

//【05】m_mtと同じ行列をコピーして生成
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

//【06】m_mtと同じ行列をコピーして生成
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

//【07】デストラクタ 全要素を削除
CMatrix::~CMatrix(){mt.clear();}

/*************** 領域確保 ***************/

//【10】m_row：行数, m_col：列数, m_init：デフォルトで0(ここの引数は無しでもOK)
void CMatrix::assign(int m_row, int m_col, double m_init)
{
	vector<double> tmp(m_col,m_init);
	mt.assign(m_row,tmp);
}

//【11】m_rank：行列数(正方行列の生成)
void CMatrix::assign(int m_rank)
{
	vector<double> tmp(m_rank,0);
	mt.assign(m_rank,tmp);
}

//【12】m_mtと同じ行列をコピーして生成領域を確保する
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

//【13】m_mtと同じ行列をコピーして生成領域を確保する
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

//【14】m_mtと同じ行列をコピーして生成領域を確保する
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

/*************** 要素関係 ***************/

//【15】行数を返す
int CMatrix::r_size()
{
	return((int)mt.size());
}

//【16】列数を返す
int CMatrix::c_size()
{
	return((int)(*mt.begin()).size());
}

//【17】m_r行にm_vベクトルを代入する
void CMatrix::SetR(int m_r, CVector m_v)
{
	for(int j=0;j<c_size();j++) mt[m_r][j] = m_v[j];
}

//【18】m_c列にm_vベクトルを代入する
void CMatrix::SetC(int m_c, CVector m_v)
{
	for(int i=0; i<r_size(); i++) mt[i][m_c] = m_v[i];
}

//【20】中身を全て0にする
void CMatrix::SetZero()
{
	for(int i=0; i<r_size(); i++){
		for(int j=0; j<c_size(); j++){
			mt[i][j] = 0.0;
		}
	}
}

//【21】m_r行目のベクトルを返す
CVector	CMatrix::row(int m_r)
{
	CVector tmp(mt[m_r]);
	return (tmp);
}

//【22】m_c列目のベクトルを返す
CVector	CMatrix::col(int m_c)
{
	CVector tmp(r_size());
	for(int i=0;i<r_size();i++) tmp[i]=mt[i][m_c];
	return (tmp);
}

//【23】中身を出力
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

//【24】中身をCSV出力
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

//【25】CSparseのMatrixに変換	※CSparse使用者はUSE_SCPARSEを定義して下さい
#ifdef USE_CSPARSE
cs *CMatrix::ConstractCSMatrix(int m_r, int m_c,int nzmax)
{
	cs *tmp;
	int TotalM = 0;
	int i,j,k=1;
	tmp = cs_spalloc(m_r, m_c, nzmax, 1, 0);//csparse用行列確保
	tmp->p[0] = 0;

	//行列の生成
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

/*************** オーバーロード ***************/

//【30】[]括弧オーバーロード
vector<double> &CMatrix::operator[](int m_r)
{
	return (mt[m_r]);
}

//【31】=演算子オーバーロード
CMatrix& CMatrix::operator=(CMatrix &m_mt)
{
	int i,j;
	for(i=0;i<(int)mt.size();i++)
		for(j=0;j<(int)(*mt.begin()).size();j++) mt[i][j]=m_mt.mt[i][j];	
	return *this;
}

//【32】=演算子オーバーロード
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

//【33】+演算子オーバーロード
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

//【34】+=演算子オーバーロード
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

//【35】-演算子オーバーロード
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

//【36】-=演算子オーバーロード
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

//【37】-演算子オーバーロード 行列内の要素の符号を逆にする
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

//【38】*演算子オーバーロード
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

//【39】*演算子オーバーロード
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

//【40】*演算子オーバーロード
CVector	CMatrix::operator*(CVector &m_v)
{
	CVector tmp;
	tmp.assign(r_size());
	for(int i=0;i<r_size();i++) tmp[i]=(*this).row(i)*m_v;
	return (tmp);
}

//【41】*演算子オーバーロード
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

//【42】()括弧オーバーロード
double& CMatrix::operator()(int i, int j)
{
	return(mt[i][j]);
}

/*************** 行列の計算 ***************/

//【50】第m_r行と第m_c列を取り除いて得る行列　[n-1][m-1]行列となる
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

//【51】転置行列(transpose matrix)を返す
CMatrix	CMatrix::Transpose()
{
	CMatrix tmp(c_size(),r_size());
	int i,j;
	for(i=0;i<c_size();i++)
		for(j=0;j<r_size();j++) tmp.mt[i][j]=mt[j][i];
	return (tmp);

}

//【52】行列式(determinant)を返す
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

//【53】単位行列化
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

//【54】逆行列(inverse matrix)を返す
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

//【55】計算 speed up
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

//【60】LU分解
void CMatrix::ludcmp(int *indx, double *d)
{
	//input a[n×n行列],n,
	//output a(上書き),indx[ｎ行1列],d(行交換回数　偶数なら1奇数なら-1)
	int n = r_size();
	int i,imax,j,k;
	double big,dum,sum,temp;
	double *vv;				//vvは各行の暗黙のスケーリングを記録する

	vv = new double[n];
	*d  = 1.0;				//まだ行交換をしていない

	for(i=0; i<n; i++){		//行についてループし、暗黙のスケーリングを記録
		big = 0.0;

		for(j=0; j<n; j++){
			if((temp=fabs(mt[i][j])) > big){
				big = temp;
			}
		}

		if(big == 0.0){
			cout<<"error"<<endl;	//最大の要素が0なら特異行列である
			break;
		}

		vv[i] = 1.0/big;			//スケーリングを記録する
	}

	for(j=0; j<n; j++){				//Crout法,列についてのループ　方程式2.3.12のi=j以外
		for(i=0; i<j; i++){
			sum=mt[i][j];
			for(k=0; k<i; k++){
				sum -= mt[i][k]*mt[k][j];
			}
			mt[i][j]=sum;
		}

		big=0.0;				//最大のピボット要素を探す準備

		for(i=j; i<n; i++){		//式2.3.12のi=jと式2.3.13のi=j+1,...,N
			sum=mt[i][j];
			for(k=0; k<j; k++){
				sum -= mt[i][k]*mt[k][j];
			}

			mt[i][j]=sum;

			if( (dum=vv[i]*fabs(sum)) >= big){	//ピボットのよさは今までの最大値以上か？
				big = dum;
				imax= i;
			}
		}
		if(j != imax){				//行交換の必要は？　
			for(k=0; k<n; k++){		//ある
				dum=mt[imax][k];
				mt[imax][k]=mt[j][k];
				mt[j][k]=dum;
			}

			*d = -(*d);				//そしてdの偶奇を変える
			vv[imax]=vv[j];			//スケール因子も交換する
		}

		indx[j]=imax;

		if(mt[j][j] == 0.0){			//もしピボット要素が0なら行列は特異である。
			mt[j][j] = MACHINE_ERROR;	//特異行列の利用法はTINYを0にすればよいこともある
		}

		if(j != n-1){
			dum=1.0/(mt[j][j]);
			for(i=j+1; i<n; i++){
				mt[i][j] *= dum;
			}
		}
	}							//次の列を片づけにかかる
	delete[] vv;
}

//【61】n個の線形方程式の組 A * x = B を解く関数
void CMatrix::lubksb(int *indx, double b[])
{
	//n個の線形方程式の組 A * x = B を解く。入力行列Aはludcmpで求めたAのLU分解
	//入力するベクトルindx[1,...,n]はludcmpが返す行交換情報である。
	//	input	b[](右辺のベクトルB),indxはludcmpからの行交換情報
	//	output	x[](解ベクトルx)
	int n = r_size();
	int i,ii=0,ip,j;
	double sum;

	for(i=0; i<n; i++){			//iiが正なら、それはbの最初の0でない要素の添え字である。
		ip	= indx[i];			//行交換を元に戻しながら式(2.3.6)の前進代入を行う
		sum	= b[ip];
		b[ip]=b[i];

		if(ii != 0){
			for(j=ii-1; j<i; j++){
				sum -= mt[i][j]*b[j];
			}

		}else if(sum != 0){			//非零要素に出会った。これ以降は上のループで和を求めなければならない
			ii = i+1;

		}
		b[i]=sum;
	}

	for(i=n-1; i>=0; i--){		//式(2.3.7)の後退代入
		sum=b[i];
		for(j=i+1; j<n; j++){
			sum -= mt[i][j]*b[j];
		}
		b[i]=sum/mt[i][i];		//解ベクトル x の成分を保存完成！
	}
}

//【62】逆行列を返す(LU分解を用いる)
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


/********** 4行4列に特化した回転,並進行列計算 **********/

//【100】２次元配列を１次元配列に
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

//【101】並進行列を生成
void CMatrix::SetTranslate4d(double dx, double dy, double dz)
{
	mt[0][0]=1; mt[0][1]=0; mt[0][2]=0; mt[0][3]=dx;
	mt[1][0]=0; mt[1][1]=1; mt[1][2]=0; mt[1][3]=dy;
	mt[2][0]=0; mt[2][1]=0; mt[2][2]=1; mt[2][3]=dz;
	mt[3][0]=0; mt[3][1]=0; mt[3][2]=0; mt[3][3]=1;
}

//【102】回転行列を生成
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

//【103】拡大縮小の行列生成
void CMatrix::SetScale4d(double scaleX, double scaleY, double scaleZ)
{
	mt[0][0]=scaleX; mt[0][1]=0;	  mt[0][2]=0;      mt[0][3]=0;
	mt[1][0]=0;		 mt[1][1]=scaleY; mt[1][2]=0;      mt[1][3]=0;
	mt[2][0]=0;		 mt[2][1]=0;      mt[2][2]=scaleZ; mt[2][3]=0;
	mt[3][0]=0;		 mt[3][1]=0;      mt[3][2]=0;      mt[3][3]=1;
}

//【104】行列式(determinant)を返す												
double	CMatrix::Det4d()
{
	return(mt[0][0]*mt[1][1]*mt[2][2]*mt[3][3]-mt[0][0]*mt[1][1]*mt[2][3]*mt[3][2]-mt[0][0]*mt[2][1]*mt[1][2]*mt[3][3]+mt[0][0]*mt[2][1]*mt[1][3]*mt[3][2]+mt[0][0]*mt[3][1]*mt[1][2]*mt[2][3]-mt[0][0]*mt[3][1]*mt[1][3]*mt[2][2]-mt[1][0]*mt[0][1]*mt[2][2]*mt[3][3]+mt[1][0]*mt[0][1]*mt[2][3]*mt[3][2]+mt[1][0]*mt[2][1]*mt[0][2]*mt[3][3]-mt[1][0]*mt[2][1]*mt[0][3]*mt[3][2]-mt[1][0]*mt[3][1]*mt[0][2]*mt[2][3]+mt[1][0]*mt[3][1]*mt[0][3]*mt[2][2]+mt[2][0]*mt[0][1]*mt[1][2]*mt[3][3]-mt[2][0]*mt[0][1]*mt[1][3]*mt[3][2]-mt[2][0]*mt[1][1]*mt[0][2]*mt[3][3]+mt[2][0]*mt[1][1]*mt[0][3]*mt[3][2]+mt[2][0]*mt[3][1]*mt[0][2]*mt[1][3]-mt[2][0]*mt[3][1]*mt[0][3]*mt[1][2]-mt[3][0]*mt[0][1]*mt[1][2]*mt[2][3]+mt[3][0]*mt[0][1]*mt[1][3]*mt[2][2]+mt[3][0]*mt[1][1]*mt[0][2]*mt[2][3]-mt[3][0]*mt[1][1]*mt[0][3]*mt[2][2]-mt[3][0]*mt[2][1]*mt[0][2]*mt[1][3]+mt[3][0]*mt[2][1]*mt[0][3]*mt[1][2]);
}

//【105】逆行列(inverse matrix)を返す
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

//【106】逆行列(inverse matrix)を返す
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

//【107】並進行列を返す
CMatrix CMatrix::Translate4d(double dx, double dy, double dz)
{
	CMatrix tmp(4);
	tmp[0][0]=1; tmp[0][1]=0; tmp[0][2]=0; tmp[0][3]=dx;
	tmp[1][0]=0; tmp[1][1]=1; tmp[1][2]=0; tmp[1][3]=dy;
	tmp[2][0]=0; tmp[2][1]=0; tmp[2][2]=1; tmp[2][3]=dz;
	tmp[3][0]=0; tmp[3][1]=0; tmp[3][2]=0; tmp[3][3]=1;
	return (tmp);
}

//【108】回転行列を返す
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

//【109】拡大縮小の行列を返す
CMatrix CMatrix::Scale4d(double scaleX, double scaleY, double scaleZ)
{
	CMatrix tmp(4);
	tmp[0][0]=scaleX;	tmp[0][1]=0;	  tmp[0][2]=0;      tmp[0][3]=0;
	tmp[1][0]=0;		tmp[1][1]=scaleY; tmp[1][2]=0;      tmp[1][3]=0;
	tmp[2][0]=0;		tmp[2][1]=0;      tmp[2][2]=scaleZ; tmp[2][3]=0;
	tmp[3][0]=0;		tmp[3][1]=0;      tmp[3][2]=0;      tmp[3][3]=1;
	return (tmp);
}