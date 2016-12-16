/*

Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

#ifndef __MY_DEFINE_H__
#define __MY_DEFINE_H__

#include "biocellion.h"

/* define constants to be used inside model functions */

/* MODEL START */

#ifndef PARAMETER_DEFINES
#define PARAMETER_DEFINES
#define AA_ADHESION 0.01                /* 0.01 - 0.10 */
#define A_TEMP 0.01                     /* */
#define A_RIGIDITY 0.01                 /* */
#define A_RADIUS 1.0
#define BASELINE_TIMESTEP 1.0
#define STEPS_PER_BASELINE_TIMESTEP 1
#define ADHESION_SCALE 0.5
#define A_SECRETE_RATE 0.15             /* 0.01 -  0.15 */
#define A_CHEMOTAXIS_FORCE_STRENGTH 0.5 /* 0.10 - 10.00 */
#define A_CHEMO_DECAY_RATE 0.15         /* 0.01 -  0.15 */
#define A_CHEMO_DIFFUSION 1.0           /* ??? */
#define A_INITIAL_CELL_DENSITY 1.0      /* ??? */
#endif


const REAL MY_PI = 3.14159265358979323846;

typedef enum _cell_type_e {
	CELL_TYPE_A,
	NUM_CELL_TYPES
} cell_type_e;

typedef enum _diffusible_elem_e {
	DIFFUSIBLE_ELEM_CHEMOATTRACTANT,
	NUM_DIFFUSIBLE_ELEMS
} diffusible_elem_e;

typedef enum _grid_model_real_e {
	NUM_GRID_MODEL_REALS
} grid_model_real_e;

typedef enum _model_rng_type_e {
	MODEL_RNG_UNIFORM,
	MODEL_RNG_GAUSSIAN,
	NUM_MODEL_RNGS
} model_rng_type_e;

const REAL IF_GRID_SPACING = 2.0;

const REAL A_CELL_RADIUS[NUM_CELL_TYPES] = { A_RADIUS };
const REAL A_CELL_DENSITY_PER_UB[NUM_CELL_TYPES] = { A_INITIAL_CELL_DENSITY };
const REAL A_CELL_D_MAX[NUM_CELL_TYPES] = { IF_GRID_SPACING };
const REAL A_CELL_CHEMOATTRACTANT_SECRETION_RATE[NUM_CELL_TYPES] = { A_SECRETE_RATE };
const REAL A_CELL_CHEMOTAXIS_FORCE_STRENGTH[NUM_CELL_TYPES] = { A_CHEMOTAXIS_FORCE_STRENGTH };

const REAL A_CELL_TEMP[NUM_CELL_TYPES] = { A_TEMP };
const REAL ADHESION_A[NUM_CELL_TYPES][NUM_CELL_TYPES] = { { AA_ADHESION } };
const REAL A_CELL_RIGIDITY[NUM_CELL_TYPES] = { A_RIGIDITY };

const REAL DIFFUSIBLE_ELEM_DECAY_RATE[NUM_DIFFUSIBLE_ELEMS] = { A_CHEMO_DECAY_RATE };
const REAL DIFFUSIBLE_ELEM_DIFFUSION_COEFFICIENT[NUM_DIFFUSIBLE_ELEMS] = { A_CHEMO_DIFFUSION };

const REAL BASELINE_TIME_STEP = BASELINE_TIMESTEP;
const S32  STEPS_PER_BASELINE = STEPS_PER_BASELINE_TIMESTEP;

const REAL A_ADHESION_SCALE = ADHESION_SCALE;

/* MODEL END */

#endif/* #ifndef __MY_DEFINE_H__ */

