#include "../stdafx.h"


//                                                                                                                  
//   Calculate the matrix to convert the coordinates to image coordinates. 
//                                                                                                                  
void CalcWorldToImage(int ImageNum, string* directory,string model,string* pose, CMatrix* ART, CVector3d* CameraPosUp)
{
	clock_t time[10];
	time[0] = clock();

	CMatrix InnerParam(4);			//Inner matrix
	CMatrix OuterParam(4);			//For temporary storage of  external matrix
	
	
	CMatrix Rotation(3);			//Rotation matrix
	CMatrix RotationT(3);			//Transposed matrix of the rotation matrix
	CVector Translation(3);		//Translation matrix

	InnerParam.SetZero();		//Initialization
	OuterParam.SetZero();		//Initialization

	double det;

	//                                                   
	//Read inner parameters                 
	//                                                   
	string innerfile;			//The name of the internal parameters of the location 
	string sline;					//For temporary reading
	istringstream ssline;

	innerfile = directory[1] + model + pose[2] + "datain.txt";
	ifstream infile[2];
	
	infile[0].open( innerfile );
	if (!innerfile.data()){
		cout <<innerfile<<"is not found !"<< endl;	//File is not , etc
	}

	for(int i=0;i<3;i++){	
		getline( infile[0], sline );
		if (sline.size() == 0){
			break;
		}
		ssline.str( sline );		//Convert to stream
		ssline >> InnerParam(i,0) >>InnerParam(i,1)>>InnerParam(i,2);
		ssline.clear();				//Empty at ssline
	}
	infile[0].close();
	
	time[1] = clock();

	//cout<<InnerParam<<endl;
	cout<<"Finish to read inner parameters!"<<endl;

	//                                                   
	//      Read external parameters ¨Calculate ART matrix         
	//                                                   
	ostringstream SSout;
	string camfile = directory[1] + model + "CameraPosUpition.txt";
	ofstream outfile(camfile);
	CMatrix TMat(4);
	TMat.IdentifyMatrix();
	ifstream fin(directory[1]+model+"ICPMatrix.txt");
	for(int i = 0 ; i < 4 ;i++){
		for(int j = 0 ; j < 4 ;j++){
			fin>>TMat(i,j);
		}
	}
	TMat = TMat.Inverse();


	for(int k=0; k<ImageNum; ++k){		//36 images of external parameters
		//Read external parameters
		SSout << directory[1] << model << pose[2] << "data" << k << ".txt";
		infile[1].open( SSout.str() );
		if (!SSout.str().data()){
			cout <<SSout.str()<<"is not found !"<< endl;	//File is not .
		}

		for(int j=0;j<3;j++){
			getline( infile[1], sline );
			if (sline.size() == 0){
				break;
			}
			ssline.str( sline );		//Convert to stream
			ssline >> OuterParam(j,0)>>OuterParam(j,1)>>OuterParam(j,2)>>OuterParam(j,3);
			ssline.clear();				//Empty at ssline
		}
		infile[1].close();

		//It is necessary in order to homogeneous coordinates
		InnerParam(3,3) = 1.0;		//fourth column,fourth row :1
		OuterParam(3,3) = 1.0;		//fourth column,fourth row :1
		//Only zebra
		//OuterParam = OuterParam * TMat;
		//cout<<k<<" :"<<OuterParam<<endl;//

		//ART = Inner@~@External
		ART[k].assign(4);
		ART[k] = InnerParam * OuterParam;
		ART[k](3,3) = 1.0;

		
		////############case ‚P
		////http://www.aist-nara.ac.jp/~takafumi-t/lecture/sip2_2011_ikeda_08.pdf
		////See 19 page of the above URL
		//for(int x(0); x<3; x++)
		//{
		//	Translation[x] = OuterParam(x, 3);
		//	for(int y(0); y<3; y++)
		//	{
		//		Rotation(x, y) = OuterParam(x, y);
		//	}
		//}
		////RotationT = Rotation.Inverse();
		//RotationT = Rotation.Transpose();
		//CameraPosUp[k].x = - RotationT(0, 0) * Translation[0] - RotationT(0, 1) * Translation[1] - RotationT(0, 2) * Translation[2];
		//CameraPosUp[k].y = - RotationT(1, 0) * Translation[0] - RotationT(1, 1) * Translation[1] - RotationT(1, 2) * Translation[2];
		//CameraPosUp[k].z = - RotationT(2, 0) * Translation[0] - RotationT(2, 1) * Translation[1] - RotationT(2, 2) * Translation[2];


		////#############Case ‚Q( Apply official of Cramer in Case‚P)
		//http://aozoragakuen.sakura.ne.jp/taiwa/taiwasen/sennkei/node23.html
		det = OuterParam.Det();	//Determinant of external matrix RT
		CameraPosUp[k].x = -OuterParam.Remove(3,0).Det()/det;		//[ sign
		CameraPosUp[k].y = OuterParam.Remove(3,1).Det()/det;			//{ sign
		CameraPosUp[k].z = - OuterParam.Remove(3,2).Det()/det;		//[ sign


		//The output of the camera position in the file
		outfile<<CameraPosUp[k].x <<" "<<CameraPosUp[k].y<<" "<<CameraPosUp[k].z<<endl;
		//cout<<CameraPosUp[k].x <<" "<<CameraPosUp[k].y<<" "<<CameraPosUp[k].z<<endl;

		//Clear the variable of istringstream
		static const string empty_string;	
		//To return the initial state
		SSout.str(empty_string);			
		SSout.clear();						
		SSout<<dec;						
	}
	//outfile.close();
	time[2] = clock();
	
	cout<<"Finish to read external parameters to calculate ART matrix!"<<endl;
}

//ART 180
//(Zhang‚)
//void Rotate180withXaxis(int ImageNum, CMatrix* ART)
//{
//	//x180x]
//	CMatrix rotate(4);
//	rotate.SetZero();
//	rotate[0][1] = -1.0;
//	rotate[1][0] = -1.0;
//	rotate[2][2] = -1.0;
//	cout<<rotate<<endl;
//	for(int i(0); i<ImageNum; i++)
//		ART[i] = rotate*ART[i];
//
//}
