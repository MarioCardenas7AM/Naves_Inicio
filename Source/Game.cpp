#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Header.h" 
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>

CGame::CGame()
{
	tiempoFrameInicial=0;
	estado = ESTADO_INICIANDO;
	Iniciando();
	InicializandoStage();

	


	
	//delete nave;
}
void CGame::Iniciando(){
	
	if (SDL_Init(SDL_INIT_VIDEO)<0)//si regresa 1 el init de video si se activo y regresa -1 si no se pudo iniciar. 
	{
		printf("No se pudo iniciar SDL: Error %s\n", SDL_GetError());//
		exit(EXIT_FAILURE);
	}

	/*if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)<0)
	{
		printf("SDL Mixer error %s/n", SDL_GetError());
	}
	musica = Mix_LoadMUS("beat.wav");
	if (musica == NULL)
	{
		printf("no se pudo cargar beat.wav %s/n", Mix_GetError());
	}
	*/
	screen= SDL_SetVideoMode(WIDTH_SCREEN, HEIGHT_SCREEN, 24, SDL_HWSURFACE);//(ancho,alto,bpp,bandera)
	if (screen==NULL)
	{
		printf("No se puede inicializar el modo grafico: \n",SDL_GetError());
		getchar();
		exit(1);
	}
	SDL_WM_SetCaption( "Mi primer Juego", NULL );

	atexit(SDL_Quit);

	fondo=new Objeto(screen,"../Data/fondo.bmp",0,0,1);
	nave = new Nave(screen,"../Data/MiNave.bmp",(WIDTH_SCREEN/2),(HEIGHT_SCREEN-80),MODULO_MINAVE_NAVE);
	menu= new Objeto(screen,"../Data/menu.bmp",0,0,MODULO_MENU_FONDO);
	textos=new Objeto(screen,"../Data/textos.bmp",0,0,-1);
	gameOver = new Objeto(screen, "../Data/gameover.bmp", 0, 0, -1);
	
	
//	enemigo = new Objeto(screen,"../Data/enemigo.bmp",0,0);

	for (int i = 0; i < 10; i++)
	{
		enemigoArreglo[i] = new Nave(screen,"../Data/enemigo.bmp",i*60,0,MODULO_ENEMIGO_NAVE);
		enemigoArreglo[i]->GetNaveObjeto()->SetAutoMovimiento(false);
		enemigoArreglo[i]->GetNaveObjeto()->SetPasoLimite(4);
	}

	tick=0;
	

//	enemigo->SetAutoMovimiento(false);
//	enemigo->SetPasoLimite(4);

}
// Con esta función eliminaremos todos los elementos en pantalla
void CGame::Finalize(){
	delete(nave);
	//delete(keys);
	//delete(enemigo);
	//delete *enemigoArreglo;
	SDL_FreeSurface(screen);
	SDL_Quit();
}

