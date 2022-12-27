/*
 * main_sim.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "main_sim".
 *
 * Model version              : 1.353
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Mon Feb 21 19:44:28 2022
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "main_sim.h"
#include "main_sim_private.h"
#include "main_sim_dt.h"

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
B_main_sim_T main_sim_B;

/* Continuous states */
X_main_sim_T main_sim_X;

/* Block states (default storage) */
DW_main_sim_T main_sim_DW;

/* Real-time model */
static RT_MODEL_main_sim_T main_sim_M_;
RT_MODEL_main_sim_T *const main_sim_M = &main_sim_M_;

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
  main_sim_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  main_sim_output();
  main_sim_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  main_sim_output();
  main_sim_derivatives();

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
void main_sim_output(void)
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
  if (rtmIsMajorTimeStep(main_sim_M)) {
    /* set solver stop time */
    if (!(main_sim_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&main_sim_M->solverInfo,
                            ((main_sim_M->Timing.clockTickH0 + 1) *
        main_sim_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&main_sim_M->solverInfo,
                            ((main_sim_M->Timing.clockTick0 + 1) *
        main_sim_M->Timing.stepSize0 + main_sim_M->Timing.clockTickH0 *
        main_sim_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(main_sim_M)) {
    main_sim_M->Timing.t[0] = rtsiGetT(&main_sim_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(main_sim_M)) {
    /* S-Function (sldrtai): '<Root>/Analog Input' */
    /* S-Function Block: <Root>/Analog Input */
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) main_sim_P.AnalogInput_RangeMode;
      parm.rangeidx = main_sim_P.AnalogInput_VoltRange;
      RTBIO_DriverIO(0, ANALOGINPUT, IOREAD, 3, main_sim_P.AnalogInput_Channels,
                     &main_sim_B.AnalogInput[0], &parm);
    }

    /* MATLAB Function: '<Root>/MATLAB Function' */
    main_sim_B.y[0] = (main_sim_B.AnalogInput[0] - 5.0) * -5.0;
    main_sim_B.y[1] = (main_sim_B.AnalogInput[1] - 5.0) * -5.0;
    main_sim_B.y[2] = (main_sim_B.AnalogInput[2] - 5.0) * -5.0;

    /* MATLAB Function: '<Root>/autogen_Z2p' */
    t2 = main_sim_B.y[0] * main_sim_B.y[0];
    t4 = main_sim_B.y[1] * main_sim_B.y[1];
    t6 = main_sim_B.y[2] * main_sim_B.y[2];
    t39 = main_sim_B.y[0] * 4.8999911281101E+13;
    t41 = main_sim_B.y[2] * 4.7733218776365E+13;
    t48 = main_sim_B.y[1] * 4.6020599945112E+13;
    t31 = main_sim_B.y[0] * t6 * 4.567884E+10;
    t32 = main_sim_B.y[2] * t2 * 4.567884E+10;
    t34 = rt_powd_snf(main_sim_B.y[0], 3.0) * 9.466641E+10;
    t42 = main_sim_B.y[1] * t6 * 5.176061E+10;
    t43 = main_sim_B.y[2] * t4 * 5.176061E+10;
    t45 = rt_powd_snf(main_sim_B.y[1], 3.0) * 1.0074818E+11;
    t50 = rt_powd_snf(main_sim_B.y[2], 3.0) * 9.743945E+10;
    t51 = main_sim_B.y[0] * t4 * 4.898757E+10;
    t52 = main_sim_B.y[1] * t2 * 4.898757E+10;
    t118_tmp = main_sim_B.y[1] * main_sim_B.y[2];
    t118_tmp_0 = main_sim_B.y[0] * main_sim_B.y[2];
    t118_tmp_1 = main_sim_B.y[0] * main_sim_B.y[1];
    t118 = (((((-(t118_tmp * 1.0352122E+11) + t2 * 9.466641E+10) + -(t118_tmp_0 *
                9.135768E+10)) + t4 * 1.0074818E+11) + t6 * 9.743945E+10) +
            -(t118_tmp_1 * 9.797514E+10)) + 7.1376865001289E+13;
    t111 = ((t2 * 3.21E+6 + t6 * 2.576E+7) + -(t4 * 2.897E+7)) - 2.275477497E+9;
    t112 = ((t4 * 1.297E+7 + t6 * 1.763E+7) + -(t2 * 3.06E+7)) +
      3.0399800799E+10;
    t4 = 1.0 / ((((((t4 * 2.0149636E+11 + t2 * 1.8933282E+11) + -(t118_tmp *
      2.0704244E+11)) + t6 * 1.948789E+11) + -(t118_tmp_0 * 1.8271536E+11)) +
                 -(t118_tmp_1 * 1.9595028E+11)) + 1.42753730002578E+14);
    t6 = (((main_sim_B.y[0] * 321.0 + main_sim_B.y[2] * 2576.0) +
           -(main_sim_B.y[1] * 2897.0)) * t111 + main_sim_B.y[0] *
          1.42753730002578E+14) + ((main_sim_B.y[1] * 1297.0 + main_sim_B.y[2] *
      1763.0) + -(main_sim_B.y[0] * 3060.0)) * t112;
    t2 = sqrt(-((((t2 * 2.85507460005156E+18 + t111 * t111) + t112 * t112) -
                 2.5695671400464038E+21) * t118) + t6 * t6 * 10000.0) / 100.0;
    t6 = ((((((((((((-t31 - t32) + t34) + t39) + t41) - t42) - t43) + t45) + t48)
             + t50) - t51) - t52) + t2) * t4 + 30.0;
    if (!(t6 > 0.0)) {
      t6 = ((((((((((((t31 + t32) - t34) - t39) - t41) + t42) + t43) - t45) -
                t48) - t50) + t51) + t52) + t2) * -t4 + 30.0;
    }

    /* End of MATLAB Function: '<Root>/autogen_Z2p' */

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/Constant'
     */
    main_sim_B.Sum = main_sim_P.Constant_Value - t6;
  }

  /* TransferFcn: '<Root>/Transfer Fcn' */
  main_sim_B.TransferFcn = 0.0;
  main_sim_B.TransferFcn += main_sim_P.TransferFcn_C *
    main_sim_X.TransferFcn_CSTATE;
  main_sim_B.TransferFcn += main_sim_P.TransferFcn_D * main_sim_B.Sum;

  /* Step: '<Root>/Step' */
  if (main_sim_M->Timing.t[0] < main_sim_P.Step_Time) {
    t2 = main_sim_P.Step_Y0;
  } else {
    t2 = main_sim_P.Step_YFinal;
  }

  /* End of Step: '<Root>/Step' */

  /* Saturate: '<Root>/Saturation' */
  if (3.5 > main_sim_P.Saturation_UpperSat) {
    t4 = main_sim_P.Saturation_UpperSat;
  } else if (3.5 < main_sim_P.Saturation_LowerSat) {
    t4 = main_sim_P.Saturation_LowerSat;
  } else {
    t4 = 3.5;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* Product: '<Root>/Matrix Multiply' */
  main_sim_B.MatrixMultiply = t2 * t4;
  if (rtmIsMajorTimeStep(main_sim_M)) {
    /* S-Function (sldrtao): '<Root>/Analog Output' */
    /* S-Function Block: <Root>/Analog Output */
    {
      {
        ANALOGIOPARM parm;
        parm.mode = (RANGEMODE) main_sim_P.AnalogOutput_RangeMode;
        parm.rangeidx = main_sim_P.AnalogOutput_VoltRange;
        RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                       &main_sim_P.AnalogOutput_Channels, ((real_T*)
          (&main_sim_B.MatrixMultiply)), &parm);
      }
    }
  }
}

/* Model update function */
void main_sim_update(void)
{
  if (rtmIsMajorTimeStep(main_sim_M)) {
    rt_ertODEUpdateContinuousStates(&main_sim_M->solverInfo);
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
  if (!(++main_sim_M->Timing.clockTick0)) {
    ++main_sim_M->Timing.clockTickH0;
  }

  main_sim_M->Timing.t[0] = rtsiGetSolverStopTime(&main_sim_M->solverInfo);

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
    if (!(++main_sim_M->Timing.clockTick1)) {
      ++main_sim_M->Timing.clockTickH1;
    }

    main_sim_M->Timing.t[1] = main_sim_M->Timing.clockTick1 *
      main_sim_M->Timing.stepSize1 + main_sim_M->Timing.clockTickH1 *
      main_sim_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void main_sim_derivatives(void)
{
  XDot_main_sim_T *_rtXdot;
  _rtXdot = ((XDot_main_sim_T *) main_sim_M->derivs);

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = 0.0;
  _rtXdot->TransferFcn_CSTATE += main_sim_P.TransferFcn_A *
    main_sim_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += main_sim_B.Sum;
}

/* Model initialize function */
void main_sim_initialize(void)
{
  /* Start for S-Function (sldrtao): '<Root>/Analog Output' */

  /* S-Function Block: <Root>/Analog Output */

  /* no initial value should be set */

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  main_sim_X.TransferFcn_CSTATE = 0.0;
}

/* Model terminate function */
void main_sim_terminate(void)
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
  main_sim_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  main_sim_update();
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
  main_sim_initialize();
}

void MdlTerminate(void)
{
  main_sim_terminate();
}

/* Registration function */
RT_MODEL_main_sim_T *main_sim(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)main_sim_M, 0,
                sizeof(RT_MODEL_main_sim_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&main_sim_M->solverInfo,
                          &main_sim_M->Timing.simTimeStep);
    rtsiSetTPtr(&main_sim_M->solverInfo, &rtmGetTPtr(main_sim_M));
    rtsiSetStepSizePtr(&main_sim_M->solverInfo, &main_sim_M->Timing.stepSize0);
    rtsiSetdXPtr(&main_sim_M->solverInfo, &main_sim_M->derivs);
    rtsiSetContStatesPtr(&main_sim_M->solverInfo, (real_T **)
                         &main_sim_M->contStates);
    rtsiSetNumContStatesPtr(&main_sim_M->solverInfo,
      &main_sim_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&main_sim_M->solverInfo,
      &main_sim_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&main_sim_M->solverInfo,
      &main_sim_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&main_sim_M->solverInfo,
      &main_sim_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&main_sim_M->solverInfo, (&rtmGetErrorStatus
      (main_sim_M)));
    rtsiSetRTModelPtr(&main_sim_M->solverInfo, main_sim_M);
  }

  rtsiSetSimTimeStep(&main_sim_M->solverInfo, MAJOR_TIME_STEP);
  main_sim_M->intgData.y = main_sim_M->odeY;
  main_sim_M->intgData.f[0] = main_sim_M->odeF[0];
  main_sim_M->intgData.f[1] = main_sim_M->odeF[1];
  main_sim_M->intgData.f[2] = main_sim_M->odeF[2];
  main_sim_M->contStates = ((real_T *) &main_sim_X);
  rtsiSetSolverData(&main_sim_M->solverInfo, (void *)&main_sim_M->intgData);
  rtsiSetSolverName(&main_sim_M->solverInfo,"ode3");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = main_sim_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    main_sim_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    main_sim_M->Timing.sampleTimes = (&main_sim_M->Timing.sampleTimesArray[0]);
    main_sim_M->Timing.offsetTimes = (&main_sim_M->Timing.offsetTimesArray[0]);

    /* task periods */
    main_sim_M->Timing.sampleTimes[0] = (0.0);
    main_sim_M->Timing.sampleTimes[1] = (0.001);

    /* task offsets */
    main_sim_M->Timing.offsetTimes[0] = (0.0);
    main_sim_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(main_sim_M, &main_sim_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = main_sim_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    main_sim_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(main_sim_M, 30.0);
  main_sim_M->Timing.stepSize0 = 0.001;
  main_sim_M->Timing.stepSize1 = 0.001;

  /* External mode info */
  main_sim_M->Sizes.checksums[0] = (371814774U);
  main_sim_M->Sizes.checksums[1] = (3286060943U);
  main_sim_M->Sizes.checksums[2] = (2871738437U);
  main_sim_M->Sizes.checksums[3] = (537556562U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[4];
    main_sim_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(main_sim_M->extModeInfo,
      &main_sim_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(main_sim_M->extModeInfo, main_sim_M->Sizes.checksums);
    rteiSetTPtr(main_sim_M->extModeInfo, rtmGetTPtr(main_sim_M));
  }

  main_sim_M->solverInfoPtr = (&main_sim_M->solverInfo);
  main_sim_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&main_sim_M->solverInfo, 0.001);
  rtsiSetSolverMode(&main_sim_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  main_sim_M->blockIO = ((void *) &main_sim_B);
  (void) memset(((void *) &main_sim_B), 0,
                sizeof(B_main_sim_T));

  /* parameters */
  main_sim_M->defaultParam = ((real_T *)&main_sim_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &main_sim_X;
    main_sim_M->contStates = (x);
    (void) memset((void *)&main_sim_X, 0,
                  sizeof(X_main_sim_T));
  }

  /* states (dwork) */
  main_sim_M->dwork = ((void *) &main_sim_DW);
  (void) memset((void *)&main_sim_DW, 0,
                sizeof(DW_main_sim_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    main_sim_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  main_sim_M->Sizes.numContStates = (1);/* Number of continuous states */
  main_sim_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  main_sim_M->Sizes.numY = (0);        /* Number of model outputs */
  main_sim_M->Sizes.numU = (0);        /* Number of model inputs */
  main_sim_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  main_sim_M->Sizes.numSampTimes = (2);/* Number of sample times */
  main_sim_M->Sizes.numBlocks = (19);  /* Number of blocks */
  main_sim_M->Sizes.numBlockIO = (5);  /* Number of block outputs */
  main_sim_M->Sizes.numBlockPrms = (21);/* Sum of parameter "widths" */
  return main_sim_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
