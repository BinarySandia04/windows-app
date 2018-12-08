#pragma once

/*
Copyright (c) Aran Roig, 2018 xd

Nah, es broma puedes copiarlo.

Este header lo que hace es tener funciones sobre el renderizado con OpenGL. Odio OpenGl,
es un rollazo y muy complicado. Normalmente aqui hay funciones copy/paste xd. Me siento mal
haciendo copy/paste en una materia que no domino.

También he metido aqui el coñazo de inicializar la ventana, osea todo lo que debería hacer WinMain y
el Window Procedure lo he pasado aqui porque no quiero tocarlo más porfavor, cada segundo que paso
tocando esto sufro mucho y me gustaría dejar ya de sufrir muchas gracias.

Se supone que mi objetivo es renderizar OpenGl en la ventana hecha con Win32 API, cosa
que quedaria muy chula.
*/

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>

HGLRC           hRC = NULL;                           // Permanent Rendering Context
HDC             hDC = NULL;                           // Private GDI Device Context
HINSTANCE       hInstance;                          // Holds The Instance Of The Application

HWND            hWnd = GetActiveWindow();          // Gets HWND of the current window?

bool            keys[256];                              // Array Used For The Keyboard Routine
bool            active = TRUE;                                // Window Active Flag Set To TRUE By Default
bool            fullscreen = TRUE;                            // Fullscreen Flag Set To Fullscreen Mode By Default

int bits = 0;

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void GetResolution(int& horizontal, int& vertical);

BOOL done = FALSE;
BOOL windowFullscreen = TRUE;

HMENU hMenu;

