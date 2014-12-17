#include "SpriteDef.h"
#include "Header.h"

SpriteDef::SpriteDef(){
	modulos[0].id=MODULO_MINAVE_NAVE;//Objeto
	modulos[0].x=0;
	modulos[0].y=0;
	modulos[0].w=64;
	modulos[0].h=64;

	modulos[1].id=MODULO_MENU_FONDO;//Fondo
	modulos[1].x=0;
	modulos[1].y=0;
	modulos[1].w=WIDTH_SCREEN;
	modulos[1].h=HEIGHT_SCREEN;

	modulos[2].id=MODULO_ENEMIGO_NAVE;//Objeto enemiga
	modulos[2].x=0;
	modulos[2].y=0;
	modulos[2].w=54;
	modulos[2].h=61;
	
	
	modulos[3].id=MODULO_TEXTOS_TITULO;//Titulo
	modulos[3].x=49;
	modulos[3].y=2;
	modulos[3].w = 307;
	modulos[3].h=61;

	modulos[4].id=MODULO_TEXTOS_NOMBRE;//Nombre Anio
	modulos[4].x=9;
	modulos[4].y=126;
	modulos[4].w=179;
	modulos[4].h=29;

	modulos[5].id=MODULO_TEXTOS_MENU_OPCION1;//Iniciar
	modulos[5].x=188;
	modulos[5].y=55;
	modulos[5].w=79;
	modulos[5].h=29;

	modulos[6].id=MODULO_TEXTOS_MENU_OPCION2;//Salir
	modulos[6].x=194;
	modulos[6].y=88;
	modulos[6].w=55;
	modulos[6].h=28;

	modulos[7].id=MODULO_TEXTOS_MENU_OPCION1_SELECCIONADO;//Iniciar verde
	modulos[7].x=264;
	modulos[7].y=56;
	modulos[7].w=79;
	modulos[7].h=31;

	modulos[8].id=MODULO_TEXTOS_MENU_OPCION2_SELECCIONADO;//Salir verde
	modulos[8].x=268;
	modulos[8].y=87;
	modulos[8].w=57;
	modulos[8].h=28;

	modulos[9].id= MODULO_BALAS_BALA;
	modulos[9].x=0;
	modulos[9].y=0;
	modulos[9].w=5;
	modulos[9].h=5;

	modulos[10].id = MODULO_GAME_OVER;
	modulos[10].x = 184;
	modulos[10].y = 210;
	modulos[10].w = 318;
	modulos[10].h = 52;

	modulos[11].id = MODULO_OPCION_REGRESAR_MENU;
	modulos[11].x = 83;
	modulos[11].y = 299;
	modulos[11].w = 522;
	modulos[11].h = 36;


}