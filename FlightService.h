//
// Created by Gracjan Ziemiański on 29/12/2023.
//

#ifndef BACKEND_FLIGHT_RADAR_FLIGHTSERVICE_H
#define BACKEND_FLIGHT_RADAR_FLIGHTSERVICE_H
#include "DbConnector.h"
#include <mysql/mysql.h>
#include <vector>
#include <string>
#include <iostream>

class FlightService {
public:
    FlightService(DbConnector& dbConnector) : db(dbConnector) {}

    std::vector<std::string> getTables() {
        MYSQL* conn = db.getConnection();
        std::vector<std::string> tables;

        if (mysql_query(conn, "SHOW TABLES")) {
            std::cerr << "MySQL query error: " << mysql_error(conn) << std::endl;
            throw std::runtime_error("Failed to execute query");
        }

        MYSQL_RES* result = mysql_store_result(conn);
        if (!result) {
            std::cerr << "MySQL store result error: " << mysql_error(conn) << std::endl;
            throw std::runtime_error("Failed to store result");
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)) != NULL) {
            tables.push_back(row[0]);
        }

        mysql_free_result(result);
        return tables;
    }

private:
    DbConnector& db;
};

#endif //BACKEND_FLIGHT_RADAR_FLIGHTSERVICE_H
