#include "sprite.h"
#include <SDL.h>


sprite::sprite(SDL_Surface * screen){
	screen;
	this->screen = screen;
}

sprite::~sprite(){
	SDL_FreeSurface(imagen);

}

void sprite::CargarImagen(char * nombre){
	imagen = SDL_LoadBMP(nombre);

}
void sprite::PintarModulo(int nombre, int x, int y, int w, int h){
		
		SDL_Rect src;
		src.x = x;
		src.y = y;
		src.w = w;
		src.h = h;
		
		SDL_BlitSurface(imagen, &src, screen, NULL);
}

void sprite::PintarModulo(int nombre, int x, int y){
		
		SDL_Rect src;
		src.x = spritedef.modulos[nombre].x;
		src.y = spritedef.modulos[nombre].y;
		src.w = spritedef.modulos[nombre].w;
		src.h = spritedef.modulos[nombre].h;
		SDL_Rect dest;
		dest.x = x;
		dest.y = y;
		SDL_BlitSurface(imagen, &src,  screen,  &dest);
}

int sprite::WidthModule(int module){
	return spritedef.modulos[module].w;
}

int sprite::HeightModule(int module){
return spritedef.modulos[module].h;
}