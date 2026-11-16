
/*@
  \flostat::distribution x1, "Normal", 0.0, 50.0;
	\flostat::distribution x2, "Normal", 0.0, 50.0;
  \flostat::distribution x3, "Normal", 0.0, 50.0;
  \flostat::prob_ensures 0.99,
	\flteq(\result, (((((x1 - 1) * (x1 - 1)) + (x2 * x1)) - ((x2 - 1) *
    (x2 - 1))) + (x3 * x2)) - ((x3 - 1) * (x3 - 1)), 1.030000e-02/2.0);
*/
float main(float x1, float x2, float x3) {
    return (((((x1 - 1.0) * (x1 - 1.0)) + (x2 * x1)) - ((x2 - 1.0) * (x2 - 1.0))) +
        (x3 * x2)) - ((x3 - 1.0) * (x3 - 1.0));
}
