#include<windows.h>

// Global Callback Declaration
/*	
*	LRESULT ->	Returntype
*				LONG_PTR
*					typedef of long
* 
	CALLBACK -> calling convention
				__stdcall
					__far __pascal
	
	HWND -> typdef of HANDLE-> typedef of PVOID -> typedef of void ptr

	UINT -> typedef of unsigned int

	WPARAM -> typedef of WORD -> typedef of unsigned int

	LPARAM -> typedef of LPARAM -> typedef of LONG_PTR ->typedef of long
						
*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Entry-point Function
/*
	WINAPI is callback convention

	HINSTANCE -> handle to process instance
					typdef of HANDLE-> typedef of PVOID -> typedef of void*

	LPSTR -> long pointer to string
			it is char** / wchar**

	LpszCmdLine : it means long pointer to zero terminated (i.e. \0) string command line argument
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR LpszCmdLine, int iCmdShow) {
	/*
	*	Hungarian Notation rules : 
	*				initial letter should be small and should denote variable type
	*				Next letter should be capital
	*				Afterward all letters should be small
	*				Every new word in variable should start with capital letter
	*				if pointer, then begin with 'p' and follow form rule 1
	*				if global variable then start with 'g' and follow from rule 1
	* 
	*/

	// Variable Declarations
	/*
		WNDCLASSEX -> window class extended -> it is a structure 
		TCHAR -> typedef of char / wchar
		MSG -> message -> it is a structure
	*/

	WNDCLASSEX	wndclass;
	HWND		hwnd;
	MSG			msg;
	TCHAR		szClassName[]	=	TEXT("MyWindow_FisrtWindow");

	// Code
	ZeroMemory((void*)&wndclass, sizeof(WNDCLASSEX));

	// Initializing Window Class
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;								// CS_HREDRAW & CS_VREDRAW are macros; Words containing underscrore are macros; CS -> class style
	wndclass.cbClsExtra = 0;												// Extra info about class
	wndclass.cbWndExtra = 0;												// extra info about window
	wndclass.lpfnWndProc = WndProc;											// long pointer to function to window proceduure
	wndclass.lpszClassName = szClassName;									// long pointer to string termineted with zero
	wndclass.lpszMenuName = NULL;											// long pointer to zero terminated string = menu name
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);			// Win32 API : GDI32 library // handle to brush to background
	wndclass.hInstance = hInstance;											
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);							// Win32 API // handle to cursor IDC : identifier of cursor, ARROW of arrow
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);						// Win32 API // handle to icon	IDI : identifier of icon, APPLICATION of application
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);						// handle to small icon

	// Register The Above Window Class
	RegisterClassEx(&wndclass);

	// Create The Window In Memory
	hwnd = CreateWindow(szClassName,
		TEXT("This is new window!"),
		WS_OVERLAPPEDWINDOW,			// WS : window style
		CW_USEDEFAULT,					// CW : create window and use default value
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	// Show The Window On Destop
	ShowWindow(hwnd, iCmdShow);		// iCmdShow is int

	// Update/Paint Window On Destop
	UpdateWindow(hwnd);
	
	// Message Loop
	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);	//wParam is typedef of WORD -> typedef unsigned int
}

// Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	// Code
	switch (iMsg) {
		
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			break;
	}

	// Calling Default Window Procedure
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
