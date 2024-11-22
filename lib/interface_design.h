#pragma once

#include "../model/condition_place.h"
#include "../model/texture_for_seats.h"

#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

// Function for setting padding for centering
void set_padding(const int& size_text)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	int console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	int padding = (console_width - size_text) / 2;

	std::cout.width(padding);
}

// Function for displaying seats in the cinema hall
void print_cinemahall(const std::vector<std::vector<int>>& hall)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < hall.size(); i++)
	{
		set_padding(hall[i].size() * 2);

		for (int j = 0; j < hall[i].size(); j++)
		{
			switch (hall[i][j])
			{
			case static_cast<int>(condition_place::empty):
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
				std::cout << static_cast<char>(texture_for_seats::empty) << ' ';
				SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				break;

			case static_cast<int>(condition_place::seat):
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
				std::cout << static_cast<char>(texture_for_seats::seat) << ' ';
				SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				break;

			case static_cast<int>(condition_place::yours):
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
				std::cout << static_cast<char>(texture_for_seats::yours) << ' ';
				SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				break;
			}
		}
		std::cout << '\n';
	}
}