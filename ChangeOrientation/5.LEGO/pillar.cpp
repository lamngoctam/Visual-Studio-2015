#include "../stdafx.h"
#include "../Voxel.h"
#include "../Lego.h"		//LEGOブロックを組み立てるためのクラス

//それぞれのパーツのID
extern int ID12;			//１×２を区別するためのID
extern int ID13;			//１×３を区別するためのID
extern int ID14;			//１×４を区別するためのID
extern int ID22;			//２×２を区別するためのID
extern int ID23;			//２×３を区別するためのID
extern int ID24;			//２×４を区別するためのID

extern int num11;		//１×１のブロックの数
extern int num12;		//１×２のブロックの数
extern int num13;		//１×３のブロックの数
extern int num14;		//１×４のブロックの数
extern int num22;		//２×２のブロックの数
extern int num23;		//２×３のブロックの数
extern int num24;		//２×４のブロックの数

class cood;

void change_bricks( Lego*** block,int x,int y,int z,int  col,int row,int IDs,int flags);
bool counter( Lego*** block,int x,int y,int z,int  col,int row);
cood centroid(Lego*** block,int x,int y,int z,int  col,int row);

class cood
{
public:
	int x,y,z,zcoord;
	bool sturt,trail;
	void set(int i, int j ,int k){
		x=i;y=j;z=k;
	}
	void clear(){
		x=0;y=0;z=0;
	}
	cood(){
		sturt=false;
		trail=false;
		x=0;
		y=0;
		z=0;
		zcoord=0;
	}
	~cood(){}
};


