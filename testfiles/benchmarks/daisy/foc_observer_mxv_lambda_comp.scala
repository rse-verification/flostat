import scala.annotation.strictfp
import daisy.lang._
import Real._

@strictfp
object FocObserverMxvLambdaComp {
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

    val initialX1: Real =
      (fluxLinkage * cos(fluxAngle)) + (inductance * iAlpha)
    val initialX2: Real =
      (fluxLinkage * sin(fluxAngle)) + (inductance * iBeta)
    val inductiveIAlpha: Real = inductance * iAlpha
    val inductiveIBeta: Real = inductance * iBeta
    val resistiveIAlpha: Real = resistance * iAlpha
    val resistiveIBeta: Real = resistance * iBeta
    val initialLambdaEstimate: Real = fluxLinkage

    // MXV update integrates voltage minus resistive drop.
    val integratedX1: Real =
      initialX1 + ((vAlpha - resistiveIAlpha) * dt)
    val integratedX2: Real =
      initialX2 + ((vBeta - resistiveIBeta) * dt)

    // MXV lambda compensation adapts lambda_est from the flux-magnitude error.
    val lambdaError: Real =
      (initialLambdaEstimate * initialLambdaEstimate) -
      (((integratedX1 - inductiveIAlpha) *
        (integratedX1 - inductiveIAlpha)) +
       ((integratedX2 - inductiveIBeta) *
        (integratedX2 - inductiveIBeta)))
    val estimatedLambdaUnclamped: Real =
      initialLambdaEstimate +
      (((0.2 * gammaHalf) * initialLambdaEstimate) *
       (-lambdaError) * dt)
    val estimatedLambdaLower: Real = fluxLinkage * 0.3
    val estimatedLambdaUpper: Real = fluxLinkage * 2.5
    val estimatedLambdaLowerClamped: Real =
      if (estimatedLambdaUnclamped < estimatedLambdaLower) {
        estimatedLambdaLower
      } else {
        estimatedLambdaUnclamped
      }
    val estimatedLambda: Real =
      if (estimatedLambdaLowerClamped > estimatedLambdaUpper) {
        estimatedLambdaUpper
      } else {
        estimatedLambdaLowerClamped
      }

    // Limit the corrected alpha/beta flux vector to estimatedLambda.
    val correctedMagnitudeSquared: Real =
      ((integratedX1 - inductiveIAlpha) *
       (integratedX1 - inductiveIAlpha)) +
      ((integratedX2 - inductiveIBeta) *
       (integratedX2 - inductiveIBeta))
    val correctedMagnitude: Real = if (correctedMagnitudeSquared >= 0.0) {
      sqrt(correctedMagnitudeSquared)
    } else {
      0.0
    }
    // The floor is inactive when normalization is selected; it keeps the
    // division defined for Daisy's interval analysis.
    val safeCorrectedMagnitude: Real =
      if (correctedMagnitude > estimatedLambda) {
        if (correctedMagnitude > 0.003) correctedMagnitude else 0.003
      } else {
        1.0
      }
    val normalizedX1: Real =
      (integratedX1 / safeCorrectedMagnitude) * estimatedLambda
    val normalizedX2: Real =
      (integratedX2 / safeCorrectedMagnitude) * estimatedLambda
    val limitedX1: Real =
      if (correctedMagnitude > estimatedLambda) normalizedX1 else integratedX1
    val limitedX2: Real =
      if (correctedMagnitude > estimatedLambda) normalizedX2 else integratedX2

    // Shared VESC protection expands flux states that fall below lambda/2.
    val finalMagnitudeSquared: Real =
      (limitedX1 * limitedX1) + (limitedX2 * limitedX2)
    val finalMagnitude: Real = if (finalMagnitudeSquared >= 0.0) {
      sqrt(finalMagnitudeSquared)
    } else {
      0.0
    }
    val lowMagnitudeScale: Real =
      if (finalMagnitude < (fluxLinkage * 0.5)) 1.1 else 1.0
    val updatedX1: Real = limitedX1 * lowMagnitudeScale
    val updatedX2: Real = limitedX2 * lowMagnitudeScale

    // VESC's fast atan2 approximation, applied after inductance correction.
    val angleX: Real = updatedX1 - inductiveIAlpha
    val angleY: Real = updatedX2 - inductiveIBeta
    val absX: Real = if (angleX < 0.0) -angleX else angleX
    val absY: Real =
      (if (angleY < 0.0) -angleY else angleY) + 1.0e-20
    val angleDenominator: Real = absX + absY
    // Daisy needs a positive lower bound for interval division. This floor
    // changes the phase approximation when the denominator is below 0.005.
    val safeAngleDenominator: Real =
      if (angleDenominator > 0.005) angleDenominator else 0.005
    val ratio: Real = (absX - absY) / safeAngleDenominator
    val ySign: Real = if (angleY < 0.0) -1.0 else 1.0
    val ratioSquared: Real = ratio * ratio
    val polynomial: Real = ((0.1963 * ratioSquared) - 0.9817) * ratio
    val xSign: Real = if (angleX >= 0.0) 1.0 else -1.0
    val unsignedAngle: Real =
      (3.14159265358979323846 / 2.0) +
      (xSign * (polynomial - (3.14159265358979323846 / 4.0)))

    ySign * unsignedAngle
  }
}
