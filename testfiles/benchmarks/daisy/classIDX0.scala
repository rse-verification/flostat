import daisy.lang._
import Real._


object ClassIDX0 {
  def classIDX0(atts0: Real, atts1: Real, atts2: Real, atts3: Real): Real = {
    require(3.0 <= atts0 && atts0 <= 9.0 &&
            1.5 <= atts1 && atts1 <= 5.0 &&
            -2 <= atts2 && atts2 <= 10 &&
            -1.0 <= atts3 && atts3 <= 3.5)
    ((-0.85073072819636686f) * atts0 + (-0.98664016916368502f) * atts1 +
              (1.3809517485817782f) * atts2 + (1.8653450939330991f) * atts3) -
              ((0.18424469636214999f) * atts0 + (0.45123431334216657f) *
                atts1 + (-0.80794264540764449f) * atts2
                + (-0.45071126534400952f) * atts3)
  }
}
