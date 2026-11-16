/*@
  \flostat::distribution x1, "Normal", 0.0, 7.5;
	\flostat::distribution x2, "Normal", 0.0, 7.5;
	\flostat::distribution x3, "Normal", 0.0, 7.5;
	\flostat::prob_ensures 0.99,
	\flteq(\result, -x1 * x2 - 2.0*x2*x3 - x1 - x3, 1.583099e-04/2.0);
*/
float main(float x1, float x2, float x3) {
	return -x1 * x2 - 2.0f*x2*x3 - x1 - x3;
}
