/*

  Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

  NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

/* DO NOT USE FUNCTIONS THAT ARE NOT THREAD SAFE (e.g. rand(), use Util::getModelRand() instead) */

#include "biocellion.h"

#include "model_routine.h"

/* MODEL START */

#include "model_define.h"

/* MODEL END */

using namespace std;

void ModelRoutine::updateGlobalData( Vector<U8>& v_globalData ) {
  /* MODEL START */

  /* nothing to do */

  /* MODEL END */

  return;
}

void ModelRoutine::updateIfGridSpacing( REAL& ifGridSpacing ) {
  /* MODEL START */

  ifGridSpacing = IF_GRID_SPACING;

  /* MODEL END */

  return;
}

void ModelRoutine::updateOptModelRoutineCallInfo( OptModelRoutineCallInfo& callInfo ) {
  /* MODEL START */
  /* AVT:
   * Controls the number of times to call the grid update routines
   * for grid-and-state time steps (sub-baseline time steps) */
  callInfo.numUpdateIfGridVarPreStateAndGridStepRounds = 1;
  callInfo.numUpdateIfGridVarPostStateAndGridStepRounds = 1;

  /* MODEL END */

  return;
}

void ModelRoutine::updateDomainBdryType( domain_bdry_type_e a_domainBdryType[DIMENSION] ) {
  /* MODEL START */

  CHECK( DIMENSION == 3 );

  for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
    a_domainBdryType[dim] = DOMAIN_BDRY_TYPE_NONPERIODIC_HARD_WALL;
  }

  /* MODEL END */

  return;
}

void ModelRoutine::updatePDEBufferBdryType( pde_buffer_bdry_type_e& pdeBufferBdryType ) {
  /* MODEL START */

  pdeBufferBdryType = PDE_BUFFER_BDRY_TYPE_HARD_WALL;

  /* MODEL END */

  return;
}

void ModelRoutine::updateTimeStepInfo( TimeStepInfo& timeStepInfo ) {
  /* MODEL START */

  timeStepInfo.durationBaselineTimeStep = BASELINE_TIME_STEP;
  timeStepInfo.numStateAndGridTimeStepsPerBaseline = STEPS_PER_BASELINE;

  /* MODEL END */

  return;
}

void ModelRoutine::updateSyncMethod( sync_method_e& extraMechIntrctSyncMethod, sync_method_e& updateIfGridVarSyncMethod/* dummy if both callUpdateIfGridVarPreStateAndGridStep and callUpdateIfGridVarPostStateAndGridStep are set to false in ModelRoutine::updateOptModelRoutineCallInfo */ ) {
  /* MODEL START */

  extraMechIntrctSyncMethod = SYNC_METHOD_OVERWRITE;
  updateIfGridVarSyncMethod = SYNC_METHOD_OVERWRITE;

  /* MODEL END */

  return;
}

#if HAS_SPAGENT
void ModelRoutine::updateSpAgentInfo( Vector<SpAgentInfo>& v_spAgentInfo ) {
  /* MODEL START */

  v_spAgentInfo.resize( NUM_CELL_TYPES );

  for( S32 i = 0 ; i < NUM_CELL_TYPES ; i++ ) {
    SpAgentInfo info;

    info.dMax = A_CELL_D_MAX[i];
    info.hasBool = false;
    info.numBoolVars = 0;
    info.numStateModelReals = 0;
    info.numStateModelInts = 0;
    info.numExtraMechIntrctModelReals = 0;
    info.numExtraMechIntrctModelInts = 0;
    info.v_odeNetInfo.clear();

    v_spAgentInfo[i] = info;
  }

  /* MODEL END */

  return;
}
#endif

void ModelRoutine::updateJunctionEndInfo( Vector<JunctionEndInfo>& v_junctionEndInfo ) {
  /* MODEL START */

  v_junctionEndInfo.clear();
  v_junctionEndInfo.resize(1);

  JunctionEndInfo info;
  info.numModelReals = 0;
  info.numModelInts = 0;

  v_junctionEndInfo[0] = info;

  /* MODEL END */

  return;
}

