﻿#include "Display.h"
#include "Login.h"
#include "Airport.h"
#include "srilakshmikanthanp/Figlet.hpp"

using namespace srilakshmikanthanp;
using namespace std;

Figlet figlet(FigletFont::make("Fonts/Standard.flf"), Smushed::make());
void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = {x, y};
	SetConsoleCursorPosition(h, c);
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void TextColor(int color)
{
	HANDLE Color;

	Color = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(Color, color);
}

void Display::SayGoodBye()
{
	system("cls");
	cout << figlet("Hen gap lai");
	system("pause");
	exit(0);
}

void Display::DisplayCursor(int pre_move, int move)
{
	gotoxy(PIVOT_X - 3, 2 * TITLE_Y + pre_move * STEP_Y);
	TextColor(7);
	cout << "  ";

	gotoxy(PIVOT_X - 3, 2 * TITLE_Y + move * STEP_Y);
	TextColor(CURSOR_COLOR);
	cout << ">>";
}

// ======== SHOW OPTION ========= //
void Display::ShowOptionMenu()
{
	gotoxy(TITLE_X - 2, TITLE_Y);
	TextColor(TITLE_COLOR);
	cout << setw(52) << right << "============= HIEN THI THONG TIN ============="; // NAM
	gotoxy(PIVOT_X + 1, TITLE_Y + STEP_Y);
	TextColor(OPTION_COLOR);
	cout << "    Chuyen bay bay    ";

	gotoxy(PIVOT_X + 1, TITLE_Y + 2 * STEP_Y);
	cout << "        May bay       ";

	gotoxy(PIVOT_X + 1, TITLE_Y + 3 * STEP_Y);
	cout << "          Ve          ";

	gotoxy(PIVOT_X - 13, TITLE_Y + 4 * STEP_Y);
	TextColor(4);
	cout << "<= Nhan ESC de thoat - BackSpace de quay lai =>";
}
void Display::ControlShowOption()
{
	int move = 0;
	int pre_move = 0;
	int option = 0;
	ShowConsoleCursor(false);
	system("cls");
	ShowOptionMenu();
	DisplayCursor(pre_move, move);
	while (1)
	{
		if (_kbhit())
		{
			char key = _getch();
			if (key == -32)
				key = _getch();
			switch (key)
			{
			case 'w':
			case 'W':
			case 72:
			{
				if (move > 0)
				{
					pre_move = move;
					--move;
				}
				break;
			}
			case 's':
			case 'S':
			case 80:
			{
				if (move < SHOW_OPTION - 1)
				{
					pre_move = move;
					++move;
				}
				break;
			}
			case 13:
			{
				TextColor(SHOW_COLOR);
				option = move;
				system("cls");
				TextColor(9);
				switch (option)
				{
				case 0:
				{ // NAM
					cout << "                           ========= DANH SACH CHUYEN BAY =========                          " << endl;
					TextColor(SHOW_COLOR);
					cout << "STT |   Ma hieu  |   Ma chuyen bay   |     Noi den     |     Noi di     |     IFSC     |     Gia ve" << endl;
					cout << "=======================================================================================================";
					break;
				}

				case 1:
				{ // NAM
					cout << "                           ========== DANH SACH MAY BAY ==========                           " << endl;

					TextColor(SHOW_COLOR);
					cout << "STT |     Ma hieu     |     Loai     |     Code     |     So day     |     So ghe     |     So ve" << endl;
					cout << "==================================================================================================";
					break;
				}

				default:
				{
					cout << "\n                    ======= DANH SACH VE MAY BAY =======                                    " << endl;
					TextColor(SHOW_COLOR);
					cout << "STT |   Ma chuyen bay   |   Ten khach hang   |   Gioi tinh   |     CMND     |   Ma khach hang" << endl;
					cout << "=============================================================================================";
				}

				break;
				}

				Airport aport;
				aport.Show(option);
				TextColor(12);
				cout << "\n\n<== Nhan phim bat ky de tiep tuc ==>" << endl;
				_getch();
				ControlShowOption();
				return;
			}
			case 8:
				return;
			case 27:
				SayGoodBye();
			}
		}
		DisplayCursor(pre_move, move);
	}
}

