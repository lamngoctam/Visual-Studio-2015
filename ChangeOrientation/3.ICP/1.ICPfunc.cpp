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
		temp(0, 0) = pointit->x;	//x W
		temp(1, 0) = pointit->y;	//y W
		temp(2, 0) = pointit->z;	//z W
		temp(3, 0) = 1.0;
		temp = mat*temp;			//mat~temp‚Ì’l‚ğtemp‚ÉŠi”[
		pointit->x = temp(0, 0);	//x•W‚ğXV
		pointit->y = temp(1, 0);	//y•W‚ğXV
		pointit->z = temp(2, 0);	//z•W‚ğXV

		++pointit;
	}

}

//
double CalcAveofPoint(vector<CVector3d> &up, vector<CVector3d> &down)
{
	double dist = 0.0;	//‹——£
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


//2013/7/14
//KdTree
void FindCorresPoint(vector<OnetoOne> &upone, vector<OnetoOne> &downone, MyKdTree& upTree, vector<CVector3d> &downsurf, const double thres)
{
	//double tempD;		//‹——£Ši”[—p
	int i(0);			//DOWN‚©‚ç‹——£‚ªÅ‚à‹ß‚¢‘Î‰“_‚ªDOWN•\–Ê”z—ñ‚Ì‰½–Ê–Ú‚©
	//int k(0);			//‹——£‚ªÅ‚à‹ß‚¢‘Î‰“_‚ªUP•\–Ê”z—ñ‚Ì‰½”Ô–Ú‚©
	MyNode NNnode;

	//#pragma omp parallel for private(k, tempD)
	for (i = 0; i<DOWN.SurfNum; i++)	//downƒ‚ƒfƒ‹‚Ì•\–Êƒ{ƒNƒZƒ‹
	{
		downone[i].flag = true;
		//step. 1 Qƒ‚ƒfƒ‹‚ÌŠe“_‚©‚çPƒ‚ƒfƒ‹‚ÌŠe“_‚Ö‚Ì‹——£‚ğ‹‚ß‚é

		//for(k = 0; k<UP.SurfNum; k++)		//upƒ‚ƒfƒ‹‚Ì•\–Êƒ{ƒNƒZƒ‹
		//{
		//	if(fabs(upsurf[k].x - downsurf[i].x) > thres)		//ŒvZŠÔ’Zk‚Ì‚½‚ß‚É
		//		continue;
		//	if(fabs(upsurf[k].y - downsurf[i].y) > thres)
		//		continue;	
		//	if(fabs(upsurf[k].z - downsurf[i].z) > thres)
		//		continue;

		//	tempD = downsurf[i].Distance(upsurf[k]);		//‹——£‚ÌŒvZ
		//	
		//	//step. 2 Qƒ‚ƒfƒ‹‚Ì‚P“_–ˆ‚ÉAÅ‹ß“_‚ğ‘I‘ğ
		//	//downƒ‚ƒfƒ‹‚Ì‚ ‚é“_‚É1”Ô‹ß‚¢upƒ‚ƒfƒ‹‚Ì“_‚Æ‚Ì‹——£‚ÆAupsurf‚Å‰½”Ô–Ú‚©
		//	if(tempD < downone[i].dist){
		//		downone[i].dist = tempD;		//‘Î‰“_‚Æ‚Ì‹——£
		//		downone[i].num = k;				//downsurf‚Ì i ”Ô–Ú‚Ì‚É‘Î‰‚·‚é‚Ì‚Íupsurf‚Ì k ”Ô–Ú‚Å‚ ‚é
		//	}
		//}

		upTree.searchNearestNeighbor(downsurf[i], NNnode);
		downone[i].dist = NNnode.point.Distance(downsurf[i]);		//‘Î‰“_‚Æ‚Ì‹——£
		downone[i].num = NNnode.index;				//downsurf‚Ì i ”Ô–Ú‚Ì‚É‘Î‰‚·‚é‚Ì‚Íupsurf‚Ì k ”Ô–Ú‚Å‚ ‚é


		//step. 3 Å‹ß“_‚Ì‹——£‚ªè‡’l‚¢‚È‚¢‚Å‚ ‚é‘Î‰“_‚ğÌ—p‚µA‚»‚¤‚Å‚È‚¢‚à‚Ì‚ÍœŠO
		//è‡’l‚Æ‚Ì”äŠrŒŸ“¢‚·‚é
		if (downone[i].dist > thres)		//
		{
			//
			downone[i].flag = false;
			upone[downone[i].num].flag = false;
			continue;		//step. 4‚
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
