
import daisy.lang._
import Real._


object Filter2 {
  def filter2(x0: Real, x1 : Real): Real = {
    require(-2 <= x0 && x0 <= 2 && -2 <= x1 && x1 <= 2)
    (0.7f) * x1 - (1.3f) * x0 + (1.4f) * ((0.7f) * x0)
  }
}