// ======== UPDATE OPTION ========= //
int ReduceUpdateCode(const char *functionName)
{
	system("cls");
	ShowConsoleCursor(true);
	TextColor(UPDATE_COLOR);
	cout << setw(17) << right << "========== " << functionName << " ==========" << endl;
	TextColor(10);
	cout << "0 - CHUYEN BAY, 1 - MAY BAY, 2 - VE >> ";
	TextColor(7);
	int type;
	cin >> type;
	if (type != 0 && type != 1 && type != 2)
		cin.ignore();
	if (cin.fail())
		throw "Du lieu nhap khong phai so";
	return type;
}
void Display::UpdateOptionMenu()
{
	gotoxy(TITLE_X - 2, TITLE_Y);
	TextColor(TITLE_COLOR);
	cout << setw(41) << "============= CAP NHAT ============="; // NAM

	gotoxy(PIVOT_X + 1, TITLE_Y + STEP_Y);
	TextColor(OPTION_COLOR);
	cout << "   Them   ";

	gotoxy(PIVOT_X + 1, TITLE_Y + 2 * STEP_Y);
	cout << "   Xoa    ";

	gotoxy(PIVOT_X + 1, TITLE_Y + 3 * STEP_Y);
	cout << " Sua chua ";

	gotoxy(PIVOT_X - 13, TITLE_Y + 4 * STEP_Y);
	TextColor(4);
	cout << "<= Nhan ESC de thoat - BackSpace de quay lai =>";
}
void Display::ControlUpdateOption()
{
	int move = 0;
	int pre_move = 0;
	int option = 0;
	ShowConsoleCursor(false);
	system("cls");
	UpdateOptionMenu();
	DisplayCursor(pre_move, move);
	while (1)
	{
		if (_kbhit())
		{
			char key = _getch();
			if (key == -32)
				key = _getch();
			switch (key)
			{
			case 'w':
			case 'W':
			case 72:
			{
				if (move > 0)
				{
					pre_move = move;
					--move;
				}
				break;
			}
			case 's':
			case 'S':
			case 80:
			{
				if (move < SHOW_OPTION - 1)
				{
					pre_move = move;
					++move;
				}
				break;
			}
			case 13:
			{
				option = move;
				switch (option)
				{
				case 0:
				{
					int type = ReduceUpdateCode("THEM");
					Airport aport;
					aport.Add(type);
					break;
				}
				case 1:
				{
					int type = ReduceUpdateCode("XOA");
					Airport aport;
					aport.Delete(type);
					break;
				}
				default:
				{
					int type = ReduceUpdateCode("SUA CHUA");
					Airport aport;
					aport.Edit(type);
					break;
				}
				break;
				}

				TextColor(12);
				cout << "\n<== Nhan phim bat ky de tiep tuc ==>" << endl;
				_getch();
				ControlUpdateOption();
				return;
			}
			case 8:
				return;
			case 27:
				SayGoodBye();
			}
		}
		DisplayCursor(pre_move, move);
	}
}

