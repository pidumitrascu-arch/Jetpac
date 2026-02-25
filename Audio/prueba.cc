
#include <esat_extra/soloud/soloud.h>
#include <esat_extra/soloud/soloud_wav.h>
#include <esat/input.h>
#include <esat/window.h>
#include <esat/draw.h>
#include <esat/time.h>
#include <stdio.h>
#include <string.h>



//Numero de sonidos que vamos a usar
const int kNumAudios = 10;

SoLoud::Soloud canal;

//Array donde se guardan los sonidos cargados.
SoLoud::Wav audio[kNumAudios];

//Inicializamos los sonidos
void AudioInit(){
  //Inicia el motor de audio.Debe llamarse una sola vez al empezar el programa.
  canal.init();
  //Carga el audio (ruta relativa a la carpeta del proyecto)
  const char *kPath = "Recursos/Audio/";
  const char *names[kNumAudios] = {
    "shoot.wav",
    "enemydies.wav",
    "fallobject.wav",
    "get_fuel.wav",
    "get_item.wav",
    "intro.wav",
    "menu_intro.wav",
    "spacedep1.wav",
    "spaceshipland.wav",
    "startgameplay.wav"
  };

  char path_buf[256];
  for (int i = 0; i < kNumAudios; ++i) {
    strcpy(path_buf, kPath);
    strcat(path_buf, names[i]);
    audio[i].load(path_buf);
  }
}

// PLAY_AUDIO
//reproduce el sonido guardado en la posicion indicada
void AudioPlay(int i){       
  canal.play(audio[i]);
}

//Comprueba si el sonido en la posición indicada se está reproduciendo
void AudioCheck(int i) {
  if (canal.isValidVoiceHandle(i)) {
    printf("El sonido %d se está reproduciendo.\n", i);
  } else {
    printf("El sonido %d no se está reproduciendo.\n", i);
  }
}

//Detiene el sonido en la posición indicada
void AudioStop(int i) {
  canal.stopAudioHandle(i);
}

//Funcion que se encarga de reproducir el sonido indicado al pular la tecla indicada
void SoundX(){
  if (esat::IsSpecialKeyPressed(esat::kSpecialKey_Space)) {
    AudioPlay(0);
    printf("DISPARO!\n");
  }
  if (esat::IsKeyPressed('Z')){
    AudioPlay(1);
    printf("Enemy_dies\n");
  }
  if (esat::IsKeyPressed('X')){
    AudioPlay(2);
    printf("Cae un objeto!!\n");
  }
  if (esat::IsKeyPressed('C')){
    AudioPlay(3);
    printf("Gasolina a la vista!!\n");
  }
  if (esat::IsKeyPressed('V')){
    AudioPlay(4);
    printf("Recibiste un objeto!\n");
  }
  if (esat::IsKeyPressed('B')){
    AudioPlay(5);
    printf("Intro del juego!\n");
  }
  if (esat::IsKeyPressed('N')){
    AudioPlay(6);
    printf("Menu_princ\n");
  }
  if (esat::IsKeyPressed('M')){
    AudioPlay(7);
    printf("spacedep1\n");
  }
    if (esat::IsKeyPressed('L')){
        AudioPlay(8);
        printf("spaceshipland\n");
    }
    if (esat::IsKeyPressed('P')){
        AudioPlay(9);
        printf("startgameplay\n");
    }
}


int esat::main(int argc, char **argv) {
  // Inicializa el sistema de audio antes del bucle principal.
  AudioInit();
  // Inicializa la ventana gráfica (ancho, alto)
  esat::WindowInit(800, 600);
  esat::WindowSetMouseVisibility(true);

  while (esat::WindowIsOpened() &&
         !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {
    esat::DrawBegin();
    esat::DrawClear(0,0,0);

    // Llamada a la funcion que reproduce el sonido
    SoundX();

    esat::DrawEnd();
    // Presenta el frame en pantalla
    esat::WindowFrame();
    esat::Sleep(10);
  }

  AudioShutdown();
  esat::WindowDestroy();
  return 0;
}