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
    val x5 = x4 + time * (sigma * (y4 - x4))
    val y5 = y4 + time * (x4 * (rho - z4) - y4)
    val z5 = z4 + time * (x4 * y4 - beta * z4)
    val x6 = x5 + time * (sigma * (y5 - x5))
    val y6 = y5 + time * (x5 * (rho - z5) - y5)
    val z6 = z5 + time * (x5 * y5 - beta * z5)
    val x7 = x6 + time * (sigma * (y6 - x6))
    val y7 = y6 + time * (x6 * (rho - z6) - y6)
    val z7 = z6 + time * (x6 * y6 - beta * z6)
    val x8 = x7 + time * (sigma * (y7 - x7))
    val y8 = y7 + time * (x7 * (rho - z7) - y7)
    val z8 = z7 + time * (x7 * y7 - beta * z7)
    val x9 = x8 + time * (sigma * (y8 - x8))
    val y9 = y8 + time * (x8 * (rho - z8) - y8)
    val z9 = z8 + time * (x8 * y8 - beta * z8)
    val x10 = x9 + time * (sigma * (y9 - x9))
    val y10 = y9 + time * (x9 * (rho - z9) - y9)
    val z10 = z9 + time * (x9 * y9 - beta * z9)
    y10
  }
}
