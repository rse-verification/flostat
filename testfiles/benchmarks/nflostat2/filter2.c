
/*@
  \flostat::distribution x0, "Normal", 0.0, 1.0;
  \flostat::distribution x1, "Normal", 0.0, 1.0;
  \flostat::prob_ensures 0.99,
		\flteq(\result, 0.7 * x1 - 1.3 * x0 + 1.4f * (0.7 * x0), 7.93E-07/2.0);
*/
float main(float x1, float x0) {
    return (0.7f) * x1 - (1.3f) * x0 + (1.4f) * ((0.7f) * x0);
}
