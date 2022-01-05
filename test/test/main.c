#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "playing.h"
#include "top_10.h"
#include "VS computer.h"

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
#define VSPLAYER 9003
#define VSCOMPUTER 9004
#define BEGINNER 9005
#define EXPERT 9006
#define CHOOSE_DIFFICULTY 9007
#define START 9008
#define MAINMENU 9009

HWND start_button, text, guide_text, computer_button, player_button, exit_button, guide_button, top10_button;
HWND b_button, e_button, c_button, return_button;

const char g_szClassName[] = "WindowClass";
HINSTANCE g_hinst;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
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
	wc.hbrBackground = (HBRUSH)(COLOR_HIGHLIGHT);
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
		WS_MINIMIZEBOX | WS_SYSMENU,
		600, 250, 500, 400,
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
	return Msg.wParam;




/*

    MSG  msg;
//    WNDCLASSW wc = {0};
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

*/




}





LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    static int computer_flag, players_flag;

    static wchar_t *lyrics =  L"\nDots and Boxes \nWelcome to the game!";
    static wchar_t *guide =  L"\nWelcome To This Amazing Pleasing, relaxing and Amusing Game\n"
                                "This Game Is all dots and you need to connect lines to form a box,\n\n"
                                "Once you have done that, you get a point and you are allowed to make another move.";


    HWND console;
    AllocConsole();
    console = FindWindowA("ConsoleWindowClass", NULL);
    //ShowWindow(console, 0);


    // navigation bar----------------------------------------------------------------
	switch(Message)
	{
		case WM_CREATE:
		{
			HMENU hMenu, hSubMenu;
			HICON hIcon, hIconSm;

			hMenu = CreateMenu();

			hSubMenu = CreatePopupMenu();
			AppendMenu(hSubMenu, MF_STRING, VSPLAYER, "&Player VS Player");
			AppendMenu(hSubMenu, MF_STRING, VSCOMPUTER, "&Player Vs Computer");
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


            // Mode
			switch(LOWORD(wParam))
			{
				case VSPLAYER:
					//MessageBox(hwnd, "Player VS Player\n Choose Grid Difficulty!", "Half The Way ..", MB_OK);
					computer_flag = 0;players_flag = 1;
					DestroyWindow(player_button);DestroyWindow(computer_button);
					DestroyWindow(guide_button);DestroyWindow(top10_button);
					goto choosing_grid;
					break;
                case VSCOMPUTER:
					//MessageBox(hwnd, "You Are Playing Against Computer!\n Choose Grid Difficulty!", "Half The Way ..", MB_OK);
					computer_flag = 1;players_flag = 0;
					DestroyWindow(player_button);DestroyWindow(computer_button);
					DestroyWindow(guide_button);DestroyWindow(top10_button);
					goto choosing_grid;
					break;
			}


            // Difficulty
			switch(LOWORD(wParam))
			{
				case BEGINNER:
                    system("cls");ShowWindow(console, 1);
					if(!computer_flag && players_flag){game('b');break;}
					else if(computer_flag && !players_flag){vs_computer('b');break;}
					else{MessageBox(hwnd, "\tChoose Mode First!\n Player VS Player  or  Player VS Computer", "Stay focus!", MB_OK);break;}

                case EXPERT:
					system("cls");ShowWindow(console, 1);
					if(!computer_flag && players_flag){game('e');break;}
					else if(computer_flag && !players_flag){vs_computer('e');break;}
					else{MessageBox(hwnd, "\tChoose Mode First!\n Player VS Player  or  Player VS Computer", "Stay focus!", MB_OK);break;}

                case CHOOSE_DIFFICULTY:
					system("cls");ShowWindow(console, 1);
					if(!computer_flag && players_flag){game('c');break;}
					else if(computer_flag && !players_flag){vs_computer('c');break;}
					else{MessageBox(hwnd, "\tChoose Mode First!\n Player VS Player  or  Player VS Computer", "Stay focus!", MB_OK);break;}


			}


			// OTHER
			switch(LOWORD(wParam))
			{
				case TOP_10:
					MessageBox(hwnd, "TOP 10 List!", "Woo!", MB_OK);break;
                case GAME_GUIDE:
					MessageBox(hwnd, "I'll show you the guide!", "Woo!", MB_OK);goto game_guide;break;
                case START:
                    DestroyWindow(start_button);goto start_game;break;
                case MAINMENU:
                    DestroyWindow(b_button);DestroyWindow(e_button);DestroyWindow(c_button);
                    DestroyWindow(guide_text);//AND destroy TOP 10 When you make them
                    DestroyWindow(return_button);goto start_game;break;
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


        start_button = CreateWindowW(L"Button", L"Start Game",
                WS_VISIBLE | WS_CHILD,
                80, 80, 300, 80, hwnd, (HMENU) START, NULL, NULL);

        DestroyWindow(text);DestroyWindow(computer_button);DestroyWindow(player_button);
        DestroyWindow(e_button);DestroyWindow(b_button);DestroyWindow(c_button);
        DestroyWindow(guide_button);DestroyWindow(top10_button);
        DestroyWindow(return_button);DestroyWindow(exit_button);

                goto skip_Game_lobby;

//case WM_CTLCOLORSTATIC:
//{
    //HDC hdcStatic = (HDC)wParam; // or obtain the static handle in some other way
    //SetTextColor(hdcStatic, RGB(255, 0, 0)); // text color
    //SetBkColor(hdcStatic, RGB(12,34,210));
    //return (LRESULT)GetStockObject(NULL_BRUSH);
//}
//break;


                    //RedrawWindow(hwnd,
                    //NULL, NULL,
                    //RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
                    start_game:

					text = CreateWindowW(L"Static", lyrics,
                        WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
                        145, 25, 180, 70,
                        hwnd, (HMENU) 1, NULL, NULL);


            player_button = CreateWindowW(L"Button", L"Player VS Player",
                WS_VISIBLE | WS_CHILD ,
                60, 120, 160, 50, hwnd, (HMENU) VSPLAYER, NULL, NULL);

            computer_button = CreateWindowW(L"Button", L"Player VS Computer",
                WS_VISIBLE | WS_CHILD ,
                250, 120, 160, 50, hwnd, (HMENU) VSCOMPUTER, NULL, NULL);

            top10_button = CreateWindowW(L"Button", L"TOP 10 List",
                WS_VISIBLE | WS_CHILD ,
                80, 220, 150, 30, hwnd, (HMENU) TOP_10, NULL, NULL);

            guide_button = CreateWindowW(L"Button", L"Game Guide",
                WS_VISIBLE | WS_CHILD ,
                240, 220, 150, 30, hwnd, (HMENU) GAME_GUIDE, NULL, NULL);

            exit_button = CreateWindowW(L"Button", L"EXIT GAME",
                WS_VISIBLE | WS_CHILD ,
                90, 280, 290, 30, hwnd, (HMENU) EXIT, NULL, NULL);


                goto skip_difficulties;

                choosing_grid:

            b_button = CreateWindowW(L"Button", L"Beginner",
                WS_VISIBLE | WS_CHILD ,
                110, 110, 110, 30, hwnd, (HMENU) BEGINNER, NULL, NULL);
                //x, y, width, height
            e_button = CreateWindowW(L"Button", L"Expert",
                WS_VISIBLE | WS_CHILD ,
                250, 110, 110, 30, hwnd, (HMENU) EXPERT, NULL, NULL);

            c_button = CreateWindowW(L"Button", L"Choose Grid",
                WS_VISIBLE | WS_CHILD ,
                150, 160, 170, 30, hwnd, (HMENU) CHOOSE_DIFFICULTY, NULL, NULL);

            return_button = CreateWindowW(L"Button", L"Return To Main Menu",
                WS_VISIBLE | WS_CHILD ,
                125, 220, 220, 30, hwnd, (HMENU) MAINMENU, NULL, NULL);

            goto skip_guide;

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





	//---------------------Game Guide ---------------------
        game_guide:



        guide_text = CreateWindowW(L"Static", guide,
            WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
            80, 20, 340, 150,
            hwnd, (HMENU) 1, NULL, NULL);

        return_button = CreateWindowW(L"Button", L"Return To Main Menu",
                WS_VISIBLE | WS_CHILD ,
                125, 220, 220, 30, hwnd, (HMENU) MAINMENU, NULL, NULL);

        DestroyWindow(text);DestroyWindow(computer_button);DestroyWindow(player_button);
        DestroyWindow(e_button);DestroyWindow(b_button);DestroyWindow(c_button);
        DestroyWindow(guide_button);DestroyWindow(top10_button);DestroyWindow(exit_button);



	//-------------------Buttons-----------------------------



            skip_Game_lobby:
            skip_difficulties:
            skip_guide:


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
