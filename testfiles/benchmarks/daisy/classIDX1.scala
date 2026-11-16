
import daisy.lang._
import Real._


object ClassIDX1 {
  def classIDX1(atts0: Real, atts1: Real, atts2: Real, atts3: Real): Real = {

    require(3.0 <= atts0 && atts0 <= 9.0 &&
      1.5 <= atts1 && atts1 <= 5.0 &&
      -2 <= atts2 && atts2 <= 10 &&
      -1.0 <= atts3 && atts3 <= 3.5)
    ((0.18424469636214999) * atts0 + (0.45123431334216657) *
      atts1 + (-0.80794264540764449) * atts2 + (-0.45071126534400952)
     * atts3) - ((0.052100253064028955) * atts0 + (-0.8942341911807864) *
       atts1 + (0.40478255170032273) * atts2 + (-0.93774690197704236) * atts3)
  }
}
