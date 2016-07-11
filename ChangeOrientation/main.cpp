#include "func.h"


extern OctVoxel Angle_;

int main(int argc, char* argv[]) {

	//ZhangCalibration(argc, argv);
	for (auto angle(0); angle <= 90; angle += 10) {

		Angle_.Orientation_Angle = (20 * M_PI / 180);
		cout << "rotated angle: " << Angle_.Orientation_Angle << endl;

		ShapeFromSilhouette(Angle_.Orientation_Angle, argc, argv);

		PCA1(argc, argv);
		ICP(argc, argv);
		//	Rotated_Integ(argc, argv);
		//	
		//	PCA2(argc, argv);
		//	ICP(argc, argv);
		//
		//	Rotated_Integ3(argc, argv);
		//	PCA3(argc, argv);
		//	ICP(argc, argv);
		Integration(argc, argv);
		//Create LEGO brick instruction
		Building(argc, argv);
		
		exit(1);

	}

	return 0;
}


