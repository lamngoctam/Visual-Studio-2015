#include "MyKdTree.h"

void MyKdTree::tellmeParent(MyNode *parent)
{
	//左の子nodeに子がいれば、そいつに親へのポインタを教える
	if(parent->left != NULL){
		parent->left->parent = parent;
		tellmeParent(parent->left);
	}
	//右の子nodeに子がいれば、そいつに親へのポインタを教える
	if(parent->right != NULL){
		parent->right->parent = parent;
		tellmeParent(parent->right);
	}
}

//２点間の距離の自乗を返す
double MyKdTree::squaredDistance(CVector3d a, CVector3d b)
{
	double X = a.x-b.x;
	double Y = a.y-b.y;
	double Z = a.z-b.z;
	return (X*X + Y*Y + Z*Z);
}

//やや早い　↓　参考サイト
//http://techtipshoge.blogspot.jp/2013/06/ck-d-tree.html
MyNode *MyKdTree::makeKdTree(std::vector<MyNode*>& points, int L, int R, int depth)
{
	if(L >= R){//点群が空だったら
		return NULL;		//子（左、または右）を持たない
	}
	else{
		// 深さに応じて軸を選択し、軸が順次選択されるようにする
		//→　ｘ軸、ｙ軸、ｚ軸のどれかを選択する
		int axis =  depth%3;		
		// 点のリストをソートし、中央値の点を選択する
		//X軸で分割する
		if(axis == 0)
			sort(points.begin() + L, points.begin() + R, MyNode::LessX);
		//Y軸で分割する
		else if(axis == 1)
			sort(points.begin() + L, points.begin() + R, MyNode::LessY);
		//Z軸で分割する
		else
			sort(points.begin() + L, points.begin() + R, MyNode::LessZ);

		int median = (L + R)/2;
		MyNode *node = new MyNode();
		node->point = points[median]->point;
		node->index = points[median]->index;
		node->depth = depth;									//nodeの深さを教える
		node->left = makeKdTree(points, L, median, depth+1);
		node->right = makeKdTree(points, median+1, R, depth+1);

		return node;
	}
}

//やや遅い
MyNode *MyKdTree::makeKdTree(std::vector<MyNode*>& points, int depth)
{
	if(points.empty()){//点群が空だったら
		return NULL;		//子（左、または右）を持たない
	}
	else{
		// 深さに応じて軸を選択し、軸が順次選択されるようにする
		//→　ｘ軸、ｙ軸、ｚ軸のどれかを選択する
		int axis =  depth%3;		
		// 点のリストをソートし、中央値の点を選択する
		//X軸で分割する
		if(axis == 0){
			sort(points.begin(), points.end(), MyNode::LessX);
		}
		//Y軸で分割する
		else if(axis == 1){
			sort(points.begin(), points.end(), MyNode::LessY);
		}
		//Z軸で分割する
		else{
			sort(points.begin(), points.end(), MyNode::LessZ);
		}

		//中央値を算出する
		int median = points.size()/2;
		MyNode *node= new MyNode();
		node->point = points[median]->point;			//中央値を決める
		node->index = points[median]->index;			//中央値を決める
		node->depth = depth;									//nodeの深さを教える

		vector<MyNode*> left_points(points.begin(), points.begin() + median);
		vector<MyNode*> right_points(points.begin() + median + 1, points.end());

		node->left = makeKdTree(left_points, depth+1);			//左の子のtree作成
		node->right = makeKdTree(right_points, depth+1);		//右の子のtree作成

		return node;
	}
}

//点群をインプットして、kdTreeを作成する
void MyKdTree::setInputCloud(vector<CVector3d>& points)
{
	clock_t time[2];	//時間を計る
	time[0] = clock();
	this->nodes.resize(points.size());
	for(unsigned int i = 0; i<points.size(); i++){
		this->nodes[i] = new MyNode;
		this->nodes[i]->point = points[i];		//その実体に値を格納する
		this->nodes[i]->index = i;						//その実体のINDEXを格納する
	}
	//this->root = this->makeKdTree(cloud, 0);
	this->root = this->makeKdTree(this->nodes, 0, points.size(), 0);
	tellmeParent(root);
	time[1] = clock();
	cout<<points.size()<<"KdTree:"<<(double)(time[1]-time[0])/CLOCKS_PER_SEC<<"[S]\n"<<endl;
}

