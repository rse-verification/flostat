
/*@
  \flostat::distribution x, "Normal", 0.0, 0.785398163395;
  \flostat::prob_ensures 0.99,
	\flteq(\result, x - (x*x*x)/6.0 + (x*x*x*x*x)/120.0 -
		(x*x*x*x*x*x*x)/5040.0, 2.367187e-07);
*/
float main(float x) {
    // require(x > -1.57079632679 && x < 1.57079632679)
    return x - (x*x*x)/6.0f + (x*x*x*x*x)/120.0f -
			(x*x*x*x*x*x*x)/5040.0f;
}
