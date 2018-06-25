bool fequal(double value1, double value2, double precision);
int line2atmosphereLBH(double viewpoint_L, double viewpoint_B, double viewponit_H,
	double target_L, double target_B, double target_H, double atmos_H,
	double *atmos_L, double *atmos_B, int axis_type);
int line2atmosphereXYZ(double Nearpoint_x, double Nearpoint_y, double Nearpoint_z,
	double Farpoint_x, double Farpoint_y, double Farpoint_z, double atmos_H,
	double *atmos_L, double *atmos_B,
	double *Land_L, double *Land_B,
	int axis_type);
int viewpointline2atmosphereXYZ(double viewpoint_L, double viewpoint_B, double viewponit_H,
	double Farpoint_x, double Farpoint_y, double Farpoint_z, double atmos_H,
	double *atmos_L, double *atmos_B,
	double *Land_L, double *Land_B,
	int axis_type);