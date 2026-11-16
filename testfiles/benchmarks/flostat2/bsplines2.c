/*@
  \flostat::distribution u, "Uniform", 0.0, 1.0;
  \flostat::prob_ensures 0.99,
      \flteq(\result, (-3 * u*u*u  + 3*u*u + 3*u + 1) / 6, 1.94E-07/2.0);
*/
float main(float u) {
	return (-3.0f * u*u*u  + 3.0f*u*u + 3.0f*u + 1.0f) / 6.0f;
}
