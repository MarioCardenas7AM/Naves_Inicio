#ifndef __NAVE_H__
#define __NAVE_H__
#include "sprite.h"
#include <SDL.h>

class nave{
	sprite *sprite1;
	int x;
	int y;
	bool autoMovimiento;
	
public:
			void Mover(int posicion);
			nave(SDL_Surface * screen, char * rutaImagen,int x, int y);
			void SetAutoMovimiento(bool autoMovimiento);
			void Pintar();
			void Actualizar();
		
};

#endif