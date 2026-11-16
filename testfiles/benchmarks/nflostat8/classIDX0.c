/*@
  \flostat::distribution atts0, "Normal", 6.0, 1.25;
  \flostat::distribution atts1, "Normal", 3.25, 0.875;
  \flostat::distribution atts2, "Normal", 4.0, 3.0;
  \flostat::distribution atts3, "Normal", 1.25, 1.125;
  \flostat::prob_ensures 0.99,
  \flteq(\result, ((-0.85073072819636686) * atts0 + (-0.98664016916368502) * atts1 +
            (1.3809517485817782) * atts2 + (1.8653450939330991) * atts3)
            - ((0.18424469636214999) * atts0 + (0.45123431334216657) *
              atts1 + (-0.80794264540764449) * atts2
              + (-0.45071126534400952) * atts3),
          6.93E-06/8.0);
*/
float main(float atts0, float atts1, float atts2, float atts3) {
    // require(3.0 <= atts0 && atts0 <= 9.0 &&
    //         1.5 <= atts1 && atts1 <= 5.0 &&
    //         -2 <= atts2 && atts2 <= 10 &&
    //         -1.0 <= atts3 && atts3 <= 3.5)
    return ((-0.85073072819636686f) * atts0 + (-0.98664016916368502f) * atts1 +
              (1.3809517485817782f) * atts2 + (1.8653450939330991f) * atts3)
              - ((0.18424469636214999f) * atts0 + (0.45123431334216657f) *
                atts1 + (-0.80794264540764449f) * atts2
                + (-0.45071126534400952f) * atts3);
}
