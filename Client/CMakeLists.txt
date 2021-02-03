cmake_minimum_required(VERSION 3.5)

project(new_client LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 5.7 COMPONENTS Core Gui Widgets Network REQUIRED)
#find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
#find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

add_executable(Client
    main.cpp
    window.cpp
    client.cpp
    window.ui
    window.h
    client.h
)

target_link_libraries(Client PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network)

