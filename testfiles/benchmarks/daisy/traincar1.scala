
import daisy.lang._
import Real._

object Traincar1 {

  // y1, y2: <1, 30, 16>    s1, s2, s3: <1, 30, 25>
  def out1(s0: Real, s1: Real, s2: Real) = {
    require(0 <= s0 && s0 <= 4.6 && 0 <= s1 && s1 <= 10 && 0 <= s2 && s2 <= 10)
    (-3.795323e2) * s0 + (-5.443608e2) * s1 + 92.729 * s2 + 4.5165916241610748e3
  }

}
