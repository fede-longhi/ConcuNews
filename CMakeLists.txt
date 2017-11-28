cmake_minimum_required(VERSION 3.8)
project(Proyecto2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/message/messages.h src/client/Cliente.cpp src/client/Cliente.h src/server/Server.cpp src/server/Server.h src/utils/utils.h)
add_executable(Proyecto2 ${SOURCE_FILES})

set(SOURCE_FILES_CLIENT client.cpp src/message/messages.h src/client/Cliente.cpp src/client/Cliente.h src/server/Server.cpp src/server/Server.h src/utils/utils.h)
add_executable(client ${SOURCE_FILES_CLIENT})

set(SOURCE_FILES_SERVER server.cpp src/message/messages.h src/client/Cliente.cpp src/client/Cliente.h src/server/Server.cpp src/server/Server.h src/utils/utils.h)
add_executable(server ${SOURCE_FILES_SERVER})

set(SOURCE_FILES_ADMIN admin.cpp src/message/messages.h src/admin/Admin.cpp src/admin/Admin.h src/utils/utils.h)
add_executable(admin ${SOURCE_FILES_ADMIN})

set(SOURCE_FILES_WS weather_service.cpp src/services/WeatherService.cpp src/services/WeatherService.h src/utils/utils.h)
add_executable(weather_service ${SOURCE_FILES_WS})

set(SOURCE_FILES_CS currency_service.cpp  src/services/CurrencyService.cpp src/services/CurrencyService.h src/utils/utils.h)
add_executable(currency_service ${SOURCE_FILES_CS})