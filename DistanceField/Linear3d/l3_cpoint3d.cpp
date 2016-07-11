#define _USE_MATH_DEFINES	//円周率M_PIを使うために必要
#include "l3.h"
using namespace std;
//##########################################//
//	CPoint3dのメンバー関数、フレンド関数	//
//##########################################//
/****** コンストラクタ＆デストラクタ *****/

//【01】コンストラクタ
CPoint3d::CPoint3d()
{
	x = y = z = 0.0;
	w = 1.0;
}

//【02】コンストラクタ
CPoint3d::CPoint3d(double X, double Y, double Z, double W)
{
	x = X;	y = Y;	z = Z;	w = W;
}

//【03】デストラクタ
CPoint3d::~CPoint3d(){}

/*************** 要素関係 ***************/

//【04】座標値の入力
void CPoint3d::Set(double X, double Y, double Z, double W)
{
	x = X;	y = Y;	z = Z;	w = W;
}

//【05】座標をセット後、正規化する
void CPoint3d::UnitVector(double X, double Y, double Z)
{
	double norm = sqrt(X*X+Y*Y+Z*Z);
	x = X/norm;	y = Y/norm;	z = Z/norm;
}

//【06】ベクトルのクリア
void CPoint3d::Clear()
{
	x = 0.0;	y = 0.0;	z = 0.0;	w = 1.0;
}

//【07】プリント出力
void CPoint3d::Print()
{
	std::cout<<"("<<x<<","<<y<<","<<z<<","<<w<<");"<<std::endl;
}

/*************** オーバーロード ***************/

//【10】=演算子オーバーロード
CPoint3d& CPoint3d::operator=(const CPoint3d& obj)
{
	x = obj.x;	y = obj.y;	z = obj.z;	w = obj.w;
	return *this;
}

//【11】+演算子オーバーロード
CPoint3d CPoint3d::operator+(const CPoint3d& obj)
{
	CPoint3d tmp;
	tmp.x = x + obj.x;	tmp.y = y + obj.y;	tmp.z = z + obj.z;
	return (tmp);
}

//【12】+=演算子オーバーロード
CPoint3d& CPoint3d::operator+=(const CPoint3d& obj)
{
	x += obj.x;	y += obj.y;	z += obj.z;
	return *this;
}

//【13】-演算子オーバーロード
CPoint3d CPoint3d::operator-(const CPoint3d& obj)
{
	CPoint3d tmp;
	tmp.x = x - obj.x;	tmp.y = y - obj.y;	tmp.z = z - obj.z;
	return (tmp);
}

//【14】-=演算子オーバーロード
CPoint3d& CPoint3d::operator-=(const CPoint3d& obj)
{
	x -= obj.x;	y -= obj.y;	z -= obj.z;
	return *this;
}

//【15】-演算子オーバーロード 符号を逆にする
CPoint3d  CPoint3d::operator-()
{
	CPoint3d tmp;
	tmp.x = -x; tmp.y = -y; tmp.z = -z;
	return(tmp);
}

//【16】*演算子オーバーロード
CPoint3d CPoint3d::operator*(const double k)
{
	CPoint3d tmp;
	tmp.x = k * x;	tmp.y = k * y;	tmp.z = k * z;
	return (tmp);
}
//【17】*演算子オーバーロード
CPoint3d operator*(const double k, const CPoint3d& obj)
{
	CPoint3d tmp;
	tmp.x = k * obj.x;	tmp.y = k * obj.y;	tmp.z = k * obj.z;
	return (tmp);
}

//【18】CVector3d型変換演算子のオーバーロード
CPoint3d::operator CVector3d()
{
	return CVector3d(x,y,z);
}

//【19】/演算子のオーバーロード
CPoint3d CPoint3d::operator/(const double k)
{
	CPoint3d tmp;
	tmp.x = x / k;	tmp.y = y / k;	tmp.z = z / k;
	return (tmp);
}

//【20】*演算子のオーバーロード
CPoint3d::operator double*()
{
	static double r[4];
	r[0] = x; r[1] = y; r[2] = z; r[3] = w;
	return r;
}


/*************** ベクトル計算 ***************/

