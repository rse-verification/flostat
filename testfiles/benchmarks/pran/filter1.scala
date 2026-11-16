
import daisy.lang._
import Real._

object Filter1 {
  def filter1(x0: Real): Real = {
    require(-2 <= x0 && x0 <= 2)
    0.7 * x0
  }
}
