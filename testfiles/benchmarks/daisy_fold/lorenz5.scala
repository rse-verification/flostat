import daisy.lang._
import Real._
import daisy.lang.Vector._

object lorentz {

	def lorentz(m:Matrix): Vector = {
require(m >= 1.0 && m <= 2.0 && m.size(5,3)
	)
        val init: Vector = m.row(0)
        val sigma: Real = 10.0
        val rho: Real = 28.0
        val beta: Real = (8.0 / 3.0)
        val time: Real = 0.01
        m.fold(init)((acc, v) => {
            val x:Real = acc.at(0)
            val y:Real = acc.at(1)
            val z:Real = acc.at(2)
            val tmpx:Real = x + sigma*(y - x)*time
            val tmpy:Real = y + (rho*x - y - x*z)*time
            val tmpz:Real = z + (x*y - beta*z)*time
            Vector(List(tmpx,tmpy,tmpz))
        })
    }


}
