//
// Created by Gracjan Ziemiański on 29/12/2023.
//

#ifndef BACKEND_FLIGHT_RADAR_DBCONNECTOR_H
#define BACKEND_FLIGHT_RADAR_DBCONNECTOR_H
#include <mysql/mysql.h>
#include <string>
#include <stdexcept>

class DbConnector {
public:
    DbConnector(const std::string& host, const std::string& user, const std::string& password, const std::string& database, int port) {
        mysql_init(&mysql);
        connection = mysql_real_connect(&mysql, host.c_str(), user.c_str(), password.c_str(), database.c_str(), port, NULL, 0);
        if (connection == NULL) {
            throw std::runtime_error(mysql_error(&mysql));
        }
    }

    ~DbConnector() {
        if (connection) {
            mysql_close(connection);
        }
    }

    void executeQuery(const std::string& query) {
        if (mysql_query(connection, query.c_str())) {
            throw std::runtime_error(mysql_error(connection));
        }
    }

    MYSQL* getConnection() {
        return connection;
    }

private:
    MYSQL mysql;
    MYSQL* connection;
};

#endif //BACKEND_FLIGHT_RADAR_DBCONNECTOR_H
