
/*@
  \flostat::distribution s0, "Uniform", -3.0, 5.0;
	\flostat::distribution s1, "Uniform", -3.0, 5.0;
	\flostat::distribution s2, "Uniform", -3.0, 5.0;
  \flostat::distribution s3, "Uniform", -6.0, 11.0;
  \flostat::distribution s4, "Uniform", -6.0, 11.0;
  \flostat::distribution s5, "Uniform", -6.0, 11.0;
  \flostat::distribution s6, "Uniform", -6.0, 11.0;
  \flostat::prob_ensures 0.99,
	\flteq(\result, (-3.7377847506227999E+02) * s0  + (7.0862205220929002E+02) * s1  +
  (-3.7886044910192999E+02) * s2  + (-4.5413076942315001E+02) * s3  +
   (-8.7386976105502004E+02) * (1.0) * s4  + (3.5911290954487999E+03) *
   (1.0) * s5  + (-2.2921226288533999E+03) * (1.0) * s6  +
   2.9021426298877441E+02, 1.75E-02/2.0);
*/
float main(float s0, float s1, float s2, float s3, float s4, float s5, float s6) {
    // require(-3 <= s0 && s0 <= 5 &&
    //         -3 <= s1 && s1 <= 5 &&
    //         -3 <= s2 && s2 <= 5 &&
    //         -6 <= s3 && s3 <= 11 &&
    //         -6 <= s4 && s4 <= 11 &&
    //         -6 <= s5 && s5 <= 11 &&
    //         -6 <= s6 && s6 <= 11)
    return (-3.7377847506227999E+02f) * s0  + (7.0862205220929002E+02f) * s1  +
    (-3.7886044910192999E+02f) * s2  + (-4.5413076942315001E+02f) * s3  +
     (-8.7386976105502004E+02f) * (1.0f) * s4  + (3.5911290954487999E+03f) *
     (1.0f) * s5  + (-2.2921226288533999E+03f) * (1.0f) * s6  +
     2.9021426298877441E+02f;
}
