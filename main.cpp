#include "DbConnector.h"
#include "FlightService.h"
#include "FlightController.h"

int main() {
    DbConnector db("127.0.0.1", "root", "password", "flight_radar", 3307);
    FlightService flightService(db);
    FlightController flightController(flightService);

    crow::SimpleApp app;
    flightController.setupRoutes(app);
    app.port(8080).multithreaded().run();
}
