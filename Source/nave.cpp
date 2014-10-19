#include "nave.h"
#include "Config.h"

nave::nave(SDL_Surface * screen, char * rutaImagen, int x, int y){
	sprite1 = new sprite(screen);
	sprite1->CargarImagen(rutaImagen);
	
	this->x = x;
	this->y = y;
	autoMovimiento = false;
}

void nave::SetAutoMovimiento(bool automovimiento){
	this->autoMovimiento = automovimiento;
}
void nave::Actualizar(){
	if(autoMovimiento){
		 Mover(1);
	}
}
void nave::Pintar(){
   sprite1->PintarModulo(0,x,y);
}

void nave::Mover(int posicion){
	x += posicion;
}



