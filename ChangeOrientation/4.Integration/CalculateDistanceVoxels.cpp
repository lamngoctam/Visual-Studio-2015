#include "../stdafx.h"


void SetSurfDist(Model& m, vector<Voxel>& knownV);
void SetTrial(Model& m, vector<Voxel>& knownV, vector<Voxel>& trialV);
void CalcTrialDist(Model& m, vector<Voxel>& trialV);
void CountDistMinNum(vector<Voxel>& trialV, int& countmin);
void SetTrailMinToKnown(vector<Voxel>& knownV, Model& m);
void SetInnerVoxelDistMinus(Model& m);

void CalculateDistance_AllVoxel(Model& m)
{
	cout << "\nCalculateDistance all Voxels :" << endl;
	vector<Voxel> trialV;		
	vector<Voxel> knownV;		
	int countmin;				
	int loopnum(0);				

	//double Dist_Thres(10.0);	

	//�
	SetSurfDist(m, knownV);

	while (true){
		++loopnum;
		//cout<<loopnum<<"��ځ@"<<"trial�{�N�Z�����@loop�O�F"<<trialV.size()<<" "<<trialV.capacity();

		//
		SetTrial(m, knownV, trialV);

		//
		CalcTrialDist(m, trialV);

		//
		sort(trialV.begin(), trialV.end(), Voxel::Lessdist);

		//
		countmin = 0;
		CountDistMinNum(trialV, countmin);

		
		knownV.clear();			
		knownV.resize(countmin);
		copy(trialV.begin(), trialV.begin() + countmin, knownV.begin());

		
		SetTrailMinToKnown(knownV, m);

	
		trialV.erase(trialV.begin(), trialV.begin() + countmin);
		trialV.shrink_to_fit();

		if (trialV.empty())
		{
			cout << "<-----loopnum---- " << loopnum << endl;
			break;
		}
	}
	knownV.clear();
	knownV.shrink_to_fit();
	
	SetInnerVoxelDistMinus(m);
}

//Fast Merching Method
void CalculateDistance(Model& m)
{
	cout << "CalculateDistance: " << endl;
	vector<Voxel> trialV;			
	vector<Voxel> knownV;		
	int countmin;						//trialdist
	int loopnum(0);					

	double Dist_Thres(10.0);		

	SetSurfDist(m, knownV);              //knownV: Integ.voxel[][][]

	while (true){
		++loopnum;
		//cout<<loopnum<<" "<<"trial loop�O�F"<<trialV.size()<<" "<<trialV.capacity();

		//known�trial�
		SetTrial(m, knownV, trialV);

		//trial
		CalcTrialDist(m, trialV);

		//trial�[(dist)
		sort(trialV.begin(), trialV.end(), Voxel::Lessdist);

		//dist
		countmin = 0;
		CountDistMinNum(trialV, countmin);

		//�dist�known
		knownV.clear();			//known
		knownV.resize(countmin);
		copy(trialV.begin(), trialV.begin() + countmin, knownV.begin());

		//known status�trial�known�
		SetTrailMinToKnown(knownV, m);

		//known trial
		trialV.erase(trialV.begin(), trialV.begin() + countmin);
		trialV.shrink_to_fit();

		//cout<<"�    "<<trialV.size()<<" "<<trialV.capacity()<<endl;
		//trial
		if (trialV.empty() || (knownV.begin()->dist) > Dist_Thres)
		{
			cout <<"loopnum:" << loopnum << endl;
			break;
		}
	}
	//
	SetInnerVoxelDistMinus(m);
}

