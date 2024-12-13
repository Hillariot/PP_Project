#include "lib/interface_design.h"
#include "lib/logic.h"
#include "lib/registration.h"
#include "model/Film.h"
#include "model/Date.h"
#include "lib/Converter.h"

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>

#ifndef __linux__
#include <Windows.h>	
#endif

using namespace std;

bool find_time(std::vector<std::string> times, std::string time)
{
	for (int i = 0; i < times.size(); i++)
	{
		if (times[i] == time)
			return true;
	}
	return false;
}

void set_cinemahall(vector<vector<int>>& cinemahall)
{
	vector<int> tmp;
	for (int i = 1; i < 8; i++)
	{
		for (int j = 0; j < i * 4; j++)
		{
			tmp.push_back(0);
		}
		cinemahall.push_back(tmp);
		tmp.clear();
	}
	
}

int main()
{
#ifndef __linux__
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
#endif // !__linux__

	vector<vector<int>> cinemahall;

	//registrate("loginsdada ", "passwordsdadas", "base.txt");
	//center_print("1. Вход");
	auto seanses = get_file_info("E:\\C++\\PP_Project\\Data\\Schedule.txt"); 	// пример строки в файле 01.12.2024;Doctor Who;11:00,12:00,16:00
	auto coasts = get_file_info("E:\\C++\\PP_Project\\Data\\Coast.txt");		// пример строки в файле 01.12.2024;Doctor Who;00:00-390rub,15:15-450rub,20:20-500rub
	
	string console_buffer;

	bool check;

	string lastDate;
	int back = 0;
	int choice;

	pair<string, Film> choose_film;

	vector<Film> choose_film_for_date;
	do
	{
		system("cls");
		for (auto i : seanses)
		{
			if (validate_date(i.first) && i.second.size() != 0 && now_and_(now_date_str(), stodate(i.first)))
			{
				cout << i.first << "\n";
				print_films(seanses, stodate(i.first));
				cout << "\n\n";
			}
		}

		switch (back)
		{
			case 0:
			{
				cout << "\n0 - Выход\nВведите дату сеансов (дд.мм.гггг): ";

				do
				{
					getline(cin, console_buffer);
					if (console_buffer.length() == 1 && console_buffer.find('0') != string::npos)
						exit(0);
					check = validate_date(console_buffer);
					if (!check)
						cout << "Неверный формат даты, повторите попытку (дд.мм.гггг): ";

				} while (!check);
				choose_film.first = console_buffer;
				back++;
				break;
			}
			case 1:
			{
				

				system("cls");

				print_films(seanses, stodate(choose_film.first));

				choose_film_for_date = seanses[choose_film.first];


				do
				{
					cout << "\n0 - Назад\nВведите название фильма: ";
					getline(cin, console_buffer);
					if (console_buffer.length() == 1 && console_buffer.find('0') != string::npos)
					{
						back--;
						break;
					}
				} while (!film_exist(choose_film_for_date, console_buffer, choose_film));
				choose_film_for_date.clear();
				if (back == 1)
					back++;
				break;
				
			}
			case 2:
			{
				system("cls");

				print_film(choose_film.second, choose_film.first);

				print_coasts(choose_film, coasts, "Цена скоро появится");

				do
				{
					cout << "\n0 - Назад\nВведите время сеанса (чч:мм): ";
					getline(cin, console_buffer);

					if (console_buffer.length() == 1 && console_buffer.find('0') != string::npos)
					{
						back--;
						break;
					}
					else if (!validateTime(console_buffer))
						cout << "Введён неверный формат времени\n";
					else if (!find_time(choose_film.second.data, console_buffer))
						cout << "Такого времени нет в расписании\n";

				} while (!back && (!validateTime(console_buffer) || !find_time(choose_film.second.data, console_buffer)));
				if (back == 2)
				{

					set_cinemahall(cinemahall);

					set_padding(strlen("Экран") - 4);
					cout << "Экран\n\n";

					print_cinemahall(cinemahall);

					getchar();
					back++;
				}
				
				break;
			}
			default:
				getchar();
				break;
		}
	} while (true);
	
	


	return 0;
}