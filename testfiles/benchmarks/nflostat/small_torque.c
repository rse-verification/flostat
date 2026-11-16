#include "math.h"

typedef struct {
  float phA;
  float phB;
} Current;

/*@
  \flostat::distribution c.phA, "Normal", 0.5, 0.25;
  \flostat::distribution c.phB, "Normal", 0.5, 0.25;
  \flostat::prob_ensures
    0.99,           // probability
    \flteq(\result, \sin(c.phA+c.phB),
    5.5e-8);     // maximum error
*/
float main(Current c) {
  float torque;
  float c_sum = c.phA;
  c_sum += c.phB;
  torque = sinf(c_sum);
  return torque;
}
