
import daisy.lang._
import Real._

object Trid4 {
  def trid4(x1: Real, x2: Real, x3: Real, x4: Real, x5: Real): Real = {
    require(-100 <= x1 && x1 <= 100 && -100 <= x2 && x2 <= 100 &&
            -100 <= x3 && x3 <= 100 && -100 <= x4 && x4 <= 100 && -100 <= x5 && x5 <= 100)
    ((((((((((x1 - 1) * (x1 - 1)) + (x2 * x1)) - ((x2 - 1) * (x2 - 1))) + (x3 * x2)) - ((x3 - 1) * (x3 - 1))) + (x4 * x3)) - ((x4 - 1) * (x4 - 1))) + (x5 * x4)) - ((x5 - 1) * (x5 - 1)))
  }
}
