/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Final_model.c
 *
 * Code generated for Simulink model 'Final_model'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Thu Jan  4 23:39:14 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "Final_model.h"
#include "rtwtypes.h"
#include <string.h>
#include <math.h>
#include <stddef.h>
#define NumBitsPerChar                 8U

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
extern real_T rt_hypotd_snf(real_T u0, real_T u1);
static real_T look1_pbinlc(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T prevIndex[], uint32_T maxIndex);
static int32_T div_nde_s32_floor(int32_T numerator, int32_T denominator);

/* Forward declaration for local functions */
static real_T xnrm2_f(int32_T n, const real_T x[12], int32_T ix0);
static void xgemv(int32_T m, int32_T n, const real_T A[12], int32_T ia0, const
                  real_T x[12], int32_T ix0, real_T y[2]);
static void xgerc(int32_T m, int32_T n, real_T alpha1, int32_T ix0, const real_T
                  y[2], real_T A[12], int32_T ia0);
static void qr(const real_T A[12], real_T b_Q[12], real_T R[4]);
static void rotate(real_T x, real_T y, real_T *c, real_T *s, real_T *r);
static real_T xnrm2(int32_T n, const real_T x[5], int32_T ix0);
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);

#define NOT_USING_NONFINITE_LITERALS   1

extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
static void rt_InitInfAndNaN(size_t realSize);
static boolean_T rtIsInf(real_T value);
static boolean_T rtIsInfF(real32_T value);
static boolean_T rtIsNaN(real_T value);
static boolean_T rtIsNaNF(real32_T value);
typedef struct {
  struct {
    uint32_T wordH;
    uint32_T wordL;
  } words;
} BigEndianIEEEDouble;

typedef struct {
  struct {
    uint32_T wordL;
    uint32_T wordH;
  } words;
} LittleEndianIEEEDouble;

typedef struct {
  union {
    real32_T wordLreal;
    uint32_T wordLuint;
  } wordL;
} IEEESingle;

real_T rtInf;
real_T rtMinusInf;
real_T rtNaN;
real32_T rtInfF;
real32_T rtMinusInfF;
real32_T rtNaNF;
static real_T rtGetInf(void);
static real32_T rtGetInfF(void);
static real_T rtGetMinusInf(void);
static real32_T rtGetMinusInfF(void);

/*
 * Initialize rtNaN needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetNaN(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T nan = 0.0;
  if (bitsPerReal == 32U) {
    nan = rtGetNaNF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF80000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    nan = tmpVal.fltVal;
  }

  return nan;
}

/*
 * Initialize rtNaNF needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetNaNF(void)
{
  IEEESingle nanF = { { 0.0F } };

  nanF.wordL.wordLuint = 0xFFC00000U;
  return nanF.wordL.wordLreal;
}

/*
 * Initialize the rtInf, rtMinusInf, and rtNaN needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */
static void rt_InitInfAndNaN(size_t realSize)
{
  (void) (realSize);
  rtNaN = rtGetNaN();
  rtNaNF = rtGetNaNF();
  rtInf = rtGetInf();
  rtInfF = rtGetInfF();
  rtMinusInf = rtGetMinusInf();
  rtMinusInfF = rtGetMinusInfF();
}

/* Test if value is infinite */
static boolean_T rtIsInf(real_T value)
{
  return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
static boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
static boolean_T rtIsNaN(real_T value)
{
  boolean_T result = (boolean_T) 0;
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  if (bitsPerReal == 32U) {
    result = rtIsNaNF((real32_T)value);
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.fltVal = value;
    result = (boolean_T)((tmpVal.bitVal.words.wordH & 0x7FF00000) == 0x7FF00000 &&
                         ( (tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 ||
                          (tmpVal.bitVal.words.wordL != 0) ));
  }

  return result;
}

/* Test if single-precision value is not a number */
static boolean_T rtIsNaNF(real32_T value)
{
  IEEESingle tmp;
  tmp.wordL.wordLreal = value;
  return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                     (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
}

/*
 * Initialize rtInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T inf = 0.0;
  if (bitsPerReal == 32U) {
    inf = rtGetInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0x7FF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    inf = tmpVal.fltVal;
  }

  return inf;
}

/*
 * Initialize rtInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetInfF(void)
{
  IEEESingle infF;
  infF.wordL.wordLuint = 0x7F800000U;
  return infF.wordL.wordLreal;
}

/*
 * Initialize rtMinusInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetMinusInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T minf = 0.0;
  if (bitsPerReal == 32U) {
    minf = rtGetMinusInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    minf = tmpVal.fltVal;
  }

  return minf;
}

/*
 * Initialize rtMinusInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetMinusInfF(void)
{
  IEEESingle minfF;
  minfF.wordL.wordLuint = 0xFF800000U;
  return minfF.wordL.wordLreal;
}

static real_T look1_pbinlc(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T prevIndex[], uint32_T maxIndex)
{
  real_T frac;
  real_T yL_0d0;
  uint32_T bpIdx;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'on'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'on'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    bpIdx = 0U;
    frac = 0.0;
  } else if (u0 < bp0[maxIndex]) {
    uint32_T found;
    uint32_T iLeft;
    uint32_T iRght;

    /* Binary Search using Previous Index */
    bpIdx = prevIndex[0U];
    iLeft = 0U;
    iRght = maxIndex;
    found = 0U;
    while (found == 0U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx - 1U;
        bpIdx = ((bpIdx + iLeft) - 1U) >> 1U;
      } else if (u0 < bp0[bpIdx + 1U]) {
        found = 1U;
      } else {
        iLeft = bpIdx + 1U;
        bpIdx = ((bpIdx + iRght) + 1U) >> 1U;
      }
    }

    frac = (u0 - bp0[bpIdx]) / (bp0[bpIdx + 1U] - bp0[bpIdx]);
  } else {
    bpIdx = maxIndex - 1U;
    frac = 1.0;
  }

  prevIndex[0U] = bpIdx;

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'wrapping'
   */
  yL_0d0 = table[bpIdx];
  return (table[bpIdx + 1U] - yL_0d0) * frac + yL_0d0;
}

static int32_T div_nde_s32_floor(int32_T numerator, int32_T denominator)
{
  return (((numerator < 0) != (denominator < 0)) && (numerator % denominator !=
           0) ? -1 : 0) + numerator / denominator;
}

