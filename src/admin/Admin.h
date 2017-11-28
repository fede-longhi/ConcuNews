//
// Created by fedelonghi on 24/11/17.
//

#ifndef PROYECTO2_ADMIN_H
#define PROYECTO2_ADMIN_H

#include <iostream>
#include <sys/msg.h>

#include "../message/messages.h"
#include "../utils/utils.h"


class Admin {
private:
    int admin_id;
    int queue_id;

public:

    Admin();

    int get_id();

    int request_connection();
    void read_connection_response();
    void establish_connection();

    void update_weather(admin_request);
    void update_currency(admin_request);
    void close_server();

    void set_queueid(int id);

    virtual ~Admin();

};


#endif //PROYECTO2_ADMIN_H
