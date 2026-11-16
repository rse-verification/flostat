/*@
  \flostat::distribution u, "Normal", 0.0, 25.0;
  \flostat::distribution v, "Normal", 10010.0, 4995.0;
  \flostat::distribution T, "Normal", 10.0, 20.0;
  \flostat::prob_ensures 0.99,
  \flteq(\result, (-(331.4f + (0.6f * T)) * v) /
          (((331.4f + (0.6f * T)) + u) *
          ((331.4f + (0.6f * T)) + u)), 7.95E-05);
*/
float main(float u, float v, float T) {
	float t1 = 331.4f + (0.6f * T);
	return (-t1 * v) / ((t1 + u) * (t1 + u));
}
