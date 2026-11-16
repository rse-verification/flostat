import daisy.lang._
import Real._

/*
  \flostat::distribution x, "Uniform", 0.0, 1.0
  \flostat::distribution y, "Uniform", 0.0, 1.0
  \flostat::distribution z, "Uniform", 0.0, 1.0
  \flostat::prob_ensures 0.99, \flteq(\result, 1.0, 5.0)
*/
object TestObject {
  def lorenz(x : Real, y : Real, z : Real) : Real = {
    require (0.0 <= x && x <= 1.0 &&
            0.0 <= y && y <= 1.0 &&
            0.0 <= z && z <= 1.0)
    val sigma: Real = 10.0
    val rho: Real = 28.0
    val beta: Real = (8.0 / 3.0)
    val time: Real = 0.01
    val x1 = x + time * (sigma * (y - x))
    val y1 = y + time * (x * (rho - z) - y)
    val z1 = z + time * (x * y - beta * z)
    val x2 = x1 + time * (sigma * (y1 - x1))
    val y2 = y1 + time * (x1 * (rho - z1) - y1)
    val z2 = z1 + time * (x1 * y1 - beta * z1)
    val x3 = x2 + time * (sigma * (y2 - x2))
    val y3 = y2 + time * (x2 * (rho - z2) - y2)
    val z3 = z2 + time * (x2 * y2 - beta * z2)
    val x4 = x3 + time * (sigma * (y3 - x3))
    val y4 = y3 + time * (x3 * (rho - z3) - y3)
    val z4 = z3 + time * (x3 * y3 - beta * z3)
    y4
  }
}
