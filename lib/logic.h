﻿#pragma once
#include "../model/constants.h"
#include "../model/Film.h"
#include "../model/Date.h"
#include "Converter.h"

#include <regex>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

std::vector<std::string> split(std::string s, const std::string& delimiter) 
{
	std::vector<std::string> tokens;
	std::size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos)
	{
		token = s.substr(0, pos);
		tokens.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	tokens.push_back(s);

	return tokens;
}

bool validateSeat(const std::string& row, const std::string& seat) 
{
	if (!std::regex_match(row, std::regex(R"(\d+)")) || !std::regex_match(seat, std::regex(R"(\d+)"))) return false;
	int rowNum = std::stoi(row);
	int seatNum = std::stoi(seat);
	return rowNum >= 1 && rowNum <= MAX_ROW && seatNum >= 1 && seatNum <= MAX_COLUMN;
}

bool validateName(const std::string& name) 
{
	std::regex pattern(R"([A-Za-zА-Яа-яЁё]{2,50})");
	return std::regex_match(name, pattern);
}

bool validatePhone(const std::string& phone) 
{
	std::regex pattern(R"((\+7|8)\d{10})");
	return std::regex_match(phone, pattern);
}

bool validateEmail(const std::string& email) 
{
	std::regex pattern(R"([^@\s]+@[^@\s]+\.[A-Za-z]{2,})");
	return std::regex_match(email, pattern);
}

bool validateAge(const std::string& age) 
{
	if (!std::regex_match(age, std::regex(R"(\d+)"))) return false;
	int ageInt = std::stoi(age);
	return ageInt >= 1 && ageInt <= 120;
}

bool validateDate(const std::string& date) 
{
	std::regex pattern(R"(\d{2}\.\d{2}\.\d{4})");
	return std::regex_match(date, pattern);
}

bool validateTime(const std::string& time) 
{
	std::regex pattern(R"((0\d|1\d|2[0-3]):[0-5]\d)");
	return std::regex_match(time, pattern);
}

bool validateTicketCount(const std::string& count) 
{
	return std::regex_match(count, std::regex(R"(\d+)"));
}

bool validate_date(const std::string& _dd_mm_yyyy)
{
	auto count_dot = [](const std::string& date)
		{
			int cnt = 0;
			for (int i = 0; i < date.length(); i++)
			{
				if (date[i] == '.')
					cnt++;
				if (cnt > 3)
					return false;
			}
			if (cnt != 3)
				return false;
			return true;
		};

	if (_dd_mm_yyyy.size() != 10)
		return false;

	if (count_dot(_dd_mm_yyyy))
		return false;

	std::vector<std::string> dd_mm_yyyy = split(_dd_mm_yyyy, ".");

	int dd = 0;
	int mm = 0;
	int yyyy = 0;

	if (string_to_int(dd_mm_yyyy[0], dd) && string_to_int(dd_mm_yyyy[1], mm))
	{
		if (dd >= 1 && dd <= 31 && mm >= 1 && mm <= 12)
			return true;
	}

	dd_mm_yyyy.clear();

	return false;
}

std::map<std::string, std::vector<Film>> parser(std::vector<std::string> lines) 
{		//��������� � �������� �������� � ������� ������� � ��������� � ������������ �������
	std::map<std::string, std::vector<Film>> Film_dates;
	for (std::string separate_str : lines) {
		if (separate_str != "")
		{

			//std::string element;		//�������, ������� ����������� ����������� �� ����� ;
			//Film data_Film;
			//std::string date;
			//short flag = 0;		//���� �� ������ ��� �����
			//unsigned i = 0;

			//while (flag < 2) {
			//	if (separate_str[i] != ';') 
			//	{
			//		element.push_back(separate_str[i]);		//�������� ������, ���� �� �� ;
			//	}
			//	else 
			//	{
			//		switch (flag)
			//		{
			//		case 0:		//����
			//			date = element;
			//			break;
			//		case 1:		//�������� ������
			//			data_Film.name = element;
			//			break;
			//		default:
			//			break;
			//		}
			//		element = "";
			//		flag++;
			//	}
			//	i++;
			//}
			//separate_str.erase(0, i);		//��������� ������ �����
			//std::string time;
			//std::vector<std::string> times;

			//for (std::string time : split(separate_str, ","))
			//	data_Film.data.push_back(time);

			//Film_dates[date].push_back(data_Film);

			auto data = split(separate_str, ";");
			Film data_Film;
			data_Film.name = data[1];
			for (auto i : split(data[2], ","))
			{
				data_Film.data.push_back(split(i, "-")[0]);
				data_Film.subdata.push_back(split(i, "-")[1]);
			}
			Film_dates[data[0]].push_back(data_Film);
		}
	}
	/*12.12.2024; Аватар 2; 11:00, 12 : 00, 16 : 00
		13.12.2024; Принц Персии 1; 11:00, 12 : 00, 16 : 00
		13.12.2024; Принц Персии 2; 11:00, 12 : 00, 16 : 00
		13.12.2024; Принц; 11:00, 12 : 00, 16 : 00
		14.12.2024; Принц Персии 1; 11:00, 12 : 00, 16 : 00
		14.12.2024; Принц Персии 2; 11:00, 12 : 00, 16 : 00
		14.12.2024; Принц; 11:00, 12 : 00, 16 : 00*/
	return Film_dates;
}

std::map<std::string, std::vector<Film>> get_file_info(std::string path)		//�������� ����� � ������ � �������
{
	std::ifstream input_file;
	input_file.open(path);

	if (!(input_file.is_open()))		//���� �� ��������
	{
		std::cout << "Error file open";
		exit(1);
	}
	else
	{
		std::vector<std::string> lines;
		while (!input_file.eof())	//���� �� �������
		{
			std::string separate_str;
			getline(input_file, separate_str);
			lines.push_back(separate_str);
		}
		input_file.close();
		return parser(lines);	//��������� ������� �� ������ ��������� �������
	}

}

int fulltime(std::string time)
{
	std::vector<std::string> hh_mm = split(time, ":");
	return stoi(hh_mm[0]) * 60 + stoi(hh_mm[1]);
}

bool film_exist(const std::vector<Film>& seanses, const std::string& film_search, std::pair<std::string, Film>& info)
{
	for (int i = 0; i < seanses.size(); i++)
	{
		if (seanses[i].name == film_search)
		{
			info.second.name = seanses[i].name;
			info.second.data = seanses[i].data;
			return true;
		}
	}
	return false;
}