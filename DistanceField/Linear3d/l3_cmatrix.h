#pragma once
#include <iostream>
#include <vector>
using namespace std;

class CVector;
class CMatrix;

//#################################//
//	ベクトルについてのクラス
//#################################//
class CVector
{
private://メンバー変数	※アクセス制限をかける為にprivate
	vector<double> v;	//配列

public://メンバー関数及びフレンド関数
	/***** コンストラクタ＆デストラクタ *****/
	CVector();										//【01】コンストラクタ
	CVector(int m_size, double m_init=0);			//【02】m_size：配列数,m_init：デフォルトで0(ここの引数は無しでもOK)
	CVector(CVector &m_v);							//【03】m_vの中身をコピーして生成する
	CVector(vector<double> &m_v);					//【04】m_vの中身をコピーして生成する
	CVector(int m_size, double *m_v);				//【05】m_vの中身をコピーして生成する
	CVector(CVector &m_v, int m_first, int m_end);	//【06】m_vの中のm_first番目からm_end番目までをコピーして生成
	CVector(vector<double> &m_v, int m_first, int m_end);	//【07】m_vの中のm_first番目からm_end番目までをコピーして生成	
	~CVector();										//【08】デストラクタ 全要素を削除

	/***** 領域確保 *****/
	void	assign(int m_size, double m_init=0);		//【10】m_size：配列数,m_init：デフォルトで0(ここの引数は無しでもOK)
	void	assign(CVector &m_v, int m_first, int m_end);//【11】m_vの中のm_first番目からm_end番目までをコピーして生成

	/***** 要素関係 *****/
	int		size();								//【20】配列の数を返す
	void	Add(double m_element);				//【21】要素を追加する
	void	Clear();							//【22】要素の中身を空にする
	void	SetZero();							//【23】中身を０にする
	void	Print();							//【24】中身を出力

	/***** オーバーロード *****/
	double	&operator[](const int &pos);		//【30】vec.v[10]からvec[10]への書き方に変更する
	CVector	&operator=(CVector &m_v);			//【31】=演算子オーバーロード
	CVector	&operator=(vector<double> &m_v);	//【32】=演算子オーバーロード
	CVector	operator+(CVector &m_v);			//【33】+演算子オーバーロード
	CVector	&operator+=(CVector &m_v);			//【34】+=演算子オーバーロード
	CVector	operator-(CVector &m_v);			//【35】-演算子オーバーロード
	CVector	&operator-=(CVector &m_v);			//【36】-=演算子オーバーロード
	CVector	operator-();						//【37】-演算子オーバーロード
	CVector	operator*(const double k);			//【38】*演算子オーバーロード
	friend CVector operator*(const double k, CVector &m_v);//【39】*演算子オーバーロード
	double	operator*(CVector &m_v);			//【40】*演算子オーバーロード
	CVector	operator*(CMatrix &m_mt);			//【41】*演算子オーバーロード

	/***** 正規化 *****/
	double	Norm();								//【50】ノルムを計算する
	void	Normalize();						//【51】正規化する

};


//#################################//
//	行列についてのクラス
//#################################//
class CMatrix
{
private://メンバー変数	※アクセス制限をかける為にprivate
	vector<vector<double> > mt;
public:
	/***** コンストラクタ＆デストラクタ *****/
	CMatrix();											//【01】コンストラクタ
	CMatrix(int m_row, int m_col, double m_init=0);		//【02】m_row：行数, m_col：列数, m_init：デフォルトで0(ここの引数は無しでもOK)
	CMatrix(int m_rank);								//【03】m_rank：行列数(正方行列の生成)
	CMatrix(CMatrix &m_mt);								//【04】m_mtと同じ行列をコピーして生成
	CMatrix(vector<vector<double> > &m_mt);				//【05】m_mtと同じ行列をコピーして生成
	CMatrix(int m_row, int m_col, double **m_mt);		//【06】m_mtと同じ行列をコピーして生成
	~CMatrix();											//【07】デストラクタ 全要素を削除

	/***** 領域確保 *****/
	void	assign(int m_row, int m_col, double m_init=0);	//【10】m_row：行数, m_col：列数, m_init：デフォルトで0(ここの引数は無しでもOK)
	void	assign(int m_rank);								//【11】m_rank：行列数(正方行列の生成)
	void	assign(CMatrix &m_mt);							//【12】m_mtと同じ行列をコピーして生成領域を確保する
	void	assign(vector<vector<double> > &m_mt);			//【13】m_mtと同じ行列をコピーして生成領域を確保する
	void	assign(int m_row, int m_col, double **m_mt);	//【14】m_mtと同じ行列をコピーして生成領域を確保する

