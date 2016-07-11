#pragma once
//クォータニオン演算ライブラリ	
//【参考書】3D-CGプログラマーのためのリアルタイムシェーダー【理論と実践】参照
class CQuat;

//##############################################//
//	クォータニオンクラス						//
//##############################################//
class CQuat
{
public://メンバー変数
	double x;	//x座標
	double y;	//y座標
	double z;	//z座標
	double w;	//

public://メンバー関数及びフレンド関数
	/***** コンストラクタ＆デストラクタ *****/
	CQuat();											//【01】コンストラクタ
	CQuat(double X, double Y, double Z, double W);		//【02】コンストラクタ
	~CQuat();											//【03】デストラクタ
	/***** 要素関係 *****/
	void Set(double X, double Y, double Z, double W);	//【04】座標をセットする
	void Clear();										//【06】クォータニオンのクリア
	void Print();										//【07】クォータニオンの出力
	/***** オーバーロード *****/
	CQuat& operator=(const CQuat& obj);					//【10】=演算子オーバーロード
	CQuat  operator+(const CQuat& obj);					//【11】+演算子オーバーロード
	CQuat& operator+=(const CQuat& obj);				//【12】+=演算子オーバーロード
	CQuat  operator-(const CQuat& obj);					//【13】-演算子オーバーロード
	CQuat& operator-=(const CQuat& obj);				//【14】-=演算子オーバーロード
	CQuat  operator-();									//【15】-演算子オーバーロード
	CQuat  operator*(const double a);					//【16】*演算子オーバーロード
	friend CQuat operator*(const double a,const CQuat& obj);	//【17】*演算子オーバーロード
	CQuat  operator*(const CQuat& obj);					//【18】*演算子オーバーロード
	/***** クォータニオンの計算 *****/
	CQuat Identify();					//【21】格納されている座標の正規化をする
	double	Norm();						//【23】クォータニオンの大きさを求める
	double	Norm_sqr();					//【24】クォータニオンのノルム
};