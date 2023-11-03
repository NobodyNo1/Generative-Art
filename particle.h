#include "pvector.h"
#include "raylib.h"
#include <stdio.h>

#ifndef PARTICLE_H
#define PARTICLE_H

// if enabled particles outside of windows jumps back from other side
#define IS_WRAP_WINDOW_ENABLED 0

float velLimit = 5.0f;


typedef struct Particle {
    PVector2* velocity;
    PVector2* position;
} Particle;

void vmod(PVector2* position, float width, float height);
float cmod(float a, float b);

void UpdateParticle(Particle* particle, int width, int height) {
    PVlimit(particle->velocity, velLimit);
    PVadd(particle->position, particle->velocity);
#if IS_WRAP_WINDOW_ENABLED
    vmod(particle->position, (float)width, (float)height);
#endif
}

void DrawParticle(Particle* particle) {
    DrawCircle(
        particle->position->x,
        particle->position->y,
        2,
        SKYBLUE
    );
}


void vmod(PVector2* position, float width, float height){
    position->x = cmod(position->x, width);
    position->y = cmod(position->y, height);
}


float cmod(float a, float b) {
    float num = a;
    while(num > b){
        num -= b;
    }
    while(num < 0){
        num += b;
    }
    return num;
}

#endif