	/***** 要素関係 *****/
	int		r_size();									//【15】行数を返す
	int		c_size();									//【16】列数を返す
	void	SetR(int m_r, CVector m_v);					//【17】m_r行にm_vベクトルを代入する
	void	SetC(int m_c, CVector m_v);					//【18】m_c列にm_vベクトルを代入する
	void	SetZero();									//【20】中身を全て0にする
	CVector	row(int m_r);								//【21】m_r行目のベクトルを返す
	CVector	col(int m_c);								//【22】m_c列目のベクトルを返す
	void	Print();									//【23】中身を出力
	void	FPrint(int NameNumber=0);					//【24】中身をCSV出力
#ifdef USE_CSPARSE
	cs		*ConstractCSMatrix(int m_r, int m_c,int nzmax);//【25】CSparseのMatrixに変換(CSparse使用者のみ)
#endif

	/***** オーバーロード *****/
	vector<double> &operator[](const int m_r);			//【30】[]括弧オーバーロード
	CMatrix	&operator=(CMatrix &m_mt);					//【31】=演算子オーバーロード
	CMatrix	&operator=(vector<vector<double>> &m_mt);	//【32】=演算子オーバーロード
	CMatrix	operator+(CMatrix &m_mt);					//【33】+演算子オーバーロード
	CMatrix &operator+=(CMatrix &m_mt);					//【34】+=演算子オーバーロード
	CMatrix	operator-(CMatrix &m_mt);					//【35】-演算子オーバーロード
	CMatrix &operator-=(CMatrix &m_mt);					//【36】-=演算子オーバーロード
	CMatrix	operator-();								//【37】-演算子オーバーロード
	CMatrix	operator*(const double k);					//【38】*演算子オーバーロード
	friend CMatrix	operator*(const double k,CMatrix &m_mt);	//【39】*演算子オーバーロード
	CVector	operator*(CVector &m_v);				//【40】*演算子オーバーロード
	CMatrix	operator*(CMatrix &m_mt);				//【41】*演算子オーバーロード
	double &operator()(int i, int j);					//【42】()括弧オーバーロード

	/***** 行列の計算 *****/
	CMatrix	Remove(int m_r, int m_c);					//【50】第m_r行と第m_c列を取り除いて得る行列
	CMatrix	Transpose();								//【51】転置行列(transpose matrix)を返す
	double	Det();										//【52】行列式(determinant)を返す
	void	IdentifyMatrix();							//【53】単位行列化
	CMatrix	Inverse();									//【54】逆行列(inverse matrix)を返す
	void	Inverse(CMatrix& ma,CMatrix& mat, CVector& vec1, CVector& vec2); //【55】計算 speed up

	/***** LU分解 *****/
	void	ludcmp(int *indx, double *d);				//【60】LU分解
	void	lubksb(int *indx, double b[]);				//【61】n個の線形方程式の組 A * x = B を解く関数
	CMatrix InverseLU();								//【62】逆行列を返す(LU分解を用いる)

	/***** 4行4列に特化した回転,並進行列計算 *****/
	operator double*();													//【100】２次元配列を１次元配列に
	void	SetTranslate4d(double dx, double dy, double dz);			//【101】並進行列を生成
	void	SetRotate4d(double Angle, double vx, double vy, double vz);	//【102】回転行列を生成
	void	SetScale4d(double scaleX, double scaleY, double scaleZ);	//【103】拡大縮小の行列生成
	double	Det4d();													//【104】行列式(determinant)を返す												
	CMatrix	Inverse4d();												//【105】逆行列(inverse matrix)を返す
	void	Inverse4d(CMatrix &m_matrix);								//【106】逆行列(inverse matrix)を返す
	CMatrix Translate4d(double dx, double dy, double dz);				//【107】並進行列を返す
	CMatrix Rotate4d(double Angle, double vx, double vy, double vz);	//【108】回転行列を返す
	CMatrix Scale4d(double scaleX, double scaleY, double scaleZ);		//【109】拡大縮小の行列を返す
};

//CVectorの出力
inline std::ostream& operator<<(std::ostream& s, CVector &A){
	for(int i=0; i<A.size(); i++){
		s<<A[i]<<" "<<::endl;
	}
	return s;
}

//CMatrixの出力
inline std::ostream& operator<<(std::ostream& s, CMatrix &A){
	for(int i=0; i<A.r_size(); i++){
		for(int j=0; j<A.c_size(); j++){
			s<<A[i][j]<<" ";
		}
		s<<std::endl;
	}
	return s;
}