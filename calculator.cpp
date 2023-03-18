#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
HWND textfield, button , plus , minus , devide , times;
char szClassName[] = "TextEntry";
HWND TextBox;
HWND  hNUM1 , hNUM2 ;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
	switch(Message) {

		/* Upon destruction, tell the main thread to stop */
		case WM_CREATE :
			textfield = CreateWindow("STATIC"," Please input two numbers",
									 WS_VISIBLE | WS_CHILD | WS_BORDER , 
									28, 25, 180, 20, 
									hwnd,NULL, NULL, NULL);

			hNUM1 = CreateWindow("Edit", "",
									WS_BORDER |  WS_CHILD | WS_VISIBLE,
									52,60,125,20,
									hwnd, NULL, NULL , NULL);

			hNUM2 = CreateWindow("Edit", "",
									WS_BORDER |  WS_CHILD | WS_VISIBLE,
									52,85,125,20,
									hwnd, NULL, NULL , NULL);

			plus  = CreateWindow("BUTTON", " + ",
									 WS_VISIBLE | WS_CHILD | WS_BORDER , 
									55, 125, 25, 25, 
									hwnd, (HMENU) 1 , NULL, NULL);
			minus = CreateWindow("BUTTON", " - ",
									 WS_VISIBLE | WS_CHILD | WS_BORDER , 
									85, 125, 25, 25, 
									hwnd, (HMENU) 2 , NULL, NULL);
			times = CreateWindow("BUTTON", " * ",
									 WS_VISIBLE | WS_CHILD | WS_BORDER , 
									115, 125, 25, 25, 
									hwnd, (HMENU) 3 , NULL, NULL);
			devide = CreateWindow("BUTTON", " / ",
									 WS_VISIBLE | WS_CHILD | WS_BORDER , 
									145, 125, 25, 25, 
									hwnd, (HMENU) 4 , NULL, NULL);
			break;

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				char number1[10],number2[10],answ[10];
				float num1, num2, out;

				case 1 : 
					::MessageBeep(MB_ICONERROR);	
					GetWindowText(hNUM1,number1,10);
					GetWindowText(hNUM2,number2,10);
					num1 = atof(number1);
					num2 = atof(number2);
					out = num1 + num2;
					sprintf(answ, "%f", out);
					::MessageBox(hwnd,answ, "Result ", MB_OK );
				break;

				case 2 : 
					::MessageBeep(MB_ICONERROR);	
					GetWindowText(hNUM1,number1,10);
					GetWindowText(hNUM2,number2,10);
					num1 = atof(number1);
					num2 = atof(number2);
					out = num1 - num2;
					sprintf(answ, "%f", out);
					::MessageBox(hwnd,answ, "Result ", MB_OK );
					break;

				case 3 : 
					::MessageBeep(MB_ICONERROR);
					GetWindowText(hNUM1,number1,10);
					GetWindowText(hNUM2,number2,10);
					num1 = atof(number1);
					num2 = atof(number2);
					out = num1 * num2;
					sprintf(answ, "%f", out);
					::MessageBox(hwnd,answ, "Result ", MB_OK );
					break;

				case 4 : 
					::MessageBeep(MB_ICONERROR);
					GetWindowText(hNUM1,number1,10);
					GetWindowText(hNUM2,number2,10);
					num1 = atof(number1);
					num2 = atof(number2);
					out = num1 / num2;
					sprintf(answ, "%f", out);
					if(num2 !=0 ){
						::MessageBox(hwnd,answ, "Result ", MB_OK );
						break;
					}
					else{
						::MessageBox(hwnd,"Error", "Result ", MB_OK );
						break;
					}
							
			}

		
		break;

		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(255,255, 0));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);


	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
