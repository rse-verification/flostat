
import daisy.lang._
import Real._


object Bsplines0 {
  // f32
  def bspline0(u: Real): Real = {
    require(0 <= u && u <= 1)
    (1 - u) * (1 - u) * (1 - u) / 6.0
  }
}
