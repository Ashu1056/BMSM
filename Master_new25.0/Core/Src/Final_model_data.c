/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Final_model_data.c
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

/* Constant parameters (default storage) */
const ConstP rtConstP = {
  /* Pooled Parameter (Expression: Wc)
   * Referenced by:
   *   '<S6>/updatePx'
   *   '<S6>/updatePy'
   */
  { 2.0, 0.25, 0.25, 0.25, 0.25 },

  /* Expression: Q
   * Referenced by: '<S6>/updatePx'
   */
  { 0.0001, 0.0, 0.0, 0.0001 },

  /* Pooled Parameter (Expression: Wm)
   * Referenced by:
   *   '<S11>/Constant'
   *   '<S12>/Constant'
   */
  { 0.0, 0.25, 0.25, 0.25, 0.25 },

  /* Expression: R1_mat
   * Referenced by: '<S18>/R1'
   */
  { 3.48022977971774, 0.245, 0.0666999270259672, 0.0180140680226288,
    0.0140181531096532, 0.0140607721952648, 0.0809238724554228,
    0.0170306567333334, 0.0125550942210769, 0.012555 },

  /* Expression: SOC_vec
   * Referenced by: '<S18>/R1'
   */
  { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 },

  /* Expression: C1_mat
   * Referenced by: '<S18>/C1'
   */
  { 205.2409638146494, 5020.408163265306, 14992.52015089441, 25232.804382356444,
    20381.735274209343, 24524.085976090522, 10297.744139621811,
    13344.918568401152, 15929.788855287874, 17124.651533253684 },

  /* Expression: SOC_vec
   * Referenced by: '<S18>/C1'
   */
  { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 },

  /* Expression: V0_mat
   * Referenced by: '<S16>/OCVTable'
   */
  { 2.999983, 3.6467766607160663, 3.6530466606318654, 3.7413367549608161,
    3.7736532501981848, 3.8033344796593269, 3.8286075253328868,
    3.9527665631792392, 4.0645760987361514, 4.1866769622073869 },

  /* Expression: SOC_vec
   * Referenced by: '<S16>/OCVTable'
   */
  { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 },

  /* Expression: R0_mat
   * Referenced by: '<S16>/R0Table'
   */
  { 0.00333917527740149, 0.00452925398918034, 0.00418572513080675,
    0.00405972765440584, 0.00391197065931089, 0.00378224261593977,
    0.0037489851082536, 0.0037620408037083, 0.00377984470750823, 0.003785 },

  /* Expression: SOC_vec
   * Referenced by: '<S16>/R0Table'
   */
  { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 },

  /* Expression: diag(Wc)
   * Referenced by: '<S6>/Constant'
   */
  { 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.25, 0.0, 0.0, 0.0, 0.0, 0.0, 0.25, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.25, 0.0, 0.0, 0.0, 0.0, 0.0, 0.25 }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
