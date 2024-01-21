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
                        auto tablesJson = flightService.getTables();
                        return crow::response{tablesJson.dump()};
                    } catch (const std::exception& e) {
                        return crow::response(500, e.what());
                    }
                });

        CROW_ROUTE(app, "/flights")
                ([this](){
                    try {
                        auto flightsJson = flightService.getAllFlights();
                        return crow::response{flightsJson.dump()};
                    } catch (const std::exception& e) {
                        return crow::response(500, e.what());
                    }
                });

        CROW_ROUTE(app, "/flights/<string>")
                ([this](const std::string& airlineName) {
                    try {
                        auto flightsJson = flightService.getFlightsByAirline(airlineName);
                        return crow::response{flightsJson.dump()};
                    } catch (const std::exception& e) {
                        return crow::response(500, e.what());
                    }
                });

        CROW_ROUTE(app, "/flights/fromCity/<string>")
                ([this](const std::string& cityName) {
                    try {
                        auto flightsJson = flightService.getFlightsFromCity(cityName);
                        return crow::response{flightsJson.dump()};
                    } catch (const std::exception& e) {
                        return crow::response(500, e.what());
                    }
                });

        CROW_ROUTE(app, "/passengerInfo/<int>")
                ([this](int flightId) {
                    try {
                        auto passengerInfoJson = flightService.getPassengerInfoForFlight(flightId);
                        return crow::response{passengerInfoJson.dump()};
                    } catch (const std::exception& e) {
                        return crow::response(500, e.what());
                    }
                });

        CROW_ROUTE(app, "/createBooking/<int>/<string>/<string>")
                ([this](int flightId, const std::string& seatNumber, const std::string& passengerName) {
                    try {
                        auto bookingResult = flightService.createBooking(flightId, seatNumber, passengerName);
                        return crow::response{bookingResult.dump()};
                    } catch (const std::exception& e) {
                        return crow::response(500, e.what());
                    }
                });

        CROW_ROUTE(app, "/reservedSeats")
                ([this]() {
                    try {
                        auto reservedSeatsJson = flightService.getReservedSeats();
                        return crow::response{reservedSeatsJson.dump()};
                    } catch (const std::exception& e) {
                        return crow::response(500, e.what());
                    }
                });

        CROW_ROUTE(app, "/reservedSeats/<int>")
                ([this](const crow::request& req, int flightId) {
                    try {
                        auto reservedSeatsJson = flightService.getReservedSeatsForFlight(flightId);
                        return crow::response{reservedSeatsJson.dump()};
                    } catch (const std::exception& e) {
                        return crow::response(500, e.what());
                    }
                });

        CROW_ROUTE(app, "/availableSeats/<int>")
                ([this](const crow::request& req, int flightId) {
                    try {
                        auto availableSeatsJson = flightService.getAvailableSeatsForFlight(flightId);
                        return crow::response{availableSeatsJson.dump()};
                    } catch (const std::exception& e) {
                        return crow::response(500, e.what());
                    }
                });

    }

private:
    FlightService& flightService;
};

#endif //BACKEND_FLIGHT_RADAR_FLIGHTCONTROLLER_H