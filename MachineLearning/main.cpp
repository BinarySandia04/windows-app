
/*
Copyright (c) Aran Roig, 2018 xd

Nah, es broma puedes copiarlo.

Este es el archivo main.cpp, que es el programa en si. Tira de los headers que he definido
antes, i el programa lo que hace es un poco de inteligencia artificial. Hice hace tiempo
un codigo con python y quiero pasarlo aqui a c++ porque es más potente (al ser compilado).

Entonces también estoy probando la libreria de windows, que sirve para hacer ventanas propias
de windows y todo ese rollo. Obiamente esto no estara en Linux.
*/

#include <Windows.h>
#include "menu_manager.h"
#include "screen_manager.h"
#include "graphics.h"
#include <stdio.h>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

	InitializeWindow(hInst, hPrevInst, args, ncmdshow);
	ProgramDefaultLoop();
}
