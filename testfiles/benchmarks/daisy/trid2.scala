
import daisy.lang._
import Real._

object Trid2 {
  def trid2(x1: Real, x2: Real, x3: Real): Real = {
    require(-100 <= x1 && x1 <= 100 && -100 <= x2 && x2 <= 100 && -100 <= x3 && x3 <= 100)
    (((((x1 - 1) * (x1 - 1)) + (x2 * x1)) - ((x2 - 1) * (x2 - 1))) + (x3 * x2)) - ((x3 - 1) * (x3 - 1))
  }
}
