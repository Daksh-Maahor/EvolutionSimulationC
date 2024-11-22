#ifndef GAME_H_
#define GAME_H_

#include "Window.h"
#include "Utils.h"

#define HALF_ENTITY_WIDTH      5
#define ENTITY_VELOCITY        5
#define PI                     3.14
#define ENTITY_OMEGA           (PI) / 90
#define HALF_PREDATOR_FOV      (PI) / 6
#define HALF_PREY_FOV          (PI) / 3
#define NUM_RAYS_PREY          20
#define NUM_RAYS_PREDATOR      10
#define PREDATOR_FOV_RANGE     200
#define PREY_FOV_RANGE         100
#define NUM_ENTITIES_EACH_TYPE 1

typedef struct
{
    float x;
    float y;
    float theta;
    float omega;
    float vel;

    float dMin; // min distance of predator
    float dTheta; // angle at which predator is
} Prey;

typedef struct
{
    float x;
    float y;
    float theta;
    float omega;
    float vel;

    float dMin; // min distance of prey
    float dTheta; // angle at which prey is
} Predator;

typedef struct
{
    Predator* predators[NUM_ENTITIES_EACH_TYPE];
    Prey* preys[NUM_ENTITIES_EACH_TYPE];
} Game;

Prey* InitialisePrey(Window* window);
void UpdatePrey(Window* window, Prey* prey, Game* game, InputManager* inputManager);
void RenderPrey(Window* window, Prey* prey);
void PreyCastRay(Window* window, Prey* prey, Game* game);


Predator* InitialisePredator(Window* window);
void UpdatePredator(Window* window, Predator* predator, Game* game, InputManager* inputManager);
void RenderPredator(Window* window, Predator* predator);
void PredatorCastRay(Window* window, Predator* prey, Game* game);

void InitializeGame(Window* window, Game* game);
void RenderGame(Window* window, Game* game, InputManager* inputManager);
void DestroyGame(Game* game);

#endif
