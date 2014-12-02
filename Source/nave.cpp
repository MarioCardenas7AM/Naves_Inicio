#include "Nave.h"
#include <SDL.h>
#include "Objeto.h"
#include "Header.h"

Nave::Nave(SDL_Surface * screen,char * rutaImagen,int x,int y,int module)
{
	nave = new Objeto(screen,rutaImagen,x,y,module);
	bala = new Objeto(screen,"../Data/balas.bmp",0,0,MODULO_BALAS_BALA);
	bala->SetVisible(false);
}

void Nave::Pintar()
{
	nave -> Pintar();
	bala->Pintar();
	bala->Mover2(-40);
}

void Nave::Disparar()
{
	bala->SetVisible(true);
	bala->PonerEn(nave->ObtenerX()+nave->ObtenerW()/2-1,nave->ObtenerY());
	
	
}

void Nave::MoverAbajo()
{
	nave->Mover2(8);
}

void Nave::MoverArriba()
{
	nave->Mover2(-8);
}

void Nave::MoverDerecha()
{
	nave->Mover(8);
}

void Nave::MoverIzquierda()
{
	nave->Mover(-8);
}

Objeto* Nave::GetNaveObjeto()
{
	return nave;
}