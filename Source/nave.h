#ifndef __NAVE_H__
#define __NAVE_H__
#include "sprite.h"
#include <SDL.h>

class nave{
	sprite *sprite1;
	int x;
	int y;
	
public:
		void Mover(int posicion);
			nave(SDL_Surface * screen, char * rutaImagen);
			void Pintar();
		
};

#endif