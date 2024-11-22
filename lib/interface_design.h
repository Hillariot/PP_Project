#pragma once

#include <iostream>
#include <windows.h>
#include <string>

// Функция для вывода текста по центру консоли
void center_text(const std::string& str)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	int console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	int padding = (console_width - str.length()) / 2;

	std::cout.width(padding);
	std::cout << str << '\n';
}