//
// Created by User on 20/8/2025.
//

#include <ctime>
#include <sstream>
#include <iomanip>
#include "utils/utils.h"


std::string getTimeCustom() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    std::ostringstream oss;
    oss << std::setfill('0')
        << std::setw(2) << localTime->tm_mday << "/"
        << std::setw(2) << (localTime->tm_mon + 1) << "/"
        << (localTime->tm_year + 1900)
        << " -> "
        << std::setw(2) << localTime->tm_hour << ":"
        << std::setw(2) << localTime->tm_min;

    return oss.str();
}