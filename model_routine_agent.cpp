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

#if HAS_SPAGENT
void ModelRoutine::addSpAgents( const BOOL init, const VIdx& startVIdx, const VIdx& regionSize, const IfGridBoxData<BOOL>& ifGridHabitableBoxData, Vector<VIdx>& v_spAgentVIdx, Vector<SpAgentState>& v_spAgentState, Vector<VReal>& v_spAgentOffset ) {
  /* MODEL START */

  if( init == true ) {
    
    /* *2D* 
     * This initialization has been set to fill a 2-D plane in the center of the 
     * z axis with agents */
    S32 dim = DIMENSION-1;
    idx_t z_mid_idx = Info::getDomainSize(dim)/2;
    if(z_mid_idx < startVIdx[dim] || z_mid_idx >= startVIdx[dim] + regionSize[dim]) {
      // doesn't contain the middle plane
      return;
    }
    /* end restriction on center plane */

    const S64 numUBs = regionSize[0] * regionSize[1] /* *2D* * regionSize[2] */;

    for( S32 i = 0 ; i < NUM_CELL_TYPES ; i++ ) {
      S64 numCells = ( S64 )( ( REAL )numUBs * A_CELL_DENSITY_PER_UB[i] );

      for( S64 j = 0 ; j < numCells ; j++ ) {
        VIdx vIdx;
        SpAgentState state;
        VReal vOffset;

        for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
          /* *2D* */
          // put z in middle of domain
          if(dim == DIMENSION-1) {
            vIdx[dim] = z_mid_idx;
            vOffset[dim] = 0.0;
            continue;
          }
          /* end 2d restriction */

          vIdx[dim] = startVIdx[dim] + ( idx_t )( ( REAL )regionSize[dim] * Util::getModelRand( MODEL_RNG_UNIFORM ) );
          if( vIdx[dim] < startVIdx[dim] ) {
            vIdx[dim] = startVIdx[dim];
          }
          else if( vIdx[dim] >= startVIdx[dim] + regionSize[dim] ) {
            vIdx[dim] = startVIdx[dim] + regionSize[dim] - 1;
          }

          vOffset[dim] = IF_GRID_SPACING * -0.5 + IF_GRID_SPACING * Util::getModelRand( MODEL_RNG_UNIFORM );
          if( vOffset[dim] < IF_GRID_SPACING * -0.5 ) {
            vOffset[dim] = -0.5 * IF_GRID_SPACING;
          }
          else if( vOffset[dim] > IF_GRID_SPACING * 0.5 ) {
            vOffset[dim] = 0.5 * IF_GRID_SPACING;
          }
        }

        state.setType( i );
        state.setRadius( A_CELL_RADIUS[i] );

        v_spAgentVIdx.push_back( vIdx );
        v_spAgentState.push_back( state );
        v_spAgentOffset.push_back( vOffset );
      }
    }
  }

  /* MODEL END */

  return;
}

void ModelRoutine::spAgentCRNODERHS( const S32 odeNetIdx, const VIdx& vIdx, const SpAgent& spAgent, const Vector<NbrBox<REAL> >& v_gridPhiNbrBox, const Vector<NbrBox<REAL> >& v_gridModelRealNbrBox, const Vector<NbrBox<S32> >& v_gridModelIntNbrBox, const Vector<double>& v_y, Vector<double>& v_f ) {
  /* MODEL START */

  ERROR( "unimplemented." );

  /* MODEL END */

  return;
}

void ModelRoutine::updateSpAgentState( const VIdx& vIdx, const AgentJunctionInfo& junctionInfo, const VReal& vOffset, const Vector<NbrBox<REAL> >& v_gridPhiNbrBox/* [elemIdx] */, const Vector<NbrBox<REAL> >& v_gridModelRealNbrBox/* [elemIdx] */, const Vector<NbrBox<S32> >& v_gridModelIntNbrBox/* [elemIdx] */, SpAgentState& state/* INOUT */ ) {
  /* MODEL START */

  /* nothing to do */

  /* MODEL END */

  return;
}

void ModelRoutine::spAgentSecretionBySpAgent( const VIdx& vIdx, const AgentJunctionInfo& junctionInfo, const VReal& vOffset, const AgentMechIntrctData& mechIntrctData, const Vector<NbrBox<REAL> >& v_gridPhiNbrBox/* [elemIdx] */, const Vector<NbrBox<REAL> >& v_gridModelRealNbrBox/* [elemIdx] */, const Vector<NbrBox<S32> >& v_gridModelIntNbrBox/* [elemIdx] */, SpAgentState& state/* INOUT */, Vector<SpAgentState>& v_spAgentState, Vector<VReal>& v_spAgentDisp ) {
  /* MODEL START */

  /* nothing to do */

  /* MODEL END */

  return;
}

void ModelRoutine::updateSpAgentBirthDeath( const VIdx& vIdx, const SpAgent& spAgent, const AgentMechIntrctData& mechIntrctData, const Vector<NbrBox<REAL> >& v_gridPhiNbrBox/* [elemIdx] */, const Vector<NbrBox<REAL> >& v_gridModelRealNbrBox/* [elemIdx] */, const Vector<NbrBox<S32> >& v_gridModelIntNbrBox/* [elemIdx] */, BOOL& divide, BOOL& disappear ) {
  /* MODEL START */

  divide = false;
  disappear = false;

  /* MODEL END */

  return;
}

/* given a position and a direction, determine which
   neighbor interface is intersected first (x, y, or z) */