//【20】ベクトルの中点を求める
CPoint3d CPoint3d::Mid(CPoint3d &obj)
{
	CPoint3d tmp;
	tmp.x = (x + obj.x)/2.0;
	tmp.y = (y + obj.y)/2.0;
	tmp.z = (z + obj.z)/2.0;
	return (tmp);
}

//【20-2】ベクトルの中点を求める
CPoint3d CPoint3d::Mid(CVector3d &obj)
{
	CPoint3d tmp;
	tmp.x = (x + obj.x)/2.0;
	tmp.y = (y + obj.y)/2.0;
	tmp.z = (z + obj.z)/2.0;
	return (tmp);
}

//【21】格納されている座標の正規化をする
CPoint3d CPoint3d::Normalize()
{
	double norm = Norm();
	CPoint3d tmp;
	if(norm!=0){
		tmp.x = x/norm;	tmp.y = y/norm;	tmp.z = z/norm;
	}
	return (tmp);
}

//【22】正規化する
void CPoint3d::Normalize(CPoint3d &obj)
{
	double norm = obj.Norm();
	if(norm!=0){
		x = obj.x/norm;	y = obj.y/norm;	z = obj.z/norm;
	}
}

//【23】ユークリッドノルム
double CPoint3d::Norm()
{
	return (sqrt( x*x + y*y + z*z ));
}

//【24】距離の計算
double CPoint3d::Distance(CPoint3d &obj)
{
	double X = x - obj.x;	
	double Y = y - obj.y;
	double Z = z - obj.z;
	return (sqrt( X*X + Y*Y + Z*Z));
}

//【24-2】距離の計算
double CPoint3d::Distance(CVector3d &obj)
{
	double X = x - obj.x;	
	double Y = y - obj.y;
	double Z = z - obj.z;
	return (sqrt( X*X + Y*Y + Z*Z));
}

//【25】ベクトルの内積
double CPoint3d::Dot(CPoint3d &obj)
{
	double dot = x * obj.x;
	dot += y * obj.y;
	dot += z * obj.z;
	return (dot);
}

//【25-2】ベクトルの内積
double CPoint3d::Dot(CVector3d &obj)
{
	double dot = x * obj.x;
	dot += y * obj.y;
	dot += z * obj.z;
	return (dot);
}

//【26】ベクトルの外積
CPoint3d CPoint3d::Cross(CPoint3d &obj)
{
	CPoint3d tmp;
	tmp.x = y*obj.z - z*obj.y;
	tmp.y = z*obj.x - x*obj.z;
	tmp.z = x*obj.y - y*obj.x;
	return (tmp);
}

//【26-2】ベクトルの外積
CPoint3d CPoint3d::Cross(CVector3d &obj)
{
	CPoint3d tmp;
	tmp.x = y*obj.z - z*obj.y;
	tmp.y = z*obj.x - x*obj.z;
	tmp.z = x*obj.y - y*obj.x;
	return (tmp);
}

//【27】aとの角度
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

//【27】aとの角度
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

//【28】Point-Line Distance
double CPoint3d::PointLineDistance(CPoint3d &P0, CPoint3d &P1)
{
	CPoint3d A = P1-P0;
	CPoint3d B( x-P0.x, y-P0.y, z-P0.z);
	return ( (A.Cross(B)).Norm()/P0.Distance(P1) );
}

//【29】a点とのxyz各最大値を返す
CPoint3d CPoint3d::Max(CPoint3d &obj)
{
	CPoint3d tmp;
	tmp.x = max(x,obj.x);
	tmp.y = max(y,obj.y);
	tmp.z = max(z,obj.z);
	return (tmp);
}

//【29-2】a点とのxyz各最大値を返す
CPoint3d CPoint3d::Max(CVector3d &obj)
{
	CPoint3d tmp;
	tmp.x = max(x,obj.x);
	tmp.y = max(y,obj.y);
	tmp.z = max(z,obj.z);
	return (tmp);
}

//【30】a点とのxyz各最小値を返す
CPoint3d CPoint3d::Min(CPoint3d &obj)
{
	CPoint3d tmp;
	tmp.x = min(x,obj.x);
	tmp.y = min(y,obj.y);
	tmp.z = min(z,obj.z);
	return (tmp);
}