/* Function for MATLAB Function: '<S6>/updatePx' */
static real_T xnrm2_f(int32_T n, const real_T x[12], int32_T ix0)
{
  real_T y;
  int32_T k;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      real_T scale;
      int32_T kend;
      scale = 3.3121686421112381E-170;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        real_T absxk;
        absxk = fabs(x[k - 1]);
        if (absxk > scale) {
          real_T t;
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          real_T t;
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrt(y);
    }
  }

  return y;
}

real_T rt_hypotd_snf(real_T u0, real_T u1)
{
  real_T a;
  real_T b;
  real_T y;
  a = fabs(u0);
  b = fabs(u1);
  if (a < b) {
    a /= b;
    y = sqrt(a * a + 1.0) * b;
  } else if (a > b) {
    b /= a;
    y = sqrt(b * b + 1.0) * a;
  } else if (rtIsNaN(b)) {
    y = (rtNaN);
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

/* Function for MATLAB Function: '<S6>/updatePx' */
static void xgemv(int32_T m, int32_T n, const real_T A[12], int32_T ia0, const
                  real_T x[12], int32_T ix0, real_T y[2])
{
  int32_T b_iy;
  int32_T iyend;
  if ((m != 0) && (n != 0)) {
    int32_T b;
    if (n - 1 >= 0) {
      memset(&y[0], 0, (uint32_T)n * sizeof(real_T));
    }

    b = (n - 1) * 6 + ia0;
    for (b_iy = ia0; b_iy <= b; b_iy += 6) {
      real_T c;
      int32_T d;
      c = 0.0;
      d = (b_iy + m) - 1;
      for (iyend = b_iy; iyend <= d; iyend++) {
        c += x[((ix0 + iyend) - b_iy) - 1] * A[iyend - 1];
      }

      iyend = div_nde_s32_floor(b_iy - ia0, 6);
      y[iyend] += c;
    }
  }
}

/* Function for MATLAB Function: '<S6>/updatePx' */
static void xgerc(int32_T m, int32_T n, real_T alpha1, int32_T ix0, const real_T
                  y[2], real_T A[12], int32_T ia0)
{
  int32_T ijA;
  int32_T j;
  if (!(alpha1 == 0.0)) {
    int32_T jA;
    jA = ia0;
    for (j = 0; j < n; j++) {
      real_T temp;
      temp = y[j];
      if (temp != 0.0) {
        int32_T b;
        temp *= alpha1;
        b = m + jA;
        for (ijA = jA; ijA < b; ijA++) {
          A[ijA - 1] += A[((ix0 + ijA) - jA) - 1] * temp;
        }
      }

      jA += 6;
    }
  }
}

/* Function for MATLAB Function: '<S6>/updatePx' */
static void qr(const real_T A[12], real_T b_Q[12], real_T R[4])
{
  real_T tau[2];
  real_T work[2];
  real_T atmp;
  real_T b_A;
  real_T beta1;
  int32_T b_lastv;
  int32_T c_k;
  int32_T exitg1;
  int32_T ii;
  int32_T itau;
  int32_T knt;
  int32_T lastc;
  memcpy(&b_Q[0], &A[0], 12U * sizeof(real_T));
  tau[0] = 0.0;
  work[0] = 0.0;
  tau[1] = 0.0;
  work[1] = 0.0;
  for (itau = 0; itau < 2; itau++) {
    ii = itau * 6 + itau;
    atmp = b_Q[ii];
    b_lastv = ii + 2;
    tau[itau] = 0.0;
    beta1 = xnrm2_f(5 - itau, b_Q, ii + 2);
    if (beta1 != 0.0) {
      b_A = b_Q[ii];
      beta1 = rt_hypotd_snf(b_A, beta1);
      if (b_A >= 0.0) {
        beta1 = -beta1;
      }

      if (fabs(beta1) < 1.0020841800044864E-292) {
        knt = 0;
        lastc = (ii - itau) + 6;
        do {
          knt++;
          for (c_k = b_lastv; c_k <= lastc; c_k++) {
            b_Q[c_k - 1] *= 9.9792015476736E+291;
          }

          beta1 *= 9.9792015476736E+291;
          atmp *= 9.9792015476736E+291;
        } while ((fabs(beta1) < 1.0020841800044864E-292) && (knt < 20));

        beta1 = rt_hypotd_snf(atmp, xnrm2_f(5 - itau, b_Q, ii + 2));
        if (atmp >= 0.0) {
          beta1 = -beta1;
        }

        tau[itau] = (beta1 - atmp) / beta1;
        atmp = 1.0 / (atmp - beta1);
        for (c_k = b_lastv; c_k <= lastc; c_k++) {
          b_Q[c_k - 1] *= atmp;
        }

        for (b_lastv = 0; b_lastv < knt; b_lastv++) {
          beta1 *= 1.0020841800044864E-292;
        }

        atmp = beta1;
      } else {
        tau[itau] = (beta1 - b_A) / beta1;
        atmp = 1.0 / (b_A - beta1);
        knt = (ii - itau) + 6;
        for (lastc = b_lastv; lastc <= knt; lastc++) {
          b_Q[lastc - 1] *= atmp;
        }

        atmp = beta1;
      }
    }

    b_Q[ii] = atmp;
    if (itau + 1 < 2) {
      b_Q[ii] = 1.0;
      if (tau[0] != 0.0) {
        b_lastv = 6;
        knt = ii + 5;
        while ((b_lastv > 0) && (b_Q[knt] == 0.0)) {
          b_lastv--;
          knt--;
        }

        knt = 1;
        lastc = ii;
        do {
          exitg1 = 0;
          if (lastc + 7 <= (ii + b_lastv) + 6) {
            if (b_Q[lastc + 6] != 0.0) {
              exitg1 = 1;
            } else {
              lastc++;
            }
          } else {
            knt = 0;
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      } else {
        b_lastv = 0;
        knt = 0;
      }

      if (b_lastv > 0) {
        xgemv(b_lastv, knt, b_Q, ii + 7, b_Q, ii + 1, work);
        xgerc(b_lastv, knt, -tau[0], ii + 1, work, b_Q, ii + 7);
      }

      b_Q[ii] = atmp;
    }
  }

  for (itau = 0; itau < 2; itau++) {
    for (ii = 0; ii <= itau; ii++) {
      R[ii + (itau << 1)] = b_Q[6 * itau + ii];
    }

    if (itau + 2 <= 2) {
      R[(itau << 1) + 1] = 0.0;
    }

    work[itau] = 0.0;
  }

  for (ii = 1; ii >= 0; ii--) {
    b_lastv = (ii * 6 + ii) + 7;
    if (ii + 1 < 2) {
      b_Q[b_lastv - 7] = 1.0;
      if (tau[ii] != 0.0) {
        knt = 6;
        lastc = b_lastv;
        while ((knt > 0) && (b_Q[lastc - 2] == 0.0)) {
          knt--;
          lastc--;
        }

        lastc = 1;
        c_k = b_lastv;
        do {
          exitg1 = 0;
          if (c_k <= (b_lastv + knt) - 1) {
            if (b_Q[c_k - 1] != 0.0) {
              exitg1 = 1;
            } else {
              c_k++;
            }
          } else {
            lastc = 0;
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      } else {
        knt = 0;
        lastc = 0;
      }

      if (knt > 0) {
        xgemv(knt, lastc, b_Q, b_lastv, b_Q, b_lastv - 6, work);
        xgerc(knt, lastc, -tau[ii], b_lastv - 6, work, b_Q, b_lastv);
      }
    }

    knt = (b_lastv - ii) - 1;
    for (lastc = b_lastv - 5; lastc <= knt; lastc++) {
      b_Q[lastc - 1] *= -tau[ii];
    }

    b_Q[b_lastv - 7] = 1.0 - tau[ii];
    if (ii - 1 >= 0) {
      b_Q[b_lastv - 8] = 0.0;
    }
  }
}

/* Function for MATLAB Function: '<S6>/updatePy' */
static void rotate(real_T x, real_T y, real_T *c, real_T *s, real_T *r)
{
  real_T absx;
  real_T absy;
  real_T rho;
  real_T xx;
  real_T yy;
  absx = fabs(x);
  absy = fabs(y);
  if (absy == 0.0) {
    *c = 1.0;
    *s = 0.0;
    *r = x;
  } else if (absx == 0.0) {
    *c = 0.0;
    *s = 1.0;
    *r = y;
  } else {
    absy += absx;
    xx = x / absy;
    yy = y / absy;
    absx = fabs(xx);
    rho = rt_hypotd_snf(absx, fabs(yy));
    *c = absx / rho;
    xx /= absx;
    *s = xx * yy / rho;
    *r = rho * absy * xx;
  }
}

/* Function for MATLAB Function: '<S6>/updatePy' */
static real_T xnrm2(int32_T n, const real_T x[5], int32_T ix0)
{
  real_T y;
  int32_T k;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      real_T scale;
      int32_T kend;
      scale = 3.3121686421112381E-170;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        real_T absxk;
        absxk = fabs(x[k - 1]);
        if (absxk > scale) {
          real_T t;
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          real_T t;
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrt(y);
    }
  }

  return y;
}

/* Model step function */
void Final_model_step(void)
{
  real_T b[25];
  real_T a__1[12];
  real_T residual_1[12];
  real_T residual[10];
  real_T rtb_ImpAsg_InsertedFor_Wm_ixk1_[10];
  real_T residual_0[5];
  real_T rtb_ImpAsg_InsertedFor_y_at_inp[5];
  real_T rtb_Y1[5];
  real_T rtb_MatrixMultiply[4];
  real_T b_c[2];
  real_T rtb_Add[2];
  real_T rtb_Kk1_j[2];
  real_T rtb_Product5[2];
  real_T rtb_SumofElements[2];
  real_T s[2];
  real_T absxk_tmp;
  real_T rtb_Gain_b_idx_0;
  real_T rtb_Gain_b_idx_1;
  real_T rtb_Gain_b_idx_2;
  real_T rtb_Gain_b_idx_3;
  real_T scale;
  int32_T ForEach_itr_oe;
  int32_T i;
  int32_T knt;
  int32_T temp_tmp_tmp;
  boolean_T errorCondition;

  /* Outputs for Iterator SubSystem: '<Root>/SOCEstimator' incorporates:
   *  ForEach: '<S1>/For Each'
   */
  /* Delay: '<S5>/Delay' incorporates:
   *  Constant: '<S5>/Constant1'
   *  Inport: '<Root>/Input2'
   *  Reshape: '<S5>/Reshape'
   */
  if (rtDW.CoreSubsys[0].icLoad) {
    rtDW.CoreSubsys[0].Delay_DSTATE[0] = rtU.Input2;
    rtDW.CoreSubsys[0].Delay_DSTATE[1] = 0.0;
  }

  /* Gain: '<S7>/Gain' incorporates:
   *  UnitDelay: '<S3>/UnitDelayP'
   */
  rtb_Gain_b_idx_0 = 1.4142135623730951 * rtDW.CoreSubsys[0].UnitDelayP_DSTATE[0];
  rtb_Gain_b_idx_1 = 1.4142135623730951 * rtDW.CoreSubsys[0].UnitDelayP_DSTATE[1];
  rtb_Gain_b_idx_2 = 1.4142135623730951 * rtDW.CoreSubsys[0].UnitDelayP_DSTATE[2];
  rtb_Gain_b_idx_3 = 1.4142135623730951 * rtDW.CoreSubsys[0].UnitDelayP_DSTATE[3];

  /* Assignment: '<S7>/Assignment' incorporates:
   *  Assignment: '<S7>/Assignment2'
   *  Delay: '<S5>/Delay'
   */
  rtDW.CoreSubsys[0].Assignment2[0] = rtDW.CoreSubsys[0].Delay_DSTATE[0];

  /* Assignment: '<S7>/Assignment1' incorporates:
   *  Assignment: '<S7>/Assignment2'
   *  Delay: '<S5>/Delay'
   *  Gain: '<S7>/Gain'
   *  Sum: '<S7>/Sum'
   */
  rtDW.CoreSubsys[0].Assignment2[2] = rtDW.CoreSubsys[0].Delay_DSTATE[0] +
    rtb_Gain_b_idx_0;

  /* Assignment: '<S7>/Assignment2' incorporates:
   *  Delay: '<S5>/Delay'
   *  Gain: '<S7>/Gain'
   *  Sum: '<S7>/Sum'
   *  Sum: '<S7>/Sum1'
   */
  rtDW.CoreSubsys[0].Assignment2[6] = rtDW.CoreSubsys[0].Delay_DSTATE[0] -
    rtb_Gain_b_idx_0;

  /* Assignment: '<S7>/Assignment1' incorporates:
   *  Assignment: '<S7>/Assignment2'
   *  Delay: '<S5>/Delay'
   *  Gain: '<S7>/Gain'
   *  Product: '<S7>/Matrix Multiply'
   *  Sum: '<S7>/Sum'
   */
  rtDW.CoreSubsys[0].Assignment2[3] = rtDW.CoreSubsys[0].Delay_DSTATE[1] +
    rtb_Gain_b_idx_1;

  /* Assignment: '<S7>/Assignment2' incorporates:
   *  Delay: '<S5>/Delay'
   *  Gain: '<S7>/Gain'
   *  Product: '<S7>/Matrix Multiply'
   *  Sum: '<S7>/Sum'
   *  Sum: '<S7>/Sum1'
   */
  rtDW.CoreSubsys[0].Assignment2[7] = rtDW.CoreSubsys[0].Delay_DSTATE[1] -
    rtb_Gain_b_idx_1;

  /* Assignment: '<S7>/Assignment' incorporates:
   *  Assignment: '<S7>/Assignment2'
   *  Delay: '<S5>/Delay'
   *  Product: '<S7>/Matrix Multiply'
   */
  rtDW.CoreSubsys[0].Assignment2[1] = rtDW.CoreSubsys[0].Delay_DSTATE[1];

  /* Assignment: '<S7>/Assignment1' incorporates:
   *  Assignment: '<S7>/Assignment2'
   *  Delay: '<S5>/Delay'
   *  Gain: '<S7>/Gain'
   *  Sum: '<S7>/Sum'
   */
  rtDW.CoreSubsys[0].Assignment2[4] = rtDW.CoreSubsys[0].Delay_DSTATE[0] +
    rtb_Gain_b_idx_2;

  /* Assignment: '<S7>/Assignment2' incorporates:
   *  Delay: '<S5>/Delay'
   *  Gain: '<S7>/Gain'
   *  Sum: '<S7>/Sum'
   *  Sum: '<S7>/Sum1'
   */
  rtDW.CoreSubsys[0].Assignment2[8] = rtDW.CoreSubsys[0].Delay_DSTATE[0] -
    rtb_Gain_b_idx_2;

  /* Assignment: '<S7>/Assignment1' incorporates:
   *  Assignment: '<S7>/Assignment2'
   *  Delay: '<S5>/Delay'
   *  Gain: '<S7>/Gain'
   *  Product: '<S7>/Matrix Multiply'
   *  Sum: '<S7>/Sum'
   */
  rtDW.CoreSubsys[0].Assignment2[5] = rtDW.CoreSubsys[0].Delay_DSTATE[1] +
    rtb_Gain_b_idx_3;

  /* Assignment: '<S7>/Assignment2' incorporates:
   *  Delay: '<S5>/Delay'
   *  Gain: '<S7>/Gain'
   *  Product: '<S7>/Matrix Multiply'
   *  Sum: '<S7>/Sum'
   *  Sum: '<S7>/Sum1'
   */
  rtDW.CoreSubsys[0].Assignment2[9] = rtDW.CoreSubsys[0].Delay_DSTATE[1] -
    rtb_Gain_b_idx_3;

  /* Outputs for Iterator SubSystem: '<S6>/Statefunction' incorporates:
   *  ForEach: '<S12>/For Each'
   */
  for (ForEach_itr_oe = 0; ForEach_itr_oe < 5; ForEach_itr_oe++) {
    /* ForEachSliceSelector generated from: '<S12>/X' incorporates:
     *  Assignment: '<S7>/Assignment2'
     *  Lookup_n-D: '<S18>/C1'
     *  Lookup_n-D: '<S18>/R1'
     *  Product: '<S18>/Divide2'
     *  Sum: '<S18>/Add'
     */
    temp_tmp_tmp = ForEach_itr_oe << 1;
    rtb_Gain_b_idx_1 = rtDW.CoreSubsys[0].Assignment2[temp_tmp_tmp];

    /* Lookup_n-D: '<S18>/R1' incorporates:
     *  ForEachSliceSelector generated from: '<S12>/X'
     */
    rtb_Gain_b_idx_2 = look1_pbinlc(rtb_Gain_b_idx_1, rtConstP.R1_bp01Data,
      rtConstP.R1_tableData, &rtDW.CoreSubsys[0].CoreSubsys[ForEach_itr_oe].
      m_bpIndex, 9U);

    /* Lookup_n-D: '<S18>/C1' */
    rtb_Gain_b_idx_0 = look1_pbinlc(rtb_Gain_b_idx_1, rtConstP.C1_bp01Data,
      rtConstP.C1_tableData, &rtDW.CoreSubsys[0].CoreSubsys[ForEach_itr_oe].
      m_bpIndex_k, 9U);

    /* Selector: '<S12>/Selector' incorporates:
     *  Constant: '<S12>/Constant'
     */
    rtb_Gain_b_idx_3 = rtConstP.pooled2[ForEach_itr_oe];

    /* Sum: '<S18>/Add' incorporates:
     *  Gain: '<S18>/Gain'
     *  Gain: '<S1>/Gain'
     *  Inport: '<Root>/Input'
     *  Product: '<S18>/Product'
     */
    scale = (real32_T)(-2.5252525252525253E-5 * -rtU.Input * rtDW.CoreSubsys[0].
                       CoreSubsys[ForEach_itr_oe].Probe[0]) + rtb_Gain_b_idx_1;
    rtb_Add[0] = scale;

    /* ForEachSliceAssignment generated from: '<S12>/Wm_ixk1_i' incorporates:
     *  Product: '<S12>/Product'
     *  Sum: '<S18>/Add'
     */
    rtb_ImpAsg_InsertedFor_Wm_ixk1_[temp_tmp_tmp] = rtb_Gain_b_idx_3 * scale;

    /* ForEachSliceAssignment generated from: '<S12>/xk1' incorporates:
     *  Sum: '<S18>/Add'
     */
    rtDW.CoreSubsys[0].ImpAsg_InsertedFor_xk1_at_inpor[temp_tmp_tmp] = scale;

    /* Sum: '<S18>/Add' incorporates:
     *  Assignment: '<S7>/Assignment2'
     *  ForEachSliceSelector generated from: '<S12>/X'
     *  Gain: '<S1>/Gain'
     *  Inport: '<Root>/Input'
     *  Product: '<S18>/Divide1'
     *  Product: '<S18>/Divide2'
     *  Product: '<S18>/Product'
     *  Product: '<S18>/Product1'
     *  Sum: '<S18>/Add1'
     */
    rtb_Gain_b_idx_1 = rtDW.CoreSubsys[0].Assignment2[temp_tmp_tmp + 1];
    scale = (real32_T)((-rtU.Input / rtb_Gain_b_idx_0 - rtb_Gain_b_idx_1 /
                        (rtb_Gain_b_idx_2 * rtb_Gain_b_idx_0)) *
                       rtDW.CoreSubsys[0].CoreSubsys[ForEach_itr_oe].Probe[0]) +
      rtb_Gain_b_idx_1;
    rtb_Add[1] = scale;

    /* ForEachSliceAssignment generated from: '<S12>/Wm_ixk1_i' incorporates:
     *  Product: '<S12>/Product'
     *  Product: '<S18>/Divide2'
     *  Sum: '<S18>/Add'
     */
    rtb_ImpAsg_InsertedFor_Wm_ixk1_[temp_tmp_tmp + 1] = rtb_Gain_b_idx_3 * scale;

    /* ForEachSliceAssignment generated from: '<S12>/xk1' incorporates:
     *  Product: '<S18>/Divide2'
     *  Sum: '<S18>/Add'
     */
    rtDW.CoreSubsys[0].ImpAsg_InsertedFor_xk1_at_inpor[temp_tmp_tmp + 1] = scale;
  }

  /* End of Outputs for SubSystem: '<S6>/Statefunction' */

  /* Sum: '<S6>/Sum of Elements' incorporates:
   *  ForEachSliceAssignment generated from: '<S12>/Wm_ixk1_i'
   */
  for (ForEach_itr_oe = 0; ForEach_itr_oe < 2; ForEach_itr_oe++) {
    rtb_Gain_b_idx_2 = -0.0;
    for (knt = 0; knt < 5; knt++) {
      rtb_Gain_b_idx_2 += rtb_ImpAsg_InsertedFor_Wm_ixk1_[(knt << 1) +
        ForEach_itr_oe];
    }

    rtb_SumofElements[ForEach_itr_oe] = rtb_Gain_b_idx_2;
  }

  /* End of Sum: '<S6>/Sum of Elements' */

  /* MATLAB Function: '<S6>/updatePx' incorporates:
   *  ForEachSliceAssignment generated from: '<S12>/xk1'
   *  Sum: '<S6>/Sum of Elements'
   */
  rtb_Gain_b_idx_0 = rtb_SumofElements[0];
  rtb_Gain_b_idx_1 = rtb_SumofElements[1];
  for (knt = 0; knt < 5; knt++) {
    temp_tmp_tmp = knt << 1;
    rtb_ImpAsg_InsertedFor_Wm_ixk1_[temp_tmp_tmp] = rtDW.CoreSubsys[0].
      ImpAsg_InsertedFor_xk1_at_inpor[temp_tmp_tmp] - rtb_Gain_b_idx_0;
    rtb_ImpAsg_InsertedFor_Wm_ixk1_[temp_tmp_tmp + 1] = rtDW.CoreSubsys[0].
      ImpAsg_InsertedFor_xk1_at_inpor[temp_tmp_tmp + 1] - rtb_Gain_b_idx_1;
    rtb_Y1[knt] = sqrt(fabs(rtConstP.pooled1[knt]));
  }

  memset(&b[0], 0, 25U * sizeof(real_T));
  for (ForEach_itr_oe = 0; ForEach_itr_oe < 5; ForEach_itr_oe++) {
    b[ForEach_itr_oe + 5 * ForEach_itr_oe] = rtb_Y1[ForEach_itr_oe];
  }

  for (ForEach_itr_oe = 0; ForEach_itr_oe < 2; ForEach_itr_oe++) {
    for (knt = 0; knt < 5; knt++) {
      rtb_Gain_b_idx_0 = 0.0;
      for (temp_tmp_tmp = 0; temp_tmp_tmp < 5; temp_tmp_tmp++) {
        rtb_Gain_b_idx_0 += rtb_ImpAsg_InsertedFor_Wm_ixk1_[(temp_tmp_tmp << 1)
          + ForEach_itr_oe] * b[5 * knt + temp_tmp_tmp];
      }

      residual[ForEach_itr_oe + (knt << 1)] = rtb_Gain_b_idx_0;
    }

    residual_1[6 * ForEach_itr_oe] = residual[ForEach_itr_oe + 2];
    residual_1[6 * ForEach_itr_oe + 1] = residual[ForEach_itr_oe + 4];
    residual_1[6 * ForEach_itr_oe + 2] = residual[ForEach_itr_oe + 6];
    residual_1[6 * ForEach_itr_oe + 3] = residual[ForEach_itr_oe + 8];
    residual_1[6 * ForEach_itr_oe + 4] = rtConstP.updatePx_Q[ForEach_itr_oe];
    residual_1[6 * ForEach_itr_oe + 5] = rtConstP.updatePx_Q[ForEach_itr_oe + 2];
  }

  qr(residual_1, a__1, rtb_MatrixMultiply);
  for (ForEach_itr_oe = 0; ForEach_itr_oe < 2; ForEach_itr_oe++) {
    if (-ForEach_itr_oe >= 0) {
      rtb_MatrixMultiply[(ForEach_itr_oe + (ForEach_itr_oe << 1)) + 1] = 0.0;
    }
  }

  rotate(rtb_MatrixMultiply[0], residual[0], &rtb_Gain_b_idx_1,
         &rtb_Gain_b_idx_2, &rtb_MatrixMultiply[0]);
  rtb_Gain_b_idx_0 = rtb_Gain_b_idx_1 * residual[1] - rtb_Gain_b_idx_2 *
    rtb_MatrixMultiply[2];
  rtb_MatrixMultiply[2] = rtb_Gain_b_idx_1 * rtb_MatrixMultiply[2] +
    rtb_Gain_b_idx_2 * residual[1];
  rotate(rtb_MatrixMultiply[3], rtb_Gain_b_idx_0, &rtb_Gain_b_idx_3,
         &rtb_Gain_b_idx_1, &rtb_MatrixMultiply[3]);

  /* End of MATLAB Function: '<S6>/updatePx' */

  /* Outputs for Iterator SubSystem: '<S6>/Measurementfunction' incorporates:
   *  ForEach: '<S11>/For Each'
   */
  for (ForEach_itr_oe = 0; ForEach_itr_oe < 5; ForEach_itr_oe++) {
    /* ForEachSliceSelector generated from: '<S11>/X' incorporates:
     *  ForEachSliceAssignment generated from: '<S12>/xk1'
     *  Lookup_n-D: '<S16>/OCVTable'
     *  Lookup_n-D: '<S16>/R0Table'
     *  Sum: '<S16>/Add2'
     */
    temp_tmp_tmp = ForEach_itr_oe << 1;
    rtb_Gain_b_idx_1 = rtDW.CoreSubsys[0]
      .ImpAsg_InsertedFor_xk1_at_inpor[temp_tmp_tmp];

    /* Lookup_n-D: '<S16>/OCVTable' incorporates:
     *  ForEachSliceSelector generated from: '<S11>/X'
     */
    rtb_Gain_b_idx_0 = look1_pbinlc(rtb_Gain_b_idx_1, rtConstP.OCVTable_bp01Data,
      rtConstP.OCVTable_tableData, &rtDW.CoreSubsys[0]
      .CoreSubsys_b[ForEach_itr_oe].m_bpIndex, 9U);

    /* Lookup_n-D: '<S16>/R0Table' */
    rtb_Gain_b_idx_2 = look1_pbinlc(rtb_Gain_b_idx_1, rtConstP.R0Table_bp01Data,
      rtConstP.R0Table_tableData, &rtDW.CoreSubsys[0]
      .CoreSubsys_b[ForEach_itr_oe].m_bpIndex_l, 9U);

    /* Sum: '<S16>/Add2' incorporates:
     *  ForEachSliceAssignment generated from: '<S12>/xk1'
     *  ForEachSliceSelector generated from: '<S11>/X'
     *  Gain: '<S1>/Gain'
     *  Inport: '<Root>/Input'
     *  Product: '<S16>/Product2'
     */
    rtb_Gain_b_idx_2 = (rtb_Gain_b_idx_0 - rtb_Gain_b_idx_2 * -rtU.Input) -
      rtDW.CoreSubsys[0].ImpAsg_InsertedFor_xk1_at_inpor[temp_tmp_tmp + 1];

    /* ForEachSliceAssignment generated from: '<S11>/Wm_iy_i' incorporates:
     *  Constant: '<S11>/Constant'
     *  Product: '<S11>/Product'
     *  Selector: '<S11>/Selector'
     */
    rtb_Y1[ForEach_itr_oe] = rtConstP.pooled2[ForEach_itr_oe] * rtb_Gain_b_idx_2;

    /* ForEachSliceAssignment generated from: '<S11>/y' */
    rtb_ImpAsg_InsertedFor_y_at_inp[ForEach_itr_oe] = rtb_Gain_b_idx_2;
  }

  /* End of Outputs for SubSystem: '<S6>/Measurementfunction' */

  /* Sum: '<S6>/Sum of Elements1' incorporates:
   *  ForEachSliceAssignment generated from: '<S11>/Wm_iy_i'
   */
  rtb_Gain_b_idx_1 = -0.0;
  for (ForEach_itr_oe = 0; ForEach_itr_oe < 5; ForEach_itr_oe++) {
    rtb_Gain_b_idx_1 += rtb_Y1[ForEach_itr_oe];
  }

  /* End of Sum: '<S6>/Sum of Elements1' */

  /* MATLAB Function: '<S6>/updatePy' incorporates:
   *  ForEachSliceAssignment generated from: '<S11>/y'
   */
  for (knt = 0; knt < 5; knt++) {
    rtb_Y1[knt] = rtb_ImpAsg_InsertedFor_y_at_inp[knt] - rtb_Gain_b_idx_1;
    residual_0[knt] = sqrt(fabs(rtConstP.pooled1[knt]));
  }

  memset(&b[0], 0, 25U * sizeof(real_T));
  for (ForEach_itr_oe = 0; ForEach_itr_oe < 5; ForEach_itr_oe++) {
    b[ForEach_itr_oe + 5 * ForEach_itr_oe] = residual_0[ForEach_itr_oe];
  }

  for (ForEach_itr_oe = 0; ForEach_itr_oe < 5; ForEach_itr_oe++) {
    rtb_Gain_b_idx_0 = 0.0;
    for (knt = 0; knt < 5; knt++) {
      rtb_Gain_b_idx_0 += b[5 * ForEach_itr_oe + knt] * rtb_Y1[knt];
    }

    residual_0[ForEach_itr_oe] = rtb_Gain_b_idx_0;
  }

  rtb_ImpAsg_InsertedFor_y_at_inp[0] = residual_0[1];
  rtb_ImpAsg_InsertedFor_y_at_inp[1] = residual_0[2];
  rtb_ImpAsg_InsertedFor_y_at_inp[2] = residual_0[3];
  rtb_ImpAsg_InsertedFor_y_at_inp[3] = residual_0[4];
  rtb_ImpAsg_InsertedFor_y_at_inp[4] = 0.1;
  rtb_Gain_b_idx_2 = residual_0[1];
  rtb_Gain_b_idx_3 = xnrm2(4, rtb_ImpAsg_InsertedFor_y_at_inp, 2);
  if (rtb_Gain_b_idx_3 != 0.0) {
    rtb_Gain_b_idx_3 = rt_hypotd_snf(residual_0[1], rtb_Gain_b_idx_3);
    if (residual_0[1] >= 0.0) {
      rtb_Gain_b_idx_3 = -rtb_Gain_b_idx_3;
    }

    if (fabs(rtb_Gain_b_idx_3) < 1.0020841800044864E-292) {
      knt = 0;
      do {
        knt++;
        rtb_ImpAsg_InsertedFor_y_at_inp[1] *= 9.9792015476736E+291;
        rtb_ImpAsg_InsertedFor_y_at_inp[2] *= 9.9792015476736E+291;
        rtb_ImpAsg_InsertedFor_y_at_inp[3] *= 9.9792015476736E+291;
        rtb_ImpAsg_InsertedFor_y_at_inp[4] *= 9.9792015476736E+291;
        rtb_Gain_b_idx_3 *= 9.9792015476736E+291;
        rtb_Gain_b_idx_2 *= 9.9792015476736E+291;
      } while ((fabs(rtb_Gain_b_idx_3) < 1.0020841800044864E-292) && (knt < 20));

      rtb_Gain_b_idx_3 = rt_hypotd_snf(rtb_Gain_b_idx_2, xnrm2(4,
        rtb_ImpAsg_InsertedFor_y_at_inp, 2));
      if (rtb_Gain_b_idx_2 >= 0.0) {
        rtb_Gain_b_idx_3 = -rtb_Gain_b_idx_3;
      }

      for (ForEach_itr_oe = 0; ForEach_itr_oe < knt; ForEach_itr_oe++) {
        rtb_Gain_b_idx_3 *= 1.0020841800044864E-292;
      }

      rtb_Gain_b_idx_2 = rtb_Gain_b_idx_3;
    } else {
      rtb_Gain_b_idx_2 = rtb_Gain_b_idx_3;
    }
  }

  rotate(rtb_Gain_b_idx_2, residual_0[0], &rtb_Gain_b_idx_3, &rtb_Gain_b_idx_2,
         &rtb_Gain_b_idx_0);
  for (temp_tmp_tmp = 0; temp_tmp_tmp < 2; temp_tmp_tmp++) {
    /* Product: '<S4>/Product1' */
    rtb_Gain_b_idx_3 = 0.0;
    for (ForEach_itr_oe = 0; ForEach_itr_oe < 5; ForEach_itr_oe++) {
      /* Product: '<S6>/Product5' incorporates:
       *  Constant: '<S6>/Constant'
       */
      rtb_Gain_b_idx_2 = 0.0;
      for (knt = 0; knt < 5; knt++) {
        rtb_Gain_b_idx_2 += rtb_ImpAsg_InsertedFor_Wm_ixk1_[(knt << 1) +
          temp_tmp_tmp] * rtConstP.Constant_Value[5 * ForEach_itr_oe + knt];
      }

      /* Product: '<S4>/Product1' incorporates:
       *  Math: '<S6>/Math Function'
       *  Product: '<S6>/Product1'
       *  Product: '<S6>/Product5'
       */
      rtb_Gain_b_idx_3 += rtb_Gain_b_idx_2 * rtb_Y1[ForEach_itr_oe];
    }

    /* Product: '<S4>/Product1' incorporates:
     *  MATLAB Function: '<S6>/updatePy'
     *  Product: '<S4>/Product6'
     *  Product: '<S6>/Product1'
     */
    rtb_Gain_b_idx_2 = rtb_Gain_b_idx_3 / rtb_Gain_b_idx_0 / rtb_Gain_b_idx_0;
    rtb_Kk1_j[temp_tmp_tmp] = rtb_Gain_b_idx_2;

    /* Product: '<S4>/Product5' incorporates:
     *  MATLAB Function: '<S6>/updatePy'
     *  Product: '<S4>/Product1'
     */
    rtb_Product5[temp_tmp_tmp] = rtb_Gain_b_idx_2 * rtb_Gain_b_idx_0;
  }

  /* MATLAB Function: '<S4>/updatePk' incorporates:
   *  Product: '<S4>/Product5'
   */
  for (temp_tmp_tmp = 0; temp_tmp_tmp < 1; temp_tmp_tmp++) {
    for (ForEach_itr_oe = 0; ForEach_itr_oe < 2; ForEach_itr_oe++) {
      if (-ForEach_itr_oe >= 0) {
        rtb_MatrixMultiply[(ForEach_itr_oe + (ForEach_itr_oe << 1)) + 1] = 0.0;
      }
    }

    errorCondition = (rtb_MatrixMultiply[0] == 0.0);
    if (!errorCondition) {
      errorCondition = (rtb_MatrixMultiply[3] == 0.0);
    }

    if (!errorCondition) {
      for (i = 0; i < 2; i++) {
        rtb_Gain_b_idx_2 = rtb_Product5[i];
        rtb_Add[i] = rtb_Gain_b_idx_2;
        ForEach_itr_oe = i << 1;
        for (knt = 0; knt < i; knt++) {
          rtb_Gain_b_idx_2 -= rtb_MatrixMultiply[ForEach_itr_oe] * rtb_Add[0];
        }

        rtb_Add[i] = rtb_Gain_b_idx_2 / rtb_MatrixMultiply[i + ForEach_itr_oe];
      }

      scale = 3.3121686421112381E-170;
      absxk_tmp = fabs(rtb_Add[0]);
      if (absxk_tmp > 3.3121686421112381E-170) {
        rtb_Gain_b_idx_2 = 1.0;
        scale = absxk_tmp;
      } else {
        rtb_Gain_b_idx_0 = absxk_tmp / 3.3121686421112381E-170;
        rtb_Gain_b_idx_2 = rtb_Gain_b_idx_0 * rtb_Gain_b_idx_0;
      }

      rtb_Gain_b_idx_3 = fabs(rtb_Add[1]);
      if (rtb_Gain_b_idx_3 > scale) {
        rtb_Gain_b_idx_0 = scale / rtb_Gain_b_idx_3;
        rtb_Gain_b_idx_2 = rtb_Gain_b_idx_2 * rtb_Gain_b_idx_0 *
          rtb_Gain_b_idx_0 + 1.0;
        scale = rtb_Gain_b_idx_3;
      } else {
        rtb_Gain_b_idx_0 = rtb_Gain_b_idx_3 / scale;
        rtb_Gain_b_idx_2 += rtb_Gain_b_idx_0 * rtb_Gain_b_idx_0;
      }

      rtb_Gain_b_idx_2 = scale * sqrt(rtb_Gain_b_idx_2);
      if (!(rtb_Gain_b_idx_2 >= 1.0)) {
        scale = sqrt(1.0 - rtb_Gain_b_idx_2 * rtb_Gain_b_idx_2);
        if (rtb_Gain_b_idx_3 == 0.0) {
          b_c[1] = 1.0;
          s[1] = 0.0;
        } else {
          rtb_Gain_b_idx_0 = scale + rtb_Gain_b_idx_3;
          rtb_Gain_b_idx_2 = scale / rtb_Gain_b_idx_0;
          scale = rtb_Add[1] / rtb_Gain_b_idx_0;
          rtb_Gain_b_idx_3 = rt_hypotd_snf(rtb_Gain_b_idx_2, fabs(scale));
          b_c[1] = rtb_Gain_b_idx_2 / rtb_Gain_b_idx_3;
          rtb_Gain_b_idx_2 /= rtb_Gain_b_idx_2;
          s[1] = rtb_Gain_b_idx_2 * scale / rtb_Gain_b_idx_3;
          scale = rtb_Gain_b_idx_3 * rtb_Gain_b_idx_0 * rtb_Gain_b_idx_2;
        }

        rtb_Add[1] = 0.0;
        if (absxk_tmp == 0.0) {
          b_c[0] = 1.0;
          s[0] = 0.0;
        } else if (scale == 0.0) {
          b_c[0] = 0.0;
          s[0] = 1.0;
        } else {
          rtb_Gain_b_idx_0 = scale + absxk_tmp;
          rtb_Gain_b_idx_2 = scale / rtb_Gain_b_idx_0;
          scale = rtb_Add[0] / rtb_Gain_b_idx_0;
          rtb_Gain_b_idx_3 = rt_hypotd_snf(rtb_Gain_b_idx_2, fabs(scale));
          b_c[0] = rtb_Gain_b_idx_2 / rtb_Gain_b_idx_3;
          s[0] = rtb_Gain_b_idx_2 / rtb_Gain_b_idx_2 * scale / rtb_Gain_b_idx_3;
        }

        rtb_Add[0] = 0.0;
        for (ForEach_itr_oe = 0; ForEach_itr_oe < 2; ForEach_itr_oe++) {
          for (knt = ForEach_itr_oe + 1; knt >= 1; knt--) {
            rtb_Gain_b_idx_0 = s[knt - 1];
            i = ((ForEach_itr_oe << 1) + knt) - 1;
            rtb_Gain_b_idx_2 = rtb_MatrixMultiply[i];
            rtb_Gain_b_idx_3 = b_c[knt - 1];
            scale = rtb_Add[ForEach_itr_oe];
            rtb_MatrixMultiply[i] = rtb_Gain_b_idx_3 * rtb_Gain_b_idx_2 -
              rtb_Gain_b_idx_0 * scale;
            rtb_Add[ForEach_itr_oe] = rtb_Gain_b_idx_3 * scale +
              rtb_Gain_b_idx_0 * rtb_Gain_b_idx_2;
          }
        }
      }
    }
  }

  /* End of MATLAB Function: '<S4>/updatePk' */

  /* Sum: '<S3>/Sum' incorporates:
   *  Inport: '<Root>/Input1'
   */
  rtb_Gain_b_idx_3 = rtU.Input1 - rtb_Gain_b_idx_1;

  /* Update for Delay: '<S5>/Delay' */
  rtDW.CoreSubsys[0].icLoad = false;

  /* Sum: '<S4>/Sum' incorporates:
   *  Product: '<S4>/Product1'
   *  Product: '<S4>/Product3'
   *  Sum: '<S6>/Sum of Elements'
   */
  rtb_Gain_b_idx_2 = rtb_Kk1_j[0] * rtb_Gain_b_idx_3 + rtb_SumofElements[0];

  /* Update for Delay: '<S5>/Delay' incorporates:
   *  Product: '<S4>/Product1'
   *  Product: '<S4>/Product3'
   *  Sum: '<S4>/Sum'
   *  Sum: '<S6>/Sum of Elements'
   * */
  rtDW.CoreSubsys[0].Delay_DSTATE[0] = rtb_Gain_b_idx_2;
  rtDW.CoreSubsys[0].Delay_DSTATE[1] = rtb_Kk1_j[1] * rtb_Gain_b_idx_3 +
    rtb_SumofElements[1];

  /* Update for UnitDelay: '<S3>/UnitDelayP' */
  rtDW.CoreSubsys[0].UnitDelayP_DSTATE[0] = rtb_MatrixMultiply[0];
  rtDW.CoreSubsys[0].UnitDelayP_DSTATE[1] = rtb_MatrixMultiply[1];
  rtDW.CoreSubsys[0].UnitDelayP_DSTATE[2] = rtb_MatrixMultiply[2];
  rtDW.CoreSubsys[0].UnitDelayP_DSTATE[3] = rtb_MatrixMultiply[3];

  /* Outport: '<Root>/Out1' incorporates:
   *  Sum: '<S4>/Sum'
   */
  rtY.Out1 = rtb_Gain_b_idx_2;

  /* End of Outputs for SubSystem: '<Root>/SOCEstimator' */
}

/* Model initialize function */
void Final_model_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    int32_T ForEach_itr_oe;

    /* SystemInitialize for Iterator SubSystem: '<Root>/SOCEstimator' */
    /* InitializeConditions for Delay: '<S5>/Delay' */
    rtDW.CoreSubsys[0].icLoad = true;

    /* InitializeConditions for UnitDelay: '<S3>/UnitDelayP' */
    rtDW.CoreSubsys[0].UnitDelayP_DSTATE[0] = 0.1;
    rtDW.CoreSubsys[0].UnitDelayP_DSTATE[1] = 0.0;
    rtDW.CoreSubsys[0].UnitDelayP_DSTATE[2] = 0.0;
    rtDW.CoreSubsys[0].UnitDelayP_DSTATE[3] = 0.1;

    /* SystemInitialize for Iterator SubSystem: '<S6>/Statefunction' */
    for (ForEach_itr_oe = 0; ForEach_itr_oe < 5; ForEach_itr_oe++) {
      /* Start for Probe: '<S18>/Probe' */
      rtDW.CoreSubsys[0].CoreSubsys[ForEach_itr_oe].Probe[0] = 1.0;
      rtDW.CoreSubsys[0].CoreSubsys[ForEach_itr_oe].Probe[1] = 0.0;
    }

    /* End of SystemInitialize for SubSystem: '<S6>/Statefunction' */
    /* End of SystemInitialize for SubSystem: '<Root>/SOCEstimator' */
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
