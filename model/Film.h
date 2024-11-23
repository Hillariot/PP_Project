#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#pragma once

struct Film {		//Структура
	std::string name;
	std::vector<std::string> times;
};

std::map<std::string, Film> split(std::vector<std::string> lines) {		//Разделить и закинуть название и времена сеансов в структуру и сформировать словарь
	std::map<std::string, Film> Film_dates;
	for (std::string separate_str : lines) {

		std::string element;		//Элемент, который формируется посимвольно до знака ;
		Film data_Film;
		std::string date;
		short flag = 0;		//Флаг на первых два слова
		unsigned i = 0;

		while (flag < 2) {
			if (separate_str[i] != ';') {
				element.push_back(separate_str[i]);		//Дописать символ, если он не ;
			}
			else {
				switch (flag)
				{
				case 0:		//Дата
					date = element;
					break;
				case 1:		//Название фильма
					data_Film.name = element;
					break;
				default:
					break;
				}
				element = "";
				flag++;
			}
			i++;
		}
		separate_str.erase(0, i);		//Оставляем только даты
		std::istringstream times_data(separate_str);
		std::string time;
		std::vector<std::string> times;
		while (times_data >> time) {		//Поделить времена потоком
			times.push_back(time);
		}
		data_Film.times = times;		//Поместить времена на место в структуре
		Film_dates[date] = data_Film;
	}
	
	
	
	return Film_dates;
}


std::map<std::string, Film> Open_and_Read_file(std::string path)		//Открытие файла и запись в словарь
{
	std::ifstream input_file;
	input_file.open(path);

	if (!(input_file.is_open()))		//Файл не открылся
	{
		std::cout << "Error file open";

	}
	else {
		std::vector<std::string> lines;
		while (!input_file.eof())	//Пока не опустел
		{
			std::string separate_str;
			getline(input_file, separate_str);
			lines.push_back(separate_str);
			
		}
		input_file.close();
		return split(lines);	//Составить словарь на основе множества фильмов
	}
	
}

int main() {

}
