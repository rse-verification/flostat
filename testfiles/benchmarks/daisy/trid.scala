import daisy.lang._
import Real._

object Trid {
  def trid(x1: Real, x2: Real): Real = {
    require(-100 <= x1 && x1 <= 100 && -100 <= x2 && x2 <= 100)
    (((x1 - 1) * (x1 - 1)) + (x2 * x1)) - ((x2 - 1) * (x2 - 1))
  }
}
