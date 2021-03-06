//######################
//Kdtreeクラスの使用法:
//�@点群（ここでは点の型はMyPoint3D）を読み込む
//�AMyKdTree型の実体を生成
//�Bvoid setInputCloud(vector<MyPoint3D>& points);を使ってKdTreeを構築する
//�Cvoid searchNearestNeighbor(MyPoint3D search, MyNode &NNnode);を使って探したい最近点の最近傍点を探す
//######################

#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>		//時間を量りたい
#include "l3.h"

using namespace std;

//class MyPoint3D;
class MyNode;
class MyKdTree;

//######################
// KdTreeＯode class
//######################
class MyNode
{
public:
	int index;			//巧NDEX
	int depth;
	CVector3d point;
	MyNode *left;		//航node
	MyNode *right;	    //qnode
	MyNode *parent;		//親node

	MyNode(void) :index(0), depth(0){};
	~MyNode(void){};

	static bool LessX(const MyNode *a, const MyNode *b){
		return a->point.x < b->point.x;
	};
	static bool LessY(const MyNode *a, const MyNode *b){
		return a->point.y < b->point.y;
	};
	static bool LessZ(const MyNode *a, const MyNode *b){
		return a->point.z < b->point.z;
	};

};

//######################
// KdTreeＤlass
//######################
class MyKdTree
{
public:
	MyKdTree(void){};
	~MyKdTree(void){};
	void setInputCloud(vector<CVector3d>& points);
	void searchNearestNeighbor(CVector3d search, MyNode &NNnode);

private:
	MyNode *root;						//kdtree
	vector<MyNode*> nodes;		//node
	// KdTree
	MyNode* makeKdTree(std::vector<MyNode*>& nodes, int left, int right, int depth);
	MyNode* makeKdTree(std::vector<MyNode*>& nodes, int depth);
	void tellmeParent(MyNode *parent);
	//
	double squaredDistance(CVector3d a, CVector3d b);
	MyNode *findRegion(CVector3d search);
	void searchNearestNeghborAtBranch(CVector3d search, MyNode &NNnode, MyNode *node, double& squaredDist_min, double& dist_min);
};

