#include "../stdafx.h"
	

extern Model Integ;
extern string pose[3];
//LEGO
Lego*** block;

extern unsigned int** BlockNum;
extern unsigned int Block_colorNum;			
extern unsigned int Block_varietyNum;			
extern double delThres;
extern int  zcood;

int ID12(0);			//‚P~‚Q‚ğ‹æ•Ê‚·‚é‚½‚ß‚ÌID
int ID13(0);			//‚P~‚R‚ğ‹æ•Ê‚·‚é‚½‚ß‚ÌID
int ID14(0);			//‚P~‚S‚ğ‹æ•Ê‚·‚é‚½‚ß‚ÌID
int ID22(0);			//‚Q~‚Q‚ğ‹æ•Ê‚·‚é‚½‚ß‚ÌID
int ID23(0);			//‚Q~‚R‚ğ‹æ•Ê‚·‚é‚½‚ß‚ÌID
int ID24(0);			//‚Q~‚S‚ğ‹æ•Ê‚·‚é‚½‚ß‚ÌID

int num11(0);		//‚P~‚P‚ÌƒuƒƒbƒN‚Ì”
int num12(0);		//‚P~‚Q‚ÌƒuƒƒbƒN‚Ì”
int num13(0);		//‚P~‚R‚ÌƒuƒƒbƒN‚Ì”
int num14(0);		//‚P~‚S‚ÌƒuƒƒbƒN‚Ì”
int num22(0);		//‚Q~‚Q‚ÌƒuƒƒbƒN‚Ì”
int num23(0);		//‚Q~‚R‚ÌƒuƒƒbƒN‚Ì”
int num24(0);		//‚Q~‚S‚ÌƒuƒƒbƒN‚Ì”

void delete_InnerBlocks(int* VoxSize);
void outputFlag(string , int*);
void outputID(string , int*);
void outputColorID(string , int*);
void CountNum_of_4(Lego*** , int*);					
void Coloring_ID(Lego*** block, int*  VoxSize);//2014/08/11
void Small_to_Big_step0(Lego*** , int*);
void Small_to_Big_before_step1(Lego*** block, int* );
void Small_to_Big_step1(Lego*** , int*);
void Small_to_Big_step1_color_new(Lego*** block, int* );
void Small_to_Big_step2(Lego*** , int*);
void Small_to_Big_before_before_step2_color(Lego*** block, int* VoxSize);//2014/08/11
void Small_to_Big_before_step2_color(Lego*** block, int* VoxSize);//2014/08//11
void Small_to_Big_step3(Lego*** , int*);
void Small_to_Big_before_step4(Lego*** , int* );
void Small_to_Big_step4(Lego*** , int*);
void Small_to_Big_step5(Lego*** , int*);
void Small_to_Big_step6(Lego*** , int*);
void Small_to_Big_step7(Lego*** , int*);
void Small_to_Big_step8(Lego*** block, int*  VoxSize);//2014/08/11
void Change_flag_2_to_12(Lego*** , int*);
void Change_flag_4_to_22(Lego*** , int*);
void Delete_Iso_Blocks_11(Lego*** block, int* VoxSize);
void Delete_Iso_Blocks_12(Lego*** block, int* VoxSize);
void Delete_Iso_Blocks_22(Lego*** block, int* VoxSize);
void Delete_Iso_Blocks(Lego*** block, int* VoxSize);

CColor RGB_to_Lab(CColor& rgb);
double DeltaE(CColor& aa, CColor& bb);
void ColoringBlock_lavest(Model& m, Lego*** b);
void ColoringBlock_zhang(Model& m, Lego*** b);

void FindOutsideVoxel(Model& m);
void Coloring(Model& integ);
void RealColor_to_LegoColor_lab(Model& m, Lego*** block);
void RealColor_to_LegoColor_lab_12_22(Model& m, Lego*** block);
void RealColor_to_LegoColor_lab_mono(Lego*** block);


//2013/9/14
void CountNum_of_4_ID(Lego*** , int* );
void Small_to_Big_step0_color(Lego*** , int*);
void Small_to_Big_step1_color(Lego*** , int* );
void Small_to_Big_step2_color(Lego*** , int* );
void Small_to_Big_step4_color(Lego*** , int*);
void Small_to_Big_step5_color(Lego*** , int*);
void Small_to_Big_step7_color(Lego*** , int*);

void GiveColorIDto12_22(int* VoxSize);
void delete_Inner11(int* VoxSize);
void FindOutsideBlocks(Lego*** m, int* VoxSize);
void Voxel2Block(int* VoxSize);
void Voxel2Block_zhang(Voxel*** Voxels, int* VoxSize);

void OutputBlock_lxfml();

//Å‹ß
void create_pileline(int* VoxSize);
void create_pileline_01(int* VoxSize);
void make_pillar( Lego*** block,Model& m, int* VoxSize);
void insurf_LEGO(int* VoxSize);
void change_bricks( Lego*** block,int x,int y,int z,int  col,int row,int IDs,int flags);
int Block_count(int* size );


extern vector<Brick> LDD;
extern BrickTable table;
extern CMatrix rot[2];

void RunOpenGL4(int argc, char *argv[]);

