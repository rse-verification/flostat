/*@
  \flostat::distribution x, "Uniform", 0.0, 1.0;
  \flostat::distribution y, "Uniform", 0.0, 1.0;
  \flostat::distribution z, "Uniform", 0.0, 1.0;
  \flostat::prob_ensures 0.99, \flteq(\result, 1.0, 4.595288e-06);
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
  float x5 = x4 + time * (sigma * (y4 - x4));
  float y5 = y4 + time * (x4 * (rho - z4) - y4);
  float z5 = z4 + time * (x4 * y4 - beta * z4);
  float x6 = x5 + time * (sigma * (y5 - x5));
  float y6 = y5 + time * (x5 * (rho - z5) - y5);
  float z6 = z5 + time * (x5 * y5 - beta * z5);
  float x7 = x6 + time * (sigma * (y6 - x6));
  float y7 = y6 + time * (x6 * (rho - z6) - y6);
  float z7 = z6 + time * (x6 * y6 - beta * z6);
  float x8 = x7 + time * (sigma * (y7 - x7));
  float y8 = y7 + time * (x7 * (rho - z7) - y7);
  float z8 = z7 + time * (x7 * y7 - beta * z7);
  float x9 = x8 + time * (sigma * (y8 - x8));
  float y9 = y8 + time * (x8 * (rho - z8) - y8);
  float z9 = z8 + time * (x8 * y8 - beta * z8);
  float x10 = x9 + time * (sigma * (y9 - x9));
  float y10 = y9 + time * (x9 * (rho - z9) - y9);
  float z10 = z9 + time * (x9 * y9 - beta * z9);
  return y10;
}
