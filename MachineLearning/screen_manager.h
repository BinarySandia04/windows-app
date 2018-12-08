#pragma once

/*
Copyright (c) Aran Roig, 2018 xd

Nah, es broma puedes copiarlo.

Este header lo que hace es tener funciones varias sobre la pantalla del ordenador
*/

#include <Windows.h>
#include "wtypes.h"

void GetResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}