bool CGame::Start()
{
	// Esta variable nos ayudara a controlar la salida del juego...
	int salirJuego = false;     

	while (salirJuego == false){
		//Maquina de estados
		switch(estado){
		case Estado::ESTADO_INICIANDO:
			Iniciando();
			//estado =ESTADO_JUGANDO;
			estado = ESTADO_PRE_JUGANDO;
			break;
		case Estado ::ESTADO_MENU:
			menu->Pintar();
			textos->Pintar(MODULO_TEXTOS_TITULO,150,50);
			textos->Pintar(MODULO_TEXTOS_NOMBRE,0,450);
			Menu();
		//estado=ESTADO_JUGANDO;
			break;
		case Estado::ESTADO_PRE_JUGANDO:
			nivelActual = 0;
			vida = 1;
			enemigosEliminados = 0;
			estado = ESTADO_MENU;
			break;
		case Estado ::ESTADO_JUGANDO:
			/*if (Mix_PlayingMusic() == 0){
				Mix_PlayingMusic();
			}
			else
			{
				if (Mix_PausedMusic() == 1){
					Mix_ResumeMusic();
				}
				else
				{
					Mix_PauseMusic();
				}
			}
			 */
		//enemigo->Actualizar();
			for (int i = 0; i < nivel[nivelActual].NumeroEnemigosVisibles; i++)
			{
				enemigoArreglo[i]->GetNaveObjeto()->Actualizar();
			}
			MoverEnemigo();
			 fondo->Pintar();
			//SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));  //limpia la imagen 

			keys= SDL_GetKeyState(NULL);
			if(keys[SDLK_RIGHT])
			{ 
				if(!EsLimitePantalla(nave->GetNaveObjeto(),BORDE_DERECHO))
					nave->MoverDerecha(nivel[nivelActual].VelocidadNavePropia);
			}//Los 3 casos siguientes son el primero aplicando a las demas direcciones
			if(keys[SDLK_LEFT])
			{
				if(!EsLimitePantalla(nave->GetNaveObjeto(),BORDE_IZQUIERDO))
					nave->MoverIzquierda(nivel[nivelActual].VelocidadNavePropia);
			}
			if(keys[SDLK_UP])
			{
				if(!EsLimitePantalla(nave->GetNaveObjeto(),BORDE_SUPERIOR))
					nave->MoverArriba(nivel[nivelActual].VelocidadNavePropia);
			}
			if(keys[SDLK_DOWN])
			{
				if(!EsLimitePantalla(nave->GetNaveObjeto(),BORDE_INFERIOR))
					nave->MoverAbajo(nivel[nivelActual].VelocidadNavePropia);
			}

			if (keys[SDLK_SPACE])
			{
				nave->Disparar(NAVE_PROPIA, nivel[nivelActual].balasMaximas);
			}

			if (keys[SDLK_x]){

				nave->simularColision(true);
			}
			if (keys[SDLK_c]){

				int enemigoAEliminar = rand() % nivel[nivelActual].NumeroEnemigosVisibles;
				enemigoArreglo[enemigoAEliminar]->simularColision(true);
			}
			if (keys[SDLK_v]){

				estado = ESTADO_TERMINANDO;
			}


			//control de colisiones
			for (int i = 0; i < nivel[nivelActual].NumeroEnemigosVisibles; i++){

				if (enemigoArreglo[i]->estaColisionandoConBala(nave))
					vida--;
				if (nave->estaColisionandoConBala(enemigoArreglo[i])){
					enemigoArreglo[i]->SetVisible(false);
					enemigosEliminados++;
				}
				nave->simularColision(false);
				if (enemigosEliminados < nivel[nivelActual].NumeroEnemigosAEliminar){
					enemigoArreglo[i]->CrearNuevo();
				}
			}
			   //control de colisiones

			if (vida <= 0)
				estado = ESTADO_TERMINANDO;
			if (enemigosEliminados >= nivel[nivelActual].NumeroEnemigosAEliminar){
				nivelActual++;

			}
				nave->Pintar(NAVE_PROPIA);
		//		enemigo->Pintar();
				for (int i = 0; i<nivel[nivelActual].NumeroEnemigosVisibles; i++)
				{
					enemigoArreglo[i]->Pintar(NAVE_ENEMIGO);
					enemigoArreglo[i]->AutoDisparar(nivel[nivelActual].balasMaximas);
					if (nivelActual=5)
					{
						nivelActual = 0;
						

					}
				
				}
			//nave->Pintar();
			break;
		case Estado ::ESTADO_TERMINANDO:
			gameOver->Pintar(MODULO_GAME_OVER, 150, 50);
			gameOver->Pintar(MODULO_OPCION_REGRESAR_MENU, 0, 450);
			if (keys[SDLK_m]){

				estado = ESTADO_MENU;
			}
			break;
		case Estado ::ESTADO_FINALIZANDO:
			salirJuego = true;
			break;
		};
		while(SDL_PollEvent(&event))//Aque SDL creara una lista de eventes ocurridos
		{
			if(event.type==SDL_QUIT){salirJuego=true;}//Si se detecta una salida de SDL o...
			if(event.type==SDL_KEYDOWN){}
		}
		SDL_Flip(screen);//Este codigo esta provicionalmente aqui
		//calculando FPS
		tiempoFrameFinal=SDL_GetTicks();
		while(tiempoFrameFinal<(tiempoFrameInicial+FPS_DELAY))
			{
				tiempoFrameFinal=SDL_GetTicks();
				SDL_Delay(1);
			}

		printf("Frames:%d Tiempo:%d Tiempo promedio:%f Tiempo por frame:%d FPS:%f\n",tick,SDL_GetTicks(),(float)SDL_GetTicks()/(float)tick,tiempoFrameFinal- tiempoFrameInicial,1000.0f/(float)(tiempoFrameFinal-tiempoFrameInicial));
		tiempoFrameInicial=tiempoFrameFinal;
		tick++;
	}
	return true;
}

