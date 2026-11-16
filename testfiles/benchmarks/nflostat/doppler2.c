/*@
  \flostat::distribution u, "Normal", 0.0, 31.25;
  \flostat::distribution v, "Normal", 12507.5, 6246.25;
  \flostat::distribution T, "Normal", 10.0, 25.0;
  \flostat::prob_ensures 0.99,
  \flteq(\result, (-(331.4f + (0.6f * T)) * v) /
          (((331.4f + (0.6f * T)) + u) *
          ((331.4f + (0.6f * T)) + u)), 1.43E-04);
*/
float main(float u, float v, float T) {
	float t1 = 331.4f + (0.6f * T);
	return (-t1 * v) / ((t1 + u) * (t1 + u));
}
