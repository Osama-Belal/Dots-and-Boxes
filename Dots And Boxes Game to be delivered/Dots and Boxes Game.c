#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "playing.h"
#include "top_10.h"
#include "VS computer.h"
#include "save, load.h"

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
#define LOAD_1 9010
#define LOAD_2 9011
#define LOAD_3 9012




HWND start_button, text, guide_text, computer_button, player_button, exit_button, guide_button, top10_button;
HWND b_button, e_button, c_button, return_button, l1_button, l2_button, l3_button;

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
	wc.hbrBackground = (HBRUSH)(COLOR_HIGHLIGHT+1);
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
		500, 200, 600, 450,
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

}





LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    static int computer_flag, players_flag;

    static wchar_t *lyrics =  L"\nDots and Boxes \nWelcome to the game!";
    static wchar_t *guide =  L"\nDots and Boxes is a game for two players (or more).Starting with an empty grid of dots,"
                                "two players take turns adding a single horizontal or vertical line between two unjoined adjacent"
                                "dots. The player who completes the fourth side of a 1x1 box (or groups of one or more adjacent"
                                "boxes) earns one point (s) and takes another turn."
                                "When short on time, a 2x2 board (a square of"
                                "9 dots) is good for beginners. A 5x5 is good for experts."
                                "Score is calculated based on the number of boxes you have. The game ends when no more"
                                "lines can be placed. The winner is the player with the most points."
                                "When a player connects dots, it may produce a chain, a chain is a groups of adjacent boxes"
                                "in which any move gives all the boxes in the chain to the player."
                                "In Dots and Boxes there is only one action, which is connecting between two dots (draw a line)"
                                "in order produce a box or a chain.If a player wins a box or a chain, he should take"
                                "another turn to draw another line and so on...";


    HWND console;
    AllocConsole();
    console = FindWindowA("ConsoleWindowClass", NULL);
    //ShowWindow(console, 0);


    // -------------------------------------- navigation bar ---------------------------------------------
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
			AppendMenu(hSubMenu, MF_STRING, TOP_10, "&Top 10");
			AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&More");

            hSubMenu = CreatePopupMenu();
			AppendMenu(hSubMenu, MF_STRING, EXIT, "YES");
			AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Exit");

			SetMenu(hwnd, hMenu);

			hIcon = (HICON)LoadImage(NULL, "dots.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);

			if(hIcon){SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);}
			else {MessageBox(hwnd, "Could not load large icon! Is it in the current working directory?", "Error", MB_OK | MB_ICONERROR);}

			hIconSm = (HICON)LoadImage(NULL, "dots.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE);

			if(hIconSm){SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIconSm);}
			else {MessageBox(hwnd, "Could not load small icon! Is it in the current working directory?", "Error", MB_OK | MB_ICONERROR);}

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



			// load
			switch(LOWORD(wParam))
			{

				case LOAD_1:
				    system("cls");ShowWindow(console, 1);
					if(!computer_flag && players_flag){game('l');break;}
					else if(computer_flag && !players_flag){vs_computer('l');break;}
				case LOAD_2:
					system("cls");ShowWindow(console, 1);
					if(!computer_flag && players_flag){game('s');break;}
					else if(computer_flag && !players_flag){vs_computer('s');break;}
				case LOAD_3:
					system("cls");ShowWindow(console, 1);
					if(!computer_flag && players_flag){game('p');break;}
					else if(computer_flag && !players_flag){vs_computer('p');break;}

			}



			// OTHER
			switch(LOWORD(wParam))
			{
				case TOP_10:
				    system("cls");ShowWindow(console, 1);top_ten_list();break;
					//MessageBox(hwnd, "TOP 10 List!", "Woo!", MB_OK);
                case GAME_GUIDE:
					//MessageBox(hwnd, "I'll show you the guide!", "Woo!", MB_OK);
					goto game_guide;break;
                case START:
                    DestroyWindow(start_button);goto start_game;break;
                case MAINMENU:
                    DestroyWindow(b_button);DestroyWindow(e_button);DestroyWindow(c_button);
                    DestroyWindow(l1_button);DestroyWindow(l2_button);DestroyWindow(l3_button);
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


	// ------------------------------------ navigation bar end ------------------------------------------



	//---------------------------------------- Buttons ------------------------------------


        start_button = CreateWindowW(L"Button", L"Start Game",
                WS_VISIBLE | WS_CHILD,
                150, 140, 300, 80, hwnd, (HMENU) START, NULL, NULL);

        DestroyWindow(text);DestroyWindow(computer_button);DestroyWindow(player_button);
        DestroyWindow(e_button);DestroyWindow(b_button);DestroyWindow(c_button);
        DestroyWindow(l1_button);DestroyWindow(l2_button);DestroyWindow(l3_button);
        DestroyWindow(guide_button);DestroyWindow(top10_button);
        DestroyWindow(return_button);DestroyWindow(exit_button);

        ShowWindow(console, 0);

        goto skip_Game_lobby;

        start_game:

        text = CreateWindowW(L"Static", lyrics,
            WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
            200, 40, 180, 70,
            hwnd, (HMENU) 1, NULL, NULL);


            player_button = CreateWindowW(L"Button", L"Player VS Player",
                WS_VISIBLE | WS_CHILD ,
                90, 150, 180, 50, hwnd, (HMENU) VSPLAYER, NULL, NULL);

            computer_button = CreateWindowW(L"Button", L"Player VS Computer",
                WS_VISIBLE | WS_CHILD ,
                310, 150, 180, 50, hwnd, (HMENU) VSCOMPUTER, NULL, NULL);

            top10_button = CreateWindowW(L"Button", L"TOP 10 List",
                WS_VISIBLE | WS_CHILD ,
                120, 240, 160, 40, hwnd, (HMENU) TOP_10, NULL, NULL);

            guide_button = CreateWindowW(L"Button", L"Game Guide",
                WS_VISIBLE | WS_CHILD ,
                300, 240, 160, 40, hwnd, (HMENU) GAME_GUIDE, NULL, NULL);

            exit_button = CreateWindowW(L"Button", L"EXIT GAME",
                WS_VISIBLE | WS_CHILD ,
                140, 320, 290, 50, hwnd, (HMENU) EXIT, NULL, NULL);


                goto skip_difficulties;

                choosing_grid:

            b_button = CreateWindowW(L"Button", L"Beginner",
                WS_VISIBLE | WS_CHILD ,
                155, 135, 125, 30, hwnd, (HMENU) BEGINNER, NULL, NULL);
                //x, y, width, height
            e_button = CreateWindowW(L"Button", L"Expert",
                WS_VISIBLE | WS_CHILD ,
                295, 135, 125, 30, hwnd, (HMENU) EXPERT, NULL, NULL);

            c_button = CreateWindowW(L"Button", L"Choose Grid",
                WS_VISIBLE | WS_CHILD ,
                200, 175, 170, 30, hwnd, (HMENU) CHOOSE_DIFFICULTY, NULL, NULL);

            l1_button = CreateWindowW(L"Button", L"Load File 1",
                WS_VISIBLE | WS_CHILD ,
                100, 220, 110, 30, hwnd, (HMENU) LOAD_1, NULL, NULL);

            l2_button = CreateWindowW(L"Button", L"Load File 2",
                WS_VISIBLE | WS_CHILD ,
                225, 220, 110, 30, hwnd, (HMENU) LOAD_2, NULL, NULL);

            l3_button = CreateWindowW(L"Button", L"Load File 3",
                WS_VISIBLE | WS_CHILD ,
                350, 220, 110, 30, hwnd, (HMENU) LOAD_3, NULL, NULL);

            return_button = CreateWindowW(L"Button", L"Return To Main Menu",
                WS_VISIBLE | WS_CHILD ,
                175, 270, 220, 30, hwnd, (HMENU) MAINMENU, NULL, NULL);

            goto skip_guide;



	//---------------------Game Guide ---------------------

        game_guide:



        guide_text = CreateWindowW(L"Static", guide,
            WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
            50, 20, 500, 230,
            hwnd, (HMENU) 1, NULL, NULL);

        return_button = CreateWindowW(L"Button", L"Return To Main Menu",
                WS_VISIBLE | WS_CHILD ,
                180, 265, 220, 40, hwnd, (HMENU) MAINMENU, NULL, NULL);

        DestroyWindow(text);DestroyWindow(computer_button);DestroyWindow(player_button);
        DestroyWindow(e_button);DestroyWindow(b_button);DestroyWindow(c_button);
        DestroyWindow(l1_button);DestroyWindow(l2_button);DestroyWindow(l3_button);
        DestroyWindow(guide_button);DestroyWindow(top10_button);DestroyWindow(exit_button);





            skip_Game_lobby:
            skip_difficulties:
            skip_guide:


    return DefWindowProcW(hwnd, Message, wParam, lParam);

	return 0;
}
