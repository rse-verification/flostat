// x1:U(-100,100), x2:U(-100,100), x3:U(-100,100), x4:U(-100,100), x5:U(-100, 100)
// ((((((((((x1 - 1) * (x1 - 1)) + (x2 * x1)) - ((x2 - 1) * (x2 - 1))) + (x3 * x2)) - ((x3 - 1) * (x3 - 1))) + (x4 * x3)) - ((x4 - 1) * (x4 - 1))) + (x5 * x4)) - ((x5 - 1) * (x5 - 1)))


/*@
  \flostat::distribution x1, "Normal", 0.0, 50.0;
	\flostat::distribution x2, "Normal", 0.0, 50.0;
  \flostat::distribution x3, "Normal", 0.0, 50.0;
  \flostat::distribution x4, "Normal", 0.0, 50.0;
  \flostat::distribution x5, "Normal", 0.0, 50.0;
  \flostat::prob_ensures 0.99,
	\flteq(\result, ((((((((((x1 - 1) * (x1 - 1)) + (x2 * x1)) -
    ((x2 - 1) * (x2 - 1))) + (x3 * x2)) - ((x3 - 1) * (x3 - 1))) +
      (x4 * x3)) - ((x4 - 1) * (x4 - 1))) + (x5 * x4)) - ((x5 - 1) *
        (x5 - 1))), 2.690000e-02);
*/
float main(float x1, float x2, float x3, float x4, float x5) {
  return ((((((((((x1 - 1.0) * (x1 - 1.0)) + (x2 * x1)) -
    ((x2 - 1.0) * (x2 - 1.0))) + (x3 * x2)) - ((x3 - 1.0) * (x3 - 1.0))) +
    (x4 * x3)) - ((x4 - 1.0) * (x4 - 1.0))) + (x5 * x4)) - ((x5 - 1.0) *
    (x5 - 1.0)));
}