//
void SetSurfDist(Model& m, vector<Voxel>& knownV)
{
	knownV.reserve(m.SurfNum);
	int x, y, z;
	for (x = 1; x<m.num[0] - 1; x++)
	{
		for (y = 1; y<m.num[1] - 1; y++)
		{
			for (z = 1; z<m.num[2] - 1; z++)
			{
				if (m.Voxels[x][y][z].surf)	//�\�ʃ{�N�Z���̎�
				{
					m.Voxels[x][y][z].dist = 0.0;						//�\�ʃ{�N�Z���̋��� = 0.0
					m.Voxels[x][y][z].SetKnown();					//known�ɃZ�b�g����
					knownV.push_back(m.Voxels[x][y][z]);		//known�z��ɑł�����
				}
			}
		}
	}
	knownV.shrink_to_fit();	//����ʃ������̈�����
}

//known trial�  // let trial be the point in close with the smallest T value

void SetTrial(Model& m, vector<Voxel>& knownV, vector<Voxel>& trialV)
{
	cv::Point3i temp(0, 0, 0);
	vector<Voxel>::iterator knownit = knownV.begin();

	while (knownit != knownV.end())
	{
		temp.x = knownit->coord.x;
		temp.y = knownit->coord.y;
		temp.z = knownit->coord.z;

		//(x - 1)
		if (0 < temp.x)			
		{
			if (m.Voxels[temp.x - 1][temp.y][temp.z].unknown)	
			{
				if (m.Voxels[temp.x - 1][temp.y][temp.z].pushed == false)	
				{
					m.Voxels[temp.x - 1][temp.y][temp.z].SetTrial();
					trialV.push_back(m.Voxels[temp.x - 1][temp.y][temp.z]);
					m.Voxels[temp.x - 1][temp.y][temp.z].pushed = true;
				}
			}
		}
		//�O(x + 1)
		if (temp.x + 1 < m.num[0])	//�{�N�Z�������݂���Ȃ�
		{
			if (m.Voxels[temp.x + 1][temp.y][temp.z].unknown)	//���������v�Z�Ȃ�
			{
				if (m.Voxels[temp.x + 1][temp.y][temp.z].pushed == false)	//���h�~(�v�Z���Ԑߖ�)
				{
					m.Voxels[temp.x + 1][temp.y][temp.z].SetTrial();
					trialV.push_back(m.Voxels[temp.x + 1][temp.y][temp.z]);
					m.Voxels[temp.x + 1][temp.y][temp.z].pushed = true;
				}
			}
		}
		//�E(y - 1)
		if (0 < temp.y)			//�{�N�Z�������݂���Ȃ�
		{
			if (m.Voxels[temp.x][temp.y - 1][temp.z].unknown)	//���������v�Z�Ȃ�
			{
				if (m.Voxels[temp.x][temp.y - 1][temp.z].pushed == false)	//���h�~(�v�Z���Ԑߖ�)
				{
					m.Voxels[temp.x][temp.y - 1][temp.z].SetTrial();
					trialV.push_back(m.Voxels[temp.x][temp.y - 1][temp.z]);
					m.Voxels[temp.x][temp.y - 1][temp.z].pushed = true;
				}
			}
		}
		//��(y + 1)
		if (temp.y + 1 < m.num[1])	//�{�N�Z�������݂���Ȃ�
		{
			if (m.Voxels[temp.x][temp.y + 1][temp.z].unknown)	//���������v�Z�Ȃ�
			{
				if (m.Voxels[temp.x][temp.y + 1][temp.z].pushed == false)	//���h�~(�v�Z���Ԑߖ�)
				{
					m.Voxels[temp.x][temp.y + 1][temp.z].SetTrial();
					trialV.push_back(m.Voxels[temp.x][temp.y + 1][temp.z]);
					m.Voxels[temp.x][temp.y + 1][temp.z].pushed = true;
				}
			}
		}
		//��(z - 1)
		if (0 < temp.z)			//�{�N�Z�������݂���Ȃ�
		{
			if (m.Voxels[temp.x][temp.y][temp.z - 1].unknown)	//���������v�Z�Ȃ�
			{
				if (m.Voxels[temp.x][temp.y][temp.z - 1].pushed == false)	//���h�~(�v�Z���Ԑߖ�)
				{
					m.Voxels[temp.x][temp.y][temp.z - 1].SetTrial();
					trialV.push_back(m.Voxels[temp.x][temp.y][temp.z - 1]);
					m.Voxels[temp.x][temp.y][temp.z - 1].pushed = true;
				}
			}
		}
		//��(z + 1)
		if (temp.z + 1< m.num[2])		//�{�N�Z�������݂���Ȃ�
		{
			if (m.Voxels[temp.x][temp.y][temp.z + 1].unknown)	//���������v�Z�Ȃ�
			{
				if (m.Voxels[temp.x][temp.y][temp.z + 1].pushed == false)	//���h�~(�v�Z���Ԑߖ�)
				{
					m.Voxels[temp.x][temp.y][temp.z + 1].SetTrial();
					trialV.push_back(m.Voxels[temp.x][temp.y][temp.z + 1]);
					m.Voxels[temp.x][temp.y][temp.z + 1].pushed = true;
				}
			}
		}
		++knownit;
	}
	trialV.shrink_to_fit();	//����ʃ������̈�����
}

