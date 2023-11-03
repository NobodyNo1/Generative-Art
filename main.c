// REFERENCE: https://www.youtube.com/watch?v=MgH3CB9Pm40

#define BACKGROUND_CLEAR_ENABLED    0


#define WINDOW_HEIGHT   900 
#define WINDOW_WIDTH    900
#define PARTICLE_AMOUNT 100


#define STING_PARTICLES         1
#define POINT_PARTICLES         2

#define PARICLE_TYPE    STING_PARTICLES

#if     PARICLE_TYPE == STING_PARTICLES
#include "drawStrings.h"
#elif   PARICLE_TYPE == POINT_PARTICLES
#include "drawParticle.h"
#endif