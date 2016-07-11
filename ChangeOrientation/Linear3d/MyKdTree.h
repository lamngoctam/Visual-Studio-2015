//######################
//KdtreeƒNƒ‰ƒX‚Ìg—p–@:
//‡@“_ŒQi‚±‚±‚Å‚Í“_‚ÌŒ^‚ÍMyPoint3Dj‚ğ“Ç‚İ‚Ş
//‡AMyKdTreeŒ^‚ÌÀ‘Ì‚ğ¶¬
//‡Bvoid setInputCloud(vector<MyPoint3D>& points);‚ğg‚Á‚ÄKdTree‚ğ\’z‚·‚é
//‡Cvoid searchNearestNeighbor(MyPoint3D search, MyNode &NNnode);‚ğg‚Á‚Ä’T‚µ‚½‚¢Å‹ß“_‚ÌÅ‹ß–T“_‚ğ’T‚·
//######################

#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>		//ŠÔ‚ğ—Ê‚è‚½‚¢
#include "l3.h"

using namespace std;

//class MyPoint3D;
class MyNode;
class MyKdTree;

//######################
// KdTree‚node class
//######################
class MyNode
{
public:
	int index;			//INDEX
	int depth;
	CVector3d point;
	MyNode *left;		//qnode
	MyNode *right;	    //qnode
	MyNode *parent;		//enode

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
// KdTree‚class
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

