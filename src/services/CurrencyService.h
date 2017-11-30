//
// Created by fedelonghi on 26/11/17.
//

#ifndef PROYECTO2_CURRENCYSERVICE_H
#define PROYECTO2_CURRENCYSERVICE_H

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <set>
#include <map>

#include "../message/messages.h"
#include "../utils/utils.h"


class CurrencyService {
private:
    int queue_id;
    std::map<std::string,float> database;
    bool running;

    void create_conection_queue();

    void loadDatabase();
    void saveDatabase();
    void addData(float value, std::string currency);
    currency_response getInfo(string);

    bool isRunning();
    void stopRunning();

    s_request read_request();
    void send_response(currency_response);

public:
    CurrencyService();
    void run();
    int getQueue_id() const;
    virtual ~CurrencyService();
};


#endif //PROYECTO2_CURRENCYSERVICE_H
