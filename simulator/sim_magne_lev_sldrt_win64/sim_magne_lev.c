/*
 * sim_magne_lev.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "sim_magne_lev".
 *
 * Model version              : 1.76
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Thu Jun  9 16:22:40 2022
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "sim_magne_lev.h"
#include "sim_magne_lev_private.h"
#include "sim_magne_lev_dt.h"

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
B_sim_magne_lev_T sim_magne_lev_B;

/* Continuous states */
X_sim_magne_lev_T sim_magne_lev_X;

/* Block states (default storage) */
DW_sim_magne_lev_T sim_magne_lev_DW;

/* Real-time model */
static RT_MODEL_sim_magne_lev_T sim_magne_lev_M_;
RT_MODEL_sim_magne_lev_T *const sim_magne_lev_M = &sim_magne_lev_M_;

/* Forward declaration for local functions */
static void sim_magne_lev_asinh(real_T *x);

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
  int_T nXc = 1;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  sim_magne_lev_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  sim_magne_lev_output();
  sim_magne_lev_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  sim_magne_lev_output();
  sim_magne_lev_derivatives();

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

/* Function for MATLAB Function: '<Root>/autogen_Z2p1' */
static void sim_magne_lev_asinh(real_T *x)
{
  real_T t;
  real_T z;
  boolean_T xneg;
  xneg = (*x < 0.0);
  if (xneg) {
    *x = -*x;
  }

  if (*x >= 2.68435456E+8) {
    *x = log(*x) + 0.69314718055994529;
  } else if (*x > 2.0) {
    *x = log(1.0 / (sqrt(*x * *x + 1.0) + *x) + 2.0 * *x);
  } else {
    t = *x * *x;
    z = t / (sqrt(t + 1.0) + 1.0) + *x;
    *x = z;
    t = fabs(z);
    if ((t > 4.503599627370496E+15) || (rtIsInf(z) || rtIsNaN(z))) {
      *x = log(z + 1.0);
    } else if (!(t < 2.2204460492503131E-16)) {
      *x = z / ((z + 1.0) - 1.0) * log(z + 1.0);
    }
  }

  if (xneg) {
    *x = -*x;
  }
}

