
/*@
  \flostat::distribution x, "Normal", 0.5, 0.25;
  \flostat::distribution y, "Normal", 0.5, 0.25;
  \flostat::distribution z, "Normal", 0.5, 0.25;
  \flostat::prob_ensures 0.99, \flteq(\result, 1.0, 3.04E-5/2.0);
*/
float main(float x, float y, float z) {
  float sigma = 10.0;
  float rho = 28.0;
  float beta = 8.0 / 3.0;
  float dt = 0.01;

  for (int i = 0; i < 100; i++){
    float next_x = x + dt * (sigma * (y - x));
    float next_y = y + dt * (x * (rho - z) - y);
    float next_z = z + dt * (x * y - beta * z);
    x = next_x;
    y = next_y;
    z = next_z;
  }
  return y;
}