//【30-2】a点とのxyz各最小値を返す
CPoint3d CPoint3d::Min(CVector3d &obj)
{
	CPoint3d tmp;
	tmp.x = min(x,obj.x);
	tmp.y = min(y,obj.y);
	tmp.z = min(z,obj.z);
	return (tmp);
}

//【31】X軸周りにrad回転
CPoint3d CPoint3d::RotateX( double rad )
{
	CPoint3d tmp;
	tmp.x = x;
	tmp.y = (y*cos(rad)) - (z*sin(rad));
	tmp.z = (y*sin(rad)) + (z*cos(rad));
	return (tmp);
}

//【32】Y軸周りにrad回転
CPoint3d CPoint3d::RotateY( double rad )
{
	CPoint3d tmp;
	tmp.x = (z*sin(rad)) + (x*cos(rad));
	tmp.y = y;
	tmp.z = (z*cos(rad)) - (x*sin(rad));
	return (tmp);
}

//【33】Z軸周りにrad回転
CPoint3d CPoint3d::RotateZ( double rad )
{
	CPoint3d tmp;
	tmp.x = (x*cos(rad)) - (y*sin(rad));
	tmp.y = (x*sin(rad)) + (y*cos(rad));
	tmp.z = z;
	return (tmp);
}



/*************** CVector3dとの互換性 ***************/

//【10-2】=演算子オーバーロード
CPoint3d& CPoint3d::operator=(const CVector3d& obj)
{
	x = obj.x;	y = obj.y;	z = obj.z;
	return *this;
}

//【11-2】+演算子オーバーロード
CPoint3d CPoint3d::operator+(const CVector3d& obj)
{
	CPoint3d tmp;
	tmp.x = x + obj.x;	tmp.y = y + obj.y;	tmp.z = z + obj.z;
	return (tmp);
}

//【12-2】+=演算子オーバーロード
CPoint3d& CPoint3d::operator+=(const CVector3d& obj)
{
	x += obj.x;	y += obj.y;	z += obj.z;
	return *this;
}

//【13-2】-演算子オーバーロード
CPoint3d CPoint3d::operator-(const CVector3d& obj)
{
	CPoint3d tmp;
	tmp.x = x - obj.x;	tmp.y = y - obj.y;	tmp.z = z - obj.z;
	return (tmp);
}

//【14-2】-=演算子オーバーロード
CPoint3d& CPoint3d::operator-=(const CVector3d& obj)
{
	x -= obj.x;	y -= obj.y;	z -= obj.z;
	return *this;
}

//######################################//
//	CVector3dのメンバー関数、フレンド関数	//
//######################################//
/****** コンストラクタ＆デストラクタ *****/

//【01】コンストラクタ
CVector3d::CVector3d()
{
	x = y = z = 0.0;
}

//【02】コンストラクタ
CVector3d::CVector3d(double X, double Y, double Z)
{
	x = X;	y = Y;	z = Z;
}

//【03】デストラクタ
CVector3d::~CVector3d(){}

/*************** 要素関係 ***************/

//【04】座標値の入力
void CVector3d::Set(double X, double Y, double Z)
{
	x = X;	y = Y;	z = Z;	
}

//【05】座標をセット後、正規化する
void CVector3d::UnitVector(double X, double Y, double Z)
{
	double norm = sqrt(X*X+Y*Y+Z*Z);
	x = X/norm;	y = Y/norm;	z = Z/norm;
}

//【06】ベクトルのクリア
void CVector3d::Clear()
{
	x = 0.0;	y = 0.0;	z = 0.0;
}

//【07】プリント出力
void CVector3d::Print()
{
	std::cout<<"("<<x<<","<<y<<","<<z<<")"<<std::endl;
}

/*************** オーバーロード ***************/

//【10】=演算子オーバーロード
CVector3d& CVector3d::operator=(const CVector3d& obj)
{
	x = obj.x;	y = obj.y;	z = obj.z;
	return *this;
}

//【11】+演算子オーバーロード
CVector3d CVector3d::operator+(const CVector3d& obj)
{
	CVector3d tmp;
	tmp.x = x + obj.x;	tmp.y = y + obj.y;	tmp.z = z + obj.z;
	return (tmp);
}

//【12】+=演算子オーバーロード
CVector3d& CVector3d::operator+=(const CVector3d& obj)
{
	x += obj.x;	y += obj.y;	z += obj.z;
	return *this;
}

