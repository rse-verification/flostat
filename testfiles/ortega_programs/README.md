# Paper observer examples

The `flostat/` and `daisy/` directories each contain three one-update observer
examples:

| Observer variant | FloStat input | Daisy input |
| --- | --- | --- |
| Ortega, VESC observer implementation | `flostat/foc_observer_ortega.c` | `daisy/foc_observer_ortega.scala` |
| MXV with lambda compensation, VESC observer implementation | `flostat/foc_observer_mxv_lambda_comp.c` | `daisy/foc_observer_mxv_lambda_comp.scala` |
| Simplified MXV lambda-compensation presentation example | `flostat/paper_simple_mxv.c` | `daisy/paper_simple_mxv.scala` |

All six inputs use independent box distributions of `[-400, 400]` for each
alpha/beta voltage component and `[-500, 500]` for each alpha/beta current
component. These are experiment bounds, not a motor-specific operating
envelope: sampling components independently permits vector magnitudes up to
`sqrt(2)` times each component limit and does not model coupled operating
conditions.

The initial flux components are computed in C immediately before the observer
call, from a uniformly sampled electrical angle and sampled currents. Motor
parameters and the initial flux-linkage estimate remain fixed. Each FloStat C
example is self-contained: it includes its observer-mode update and the common
VESC post-update safeguards and phase approximation directly in that file.

The FloStat examples retain a 99% probability target and use a `1e-5` absolute
phase-difference threshold. With these wide inputs, occasional estimates near
the angle wrap can differ substantially because the angle approximation is
discontinuous there; the absolute difference can overstate the underlying
angular error for such cases.
