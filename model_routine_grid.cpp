/*

  Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

  NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

/* DO NOT USE FUNCTIONS THAT ARE NOT THREAD SAFE (e.g. rand(), use Util::getModelRand() instead) */

#include "biocellion.h"

#include "model_routine.h"

#include "model_define.h"

using namespace std;

void ModelRoutine::initIfGridVar( const VIdx& vIdx, const UBAgentData& ubAgentData, Vector<REAL>& v_gridPhi/* [elemIdx] */, Vector<REAL>& v_gridModelReal/* [elemIdx] */, Vector<S32>& v_gridModelInt ) {
  /* MODEL START */

  CHECK( v_gridPhi.size() == NUM_DIFFUSIBLE_ELEMS );
  CHECK( v_gridModelReal.size() == NUM_GRID_MODEL_REALS );
  CHECK( v_gridModelInt.size() == 0 );

  v_gridPhi[DIFFUSIBLE_ELEM_CHEMOATTRACTANT] = 0.0;

  for( S32 elemIdx = 0 ; elemIdx < NUM_GRID_MODEL_REALS ; elemIdx++ ) {
    v_gridModelReal[elemIdx] = 0.0;
  }

  /* MODEL END */

  return;
}

void ModelRoutine::updateIfGridVar( const BOOL pre, const S32 round, const VIdx& vIdx, const NbrBox<const UBAgentData*>& ubAgentDataPtrNbrBox, Vector<NbrBox<REAL> >& v_gridPhiNbrBox/* [elemIdx] */, Vector<NbrBox<REAL> >& v_gridModelRealNbrBox/* INOUT, [elemIdx] */, Vector<NbrBox<S32> >& v_gridModelIntNbrBox/* INOUT, [elemIdx] */ ) {
  /* MODEL START */

  if (pre) {
    for( S32 elemIdx = 0 ; elemIdx < NUM_DIFFUSIBLE_ELEMS ; elemIdx++ ) {
      REAL phi = v_gridPhiNbrBox[elemIdx].getVal( 0, 0, 0 );
      const UBAgentData& ubAgentData = *( ubAgentDataPtrNbrBox.getVal(0, 0, 0) );
      for( ubAgentIdx_t l = 0 ; l < ( ubAgentIdx_t )ubAgentData.v_spAgent.size() ; l++ ) {
        const SpAgent& spAgent = ubAgentData.v_spAgent[l];
        S32 agentType = spAgent.state.getType();
        phi += A_CELL_CHEMOATTRACTANT_SECRETION_RATE[agentType];
      }
      v_gridPhiNbrBox[elemIdx].setVal( 0, 0, 0, phi );
    }
  }

  /* MODEL END */

  return;
}

void ModelRoutine::updateIfGridKappa( const VIdx& vIdx, const UBAgentData& ubAgentData, const Vector<REAL>& v_gridPhi/* [elemIdx] */, const Vector<REAL>& v_gridModelReal/* [elemIdx] */, const Vector<S32>& v_gridModelInt/* [elemIdx] */, REAL& gridKappa/* to consider cell volume exclusion in computing diffusion flux, set to 1.0 to ignore the volume occupied by cells */ ) {
  /* MODEL START */

  gridKappa = 1.0;

  /* MODEL END */

  return;
}

void ModelRoutine::updateIfGridAlpha( const S32 elemIdx, const VIdx& vIdx, const UBAgentData& ubAgentData, const Vector<REAL>& v_gridPhi/* [elemIdx] */, const Vector<REAL>& v_gridModelReal/* [elemIdx] */, const Vector<S32>& v_gridModelInt/* [elemIdx] */, REAL& gridAlpha/* decay (-) */ ) {
  /* MODEL START */

  gridAlpha = -DIFFUSIBLE_ELEM_DECAY_RATE[elemIdx];

  /* MODEL END */

  return;
}

void ModelRoutine::updateIfGridBetaInIfRegion( const S32 elemIdx, const S32 dim, const VIdx& vIdx0, const VIdx& vIdx1, const UBAgentData& ubAgentData0, const UBAgentData& ubAgentData1, const Vector<REAL>& v_gridPhi0/* [elemIdx] */, const Vector<REAL>& v_gridPhi1/* [elemIdx] */, const Vector<REAL>& v_gridModelReal0/* [elemIdx] */, const Vector<REAL>& v_gridModelReal1/* [elemIdx] */, const Vector<S32>& v_gridModelInt0/* [elemIdx] */, const Vector<S32>& v_gridModelInt1/* [elemIdx] */, REAL& gridBeta ) {
  /* MODEL START */

  gridBeta = DIFFUSIBLE_ELEM_DIFFUSION_COEFFICIENT[elemIdx];

  /* MODEL END */

  return;
}