// ======== SEARCH OPTION ========= //
void Display::SearchOptionMenu()
{
	gotoxy(TITLE_X - 2, TITLE_Y);
	TextColor(TITLE_COLOR);
	cout << setw(47) << right << "============= TIM KIEM ============="; // NAM

	gotoxy(PIVOT_X + 1, TITLE_Y + STEP_Y);
	TextColor(OPTION_COLOR);
	cout << "      Chuyen bay      ";

	gotoxy(PIVOT_X + 1, TITLE_Y + 2 * STEP_Y);
	cout << "       May bay        ";

	gotoxy(PIVOT_X + 1, TITLE_Y + 3 * STEP_Y);
	cout << "         Ve           ";

	gotoxy(PIVOT_X - 13, TITLE_Y + 4 * STEP_Y);
	TextColor(4);
	cout << "<= Nhan ESC de thoat - BackSpace de quay lai =>";
}
void Display::ControlSearchOption()
{
	int move = 0;
	int pre_move = 0;
	int option = 0;
	ShowConsoleCursor(false);
	system("cls");
	SearchOptionMenu();
	DisplayCursor(pre_move, move);
	while (1)
	{
		if (_kbhit())
		{
			char key = _getch();
			if (key == -32)
				key = _getch();
			switch (key)
			{
			case 'w':
			case 'W':
			case 72:
			{
				if (move > 0)
				{
					pre_move = move;
					--move;
				}
				break;
			}
			case 's':
			case 'S':
			case 80:
			{
				if (move < SHOW_OPTION - 1)
				{
					pre_move = move;
					++move;
				}
				break;
			}
			case 13:
			{
				option = move;
				switch (option)
				{
				case 0:
				{
					system("cls");
					ShowConsoleCursor(true);
					TextColor(UPDATE_COLOR);
					cout << setw(43) << "========== TIM KIEM CHUYEN BAY ==========" << endl; // NAM
					TextColor(10);
					cout << "Tim kiem bang (0 - Ma chuyen bay, 1 - ISFC) >> ";
					TextColor(7);
					int type;
					cin >> type;
					if (cin.fail())
						throw "Du lieu nhap khong phai so";
					TextColor(11);
					Airport aport;
					int found = aport.Search(option, type);
					if (found != NOT_FOUND)
					{
						TextColor(SHOW_COLOR);
						cout << setw(61) << right << "========== TIM THAY ==========" << endl;
						cout << "  |   Ma hieu  |   Ma chuyen bay   |     Noi den     |     Noi di     |     IFSC     |     Gia ve" << endl;
						cout << "=======================================================================================================" << endl;
						aport.GetFlight(found)->Output();
					}
					else
					{
						TextColor(13);
						cout << "\n========== KHONG TIM THAY ==========" << endl;
					}
					break;
				}
				case 1:
				{
					system("cls");
					ShowConsoleCursor(true);
					TextColor(UPDATE_COLOR);
					cout << setw(44) << right << "========== TIM KIEM MAY BAY ==========" << endl;
					TextColor(10);
					cout << "Tim kiem bang (0 - Loai may bay, 1 - Ma hieu) >> ";
					TextColor(7);
					int type;
					cin >> type;
					if (cin.fail())
						throw "Du lieu nhap khong phai so";
					TextColor(11);
					Airport aport;
					int found = aport.Search(option, type);
					if (found != NOT_FOUND)
					{
						TextColor(SHOW_COLOR);
						cout << setw(60) << right << "========== TIM THAY ==========" << endl;
						cout << "  |     Ma hieu     |     Loai     |     Code     |     So day     |     So ghe     |     So ve" << endl;
						cout << "===============================================================================================" << endl;
						aport.GetPlane(found)->Output();
					}
					else
					{
						TextColor(13);
						cout << "\n========== KHONG TIM THAY ==========" << endl;
					}
					break;
				}
				default:
				{
					system("cls");
					ShowConsoleCursor(true);
					TextColor(UPDATE_COLOR);
					cout << "========== TIM KIEM VE ==========" << endl;
					TextColor(11);
					Airport aport;
					int found = aport.Search(option, 0);
					if (found != NOT_FOUND)
					{
						TextColor(13);
						cout << setw(60) << right << "========== TIM THAY ==========" << endl;
						TextColor(SHOW_COLOR);
						cout << "  |   Ma chuyen bay   |   Ten khach hang   |   Gioi tinh   |     CMND     |   Ma khach hang" << endl;
						cout << "=============================================================================================";
						aport.GetTicket(found)->Output();
					}
					else
					{
						TextColor(13);
						cout << "\n========== KHONG TIM THAY ==========" << endl;
					}
					break;
				}
				}

				TextColor(12);
				cout << "\n<== Nhan phim bat ky de tiep tuc ==>" << endl;
				_getch();
				ControlSearchOption();
				return;
			}
			case 8:
				return;
			case 27:
				SayGoodBye();
			}
		}
		DisplayCursor(pre_move, move);
	}
}

// ======== BORROW BOOKS OPTION ========= //
void Display::ControlBuyTicketOption()
{
	system("cls");
	gotoxy(TITLE_X - 2, TITLE_Y);
	TextColor(TITLE_COLOR);
	ShowConsoleCursor(true);
	cout << "======== MUA VE ========";
	TextColor(7);
	// Airport aport;
	// aport.BuyTickets();
	// TextColor(12);
	cout << "\n<== Nhan phim bat ky de tiep tuc ==>" << endl;
	_getch();
}