/* Model output function */
void sim_magne_lev_output(void)
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
  if (rtmIsMajorTimeStep(sim_magne_lev_M)) {
    /* set solver stop time */
    if (!(sim_magne_lev_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&sim_magne_lev_M->solverInfo,
                            ((sim_magne_lev_M->Timing.clockTickH0 + 1) *
        sim_magne_lev_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&sim_magne_lev_M->solverInfo,
                            ((sim_magne_lev_M->Timing.clockTick0 + 1) *
        sim_magne_lev_M->Timing.stepSize0 + sim_magne_lev_M->Timing.clockTickH0 *
        sim_magne_lev_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(sim_magne_lev_M)) {
    sim_magne_lev_M->Timing.t[0] = rtsiGetT(&sim_magne_lev_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(sim_magne_lev_M)) {
    /* S-Function (sldrtai): '<Root>/Analog Input2' */
    /* S-Function Block: <Root>/Analog Input2 */
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) sim_magne_lev_P.AnalogInput2_RangeMode;
      parm.rangeidx = sim_magne_lev_P.AnalogInput2_VoltRange;
      RTBIO_DriverIO(0, ANALOGINPUT, IOREAD, 4,
                     sim_magne_lev_P.AnalogInput2_Channels,
                     &sim_magne_lev_B.AnalogInput2[0], &parm);
    }

    /* MATLAB Function: '<Root>/Current' */
    sim_magne_lev_B.y_k = 0.4831460674157303 * sim_magne_lev_B.AnalogInput2[3];

    /* MATLAB Function: '<Root>/MATLAB Function' */
    sim_magne_lev_B.y[0] = (sim_magne_lev_B.AnalogInput2[0] - 5.0) * -5.0;
    sim_magne_lev_B.y[1] = (sim_magne_lev_B.AnalogInput2[1] - 5.0) * -5.0;
    sim_magne_lev_B.y[2] = (sim_magne_lev_B.AnalogInput2[2] - 5.0) * -5.0;

    /* MATLAB Function: '<Root>/autogen_Z2p' */
    t2 = sim_magne_lev_B.y[0] * sim_magne_lev_B.y[0];
    t4 = sim_magne_lev_B.y[1] * sim_magne_lev_B.y[1];
    t6 = sim_magne_lev_B.y[2] * sim_magne_lev_B.y[2];
    t39 = sim_magne_lev_B.y[0] * 4.8999911281101E+13;
    t41 = sim_magne_lev_B.y[2] * 4.7733218776365E+13;
    t48 = sim_magne_lev_B.y[1] * 4.6020599945112E+13;
    t31 = sim_magne_lev_B.y[0] * t6 * 4.567884E+10;
    t32 = sim_magne_lev_B.y[2] * t2 * 4.567884E+10;
    t34 = rt_powd_snf(sim_magne_lev_B.y[0], 3.0) * 9.466641E+10;
    t42 = sim_magne_lev_B.y[1] * t6 * 5.176061E+10;
    t43 = sim_magne_lev_B.y[2] * t4 * 5.176061E+10;
    t45 = rt_powd_snf(sim_magne_lev_B.y[1], 3.0) * 1.0074818E+11;
    t50 = rt_powd_snf(sim_magne_lev_B.y[2], 3.0) * 9.743945E+10;
    t51 = sim_magne_lev_B.y[0] * t4 * 4.898757E+10;
    t52 = sim_magne_lev_B.y[1] * t2 * 4.898757E+10;
    t118_tmp = sim_magne_lev_B.y[1] * sim_magne_lev_B.y[2];
    t118_tmp_0 = sim_magne_lev_B.y[0] * sim_magne_lev_B.y[2];
    t118_tmp_1 = sim_magne_lev_B.y[0] * sim_magne_lev_B.y[1];
    t118 = (((((-(t118_tmp * 1.0352122E+11) + t2 * 9.466641E+10) + -(t118_tmp_0 *
                9.135768E+10)) + t4 * 1.0074818E+11) + t6 * 9.743945E+10) +
            -(t118_tmp_1 * 9.797514E+10)) + 7.1376865001289E+13;
    t111 = ((t2 * 3.21E+6 + t6 * 2.576E+7) + -(t4 * 2.897E+7)) - 2.275477497E+9;
    t112 = ((t4 * 1.297E+7 + t6 * 1.763E+7) + -(t2 * 3.06E+7)) +
      3.0399800799E+10;
    t4 = 1.0 / ((((((t4 * 2.0149636E+11 + t2 * 1.8933282E+11) + -(t118_tmp *
      2.0704244E+11)) + t6 * 1.948789E+11) + -(t118_tmp_0 * 1.8271536E+11)) +
                 -(t118_tmp_1 * 1.9595028E+11)) + 1.42753730002578E+14);
    t6 = (((sim_magne_lev_B.y[0] * 321.0 + sim_magne_lev_B.y[2] * 2576.0) +
           -(sim_magne_lev_B.y[1] * 2897.0)) * t111 + sim_magne_lev_B.y[0] *
          1.42753730002578E+14) + ((sim_magne_lev_B.y[1] * 1297.0 +
      sim_magne_lev_B.y[2] * 1763.0) + -(sim_magne_lev_B.y[0] * 3060.0)) * t112;
    t2 = sqrt(-((((t2 * 2.85507460005156E+18 + t111 * t111) + t112 * t112) -
                 2.5695671400464038E+21) * t118) + t6 * t6 * 10000.0) / 100.0;
    t6 = ((((((((((((-t31 - t32) + t34) + t39) + t41) - t42) - t43) + t45) + t48)
             + t50) - t51) - t52) + t2) * t4 + 30.0;
    if (!(t6 > 0.0)) {
      t6 = ((((((((((((t31 + t32) - t34) - t39) - t41) + t42) + t43) - t45) -
                t48) - t50) + t51) + t52) + t2) * -t4 + 30.0;
    }

    /* End of MATLAB Function: '<Root>/autogen_Z2p' */

    /* Gain: '<Root>/Gain' incorporates:
     *  Constant: '<Root>/Constant'
     *  Sum: '<Root>/Sum'
     */
    sim_magne_lev_B.Gain = (sim_magne_lev_P.Constant_Value - t6) *
      sim_magne_lev_P.Gain_Gain;
  }

  /* TransferFcn: '<Root>/Transfer Fcn' */
  sim_magne_lev_B.TransferFcn = 0.0;
  sim_magne_lev_B.TransferFcn += sim_magne_lev_P.TransferFcn_C *
    sim_magne_lev_X.TransferFcn_CSTATE;
  sim_magne_lev_B.TransferFcn += sim_magne_lev_P.TransferFcn_D *
    sim_magne_lev_B.Gain;

  /* MATLAB Function: '<Root>/autogen_Z2p1' */
  t2 = sim_magne_lev_B.y_k * sim_magne_lev_B.y_k;
  t4 = 1.0 / sim_magne_lev_B.Gain;
  t31 = t4 * t4;
  t48 = 1.0 / (sim_magne_lev_B.Gain + 0.0631);
  t39 = t48 * t48;
  t41 = t48 * 0.047;
  sim_magne_lev_asinh(&t41);
  t48 *= 0.0173;
  sim_magne_lev_asinh(&t48);
  t32 = t4 * 0.047;
  sim_magne_lev_asinh(&t32);
  t4 *= 0.0173;
  sim_magne_lev_asinh(&t4);
  t32 += -t4;
  t4 = -((sim_magne_lev_B.Gain + 0.0631) * (t41 + -t48)) + t32 *
    sim_magne_lev_B.Gain;
  t42 = t4 * t4;
  t34 = t2 * t42;
  t42 = 1.0 / sim_magne_lev_B.y_k * (1.0 / t42);
  sim_magne_lev_B.u = ((((t39 / sqrt(t39 * 0.002209 + 1.0) * 0.047 - t39 / sqrt
    (t39 * 0.00029929 + 1.0) * 0.0173) * (sim_magne_lev_B.Gain + 0.0631) +
    ((-t41 + t48) + t32)) - (t31 / sqrt(t31 * 0.002209 + 1.0) * 0.047 - t31 /
    sqrt(t31 * 0.00029929 + 1.0) * 0.0173) * sim_magne_lev_B.Gain) * (t2 * t4 *
    sim_magne_lev_B.TransferFcn) * -296208.42211174237 + t34 *
                       2.9648918838862558E+6) * t42 * 1.94273525834272E-6 +
    (((sim_magne_lev_B.Gain * 1000.0 + sim_magne_lev_B.TransferFcn * 300.0) -
      t34 * 4.4431263316761367E+6) + 269.0) * t42 * 1.94273525834272E-6;

  /* Step: '<Root>/Step' */
  if (sim_magne_lev_M->Timing.t[0] < sim_magne_lev_P.Step_Time) {
    t2 = sim_magne_lev_P.Step_Y0;
  } else {
    t2 = sim_magne_lev_P.Step_YFinal;
  }

  /* End of Step: '<Root>/Step' */

  /* Saturate: '<Root>/Saturation' */
  if (sim_magne_lev_B.u > sim_magne_lev_P.Saturation_UpperSat) {
    t39 = sim_magne_lev_P.Saturation_UpperSat;
  } else if (sim_magne_lev_B.u < sim_magne_lev_P.Saturation_LowerSat) {
    t39 = sim_magne_lev_P.Saturation_LowerSat;
  } else {
    t39 = sim_magne_lev_B.u;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* Product: '<Root>/Matrix Multiply' */
  sim_magne_lev_B.MatrixMultiply = t2 * t39;
  if (rtmIsMajorTimeStep(sim_magne_lev_M)) {
    /* S-Function (sldrtao): '<Root>/Analog Output' */
    /* S-Function Block: <Root>/Analog Output */
    {
      {
        ANALOGIOPARM parm;
        parm.mode = (RANGEMODE) sim_magne_lev_P.AnalogOutput_RangeMode;
        parm.rangeidx = sim_magne_lev_P.AnalogOutput_VoltRange;
        RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                       &sim_magne_lev_P.AnalogOutput_Channels, ((real_T*)
          (&sim_magne_lev_B.MatrixMultiply)), &parm);
      }
    }
  }
}

/* Model update function */
void sim_magne_lev_update(void)
{
  if (rtmIsMajorTimeStep(sim_magne_lev_M)) {
    rt_ertODEUpdateContinuousStates(&sim_magne_lev_M->solverInfo);
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
  if (!(++sim_magne_lev_M->Timing.clockTick0)) {
    ++sim_magne_lev_M->Timing.clockTickH0;
  }

  sim_magne_lev_M->Timing.t[0] = rtsiGetSolverStopTime
    (&sim_magne_lev_M->solverInfo);

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
    if (!(++sim_magne_lev_M->Timing.clockTick1)) {
      ++sim_magne_lev_M->Timing.clockTickH1;
    }

    sim_magne_lev_M->Timing.t[1] = sim_magne_lev_M->Timing.clockTick1 *
      sim_magne_lev_M->Timing.stepSize1 + sim_magne_lev_M->Timing.clockTickH1 *
      sim_magne_lev_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void sim_magne_lev_derivatives(void)
{
  XDot_sim_magne_lev_T *_rtXdot;
  _rtXdot = ((XDot_sim_magne_lev_T *) sim_magne_lev_M->derivs);

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = 0.0;
  _rtXdot->TransferFcn_CSTATE += sim_magne_lev_P.TransferFcn_A *
    sim_magne_lev_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += sim_magne_lev_B.Gain;
}

/* Model initialize function */
void sim_magne_lev_initialize(void)
{
  /* Start for S-Function (sldrtao): '<Root>/Analog Output' */

  /* S-Function Block: <Root>/Analog Output */

  /* no initial value should be set */

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  sim_magne_lev_X.TransferFcn_CSTATE = 0.0;
}

/* Model terminate function */
void sim_magne_lev_terminate(void)
{
  /* Terminate for S-Function (sldrtao): '<Root>/Analog Output' */

  /* S-Function Block: <Root>/Analog Output */

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
  sim_magne_lev_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  sim_magne_lev_update();
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
  sim_magne_lev_initialize();
}

void MdlTerminate(void)
{
  sim_magne_lev_terminate();
}

/* Registration function */
RT_MODEL_sim_magne_lev_T *sim_magne_lev(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)sim_magne_lev_M, 0,
                sizeof(RT_MODEL_sim_magne_lev_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&sim_magne_lev_M->solverInfo,
                          &sim_magne_lev_M->Timing.simTimeStep);
    rtsiSetTPtr(&sim_magne_lev_M->solverInfo, &rtmGetTPtr(sim_magne_lev_M));
    rtsiSetStepSizePtr(&sim_magne_lev_M->solverInfo,
                       &sim_magne_lev_M->Timing.stepSize0);
    rtsiSetdXPtr(&sim_magne_lev_M->solverInfo, &sim_magne_lev_M->derivs);
    rtsiSetContStatesPtr(&sim_magne_lev_M->solverInfo, (real_T **)
                         &sim_magne_lev_M->contStates);
    rtsiSetNumContStatesPtr(&sim_magne_lev_M->solverInfo,
      &sim_magne_lev_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&sim_magne_lev_M->solverInfo,
      &sim_magne_lev_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&sim_magne_lev_M->solverInfo,
      &sim_magne_lev_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&sim_magne_lev_M->solverInfo,
      &sim_magne_lev_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&sim_magne_lev_M->solverInfo, (&rtmGetErrorStatus
      (sim_magne_lev_M)));
    rtsiSetRTModelPtr(&sim_magne_lev_M->solverInfo, sim_magne_lev_M);
  }

  rtsiSetSimTimeStep(&sim_magne_lev_M->solverInfo, MAJOR_TIME_STEP);
  sim_magne_lev_M->intgData.y = sim_magne_lev_M->odeY;
  sim_magne_lev_M->intgData.f[0] = sim_magne_lev_M->odeF[0];
  sim_magne_lev_M->intgData.f[1] = sim_magne_lev_M->odeF[1];
  sim_magne_lev_M->intgData.f[2] = sim_magne_lev_M->odeF[2];
  sim_magne_lev_M->contStates = ((real_T *) &sim_magne_lev_X);
  rtsiSetSolverData(&sim_magne_lev_M->solverInfo, (void *)
                    &sim_magne_lev_M->intgData);
  rtsiSetSolverName(&sim_magne_lev_M->solverInfo,"ode3");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = sim_magne_lev_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    sim_magne_lev_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    sim_magne_lev_M->Timing.sampleTimes =
      (&sim_magne_lev_M->Timing.sampleTimesArray[0]);
    sim_magne_lev_M->Timing.offsetTimes =
      (&sim_magne_lev_M->Timing.offsetTimesArray[0]);

    /* task periods */
    sim_magne_lev_M->Timing.sampleTimes[0] = (0.0);
    sim_magne_lev_M->Timing.sampleTimes[1] = (0.001);

    /* task offsets */
    sim_magne_lev_M->Timing.offsetTimes[0] = (0.0);
    sim_magne_lev_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(sim_magne_lev_M, &sim_magne_lev_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = sim_magne_lev_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    sim_magne_lev_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(sim_magne_lev_M, 15.0);
  sim_magne_lev_M->Timing.stepSize0 = 0.001;
  sim_magne_lev_M->Timing.stepSize1 = 0.001;

  /* External mode info */
  sim_magne_lev_M->Sizes.checksums[0] = (2497027632U);
  sim_magne_lev_M->Sizes.checksums[1] = (2071789833U);
  sim_magne_lev_M->Sizes.checksums[2] = (2559400913U);
  sim_magne_lev_M->Sizes.checksums[3] = (2622809126U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[5];
    sim_magne_lev_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(sim_magne_lev_M->extModeInfo,
      &sim_magne_lev_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(sim_magne_lev_M->extModeInfo,
                        sim_magne_lev_M->Sizes.checksums);
    rteiSetTPtr(sim_magne_lev_M->extModeInfo, rtmGetTPtr(sim_magne_lev_M));
  }

  sim_magne_lev_M->solverInfoPtr = (&sim_magne_lev_M->solverInfo);
  sim_magne_lev_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&sim_magne_lev_M->solverInfo, 0.001);
  rtsiSetSolverMode(&sim_magne_lev_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  sim_magne_lev_M->blockIO = ((void *) &sim_magne_lev_B);
  (void) memset(((void *) &sim_magne_lev_B), 0,
                sizeof(B_sim_magne_lev_T));

  /* parameters */
  sim_magne_lev_M->defaultParam = ((real_T *)&sim_magne_lev_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &sim_magne_lev_X;
    sim_magne_lev_M->contStates = (x);
    (void) memset((void *)&sim_magne_lev_X, 0,
                  sizeof(X_sim_magne_lev_T));
  }

  /* states (dwork) */
  sim_magne_lev_M->dwork = ((void *) &sim_magne_lev_DW);
  (void) memset((void *)&sim_magne_lev_DW, 0,
                sizeof(DW_sim_magne_lev_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    sim_magne_lev_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  sim_magne_lev_M->Sizes.numContStates = (1);/* Number of continuous states */
  sim_magne_lev_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  sim_magne_lev_M->Sizes.numY = (0);   /* Number of model outputs */
  sim_magne_lev_M->Sizes.numU = (0);   /* Number of model inputs */
  sim_magne_lev_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  sim_magne_lev_M->Sizes.numSampTimes = (2);/* Number of sample times */
  sim_magne_lev_M->Sizes.numBlocks = (24);/* Number of blocks */
  sim_magne_lev_M->Sizes.numBlockIO = (7);/* Number of block outputs */
  sim_magne_lev_M->Sizes.numBlockPrms = (23);/* Sum of parameter "widths" */
  return sim_magne_lev_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
