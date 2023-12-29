//
// Created by Gracjan Ziemiański on 28/12/2023.
//
#include <string>
#include <vector>
#include <random>
#include <ctime>

struct FlightData {
    int airlineID;
    int originAirportID;
    int destinationAirportID;
    std::string departureTime;
    std::string arrivalTime;
    double price;
    std::string status;
};

FlightData generateFlightData() {
    static std::mt19937 rng(static_cast<unsigned int>(time(nullptr))); // generator liczb pseudolosowych
    std::uniform_int_distribution<int> airlineDist(1, 10); // zakładamy 10 różnych linii lotniczych
    std::uniform_int_distribution<int> airportDist(1, 20); // zakładamy 20 różnych lotnisk
    std::uniform_real_distribution<double> priceDist(100.0, 1000.0); // zakres cen biletów
    std::vector<std::string> statuses = {"On Time", "Delayed", "Cancelled"};

    FlightData flight;
    flight.airlineID = airlineDist(rng);
    flight.originAirportID = airportDist(rng);
    flight.destinationAirportID = airportDist(rng);
    flight.departureTime = "2023-12-01T14:26:57"; // przykładowa data, można tu dodać generowanie losowej daty
    flight.arrivalTime = "2023-12-01T20:26:57"; // przykładowa data
    flight.price = priceDist(rng);
    flight.status = statuses[rng() % statuses.size()];

    return flight;
}
