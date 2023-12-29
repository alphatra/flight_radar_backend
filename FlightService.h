//
// Created by Gracjan Ziemiański on 29/12/2023.
//

#ifndef BACKEND_FLIGHT_RADAR_FLIGHTSERVICE_H
#define BACKEND_FLIGHT_RADAR_FLIGHTSERVICE_H
#include "DbConnector.h"
#include <nlohmann/json.hpp>
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

private:
    DbConnector& db;
};

#endif //BACKEND_FLIGHT_RADAR_FLIGHTSERVICE_H
