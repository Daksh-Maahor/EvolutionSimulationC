#include "Game.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>

Prey* InitialisePrey(Window* window)
{
    Prey* prey = (Prey*)malloc(sizeof(Prey));
    prey->x = rand() % window->width;
    prey->y = rand() % window->height;
    prey->theta = (float)(rand() % 36000) / 100.0f;
    prey->omega = 0;
    prey->vel = 0;
    prey->dMin = 0;
    prey->dTheta = 0;
    return prey;
}

void UpdatePrey(Window* window, Prey* prey, Game* game, InputManager* inputManager)
{
    // move prey
    float tx = prey->x + prey->vel * cosf(prey->theta);
    float ty = prey->y + prey->vel * sinf(prey->theta);

    if (tx < 0)
    {
        tx += window->width;
    }
    else if (tx >= window->width)
    {
        tx -= window->width;
    }

    if (ty < 0)
    {
        ty += window->height;
    }
    else if (ty >= window->height)
    {
        ty -= window->height;
    }

    prey->x = tx;
    prey->y = ty;

    // rotate prey
    prey->theta += prey->omega;

    // cast rays
    PreyCastRay(window, prey, game);

//    printf("\n\n\n");
//    printf("Prey : \n");
//    printf("Min Dist from predator : %f\n", prey->dMin);
//    printf("Angle : %f\n", prey->dTheta);
}

void RenderPrey(Window* window, Prey* prey)
{
    FillRect(window, prey->x - HALF_ENTITY_WIDTH, prey->y - HALF_ENTITY_WIDTH, 2 * HALF_ENTITY_WIDTH + 1, 2 * HALF_ENTITY_WIDTH + 1, 0, 255, 0);

    // render viewframe
/** for (float dtheta = -HALF_PREY_FOV; dtheta <= HALF_PREY_FOV; dtheta += (2 * HALF_PREY_FOV) / NUM_RAYS_PREY)
    {
        DrawLine(window, (float) prey->x, (float) prey->y, (float) prey->x + PREY_FOV_RANGE * cosf(prey->theta + dtheta), (float) prey->y + PREY_FOV_RANGE * sinf(prey->theta + dtheta), 0, 0, 255);
    } */
}

void PreyCastRay(Window* window, Prey* prey, Game* game)
{
    prey->dMin = PREY_FOV_RANGE;
    prey->dTheta = 0;
    for (float dTheta = -HALF_PREY_FOV; dTheta <= HALF_PREY_FOV; dTheta += (2 * HALF_PREY_FOV) / NUM_RAYS_PREY)
    {
        float theta = prey->theta + dTheta;
        float d = 0;
        float xMin = prey->x + PREY_FOV_RANGE * cos(theta);;
        float yMin = prey->y + PREY_FOV_RANGE * sin(theta);
        while (d <= PREY_FOV_RANGE)
        {
            float x = prey->x + d * cos(theta);
            float y = prey->y + d * sin(theta);

            int struck = 0;

            for (int i = 0; i < NUM_ENTITIES_EACH_TYPE; i++)
            {
                if (fabsf(x - game->predators[i]->x) <= HALF_ENTITY_WIDTH && fabsf(y - game->predators[i]->y) <= HALF_ENTITY_WIDTH)
                {
                    //printf("Prey saw Predator\n");
                    // ray struck predator
                    if (d < prey->dMin)
                    {
                        prey->dMin = d;
                        prey->dTheta = dTheta;
                        xMin = x;
                        yMin = y;
                    }
                    struck = 1;
                    break;
                }
            }

            if (struck > 0)
            {
                break;
            }

            d++;
        }

        DrawLine(window, (float) prey->x, (float) prey->y, xMin, yMin, 0, 0, 255);
    }
    //printf("Line drawn");
    /**for (float dtheta = -HALF_PREY_FOV; dtheta <= HALF_PREY_FOV; dtheta += (2 * HALF_PREY_FOV) / NUM_RAYS_PREY)
    {

    }*/
}



Predator* InitialisePredator(Window* window)
{
    Predator* predator = (Predator*)malloc(sizeof(Predator));
    predator->x = rand() % window->width;
    predator->y = rand() % window->height;
    predator->theta = (float)(rand() % 36000) / 100.0f;
    predator->omega = 0;
    predator->vel = 0;
    predator->dMin = 0;
    predator->dTheta = 0;
    return predator;
}