void ModelRoutine::updateIfGridBetaPDEBufferBdry( const S32 elemIdx, const S32 dim, const VIdx& vIdx, const UBAgentData& ubAgentData, const Vector<REAL>& v_gridPhi/* [elemIdx] */, const Vector<REAL>& v_gridModelReal/* [elemIdx] */, const Vector<S32>& v_gridModelInt/* [elemIdx] */, REAL& gridBeta ) {
  /* MODEL START */

  ERROR( "unimplemented." );

  /* MODEL END */

  return;
}

void ModelRoutine::updateIfGridBetaDomainBdry( const S32 elemIdx, const S32 dim, const VIdx& vIdx, const UBAgentData& ubAgentData, const Vector<REAL>& v_gridPhi/* [elemIdx] */, const Vector<REAL>& v_gridModelReal/* [elemIdx] */, const Vector<S32>& v_gridModelInt/* [elemIdx] */, REAL& gridBeta ) {
  /* MODEL START */

  gridBeta = 0.0;

  /* MODEL END */

  return;
}

void ModelRoutine::updateIfGridAdvectionVelocityInIfRegion( const S32 elemIdx, const S32 dim, const VIdx& vIdx0, const VIdx& vIdx1, const UBAgentData& ubAgentData0, const UBAgentData& ubAgentData1, const Vector<REAL>& v_gridPhi0/* [elemIdx] */, const Vector<REAL>& v_gridPhi1/* [elemIdx] */, const Vector<REAL>& v_gridModelReal0/* [elemIdx] */, const Vector<REAL>& v_gridModelReal1/* [elemIdx] */, const Vector<S32>& v_gridModelInt0/* [elemIdx] */, const Vector<S32>& v_gridModelInt1/* [elemIdx] */, REAL& gridAdvectionVelocity ) {
  /* MODEL START */

  ERROR( "unimplemented." );

  /* MODEL END */

  return;
}

void ModelRoutine::updateIfGridAdvectionVelocityPDEBufferBdry( const S32 elemIdx, const S32 dim, const VIdx& vIdx, const UBAgentData& ubAgentData, const Vector<REAL>& v_gridPhi/* [elemIdx] */, const Vector<REAL>& v_gridModelReal/* [elemIdx] */, const Vector<S32>& v_gridModelInt/* [elemIdx] */, REAL& gridAdvectionVelocity ) {
  /* MODEL START */

  ERROR( "unimplemented." );

  /* MODEL END */

  return;
}

void ModelRoutine::updateIfGridAdvectionVelocityDomainBdry( const S32 elemIdx, const S32 dim, const VIdx& vIdx, const UBAgentData& ubAgentData, const Vector<REAL>& v_gridPhi/* [elemIdx] */, const Vector<REAL>& v_gridModelReal/* [elemIdx] */, const Vector<S32>& v_gridModelInt/* [elemIdx] */, REAL& gridAdvectionVelocity ) {
  /* MODEL START */

  ERROR( "unimplemented." );

  /* MODEL END */

  return;
}

void ModelRoutine::updateIfGridRHSLinear( const S32 elemIdx, const VIdx& vIdx, const UBAgentData& ubAgentData, const Vector<REAL>& v_gridPhi/* [elemIdx] */, const Vector<REAL>& v_gridModelReal/* [elemIdx] */, const Vector<S32>& v_gridModelInt/* [elemIdx] */, REAL& gridRHS/* uptake(-) and secretion (+) */ ) {
  /* MODEL START */

  gridRHS = 0.0;

  /* MODEL END */

  return;
}

void ModelRoutine::adjustIfGridRHSTimeDependentLinear( const S32 elemIdx, const VIdx& vIdx, const REAL gridPhi, const Vector<REAL>& v_gridModelReal/* [elemIdx] */, const Vector<S32>& v_gridModelInt/* [elemIdx] */, REAL& gridRHS/* INOUT, uptake(-) and secretion (+) */ ) {
  /* MODEL START */

  // NOOP

  /* MODEL END */

  return;
}

void ModelRoutine::updateIfGridRHSTimeDependentSplitting( const S32 pdeIdx, const VIdx& vIdx, const UBAgentData& ubAgentData, const Vector<double>& v_gridPhi/* [idx] */, const Vector<REAL>& v_gridModelReal/* [elemIdx] */, const Vector<S32>& v_gridModelInt/* [elemIdx] */, Vector<double>& v_gridRHS/* [idx], uptake(-) and secretion (+) */ ) {
  /* MODEL START */

  ERROR( "unimplemented." );

  /* MODEL END */

  return;
}

void ModelRoutine::updateIfGridAMRTags( const VIdx& vIdx, const NbrBox<const UBAgentData*>& ubAgentDataPtrNbrBox, const Vector<NbrBox<REAL> >& v_gridPhiNbrBox/* [elemIdx] */, const Vector<NbrBox<REAL> >& v_gridModelRealNbrBox/* [elemIdx] */, const Vector<NbrBox<S32> >& v_gridModelIntNbrBox/* [elemIdx] */, Vector<S32>& v_finestLevel/* [pdeIdx] */ ) {
  /* MODEL START */

  for( S32 pdeIdx = 0 ; pdeIdx < NUM_DIFFUSIBLE_ELEMS ; pdeIdx++ ) {
    v_finestLevel[pdeIdx] = 2;
  }

  /* MODEL END */

  return;
}

