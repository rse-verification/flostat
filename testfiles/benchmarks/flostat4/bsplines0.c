/*@
  \flostat::distribution u, "Uniform", 0.0, 1.0;
  \flostat::prob_ensures 0.99,
		\flteq(\result,
		((1-u) * (1-u) * (1-u)) / 6,
		5.71E-08/4.0);
*/
float main(float u) {
	return ((1.0f - u) * (1.0f - u) * (1.0f - u)) / 6.0f;
}
