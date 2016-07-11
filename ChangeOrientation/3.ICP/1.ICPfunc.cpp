#include "../stdafx.h"


extern Model UP;
extern Model DOWN;

//------------------------------------------------------------------------------------

void OutsideVoxeltoVector(Model &m, vector<CVector3d> &surf)
{
	for (vector<Voxel>::iterator it = m.SurfVoxels.begin(); it != m.SurfVoxels.end(); it++)
		surf.push_back((*it).center);
}

void RenewPointwithMatrix(vector<CVector3d> &point, CMatrix &mat)
{
	//mat
	vector<CVector3d>::iterator pointit = point.begin();
	CMatrix temp(4, 1);
	while (pointit != point.end())
	{
		temp(0, 0) = pointit->x;	//x� W
		temp(1, 0) = pointit->y;	//y� W
		temp(2, 0) = pointit->z;	//z� W
		temp(3, 0) = 1.0;
		temp = mat*temp;			//mat�~temp�̒l��temp�Ɋi�[
		pointit->x = temp(0, 0);	//x��W���X�V
		pointit->y = temp(1, 0);	//y��W���X�V
		pointit->z = temp(2, 0);	//z��W���X�V

		++pointit;
	}

}

//
double CalcAveofPoint(vector<CVector3d> &up, vector<CVector3d> &down)
{
	double dist = 0.0;	//����
	vector<CVector3d>::iterator upit = up.begin();
	vector<CVector3d>::iterator downit = down.begin();
	while (downit != down.end())
	{
		dist += (*downit).Distance((*upit));
		++upit;
		++downit;
	}
	return (dist / down.size());
}


//2013/7/14�
//KdTree
void FindCorresPoint(vector<OnetoOne> &upone, vector<OnetoOne> &downone, MyKdTree& upTree, vector<CVector3d> &downsurf, const double thres)
{
	//double tempD;		//�����i�[�p
	int i(0);			//DOWN���狗�����ł��߂��Ή��_��DOWN�\�ʔz��̉��ʖڂ�
	//int k(0);			//�������ł��߂��Ή��_��UP�\�ʔz��̉��Ԗڂ�
	MyNode NNnode;

	//#pragma omp parallel for private(k, tempD)
	for (i = 0; i<DOWN.SurfNum; i++)	//down���f���̕\�ʃ{�N�Z��
	{
		downone[i].flag = true;
		//step. 1 Q���f���̊e�_����P���f���̊e�_�ւ̋��������߂�

		//for(k = 0; k<UP.SurfNum; k++)		//up���f���̕\�ʃ{�N�Z��
		//{
		//	if(fabs(upsurf[k].x - downsurf[i].x) > thres)		//�v�Z���ԒZ�k�̂��߂�
		//		continue;
		//	if(fabs(upsurf[k].y - downsurf[i].y) > thres)
		//		continue;	
		//	if(fabs(upsurf[k].z - downsurf[i].z) > thres)
		//		continue;

		//	tempD = downsurf[i].Distance(upsurf[k]);		//�����̌v�Z
		//	
		//	//step. 2 Q���f���̂P�_���ɁA�ŋߓ_��I��
		//	//down���f���̂���_��1�ԋ߂�up���f���̓_�Ƃ̋����ƁAupsurf�ŉ��Ԗڂ�
		//	if(tempD < downone[i].dist){
		//		downone[i].dist = tempD;		//�Ή��_�Ƃ̋���
		//		downone[i].num = k;				//downsurf�� i �Ԗڂ̂ɑΉ�����̂�upsurf�� k �Ԗڂł���
		//	}
		//}

		upTree.searchNearestNeighbor(downsurf[i], NNnode);
		downone[i].dist = NNnode.point.Distance(downsurf[i]);		//�Ή��_�Ƃ̋���
		downone[i].num = NNnode.index;				//downsurf�� i �Ԗڂ̂ɑΉ�����̂�upsurf�� k �Ԗڂł���


		//step. 3 �ŋߓ_�̋�����臒l���Ȃ��ł���Ή��_���̗p���A�����łȂ����̂͏��O
		//臒l�Ƃ̔�r��������
		if (downone[i].dist > thres)		//
		{
			//
			downone[i].flag = false;
			upone[downone[i].num].flag = false;
			continue;		//step. 4�
		}

		//step. 4
		//
		if (upone[downone[i].num].flag == false)
		{
			upone[downone[i].num].dist = downone[i].dist;			
			upone[downone[i].num].num = i;									//
			upone[downone[i].num].flag = true;								//
		}
		//
		else
		{
			//
			if (upone[downone[i].num].dist < downone[i].dist)
				downone[i].Initial();
			//downone[i].flag = false;	//
			else	//upone[it->num].dist > it->dist
			{
				//downone[ upone[downone[i].num].num ].flag = false;
				downone[upone[downone[i].num].num].Initial();
				upone[downone[i].num].dist = downone[i].dist;
				upone[downone[i].num].num = i;
			}
		}

	}
}