void make_pillar( Lego*** block,Model& m, int* VoxSize){

	vector<cood> Inner_surf;
	vector<cood> Inner_pillar;
	cood temp;
	//内部の表面ボクセルを見つける
		int x,y,z;
	for(z=1; z < VoxSize[2]-1; z = z + 1 )				//ｚ＝1,3,5,...
	{
		for(x=1; x < VoxSize[0]-1; x = x + 1)
		{
			for(y=1; y < VoxSize[1]-1; y = y + 1)
			{
				if(!block[x][y][z].fill)continue;
				if(m.Voxels[x][y][z].dist>=0.0)continue;
				if(block[x][y][z].surf)continue;
					//ボクセルの上下、左右、前後に其々ボクセルが存在するか？
					//X軸の正の方向を進む方向と考えて
					//上(z + 1)
					if(block[x][y][z+1].fill == false)
					{
						block[x][y][z].in_surf = true;
						continue;
					}
					//下(z - 1)
					if(block[x][y][z-1].fill == false)
					{
						block[x][y][z].in_surf = true;
						//m.SurfNum++;
						continue;
					}
					//前(x + 1)
					if(block[x+1][y][z].fill == false)
					{
						block[x][y][z].in_surf = true;
						//m.SurfNum++;
						continue;
					}
					//後(x - 1)
					if(block[x-1][y][z].fill == false)
					{
						block[x][y][z].in_surf = true;
						//m.SurfNum++;
						continue;
					}
					//左(y + 1)
					if(block[x][y+1][z].fill == false)
					{		
						block[x][y][z].in_surf = true;
						//m.SurfNum++;
						continue;
					}
					//右(y - 1)
					if(block[x][y-1][z].fill == false)
					{
						block[x][y][z].in_surf = true;
						//m.SurfNum++;
					}

			}
		}
	}


	//内部の表面ブロックを入れる
	//z方向が逆
	//下にブロックがない場合
	for(z=1; z < VoxSize[2]-5; z = z + 1 )				//ｚ＝1,3,5,...
	{
		for(x=1; x < VoxSize[0]-1; x = x + 1)
		{
			for(y=1; y < VoxSize[1]-1; y = y + 1)
			{

				if (!block[x][y][z].in_surf)continue;
				if (!block[x][y][z].fill)continue;
				if (block[x][y][z+1].fill)continue;
				if (block[x][y][z+2].fill)continue;
				if (block[x][y][z+3].fill)continue;
				if (block[x][y][z+4].fill)continue;
						temp.set(x,y,z+1);
						Inner_surf.push_back(temp);
			}
		}
	}
	cout<<"内部表面ブロックを見つけた　　その数は"<<Inner_surf.size()<<endl;
		int num;
	//z方向が逆
	//ブロックの角に柱を配置
	for(int i (0); i < (int)Inner_surf.size();i++){
		//1×1,1×2,2×2は無視
		num=0;
		x=Inner_surf[i].x;
		y=Inner_surf[i].y;
		z=Inner_surf[i].z;

		//1×3,1×4
		if(block[x][y][z-1].flag==13
			||block[x][y][z-1].flag==14)
			if(block[x][y][z-1].corner==0){
				Inner_surf[i].clear();
			}
		//2×3，2×4
		if(block[x][y][z-1].flag==23
			||block[x][y][z-1].flag==24)
			if(block[x][y][z-1].corner==0){
				//4近傍操作して角を見つける
				if (block[x][y][z-1].flag==block[x][y+1][z-1].flag)
					if (block[x][y][z-1].ID==block[x][y+1][z-1].ID)
				{
					num++;
				}
				if (block[x][y][z-1].flag==block[x+1][y][z-1].flag)
					if (block[x][y][z-1].ID==block[x+1][y][z-1].ID)
				{
					num++;
				}
				if (block[x][y][z-1].flag==block[x-1][y][z-1].flag)
					if (block[x][y][z-1].ID==block[x-1][y][z-1].ID)
				{
					num++;
				}
				if (block[x][y][z-1].flag==block[x][y-1][z-1].flag)
					if (block[x][y][z-1].ID==block[x][y-1][z-1].ID)
				{
					num++;
				}
					//角はnum=2,それ以外num=3
					if(num==3)
					Inner_surf[i].clear();
			}
	}

	//角以外を削除
	for(int i (0); i < (int)Inner_surf.size();i++){
		if(!Inner_surf[i].x&&!Inner_surf[i].y&&!Inner_surf[i].z){
		Inner_surf.erase(Inner_surf.begin()+i);
		i--;
		}
	}
	

	int ID;
	int flag;
	bool NN=0;
	//下に何もないブロックか判定
	for(int i (0); i < (int)Inner_surf.size();i++){
		x=Inner_surf[i].x;
		y=Inner_surf[i].y;
		z=Inner_surf[i].z;
		ID=	block[x][y][z-1].ID;
		flag=block[x][y][z-1].flag;
		for(int j(-3); j<4;j++)
			for(int k(-3); k < 4; k++)
				if((x+j)>0||(x+j)<m.num[1])
					if((y+k)>0||(y+k)<m.num[1])
						if(block[x+j][y+k][z-1].ID==ID)
							if(block[x+j][y+k][z-1].flag==flag)
								if(block[x+j][y+k][z].in_surf==true)
								NN=true;
		if(NN==false){
			block[x][y][z].airP=true;
		}
		NN=false;

	}
	//浮遊ブロック以外にブロックを配置
	//角のブロックを作る
	for(int i (0); i < (int)Inner_surf.size();i++){
		x=Inner_surf[i].x;
		y=Inner_surf[i].y;
		z=Inner_surf[i].z;
		if(!block[x][y][z].fill)
			if(block[x][y][z].airP||block[x+1][y][z].airP
				||block[x-1][y][z].airP||block[x][y+1][z].airP||block[x][y-1][z].airP){
		block[x][y][z].flag=1;
		block[x][y][z].fill=true;
		block[x][y][z].p_fill=true;
		block[x][y][z].ColorID=3;
		num11++;
		}
	}



	cout<<"必要のない柱を除去"<<endl;
	//大きいサイズに変更する
	int InnerS_size = (int)Inner_surf.size();
	//貪欲法で置換
	//2×4
	for(int i (0); i < InnerS_size;i++){
		x=Inner_surf[i].x;
		y=Inner_surf[i].y;
		z=Inner_surf[i].z;
		if (counter(block,x,y,z,4,2))
		{
			ID24++;
			num11=num11-8;
			change_bricks(block,x,y,z,4,2,ID24,24);
			Inner_pillar.push_back(centroid(block,x,y,z,4,2));
			continue;
		}
		if (counter(block,x,y,z,2,4))
		{
			ID24++;
			num11=num11-8;
			change_bricks(block,x,y,z,2,4,ID24,24);
			Inner_pillar.push_back(centroid(block,x,y,z,2,4));
		}
	}

	//2×3
	for(int i (0); i < InnerS_size;i++){
		x=Inner_surf[i].x;
		y=Inner_surf[i].y;
		z=Inner_surf[i].z;
		if (counter(block,x,y,z,3,2))
		{
			ID23++;
			num11=num11-6;
			change_bricks(block,x,y,z,3,2,ID23,23);
			Inner_pillar.push_back(centroid(block,x,y,z,3,2));
			continue;
		}
		if (counter(block,x,y,z,2,3))
		{
			ID23++;
			num11=num11-6;
			change_bricks(block,x,y,z,2,3,ID23,23);
			Inner_pillar.push_back(centroid(block,x,y,z,2,3));
		}
	}
	//2×2
		for(int i (0); i < InnerS_size;i++){
		x=Inner_surf[i].x;
		y=Inner_surf[i].y;
		z=Inner_surf[i].z;
		if (counter(block,x,y,z,2,2))
		{
			ID22++;
			num11=num11-4;
			change_bricks(block,x,y,z,2,2,ID22,22);
			Inner_pillar.push_back(centroid(block,x,y,z,2,2));
		}
	}
	//1×4
	for(int i (0); i < InnerS_size;i++){
		x=Inner_surf[i].x;
		y=Inner_surf[i].y;
		z=Inner_surf[i].z;
		if (counter(block,x,y,z,4,1))
		{
			ID14++;
			num11=num11-4;
			change_bricks(block,x,y,z,4,1,ID14,14);
			Inner_pillar.push_back(centroid(block,x,y,z,4,1));
			continue;
		}
		if (counter(block,x,y,z,1,4))
		{
			ID14++;
			num11=num11-4;
			change_bricks(block,x,y,z,1,4,ID14,14);
			Inner_pillar.push_back(centroid(block,x,y,z,1,4));
		}
	}
	//1×3
		for(int i (0); i < InnerS_size;i++){
		x=Inner_surf[i].x;
		y=Inner_surf[i].y;
		z=Inner_surf[i].z;
		if (counter(block,x,y,z,3,1))
		{
			ID13++;
			num11=num11-3;
			change_bricks(block,x,y,z,3,1,ID13,13);
			Inner_pillar.push_back(centroid(block,x,y,z,3,1));
			continue;
		}
		if (counter(block,x,y,z,1,3))
		{
			ID13++;
			num11=num11-3;
			change_bricks(block,x,y,z,1,3,ID13,13);
			Inner_pillar.push_back(centroid(block,x,y,z,1,3));
		}
	}
	//1×2
		for(int i (0); i < InnerS_size;i++){
		x=Inner_surf[i].x;
		y=Inner_surf[i].y;
		z=Inner_surf[i].z;
		if (counter(block,x,y,z,2,1))
		{
			ID12++;
			num11=num11-2;
			change_bricks(block,x,y,z,2,1,ID12,12);
			Inner_pillar.push_back(centroid(block,x,y,z,2,1));
			continue;
		}
		if (counter(block,x,y,z,1,2))
		{
			ID12++;
			num11=num11-2;
			change_bricks(block,x,y,z,1,2,ID12,12);
			Inner_pillar.push_back(centroid(block,x,y,z,1,2));
		}
	}

		//1×1のまま残っているブロックは除去
		for(int i (0) ; i < InnerS_size ; i++){
			x=Inner_surf[i].x;
			y=Inner_surf[i].y;
			z=Inner_surf[i].z;		
			if(block[x][y][z].flag==1){
				if(block[x][y][z].airP){
					Inner_pillar.push_back(centroid(block,x,y,z,1,1));
				}
				else{
					block[x][y][z].Initiaization();
					num11--;
				}
			}
		}

		cout<<"貪欲法で置換　その数　"<<Inner_pillar.size()<<endl;
		int Inner_size = (int)Inner_pillar.size() ;

		for(int i (0) ; i < Inner_size ; i++){
			x=Inner_pillar[i].x;
			y=Inner_pillar[i].y;
			z=Inner_pillar[i].z+1;		
			block[x][y][z].root=true;
		}

		//周辺に柱がある場合、統合し1つにする
		for(int i (0) ; i < Inner_size ; i++){
			x=Inner_pillar[i].x;
			y=Inner_pillar[i].y;
			z=Inner_pillar[i].z+1;		
			//8近傍を調査し、柱を検出
			for(int xx (-1); xx < 2 ; xx++)
				for(int yy (-1); yy < 2 ; yy++)
					for(int zz (0); zz < 3 ; zz++){
						//連結性を考慮し、残す柱を決める
						//重心位置も考える
						if(xx==0&&yy==0)continue;
						if(block[x+xx][y+yy][z+zz].root){
							Inner_pillar[i].trail=true;
							if(Inner_pillar[i].zcoord<z+zz)
							Inner_pillar[i].zcoord=z+zz;
							block[x][y][z].root=false;
						}			 
					}

		}
		for(int i (0) ; i < Inner_size ; i++){
			if(Inner_pillar[i].trail){
			x=Inner_pillar[i].x;
			y=Inner_pillar[i].y;
			z=Inner_pillar[i].z+1;	
			while(Inner_pillar[i].zcoord>=z){
				block[x][y][z].fill=true;
				block[x][y][z].p_fill=true;
				block[x][y][z].flag=1;
				block[x][y][z].root=true;
			z++;
			}
			}
		}
		//2×2を配置
		for(int i (0) ; i < Inner_size ; i++){
			if(!Inner_pillar[i].trail){
			x=Inner_pillar[i].x;
			y=Inner_pillar[i].y;
			z=Inner_pillar[i].z+1;	

			if(block[x-1][y-1][z].root||(block[x-1][y][z].root&&block[x][y-1][z].root)){
			ID22++;
			change_bricks(block,x-1,y-1,z,2,2,ID22,22);
			//num11=num11-3;//1×1の個数が違う		
			}		
			else if(block[x-1][y+1][z].root||(block[x-1][y][z].root&&block[x][y+1][z].root)){
			ID22++;
			change_bricks(block,x-1,y,z,2,2,ID22,22);
			//num11=num11-3;//1×1の個数が違う		
			}	
			else if(block[x+1][y-1][z].root||(block[x+1][y][z].root&&block[x][y-1][z].root)){
			ID22++;
			change_bricks(block,x,y-1,z,2,2,ID22,22);
			//num11=num11-3;//1×1の個数が違う		
			}
			else if(block[x+1][y+1][z].root||(block[x+1][y][z].root&&block[x][y+1][z].root)){
			ID22++;
			change_bricks(block,x,y,z,2,2,ID22,22);
			//num11=num11-3;//1×1の個数が違う		
			}
			else	if(block[x+1][y][z].root||block[x][y+1][z].root){
			ID22++;
			change_bricks(block,x,y,z,2,2,ID22,22);
			//num11=num11-3;//1×1の個数が違う
			}
			else if(block[x-1][y][z].root||block[x][y+1][z].root){
			ID22++;
			change_bricks(block,x-1,y,z,2,2,ID22,22);
			//num11=num11-3;//1×1の個数が違う		
			}
			else if(block[x+1][y][z].root||block[x][y-1][z].root){
			ID22++;
			change_bricks(block,x,y-1,z,2,2,ID22,22);
			//num11=num11-3;//1×1の個数が違う
			}
			else if(block[x-1][y][z].root||block[x][y-1][z].root){
			ID22++;
			change_bricks(block,x-1,y-1,z,2,2,ID22,22);
			//num11=num11-3;//1×1の個数が違う
			}
			}
		}

		//Inner_pillarを元に柱を組立てる
		int p(0);
		bool P[2];
		for(int i (0) ; i < Inner_size ; i++){
			if(Inner_pillar[i].trail)continue;
			x=Inner_pillar[i].x;
			y=Inner_pillar[i].y;
			z=Inner_pillar[i].z;
			int k=1;
			do{
				if(block[x][y][z+k].flag==0){
				block[x][y][z+k].fill=true;
				block[x][y][z+k].p_fill=true;
				block[x][y][z+k].flag=1;
				num11++;
				}
				k++;
			}while(!block[x][y][z+k].fill);
			P[0]=false;	P[1]=false;
			//一番下の柱は2つ以上のブロックに跨ぐように設定する(無理な場合を一つ上の層に上がる)
			if(!block[x][y+1][z+k].fill&&block[x][y+1][z+k+1].fill){
				block[x][y+1][z+k].fill=true;
				block[x][y+1][z+k].in_surf=true;
				block[x][y+1][z+k].p_fill=true;
				block[x][y+1][z+k].flag=1;
				num11++;
				P[0]=true;
			}
				if(!block[x][y-1][z+k].fill&&block[x][y-1][z+k+1].fill){
				block[x][y-1][z+k].fill=true;
				block[x][y-1][z+k].in_surf=true;
				block[x][y-1][z+k].p_fill=true;
				block[x][y-1][z+k].flag=1;
				num11++;
				P[1]=true;
			}
			//1×3を配置する
			//十字を利用する
			if(block[x][y][z+k-1].flag!=1)continue;
			if(block[x][y-1][z+k].ID!=block[x][y+1][z+k].ID&&
				block[x][y-1][z+k].in_surf&&block[x][y+1][z+k].in_surf&&
				((block[x][y-1][z+k-1].flag==1||block[x][y-1][z+k-1].flag==0)&&
				(block[x][y+1][z+k-1].flag==1||block[x][y+1][z+k-1].flag==0))){
					num11--;
					ID13++;
					num13++;
			for(p=-1; p< 2 ; p++){
				block[x][y+p][z+k-1].fill=true;
				block[x][y+p][z+k-1].p_fill=true;
				block[x][y+p][z+k-1].ID=ID13;
				block[x][y+p][z+k-1].flag=13;
			}
			block[x][y-1][z+k-1].corner=1;
			block[x][y+1][z+k-1].corner=2;
			continue;
			}
			////余分に配置したブロックを除去する
			if(P[0]&&block[x][y-1][z+k].fill&&block[x][y-1][z+k].flag==1)block[x][y-1][z+k].Initiaization(),num11--;
			if(P[1]&&block[x][y+1][z+k].fill&&block[x][y+1][z+k].flag==1)block[x][y+1][z+k].Initiaization(),num11--;
			////------------------------------
			P[0]=false;	P[1]=false;
			if(!block[x+1][y][z+k].fill&&block[x+1][y][z+k+1].fill){
				block[x+1][y][z+k].fill=true;
				block[x+1][y][z+k].in_surf=true;
				block[x+1][y][z+k].p_fill=true;
				block[x+1][y][z+k].flag=1;
				num11++;
				P[0]=true;
			}
				if(!block[x-1][y][z+k].fill&&block[x-1][y][z+k+1].fill){
				block[x-1][y][z+k].fill=true;
				block[x-1][y][z+k].in_surf=true;
				block[x-1][y][z+k].p_fill=true;
				block[x-1][y][z+k].flag=1;
				num11++;
				P[1]=true;
			}
			if(block[x-1][y][z+k].ID!=block[x+1][y][z+k].ID&&
				block[x-1][y][z+k].in_surf&&block[x+1][y][z+k].in_surf&&
				((block[x-1][y][z+k-1].flag==1||block[x-1][y][z+k-1].flag==0)&&
				(block[x+1][y][z+k-1].flag==1||block[x+1][y][z+k-1].flag==0))){
					num11--;
					num13++;
					ID13++;
			for(p=-1; p< 2 ; p++){
				block[x+p][y][z+k-1].fill=true;
				block[x+p][y][z+k-1].p_fill=true;
				block[x+p][y][z+k-1].flag=13;
				block[x+p][y][z+k-1].ID=ID13;
			}
			block[x-1][y][z+k-1].corner=1;
			block[x+1][y][z+k-1].corner=2;	
					continue;
			}
			//余分に配置したブロックを除去する
			if(P[0]&&block[x-1][y][z+k].fill&&block[x-1][y][z+k].flag==1)block[x-1][y][z+k].Initiaization();
			if(P[1]&&block[x+1][y][z+k].fill&&block[x+1][y][z+k].flag==1)block[x+1][y][z+k].Initiaization();
			//------------------------------
		
			//一層上に移動
			if(block[x][y-1][z+k].ID!=block[x][y+1][z+k].ID){
				if(block[x][y-1][z+k-1].in_surf&&block[x][y+1][z+k-1].in_surf){
				//何もしない
				}
				else if(block[x][y+1][z+k-1].in_surf&&
				(block[x][y+1][z+k-1].flag==1||block[x][y+1][z+k-1].flag==0)){
				//
					ID12++;
				block[x][y][z+k-1].fill=true;					block[x][y-1][z+k-1].fill=true;
				block[x][y][z+k-1].p_fill=true;				block[x][y-1][z+k-1].p_fill=true;
				block[x][y][z+k-1].flag=12;					block[x][y-1][z+k-1].flag=12;
				block[x][y][z+k-1].ID=ID12;					block[x][y-1][z+k-1].ID=ID12;
				block[x][y][z+k-1].corner=2;					block[x][y-1][z+k-1].corner=1;
				}
				else if(block[x][y-1][z+k-1].in_surf&&
				(block[x][y-1][z+k-1].flag==1||block[x][y-1][z+k-1].flag==0)){
				//
					ID12++;
				block[x][y][z+k-1].fill=true;					block[x][y+1][z+k-1].fill=true;
				block[x][y][z+k-1].p_fill=true;				block[x][y+1][z+k-1].p_fill=true;
				block[x][y][z+k-1].flag=12;					block[x][y+1][z+k-1].flag=12;
				block[x][y][z+k-1].ID=ID12;					block[x][y+1][z+k-1].ID=ID12;
				block[x][y][z+k-1].corner=2;					block[x][y+1][z+k-1].corner=1;				
				}
				else continue;
				if(!block[x][y-1][z+k-2].fill&&!block[x][y+1][z+k-2].fill&&
				(block[x][y+1][z+k-2].flag==1||block[x][y+1][z+k-2].flag==0)&&
				(block[x][y-1][z+k-2].flag==1||block[x][y-1][z+k-2].flag==0)){					
						num13++;
						ID13++;
						for(p=-1; p< 2 ; p++){
							block[x][y+p][z+k-2].fill=true;
							block[x][y+p][z+k-2].p_fill=true;
							block[x][y+p][z+k-2].ID=ID13;
							block[x][y+p][z+k-2].flag=13;
						}
						block[x][y-1][z+k-2].corner=1;
						block[x][y+1][z+k-2].corner=2;
						continue;				
					}
			}
			//一層上に移動
			if(block[x-1][y][z+k].ID!=block[x+1][y][z+k].ID){
				if(block[x-1][y][z+k-1].in_surf&&block[x+1][y][z+k-1].in_surf){
				//何もしない
				}
				else if(block[x+1][y][z+k-1].in_surf&&
				(block[x+1][y][z+k-1].flag==1||block[x+1][y][z+k-1].flag==0)){
				//
					ID12++;
				block[x][y][z+k-1].fill=true;					block[x-1][y][z+k-1].fill=true;
				block[x][y][z+k-1].p_fill=true;				block[x-1][y][z+k-1].p_fill=true;
				block[x][y][z+k-1].ID=ID12;					block[x-1][y][z+k-1].ID=ID12;
				block[x][y][z+k-1].flag=12;					block[x-1][y][z+k-1].flag=12;
				block[x][y][z+k-1].corner=2;					block[x-1][y][z+k-1].corner=1;
				}
				else if(block[x-1][y][z+k-1].in_surf&&
				(block[x-1][y][z+k-1].flag==1||block[x-1][y][z+k-1].flag==0)){
				//
					ID12++;
				block[x][y][z+k-1].fill=true;					block[x+1][y][z+k-1].fill=true;
				block[x][y][z+k-1].p_fill=true;				block[x+1][y][z+k-1].p_fill=true;
				block[x][y][z+k-1].ID=ID12;					block[x+1][y][z+k-1].ID=ID12;
				block[x][y][z+k-1].flag=12;					block[x+1][y][z+k-1].flag=12;
				block[x][y][z+k-1].corner=2;					block[x+1][y][z+k-1].corner=1;				
				}
				else continue;
				if(!block[x-1][y][z+k-2].fill&&!block[x+1][y][z+k-2].fill&&
				(block[x+1][y][z+k-2].flag==1||block[x+1][y][z+k-2].flag==0)&&
				(block[x-1][y][z+k-2].flag==1||block[x-1][y][z+k-2].flag==0)){					
						num13++;
						ID13++;
						for(p=-1; p< 2 ; p++){
							block[x+p][y][z+k-2].fill=true;
							block[x+p][y][z+k-2].ID=ID13;				
							block[x+p][y][z+k-2].p_fill=true;
							block[x+p][y][z+k-2].flag=13;
						}
						block[x-1][y][z+k-2].corner=1;
						block[x+1][y][z+k-2].corner=2;
						continue;				
					}
			}
			
		}


}

