/*@
  \flostat::distribution u, "Uniform", -125.0, 125.0;
  \flostat::distribution v, "Uniform", 15.0, 25000.0;
  \flostat::distribution T, "Uniform", -40.0, 60.0;
  \flostat::prob_ensures 0.99,
  \flteq(\result, (-(331.4f + (0.6f * T)) * v) /
          (((331.4f + (0.6f * T)) + u) *
          ((331.4f + (0.6f * T)) + u)), 1.43E-04);
*/
float main(float u, float v, float T) {
	float t1 = 331.4f + (0.6f * T);
	return (-t1 * v) / ((t1 + u) * (t1 + u));
}
