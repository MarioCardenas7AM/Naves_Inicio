#include <stdio.h>
#include <stdlib.h>
#include "Game.h"

CGame::CGame(){
	estado = estado;//ACT2: Mal, estas dando el valor que ya tenias, eso no es correcto. Lo que debes de haces es indicar cual sera tu estado inicial.
}

// Con esta función eliminaremos todos los elementos en pantalla
void CGame::Finalize(){
}

bool CGame::Start()
{
	// Esta variable nos ayudara a controlar la salida del juego...
	int salirJuego = false;
          
	while (salirJuego == false){
            
		//Maquina de estados
		switch(estado){
		case  Estado::ESTADO_INICIANDO:
		
			break;
		case   Estado::ESTADO_MENU:
			
			break;
		case  Estado::ESTADO_JUGANDO:
				
				
			break;
		case Estado::ESTADO_TERMINANDO:
			
			break;
		case Estado::ESTADO_FINALIZANDO:
			salirJuego = true;
			
			
			break;
		};
    }
	return true;
}
