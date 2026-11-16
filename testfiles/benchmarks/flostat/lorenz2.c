/*@
  \flostat::distribution x, "Uniform", 0.0, 1.0;
  \flostat::distribution y, "Uniform", 0.0, 1.0;
  \flostat::distribution z, "Uniform", 0.0, 1.0;
  \flostat::prob_ensures 0.99, \flteq(\result, 1.0, 3.490917e-07);
*/
float main(float x, float y, float z) {
  float sigma = 10.0;
  float rho = 28.0;
  float beta = (8.0 / 3.0);
  float time = 0.01;
  float x1 = x + time * (sigma * (y - x));
  float y1 = y + time * (x * (rho - z) - y);
  float z1 = z + time * (x * y - beta * z);
  float x2 = x1 + time * (sigma * (y1 - x1));
  float y2 = y1 + time * (x1 * (rho - z1) - y1);
  return y2;
}
