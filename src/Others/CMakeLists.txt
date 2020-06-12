cmake_minimum_required(VERSION 3.10)
project(SCZR-project)
add_library(others-lib STATIC utilities.cpp database.cpp schedulingPolicies.cpp)
target_link_libraries(others-lib
        #        sudo apt-get install libsqlite3-dev
        sqlite3
        rt)