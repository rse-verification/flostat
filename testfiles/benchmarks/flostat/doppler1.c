/*@
  \flostat::distribution u, "Uniform", -100.0, 100.0;
  \flostat::distribution v, "Uniform", 20.0, 20000.0;
  \flostat::distribution T, "Uniform", -30.0, 50.0;
  \flostat::prob_ensures 0.99,
  \flteq(\result, (-(331.4f + (0.6f * T)) * v) /
          (((331.4f + (0.6f * T)) + u) *
          ((331.4f + (0.6f * T)) + u)), 7.95E-05);
*/
float main(float u, float v, float T) {
	float t1 = 331.4f + (0.6f * T);
	return (-t1 * v) / ((t1 + u) * (t1 + u));
}
