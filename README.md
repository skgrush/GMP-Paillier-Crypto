# GMP-Paillier-Crypto
> C implementation of the Paillier homomorphic cryptosystem using the
  GNU multiple precision arithmetic library.

## Getting Started

### Prerequisites

A C compiler is required. Only `gcc` version ≥6.3 is tested.

The GNU multiple precision library (`GMP`) and its dev(el) package are required.
They can generally be installed with the following (or platform equivalent):

```
#  apt install libgmp-dev
```

### Building

The build process under gcc is simply

```
$  gcc  src/*.c  -o gpc  -lgmp
```

This will — if successful — generate the binary executable `gpc`.

## Execution

Running `./gpc` with no arguments will
initiate the interactive script specified in the initial project specification.

You will need:
  * 1\. **input** file containing **_p_, _q_, and _g_**.  _p_ and _q_ should
    be "large prime numbers" such that `gcd(p*q, (p-1)(q-1)) = 1`, and _g_
    should be in the same multiplicative group under modulo _n²_.
    Numbers should whitespace-delimited.
  * 3\. **input** file containing **_u⃗_**, a list of whitespace-delimited
    integers.
  * 5\. **input** file containing **_v⃗_**, same as 3.

## Authors

* **Shawn McCormick**
* **Samuel K. Grush**

[//]: # (&#x20d7; for vector symbol)
