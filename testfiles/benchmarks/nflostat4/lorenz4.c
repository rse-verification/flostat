/*@
  \flostat::distribution x, "Normal", 0.5, 0.25;
  \flostat::distribution y, "Normal", 0.5, 0.25;
  \flostat::distribution z, "Normal", 0.5, 0.25;
  \flostat::prob_ensures 0.99, \flteq(\result, 1.0, 8.480037e-07/4.0);
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
  float z2 = z1 + time * (x1 * y1 - beta * z1);
  float x3 = x2 + time * (sigma * (y2 - x2));
  float y3 = y2 + time * (x2 * (rho - z2) - y2);
  float z3 = z2 + time * (x2 * y2 - beta * z2);
  float x4 = x3 + time * (sigma * (y3 - x3));
  float y4 = y3 + time * (x3 * (rho - z3) - y3);
  float z4 = z3 + time * (x3 * y3 - beta * z3);
  return y4;
}
