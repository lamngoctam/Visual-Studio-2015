#pragma once

class CPoint3d;
class CVector3d;

//##############################################//
//	頂点情報についてのクラス(制御点用クラス)	//
//##############################################//
class CPoint3d
{
public://メンバー変数
	double x;	//x座標
	double y;	//y座標
	double z;	//z座標
	double w;	//重み

public://メンバー関数及びフレンド関数
	/***** コンストラクタ＆デストラクタ *****/
	CPoint3d();												//【01】コンストラクタ
	CPoint3d(double X, double Y, double Z, double W = 1.0);	//【02】コンストラクタ
	~CPoint3d();											//【03】デストラクタ

	/***** 要素関係 *****/
	void Set(double X, double Y, double Z, double W = 1.0 );//【04】座標をセットする
	void UnitVector(double X, double Y, double Z);			//【05】座標をセット後、正規化する
	void Clear();											//【06】ベクトルのクリア
	void Print();											//【07】ベクトルの出力

	/***** オーバーロード *****/
	CPoint3d& operator=(const CPoint3d& obj);	//【10】=演算子オーバーロード
	CPoint3d  operator+(const CPoint3d& obj);	//【11】+演算子オーバーロード
	CPoint3d& operator+=(const CPoint3d& obj);	//【12】+=演算子オーバーロード
	CPoint3d  operator-(const CPoint3d& obj);	//【13】-演算子オーバーロード
	CPoint3d& operator-=(const CPoint3d& obj);	//【14】-=演算子オーバーロード
	CPoint3d  operator-();						//【15】-演算子オーバーロード
	CPoint3d  operator*(const double k);		//【16】*演算子オーバーロード
	friend CPoint3d operator*(const double k,const CPoint3d& obj);	//【17】*演算子オーバーロード
	operator CVector3d();						//【18】CVector3d型変換演算子のオーバーロード
	CPoint3d operator/(const double k);			//【19】/演算子のオーバーロード
	operator	 double*();						//【20】*演算子のオーバーロード

	/***** ベクトル計算 *****/
	CPoint3d Mid(CPoint3d &obj);			//【20】obj点との中点を求める
	CPoint3d Normalize();					//【21】格納されている座標の正規化をする
	void	Normalize(CPoint3d &obj);		//【22】obj点を正規化する
	double	Norm();							//【23】ベクトルの大きさを求める
	double	Distance(CPoint3d &obj);		//【24】obj点との距離を求める
	double	Dot(CPoint3d &obj);				//【25】obj点との内積を求める
	CPoint3d Cross(CPoint3d &obj);			//【26】obj点との外積を求める
	double	Angle(CPoint3d &obj);			//【27】objとの角度
	double	PointLineDistance(CPoint3d &P0, CPoint3d &P1);	//【28】Point-Line Distance
	CPoint3d Max(CPoint3d &obj);			//【29】obj点とのxyz各最大値を返す
	CPoint3d Min(CPoint3d &obj);			//【30】obj点とのxyz各最小値を返す
	CPoint3d RotateX(double rad);			//【31】X軸周りにrad回転
	CPoint3d RotateY(double rad);			//【32】Y軸周りにrad回転
	CPoint3d RotateZ(double rad);			//【33】Z軸周りにrad回転

	/***** CVector3dとの互換性*****/
	CPoint3d& operator=(const CVector3d& obj);	//【10-2】=演算子オーバーロード
	CPoint3d  operator+(const CVector3d& obj);	//【11-2】+演算子オーバーロード
	CPoint3d& operator+=(const CVector3d& obj);	//【12-2】+=演算子オーバーロード
	CPoint3d  operator-(const CVector3d& obj);	//【13-2】-演算子オーバーロード
	CPoint3d& operator-=(const CVector3d& obj);	//【14-2】-=演算子オーバーロード
	CPoint3d Mid(CVector3d &obj);				//【20-2】obj点との中点を求める
	double	Distance(CVector3d &obj);			//【24-2】obj点との距離を求める
	double	Dot(CVector3d &obj);				//【25-2】obj点との内積を求める
	CPoint3d Cross(CVector3d &obj);				//【26-2】obj点との外積を求める
	double	Angle(CVector3d &obj);				//【27-2】objとの角度
	CPoint3d Max(CVector3d &obj);				//【29-2】obj点とのxyz各最大値を返す
	CPoint3d Min(CVector3d &obj);				//【30-2】obj点とのxyz各最小値を返す
};