//変換するアルゴリズム
//2つ目の引数はブロックの座標
//5つ目の引数はブロックサイズ
void change_bricks( Lego*** block,int x,int y,int z,int  col,int row,int IDs,int flags){

	for(int i (0); i<col;i++){
		for(int j(0); j <row;j++){
			block[x+i][y+j][z].ID=IDs;
			block[x+i][y+j][z].flag=flags;
			block[x+i][y+j][z].fill=true;
		}
	}
	block[x][y][z].corner=1;
	block[x+col-1][y+row-1][z].corner=2;

}

bool counter( Lego*** block,int x,int y,int z,int  col,int row){
	int number=0;
	for(int i (0); i<col;i++){
		for(int j(0); j <row;j++){
					if(block[x+i][y+j][z].p_fill)
					if(block[x+i][y+j][z].flag==1)
					number++;
		}
	}
	if(col*row==number)
		return 1;
	else
		return 0;

}

cood centroid(Lego*** block,int x,int y,int z,int  col,int row){

	cood temp;
	temp.set(x,y,z);
	int Xc=0,Yc=0;
	for(int i (0); i<col;i++){
		for(int j(0); j <row;j++){
			Xc=Xc+i;
			Yc=Yc+j;
		}
	}
	Xc=Xc/(col*row);
	Yc=Yc/(col*row);
	temp.x=(temp.x+Xc);
	temp.y=(temp.y+Yc);
	return temp;
}