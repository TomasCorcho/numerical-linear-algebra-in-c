# numerical-linear-algebra-in-c
Numerical linear algebra methods implemented in C, including Gaussian elimination, least squares and finite differences.

# Numerical Linear Algebra in C

This repository contains a collection of numerical methods implemented in **C** as part of the *Numerical Methods I* course at the University of Barcelona.

The project focuses on the implementation and application of basic algorithms from numerical linear algebra. The main methods were implemented from scratch and later used to solve linear systems, least-squares problems, and a boundary-value problem for an ordinary differential equation.

## Contents

The repository includes implementations of:

* Back substitution for upper-triangular linear systems
* Matrix multiplication
* Gaussian elimination
* Partial pivoting
* Detection of numerical singularity using a tolerance
* Solution of general linear systems
* Least-squares approximation using the normal equations
* Linear and quadratic data fitting
* Finite-difference discretization of boundary-value problems

## Project Structure

```text
.
├── assignment/
│   └── prac-AL.pdf
│
├── report/
│   ├── CorchoTomas-Comentari1.pdf
│   ├── CorchoTomas-Comentari2.pdf
│   └── CorchoTomas-Comentari3.pdf
│
├── src/
│   ├── func1.c
│   ├── func2.c
│   ├── funcions-temaAL.c
│   ├── main-trian.c
│   ├── resol-constr.c
│   ├── resol-fitxer.c
│   ├── sobredeter.c
│   └── valorsFrontera.c
│
└── README.md
```

## Numerical Methods

### 1. Upper-Triangular Systems

The function

```c
void triangSup(double **matU, double *t, double *sol, int n);
```

solves a non-singular upper-triangular system

$$
Ux = t
$$

using back substitution.

The implementation computes the solution starting from the last equation and proceeding upwards.

The method has quadratic computational complexity:

$O(n^2)$.

The program `main-trian.c` was used to test the implementation for matrices of different dimensions and to measure execution times.

The experiments included systems with dimensions up to (n=20000), allowing the observed computational cost to be compared with the expected theoretical behavior.

### 2. Matrix Multiplication

The function

```c
double **prodMat(
    double **a,
    int filA,
    int colA,
    double **b,
    int colB
);
```

computes the product of two matrices.

As a simple application, the implementation was used to verify numerically that the product of two lower-triangular matrices is also lower triangular.

### 3. Gaussian Elimination

Gaussian elimination with pivoting is implemented through the functions

```c
int pivot(double **matA, int pas, int n);
```

and

```c
int gauss(double **a, double *b, double tol, int n);
```

The `pivot` function searches for the element with maximum absolute value in the current column.

The `gauss` function transforms the system

[
Ax=b
]

into an equivalent upper-triangular system. The resulting system can then be solved using back substitution.

If a pivot is smaller than the specified tolerance, the matrix is treated as numerically singular.

## Applications

### Solving Linear Systems from Files

`resol-fitxer.c` reads a linear system from an input file, solves it using Gaussian elimination and back substitution, and writes the resulting solution to an output file.

The input contains:

1. the system dimension,
2. the coefficients of the augmented matrix,
3. the numerical tolerance.

### Ill-Conditioned Linear Systems

`resol-constr.c` constructs systems whose matrix has entries

[
a_{ij}=\frac{1}{i+j-1}.
]

These matrices become increasingly ill-conditioned as their dimension grows.

The program was used to study how Gaussian elimination behaves for different matrix sizes and numerical tolerances.

For sufficiently large dimensions, the system can be classified as numerically singular for the chosen tolerance.

### Least-Squares Approximation

`sobredeter.c` solves overdetermined systems

[
Ax \approx c
]

using the normal equations

[
A^TAx=A^Tc.
]

This was applied to experimental data using both linear and quadratic models.

For the linear approximation

$$
y=c_1+c_2x,
$$

the computed coefficients were approximately

$$
c_1=0.0685714,
\qquad
c_2=1.1257143.
$$

For the quadratic approximation

$$
y=c_0+c_1x+c_2x^2,
$$

the computed coefficients were approximately

$$
c_0=-0.0057143,
$$

$$
c_1=1.3238095,
$$

$$
c_2=-0.0990476.
$$

## Boundary-Value Problems

As an optional extension of the assignment, `valorsFrontera.c` solves second-order boundary-value problems of the form

$$
y''(x)=p(x)y'(x)+q(x)y(x)+r(x),
$$

subject to

$$
y(a)=\alpha,
\qquad
y(b)=\beta.
$$

The interval is divided into a uniform grid and the derivatives are approximated using centered finite differences:

$$
y'(x_i)\approx
\frac{y_{i+1}-y_{i-1}}{2h},
$$

and

$$
y''(x_i)\approx
\frac{y_{i+1}-2y_i+y_{i-1}}{h^2}.
$$

This produces a tridiagonal linear system that is solved using the Gaussian-elimination routines implemented earlier in the project.

Two example differential equations were studied:

### Example 1

$$
y''=4(y-x),
$$

with

$$
0\leq x\leq1,
\qquad
y(0)=0,
\qquad
y(1)=2.
$$

### Example 2

$$
y''=y'+2y+\cos x,
$$

with

$$
0\leq x\leq\frac{\pi}{2},
\qquad
y(0)=-0.3,
\qquad
y\left(\frac{\pi}{2}\right)=-0.1.
$$

The files `func1.c` and `func2.c` define the corresponding functions (p(x)), (q(x)), and (r(x)).

The numerical solutions were exported to `sortida.dat` and visualized using **gnuplot**.

## Compilation

The programs were developed and tested in a Linux environment using GCC.

For example, the triangular-system program can be compiled with:

```bash
gcc src/main-trian.c src/funcions-temaAL.c -o main-trian -lm
```

and executed with:

```bash
./main-trian
```

The Gaussian-elimination example can be compiled with:

```bash
gcc src/resol-constr.c src/funcions-temaAL.c -o resol-constr -lm
```

The least-squares program can be compiled with:

```bash
gcc src/sobredeter.c src/funcions-temaAL.c -o sobredeter -lm
```

The first boundary-value example can be compiled with:

```bash
gcc src/valorsFrontera.c src/funcions-temaAL.c src/func1.c -o boundary-example-1 -lm
```

and the second with:

```bash
gcc src/valorsFrontera.c src/funcions-temaAL.c src/func2.c -o boundary-example-2 -lm
```

## Reports

The `report/` directory contains the accompanying analysis of the numerical experiments, including:

* execution-time measurements for back substitution,
* behavior of Gaussian elimination on ill-conditioned systems,
* least-squares approximations,
* numerical solutions of boundary-value problems,
* plots generated with gnuplot.

## Assignment

The original course assignment is included in:

```text
assignment/prac-AL.pdf
```

This provides the original specifications for the algorithms and applications implemented in the project.

## Technologies

* C
* GCC
* Linux
* Gnuplot
* Numerical linear algebra
* Finite-difference methods

## Academic Context

This project was developed as coursework for **Numerical Methods I** at the **University of Barcelona**, during the Spring 2025–2026 semester.

