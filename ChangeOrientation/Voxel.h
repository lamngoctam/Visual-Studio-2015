#ifndef ___OCTREE_H_
#define ___OCTREE_H_

#include "stdafx.h"

//Octree
class OctVoxel{		//2520!!!!(2013/5/2)

public:

	CVector3d origin;		//Voxel W(x,y,z) 2014
	double length;			//
	double height;			//Å
	short LV;				//OctreeÇ
	//
	bool in;				//inside
	bool out;				//outside
	bool amb;			    //ambiguous
	//OctVoxel child[8];
	int ND[3];//number of division x,y,z

	OctVoxel();
	
	OctVoxel(double width);

	void SetParameter(double width);
	void SetOrigin(CVector3d& ori);
	void SetVertexWorld(CVector3d* vertW);			
	void SetVertexWorld_Rotated(double Rotated_Angle, CVector3d* vertW);
	void SetVertexWorld_6(CVector3d& vertW);		
	void SetVertexWorld_6_Rotated(double Rotated_Angle, CVector3d& vertW);
	void OutputInformation();
	void CalcCenterGrabity();	

	double Orientation_Angle;
	//~OctVoxel();
	void SetVertexWorld_Center_Rotated(double Rotated_Angle, CVector3d& vertW); 
	CVector3d Center_Octrees;
	void SetVertexWorld_Center_(CVector3d& vertW);
	//2016/5/17
	void Set_Middle_World(CVector3d* vertW);

};

//Octree
class Voxel{			//(2013/5/2)
public:
	bool fill;		
	bool surf;					//
	CVector3d origin;			//VoxelïW(x,y,z)(24)Å@2014Å
	CVector3d center;			// Voxel center
	static double length;		
	static double height;

	vector<CVector3d> line;


	//spin image
	CVector3d normal;							

	//
	double dist;		
	bool trial;			
	bool unknown;		
	bool known;			
	bool pushed;		
	bool pic;			
	cv::Point3i coord;	

	static bool Lessdist(const Voxel& a, const Voxel& b)	{	return a.dist < b.dist;	};
	
	Voxel();

	//
	void SetParameter(double width);
	void SetOrigin(CVector3d& ori);	//voxelÇ
	void SetCenterOfGrabity();
	void SetVertexWorld(CVector3d* vertW);	
	double Dist(Voxel a);					
	void SetTrial();						
	void SetKnown();						
	void SetCoord(int x,int y,int z);		
	void ClearDist();						
	void CoordTrans(CMatrix& m, CVector3d* vertexW);
	cv::Point CalcImageCoordofCenter(CMatrix ART);


	void SetCenterOfGrabity_Rotated(double Rotated_Angle);

	void SetVertexWorld_Rotated_PCA(double Rotated_Angle, CVector3d* vertW);

	void SetOrigin_Rotated(CVector3d& ori, double Rotated_Angle);
	void SetCoord_Rotated(int x, int y, int z, double Rotated_Angle);

};


//                                                                                                  
//                                                               
class VoxelFlag{
public:
	bool up;			
	bool down;			
	bool upCan;			
	bool downCan;	
	
	VoxelFlag();
	void Initialization();		
};


//ICPÇ
class OnetoOne{
public:
	double dist;	
	int num;		
	bool flag;		

	OnetoOne();		
	void Initial();	
};

//
class Labeling
{
public:
	bool fill;				
	int label;				
	
	
	Labeling();

	void SetFillValue(bool);	//fill flag
	void SetLabelNumber(int);	//labelç
	bool GetFillValue(void);	//fill flag
	int GetLabelNumber(void);	//label
};

//                                                       
//      Octree model & Voxel modelÇÇﬁmodel class      
//                                                       
class Model			//(2013/5/2)
{
public:
	//variable
	int OctLevel;		
	//Octree Model
	vector<OctVoxel> Octrees;	//Octree model
	vector<OctVoxel> Save_Up_Octrees;	//Octree model
	vector<OctVoxel> Save_Down_Octrees;	//Octree model
	vector<OctVoxel> New_Octrees;	//Octree model

	vector<CVector3d> max_vertex_point;
	vector<CVector3d> min_vertex_point;
	
	CVector3d max_vertex_bbox;
	CVector3d min_vertex_bbox[6];
	//2016/5/12
	CVector3d P_IntersecPoint[8]; // Plane intersection point
	CVector3d Diagonal_Point[8];
	//2016/5/14
	CVector3d New_smallcubicvertex[8];  // farest of extern bounding_box_vertex
	//2016/05/19
	vector<CVector3d> New_center_octrees; 
	

	//Voxel Model
	int num[3];					//x,y,zÇ(12edges)
	int VoxelNum;				//Model(4)
	int FillVoxelNum;			//Model(4)
	Voxel*** Voxels;			//Model(4) 3D dynamics array
	Voxel*** Check_Octree_surf;			//Model(4) 3D dynamics array
	int Surf_octree_Num;
	CColor*** Voxel_colors;		

	int SurfNum;				//Model(4) Number of surface
	vector<Voxel> SurfVoxels;
	vector<Voxel> SurfOctrees;

	vector<CColor> SurfColors;	

	vector<Voxel> IsoVoxels;	
	
	Voxel CorresVoxel3[3];		//spin imageóp

	VoxelFlag*** Flags;				

	//PCA
	CVector3d CoV;				 //Center of voxel (gravity)
	CVector3d PrAxix[3];		 //Principal axis
								 
	vector<CColor> LegoColor;	 //LEGO RGB
	vector<CColor> LegoColor_Lab;//LEGOÇLab
	vector<double> LegoHue;		 
	CColor BackColor;			 // RGB

	cv::Point3i Pick[3];	//(36)
	double MinDist;
	
	Model(int level);


	Voxel*** Octree_Check;

	//~Model();
	CVector3d VertexMin_;	//origin
	CVector3d VertexMax_;	//Diagonal point of origin

	vector<CVector3d> New_origin_octrees;
	OctVoxel BoundingBox;		//Bounding box of UP model
	
	int count_label;

	vector<int> ColorID;
};

//RGB
class Color_hue:public CColor
{
public:
	double hue;					//êFëäÅiÇOÅ`ÇRÇUÇOÅj
	double luminance;		//ãPìxÅiÇOÅ`ÇPÇOÇOÅj

	Color_hue();				//ÉRÉìÉXÉgÉâÉNÉ^
	
	void CalcHue();
	double GetHue();
	void CalcLuminance();
	double GetLuminance();
	
	void Clear();
	
	static bool Less_Lumi(const Color_hue& a, const Color_hue& b)	{	return a.luminance < b.luminance;	};
	static bool Less_Hue(const Color_hue& a, const Color_hue& b)	{	return a.hue < b.hue;	};

};



#endif