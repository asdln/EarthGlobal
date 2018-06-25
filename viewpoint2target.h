int viewpoint2targetangle(double viewpoint_L, double viewpoint_B, double viewponit_H,
	double target_L, double target_B, double target_H, double *Pitch, double *azimuth, int axis_type);
int viewpoint2targetangle_xyz(double viewpoint_x, double viewpoint_y, double viewpoint_z,
	double target_x, double target_y, double target_z, double *Pitch, double *azimuth, int axis_type);
double getRotateAngle(double x1, double y1, double z1,
	double x2, double y2, double z2,
	double m, double n, double p);