/*
    Spring-Line like particle
*/

#include "particle.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef SPARTICLE_H
#define SPARTICLE_H

#define POTENTIAL_STRENGTH_INTENSITY    1
#define VARIATIC_COLOR                  1

#define NEW_UPDATE
#define POTENTIAL_RADIUS    0.2f
#define POTENTIAL_STRENGTH  0.00000005 * POTENTIAL_STRENGTH_INTENSITY
#define POTENTIAL_POWER     2.0f


typedef struct PColor {
    int red;
    int green;
    int blue;
    int alpha;
} PColor;

typedef struct SParticle {
    Particle** points;
    int particleSize;
    float* springConstants;
    float* distances;
    PColor* color;
} SParticle;

PVector2 speed = {
    0.0f, -0.001
};
PVector2* dir;
PVector2* dVec;

SParticle *CreateSParticle(
    Particle** particles,
    int particleSize,
    float* constants,
    float* dists,
    PColor* color
){
    SParticle* sparticle = (SParticle*) malloc(sizeof(SParticle));
    sparticle->points           = particles;
    sparticle->particleSize     = particleSize;
    sparticle->springConstants  = constants;
    sparticle->distances        = dists;
    sparticle->color            = color;
	dir = (PVector2*) malloc(sizeof(PVector2));
    dVec = (PVector2*) malloc(sizeof(PVector2));
    return sparticle;
}


SParticle *UpdateSParticleData(
    SParticle* sparticle,
    Particle** particles,
    int particleSize,
    float* constants,
    float* dists,
    PColor* color
){
    sparticle->points           = particles;
    sparticle->particleSize     = particleSize;
    sparticle->springConstants  = constants;
    sparticle->distances        = dists;
    sparticle->color            = color;
    memset(dir,  0, sizeof(PVector2));
    memset(dVec, 0, sizeof(PVector2));
    return sparticle;
}

void UpdateSParticle(SParticle* sparicle, int width, int height) {
    for (int i = 0; i < sparicle->particleSize; i++)
    {
        if(i < sparicle->particleSize - 1) {

            PVsubCopy(
                sparicle->points[i+1]->position,
                sparicle->points[i]->position,
                dir
            );
            float d = PVmag(dir);
            PVsetMag(dir, 1);
            float something = sparicle->springConstants[i] * (
                d - sparicle->distances[i]
            );
            PVmult(dir, something);
            PVadd(
                sparicle->points[i]->velocity,
                dir
            );
            PVmult(dir, -1);
            PVadd(
                sparicle->points[i+1]->velocity,
                dir
            );
        }
#ifdef NEW_UPDATE
        dVec->x = sparicle->points[i]->position->x - width/2.0;
        dVec->y = sparicle->points[i]->position->y - height/2.0;
        if(PVmag(dVec) < POTENTIAL_RADIUS * ((float)(width+ height)/2.0)){
            PVmult(
                dVec,
                POTENTIAL_STRENGTH * pow(
                    PVmag(dVec), 
                    POTENTIAL_POWER
                )
            );
            PVadd(
                sparicle->points[i]->velocity,
                dVec
            );
        }
#endif
        PVadd(
            sparicle->points[i]->velocity,
            &speed
        );

        UpdateParticle(sparicle->points[i], width, height);
    }
    
}

void DrawSParticle(
    SParticle* sparicle, 
    PVector2* windowCenter,
    int width, int height
) {
#if VARIATIC_COLOR == 0
    Color rayColor = {
        .r = sparicle->color->red,
        .g = sparicle->color->green,
        .b = sparicle->color->blue,
        .a = sparicle->color->alpha
    };
#endif
    for (int i = 0; i < sparicle->particleSize; i++)
    {
#if VARIATIC_COLOR == 1
        float distanceToCenter = dist(
            sparicle->points[i]->position,
            windowCenter
        );
        Color rayColor = {
            .r = sparicle->color->red   * ((distanceToCenter/ width) *4),
            .g = sparicle->color->green * (1.0 + distanceToCenter/ width),
            .b = sparicle->color->blue,
            .a = sparicle->color->alpha * (1.0+ (distanceToCenter / width) * distanceToCenter/10)
        };

#endif
        if(i < sparicle->particleSize - 1)
        {
            PVector2* cur = sparicle->points[i]->position;
            PVector2* next = sparicle->points[i+1]->position;
            DrawLine(
                cur->x, cur->y,
                next->x, next->y,
                rayColor//SKYBLUE
                //TODO: sparicle->color
            );
        }
    }
}

#endif