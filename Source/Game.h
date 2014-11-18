#include <SDL.h>
#include "Nave.h"
#include "COnfig.h"

class CGame
{
public:
	enum Estado{
		ESTADO_INICIANDO,
		ESTADO_MENU,
		ESTADO_JUGANDO,
		ESTADO_TERMINANDO,
		ESTADO_FINALIZANDO
	};

	bool Start();
	static CGame instanceGame;

	CGame();
	void Finalize();

private:
	int tick;
	int tiempoFrame;

	Nave *texto;//textos del juego
	Nave *menu;//fodno del menu
    Nave *fondo;//dongo del juego

	void Iniciando();
	void Menu();
	void MoverEnemigo();
	bool EsLimitePantalla(Nave * objeto,int bandera);

	int opcionSeleccionada;

	Uint8 * keys;//Esta variable nos servira para ver si determinadas teclas estan o no pulsadas
	SDL_Event event;// La variable event de tipo evento de SDL nos servira para monitorizar el teclado

	SDL_Surface *screen;
	Nave *nave;
	/*Nave* enemigo;*/
	Nave *enemigoArreglo[10];
	Estado estado;
};