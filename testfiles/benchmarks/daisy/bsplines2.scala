
import daisy.lang._
import Real._


object Bsplines2 {

  // f32
  def bspline2(u: Real): Real = {
    require(0 <= u && u <= 1)
    (-3 * u*u*u  + 3*u*u + 3*u + 1) / 6.0
  } 

}