//##############################################//
//	頂点情報についてのクラス(制御点用クラス)	//
//##############################################//
class CVector3d
{
public://メンバー変数
	double x;	//x座標
	double y;	//y座標
	double z;	//z座標

public://メンバー関数及びフレンド関数
	/***** コンストラクタ＆デストラクタ *****/
	CVector3d();								//【01】コンストラクタ
	CVector3d(double X, double Y, double Z);	//【02】コンストラクタ
	~CVector3d();								//【03】デストラクタ

	/***** 要素関係 *****/
	void Set(double X, double Y, double Z);	//【04】座標をセットする
	void UnitVector(double X, double Y, double Z);	//【05】座標をセット後、正規化する
	void Clear();							//【06】ベクトルのクリア
	void Print();							//【07】ベクトルの出力

	/***** オーバーロード *****/
	CVector3d& operator=(const CVector3d& obj);		//【10】=演算子オーバーロード
	CVector3d  operator+(const CVector3d& obj);		//【11】+演算子オーバーロード
	CVector3d& operator+=(const CVector3d& obj);	//【12】+=演算子オーバーロード
	CVector3d  operator-(const CVector3d& obj);		//【13】-演算子オーバーロード
	CVector3d& operator-=(const CVector3d& obj);	//【14】-=演算子オーバーロード
	CVector3d  operator-();							//【15】-演算子オーバーロード
	CVector3d  operator*(const double k);			//【16】*演算子オーバーロード
	friend CVector3d operator*(const double k,const CVector3d& obj);	//【17】*演算子オーバーロード
	operator CPoint3d();							//【18】CPoint3d型変換演算子のオーバーロード
	CVector3d operator/(const double k);			//【19】/演算子のオーバーロード
	operator	 double*();							//【20】*演算子のオーバーロード

	/***** ベクトル計算 *****/
	CVector3d Mid(CVector3d &obj);			//【20】obj点との中点を求める
	CVector3d Normalize();					//【21】格納されている座標の正規化をする
	void	Normalize(CVector3d &obj);		//【22】obj点を正規化する
	double	Norm();							//【23】ベクトルの大きさを求める
	double	Distance(CVector3d &obj);		//【24】obj点との距離を求める
	double SquaredDistance(CVector3d &obj);

	double	Dot(CVector3d &obj);			//【25】obj点との内積を求める
	CVector3d Cross(CVector3d &obj);		//【26】obj点との外積を求める
	double	Angle(CVector3d &obj);			//【27】objとの角度
	double	PointLineDistance(CVector3d &P0, CVector3d &P1);	//【28】Point-Line Distance
	CVector3d Max(CVector3d &obj);			//【29】a点とのxyz各最大値を返す
	CVector3d Min(CVector3d &obj);			//【30】a点とのxyz各最小値を返す
	CVector3d RotateX(double rad);			//【31】X軸周りにrad回転
	CVector3d RotateY(double rad);			//【32】Y軸周りにrad回転
	CVector3d RotateZ(double rad);			//【33】Z軸周りにrad回転

	/***** CVector3dとの互換性*****/
	CVector3d& operator=(const CPoint3d& obj);	//【10-2】=演算子オーバーロード
	CVector3d  operator+(const CPoint3d& obj);	//【11-2】+演算子オーバーロード
	CVector3d& operator+=(const CPoint3d& obj);	//【12-2】+=演算子オーバーロード
	CVector3d  operator-(const CPoint3d& obj);	//【13-2】-演算子オーバーロード
	CVector3d& operator-=(const CPoint3d& obj);	//【14-2】-=演算子オーバーロード
	CVector3d Mid(CPoint3d &obj);				//【20-2】obj点との中点を求める
	double	Distance(CPoint3d &obj);			//【24-2】obj点との距離を求める
	double	Dot(CPoint3d &obj);				//【25-2】obj点との内積を求める
	CVector3d Cross(CPoint3d &obj);			//【26-2】obj点との外積を求める
	double	Angle(CPoint3d &obj);			//【27-2】objとの角度
	CVector3d Max(CPoint3d &obj);			//【29-2】obj点とのxyz各最大値を返す
	CVector3d Min(CPoint3d &obj);			//【30-2】obj点とのxyz各最小値を返す
	CVector3d NormalVector(CVector3d b,CVector3d c);	//【34 3点a,b,cの単位法線ベクトルを返す2012/5/29(他の人との互換性が悪いのでいずれ他の所に持ってく)
};