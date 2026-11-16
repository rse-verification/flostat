
/*@
  \flostat::distribution a, "Normal", 7.5, 1.25;
	\flostat::distribution b, "Normal", 2.5, 1.25;
	\flostat::distribution c, "Normal", 2.5, 1.25;
	\flostat::prob_ensures 0.99,
		\flteq(\result, (((((2 * a) * a) * a) - (((9 * a) * b) + (27 * c))) / 54) +
			(((a * a) - (3 * b)) / 9), 1.716172e-05);
*/
float main(float a, float b, float c) {
	return (((((2.0 * a) * a) * a) - (((9.0 * a) * b) + (27.0 * c))) / 54.0) + (((a * a) - (3.0 * b)) / 9.0);
}
