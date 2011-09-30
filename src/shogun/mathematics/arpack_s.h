/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2011 Sergey Lisitsyn
 * Copyright (C) 2011 Berlin Institute of Technology and Max-Planck-Society
 */

#ifndef ARPACK_H_
#define ARPACK_H_
#include <shogun/lib/config.h>
#ifdef HAVE_ARPACK
#ifdef HAVE_LAPACK
#include <shogun/mathematics/lapack.h>

/** external ARPACK routine DSAUPD */
extern "C" void ssaupd_(int *ido, char *bmat, int *n, char *which,
			int *nev, float *tol, float *resid, int *ncv,
			float *v, int *ldv, int *iparam, int *ipntr,
			float *workd, float *workl, int *lworkl,
			int *info);

/** external ARPACK routine DSEUPD */
extern "C" void sseupd_(int *rvec, char *All, int *select, float *d,
			float *v, int *ldv, float *sigma, 
			char *bmat, int *n, char *which, int *nev,
			float *tol, float *resid, int *ncv, float *tv,
			int *tldv, int *iparam, int *ipntr, float *workd,
			float *workl, int *lworkl, int *ierr);
namespace shogun
{

/** Wrapper for ARPACK's ssaupd/sseupd routines. These ARPACK 
 * routines are being used to compute specified number of eigenpairs 
 * (e.g. k largest eigenvalues). Underlying routines involve 
 * a variant of Arnoldi process called the IRAM
 * (Implicitly Restarted Arnoldi Method) reduced to IRLM 
 * (Implicitly Restarted Lanczos Method). A strategy specifying 
 * which eigenpairs to compute should be provided as parameter.
 *
 * @param matrix symmetric real matrix of size n*n
 *        (will be modified if mode==3)
 * @param rhs_diag array of size n representing right hand side diagonal matrix,
 *        should be NULL if non-general eigenproblem to be solved
 * @param n size of matrix
 * @param nev number of eigenpairs to compute (nev<=n)
 * @param which eigenvalue finding strategy. Possible values:
 *        - "LM": nev Largest Magnitude eigenvalues
 *        - "SM": nev Smallest Magnitude eigenvalues
 *        - "LA": nev Largest Algebraic eigenvalues
 *                (if mode==3 eigenvalues from the right of shift) 
 *        - "SA": nev Smallest Algebraic eigenvalues
 *                (if mode==3 eigenvalues from the left of shift)
 *        - "BE": half of nev from each end of the spectrum, i.e. nev%2
 *                smallest and nev%2 largest eigenvalues. If nev is odd,
 *                one more largest eigenvalue will be computed
 * @param mode shift-mode of IRLM. Possible values:
 *        - 1: regular mode
 *        - 3: shift-invert mode
 * @param pos true if matrix is positive definite (Cholesky factorization is used in
 *        this case instead of LUP factorization))
 * @param shift shift for shift-invert (3) mode of IRLM. In this mode
 *        routine will compute eigenvalues near provided shift
 * @param tolerance tolerance with eigenvalues should be computed (zero means machine precision)
 * @param eigenvalues array of size nev to hold computed eigenvalues
 * @param eigenvectors array of size nev*n to hold computed eigenvectors
 * @param status on output -1 if computation failed
 */
void arpack_ssxupd(float* matrix, float* rhs_diag, int n, int nev, const char* which,
                   int mode, bool pos, float shift, float tolerance,
                   float* eigenvalues, float* eigenvectors, int& status);
}
#endif /* HAVE_LAPACK */
#endif /* HAVE_ARPACK */
#endif /* ARPACK_H_ */
