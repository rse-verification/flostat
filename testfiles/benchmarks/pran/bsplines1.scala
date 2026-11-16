
import daisy.lang._
import Real._


object Bsplines1 {

  // f32
  def bspline1(u: Real): Real = {
    require(0 <= u && u <= 1)
    (3 * u*u*u - 6 * u*u + 4) / 6.0
  }

}
