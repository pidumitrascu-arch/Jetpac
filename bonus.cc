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

int fps = 60;



struct Bonus //Struct Bonus items
{
    esat::SpriteTransform BonusTransform;
   
    int BonusDirrection;
    float BonusSpeed;
    esat::SpriteHandle sprite[3];
};
Bonus bonus;
struct bonus{
    esat::Sprite
}
void Bonus() //Aquí imprimo los sprites de los diferentes Bonus que hay.
{
    sprite[0]= esat::SpriteFromFile("./Recursos/Diamante.png");

    sprite[1]= esat::SpriteFromFile("./Recursos/Geoda.png");
    
    sprite[2]= esat::SpriteFromFile("./Recursos/Lingote.png");

    //A continuación haremos que aparezcan en pantalla en sitios aleatorios y en caso que no haya suelo, q caiga dentro del rectángulo del suelo, para que no se pierda el Bonus.

    int randomX = rand() % (screenX - 50); // Genera una posición X aleatoria dentro de los límites de la pantalla
    int randomY = rand() % (screenY - 50); // Genera una posición Y aleatoria dentro de los límites de la pantalla
    

    
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