//入力のsearch点を含む領域を探して、ノードへのポインタを返す
MyNode *MyKdTree::findRegion(CVector3d search)
{
	int axis;
	double S,P;			//S:search	P:parent
	MyNode *parent = this->root;
	int depth = root->depth;

	while(true){
		axis = depth%3;		//ｘ軸？？ｙ軸？？ｚ軸？？
		//###########
		//         x軸
		if(axis == 0){
			S = search.x;
			P = parent->point.x;
		}
		//###########
		//         y軸
		else if(axis ==1){
			S = search.y;
			P = parent->point.y;
		}
		//###########
		//          z軸
		else{
			S = search.z;
			P = parent->point.z;
		}
		//##################
		//左か右の子へ → S=Pとなる時は左に行くべきは右に行くべきかはわからない！！→故に領域探しは必ずしも正解とは限らない
		//##################
		//左側の子ノードへ
		if(S < P){
			if(parent->left == NULL){
				return parent;
			}
			else{
				depth++;
				parent = parent->left;
			}
		}
		//右側の子ノードへ
		else{
			if(parent->right == NULL){
				return parent;
			}
			else{
				depth++;
				parent = parent->right;
			}
		}

	}

}

void MyKdTree::searchNearestNeighbor(CVector3d search, MyNode &NNnode)
{
	//######################################
	//①最初のステップ：サーチ点（クエリ）を含む領域を見つける
	//######################################
	//		→		領域の親ノードとの距離を計算する（暫定的な最近傍解とする）
	MyNode *tempNN = findRegion(search);				//暫定的な最近傍点を返す
	double squaredDist_min = this->squaredDistance(search, tempNN->point);	//暫定的な最近傍点との自乗距離を返す
	double dist_min = sqrt(squaredDist_min);												//距離

	NNnode = *tempNN;			//最近傍解をとりあえず暫定解とする

	//######################################
	//②再帰的に親を登っていきより近い点があったら更新する
	//######################################
	//1.子と比較
	int axis = (tempNN->depth)%3;
	double dist, squaredDist;
	vector<MyNode*> parent;
	MyNode *temp = tempNN;

	while(true){
		parent.push_back(temp);
		if(temp->depth == 0){
			break;
		}
		temp = temp->parent;
	}
	//左の子ノードがあれば
	if(	parent[0]->left != NULL){
		searchNearestNeghborAtBranch(search, NNnode, parent[0]->left, squaredDist_min, dist_min);
	}
	//右の子ノードがあれば
	else if(parent[0]->right != NULL){
		searchNearestNeghborAtBranch(search, NNnode, parent[0]->right, squaredDist_min, dist_min);
	}
	//2.再帰的に（再帰関数を使わない）(i=0は暫定解)暫定解の親からスタートして、根に到着するまで行う
	for(unsigned int i=1; i<parent.size(); i++){
		//2.1親との距離比較
		axis = (parent[i]->depth)%3;
		if(axis == 0)
			dist = fabs(parent[i]->point.x - search.x) ;
		else if(axis == 1)
			dist = fabs(parent[i]->point.y - search.y) ;
		else
			dist = fabs(parent[i]->point.z - search.z);
		//更新
		//交わるとき(交わらない場合は何もしない)	
		if(dist <= dist_min){
			squaredDist = this->squaredDistance(parent[i]->point, search);		
			//距離自乗を計算して近かったら更新
			if(squaredDist <= squaredDist_min){
				NNnode = *parent[i];
				squaredDist_min = squaredDist;
				dist_min = sqrt(squaredDist);
			}
			//2.2親のもう一方の子との距離比較
			if(parent[i]->left != NULL && parent[i]->left != parent[i-1] && parent[i]->right == parent[i-1]){
				searchNearestNeghborAtBranch(search, NNnode, parent[i]->left, squaredDist_min, dist_min);
			}
			else if(parent[i]->right != NULL && parent[i]->right != parent[i-1] && parent[i]->left == parent[i-1]){
				searchNearestNeghborAtBranch(search, NNnode, parent[i]->right, squaredDist_min, dist_min);
			}

		}
	}

}

