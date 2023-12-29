cmake_minimum_required(VERSION 3.27)
project(Backend_Flight_Radar)

set(CMAKE_CXX_STANDARD 17)
find_package(Boost 1.83.0 COMPONENTS date_time REQUIRED)

# Dodajemy katalogi nagłówków
include_directories(${Boost_INCLUDE_DIRS})
include_directories(/usr/local/include)
include_directories(/opt/homebrew/Cellar/mysql/8.2.0_1/include)

add_executable(Backend_Flight_Radar main.cpp
        DbConnector.h
        FlightService.h
        FlightController.h)

# Znajdujemy i linkujemy z biblioteką klienta MySQL
find_library(MYSQL_LIBRARY NAMES mysqlclient PATHS /opt/homebrew/lib)

if(NOT MYSQL_LIBRARY)
    message(FATAL_ERROR "MySQL client library not found.")
endif()

# Linkujemy z bibliotekami Boost i klientem MySQL
target_link_libraries(Backend_Flight_Radar ${Boost_LIBRARIES} ${MYSQL_LIBRARY})
