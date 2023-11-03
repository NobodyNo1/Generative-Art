#include <math.h>
#include <stdlib.h>

#ifndef PVECTOR_H
#define PVECTOR_H

typedef struct PVector2
{
    float x;
    float y;
} PVector2;


void PVsubCopy(PVector2* v, PVector2* toSub, PVector2* target) {
    
    target->x = v->x - toSub->x;
    target->y = v->y - toSub->y;
}

void PVsub(PVector2* v, PVector2* toSub) {
    v->x -= toSub->x;
    v->y -= toSub->y;
}

void PVadd(PVector2* v, PVector2* toAdd) {
    v->x += toAdd->x;
    v->y += toAdd->y;
}

void PVmult(PVector2* vector, float n) {
    vector->x *= n;
    vector->y *= n;
}

void PVdiv(PVector2* vector, float n) {
    vector->x /= n;
    vector->y /= n;
}

float PVmag(PVector2* vector) {
    return (float) sqrt(vector->x*vector->x + vector->y*vector->y);
}

float PVnormalize(PVector2* vector) {
    float m = PVmag(vector);
    if (m != 0 && m != 1) {
      PVdiv(vector, m);
    }
}

float PVmagSq(PVector2* vector){
    return ((vector->x * vector->x) + (vector->y * vector->y));
}

float PVlimit(PVector2* vector, float max) {
    if(PVmagSq(vector) > max) {
      PVnormalize(vector);
      PVmult(vector, max);
    }
}
void PVsetMag(PVector2* vector, float len) {
    PVnormalize(vector);
    PVmult(vector, len);
}

PVector2* PVfromAngle(float angle) {
    PVector2* vector = (PVector2*) malloc(sizeof(PVector2));
    vector->x=(float) cos(angle);
    vector->y=(float) sin(angle);
    return vector;
}

float dist(PVector2* v, PVector2* toV) {
    float dx = v->x - toV->x;
    float dy = v->y - toV->y;
    return (float) sqrt(dx*dx + dy*dy);
}

PVector2* PVfromCord(float x, float y) {
    PVector2* vector = (PVector2*) malloc(sizeof(PVector2));
    vector->x=x;
    vector->y=y;
    return vector;
}

#endif