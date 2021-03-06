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
		temp = mat*temp;			//mat~tempΜlπtempΙi[
		pointit->x = temp(0, 0);	//xWπXV
		pointit->y = temp(1, 0);	//yWπXV
		pointit->z = temp(2, 0);	//zWπXV

		++pointit;
	}

}

//
double CalcAveofPoint(vector<CVector3d> &up, vector<CVector3d> &down)
{
	double dist = 0.0;	//£
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
	//double tempD;		//£i[p
	int i(0);			//DOWN©η£ͺΕΰί’Ξ_ͺDOWN\ΚzρΜ½ΚΪ©
	//int k(0);			//£ͺΕΰί’Ξ_ͺUP\ΚzρΜ½ΤΪ©
	MyNode NNnode;

	//#pragma omp parallel for private(k, tempD)
	for (i = 0; i<DOWN.SurfNum; i++)	//downfΜ\Κ{NZ
	{
		downone[i].flag = true;
		//step. 1 QfΜe_©ηPfΜe_ΦΜ£πίι

		//for(k = 0; k<UP.SurfNum; k++)		//upfΜ\Κ{NZ
		//{
		//	if(fabs(upsurf[k].x - downsurf[i].x) > thres)		//vZΤZkΜ½ίΙ
		//		continue;
		//	if(fabs(upsurf[k].y - downsurf[i].y) > thres)
		//		continue;	
		//	if(fabs(upsurf[k].z - downsurf[i].z) > thres)
		//		continue;

		//	tempD = downsurf[i].Distance(upsurf[k]);		//£ΜvZ
		//	
		//	//step. 2 QfΜP_ΙAΕί_πIπ
		//	//downfΜ ι_Ι1Τί’upfΜ_ΖΜ£ΖAupsurfΕ½ΤΪ©
		//	if(tempD < downone[i].dist){
		//		downone[i].dist = tempD;		//Ξ_ΖΜ£
		//		downone[i].num = k;				//downsurfΜ i ΤΪΜΙΞ·ιΜΝupsurfΜ k ΤΪΕ ι
		//	}
		//}

		upTree.searchNearestNeighbor(downsurf[i], NNnode);
		downone[i].dist = NNnode.point.Distance(downsurf[i]);		//Ξ_ΖΜ£
		downone[i].num = NNnode.index;				//downsurfΜ i ΤΪΜΙΞ·ιΜΝupsurfΜ k ΤΪΕ ι


		//step. 3 Εί_Μ£ͺθl’Θ’Ε ιΞ_πΜp΅A»€ΕΘ’ΰΜΝO
		//θlΖΜδr’·ι
		if (downone[i].dist > thres)		//
		{
			//
			downone[i].flag = false;
			upone[downone[i].num].flag = false;
			continue;		//step. 4
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
