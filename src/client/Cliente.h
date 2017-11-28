//
// Created by fedelonghi on 05/11/17.
//

#ifndef PROYECTO2_CLIENTE_H
#define PROYECTO2_CLIENTE_H

#include <iostream>
#include <sys/msg.h>

#include "../message/messages.h"
#include "../utils/utils.h"


using namespace std;

class Cliente {

private:
    int client_id;
    int queue_id;

public:

    Cliente();

    int get_id();

    int request_connection();
    void read_connection_response();
    void establish_connection();

    void send_request(service_request message);
    void request_weather(string);
    void request_currency(string);
    weather_response read_weather_response();
    currency_response read_currency_response();
    void set_queueid(int id);

    virtual ~Cliente();

};


#endif //PROYECTO2_CLIENTE_H
