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
void ModelRoutine::initJunctionSpAgent( const VIdx& vIdx0, const SpAgent& spAgent0, const VIdx& vIdx1, const SpAgent& spAgent1, const VReal& dir/* unit direction vector from spAgent1 to spAgent0 */, const REAL& dist, BOOL& link, JunctionEnd& end0/* dummy if link == false */, JunctionEnd& end1/* dummy if link == false */
                                        ) {
  /* MODEL START */

  link = false;

  /* MODEL END */

  return;
}

void ModelRoutine::computeForceSpAgent( const VIdx& vIdx0, const SpAgent& spAgent0, const Vector<REAL>& v_gridPhi0/* [elemIdx] */, const Vector<REAL>& v_gridModelReal0/* [elemIdx] */, const Vector<S32>& v_gridModelInt0/* [elemIdx] */, const VIdx& vIdx1, const SpAgent& spAgent1, const Vector<REAL>& v_gridPhi1/* [elemIdx] */, const Vector<REAL>& v_gridModelReal1/* [elemIdx] */, const Vector<S32>& v_gridModelInt1/* [elemIdx] */, const VReal& dir/* unit direction vector from spAgent1 to spAgent0 */, const REAL& dist, VReal& force/* force on spAgent0 due to interaction with spAgent1 (force on spAgent1 due to interaction with spAgent0 has same magnitude but the opposite direction), if force has the same direction with dir, two cells push each other, if has the opposite direction, two cells pull each other. */ ) {
  /* MODEL START */

  REAL R = spAgent0.state.getRadius() + spAgent1.state.getRadius();
  REAL mag;/* + for repulsive force, - for adhesive force */

  if( dist <= R ) {/* shoving */
    REAL rigidity = (A_CELL_RIGIDITY[spAgent0.state.getType()] + A_CELL_RIGIDITY[spAgent1.state.getType()])/2.0;
    mag = rigidity * ( R - dist );
  }
  else {/* adhesion */
    REAL x = dist / R;
    REAL a = ADHESION_A[spAgent0.state.getType()][spAgent1.state.getType()];
    mag = -a * ( dist - R ) * exp( -1.0 * ( x - 1.0 ) * ( x - 1.0 ) / A_ADHESION_SCALE );
  }

  for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
    force[dim] = mag * dir[dim];
  }

  /* MODEL END */

  return;
}

void ModelRoutine::computeExtraMechIntrctSpAgent( const VIdx& vIdx0, const SpAgent& spAgent0, const Vector<REAL>& v_gridPhi0/* [elemIdx] */, const Vector<REAL>& v_gridModelReal0/* [elemIdx] */, const Vector<S32>& v_gridModelInt0/* [elemIdx] */, const VIdx& vIdx1, const SpAgent& spAgent1, const Vector<REAL>& v_gridPhi1/* [elemIdx] */, const Vector<REAL>& v_gridModelReal1/* [elemIdx] */, const Vector<S32>& v_gridModelInt1/* [elemIdx] */, const VReal& dir/* unit direction vector from spAgent1 to spAgent0 */, const REAL& dist, ExtraMechIntrctData& extraMechIntrctData0, ExtraMechIntrctData& extraMechIntrctData1, BOOL& link, JunctionEnd& end0/* dummy if link == false */, JunctionEnd& end1/* dummy if link == false */, BOOL& unlink ) {
  /* MODEL START */

  link = false;
  unlink = false;

  REAL R = spAgent0.state.getRadius() + spAgent1.state.getRadius();
  REAL x = dist / R;
  if (x < 2.0) {
    link = true;
    end0.setType(0);
    end1.setType(0);
  } else if (spAgent0.junctionInfo.isLinked(spAgent1.junctionInfo)) {
    unlink = true;
  }

  /* MODEL END */

  return;
}
#endif

