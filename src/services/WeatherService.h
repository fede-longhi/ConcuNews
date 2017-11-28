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


class WeatherService {
private:
    int queue_id;

    void create_conection_queue();
    int read_request();
    weather_response getInfo(int);
    void send_response(weather_response);
    float getPressure(int);
    float getHummidity(int);
    float getTemperature(int);

public:
    WeatherService();

    void run();

    int getQueue_id() const;

    virtual ~WeatherService();
};


#endif //PROYECTO2_WEATHERSERVICE_H
