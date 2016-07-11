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
		//�l�̑傫�����̎}�𒲂ׂ�
				max=root*2+1;
		if(root*2+2<=size){//�Q�̎}�����݂���
			if(ar[root*2+1]<ar[root*2+2]){//�P�̎}�Ɣ�r����
				max=root*2+2;
			}
		}
		else if(!(root*2+1<=size)) break;//�P�̎}�����݂��Ȃ����ߏI��

		//�l�̑傫���ق��̎}�ƍ����ׂāA�l����������
		if(ar[root]<ar[max]){
			swap(&ar[root],&ar[max]);
			swap(&x_ar[root],&x_ar[max]);
			root=max;//�����ł������߁A�}�����ɂ���
		}
		else break;//���̕����傫�����ߏI��
	}
	return;
}

void heap_sort(int*ar,int*x_ar,int size ){
	//�q�[�v�쐬
	for(int i=(size/2);i>=0;i--){
		h_down(ar,x_ar,size,i);
	}
	//�q�[�v�\�[�g
	while(1){
		swap(&ar[0],&ar[size--]);
		size++;
        swap(&x_ar[0],&x_ar[size--]);
		if(!size) break;
		h_down(ar,x_ar,size,0);
	}
	return;
}


//�ȉ���Heap sort��double��
void swap_db(double*a, double*b){
    double c;
    c=*a;
	*a=*b;
	*b=c;
}

void h_down_db(double*ar,int*x_ar,int size,int root){
	int max;
	while(1){
		//�l�̑傫�����̎}�𒲂ׂ�
				max=root*2+1;
		if(root*2+2<=size){//�Q�̎}�����݂���
			if(ar[root*2+1]<ar[root*2+2]){//�P�̎}�Ɣ�r����
				max=root*2+2;
			}
		}
		else if(!(root*2+1<=size)) break;//�P�̎}�����݂��Ȃ����ߏI��

		//�l�̑傫���ق��̎}�ƍ����ׂāA�l����������
		if(ar[root]<ar[max]){
			swap_db(&ar[root],&ar[max]);
			swap(&x_ar[root],&x_ar[max]);
			root=max;//�����ł������߁A�}�����ɂ���
		}
		else break;//���̕����傫�����ߏI��
	}
	return;
}

void heap_sort_dbl(double*ar,int*x_ar,int size ){
	//�q�[�v�쐬
	for(int i=(size/2);i>=0;i--){
		h_down_db(ar,x_ar,size,i);
	}
	//�q�[�v�\�[�g
	while(1){
		swap_db(&ar[0],&ar[size--]);
		size++;
        swap(&x_ar[0],&x_ar[size--]);
		if(!size) break;
		h_down_db(ar,x_ar,size,0);
	}
	return;
}
//�ȏ��Heap sort��double��