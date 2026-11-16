
/*@
  \flostat::distribution s0, "Normal", 2.3, 1.15;
	\flostat::distribution s1, "Normal", 5.0, 2.5;
	\flostat::distribution s2, "Normal", 5.0, 2.5;
  \flostat::prob_ensures 0.99,
	\flteq(\result, (-3.795323e2) * s0 + (-5.443608e2) * s1 + 92.729 *
		s2 + 4.5165916241610748e3, 1.76E-03/4.0);
*/
float main(float s0, float s1, float s2) {
    // require(0 <= s0 && s0 <= 4.6 &&
			// 			 0 <= s1 && s1 <= 10 &&
			// 			 0 <= s2 && s2 <= 10)
    return (-3.795323e2) * s0 + (-5.443608e2) * s1 + 92.729 *
			s2 + 4.5165916241610748e3;
}
