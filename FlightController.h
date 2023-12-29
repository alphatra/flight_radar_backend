//
// Created by Gracjan Ziemiański on 29/12/2023.
//

#ifndef BACKEND_FLIGHT_RADAR_FLIGHTCONTROLLER_H
#define BACKEND_FLIGHT_RADAR_FLIGHTCONTROLLER_H
#include "FlightService.h"
#include "crow_all.h"

class FlightController {
public:
    FlightController(FlightService& service) : flightService(service) {}

    void setupRoutes(crow::SimpleApp& app) {
        CROW_ROUTE(app, "/tables")
                ([this](){
                    try {
                        auto tables = flightService.getTables();
                        std::ostringstream os;
                        for (const auto& table : tables) {
                            os << table << "\n";
                        }
                        return crow::response{os.str()};
                    } catch (const std::exception& e) {
                        return crow::response(500, e.what());
                    }
                });
    }

private:
    FlightService& flightService;
};

#endif //BACKEND_FLIGHT_RADAR_FLIGHTCONTROLLER_H