//【13】-演算子オーバーロード
CVector3d CVector3d::operator-(const CVector3d& obj)
{
	CVector3d tmp;
	tmp.x = x - obj.x;	tmp.y = y - obj.y;	tmp.z = z - obj.z;
	return (tmp);
}

//【14】-=演算子オーバーロード
CVector3d& CVector3d::operator-=(const CVector3d& obj)
{
	x -= obj.x;	y -= obj.y;	z -= obj.z;
	return *this;
}

//【15】-演算子オーバーロード 符号を逆にする
CVector3d  CVector3d::operator-()
{
	CVector3d tmp;
	tmp.x = -x; tmp.y = -y; tmp.z = -z;
	return(tmp);
}

//【16】*演算子オーバーロード
CVector3d CVector3d::operator*(const double k)
{
	CVector3d tmp;
	tmp.x = k * x;	tmp.y = k * y;	tmp.z = k * z;
	return (tmp);
}
//【17】*演算子オーバーロード
CVector3d operator*(const double k, const CVector3d& obj)
{
	CVector3d tmp;
	tmp.x = k * obj.x;	tmp.y = k * obj.y;	tmp.z = k * obj.z;
	return (tmp);
}

//【18】CPoint3d型変換演算子のオーバーロード
CVector3d::operator CPoint3d()
{
	return CPoint3d(x,y,z);
}

//【19】/演算子のオーバーロード
CVector3d CVector3d::operator/(const double k)
{
	CVector3d tmp;
	tmp.x = x / k;	tmp.y = y / k;	tmp.z = z / k;
	return (tmp);
}

//【20】*演算子のオーバーロード
CVector3d::operator double*()
{
	static double r[3];
	r[0] = x; r[1] = y; r[2] = z;
	return r;
}

/*************** ベクトル計算 ***************/

//【20】ベクトルの中点を求める
CVector3d CVector3d::Mid(CVector3d &obj)
{
	CVector3d tmp;
	tmp.x = (x + obj.x)/2.0;
	tmp.y = (y + obj.y)/2.0;
	tmp.z = (z + obj.z)/2.0;
	return (tmp);
}

//【20-2】ベクトルの中点を求める
CVector3d CVector3d::Mid(CPoint3d &obj)
{
	CVector3d tmp;
	tmp.x = (x + obj.x)/2.0;
	tmp.y = (y + obj.y)/2.0;
	tmp.z = (z + obj.z)/2.0;
	return (tmp);
}

//【21】格納されている座標の正規化をする
CVector3d CVector3d::Normalize()
{
	double norm = Norm();
	CVector3d tmp;
	tmp.x = x/norm;	tmp.y = y/norm;	tmp.z = z/norm;
	return (tmp);
}

//【22】正規化する
void CVector3d::Normalize(CVector3d &obj)
{
	double norm = obj.Norm();
	x = obj.x/norm;	y = obj.y/norm;	z = obj.z/norm;

}

//【23】ユークリッドノルム
double CVector3d::Norm()
{
	return (sqrt( x*x + y*y + z*z ));
}

//【24】距離の計算
double CVector3d::Distance(CVector3d &obj)
{
	double X = x - obj.x;	
	double Y = y - obj.y;
	double Z = z - obj.z;
	return (sqrt( X*X + Y*Y + Z*Z));
}

//【24-2】距離の計算
double CVector3d::Distance(CPoint3d &obj)
{
	double X = x - obj.x;	
	double Y = y - obj.y;
	double Z = z - obj.z;
	return (sqrt( X*X + Y*Y + Z*Z));
}

//【25】ベクトルの内積
double CVector3d::Dot(CVector3d &obj)
{
	double dot = x * obj.x;
	dot += y * obj.y;
	dot += z * obj.z;
	return (dot);
}

//【25-2】ベクトルの内積
double CVector3d::Dot(CPoint3d &obj)
{
	double dot = x * obj.x;
	dot += y * obj.y;
	dot += z * obj.z;
	return (dot);
}

//【26】ベクトルの外積
CVector3d CVector3d::Cross(CVector3d &obj)
{
	CVector3d tmp;
	tmp.x = y*obj.z - z*obj.y;
	tmp.y = z*obj.x - x*obj.z;
	tmp.z = x*obj.y - y*obj.x;
	return (tmp);
}

