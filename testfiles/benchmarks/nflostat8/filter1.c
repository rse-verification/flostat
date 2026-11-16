
/*@
  \flostat::distribution x0, "Normal", 0.0, 1.0;
  \flostat::prob_ensures 0.99,
		\flteq(\result, 0.7 * x0 , 1.25E-07/8.0);
*/
float main(float x0) {
    // require(-2 <= x0 && x0 <= 2)
    return 0.7f * x0;
}
