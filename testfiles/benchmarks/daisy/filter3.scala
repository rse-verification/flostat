
import daisy.lang._
import Real._


object Filter3 {
  def filter3(x0: Real, x1 : Real, x2 : Real): Real = {
    require(-2 <= x0 && x0 <= 2 && -2 <= x1 && x1 <= 2 && -2 <= x2 && x2 <= 2)

    val t1 : Real = ((0.7f) * x0)
    (0.7f) * x2 - (1.3f) * x1 + (1.1f) * x0 + (1.4f) * ((0.7f) * x1 -
      (1.3f) * x0 + (1.4f) * t1) - (0.7f) * t1
  }
}
