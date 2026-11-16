import daisy.lang._
import Real._
object sine {
  def sine(x: Real): Real = {
    require(0.0 < x && x < 10.0)
    ((((1.0 + (0.5*x)) - ((0.125*x)*x)) + (((0.0625*x)*x)*x)) - ((((0.0390625*x)*x)*x)*x))
  }
}
