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
		//’l‚Ì‘å‚«‚¢•û‚Ì}‚ğ’²‚×‚é
				max=root*2+1;
		if(root*2+2<=size){//‚Q‚Ì}‚ª‘¶İ‚·‚é
			if(ar[root*2+1]<ar[root*2+2]){//‚P‚Ì}‚Æ”äŠr‚µ‚Ä
				max=root*2+2;
			}
		}
		else if(!(root*2+1<=size)) break;//‚P‚Ì}‚ª‘¶İ‚µ‚È‚¢‚½‚ßI—¹

		//’l‚Ì‘å‚«‚¢‚Ù‚¤‚Ì}‚Æª‚ğ”ä‚×‚ÄA’l‚ğŒğŠ·‚·‚é
		if(ar[root]<ar[max]){
			swap(&ar[root],&ar[max]);
			swap(&x_ar[root],&x_ar[max]);
			root=max;//ŒğŠ·‚Å‚«‚½‚½‚ßA}©ª‚É‚·‚é
		}
		else break;//ª‚Ì•û‚ª‘å‚«‚¢‚½‚ßI—¹
	}
	return;
}

void heap_sort(int*ar,int*x_ar,int size ){
	//ƒq[ƒvì¬
	for(int i=(size/2);i>=0;i--){
		h_down(ar,x_ar,size,i);
	}
	//ƒq[ƒvƒ\[ƒg
	while(1){
		swap(&ar[0],&ar[size--]);
		size++;
        swap(&x_ar[0],&x_ar[size--]);
		if(!size) break;
		h_down(ar,x_ar,size,0);
	}
	return;
}


//ˆÈ‰º‚ÍHeap sort‚Ìdouble”Å
void swap_db(double*a, double*b){
    double c;
    c=*a;
	*a=*b;
	*b=c;
}

void h_down_db(double*ar,int*x_ar,int size,int root){
	int max;
	while(1){
		//’l‚Ì‘å‚«‚¢•û‚Ì}‚ğ’²‚×‚é
				max=root*2+1;
		if(root*2+2<=size){//‚Q‚Ì}‚ª‘¶İ‚·‚é
			if(ar[root*2+1]<ar[root*2+2]){//‚P‚Ì}‚Æ”äŠr‚µ‚Ä
				max=root*2+2;
			}
		}
		else if(!(root*2+1<=size)) break;//‚P‚Ì}‚ª‘¶İ‚µ‚È‚¢‚½‚ßI—¹

		//’l‚Ì‘å‚«‚¢‚Ù‚¤‚Ì}‚Æª‚ğ”ä‚×‚ÄA’l‚ğŒğŠ·‚·‚é
		if(ar[root]<ar[max]){
			swap_db(&ar[root],&ar[max]);
			swap(&x_ar[root],&x_ar[max]);
			root=max;//ŒğŠ·‚Å‚«‚½‚½‚ßA}©ª‚É‚·‚é
		}
		else break;//ª‚Ì•û‚ª‘å‚«‚¢‚½‚ßI—¹
	}
	return;
}

void heap_sort_dbl(double*ar,int*x_ar,int size ){
	//ƒq[ƒvì¬
	for(int i=(size/2);i>=0;i--){
		h_down_db(ar,x_ar,size,i);
	}
	//ƒq[ƒvƒ\[ƒg
	while(1){
		swap_db(&ar[0],&ar[size--]);
		size++;
        swap(&x_ar[0],&x_ar[size--]);
		if(!size) break;
		h_down_db(ar,x_ar,size,0);
	}
	return;
}
//ˆÈã‚ÍHeap sort‚Ìdouble”Å