int Building(int argc, char *argv[])
{
	cout<<"====================================\n                 LEGO                \n===================================="<<endl;

	//################################
	//                 LEGOƒuƒƒbƒN‚Ìƒƒ‚ƒŠŠm•Û                      
	//################################
	int VoxSize[3];
	for(int i(0); i<3; i++)
		VoxSize[i] = Integ.num[i];

	block = new Lego **[VoxSize[0]];
	for(int x(0); x < VoxSize[0]; x++){
		block[x] = new Lego  *[VoxSize[1]];
		for(int y(0); y < VoxSize[1]; y++){
			block[x][y] = new Lego [VoxSize[2]];
		}
	}

	//##################################
	//                        
	//##################################
	Voxel2Block(VoxSize);

	//#####################################
	//   
	//#####################################
	RealColor_to_LegoColor_lab(Integ, block);

	CountNum_of_4_ID(block, VoxSize);
	cout<<"Step 0\n"<<endl;
	//Small_to_Big_step0(block, VoxSize);						
	Small_to_Big_step0_color(block, VoxSize);					
	Coloring_ID(block, VoxSize);
	delete_Inner11(VoxSize);
	



	//GiveColorIDto12_22(VoxSize);
	//#####################################
	//  
	//#####################################
	//RealColor_to_LegoColor_lab_12_22(Integ, block);

	//#######################################
	//
	//#######################################
	//cout<<"step.1 ‚P~‚P‚ğ‚P~‚P‚©‚P~‚Q‚Æ‡¬I"<<endl;
	//Small_to_Big_before_step1(block, VoxSize);		//ŒÇ—§‚µ‚»‚¤‚È‚P~‚P‚ğ‚Ù‚©‚Ì‚P~‚P‚Æ‚P~‚Q‚Æ‚­‚Á‚Â‚¯‚é
	//Small_to_Big_step1(block, VoxSize);					//‚P~‚P‚ğ‚Ù‚©‚Ì‚P~‚P‚Æ‚P~‚Q‚Æ‚­‚Á‚Â‚¯‚é
	//cout<<"step.2 ‚P~‚P‚ğ‚P~‚R‚Æ‡¬I"<<endl;
	//Small_to_Big_step2(block, VoxSize);					//‚P~‚P‚Ì‚S•ûŒü‚É@‚P~3@‚ª‚ ‚Á‚½‚ç@Œ‹‡‚³‚¹‚é
	//cout<<"step.3 ‚Q~‚Q‚ÆŒÇ—§‚µ‚»‚¤‚È‚P~‚P‚Æ‡¬‚µ‚Ü‚·I"<<endl;
	//Small_to_Big_step3(block, VoxSize);					//‚Q~‚Q‚ÆŒÇ—§‚µ‚»‚¤‚È‚P~‚P‚©‚ç‚P~‚R‚Æ‚P~‚Q‚ğ¶¬‰Â”\‚Å‚ ‚ê‚Îì¬
	//cout<<"step.4 ‚P~‚Q‚Æ‚P~‚Q‚©‚Q~‚Q‚Æ‡¬‚µ‚Ü‚·I"<<endl;
	//Small_to_Big_before_step4(block, VoxSize);		//ŒÇ—§‚µ‚»‚¤‚È‚P~‚Q‚ğ—Dæ“I‚ÉA‚P~‚Q‚Æ‚Q~‚Q‚ğg‚Á‚Ä@‚P~‚SA‚Q~‚QA‚Q~‚R‚ğ¶¬
	//Small_to_Big_step4(block, VoxSize);					//‚P~‚Q@‚ğ@‚P~‚Q‚Æ‚Q~‚Q@‚©‚ç@‚P~‚SA‚Q~‚QA‚Q~‚R‚ğ¶¬
	//cout<<"step.5 ‚P~‚Q‚Æ‚Q~‚R‚Æ‡¬‚µ‚Ü‚·I"<<endl;
	//Small_to_Big_step5(block, VoxSize);					//‚P~‚Q‚Æ‚Q~‚R‚©‚ç‚Q~‚S‚ğ¶¬
	//cout<<"step.6 ‚P~‚Qi‚P~‚P‚Æ‚P~‚P‚©‚ç‚È‚éj‚Æ‚Q~‚Qi‚P~‚Q‚Æ‚P~‚Q‚©‚ç‚È‚éj‚Æ‡¬‚µ‚Ü‚·I"<<endl;
	//Small_to_Big_step6(block, VoxSize);					//‚P~‚Qi‚P~‚P‚Æ‚P~‚P‚©‚ç‚È‚éj‚Æ‚Q~‚Qi‚P~‚Q‚Æ‚P~‚Q‚©‚ç‚È‚éj‚ğ‡¬‚·‚é	
	//cout<<"step.7 ‚Q~‚Q‚Æ‚Q~‚Q‚ğ‡¬‚µ‚Ü‚·I"<<endl;
	//Small_to_Big_step7(block, VoxSize);					//‚Q~‚Q‚Æ‚Q~‚Q‚©‚ç‚Q~‚S‚ğ¶¬
	//Change_flag_2_to_12(block, VoxSize);				//‚P~‚Q‚Åflag‚ª‚Q‚Ì‚Ü‚Ü‚Åc‚Á‚Ä‚¢‚éê‡flag‚ğ‚P‚Q‚É•ÏX‚·‚é
	//Change_flag_4_to_22(block, VoxSize);				//‚Q~‚Q‚Åflag‚ª‚S‚Ì‚Ü‚Ü‚Åc‚Á‚Ä‚¢‚éê‡flag‚ğ‚Q‚Q‚É•ÏX
	////
	//Delete_Iso_Blocks_22(block, VoxSize);		//—pŒŸ“¢
	//Delete_Iso_Blocks_12(block, VoxSize);		//—pŒŸ“¢
	//Delete_Iso_Blocks_11(block, VoxSize);		//—pŒŸ“¢
	//Delete_Iso_Blocks(block, VoxSize);
	////
	//ColoringBlock(Integ, block);//‚»‚Ì‚Ü‚Üg‚¦‚»‚¤‚¾


	//######################################
	//
	//######################################
	Small_to_Big_before_step1(block, VoxSize);		

	//Small_to_Big_step1_color(block, VoxSize);		
	Coloring_ID(block, VoxSize);
	
	Small_to_Big_step1_color_new(block, VoxSize);//1~1‚ğ‚Ù‚©‚Ì1~1‚Æ‚­‚Á‚Â‚¯‚é
	
	Coloring_ID(block, VoxSize);

	cout<<"Step2:\n"<<endl;
	Small_to_Big_before_before_step2_color(block, VoxSize);
	Small_to_Big_before_step2_color(block, VoxSize);
	
	Small_to_Big_step2_color(block, VoxSize);		
	Coloring_ID(block, VoxSize);

	cout<< "Step3:\n" <<endl;
	Small_to_Big_step3(block, VoxSize);				
	
	cout << "Step4:\n" << endl;
	Small_to_Big_before_step4(block, VoxSize);		
	Small_to_Big_step4_color(block, VoxSize);		
	
	cout<< "Step5:\n" <<endl;
	Small_to_Big_step5_color(block, VoxSize);		
	
	cout << "Step6:\n" << endl;
	Small_to_Big_step6(block, VoxSize);				
	
	cout << "Step7:\n" << endl;
	Small_to_Big_step7_color(block, VoxSize);		
	Coloring_ID(block, VoxSize);

	Change_flag_2_to_12(block, VoxSize);			
	Change_flag_4_to_22(block, VoxSize);			
	Small_to_Big_step8(block, VoxSize);				


	//Delete_Iso_Blocks_22(block, VoxSize);	
	Delete_Iso_Blocks_12(block, VoxSize);	
	Delete_Iso_Blocks_11(block, VoxSize);	

	//make_pillar(block, Integ,VoxSize);
	
	//create_pileline_01( VoxSize);
	
	//Delete_Iso_Blocks(block, VoxSize);
	//RealColor_to_LegoColor_lab_mono(block);  //2014/5/21
	//Voxel2Block(VoxSize);
	//######################
	//                                
	//######################
	if(pose[2] == "Lavest_Calib/")
		ColoringBlock_lavest(Integ, block);
	else if( pose[2] == "Zhang_Calib/")
		ColoringBlock_zhang(Integ, block);

	string blockname[7] ={	"‚P~‚PF", 	"‚P~‚QF", 	"‚P~‚RF", 	"‚P~‚SF", 	"‚Q~‚QF", 	"‚Q~‚RF", 	"‚Q~‚SF"};
	int num[7];
	num[0] = num11;
	num[1] = num12;
	num[2] = num13;
	num[3] = num14;
	num[4] = num22;
	num[5] = num23;
	num[6] = num24;

	cout<<"Block_colorNum\n"<<endl;

	for(int k(0); k<7; k++){
		cout<<blockname[k]<<num[k]<<" ";
		for(int i(0); i<Block_colorNum; i++){
			cout<<BlockNum[k][i]<<" ";
		}
		cout<<endl;
	}

	//cout<<"‚P~‚PF"<<num11<<" ";
	//for(int i(0); i<Block_colorNum; i++)
	//	cout<<BlockNum[0][i]<<" ";
	//cout<<endl;
	//cout<<"‚P~‚QF"<<num12<<" ";
	//for(int i(0); i<Block_colorNum; i++)
	//	cout<<BlockNum[1][i]<<" ";
	//cout<<endl;
	//cout<<"‚P~‚RF"<<num13<<" ";
	//for(int i(0); i<Block_colorNum; i++)
	//	cout<<BlockNum[2][i]<<" ";
	//cout<<endl;
	//cout<<"‚P~‚SF"<<num14<<" ";
	//for(int i(0); i<Block_colorNum; i++)
	//	cout<<BlockNum[3][i]<<" ";
	//cout<<endl;
	//cout<<"‚Q~‚QF"<<num22<<" ";
	//for(int i(0); i<Block_colorNum; i++)
	//	cout<<BlockNum[4][i]<<" ";
	//cout<<endl;
	//cout<<"‚Q~‚RF"<<num23<<" ";
	//for(int i(0); i<Block_colorNum; i++)
	//	cout<<BlockNum[5][i]<<" ";
	//cout<<endl;
	//cout<<"‚Q~‚SF"<<num24<<" ";
	//for(int i(0); i<Block_colorNum; i++)
	//	cout<<BlockNum[6][i]<<" ";
	//cout<<endl;


	Integ.LegoColor.clear();
	Integ.LegoColor.shrink_to_fit();
	Integ.LegoColor_Lab.clear();
	Integ.LegoColor_Lab.shrink_to_fit();
	Integ.LegoHue.clear();
	Integ.LegoHue.shrink_to_fit();

	//insurf_LEGO(VoxSize);

	
	//#################################
	//            LEGO Digital Designer(.lxfml)‚Ìo—Í               
	//#################################
	OutputBlock_lxfml();
		
	//#################################
	//                            OpenGL‚Å•`‰æ                                
	//#################################
	RunOpenGL4(argc, argv);

	for(int i(0); i<VoxSize[0]; i++){
		for(int k(0); k<VoxSize[1]; k++){
			delete [] Integ.Voxel_colors[i][k];
			delete [] block[i][k];
			delete [] Integ.Voxels[i][k];
		}
		delete [] Integ.Voxel_colors[i];
		delete [] block[i];
		delete [] Integ.Voxels[i];
	}
	delete [] Integ.Voxel_colors;
	delete [] block;
	delete [] Integ.Voxels;

	return 0;
}



