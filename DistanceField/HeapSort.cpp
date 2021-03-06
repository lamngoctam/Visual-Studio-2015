#include "stdafx.h"
using namespace std;

void swap(int*a, int*b){
    int c;
    c=*a;
	*a=*b;
	*b=c;
}

void h_down(int*ar,int*x_ar,int size,int root){
	int max;
	while(1){
		//値の大きい方の枝を調べる
				max=root*2+1;
		if(root*2+2<=size){//２の枝が存在する
			if(ar[root*2+1]<ar[root*2+2]){//１の枝と比較して
				max=root*2+2;
			}
		}
		else if(!(root*2+1<=size)) break;//１の枝が存在しないため終了

		//値の大きいほうの枝と根を比べて、値を交換する
		if(ar[root]<ar[max]){
			swap(&ar[root],&ar[max]);
			swap(&x_ar[root],&x_ar[max]);
			root=max;//交換できたため、枝←根にする
		}
		else break;//根の方が大きいため終了
	}
	return;
}

void heap_sort(int*ar,int*x_ar,int size ){
	//ヒープ作成
	for(int i=(size/2);i>=0;i--){
		h_down(ar,x_ar,size,i);
	}
	//ヒープソート
	while(1){
		swap(&ar[0],&ar[size--]);
		size++;
        swap(&x_ar[0],&x_ar[size--]);
		if(!size) break;
		h_down(ar,x_ar,size,0);
	}
	return;
}


//以下はHeap sortのdouble版
void swap_db(double*a, double*b){
    double c;
    c=*a;
	*a=*b;
	*b=c;
}

void h_down_db(double*ar,int*x_ar,int size,int root){
	int max;
	while(1){
		//値の大きい方の枝を調べる
				max=root*2+1;
		if(root*2+2<=size){//２の枝が存在する
			if(ar[root*2+1]<ar[root*2+2]){//１の枝と比較して
				max=root*2+2;
			}
		}
		else if(!(root*2+1<=size)) break;//１の枝が存在しないため終了

		//値の大きいほうの枝と根を比べて、値を交換する
		if(ar[root]<ar[max]){
			swap_db(&ar[root],&ar[max]);
			swap(&x_ar[root],&x_ar[max]);
			root=max;//交換できたため、枝←根にする
		}
		else break;//根の方が大きいため終了
	}
	return;
}

void heap_sort_dbl(double*ar,int*x_ar,int size ){
	//ヒープ作成
	for(int i=(size/2);i>=0;i--){
		h_down_db(ar,x_ar,size,i);
	}
	//ヒープソート
	while(1){
		swap_db(&ar[0],&ar[size--]);
		size++;
        swap(&x_ar[0],&x_ar[size--]);
		if(!size) break;
		h_down_db(ar,x_ar,size,0);
	}
	return;
}
//以上はHeap sortのdouble版