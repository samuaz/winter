//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2019-11-21.
//
#pragma once
#ifndef WINTERCPP_WINTER_RANDOM_H
#    define WINTERCPP_WINTER_RANDOM_H

#    include <chrono>
#    include <ctime>
#    include <iostream>
#    include <random>
#    include <sstream>
#    include <string>

namespace winter::random {
    using namespace std;

    unsigned int randomChar(bool onlyABC, bool onlyHex);

    std::string generateHex(unsigned int len);

    string uuidRandom();

    string timeNowHex();

    string highResolutionClockHex();

    string uuid(bool dashed);

    string uuid();

    string uuidDashed();

    string uuidNoDashed();

    std::size_t StreamSize(const std::stringstream &s);

}  // namespace winter::random

#endif  // WINTERCPP_WINTER_RANDOM_H
