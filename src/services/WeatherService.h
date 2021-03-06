//
// Created by fedelonghi on 26/11/17.
//

#ifndef PROYECTO2_WEATHERSERVICE_H
#define PROYECTO2_WEATHERSERVICE_H

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <set>

#include "../message/messages.h"
#include "../utils/utils.h"
#include <map>


class WeatherService {
private:
    int queue_id;
    std::map<std::string,weather_data> database;
    bool running;

    void create_conection_queue();
    s_request read_request();
    weather_response getInfo(string);
    void send_response(weather_response);

    void loadDatabase();
    void saveDatabase();
    void addData(weather_data data, string city);

    bool isRunning();

public:
    WeatherService();

    void run();

    int getQueue_id() const;

    virtual ~WeatherService();

    void stopRunning();
};


#endif //PROYECTO2_WEATHERSERVICE_H
