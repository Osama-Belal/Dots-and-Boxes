#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "playing.h"

#define  reset "\x1b[0m"


#define  black "\x1b[30m"
#define  red "\x1b[31m"
#define  green "\x1b[32m"
#define  yellow "\x1b[33m"
#define  blue "\x1b[34m"
#define  magenta "\x1b[35m"
#define  cyan "\x1b[36m"
#define  white "\x1b[37m"


#define EXIT 0

#define GAME_GUIDE 9001
#define TOP_10 9002
#define MODE_1 9003
#define MODE_2 9004
#define BEGINNER 9005
#define EXPERT 9006
#define CHOOSE_DIFFICULTY 9007

#define VSPLAYER 1
#define VSCOMPUTER 2


const char g_szClassName[] = "myWindowClass";
HINSTANCE g_hinst;
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{

    // navigation bar----------------------------------------------------------------
	switch(Message)
	{
		case WM_CREATE:
		{
			HMENU hMenu, hSubMenu;
			HICON hIcon, hIconSm;

			hMenu = CreateMenu();

			hSubMenu = CreatePopupMenu();
			AppendMenu(hSubMenu, MF_STRING, MODE_1, "&Player VS Player");
			AppendMenu(hSubMenu, MF_STRING, MODE_2, "&Player Vs Computer");
			AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Play");

			hSubMenu = CreatePopupMenu();
			AppendMenu(hSubMenu, MF_STRING, BEGINNER, "&Beginner");
			AppendMenu(hSubMenu, MF_STRING, EXPERT, "&Expert");
			AppendMenu(hSubMenu, MF_STRING, CHOOSE_DIFFICULTY, "&Choose Grid");
			AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Modes");

			hSubMenu = CreatePopupMenu();
			AppendMenu(hSubMenu, MF_STRING, GAME_GUIDE, "&Game Guide");
			AppendMenu(hSubMenu, MF_STRING, TOP_10, "&Top 10");
			AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&More");

            hSubMenu = CreatePopupMenu();
			AppendMenu(hSubMenu, MF_STRING, EXIT, "YES");

			AppendMenu(hSubMenu, MF_STRING, EXIT, "NO");
			AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Exit");

			SetMenu(hwnd, hMenu);

			hIcon = (HICON)LoadImage(NULL, "menu_two.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
			if(hIcon)
			{
				SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
			}
			else
			{
				MessageBox(hwnd, "Could not load large icon! Is it in the current working directory?", "Error", MB_OK | MB_ICONERROR);
			}

			hIconSm = (HICON)LoadImage(NULL, "menu_two.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
			if(hIconSm)
			{
				SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIconSm);
			}
			else
			{
				MessageBox(hwnd, "Could not load small icon! Is it in the current working directory?", "Error", MB_OK | MB_ICONERROR);
			}
		}
		break;
		case WM_COMMAND:

            // file
			switch(LOWORD(wParam))
			{
				case TOP_10:
					MessageBox(hwnd, "TOP 10 List!", "Woo!", MB_OK);break;
			}


            // Mode
			switch(LOWORD(wParam))
			{
				case MODE_1:
					MessageBox(hwnd, "Player VS Player", "SURE!", MB_OK);break;
                case MODE_2:
					MessageBox(hwnd, "Player VS Computer", "SURE!", MB_OK);break;
			}


            // Difficulty
			switch(LOWORD(wParam))
			{
				case BEGINNER:
					MessageBox(hwnd, "Beginner (2 X 2) Boxes", "SURE!", MB_OK);system("cls");game('b');break;
                case EXPERT:
					MessageBox(hwnd, "Expert (5 X 5) Boxes", "SURE!", MB_OK);system("cls");game('e');break;
                case CHOOSE_DIFFICULTY:
					MessageBox(hwnd, "Choose Grid (n X m) Boxs", "SURE!", MB_OK);system("cls");game('c');break;
                case VSPLAYER:
					MessageBox(hwnd, "You Are 2 Players!", "SURE!", MB_OK);system("cls");break;
                case VSCOMPUTER:
					MessageBox(hwnd, "You Are Playing Against Computer!", "SURE!", MB_OK);system("cls");break;
			}


			// Exit
			switch(LOWORD(wParam))
			{
				case EXIT:
					PostMessage(hwnd, WM_CLOSE, 0, 0);break;
			}


		break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
		break;
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	// navigation bar ----------------------------------------------------------------------



	//---------------------TEXT------------------------------------



                    static wchar_t *lyrics =  L"     Dots and Boxes \nWelcome to the game!";
					CreateWindowW(L"Static", lyrics,
                                    WS_CHILD | WS_VISIBLE | SS_LEFT,
                                    165, 40, 300, 230,
                                    hwnd, (HMENU) 1, NULL, NULL);

        /*

            static wchar_t *lyrics =  L"     Dots and Boxes \nWelcome to the game !";

            switch(Message) {

                case WM_CREATE:

                    CreateWindowW(L"Static", lyrics,
                        WS_CHILD | WS_VISIBLE | SS_LEFT,
                        165, 40, 300, 230,
                        hwnd, (HMENU) 1, NULL, NULL);
                    break;

                case WM_DESTROY:

                    PostQuitMessage(0);
                    break;
            }*/

   // return DefWindowProcW(hwnd, Message, wParam, lParam);
    // only one return at the end of all objects added





	//---------------------TEXT---------------------



	//-------------------Buttons-----------------------------





	switch(Message) {

        case WM_CREATE:

            CreateWindowW(L"Button", L"Beginner",
                WS_VISIBLE | WS_CHILD ,
                60, 100, 110, 30, hwnd, (HMENU) BEGINNER, NULL, NULL);
                //x, y, width, height
            CreateWindowW(L"Button", L"Expert",
                WS_VISIBLE | WS_CHILD ,
                180, 100, 110, 30, hwnd, (HMENU) EXPERT, NULL, NULL);

            CreateWindowW(L"Button", L"Choose Grid",
                WS_VISIBLE | WS_CHILD ,
                300, 100, 110, 30, hwnd, (HMENU) CHOOSE_DIFFICULTY, NULL, NULL);

            CreateWindowW(L"Button", L"Player VS Player",
                WS_VISIBLE | WS_CHILD ,
                70, 160, 150, 30, hwnd, (HMENU) VSPLAYER, NULL, NULL);

            CreateWindowW(L"Button", L"Player VS Computer",
                WS_VISIBLE | WS_CHILD ,
                250, 160, 150, 30, hwnd, (HMENU) VSCOMPUTER, NULL, NULL);

            CreateWindowW(L"Button", L"EXIT GAME",
                WS_VISIBLE | WS_CHILD ,
                80, 220, 310, 30, hwnd, (HMENU) EXIT, NULL, NULL);
            break;
    }

    return DefWindowProcW(hwnd, Message, wParam, lParam);





	//---------------------Button--------------------------




	//------------------------- Dropbox----------------------------------------





/*
static HWND hwndCombo, hwndStatic;
    const wchar_t *items[] = { L"FreeBSD", L"OpenBSD",
        L"NetBSD", L"Solaris", L"Arch" };

    switch(Message) {

        case WM_CREATE:

              hwndCombo = CreateWindowW(L"Combobox", NULL,
                    WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
                    10, 10, 120, 110, hwnd, NULL, g_hinst, NULL);

              CreateWindowW(L"Button", L"Drop down",
                    WS_CHILD | WS_VISIBLE,
                    150, 10, 90, 25, hwnd, (HMENU) 1, g_hinst, NULL);

              hwndStatic = CreateWindowW(L"Static", L"",
                    WS_CHILD | WS_VISIBLE,
                    150, 80, 90, 25, hwnd, NULL, g_hinst, NULL);

              for (int i = 0; i < 4; i++ ) {

                  SendMessageW(hwndCombo, CB_ADDSTRING, 0, (LPARAM) items[i]);
              }

              break;

        case WM_COMMAND:

             if (HIWORD(wParam) == BN_CLICKED) {

                  SendMessage(hwndCombo, CB_SHOWDROPDOWN, (WPARAM) TRUE, 0);
             }

             if (HIWORD(wParam) == CBN_SELCHANGE) {

                  LRESULT sel = SendMessage(hwndCombo, CB_GETCURSEL, 0, 0);
                  SetWindowTextW(hwndStatic, items[sel]);
             }
             break;

    }

    return DefWindowProcW(hwnd, Message, wParam, lParam);

*/






	//------------------------------Dropbox-----------------------------


	return 0;
}





int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	/*WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.style		 = 0;
	wc.lpfnWndProc	 = WndProc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = hInstance;
	wc.hIcon		 = NULL;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm		 = NULL;

	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"Dots and Boxes",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 900, 400,
		NULL, NULL, hInstance, NULL);

	if(hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;*/






    MSG  msg;
    WNDCLASSW wc = {0};
    wc.lpszClassName = L"Buttons";
    wc.hInstance     = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc   = WndProc;
    wc.hCursor       = LoadCursor(0, IDC_ARROW);

    g_hinst = hInstance;

    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"DOTS and BOXES",
                  WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  600, 250, 500, 400, 0, 0, hInstance, 0);

    //while (GetMessage(&msg, NULL, 0, 0)) {

        //DispatchMessage(&msg);
    //}

    //return (int) msg.wParam;


    while (GetMessage(&msg, NULL, 0, 0)) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;






}