void UpdatePredator(Window* window, Predator* predator, Game* game, InputManager* inputManager)
{
    // move predator
    float tx = predator->x + predator->vel * cosf(predator->theta);
    float ty = predator->y + predator->vel * sinf(predator->theta);

    if (tx < 0)
    {
        tx += window->width;
    }
    else if (tx >= window->width)
    {
        tx -= window->width;
    }

    if (ty < 0)
    {
        ty += window->height;
    }
    else if (ty >= window->height)
    {
        ty -= window->height;
    }

    predator->x = tx;
    predator->y = ty;

    // rotate predator
    predator->theta += predator->omega;

    // cast rays
    PredatorCastRay(window, predator, game);

//    system("cls");
//    printf("\n\n\n");
//    printf("Predator : \n");
//    printf("Min Dist from prey : %f\n", predator->dMin);
//    printf("Angle : %f\n", predator->dTheta);
}

void RenderPredator(Window* window, Predator* predator)
{
    FillRect(window, predator->x - HALF_ENTITY_WIDTH, predator->y - HALF_ENTITY_WIDTH, 2 * HALF_ENTITY_WIDTH + 1, 2 * HALF_ENTITY_WIDTH + 1, 255, 0, 0);
    
    // render viewframe
/** for (float dtheta = -HALF_PREDATOR_FOV; dtheta <= HALF_PREDATOR_FOV; dtheta += (2 * HALF_PREDATOR_FOV) / NUM_RAYS_PREDATOR)
    {
        DrawLine(window, (float) predator->x, (float) predator->y, (float) predator->x + PREDATOR_FOV_RANGE * cosf(predator->theta + dtheta), (float) predator->y + PREDATOR_FOV_RANGE * sinf(predator->theta + dtheta), 0, 0, 255);
    }*/
}

void PredatorCastRay(Window* window, Predator* predator, Game* game)
{
    predator->dMin = PREDATOR_FOV_RANGE;
    predator->dTheta = 0;
    for (float dTheta = -HALF_PREDATOR_FOV; dTheta <= HALF_PREDATOR_FOV; dTheta += (2 * HALF_PREDATOR_FOV) / NUM_RAYS_PREDATOR)
    {
        float theta = predator->theta + dTheta;
        float d = 0;
        float xMin = predator->x + PREDATOR_FOV_RANGE * cos(theta);;
        float yMin = predator->y + PREDATOR_FOV_RANGE * sin(theta);
        while (d <= PREDATOR_FOV_RANGE)
        {
            float x = predator->x + d * cos(theta);
            float y = predator->y + d * sin(theta);

            int struck = 0;
            
            for (int i = 0; i < NUM_ENTITIES_EACH_TYPE; i++)
            {
                if (fabsf(x - game->preys[i]->x) <= HALF_ENTITY_WIDTH && fabsf(y - game->preys[i]->y) <= HALF_ENTITY_WIDTH)
                {
                    //printf("Predator saw Prey\n");
                    // ray struck prey
                    if (d < predator->dMin)
                    {
                        predator->dTheta = dTheta;
                        predator->dMin = d;
                        xMin = x;
                        yMin = y;
                    }
                    struck = 1;
                    break;
                }
            }

            if (struck > 0)
            {
                break;
            }

            d++;
        }

        DrawLine(window, (float) predator->x, (float) predator->y, xMin, yMin, 255, 255, 0);
    }
    //printf("Line drawn");
    /**for (float dtheta = -HALF_PREY_FOV; dtheta <= HALF_PREY_FOV; dtheta += (2 * HALF_PREY_FOV) / NUM_RAYS_PREY)
    {

    }*/
}



void InitializeGame(Window* window, Game* game)
{
    for (int i = 0; i < NUM_ENTITIES_EACH_TYPE; i++)
    {
        game->predators[i] = InitialisePredator(window);
        game->preys[i] = InitialisePrey(window);
    }
}

void RenderGame(Window* window, Game* game, InputManager* inputManager)
{
    FillRect(window, 0, 0, window->width, window->height, 0, 0, 0);
    for (int i = 0; i < NUM_ENTITIES_EACH_TYPE; i++)
    {
        UpdatePredator(window, game->predators[i], game, inputManager);
        RenderPredator(window, game->predators[i]);
        UpdatePrey(window, game->preys[i], game, inputManager);
        RenderPrey(window, game->preys[i]);
    }
}

void DestroyGame(Game* game)
{
    for (int i = 0; i < NUM_ENTITIES_EACH_TYPE; i++)
    {
        free(game->predators[i]);
        free(game->preys[i]);
    }
}
