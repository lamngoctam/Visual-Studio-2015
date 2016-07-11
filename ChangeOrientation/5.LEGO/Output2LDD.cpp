#include "../stdafx.h"

extern vector<Brick> LDD;
extern BrickTable table;
extern CMatrix rot[2];
extern string directory[2];	//データのディレクトリ
extern string model;			//モデルの名前
extern short OctLevels;	

//(LEGO Digital Designer)
void OutputBlock_lxfml()
{
	cout << "Output: LEGO Digital Designer  file - block.lxfml\n";
	cout<<"LDD size: "<<LDD.size()<<endl;
	string filename("block");
	string extension(".lxfml");
	ofstream fout(directory[1] + model + filename + extension);
	//#########################################
	//                                     最初の共通部分                                           
	//#########################################
	//<?xml version="1.0" encoding="UTF-8" standalone="no" ?>
	////<LXFML versionMajor="5" versionMinor="0" name="12">				//nameとはファイルの名前です//.lxfmlファイルの最初！
	//  <Meta>
	//   <Application name="LEGO Digital Designer" versionMajor="4" versionMinor="3"/>
	//   <Brand name="LDD"/>				//Brand name はLDD,LDDExtended,など
	//   <BrickSet version="1182"/>
	//// </Meta>
	fout<<"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n";
	fout<<"<LXFML versionMajor=\"5\" versionMinor=\"0\" name=\""<<filename<<"\">\n";
		//<<"  <Meta>\n"
		//<<"    <Application name=\"LEGO Digital Designer\" versionMajor=\"4\" versionMinor=\"3\"/>\n"
		//<<"    <Brand name=\"LDD\"/>\n"
		//<<"    <BrickSet version=\"1182\"/>\n"
		//<<"  </Meta>\n";

	//###################################
	//										カメラ											
	//###################################
	//  <Cameras>
	//   <Camera refID="0" fieldOfView="80" distance="7.964444637298584" transformation="0.78045809268951416,0,-0.62520796060562134,-0.4220941960811615,0.73770231008529663,-0.52690768241882324,0.46121734380722046,0.67512613534927368,0.57574576139450073,4.5381312370300293,5.8736329078674316,5.8184566497802734"/>
	// </Cameras>
	//fout<<"  <Cameras>\n"
	//	<<"    <Camera refID=\"0\" fieldOfView=\"200\" distance=\"300\" transformation=\"0.78045809268951416,0,-0.62520796060562134,-0.4220941960811615,0.73770231008529663,-0.52690768241882324,0.46121734380722046,0.67512613534927368,0.57574576139450073,100.0,100.0,100.0\"/>\n"
	//	<<"  </Cameras>\n";
	//###################################
	//									ブリックの配置								
	//###################################
	//<Bricks cameraRef="0">
	//   <Brick refID="0" designID="3004" itemNos="300421">
	//     <Part refID="0" designID="3004" materials="21,0,0,0" decoration="0,0,0">
	//       <Bone refID="0" transformation="0,0,1,0,0.99999994039535522,0,-1,0,0,0.40000000596046448,0,0.40000000596046448">		//回転と並進
	//       </Bone>
	//     </Part>
	//   </Brick>
	//   <Brick refID="0" designID="3004" itemNos="300421">
	//   </Brick>
	// </Bricks>
	
	//fout<<"  <Bricks cameraRef=\"0\">\n";
	fout<<"  <Bricks>\n";
	//ブロックの数に応じてループを回す


	unsigned designID;
	unsigned itemNos;
	unsigned colorID;
	unsigned rn;

	for(int i(0); i<LDD.size(); i++)
	{
		fout<<"    <Brick refID=\""<< i <<"\" designID=\""<< LDD[i].DesignID <<"\" itemNos=\""<< LDD[i].itemNos <<"\">\n";
		//場合わけが必要かもしれない(2014/1/23→全部それ以外でOKだった！
		//２×２：materials=\"21,0,0\" decoration=\"0,0\"
		//１×２：materials=\"21,0,0,0\" decoration=\"0,0,0\"
		//１×１：materials=\"21,0\" decoration=\"0\"
		//それ以外：materials=\"21\"
		//１×１の場合
		designID = LDD[i].DesignID;
		itemNos = LDD[i].itemNos;
		colorID = LDD[i].colorID;
		rn = LDD[i].rn;

		//if(designID == table.DesignID[0])
		//	fout<<"      <Part refID=\""<< i <<"\" designID=\""<< designID <<"\" materials=\""<< colorID <<",0\" decoration=\"0\">\n";
		////１×２の場合
		//else if(designID == table.DesignID[1])
		//	fout<<"      <Part refID=\""<< i <<"\" designID=\""<< designID <<"\" materials=\""<< colorID <<",0,0,0\" decoration=\"0,0,0\">\n";
		////２×２の場合
		//else if(designID == table.DesignID[4])
		//	fout<<"      <Part refID=\""<< i <<"\" designID=\""<< designID <<"\" materials=\""<< colorID <<",0,0\" decoration=\"0,0\">\n";
		////それ以外の場合
		//else
		//	fout<<"      <Part refID=\""<< i <<"\" designID=\""<< designID <<"\" materials=\""<< colorID <<"\">\n";

		fout<<"      <Part refID=\""<< i <<"\" designID=\""<< designID <<"\" materials=\""<< colorID <<"\">\n";	//これで十分

		fout<<"        <Bone refID=\""<< i <<"\" transformation=\""
			<<rot[rn][0][0]<<","<<rot[rn][0][1]<<","<<rot[rn][0][2]<<","
			<<rot[rn][1][0]<<","<<rot[rn][1][1]<<","<<rot[rn][1][2]<<","
			<<rot[rn][2][0]<<","<<rot[rn][2][1]<<","<<rot[rn][2][2]<<","
			<<LDD[i].trans.x<<","<<LDD[i].trans.y<<","<<LDD[i].trans.z<<"\">\n"
			<<"        </Bone>\n"
			<<"      </Part>\n"
			<<"    </Brick>\n";
	}
	fout<<"  </Bricks>\n";
	//###################################
	//						パーツを構成するブリック							
	//###################################
	//<RigidSystems>
	//<RigidSystem>
	//<Rigid refID="0" transformation="0,0,1,0,0.99999994039535522,0,-1,0,0,0.40000000596046448,0,0.40000000596046448" boneRefs="0"/>		//1番目のtransformationとこのパーツを構成するブロックのID
	//<Rigid refID="1" transformation="1,0,0,0,1,0,0,0,1,2,0,-2" boneRefs="1,2,3,4,5,6,7,8"/>
	//<Rigid refID="2" transformation="1,0,0,0,1,0,0,0,1,0.40000000596046448,0,1.2000000476837158" boneRefs="9,10"/>
	//<Joint type="hinge">			//ブロックとブロックの接続 hinge(二枚貝などのちょうつがい)
	//  <RigidRef rigidRef="1" a="0,1,0" z="0,0,1" t="1.6000001430511475,0.96000379323959351,2.4000000953674316"/>
	//  <RigidRef rigidRef="0" a="0,1,0" z="0,0,1" t="0,0.95999997854232788,-0.80000007152557373"/>
	//</Joint>
	//</RigidSystem>
	//</RigidSystems>

	//fout<<"  <RigidSystems>\n"
	//	//<<"    <RigidSystem>\n"
	//	//<<"      <Rigid refID=\"0\" transformation=\"0,0,1,0,0.99999994039535522,0,-1,0,0,0.40000000596046448,0,0.40000000596046448\" boneRefs=\"0\"/>\n"
	//	//<<"    </RigidSystem>\n"
	//	<<"  </RigidSystems>\n";



	//###################################
	//　　　　　最後の部分
	//###################################
	//	  <GroupSystems>
	//    <GroupSystem>
	//    </GroupSystem>
	//  </GroupSystems>
	//  <BuildingInstructions>
	//  </BuildingInstructions>
	//</LXFML>									//.lxfmlファイルの最後！
	//fout<<"  <GroupSystems>\n"
	//	<<"    <GroupSystem>\n"
	//	<<"    </GroupSystem>\n"
	//	<<"  </GroupSystems>\n"
	//	<<"  <BuildingInstructions>\n"
	//	<<"  </BuildingInstructions>\n"
	//	<<"</LXFML>\n";
	fout<<"</LXFML>\n";


}

//1 stud = 7.986 mm プラマイ 0.002 mm(２５°)
//横 1stud 高さ 6/5 stud