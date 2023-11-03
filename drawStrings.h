
#include <raylib.h>
#include "particle.h"
#include <time.h>
#include <stdlib.h>
#include "sparticle.h"

#define STARTS_AT_THE_CENTER 1

int LimRand(int lim) {
	return (rand() % lim);
}

float LimRandF(float lim){
	return ((float)rand()/(float)(RAND_MAX)) * lim;
}

float LimRandRangeF(float min, float max){
	return ((float)rand()/(float)(RAND_MAX)) * (max - min) + min;
}

void draw(SParticle* sparticle);
void drawOver();

float* constan;
float* distanc;
Particle** particles;
SParticle* sparticle;
PVector2 windowCenter = {
	(float)WINDOW_WIDTH/2.0,
	(float)WINDOW_HEIGHT/2.0
};
void initSparticle(PColor *color);
void cleanData();

int main() {
	srand(time(NULL));
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "generative art");
	SetTargetFPS(60);
	// Create a render texture (framebuffer)
    RenderTexture2D framebuffer = LoadRenderTexture(
		WINDOW_WIDTH, 
		WINDOW_HEIGHT
	);
	Vector2 texturePosition;
    texturePosition.x = 0.0f;
    texturePosition.y = 0.0f;
	Rectangle textureSource = {
		0.0f, 0.0f, WINDOW_WIDTH, -WINDOW_HEIGHT
	};
	PColor color =  {
		.red = 90,
		.green = 100, 
		.blue = 250, 
		.alpha = 5
	};
	constan = (float*) malloc((PARTICLE_AMOUNT-1)* sizeof(float));
    distanc = (float*) malloc((PARTICLE_AMOUNT-1)* sizeof(float));
	particles = (Particle**) malloc(PARTICLE_AMOUNT* sizeof(Particle*));
	
	initSparticle(&color);

	printf("PARTICLE SIZE: %d\n", sparticle->particleSize);
	bool windowClearedOnce = false;
	while(!WindowShouldClose()){
		if(IsKeyPressed(KEY_R)){
			printf("Restart!\n");
			cleanData();
			initSparticle(&color);
			windowClearedOnce = false;
		}
#if BACKGROUND_CLEAR_ENABLED
		BeginDrawing();
			ClearBackground(BLACK);
			draw(sparticle);
			drawOver();
		EndDrawing();
#else	
		BeginTextureMode(framebuffer); 
			if(!windowClearedOnce) {
				ClearBackground(BLACK);
				windowClearedOnce = true;
			}
			draw(sparticle);
		EndTextureMode();

		BeginDrawing();
		 	DrawTextureRec(
				framebuffer.texture, 
				textureSource,
				texturePosition,
				WHITE
			);
			drawOver();
		EndDrawing();
#endif

		UpdateSParticle(sparticle, WINDOW_WIDTH, WINDOW_HEIGHT);
	}

	return 0;
}

int textPadding = 20;
int textSize 	= 22;
void draw(SParticle* sparticle) { 
	DrawSParticle(sparticle, &windowCenter, WINDOW_WIDTH, WINDOW_HEIGHT);
	
}

float drawStart = 0.0f;
float maxTextVisibleTime = 3.0;
Color textColor = {
	.r = 255, .g = 255, .b = 255, .a = 255
};

void drawOver() {
	DrawText("HELLO", WINDOW_WIDTH/2, WINDOW_HEIGHT/2, textSize, BLACK);
	float deltaT = GetTime() - drawStart;
	if(deltaT < maxTextVisibleTime) {
		// 0 1
		float halfTime = maxTextVisibleTime/2.0;

		float alphaMulti = ((GetTime() - drawStart)/halfTime);
		if(deltaT >= halfTime && 0.0 < alphaMulti){
			alphaMulti = 1.0 - alphaMulti;
		}
		textColor.a = (int)(255 * alphaMulti) ;
		DrawText(
			TextFormat("Press 'R' to restart"),
			WINDOW_WIDTH/2 - 22*4, 
			WINDOW_HEIGHT-textSize-textPadding,
			textSize,
			textColor
		);
	}
}

void cleanData() {
	for (int i = 0; i < PARTICLE_AMOUNT; i++)
	{
		free(particles[i]->position);
		free(particles[i]->velocity);
	}
}

void initSparticle(PColor *color) {
	drawStart = GetTime();
	memset(constan, 0,(PARTICLE_AMOUNT-1)* sizeof(float));
   	memset(distanc, 0, (PARTICLE_AMOUNT-1)* sizeof(float));
	
    //Particle** particles = (Particle**) malloc(PARTICLE_AMOUNT* sizeof(Particle*));
	for (int i = 0; i < PARTICLE_AMOUNT; i++)
	{
#if STARTS_AT_THE_CENTER
		PVector2* position = PVfromCord(
			WINDOW_WIDTH/2,
			WINDOW_HEIGHT/2
		);
#else
		PVector2* position = PVfromCord(
			LimRandF(WINDOW_WIDTH),
			LimRandF(WINDOW_HEIGHT)
		);
#endif
		PVector2* velocity = PVfromAngle(LimRandF(2*PI));
		PVmult(velocity, LimRandF(velLimit));

		Particle* particle = (Particle*) malloc(sizeof(Particle));
		particle->position = position;
		particle->velocity = velocity;
		particles[i] = particle;
        if( i < PARTICLE_AMOUNT - 1){
            constan[i] = 0.04f;
            distanc[i] = LimRandRangeF(WINDOW_WIDTH/400, WINDOW_WIDTH/40);
		}
	}
	
	if(sparticle == NULL)
		sparticle = CreateSParticle(
			particles,
			PARTICLE_AMOUNT,
			constan,
			distanc,
			color 
		);
	else
		UpdateSParticleData(
			sparticle,
			particles,
			PARTICLE_AMOUNT,
			constan,
			distanc,
			color
		);
}