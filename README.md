# FloStat

FloStat is a Frama-C plugin for statistically checking floating-point
rounding error. It compares executions of a C function using native
floating-point arithmetic with executions of a generated MPFR version.

## Build

Build with Dune from the plugin source directory:

```sh
cd src
dune build
```

FloStat requires Frama-C and the libraries listed in `src/dune` to be
installed in the active OCaml/Dune environment.

## Run

Run Frama-C from this directory, selecting the function whose ACSL contract
FloStat should check:

```sh
dune exec --root src -- frama-c \
  -main calculate -flostat -fs-execs 1000 \
  testfiles/nested_structs.c
```

`-main` must name an existing function with a FloStat contract. If
`-fs-out-dir DIR` is omitted, generated C files, the executable, samples, and
results are written to a new directory based on the input filename and time.
Useful options include:

- `-fs-execs N`: number of sampled executions (default: `10`).
- `-fs-prec N`: MPFR precision in bits (default: `256`).
- `-fs-out-dir DIR`: output directory.
- `-fs-sample-file FILE`: use a CSV file of input samples instead of drawing
  random samples. Columns must correspond to the contract's distributions.
- `-fs-only-sample`: generate samples without running the comparison.
- `-fs-more-stats`: also print minimum, maximum, and mean absolute measured
  differences; the default statistics output remains unchanged.

## Contracts

Attach uniform input distributions and one probability postcondition to the
selected function. The existing form takes a probability, a confidence level,
and a `\flteq` predicate:

```c
/*@
  \flostat::distribution input, "Uniform", 0.0, 1.0;
  \flostat::prob_ensures 0.99, 0.001,
    \flteq(\result, input + 2.0, 0.000001);
*/
float calculate(float input) {
  return input + 2.0f;
}
```

The probability and confidence arguments must be real constants. A shorter
rounding-error form is also supported; its reported confidence level defaults
to `0.95`:

```c
/*@
  \flostat::distribution input, "Uniform", 0.0, 1.0;
  \flostat::prob_ensures
    0.99,
    \round_error(\result) <= 0.00034;
*/
float calculate(float input) {
  return input * input;
}
```

`\round_error(x)` measures the absolute difference between the native
floating-point evaluation of `x` and its MPFR evaluation, equivalent to
`\abs(x - \real(x))`. The predicate currently supports `\round_error(x) <=
tolerance`. Both forms compare the requested probability of staying within
the tolerance. Distributions support `"Uniform"` with real-constant lower and
upper bounds, and `"Normal"` with a real-constant mean and standard deviation.

Use `\flostat::equation target, expression;` to define an input from other
sampled inputs. Equation expressions are evaluated in MPFR before either
program execution; each result is rounded once to `float`, then that same
rounded value is supplied to both the native and MPFR executions. This lets
you generate correlated inputs without including equation-evaluation rounding
in the measured function difference:

```c
/*@
  \flostat::distribution input.angle, "Uniform", -3.14159, 3.14159;
  \flostat::equation input.x, 0.01 * \cos(input.angle);
*/
```

Equation targets must be floating-point entry-point arguments and should not
also have distributions. The supported right-hand-side forms are floating
constants, entry-point argument fields, unary negation, `+`, `-`, `*`, `/`,
and one-argument `\sin(...)` / `\cos(...)`. Equations execute in declaration
order, so a later equation can use a target assigned by an earlier equation.
Only the distribution targets appear as columns in `samples.csv`; equation
targets are calculated after those columns have been read.

To sample a fresh value for every element of a fixed-size array, use an
inclusive ACSL range in the distribution target. Each expanded element becomes
its own sample column, and the full row is used for one execution:

```c
typedef struct {
  float values[100];
} inputs_t;

/*@
  \flostat::distribution inputs.values[0..99], "Uniform", 0.0, 1.0;
  \flostat::prob_ensures 0.99, 0.001,
    \flteq(\result, 0.0, 100.0);
*/
float sum_inputs(inputs_t inputs) {
  float sum = 0.0f;
  for (int i = 0; i < 100; i++) {
    sum += inputs.values[i];
  }
  return sum;
}
```

Range endpoints must be integer constants, and the target must be an lvalue
that FloStat can convert to a C array element. Bounds are inclusive, so
`[0..99]` expands to 100 independently sampled elements. MPFR arrays embedded
in structs are initialized element-by-element during comparison.

## Test files

The current VESC Ortega observer examples live in
`testfiles/ortega_programs/`. This directory contains the standalone one-step
Ortega observer programs used for the paper experiments:

- `testfiles/ortega_programs/flostat/foc_ortega/` contains the FloStat
  `ortega.c` variants.
- `testfiles/ortega_programs/flostat/foc_ortega_fast/` contains the FloStat
  `ortegaFast.c` variants.
- `testfiles/ortega_programs/daisy/foc_observer_ortega.scala` contains the
  matching Daisy version.

The examples sample independent alpha/beta voltage and current inputs plus a
flux angle, compute the initial flux state immediately before the observer
update, and inline the VESC Ortega-mode update and common post-update
safeguards in a self-contained file. See
`testfiles/ortega_programs/README.md` for the detailed input bounds and
assumptions.

The benchmark inputs used by the benchmark suite are under
`testfiles/benchmarks/`. This directory contains the benchmark programs for
FloStat and the other comparison tools.

## Supported C syntax and limitations

FloStat operates on the Frama-C C AST; source must first be accepted by the
installed Frama-C parser. The MPFR translator supports a subset of C, not every
valid C program:

- Floating-point arithmetic currently covers `+`, `-`, `*`, `/`, unary
  negation, and floating-point comparisons. Other operators or expression
  forms may be rejected or translated incorrectly.
- Implicit casts are not fully supported. FloStat prints a warning about this
  when it starts; use explicit, simple casts where possible.
- Transcendental-function translation is limited to the functions mapped in
  `src/mpfr_utils.ml`. Other library calls are not automatically given
  MPFR-equivalent behavior.
- Structs and nested structs containing floating-point fields are supported
  for the covered operations. Pointer-to-struct fields are supported in
  common cases, but arbitrary pointer aliasing, pointer arithmetic, and
  indirect memory patterns are not generally supported.
- Struct copies containing arrays require compatible, fixed-size arrays.
  Variable-length or otherwise non-constant array sizes are unsupported.
- A function contract must have a single behavior. Multiple behaviors,
  multiple probability clauses, predicates other than `\flteq`, and
  distribution kinds other than `"Uniform"` are unsupported.
- Contract terms are limited to the forms handled by the translator, such as
  constants, variables, `\result`, supported binary arithmetic, and
  `\old(...)`. Arbitrary field expressions and general ACSL logic are not
  supported.

Unsupported cases may stop with a diagnostic during translation or C
compilation. A successful run only checks the generated samples; it does not
establish correctness for inputs outside the sampled distribution.
