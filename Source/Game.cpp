#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Config.h"
#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>

CGame::CGame(){
<<<<<<< HEAD
//<<<<<<< HEAD
	estado = ESTADO_INICIANDO;
//=======
	estadofin = ESTADO_FINALIZANDO;
//>>>>>>> origin/master
=======
	estado = ESTADO_INICIANDO;
>>>>>>> origin/master
	atexit(SDL_Quit);
}

// Con esta función eliminaremos todos los elementos en pantalla
void CGame::Finalize()
{
	SDL_Quit();
}

void CGame::Iniciando()
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("Error %s ", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	screen = SDL_SetVideoMode(WIDTH_SCREEN, 480, 24, SDL_HWSURFACE);
	if (screen == NULL)
	{
		printf("Error %s ", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_WM_SetCaption("Mi primer Juego", NULL);
	atexit(SDL_Quit);
	nave1 = new nave(screen,"../Data/Minave.bmp", (WIDTH_SCREEN/2)/*-(sprite->WidthModule(0)/2)*/ ,(HEIGHT_SCREEN - 80) /*- (sprite->HeighModule(0))*/);
	enemigo = new nave(screen,"../Data/enemigo.bmp",0,0);
	enemigo->SetAutoMovimiento(true);
	
	//nave->CargarImagen("../Data/MiNave.bmp");
}
bool CGame::Start()
{
	// Esta variable nos ayudara a controlar la salida del juego...
	int salirJuego = false;
          char s;
	while (salirJuego == false){
            
		//Maquina de estados
		switch(estado){
		case Estado::ESTADO_INICIANDO:
			printf(" Estado Iniciando");
			Iniciando();
			
				//nave = IMG_LoadJPG_RW(SDL_RWFromFile("../Data/cuadro.jpg", "rb"));
				//SDL_Rect fuente;
				//fuente.x = 582;
				//fuente.y = 383;
				//fuente.w = 321;
				//fuente.h = 16;

				//SDL_Rect destino;
				//destino.x = 100;
				//destino.y = 100;
				//destino.w = fuente.w;
				//.h = fuente.h;

				//SDL_BlitSurface(nave, &fuente, screen, &destino);
			
			estado = Estado::ESTADO_MENU;
			break;
		case Estado::ESTADO_MENU:
			printf("\n Estado Menu");
			//nave->PintarModulo(0,0,0,64,64);
			//nave->PintarModulo(0,0,0);
			
			estado = Estado::ESTADO_JUGANDO;
			break;
		case Estado::ESTADO_JUGANDO:	
			if (estadofin == ESTADO_JUGANDO)
					{
						estado = ESTADO_FINALIZANDO;
				
						estadofin = ESTADO_FINALIZANDO;


					}
					 if (estado==ESTADO_JUGANDO)
					{
					
						estado = ESTADO_TERMINANDO;
					}
			enemigo->Actualizar();
			SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0,0,0));

			keys = SDL_GetKeyState(NULL);
			if(keys[SDLK_RIGHT]){
				nave1->Mover(1);
				
			}
			if (keys[SDLK_LEFT]){
			nave1->Mover(-1);
			}
			nave1->Pintar();
			enemigo->Pintar();
			
			

	//estado = ESTADO_TERMINANDO;
			break;
		case Estado::ESTADO_TERMINANDO: 
			printf("\n Estado Terminando");

			
				salirJuego = false;
				
				estado = Estado::ESTADO_FINALIZANDO;
				break;
		case Estado::ESTADO_FINALIZANDO:
			printf("\n Estado Finalizando");
			delete(nave1);
			SDL_FreeSurface(screen);
			SDL_Quit();
			estado = ESTADO_FINALIZANDO;
			std::puts("\n Presiona el recuadro x para salir");

			std::getchar();
			break;
		};

		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT) {salirJuego = true;}
			if(event.type == SDL_KEYDOWN) { }
		}
		SDL_Flip(screen);
    }
	return true;
}
