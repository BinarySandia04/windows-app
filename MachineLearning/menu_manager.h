#pragma once

/*
Copyright (c) Aran Roig, 2018 xd

Nah, es broma puedes copiarlo.

Este header lo que hace es definir todos los menus para la ventana, i devuelve los menus
con sus acciones y lo hace. Se llama desde funciones desde main.cpp
*/

#include <Windows.h>
#include "wtypes.h"

#define MENU_NEW_FILE 2
#define	MENU_HELP 3
#define MENU_EXIT_PROGRAM 4

void AddMenus(HMENU hMenu, HWND hWnd) {
	hMenu = CreateMenu();

	HMENU hFileMenu = CreateMenu(); // Submenu de archivo creado

	AppendMenu(hFileMenu, MF_STRING, MENU_NEW_FILE, "Nuevo");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL); // Espacio
	AppendMenu(hFileMenu, MF_STRING, MENU_EXIT_PROGRAM, "Salir");

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "Archivo");
	AppendMenu(hMenu, MF_STRING, MENU_HELP, "Ayuda");

	SetMenu(hWnd, hMenu);
}

void RemoveMenus(HWND hWnd) {
	SetMenu(hWnd, NULL);
}

void menuClickedAction(WPARAM wp, HWND hWnd) {
	switch (wp) {
	case MENU_NEW_FILE:
		// "Archivo - Nuevo"
		MessageBeep(MB_ICONERROR); // Beep sonido de ok prueba
		break;
	case MENU_EXIT_PROGRAM:
		ExitProcess(0x0);
	case MENU_HELP:
		// Ayuda
	default:
		break;
	}
}