void ModelRoutine::updatePDEInfo( Vector<PDEInfo>& v_pdeInfo ) {
  /* MODEL START */

  /* AVT:
   * Initialize type information for v_gridPhi variables (ones that have updates
   * mainly handled by PDE solvers.)
   */

  CHECK( NUM_DIFFUSIBLE_ELEMS == 1 );
  v_pdeInfo.resize( NUM_DIFFUSIBLE_ELEMS );

  PDEInfo pdeInfo;
  GridPhiInfo gridPhiInfo;

  /* Configure PDE solver properties 
   * CGL: Can't claim to understand all of these values at this time.
   */
  pdeInfo.pdeType = PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_LINEAR;
  pdeInfo.numLevels = 3;
  pdeInfo.numTimeSteps = 1;
  pdeInfo.callAdjustRHSTimeDependentLinear = false;

  pdeInfo.mgSolveInfo.numPre = 3;
  pdeInfo.mgSolveInfo.numPost = 3;
  pdeInfo.mgSolveInfo.numBottom = 3;
  pdeInfo.mgSolveInfo.vCycle = true;
  pdeInfo.mgSolveInfo.maxIters = 30;
  pdeInfo.mgSolveInfo.epsilon = 1e-8;
  pdeInfo.mgSolveInfo.hang = 1e-8;
  pdeInfo.mgSolveInfo.normThreshold = 1e-18;


  gridPhiInfo.elemIdx = DIFFUSIBLE_ELEM_CHEMOATTRACTANT;
  gridPhiInfo.name = "chemoattractant";
  /* PDE Boundary conditions */
  gridPhiInfo.aa_bcType[0][0] = BC_TYPE_NEUMANN_CONST;
  gridPhiInfo.aa_bcType[0][1] = BC_TYPE_NEUMANN_CONST;
  gridPhiInfo.aa_bcType[1][0] = BC_TYPE_NEUMANN_CONST;
  gridPhiInfo.aa_bcType[1][1] = BC_TYPE_NEUMANN_CONST;
  gridPhiInfo.aa_bcType[2][0] = BC_TYPE_NEUMANN_CONST;
  gridPhiInfo.aa_bcType[2][1] = BC_TYPE_NEUMANN_CONST;
  gridPhiInfo.aa_bcVal[0][0] = 0.0;
  gridPhiInfo.aa_bcVal[0][1] = 0.0;
  gridPhiInfo.aa_bcVal[1][0] = 0.0;
  gridPhiInfo.aa_bcVal[1][1] = 0.0;
  gridPhiInfo.aa_bcVal[2][0] = 0.0;
  gridPhiInfo.aa_bcVal[2][1] = 0.0;
  /* PDE error/warning and corrections */
  gridPhiInfo.errorThresholdVal = -1.0e-15;
  gridPhiInfo.warningThresholdVal = -1.0e-18;
  gridPhiInfo.setNegToZero = true;
   
  // assign PDE grid info
  pdeInfo.v_gridPhiInfo.assign( 1, gridPhiInfo );

  // Finally register the pde information
  v_pdeInfo[DIFFUSIBLE_ELEM_CHEMOATTRACTANT] = pdeInfo;
  

  /* MODEL END */

  return;
}

void ModelRoutine::updateIfGridModelVarInfo( Vector<IfGridModelVarInfo>& v_ifGridModelRealInfo, Vector<IfGridModelVarInfo>& v_ifGridModelIntInfo ) {
  /* MODEL START */

  /* AVT:
   * Need to initialize grid value types here.  None for now.
   */

  /* No real values */
  v_ifGridModelRealInfo.clear();
  
  // IfGridModelVarInfo info;

  // v_ifGridModelRealInfo.resize( NUM_GRID_MODEL_REALS );

  // info.name = "nutrient";
  // v_ifGridModelRealInfo[GRID_MODEL_REAL_NUTRIENT] = info;

  /* No integer values */
  v_ifGridModelIntInfo.clear();

  /* MODEL END */

  return;
}

void ModelRoutine::updateRNGInfo( Vector<RNGInfo>& v_rngInfo ) {
  /* MODEL START */

  v_rngInfo.resize( NUM_MODEL_RNGS );
  
  RNGInfo& rngInfoUniform = v_rngInfo[MODEL_RNG_UNIFORM];

  rngInfoUniform.type = RNG_TYPE_UNIFORM;
  rngInfoUniform.param0 = 0.0;
  rngInfoUniform.param1 = 1.0;
  rngInfoUniform.param2 = 0.0;/* dummy */

  RNGInfo& rngInfoGaussian = v_rngInfo[MODEL_RNG_GAUSSIAN];

  rngInfoGaussian.type = RNG_TYPE_GAUSSIAN;
  rngInfoGaussian.param0 = 0.0;
  rngInfoGaussian.param1 = 1.0;
  rngInfoGaussian.param2 = 0.0;/* dummy */

  /* MODEL END */

  return;
}

void ModelRoutine::updateFileOutputInfo( FileOutputInfo& fileOutputInfo ) {
  /* MODEL START */

  fileOutputInfo.particleOutput = true;
  fileOutputInfo.particleNumExtraOutputVars = 0;
  /* AVT:
   * Output the nutrient values
   */
  fileOutputInfo.v_gridPhiOutput.assign( NUM_DIFFUSIBLE_ELEMS, true );
  fileOutputInfo.v_gridPhiOutputDivideByKappa.assign( NUM_DIFFUSIBLE_ELEMS, false );

  /* MODEL END */

  return;
}

void ModelRoutine::updateSummaryOutputInfo( SummaryOutputInfo& summaryOutputInfo ) {
  /* MODEL START */

  /* nothing to do */

  /* MODEL END */

  return;
}

void ModelRoutine::init( void ) {
  /* MODEL START */

  /* nothing to do */

  /* MODEL END */

  return;
}

void ModelRoutine::term( void ) {
  /* MODEL START */

  /* nothing to do */

  /* MODEL END */

  return;
}

void ModelRoutine::setPDEBuffer( const VIdx& startVIdx, const VIdx& regionSize, BOOL& isPDEBuffer ) {
  /* MODEL START */

  isPDEBuffer = false;

  /* MODEL END */

  return;
}

void ModelRoutine::setHabitable( const VIdx& vIdx, BOOL& isHabitable ) {
  /* MODEL START */

  isHabitable = true;

  /* MODEL END */

  return;
}

