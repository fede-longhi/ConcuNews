//
// Created by fedelonghi on 26/11/17.
//

#ifndef PROYECTO2_CURRENCYSERVICE_H
#define PROYECTO2_CURRENCYSERVICE_H
#include <iostream>
#include <map>

class CurrencyService {
private:
    int queue_id;
    std::map<std::string,float> database;


    void create_conection_queue();

    void loadDatabase();
    void saveDatabase();
    void addData(float value, std::string currency);

public:
    CurrencyService();

    void run();

    int getQueue_id() const;

    virtual ~CurrencyService();
};


#endif //PROYECTO2_CURRENCYSERVICE_H