//【26-2】ベクトルの外積
CVector3d CVector3d::Cross(CPoint3d &obj)
{
	CVector3d tmp;
	tmp.x = y*obj.z - z*obj.y;
	tmp.y = z*obj.x - x*obj.z;
	tmp.z = x*obj.y - y*obj.x;
	return (tmp);
}

//【27】aとの角度
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

//【27-2】aとの角度
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

//【28】Point-Line Distance
double CVector3d::PointLineDistance(CVector3d &P0, CVector3d &P1)
{
	CVector3d A = P1-P0;
	CVector3d B( x-P0.x, y-P0.y, z-P0.z);
	return ( (A.Cross(B)).Norm()/P0.Distance(P1) );
}

//【29】a点とのxyz各最大値を返す
CVector3d CVector3d::Max(CVector3d &obj)
{
	CVector3d tmp;
	tmp.x = max(x,obj.x);
	tmp.y = max(y,obj.y);
	tmp.z = max(z,obj.z);
	return (tmp);
}

//【29-2】a点とのxyz各最大値を返す
CVector3d CVector3d::Max(CPoint3d &obj)
{
	CVector3d tmp;
	tmp.x = max(x,obj.x);
	tmp.y = max(y,obj.y);
	tmp.z = max(z,obj.z);
	return (tmp);
}

//【30】a点とのxyz各最小値を返す
CVector3d CVector3d::Min(CVector3d &obj)
{
	CVector3d tmp;
	tmp.x = min(x,obj.x);
	tmp.y = min(y,obj.y);
	tmp.z = min(z,obj.z);
	return (tmp);
}

//【30-2】a点とのxyz各最小値を返す
CVector3d CVector3d::Min(CPoint3d &obj)
{
	CVector3d tmp;
	tmp.x = min(x,obj.x);
	tmp.y = min(y,obj.y);
	tmp.z = min(z,obj.z);
	return (tmp);
}

//【31】X軸周りにrad回転
CVector3d CVector3d::RotateX( double rad )
{
	CVector3d tmp;
	tmp.x = x;
	tmp.y = (y*cos(rad)) - (z*sin(rad));
	tmp.z = (y*sin(rad)) + (z*cos(rad));
	return (tmp);
}

//【32】Y軸周りにrad回転
CVector3d CVector3d::RotateY( double rad )
{
	CVector3d tmp;
	tmp.x = (z*sin(rad)) + (x*cos(rad));
	tmp.y = y;
	tmp.z = (z*cos(rad)) - (x*sin(rad));
	return (tmp);
}

//【33】Z軸周りにrad回転
CVector3d CVector3d::RotateZ( double rad )
{
	CVector3d tmp;
	tmp.x = (x*cos(rad)) - (y*sin(rad));
	tmp.y = (x*sin(rad)) + (y*cos(rad));
	tmp.z = z;
	return (tmp);
}

/*************** CPoint3dとの互換性 ***************/

//【10-2】=演算子オーバーロード
CVector3d& CVector3d::operator=(const CPoint3d& obj)
{
	x = obj.x;	y = obj.y;	z = obj.z;
	return *this;
}

//【11-2】+演算子オーバーロード
CVector3d CVector3d::operator+(const CPoint3d& obj)
{
	CVector3d tmp;
	tmp.x = x + obj.x;	tmp.y = y + obj.y;	tmp.z = z + obj.z;
	return (tmp);
}

//【12-2】+=演算子オーバーロード
CVector3d& CVector3d::operator+=(const CPoint3d& obj)
{
	x += obj.x;	y += obj.y;	z += obj.z;
	return *this;
}

//【13-2】-演算子オーバーロード
CVector3d CVector3d::operator-(const CPoint3d& obj)
{
	CVector3d tmp;
	tmp.x = x - obj.x;	tmp.y = y - obj.y;	tmp.z = z - obj.z;
	return (tmp);
}

//【14-2】-=演算子オーバーロード
CVector3d& CVector3d::operator-=(const CPoint3d& obj)
{
	x -= obj.x;	y -= obj.y;	z -= obj.z;
	return *this;
}