
/*@
  \flostat::distribution s0, "Normal", 2.0, 2.25;
  \flostat::distribution s1, "Normal", 2.0, 2.25;
  \flostat::distribution s2, "Normal", 2.0, 2.25;
  \flostat::distribution s3, "Normal", 2.0, 2.25;
	\flostat::distribution s4, "Normal", 5.0, 3.5;
  \flostat::distribution s5, "Normal", 5.0, 3.5;
  \flostat::distribution s6, "Normal", 5.0, 3.5;
  \flostat::distribution s7, "Normal", 5.0, 3.5;
  \flostat::distribution s8, "Normal", 5.0, 3.5;
  \flostat::prob_ensures 0.99,
	\flteq(\result, (-1201.0) * s0  + (-4876.0) * s1  + 1.3415999999999998E+04 *
    s2 + (-10484.0) * s3  + (-774.0) * s4  + (-1.3620000000000002E+04) *
    s5 + 10481.0 * s6 + 20425.0 * s7  + (-17815.0) *
    s8 + 5.2121094496644555E+03, 1.81E-1/2.0);
*/
float main(float s0, float s1, float s2, float s3, float s4, float s5, float s6, float s7, float s8) {
    // require(-2.5 <= s0 && s0 <= 6.5 &&
    //         -2.5 <= s1 && s1 <= 6.5 &&
    //         -2.5 <= s2 && s2 <= 6.5 &&
    //         -2.5 <= s3 && s3 <= 6.5 &&
    //         -2 <= s4 && s4 <= 12 &&
    //         -2 <= s5 && s5 <= 12 &&
    //         -2 <= s6 && s6 <= 12 &&
    //         -2 <= s7 && s7 <= 12 &&
    //         -2 <= s8 && s8 <= 12)
      return (-1201.0f) * s0  + (-4876.0f) * s1  + 1.3415999999999998E+04f *
        s2 + (-10484.0f) * s3  + (-774.0f) * s4  + (-1.3620000000000002E+04f) *
        s5 + 10481.0f * s6 + 20425.0f * s7  + (-17815.0f) *
        s8 + 5.2121094496644555E+03f;
}
