
import daisy.lang._
import Real._

object Filter4 {
  def filter4(x0: Real, x1 : Real, x2 : Real, x3 : Real): Real = {
    require(-2 <= x0 && x0 <= 2 && -2 <= x1 && x1 <= 2 &&
      -2 <= x2 && x2 <= 2 && -2 <= x2 && x2 <= 2 && -2 <= x3 && x3 <= 2)

    val t1 : Real = (0.7f) * x1 - (1.3f) * x0 + (1.4f) * ((0.7f) * x0)
    (0.7f) * x3 - (1.3f) * x2 + (1.1f) * x1 + (1.4f) *
      ((0.7f) * x2 - (1.3f) * x1 + (1.1f) * x0 + (1.4f) * (t1) - (0.7f) *
      ((0.7f) * x0)) - (0.7f) * (t1)
  }
}