class Pileline
{
public:
	CVector3d *point;				//LEGOƒuƒƒbƒN‚ÌŠeƒ{ƒNƒZƒ‹‚ÌˆÊ’u
	vector<CVector3d> Point;		//LEGOƒuƒƒbƒN‚ÌŠeƒ{ƒNƒZƒ‹‚ÌˆÊ’u
	CVector3d gravity;				//LEGOƒuƒƒbƒN‚ÌdS
	bool ground;					//’n–Ê‚ÉÚ‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©
	bool in_surf;					//“à•”•\–ÊƒuƒƒbƒN‚©‚Ç‚¤‚©
	int num;
	Pileline(){
		in_surf=false;
		ground=false;
	}
	void init(){
		ground=false;
		in_surf=false;
	}
	~Pileline(){}
};
class edge{
public:
	int PN[2];//point number
	short cost;//cost of edge
};

//Pilelineì¬i2014/07/14j
void create_pileline(int* VoxSize){

	int cID=0;//current ID
	short cflag=0;//current flag
	Pileline P,Q;
	edge E;
	vector<Pileline> CT;//connection
	vector<edge>  Et;//edge cost
	int co=0;

	cout <<"Pileline\n"<<endl;
	for(int z(1); z < VoxSize[2]-1; z++)
	{
		for(int x(1); x < VoxSize[0]-1; x++)
		{
			for(int y(1); y < VoxSize[1]-1; y++)
			{

				//ƒuƒƒbƒN‚ª‚ ‚èAID‚Æflag‚ª‚ ‚éê‡A”Ô†‚ğ‚Â‚¯‚é
				if(block[x][y][z].fill == true&&block[x][y][z].calc==false){
					block[x][y][z].calc=true;
					cID= block[x][y][z].ID;
					cflag= block[x][y][z].flag;
					//ƒuƒƒbƒN‚ÌƒTƒCƒY•ª—pˆÓ
					if(cflag == 1)
						P.point= new CVector3d [1];
					else if(cflag == 12)
						P.point= new CVector3d [2];
					else if(cflag == 13)
						P.point= new CVector3d [3];
					else if(cflag == 23)
						P.point= new CVector3d [6];
					else if(cflag == 24)
						P.point= new CVector3d [8];
					else 
						P.point= new CVector3d [4];

					//—ÌˆæŠg’£–@‚Å“¯‚¶ƒuƒƒbƒN‚ğŒ©‚Â‚¯‚éiÅ‘å2~4‚È‚Ì‚Å3-ring‘–¸©ŠÈ’P‚¯‚ÇŠÔ‚Í‚©‚©‚éj
					int num=0;
					for(int i(-3) ; i < 4 ; ++i){
						if((x+i)<0||(x+i)>VoxSize[0]-1)continue;
						for(int j(-3) ; j < 4 ; ++j){
							if((y+j)<0||(y+j)>VoxSize[1]-1)continue;

							if(block[(x+i)][(y+j)][z].ID==cID&&block[(x+i)][(y+j)][z].flag==cflag){
								block[(x+i)][(y+j)][z].calc=true;
								P.point[num].Set((x+i),(y+j),z);
								//	cout<<"zÀ•W@@"<<z<<endl;
								num++;
							}
						}
					}
					for(int k(0) ; k< num; k++){
						P.gravity.x+=P.point[k].x;
						P.gravity.y+=P.point[k].y;
						P.gravity.z+=P.point[k].z;
					}

					P.gravity.Set(P.gravity.x/(double)num,P.gravity.y/(double)num,P.gravity.z/(double)num);
					//P.gravity.Set(P.point[0].x,P.point[0].y,P.point[0].z);
					P.num=num;
					CT.push_back(P);
					//CT[co].num=num;
					CT[co].point = new CVector3d [CT[co].num];
					for(int k(0) ; k< num; k++){
						CT[co].point[k]=P.point[k];
					}
					co++;
					P.gravity.Clear();
					delete [] P.point;
					//cout <<"push back!!      "<<num<<endl;
				}
			}
		}
	}

	cID=0;
	cflag=0;
	bool F=0;
	vector<int> Nc;
	//•Ó‚ÆƒRƒXƒgŒvZ
	for(int i (0); i < (int) CT.size();++i){

		for(int c(0); c< CT[i].num; c++){
			
			F=0;
			//‰º‚©‚ç‡‚É‘–¸‚·‚é‚©‚ç
			for(int j = 0 ; j<(int)CT.size(); j++){
				for(int b(0); b < CT[j].num; b++){
					if(CT[j].point[b].x==CT[i].point[c].x&&CT[j].point[b].y==CT[i].point[c].y&&CT[j].point[b].z==(CT[i].point[c].z+1)){
						Nc.push_back(j);
		
						F=true;
						break;
					}
				}
				if(F==true)break;
			}

		}
		int number=0;
		for(int a(0); a <(int) Nc.size(); a++){
			if(Nc[a]==-1)continue;
			int count=1;
			number=Nc[a];
			for(int k = a+1; k <(int) Nc.size();k++){
				if(Nc[k]==number){
					count++;
					Nc[k]=-1;
				}
				E.cost=count;
				E.PN[0]=i;
				E.PN[1]=number;
				Et.push_back(E);
											}
									}
		Nc.clear();
		Nc.shrink_to_fit();
	}

	cout<<endl;
	//	cout<<"@@@@@ƒuƒƒbƒN‚ÌPileline‚ğo—Í!!!!!!!        "<<endl;

	ofstream Ffout("Pileline_gravity.txt");
	Ffout<<CT.size()<<"  "<<Et.size()<<endl;
	for(int i (0); i < (int) CT.size();++i){
		//CT[i].gravity.Print();
		//Ffout<<CT[i].gravity.x<<"   "<<CT[i].gravity.y<<"   "<<CT[i].gravity.z*1.2<<endl;
		//LEGOd—l‚É•ÏX
		//Ffout<<CT[i].gravity.y<<"   "<<VoxSize[2]-CT[i].gravity.z<<"   "<<(VoxSize[0]-CT[i].gravity.x)*1.2<<endl;
		Ffout<<CT[i].gravity.x<<"   "<<CT[i].gravity.y<<"   "<<CT[i].gravity.z*1.2<<"  "<<CT[i].num<<endl;
	}
	for(int i(0) ; i < (int)Et.size(); i++)
	{
		Ffout<<Et[i].PN[0]<<" "<<Et[i].PN[1]<<" "<<Et[i].cost<<endl;

	}
	Ffout.close();
	CT.clear();
	CT.shrink_to_fit();

}

