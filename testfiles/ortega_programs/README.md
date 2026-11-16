# VESC Ortega observer examples

This directory contains the current standalone one-step VESC Ortega observer
programs used for the paper experiments.

| Observer variant | FloStat inputs | Daisy input |
| --- | --- | --- |
| Ortega, VESC observer implementation | `flostat/foc_ortega/` | `daisy/foc_observer_ortega.scala` |
| Ortega with the fast phase approximation | `flostat/foc_ortega_fast/` | n/a |

The examples sample independent alpha/beta voltage and current inputs plus a
uniform electrical flux angle. They compute the initial flux components
immediately before the observer call, from the sampled angle and sampled
currents. Motor parameters and the initial flux-linkage estimate remain fixed.
Each FloStat C example is self-contained: it includes the Ortega-mode update
and the common VESC post-update safeguards directly in that file.

The benchmark inputs used by the benchmark suite live under `../benchmarks/`.