// ======== MAIN DISPLAY ======== //
void Display::MainMenu()
{

	gotoxy(PIVOT_X - 12, TITLE_Y);
	TextColor(TITLE_COLOR);
	cout << "====== HE THONG QUAN LY SAN BAY ======";

	gotoxy(PIVOT_X, TITLE_Y + STEP_Y);
	TextColor(OPTION_COLOR);
	cout << "  Hien Thi  ";

	gotoxy(PIVOT_X, TITLE_Y + 2 * STEP_Y);
	cout << "  Cap Nhat  ";

	gotoxy(PIVOT_X, TITLE_Y + 3 * STEP_Y);
	cout << "  Tim Kiem  ";

	gotoxy(PIVOT_X - 6, TITLE_Y + 5 * STEP_Y);
	TextColor(4);
	cout << "<== Nhan ESC de thoat ==>";
}
void Display::DisplayMain()
{
	system("cls");
	int move = 0;
	int pre_move = 0;
	int option = 0;
	ShowConsoleCursor(false);
	MainMenu();
	DisplayCursor(pre_move, move);
	while (1)
	{
		if (_kbhit())
		{
			char key = _getch();
			if (key == -32)
				key = _getch();
			switch (key)
			{
			case 'w':
			case 'W':
			case 72:
			{
				if (move > 0)
				{
					pre_move = move;
					--move;
				}
				break;
			}
			case 's':
			case 'S':
			case 80:
			{
				if (move < MAX_OPTION - 3)
				{
					pre_move = move;
					++move;
				}
				break;
			}
			case 13:
			{
				option = move;
				switch (option)
				{
				case 0:
				{
					ControlShowOption();
					DisplayMain();
					return;
				}
				case 1:
				{
					ControlUpdateOption();
					DisplayMain();
					return;
				}
				case 2:
				{
					ControlSearchOption();
					DisplayMain();
					return;
				}
				// case 3:
				// {
				// 	ControlBuyTicketOption();
				// 	DisplayMain();
				// 	return;
				// }
				// case 4:
				// {
				// 	// ControlCancelTicketOption();
				// 	DisplayMain();
				// 	return;
				// }
				break;
				}
			case 27:
				SayGoodBye();
			}
			}
			DisplayCursor(pre_move, move);
		}
	}
}
//=========dang nhap dang ky===========
void Display::ShowLogin()
{
	system("cls");
	// Figlet figlet(FigletFont::make("Fonts/Standard.flf"), Smushed::make());
	// TextColor(TITLE_COLOR);
	// gotoxy(0, 0);
	// cout << figlet("Chao ban!");
	Figlet figlet(FigletFont::make("Fonts/Standard.flf"), Smushed::make());
	TextColor(TITLE_COLOR);
	cout << figlet(" San bay HVN ");

	TextColor(OPTION_COLOR);
	gotoxy(PIVOT_X, TITLE_Y + 2 * STEP_Y);
	cout << "  dang ky   ";
	gotoxy(PIVOT_X, TITLE_Y + 3 * STEP_Y);
	cout << "  dang nhap ";
}
void Display::MainLogin()
{
	Login app;
	int option;
	bool isLogin;
	int move = 1;
	int pre_move = 0;
	ShowLogin();
	ShowConsoleCursor(false);
	DisplayCursor(pre_move, move);
	while (1)
	{
		if (_kbhit())
		{
			char key = _getch();
			if (key == -32)
				key = _getch();
			switch (key)
			{
			case 'w':
			case 'W':
			case 72:
			{
				if (move > 1)
				{
					pre_move = move;
					--move;
				}
				break;
			}
			case 's':
			case 'S':
			case 80:
			{
				if (move < MAX_OPTION - 3)
				{
					pre_move = move;
					++move;
				}
				break;
			}
			case 13:
			{
				option = move;
				switch (option)
				{
				case 1:
				{
					app.dangKi();
					MainLogin();
					return;
				}
				case 2:
				{
					app.dangNhap();
					MainLogin();
					return;
				}
				break;
				}
			case 27:
				SayGoodBye();
			}
			}
			DisplayCursor(pre_move, move);
		}
	}
}