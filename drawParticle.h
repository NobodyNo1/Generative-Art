
#include <raylib.h>
#include "particle.h"
#include <time.h>
#include <stdlib.h>

int LimRand(int lim) {
	return (rand() % lim);
}

float LimRandF(float lim){
	return ((float)rand()/(float)(RAND_MAX)) * lim;
}

void draw(Particle** particles);

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

	Particle** particles = (Particle**) malloc(PARTICLE_AMOUNT* sizeof(Particle*));
	for (int i = 0; i < PARTICLE_AMOUNT; i++)
	{
		PVector2* position = PVfromCord(
			LimRandF(WINDOW_WIDTH),
			LimRandF(WINDOW_HEIGHT)
		);
		PVector2* velocity = PVfromAngle(LimRandF(2*PI));
		PVmult(velocity, LimRandF(velLimit));
		Particle* particle = (Particle*) malloc(sizeof(Particle));
		particle->position = position;
		particle->velocity = velocity;
		particles[i] = particle;
	}
	bool windowClearedOnce = false;
	while(!WindowShouldClose()){

		//0000
#if BACKGROUND_CLEAR_ENABLED
		BeginDrawing();
			ClearBackground(BLACK);
			draw(particles);
		EndDrawing();
#else	
		BeginTextureMode(framebuffer); 
			if(!windowClearedOnce) {
				ClearBackground(BLACK);
				windowClearedOnce = true;
			}
			draw(particles);
		EndTextureMode();

		BeginDrawing();
		 	DrawTextureRec(
				framebuffer.texture, 
				textureSource,
				texturePosition,
				WHITE
			);
		EndDrawing();
#endif
		for (int i = 0; i < PARTICLE_AMOUNT; i++)
		{
			UpdateParticle(particles[i], WINDOW_WIDTH, WINDOW_HEIGHT);
		}
	}

	return 0;
}


void draw(Particle** particles) {
	for (int i = 0; i < PARTICLE_AMOUNT; i++)
	{
			DrawParticle(particles[i]);
	}
	DrawText("HELLO", WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 22, BLACK);
}