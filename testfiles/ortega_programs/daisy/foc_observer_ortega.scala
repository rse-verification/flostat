import scala.annotation.strictfp
import daisy.lang._
import Real._

@strictfp
object FocObserverOrtega {
  def foc_observer_ortega(
      v_alpha: Real,
      v_beta: Real,
      i_alpha: Real,
      i_beta: Real,
      flux_angle: Real
  ): Real = {
    require(
      (-40.0 <= v_alpha) && (v_alpha <= 40.0) &&
      (-40.0 <= v_beta) && (v_beta <= 40.0) &&
      (-100.0 <= i_alpha) && (i_alpha <= 100.0) &&
      (-100.0 <= i_beta) && (i_beta <= 100.0) &&
      (-3.14159265 <= flux_angle) && (flux_angle <= 3.14159265)
    )
    val resistance: Real = 0.05
    val Ld_Lq_diff: Real = 0.00001
    val lambda: Real = 0.01
    val gamma: Real = 6.0
    val dt: Real = 0.00005

    // Inlines the C Park-transform helper's id/iq calculations.
    val id: Real = (cos(flux_angle) * i_alpha) + (sin(flux_angle) * i_beta)
    val iq: Real = (cos(flux_angle) * i_beta) - (sin(flux_angle) * i_alpha)
    val L: Real = if (
      (if (id < 0.0) -id else id) > 1.0 ||
      (if (iq < 0.0) -iq else iq) > 1.0
    ) {
      0.0001 - (Ld_Lq_diff / 2.0) +
        (Ld_Lq_diff * (iq * iq) / ((id * id) + (iq * iq)))
    } else {
      0.0001
    }
    val L_ia: Real = L * i_alpha
    val L_ib: Real = L * i_beta
    val R_ia: Real = resistance * i_alpha
    val R_ib: Real = resistance * i_beta
    val gamma_half: Real = gamma * 0.5;

    // Inlines estimate_prev_x, which initializes x1/x2 from the flux angle.
    val x1: Real = (lambda * cos(flux_angle)) + L_ia
    val x2: Real = (lambda * sin(flux_angle)) + L_ib

    val err: Real =
      (lambda * lambda) -
      (((x1 - L_ia) * (x1 - L_ia)) +
       ((x2 - L_ib) * (x2 - L_ib)))
    val clamped_err: Real = if (err > 0.0) 0.0 else err
    val x1_dot: Real =
      v_alpha - R_ia + (gamma_half * (x1 - L_ia) * clamped_err)
    val x2_dot: Real =
      v_beta - R_ib + (gamma_half * (x2 - L_ib) * clamped_err)
    val x1_updated: Real = x1 + (x1_dot * dt)
    val x2_updated: Real = x2 + (x2_dot * dt)

    val flux_magnitude_squared: Real =
      (x1_updated * x1_updated) + (x2_updated * x2_updated)
    val flux_magnitude: Real = if (flux_magnitude_squared >= 0.0) {
      sqrt(flux_magnitude_squared)
    } else {
      0.0
    }
    val fix_new_x1: Real = if (flux_magnitude < (lambda * 0.5)) {
      x1_updated * 1.1
    } else {
      x1_updated
    }
    val fix_new_x2: Real = if (flux_magnitude < (lambda * 0.5)) {
      x2_updated * 1.1
    } else {
      x2_updated
    }

    val y: Real = fix_new_x2 - L_ib
    val x: Real = fix_new_x1 - L_ia
    val abs_y: Real = (if (y < 0.0) -y else y) + 0.1
    val ratio: Real = if (x >= 0.0) {
      (x - abs_y) / (x + abs_y)
    } else {
      (x + abs_y) / (abs_y - x)
    }
    val ratio_squared: Real = ratio * ratio
    val angle: Real = if (x >= 0.0) {
      ((0.1963 * ratio_squared) - 0.9817) * ratio +
        (3.14159265358979323846 / 4.0)
    } else {
      ((0.1963 * ratio_squared) - 0.9817) * ratio +
        (3.0 * 3.14159265358979323846 / 4.0)
    }

    if (y < 0.0) -angle else angle
  }
}
