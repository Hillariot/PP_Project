#include "lib/interface_design.h"
#include "lib/logic.h"
#include "lib/registration.h"
#include "model/Film.h"
#include "model/Date.h"
#include "model/Ticket.h"
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

void reset(vector<vector<int>>& cinemahall)
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

void set_cinemahall(vector<vector<int>>& cinemahall, const pair<string, Film>& choose_film, const string& path_tickets, const string& time_seanse)
{
	ifstream fin(path_tickets);

	vector<Ticket> tickets;

	if (!fin.is_open())
		return;

	string line;

	Ticket t;

	vector<string> parse_line;

	while (getline(fin, line))
	{
		

		parse_line = split(line, ";");

		t.date = parse_line[0];
		t.filmName = parse_line[1];
		t.startTime = parse_line[2];
		string_to_int(parse_line[3], t.hallNumber);
		int raw;
		for (auto i : split(parse_line[4], ","))
		{
			string_to_int(i, raw);
			t.raws.push_back(raw);
		}
		int seat;
		for (auto i : split(parse_line[5], ","))
		{
			string_to_int(i, seat);
			t.seats.push_back(seat);
		}
		tickets.push_back(t);
	}

	for (auto i : tickets)
	{
		if (i.date == choose_film.first && i.filmName == choose_film.second.name && i.startTime == time_seanse)
		{
			for (int j = 0; j < i.raws.size(); j++)
			{	
				int raw = i.raws[j];
				int col = i.seats[j];
				cinemahall[i.raws[j]][i.seats[j]] = 1;
			}
		}
	}

	fin.close();
}

int main()
{
#ifndef __linux__
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
#endif // !__linux__

	vector<vector<int>> cinemahall;

	reset(cinemahall);

	//registrate("loginsdada ", "passwordsdadas", "base.txt");
	//center_print("1. ????");
	auto seanses = get_file_info("E:\\C++\\PP_Project\\Data\\Schedule.txt"); 	// Пример входных данных: 13.12.2024;Аватар;13:10-2,16:15-1
	auto coasts = get_file_info("E:\\C++\\PP_Project\\Data\\Coast.txt");		// Пример входных данных: 01.12.2024;Doctor Who;00:00-390rub,15:15-450rub,20:20-500rub
	
	string console_buffer;

	bool check;

	string lastDate;
	int back = 0;
	int choice;

	pair<string, Film> choose_film;

	vector<Film> choose_film_for_date;

	Ticket ticket;
	do
	{
		

		switch (back)
		{
			case 0:
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
				ticket.date = console_buffer;
				choose_film.first = ticket.date;
				back++;
				break;
			}
			case 1:
			{
				

				system("cls");

				print_films(seanses, stodate(ticket.date));

				choose_film_for_date = seanses[ticket.date];

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
				{
					back++;
					ticket.filmName = choose_film.second.name;
				}
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
				ticket.startTime = console_buffer;
				string_to_int(choose_film.second.subdata[get_filmIndex_time(choose_film.second, ticket.startTime)], ticket.hallNumber);
				if (back == 2 && find_time(choose_film.second.data, console_buffer))
				{


					set_padding(strlen("Экран") - 4);
					cout << "Экран\n\n";
					set_cinemahall(cinemahall, choose_film, "E:\\C++\\PP_Project\\Data\\Tickets.txt", ticket.startTime);
					do
					{
						
						print_cinemahall(cinemahall);
						cout << "\n0 - Назад\nВведите ряд: ";
						int raw;
						getline(cin, console_buffer);
						if (console_buffer.length() == 1 && console_buffer.find('0') != string::npos)
							break;
						if (!string_to_int(console_buffer, raw))
							continue;
						
						ticket.raws.push_back(raw);
						cout << "\n0 - Назад\nВведите место: ";
						int seat;
						getline(cin, console_buffer);
						if (console_buffer.length() == 1 && console_buffer.find('0') != string::npos)
							break;
						if (!string_to_int(console_buffer, seat))
							continue;
						ticket.seats.push_back(seat);
						cinemahall[raw][seat] = static_cast<int>(condition_place::your);
						cout << (console_buffer.length() == 1);
						
					} while (true);
					cinemahall.clear();
						reset(cinemahall);
					if(console_buffer != "0")
						save_ticket(ticket, "E:\\C++\\PP_Project\\Data\\Tickets.txt");
					back++;
				}
				break;
			}
			default:
				back = 0;
				break;
		}
	} while (true);
	
	


	return 0;
}