//trial
void CalcTrialDist(Model& m, vector<Voxel>& trialV)
{
	cv::Point3i temp(0, 0, 0);
	vector<Voxel>::iterator trialit = trialV.begin();
	//� a x^2 + b x + c = 0�
	double a(0.0);		//x^2�
	double b(0.0);		//x�
	double c(0.0);		//

	//
	//double hx(m.Voxels[0][0][0].length);
	//double hy(m.Voxels[0][0][0].length);
	//double hz(m.Voxels[0][0][0].length);
	//double hx(m.Voxels[0][0][0].length);
	//double hy(m.Voxels[0][0][0].length);
	//double hz(m.Voxels[0][0][0].height);	
	//double hx = 1.0;
	//double hy = 1.0;
	//double hz = 1.0;

	double hx = 1.0;
	double hy = 1.0;
	double hz = 1.2;

	while (trialit != trialV.end())	//trial
	{
		temp.x = trialit->coord.x;
		temp.y = trialit->coord.y;
		temp.z = trialit->coord.z;
		a = 0.0;
		b = 0.0;
		c = 0.0;
		//��(x - 1)
		if (0 < temp.x)			//
		{
			if (m.Voxels[temp.x - 1][temp.y][temp.z].known)	//
			{
				a += 1.0 / hx / hx;
				b += -2.0 / hx / hx*m.Voxels[temp.x - 1][temp.y][temp.z].dist;
				c += 1.0 / hx / hx*m.Voxels[temp.x - 1][temp.y][temp.z].dist*m.Voxels[temp.x - 1][temp.y][temp.z].dist;
			}
		}
		//�O(x + 1)
		if (temp.x + 1 < m.num[0])	//
		{
			if (m.Voxels[temp.x + 1][temp.y][temp.z].known)	//���
			{
				a += 1.0 / hx / hx;
				b += -2.0 / hx / hx*m.Voxels[temp.x + 1][temp.y][temp.z].dist;
				c += 1.0 / hx / hx*m.Voxels[temp.x + 1][temp.y][temp.z].dist*m.Voxels[temp.x + 1][temp.y][temp.z].dist;
			}
		}
		//�E(y - 1)
		if (0 < temp.y)			//�{�N�Z�������݂���Ȃ�
		{
			if (m.Voxels[temp.x][temp.y - 1][temp.z].known)	//���
			{
				a += 1.0 / hy / hy;
				b += -2.0 / hy / hy*m.Voxels[temp.x][temp.y - 1][temp.z].dist;
				c += 1.0 / hy / hy*m.Voxels[temp.x][temp.y - 1][temp.z].dist*m.Voxels[temp.x][temp.y - 1][temp.z].dist;
			}
		}
		//��(y + 1)
		if (temp.y + 1 < m.num[1])	//�{�N�Z�������݂���Ȃ�
		{
			if (m.Voxels[temp.x][temp.y + 1][temp.z].known)	//���������m�Ȃ�
			{
				a += 1.0 / hy / hy;
				b += -2.0 / hy / hy*m.Voxels[temp.x][temp.y + 1][temp.z].dist;
				c += 1.0 / hy / hy*m.Voxels[temp.x][temp.y + 1][temp.z].dist*m.Voxels[temp.x][temp.y + 1][temp.z].dist;
			}
		}
		//��(z - 1)
		if (0 < temp.z)			//�{�N�Z�������݂���Ȃ�
		{
			if (m.Voxels[temp.x][temp.y][temp.z - 1].known)	//���������m�Ȃ�
			{
				a += 1.0 / hz / hz;
				b += -(2.0 / hz / hz)*(m.Voxels[temp.x][temp.y][temp.z - 1].dist);
				c += (1.0 / hz / hz)*(m.Voxels[temp.x][temp.y][temp.z - 1].dist)*(m.Voxels[temp.x][temp.y][temp.z - 1].dist);
			}
		}
		//��(z + 1)
		if (temp.z + 1 < m.num[2])		//�{�N�Z�������݂���Ȃ�
		{
			if (m.Voxels[temp.x][temp.y][temp.z + 1].known)	//���������m�Ȃ�
			{
				a += 1.0 / hz / hz;
				b += -(2.0 / hz / hz)*m.Voxels[temp.x][temp.y][temp.z + 1].dist;
				c += (1.0 / hz / hz)*m.Voxels[temp.x][temp.y][temp.z + 1].dist*m.Voxels[temp.x][temp.y][temp.z + 1].dist;
			}
		}
		c += -1.0; //(F = 1)

		double D = b*b - 4.0*a*c;

		if (D > 0.0)		//������������
		{
			//cout<<"������������!"<<endl;
			trialit->dist = (-b + sqrt(D)) / 2.0 / a;
			m.Voxels[temp.x][temp.y][temp.z].dist = (-b + sqrt(D)) / 2.0 / a;	//�Ȃ��+�H
		}
		else if (D == 0.0)	//�d��������
		{
			//cout<<"�d��������!"<<endl;
			trialit->dist = -b / 2.0 / a;
			m.Voxels[temp.x][temp.y][temp.z].dist = -b / 2.0 / a;
		}
		else			//���f����������
		{
			cout << "Phuong trinh ko co nghiem D<0 : D= " << D << endl;
		}
		++trialit;
	}
}

