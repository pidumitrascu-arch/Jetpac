#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


double current_time, last_time;

// ---- Variables Globales ----
const int scale = 3;

const unsigned int screenX = 256 * scale;
const unsigned int screenY = 192 * scale;

const int wX = 800, wY = 600;

int fps = 60;


struct Bonus //Struct Bonus items
{
    esat::SpriteTransform BonusTransform;
    float x, y;
    int BonusDirection;
    float BonusSpeed;
    bool active = false;
    esat::SpriteHandle sprite;
};

Bonus* bonus = nullptr;

void SpritesBonus() //Aquí imprimo los sprites de los diferentes Bonus que hay.

    Bonus* bn = bonus;
{
    bn->sprite = esat::SpriteFromFile("./Recursos/Diamond.png");

    bn->sprite = esat::SpriteFromFile("./Recursos/Geode.png");
    
    bn->sprite = esat::SpriteFromFile("./Recursos/Dablooon.png");

    bn->sprite = esat::SpriteFromFile("./Recursos/Triangle.png");

    bn->sprite = esat::SpriteFromFile("./Recursos/Bomb.png");

    //A continuación haremos que aparezcan en pantalla en sitios aleatorios y en caso que no haya suelo, q caiga dentro del rectángulo del suelo, para que no se pierda el Bonus.
    
}

void InitBonus(Bonus* bn)
{
    bn->active = false;
    bn->x = 0.0f;
    bn->y = 0.0f;
    bn->BonusSpeed = 0.0f;

}

void SpawnFuel()
{
    bonus->active = true;
    bonus->x = rand() % (wX - 50); //Genera una posición X aleatoria dentro de los límites de la pantalla
    bonus->y = 0.0f;
}

void BonusMov(Bonus* bonus)
{
    
}

void DrawBonus()
{

}



int esat::main(int argc, char **argv)
{

    srand(time(NULL));

    esat::WindowInit(screenX, screenY);
    esat::WindowSetMouseVisibility(true);

    while (esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape))
    {

        last_time = esat::Time();
        esat::DrawBegin();
        esat::DrawClear(0, 0, 0);




        esat::DrawEnd();

        // Control fps
        do {

            current_time = esat::Time();

        } while ((current_time - last_time) <= 1000.0 / fps);

        esat::WindowFrame();
    }

    esat::WindowDestroy();

    return 0;
}