GLvoid ReSizeGLScene(GLsizei width, GLsizei height) // Resize And Initialize The GL Window
{
	if (height == 0) // Prevent A Divide By Zero By
	{
		height = 1;  // Making Height Equal One
	}

	glViewport(0, 0, width, height); // Reset The Current Viewport
	glMatrixMode(GL_PROJECTION); // Select The Projection Matrix
	glLoadIdentity(); // Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
	glLoadIdentity(); // Reset The Modelview Matrix
}
int InitGL(GLvoid) { // All Setup For OpenGL Goes Here
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Background color
	
	glClearDepth(1.0f);                         // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);                         // The Type Of Depth Test To Do


	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective Calculations :D

	return TRUE;
}
int DrawGLScene(GLvoid)                             // Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear The Screen And The Depth Buffer
	glLoadIdentity();                           // Reset The Current Modelview Matrix
	return TRUE;                                // Everything Went OK
}
GLvoid KillGLWindow(GLvoid) {                     // Properly Kill The Window
	if (fullscreen) { // We are in fullscreen?
		ChangeDisplaySettings(NULL, 0);  // If So Switch Back To The Desktop
		ShowCursor(TRUE);                // Show Mouse Pointer
	}
	if (hRC) { // Do we have a rendering context?
		if (!wglMakeCurrent(NULL, NULL)) // We aren't able to release the DC and RC?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION); // ERROR
		}
		if (!wglDeleteContext(hRC)) // We aren't Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION); // ERROR
		}
		hRC = NULL;                           // Set RC To NULL
	}
	if (hDC && !ReleaseDC(hWnd, hDC))                    // Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;                           // Set DC To NULL
	}
	if (hWnd && !DestroyWindow(hWnd))                   // Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;                          // Set hWnd To NULL
	}
	if (!UnregisterClass("OpenGL", hInstance))               // Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;                         // Set hInstance To NULL
	}
	
}
static  PIXELFORMATDESCRIPTOR pfd =                  // pfd Tells Windows How We Want Things To Be
{
	sizeof(PIXELFORMATDESCRIPTOR),                  // Size Of This Pixel Format Descriptor
	1,                              // Version Number
	PFD_DRAW_TO_WINDOW |                        // Format Must Support Window
	PFD_SUPPORT_OPENGL |                        // Format Must Support OpenGL
	PFD_DOUBLEBUFFER,                       // Must Support Double Buffering
	PFD_TYPE_RGBA,                          // Request An RGBA Format
	bits,                               // Select Our Color Depth
	0, 0, 0, 0, 0, 0,                       // Color Bits Ignored
	0,                              // No Alpha Buffer
	0,                              // Shift Bit Ignored
	0,                              // No Accumulation Buffer
	0, 0, 0, 0,                         // Accumulation Bits Ignored
	16,                             // 16Bit Z-Buffer (Depth Buffer)
	0,                              // No Stencil Buffer
	0,                              // No Auxiliary Buffer
	PFD_MAIN_PLANE,                         // Main Drawing Layer
	0,                              // Reserved
	0, 0, 0                             // Layer Masks Ignored
};
int InitializeWindow(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	/*
	AllocConsole();

	SetConsoleTitle("Dev Console");

	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;

	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;

	// Esto añade una consola?

	*/

	GLuint      PixelFormat;                        // Holds The Results After Searching For A Match
	WNDCLASSW wc = { 0 };
	DWORD       dwExStyle;                      // Window Extended Style
	DWORD       dwStyle;                        // Window Style

	if (MessageBox(NULL, "Would You Like To Run In Fullscreen Mode?", "Start FullScreen?", MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		windowFullscreen = FALSE;                       // Windowed Mode
	}
	// TODO: Pasar esto a graphics.h
	int Wheight = 800, Wwidth = 1280;
	int horizontalScreen = 0, verticalScreen = 0;
	GetResolution(horizontalScreen, verticalScreen);
	int finalWidth = (horizontalScreen / 2 - Wwidth / 2), finalHeight = (verticalScreen / 2 - Wheight / 2);

	RECT WindowRect;                            // Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;                        // Set Left Value To 0
	WindowRect.right = (long)Wwidth;                       // Set Right Value To Requested Width
	WindowRect.top = (long)0;                         // Set Top Value To 0
	WindowRect.bottom = (long)Wheight;                     // Set Bottom Value To Requested Height


	wc.hInstance = hInst;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WindowProcedure;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Cursor
	wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255)); // Color de fondo
	wc.lpszClassName = L"OpenGl";
	wc.style = CS_OWNDC;

	if (!RegisterClassW(&wc)) return -1;

	if (windowFullscreen)                             // Attempt Fullscreen Mode?
	{
		DEVMODE dm;
		memset(&dm, 0, sizeof(dm));
		dm.dmSize = sizeof(dm);

		if (0 != EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm))
		{
			int savew = dm.dmPelsWidth;
			int saveh = dm.dmPelsHeight;
			dm.dmPelsWidth = horizontalScreen;
			dm.dmPelsHeight = verticalScreen;

			LONG result = ChangeDisplaySettings(&dm, 0);
			if (result == DISP_CHANGE_SUCCESSFUL)
			{
				ChangeDisplaySettings(&dm, 0);
			}
			else
			{
				MessageBox(NULL, "Fullscreen error", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			}
		}
	}

	if (windowFullscreen)                             // Are We Still In Fullscreen Mode?
	{
		// Como se mostrara la ventana en fullscreen

		dwExStyle = WS_EX_APPWINDOW;                  // Window Extended Style
		dwStyle = WS_POPUP;                       // Windows Style

		if (!(hWnd = CreateWindowEx(dwExStyle,              // Extended Style For The Window
			"OpenGL",               // Class Name
			"Machine Learning",                  // Window Title
			WS_CLIPSIBLINGS |           // Required Window Style
			WS_CLIPCHILDREN |           // Required Window Style
			dwStyle,
			0, 0,                   // Window Position
			horizontalScreen,   // Calculate Adjusted Window Width
			verticalScreen,// Calculate Adjusted Window Height
			NULL,                   // No Parent Window
			NULL,                   // No Menu
			hInstance,              // Instance
			NULL)))                 // Don't Pass Anything To WM_CREATE
		{
			KillGLWindow();                         // Reset The Display
			MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;                           // Return FALSE
		}
	}
	else
	{
		// Como se mostrara sin fullscreen

		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;           // Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;                    // Windows Style

		if (!(hWnd = CreateWindowEx(dwExStyle,              // Extended Style For The Window
			"OpenGL",               // Class Name
			"Machine Learning",                  // Window Title
			WS_CLIPSIBLINGS |           // Required Window Style
			WS_CLIPCHILDREN |           // Required Window Style
			dwStyle,
			0, 0,                   // Window Position
			Wwidth,   // Calculate Adjusted Window Width
			Wheight,// Calculate Adjusted Window Height
			NULL,                   // No Parent Window
			NULL,                   // No Menu
			hInstance,              // Instance
			NULL)))                 // Don't Pass Anything To WM_CREATE
		{
			KillGLWindow();                         // Reset The Display
			MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;                           // Return FALSE
		}


	}



	if (!(hDC = GetDC(hWnd)))                         // Did We Get A Device Context?
	{
		KillGLWindow();                         // Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                           // Return FALSE
	}
	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))             // Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();                         // Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                           // Return FALSE
	}
	if (!SetPixelFormat(hDC, PixelFormat, &pfd))               // Are We Able To Set The Pixel Format?
	{
		KillGLWindow();                         // Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                           // Return FALSE
	}
	if (!(hRC = wglCreateContext(hDC)))                   // Are We Able To Get A Rendering Context?
	{
		KillGLWindow();                         // Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                           // Return FALSE
	}
	if (!wglMakeCurrent(hDC, hRC))                        // Try To Activate The Rendering Context
	{
		KillGLWindow();                         // Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                           // Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);                       // Show The Window
	SetForegroundWindow(hWnd);                      // Slightly Higher Priority
	SetFocus(hWnd);                             // Sets Keyboard Focus To The Window
	ReSizeGLScene(finalWidth, finalHeight);                       // Set Up Our Perspective GL Screen


	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);     // Adjust Window To True Requested Size

	/*
	CreateWindowW(L"myWindowClass", L"Machine Learning", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
		finalWidth, finalHeight, Wwidth, Wheight,
		NULL, NULL, hInst, NULL);
	*/

	if (!InitGL())                              // Initialize Our Newly Created GL Window
	{
		KillGLWindow();                         // Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                           // Return FALSE
	}
}
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_CREATE: // Esto ocurre cuando la window detecta que fue creada
		if (!windowFullscreen) AddMenus(hMenu, hwnd); // Se añaden ahora después de decir si la ventana es fullscreen o no
		break;
	case WM_DESTROY: // Esto ocurre cuando la window detecta que se cierra
		done = TRUE;
		break;
	case WM_COMMAND: // Cuando la window detecta que el menú de arriba es presionado
		menuClickedAction(wp, hwnd);
		break;
	case WM_ACTIVATE:                       // Watch For Window Activate Message
		if (!HIWORD(wp))                    // Check Minimization State
		{
			active = TRUE;                    // Program Is Active
		}
		else
		{
			active = FALSE;                   // Program Is No Longer Active
		}
		break;
	case WM_SYSCOMMAND:                     // Intercept System Commands
		switch (wp)                     // Check System Calls
		{
		case SC_SCREENSAVE:             // Screensaver Trying To Start?
			break;
		case SC_MONITORPOWER:               // Monitor Trying To Enter Powersave?
			break;
		}
		break;                          // Exit
	case WM_KEYDOWN:                        // Is A Key Being Held Down?
		keys[wp] = TRUE;                    // If So, Mark It As TRUE
		break;
	case WM_KEYUP:                          // Has A Key Been Released?
		keys[wp] = FALSE;                   // If So, Mark It As FALSE
		break;
	case WM_SIZE:                           // Resize The OpenGL Window
		ReSizeGLScene(LOWORD(lp), HIWORD(lp));       // LoWord=Width, HiWord=Height
		break;
	}
	return DefWindowProcW(hwnd, msg, wp, lp);
}
WPARAM ProgramDefaultLoop() {
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL) && !done) {
		TranslateMessage(&msg);             // Translate The Message
		DispatchMessage(&msg);              // Dispatch The Message
		if (keys[VK_ESCAPE])                // Was ESC Pressed?
		{
			done = TRUE;              // ESC Signalled A Quit
		}
		else                        // Not Time To Quit, Update Screen
		{
			DrawGLScene();              // Draw The Scene
			SwapBuffers(hDC);           // Swap Buffers (Double Buffering)
		}
	}

	// Se ha cerrado
	// Shutdown
	PostQuitMessage(0); // Hace el proceso de cerrarse
	KillGLWindow();                             // Kill The Window
	return (msg.wParam);                            // Exit The Program
}