#pragma once

#include "../model/constants.h"
#include <regex>
#include <string>


bool validateName(const std::string& name) {
    std::regex pattern(R"([A-Za-zА-Яа-яЁё]{2,50})");
    return std::regex_match(name, pattern);
}
bool validatePhone(const std::string& phone) {
    std::regex pattern(R"((\+7|8)\d{10})");
    return std::regex_match(phone, pattern);
}
bool validateEmail(const std::string& email) {
    std::regex pattern(R"([^@\s]+@[^@\s]+\.[A-Za-z]{2,})");
    return std::regex_match(email, pattern);
}
bool validateAge(const std::string& age) {
    if (!std::regex_match(age, std::regex(R"(\d+)"))) return false;
    int ageInt = std::stoi(age);
    return ageInt >= 1 && ageInt <= 120;
}
bool validateDate(const std::string& date) {
    std::regex pattern(R"(\d{2}\.\d{2}\.\d{4})");
    return std::regex_match(date, pattern);
}
bool validateTime(const std::string& time) {
    std::regex pattern(R"((0\d|1\d|2[0-3]):[0-5]\d)");
    return std::regex_match(time, pattern);
}
bool validateSeat(const std::string& row, const std::string& seat) {
    if (!std::regex_match(row, std::regex(R"(\d+)")) || !std::regex_match(seat, std::regex(R"(\d+)"))) return false;
    int rowNum = std::stoi(row);
    int seatNum = std::stoi(seat);
    return rowNum >= 1 && rowNum <= MAX_ROW && seatNum >= 1 && seatNum <= MAX_COLUMN;
}
bool validateTicketCount(const std::string& count) {
    return std::regex_match(count, std::regex(R"(\d+)"));
}

