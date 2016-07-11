#include "l3.h"
using namespace std;
//##########################################//
//	CPoint3dのメンバー関数、フレンド関数	//
//##########################################//
/****** コンストラクタ＆デストラクタ *****/

//【01】コンストラクタ
CQuat::CQuat()
{
	x = y = z = w = 0.0;
}

//【02】コンストラクタ
CQuat::CQuat(double X, double Y, double Z, double W)
{
	x = X;	y = Y;	z = Z;	w = W;
}

//【03】デストラクタ
CQuat::~CQuat(){}

/*************** 要素関係 ***************/

//【04】座標値の入力
void CQuat::Set(double X, double Y, double Z, double W)
{
	x = X;	y = Y;	z = Z;	w = W;
}

//【06】ベクトルのクリア
void CQuat::Clear()
{
	x = 0.0;	y = 0.0;	z = 0.0;	w = 0.0;
}

//【07】プリント出力
void CQuat::Print()
{
	std::cout<<"("<<x<<","<<y<<","<<z<<","<<w<<")"<<std::endl;
}

/*************** オーバーロード ***************/

//【10】=演算子オーバーロード
CQuat& CQuat::operator=(const CQuat& obj)
{
	x = obj.x;	y = obj.y;	z = obj.z;	w = obj.w;
	return *this;
}

//【11】+演算子オーバーロード
CQuat CQuat::operator+(const CQuat& obj)
{
	CQuat tmp;
	tmp.x = x + obj.x;	tmp.y = y + obj.y;	tmp.z = z + obj.z;	tmp.w = w + obj.w;
	return (tmp);
}

//【12】+=演算子オーバーロード
CQuat& CQuat::operator+=(const CQuat& obj)
{
	x += obj.x;	y += obj.y;	z += obj.z; w += obj.w;
	return *this;
}

//【13】-演算子オーバーロード
CQuat CQuat::operator-(const CQuat& obj)
{
	CQuat tmp;
	tmp.x = x - obj.x;	tmp.y = y - obj.y;	tmp.z = z - obj.z;	tmp.w = w - obj.w;
	return (tmp);
}

//【14】-=演算子オーバーロード
CQuat& CQuat::operator-=(const CQuat& obj)
{
	x -= obj.x;	y -= obj.y;	z -= obj.z;	w -= obj.w;
	return *this;
}

//【15】-演算子オーバーロード 符号を逆にする
CQuat  CQuat::operator-()
{
	CQuat tmp;
	tmp.x = -x; tmp.y = -y; tmp.z = -z;	tmp.w = -w;
	return(tmp);
}

//【16】*演算子オーバーロード
CQuat CQuat::operator*(const double a)
{
	CQuat tmp;
	tmp.x = a * x;	tmp.y = a * y;	tmp.z = a * z;	tmp.w = a * w;
	return (tmp);
}
//【17】*演算子オーバーロード
CQuat operator*(const double a, const CQuat& obj)
{
	CQuat tmp;
	tmp.x = a * obj.x;	tmp.y = a * obj.y;	tmp.z = a * obj.z;	tmp.w = a * obj.w;
	return (tmp);
}

//【18】*演算子オーバーロード
CQuat  CQuat::operator*(const CQuat& obj)
{
	CQuat tmp;
	tmp.w = w * obj.w - x * obj.x - y * obj.y - z * obj.z;
	tmp.x = w * obj.x + x * obj.w - y * obj.z + z * obj.y;
	tmp.y = w * obj.y + x * obj.z + y * obj.w - z * obj.x;
	tmp.z = w * obj.z - x * obj.y + y * obj.x + z * obj.w;
	
	return (tmp);
}

/*************** クォータニオン計算 ***************/
//【21】格納されている座標の正規化をする
CQuat CQuat::Identify()
{
	CQuat tmp(0,0,0,1.0);
	return (tmp);
}

//【23】クォータニオンの大きさを求める
double CQuat::Norm()
{
	return (sqrt(Norm_sqr()));
}

//【24】クォータニオンのノルム
double CQuat::Norm_sqr()
{
	return (x*x + y*y + z*z + w*w);
}