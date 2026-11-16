/*@
  \flostat::distribution u, "Uniform", 0.0, 1.0;
  \flostat::prob_ensures 0.99,
      \flteq(\result, -u*u*u / 6.0, 4.22E-08/8.0);
*/
float main(float u) {
	return -u*u*u / 6.0f;
}
