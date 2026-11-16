/*@
  \flostat::distribution u, "Uniform", -30.0, 120.0;
  \flostat::distribution v, "Uniform", 320.0, 20300.0;
  \flostat::distribution T, "Uniform", -50.0, 30.0;
  \flostat::prob_ensures 0.99,
  \flteq(\result, (-(331.4f + (0.6f * T)) * v) /
          (((331.4f + (0.6f * T)) + u) *
          ((331.4f + (0.6f * T)) + u)), 4.55E-05/2.0);
*/
float main(float u, float v, float T) {
	float t1 = 331.4f + (0.6f * T);
	return (-t1 * v) / ((t1 + u) * (t1 + u));
}