////①調査点、②最近点、③調査する点、④距離の自乗、⑤距離
//void MyKdTree::searchNearestNeghborAtBranch(CVector3d search, MyNode &NNnode, MyNode *parent, double& squaredDist_min , double& dist_min)
//{
//	int axis = (parent->depth)%3;
//	double dist;
//	double squaredDist;
//
//	//親との距離を計算する
//	if(axis == 0)
//		dist = fabs(parent->point.x - search.x) ;
//	else if(axis == 1)
//		dist = fabs(parent->point.y - search.y) ;
//	else
//		dist = fabs(parent->point.z - search.z) ;
//
//	//境界と交わる場合　→　両方の子
//	if(dist <= dist_min){
//		//距離を計算する
//		squaredDist = squaredDistance(parent->point, search);
//		if(squaredDist < squaredDist_min){
//			//cout<<"枝前："<<NNnode.index<<" "<<NNnode.point.x<<" "<<NNnode.point.y<<", "<<NNnode.point.z<<"	"<<squaredDist_min<<"	"<<dist_min<<endl;
//			NNnode = *parent;
//			squaredDist_min = squaredDist;
//			dist_min = sqrt(squaredDist);
//			//cout<<"枝後："<<NNnode.index<<" "<<NNnode.point.x<<" "<<NNnode.point.y<<", "<<NNnode.point.z<<"	"<<squaredDist_min<<"	"<<dist_min<<endl;
//		}
//	}
//	//左の子
//	if(parent->left != NULL)
//		searchNearestNeghborAtBranch(search, NNnode, parent->left, squaredDist_min, dist_min);
//	//右の子
//	if(parent->right != NULL)
//		searchNearestNeghborAtBranch(search, NNnode, parent->right, squaredDist_min, dist_min);
//}

void MyKdTree::searchNearestNeghborAtBranch(CVector3d search, MyNode &NNnode, MyNode *parent, double& squaredDist_min , double& dist_min)
{
	//##########################
	//球との距離を計算する
	//##########################
	int axis = (parent->depth)%3;
	double S,P;
	if(axis == 0){
		P = parent->point.x;
		S = search.x;
	}
	else if(axis == 1){
		P = parent->point.y;
		S = search.y;
	}
	else{
		P = parent->point.z;
		S = search.z;
	}
	//##########################
	//球と交わる場合　→　両方の子の部分枝
	//##########################
	double squaredDist;
	if(fabs(S - P) <= dist_min){
		//距離を計算する
		squaredDist = squaredDistance(parent->point, search);
		if(squaredDist < squaredDist_min){
			//cout<<"枝前："<<NNnode.index<<" "<<NNnode.point.x<<" "<<NNnode.point.y<<", "<<NNnode.point.z<<"	"<<squaredDist_min<<"	"<<dist_min<<endl;
			NNnode = *parent;
			squaredDist_min = squaredDist;
			dist_min = sqrt(squaredDist);
			//cout<<"枝後："<<NNnode.index<<" "<<NNnode.point.x<<" "<<NNnode.point.y<<", "<<NNnode.point.z<<"	"<<squaredDist_min<<"	"<<dist_min<<endl;
		}
		//左の子
		if(parent->left != NULL)
			searchNearestNeghborAtBranch(search, NNnode, parent->left, squaredDist_min, dist_min);
		//右の子
		if(parent->right != NULL)
			searchNearestNeghborAtBranch(search, NNnode, parent->right, squaredDist_min, dist_min);
	}
	//##########################
	//球と交わらない場合　→　一方の子の部分枝のみ
	//##########################
	else{
		if(S < P){
			//左の子
			if(parent->left != NULL)
				searchNearestNeghborAtBranch(search, NNnode, parent->left, squaredDist_min, dist_min);
		}
		else{
			//右の子
			if(parent->right != NULL)
				searchNearestNeghborAtBranch(search, NNnode, parent->right, squaredDist_min, dist_min);
		}
	}

}
