/*
 * observe_2021a_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "observe_2021a".
 *
 * Model version              : 1.8
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Mon Jun 20 19:39:53 2022
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "observe_2021a.h"
#include "observe_2021a_private.h"

/* Block parameters (default storage) */
P_observe_2021a_T observe_2021a_P = {
  /* Variable: I0
   * Referenced by: '<Root>/Constant7'
   */
  0.88544371307547154,

  /* Variable: K
   * Referenced by: '<Root>/Gain2'
   */
  { -906.48798173901912, -115.56294987514484, -6.3600000000008556 },

  /* Variable: V0
   * Referenced by: '<Root>/Constant5'
   */
  28.050856830230938,

  /* Variable: y0
   * Referenced by: '<Root>/Constant6'
   */
  0.03,

  /* Mask Parameter: AnalogInput1_MaxMissedTicks
   * Referenced by: '<Root>/Analog Input1'
   */
  10.0,

  /* Mask Parameter: AnalogOutput1_MaxMissedTicks
   * Referenced by: '<Root>/Analog Output1'
   */
  10.0,

  /* Mask Parameter: AnalogInput1_YieldWhenWaiting
   * Referenced by: '<Root>/Analog Input1'
   */
  0.0,

  /* Mask Parameter: AnalogOutput1_YieldWhenWaiting
   * Referenced by: '<Root>/Analog Output1'
   */
  0.0,

  /* Mask Parameter: AnalogInput1_Channels
   * Referenced by: '<Root>/Analog Input1'
   */
  { 0, 1, 2, 4 },

  /* Mask Parameter: AnalogOutput1_Channels
   * Referenced by: '<Root>/Analog Output1'
   */
  0,

  /* Mask Parameter: AnalogInput1_RangeMode
   * Referenced by: '<Root>/Analog Input1'
   */
  0,

  /* Mask Parameter: AnalogOutput1_RangeMode
   * Referenced by: '<Root>/Analog Output1'
   */
  0,

  /* Mask Parameter: AnalogInput1_VoltRange
   * Referenced by: '<Root>/Analog Input1'
   */
  0,

  /* Mask Parameter: AnalogOutput1_VoltRange
   * Referenced by: '<Root>/Analog Output1'
   */
  0,

  /* Expression: 10
   * Referenced by: '<S2>/Step1'
   */
  10.0,

  /* Expression: 1
   * Referenced by: '<S2>/Step1'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S2>/Step1'
   */
  0.0,

  /* Expression: 92.9
   * Referenced by: '<S1>/Constant2'
   */
  92.9,

  /* Expression: 1e-3
   * Referenced by: '<S1>/Gain2'
   */
  0.001,

  /* Computed Parameter: TransferFcn_A
   * Referenced by: '<Root>/Transfer Fcn'
   */
  { -4000.0, -4.0E+6 },

  /* Computed Parameter: TransferFcn_C
   * Referenced by: '<Root>/Transfer Fcn'
   */
  { 2000.0, 0.0 },

  /* Expression: 1/5.5
   * Referenced by: '<S2>/Gain3'
   */
  0.18181818181818182,

  /* Expression: 10
   * Referenced by: '<S2>/Saturation1'
   */
  10.0,

  /* Expression: -10
   * Referenced by: '<S2>/Saturation1'
   */
  -10.0
};
