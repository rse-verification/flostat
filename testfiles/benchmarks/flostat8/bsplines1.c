
/*@
  \flostat::distribution u, "Uniform", 0.0, 1.0;
  \flostat::prob_ensures 0.99,
		\flteq(\result, (3 * u*u*u - 6 * u*u + 4) / 6 , 1.86E-07/8.0);
*/
float main(float u) {
	return (3.0f * u * u * u - 6.0f * u * u + 4.0f) / 6.0f;
}
