#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define num_bonus 5 //cantidad de bonus items

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
{
    bonus[0].sprite = esat::SpriteFromFile("./Recursos/Diamond.png");

    bonus[1].sprite = esat::SpriteFromFile("./Recursos/Geode.png");
    
    bonus[2].sprite = esat::SpriteFromFile("./Recursos/Dablooon.png");

    bonus[3].sprite = esat::SpriteFromFile("./Recursos/Triangle.png");

    bonus[4].sprite = esat::SpriteFromFile("./Recursos/Bomb.png");   
}

void InitBonus(Bonus* bn) //posicion y estado inicial de los bonus items
{
    bn->active = false;
    bn->x = 0.0f;
    bn->y = 0.0f;
    bn->BonusSpeed = 0.0f;

}

void SpawnBonus(int index) //posicion y estado de los bonus items cuando aparecen
{
    Bonus* bn = bonus + index;

    bn->active = true;
    bn->x = rand() % (wX - 50); //Genera una posición X aleatoria dentro de los límites de la pantalla
    bn->y = 0.0f;
    bn->BonusSpeed = 2.0f + rand()%3;
}

bool OneBonusAtATime() //para que aparezca solo uno a la vez
{
    for(int i = 0; i < num_bonus; ++i){
        if(bonus[i].active) {
            return true;
        }
    }
    return false;
}

void BonusMov()//animacion
{
    for(int i = 0; i < num_bonus; ++i){

        Bonus* bn = bonus + i;

        if(bn->active){
            bn->y += bn->BonusSpeed;

            if(bn->y > wY){
                bn->active = false;
            }

            if(bn->y > 510){//si toca el suelo
                bn->y = 510;
            }
        }
    }
}

void DrawBonus()
{
    for(int i = 0; i < num_bonus; ++i){

        Bonus* bn = bonus + i;

        if(bn->active){
            esat::DrawSprite(bn->sprite, bn->x, bn->y);
        }
    }
}

void RunBonus()
{
    static double last_spawn = 0; //Con static: la variable conserva su valor entre llamadas.

    if(current_time - last_spawn > 8000 && !OneBonusAtATime()){
    int random_bonus = rand() % num_bonus;
    SpawnBonus(random_bonus);
    last_spawn = current_time;}

    BonusMov();
    DrawBonus();
}

int esat::main(int argc, char **argv)
{

    srand(time(NULL));

    bonus = (Bonus*)malloc(sizeof(Bonus) * num_bonus);

    for(int i = 0; i < num_bonus; ++i){
        InitBonus(&bonus[i]);
    }
    
    esat::WindowInit(screenX, screenY);
    esat::WindowSetMouseVisibility(true);

    SpritesBonus();

    while (esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape))
    {
        // Control fps
        do {

            current_time = esat::Time();

        } while ((current_time - last_time) <= 1000.0 / fps);

        last_time = esat::Time();
        esat::DrawBegin();
        esat::DrawClear(255, 255, 255);

        RunBonus();

        esat::DrawEnd();

        esat::WindowFrame();
    }

    esat::WindowDestroy();

    return 0;
}