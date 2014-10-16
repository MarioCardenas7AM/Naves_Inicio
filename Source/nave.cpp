#include "nave.h"
#include "Config.h"

nave::nave(SDL_Surface * screen, char * rutaImagen){
	sprite1 = new sprite(screen);
	sprite1->CargarImagen(rutaImagen);
	x = (WIDTH_SCREEN/2)-(sprite1->WidthModule(0)/2);
	y= (HEIGHT_SCREEN-80)-(sprite1->HeightModule(0));
}

void nave::Pintar(){
   sprite1->PintarModulo(0,x,y);
}

void nave::Mover(int posicion){
	x += posicion;
}



