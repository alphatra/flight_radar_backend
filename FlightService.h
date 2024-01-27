//
// Created by Gracjan Ziemiański on 29/12/2023.
//

#ifndef BACKEND_FLIGHT_RADAR_FLIGHTSERVICE_H
#define BACKEND_FLIGHT_RADAR_FLIGHTSERVICE_H
#include "DbConnector.h"
#include "json.hpp"
#include <mysql/mysql.h>
#include <vector>
#include <string>
#include <iostream>

class FlightService {
public:
    FlightService(DbConnector& dbConnector) : db(dbConnector) {}

    nlohmann::json getTables() {
        MYSQL* conn = db.getConnection();
        nlohmann::json resultJson;

        if (mysql_query(conn, "SHOW TABLES")) {
            throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
        }

        MYSQL_RES* result = mysql_store_result(conn);
        if (!result) {
            throw std::runtime_error("Failed to store result: " + std::string(mysql_error(conn)));
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)) != NULL) {
            resultJson["tables"].push_back(row[0]);
        }

        mysql_free_result(result);
        return resultJson;
    }

    nlohmann::json getAllFlights() {
    MYSQL* conn = db.getConnection();
      nlohmann::json resultJson;
    if (mysql_query(conn, "SELECT f.FlightID, a.Name AS Airline, ao.City AS OriginCity, ad.City AS DestinationCity, f.DepartureTime, f.ArrivalTime, f.Price, f.Status "
      "FROM Flights f "
      "JOIN Airlines a ON f.AirlineID = a.AirlineID "
      "JOIN Airports ao ON f.OriginAirportID = ao.AirportID "
      "JOIN Airports ad ON f.DestinationAirportID = ad.AirportID;")) {
      throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        throw std::runtime_error("Failed to store result: " + std::string(mysql_error(conn)));
      }

      MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)) != NULL) {
      nlohmann::json flight;
        flight["flight_id"] = row[0];
      flight["airline"] = row[1];
        flight["origin_city"] = row[2];
      flight["destination_city"] = row[3];
        flight["departure_time"] = row[4];
      flight["arrival_time"] = row[5];
        flight["price"] = row[6];
      flight["status"] = row[7];
        resultJson["flights"].push_back(flight);
      }

      mysql_free_result(result);
    return resultJson;
      }

    nlohmann::json getFlightsByAirline(const std::string& airlineName) {
        MYSQL* conn = db.getConnection();
        nlohmann::json resultJson;

        std::string query =
        "SELECT f.FlightID, a.Name AS Airline, ao.City AS OriginCity, ad.City AS DestinationCity, f.DepartureTime, f.ArrivalTime, f.Price, f.Status "
            "FROM Flights f "
            "JOIN Airlines a ON f.AirlineID = a.AirlineID "
            "JOIN Airports ao ON f.OriginAirportID = ao.AirportID "
            "JOIN Airports ad ON f.DestinationAirportID = ad.AirportID "
            "WHERE a.Name = '" + airlineName + "';";
        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
        }

        MYSQL_RES* result = mysql_store_result(conn);
        if (!result) {
            throw std::runtime_error("Failed to store result: " + std::string(mysql_error(conn)));
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)) != NULL) {
            nlohmann::json flight;
            // Uzupełnij odpowiednio do struktury tabeli Flights
            flight["flight_id"] = row[0];
            flight["departure_time"] = row[1];
            flight["arrival_time"] = row[2];
            flight["price"] = row[3];
            flight["status"] = row[4];
            resultJson.push_back(flight);
        }

        mysql_free_result(result);
        return resultJson;
    }
    nlohmann::json getFlightsFromCity(const std::string& cityName) {
        MYSQL* conn = db.getConnection();
        nlohmann::json resultJson;

        std::string query =
        "SELECT f.FlightID, a.Name AS Airline, ad.City AS DestinationCity, f.DepartureTime, f.Status "
            "FROM Flights f "
            "JOIN Airlines a ON f.AirlineID = a.AirlineID "
            "JOIN Airports ao ON f.OriginAirportID = ao.AirportID "
            "JOIN Airports ad ON f.DestinationAirportID = ad.AirportID "
            "WHERE ao.City = '" + cityName + "';";
        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
        }

        MYSQL_RES* result = mysql_store_result(conn);
        if (!result) {
            throw std::runtime_error("Failed to store result: " + std::string(mysql_error(conn)));
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)) != NULL) {
            nlohmann::json flight;
            flight["flight_id"] = row[0];
            flight["airline"] = row[1];
            flight["departure_time"] = row[2];
            flight["status"] = row[3];
            resultJson.push_back(flight);
        }

        mysql_free_result(result);
        return resultJson;
    }
    nlohmann::json getPassengerInfoForFlight(int flightId) {
        MYSQL* conn = db.getConnection();
        nlohmann::json resultJson;

        std::string query = "SELECT b.PassengerName, b.BookingTime, f.FlightID "
                            "FROM Bookings b "
                            "JOIN Flights f ON b.FlightID = f.FlightID "
                            "WHERE f.FlightID = " + std::to_string(flightId) + ";";

        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
        }

        MYSQL_RES* result = mysql_store_result(conn);
        if (!result) {
            throw std::runtime_error("Failed to store result: " + std::string(mysql_error(conn)));
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)) != NULL) {
            nlohmann::json passengerInfo;
            passengerInfo["passenger_name"] = row[0];
            passengerInfo["booking_time"] = row[1];
            passengerInfo["flight_id"] = row[2];
            resultJson.push_back(passengerInfo);
        }

        mysql_free_result(result);
        return resultJson;
    }
    nlohmann::json createBooking(int flightId, const std::string& seatNumber, const std::string& passengerName) {
        MYSQL* conn = db.getConnection();
        nlohmann::json resultJson;

        // Sprawdzenie dostępności miejsca
        std::string checkQuery = "SELECT IsOccupied FROM Seats WHERE FlightID = " + std::to_string(flightId) + " AND SeatNumber = '" + seatNumber + "';";
        if (mysql_query(conn, checkQuery.c_str())) {
            throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
        }

        MYSQL_RES* checkResult = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(checkResult);
        if (!row || std::stoi(row[0]) == 1) {
            resultJson["status"] = "error";
            resultJson["message"] = "Seat is already occupied";
            mysql_free_result(checkResult);
            return resultJson;
        }
        mysql_free_result(checkResult);

        // Rezerwacja miejsca
        std::string insertQuery = "INSERT INTO Bookings (FlightID, PassengerName, SeatNumber) VALUES (" + std::to_string(flightId) + ", '" + passengerName + "', '" + seatNumber + "');";
        if (mysql_query(conn, insertQuery.c_str())) {
            throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
        }

        // Zaktualizowanie statusu miejsca
        std::string updateQuery = "UPDATE Seats SET IsOccupied = 1 WHERE FlightID = " + std::to_string(flightId) + " AND SeatNumber = '" + seatNumber + "';";
        if (mysql_query(conn, updateQuery.c_str())) {
            throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
        }

        resultJson["status"] = "success";
        resultJson["message"] = "Booking created successfully";
        return resultJson;
    }

    nlohmann::json getReservedSeats() {
        MYSQL* conn = db.getConnection();
        nlohmann::json resultJson;

        std::string query = "SELECT FlightID, SeatNumber, PassengerName FROM Bookings WHERE SeatNumber IS NOT NULL;";
        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
        }

        MYSQL_RES* result = mysql_store_result(conn);
        if (!result) {
            throw std::runtime_error("Failed to store result: " + std::string(mysql_error(conn)));
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)) != NULL) {
            nlohmann::json booking;
            booking["flight_id"] = row[0];
            booking["seat_number"] = row[1];
            booking["passenger_name"] = row[2];
            resultJson.push_back(booking);
        }

        mysql_free_result(result);
        return resultJson;
    }

    nlohmann::json getReservedSeatsForFlight(int flightId) {
        MYSQL* conn = db.getConnection();
        nlohmann::json resultJson;
        std::string query = "SELECT SeatNumber FROM Seats WHERE FlightID = " + std::to_string(flightId) + " AND IsOccupied = 1;";
        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
        }

        MYSQL_RES* result = mysql_store_result(conn);
        if (!result) {
            throw std::runtime_error("Failed to store result: " + std::string(mysql_error(conn)));
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)) != NULL) {
            resultJson.push_back({{"seat_number", row[0]}});
        }

        mysql_free_result(result);
        return resultJson;
    }

    nlohmann::json getAvailableSeatsForFlight(int flightId) {
        MYSQL* conn = db.getConnection();
        nlohmann::json resultJson;

        std::string query = "SELECT SeatNumber FROM Seats WHERE FlightID = " + std::to_string(flightId) + " AND IsOccupied = 0;";
        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
        }

        MYSQL_RES* result = mysql_store_result(conn);
        if (!result) {
            throw std::runtime_error("Failed to store result: " + std::string(mysql_error(conn)));
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)) != NULL) {
            resultJson.push_back({{"seat_number", row[0]}});
        }

        mysql_free_result(result);
        return resultJson;
    }
    nlohmann::json getFlightsBetweenCities(const std::string& originCity, const std::string& destinationCity) {
      MYSQL* conn = db.getConnection();
      nlohmann::json resultJson;

      std::string query = "SELECT f.FlightID, a.Name AS Airline, f.DepartureTime, f.ArrivalTime, f.Price, f.Status "
                          "FROM Flights f "
                          "JOIN Airlines a ON f.AirlineID = a.AirlineID "
                          "JOIN Airports ao ON f.OriginAirportID = ao.AirportID "
                          "JOIN Airports ad ON f.DestinationAirportID = ad.AirportID ";

      bool whereClauseAdded = false;
      if (!originCity.empty()) {
        query += "WHERE ao.City = '" + originCity + "' ";
        whereClauseAdded = true;
      }
      if (!destinationCity.empty()) {
        query += (whereClauseAdded ? "AND " : "WHERE ") + std::string("ad.City = '") + destinationCity + "'";
      }

      if (mysql_query(conn, query.c_str())) {
        throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
      }

      MYSQL_RES* result = mysql_store_result(conn);
      if (!result) {
        throw std::runtime_error("Failed to store result: " + std::string(mysql_error(conn)));
      }

      MYSQL_ROW row;
      while ((row = mysql_fetch_row(result)) != NULL) {
        nlohmann::json flight;
        // Uzupełnij odpowiednio do struktury tabeli Flights
        flight["flight_id"] = row[0];
        flight["airline"] = row[1];
        flight["departure_time"] = row[2];
        flight["arrival_time"] = row[3];
        flight["price"] = row[4];
        flight["status"] = row[5];
        resultJson.push_back(flight);
    }

    mysql_free_result(result);
    return resultJson;
}
    nlohmann::json getFlightsFromToWithinDateRange(const std::string& originCity, const std::string& destinationCity, const std::string& startDate, const std::string& endDate) {
    MYSQL* conn = db.getConnection();
    nlohmann::json resultJson;

    std::string query = "SELECT f.FlightID, a.Name AS Airline, ao.City AS OriginCity, ad.City AS DestinationCity, f.DepartureTime, f.ArrivalTime, f.Price, f.Status "
                        "FROM Flights f "
                        "JOIN Airlines a ON f.AirlineID = a.AirlineID "
                        "JOIN Airports ao ON f.OriginAirportID = ao.AirportID "
                        "JOIN Airports ad ON f.DestinationAirportID = ad.AirportID "
                        "WHERE ao.City = '" + originCity + "' AND ad.City = '" + destinationCity + "' "
                        "AND f.DepartureTime >= '" + startDate + "' AND f.DepartureTime <= '" + endDate + "' "
                        "AND f.ArrivalTime >= '" + startDate + "' AND f.ArrivalTime <= '" + endDate + "';";

    if (mysql_query(conn, query.c_str())) {
        throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        throw std::runtime_error("Failed to store result: " + std::string(mysql_error(conn)));
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)) != NULL) {
        nlohmann::json flight;
        flight["flight_id"] = row[0];
        flight["airline"] = row[1];
        flight["origin_city"] = row[2];
        flight["destination_city"] = row[3];
        flight["departure_time"] = row[4];
        flight["arrival_time"] = row[5];
        flight["price"] = row[6];
        flight["status"] = row[7];
        resultJson.push_back(flight);
    }

    mysql_free_result(result);
    return resultJson;
}




private:
    DbConnector& db;
};

#endif //BACKEND_FLIGHT_RADAR_FLIGHTSERVICE_H