//Pilelineì¬i2014/07/18j
void create_pileline_01(int* VoxSize)
{
	Pileline P;
	edge E;
	CVector3d temp;
	vector<Pileline> CT;//connection
	vector<edge>  Et;//edge cost
	int count=0;
	for(int z(1); z<VoxSize[2]-1; z++)
		for(int x(1); x<VoxSize[0]-1; x++)
		{
			for(int y(1); y<VoxSize[1]-1; y++)
			{
				if(block[x][y][z].fill == false)continue;
				//###################################
				//‚P~‚P‚Ìê‡
				//###################################
				if(block[x][y][z].flag == 1)
				{
					temp.Set(x,y,z);
					P.Point.push_back(temp);
					P.num=1;

					P.gravity.Clear();
					for(int i(0); i <(int)P.Point.size();i++)
						P.gravity+=P.Point[i];
					P.gravity.Set(P.gravity.x/P.num , P.gravity.y/P.num , P.gravity.z/P.num);
					if((zcood-1)==z)
						P.ground=true;
					if(block[x][y][z].in_surf)
						P.in_surf=true;
					CT.push_back(P);
					P.init();
					temp.Clear();
					P.Point.clear();
					P.Point.shrink_to_fit();
					block[x][y][z].BrickN=count;
					count++;
				}
				else if(block[x][y][z].flag > 1)
				{
					if(block[x][y][z].corner != 1)
						continue;

					//###################################
					//‚P~‚Q‚Ìê‡
					//###################################
					if(block[x][y][z].flag == 12)
					{
						//‚P~‚Q‚ª‚™•ûŒü‚Ìê‡
						if(block[x][y+1][z].flag == 12 && block[x][y][z].ID == block[x][y+1][z].ID && block[x][y+1][z].corner == 2)
						{
							for(int i(0);i<2;i++){
								temp.Set(x,y+i,z);
								P.Point.push_back(temp);
								block[x][y+i][z].BrickN=count;
							}
							P.num=2;

							P.gravity.Clear();
							for(int i(0); i <(int)P.Point.size();i++)
								P.gravity+=P.Point[i];
							P.gravity.Set(P.gravity.x/P.num , P.gravity.y/P.num , P.gravity.z/P.num);
							if((zcood-1)==z)
								P.ground=true;
							if(block[x][y][z].in_surf)
								P.in_surf=true;
							CT.push_back(P);
							P.init();
							temp.Clear();				
							P.Point.clear();
							P.Point.shrink_to_fit();
							count++;
							continue;
						}
						//‚P~‚Q‚ª‚˜•ûŒü‚Ìê‡
						if(block[x+1][y][z].flag == 12 && block[x][y][z].ID == block[x+1][y][z].ID && block[x+1][y][z].corner == 2)
						{
							for(int i(0);i<2;i++){
								temp.Set( x+i , y ,z );
								P.Point.push_back(temp);
								block[x+i][y][z].BrickN=count;
							}
							P.num=2;

							P.gravity.Clear();
							for(int i(0); i <(int)P.Point.size();i++)
								P.gravity+=P.Point[i];
							P.gravity.Set(P.gravity.x/P.num , P.gravity.y/P.num , P.gravity.z/P.num);

							if((zcood-1)==z)
								P.ground=true;
							if(block[x][y][z].in_surf)
								P.in_surf=true;
							CT.push_back(P);
							P.init();
							temp.Clear();
							P.Point.clear();
							P.Point.shrink_to_fit();
							count++;
						}
					}
					//###################################
					//‚P~‚R‚Ìê‡
					//###################################
					//else if(block[x][y][z].flag == 13 && block[x][y][z].corner == 1)
					else if(block[x][y][z].flag == 13)
					{
						//‚P~‚R‚ª‚™•ûŒü‚Ìê‡
						if(y+2 < VoxSize[1])
						{
							if(block[x][y+2][z].flag == 13 && block[x][y][z].ID == block[x][y+2][z].ID && block[x][y+2][z].corner == 2)
							{
								for(int i(0);i<3;i++){
									temp.Set( x , y+i ,z );
									P.Point.push_back(temp);
									block[x][y+i][z].BrickN=count;
								}
								P.num=3;

								P.gravity.Clear();
								for(int i(0); i <(int)P.Point.size();i++)
									P.gravity+=P.Point[i];
								P.gravity.Set(P.gravity.x/P.num , P.gravity.y/P.num , P.gravity.z/P.num);

								if((zcood-1)==z)
									P.ground=true;
								if(block[x][y][z].in_surf)
									P.in_surf=true;
								CT.push_back(P);
								P.init();
								temp.Clear();
								P.Point.clear();
								P.Point.shrink_to_fit();
								count++;	
								continue;
							}
						}
						//‚P~‚R‚ª‚˜•ûŒü‚Ìê‡
						if(x+2 < VoxSize[0])
						{
							if(block[x+2][y][z].flag == 13 && block[x][y][z].ID == block[x+2][y][z].ID && block[x+2][y][z].corner == 2)
							{
								for(int i(0);i<3;i++){
									temp.Set( x+i , y ,z );
									P.Point.push_back(temp);
									block[x+i][y][z].BrickN=count;
								}
								P.num=3;

								P.gravity.Clear();
								for(int i(0); i <(int)P.Point.size();i++)
									P.gravity+=P.Point[i];
								P.gravity.Set(P.gravity.x/P.num , P.gravity.y/P.num , P.gravity.z/P.num);

								if((zcood-1)==z)
									P.ground=true;
								if(block[x][y][z].in_surf)
									P.in_surf=true;
								CT.push_back(P);
								P.init();
								temp.Clear();
								P.Point.clear();
								P.Point.shrink_to_fit();
								count++;
							}
						}
					}

					//###################################
					//‚P~‚S‚Ìê‡
					//###################################
					//else if(block[x][y][z].flag == 14 && block[x][y][z].corner == 1)
					else if(block[x][y][z].flag == 14)
					{
						//‚P~‚S‚ª‚™•ûŒü‚Ìê‡
						if(y+3 < VoxSize[1])
						{
							if(block[x][y+3][z].flag == 14 && block[x][y][z].ID == block[x][y+3][z].ID && block[x][y+3][z].corner == 2)
							{
								for(int i(0);i<4;i++){
									temp.Set( x , y+i ,z );
									P.Point.push_back(temp);
									block[x][y+i][z].BrickN=count;
								}
								P.num=4;

								P.gravity.Clear();
								for(int i(0); i <(int)P.Point.size();i++)
									P.gravity+=P.Point[i];
								P.gravity.Set(P.gravity.x/P.num , P.gravity.y/P.num , P.gravity.z/P.num);

								if((zcood-1)==z)
									P.ground=true;
								if(block[x][y][z].in_surf)
									P.in_surf=true;
								CT.push_back(P);
								P.init();
								temp.Clear();
								P.Point.clear();
								P.Point.shrink_to_fit();
								count++;
								continue;

							}
						}
						//‚P~‚S‚ª‚˜•ûŒü‚Ìê‡
						if(x+3 < VoxSize[0])
						{
							if(block[x+3][y][z].flag == 14 && block[x][y][z].ID == block[x+3][y][z].ID && block[x+3][y][z].corner == 2)
							{
								for(int i(0);i<4;i++){
									temp.Set( x+i , y ,z );
									P.Point.push_back(temp);
									block[x+i][y][z].BrickN=count;
								}
								P.num=4;

								P.gravity.Clear();
								for(int i(0); i <(int)P.Point.size();i++)
									P.gravity+=P.Point[i];
								P.gravity.Set(P.gravity.x/P.num , P.gravity.y/P.num , P.gravity.z/P.num);

								if((zcood-1)==z)
									P.ground=true;
								if(block[x][y][z].in_surf)
									P.in_surf=true;
								CT.push_back(P);
								P.init();
								temp.Clear();
								P.Point.clear();
								P.Point.shrink_to_fit();
								count++;
							}
						}
					}
					//###################################
					//‚Q~‚Q‚Ìê‡
					//###################################
					//else if(block[x][y][z].flag == 22 && block[x][y][z].corner == 1)
					else if(block[x][y][z].flag == 22)
					{
						if(block[x+1][y+1][z].flag == 22 && block[x][y][z].ID == block[x+1][y+1][z].ID && block[x+1][y+1][z].corner == 2)
						{
							for(int i(0) ; i<2;++i)
								for(int j(0);j<2;++j){
									temp.Set(x+i,y+j,z);
									P.Point.push_back(temp);
									block[x+i][y+j][z].BrickN=count;
								}
								P.num=4;

								P.gravity.Clear();
								for(int i(0); i <(int)P.Point.size();i++)
									P.gravity+=P.Point[i];
								P.gravity.Set(P.gravity.x/P.num , P.gravity.y/P.num , P.gravity.z/P.num);

								if((zcood-1)==z)
									P.ground=true;
								if(block[x][y][z].in_surf)
									P.in_surf=true;
								CT.push_back(P);
								P.init();
								temp.Clear();
								P.Point.clear();
								P.Point.shrink_to_fit();
								count++;
						}
					}
					//###################################
					//‚Q~‚R‚Ìê‡
					//###################################
					//else if(block[x][y][z].flag == 23 && block[x][y][z].corner == 1)
					else if(block[x][y][z].flag == 23)
					{
						//‚Q~‚R‚ª‚™•ûŒü‚Ìê‡
						if(y+2 < VoxSize[1])
						{
							if(block[x+1][y+2][z].flag == 23 && block[x][y][z].ID == block[x+1][y+2][z].ID && block[x+1][y+2][z].corner == 2)
							{
								for(int i(0) ; i<2;++i)
									for(int j(0);j<3;++j){
										temp.Set(x+i,y+j,z);
										P.Point.push_back(temp);
										block[x+i][y+j][z].BrickN=count;
									}
									P.num=6;

									P.gravity.Clear();
									for(int i(0); i <(int)P.Point.size();i++)
										P.gravity+=P.Point[i];
									P.gravity.Set(P.gravity.x/P.num , P.gravity.y/P.num , P.gravity.z/P.num);

									if((zcood-1)==z)
										P.ground=true;
									if(block[x][y][z].in_surf)
										P.in_surf=true;
									CT.push_back(P);
									P.init();
									temp.Clear();
									P.Point.clear();
									P.Point.shrink_to_fit();
									count++;
									continue;
							}
						}
						//‚Q~‚R‚ª‚˜•ûŒü‚Ìê‡
						if(x+2 < VoxSize[0])
						{
							if(block[x+2][y+1][z].flag == 23 && block[x][y][z].ID == block[x+2][y+1][z].ID && block[x+2][y+1][z].corner == 2)
							{
								for(int i(0) ; i<3;++i)
									for(int j(0);j<2;++j){
										temp.Set(x+i,y+j,z);
										P.Point.push_back(temp);
										block[x+i][y+j][z].BrickN=count;
									}
									P.num=6;
									P.gravity.Clear();

									for(int i(0); i <(int)P.Point.size();i++)
										P.gravity+=P.Point[i];
									P.gravity.Set(P.gravity.x/P.num , P.gravity.y/P.num , P.gravity.z/P.num);

									if((zcood-1)==z)
										P.ground=true;
									if(block[x][y][z].in_surf)
										P.in_surf=true;
									CT.push_back(P);
									P.init();
									temp.Clear();
									P.Point.clear();
									P.Point.shrink_to_fit();
									count++;
							}
						}
					}
					//###################################
					//‚Q~‚S‚Ìê‡
					//###################################
					//else if(block[x][y][z].flag == 24 && block[x][y][z].corner == 1)
					else if(block[x][y][z].flag == 24)
					{
						//‚Q~‚S‚ª‚™•ûŒü‚Ìê‡
						if(y+3 < VoxSize[1])
						{
							if(block[x+1][y+3][z].flag == 24 && block[x][y][z].ID == block[x+1][y+3][z].ID && block[x+1][y+3][z].corner == 2)
							{
								for(int i(0) ; i<2;++i)
									for(int j(0);j<4;++j){
										temp.Set(x+i,y+j,z);
										block[x+i][y+j][z].BrickN=count;
										P.Point.push_back(temp);
									}
									P.num=8;
									P.gravity.Clear();

									for(int i(0); i <(int)P.Point.size();i++)
										P.gravity+=P.Point[i];
									P.gravity.Set(P.gravity.x/P.num , P.gravity.y/P.num , P.gravity.z/P.num);

									if((zcood-1)==z)
										P.ground=true;
									if(block[x][y][z].in_surf)
										P.in_surf=true;
									CT.push_back(P);
									P.init();
									temp.Clear();
									P.Point.clear();
									P.Point.shrink_to_fit();
									count++;
									continue;
							}
						}
						//‚Q~‚S‚ª‚˜•ûŒü‚Ìê‡
						if(x+3 < VoxSize[0])
						{
							if(block[x+3][y+1][z].flag == 24 && block[x][y][z].ID == block[x+3][y+1][z].ID && block[x+3][y+1][z].corner == 2)
							{
								for(int i(0) ; i<4;++i)
									for(int j(0);j<2;++j){
										temp.Set(x+i,y+j,z);
										P.Point.push_back(temp);
										block[x+i][y+j][z].BrickN=count;
									}
									P.num=8;
									P.gravity.Clear();

									for(int i(0); i <(int)P.Point.size();i++)
										P.gravity+=P.Point[i];
									P.gravity.Set(P.gravity.x/P.num , P.gravity.y/P.num , P.gravity.z/P.num);

									if((zcood-1)==z)
										P.ground=true;
									if(block[x][y][z].in_surf)
										P.in_surf=true;
									CT.push_back(P);
									P.init();
									temp.Clear();
									P.Point.clear();
									P.Point.shrink_to_fit();
									count++;
							}
						}
					}
				}
			}
		}

		//for(int z(1); z<VoxSize[2]-1; z++)
		//	for(int x(1); x<VoxSize[0]-1; x++)
		//	{
		//		for(int y(1); y<VoxSize[1]-1; y++)
		//		{
		//			if(block[x][y][z].fill == false)continue;
		//
		//		
		//		
		//		
		//		}
		//	}



	vector<int> Nc;
	//•Ó‚ÆƒRƒXƒgŒvZ
	for(int i (0); i < (int) CT.size();++i){
		for(int c(0); c< CT[i].num; c++){

			if(block[(int)CT[i].Point[c].x][(int)CT[i].Point[c].y][(int)CT[i].Point[c].z+1].fill){
				Nc.push_back(block[(int)CT[i].Point[c].x][(int)CT[i].Point[c].y][(int)CT[i].Point[c].z+1].BrickN);
			if(block[(int)CT[i].Point[c].x][(int)CT[i].Point[c].y][(int)CT[i].Point[c].z+1].BrickN==0)
				cout<<"‚¨‚©‚µ‚¢‚Ì‚Í   "<<(int)CT[i].Point[c].z<<"  "<<block[(int)CT[i].Point[c].x][(int)CT[i].Point[c].y][(int)CT[i].Point[c].z+1].flag<<endl;
			}
		}

		//int number=0;
		//cout<<endl;
		//for(int a(0); a <(int) Nc.size(); a++){
		//cout<<Nc[a]<<"   ";
		//	if(Nc[a]==-10)continue;
		//	int count=1;
		//	number=Nc[a];
		//	for(int k = a+1; k <(int) Nc.size();k++){
		//		if(Nc[k] == number){
		//			count++;
		//			Nc[k]=-10;
		//		}
		//		E.cost=count;
		//		E.PN[0]=i;
		//		E.PN[1]=number;
		//		Et.push_back(E);
		//									}
		//							}
		//Nc.clear();
		//Nc.shrink_to_fit();
		
		//“¯‚¶”Ô†‚ğ‚Ç‚¤”‚¦‚é‚©
		int num=0;
		int cou=0;
		for(int a(0) ; a < (int)Nc.size();a++){
			if(Nc[a]<0)continue;
			cou=0;
		num=Nc[a];
		for(int k(a+1); k < (int)Nc.size(); k++){
			if(Nc[k]==num){
				cou++;
				Nc[k]=-10;
			}
		}
				E.cost=cou+1;
				E.PN[0]=i;
				E.PN[1]=num;
				Et.push_back(E);
		}
		Nc.clear();
		Nc.shrink_to_fit();
	}

	ofstream Ffout("Pileline_gravity01.txt");
	Ffout<<CT.size()<<"  "<<Et.size()<<endl;
	for(int i (0); i < (int) CT.size();++i){
		//CT[i].gravity.Print();
		//Ffout<<CT[i].gravity.x<<"   "<<CT[i].gravity.y<<"   "<<CT[i].gravity.z*1.2<<endl;
		//LEGOd—l‚É•ÏX
		//Ffout<<CT[i].gravity.y<<"   "<<VoxSize[2]-CT[i].gravity.z<<"   "<<(VoxSize[0]-CT[i].gravity.x)*1.2<<endl;
		Ffout<<CT[i].gravity.x<<"   "<<CT[i].gravity.y<<"   "<<CT[i].gravity.z*1.2<<"  "<<CT[i].num<<"  "<<CT[i].ground
			<<"  "<<CT[i].in_surf<<endl;
	}
	for(int i(0) ; i < (int)Et.size(); i++)
	{
		Ffout<<Et[i].PN[0]<<" "<<Et[i].PN[1]<<" "<<Et[i].cost<<endl;

	}
	Ffout.close();
	CT.clear();
	CT.shrink_to_fit();
	
	
	//PilelineƒAƒ‹ƒSƒŠƒYƒ€‚æ‚èŠO‘¤‚Ì’Œ‚ğ”z’u‚·‚é
	//ì‚èI‚í‚Á‚½ŒãAœ‹
	int ID,flag ,Zcoord,Xcoord,Ycoord;
	//double Zcoord,Xcoord,Ycoord;
	string line;
	stringstream ssline;
	fstream fin("Prop.txt");
	for(int i (0) ; i < 10 ; i++){
	getline(fin , line);
	ssline.str(line);
	ssline>>Xcoord>>Ycoord>>Zcoord;
	ssline.clear();
	//‚RŸŒ³”z—ñ‚É‘Î‰‚³‚¹A’Œ‚ğì‚é
	ID=block[Xcoord][Ycoord][Zcoord].ID;
	flag=block[Xcoord][Ycoord][Zcoord].flag;

		//for(int j = Zcoord+1; j < zcood ; j++){
			if(flag==24){
				if(block[Xcoord-2][(int)(Ycoord)-1][Zcoord].ID==ID&&
					block[Xcoord-2][(int)(Ycoord)-1][Zcoord].flag==flag&&
					block[Xcoord-2][(int)(Ycoord)-1][Zcoord].corner==1){
						for(int j = Zcoord+1; j < zcood ; j++){
							ID24++;change_bricks(block,Xcoord-2,Ycoord-1,j,4,2,ID24,flag);
						}
				}
				else if(block[Xcoord-1][Ycoord-2][Zcoord].ID==ID&&
						  block[Xcoord-1][Ycoord-2][Zcoord].flag==flag&&
						  block[Xcoord-1][Ycoord-2][Zcoord].corner==1){
						for(int j = Zcoord+1; j < zcood ; j++){
							ID24++;change_bricks(block,Xcoord-1,Ycoord-2,j,2,4,ID24,flag);
						}
				}
			}
			
			else if(flag==23){
				 if(block[Xcoord][Ycoord+1][Zcoord].ID==ID&&
					block[Xcoord][Ycoord+1][Zcoord].flag==flag){
						for(int j = Zcoord+1; j < zcood ; j++){
							ID23++;change_bricks(block,Xcoord-1,Ycoord-1,j,3,2,ID23,flag);
						}
				}
				else {
						for(int j = Zcoord+1; j < zcood ; j++){
							ID23++;change_bricks(block,Xcoord-1,Ycoord-1,j,2,3,ID23,flag);
						}
				}
			}
			else if(flag==22){
				for(int j = Zcoord+1; j < zcood ; j++){
					ID22++;change_bricks(block,Xcoord-1,Ycoord-1,j,2,2,ID22,flag);
	
				}
			}
			else if(flag==14){
				if(block[Xcoord-2][Ycoord][Zcoord].ID==ID&&
				   block[Xcoord-2][Ycoord][Zcoord].flag==flag){
						for(int j = Zcoord+1; j < zcood ; j++){
							ID14++;change_bricks(block,Xcoord-2,Ycoord,j,4,1,ID14,flag);
						}
				}
				else {
					for(int j = Zcoord+1; j < zcood ; j++){
						ID14++;change_bricks(block,Xcoord,Ycoord-2,j,1,4,ID14,flag);
					}
				}
			}
			else if(flag==13){
				if(block[Xcoord-1][Ycoord][Zcoord].ID==ID&&
				   block[Xcoord-1][Ycoord][Zcoord].flag==flag){
						for(int j = Zcoord+1; j < zcood ; j++){
							ID13++;change_bricks(block,Xcoord-1,Ycoord,j,3,1,ID13,flag);
						}
				}
				else {
					for(int j = Zcoord+1; j < zcood ; j++){
						ID14++;change_bricks(block,Xcoord,Ycoord-1,j,1,3,ID13,flag);
					}
				}
			}
			else if(flag==12){
				if(block[Xcoord-1][Ycoord][Zcoord].ID==ID&&
				   block[Xcoord-1][Ycoord][Zcoord].flag==flag){
						for(int j = Zcoord+1; j < zcood ; j++){
							ID12++;change_bricks(block,Xcoord-1,Ycoord,j,2,1,ID12,flag);
						}
				}
				else {
					for(int j = Zcoord+1; j < zcood ; j++){
						ID12++;change_bricks(block,Xcoord,Ycoord-1,j,1,2,ID12,flag);
					}
				}
			}
			else if(flag==1){
				for(int j = Zcoord+1; j < zcood ; j++){
					change_bricks(block,Xcoord,Ycoord,j,1,1,0,flag);
				}
			}
		//}
	}
}