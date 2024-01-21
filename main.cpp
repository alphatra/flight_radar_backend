#include "DbConnector.h"
#include "FlightService.h"
#include "FlightController.h"
#include "DataGenerator.h"
#include <iostream>
#include <stdexcept>

int main() {
    DbConnector db("127.0.0.1", "root", "password", "flight_radar", 3307);
    FlightService flightService(db);
    FlightController flightController(flightService);
    // Konfiguracja i uruchomienie serwera
    crow::SimpleApp app;
    flightController.setupRoutes(app);
    app.port(8080).multithreaded().run();
}
