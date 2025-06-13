/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Final_model.h
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

#ifndef RTW_HEADER_Final_model_h_
#define RTW_HEADER_Final_model_h_
#ifndef Final_model_COMMON_INCLUDES_
#define Final_model_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Final_model_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<S6>/Statefunction' */
typedef struct {
  real_T Probe[2];                     /* '<S18>/Probe' */
  uint32_T m_bpIndex;                  /* '<S18>/R1' */
  uint32_T m_bpIndex_k;                /* '<S18>/C1' */
} DW_CoreSubsys_d;

/* Block signals and states (default storage) for system '<S6>/Measurementfunction' */
typedef struct {
  uint32_T m_bpIndex;                  /* '<S16>/OCVTable' */
  uint32_T m_bpIndex_l;                /* '<S16>/R0Table' */
} DW_CoreSubsys_dg;

/* Block signals and states (default storage) for system '<Root>/SOCEstimator' */
typedef struct {
  DW_CoreSubsys_dg CoreSubsys_b[5];    /* '<S6>/Measurementfunction' */
  DW_CoreSubsys_d CoreSubsys[5];       /* '<S6>/Statefunction' */
  real_T Assignment2[10];              /* '<S7>/Assignment2' */
  real_T ImpAsg_InsertedFor_xk1_at_inpor[10];/* '<S12>/Statefunction' */
  real_T Delay_DSTATE[2];              /* '<S5>/Delay' */
  real_T UnitDelayP_DSTATE[4];         /* '<S3>/UnitDelayP' */
  boolean_T icLoad;                    /* '<S5>/Delay' */
} DW_CoreSubsys;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_CoreSubsys CoreSubsys[1];         /* '<Root>/SOCEstimator' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: Wc)
   * Referenced by:
   *   '<S6>/updatePx'
   *   '<S6>/updatePy'
   */
  real_T pooled1[5];

  /* Expression: Q
   * Referenced by: '<S6>/updatePx'
   */
  real_T updatePx_Q[4];

  /* Pooled Parameter (Expression: Wm)
   * Referenced by:
   *   '<S11>/Constant'
   *   '<S12>/Constant'
   */
  real_T pooled2[5];

  /* Expression: R1_mat
   * Referenced by: '<S18>/R1'
   */
  real_T R1_tableData[10];

  /* Expression: SOC_vec
   * Referenced by: '<S18>/R1'
   */
  real_T R1_bp01Data[10];

  /* Expression: C1_mat
   * Referenced by: '<S18>/C1'
   */
  real_T C1_tableData[10];

  /* Expression: SOC_vec
   * Referenced by: '<S18>/C1'
   */
  real_T C1_bp01Data[10];

  /* Expression: V0_mat
   * Referenced by: '<S16>/OCVTable'
   */
  real_T OCVTable_tableData[10];

  /* Expression: SOC_vec
   * Referenced by: '<S16>/OCVTable'
   */
  real_T OCVTable_bp01Data[10];

  /* Expression: R0_mat
   * Referenced by: '<S16>/R0Table'
   */
  real_T R0Table_tableData[10];

  /* Expression: SOC_vec
   * Referenced by: '<S16>/R0Table'
   */
  real_T R0Table_bp01Data[10];

  /* Expression: diag(Wc)
   * Referenced by: '<S6>/Constant'
   */
  real_T Constant_Value[25];
} ConstP;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Input;                        /* '<Root>/Input' */
  real_T Input1;                       /* '<Root>/Input1' */
  real_T Input2;                       /* '<Root>/Input2' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Out1;                         /* '<Root>/Out1' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void Final_model_initialize(void);
extern void Final_model_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S9>/Data Type Duplicate' : Unused code path elimination
 * Block '<S10>/Data Type Duplicate' : Unused code path elimination
 * Block '<S15>/Data Type Duplicate' : Unused code path elimination
 * Block '<S17>/Data Type Duplicate' : Unused code path elimination
 * Block '<S19>/Data Type Duplicate' : Unused code path elimination
 * Block '<S20>/Data Type Duplicate' : Unused code path elimination
 * Block '<S9>/Conversion' : Eliminate redundant data type conversion
 * Block '<S10>/Conversion' : Eliminate redundant data type conversion
 * Block '<S15>/Conversion' : Eliminate redundant data type conversion
 * Block '<S17>/Conversion' : Eliminate redundant data type conversion
 * Block '<S3>/Rate Transition' : Eliminated since input and output rates are identical
 * Block '<S3>/Rate Transition1' : Eliminated since input and output rates are identical
 * Block '<S3>/Rate Transition3' : Eliminated since input and output rates are identical
 * Block '<S3>/Reshape' : Reshape block reduction
 * Block '<S19>/Conversion' : Eliminate redundant data type conversion
 * Block '<S20>/Conversion' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Final_model'
 * '<S1>'   : 'Final_model/SOCEstimator'
 * '<S2>'   : 'Final_model/SOCEstimator/KalmanFilter'
 * '<S3>'   : 'Final_model/SOCEstimator/KalmanFilter/UKF'
 * '<S4>'   : 'Final_model/SOCEstimator/KalmanFilter/UKF/Correction'
 * '<S5>'   : 'Final_model/SOCEstimator/KalmanFilter/UKF/DelayX'
 * '<S6>'   : 'Final_model/SOCEstimator/KalmanFilter/UKF/Prediction'
 * '<S7>'   : 'Final_model/SOCEstimator/KalmanFilter/UKF/Sigmapoints'
 * '<S8>'   : 'Final_model/SOCEstimator/KalmanFilter/UKF/Correction/updatePk'
 * '<S9>'   : 'Final_model/SOCEstimator/KalmanFilter/UKF/DelayX/Data Type Conversion Inherited'
 * '<S10>'  : 'Final_model/SOCEstimator/KalmanFilter/UKF/Prediction/Data Type Conversion Inherited'
 * '<S11>'  : 'Final_model/SOCEstimator/KalmanFilter/UKF/Prediction/Measurementfunction'
 * '<S12>'  : 'Final_model/SOCEstimator/KalmanFilter/UKF/Prediction/Statefunction'
 * '<S13>'  : 'Final_model/SOCEstimator/KalmanFilter/UKF/Prediction/updatePx'
 * '<S14>'  : 'Final_model/SOCEstimator/KalmanFilter/UKF/Prediction/updatePy'
 * '<S15>'  : 'Final_model/SOCEstimator/KalmanFilter/UKF/Prediction/Measurementfunction/Data Type Conversion Inherited'
 * '<S16>'  : 'Final_model/SOCEstimator/KalmanFilter/UKF/Prediction/Measurementfunction/Measurementfunction'
 * '<S17>'  : 'Final_model/SOCEstimator/KalmanFilter/UKF/Prediction/Statefunction/Data Type Conversion Inherited'
 * '<S18>'  : 'Final_model/SOCEstimator/KalmanFilter/UKF/Prediction/Statefunction/Statefunction'
 * '<S19>'  : 'Final_model/SOCEstimator/KalmanFilter/UKF/Sigmapoints/Data Type Conversion Inherited'
 * '<S20>'  : 'Final_model/SOCEstimator/KalmanFilter/UKF/Sigmapoints/Data Type Conversion Inherited1'
 */
#endif                                 /* RTW_HEADER_Final_model_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
