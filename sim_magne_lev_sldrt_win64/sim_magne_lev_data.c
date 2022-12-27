/*
 * sim_magne_lev_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "sim_magne_lev".
 *
 * Model version              : 1.78
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Wed Jun 22 18:22:51 2022
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "sim_magne_lev.h"
#include "sim_magne_lev_private.h"

/* Block parameters (default storage) */
P_sim_magne_lev_T sim_magne_lev_P = {
  /* Mask Parameter: AnalogInput2_MaxMissedTicks
   * Referenced by: '<Root>/Analog Input2'
   */
  10.0,

  /* Mask Parameter: AnalogOutput_MaxMissedTicks
   * Referenced by: '<Root>/Analog Output'
   */
  10.0,

  /* Mask Parameter: AnalogInput2_YieldWhenWaiting
   * Referenced by: '<Root>/Analog Input2'
   */
  0.0,

  /* Mask Parameter: AnalogOutput_YieldWhenWaiting
   * Referenced by: '<Root>/Analog Output'
   */
  0.0,

  /* Mask Parameter: AnalogInput2_Channels
   * Referenced by: '<Root>/Analog Input2'
   */
  { 0, 1, 2, 4 },

  /* Mask Parameter: AnalogOutput_Channels
   * Referenced by: '<Root>/Analog Output'
   */
  0,

  /* Mask Parameter: AnalogInput2_RangeMode
   * Referenced by: '<Root>/Analog Input2'
   */
  0,

  /* Mask Parameter: AnalogOutput_RangeMode
   * Referenced by: '<Root>/Analog Output'
   */
  0,

  /* Mask Parameter: AnalogInput2_VoltRange
   * Referenced by: '<Root>/Analog Input2'
   */
  0,

  /* Mask Parameter: AnalogOutput_VoltRange
   * Referenced by: '<Root>/Analog Output'
   */
  0,

  /* Expression: 15
   * Referenced by: '<Root>/Step'
   */
  15.0,

  /* Expression: 1
   * Referenced by: '<Root>/Step'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/Step'
   */
  0.0,

  /* Expression: 92.3
   * Referenced by: '<Root>/Constant'
   */
  92.3,

  /* Expression: 1e-3
   * Referenced by: '<Root>/Gain'
   */
  0.001,

  /* Computed Parameter: TransferFcn_A
   * Referenced by: '<Root>/Transfer Fcn'
   */
  -2000.0,

  /* Computed Parameter: TransferFcn_C
   * Referenced by: '<Root>/Transfer Fcn'
   */
  -4.0E+6,

  /* Computed Parameter: TransferFcn_D
   * Referenced by: '<Root>/Transfer Fcn'
   */
  2000.0,

  /* Expression: 0.2
   * Referenced by: '<Root>/Gain2'
   */
  0.2,

  /* Expression: 0.01
   * Referenced by: '<Root>/Gain1'
   */
  0.01,

  /* Expression: 0.04
   * Referenced by: '<Root>/Constant1'
   */
  0.04,

  /* Expression: 10
   * Referenced by: '<Root>/Saturation'
   */
  10.0,

  /* Expression: -10
   * Referenced by: '<Root>/Saturation'
   */
  -10.0
};