S32 findNearestInterface(const VReal& vOffset, const VReal& vDir) {
  S32 interface = -1;
  REAL tNearest = 1.0e10;
  for (S32 dim = 0; dim < DIMENSION; dim++) {
    if (fabs(vDir[dim]) > 0.0001) {
      REAL t = ((vDir[dim] > 0 ? 0.5 : -0.5) - vOffset[dim] / IF_GRID_SPACING) / vDir[dim];
      if (t < tNearest) {
        interface = dim;
        tNearest = t;
      }
    }
  }
  return interface;
}

void ModelRoutine::adjustSpAgent( const VIdx& vIdx, const AgentJunctionInfo& junctionInfo, const VReal& vOffset, const AgentMechIntrctData& mechIntrctData, const Vector<NbrBox<REAL> >& v_gridPhiNbrBox/* [elemIdx] */, const Vector<NbrBox<REAL> >& v_gridModelRealNbrBox/* [elemIdx] */, const Vector<NbrBox<S32> >& v_gridModelIntNbrBox/* [elemIdx] */, SpAgentState& state/* INOUT */, VReal& disp ) {
  /* MODEL START */

  disp = mechIntrctData.force;

  if (junctionInfo.getNumJunctions() < 4) { /* inhibit chemotaxis if number of junctions (neighbors) is 4 or more */

    /* forward and backward direction vectors */
    VReal fwdDir;
    VReal bckDir;
    REAL mag = 0.0;

    /* calculate a random forward vector, and its magnitude */
    for (S32 dim = 0; dim < DIMENSION; dim++) {
      // do not do motion in z-dimension *2D*
      if (dim == DIMENSION-1) {
        fwdDir[dim] = 0.0;
        continue;
      }

      fwdDir[dim] = -0.5 + Util::getModelRand(MODEL_RNG_UNIFORM);
      mag += fwdDir[dim] * fwdDir[dim];
    }
    mag = sqrt(mag);

    /* normalize the forward vector, and set the backward vector */
    for (S32 dim = 0; dim < DIMENSION; dim++) {
      fwdDir[dim] /= mag; // normalize
      bckDir[dim] = -fwdDir[dim];
    }

    /* find the nearest neighbor interface (x, y, or z) in both the
       forward and backward directions (using a separate function) */
    S32 fwdInt = findNearestInterface(vOffset, fwdDir);
    S32 bckInt = findNearestInterface(vOffset, bckDir);

    /* calculate the offset ([-1,0,1] in all dimensions) for each of the two neighbors */
    VIdx fwdOffset;
    VIdx bckOffset;
    for (S32 dim = 0; dim < DIMENSION; dim++) {
      fwdOffset[dim] = dim == fwdInt ? (fwdDir[fwdInt] > 0 ? 1 : -1) : 0;
      bckOffset[dim] = dim == bckInt ? (bckDir[bckInt] > 0 ? 1 : -1) : 0;
    }

    /* read the chemoattractant values from each of the two neighbors */
    NbrBox<REAL> nbr = v_gridPhiNbrBox[DIFFUSIBLE_ELEM_CHEMOATTRACTANT];
    REAL fwdVal = 0.0;
    REAL bckVal = 0.0;
    if (nbr.getValidFlag(fwdOffset)) {
      fwdVal = nbr.getVal(fwdOffset);
    }
    if (nbr.getValidFlag(bckOffset)) {
      bckVal = nbr.getVal(bckOffset);
    }

    /* calculate the chemotactic force, and apply it if positive */
    REAL chemForce = A_CELL_CHEMOTAXIS_FORCE_STRENGTH[state.getType()] * (fwdVal - bckVal);
    if (chemForce > 0) {
      for (S32 dim = 0; dim < DIMENSION; dim++) {
        disp[dim] += fwdDir[dim] * chemForce;
      }
    }
  }

  /* add Brownian motion */
  for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
    // do not do motion in z-dimension *2D*
    if (dim == DIMENSION-1) {
      continue;
    }

    disp[dim] += A_CELL_RADIUS[state.getType()] * ( Util::getModelRand( MODEL_RNG_GAUSSIAN ) ) * A_CELL_TEMP[state.getType()];
  }

  /* limit the maximum displacement within a single time step */
  for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
    if( disp[dim] > IF_GRID_SPACING ) {
      disp[dim] = IF_GRID_SPACING;
    }
    else if( disp[dim] < ( IF_GRID_SPACING * -1.0 ) ) {
      disp[dim] = IF_GRID_SPACING * -1.0;
    }
  }

  /* MODEL END */

  return;
}

void ModelRoutine::divideSpAgent( const VIdx& vIdx, const AgentJunctionInfo& junctionInfo, const VReal& vOffset, const AgentMechIntrctData& mechIntrctData, const Vector<NbrBox<REAL> >& v_gridPhiNbrBox/* [elemIdx] */, const Vector<NbrBox<REAL> >& v_gridModelRealNbrBox/* [elemIdx] */, const Vector<NbrBox<S32> >& v_gridModelIntNbrBox/* [elemIdx] */, SpAgentState& motherState/* INOUT */, VReal& motherDisp, SpAgentState& daughterState, VReal& daughterDisp, Vector<BOOL>& v_junctionDivide, BOOL& motherDaughterLinked, JunctionEnd& motherEnd, JunctionEnd& daughterEnd ) {
  /* MODEL START */

  ERROR( "unimplemented." );
  
  /* MODEL END */

  return;
}
#endif

