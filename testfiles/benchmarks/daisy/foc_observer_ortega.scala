import scala.annotation.strictfp
import daisy.lang._
import Real._

@strictfp
object FocObserverOrtega {
  def focObserverUpdate(
      vAlpha: Real,
      vBeta: Real,
      iAlpha: Real,
      iBeta: Real,
      fluxAngle: Real
  ): Real = {
    require(
      (-400.0 <= vAlpha) && (vAlpha <= 400.0) &&
      (-400.0 <= vBeta) && (vBeta <= 400.0) &&
      (-500.0 <= iAlpha) && (iAlpha <= 500.0) &&
      (-500.0 <= iBeta) && (iBeta <= 500.0) &&
      (-3.14159265 <= fluxAngle) && (fluxAngle <= 3.14159265)
    )

    val resistance: Real = 0.05
    val inductance: Real = 0.0001
    val fluxLinkage: Real = 0.01
    val gammaHalf: Real = 3.0
    val dt: Real = 0.00005

    val x1: Real = (fluxLinkage * cos(fluxAngle)) + (inductance * iAlpha)
    val x2: Real = (fluxLinkage * sin(fluxAngle)) + (inductance * iBeta)
    val inductiveIAlpha: Real = inductance * iAlpha
    val inductiveIBeta: Real = inductance * iBeta
    val resistiveIAlpha: Real = resistance * iAlpha
    val resistiveIBeta: Real = resistance * iBeta

    // FOC_OBSERVER_ORTEGA_ORIGINAL update.
    val fluxError: Real =
      (fluxLinkage * fluxLinkage) -
      (((x1 - inductiveIAlpha) * (x1 - inductiveIAlpha)) +
       ((x2 - inductiveIBeta) * (x2 - inductiveIBeta)))
    val clampedError: Real = if (fluxError > 0.0) 0.0 else fluxError
    val x1Dot: Real =
      vAlpha - resistiveIAlpha +
      (gammaHalf * (x1 - inductiveIAlpha) * clampedError)
    val x2Dot: Real =
      vBeta - resistiveIBeta +
      (gammaHalf * (x2 - inductiveIBeta) * clampedError)
    val integratedX1: Real = x1 + (x1Dot * dt)
    val integratedX2: Real = x2 + (x2Dot * dt)

    // Shared VESC protection expands flux states that fall below lambda/2.
    val fluxMagnitudeSquared: Real =
      (integratedX1 * integratedX1) + (integratedX2 * integratedX2)
    val fluxMagnitude: Real = if (fluxMagnitudeSquared >= 0.0) {
      sqrt(fluxMagnitudeSquared)
    } else {
      0.0
    }
    val magnitudeScale: Real =
      if (fluxMagnitude < (fluxLinkage * 0.5)) 1.1 else 1.0
    val updatedX1: Real = integratedX1 * magnitudeScale
    val updatedX2: Real = integratedX2 * magnitudeScale

    // VESC's fast atan2 approximation, applied after inductance correction.
    val angleX: Real = updatedX1 - inductiveIAlpha
    val angleY: Real = updatedX2 - inductiveIBeta
    val absX: Real = if (angleX < 0.0) -angleX else angleX
    val absY: Real =
      (if (angleY < 0.0) -angleY else angleY) + 1.0e-20
    val denominator: Real = absX + absY
    // Daisy needs a positive lower bound for interval division. This floor
    // changes the phase approximation when the denominator is below 0.001.
    val safeDenominator: Real =
      if (denominator > 0.001) denominator else 0.001
    val ratio: Real = (absX - absY) / safeDenominator
    val ratioSquared: Real = ratio * ratio
    val polynomial: Real = ((0.1963 * ratioSquared) - 0.9817) * ratio
    val xSign: Real = if (angleX >= 0.0) 1.0 else -1.0
    val ySign: Real = if (angleY < 0.0) -1.0 else 1.0
    val unsignedAngle: Real =
      (3.14159265358979323846 / 2.0) +
      (xSign * (polynomial - (3.14159265358979323846 / 4.0)))

    ySign * unsignedAngle
  }
}