bool CGame::EsLimitePantalla(Objeto * objeto, int bandera)
{
	if (bandera&BORDE_IZQUIERDO)
	if (objeto->ObtenerX()<=0)
		return true;
	if(bandera&BORDE_SUPERIOR)
	if (objeto->ObtenerY()<=0)
		return true;
	if(bandera&BORDE_DERECHO)
	if (objeto->ObtenerX()>=WIDTH_SCREEN-objeto->ObtenerW())
		return true;
	if(bandera&BORDE_INFERIOR)
	if (objeto->ObtenerY()>=HEIGHT_SCREEN-objeto->ObtenerH())
		return true;
	return false;
}
void CGame::MoverEnemigo()
{
//	if(enemigo->ObtenerPasoActual()==0)
//		if(!EsLimitePantalla(enemigo,BORDE_DERECHO))
//	         enemigo->Mover(1);//Derecha
//		else
//		{
//			enemigo->IncrementarPasoAcutal();
//			//enemigo->IncrementarPasoAcutal();
//		}
//	if(enemigo->ObtenerPasoActual()==1)
//		if(!EsLimitePantalla(enemigo,BORDE_INFERIOR))
//			enemigo->Mover2(1);
//		else
//		{
//			enemigo->IncrementarPasoAcutal();
//		}
//	if(enemigo->ObtenerPasoActual()==2)
//		if(!EsLimitePantalla(enemigo,BORDE_IZQUIERDO))
//			enemigo->Mover(-1);
//		else
//		{
//			enemigo->IncrementarPasoAcutal();
//		}
//
//	if(enemigo->ObtenerPasoActual()==3)
//		if(!EsLimitePantalla(enemigo,BORDE_INFERIOR))
//			enemigo->Mover2(1);
//		else
//		{
//			enemigo->IncrementarPasoAcutal();
//		}
//
	for (int i = 0; i < nivel[nivelActual].NumeroEnemigosVisibles; i++)
		{
			if (enemigoArreglo[i]->GetNaveObjeto()->ObtenerPasoActual() == 0)
				if (!EsLimitePantalla(enemigoArreglo[i]->GetNaveObjeto(), BORDE_DERECHO))
					{
				enemigoArreglo[i]->GetNaveObjeto()->Mover(nivel[nivelActual].VelocidadNaveEnemigo);//Derecha
					}
				else
					{
					enemigoArreglo[i]->GetNaveObjeto()->IncrementarPasoAcutal();
						//enemigoArreglo[i]->IncrementarPasoAcutal();
					}
			if (enemigoArreglo[i]->GetNaveObjeto()->ObtenerPasoActual() == 1)
				if (!EsLimitePantalla(enemigoArreglo[i]->GetNaveObjeto(), BORDE_INFERIOR))
					{
				enemigoArreglo[i]->GetNaveObjeto()->Mover2(nivel[nivelActual].VelocidadNaveEnemigo);
					}
				else
					{
					enemigoArreglo[i]->GetNaveObjeto()->IncrementarPasoAcutal();
					}
			if (enemigoArreglo[i]->GetNaveObjeto()->ObtenerPasoActual() == 2)
				if (!EsLimitePantalla(enemigoArreglo[i]->GetNaveObjeto(), BORDE_IZQUIERDO))
					{	
				enemigoArreglo[i]->GetNaveObjeto()->Mover(-nivel[nivelActual].VelocidadNaveEnemigo);
					}
				else
					{
					enemigoArreglo[i]->GetNaveObjeto()->IncrementarPasoAcutal();
						//enemigoArreglo[i]->IncrementarPasoAcutal();
					}
			if (enemigoArreglo[i]->GetNaveObjeto()->ObtenerPasoActual() == 3)
				if (!EsLimitePantalla(enemigoArreglo[i]->GetNaveObjeto(), BORDE_SUPERIOR))
				{
				enemigoArreglo[i]->GetNaveObjeto()->Mover2(-nivel[nivelActual].VelocidadNaveEnemigo);
				}
				else
				{
					enemigoArreglo[i]->GetNaveObjeto()->IncrementarPasoAcutal();
				}
}
}
void CGame::Menu()
{
	for (int i = MODULO_TEXTOS_MENU_OPCION1,j=0; i <= MODULO_TEXTOS_MENU_OPCION2 ; i++,j++)
	{
		keys= SDL_GetKeyState(NULL);
		
		if(keys[SDLK_UP])	
		{
			opcionSeleccionada=MODULO_TEXTOS_MENU_OPCION1;
		}	
			
		if(keys[SDLK_DOWN])
		{
			opcionSeleccionada=MODULO_TEXTOS_MENU_OPCION2;
					
		}
		if (i==opcionSeleccionada)
			{
				textos->Pintar(i+2,300,180+(j*80));
			}
			else
			{
				textos->Pintar(i,300,180+(j*80));
			}
		/*if (i==opcionSeleccionada)
			{
				textos->Pintar(i+2,300,180+(j*80));
			}
			else
			{
				textos->Pintar(i,300,180+(j*80));
			}*/
		if(keys[SDLK_i])
		{
			if (opcionSeleccionada==MODULO_TEXTOS_MENU_OPCION1)
			{
				estado=ESTADO_JUGANDO;
			}
			else
			{
				estado=ESTADO_FINALIZANDO;
			}
					
		}
	}
}

	
