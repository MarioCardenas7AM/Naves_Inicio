#ifndef __SPRITE_H__
#define __SPRITE_H__
#include <SDL.h>
#include "spritedef.h"

class sprite{
	SDL_Surface * imagen;
	SDL_Surface * screen;
	spritedef spritedef;
public:
	sprite(SDL_Surface * screen);
	~sprite();

	void CargarImagen (char * nombre);
	void PintarModulo(int nombre, int x, int, int w, int h);
	void PintarModulo(int nombre, int x, int y);
	int WidthModule(int module);
	int HeightModule(int module);

	};
#endif