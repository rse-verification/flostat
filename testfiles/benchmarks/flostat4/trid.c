
/*@
  \flostat::distribution x1, "Uniform", -100.0, 100.0;
	\flostat::distribution x2, "Uniform", -100.0, 100.0;
  \flostat::prob_ensures 0.99,
	\flteq(\result, (((x1 - 1) * (x1 - 1)) + (x2 * x1)) -
    ((x2 - 1) * (x2 - 1)), 1.030000e-02/4.0);
*/
float main(float x1, float x2) {
    return (((x1 - 1.0) * (x1 - 1.0)) + (x2 * x1)) - ((x2 - 1.0) * (x2 - 1.0));
}
