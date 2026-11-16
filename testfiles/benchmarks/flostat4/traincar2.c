
/*@
  \flostat::distribution s0, "Uniform", -2.0, 9.0;
	\flostat::distribution s1, "Uniform", -2.0, 9.0;
	\flostat::distribution s2, "Uniform", 0.0, 10.0;
  \flostat::distribution s3, "Uniform", 0.0, 10.0;
  \flostat::distribution s4, "Uniform", 0.0, 10.0;
  \flostat::prob_ensures 0.99,
	\flteq(\result, (-2.9829300077345002E+00) * s0 + 2.8399180104656203E+01 * s1 + (-1.5201325206209998E+02) * s2 +
   3.5623840930436779E+02 * s3 + (-2.0636383424191501E+02) * s4 + 2.1660394157545902E+01,
   1.04E-3/4.0);
*/
float main(float s0, float s1, float s2, float s3, float s4) {
   // require(-2 <= s0 && s0 <= 9 &&
   //         -2 <= s1 && s1 <= 9 &&
   //          0 <= s2 && s2 <= 10 &&
   //          0 <= s3 && s3 <= 10 &&
   //          0 <= s4 && s4 <= 10)
   return (-2.9829300077345002E+00f) * s0 + 2.8399180104656203E+01f * s1 +
          (-1.5201325206209998E+02f) * s2 + 3.5623840930436779E+02f *
          s3 + (-2.0636383424191501E+02f) * s4 + 2.1660394157545902E+01f;
}
