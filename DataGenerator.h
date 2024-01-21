//
// Created by Gracjan Ziemiański on 02/01/2024.
//

#ifndef BACKEND_FLIGHT_RADAR_DATAGENERATOR_H
#define BACKEND_FLIGHT_RADAR_DATAGENERATOR_H

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

class DataGenerator {
public:
    static std::string generateAirlinesInsert(int count);
    static std::string generateAirportsInsert(int count);
    static std::string generateBookingsInsert(int count);
    static std::string generateFlightsInsert(int count);
};

#endif //BACKEND_FLIGHT_RADAR_DATAGENERATOR_H
