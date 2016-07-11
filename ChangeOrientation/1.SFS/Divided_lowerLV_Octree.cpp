#include "../stdafx.h"

extern int ImageNum;

extern double MinVoxelL;			//Length of the model minimum voxel
extern double MinVoxelH;			//Height of the model minimum voxel

void Divided_lowerLV_Octree(Model& m, short LV, double Rotated_Angle, vector<OctVoxel>& Octree){

	
	vector<OctVoxel>::iterator it;
	for (it = m.Octrees.begin(); it != m.Octrees.end(); ++it){
		OctVoxel temp;

		if (it->LV < LV - 1){
			temp.LV = it->LV;
			CVector3d x(2.0*MinVoxelL, 0.0, 0.0);
			CVector3d y(0.0, 2.0*MinVoxelL, 0.0);
			CVector3d z(0.0, 0.0, 2.0*MinVoxelH);

			CVector3d x_rotated = x *cos(Rotated_Angle) - y*sin(Rotated_Angle);
			CVector3d y_rotated = x *sin(Rotated_Angle) + y*cos(Rotated_Angle);
			CVector3d z_rotated = z;

			CVector3d vertex_[8];
			vertex_[0] = it->origin;
			vertex_[1] = it->origin + x_rotated;
			vertex_[2] = it->origin + x_rotated + y_rotated;
			vertex_[3] = it->origin + y_rotated;
			vertex_[4] = it->origin + z_rotated;
			vertex_[5] = it->origin + z_rotated + x_rotated;
			vertex_[6] = it->origin + z_rotated + x_rotated + y_rotated;
			vertex_[7] = it->origin + z_rotated + y_rotated;
			
			//it->origin.Clear();
			
			for (int n = 0; n < 8; ++n){			
				temp.SetOrigin(vertex_[n]);						

				CVector3d x2(MinVoxelL, 0.0, 0.0);
				CVector3d y2(0.0, MinVoxelL, 0.0);
				CVector3d z2(0.0, 0.0, MinVoxelH);

				CVector3d x_rot_2 = x2 *cos(Rotated_Angle) - y2*sin(Rotated_Angle);
				CVector3d y_rot_2 = x2 *sin(Rotated_Angle) + y2*cos(Rotated_Angle);
				CVector3d z_rot_2 = z2;

				CVector3d vertex_continue[8];
				vertex_continue[0] = temp.origin;
				vertex_continue[1] = temp.origin + x_rot_2;
				vertex_continue[2] = temp.origin + x_rot_2 + y_rot_2;
				vertex_continue[3] = temp.origin + y_rot_2;
				vertex_continue[4] = temp.origin + z_rot_2;
				vertex_continue[5] = temp.origin + z_rot_2 + x_rot_2;
				vertex_continue[6] = temp.origin + z_rot_2 + x_rot_2 + y_rot_2;
				vertex_continue[7] = temp.origin + z_rot_2 + y_rot_2;
				
				temp.LV++;

				for (int n = 0; n < 8; ++n){					
					
					temp.SetOrigin(vertex_continue[n]);
					m.New_Octrees.push_back(temp);
					
				}
				m.count_label++;

			}
			
		}

		else if (it->LV < LV){                                //Octree‚LV
			temp.LV = LV + 1;
			temp.origin.Clear();

			CVector3d x(MinVoxelL, 0.0, 0.0);
			CVector3d y(0.0, MinVoxelL, 0.0);
			CVector3d z(0.0, 0.0, MinVoxelH);

			CVector3d x_rotated = x *cos(Rotated_Angle) - y*sin(Rotated_Angle);
			CVector3d y_rotated = x *sin(Rotated_Angle) + y*cos(Rotated_Angle);
			CVector3d z_rotated = z;

			CVector3d vertex_[8];
			vertex_[0] = it->origin;
			vertex_[1] = it->origin + x_rotated;
			vertex_[2] = it->origin + x_rotated + y_rotated;
			vertex_[3] = it->origin + y_rotated;
			vertex_[4] = it->origin + z_rotated;
			vertex_[5] = it->origin + z_rotated + x_rotated;
			vertex_[6] = it->origin + z_rotated + x_rotated + y_rotated;
			vertex_[7] = it->origin + z_rotated + y_rotated;
			for (int n = 0; n < 8; ++n){
				temp.SetOrigin(vertex_[n]);
				m.New_Octrees.push_back(temp);

			}
			//it->origin.Clear();

		}

	}
	m.Octrees.reserve(m.Octrees.size() + m.New_Octrees.size());
	m.Octrees.insert(m.Octrees.end(), m.New_Octrees.begin(), m.New_Octrees.end());
	

	cout << "m.New_Octrees.size: " << m.New_Octrees.size() << endl;
	cout << "m.Octrees.size: " << m.Octrees.size() << endl;


	m.New_Octrees.clear();
	
}