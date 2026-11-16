
/*@
  \flostat::distribution x, "Uniform", 0.0, 1.0;
  \flostat::distribution y, "Uniform", 0.0, 1.0;
  \flostat::distribution z, "Uniform", 0.0, 1.0;
  \flostat::prob_ensures 0.99, \flteq(\result, 1.0, 22.2/8.0);
*/
float main(float x, float y, float z) {
  float sigma = 10.0;
  float rho = 28.0;
  float beta = 8.0 / 3.0;
  float dt = 0.01;

  for (int i = 0; i < 1000; i++) {
    float next_x = x + dt * (sigma * (y - x));
    float next_y = y + dt * (x * (rho - z) - y);
    float next_z = z + dt * (x * y - beta * z);
    x = next_x;
    y = next_y;
    z = next_z;
  }
  return y;
}