void ModelRoutine::updateIfGridDirichletBCVal( const S32 elemIdx, const VReal& pos, const S32 dim, const BOOL lowSide, const REAL a_gridPhi[3], const Vector<Vector<REAL> >& vv_gridModelReal/* [elemIdx] */, const Vector<Vector<S32> >& vv_gridModelInt/* [elemIdx] */, REAL& bcVal ) {
  /* MODEL START */

  ERROR( "unimplmented." );

  /* MODEL END */

  return;
}

void ModelRoutine::updateIfGridNeumannBCVal( const S32 elemIdx, const VReal& pos, const S32 dim, const BOOL lowSide, const REAL a_gridPhi[3], const Vector<Vector<REAL> >& vv_gridModelReal/* [elemIdx] */, const Vector<Vector<S32> >& vv_gridModelInt/* [elemIdx] */, REAL& bcVal ) {
  /* MODEL START */

  ERROR( "unimplmented." );

  /* MODEL END */

  return;
}

void ModelRoutine::initPDEBufferPhi( const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, Vector<REAL>& v_gridPhi ) {
  /* MODEL START */

  CHECK( v_gridPhi.size() == 0 );

  /* MODEL END */

  return;
}

void ModelRoutine::updatePDEBufferKappa( const S32 pdeIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, REAL& gridKappa/* to consider cell volume exclusion in computing diffusion flux, set to 1.0 to ignore the volume occupied by cells */ ) {
  /* MODEL START */

  ERROR( "unimplmented." );

  /* MODEL END */

  return;
}

void ModelRoutine::updatePDEBufferAlpha( const S32 elemIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, REAL& gridAlpha/* decay (-) */ ) {
  /* MODEL START */

  ERROR( "unimplmented." );

  /* MODEL END */

  return;
}

void ModelRoutine::updatePDEBufferBetaInPDEBufferRegion( const S32 elemIdx, const S32 dim, const VIdx& startVIdx0, const VIdx& startVIdx1, const VIdx& pdeBufferBoxSize, REAL& gridBeta ) {
  /* MODEL START */

  ERROR( "unimplmented." );

  /* MODEL END */

  return;
}

void ModelRoutine::updatePDEBufferBetaDomainBdry( const S32 elemIdx, const S32 dim, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, REAL& gridBeta ) {
  /* MODEL START */

  ERROR( "unimplmented." );

  /* MODEL END */

  return;
}

void ModelRoutine::updatePDEBufferAdvectionVelocityInPDEBufferRegion( const S32 elemIdx, const S32 dim, const VIdx& startVIdx0, const VIdx& startVIdx1, const VIdx& pdeBufferBoxSize, REAL& gridAdvectionVelocity ) {
  /* MODEL START */

  ERROR( "unimplmented." );

  /* MODEL END */

  return;
}

void ModelRoutine::updatePDEBufferAdvectionVelocityDomainBdry( const S32 elemIdx, const S32 dim, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, REAL& gridAdvectionVelocity ) {
  /* MODEL START */

  ERROR( "unimplmented." );

  /* MODEL END */

  return;
}

void ModelRoutine::updatePDEBufferRHSLinear( const S32 elemIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, const REAL gridPhi, REAL& gridRHS/* uptake(-) and secretion (+) */ ) {
  /* MODEL START */

  ERROR( "unimplmented." );

  /* MODEL END */

  return;
}

void ModelRoutine::adjustPDEBufferRHSTimeDependentLinear( const S32 elemIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, const REAL gridPhi, REAL& gridRHS/* INOUT, uptake(-) and secretion (+) */ ) {
  /* MODEL START */

  ERROR( "unimplemented." );

  /* MODEL END */

  return;
}

void ModelRoutine::updatePDEBufferRHSTimeDependentSplitting( const S32 pdeIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, const Vector<double>& v_gridPhi/* [idx] */, Vector<double>& v_gridRHS/* [idx], uptake(-) and secretion (+) */ ) {
  /* MODEL START */

  ERROR( "unimplemented." );

  /* MODEL END */

  return;
}

void ModelRoutine::updatePDEBufferDirichletBCVal( const S32 elemIdx, const VReal& startPos, const VReal& pdeBufferFaceSize, const S32 dim, const BOOL lowSide, REAL& bcVal ) {
  /* MODEL START */

  ERROR( "unimplmented." );

  /* MODEL END */

  return;
}

void ModelRoutine::updatePDEBufferNeumannBCVal( const S32 elemIdx, const VReal& startPos, const VReal& pdeBufferFaceSize, const S32 dim, const BOOL lowSide, REAL& bcVal ) {
  /* MODEL START */

  ERROR( "unimplmented." );

  /* MODEL END */

  return;
}

