/*@
  \flostat::distribution x1, "Normal", 0.0, 7.5;
	\flostat::distribution x2, "Normal", 0.0, 7.5;
	\flostat::distribution x3, "Normal", 0.0, 7.5;
	\flostat::prob_ensures 0.99,
	\flteq(\result, 2*(x1*x2*x3) + (3*x3*x3) - x2*(x1*x2*x3) + (3*x3*x3) - x2,
		1.936293e-02/4.0);
*/
float main(float x1, float x2, float x3) {
	float t1 = x1*x2*x3;
	float t2 = 3.0f*x3*x3;
	return 2.0f*(t1) + t2 - x2*(t1) + t2 - x2;
}