//trial
void CountDistMinNum(vector<Voxel>& trialV, int& countmin)
{
	double minDist = trialV.begin()->dist;	//trial

	vector<Voxel>::iterator trialit = trialV.begin();

	while (trialit != trialV.end())
	{
		//if(trialit->dist == minDist)		
		if (trialit->dist <= minDist + 0.05)	
		{
			++countmin;
		}
		else{
			break;
		}
		++trialit;
	}
}

//known�status�trial�known�
void SetTrailMinToKnown(vector<Voxel>& knownV, Model& m)
{
	vector<Voxel>::iterator knownit = knownV.begin();
	while (knownit != knownV.end())
	{
		m.Voxels[knownit->coord.x][knownit->coord.y][knownit->coord.z].SetKnown();
		++knownit;
	}
}

//
void SetInnerVoxelDistMinus(Model& m)
{
	double min(0.0);		//2013/10/11

	for (int x = 1; x<m.num[0] - 1; ++x){
		for (int y = 1; y<m.num[1] - 1; ++y){
			for (int z = 1; z<m.num[2] - 1; ++z){
				if (m.Voxels[x][y][z].fill)		//�����{�N�Z���ł���
				{
					if (m.Voxels[x][y][z].surf == false)		//�\�ʃ{�N�Z���ł͂Ȃ�
					{
						m.Voxels[x][y][z].dist = -m.Voxels[x][y][z].dist;
						if (m.Voxels[x][y][z].dist < min)
							min = m.Voxels[x][y][z].dist;
					}
				}
			}
		}
	}
	m.MinDist = min;
}

