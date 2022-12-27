/*
 * observe_2021a.c
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
#include "observe_2021a_dt.h"

/* options for Simulink Desktop Real-Time board 0 */
static double SLDRTBoardOptions0[] = {
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
};

/* list of Simulink Desktop Real-Time timers */
const int SLDRTTimerCount = 1;
const double SLDRTTimers[2] = {
  0.001, 0.0,
};

/* list of Simulink Desktop Real-Time boards */
const int SLDRTBoardCount = 1;
SLDRTBOARD SLDRTBoards[1] = {
  { "National_Instruments/PCIe-6361", 4294967295U, 7, SLDRTBoardOptions0 },
};

/* Block signals (default storage) */
B_observe_2021a_T observe_2021a_B;

/* Continuous states */
X_observe_2021a_T observe_2021a_X;

/* Block states (default storage) */
DW_observe_2021a_T observe_2021a_DW;

/* Real-time model */
static RT_MODEL_observe_2021a_T observe_2021a_M_;
RT_MODEL_observe_2021a_T *const observe_2021a_M = &observe_2021a_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  observe_2021a_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  observe_2021a_output();
  observe_2021a_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  observe_2021a_output();
  observe_2021a_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T tmp;
  real_T tmp_0;
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/* Model output function */
void observe_2021a_output(void)
{
  real_T t111;
  real_T t112;
  real_T t118;
  real_T t118_tmp;
  real_T t118_tmp_0;
  real_T t118_tmp_1;
  real_T t2;
  real_T t31;
  real_T t32;
  real_T t34;
  real_T t39;
  real_T t4;
  real_T t41;
  real_T t42;
  real_T t43;
  real_T t45;
  real_T t48;
  real_T t50;
  real_T t51;
  real_T t52;
  real_T t6;
  if (rtmIsMajorTimeStep(observe_2021a_M)) {
    /* set solver stop time */
    if (!(observe_2021a_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&observe_2021a_M->solverInfo,
                            ((observe_2021a_M->Timing.clockTickH0 + 1) *
        observe_2021a_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&observe_2021a_M->solverInfo,
                            ((observe_2021a_M->Timing.clockTick0 + 1) *
        observe_2021a_M->Timing.stepSize0 + observe_2021a_M->Timing.clockTickH0 *
        observe_2021a_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(observe_2021a_M)) {
    observe_2021a_M->Timing.t[0] = rtsiGetT(&observe_2021a_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(observe_2021a_M)) {
    /* S-Function (sldrtai): '<Root>/Analog Input1' */
    /* S-Function Block: <Root>/Analog Input1 */
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) observe_2021a_P.AnalogInput1_RangeMode;
      parm.rangeidx = observe_2021a_P.AnalogInput1_VoltRange;
      RTBIO_DriverIO(0, ANALOGINPUT, IOREAD, 4,
                     observe_2021a_P.AnalogInput1_Channels,
                     &observe_2021a_B.AnalogInput1[0], &parm);
    }

    /* MATLAB Function: '<S1>/MATLAB Function1' */
    observe_2021a_B.y[0] = (observe_2021a_B.AnalogInput1[0] - 5.0) * -5.0;
    observe_2021a_B.y[1] = (observe_2021a_B.AnalogInput1[1] - 5.0) * -5.0;
    observe_2021a_B.y[2] = (observe_2021a_B.AnalogInput1[2] - 5.0) * -5.0;

    /* MATLAB Function: '<S1>/autogen_Z2p1' */
    t2 = observe_2021a_B.y[0] * observe_2021a_B.y[0];
    t4 = observe_2021a_B.y[1] * observe_2021a_B.y[1];
    t6 = observe_2021a_B.y[2] * observe_2021a_B.y[2];
    t39 = observe_2021a_B.y[0] * 4.8999911281101E+13;
    t41 = observe_2021a_B.y[2] * 4.7733218776365E+13;
    t48 = observe_2021a_B.y[1] * 4.6020599945112E+13;
    t31 = observe_2021a_B.y[0] * t6 * 4.567884E+10;
    t32 = observe_2021a_B.y[2] * t2 * 4.567884E+10;
    t34 = rt_powd_snf(observe_2021a_B.y[0], 3.0) * 9.466641E+10;
    t42 = observe_2021a_B.y[1] * t6 * 5.176061E+10;
    t43 = observe_2021a_B.y[2] * t4 * 5.176061E+10;
    t45 = rt_powd_snf(observe_2021a_B.y[1], 3.0) * 1.0074818E+11;
    t50 = rt_powd_snf(observe_2021a_B.y[2], 3.0) * 9.743945E+10;
    t51 = observe_2021a_B.y[0] * t4 * 4.898757E+10;
    t52 = observe_2021a_B.y[1] * t2 * 4.898757E+10;
    t118_tmp = observe_2021a_B.y[1] * observe_2021a_B.y[2];
    t118_tmp_0 = observe_2021a_B.y[0] * observe_2021a_B.y[2];
    t118_tmp_1 = observe_2021a_B.y[0] * observe_2021a_B.y[1];
    t118 = (((((-(t118_tmp * 1.0352122E+11) + t2 * 9.466641E+10) + -(t118_tmp_0 *
                9.135768E+10)) + t4 * 1.0074818E+11) + t6 * 9.743945E+10) +
            -(t118_tmp_1 * 9.797514E+10)) + 7.1376865001289E+13;
    t111 = ((t2 * 3.21E+6 + t6 * 2.576E+7) + -(t4 * 2.897E+7)) - 2.275477497E+9;
    t112 = ((t4 * 1.297E+7 + t6 * 1.763E+7) + -(t2 * 3.06E+7)) +
      3.0399800799E+10;
    t4 = 1.0 / ((((((t4 * 2.0149636E+11 + t2 * 1.8933282E+11) + -(t118_tmp *
      2.0704244E+11)) + t6 * 1.948789E+11) + -(t118_tmp_0 * 1.8271536E+11)) +
                 -(t118_tmp_1 * 1.9595028E+11)) + 1.42753730002578E+14);
    t6 = (((observe_2021a_B.y[0] * 321.0 + observe_2021a_B.y[2] * 2576.0) +
           -(observe_2021a_B.y[1] * 2897.0)) * t111 + observe_2021a_B.y[0] *
          1.42753730002578E+14) + ((observe_2021a_B.y[1] * 1297.0 +
      observe_2021a_B.y[2] * 1763.0) + -(observe_2021a_B.y[0] * 3060.0)) * t112;
    t2 = sqrt(-((((t2 * 2.85507460005156E+18 + t111 * t111) + t112 * t112) -
                 2.5695671400464038E+21) * t118) + t6 * t6 * 10000.0) / 100.0;
    t6 = ((((((((((((-t31 - t32) + t34) + t39) + t41) - t42) - t43) + t45) + t48)
             + t50) - t51) - t52) + t2) * t4 + 30.0;
    if (!(t6 > 0.0)) {
      t6 = ((((((((((((t31 + t32) - t34) - t39) - t41) + t42) + t43) - t45) -
                t48) - t50) + t51) + t52) + t2) * -t4 + 30.0;
    }

    /* End of MATLAB Function: '<S1>/autogen_Z2p1' */

    /* Gain: '<S1>/Gain2' incorporates:
     *  Constant: '<S1>/Constant2'
     *  Sum: '<S1>/Sum4'
     */
    observe_2021a_B.Gain2 = (observe_2021a_P.Constant2_Value - t6) *
      observe_2021a_P.Gain2_Gain;

    /* Sum: '<Root>/Sum8' incorporates:
     *  Constant: '<Root>/Constant6'
     */
    observe_2021a_B.Sum8 = observe_2021a_B.Gain2 - observe_2021a_P.y0;

    /* MATLAB Function: '<S1>/Current1' */
    observe_2021a_B.y_b = 0.4831460674157303 * observe_2021a_B.AnalogInput1[3];

    /* Sum: '<Root>/Sum9' incorporates:
     *  Constant: '<Root>/Constant7'
     */
    observe_2021a_B.Sum9 = observe_2021a_B.y_b - observe_2021a_P.I0;
  }

  /* TransferFcn: '<Root>/Transfer Fcn' */
  observe_2021a_B.TransferFcn = 0.0;
  observe_2021a_B.TransferFcn += observe_2021a_P.TransferFcn_C[0] *
    observe_2021a_X.TransferFcn_CSTATE[0];
  observe_2021a_B.TransferFcn += observe_2021a_P.TransferFcn_C[1] *
    observe_2021a_X.TransferFcn_CSTATE[1];

  /* Sum: '<Root>/Sum7' incorporates:
   *  Constant: '<Root>/Constant5'
   *  Gain: '<Root>/Gain2'
   *  SignalConversion generated from: '<Root>/Gain2'
   */
  observe_2021a_B.Sum7 = ((-observe_2021a_P.K[0] * observe_2021a_B.Sum8 +
    -observe_2021a_P.K[1] * observe_2021a_B.TransferFcn) + -observe_2021a_P.K[2]
    * observe_2021a_B.Sum9) + observe_2021a_P.V0;

  /* Gain: '<S2>/Gain3' */
  t2 = observe_2021a_P.Gain3_Gain * observe_2021a_B.Sum7;

  /* Step: '<S2>/Step1' */
  if (observe_2021a_M->Timing.t[0] < observe_2021a_P.Step1_Time) {
    t4 = observe_2021a_P.Step1_Y0;
  } else {
    t4 = observe_2021a_P.Step1_YFinal;
  }

  /* End of Step: '<S2>/Step1' */

  /* Saturate: '<S2>/Saturation1' */
  if (t2 > observe_2021a_P.Saturation1_UpperSat) {
    t2 = observe_2021a_P.Saturation1_UpperSat;
  } else if (t2 < observe_2021a_P.Saturation1_LowerSat) {
    t2 = observe_2021a_P.Saturation1_LowerSat;
  }

  /* End of Saturate: '<S2>/Saturation1' */

  /* Product: '<S2>/Matrix Multiply1' */
  observe_2021a_B.MatrixMultiply1 = t4 * t2;
  if (rtmIsMajorTimeStep(observe_2021a_M)) {
    /* S-Function (sldrtao): '<Root>/Analog Output1' */
    /* S-Function Block: <Root>/Analog Output1 */
    {
      {
        ANALOGIOPARM parm;
        parm.mode = (RANGEMODE) observe_2021a_P.AnalogOutput1_RangeMode;
        parm.rangeidx = observe_2021a_P.AnalogOutput1_VoltRange;
        RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                       &observe_2021a_P.AnalogOutput1_Channels, ((real_T*)
          (&observe_2021a_B.MatrixMultiply1)), &parm);
      }
    }
  }
}

/* Model update function */
void observe_2021a_update(void)
{
  if (rtmIsMajorTimeStep(observe_2021a_M)) {
    rt_ertODEUpdateContinuousStates(&observe_2021a_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++observe_2021a_M->Timing.clockTick0)) {
    ++observe_2021a_M->Timing.clockTickH0;
  }

  observe_2021a_M->Timing.t[0] = rtsiGetSolverStopTime
    (&observe_2021a_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++observe_2021a_M->Timing.clockTick1)) {
      ++observe_2021a_M->Timing.clockTickH1;
    }

    observe_2021a_M->Timing.t[1] = observe_2021a_M->Timing.clockTick1 *
      observe_2021a_M->Timing.stepSize1 + observe_2021a_M->Timing.clockTickH1 *
      observe_2021a_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void observe_2021a_derivatives(void)
{
  XDot_observe_2021a_T *_rtXdot;
  _rtXdot = ((XDot_observe_2021a_T *) observe_2021a_M->derivs);

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE[0] = 0.0;
  _rtXdot->TransferFcn_CSTATE[0] += observe_2021a_P.TransferFcn_A[0] *
    observe_2021a_X.TransferFcn_CSTATE[0];
  _rtXdot->TransferFcn_CSTATE[1] = 0.0;
  _rtXdot->TransferFcn_CSTATE[0] += observe_2021a_P.TransferFcn_A[1] *
    observe_2021a_X.TransferFcn_CSTATE[1];
  _rtXdot->TransferFcn_CSTATE[1] += observe_2021a_X.TransferFcn_CSTATE[0];
  _rtXdot->TransferFcn_CSTATE[0] += observe_2021a_B.Gain2;
}

/* Model initialize function */
void observe_2021a_initialize(void)
{
  /* Start for S-Function (sldrtao): '<Root>/Analog Output1' */

  /* S-Function Block: <Root>/Analog Output1 */

  /* no initial value should be set */

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  observe_2021a_X.TransferFcn_CSTATE[0] = 0.0;
  observe_2021a_X.TransferFcn_CSTATE[1] = 0.0;
}

/* Model terminate function */
void observe_2021a_terminate(void)
{
  /* Terminate for S-Function (sldrtao): '<Root>/Analog Output1' */

  /* S-Function Block: <Root>/Analog Output1 */

  /* no final value should be set */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  observe_2021a_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  observe_2021a_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  observe_2021a_initialize();
}

void MdlTerminate(void)
{
  observe_2021a_terminate();
}

/* Registration function */
RT_MODEL_observe_2021a_T *observe_2021a(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)observe_2021a_M, 0,
                sizeof(RT_MODEL_observe_2021a_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&observe_2021a_M->solverInfo,
                          &observe_2021a_M->Timing.simTimeStep);
    rtsiSetTPtr(&observe_2021a_M->solverInfo, &rtmGetTPtr(observe_2021a_M));
    rtsiSetStepSizePtr(&observe_2021a_M->solverInfo,
                       &observe_2021a_M->Timing.stepSize0);
    rtsiSetdXPtr(&observe_2021a_M->solverInfo, &observe_2021a_M->derivs);
    rtsiSetContStatesPtr(&observe_2021a_M->solverInfo, (real_T **)
                         &observe_2021a_M->contStates);
    rtsiSetNumContStatesPtr(&observe_2021a_M->solverInfo,
      &observe_2021a_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&observe_2021a_M->solverInfo,
      &observe_2021a_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&observe_2021a_M->solverInfo,
      &observe_2021a_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&observe_2021a_M->solverInfo,
      &observe_2021a_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&observe_2021a_M->solverInfo, (&rtmGetErrorStatus
      (observe_2021a_M)));
    rtsiSetRTModelPtr(&observe_2021a_M->solverInfo, observe_2021a_M);
  }

  rtsiSetSimTimeStep(&observe_2021a_M->solverInfo, MAJOR_TIME_STEP);
  observe_2021a_M->intgData.y = observe_2021a_M->odeY;
  observe_2021a_M->intgData.f[0] = observe_2021a_M->odeF[0];
  observe_2021a_M->intgData.f[1] = observe_2021a_M->odeF[1];
  observe_2021a_M->intgData.f[2] = observe_2021a_M->odeF[2];
  observe_2021a_M->contStates = ((real_T *) &observe_2021a_X);
  rtsiSetSolverData(&observe_2021a_M->solverInfo, (void *)
                    &observe_2021a_M->intgData);
  rtsiSetSolverName(&observe_2021a_M->solverInfo,"ode3");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = observe_2021a_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    observe_2021a_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    observe_2021a_M->Timing.sampleTimes =
      (&observe_2021a_M->Timing.sampleTimesArray[0]);
    observe_2021a_M->Timing.offsetTimes =
      (&observe_2021a_M->Timing.offsetTimesArray[0]);

    /* task periods */
    observe_2021a_M->Timing.sampleTimes[0] = (0.0);
    observe_2021a_M->Timing.sampleTimes[1] = (0.001);

    /* task offsets */
    observe_2021a_M->Timing.offsetTimes[0] = (0.0);
    observe_2021a_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(observe_2021a_M, &observe_2021a_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = observe_2021a_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    observe_2021a_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(observe_2021a_M, 15.0);
  observe_2021a_M->Timing.stepSize0 = 0.001;
  observe_2021a_M->Timing.stepSize1 = 0.001;

  /* External mode info */
  observe_2021a_M->Sizes.checksums[0] = (574974362U);
  observe_2021a_M->Sizes.checksums[1] = (2076806378U);
  observe_2021a_M->Sizes.checksums[2] = (221886507U);
  observe_2021a_M->Sizes.checksums[3] = (1654532737U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[4];
    observe_2021a_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(observe_2021a_M->extModeInfo,
      &observe_2021a_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(observe_2021a_M->extModeInfo,
                        observe_2021a_M->Sizes.checksums);
    rteiSetTPtr(observe_2021a_M->extModeInfo, rtmGetTPtr(observe_2021a_M));
  }

  observe_2021a_M->solverInfoPtr = (&observe_2021a_M->solverInfo);
  observe_2021a_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&observe_2021a_M->solverInfo, 0.001);
  rtsiSetSolverMode(&observe_2021a_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  observe_2021a_M->blockIO = ((void *) &observe_2021a_B);
  (void) memset(((void *) &observe_2021a_B), 0,
                sizeof(B_observe_2021a_T));

  /* parameters */
  observe_2021a_M->defaultParam = ((real_T *)&observe_2021a_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &observe_2021a_X;
    observe_2021a_M->contStates = (x);
    (void) memset((void *)&observe_2021a_X, 0,
                  sizeof(X_observe_2021a_T));
  }

  /* states (dwork) */
  observe_2021a_M->dwork = ((void *) &observe_2021a_DW);
  (void) memset((void *)&observe_2021a_DW, 0,
                sizeof(DW_observe_2021a_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    observe_2021a_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  observe_2021a_M->Sizes.numContStates = (2);/* Number of continuous states */
  observe_2021a_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  observe_2021a_M->Sizes.numY = (0);   /* Number of model outputs */
  observe_2021a_M->Sizes.numU = (0);   /* Number of model inputs */
  observe_2021a_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  observe_2021a_M->Sizes.numSampTimes = (2);/* Number of sample times */
  observe_2021a_M->Sizes.numBlocks = (34);/* Number of blocks */
  observe_2021a_M->Sizes.numBlockIO = (9);/* Number of block outputs */
  observe_2021a_M->Sizes.numBlockPrms = (31);/* Sum of parameter "widths" */
  return observe_2021a_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
