
/*@
  \flostat::distribution x, "Normal", 5.0, 2.5;
  \flostat::prob_ensures 0.99,
	\flteq(\result, ((((1.0 + (0.5*x)) - ((0.125*x)*x)) + (((0.0625*x)*x)*x)) -
      ((((0.0390625*x)*x)*x)*x)), 1.539099e-04/4.0);
*/
float main(float x) {
    return ((((1.0 + (0.5*x)) - ((0.125*x)*x)) +
        (((0.0625*x)*x)*x)) - ((((0.0390625*x)*x)*x)*x));
}
