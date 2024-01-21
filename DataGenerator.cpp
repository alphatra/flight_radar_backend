//
// Created by Gracjan Ziemiański on 02/01/2024.
//
#include "DataGenerator.h"

std::string DataGenerator::generateAirlinesInsert(int count) {
    std::stringstream ss;
    ss << "INSERT INTO `Airlines` (`Name`, `Country`) VALUES ";
    for (int i = 1; i <= count; i++) {
        ss << "('Airline " << i << "', 'Country " << i << "')";
        if (i != count) ss << ", ";
    }
    ss << ";";
    return ss.str();
}

std::string DataGenerator::generateAirportsInsert(int count) {
    std::stringstream ss;
    ss << "INSERT INTO `Airports` (`Name`, `City`, `Country`) VALUES ";
    for (int i = 1; i <= count; i++) {
        ss << "('Airport " << i << "', 'City " << i << "', 'Country " << i << "')";
        if (i != count) ss << ", ";
    }
    ss << ";";
    return ss.str();
}

std::string DataGenerator::generateBookingsInsert(int count) {
    std::stringstream ss;
    ss << "INSERT INTO `Bookings` (`FlightID`, `PassengerName`, `BookingTime`) VALUES ";
    for (int i = 1; i <= count; i++) {
        ss << "(" << i << ", 'Passenger " << i << "', NOW())";
        if (i != count) ss << ", ";
    }
    ss << ";";
    return ss.str();
}

std::string DataGenerator::generateFlightsInsert(int count) {
    std::stringstream ss;
    ss << "INSERT INTO `Flights` (`AirlineID`, `OriginAirportID`, `DestinationAirportID`, `DepartureTime`, `ArrivalTime`, `Price`, `Status`) VALUES ";
    for (int i = 1; i <= count; i++) {
        ss << "(" << (rand() % 5 + 1) << ", " << (rand() % 5 + 1) << ", " << (rand() % 5 + 1)
           << ", NOW(), NOW(), " << (rand() % 100 + 100) << ".00, 'On Time')";
        if (i != count) ss << ", ";
    }
    ss << ";";
    return ss.str();
}
